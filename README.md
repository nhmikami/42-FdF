# 42-FdF

The FdF (Fil de Fer) project aims to project a 3D map into a 2D screen using the MiniLibX library.

## Description

The program takes a file containing a grid of heights and translates it into a visual representation, allowing the user to interact with the map through keyboard and mouse controls.

**Features**
*   **Map reading:** reads a 3D map data from a `.fdf` file
*   **Projections:** implements different types of projections:
    *   Isometric
    *   Parallel
    *   Top
    *   Front
    *   Right
*   **User interaction:**
    *   **Zoom:** zoom in and out using the `+` and `-` keys or the mouse scroll wheel
    *   **Translation:** move the map using the arrow keys or dragging with the right mouse button
    *   **Rotation:** rotate the map around the X, Y, and Z axes using the `W`, `S`, `A`, `D`, `Q`, and `E` keys or dragging with the left mouse button
    *   **Projection switching:** switch between different projections using `I` (isometric), `P` (´parallel), `T` (top), `F` (front) and `R` (right) keys
*   **Color Interpolation:** implements color interpolation when drawing lines between points
*   **Menu:** displays an on-screen menu with keyboard and mouse controls

## MiniLibX

The MiniLibX library is a simple, lightweight graphics library developed for educational purposes. It provides a basic set of functions for creating graphical applications, drawing pixels, and handling events from user input.<br />

**Main functions**
*  `mlx_init`: initializes the connection between the program and the graphical system
*  `mlx_new_window`: creates a new window where the graphics will be displayed
*  `mlx_new_image`: allocates memory for a new image that can be drawn and manipulated before displaying it in the window
*  `mlx_get_data_addr`: obtains a pointer to the image's memory area where you can directly manipulate the pixel data, and other information about the image
*  `mlx_pixel_put`: draws a single pixel at the given coordinates with the specified color
*  `mlx_put_image_to_window`: displays an image in the specified window at the given coordinates
*  `mlx_string_put`: puts a string of text on the window at the specified coordinates
*  `mlx_hook`: sets up callback functions to handle events in the window, such as key press and mouse movement
*  `mlx_loop`: enters an infinite loop that detects events and refreshes the window as needed

Useful links: [documentation](https://github.com/42Paris/minilibx-linux)   |   [manual](https://harm-smits.github.io/42docs/libs/minilibx)
