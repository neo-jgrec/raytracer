/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DLLoader
*/

#ifndef ARCADE_DLLOADER_HPP
    #define ARCADE_DLLOADER_HPP

    #include <dlfcn.h>
    #include <string>
    #include <memory>

    #include "Exceptions.hpp"

namespace utils
{
    template <typename T>
    class DLLoader {
    private:
        std::shared_ptr<void> _lib = nullptr;
        T *_instance = nullptr;

    public:
        class DLLoaderException final : public Exception {
        public:
            DLLoaderException(const std::string &message) :
                Exception("DLLoader", message) {}
        };

        DLLoader(const std::string &path, const std::string &symbol)
        {
            _lib = std::shared_ptr<void>(dlopen(path.c_str(), RTLD_LAZY), [](void *lib) {
                if (lib)
                    dlclose(lib);
            });
            if (!_lib)
                throw DLLoaderException(dlerror());

            void *constructor = dlsym(_lib.get(), symbol.c_str());
            if (!constructor)
                throw std::runtime_error(dlerror());

            _instance = reinterpret_cast<T*>(constructor);
        }

        ~DLLoader() {}

        [[nodiscard]] T *get() const
        {
            return _instance;
        }

        void destroy()
        {
            void *destructor = dlsym(_lib.get(), "destroy");
            if (!destructor)
                throw DLLoaderException(dlerror());
            reinterpret_cast<void (*)(T *)>(destructor)(_instance);
        }

        void *operator[](const std::string &symbol) const
        {
            return dlsym(_lib.get(), symbol.c_str());
        }
    };
}


#endif //ARCADE_DLLOADER_HPP
