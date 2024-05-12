---
title: Lights
sidebar_position: 4
---

```cfg title="Lights configuration example"
lights:
(
    {
        lib = "raytracer_ambientlight.so";
        color = { r = 255; g = 255; b = 255; };
        intensity = 0.4;
    },
    {
        lib = "raytracer_pointlight.so";
        origin = { x = 400; y = 500; z = 100; };
        color = { r = 255; g = 255; b = 255; };
        intensity = 0.6;
    },
);
```

### Mandatory fields for all lights

- `lib`: Name of the shared library.

### Specific fields for each default light

- `raytracer_ambientlight.so`:
    - `color`: Color of the light.
        - `r`, `g`, `b`
    - `intensity`: Intensity of the light.

- `raytracer_pointlight.so`:
    - `origin`: Position of the light.
        - `x`, `y`, `z`
    - `color`: Color of the light.
        - `r`, `g`, `b`
    - `intensity`: Intensity of the light.

- `raytracer_directionallight.so`:
    - `origin`: Position of the light.
        - `x`, `y`, `z`
    - `direction`: Direction of the light.
        - `x`, `y`, `z`
    - `color`: Color of the light.
        - `r`, `g`, `b`
    - `intensity`: Intensity of the light.
