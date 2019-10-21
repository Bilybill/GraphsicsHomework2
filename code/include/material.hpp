#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"

#include <iostream>
#include <algorithm>

// TODO: Implement Shade function that computes Phong introduced in class.
class Material {
public:

    explicit Material(const Vector3f &d_color, const Vector3f &s_color = Vector3f::ZERO, float s = 0) :
            diffuseColor(d_color), specularColor(s_color), shininess(s) {

    }

    virtual ~Material() = default;

    virtual Vector3f getDiffuseColor() const {
        return diffuseColor;
    }


    Vector3f Shade(const Ray &ray, const Hit &hit,
                   const Vector3f &dirToLight, const Vector3f &lightColor) {
        Vector3f shaded = Vector3f::ZERO;
        //
        Vector3f N = hit.getNormal();
        Vector3f V = -ray.getDirection();
        Vector3f R = 2 * Vector3f::dot(N,dirToLight)*N-dirToLight;
        R.normalize();
        //Li = dirToLight;
        float kd = Vector3f::dot(dirToLight,N);
        float km = Vector3f::dot(V,R);
        if(km>1)km = 1;
        else if(km<0)km = 0;
        float ks = pow(km,shininess);
        if(kd>1)kd = 1;
        else if(kd<0)kd = 0;
        if(ks>1)ks = 1;
        else if(ks<0)ks = 0;
        shaded = diffuseColor * kd + specularColor * ks;
        /*for(int i = 0;i<3;i++)
        {
            if(shaded[i]<0)shaded[i]=0;
            else if(shaded[i]>1)shaded[i]=1;
        }
         */
        return shaded;
    }

protected:
    Vector3f diffuseColor;//kd
    Vector3f specularColor;//ks
    float shininess;
};


#endif // MATERIAL_H
