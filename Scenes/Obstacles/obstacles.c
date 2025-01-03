
#include "obstacles.h"

void set_obstacles(Obstacles *obstacles, SDL_Context *window)
{
    // Set every obstacle
    init_obstacle(window, obstacles, 1, "../Assets/Obstacles/long_pit_obstacle.png", 1150, 338);
    init_obstacle(window, obstacles, 1, "../Assets/Obstacles/pit_obstacle.png", 1300, 178);
    init_obstacle(window, obstacles, 0, "../Assets/Obstacles/thick_block_obstacle.png", 500, 800);
    init_obstacle(window, obstacles, 0, "../Assets/Obstacles/thick_block_obstacle_1.png", 440, 293);
    init_obstacle(window, obstacles, 0, "../Assets/Obstacles/thick_block_obstacle_2.png", 380, 386);
    init_obstacle(window, obstacles, 0, "../Assets/Obstacles/thick_block_obstacle_3.png", 157, 436);
}

void init_obstacles(Obstacles *obstacles, int size)
{
    obstacles->count_obstacles = size;
    obstacles->capacity = 0;
    obstacles->obstacles = (Obstacle *)malloc(size * sizeof(Obstacle));
}

void init_obstacle(SDL_Context *window, Obstacles *obstacles, int id, char *tex, int x, int y)
{
    Obstacle *obstacle = (Obstacle *)malloc(sizeof(Obstacle));

    set_obstacle_id(obstacle, id);

    set_obstacle_texture(obstacle, window, tex);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(obstacle->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    dest->x = x;
    dest->y = y;

    set_obstacle_rectangle(obstacle, dest);

    obstacles->obstacles[obstacles->capacity] = *obstacle;
    obstacles->capacity += 1;
}

// ---------------------------------------

void set_obstacle_id(Obstacle *obstacle, int id)
{
    obstacle->id = id;
}

void set_obstacle_rectangle(Obstacle *obstacle, SDL_Rect *rect)
{
    obstacle->rectangle = rect;
}

void set_obstacle_name(Obstacle *obstacle, char *name)
{
    strcpy(obstacle->name, name);
}

void set_obstacle_texture(Obstacle *obstacle, SDL_Context *window, char *texture)
{
    SDL_Texture *tex = IMG_LoadTexture(window->renderer, texture);
    assert(tex);

    obstacle->texture = tex;
}

int get_obstacle_id(Obstacle *obstacle)
{
    return obstacle->id;
}

int get_obstacle_x(Obstacle *obstacle)
{
    return obstacle->rectangle->x;
}

int get_obstacle_y(Obstacle *obstacle)
{
    return obstacle->rectangle->y;
}

int get_obstacle_w(Obstacle *obstacle)
{
    return obstacle->rectangle->w;
}

int get_obstacle_h(Obstacle *obstacle)
{
    return obstacle->rectangle->h;
}
