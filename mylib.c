#include "mylib.h"

#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define PI 3.1415
#define G 9.8

double to_degrees(double radians)
{
    return radians * (180.0 / PI);
}

double to_rad(double degrees)
{
    return (degrees / 360.0f) * 2.0f * PI;
}

void glDrawCube(Cube cube)
{
    glColor3f(cube.color.r, cube.color.g, cube.color.b);

    float halfSize = 0.5f * cube.size;

    glBegin(GL_QUADS);
        // Front Face
        glVertex3f(cube.pos.x - halfSize, cube.pos.y - halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y - halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y + halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x - halfSize, cube.pos.y + halfSize, cube.pos.z + halfSize);

        // Back Face
        glVertex3f(cube.pos.x - halfSize, cube.pos.y - halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x - halfSize, cube.pos.y + halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y + halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y - halfSize, cube.pos.z - halfSize);

        // Top Face
        glVertex3f(cube.pos.x - halfSize, cube.pos.y + halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x - halfSize, cube.pos.y + halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y + halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y + halfSize, cube.pos.z - halfSize);

        // Bottom Face
        glVertex3f(cube.pos.x - halfSize, cube.pos.y - halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y - halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y - halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x - halfSize, cube.pos.y - halfSize, cube.pos.z + halfSize);

        // Right Face
        glVertex3f(cube.pos.x + halfSize, cube.pos.y - halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y + halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y + halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x + halfSize, cube.pos.y - halfSize, cube.pos.z + halfSize);

        // Left Face
        glVertex3f(cube.pos.x - halfSize, cube.pos.y - halfSize, cube.pos.z - halfSize);
        glVertex3f(cube.pos.x - halfSize, cube.pos.y - halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x - halfSize, cube.pos.y + halfSize, cube.pos.z + halfSize);
        glVertex3f(cube.pos.x - halfSize, cube.pos.y + halfSize, cube.pos.z - halfSize);
    glEnd();

    // Draw borders
    glColor3f(0, 1.0f, 0);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        float vertices[8][3] = {
            {cube.pos.x - halfSize, cube.pos.y - halfSize, cube.pos.z - halfSize},
            {cube.pos.x + halfSize, cube.pos.y - halfSize, cube.pos.z - halfSize},
            {cube.pos.x + halfSize, cube.pos.y + halfSize, cube.pos.z - halfSize},
            {cube.pos.x - halfSize, cube.pos.y + halfSize, cube.pos.z - halfSize},
            {cube.pos.x - halfSize, cube.pos.y - halfSize, cube.pos.z + halfSize},
            {cube.pos.x + halfSize, cube.pos.y - halfSize, cube.pos.z + halfSize},
            {cube.pos.x + halfSize, cube.pos.y + halfSize, cube.pos.z + halfSize},
            {cube.pos.x - halfSize, cube.pos.y + halfSize, cube.pos.z + halfSize}
        };

        int edges[12][2] = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0},
            {4, 5}, {5, 6}, {6, 7}, {7, 4},
            {0, 4}, {1, 5}, {2, 6}, {3, 7}
        };

        for (int i = 0; i < 12; i++) {
            glVertex3fv(vertices[edges[i][0]]);
            glVertex3fv(vertices[edges[i][1]]);
        }

    glEnd();
}

void glDrawTriangle(Triangle triangle)
{
    glColor3f(triangle.color.r, triangle.color.g, triangle.color.b);

    glBegin(GL_TRIANGLES);
        glVertex2f(triangle.pos1.x, triangle.pos1.y);
        glVertex2f(triangle.pos2.x, triangle.pos2.y);
        glVertex2f(triangle.pos3.x, triangle.pos3.y);

    glEnd();
}

void glDrawSquare(Square square)
{
    glColor3f(square.color.r, square.color.g, square.color.b);

    glBegin(GL_QUADS);
        glVertex2f(square.pos.x - 0.5f * square.size, square.pos.y + 0.5f * square.size);
        glVertex2f(square.pos.x + 0.5f * square.size, square.pos.y + 0.5f * square.size);
        glVertex2f(square.pos.x + 0.5f * square.size, square.pos.y - 0.5f * square.size);
        glVertex2f(square.pos.x - 0.5f * square.size, square.pos.y - 0.5f * square.size);

    glEnd();
}

void glDrawSquareAngle(SquareA square)
{
    float angle = square.angle;
    // Save the current transformation matrix
    glPushMatrix();

    // Move to the square's position
    glTranslatef(square.pos.x, square.pos.y, 0.0f);

    // Rotate around the center of the square
    glRotatef(to_degrees(angle), 0.0f, 0.0f, 1.0f);

    // Set the color
    glColor3f(square.color.r, square.color.g, square.color.b);

    // Draw the square centered at (0,0)
    glBegin(GL_QUADS);
        glVertex2f(-0.5f * square.size,  0.5f * square.size);
        glVertex2f( 0.5f * square.size,  0.5f * square.size);
        glVertex2f( 0.5f * square.size, -0.5f * square.size);
        glVertex2f(-0.5f * square.size, -0.5f * square.size);
    glEnd();

    glPopMatrix(); // Restore the previous transformation matrix
}


void glDrawAxes() 
{
    glLineWidth(2.0f); // Set line thickness

    glBegin(GL_LINES);
    
    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();
}

void glDrawCircle(Circle circle)
{
    const float num_segments = 360;

    glBegin(GL_TRIANGLE_FAN);
    
    Color color = circle.color;
    glColor3f(color.r, color.g, color.b);
    glVertex2f(circle.pos.x, circle.pos.y);
    
    for (int i = 0; i < num_segments + 1; i++) {
        float theta = 2.0f * PI * (float)i / (float)num_segments;
        float x = circle.radius * cosf(theta); // X coordinate
        float y = circle.radius * sinf(theta); // Y coordinate
        glVertex2f(circle.pos.x + x, circle.pos.y + y);
    }
    
    glEnd();
}

bool collide(Square sq1, Square sq2)
{
    float halfSize1 = sq1.size / 2.0f;
    float halfSize2 = sq2.size / 2.0f;

    float left1   = sq1.pos.x - halfSize1;
    float right1  = sq1.pos.x + halfSize1;
    float top1    = sq1.pos.y - halfSize1;
    float bottom1 = sq1.pos.y + halfSize1;

    float left2   = sq2.pos.x - halfSize2;
    float right2  = sq2.pos.x + halfSize2;
    float top2    = sq2.pos.y - halfSize2;
    float bottom2 = sq2.pos.y + halfSize2;

    if (right1 < left2 || right2 < left1 ||
        bottom1 < top2 || bottom2 < top1)
    {
        return false;
    }

    return true;
}