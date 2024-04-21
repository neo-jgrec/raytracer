/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DLLoader
*/

#ifndef ARCADE_DLLOADER_HPP
    #define ARCADE_DLLOADER_HPP

    #include <iostream>
    #include <dlfcn.h>
    #include <string>
    #include <memory>

namespace utils
{
    enum LibraryType {
        LIGHT     = 0,
        MATERIAL  = 1,
        PRIMITIVE = 2,
        CAMERA    = 3,
        PARSER    = 4,
        DISPLAY   = 5,
    };

    template <typename T>
    class DLLoader {
    private:
        std::shared_ptr<void> _lib = nullptr;
        T *_instance = nullptr;

    public:
        DLLoader(const LibraryType type, const std::string &path)
        {
            _lib = std::shared_ptr<void>(dlopen(path.c_str(), RTLD_LAZY), [](void *lib) { dlclose(lib); });
            if (!_lib)
                throw std::runtime_error(dlerror());

            void *getType = dlsym(_lib.get(), "getType");
            if (!getType)
                throw std::runtime_error(dlerror());
            const LibraryType libType = reinterpret_cast<LibraryType (*)()>(getType)();
            if (libType != type)
                throw std::runtime_error("Invalid library type");

            void *constructor = dlsym(_lib.get(), "create");
            if (!constructor)
                throw std::runtime_error(dlerror());

            _instance = reinterpret_cast<T *(*)()>(constructor)();
        }

        ~DLLoader() noexcept(false)
        {
            void *destructor = dlsym(_lib.get(), "destroy");
            if (!destructor)
                throw std::runtime_error(dlerror());
            reinterpret_cast<void (*)(T *)>(destructor)(_instance);
        }

        [[nodiscard]] T *get() const
        {
            return _instance;
        }

        void *operator[](const std::string &symbol) const
        {
            return dlsym(_lib.get(), symbol.c_str());
        }
    };
}


#endif //ARCADE_DLLOADER_HPP