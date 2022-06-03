#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
    public:
        double k_a; // ambient  coefficient
        double k_d; // diffuse  coefficient
        double k_s; // specular coefficient
        double k_m; // mirror   coefficient
        double p;   // Phong exponent

        Material() {
            this->k_a = 0.0;
            this->k_d = 0.0;
            this->k_s = 0.0;
            this->k_m = 0.0;
            this->p   = 0.0;
        }

        Material(const double k_a, const double k_d, const double k_s, const double k_m, const double p) {
            this->k_a = k_a;
            this->k_d = k_d;
            this->k_s = k_s;
            this->k_m = k_m;
            this->p   = p;
        }

        inline void set_ambient (const double k_a) { this->k_a = k_a; }
        inline void set_diffuse (const double k_d) { this->k_d = k_d; }
        inline void set_specular(const double k_s) { this->k_s = k_s; }
        inline void set_mirror  (const double k_m) { this->k_m = k_m; }
        inline void set_phong   (const double p)   { this->p   = p; }
};

#endif