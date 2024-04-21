/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FlatColor
*/

#ifndef FLATCOLOR_HPP
#define FLATCOLOR_HPP

#include "../IMaterial.hpp"

namespace rt
{
    class FlatColor : public IMaterial {
    private:
        utils::Color _color{0, 0, 0};

    public:
        [[nodiscard]] utils::Color getColor(const math::Vector3<float> &point) const override;

        void setColor(const utils::Color &color);
    };
} // rt

#endif //FLATCOLOR_HPP
