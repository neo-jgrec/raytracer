/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** Parser
*/

#include "Parser.hpp"

#include <filesystem>
#include <functional>
#include <iostream>
#include <libconfig.h++>
#include <string>

namespace rt
{
    Parser::~Parser()
    {
        delete _camera;
        for (const auto &material : _materials) {
            delete material.second;
        }
        for (const auto &primitive : _primitives) {
            delete primitive;
        }
        for (const auto &light : _lights) {
            delete light;
        }
    }

    std::string Parser::getLibPathFromMainBinary(const std::string &path)
    {
        const std::string binaryPath = std::filesystem::read_symlink("/proc/self/exe");
        const std::string binaryDir = std::filesystem::path(binaryPath).parent_path();
        std::string finalPath = binaryDir + "/lib/" + path;

        return finalPath;
    }

    void Parser::parseCamera(libconfig::Setting &camera)
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

    void Parser::parseMaterials(const libconfig::Setting &materials)
    {
        for (auto& material : materials) {
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

    void Parser::parsePrimitives(const libconfig::Setting &primitives)
    {
        for (auto& primitive : primitives) {
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
                reinterpret_cast<IPrimitive *(*)(const libconfig::Setting &, IMaterial *)>(primitiveLoaders.back().get());
            if (createComponent == nullptr)
                throw std::runtime_error("Failed to load primitive component");

            _primitives.emplace_back(createComponent(static_cast<const libconfig::Setting &>(primitive), usedMaterial));
        }
    }

    void Parser::parseLights(const libconfig::Setting &lights)
    {
        for (auto& light : lights) {
            try {
                lightLoaders.emplace_back(getLibPathFromMainBinary(light["lib"]), "createComponent");
            } catch (const utils::DLLoader<ILight>::DLLoaderException &e) {
                throw ParserExecption("Invalid path", light["lib"]);
            }

            const std::function createComponent =
                reinterpret_cast<ILight *(*)(const libconfig::Setting &)>(lightLoaders.back().get());
            if (createComponent == nullptr)
                throw ParserExecption("Failed to load light component");

            _lights.emplace_back(createComponent(static_cast<const libconfig::Setting &>(light)));
        }
    }

    Parser *Parser::parseScene(const std::string &path)
    {
        const std::string abs_path = std::filesystem::absolute(path);

        try {
            libconfig::Config cfg;
            cfg.readFile(abs_path);

            const libconfig::Setting &root = cfg.getRoot();
            parseCamera(root["camera"]);
            parseMaterials(root["materials"]);
            parsePrimitives(root["primitives"]);
            parseLights(root["lights"]);

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

        return this;
    }
} // namespace rt
