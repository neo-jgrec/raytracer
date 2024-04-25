/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace rt
{
    float Sphere::hit(const math::Ray &ray) const
    {
        const math::Vector3<float> oc = ray.origin - _origin;
        const auto a = ray.direction.dot(ray.direction);
        const auto b = 2.0f * oc.dot(ray.direction);
        const auto c = oc.dot(oc) - _radius * _radius;

        const auto descriminant = b * b - 4 * a * c;
        return descriminant < 0 ? -1 : (-b - std::sqrt(descriminant)) / (2 * a);
    }
} // namespace rt
