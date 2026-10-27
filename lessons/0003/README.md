# Generating Asteroids

Our jet is lonely out in deep space. Let's throw a bunch of asteroids at it. By 
the end of this lesson, you should be able to create a window like this:

![Asteroids!](asteroids.gif "Asteroids")

Note that our asteroids are represented by grey rectangles. Later, we will make them
prettier. Also, the asteroid won't do any damage to the jet yet. We will do that next
lesson. 

## Asteroids!

Start by adding some scaffolding code to represent Asteroids. First add a NUM_ASTEROID
macro below your other `#define` statements:

```c
// Other define statements
#define NUM_ASTEROIDS 10
```
Now add the code following code below the initial Jet code
and fill in the TODO items in the comments:

```c
typedef struct Asteroid { // defines the Asteroid struct
    Vector2 position;
    int exists;
} Asteroid;

// TODO define a `const Vector2` called ASTEROID_SIZE similar to JET_SIZE.
    // I made mine the same size as JET_SIZE, but you are welcome to use a different size.

// TODO define a `const float` called ASTEROID_SPEED similar to jet_speed.
    // I recommend being merciful by making the asteroids move slower than the jet.

Asteroid asteroids[NUM_ASTEROIDS]; // declares an array of Asteroids
```

This code (1) defines an `Asteroid` struct, (2) sets the size and speed for all
Asteroids, and (3) declares an array of Asteroids. 

While our game is running, we will populate this array with Asteroids randomly.
We will use the `exists` flag in `Asteroid` to indicate whether or not that
`Asteroid` is currently populated. Asteroids that fly off the screen
will no longer "exist" in this context. 1 means an `Asteroid` exists, 0 means it does not. 

## Initializing asteroids

Now, we need to initialize our `asteroids`. When we declared `asteroids`, we told C that
there will be an array of `NUM_ASTEROIDS` Asteroids. But we didn't tell it what the values
in that array should be. In particular, the `exists` flag for each asteroid should be 
either 1 or 0. We need to make sure that is true by setting all `exists` values to 0
before we start the game. Add this code to your `main` function after 
`SetWindowFocused();`:

```c
while (!IsWindowReady()) {} // already there
SetWindowFocused(); // already there

// make sure that no asteroids exist at game start
for (int i = 0; i < NUM_ASTEROIDS; i++) {
    asteroids[i].exists = 0;
}
```
This is a [for loop](https://www.w3schools.com/c/c_for_loop.php). It (1) sets `int i` to 0,
(2) runs until `i` is no longer less than `NUM_ASTEROIDS`, and (3) increases `i` by 1
after each iteration. 

So `i` takes the values 0, 1, 2, ..., 9 during the loop. The loop body sets `exists` to
0 (false) for each asteroid. `asteroids[0]` refers to the first asteroid because
arrays in C are "0-indexed". That means that the index 0 refers to the first element. 
So an array with 10 elements will have indexes 0, 1, 2, ..., 9. 

## Drawing One Asteroid
Now we know that none of our asteroids exist. Let's make the first asteroid,
`asteroid[0]`, exist in a specific location and draw it. 

Define a function called `maybe_generate_asteroid` like so: 

```c
void maybe_generate_asteroid() {
    if (!asteroids[0].exists) {
        asteroids[0].exists = 1;
        asteroids[0].position.x = (SCREEN_WIDTH / 2 - ASTEROID_SIZE.x);
        asteroids[0].position.y = (SCREEN_HEIGHT / 2 - ASTEROID_SIZE.y);
        return;
    }
}
```

This function currently generates the first asteroid if it doesn't exist. 
Later, we will make it generate all the asteroids in random locations.

Now call `maybe_generate_asteroid` from your render loop. Also add the code to
draw `asteroid[0]` if it exists like so:

```c
    while (!WindowShouldClose()) {
        handle_movement();
        set_jet_vertices();
        maybe_generate_asteroid(); // add this line


        BeginDrawing();
            // ... other code ...

            // add these lines // // // // // // // // // // // // // // // // // // // //
            if (asteroids[0].exists) {
                DrawRectangleV(asteroids[0].position, ASTEROID_SIZE, GRAY);
            }
            // // // // // // // // // // // // // // // // // // // // // // // // // //

        EndDrawing();
    }
```

This should give you a window that has a stationary asteroid and a movable jet.

![One Asteroid!](one_asteroid.png "One Asteroid")

## Moving the Asteroid
Now, if it exists, we want to move the asteroid downward towards our fearless pilot. 
When it reaches the end of the screen, we want to cause it to no longer exists. 
That way, we can generate it again and continue endangering our hero. 

Define a function called `step_asteroids` like so and fill in the code for 
the TODO items.

```c
void step_asteroids() {
    if (asteroids[0].exists) {
        // TODO increase asteroids[0]'s y position by ASTEROID_SPEED.
        if (asteroids[0].position.y > SCREEN_HEIGHT) {
            // TODO make asteroids[0] no longer exist.
        }
    }
}
```

Once you've done the TODO items, call `step_asteroids` below `maybe_generate_asteroid`.

```c
    // ... other code ...
    maybe_generate_asteroid(); 
    step_asteroids();
    // ... other code ...
```

Now you should see the asteroid moving down off the screen and immediately reappearing 
continuiously. 

## Randomly Generating One Asteroid
Now, we don't want the asteroid to simply appear in the middle of the screen. 
Instead, we want it to start at a random `x` position. And we also want it to move
into view from the top of the screen. 

To do the random x position, we will use random number generation. The
built-in `rand` function in C's stdlib (included at the top) generates a
number between 0 and RAND_MAX. Therefore, if we do the following:

```c
r = rand() / (double)RAND_MAX;
```

Then `r` will be a random number between 0 and 1. Moreover, `r * SCREEN_WIDTH` would be 
a number between 0 and `SCREEN_WIDTH`. We can use this to make `asteroids[0]` appear in
a random `x` position each time it generates.

First, we have to set the random seed using the current time. Add this line to the top
of your main function:

```c
int main(void) {
    srand((unsigned)time(NULL)); // add this line
    // ... other code ...
}
```

Now in `maybe_generate_asteriod`, add these lines and fill in the TODO items:

```c
void maybe_generate_asteroid() {
    double r; // add this
    if (!asteroids[0].exists) {
        r = rand() / (double)RAND_MAX; 
        asteroids[0].exists = 1;
        // TODO: set asteroid[0].position.x to be a random number between 
        //  0 and (SCREEN_WIDTH - ASTEROID_SIZE.x)
        //
        //  Thought Question: why do we want to subtract ASTEROID_SIZE.x
        //  from screen width here?

        // TODO: set asteroid[0].position.y so that the asteroid starts
        // just off the screen at the top. 
        //
        //  Hint 1: y = 0 is the top of the screen.
        //  Hint 2: y can be negative.

        return; // This return statement is irreelevant now. We will want it later
        // when we turn this into a loop.
    }
}
```

Now when you run the program, the asteroid should slide into the screen from the top
and appear in a random `x` position each time it generates. 

## Generating All Asteroids

Our game will not be very fun with only one asteroid. We need more danger! 
Now we are going to make our code operate on all asteroids. 

Before you read on -- STOP! You may already be able to figure out how to do this.
If you think you can, try to figure it out before reading below. Otherwise, here is a hint. 

### Hint:
You already saw code before that loops through all asteroids and makes sure they 
don't exist. In your main function, you have this code:

```c
for (int i = 0; i < NUM_ASTEROIDS; i++) {
    asteroids[i].exists = 0;
}
```

You simply need to apply the same thing to any code that refers to `asteroids[0]`. 
Add the for loop above the code, indent the code an additional level, and add
a curly bracket at the end to close the loop. Then change `asteroids[0]` to `asteroids[i]`.

Now you should see 10 asteroids generating almost all at once. When they reach the end of the
screen, they should immediately reappear at the top. It is likely that some will overlap.
That's okay for now. We can improve the generation logic later to prevent overlaps. 

Thought Question: Why are the asteroids slightly offset?

## Desyncronizing Asteroid Generation
Next we want to prevent the asteroids from generating all at once. To do that
we will use random number generation again. Add this macro definition to
your `#define` section at the top:

```c
#define ASTEROID_GEN_COEFF .05
```

This stands for Asteroid Generation Coefficient. This will be interpreted as:
"The probability that an asteroid will generate in a given frame assuming that 
there is at least one asteroid which does not exist." So `.05` means we have
a 5% probability of generating a new asteroid each frame (as long as one does not
exist). 

Now in `maybe_generate_asteroid`, add these two lines:

```c
if (!asteroids[i].exists) { // already exists
    r = rand() / (double)RAND_MAX; // add this line
    if (r > ASTEROID_GEN_COEFF) return; // add this line
    r = rand() / (double)RAND_MAX; // already exists

    // ... other code ...
}
```

This will cause an asteroid to generate only if `r` less than or equal to 
`ASTEROID_GEN_COEFF`. If `r` is greater, the `return` statement will immediately
exit the function. 

Now you should see asteroids generating like the gif at the top. 

Try playing around with the values for `NUM_ASTEROIDS` and `ASTEROID_GEN_COEFF`
to see what happens. But don't make `NUM_ASTEROIDS` too large or you may
crash your game.

[<-- Previous Lesson](../0002/README.md)  
[Next Lesson -->](../0004/README.md)  
[Back to Index](../../README.md)
