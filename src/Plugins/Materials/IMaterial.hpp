/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP
#define IMATERIAL_HPP

#include "../../Math/Math.hpp"
#include "../../Utils/Utils.hpp"

namespace rt
{
    class IMaterial {
    public:
        class IMaterialException : public utils::Exception {
        public:
            IMaterialException(const std::string &name, const std::string &message) :
                Exception("[Material] " + name, message)
            {}
        };

        virtual ~IMaterial() = default;

        [[nodiscard]] virtual utils::Color getColor(const math::Vector3<float> &point) const = 0;
    };
} // namespace rt

#endif // IMATERIAL_HPP
