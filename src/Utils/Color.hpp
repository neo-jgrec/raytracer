/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color
*/

#ifndef COLOR_HPP
#define COLOR_HPP

#include <algorithm>
#include <ostream>

namespace utils
{
    class Color {
    public:
        float r;
        float g;
        float b;
        float a;

        Color(const float r = 0, const float g = 0, const float b = 0, const float a = 1) : r{r}, g{g}, b{b}, a{a} {}

        // Addition
        Color operator+(const float &value) const { return Color{r + value, g + value, b + value, a}; }
        Color operator+(const Color &color) const { return Color{r + color.r, g + color.g, b + color.b, a}; }
        Color operator+=(const float &value)
        {
            r += value;
            g += value;
            b += value;
            return *this;
        }
        Color operator+=(const Color &color)
        {
            r += color.r;
            g += color.g;
            b += color.b;
            return *this;
        }

        // Subtraction
        Color operator-(const float &value) const { return Color{r - value, g - value, b - value, a}; }
        Color operator-(const Color &color) const { return Color{r - color.r, g - color.g, b - color.b, a}; }
        Color operator-=(const float &value)
        {
            r -= value;
            g -= value;
            b -= value;
            return *this;
        }
        Color operator-=(const Color &color)
        {
            r -= color.r;
            g -= color.g;
            b -= color.b;
            return *this;
        }

        // Multiplication
        Color operator*(const float &value) const { return Color{r * value, g * value, b * value, a}; }
        Color operator*(const Color &color) const { return Color{r * color.r, g * color.g, b * color.b, a}; }
        Color operator*=(const float &value)
        {
            r *= value;
            g *= value;
            b *= value;
            return *this;
        }
        Color operator*=(const Color &color)
        {
            r *= color.r;
            g *= color.g;
            b *= color.b;
            return *this;
        }

        // Division
        Color operator/(const float &value) const { return Color{r / value, g / value, b / value, a}; }
        Color operator/(const Color &color) const { return Color{r / color.r, g / color.g, b / color.b, a}; }
        Color operator/=(const float &value)
        {
            r /= value;
            g /= value;
            b /= value;
            return *this;
        }
        Color operator/=(const Color &color)
        {
            r /= color.r;
            g /= color.g;
            b /= color.b;
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

        // Stream
        friend std::ostream &operator<<(std::ostream &os, const Color &color)
        {
            os << "Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
            return os;
        }

        Color clamp()
        {
            r = std::clamp(r, 0.f, 1.f);
            g = std::clamp(g, 0.f, 1.f);
            b = std::clamp(b, 0.f, 1.f);
            return *this;
        }
    };
} // namespace utils

#endif // COLOR_HPP
