/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** APrimitive
*/

#ifndef APRIMITIVE_HPP
#define APRIMITIVE_HPP

#include "IPrimitive.hpp"

#include <libconfig.h++>
#include <vector>

namespace rt
{
    class APrimitive : public IPrimitive {
    private:
        IMaterial *_material = nullptr;

    protected:
        std::vector<math::Vector3<float>> _vertices;
        std::vector<math::Vector3<float>> _directions;

        void setVertices(const std::vector<math::Vector3<float>> &vertices) { _vertices = vertices; }
        void setDirections(const std::vector<math::Vector3<float>> &directions) { _directions = directions; }

    public:
        class APrimitiveException : public IPrimitiveException {
        public:
            APrimitiveException(const std::string &name, const std::string &message) :
                IPrimitiveException(name, message)
            {}
        };

        APrimitive(const std::vector<math::Vector3<float>> &vertices) : _vertices(vertices) {}
        APrimitive(const std::vector<math::Vector3<float>> &vertices,
                   const std::vector<math::Vector3<float>> &directions) :
            _vertices(vertices),
            _directions(directions)
        {}

        [[nodiscard]] float hit(const math::Ray &ray) const override = 0;
        [[nodiscard]] math::Vector3<float> getNormal(const math::Vector3<float> &point) const override = 0;

        void setMaterial(IMaterial *material) override { _material = material; }
        [[nodiscard]] IMaterial *getMaterial() const override { return _material; }

        void setTranslation(const math::Vector3<float> &translation) override
        {
            for (auto &vertex : _vertices)
                vertex += translation;
        }

        void setRotation(const math::Vector3<float> &rotation) override
        {
            const math::Vector3<float> rotationRad = rotation * (M_PI / 180);
            const std::vector<math::Vector3<float>> matrixRotation = {
                {std::cos(rotationRad.y) * std::cos(rotationRad.z),
                 std::sin(rotationRad.x) * std::sin(rotationRad.y) * std::cos(rotationRad.z) -
                     std::cos(rotationRad.x) * std::sin(rotationRad.z),
                 std::cos(rotationRad.x) * std::sin(rotationRad.y) * std::cos(rotationRad.z) +
                     std::sin(rotationRad.x) * std::sin(rotationRad.z)},
                {std::cos(rotationRad.y) * std::sin(rotationRad.z),
                 std::sin(rotationRad.x) * std::sin(rotationRad.y) * std::sin(rotationRad.z) +
                     std::cos(rotationRad.x) * std::cos(rotationRad.z),
                 std::cos(rotationRad.x) * std::sin(rotationRad.y) * std::sin(rotationRad.z) -
                     std::sin(rotationRad.x) * std::cos(rotationRad.z)},
                {-std::sin(rotationRad.y), std::sin(rotationRad.x) * std::cos(rotationRad.y),
                 std::cos(rotationRad.x) * std::cos(rotationRad.y)}};

            const auto originBefore = getOriginPoint();
            for (auto &vertex : _vertices) {
                const math::Vector3<float> tmp = vertex;
                vertex.x = tmp.x * matrixRotation[0].x + tmp.y * matrixRotation[1].x + tmp.z * matrixRotation[2].x;
                vertex.y = tmp.x * matrixRotation[0].y + tmp.y * matrixRotation[1].y + tmp.z * matrixRotation[2].y;
                vertex.z = tmp.x * matrixRotation[0].z + tmp.y * matrixRotation[1].z + tmp.z * matrixRotation[2].z;
            }
            setTranslation(originBefore - getOriginPoint());

            for (auto &direction : _directions) {
                const math::Vector3<float> tmp = direction;
                direction.x = tmp.x * matrixRotation[0].x + tmp.y * matrixRotation[1].x + tmp.z * matrixRotation[2].x;
                direction.y = tmp.x * matrixRotation[0].y + tmp.y * matrixRotation[1].y + tmp.z * matrixRotation[2].y;
                direction.z = tmp.x * matrixRotation[0].z + tmp.y * matrixRotation[1].z + tmp.z * matrixRotation[2].z;
            }
        }

        void setScale(const math::Vector3<float> &scale) override
        {
            for (auto &vertex : _vertices)
                vertex *= scale;
        }

        void setMatrix(const math::Vector3<math::Vector3<float>> &matrix) override
        {
            const auto originBefore = getOriginPoint();
            for (auto &vertex : _vertices) {
                const math::Vector3<float> tmp = vertex;
                vertex.x = tmp.x * matrix.x.x + tmp.y * matrix.y.x + tmp.z * matrix.z.x;
                vertex.y = tmp.x * matrix.x.y + tmp.y * matrix.y.y + tmp.z * matrix.z.y;
                vertex.z = tmp.x * matrix.x.z + tmp.y * matrix.y.z + tmp.z * matrix.z.z;
            }
            setTranslation(originBefore - getOriginPoint());

            for (auto &direction : _directions) {
                const math::Vector3<float> tmp = direction;
                direction.x = tmp.x * matrix.x.x + tmp.y * matrix.y.x + tmp.z * matrix.z.x;
                direction.y = tmp.x * matrix.x.y + tmp.y * matrix.y.y + tmp.z * matrix.z.y;
                direction.z = tmp.x * matrix.x.z + tmp.y * matrix.y.z + tmp.z * matrix.z.z;
            }
        }

        [[nodiscard]] math::Vector3<float> getOriginPoint() const override
        {
            math::Vector3<float> origin;

            for (const auto &vertex : _vertices)
                origin += vertex;
            return origin / static_cast<float>(_vertices.size());
        }

        void settingsTransform(const libconfig::Setting &setting)
        {
            try {
                setTranslation(math::Vector3{setting["transform"]["translation"]["x"].operator float(),
                                             setting["transform"]["translation"]["y"].operator float(),
                                             setting["transform"]["translation"]["z"].operator float()});
            } catch (libconfig::SettingNotFoundException &_) {
            }
            try {
                setRotation(math::Vector3{setting["transform"]["rotation"]["x"].operator float(),
                                          setting["transform"]["rotation"]["y"].operator float(),
                                          setting["transform"]["rotation"]["z"].operator float()});
            } catch (libconfig::SettingNotFoundException &_) {
            }
            try {
                setScale(math::Vector3{setting["transform"]["scale"]["x"].operator float(),
                                       setting["transform"]["scale"]["y"].operator float(),
                                       setting["transform"]["scale"]["z"].operator float()});
            } catch (libconfig::SettingNotFoundException &_) {
            }
            try {
                setMatrix(math::Vector3<math::Vector3<float>>{{setting["transform"]["matrix"][0].operator float(),
                                                               setting["transform"]["matrix"][1].operator float(),
                                                               setting["transform"]["matrix"][2].operator float()},
                                                              {setting["transform"]["matrix"][3].operator float(),
                                                               setting["transform"]["matrix"][4].operator float(),
                                                               setting["transform"]["matrix"][5].operator float()},
                                                              {setting["transform"]["matrix"][6].operator float(),
                                                               setting["transform"]["matrix"][7].operator float(),
                                                               setting["transform"]["matrix"][8].operator float()}});
            } catch (libconfig::SettingNotFoundException &_) {
            }
        }
    };
} // namespace rt

extern "C" {
    void destroy(const rt::IPrimitive *ptr) { delete ptr; }
}

#endif // APRIMITIVE_HPP
