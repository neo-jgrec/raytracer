/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Images
*/

#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <cstring>
#include <iostream>
#include <memory>

#include "../../../Utils/Utils.hpp"

class IImage {
public:
    virtual ~IImage() = default;

    [[nodiscard]] virtual std::pair<uint32_t, uint32_t> getSize() const = 0;
    [[nodiscard]] virtual std::shared_ptr<uint8_t> getPixels() const = 0;

    virtual void setSize(const std::pair<uint32_t, uint32_t> &size) = 0;
    virtual void setPixel(uint32_t x, uint32_t y, const utils::Color &color) const = 0;
};

class AImage : public IImage {
protected:
    std::pair<uint32_t, uint32_t> _size;
    std::shared_ptr<uint8_t> _pixels;

public:
    explicit AImage(const std::pair<uint32_t, uint32_t> &size) : _size(size) {}

    [[nodiscard]] std::pair<uint32_t, uint32_t> getSize() const override { return _size; }
    [[nodiscard]] std::shared_ptr<uint8_t> getPixels() const override { return _pixels; }
};

class ImageRGB final : public AImage {
public:
    ImageRGB(const std::pair<uint32_t, uint32_t> &size) : AImage({size.first, size.second})
    {
        _pixels =
            std::shared_ptr<uint8_t>(new uint8_t[_size.first * _size.second * 3], std::default_delete<uint8_t[]>());
        std::memset(_pixels.get(), 0, _size.first * _size.second * 3);
    }

    void setSize(const std::pair<uint32_t, uint32_t> &size) override
    {
        _size = size;
        _pixels =
            std::shared_ptr<uint8_t>(new uint8_t[_size.first * _size.second * 3], std::default_delete<uint8_t[]>());
        std::memset(_pixels.get(), 0, _size.first * _size.second * 3);
    }
    void setPixel(const uint32_t x, const uint32_t y, const utils::Color &color) const override
    {
        const int index = static_cast<int>(y * 3 * _size.first + x * 3);
        _pixels.get()[index] = static_cast<uint8_t>(255.999f * color.r);
        _pixels.get()[index + 1] = static_cast<uint8_t>(255.999f * color.g);
        _pixels.get()[index + 2] = static_cast<uint8_t>(255.999f * color.b);
    }
};

class ImageRGBA final : public AImage {
public:
    ImageRGBA(const std::pair<uint32_t, uint32_t> &size) : AImage({size.first, size.second})
    {
        _pixels =
            std::shared_ptr<uint8_t>(new uint8_t[_size.first * _size.second * 4], std::default_delete<uint8_t[]>());
        std::memset(_pixels.get(), 0, _size.first * _size.second * 4);
    }

    void setSize(const std::pair<uint32_t, uint32_t> &size) override
    {
        _size = size;
        _pixels =
            std::shared_ptr<uint8_t>(new uint8_t[_size.first * _size.second * 4], std::default_delete<uint8_t[]>());
        std::memset(_pixels.get(), 0, _size.first * _size.second * 4);
    }
    void setPixel(const uint32_t x, const uint32_t y, const utils::Color &color) const override
    {
        const int index = static_cast<int>(y * 4 * _size.first + x * 4);
        _pixels.get()[index] = static_cast<uint8_t>(255.999f * color.r);
        _pixels.get()[index + 1] = static_cast<uint8_t>(255.999f * color.g);
        _pixels.get()[index + 2] = static_cast<uint8_t>(255.999f * color.b);
        _pixels.get()[index + 3] = static_cast<uint8_t>(255.999f * color.a);
    }
};

#endif // IMAGES_HPP
