/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP
    #define IPRIMITIVE_HPP

    #include "../Ray.hpp"

class IPrimitive {
public:
    [[nodiscard]] virtual bool hit(const Ray &ray) const = 0;

    // virtual void setMaterial(IMaterial *material) = 0;
};

#endif //IPRIMITIVE_HPP
