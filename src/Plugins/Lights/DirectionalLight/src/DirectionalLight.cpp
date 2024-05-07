/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"

#include <iostream>

namespace rt
{
    utils::Color DirectionalLight::lightAtPoint(const math::Vector3<float> &point) const
    {
        const auto lightDir = _direction.normalize() * -1;
        const float lightPower = std::max(0.f, point.dot(lightDir)) * _intensity;
        return _color * lightPower;
    }

    utils::Color DirectionalLight::illuminate(const math::Vector3<float> &point,
                                              const std::list<IPrimitive *> &primitives,
                                              const IPrimitive *closestPrimitive) const
    {
        const math::Ray shadowRay{point, (_origin - point).normalize()};
        const float max = point.distance(_origin);
        bool visible = true;

        for (const auto &primitive : primitives) {
            if (primitive == closestPrimitive)
                continue;

            if (const auto t = primitive->hit(shadowRay); t > 0 && t < max) {
                visible = false;
                break;
            }
        }

        return visible ? lightAtPoint(closestPrimitive->getNormal(point)) : utils::Color{0, 0, 0};
    }
} // namespace rt
