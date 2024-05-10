/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vector3
*/

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <complex>

namespace math
{
    template <typename T>
    class Vector3 {
    public:
        T x;
        T y;
        T z;

        Vector3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}

        // Multiplication
        Vector3 operator*(const T &scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
        Vector3 operator*(const Vector3 &other) const { return Vector3(x * other.x, y * other.y, z * other.z); }
        Vector3 operator*=(const T &scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        Vector3 operator*=(const Vector3 &other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        // Addition
        Vector3 operator+(const T &scalar) const { return Vector3(x + scalar, y + scalar, z + scalar); }
        Vector3 operator+(const Vector3 &other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
        Vector3 operator+=(const T &scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
            return *this;
        }
        Vector3 operator+=(const Vector3 &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        // Substraction
        Vector3 operator-(const T &scalar) const { return Vector3(x - scalar, y - scalar, z - scalar); }
        Vector3 operator-(const Vector3 &other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
        Vector3 operator-=(const T &scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            return *this;
        }
        Vector3 operator-=(const Vector3 &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        // Division
        Vector3 operator/(const T &scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }
        Vector3 operator/(const Vector3 &other) const { return Vector3(x / other.x, y / other.y, z / other.z); }
        Vector3 operator/=(const T &scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }
        Vector3 operator/=(const Vector3 &other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        // Comparison
        bool operator==(const Vector3 &other) const { return x == other.x && y == other.y && z == other.z; }
        bool operator!=(const Vector3 &other) const { return x != other.x || y != other.y || z != other.z; }
        bool operator<(const Vector3 &other) const { return x < other.x && y < other.y && z < other.z; }
        bool operator>(const Vector3 &other) const { return x > other.x && y > other.y && z > other.z; }

        // operator []
        T operator[](const int index) const
        {
            switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw std::out_of_range("Index out of range");
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const Vector3 &dot)
        {
            os << "Vector3(" << dot.x << ", " << dot.y << ", " << dot.z << ")";
            return os;
        }

        T dot(const Vector3 &other) const { return x * other.x + y * other.y + z * other.z; }
        T distance(const Vector3 &other) const
        {
            return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
        }

        T length() const { return std::sqrt(x * x + y * y + z * z); }

        Vector3 normalize() const { return *this / length(); }
        Vector3 cross(const Vector3 &other) const
        {
            return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
        }
    };
} // namespace math

#endif // VECTOR3_HPP
