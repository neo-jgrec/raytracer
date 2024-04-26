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

    math::Vector3<float> Plane::getPosition() const
    {
        return _position;
    }
    void Plane::setPosition(const math::Vector3<float> &position)
    {
        _position = position;
    }

    math::Vector3<float> Plane::getLimit() const
    {
        return _position;
    }
    void Plane::setLimit(const math::Vector3<float> &limit)
    {
        _limit = limit;
    }
}
