#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera {
public:
    Camera(const Vector3f &center, const Vector3f &direction, const Vector3f &up, int imgW, int imgH) {
        this->center = center;
        this->direction = direction.normalized();
        this->horizontal = Vector3f::cross(this->direction, up);
        this->up = Vector3f::cross(this->horizontal, this->direction);
        this->width = imgW;
        this->height = imgH;
    }

    // Generate rays for each screen-space coordinate
    virtual Ray generateRay(const Vector2f &point) = 0;
    virtual ~Camera() = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

protected:
    // Extrinsic parameters
    Vector3f center;
    Vector3f direction;
    Vector3f up;
    Vector3f horizontal;
    // Intrinsic parameters
    int width;
    int height;
};

// TODO: Implement Perspective camera
// You can add new functions or variables whenever needed.
class PerspectiveCamera : public Camera {

public:
    PerspectiveCamera(const Vector3f &center, const Vector3f &direction,
            const Vector3f &up, int imgW, int imgH, float angle) : Camera(center, direction, up, imgW, imgH) {
        // angle is in radian.
		RotateMatrix = Matrix3f(horizontal,-up,direction);
		//get intrinsic parameter
        //float fovyd = angle / 3.1415 * 180.0;
        fx = fy = (float) height / (2 * tanf(angle/2));
        cx = width / 2.0f;
        cy = height / 2.0f;
    }

    Ray generateRay(const Vector2f &point) override {
		assert(point.x() >= 0 && point.x() < width);
		assert(point.y() >= 0 && point.y() < height);
		Vector3f dRc((point.x() - cx) / fx, -(point.y() - cy) / fy, 1);
		//dRc.normalize();
		Vector3f dRw = RotateMatrix * dRc;
		dRw.normalize();
		return Ray(center,dRw);
    }
	Matrix3f RotateMatrix;
    float fx;
    float fy;
    float cx;
    float cy;
};

#endif //CAMERA_H
