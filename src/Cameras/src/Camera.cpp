/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

#include <iostream>
#include <thread>
#include <vector>

namespace rt
{
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

    void Camera::generateImageChunk(const uint32_t startHeight, const uint32_t endHeight, const uint32_t startWidth,
                                    const uint32_t endWidth, const std::list<IPrimitive *> &primitives,
                                    const std::list<ILight *> &lights, const std::shared_ptr<uint8_t> &pixels) const
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
                for (const auto &primitive : primitives) {
                    if (const auto tmp = primitive->hit(ray); tmp > 0 && (t < 0 || tmp < t)) {
                        t = tmp;
                        closestPrimitive = primitive;
                    }
                }

                utils::Color color;
                if (closestPrimitive) {
                    color = closestPrimitive->getMaterial()->getColor(ray.at(t));
                    for (const auto &light : lights)
                        light->illuminate(ray.at(t), color);
                }

                const int index = static_cast<int>((_height - j - 1) * _width * 3 + i * 3);
                pixels.get()[index] = static_cast<uint8_t>(255.999f * color.r);
                pixels.get()[index + 1] = static_cast<uint8_t>(255.999f * color.g);
                pixels.get()[index + 2] = static_cast<uint8_t>(255.999f * color.b);
            }
        }
    }

    std::tuple<int, int, std::shared_ptr<uint8_t>> Camera::generateImage(const std::list<IPrimitive *> primitives,
                                                                         const std::list<ILight *> lights)
    {
        const auto pixels =
            std::shared_ptr<uint8_t>(new uint8_t[_width * _height * 3], std::default_delete<uint8_t[]>());

        const auto nbThreads = std::thread::hardware_concurrency();
        std::cout << "Using " << nbThreads << " threads" << std::endl;

        std::vector<std::thread> threads;
        const uint16_t height = _height / nbThreads;

        for (uint8_t i = 0; i < nbThreads; ++i) {
            if (i == nbThreads - 1) {
                threads.emplace_back(&Camera::generateImageChunk, this, i * height, _height, 0, _width, primitives,
                                     lights, std::ref(pixels));
            } else {
                threads.emplace_back(&Camera::generateImageChunk, this, i * height, (i + 1) * height, 0, _width,
                                     primitives, lights, std::ref(pixels));
            }
        }
        for (auto &thread : threads) {
            thread.join();
        }

        return {_width, _height, pixels};
    }
} // namespace rt
