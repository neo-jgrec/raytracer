/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include <iostream>

namespace rt
{
    float Cylinder::hit(const math::Ray &ray) const
    {
        math::Vector3 oc = ray.origin - _origin;
        float a = ray.direction.dot(ray.direction) - pow(ray.direction.dot(_direction.normalize()), 2);
        float b = 2.0 * (ray.direction.dot(oc) - (ray.direction.dot(_direction.normalize()) * oc.dot(_direction.normalize())));
        float c = oc.dot(oc) - pow(oc.dot(_direction.normalize()), 2) - _radius * _radius;

        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return -1;

        discriminant = sqrt(discriminant);
        float t0 = (-b - discriminant) / (2.0 * a);
        float t1 = (-b + discriminant) / (2.0 * a);

        if (t0 > t1)
            std::swap(t0, t1);

        float t = t0;
        math::Vector3 pt = ray.origin + ray.direction * t;
        if (pt.dot(_direction.normalize()) < 0 || pt.dot(_direction.normalize()) > _height)
            t = t1;

        pt = ray.origin + ray.direction * t;
        if (pt.dot(_direction.normalize()) < 0 || pt.dot(_direction.normalize()) > _height)
            return -1;

        return t;
    }

    math::Vector3<float> Cylinder::getNormal(const math::Vector3<float> &point) const
    {
        math::Vector3<float> normal = point - _origin;
        normal = normal - _direction.normalize() * normal.dot(_direction.normalize());
        normal = normal.normalize();
        return normal;
    }
} // namespace rt
