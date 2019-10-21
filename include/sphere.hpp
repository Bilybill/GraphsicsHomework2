#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement functions and add more fields as necessary

class Sphere : public Object3D {
public:
    Sphere():center(Vector3f(0,0,0)),radius(1),Object3D(nullptr){
        // unit ball at the center
    }

    Sphere(const Vector3f &center, float radius, Material *material) : Object3D(material),center(center),radius(radius) {

    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        //
		Vector3f l = center - r.getOrigin();
		float tp = Vector3f::dot(l,r.getDirection());
		if (tp < 0)
		{
			return false;
		}
		float d_square = l.squaredLength() - tp * tp;
		if (d_square >= radius * radius)
		{
			return false;
		}
		float tpie = sqrt(radius * radius - d_square);
		float t = 0;
		//if light origin is outside of sphere
		if (l.squaredLength() > radius* radius)
		{
			t = tp - tpie;
		}
		else 
		{
			t = tp + tpie;
		}
		if (t > h.getT())
		{
			return false;
		}
		else if (t < tmin)
		{
			return false;
		}
		Vector3f intersectPoint = r.getOrigin() + t * r.getDirection();
		Vector3f normal = (intersectPoint - center).normalized();
		h.set(t,material,normal);
        return true;
    }

protected:
	Vector3f center;
	float radius;
};


#endif
