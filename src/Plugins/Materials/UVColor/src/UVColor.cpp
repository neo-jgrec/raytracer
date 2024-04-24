/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** UVColor
*/

#include "UVColor.hpp"

namespace rt
{
    utils::Color UVColor::getColor(const math::Vector3<float> &point) const
    {
        const auto N = (point - math::Vector3<float>{0, 0, -1}).normalize();
        return utils::Color{
            255.9999f * (N.x + 1),
            255.9999f * (N.y + 1),
            255.9999f * (N.z + 1)
        } * 0.5f;
    }
} // namespace rt
