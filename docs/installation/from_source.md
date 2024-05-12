---
title: From source
sidebar_position: 1
---

## Dependencies

For this project, you will need the following dependencies:
- `liconfig++` for the configuration file.
- `sfml2.5.1` for the graphical interface (only needed by the `raytracer_sfml` library).
- `imgui` for the graphical interface (only needed by the `raytracer_sfml` library).
- `imgui-sfml` for the graphical interface (only needed by the `raytracer_sfml` library).

## Using the tools at your disposal

```bash
git clone git@github.com:neo-jgrec/raytracer.git
git submodule update --init --recursive
cd raytracer
./build_me.sh
./arcade [configuration_file_path]
```

## If you want to do everything manually

:::warning
If you want to do everything manually, you will need to meet one requirement in your *build environment*.
The shared libraries must be in a folder named `lib` in the same directory as the executable.
:::

With that aside, you can compile the project using `cmake` or your favorite compiler.

Finally, you can run the project with the following command:

```bash
./arcade [configuration_file_path]
```

---

:::note
Read the documentation to understand how it works.
Especially the [Configuration](/category/configuration) section to give proper configuration to the raytracer.
:::
