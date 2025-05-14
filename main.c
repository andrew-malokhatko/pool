#include "mylib.h"
#include "list.h"
#include "ball.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>


// Window size
const double WINDOW_WIDTH = 1600;
const double WINDOW_HEIGHT = 900;

// Game variables
List balls = {NULL, 0, 0};

// constants & stuff
const int radius = 50;

// mouse state 
bool isDragging = false;
Ball* selectedBall = NULL;
Vector2 currentMousePos = {-1, -1};

// Key states
bool keyA = false;
bool keyD = false;

void reshapeWindow(int width, int height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
} 

void draw()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // draw balls
    ListNode* current = balls.head;
    while (current)
    {
        Ball* ball = (Ball*)current->data;
        ball_draw(ball);

        current = current->next;
    }

    // draw mouse
    if (isDragging && selectedBall)
    {
        glColor3f(0.0f, 1.0f, 1.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(selectedBall->x, selectedBall->y);
        glVertex2f(currentMousePos.x, currentMousePos.y);
        glEnd();
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
    // Invert y coordinate
    y = WINDOW_HEIGHT - y;
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        Vector2 mouseDownPos = (Vector2){x, y};

        ListNode* current = balls.head;
        while (current)
        {
            Ball* ball = (Ball*)current->data;

            if (ball_collides_point(ball, mouseDownPos))
            {
                selectedBall = ball;
                break;
            }

            current = current->next;
        }
        
        // if no ball was selected, set selectedBall to NULL
        if (current == NULL)
        {
            selectedBall = NULL;
            return;
        }

        isDragging = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        if (!selectedBall)
        {
            return;
        }

        Vector2 mouseUpPos = (Vector2){x, y};
        Vector2 impulse = {selectedBall->x - mouseUpPos.x, selectedBall->y - mouseUpPos.y};

        if (selectedBall)
        {
            ball_set_velocity(selectedBall, impulse.x, impulse.y);
        }

        isDragging = false;
    }
}

void mouseMotion(int x, int y)
{
    y = WINDOW_HEIGHT - y;
    currentMousePos = (Vector2){x, y};
}


void update(int deltaTime)
{
    float dt = (float)deltaTime / 1000;

    ListNode* current = balls.head;
    while (current)
    {
        Ball* ball = (Ball*)current->data;

        ball_update(ball, dt, WINDOW_WIDTH, WINDOW_HEIGHT);

        current = current->next;
    }
    
    // POTENTIAL MISTAKES, NOT ALL COLLISIONS ARE HANDLED PROPERLY!!!!
    // BUT WORKS FOR 2 BALLS
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

    Ball ball1 = ball_init(400, 400, 10, radius);
    Ball ball2 = ball_init(100, 100, 10, radius);

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
    glutMotionFunc(mouseMotion);

    glutMainLoop();
}