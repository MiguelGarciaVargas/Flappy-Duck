# Flappy Duck

**Flappy Duck** is a game inspired by the popular "Flappy Bird," developed as the final project for the Computer Graphics course. The primary goal of the project was to strengthen object-oriented programming skills, learn C++ programming, and explore 3D graphics using GLFW.

## 🎮 Game Mechanics

1. **Duck Flight:**
   - The player controls the duck by pressing the "SPACE" key, which makes the duck fly in a parabolic trajectory. The duck remains fixed on the X-axis, and its height changes along the Y-axis.

2. **Watermelon Collection:**
   - The player must collect watermelons scattered throughout the map. The watermelons move from the right side of the screen to the left at a constant speed. Once collected, they respawn at random heights after a short delay.

3. **Collision with Pipes:**
   - The main objective, aside from collecting watermelons, is to avoid colliding with the pipes. The pipes move from right to left and appear both at the top and bottom of the screen. Their length and appearance are randomized to keep the player on edge. If the duck hits a pipe, the game ends, and the duck turns into a roasted duck.

## 🛠️ Features and Design

- **3D Object Representation:**
  - The game uses PLY and OBJ file formats for representing 3D objects like the duck, pipes, and watermelons. PLY files store geometric data, and OBJ files include vertex, texture, and material information.
  
- **Collision Detection:**
  - The game implements bounding boxes for each 3D object to detect collisions. These boxes are used to check interactions between the duck, pipes, and watermelons.

- **Animations:**
  - The game uses linear motion for the pipes and watermelons, and a parabolic movement for the duck. Animation functions such as `Animation::line()` and `Animation::bezier()` handle these movements.

## 📊 Class Structure

- **Vertex**: Represents a point in 3D space.
- **Edge**: Defines a line segment between two vertices.
- **Face**: Made up of edges to form polygons.
- **Object**: Base class representing 3D objects.
- **Obj & Ply**: Subclasses for reading OBJ and PLY file formats, respectively.
- **BoundariesBox**: Manages collision detection between objects.
- **Duck, Pipe, Watermelon**: Represent game entities, each with methods for movement and collision handling.

## 🚧 Challenges and Solutions

1. **Collision Management:**
   - The primary challenge was ensuring the duck could collide with pipes to end the game and collect watermelons to increase the score. The solution was implementing bounding boxes that move dynamically with the objects.

2. **Object Localization:**
   - Adjusting the position of objects in 3D space required modifications in Blender to ensure accurate bounding box generation.

3. **Watermelon Timer:**
   - A timer was implemented using `glfwGetTime()` to introduce a delay between watermelon respawns.

4. **Compatibility with OBJ Files:**
   - The game was initially built for PLY files, and OBJ file integration presented challenges with collision detection. Using PLY files provided a more stable experience.

## 📖 User Manual

You can consult the complete **User Manual (in spanish)** at the following link:

[User Manual - Flappy Duck](https://drive.google.com/file/d/1rEjJKhexnvGWZUxIk4asbWqtFgcmxeuo/view?usp=sharing)

## 📷 Screenshots

- **Duck and Pipe Model:**  
  ![Duck & Pipe](https://github.com/user-attachments/assets/6de189cc-f12a-420d-920e-7c00163d64d1)
  
- **Watermelon and DuckCollided Model:**  
  ![Watermelon & DuckCollided](https://github.com/user-attachments/assets/361a3d1e-629f-40b2-9998-dabd97e0dacc)




