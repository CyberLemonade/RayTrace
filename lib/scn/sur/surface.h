#ifndef SURFACE_H
#define SURFACE_H

#include "scn/hitrecord.h"

#include <Eigen/Dense>

class Surface {
    public:
        virtual double hit(const Eigen::Vector3d& ray_origin, const Eigen::Vector3d& ray_direction, double t_0, double t_1) = 0; // returns time at which ray hits the surface, -1 if invalid
        virtual Eigen::Vector3d normal(const Eigen::Vector3d& ray_intersection) = 0; // returns unit normal to point of incidence
};

#endif