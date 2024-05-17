/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>

#include "../../IDisplay.hpp"

namespace rt
{
    class ImageTexture final : public AImage {
    private:
        sf::Texture _texture;
        std::unique_ptr<sf::Uint8[]> _pixels;

    public:
        ImageTexture(const std::pair<uint32_t, uint32_t> &size) : AImage(size)
        {
            _texture.create(size.first, size.second);
            _pixels = std::make_unique<sf::Uint8[]>(size.first * size.second * 4);
        }

        void setSize(const std::pair<uint32_t, uint32_t> &size) override
        {
            _size = size;
            _texture.create(size.first, size.second);
            _pixels = std::make_unique<sf::Uint8[]>(size.first * size.second * 4);
        }
        void setPixel(const uint32_t x, const uint32_t y, const utils::Color &color) override
        {
            const auto index = y * _size.first + x;
            _pixels[index * 4] = static_cast<sf::Uint8>(255.999f * color.r);
            _pixels[index * 4 + 1] = static_cast<sf::Uint8>(255.999f * color.g);
            _pixels[index * 4 + 2] = static_cast<sf::Uint8>(255.999f * color.b);
            _pixels[index * 4 + 3] = 255;
        }

        [[nodiscard]] sf::Texture &getTexture() { return _texture; }
        void updateTexture() { _texture.update(_pixels.get()); }
    };

    class SFML final : public IDisplay {
    private:
        sf::RenderWindow _window;

    public:
        SFML(uint32_t width = 800, uint32_t height = 600, const std::string &title = "Raytracer");
        ~SFML() override;

        void run(std::shared_ptr<Scene> parser) override;
    };

    extern "C" {
        IDisplay *create_display(const uint32_t width, const uint32_t height, const std::string &title)
        {
            return new SFML{width, height, title};
        }

        void destroy(const SFML *display) { delete display; }
    }
} // namespace rt

#endif /* !SFML_HPP_ */
