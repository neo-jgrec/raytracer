---
title: Configuration
sidebar_position: 2
---

To configure a raytracer scene, you need to create a `.cfg`, here's a sample that can be found in the `scenes` folder:

```cfg title="default.cfg"
# Configuration of the camera
camera:
{
    lib = "raytracer_camera.so";
    origin = { x = 0; y = 0; z = 1; };
    resolution = { width = 3840; height = 2160; };
    fieldOfView = 75;
};

materials:
(
    { lib = "raytracer_flatcolor.so"; name = "red";   color = { r = 255; g = 64; b = 64; }; },
    { lib = "raytracer_flatcolor.so"; name = "green"; color = { r = 64; g = 255; b = 64; }; },
    { lib = "raytracer_flatcolor.so"; name = "blue";  color = { r = 64; g = 64; b = 255; }; },
    { lib = "raytracer_uvcolor.so";   name = "uv"; },
);

# Primitives in the scene
primitives:
(
    { lib = "raytracer_sphere.so"; material = "blue"; x = -1; y = 0; z = 0; r = 0.5  },
    { lib = "raytracer_sphere.so"; material = "red";  x = 0;  y = 0; z = 0; r = 0.65 },
    { lib = "raytracer_sphere.so"; material = "blue"; x = 1;  y = 0; z = 0; r = 0.5  },
);

# Light configuration
lights:
(
    {
        lib = "raytracer_directionallight.so";
        origin = { x = -1; y = -1; z = 0; };
        direction = { x = 0; y = -1; z = -1; };
        color = { r = 0; g = 0; b = 0; };
        intensity = 1.0;
    },
);
```

Here are all the mandatory fields for each `shared library`:

- `raytracer_camera.so`:
    - `resolution`: Resolution of the image.
    - `position`: Position of the camera.
    - `rotation`: Rotation of the camera.
    - `fieldOfView`: Field of view of the camera
- `raytracer_uvcolor.so`:
    - `color`: Color of the material.
- `raytracer_sphere.so`:
    - `material`: Material of the sphere.
    - `x`, `y`, `z`: Position of the sphere.
    - `r`: Radius of the sphere.
    - `color`: Color of the sphere.
- `raytracer_plane.so`:
    - `material`: Material of the plane.
    - `axis`: Axis of the plane.
    - `position`: Position of the plane.
    - `color`: Color of the plane.
