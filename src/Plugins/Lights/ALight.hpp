/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ILight
*/

#ifndef ALIGHT_HPP
#define ALIGHT_HPP

#include "ILight.hpp"

namespace rt
{
    class ALight : public ILight {
    protected:
        math::Vector3<float> _origin;
        utils::Color _color;
        float _intensity = 1.f;

    public:
        class ALightException final : public ILightException {
        public:
            ALightException(const std::string &message) : ILightException("", message) {}
        };

        [[nodiscard]] const math::Vector3<float> &getOrigin() const override { return _origin; }
        void setOrigin(const math::Vector3<float> &origin) override { _origin = origin; }

        [[nodiscard]] const utils::Color &getColor() const override { return _color; }
        void setColor(const utils::Color &color) override { _color = color; }

        [[nodiscard]] float getIntensity() const override { return _intensity; }
        void setIntensity(const float intensity) override
        {
            if (intensity < 0.f || intensity > 1.f)
                throw ALightException("Intensity must be between 0 and 1");
            _intensity = intensity;
        }
    };

    extern "C" {
        void destroy(const ALight *ptr) { delete ptr; }
    }
} // namespace rt

#endif // ALIGHT_HPP
