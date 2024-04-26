/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** ICamera
*/

#ifndef ICAMERA_HPP_
#define ICAMERA_HPP_

#include <list>

#include "../Plugins/Lights/ILight.hpp"
#include "../Plugins/Primitives/IPrimitive.hpp"

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

        virtual std::tuple<int, int, std::shared_ptr<uint8_t>> generateImage(std::list<IPrimitive *> primitives,
                                                                             std::list<ILight *> lights) = 0;
    };
} // namespace rt

#endif /* !ICAMERA_HPP_ */
