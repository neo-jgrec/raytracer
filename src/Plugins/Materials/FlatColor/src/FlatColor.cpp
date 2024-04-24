/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FlatColor
*/

#include "FlatColor.hpp"

namespace rt
{
    utils::Color FlatColor::getColor([[maybe_unused]] const math::Vector3<float> &point) const
    {
        return _color;
    }

    utils::Color FlatColor::getColor() const
    {
        return _color;
    }
    void FlatColor::setColor(const utils::Color &color)
    {
        _color = color;
    }
} // rt
