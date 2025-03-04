#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "scene_parser.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "group.hpp"
#include "light.hpp"

#include <string>

using namespace std;

int main(int argc, char *argv[]) {


    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3) {
        cout << "Usage: ./bin/PA1 <input scene file> <output bmp file>" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2];  // only bmp is allowed.

   // string inputFile = "../testcases/scene01_basic.txt";

    // TODO: Main RayCasting Logic
    // First, parse the scene using SceneParser.
    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.
    Vector3f bgc(0,0,0);
	SceneParser sceneParser(inputFile.c_str());
	Camera *camera = sceneParser.getCamera();
	Image outputImage(camera->getWidth(),camera->getHeight());
	for(int x = 0;x < camera->getWidth( );++x)
    {
	    for(int y = 0;y < camera->getHeight();++y)
        {
	        //Compute ray from point(x,y)
	        if(x == 44 && y == 90)
            {
	            cout<<"here"<<endl;
            }
            Vector2f point(x,y);
	        Ray camRay = camera->generateRay(point);
            Group *baseGroup;
            baseGroup = sceneParser.getGroup();
	        Hit hit;
	        //determine whether the ray intersects with group or not
	        bool isInerSect = baseGroup->intersect(camRay,hit,0);
	        if(isInerSect)
            {
	            Vector3f finalColor = Vector3f::ZERO;
	            //find intersect point,compute fill color
	            for(int li = 0; li < sceneParser.getNumLights(); ++li)
                {
	                Light *light = sceneParser.getLight(li);
	                Vector3f L,light_color;
	                //get illumination
	                light->getIllumination(camRay.pointAtParameter(hit.getT()),L,light_color);
	                //compute and pay attention to numeric overflow
	                finalColor += hit.getMaterial()->Shade(camRay,hit,L,light_color);
                }
	            outputImage.SetPixel(x,y,finalColor);
            }
	        else
            {
	            outputImage.SetPixel(x,y,sceneParser.getBackgroundColor());
            }
        }
    }
	//outputImage.SaveImage("result1.bmp");
	outputImage.SaveImage(outputFile.data());
    cout << "Hello! Computer Graphics!" << endl;
    return 0;
}

