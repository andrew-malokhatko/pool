#include "mylib.h"
#include "list.h"
#include "ball.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>


const double WINDOW_WIDTH = 900;
const double WINDOW_HEIGHT = 900;


// constants & stuff
float speed = 250;
float projectile_speed = 600;
int radius = 100;
float gravity = 70;
int projectile_mass = 3;
bool gameOver = false;


List balls = {NULL, 0, 0};

Ball ball1;
Ball ball2;

// Key states
bool keyA = false;
bool keyD = false;

void reshapeWindow(int width, int height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
} 

void draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    ListNode* current = balls.head;
    while (current)
    {
        Ball* ball = (Ball*)current->data;
        ball_draw(ball);

        current = current->next;
    }

    glutSwapBuffers();
}

// On key down
void handleKeyboard(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A') keyA = true;
    if (key == 'd' || key == 'D') keyD = true;
}

// On key release
void handleKeyboardUp(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A') keyA = false;
    if (key == 'd' || key == 'D') keyD = false;
}

// On mouse clicked
void mouseClick(int button, int state, int x, int y)
{
    y = WINDOW_HEIGHT - y; // Invert y coordinate
    Vector2 mousePos = {x, y};

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        
    }
}


void update(int deltaTime)
{
    if (gameOver)
    {
        return;
    }

    float dt = (float)deltaTime / 1000;

    ListNode* current = balls.head;
    while (current)
    {
        Ball* ball = (Ball*)current->data;

        ball_update(ball, dt, WINDOW_WIDTH, WINDOW_HEIGHT);

        current = current->next;
    }
    
    current = balls.head;
    while (current->next)
    {
            
        Ball* ball = (Ball*)current->data;
        Ball* nextBall = (Ball*)current->next->data;
        
        handle_collisions(ball, nextBall);
        
        current = current->next;
    }
    
    glutPostRedisplay();
    glutTimerFunc(25, update, 25);
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    ball1 = ball_init(400, 100, 10, radius);
    ball_set_velocity(&ball1, 150, 150);

    ball2 = ball_init(100, 100, 10, radius);
    ball_set_velocity(&ball2, -150, 200);

    balls = list_init(sizeof(Ball));
    list_add(&balls, &ball1);
    list_add(&balls, &ball2);

    // Basic settings    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    // Register callbacks
    glutReshapeFunc(reshapeWindow);
    glutDisplayFunc(draw);
    glutTimerFunc(25, update, 25);

    // Keyboard callbacks
    glutKeyboardFunc(handleKeyboard);
    glutKeyboardUpFunc(handleKeyboardUp);

    // Mouse callbacks
    glutMouseFunc(mouseClick);

    glutMainLoop();
}