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
        // Convert Euler angles to rotation matrix
        math::Matrix3 rotationMatrix = math::Matrix3::eulerToMatrix(_rotation * M_PI / 180);

        // Rotate the ray
        math::Ray rotatedRay;
        rotatedRay.origin = rotationMatrix * (ray.origin - _origin);
        rotatedRay.direction = rotationMatrix * ray.direction;

        math::Vector3 oc = rotatedRay.origin;
        float a = rotatedRay.direction.dot(rotatedRay.direction) - pow(rotatedRay.direction.dot(_direction.normalize()), 2);
        float b = 2.0 * (rotatedRay.direction.dot(oc) - (rotatedRay.direction.dot(_direction.normalize()) * oc.dot(_direction.normalize())));
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
        if (_height >= 0) {
            math::Vector3 pt = rotatedRay.origin + rotatedRay.direction * t;
            if (pt.dot(_direction.normalize()) < 0 || pt.dot(_direction.normalize()) > _height)
                t = t1;

            pt = rotatedRay.origin + rotatedRay.direction * t;
            if (pt.dot(_direction.normalize()) < 0 || pt.dot(_direction.normalize()) > _height)
                return -1;
        }

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
