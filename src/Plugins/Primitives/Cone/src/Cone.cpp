/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cone
*/

#include "Cone.hpp"
#include <iostream>

namespace rt
{
    float Cone::hit(const math::Ray &ray) const
    {
        math::Vector3 oc = ray.origin - _origin;
        float k = _radius;

        float a = ray.direction.dot(ray.direction) - (1 + k * k) * pow(ray.direction.dot(_direction.normalize()), 2);
        float b = 2.0 * (ray.direction.dot(oc) - (1 + k * k) * ray.direction.dot(_direction.normalize()) * oc.dot(_direction.normalize()));
        float c = oc.dot(oc) - (1 + k * k) * pow(oc.dot(_direction.normalize()), 2);

        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return -1;

        discriminant = sqrt(discriminant);
        float t0 = -b - discriminant;
        float t1 = -b + discriminant;

        if (t0 > t1)
            std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0)
                return -1;
        }

        return t0 / (2.0 * a);
    }

    math::Vector3<float> Cone::getNormal(const math::Vector3<float> &point) const
    {
        math::Vector3<float> normal = point - _origin;
        normal = normal - _direction * normal.dot(_direction);
        normal = normal.normalize();
        return normal;
    }
} // namespace rt
