/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP
    #define IMATERIAL_HPP

    #include "../../Utils/Utils.hpp"
    #include "../../Math/Math.hpp"

namespace rt
{
    class IMaterial {
    public:
        class IMaterialException : public utils::Exception {
        public:
            IMaterialException(const std::string &name, const std::string &message) :
                Exception("[Material] " + name, message) {}
        };

        [[nodiscard]] virtual utils::Color getColor(const math::Vector3<float> &point) const = 0;
    };
} // namespace rt

#endif //IMATERIAL_HPP
