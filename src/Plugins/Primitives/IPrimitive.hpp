/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP
    #define IPRIMITIVE_HPP

    #include <memory>

    #include "../Materials/IMaterial.hpp"
    #include "../../Exceptions.hpp"
    #include "../../Math/Math.hpp"

namespace rt
{
    class IPrimitive {
    public:
        class PrimitiveException : public Exception {
        public:
            PrimitiveException(const std::string &name, const std::string &message) :
                Exception(name, message) {}
        };

        [[nodiscard]] virtual float hit(const math::Ray &ray) const = 0;

        virtual void setMaterial(IMaterial *material) = 0;
        [[nodiscard]] virtual IMaterial *getMaterial() const = 0;
    };
} // namespace rt

#endif //IPRIMITIVE_HPP
