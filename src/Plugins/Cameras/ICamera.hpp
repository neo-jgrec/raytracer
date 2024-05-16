/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** ICamera
*/

#ifndef ICAMERA_HPP_
#define ICAMERA_HPP_

#include <list>

#include "../../Core/src/Images/Images.hpp"
#include "../Lights/ILight.hpp"
#include "../Primitives/IPrimitive.hpp"

namespace rt
{
    class ICamera {
    public:
        class ICameraException : public utils::Exception {
        public:
            ICameraException(const std::string &name, const std::string &message) :
                Exception("[Camera] " + name, message)
            {}
        };

        virtual ~ICamera() = default;

        [[nodiscard]] virtual std::pair<int, int> getResolution() const = 0;
        virtual void setResolution(int width, int height) = 0;

        [[nodiscard]] virtual const math::Vector3<float> &getOrigin() const = 0;
        virtual void setOrigin(const math::Vector3<float> &origin) = 0;

        [[nodiscard]] virtual const math::Vector3<float> &getDirection() const = 0;
        virtual void setDirection(const math::Vector3<float> &direction) = 0;

        [[nodiscard]] virtual int getFieldOfView() const = 0;
        virtual void setFieldOfView(int fov) = 0;

        virtual void drawImage(const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                               const IImage &image) = 0;
        virtual void asyncDrawImage(const std::list<IPrimitive *> &primitives, const std::list<ILight *> &lights,
                                    const IImage &image) = 0;
        virtual void awaitDrawImage() = 0;
    };
} // namespace rt

#endif /* !ICAMERA_HPP_ */
