#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Dense>

class Camera {
    public:
        Eigen::Vector3d u, v, w;    // orthonormal basis
        Eigen::Vector3d e;          // origin

        double l, r, b, t;          // bounds

        inline void set_basis(const Eigen::Vector3d& u, const Eigen::Vector3d& v, const Eigen::Vector3d& w) { this->u = u; this->v = v; this->w = w; }
        inline void set_origin(const Eigen::Vector3d& e) { this->e = e; }
        inline void set_bounds(const double l, const double r, const double b, const double t) { this->l = l; this->r = r; this->b = b; this->t = t; }

        Eigen::Vector3d pixel_delta(const int x, const int y, const int width, const int height) {  // position on camera plane based on pixel and resolution
            double u = l + (r - l) * (x + 0.5) / width;
            double v = t - (t - b) * (y + 0.5) / height;
            return u * this->u + v * this-> v;
        }

        virtual std::pair<Eigen::Vector3d, Eigen::Vector3d> ray(const int x, const int y, const int width, const int height) = 0;
};

#endif