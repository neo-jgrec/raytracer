---
title: Materials
sidebar_position: 2
---

```cfg title="Materials configuration example"
materials:
(
    { lib = "raytracer_flatcolor.so"; name = "red";   color = { r = 255; g = 64; b = 64; }; },
    { lib = "raytracer_flatcolor.so"; name = "green"; color = { r = 64; g = 255; b = 64; }; },
    { lib = "raytracer_flatcolor.so"; name = "blue";  color = { r = 64; g = 64; b = 255; }; }
);
```

### Mandatory fields for all materials

- `lib`: Name of the shared library.
- `name`: Name of the material.

### Specific fields for each default material

- `raytracer_flatcolor.so`:
    - `color`: Color of the material.
        - `r`, `g`, `b`

- `raytracer_uvcolor.so`:
