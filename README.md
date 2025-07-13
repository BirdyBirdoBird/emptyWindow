# 🧊 emptyWindow

A lightweight C++ OpenGL engine that renders procedurally generated voxel terrain — inspired by Minecraft-style chunk systems. Built using raw OpenGL and `FastNoiseLite`, this project demonstrates efficient terrain generation, block face culling, and chunk-based world rendering.

---

## 🚀 Features

- ✅ Chunk-based world system (16×16×16 blocks)
- ✅ Procedural terrain generation using `FastNoiseLite`
- ✅ Face culling to avoid rendering hidden block faces
- ✅ Dynamic loading and unloading of nearby chunks
- ✅ WASD + mouse camera control
- ✅ Texture atlas support

---

## 🛠️ Dependencies

| Library         | Purpose                           |
|------------------|-----------------------------------|
| OpenGL / GLFW    | Window and rendering context      |
| GLAD             | OpenGL function loader            |
| GLM              | Matrix and vector math            |
| FastNoiseLite    | Procedural noise (terrain height) |
| stb_image        | Texture loading (atlas)           |
| Eigen            | (Optional) Math utilities         |

## 🎮 Controls

| Key         | Action                   |
|--------------|----------------------------|
| `W A S D`    | Move forward/strafe        |
| Mouse        | Look around                |
| `Space`      | Move upward                |
| `Esc`        | Exit application           |

---

## 🔧 How to Build

> ⚠️ This project uses OpenGL and assumes you have GLFW, GLAD, and GLM installed.

### 1. Clone the repository
```bash
git clone https://github.com/BirdyBirdoBird/emptyWindow.git
cd emptyWindow
```

## 2. Set Up Dependencies

Make sure the following libraries are available in your environment:

| Dependency       | Purpose                           |
|------------------|------------------------------------|
| **GLFW**         | Window creation, input, context    |
| **GLAD**         | OpenGL function loader             |
| **GLM**          | Math for vectors and matrices      |
| **FastNoiseLite**| Terrain heightmap generation       |
| **stb_image.h**  | Texture atlas loading              |
| **Eigen**        | (Optional) math utilities          |

> You can install these using [vcpkg](https://github.com/microsoft/vcpkg) or include them manually.

---

## 3. Compile

### 🛠 Manual Compilation

If you're compiling manually:

- Add `glad.c` to your list of source files.
- Link against:
  - `opengl32`
  - `glfw3`
  - Any required system libs (e.g., `user32`, `gdi32` on Windows).

### 💼 Using an IDE

If you're using **Visual Studio** or **CLion**:

- Add all `.cpp` and `.h` files to the project.
- Set include directories for:
  - `glfw`, `glad`, `glm`, `stb`, and `FastNoiseLite`
- Link against OpenGL and GLFW.
- Build and run the executable.

---

## 🌍 How It Works

- Each chunk is a 16×16×16 grid of blocks stored in a 3D array.
- A heightmap from **FastNoiseLite** determines terrain shape.
- Only faces **not covered by adjacent blocks** are rendered (face culling).
- The `World` class:
  - Loads chunks near the camera
  - Removes distant chunks
  - Uses a `std::map` with `(x,z)` as keys
- As the player moves, new chunks are generated and rendered dynamically.

---

## 📸 Screenshots

> _(Add actual images or screenshots in the repo’s `assets/` folder and link them below)_

```markdown
![terrain screenshot](assets/terrain_demo.png)
