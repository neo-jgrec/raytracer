/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Main
*/

#include <cstddef>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <tuple>

#include "Raytracer.hpp"

class CommandLineParser {
public:
    CommandLineParser(const int argc, char **argv) { args.assign(argv, argv + argc); }

    void addOption(const std::string &longOpt, const std::string &shortOpt, const std::string &description)
    {
        options[longOpt] = std::make_tuple(shortOpt, description, std::nullopt);
    }

    void parse()
    {
        for (std::size_t i = 1; i < args.size(); ++i) {
            if (args[i][0] != '-')
                continue;
            std::string option = args[i];
            std::string argument;

            bool optionFound = false;
            for (const auto &[fst, snd] : options) {
                if (option == fst || std::get<0>(snd) == option) {
                    option = (fst == option) ? option : (std::get<0>(snd) == option) ? fst : option;
                    if (i + 1 < args.size() && args[i + 1][0] != '-') {
                        argument = args[i + 1];
                        ++i;
                    }
                    optionFound = true;
                    break;
                }
            }

            if (!optionFound)
                throw std::runtime_error("Unknown option: " + option);

            options[option] = std::make_tuple(std::get<0>(options[option]), std::get<1>(options[option]), argument);
        }
    }

    [[nodiscard]] std::optional<std::string> getOption(const std::string &longOpt) const
    {
        if (!options.contains(longOpt))
            return std::nullopt;
        return std::get<2>(options.at(longOpt));
    }

    void displayHelp(const std::string &binaryName) const
    {
        std::cout << "Usage: " << binaryName << " [scene.cfg]\n";
        for (const auto &[fst, snd] : options) {
            std::string longOpt = fst;
            std::string shortOpt = std::get<0>(snd);
            std::string description = std::get<1>(snd);
            std::cout << " ";
            if (!shortOpt.empty())
                std::cout << std::setw(2) << shortOpt << ", ";
            std::cout << std::setw(10) << std::left << longOpt << " [";
            if (!description.empty())
                std::cout << description;
            std::cout << "]\n";
        }
    }

private:
    std::vector<std::string> args;
    std::map<std::string, std::tuple<std::string, std::string, std::optional<std::string>>> options;
};

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv);
    parser.addOption("--output", "-o", "The output file that will contain the rendered image. e.g. image.ppm");
    parser.addOption("--display", "-d", "The graphical plugin to use to display the image. e.g. libsfml.so");
    parser.addOption("--preview", "-p", "Display a preview of the image");
    parser.addOption("--help", "-h", "Display this help message");

    try {
        parser.parse();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    if (parser.getOption("--help") != std::nullopt) {
        parser.displayHelp(argv[0]);
        return 0;
    }

    std::string sceneName;

    if (argc > 1) {
        sceneName = argv[1];
    } else {
        std::cerr << "No scene provided\n";
        return 84;
    }

    std::string saveAs = parser.getOption("--output").value_or("");
    std::string graphicalPlugin = parser.getOption("--display").value_or("");
    bool preview = parser.getOption("--preview").has_value();

    std::cout << "Scene: " << sceneName << std::endl;
    std::cout << "Save as: " << (saveAs.empty() ? "No output" : saveAs) << std::endl;
    std::cout << "Graphical plugin: " << (graphicalPlugin.empty() ? "No graphical plugin" : graphicalPlugin)
              << std::endl;
    std::cout << "Preview: " << std::boolalpha << preview << std::endl;

    try {
        rt::Raytracer raytracer(sceneName, saveAs, graphicalPlugin, preview);
        raytracer.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
