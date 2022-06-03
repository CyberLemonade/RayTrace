#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "cam/camera.h"

#include <Eigen/Dense>

class OrthographiCamera : public Camera {
    public:
        std::pair<Eigen::Vector3d, Eigen::Vector3d> Camera::ray(const int x, const int y, const int width, const int height) {
            Eigen::Vector3d ray_origin = this->e + this->pixel_delta(x, y, width, height);
            Eigen::Vector3d ray_direction = -w;
            return { ray_origin, ray_direction };
        }
};

#endif