#ifndef BOX_H
#define BOX_H

#include "mylib.h"

typedef struct Ball
{
    int x;
    int y;
    int mass;

    Circle circle;
    Vector2 velocity;
} Ball;

Ball ball_init(int x, int y, float mass, float radius);
void ball_update(Ball* ball, float dt, int window_width, int window_height);
void ball_draw(Ball* ball);
void ball_set_velocity(Ball* ball, float x, float y);
bool handle_collisions(Ball* ball1, Ball* ball2);
bool ball_collides_point(Ball* ball, Vector2 point);
Vector2 ball_get_impulse(Ball* ball);

#endif