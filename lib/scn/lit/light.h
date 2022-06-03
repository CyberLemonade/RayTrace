#ifndef LIGHT_H
#define LIGHT_H

#include <Eigen/Dense>

struct Light {
    public:
        Eigen::Vector3d source; // point source
        double I;               // intensity

        Light() {
            this->source = Eigen::Vector3d();
            this->I = 0.0;
        }

        Light(const Eigen::Vector3d& source, const double I) {
            this->source = source;
            this->I = I;
        }

        inline void set_source(const Eigen::Vector3d& source) { this->source = source; }
        inline void set_intensity(const double I) { this->I = I; }
};

#endif