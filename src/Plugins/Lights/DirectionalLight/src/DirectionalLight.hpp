/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "../ALight.hpp"

#include <libconfig.h++>

#include "../../../Math/Math.hpp"

namespace rt
{
    class DirectionalLight final : public ALight {
    private:
        math::Vector3<float> _direction;

        [[nodiscard]] utils::Color lightAtPoint(const math::Vector3<float> &point) const;

    public:
        class DirectionalLightException final : public ILightException {
        public:
            DirectionalLightException(const std::string &message) : ILightException("DirectionalLight", message) {}
        };

        [[nodiscard]] const math::Vector3<float> &getDirection() const { return _direction; }
        void setDirection(const math::Vector3<float> &direction) { _direction = direction; }

        [[nodiscard]] utils::Color illuminate(const math::Vector3<float> &point,
                                              const std::list<IPrimitive *> &primitives,
                                              const IPrimitive *closestPrimitive) const override;
    };

    extern "C" {
        DirectionalLight *createComponent(const libconfig::Setting &setting)
        {
            auto *ptr = new DirectionalLight();

            ptr->setOrigin(math::Vector3{static_cast<float>(setting["origin"]["x"].operator int()),
                                         static_cast<float>(setting["origin"]["y"].operator int()),
                                         static_cast<float>(setting["origin"]["z"].operator int())});
            ptr->setDirection(math::Vector3{static_cast<float>(setting["direction"]["x"].operator int()),
                                            static_cast<float>(setting["direction"]["y"].operator int()),
                                            static_cast<float>(setting["direction"]["z"].operator int())});
            ptr->setColor(utils::Color{static_cast<float>(setting["color"]["r"].operator int()) / 255.f,
                                       static_cast<float>(setting["color"]["g"].operator int()) / 255.f,
                                       static_cast<float>(setting["color"]["b"].operator int()) / 255.f});
            ptr->setIntensity(setting["intensity"].operator float());

            return ptr;
        }
    }
} // namespace rt

#endif // DIRECTIONALLIGHT_HPP
