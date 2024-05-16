/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "../ILight.hpp"

#include <libconfig.h++>

#include "../../../Math/Math.hpp"

namespace rt
{
    class PointLight final : public ILight {
    private:
        math::Vector3<float> _origin;
        utils::Color _color;

        float _intensity = 1.f;

        [[nodiscard]] utils::Color lightAtPoint(const math::Vector3<float> &point) const;

    public:
        class PointLightException final : public ILightException {
        public:
            PointLightException(const std::string &message) : ILightException("PointLight", message) {}
        };

        [[nodiscard]] utils::Color illuminate(const math::Vector3<float> &point,
                                              const std::list<IPrimitive *> &primitives,
                                              const IPrimitive *closestPrimitive) const override;

        [[nodiscard]] const math::Vector3<float> &getOrigin() const override { return _origin; }
        void setOrigin(const math::Vector3<float> &origin) { _origin = origin; }

        [[nodiscard]] const utils::Color &getColor() const { return _color; }
        void setColor(const utils::Color &color) { _color = color; }

        [[nodiscard]] float getIntensity() const { return _intensity; }
        void setIntensity(const float intensity)
        {
            if (intensity < 0.f || intensity > 1.f)
                throw PointLightException("Intensity must be between 0 and 1");
            _intensity = intensity;
        }
    };

    extern "C" {
        PointLight *createComponent(const libconfig::Setting &setting)
        {
            auto *ptr = new PointLight();

            ptr->setOrigin(math::Vector3{static_cast<float>(setting["origin"]["x"].operator int()),
                                         static_cast<float>(setting["origin"]["y"].operator int()),
                                         static_cast<float>(setting["origin"]["z"].operator int())});
            ptr->setColor(utils::Color{static_cast<float>(setting["color"]["r"].operator int()) / 255.f,
                                       static_cast<float>(setting["color"]["g"].operator int()) / 255.f,
                                       static_cast<float>(setting["color"]["b"].operator int()) / 255.f});
            ptr->setIntensity(setting["intensity"].operator float());

            return ptr;
        }

        void destroy(const PointLight *ptr) { delete ptr; }
    }
} // namespace rt

#endif // POINTLIGHT_HPP
