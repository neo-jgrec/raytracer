/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FlatColor
*/

#include "FlatColor.hpp"

namespace rt
{
    utils::Color FlatColor::getColor([[maybe_unused]] const IPrimitive *currentPrimitive,
                                     [[maybe_unused]] const math::Vector3<float> &point) const
    {
        return _color;
    }
} // namespace rt
