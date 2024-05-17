/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AmbientLight
*/

#include "AmbientLight.hpp"

namespace rt
{
    utils::Color AmbientLight::illuminate([[maybe_unused]] const math::Vector3<float> &point,
                                          [[maybe_unused]] const std::list<IPrimitive *> &primitives,
                                          [[maybe_unused]] const IPrimitive *closestPrimitive) const
    {
        return _color * getIntensity();
    }
} // namespace rt
