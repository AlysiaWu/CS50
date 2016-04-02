//
// breakout.c
// Andy Davies
//
// CS50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle dimensions (todo no.1)
#define PAD_HEIGHT 7
#define PAD_WIDTH 70

// brick dimensions (todo no.3)
#define BRICKHEIGHT 10
#define BRICKWIDTH 30

// ball dimensions
#define BALLSIZE 20

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

// my prototypes
void paddleMove(GRect paddle);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    
    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initial ball velocity
    double xvelocity = 2.0 * drand48();  
    double yvelocity = 2.0;  
    
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // update scoreboard
        updateScoreboard(window, label, points);
        
        // paddle movement
        paddleMove(paddle);
        
        // ball movement
        // basic movement
        move(ball, xvelocity, yvelocity); 
    
        // bounce off edges or lose life if bottom
        // getX(ball) <= 0 used instead of == because drand48 causes the ball
        // to 'skip over' 0
        if (getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }
        if (getY(ball) == 0)
        {
            yvelocity = -yvelocity;
        }
        
        // lose life when hit bottom
        if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            lives--;
            waitForClick();
            setLocation(ball, WIDTH / 2, HEIGHT / 2);
        }
        
        // control speed
        pause(10); 
        
        // detect for collision with paddle/brick
        GObject collidewith = detectCollision(window, ball);
        if (collidewith != NULL)
        {
            if (strcmp(getType(collidewith), "GRect") == 0)
            {
                yvelocity = -yvelocity;
                
                if (collidewith != paddle) // remove bricks
                {
                    removeGWindow(window, collidewith);
                    points++;
                }
            }
        }
             
    }

    // wait for click before exiting
    // waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // initialise bricks
    int i, j, xpos, ypos;
    for (j = 0, ypos = 30; j < ROWS; j++, ypos += 15)
    {
        for (i = 0, xpos = 30; i < COLS; i++, xpos += 35)
        {
            GRect brick = newGRect(xpos, ypos, BRICKWIDTH, BRICKHEIGHT);
            if (j % 2 == 0)
            {
                setColor(brick, "red");                 
            }
            else
            {
                setColor(brick, "blue");
            }
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // initialise ball 
    GOval ball = newGOval(WIDTH / 2, HEIGHT / 2, BALLSIZE, BALLSIZE);
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // implement initPaddle
    GRect paddle = newGRect(170, 550, PAD_WIDTH, PAD_HEIGHT);
    setColor(paddle, "black");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
* My paddle movement function
*/
void paddleMove(GRect paddle)
{
    // check for mouse event
    GEvent event = getNextEvent(MOUSE_EVENT);

    // if we heard one
    if (event != NULL)
    {
        // if the event was movement
        if (getEventType(event) == MOUSE_MOVED)
        {
            // ensure paddle follows cursor
            double x = getX(event) - getWidth(paddle) / 2;
            setLocation(paddle, x, 550);
        }
    }    
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate scoreboard
    GLabel label = newGLabel("0");
    setLocation(label, WIDTH / 2, HEIGHT / 2);
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
