# VisualizationEngine

OpenGL-based visualization project for simulating and rendering CPG (Central Pattern Generator) driven lamprey movement.

The project includes procedural animation, segmented body movement, camera controls, shaders, and basic lighting.

---

# Setup & Dependencies

This project uses several third-party libraries for OpenGL rendering, math, window management, and image loading.  
To build and run the project correctly in Visual Studio, make sure all libraries are installed and all dependencies are configured properly.

---

## Required Libraries

The project uses:

- **GLFW** – window creation and input handling  
- **GLAD** – OpenGL function loader  
- **GLM** – mathematics library for vectors, matrices, transformations  
- **SOIL** (Simple OpenGL Image Library) – texture/image loading


## Project Structure

```text
VisualizationEngine/
│── OpenGL/
│   ├── OpenGL.cpp
│   ├── glad.c
│   ├── SOIL.c
│   ├── image_DXT.c
│   ├── image_helper.c
│   ├── stb_image_aug.c
│   └── shaders...
│
│── includes/
│   ├── glad/
│   ├── GLFW/
│   ├── glm/
│   └── SOIL/
