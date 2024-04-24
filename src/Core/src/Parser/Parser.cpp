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

using namespace rt;

std::string Parser::getLibPathFromMainBinary(const std::string &path)
{
    std::string binaryPath = std::filesystem::read_symlink("/proc/self/exe");
    std::string binaryDir = std::filesystem::path(binaryPath).parent_path();
    std::string finalPath = binaryDir + "/lib/" + path;

    return finalPath;
}

void Parser::parseCamera(libconfig::Setting &camera)
{
    cameraLoaders.emplace_back(getLibPathFromMainBinary(camera["lib"]), "createComponent");
    std::function<ICamera *(libconfig::Setting &)> createComponent = reinterpret_cast<ICamera *(*)(libconfig::Setting &)>(cameraLoaders.back().get());

    if (createComponent == nullptr)
        throw std::runtime_error("Failed to load camera component");

    _camera = createComponent(camera);
    cameraLoaders.back().setPointer(_camera);
}

void Parser::parseMaterials(libconfig::Setting &materials)
{
    for (int i = 0; i < materials.getLength(); i++) {
        std::string materialName = static_cast<std::string>(materials[i]["name"]);
        bool materialExists = false;

        for (const auto& name : materialLoadersNames) {
            if (name == materialName) {
                materialExists = true;
                break;
            }
        }
        if (materialExists)
            throw std::runtime_error("Material with the same name already exists: " + materialName);

        try {
            materialLoaders.emplace_back(getLibPathFromMainBinary(materials[i]["lib"]), "createComponent");
            materialLoadersNames.emplace_back(materialName);
        } catch (const utils::DLLoader<IMaterial>::DLLoaderException &e) {
            std::cerr << e.what() << std::endl;
            continue;
        }
        std::function<IMaterial *(libconfig::Setting &)> createComponent;
        try {
            createComponent = reinterpret_cast<IMaterial *(*)(libconfig::Setting &)>(materialLoaders.back().get());
        } catch (const std::out_of_range &e) {
            throw std::runtime_error("Material not found: " + materialName);
        }

        if (createComponent == nullptr)
            throw std::runtime_error("Failed to load material component");

        _materials.emplace(materialName, createComponent(materials[i]));
        materialLoaders.back().setPointer(_materials.at(materialName));
    }
}

void Parser::parsePrimitives(libconfig::Setting &primitives)
{
    for (int i = 0; i < primitives.getLength(); i++) {
        IMaterial *usedMaterial = nullptr;

        try {
            usedMaterial = _materials.at(static_cast<std::string>(primitives[i]["material"]));
        } catch (const std::out_of_range &e) {
            throw std::runtime_error("Material not found: " + static_cast<std::string>(primitives[i]["material"]));
        }

        try {
            primitiveLoaders.emplace_back(getLibPathFromMainBinary(primitives[i]["lib"]), "createComponent");
        } catch (const utils::DLLoader<IPrimitive>::DLLoaderException &e) {
            std::cerr << e.what() << std::endl;
            continue;
        }
        std::function<IPrimitive *(libconfig::Setting &, IMaterial *)> createComponent = reinterpret_cast<IPrimitive *(*)(libconfig::Setting &, IMaterial *)>(primitiveLoaders.back().get());

        if (createComponent == nullptr)
            throw std::runtime_error("Failed to load primitive component");

        _primitives.emplace_back(createComponent(primitives[i], usedMaterial));
        primitiveLoaders.back().setPointer(_primitives.back());
    }
}

Parser *Parser::parseScene(const std::string &path)
{
    libconfig::Config cfg;
    std::string abs_path = std::filesystem::absolute(path);

    try {
        cfg.readFile(abs_path);
        libconfig::Setting &root = cfg.getRoot();
        parseCamera(root["camera"]);
        parseMaterials(root["materials"]);
        parsePrimitives(root["primitives"]);
        std::cout << "Scene parsed successfully" << std::endl;
    } catch(const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file: " << fioex.what() << std::endl;
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting not found: " << nfex.getPath() << std::endl;
    } catch(const libconfig::SettingTypeException &stex) {
        std::cerr << "Setting type error: " << stex.getPath() << std::endl;
    } catch(const std::exception &e) {
        std::cerr << "ERROR : " << e.what() << std::endl;
    }

    return this;
}
