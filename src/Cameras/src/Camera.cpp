/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

#include <fstream>
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

    std::pair<int, int> Camera::getResolution() const
    {
        return {_width, _height};
    }
    void Camera::setResolution(const int width, const int height)
    {
        _width = width;
        _height = height;
        _aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);

        _viewportWidth = _aspectRatio * _viewportHeight;

        _horizontal = math::Vector3<float>{_viewportWidth, 0, 0};
        _vertical = math::Vector3<float>{0, _viewportHeight, 0};
        _bottomLeft = _origin - _horizontal / 2 - _vertical / 2 - math::Vector3<float>{0, 0, _focalLength};
    }

    const math::Vector3<float> &Camera::getOrigin() const
    {
        return _origin;
    }
    void Camera::setOrigin(const math::Vector3<float> &origin)
    {
        _origin = origin;
    }

    std::tuple<int, int, std::shared_ptr<uint8_t>> Camera::generateImage(const std::list<IPrimitive *> primitives)
    {
        const auto pixels = std::shared_ptr<uint8_t>(new uint8_t[_width * _height * 3]);

        for (int j = _height - 1; j >= 0; --j) {
            std::cout << std::fixed << std::setprecision(2) << "\rProgress: "
                << (1 - (static_cast<float>(j) / static_cast<float>(_height - 1))) * 100 << "% " << std::flush;
            for (int i = 0; i < _width; ++i) {
                const auto u = static_cast<float>(i) / static_cast<float>(_width - 1);
                const auto v = static_cast<float>(j) / static_cast<float>(_height - 1);

                const auto direction{_bottomLeft + _horizontal * u + _vertical * v - _origin};
                const math::Ray ray{_origin, direction};

                float t = -1;
                const IPrimitive *closestPrimitive = nullptr;
                for (const auto &primitive : primitives) {
                    const auto tmp = primitive->hit(ray);
                    if (tmp > 0 && (t < 0 || tmp < t)) {
                        t = tmp;
                        closestPrimitive = primitive;
                    }
                }

                const utils::Color color = t > 0
                    ? closestPrimitive->getMaterial()->getColor(ray.at(t))
                    : getBackgroundPixel(direction);
                pixels.get()[j * _width * 3 + i * 3] = static_cast<uint8_t>(color.r);
                pixels.get()[j * _width * 3 + i * 3 + 1] = static_cast<uint8_t>(color.g);
                pixels.get()[j * _width * 3 + i * 3 + 2] = static_cast<uint8_t>(color.b);
            }
        }
        std::cout << std::endl;
        return {_width, _height, pixels};
    }
} // namespace raytracer
