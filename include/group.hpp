#ifndef GROUP_H
#define GROUP_H


#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <vector>


// TODO: Implement Group - add data structure to store a list of Object*
class Group : public Object3D {

public:

    Group() {

    }

    explicit Group (int num_objects):num_objs(num_objects){
    }

    ~Group() override {

    }

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        bool res = false;
        for(int i = 0;i<objs.size();i++)
        {
            res |= objs[i]->intersect(r,h,tmin);
        }
		return res;
    }

    void addObject(int index, Object3D *obj) {
		std::vector<Object3D*>::iterator it;
		it = objs.begin();
		objs.insert(it + index, obj);

		//objs.push_back(obj);
    }

    int getGroupSize() {
		return objs.size();
    }

private:
	std::vector<Object3D*> objs;
    int num_objs;
};

#endif
	
