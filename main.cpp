#include <iostream>
#include <vector>
#include "Vec3.h"
#include "Camera.h"
#include "Color.h"
#include "fstream"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"
#include "Matrix3.h"
#include "Triangle.h"
#include "Light.h"

using namespace  std;

#define AMBIENT 10.0/255.0
#define EPSILON 0.000001
#define PHONGEXPONENT 100


Camera* readCamera(const string& fileName, string& outFileName);
Color*** initImage(const Camera& camera);
void readScene(vector<GeometricObject*>& scene, const string& sceneFileName);
void renderImage(vector<GeometricObject*>& scene, Color*** imagePlane, const Camera& camera, const Light& light);
int traceRay(Ray ray, vector<GeometricObject*>& scene, double &tmin);
void writeImage(Color*** imagePlane, string outFileName, const Camera& camera);

int main() {
    string outFileName;
    Camera* camera = readCamera("..\\simple_camera.txt",outFileName);
    if(!camera)
    {
        cout << "Problem creating the camera" << endl;
        exit(2);
    }
    Color*** imagePlane = initImage(*camera);
    std::vector<GeometricObject*> scene;
    readScene(scene,"..\\simple_scene.txt");

    Light light(Vec3(30,10,10), Color(200.0/255.0,200.0/255.0,200.0/255.0));
    renderImage(scene, imagePlane, *camera, light);
    writeImage(imagePlane,outFileName,*camera);
    return 0;
}

Camera* readCamera(const string& fileName, string& outFileName)
{
    ifstream cameraFile;
    cameraFile.open(fileName);
    if(!cameraFile)
    {
        cout << "Can't open the camera file" << endl;
        exit(1);
    }
    double x,y,z,l,r,b,t,d;
    int sizeX,sizeY;
    Vec3* e = nullptr;  Vec3* gaze = nullptr; Vec3* v = nullptr;
    if(cameraFile >> x >> y >> z)
    {
        e = new Vec3(x,y,z);
    }
    if(cameraFile >> x >> y >> z)
    {
        gaze = new Vec3(x,y,z);
    }
    if(cameraFile >> x >> y >> z)
    {
        v = new Vec3(x,y,z);
    }

    if((cameraFile >> l >> r >> b >> t >> d >> sizeX >> sizeY >> outFileName) && e && gaze && v)
    {
        cameraFile.close();
        return new Camera(*e,*gaze,*v,l,r,b,t,d,sizeX,sizeY);
    }
    cameraFile.close();
    return nullptr;
}

Color*** initImage(const Camera& camera)
{
    Color*** imagePlan = (Color ***) malloc(camera.getSizeY()* sizeof(Color**));
    if(!imagePlan)
    {
        printf("Cannot allocate memory for image.");
        exit(3);
    }
    for(int i=0; i<camera.getSizeY(); i++)
    {
        imagePlan[i] = (Color **) malloc(camera.getSizeX()* sizeof(Color*));
        if(!imagePlan[i])
        {
            printf("Cannot allocate memory for image.");
            exit(4);
        }
    }
    for(int i=0; i<camera.getSizeY(); i++)
    {
        for(int j=0; j<camera.getSizeX(); j++)
        {
            imagePlan[i][j] = new Color(0,0,0);
        }
    }
    return imagePlan;
}

void readScene(vector<GeometricObject*>& scene, const string& sceneFileName)
{
    ifstream sceneFile;
    sceneFile.open(sceneFileName);
    if(!sceneFile)
    {
        cout << "Can't open the scene file" << endl;
        exit(5);
    }

    int numSpheres = 0;
    double x,y,z,radius,r,g,b;
    sceneFile >> numSpheres;
    for(int i=0; i<numSpheres; i++)
    {
        if(sceneFile >> x >> y >> z >> radius >> r >> g >> b)
        {
            scene.push_back(new Sphere(Vec3(x,y,z), radius, Color((double)r,(double)g,(double)b)));
        }
    }

    int numTriangles = 0;
    double Ax,Ay,Az,Bx,By,Bz,Cx,Cy,Cz;
    sceneFile >> numTriangles;
    for(int i=0; i<numTriangles; i++)
    {
        if(sceneFile >> Ax >> Ay >> Az >> Bx >> By >> Bz >> Cx >> Cy >> Cz >> r >> g >> b)
        {
            scene.push_back(new Triangle(Color(r,g,b), Vec3(Ax,Ay,Az), Vec3(Bx,By,Bz), Vec3(Cx,Cy,Cz)));
        }
    }

    sceneFile.close();
}

void renderImage(vector<GeometricObject*>& scene, Color*** imagePlane, const Camera& camera, const Light& light)
{
    Vec3 m = camera.getE() + camera.getGaze()%camera.getD();
    Vec3 q = m + camera.getU()%camera.getL() + camera.getV()%camera.getT();
    Vec3 s(0,0,0);
    double su, sv;
    Ray currentRay(Vec3(0,0,0), Vec3(0,0,0));
    int closetObject, shadowingObject;
    double tmin, disposableTmin;
    double diffuse;
    double specular;
    Vec3 toLight(0,0,0), point(0,0,0), normal(0,0,0), toEye(0,0,0), half(0,0,0);
    for(int i=0; i<camera.getSizeY(); i++)
    {
        for(int j=0; j<camera.getSizeX(); j++)
        {
            su = j*camera.getPixelW() + camera.getHalfPixelW();
            sv = i*camera.getPixelH() + camera.getHalfPixelH();
            s = Vec3(q + camera.getU()%su - camera.getV()%sv);
            currentRay = Ray(camera.getE(), s - camera.getE());
            closetObject = traceRay(currentRay, scene,tmin);
            if(closetObject > -1)
            {
                point = Vec3(currentRay.getO() + currentRay.getD()%tmin);
                toLight = Vec3(light.getPos() - (point));
                toLight.normalize();
                imagePlane[i][j]->setR(scene[closetObject]->getColor().getR()*AMBIENT);
                imagePlane[i][j]->setG(scene[closetObject]->getColor().getG()*AMBIENT);
                imagePlane[i][j]->setB(scene[closetObject]->getColor().getB()*AMBIENT);
                shadowingObject = traceRay(Ray(point+toLight%EPSILON, toLight), scene, disposableTmin);
                if(shadowingObject == -1)
                {
                    normal = Vec3(scene[closetObject]->getNormal(point));
                    diffuse = (toLight) * (normal);
                    if(diffuse < 0)
                        diffuse = 0;
                    toEye = Vec3(currentRay.getD()%(-1));
                    toEye.normalize();
                    half = Vec3(toLight + toEye);
                    half.normalize();
                    specular = half * normal;
                    if(specular < 0)
                        specular = 0;
                    imagePlane[i][j]->setR(scene[closetObject]->getColor().getR()*light.getIntensity().getR()*diffuse +
                                                   pow(specular,PHONGEXPONENT)*light.getIntensity().getR()
                                                   + imagePlane[i][j]->getR());
                    imagePlane[i][j]->setG(scene[closetObject]->getColor().getG()*light.getIntensity().getG()*diffuse +
                                                   pow(specular,PHONGEXPONENT)*light.getIntensity().getG()
                                                   + imagePlane[i][j]->getG());
                    imagePlane[i][j]->setB(scene[closetObject]->getColor().getB()*light.getIntensity().getB()*diffuse +
                                                   pow(specular,PHONGEXPONENT)*light.getIntensity().getB()
                                                   + imagePlane[i][j]->getB());
                }
            }
        }
    }
}

int traceRay(Ray ray, vector<GeometricObject*>& scene, double &tmin)
{
    tmin = 40000;
    int closetObject = -1;
    double t;
    for(int k=0; k<scene.size(); k++)
    {
        if(scene[k]->hitMe(t,ray) && t<tmin)
        {
            tmin = t;
            closetObject = k;
        }
    }
    return closetObject;
}

void writeImage(Color*** imagePlane, string outFileName, const Camera& camera)
{
    ofstream imageFile;
    imageFile.open("..\\"+outFileName);
    imageFile << "P3" << endl;
    imageFile << "# " << outFileName << endl;
    imageFile << camera.getSizeX() << " " << camera.getSizeY() << endl;
    imageFile << 255 << endl;
    for(int i=0; i<camera.getSizeY(); i++)
    {
        for(int j=0; j<camera.getSizeX(); j++)
        {
            imageFile << *(imagePlane[i][j]);
        }
        imageFile << endl;
    }
    imageFile.close();
}

/*
    std::cout << "Hello, World!" << std::endl;
    Vec3 v1(1,2,3);
    Vec3 v2(6,7,8);
    cout << (v1^v2) << endl;
    cout << (v2^v1) << endl;
    cout << (v2*v1) << endl;
    cout << (v2+v1) << endl;
    cout << (v2-v1) << endl;
    cout << (v1%3) << endl;
    cout << (v1==v2) << endl;
    cout << (v1==v1) << endl;
    cout << ((Vec3(1,2,1))|(Vec3(1,-1,5))) <<endl;
    v1.normalize();
    v2.normalize();
    cout <<  v1 << v1.length() << v2 << v2.length() << endl;
    cout << 0.267261 << 0.267261*2 << 0.267261*3 << endl;
*/

/*for(GeometricObject* geo:scene)
    {
        Sphere* s = dynamic_cast<Sphere *> (geo);
        if(s)
        {
            cout << s->getCenter().getX() << " " << s->getCenter().getY() << " " << s->getCenter().getZ() <<endl;
            cout << s->getR() << endl;
            cout << s->getColor().getR() << " " << s->getColor().getG() << " " << s->getColor().getB() <<endl;
        }
    }*/