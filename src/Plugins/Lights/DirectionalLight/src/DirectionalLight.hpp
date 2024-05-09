/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "../ILight.hpp"

#include <libconfig.h++>

#include "../../../Math/Math.hpp"

namespace rt
{
    class DirectionalLight final : public ILight {
    private:
        math::Vector3<float> _origin;
        math::Vector3<float> _direction;
        utils::Color _color;

        float _intensity = 1.f;

        [[nodiscard]] utils::Color lightAtPoint(const math::Vector3<float> &point) const;

    public:
        class DirectionalLightException final : public ILightException {
        public:
            DirectionalLightException(const std::string &message) : ILightException("DirectionalLight", message) {}
        };

        [[nodiscard]] utils::Color illuminate(const math::Vector3<float> &point,
                                              const std::list<IPrimitive *> &primitives,
                                              const IPrimitive *closestPrimitive) const override;

        [[nodiscard]] const math::Vector3<float> &getOrigin() const override { return _origin; }
        void setOrigin(const math::Vector3<float> &origin) { _origin = origin; }

        [[nodiscard]] const math::Vector3<float> &getDirection() const { return _direction; }
        void setDirection(const math::Vector3<float> &direction) { _direction = direction; }

        [[nodiscard]] const utils::Color &getColor() const { return _color; }
        void setColor(const utils::Color &color) { _color = color; }

        [[nodiscard]] float getIntensity() const { return _intensity; }
        void setIntensity(const float intensity)
        {
            if (intensity < 0.f || intensity > 1.f)
                throw DirectionalLightException("Intensity must be between 0 and 1");
            _intensity = intensity;
        }
    };
} // namespace rt

extern "C" {
    rt::DirectionalLight *createComponent(const libconfig::Setting &light)
    {
        auto *newDirectionalLight = new rt::DirectionalLight();

        newDirectionalLight->setOrigin(math::Vector3{static_cast<float>(light["origin"]["x"].operator int()),
                                                     static_cast<float>(light["origin"]["y"].operator int()),
                                                     static_cast<float>(light["origin"]["z"].operator int())});
        newDirectionalLight->setDirection(math::Vector3{static_cast<float>(light["direction"]["x"].operator int()),
                                                        static_cast<float>(light["direction"]["y"].operator int()),
                                                        static_cast<float>(light["direction"]["z"].operator int())});
        newDirectionalLight->setColor(utils::Color{static_cast<float>(light["color"]["r"].operator int()) / 255.f,
                                                   static_cast<float>(light["color"]["g"].operator int()) / 255.f,
                                                   static_cast<float>(light["color"]["b"].operator int()) / 255.f});
        newDirectionalLight->setIntensity((light["intensity"].operator float()));

        return newDirectionalLight;
    }

    void destroy(const rt::DirectionalLight *ptr) { delete ptr; }
}

#endif // DIRECTIONALLIGHT_HPP
