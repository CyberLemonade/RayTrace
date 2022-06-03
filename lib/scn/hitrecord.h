#ifndef HITRECORD_H
#define HITRECORD_H

#include "scn/mat/material.h"

#include <Eigen/Dense>

struct HitRecord {
    public:
        double t;           // hit distance
        Eigen::Vector3d n;  // normal
        Eigen::Vector3d c;  // colour
        Material m;         // material

        HitRecord() {
            this->t = 0.0;
            this->n = Eigen::Vector3d();
            this->c = Eigen::Vector3d();
            this->m = Material();
        }

        HitRecord(double t, const Eigen::Vector3d& n, const Eigen::Vector3d& c, const Material& m) {
            this->t = t;
            this->n = n;
            this->c = c;
            this->m = m;
        }

        inline void set_distance(double t) { this->t = t; }
        inline void set_normal(const Eigen::Vector3d n) { this->n = n; }
        inline void set_colour(const Eigen::Vector3d c) { this->c = c; }
        inline void set_material(const Material& m) { this->m = m; }
};

#endif