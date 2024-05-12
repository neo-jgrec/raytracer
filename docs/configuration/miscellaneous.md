---
title: Miscellaneous
sidebar_position: 6
---

You can import scenes from other configuration files using the `imports` field. This is useful for reusing common configurations across multiple scenes.

:::warning
Cameras can't be imported.
:::

```cfg title="Miscellaneous configuration example"
imports:
(
    "scenes/sphere.cfg",
);
```
