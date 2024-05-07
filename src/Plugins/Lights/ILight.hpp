/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ILight
*/

#ifndef ILIGHT_HPP
#define ILIGHT_HPP

#include <list>

#include "../../Math/Math.hpp"
#include "../../Utils/Utils.hpp"
#include "../Primitives/IPrimitive.hpp"


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
        [[nodiscard]] virtual utils::Color illuminate(const math::Vector3<float> &point,
                                                      const std::list<IPrimitive *> &primitives,
                                                      const IPrimitive *closestPrimitive) const = 0;
    };
} // namespace rt

#endif // ILIGHT_HPP
