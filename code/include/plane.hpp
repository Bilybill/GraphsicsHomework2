#ifndef PLANE_H
#define PLANE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement Plane representing an infinite plane
// choose your representation , add more fields and fill in the functions

class Plane : public Object3D {
public:
    Plane():Object3D(nullptr),normal((0,0,0)),d(0) {

    }

    Plane(const Vector3f &normal, float d, Material *m) : Object3D(m) ,normal(normal),d(d){

    }

    ~Plane() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
		Vector3f R0 = r.getOrigin();
		Vector3f Rd = r.getDirection();
		float division = Vector3f::dot(normal,Rd);
		float t = -(-d + Vector3f::dot(normal, R0)) / division;
		if (t < 0)
		{
			return false;
		}
		else if (t > h.getT()|| t < tmin)
		{
			return false;
		}
		h.set(t,material,normal);
        return true;
    }

protected:
	Vector3f normal;
	float d;

};

#endif //PLANE_H


