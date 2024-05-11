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

        /**
         * @brief compute if the ray pass though the primitive or not
         * @param ray the ray to compute
         * @return -1 if the ray doesn't pass through the primitive or
         * a float corresponding to the distance between the origin of the ray and the hit point
         */
        [[nodiscard]] virtual float hit(const math::Ray &ray) const = 0;
        [[nodiscard]] virtual math::Vector3<float> getNormal(const math::Vector3<float> &point) const = 0;

        virtual void setTranslation(const math::Vector3<float> &translation) = 0;
        virtual void setRotation(const math::Vector3<float> &rotation) = 0;
        virtual void setScale(const math::Vector3<float> &scale) = 0;
        virtual void setMatrix(const math::Vector3<math::Vector3<float>> &matrix) = 0;

        virtual void setMaterial(IMaterial *material) = 0;
        [[nodiscard]] virtual IMaterial *getMaterial() const = 0;

        [[nodiscard]] virtual math::Vector3<float> getOriginPoint() const = 0;
    };
} // namespace rt

#endif // IPRIMITIVE_HPP
