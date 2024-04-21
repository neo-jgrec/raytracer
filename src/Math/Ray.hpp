/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ray
*/

#ifndef RAY_HPP
#define RAY_HPP

#include "../Math/Vector3.hpp"

namespace math
{
    class Ray {
    public:
        Vector3<float> origin;
        Vector3<float> direction;

        Ray(const Vector3<float> origin = {0, 0, 0}, const Vector3<float> direction = {0, 0, 0})
            : origin{origin}, direction{direction} {}

        Vector3<float> at(float t) const
        {
            return origin + direction * t;
        }
    };
} // rt

#endif //RAY_HPP
