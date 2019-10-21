#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// TODO: implement this class and add more fields as necessary,
class Triangle: public Object3D {

public:
	Triangle() = delete;

    // a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) : Object3D(m) {

		vertices[0] = a;
		vertices[1] = b;
		vertices[2] = c;

		Vector3f l1 = b - a;
		Vector3f l2 = c - a;
		normal = Vector3f::cross(l1, l2);
		d = -Vector3f::dot(normal, a);
	}

	bool intersect( const Ray& ray,  Hit& hit , float tmin) override {
		Vector3f R0 = ray.getOrigin();
		Vector3f Rd = ray.getDirection();
		Matrix3f paraMatrix(Rd,vertices[0] - vertices[1],vertices[0] - vertices[2]);
		Vector3f paraAnswer = paraMatrix.inverse() * (vertices[0] - R0);
		float t = paraAnswer[0];
		if(t < 0 || t > hit.getT() || t < tmin)
        {
		    return false;
        }
		else if(paraAnswer[1] >= 0 && paraAnswer[1] <= 1 && paraAnswer[2] >= 0 && paraAnswer[2] <= 1 && paraAnswer[1] + paraAnswer[2] <=1)
        {
            hit.set(t, material, normal);
            return true;
        }
		return false;
		/*
		float t = -(d + Vector3f::dot(normal, R0)) / Vector3f::dot(normal, Rd);
		if (t < 0)
		{
			return false;
		}
		else if (t > hit.getT() || t < tmin)
		{
			return false;
		}
		Vector3f intersection = R0 + t * Rd;
		if (!inside(intersection))
		{
			return false;
		}
		hit.set(t, material, normal);
		return true;
		 */
	}
	Vector3f normal;
	Vector3f vertices[3];
protected:
	float d;
	bool inside(Vector3f point)
	{
		Vector3f V0 = vertices[2] - vertices[0];
		Vector3f V1 = vertices[1] - vertices[0];
		Vector3f V2 = point - vertices[0];

		float dot00 = Vector3f::dot(V0, V0);
		float dot01 = Vector3f::dot(V0, V1);
		float dot02 = Vector3f::dot(V0, V2);
		float dot11 = Vector3f::dot(V1, V1);
		float dot12 = Vector3f::dot(V1, V2);

		float division = 1 / dot00 * dot11 - dot01 * dot01;

		float beta = (dot11 * dot02 - dot01 * dot12) * division;
		if (beta < 0 || beta>1)
		{
			return false;
		}
		float gamma = (dot00 * dot12 - dot02 * dot01) * division;
		if (gamma < 0 || gamma>1)
		{
			return false;
		}
		/*
		if(beta + gamma <= 1)
        {
		    cout<<"inside triangle"<<std::endl;
        }
        */
		return (beta + gamma) <= 1;
	}
};

#endif //TRIANGLE_H
