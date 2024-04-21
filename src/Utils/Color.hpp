/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color
*/

#ifndef COLOR_HPP
#define COLOR_HPP

namespace utils
{
    class Color {
    public:
        float r;
        float g;
        float b;
        float a;

        Color(const float r = 0, const float g = 0, const float b = 0, const float a = 1)
            : r{r}, g{g}, b{b}, a{a}
        {}

        // Addition
        Color operator+(const float &value) const
        {
            return Color{r + value, g + value, b + value, a + value};
        }
        Color operator+(const Color &color) const
        {
            return Color{r + color.r, g + color.g, b + color.b, a + color.a};
        }
        Color operator+=(const float &value)
        {
            r += value;
            g += value;
            b += value;
            a += value;
            return *this;
        }
        Color operator+=(const Color &color)
        {
            r += color.r;
            g += color.g;
            b += color.b;
            a += color.a;
            return *this;
        }

        // Subtraction
        Color operator-(const float &value) const
        {
            return Color{r - value, g - value, b - value, a - value};
        }
        Color operator-(const Color &color) const
        {
            return Color{r - color.r, g - color.g, b - color.b, a - color.a};
        }
        Color operator-=(const float &value)
        {
            r -= value;
            g -= value;
            b -= value;
            a -= value;
            return *this;
        }
        Color operator-=(const Color &color)
        {
            r -= color.r;
            g -= color.g;
            b -= color.b;
            a -= color.a;
            return *this;
        }

        // Multiplication
        Color operator*(const float &value) const
        {
            return Color{r * value, g * value, b * value, a * value};
        }
        Color operator*(const Color &color) const
        {
            return Color{r * color.r, g * color.g, b * color.b, a * color.a};
        }
        Color operator*=(const float &value)
        {
            r *= value;
            g *= value;
            b *= value;
            a *= value;
            return *this;
        }
        Color operator*=(const Color &color)
        {
            r *= color.r;
            g *= color.g;
            b *= color.b;
            a *= color.a;
            return *this;
        }

        // Division
        Color operator/(const float &value) const
        {
            return Color{r / value, g / value, b / value, a / value};
        }
        Color operator/(const Color &color) const
        {
            return Color{r / color.r, g / color.g, b / color.b, a / color.a};
        }
        Color operator/=(const float &value)
        {
            r /= value;
            g /= value;
            b /= value;
            a /= value;
            return *this;
        }
        Color operator/=(const Color &color)
        {
            r /= color.r;
            g /= color.g;
            b /= color.b;
            a /= color.a;
            return *this;
        }

        // Comparison
        bool operator==(const Color &color) const
        {
            return r == color.r && g == color.g && b == color.b && a == color.a;
        }
        bool operator!=(const Color &color) const
        {
            return r != color.r || g != color.g || b != color.b || a != color.a;
        }
    };
}


#endif //COLOR_HPP
