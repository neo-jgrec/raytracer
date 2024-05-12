---
title: Execution
sidebar_position: 3
---

To execute the raytracer, you need to run the following command:

```bash title="Run the raytracer"
./raytracer [scene.cfg]
```

The `scene.cfg` file is a configuration file that describes the scene to render. You can find examples in the `scenes` folder of the project.

Available flags:

- `-d`, `--display` The graphical plugin to use to display the image. e.g. libsfml.so
- `-h`, `--help`    Display this help message
- `-o`, `--output`  The output file that will contain the rendered image. e.g. image.ppm
- `-p`, `--preview` Display a preview of the image
