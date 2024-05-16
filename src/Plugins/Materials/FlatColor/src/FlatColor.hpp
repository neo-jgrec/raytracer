/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** FlatColor
*/

#ifndef FLATCOLOR_HPP
#define FLATCOLOR_HPP

#include <libconfig.h++>
#include "../IMaterial.hpp"

namespace rt
{
    class FlatColor final : public IMaterial {
    private:
        utils::Color _color;

    public:
        class FlatColorException final : public IMaterialException {
        public:
            FlatColorException(const std::string &message) : IMaterialException("FlatColor", message) {}
        };

        [[nodiscard]] utils::Color getColor(const IPrimitive *currentPrimitive,
                                            const math::Vector3<float> &point) const override;

        [[nodiscard]] utils::Color getColor() const { return _color; }
        void setColor(const utils::Color &color) { _color = color; }
    };

    extern "C" {
        FlatColor *createComponent(const libconfig::Setting &setting)
        {
            auto *ptr = new FlatColor();

            ptr->setColor(utils::Color{static_cast<float>(setting["color"]["r"].operator int()) / 255,
                                       static_cast<float>(setting["color"]["g"].operator int()) / 255,
                                       static_cast<float>(setting["color"]["b"].operator int()) / 255});

            return ptr;
        }

        void destroy(const FlatColor *ptr) { delete ptr; }
    }
} // namespace rt

#endif // FLATCOLOR_HPP
