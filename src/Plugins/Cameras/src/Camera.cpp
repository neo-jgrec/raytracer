/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

#include <cstring>
#include <mutex>
#include <thread>
#include <vector>

namespace rt
{
    void Camera::setResolution(const int width, const int height)
    {
        _width = width;
        _height = height;
        reload();
    }

    void Camera::reload()
    {
        _aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
        _viewportWidth = _aspectRatio * _viewportHeight;

        _horizontal = {_viewportWidth, 0, 0};
        _vertical = {0, _viewportHeight, 0};
        const auto focalLength = static_cast<float>(1 / std::tan(static_cast<float>(_fov) / 2 * M_PI / 180));

        _bottomLeft = _origin - _horizontal / 2 - _vertical / 2 - _direction * -focalLength;
    }

    void Camera::drawChunk(const std::pair<uint32_t, uint32_t> &coord, const std::pair<uint32_t, uint32_t> &size,
                           const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                           const IImage &image)
    {
        for (uint32_t y = coord.second + size.second; y > coord.second; --y) {
            for (uint32_t x = coord.first; x < coord.first + size.first; ++x) {
                const math::Ray ray{
                    _origin,
                    {_bottomLeft + _horizontal * (static_cast<float>(x) / static_cast<float>(_width - 1)) // u
                     + _vertical * (static_cast<float>(_height - y) / static_cast<float>(_height - 1))    // v
                     - _origin}};

                float t = -1;
                const IPrimitive *closestPrimitive = nullptr;
                for (const auto &primitive : primitives)
                    if (const auto tmp = primitive->hit(ray); tmp > 0 && (t < 0 || tmp < t)) {
                        t = tmp;
                        closestPrimitive = primitive;
                    }

                utils::Color color;
                if (closestPrimitive) {
                    for (const auto &light : lights)
                        color += light->illuminate(ray.at(t), primitives, closestPrimitive);

                    color *= closestPrimitive->getMaterial()->getColor(ray.at(t));
                    color = color.clamp();
                }

                image.setPixel(x, y - 1, color);
            }
        }
    }

    void Camera::asyncDrawImage(const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                                const IImage &image)
    {
        for (auto &thread : _threads)
            thread.request_stop();
        for (auto &thread : _threads)
            thread.join();
        _threads.clear();

        const auto [width, height] = image.getSize();
        const auto nbThreads = std::thread::hardware_concurrency();

        const uint32_t nbCol = nbThreads > 4 ? nbThreads / 4 : 1;
        const uint32_t nbRow = std::floor(nbThreads / nbCol);

        reload();
        for (uint8_t i = 0; i < nbThreads; ++i) {
            const std::pair coord = {i % nbCol * width / nbCol, i / nbCol * height / nbRow};
            std::pair size = {width / nbCol, height / nbRow};

            if (i % nbCol == nbCol - 1)
                size.first = width - coord.first;
            if (i / nbCol == nbRow - 1)
                size.second = height - coord.second;

            _threads.emplace_back(&Camera::drawChunk, this, coord, size, primitives, lights, std::ref(image));
        }
    }

    void Camera::awaitDrawImage()
    {
        for (auto &thread : _threads)
            thread.join();
        _threads.clear();
    }

    void Camera::drawImage(const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                           const IImage &image)
    {
        asyncDrawImage(primitives, lights, image);
        awaitDrawImage();
    }
} // namespace rt
