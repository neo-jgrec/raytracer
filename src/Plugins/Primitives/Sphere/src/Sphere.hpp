/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../../APrimitive.hpp"

namespace rt
{
    class Sphere final : public APrimitive {
    private:
        math::Vector3<float> _origin = math::Vector3<float>{0, 0, -1};
        float _radius = 0.5;

    public:
        class SphereException final : public Exception {
            SphereException(const std::string &message):
                Exception("Sphere", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;

        void setOrigin(const math::Vector3<float> &origin);
        void setRadius(float radius);
    };
} // namespace rt

#endif //SPHERE_HPP
