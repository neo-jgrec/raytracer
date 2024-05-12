---
title: Add new features
sidebar_position: 6
---

The raytracer project is a work in progress. Here how to add your own features to the project.

:::note
You only can add new types of Camera, Light, Material, Primitive and Display.
:::

For each type, you need to create a new shared library that implements the corresponding interface and abstract class.
You can directly implement them aside from the default implementations provided in the project.
To be able to use your new feature, the shared library must be placed in the `lib` folder of the project.

:::warning
The implementation of a new primitive requires to use the constructor of the abstract class `APrimitive` to set the vertices of the primitive (and the directions if needed).
This is needed to be able to compute transformations on the primitive.
:::

You also need to create extern functions to create and destroy the object of your new type.
