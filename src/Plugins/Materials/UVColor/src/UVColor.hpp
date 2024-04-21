/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** UVColor
*/

#ifndef UVCOLOR_HPP
#define UVCOLOR_HPP

#include "../IMaterial.hpp"

namespace rt
{
    class UVColor : public IMaterial {
    public:
        [[nodiscard]] utils::Color getColor(const math::Vector3<float> &point) const override;
    };
} // namespace rt

#endif //UVCOLOR_HPP
