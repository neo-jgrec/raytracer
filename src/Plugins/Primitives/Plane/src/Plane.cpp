/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"

namespace rt
{
    float Plane::hit(const math::Ray &ray) const
    {
        return 0;
    }

    const std::string Plane::getAxis() const
    {
        return _axis;
    }

    void Plane::setAxis(const std::string axis)
    {
        _axis = axis;
    }

    float Plane::getPosition() const
    {
        return _position;
    }
    void Plane::setPosition(const float position)
    {
        _position = position;
    }
}
