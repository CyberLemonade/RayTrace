#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "cam/camera.h"

#include <Eigen/Dense>

class PerspectiveCamera : public Camera {
    public:
        double d;

        void set_distance(const double d) { this->d = d; }

        std::pair<Eigen::Vector3d, Eigen::Vector3d> Camera::ray(const int x, const int y, const int width, const int height) {
            Eigen::Vector3d ray_origin = this->e - this->d * this->w + this->pixel_delta(x, y, width, height);
            Eigen::Vector3d ray_direction = ray_origin - this->e;
            return { ray_origin, ray_direction };
        }
};

#endif