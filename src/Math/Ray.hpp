/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ray
*/

#ifndef RAY_HPP
#define RAY_HPP

#include "../Math/Vector3.hpp"

namespace math
{
    class Ray final {
    public:
        Vector3<float> origin;
        Vector3<float> direction;

        Ray(const Vector3<float> origin = {0, 0, 0}, const Vector3<float> direction = {0, 0, 0}) :
            origin{origin}, direction{direction}
        {}

        [[nodiscard]] Vector3<float> at(const float t) const { return origin + direction * t; }

        friend std::ostream &operator<<(std::ostream &os, const Ray &ray)
        {
            os << "Ray{origin: " << ray.origin << ", direction: " << ray.direction << "}";
            return os;
        }
    };
} // namespace math

#endif // RAY_HPP
