# Adding a Jet
Now, instead of "Hello, World!", we are going to add a jet that you can 
move around using the arrow keys or WASD on your keyboard. 

By the end of this lesson, you should be able to create a window like this:

![Triangle Jet](hello_raylib.png "A Triangle Jet")

## The Jet Variable
The first thing we need to define is a `struct` and global variable called `Jet` and `jet`. 
`Jet` will be a `struct` with 4 (x, y) points: a position and 3 triangle
vertices. Raylib uses `Vector2` to represent an (x, y) point. 
In `raylib.h`, you can see the definition of `Vector2` below. 

```c
typedef struct Vector2 {
    float x;                // Vector x component
    float y;                // Vector y component
} Vector2;
```

Add these lines below your `#define` statements and above `main`. 

```c
typedef struct Jet {
    Vector2 position;
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;
} Jet;

Jet jet = (Jet){ 
    .position = (Vector2){ 100, 100 }
};
```

This tells C that we will have a `Vector2` variable called `jet`. Since we
declared it outside of `main`, it is called a global variable, meaning we can
access it from anywhere in our program. We set the initial position to (100, 100).
Later you can change the initial position and see what happens.

Notice that the Jet struct also contains Vector2 variables v1, v2, and v3. We will use
these later to make the jet a triangle. 

## Drawing the Jet as a Rectangle
We will start by drawing our jet as a rectangle. In [raylib.h](../../raylib/include/raylib.h),
find the `DrawRectangleV` function. The definition is as follows:

```c
RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  // Draw a color-filled rectangle (Vector version)
```

