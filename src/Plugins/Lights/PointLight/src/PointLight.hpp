/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "../ALight.hpp"

#include <libconfig.h++>

#include "../../../Math/Math.hpp"

namespace rt
{
    class PointLight final : public ALight {
    private:
        [[nodiscard]] utils::Color lightAtPoint(const math::Vector3<float> &point) const;

    public:
        class PointLightException final : public ILightException {
        public:
            PointLightException(const std::string &message) : ILightException("PointLight", message) {}
        };

        [[nodiscard]] utils::Color illuminate(const math::Vector3<float> &point,
                                              const std::list<IPrimitive *> &primitives,
                                              const IPrimitive *closestPrimitive) const override;
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
    }
} // namespace rt

#endif // POINTLIGHT_HPP
