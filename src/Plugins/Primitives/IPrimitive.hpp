/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP
    #define IPRIMITIVE_HPP

    #include "../Materials/IMaterial.hpp"
    #include "../../Utils/Utils.hpp"
    #include "../../Math/Math.hpp"

namespace rt
{
    class IPrimitive {
    public:
        class IPrimitiveException : public utils::Exception {
        public:
            IPrimitiveException(const std::string &name, const std::string &message) :
                Exception("[Primitive] " + name, message) {}
        };

        [[nodiscard]] virtual float hit(const math::Ray &ray) const = 0;

        virtual void setMaterial(IMaterial *material) = 0;
        [[nodiscard]] virtual IMaterial *getMaterial() const = 0;
    };
} // namespace rt

#endif //IPRIMITIVE_HPP
