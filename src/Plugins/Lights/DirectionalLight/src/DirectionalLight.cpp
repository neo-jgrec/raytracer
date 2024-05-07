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
    utils::Color DirectionalLight::illuminate(const math::Vector3<float> &point) const
    {
        const auto lightDir = _direction.normalize() * -1;
        const float lightPower = std::max(0.f, point.dot(lightDir)) * _intensity;
        return _color * lightPower;
    }
} // namespace rt
