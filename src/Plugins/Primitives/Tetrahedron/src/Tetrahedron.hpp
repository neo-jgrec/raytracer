/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Tetrahedron
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <libconfig.h++>
#include "../../APrimitive.hpp"

namespace rt
{
    class Tetrahedron final : public APrimitive {
    private:
        math::Vector3<float> _v0;
        math::Vector3<float> _v1;
        math::Vector3<float> _v2;
        math::Vector3<float> _v3;

    public:
        class TriangleException final : public APrimitiveException {
        public:
            TriangleException(const std::string &message) : APrimitiveException("Tetrahedron", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;
        [[nodiscard]] math::Vector3<float> getOriginPoint() const override {
            return (_v0 + _v1 + _v2 + _v3) / 4;
        }

        void setV0(const math::Vector3<float> &v0) { _v0 = v0; }
        void setV1(const math::Vector3<float> &v1) { _v1 = v1; }
        void setV2(const math::Vector3<float> &v2) { _v2 = v2; }
        void setV3(const math::Vector3<float> &v3) { _v3 = v3; }
        [[nodiscard]] const math::Vector3<float> &getV0() const { return _v0; }
        [[nodiscard]] const math::Vector3<float> &getV1() const { return _v1; }
        [[nodiscard]] const math::Vector3<float> &getV2() const { return _v2; }
        [[nodiscard]] const math::Vector3<float> &getV3() const { return _v3; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(const libconfig::Setting &setting, rt::IMaterial *material)
    {
        auto *tetrahedron = new rt::Tetrahedron();

        tetrahedron->setV0({static_cast<float>(setting["v0"]["x"].operator int()),
                            static_cast<float>(setting["v0"]["y"].operator int()),
                            static_cast<float>(setting["v0"]["z"].operator int())});
        tetrahedron->setV1({static_cast<float>(setting["v1"]["x"].operator int()),
                            static_cast<float>(setting["v1"]["y"].operator int()),
                            static_cast<float>(setting["v1"]["z"].operator int())});
        tetrahedron->setV2({static_cast<float>(setting["v2"]["x"].operator int()),
                            static_cast<float>(setting["v2"]["y"].operator int()),
                            static_cast<float>(setting["v2"]["z"].operator int())});
        tetrahedron->setV3({static_cast<float>(setting["v3"]["x"].operator int()),
                            static_cast<float>(setting["v3"]["y"].operator int()),
                            static_cast<float>(setting["v3"]["z"].operator int())});
        tetrahedron->setMaterial(material);

        return tetrahedron;
    }

    void destroy(const rt::IPrimitive *ptr) { delete ptr; }
}

#endif // SPHERE_HPP
