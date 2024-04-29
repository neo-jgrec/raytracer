/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <libconfig.h++>
#include "../../APrimitive.hpp"

namespace rt
{
    class Rectangle final : public APrimitive {
    private:
        math::Vector3<float> _v0;
        math::Vector3<float> _v1;
        math::Vector3<float> _v2;

    public:
        class RectangleException final : public APrimitiveException {
        public:
            RectangleException(const std::string &message) : APrimitiveException("Rectangle", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;

        void setV0(const math::Vector3<float> &v0) { _v0 = v0; }
        void setV1(const math::Vector3<float> &v1) { _v1 = v1; }
        void setV2(const math::Vector3<float> &v2) { _v2 = v2; }

        [[nodiscard]] const math::Vector3<float> &getV0() const { return _v0; }
        [[nodiscard]] const math::Vector3<float> &getV1() const { return _v1; }
        [[nodiscard]] const math::Vector3<float> &getV2() const { return _v2; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *rectangle = new rt::Rectangle();

        rectangle->setV0({static_cast<float>(setting["v0"]["x"].operator int()),
                         static_cast<float>(setting["v0"]["y"].operator int()),
                         static_cast<float>(setting["v0"]["z"].operator int())});
        rectangle->setV1({static_cast<float>(setting["v1"]["x"].operator int()),
                         static_cast<float>(setting["v1"]["y"].operator int()),
                         static_cast<float>(setting["v1"]["z"].operator int())});
        rectangle->setV2({static_cast<float>(setting["v2"]["x"].operator int()),
                         static_cast<float>(setting["v2"]["y"].operator int()),
                         static_cast<float>(setting["v2"]["z"].operator int())});
        rectangle->setMaterial(material);

        return rectangle;
    }

    void destroy(const rt::IPrimitive *ptr) { delete ptr; }
}

#endif /* !RECTANGLE_HPP */
