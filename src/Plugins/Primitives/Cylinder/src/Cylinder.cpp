/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

#include <cmath>

namespace rt
{
    float Cylinder::hit(const math::Ray &ray) const
    {
        const math::Vector3 oc = ray.origin - _vertices[0];
        const float a = static_cast<float>(ray.direction.dot(ray.direction) -
                                           pow(ray.direction.dot(_directions[0].normalize()), 2));
        const float b = 2.0f *
            (ray.direction.dot(oc) -
             (ray.direction.dot(_directions[0].normalize()) * oc.dot(_directions[0].normalize())));
        const float c = static_cast<float>(oc.dot(oc) - pow(oc.dot(_directions[0].normalize()), 2) - _radius * _radius);

        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return -1;

        discriminant = std::sqrt(discriminant);
        auto t0 = static_cast<float>((-b - discriminant) / (2.0 * a));
        auto t1 = static_cast<float>((-b + discriminant) / (2.0 * a));

        if (t0 > t1)
            std::swap(t0, t1);

        float t = t0;
        math::Vector3 pt = ray.origin + ray.direction * t;
        if (pt.dot(_directions[0].normalize()) < 0 || pt.dot(_directions[0].normalize()) > _height)
            t = t1;

        pt = ray.origin + ray.direction * t;
        if (pt.dot(_directions[0].normalize()) < 0 || pt.dot(_directions[0].normalize()) > _height)
            return -1;

        return t;
    }

    math::Vector3<float> Cylinder::getNormal(const math::Vector3<float> &point) const
    {
        math::Vector3<float> normal = point - _vertices[0];
        normal = normal - _directions[0].normalize() * normal.dot(_directions[0].normalize());
        normal = normal.normalize();
        return normal;
    }
} // namespace rt
