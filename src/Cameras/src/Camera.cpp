/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace rt
{
    void Camera::setResolution(const int width, const int height)
    {
        _width = width;
        _height = height;
    }

    void Camera::generateImageChunk(const uint32_t startHeight, const uint32_t endHeight, const uint32_t startWidth,
                                    const uint32_t endWidth, const std::list<IPrimitive *> &primitives,
                                    const std::list<ILight *> &lights, const std::shared_ptr<uint8_t> &pixels,
                                    const bool rgba)
    {
        for (uint32_t j = startHeight; j < endHeight; ++j) {
            for (uint32_t i = startWidth; i < endWidth; ++i) {
                const math::Ray ray{_origin,
                                    {_bottomLeft +
                                     _horizontal * (static_cast<float>(i) / static_cast<float>(_width - 1))  // u
                                     + _vertical * (static_cast<float>(j) / static_cast<float>(_height - 1)) // v
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

                _mutex.lock();
                if (rgba) {
                    const int index = static_cast<int>((_height - j - 1) * _width * 4 + i * 4);
                    pixels.get()[index] = static_cast<uint8_t>(255.999f * color.r);
                    pixels.get()[index + 1] = static_cast<uint8_t>(255.999f * color.g);
                    pixels.get()[index + 2] = static_cast<uint8_t>(255.999f * color.b);
                    pixels.get()[index + 3] = 255;
                } else {
                    const int index = static_cast<int>((_height - j - 1) * _width * 3 + i * 3);
                    pixels.get()[index] = static_cast<uint8_t>(255.999f * color.r);
                    pixels.get()[index + 1] = static_cast<uint8_t>(255.999f * color.g);
                    pixels.get()[index + 2] = static_cast<uint8_t>(255.999f * color.b);
                }
                _mutex.unlock();
            }
        }
    }

    void Camera::reload(const bool rgba)
    {
        _aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
        _viewportWidth = _aspectRatio * _viewportHeight;

        _horizontal = {_viewportWidth, 0, 0};
        _vertical = {0, _viewportHeight, 0};
        const auto focalLength = static_cast<float>(1 / std::tan(static_cast<float>(_fov) / 2 * M_PI / 180));

        _bottomLeft = _origin - _horizontal / 2 - _vertical / 2 - _direction * -focalLength;
        _pixels.reset(new uint8_t[_width * _height * (rgba ? 4 : 3)], std::default_delete<uint8_t[]>());
        std::memset(_pixels.get(), 0, _width * _height * 3);
    }

    std::tuple<int, int, std::shared_ptr<uint8_t>> Camera::getImages() const { return {_width, _height, _pixels}; }

    std::tuple<int, int, std::shared_ptr<uint8_t>> Camera::generateImage(const std::list<IPrimitive *> &primitives,
                                                                         const std::list<ILight *> &lights,
                                                                         const bool rgba, const bool waiting)
    {
        reload(rgba);

        const auto nbThreads = std::thread::hardware_concurrency();
        const uint16_t height = _height / nbThreads;

        std::cout << "Rendering with " << nbThreads << " threads" << std::endl;
        for (uint8_t i = 0; i < nbThreads; ++i)
            if (i == nbThreads - 1)
                _threads.emplace_back(&Camera::generateImageChunk, this, i * height, _height, 0, _width, primitives,
                                     lights, _pixels, rgba);
            else
                _threads.emplace_back(&Camera::generateImageChunk, this, i * height, (i + 1) * height, 0, _width,
                                     primitives, lights, _pixels, rgba);

        if (waiting)
            for (auto &thread : _threads)
                thread.join();

        return {_width, _height, _pixels};
    }
} // namespace rt
