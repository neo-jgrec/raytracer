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
        math::Vector3 newDirection = _direction.normalize() + _rotation / 360;
        newDirection = newDirection.normalize();

        float a = ray.direction.dot(ray.direction) - (1 + k * k) * pow(ray.direction.dot(newDirection.normalize()), 2);
        float b = 2.0 * (ray.direction.dot(oc) - (1 + k * k) * ray.direction.dot(newDirection.normalize()) * oc.dot(newDirection.normalize()));
        float c = oc.dot(oc) - (1 + k * k) * pow(oc.dot(newDirection.normalize()), 2);

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
        if (pt.dot(newDirection.normalize()) < 0 || pt.dot(newDirection.normalize()) > _height)
            t = t1;

        pt = ray.origin + ray.direction * t;
        if (pt.dot(newDirection.normalize()) < 0 || pt.dot(newDirection.normalize()) > _height)
            return -1;

        return t;
    }

    math::Vector3<float> Cone::getNormal(const math::Vector3<float> &point) const
    {
        math::Vector3 newDirection = _direction.normalize() * 360 + _rotation;
        math::Vector3<float> normal = point - _origin;
        normal = normal - newDirection.normalize() * normal.dot(newDirection.normalize());
        normal = normal.normalize();
        return normal;
    }
} // namespace rt
