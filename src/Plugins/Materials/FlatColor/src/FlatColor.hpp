/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FlatColor
*/

#ifndef FLATCOLOR_HPP
#define FLATCOLOR_HPP

#include <iostream>

#include <libconfig.h++>
#include "../IMaterial.hpp"

namespace rt
{
    class FlatColor : public IMaterial {
    private:
        utils::Color _color;

    public:
        class FlatColorException final : public IMaterialException {
        public:
            FlatColorException(const std::string &message) : IMaterialException("FlatColor", message) {}
        };

        [[nodiscard]] utils::Color getColor(const math::Vector3<float> &point) const override;

        [[nodiscard]] utils::Color getColor() const;
        void setColor(const utils::Color &color);
    };
} // namespace rt

extern "C" {
    rt::FlatColor *createComponent([[maybe_unused]] libconfig::Setting &material)
    {
        auto *newUVColor = new rt::FlatColor();
        newUVColor->setColor(utils::Color{static_cast<float>(material["color"]["r"].operator int()) / 255,
                                          static_cast<float>(material["color"]["g"].operator int()) / 255,
                                          static_cast<float>(material["color"]["b"].operator int()) / 255});

        return newUVColor;
    }

    void destroy(const rt::FlatColor *ptr) { delete ptr; }
}


#endif // FLATCOLOR_HPP
