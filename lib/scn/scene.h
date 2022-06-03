#ifndef SCENE_H
#define SCENE_H

#include "scn/obj/object.h"
#include "scn/lit/light.h"
#include "scn/hitrecord.h"

#include <vector>
#include <Eigen/Dense>

const double EPS = 0.01;
const double INF = 1e18;

class Scene {
public:
    std::vector<Object*> objects;       // objects
    std::vector<Light> lights;          // lights

    Light ambient_light;                // ambient light
    Eigen::Vector3d background_colour;  // background colour

    inline void add_object(Object* object) { this->objects.push_back(object); }
    inline void add_light(Light& light) { this->lights.push_back(light); }

    inline void set_ambient_light(double I) { this->ambient_light.set_intensity(I); }
    inline void set_background_colour(Eigen::Vector3d& colour) { this->background_colour = colour; }

    bool hit(const Eigen::Vector3d& ray_origin, const Eigen::Vector3d& ray_direction, double t_0, double t_1, HitRecord& rec) {     // returns true if the ray hits any object in the scene, and updates HitRecord accordingly
        bool hit = false;

        for (Object* object : this->objects) {
            HitRecord temp_rec;
            if (object->hit(ray_origin, ray_direction, t_0, t_1, temp_rec)) {
                hit = true;
                rec = temp_rec;
                t_1 = rec.t;
            }
        }

        return hit;
    }

    Eigen::Vector3d ray_colour(const Eigen::Vector3d& ray_origin, const Eigen::Vector3d& ray_direction, double t_0, double t_1, int depth) {    // returns colour of the given ray
        if (depth == 0) { return background_colour; }

        HitRecord rec;
        if (this->hit(ray_origin, ray_direction, t_0, t_1, rec)) {
            Eigen::Vector3d ray_intersection = ray_origin + rec.t * ray_direction;
            
            double scalar_light = rec.m.k_a * ambient_light.I;

            for (Light& light : this->lights) {
                Eigen::Vector3d light_direction = (light.source - ray_intersection).normalized();
                HitRecord srec;

                if (!this->hit(ray_intersection, light_direction, EPS, INF, srec)) {
                    Eigen::Vector3d half_vector = (light_direction.normalized() - ray_direction.normalized()).normalized();

                    double specular_lighting = half_vector.dot(rec.n);
                    double diffuse_lighting = light_direction.normalized().dot(rec.n);

                    scalar_light += rec.m.k_d * light.I * std::max(diffuse_lighting, 0.) + rec.m.k_s * light.I * pow(specular_lighting, rec.m.p);
                }
            }

            Eigen::Vector3d reflected_ray = ray_direction - 2 * ray_direction.dot(rec.n) * rec.n;
            return scalar_light * rec.c + rec.m.k_m * ray_colour(ray_intersection, reflected_ray, EPS, INF, depth - 1);
        } else {
            return background_colour;
        }
    }
};

#endif