/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include <string>

#include "../Core/src/Parser/Parser.hpp"

namespace rt
{
    class IDisplay {
    public:
        class IDisplayException : public utils::Exception {
        public:
            IDisplayException(const std::string &name, const std::string &message) :
                Exception("[Display] " + name, message)
            {}
        };

        virtual void createWindow(const int &width, const int &height, const std::string &title) = 0;

        virtual void run(const rt::Parser &parser) = 0;

        virtual void destroyWindow() = 0;

    };
} // namespace rt

#endif /* !IDISPLAY_HPP_ */
