#include <stdlib.h>
#include "ball.h"

Ball ball_init(int x, int y, float mass, float radius)
{
    Ball ball;
    ball.x = x;
    ball.y = y;
    ball.mass = mass;

    int randomRed = rand() % 200 +  55;
    ball.circle = (Circle){{x, y}, radius, {randomRed, 0.2f, 0.6f}};

    ball.velocity = (Vector2){0, 0};
    return ball;
}

void ball_update(Ball* ball, float dt, int window_width, int window_height)
{
    // Update the box's position based on its velocity
    ball->x += ball->velocity.x * dt;
    ball->y += ball->velocity.y * dt;

    int radius = ball->circle.radius;

    // handle collisions with the window boundaries
    if (ball->x - radius < 0)
    {
        ball->x = radius;
        ball->velocity.x *= -1;
    }
    else if (ball->x + radius > window_width)
    {
        ball->x = window_width - radius;
        ball->velocity.x *= -1;
    }

    if (ball->y - radius < 0)
    {
        ball->y = radius;
        ball->velocity.y *= -1;
    }
    else if (ball->y + radius > window_height)
    {
        ball->y = window_height - radius;
        ball->velocity.y *= -1;
    }

    // Update the square's position
    ball->circle.pos.x = ball->x;
    ball->circle.pos.y = ball->y;
}

void ball_draw(Ball* ball)
{
    glDrawCircle(ball->circle);
}

void ball_set_velocity(Ball* ball, float x, float y)
{
    ball->velocity.x = x;
    ball->velocity.y = y;
}

bool ball_collides(Ball* ball1, Ball* ball2)
{
    int first_radius = ball1->circle.radius;
    int second_radius = ball2->circle.radius;

    float dx = ball1->x - ball2->x;
    float dy = ball1->y - ball2->y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance < first_radius + second_radius)
    {
        return true;
    }
    
    return false;
}

bool handle_collisions(Ball* ball1, Ball* ball2)
{
    if (!ball_collides(ball1, ball2))
    {
        return false;
    }

    // Calculate the normal vector between the two balls
    float dx = ball2->x - ball1->x;
    float dy = ball2->y - ball1->y;
    float distance = sqrt(dx * dx + dy * dy);

    // Normalize the normal vector from r12
    Vector2 normal = {dx / distance, dy / distance};

    // Calculate the relative momentum (p12)
    float momentum_x = ball2->velocity.x * ball2->mass - ball1->velocity.x * ball1->mass;
    float momentum_y = ball2->velocity.y * ball2->mass - ball1->velocity.y * ball1->mass;

    // Calculate the impulse using scalar vector multiplication
    float dot = momentum_x * normal.x + momentum_y * normal.y;
    Vector2 impulse = {dot * normal.x, dot * normal.y};

    // Apply the impulse to both balls
    ball1->velocity.x += impulse.x / ball1->mass;
    ball1->velocity.y += impulse.y / ball1->mass;

    ball2->velocity.x -= impulse.x / ball2->mass;
    ball2->velocity.y -= impulse.y / ball2->mass;

    // Calculate the overlap distance
    float overlap = ball1->circle.radius + ball2->circle.radius - distance;
    
    ball1->x -= overlap / 2  * normal.x;
    ball1->y -= overlap / 2 * normal.y;

    ball2->x += overlap / 2 * normal.x;
    ball2->y += overlap / 2 * normal.y;

    return true;
}

bool ball_collides_point(Ball* ball, Vector2 point)
{
    float dx = point.x - ball->x;
    float dy = point.y - ball->y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance < ball->circle.radius)
    {
        return true;
    }
    
    return false;
}