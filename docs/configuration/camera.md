---
title: Camera
sidebar_position: 1
---

```cfg title="Camera configuration example"
camera:
{
    lib = "raytracer_camera.so";
    resolution = { width = 1920; height = 1080; };
    origin = { x = 0; y = 20; z = -100; };
    direction = { x = 0; y = 0; z = 1; };
    fieldOfView = 72;
};
```

### Mandatory fields for all cameras

- `lib`: Name of the shared library.

### Specific fields for each default camera

- `raytracer_camera.so`:
    - `origin`: Position of the camera.
        - `x`, `y`, `z`
    - `direction`: Direction of the camera.
        - `x`, `y`, `z`
    - `resolution`: Resolution of the camera.
        - `width`, `height`
    - `fieldOfView`: Field of view of the camera.
