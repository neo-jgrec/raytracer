/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DLLoader
*/

#ifndef ARCADE_DLLOADER_HPP
#define ARCADE_DLLOADER_HPP

#include <dlfcn.h>
#include <memory>
#include <string>

#include "Exceptions.hpp"

namespace utils
{
    template <typename T>
    class DLLoader {
    private:
        std::shared_ptr<void> _lib = nullptr;
        T *_instance = nullptr;

        T *_ptr = nullptr;

    public:
        class DLLoaderException final : public Exception {
        public:
            DLLoaderException(const std::string &message) : Exception("DLLoader", message) {}
        };

        DLLoader(const std::string &path, const std::string &symbol)
        {
            _lib = std::shared_ptr<void>(dlopen(path.c_str(), RTLD_LAZY),
                                         [](void *lib)
                                         {
                                             if (lib)
                                                 dlclose(lib);
                                         });
            if (!_lib)
                throw DLLoaderException(dlerror());

            void *constructor = dlsym(_lib.get(), symbol.c_str());
            if (!constructor)
                throw std::runtime_error(dlerror());

            _instance = reinterpret_cast<T *>(constructor);
        }

        ~DLLoader()
        {
            if (!_ptr)
                return;
            void *destructor = dlsym(_lib.get(), "destroy");
            if (destructor)
                reinterpret_cast<void (*)(const T *)>(destructor)(_ptr);
        }

        [[nodiscard]] T *get() const { return _instance; }

        void setPointer(T *ptr) { _ptr = ptr; }

        void *operator[](const std::string &symbol) const { return dlsym(_lib.get(), symbol.c_str()); }
    };
} // namespace utils


#endif // ARCADE_DLLOADER_HPP
