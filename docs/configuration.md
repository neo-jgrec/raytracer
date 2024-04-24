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
    resolution = { width = 1920; height = 1080; };
    position = { x = 0; y = -100; z = 20; };
    rotation = { x = 0; y = 0; z = 0; };
    fieldOfView = 72.0;
};

materials:
(
    { lib = "raytracer_uvcolor.so"; name = "red"; color = { r = 255; g = 64; b = 64; }; },
    { lib = "raytracer_uvcolor.so"; name = "green"; color = { r = 64; g = 255; b = 64; }; },
    { lib = "raytracer_uvcolor.so"; name = "blue"; color = { r = 64; g = 64; b = 255; }; }
);

# Primitives in the scene
primitives:
(
    { lib = "raytracer_sphere.so"; material = "red"; x = 60; y = 5; z = 40; r = 25; color = { r = 255; g = 64; b = 64; }; },
    { lib = "raytracer_sphere.so"; material = "red"; x = -40; y = 20; z = -10; r = 35; color = { r = 64; g = 255; b = 64; }; },
    { lib = "raytracer_plane.so"; material = "red"; axis = "Z"; position = -20; color = { r = 64; g = 64; b = 255; }; }
);

# Light configuration
lights:
{
    ambient = 0.4; # Multiplier of ambient light
    diffuse = 0.6; # Multiplier of diffuse light
    # List of point lights
    point = (
        { lib = "raytracer_light.so"; x = 400; y = 100; z = 500; }
    );
    # List of directional lights
    directional = ();
};
```

Here are all the field allowed per `shared library`:

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
