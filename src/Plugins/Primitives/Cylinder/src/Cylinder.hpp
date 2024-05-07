/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <libconfig.h++>
#include "../../APrimitive.hpp"

namespace rt
{
    class Cylinder final : public APrimitive {
    private:
        math::Vector3<float> _direction = math::Vector3<float>{0, 0, 0};
        math::Vector3<float> _origin = math::Vector3<float>{0, 0, -1};
        float _radius = 0.5;
        float _height = 1;

    public:
        class CylinderException final : public APrimitiveException {
        public:
            CylinderException(const std::string &message) : APrimitiveException("Cylinder", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;

        [[nodiscard]] const math::Vector3<float> &getOrigin() const { return _origin; }
        [[nodiscard]] float getRadius() const { return _radius; }

        void setOrigin(const math::Vector3<float> &origin) { _origin = origin; }
        void setRadius(const float radius) { _radius = radius; }
        void setDirection(const math::Vector3<float> &direction) { _direction = direction; }
        void setHeight(const float height) { _height = height; }

        static float sgn(float x) { return x > 0 ? 1 : -1; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(libconfig::Setting &cylinder, rt::IMaterial *material)
    {
        auto *newCylinder = new rt::Cylinder();

        newCylinder->setOrigin(math::Vector3{static_cast<float>(cylinder["x"].operator int()),
                                           static_cast<float>(cylinder["y"].operator int()),
                                           static_cast<float>(cylinder["z"].operator int())});
        newCylinder->setRadius((cylinder["r"].operator float()));
        newCylinder->setMaterial(material);
        newCylinder->setDirection(math::Vector3{static_cast<float>(cylinder["direction"]["x"].operator int()),
                                                static_cast<float>(cylinder["direction"]["y"].operator int()),
                                                static_cast<float>(cylinder["direction"]["z"].operator int())});
        newCylinder->setHeight(cylinder["height"].operator float());

        return newCylinder;
    }

    void destroy(const rt::IPrimitive *ptr) { delete ptr; }
}

#endif // CYLINDER_HPP
