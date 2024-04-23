/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

#include <iomanip>
#include <iostream>

namespace rt
{
    utils::Color Camera::getBackgroundPixel(const math::Vector3<float> &direction)
    {
        const auto tf = 0.5f * (direction.y + 1.0f);
        const auto vecColor = math::Vector3{1.0f, 1.0f, 1.0f} * (1.0f - tf)
            + math::Vector3{0.5f, 0.7f, 1.0f} * tf;
        return {vecColor.x, vecColor.y, vecColor.z};
    }

    void Camera::writePixel(const utils::Color &color)
    {
        std::cout
            << static_cast<int>(255.999 * color.r) << " "
            << static_cast<int>(255.999 * color.g) << " "
            << static_cast<int>(255.999 * color.b) << "\n";
    }

    void Camera::setOrigin(const math::Vector3<float> &origin)
    {
        _origin = origin;
    }

    void Camera::generateImage(const std::list<IPrimitive *> primitives)
    {
        std::cout << "P3\n" << _width << " " << _height << "\n255\n";

        for (int j = _height - 1; j >= 0; --j) {
            std::cerr << std::fixed << std::setprecision(2) << "\rProgress: "
                << (1 - (static_cast<float>(j) / static_cast<float>(_height - 1))) * 100 << "% " << std::flush;
            for (int i = 0; i < _width; ++i) {
                const auto u = static_cast<float>(i) / static_cast<float>(_width - 1);
                const auto v = static_cast<float>(j) / static_cast<float>(_height - 1);

                const auto direction{_bottomLeft + _horizontal * u + _vertical * v - _origin};

                const math::Ray ray{_origin, direction};
                float t = -1;
                for (const auto &primitive : primitives) {
                    const auto tmp = primitive->hit(ray);
                    if (tmp > 0 && (t < 0 || tmp < t))
                        t = tmp;
                }

                try {
                    writePixel(t > 0
                        ? primitives.front()->getMaterial()->getColor(ray.at(t))
                        : getBackgroundPixel(direction));
                } catch (const utils::Exception &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
        std::cerr << "\nDone." << std::endl;
    }
} // namespace raytracer
