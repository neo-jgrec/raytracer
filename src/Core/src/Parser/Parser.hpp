/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** ComponentFactory
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <libconfig.h++>
#include <map>

#include "../../../Cameras/ICamera.hpp"

namespace rt
{
    class Parser {
    private:
        ICamera *_camera{};
        std::list<IPrimitive *> _primitives;
        std::list<ILight *> _lights;

        std::map<std::string, IMaterial *> _materials;

        std::list<utils::DLLoader<ICamera>> cameraLoaders;
        std::list<utils::DLLoader<IPrimitive>> primitiveLoaders;
        std::list<utils::DLLoader<ILight>> lightLoaders;

        std::list<std::string> materialLoadersNames;
        std::list<utils::DLLoader<IMaterial>> materialLoaders;

        static std::string getLibPathFromMainBinary(const std::string &path);

        void parseCamera(libconfig::Setting &camera);
        void parsePrimitives(const libconfig::Setting &primitives);
        void parseMaterials(const libconfig::Setting &materials);
        void parseLights(const libconfig::Setting &lights);

    public:
        class ParserExecption final : public utils::Exception {
        public:
            ParserExecption(const std::string &message) : Exception("[Parser] ", message) {}
            ParserExecption(const std::string &name, const std::string &message) :
                Exception("[Parser] " + name, message)
            {}
        };

        ~Parser();

        [[nodiscard]] ICamera *getCamera() const { return _camera; }
        std::list<IPrimitive *> getPrimitives() { return _primitives; }
        std::list<ILight *> getLights() { return _lights; }

        Parser *parseScene(const std::string &path);
    };
} // namespace rt

#endif /* !PARSER_HPP_ */
