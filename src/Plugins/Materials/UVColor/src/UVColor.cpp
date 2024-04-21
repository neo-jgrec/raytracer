/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** UVColor
*/

#include "UVColor.hpp"

extern "C" {
    utils::LibraryType getType()
    {
        return utils::LibraryType::MATERIAL;
    }

    rt::UVColor *create()
    {
        return new rt::UVColor();
    }

    void destroy(const rt::UVColor *ptr)
    {
        delete ptr;
    }
}

namespace rt
{
    utils::Color UVColor::getColor(const math::Vector3<float> &point) const
    {
        const auto N = (point - math::Vector3<float>{0, 0, -1}).normalize();
        return utils::Color{N.x + 1, N.y + 1, N.z + 1} * 0.5f;
    }
} // namespace rt