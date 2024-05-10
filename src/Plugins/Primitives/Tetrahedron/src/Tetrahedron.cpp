/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Tetrahedron
*/

#include "Tetrahedron.hpp"

#include <vector>

namespace rt
{
    float Tetrahedron::hit(const math::Ray &ray) const
    {
        constexpr float epsilon = std::numeric_limits<float>::epsilon();
        const std::vector<std::tuple<math::Vector3<float>, math::Vector3<float>, math::Vector3<float>>> edges = {
            {_vertices[0], _vertices[1], _vertices[2]},
            {_vertices[0], _vertices[1], _vertices[3]},
            {_vertices[0], _vertices[2], _vertices[3]},
            {_vertices[1], _vertices[2], _vertices[3]}};
        float t_min = -1;

        for (uint8_t i = 0; i < 4; i++) {
            const math::Vector3<float> edge1 = std::get<1>(edges[i]) - std::get<0>(edges[i]);
            const math::Vector3<float> edge2 = std::get<2>(edges[i]) - std::get<0>(edges[i]);
            const math::Vector3<float> cross_edge2 = ray.direction.cross(edge2);
            const float det = edge1.dot(cross_edge2);

            // Ray is parallel to the triangle
            if (det > -epsilon && det < epsilon)
                continue;

            // Ray intersects the rectangle containing the triangle
            const float invDet = 1.0f / det;
            const math::Vector3<float> tvec = ray.origin - std::get<0>(edges[i]);
            const float u = tvec.dot(cross_edge2) * invDet;

            if (u < 0 || u > 1)
                continue;

            // Ray intersects the triangle
            const math::Vector3<float> cross_edge1 = tvec.cross(edge1);
            const float v = ray.direction.dot(cross_edge1) * invDet;

            if (v < 0 || u + v > 1)
                continue;

            if (const float t = ray.direction.dot(cross_edge1) * invDet; t > epsilon && t > t_min)
                t_min = t;
        }
        return t_min;
    }

    math::Vector3<float> Tetrahedron::getNormal(const math::Vector3<float> &point) const
    {
        const std::vector<std::tuple<math::Vector3<float>, math::Vector3<float>, math::Vector3<float>>> edges = {
            {_vertices[0], _vertices[1], _vertices[2]},
            {_vertices[0], _vertices[1], _vertices[3]},
            {_vertices[0], _vertices[2], _vertices[3]},
            {_vertices[1], _vertices[2], _vertices[3]}};
        math::Vector3<float> normal;

        for (uint8_t i = 0; i < 4; i++) {
            const math::Vector3<float> edge1 = std::get<1>(edges[i]) - std::get<0>(edges[i]);
            const math::Vector3<float> edge2 = std::get<2>(edges[i]) - std::get<0>(edges[i]);
            normal = edge1.cross(edge2).normalize();
            if (normal.dot(point - std::get<0>(edges[i])) > 0)
                return normal;
        }
        return normal;
    }
} // namespace rt
