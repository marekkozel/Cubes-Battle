
#include "projectils.h"

void init_projectils(dynarray *projectils)
{
    dynarray_init(projectils, 1);
}

void init_projectil(dynarray *projectils, SDL_Context *window, int id, int player_id, int x, int y, int velocity, double direction_x, double direction_y, double time, double self_destruct, char *path)
{
    Projectil *projectil = (Projectil *)malloc(sizeof(Projectil));

    set_projectil_id(projectil, id);
    set_projectil_player_id(projectil, player_id);
    set_projectil_velocity_x(projectil, velocity * direction_x);
    set_projectil_velocity_y(projectil, velocity * direction_y);

    set_projectil_spawn_time(projectil, time);

    set_projectil_texture(projectil, window, path);
    set_projectil_self_destruct(projectil, self_destruct + time);

    SDL_Rect *dest = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_QueryTexture(projectil->texture, NULL, NULL, &dest->w, &dest->h);
    dest->w *= 5;
    dest->h *= 5;
    dest->x = x - dest->w / 2;
    dest->y = y - dest->h / 2;

    set_projectil_rectangle(projectil, dest);

    dynarray_push(projectils, projectil);
}

void move_projectil(Projectil *projectil, double delta_time)
{
    double velocity_x = get_projectil_velocity_x(projectil);
    double velocity_y = get_projectil_velocity_y(projectil);

    set_projectil_x(projectil, (double)get_projectil_x(projectil) + (velocity_x * delta_time));
    set_projectil_y(projectil, (double)get_projectil_y(projectil) + (velocity_y * delta_time));
}

void destroy_projectil(dynarray *projectils, Projectil *projectil, double time)
{
    // After destruction time, hide the projectile, wait 10 seconds and then remove it
    if (get_projectil_self_destruct(projectil) - time <= 0)
    {
        set_projectil_w(projectil, 0);
        set_projectil_h(projectil, 0);
    }
    if ((get_projectil_self_destruct(projectil) + 10) - time <= 0)
    {
        dynarray_remove(projectils, projectil);
    }
}

void projectil_collision(dynarray *projectils, Obstacles *obstacles, Projectil *projectil, SDL_Context *window, bool player_exist, double time)
{
    for (int i = 0; i < obstacles->count_obstacles; i++)
    {
        if (SDL_HasIntersection(projectil->rectangle, obstacles->obstacles[i].rectangle) && get_obstacle_id(&obstacles->obstacles[i]) != 1)
        {
            if (get_projectil_id(projectil) == ROCKET)
            {
                rocket_explosion(projectil, projectils, window, get_projectil_player_id(projectil), get_projectil_x(projectil), get_projectil_y(projectil), time);
            }
            set_projectil_w(projectil, 0);
            set_projectil_h(projectil, 0);
        }
    }
    if (player_exist)
    {

        for (int i = 0; i < projectils->size; i++)
        {
            Projectil *another_projectil;
            another_projectil = dynarray_get(projectils, i);

            if (SDL_HasIntersection(projectil->rectangle, another_projectil->rectangle) && get_projectil_player_id(projectil) != get_projectil_player_id(another_projectil) && get_projectil_id(another_projectil) != MINE && get_projectil_id(projectil) != MINE)
            {
                set_projectil_w(projectil, 0);
                set_projectil_h(projectil, 0);
                set_projectil_w(another_projectil, 0);
                set_projectil_h(another_projectil, 0);
                if (get_projectil_id(projectil) == ROCKET)
                {

                    rocket_explosion(projectil, projectils, window, get_projectil_player_id(projectil), get_projectil_x(projectil), get_projectil_y(projectil), time);
                }
            }
        }
    }

    // Explode the rocket, if it hits the borders
    if (get_projectil_id(projectil) == ROCKET && get_projectil_w(projectil) != 0)
    {
        if (get_projectil_x(projectil) <= 0)
            rocket_explosion(projectil, projectils, window, get_projectil_player_id(projectil), get_projectil_x(projectil), get_projectil_y(projectil), time);
        if (get_projectil_y(projectil) <= 0)
            rocket_explosion(projectil, projectils, window, get_projectil_player_id(projectil), get_projectil_x(projectil), get_projectil_y(projectil), time);

        if (get_projectil_x(projectil) >= WINDOW_WIDTH - get_projectil_w(projectil))
            rocket_explosion(projectil, projectils, window, get_projectil_player_id(projectil), get_projectil_x(projectil), get_projectil_y(projectil), time);
        if (get_projectil_y(projectil) >= WINDOW_HEIGHT - get_projectil_h(projectil))
            rocket_explosion(projectil, projectils, window, get_projectil_player_id(projectil), get_projectil_x(projectil), get_projectil_y(projectil), time);
    }
}

void rocket_explosion(Projectil *projectil, dynarray *projectils, SDL_Context *window, int player_id, int x, int y, double time)
{
    set_projectil_w(projectil, 0);
    set_projectil_h(projectil, 0);

    char path[100] = "../Assets/Projectils/bullet.png";
    init_projectil(projectils, window, 0, player_id, x, y, 1000, 1, 1, time, 1, path);
    init_projectil(projectils, window, 0, player_id, x, y, 1000, 1, 0, time, 1, path);
    init_projectil(projectils, window, 0, player_id, x, y, 1000, 1, -1, time, 1, path);
    init_projectil(projectils, window, 0, player_id, x, y, 1000, 0, -1, time, 1, path);
    init_projectil(projectils, window, 0, player_id, x, y, 1000, -1, -1, time, 1, path);
    init_projectil(projectils, window, 0, player_id, x, y, 1000, -1, 0, time, 1, path);
    init_projectil(projectils, window, 0, player_id, x, y, 1000, -1, 1, time, 1, path);
    init_projectil(projectils, window, 0, player_id, x, y, 1000, 0, 1, time, 1, path);
}

//------------

void set_projectil_id(Projectil *projectil, int id)
{
    projectil->id = id;
}

void set_projectil_player_id(Projectil *projectil, int player_id)
{
    projectil->player_id = player_id;
}

void set_projectil_rectangle(Projectil *projectil, SDL_Rect *rect)
{
    projectil->rectangle = rect;
}

void set_projectil_x(Projectil *projectil, double x)
{
    projectil->rectangle->x = floor(x);
}

void set_projectil_y(Projectil *projectil, double y)
{
    projectil->rectangle->y = floor(y);
}

void set_projectil_w(Projectil *projectil, int w)
{
    projectil->rectangle->w = w;
}

void set_projectil_h(Projectil *projectil, int h)
{
    projectil->rectangle->h = h;
}

void set_projectil_velocity_x(Projectil *projectil, double velocity_x)
{
    projectil->velocity_x = velocity_x;
}
void set_projectil_velocity_y(Projectil *projectil, double velocity_y)
{
    projectil->velocity_y = velocity_y;
}

void set_projectil_texture(Projectil *projectil, SDL_Context *window, char *texture)
{
    SDL_Texture *tex = IMG_LoadTexture(window->renderer, texture);
    assert(tex);

    projectil->texture = tex;
}

void set_projectil_direction(Projectil *projectil, int direction_x, int direction_y)
{
    projectil->direction_x = direction_x;
    projectil->direction_y = direction_y;
}

void set_projectil_spawn_time(Projectil *projectil, double time)
{
    projectil->spawn_time = time;
}

void set_projectil_self_destruct(Projectil *projectil, double time)
{
    projectil->self_destruct = time;
}

// Geters

int get_projectil_id(Projectil *projectil)
{
    return projectil->id;
}

int get_projectil_player_id(Projectil *projectil)
{
    return projectil->player_id;
}

int get_projectil_x(Projectil *projectil)
{
    return projectil->rectangle->x;
}

int get_projectil_y(Projectil *projectil)
{
    return projectil->rectangle->y;
}

int get_projectil_w(Projectil *projectil)
{
    return projectil->rectangle->w;
}

int get_projectil_h(Projectil *projectil)
{
    return projectil->rectangle->h;
}

double get_projectil_velocity_x(Projectil *projectil)
{
    return projectil->velocity_x;
}
double get_projectil_velocity_y(Projectil *projectil)
{
    return projectil->velocity_y;
}

int get_projectil_direction_x(Projectil *projectil)
{
    return projectil->direction_x;
}

int get_projectil_direction_y(Projectil *projectil)
{
    return projectil->direction_y;
}

double get_projectil_spawn_time(Projectil *projectil)
{
    return projectil->spawn_time;
}

double get_projectil_self_destruct(Projectil *projectil)
{
    return projectil->self_destruct;
}
