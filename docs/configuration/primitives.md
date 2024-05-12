---
title: Primitives
sidebar_position: 3
---

```cfg title="Primitives configuration example"
primitives:
(
    {
        lib = "raytracer_sphere.so";
        material = "red";
        origin = { x = 60.0; y = 40.0; z = 5.0; };
        radius = 25.0;
    },
    {
        lib = "raytracer_sphere.so";
        material = "green";
        origin = { x = -40.0; y = -10.0; z = 20.0; };
        radius = 35.0;
    },
    {
        lib = "raytracer_plane.so";
        material = "blue";
        origin = { x = 0.0; y = -20.0; z = 0.0; };
        direction = { x = 0.0; y = 1.0; z = 0.0; };
    }
);
```

### Mandatory fields for all primitive

- `lib`: Name of the shared library.
- `material`: name of the material.

### Optional fields for all primitive

- `transform`:
    - `scale`: Scale of the primitive.
        - `x`, `y`, `z`
    - `rotation`: Rotation of the primitive.
        - `x`, `y`, `z`
    - `translation`: Translation of the primitive.
        - `x`, `y`, `z`
    - `matrix`: Matrix of the primitive.
        - `m00`, `m01`, `m02`
        - `m10`, `m11`, `m12`
        - `m20`, `m21`, `m22`

### Specific fields for each default primitive

- `raytracer_cone.so`:
    - `origin`: Position of the cone.
        - `x`, `y`, `z`
    - `direction`: Direction of the cone.
        - `x`, `y`, `z`
    - `radius`: Radius of the cone.
    - `height`: Height of the cone.
- `raytracer_cylinder.so`:
    - `origin`: Position of the cylinder.
        - `x`, `y`, `z`
    - `direction`: Direction of the cylinder.
        - `x`, `y`, `z`
    - `radius`: Radius of the cylinder.
    - `height`: Height of the cylinder.
- `raytracer_plane.so`:
    - `origin`: Position of the plane.
        - `x`, `y`, `z`
    - `direction`: Direction of the plane.
        - `x`, `y`, `z`
- `raytracer_sphere.so`:
    - `origin`: Position of the sphere.
        - `x`, `y`, `z`
    - `radius`: Radius of the sphere.
- `raytracer_tetrahedron.so`:
    - `v0`: First vertex of the tetrahedron.
        - `x`, `y`, `z`
    - `v1`: Second vertex of the tetrahedron.
        - `x`, `y`, `z`
    - `v2`: Third vertex of the tetrahedron.
        - `x`, `y`, `z`
    - `v3`: Fourth vertex of the tetrahedron.
        - `x`, `y`, `z`
- `raytracer_triangle.so`:
    - `v0`: First vertex of the triangle.
        - `x`, `y`, `z`
    - `v1`: Second vertex of the triangle.
        - `x`, `y`, `z`
    - `v2`: Third vertex of the triangle.
        - `x`, `y`, `z`
