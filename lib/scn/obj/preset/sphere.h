#ifndef SPHERE_H
#define SPHERE_H

#include "scn/sur/surface.h"
#include "scn/obj/object.h"

#include <Eigen/Dense>

class Sphere : public Object {
    public:
        Sphere(Eigen::Vector3d origin, double radius) {
            Surface* surf = new SphereSurface(origin, radius);
            this->add_surface(surf);
        }

        bool Object::hit(const Eigen::Vector3d& ray_origin, const Eigen::Vector3d& ray_direction, double t_0, double t_1, HitRecord& rec) {
            double t = this->surfaces[0]->hit(ray_origin, ray_direction, t_0, t_1);
            
            if (t >= 0) {
                Eigen::Vector3d ray_intersection = ray_origin + t * ray_direction;
                rec.set_distance(t);
                rec.set_colour(this->colour);
                rec.set_material(this->material);
                rec.set_normal(this->surfaces[0]->normal(ray_intersection));
            }

            return t >= 0;
        }

        class SphereSurface : public Surface {
            public:
                Eigen::Vector3d origin;
                double radius;

                SphereSurface() {
                    this->origin = Eigen::Vector3d();
                    this->radius = 0.0;
                }

                SphereSurface(Eigen::Vector3d& origin, double radius) {
                    this->origin = origin;
                    this->radius = radius;
                }

                double Surface::hit(const Eigen::Vector3d& ray_origin, const Eigen::Vector3d& ray_direction, double t_0, double t_1) {
                    Eigen::Vector3d ray_to_origin = ray_origin - this->origin;
                    double discriminant = pow(ray_direction.dot(ray_to_origin), 2) - ray_direction.dot(ray_direction) * ( ray_to_origin.dot(ray_to_origin) - this->radius*this->radius );

                    if (discriminant >= 0) {
                        double t1 = (- ray_direction.dot(ray_to_origin) - sqrt(discriminant)) / (ray_direction.dot(ray_direction));
                        if (t1 >= t_0 && t1 <= t_1) { return t1; }
                        double t2 = (- ray_direction.dot(ray_to_origin) + sqrt(discriminant)) / (ray_direction.dot(ray_direction));
                        if (t2 >= t_0 && t2 <= t_1) { return t2; }
                    }

                    return -1;
                }

                Eigen::Vector3d Surface::normal(const Eigen::Vector3d& ray_intersection) {
                    return (ray_intersection - this->origin) / this->radius;
                }
        };
};

#endif