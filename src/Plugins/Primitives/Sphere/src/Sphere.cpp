/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include <complex>
#include <vector>

extern "C" {
    utils::LibraryType getType()
    {
        return utils::LibraryType::PRIMITIVE;
    }

    rt::Sphere *create()
    {
        return new rt::Sphere();
    }

    void destroy(const rt::Sphere *ptr)
    {
        delete ptr;
    }
}

namespace rt
{
    float Sphere::hit(const math::Ray &ray) const
    {
        const math::Vector3<float> oc = ray.origin - _origin;
        const auto a = ray.direction.dot(ray.direction);
        const auto b = 2.0f * oc.dot(ray.direction);
        const auto c = oc.dot(oc) - _radius * _radius;

        const auto descriminant = b * b - 4 * a * c;
        return descriminant < 0
            ? -1
            : (-b - std::sqrt(descriminant)) / (2 * a);
    }

    void Sphere::setOrigin(const math::Vector3<float> &origin)
    {
        _origin = origin;
    }
    void Sphere::setRadius(const float radius)
    {
        _radius = radius;
    }
}
