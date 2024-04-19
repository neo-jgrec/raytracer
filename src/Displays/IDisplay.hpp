/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Arch]
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include <string>
#include "../Camera/ICamera.hpp"

class IDisplay {
    public:
        IDisplay();
        ~IDisplay();

        class DisplayExeption : public std::exception {
            public:
                DisplayExeption(std::string const &message);
                const char *what() const noexcept override;

            private:
                std::string _message;
        };

        virtual void createWindow() = 0;
        virtual void destroyWindow() = 0;
        virtual void displayWindow() = 0;
        virtual void clearWindow() = 0;
        virtual void sendCamera(ICamera *camera) = 0;

    protected:
    private:
};

#endif /* !IDISPLAY_HPP_ */
