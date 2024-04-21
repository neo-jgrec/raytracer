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
        utils::Color _color;

    public:
        class FlatColorException final : public IMaterialException {
        public:
            FlatColorException(const std::string &message) :
                IMaterialException("FlatColor", message) {}
        };

        [[nodiscard]] utils::Color getColor(const math::Vector3<float> &point) const override;

        void setColor(const utils::Color &color);
    };
} // rt

#endif //FLATCOLOR_HPP
