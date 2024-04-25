/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** APrimitive
*/

#ifndef APRIMITIVE_HPP
#define APRIMITIVE_HPP

#include "IPrimitive.hpp"

namespace rt
{
    class APrimitive : public IPrimitive {
    private:
        IMaterial *_material = nullptr;

    public:
        class APrimitiveException : public IPrimitiveException {
        public:
            APrimitiveException(const std::string &name, const std::string &message) :
                IPrimitiveException(name, message)
            {}
        };

        void setMaterial(IMaterial *material) override { _material = material; }
        [[nodiscard]] IMaterial *getMaterial() const override
        {
            if (!_material)
                throw APrimitiveException("Primitive", "Material not set");
            return _material;
        }
    };
} // namespace rt

#endif // APRIMITIVE_HPP
