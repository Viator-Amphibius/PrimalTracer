#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Vec3.h"
#include "Camera.h"
#include "Color.h"
#include <fstream>
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"
#include "Matrix3.h"
#include "Triangle.h"
#include "Light.h"

using namespace  std;

#define BACKGROUD_R 0
#define BACKGROUD_G 0
#define BACKGROUD_B 0
#define AMBIENT 10.0/255.0
#define EPSILON 0.000001
#define PHONG_EXPONENT 100
#define MAX_DEPTH 2 //When set to 1 there will be no reflections, else, there will be (depth-1) iterations of reflections


Camera* readCamera(const string& fileName, string& outFileName);
Color*** initImage(const Camera& camera);
void readScene(vector<GeometricObject*>& scene, const string& sceneFileName);
void renderImage(vector<GeometricObject*>& scene, Color*** imagePlane, const Camera& camera, const Light& light);
bool getPixelColor(Color& Pixel, vector<GeometricObject*>& scene, const Light& light, Ray currentRay, double t_least, int depth);
int traceRay(Ray ray, vector<GeometricObject*>& scene, double &tmin, double t_least);
void writeImage(Color*** imagePlane, string outFileName, const Camera& camera);

/*
 Commands for running using g++
 >g++ main.cpp Vec3.h Vec3.cpp Matrix3.h Matrix3.cpp Ray.h Ray.cpp Color.h Color.cpp Light.h Light.cpp GeometricObject.h GeometricObject.cpp Triangle.h Triangle.cpp Sphere.h Sphere.cpp Camera.h Camera.cpp
 >a simple_camera.txt simple_scene.txt
 */

int main(int argc, char** argv) {
    string outFileName;
    string cameraFileName;
    string sceneFileName;
    if(argc >=3)
    {
        cameraFileName = argv[1];
        sceneFileName = argv[2];
    }
    else
    {
        cout << "Invalid command line arguments, running the program using default file names (simple_camera.txt, simple_scene.txt)" << endl;
        cameraFileName = "simple_camera.txt";
        sceneFileName = "simple_scene.txt";
    }
    Camera* camera = readCamera(cameraFileName,outFileName);
    if(!camera)
    {
        cout << "Problem creating the camera" << endl;
        exit(2);
    }
    Color*** imagePlane = initImage(*camera);
    std::vector<GeometricObject*> scene;
    readScene(scene,sceneFileName);

    Light light(Vec3(30,10,10), Color(200.0/255.0,200.0/255.0,200.0/255.0));
    renderImage(scene, imagePlane, *camera, light);
    writeImage(imagePlane,outFileName,*camera);
    return 0;
}

Camera* readCamera(const string& fileName, string& outFileName)
{
    ifstream cameraFile;
    cameraFile.open(fileName.c_str());
    if(!cameraFile)
    {
        cout << "Can't open the camera file" << endl;
        exit(1);
    }
    double x,y,z,l,r,b,t,d;
    int sizeX,sizeY;
    Vec3* e = NULL;  Vec3* gaze = NULL; Vec3* v = NULL;
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
    return NULL;
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
            imagePlan[i][j] = new Color(BACKGROUD_R,BACKGROUD_G,BACKGROUD_B);
        }
    }
    return imagePlan;
}

void readScene(vector<GeometricObject*>& scene, const string& sceneFileName)
{
    ifstream sceneFile;
    sceneFile.open(sceneFileName.c_str());
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
    Color Pixel(0,0,0);
    for(int i=0; i<camera.getSizeY(); i++)
    {
        for(int j=0; j<camera.getSizeX(); j++)
        {
            su = j*camera.getPixelW() + camera.getHalfPixelW();
            sv = i*camera.getPixelH() + camera.getHalfPixelH();
            s = Vec3(q + camera.getU()%su - camera.getV()%sv);
            currentRay = Ray(camera.getE(), s - camera.getE());
            if(getPixelColor(Pixel,scene,light,currentRay,1,1))
            {
                *imagePlane[i][j] = Pixel;
            }
        }
    }
}

bool getPixelColor(Color& Pixel, vector<GeometricObject*>& scene, const Light& light, Ray currentRay, double t_least, int depth) {
    int closetObject, shadowingObject;
    double tmin, disposableTmin;
    double diffuse;
    double specular;
    Vec3 toLight(0, 0, 0), point(0, 0, 0), normal(0, 0, 0), toEye(0, 0, 0), half(0, 0, 0);
    closetObject = traceRay(currentRay, scene, tmin, t_least);
    if (closetObject > -1) {
        point = Vec3(currentRay.getO() + currentRay.getD() % tmin);
        toLight = Vec3(light.getPos() - (point));
        toLight.normalize();
        normal = Vec3(scene[closetObject]->getNormal(point));
        toEye = Vec3(currentRay.getD() % (-1));
        toEye.normalize();
        Pixel.setR(scene[closetObject]->getColor().getR() * AMBIENT);
        Pixel.setG(scene[closetObject]->getColor().getG() * AMBIENT);
        Pixel.setB(scene[closetObject]->getColor().getB() * AMBIENT);
        shadowingObject = traceRay(Ray(point + toLight % EPSILON, toLight), scene, disposableTmin, t_least);
        if (shadowingObject == -1) {
            diffuse = (toLight) * (normal);
            if (diffuse < 0)
                diffuse = 0;
            half = Vec3(toLight + toEye);
            half.normalize();
            specular = half * normal;
            if (specular < 0)
                specular = 0;
            Pixel.setR(scene[closetObject]->getColor().getR() * light.getIntensity().getR() * diffuse +
                       pow(specular, PHONG_EXPONENT) * light.getIntensity().getR()
                       + Pixel.getR());
            Pixel.setG(scene[closetObject]->getColor().getG() * light.getIntensity().getG() * diffuse +
                       pow(specular, PHONG_EXPONENT) * light.getIntensity().getG()
                       + Pixel.getG());
            Pixel.setB(scene[closetObject]->getColor().getB() * light.getIntensity().getB() * diffuse +
                       pow(specular, PHONG_EXPONENT) * light.getIntensity().getB()
                       + Pixel.getB());
        }
        if(depth < MAX_DEPTH)
        {
            Ray mirror(point, (normal%(normal*toEye))%2 - toEye);
            Color mirrorPixel;
            if(getPixelColor(mirrorPixel,scene,light,mirror,EPSILON,depth+1))
            {
                Pixel.setR(Pixel.getR() + scene[closetObject]->getReflectance() * mirrorPixel.getR());
                Pixel.setG(Pixel.getG() + scene[closetObject]->getReflectance() * mirrorPixel.getG());
                Pixel.setB(Pixel.getB() + scene[closetObject]->getReflectance() * mirrorPixel.getB());
            }
        }
        return true;
    }
    else
        return false;
}

int traceRay(Ray ray, vector<GeometricObject*>& scene, double &tmin, double t_least)
{
    tmin = 40000;
    int closetObject = -1;
    double t;
    for(int k=0; k<scene.size(); k++)
    {
        if(scene[k]->hitMe(t,ray,t_least) && t<tmin)
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
    imageFile.open(outFileName.c_str());
    if(!imageFile.is_open())
    {
        cout << "Cannot open file for writing" << endl;
        exit(6);
    }
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
    cout << outFileName << " was written successfully" << endl;
    imageFile.close();
}