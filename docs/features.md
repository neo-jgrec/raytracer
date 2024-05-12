---
title: Features
sidebar_position: 4
---

Here are the asked features of the raytracer project:

### Must

- Primitives:
    - [x] Sphere
    - [x] Plane

- Transformations:
    - [x] Translation

- Light:
    - [x] Directional light
    - [x] Ambient light

- Material:
    - [x] Flat color

- Scene configuration:
    - [x] Add primitives to scene
    - [x] Setup lighting
    - [x] Setup camera

- Interface:
    - [x] No GUI, output to a PPM file

### Should

- Primitives:
    - [x] Cylinder
    - [x] Cone
- Transformations:
    - [x] Rotation
- Light:
    - [x] Dropshadows

### Could

- Primitives:
    - [x] Limited cylinder (0.5)
    - [x] Limited cone (0.5)
    - [ ] Torus (1)
    - [ ] Tanglecube (1)
    - [x] Triangles (1)
    - [ ] .OBJ file (1)
    - [ ] Fractals (2)
    - [ ] Möbius strip (2)
- Transformations:
    - [x] Scale (0.5)
    - [ ] Shear (0.5)
    - [ ] Transformation matrix (2)
    - [ ] Scene graph (2)
- Light:
    - [x] Multiple directional lights (0.5)
    - [x] Multiple point lights (1)
    - [x] Colored light (0.5)
    - [ ] Phong reflection model (2)
    - [ ] Ambient occlusion (2)
- Material:
    - [ ] Transparency (0.5)
    - [ ] Refraction (1)
    - [ ] Reflection (0.5)
    - [ ] Texturing from file (1)
    - [ ] Texturing from procedural generation of chessboard (1)
    - [ ] Texturing from procedural generation of Perlin noise (1)
    - [ ] Normal mapping (2)
- Scene configuration:
    - [x] Import a scene in a scene (2)
    - [ ] Setup antialiasing through supersampling (0.5)
    - [ ] Setup antialiasing through adaptive supersampling (1)
- Optimizations:
    - [ ] Space partitioning (2)
    - [x] Multithreading (1)
    - [ ] Clustering (3)
- Interface:
    - [x] Display the image during and after generation (1)
    - [ ] Exit during or after generation (0.5)
    - [x] Scene preview using a basic and fast renderer (2)
    - [ ] Automatic reload of the scene at file change (1)
