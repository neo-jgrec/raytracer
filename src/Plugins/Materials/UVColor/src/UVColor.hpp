/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** UVColor
*/

#ifndef UVCOLOR_HPP
#define UVCOLOR_HPP

#include <libconfig.h++>
#include "../IMaterial.hpp"

namespace rt
{
    class UVColor final : public IMaterial {
    public:
        class UVColorException final : public IMaterialException {
        public:
            UVColorException(const std::string &message) : IMaterialException("UVColor", message) {}
        };

        [[nodiscard]] utils::Color getColor(const IPrimitive *currentPrimitive,
                                            const math::Vector3<float> &point) const override;
    };

    extern "C" {
        UVColor *createComponent([[maybe_unused]] libconfig::Setting &setting) { return new UVColor(); }

        void destroy(const UVColor *ptr) { delete ptr; }
    }
} // namespace rt

#endif // UVCOLOR_HPP
