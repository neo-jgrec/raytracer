/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Triangle
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <libconfig.h++>
#include "../../APrimitive.hpp"

namespace rt
{
    class Triangle final : public APrimitive {
    private:
        math::Vector3<float> _v0;
        math::Vector3<float> _v1;
        math::Vector3<float> _v2;

    public:
        class TriangleException final : public APrimitiveException {
        public:
            TriangleException(const std::string &message) : APrimitiveException("Triangle", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;

        void setV0(const math::Vector3<float> &v0) { _v0 = v0; }
        void setV1(const math::Vector3<float> &v1) { _v1 = v1; }
        void setV2(const math::Vector3<float> &v2) { _v2 = v2; }
        [[nodiscard]] const math::Vector3<float> &getV0() const { return _v0; }
        [[nodiscard]] const math::Vector3<float> &getV1() const { return _v1; }
        [[nodiscard]] const math::Vector3<float> &getV2() const { return _v2; }

        void setTranslation(const math::Vector3<float> &translation) override;
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *triangle = new rt::Triangle();

        triangle->setV0({static_cast<float>(setting["v0"]["x"].operator int()),
                         static_cast<float>(setting["v0"]["y"].operator int()),
                         static_cast<float>(setting["v0"]["z"].operator int())});
        triangle->setV1({static_cast<float>(setting["v1"]["x"].operator int()),
                         static_cast<float>(setting["v1"]["y"].operator int()),
                         static_cast<float>(setting["v1"]["z"].operator int())});
        triangle->setV2({static_cast<float>(setting["v2"]["x"].operator int()),
                         static_cast<float>(setting["v2"]["y"].operator int()),
                         static_cast<float>(setting["v2"]["z"].operator int())});
        triangle->setMaterial(material);

        return triangle;
    }

    void destroy(const rt::IPrimitive *ptr) { delete ptr; }
}

#endif // SPHERE_HPP
