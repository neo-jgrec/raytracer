/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ILight
*/

#ifndef ILIGHT_HPP
#define ILIGHT_HPP

#include "../../Math/Math.hpp"
#include "../../Utils/Utils.hpp"

namespace rt
{
    class ILight {
    public:
        class ILightException : public utils::Exception {
        public:
            ILightException(const std::string &name, const std::string &message) : Exception("[Light] " + name, message)
            {}
        };

        virtual ~ILight() = default;

        [[nodiscard]] virtual const math::Vector3<float> &getOrigin() const = 0;
        virtual void illuminate(const math::Vector3<float> &point, utils::Color &color) const = 0;
    };
} // namespace rt

#endif // ILIGHT_HPP
