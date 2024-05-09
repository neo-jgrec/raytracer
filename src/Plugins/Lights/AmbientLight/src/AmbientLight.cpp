/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AmbientLight
*/

#include "AmbientLight.hpp"

namespace rt
{
    utils::Color AmbientLight::illuminate(const math::Vector3<float> &point,
                                          [[maybe_unused]] const std::list<IPrimitive *> &primitives,
                                          [[maybe_unused]] const IPrimitive *closestPrimitive) const
    {
        return _color * _intensity;
    }

    const math::Vector3<float> &AmbientLight::getOrigin() const
    {
        static math::Vector3<float> origin;
        return origin;
    }
} // namespace rt
