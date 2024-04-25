/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP
#define IPRIMITIVE_HPP

#include "../../Math/Math.hpp"
#include "../../Utils/Utils.hpp"
#include "../Materials/IMaterial.hpp"

namespace rt
{
    class IPrimitive {
    public:
        class IPrimitiveException : public utils::Exception {
        public:
            IPrimitiveException(const std::string &name, const std::string &message) :
                Exception("[Primitive] " + name, message)
            {}
        };

        virtual ~IPrimitive() = default;

        [[nodiscard]] virtual float hit(const math::Ray &ray) const = 0;

        virtual void setMaterial(IMaterial *material) = 0;
        [[nodiscard]] virtual IMaterial *getMaterial() const = 0;
    };
} // namespace rt

#endif // IPRIMITIVE_HPP
