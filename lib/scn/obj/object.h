#ifndef OBJECT_H
#define OBJECT_H

#include "scn/mat/material.h"
#include "scn/sur/surface.h"

#include <vector>
#include <Eigen/Dense>

class Object {
    public:
        Material material;      // material
        Eigen::Vector3d colour; // colour

        std::vector<Surface*> surfaces; // surfaces in the object

        virtual bool hit(const Eigen::Vector3d& ray_origin, const Eigen::Vector3d& ray_direction, double t_0, double t_1, HitRecord& rec) = 0; // returns true if the ray hits object within t_0 and t_1, and updates HitRecord accordingly

        inline void set_colour(const Eigen::Vector3d& colour) { this->colour = colour; }
        inline void set_material(const Material& material) { this->material = material; }
        inline void add_surface(Surface* surface) { this->surfaces.push_back(surface); }
};

#endif