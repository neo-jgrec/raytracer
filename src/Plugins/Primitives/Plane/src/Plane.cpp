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
        constexpr float epsilon = std::numeric_limits<float>::epsilon();

        const float denom = ray.direction.dot(_direction);
        if (denom <= epsilon)
            return -1;

        const math::Vector3<float> oc = ray.origin - _origin;
        const float t = oc.dot(ray.origin) / denom;
        return t > 0 ? t : -1;
    }
} // namespace rt
