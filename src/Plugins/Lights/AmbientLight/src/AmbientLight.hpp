/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AmbientLight
*/

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

#include <libconfig.h++>

#include "../ALight.hpp"

namespace rt
{
    class AmbientLight final : public ALight {
    private:
        float _intensity = 1.f;

    public:
        class AmbientLightException final : public ILightException {
        public:
            AmbientLightException(const std::string &message) : ILightException("AmbientLight", message) {}
        };

        [[nodiscard]] utils::Color illuminate(const math::Vector3<float> &point,
                                              const std::list<IPrimitive *> &primitives,
                                              const IPrimitive *closestPrimitive) const override;

        // [[nodiscard]] const math::Vector3<float> &getOrigin() const override { return math::Vector3<float>{0, 0, 0};
        // } void setOrigin([[maybe_unused]] const math::Vector3<float> &origin) override {}
    };

    extern "C" {
        AmbientLight *createComponent(const libconfig::Setting &setting)
        {
            auto *ptr = new AmbientLight();

            ptr->setColor(utils::Color{static_cast<float>(setting["color"]["r"].operator int()) / 255.f,
                                       static_cast<float>(setting["color"]["g"].operator int()) / 255.f,
                                       static_cast<float>(setting["color"]["b"].operator int()) / 255.f});
            ptr->setIntensity(setting["intensity"].operator float());

            return ptr;
        }
    }
} // namespace rt

#endif // AMBIENTLIGHT_HPP
