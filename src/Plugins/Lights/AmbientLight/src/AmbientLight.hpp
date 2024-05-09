/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AmbientLight
*/

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

#include "../ILight.hpp"

#include <libconfig.h++>

#include "../../../Math/Math.hpp"

namespace rt
{
    class AmbientLight final : public ILight {
    private:
        utils::Color _color;
        float _intensity = 1.f;

    public:
        class AmbientLightException final : public ILightException {
        public:
            AmbientLightException(const std::string &message) : ILightException("AmbientLight", message) {}
        };

        [[nodiscard]] utils::Color illuminate(const math::Vector3<float> &point,
                                              [[maybe_unused]] const std::list<IPrimitive *> &primitives,
                                              [[maybe_unused]] const IPrimitive *closestPrimitive) const override;

        [[nodiscard]] const math::Vector3<float> &getOrigin() const override;

        [[nodiscard]] const utils::Color &getColor() const { return _color; }
        void setColor(const utils::Color &color) { _color = color; }

        [[nodiscard]] float getIntensity() const { return _intensity; }
        void setIntensity(const float intensity)
        {
            if (intensity < 0.f || intensity > 1.f)
                throw AmbientLightException("Intensity must be between 0 and 1");
            _intensity = intensity;
        }
    };
} // namespace rt

extern "C" {
    rt::AmbientLight *createComponent(const libconfig::Setting &light)
    {
        auto *ptr = new rt::AmbientLight();

        ptr->setColor(utils::Color{static_cast<float>(light["color"]["r"].operator int()) / 255.f,
                                   static_cast<float>(light["color"]["g"].operator int()) / 255.f,
                                   static_cast<float>(light["color"]["b"].operator int()) / 255.f});
        ptr->setIntensity((light["intensity"].operator float()));

        return ptr;
    }

    void destroy(const rt::AmbientLight *ptr) { delete ptr; }
}

#endif // AMBIENTLIGHT_HPP
