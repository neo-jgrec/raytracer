/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cone
*/

#ifndef CONE_HPP
#define CONE_HPP

#include <libconfig.h++>
#include "../../APrimitive.hpp"

namespace rt
{
    class Cone final : public APrimitive {
    private:
        math::Vector3<float> _direction = math::Vector3<float>{0, 0, 0};
        math::Vector3<float> _origin = math::Vector3<float>{0, 0, -1};
        float _radius = 0.5;
        bool _isInfinite = true;

    public:
        class ConeException final : public APrimitiveException {
        public:
            ConeException(const std::string &message) : APrimitiveException("Cone", message) {}
        };

        [[nodiscard]] float hit(const math::Ray &ray) const override;

        [[nodiscard]] const math::Vector3<float> &getOrigin() const { return _origin; }
        [[nodiscard]] float getRadius() const { return _radius; }
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override;

        void setOrigin(const math::Vector3<float> &origin) { _origin = origin; }
        void setRadius(const float radius) { _radius = radius; }
        void setDirection(const math::Vector3<float> &direction) { _direction = direction; }
        void setInfinite(const bool isInfinite) { _isInfinite = isInfinite; }

        static float sgn(float x) { return x > 0 ? 1 : -1; }
    };
} // namespace rt

extern "C" {
    rt::IPrimitive *createComponent(libconfig::Setting &cone, rt::IMaterial *material)
    {
        auto *newCone = new rt::Cone();

        newCone->setOrigin(math::Vector3{static_cast<float>(cone["x"].operator int()),
                                           static_cast<float>(cone["y"].operator int()),
                                           static_cast<float>(cone["z"].operator int())});
        newCone->setRadius((cone["r"].operator float()));
        newCone->setMaterial(material);
        newCone->setDirection(math::Vector3{static_cast<float>(cone["direction"]["x"].operator int()),
                                                static_cast<float>(cone["direction"]["y"].operator int()),
                                                static_cast<float>(cone["direction"]["z"].operator int())});
        newCone->setInfinite(cone["infinite"].operator bool());

        return newCone;
    }

    void destroy(const rt::IPrimitive *ptr) { delete ptr; }
}

#endif // CONE_HPP
