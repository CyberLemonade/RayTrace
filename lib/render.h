#ifndef RENDER_H
#define RENDER_H

#include "scn/scene.h"
#include "cam/camera.h"
#include "utils.h"

#include <Eigen/Dense>

const int BOUNCES = 3;

void render_image(Scene& scene, Camera* camera, const int W, const int H, const std::string filename) {
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(W, H);
    Eigen::MatrixXd G = Eigen::MatrixXd::Zero(W, H);
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(W, H);
    Eigen::MatrixXd A = Eigen::MatrixXd::Ones(W, H);

    for (int x = 0; x < W; x++) {
        for (int y = 0; y < H; y++) {
            std::pair<Eigen::Vector3d, Eigen::Vector3d> ray = camera->ray(x, y, W, H);
            Eigen::Vector3d colour = scene.ray_colour(ray.first, ray.second, 0.0, INF, BOUNCES);

            R(x, y) = colour(0);
            G(x, y) = colour(1);
            B(x, y) = colour(2);
        }
    }

    write_matrix_to_png(R, G, B, A, filename);
}

#endif