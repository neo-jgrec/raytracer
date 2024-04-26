/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <libconfig.h++>
#include "../ICamera.hpp"

namespace rt
{
    class Camera final : public ICamera {
    private:
        math::Vector3<float> _origin;
        int _width = 256;
        int _height = 256;
        int _fov = 75;

        float _aspectRatio = 0;
        float _viewportHeight = 2.f;
        float _viewportWidth = 0;

        math::Vector3<float> _horizontal;
        math::Vector3<float> _vertical;
        math::Vector3<float> _bottomLeft;

        std::shared_ptr<uint8_t> _pixels{new uint8_t[_width * _height * 4], std::default_delete<uint8_t[]>()};

        void generateImageChunk(uint32_t startHeight, uint32_t endHeight, uint32_t startWidth, uint32_t endWidth,
                                const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                                const std::shared_ptr<uint8_t> &pixels, bool rgba) const;

    public:
        class CameraException final : public ICameraException {
        public:
            CameraException(const std::string &message) : ICameraException("Camera", message) {}
        };

        [[nodiscard]] std::pair<int, int> getResolution() const override { return {_width, _height}; }
        void setResolution(int width, int height) override;

        [[nodiscard]] const math::Vector3<float> &getOrigin() const override { return _origin; }
        void setOrigin(const math::Vector3<float> &origin) override { _origin = origin; }

        [[nodiscard]] int getFieldOfView() const { return _fov; }
        void setFieldOfView(const int fov) { _fov = fov; }

        void reload(bool rgba);
        std::tuple<int, int, std::shared_ptr<uint8_t>>
        generateImage(const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights, bool rgba) override;
    };
} // namespace rt

extern "C" {
    rt::ICamera *createComponent(const libconfig::Setting &camera)
    {
        auto *newCamera = new rt::Camera();

        newCamera->setOrigin(math::Vector3{static_cast<float>(camera["origin"]["x"].operator int()),
                                           static_cast<float>(camera["origin"]["y"].operator int()),
                                           static_cast<float>(camera["origin"]["z"].operator int())});
        newCamera->setResolution(camera["resolution"]["width"].operator int(),
                                 camera["resolution"]["height"].operator int());
        newCamera->setFieldOfView(camera["fieldOfView"].operator int());

        return newCamera;
    }

    void destroy(const rt::ICamera *ptr) { delete ptr; }
}

#endif /* !CAMERA_HPP_ */
