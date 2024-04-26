/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"

namespace rt
{
    float Plane::hit(const math::Ray &ray) const
    {
        constexpr auto epsilon = std::numeric_limits<float>::epsilon();
        const auto normal = _direction.normalize();

        if (const float denom = normal.dot(ray.direction); std::abs(denom) > epsilon)
            if (const float t = (_origin - ray.origin).dot(normal) / denom; t >= 0)
                return t;
        return -1;
    }
} // namespace rt
