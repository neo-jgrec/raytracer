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
        float matrix[3][3];

        Matrix3()
        {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    this->matrix[i][j] = 0;
                }
            }
        }
        Matrix3(const float a, const float b, const float c,
                const float d, const float e, const float f,
                const float g, const float h, const float i)
        {
            this->matrix[0][0] = a;
            this->matrix[0][1] = b;
            this->matrix[0][2] = c;
            this->matrix[1][0] = d;
            this->matrix[1][1] = e;
            this->matrix[1][2] = f;
            this->matrix[2][0] = g;
            this->matrix[2][1] = h;
            this->matrix[2][2] = i;
        }
        static Matrix3 eulerToMatrix(const Vector3<float> &euler)
        {
            float c1 = cos(euler.z);
            float s1 = sin(euler.z);
            float c2 = cos(euler.y);
            float s2 = sin(euler.y);
            float c3 = cos(euler.x);
            float s3 = sin(euler.x);

            return Matrix3(
                c1 * c2, -s1 * c2, s2,
                c1 * s2 * s3 + s1 * c3, -s1 * s2 * s3 + c1 * c3, -c2 * s3,
                -c1 * s2 * c3 + s1 * s3, s1 * s2 * c3 + c1 * s3, c2 * c3
            );
        }
        Matrix3 operator*(const Matrix3 &matrix) const
        {
            Matrix3 result;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    result.matrix[i][j] = 0;
                    for (int k = 0; k < 3; k++) {
                        result.matrix[i][j] += this->matrix[i][k] * matrix.matrix[k][j];
                    }
                }
            }
            return result;
        }
        Vector3<float> operator*(const Vector3<float> &vector) const
        {
            return Vector3<float>(
                matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2] * vector.z,
                matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2] * vector.z,
                matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2] * vector.z
            );
        }
    };
} // namespace math

#endif /* !MATRIX3_HPP_ */
