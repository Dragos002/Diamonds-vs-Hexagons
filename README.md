# Diamonds vs Hexagons

## :sparkles: What is this game ?

Diamonds vs Hexagons is a simplified verson of the popular game "Plants vs Zombies" which uses simple, minimal geomatrical froms.



## :rocket: Running

You can run the project from an IDE, as well as standalone, from anywhere on disk. For example:

-   Windows, one of the following:
    -   `.\bin\Debug\GFXFramework`
    -   or just open the `.sln` file in Visual Studio, then press `F5` to run it

-   Linux and macOS:
    -   `./bin/Debug/GFXFramework`

## :video_game: How is it played ?

Briefly, the game will unfold within the framework of 3 rows, each containing 3 columns. From the right side, enemies of the "bad" hexagon type appear at random intervals, traversing a line until reaching the left side of the screen. Once a hexagon crosses the entire line, the player loses a life. Upon losing 3 lives, the game is lost.

To combat the evil hexagons, the player has the option to place a saving diamond in one of the 3 cells on each row, which launches projectiles that move towards the right, along the row where the diamond that launched the projectile is placed. Upon encountering a hexagon, the projectile inflicts damage, and after 3 hits, the hexagon disappears, saving the situation temporarily.

However, the player faces 2 inconveniences. They cannot place as many diamonds as they want because each placed diamond costs a certain number of stars. These stars appear at random intervals on the stage, and the player must collect them. Additionally, each diamond can only harm a specific type of hexagon, based on the color of each hexagon.

## :book: Implementation
This game was created with an OpenGL framework provided by my university. In addition to the process of drawing shapes and placing each object in scene, two aspects of the implementation are noteworthy: the `drag & drop behavior` of the diamonds and the `collisions` between hexagons, diamonds, and projectiles. Diamonds can be placed in a square if the player has enough resources (stars). By left-clicking on one of the upper portion in the window, the player can select a diamond, which will then be rendered in all frames at the mouse coordinates until the left-click is released, in a valid position (a green square which is not occupied by other diamonds). Additionally, right-clicking a placed diamond can remove the diamond from the grid. The second aspect, regarding collisions, was implemented utilizing circles. In short, these circles provide an approximation of an object's shape: a disc whose center coincides with the object's center. This approach requires less processing power. Thus, this collision form is defined for projectiles, hexagons, and diamonds. The circles are not drawn on the screen; they are only used to create the game logic. To detect collision between two objects, the following steps must be followed:
1) Obtain the coordinates of the centers of the two objects.
2) Determine the radius of each circle.
3) Calculate the distance between the two centers.
4) Check if the distance is less than the sum of the radii of the circles.


