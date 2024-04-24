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
    // TODO: handle multiple lights
    void DirectionalLight::illuminate(const math::Vector3<float> &point, utils::Color &color) const
    {
        const auto lightDirection = (_origin - point + _direction).normalize();
        const float d = point.dot({-lightDirection.x, -lightDirection.y, -lightDirection.z});
        const auto max = std::max(d * 2.0f, 0.f);

        color *= max * _intensity;
        color.clamp();
    }
} // namespace rt
