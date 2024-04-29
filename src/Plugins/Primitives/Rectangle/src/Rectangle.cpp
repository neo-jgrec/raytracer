/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

namespace rt
{
    float Rectangle::hit(const math::Ray &ray) const
    {
        constexpr float epsilon = std::numeric_limits<float>::epsilon();

        const math::Vector3<float> edge1 = _v1 - _v0;
        const math::Vector3<float> edge2 = _v2 - _v0;
        const math::Vector3<float> cross_edge2 = ray.direction.cross(edge2);
        const float det = edge1.dot(cross_edge2);

        // Ray is parallel to the rectangle
        if (det > -epsilon && det < epsilon)
            return -1;

        // Ray intersects the rectangle
        const float invDet = 1.0f / det;
        const math::Vector3<float> tvec = ray.origin - _v0;
        const float t = tvec.dot(cross_edge2) * invDet;
        return t > epsilon ? t : -1;
    }
} // namespace rt
