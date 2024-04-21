/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "../ICamera.hpp"

namespace rt
{
    class Camera final : public ICamera {
    private:
        int _width = 256;
        int _height = 256;

        float _aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
        float _viewportHeight = 2.f;
        float _viewportWidth = _aspectRatio * _viewportHeight;
        float _focalLength = 1.f;

        math::Vector3<float> _origin{0, 0, 0};
        math::Vector3<float> _horizontal{_viewportWidth, 0, 0};
        math::Vector3<float> _vertical{0, _viewportHeight, 0};
        math::Vector3<float> _bottomLeft = _origin - _horizontal / 2 - _vertical / 2 - math::Vector3<float>{
            0, 0, _focalLength
        };

        [[nodiscard]] static utils::Color getBackgroundPixel(const math::Vector3<float> &direction);
        static void writePixel(const utils::Color &color);

    public:
        void setOrigin(const math::Vector3<float> &origin) override;

        void generateImage(std::list<IPrimitive *> primitives) override;
    };;
} // namespace rt

#endif /* !CAMERA_HPP_ */