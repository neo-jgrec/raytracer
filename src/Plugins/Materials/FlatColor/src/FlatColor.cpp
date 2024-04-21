/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FlatColor
*/

#include "FlatColor.hpp"

extern "C" {
    utils::LibraryType getType()
    {
        return utils::LibraryType::MATERIAL;
    }

    rt::FlatColor *create()
    {
        return new rt::FlatColor();
    }

    void destroy(const rt::FlatColor *ptr)
    {
        delete ptr;
    }
}

namespace rt
{
    utils::Color FlatColor::getColor([[maybe_unused]] const math::Vector3<float> &point) const
    {
        return _color;
    }

    void FlatColor::setColor(const utils::Color &color)
    {
        _color = color;
    }
} // rt
