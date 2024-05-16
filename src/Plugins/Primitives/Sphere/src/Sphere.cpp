/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include <iostream>

namespace rt
{
    float Sphere::hit(const math::Ray &ray) const
    {
        const math::Vector3<float> oc = ray.origin - _vertices[0];
        const auto a = ray.direction.dot(ray.direction);
        const auto b = 2.0f * oc.dot(ray.direction);
        const auto c = oc.dot(oc) - _radius * _radius;

        const auto descriminant = b * b - 4 * a * c;
        if (descriminant < 0)
            return -1.0f;
        if (const auto t1 = (-b - std::sqrt(descriminant)) / (2 * a); t1 > 0)
            return t1;
        return (-b + std::sqrt(descriminant)) / (2 * a);
    }

    math::Vector3<float> Sphere::getNormal(const math::Vector3<float> &point) const
    {
        return (point - _vertices[0]).normalize();
    }
} // namespace rt
