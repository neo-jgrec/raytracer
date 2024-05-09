/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Triangle
*/

#include "Triangle.hpp"

namespace rt
{
    float Triangle::hit(const math::Ray &ray) const
    {
        constexpr float epsilon = std::numeric_limits<float>::epsilon();

        const math::Vector3<float> edge1 = _v1 - _v0;
        const math::Vector3<float> edge2 = _v2 - _v0;
        const math::Vector3<float> cross_edge2 = ray.direction.cross(edge2);
        const float det = edge1.dot(cross_edge2);

        // Ray is parallel to the triangle
        if (det > -epsilon && det < epsilon)
            return -1;

        // Ray intersects the rectangle containing the triangle
        const float invDet = 1.0f / det;
        const math::Vector3<float> tvec = ray.origin - _v0;
        const float u = tvec.dot(cross_edge2) * invDet;

        if (u < 0 || u > 1)
            return -1;

        // Ray intersects the triangle
        const math::Vector3<float> cross_edge1 = tvec.cross(edge1);
        const float v = ray.direction.dot(cross_edge1) * invDet;

        if (v < 0 || u + v > 1)
            return -1;

        const float t = ray.direction.dot(cross_edge1) * invDet;
        return t > epsilon ? t : -1;
    }

    math::Vector3<float> Triangle::getNormal(const math::Vector3<float> &point) const
    {
        const math::Vector3<float> normal = (_v1 - _v0).cross(_v2 - _v0);
        return normal.normalize();
    }

    void Triangle::setTranslation(const math::Vector3<float> &translation)
    {
        _v0 += translation;
        _v1 += translation;
        _v2 += translation;
    }
} // namespace rt
