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
### **GLFW (v3.3+)**
*   **Purpose:** Window creation and input event handling.
*   **Official Site:** [glfw.org](https://www.glfw.org/)

###  **GLAD**
*   **Purpose:** Multi-Language GL Loader (OpenGL 3.3 Core Profile).
*   **Note:** The `glad.c` file **must** be compiled as part of your source files.

### **GLM (OpenGL Mathematics)** 
*Version 0.9.9+ Recommended*

###  **stb_image.h**
*   **Purpose:** Header-only library for texture loading.
*   **Implementation:** Ensure `#define STB_IMAGE_IMPLEMENTATION` is included in your main `.cpp` file.

---



## Project Structure

```text
VisualizationEngine/
│── OpenGL/
│   ├── OpenGL.cpp
│   └── shaders...
│
│── includes/
│   ├── glad/
│   ├── GLFW/
│   ├── glm/
│   └── stb_image.h
