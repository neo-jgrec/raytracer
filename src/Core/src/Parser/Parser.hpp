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
    #include "../../../Plugins/Primitives/IPrimitive.hpp"
    #include "../../../Plugins/Materials/IMaterial.hpp"
    // #include "../../Plugins/Lights/ILight.hpp"

namespace rt {
    class Parser {
        public:
            Parser() = default;
            ~Parser() {};

            rt::ICamera *getCamera(void) { return _camera; }
            std::list<rt::IPrimitive *> getPrimitives(void) { return _primitives; }
            // std::list<rt::ILight *> getLights(void) { return _lights; }

            Parser *parseScene(const std::string &path);

            private:
                static std::string getLibPathFromMainBinary(const std::string &path);

                void parseCamera(libconfig::Setting &camera);
                void parsePrimitives(libconfig::Setting &primitives);
                void parseMaterials(libconfig::Setting &materials);
                // void parseLights(libconfig::Setting &lights);

                rt::ICamera *_camera{};
                std::list<rt::IPrimitive *> _primitives;
                // std::list<rt::ILight *> _lights;

                std::map<std::string, rt::IMaterial *> _materials;

                std::list<utils::DLLoader<ICamera>> cameraLoaders;
                std::list<utils::DLLoader<IPrimitive>> primitiveLoaders;
                // std::vector<utils::DLLoader<ILight>> lightLoaders;

                std::list<std::string> materialLoadersNames;
                std::list<utils::DLLoader<IMaterial>> materialLoaders;
    };
}

#endif /* !PARSER_HPP_ */