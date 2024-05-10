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
        const auto normal = _directions[0].normalize();

        if (const float denom = normal.dot(ray.direction); std::abs(denom) > epsilon)
            if (const float t = (_vertices[0] - ray.origin).dot(normal) / denom; t >= 0)
                return t;
        return -1;
    }

    math::Vector3<float> Plane::getNormal([[maybe_unused]] const math::Vector3<float> &point) const
    {
        return _directions[0].normalize();
    }
} // namespace rt
