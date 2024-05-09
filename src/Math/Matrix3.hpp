/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Matrix3
*/

#ifndef MATRIX3_HPP_
#define MATRIX3_HPP_

#include <cmath>
#include "../Math/Vector3.hpp"

namespace math
{
    class Matrix3 final {
    public:
        float m[3][3];

        Matrix3() {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    m[i][j] = (i == j) ? 1.0f : 0.0f;
        }

        static Matrix3 rotation(const Vector3<float>& axis, float angle) {
            Matrix3 rot;
            float c = cos(angle);
            float s = sin(angle);
            float t = 1.0f - c;
            float x = axis.x, y = axis.y, z = axis.z;

            // First row
            rot.m[0][0] = t*x*x + c;
            rot.m[0][1] = t*x*y - s*z;
            rot.m[0][2] = t*x*z + s*y;

            // Second row
            rot.m[1][0] = t*x*y + s*z;
            rot.m[1][1] = t*y*y + c;
            rot.m[1][2] = t*y*z - s*x;

            // Third row
            rot.m[2][0] = t*x*z - s*y;
            rot.m[2][1] = t*y*z + s*x;
            rot.m[2][2] = t*z*z + c;

            return rot;
        }

        Vector3<float> operator*(const Vector3<float>& v) const {
            return Vector3(
                m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z,
                m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z,
                m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z
            );
        }
    };
} // namespace math

#endif /* !MATRIX3_HPP_ */
