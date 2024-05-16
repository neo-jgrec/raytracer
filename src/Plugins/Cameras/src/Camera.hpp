/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "../ICamera.hpp"

#include <libconfig.h++>
#include <thread>

namespace rt
{
    class Camera final : public ICamera {
    private:
        math::Vector3<float> _origin;
        math::Vector3<float> _direction{0, 0, -1};
        int _width = 256;
        int _height = 256;
        int _fov = 75;

        float _aspectRatio = 0;
        float _viewportHeight = 2.f;
        float _viewportWidth = 0;

        math::Vector3<float> _horizontal;
        math::Vector3<float> _vertical;
        math::Vector3<float> _bottomLeft;

        std::list<std::jthread> _threads;

        void reload();
        void drawChunk(const std::pair<uint32_t, uint32_t> &coord, const std::pair<uint32_t, uint32_t> &size,
                       const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                       const IImage &image);

    public:
        class CameraException final : public ICameraException {
        public:
            CameraException(const std::string &message) : ICameraException("Camera", message) {}
        };

        [[nodiscard]] std::pair<int, int> getResolution() const override { return {_width, _height}; }
        void setResolution(int width, int height) override;

        [[nodiscard]] const math::Vector3<float> &getOrigin() const override { return _origin; }
        void setOrigin(const math::Vector3<float> &origin) override { _origin = origin; }

        [[nodiscard]] const math::Vector3<float> &getDirection() const override { return _direction; }
        void setDirection(const math::Vector3<float> &direction) override { _direction = direction; }

        [[nodiscard]] int getFieldOfView() const override { return _fov; }
        void setFieldOfView(const int fov) override { _fov = fov; }

        void drawImage(const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                       const IImage &image) override;
        void asyncDrawImage(const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                            const IImage &image) override;
        void awaitDrawImage() override;
    };
} // namespace rt

extern "C" {
    rt::ICamera *createComponent(const libconfig::Setting &camera)
    {
        auto *newCamera = new rt::Camera();

        newCamera->setOrigin(math::Vector3{static_cast<float>(camera["origin"]["x"].operator int()),
                                           static_cast<float>(camera["origin"]["y"].operator int()),
                                           static_cast<float>(camera["origin"]["z"].operator int())});
        newCamera->setDirection(math::Vector3{static_cast<float>(camera["direction"]["x"].operator int()),
                                              static_cast<float>(camera["direction"]["y"].operator int()),
                                              static_cast<float>(camera["direction"]["z"].operator int())});
        newCamera->setResolution(camera["resolution"]["width"].operator int(),
                                 camera["resolution"]["height"].operator int());
        newCamera->setFieldOfView(camera["fieldOfView"].operator int());

        return newCamera;
    }
}

#endif /* !CAMERA_HPP_ */
