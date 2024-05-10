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
        // Convert rotation angles to rotation matrix
        math::Matrix3 rotationMatrix = math::Matrix3::eulerToMatrix(_rotation * M_PI / 180);

        // create a new ray with the origin and direction rotated
        math::Ray rotatedRay;
        rotatedRay.origin = rotationMatrix * (ray.origin - _origin);
        rotatedRay.direction = rotationMatrix * ray.direction;

        // create aliases to make the code more readable
        math::Vector3 rayO = rotatedRay.origin;
        math::Vector3 normDir = _direction.normalize();

        float a = rotatedRay.direction.dot(rotatedRay.direction) - (1 + _radius * _radius) * pow(rotatedRay.direction.dot(normDir), 2);
        float b = 2.0 * (rotatedRay.direction.dot(rayO) - (1 + _radius * _radius) * rotatedRay.direction.dot(normDir) * rayO.dot(normDir));
        float c = rayO.dot(rayO) - (1 + _radius * _radius) * pow(rayO.dot(normDir), 2);

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
            if (pt.dot(normDir) < 0 || pt.dot(normDir) > _height)
                t = t1;

            pt = rotatedRay.origin + rotatedRay.direction * t;
            if (pt.dot(normDir) < 0 || pt.dot(normDir) > _height)
                return -1;
        }

        return t;
    }

    math::Vector3<float> Cone::getNormal(const math::Vector3<float> &point) const
    {
        math::Matrix3 rotationMatrix = math::Matrix3::eulerToMatrix(_rotation);

        math::Vector3 normDir = _direction.normalize();
        math::Vector3<float> normal = point - _origin;
        normal = normal - normDir * normal.dot(normDir);
        normal = rotationMatrix * normal;
        normal = normal.normalize();

        return normal;
    }
} // namespace rt
