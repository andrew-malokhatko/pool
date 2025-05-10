#ifndef MYLIB_H
#define MYLIB_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define PI 3.1415
#define G 9.8

// Struct definitions
typedef struct Vector2
{
    float x;
    float y;
} Vector2;

typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3;

typedef struct Color
{
    float r;
    float g;
    float b;
} Color;

typedef struct Square {
    Vector2 pos;
    Vector2 velocity;
    Vector2 acceleration;

    float angle;
    float size;
    Color color;
} Square;

typedef struct SquareA {
    Vector2 pos;

    Vector2 velocity;
    Vector2 acceleration;

    float w;
    float e;

    float angle;
    float size;
    Color color;
} SquareA;

typedef struct Triangle {
    Vector2 pos1;
    Vector2 pos2;
    Vector2 pos3;

    Color color;
} Triangle;

typedef struct Circle {
    Vector2 pos;
    float radius;

    Color color;
} Circle;

typedef struct Cube {
    Vector3 pos;
    float angle;
    float w;
    float e;
    float r;
    float size;
    Color color;
} Cube;


// General functions
double to_degrees(double radians);
double to_rad(double degrees);

// Draw functions
void glDrawCube(Cube cube);
void glDrawSquare(Square square);
void glDrawSquareAngle(SquareA square);
void glDrawTriangle(Triangle triangle);
void glDrawAxes();
void glDrawCircle(Circle circle);

bool collide(Square sq1, Square sq2);


#endif
