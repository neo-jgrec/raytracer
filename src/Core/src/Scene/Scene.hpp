/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** ComponentFactory
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <filesystem>
#include <functional>
#include <iostream>
#include <libconfig.h++>
#include <map>

#include "../../../Cameras/ICamera.hpp"

namespace rt
{
    class Scene {
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

        std::list<std::string> importedScenes;

        static std::string getLibPathFromMainBinary(const std::string &path)
        {
            const std::string binaryPath = std::filesystem::read_symlink("/proc/self/exe");
            const std::string binaryDir = std::filesystem::path(binaryPath).parent_path();
            std::string finalPath = binaryDir + "/lib/" + path;

            return finalPath;
        }

        void parseCamera(libconfig::Setting &camera)
        {
            try {
                cameraLoaders.emplace_back(getLibPathFromMainBinary(camera["lib"]), "createComponent");
            } catch (const utils::DLLoader<ICamera>::DLLoaderException &e) {
                throw ParserExecption("Invalid path", camera["lib"]);
            }

            const std::function createComponent =
                reinterpret_cast<ICamera *(*)(libconfig::Setting &)>(cameraLoaders.back().get());
            if (createComponent == nullptr)
                throw ParserExecption("Failed to load camera component");

            _camera = createComponent(camera);
        }

        void parseMaterials(const libconfig::Setting &materials)
        {
            for (auto &material : materials) {
                auto materialName = static_cast<std::string>(material["name"]);

                for (const auto &name : materialLoadersNames)
                    if (name == materialName)
                        throw ParserExecption("Material with the same name already exists", materialName);

                try {
                    materialLoaders.emplace_back(getLibPathFromMainBinary(material["lib"]), "createComponent");
                    materialLoadersNames.emplace_back(materialName);
                } catch (const utils::DLLoader<IMaterial>::DLLoaderException &e) {
                    throw ParserExecption("Invalid path", material["lib"]);
                }

                const auto createComponent =
                    reinterpret_cast<IMaterial *(*)(const libconfig::Setting &)>(materialLoaders.back().get());
                if (createComponent == nullptr)
                    throw ParserExecption("Failed to load material component");

                _materials.emplace(materialName, createComponent(static_cast<const libconfig::Setting &>(material)));
            }
        }

        void parsePrimitives(const libconfig::Setting &primitives)
        {
            for (auto &primitive : primitives) {
                IMaterial *usedMaterial;

                try {
                    usedMaterial = _materials.at((primitive["material"]));
                } catch (const std::out_of_range &) {
                    throw ParserExecption("Material not found", primitive["material"]);
                }

                try {
                    primitiveLoaders.emplace_back(getLibPathFromMainBinary(primitive["lib"]), "createComponent");
                } catch (const utils::DLLoader<IPrimitive>::DLLoaderException &e) {
                    throw ParserExecption("Invalid path", primitive["lib"]);
                }

                std::function createComponent =
                    reinterpret_cast<IPrimitive *(*)(const libconfig::Setting &, IMaterial *)>(
                        primitiveLoaders.back().get());
                if (createComponent == nullptr)
                    throw ParserExecption("Failed to load primitive component");

                _primitives.emplace_back(createComponent(primitive, usedMaterial));
            }
        }

        void parseLights(const libconfig::Setting &lights)
        {
            for (auto &light : lights) {
                try {
                    lightLoaders.emplace_back(getLibPathFromMainBinary(light["lib"]), "createComponent");
                } catch (const utils::DLLoader<ILight>::DLLoaderException &e) {
                    throw ParserExecption("Invalid path", light["lib"]);
                }

                const std::function createComponent =
                    reinterpret_cast<ILight *(*)(const libconfig::Setting &)>(lightLoaders.back().get());
                if (createComponent == nullptr)
                    throw ParserExecption("Failed to load light component");

                _lights.emplace_back(createComponent(light));
            }
        }

        void parseImports(const libconfig::Setting &imports)
        {
            for (int i = 0; i < imports.getLength(); ++i) {
                std::string importPath = imports[i];
                std::cout << "Importing scene from " << importPath << std::endl;

                if (std::find(importedScenes.begin(), importedScenes.end(), importPath) != importedScenes.end())
                    std::cerr << "Scene already imported (" << importPath << ")" << std::endl;

                importedScenes.emplace_back(importPath);

                try {
                    libconfig::Config cfg;
                    cfg.readFile(importPath);
                    const libconfig::Setting &root = cfg.getRoot();

                    ComponentFactory parserMap(this);
                    for (auto &parser : parserMap.parsers) {
                        if (root.exists(parser.first))
                            parser.second(root[parser.first]);
                    }

                } catch (const libconfig::FileIOException &fioex) {
                    throw ParserExecption("I/O error", fioex.what());
                } catch (const libconfig::ParseException &pex) {
                    throw ParserExecption("Parse error",
                                          std::string(pex.getError()) + " at line " + std::to_string(pex.getLine()));
                } catch (const libconfig::SettingNotFoundException &nfex) {
                    throw ParserExecption("Setting not found", nfex.getPath());
                } catch (const libconfig::SettingTypeException &stex) {
                    throw ParserExecption("Setting type error", stex.getPath());
                } catch (const std::exception &e) {
                    throw ParserExecption("Unknown error", e.what());
                }
            }
        }

        class ComponentFactory {
        public:
            std::map<std::string, std::function<void(libconfig::Setting &)>> parsers;

            ComponentFactory(Scene *scene)
            {
                parsers["imports"] = [scene](libconfig::Setting &imports) { scene->parseImports(imports); };
                parsers["camera"] = [scene](libconfig::Setting &camera) { scene->parseCamera(camera); };
                parsers["materials"] = [scene](libconfig::Setting &materials) { scene->parseMaterials(materials); };
                parsers["primitives"] = [scene](libconfig::Setting &primitives) { scene->parsePrimitives(primitives); };
                parsers["lights"] = [scene](libconfig::Setting &lights) { scene->parseLights(lights); };
            }
        };

    public:
        class ParserExecption final : public utils::Exception {
        public:
            ParserExecption(const std::string &message) : Exception("[Parser] ", message) {}
            ParserExecption(const std::string &name, const std::string &message) :
                Exception("[Parser] " + name, message)
            {}
        };

        [[nodiscard]] ICamera *getCamera() const { return _camera; }
        std::list<IPrimitive *> getPrimitives() { return _primitives; }
        std::list<ILight *> getLights() { return _lights; }

        ~Scene()
        {
            for (auto primitive : _primitives)
                delete primitive;
            _primitives.clear();

            for (auto light : _lights)
                delete light;
            _lights.clear();
        }

        Scene(const std::string &path)
        {
            const std::string abs_path = std::filesystem::absolute(path);

            try {
                libconfig::Config cfg;
                cfg.readFile(abs_path);
                const libconfig::Setting &root = cfg.getRoot();

                ComponentFactory parserMap(this);
                for (auto &parser : parserMap.parsers) {
                    if (root.exists(parser.first))
                        parser.second(root[parser.first]);
                }

                std::cout << "Primitives: " << _primitives.size() << std::endl;
                std::cout << "Lights: " << _lights.size() << std::endl;
                std::cout << "Materials: " << _materials.size() << std::endl;
                std::cout << "Camera: " << _camera << std::endl;
                std::cout << "Scene parsed successfully" << std::endl;
            } catch (const libconfig::FileIOException &fioex) {
                throw ParserExecption("I/O error", fioex.what());
            } catch (const libconfig::ParseException &pex) {
                throw ParserExecption("Parse error",
                                      std::string(pex.getError()) + " at line " + std::to_string(pex.getLine()));
            } catch (const libconfig::SettingNotFoundException &nfex) {
                throw ParserExecption("Setting not found", nfex.getPath());
            } catch (const libconfig::SettingTypeException &stex) {
                throw ParserExecption("Setting type error", stex.getPath());
            } catch (const std::exception &e) {
                throw ParserExecption("Unknown error", e.what());
            }
        }
    };
} // namespace rt

#endif /* !PARSER_HPP_ */
