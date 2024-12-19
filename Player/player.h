#pragma once

#include <SDL2/SDL.h>
#include "Config/sdl.h"
#include "Scenes/Obstacles/obstacles.h"
#include "Weapons/Power_ups/power_ups.h"

#define PLAYER_SPEED (450)
#define FRICTION (150)

typedef enum
{
    RED,
    GREEN,
    BLUE,
    ORANGE
} Color;

typedef struct
{
    int id;
    SDL_Rect *rectangle;
    double velocity_x;
    double velocity_y;
    int friction_x;
    int friction_y;
    int multiplier_x;
    int multiplier_y;
    int direction_x;
    int direction_y;
    Power power;
    SDL_Texture *texture;
    Color color;
    int health;
} Player;

typedef struct
{
    int count_players;
    Player *players;
} Players;

void init_players(Players *players);
void add_player(Players *players, Player *player);

void init_player(Player *player, SDL_Context *window, int id, char tex[100], Color color);

void move_player(Player *player, double delta_time, Players *players, Obstacles *obstacles, dynarray *power_ups, dynarray *projectils);

void animate_player(Player *player, SDL_Context *window, char *path);

void detect_players_collisions(Player *player, Players *players);
void detect_boarders_collisions(Player *Player);

void detect_obstacles_collisions(Player *player, Obstacles *obstacles);

void detect_power_up_collision(Player *player, dynarray *array);

void detect_projectils_collision(Player *player, dynarray *projectils);

void spawn_projectil(Player *player, dynarray *projectils, SDL_Context *window);

void set_player_friction_x(Player *player, int friction);
void set_player_friction_y(Player *player, int friction);

void set_player_id(Player *player, int id);
void set_player_rectangle(Player *player, SDL_Rect *rect);
void set_player_x(Player *player, double x);
void set_player_y(Player *player, double y);
void set_player_w(Player *player, int w);
void set_player_h(Player *player, int h);
void set_player_texture(Player *player, SDL_Context *window, char *texture);
void set_player_health(Player *player, int health);
void set_player_velovity_x(Player *player, double velocity_x);
void set_player_velovity_y(Player *player, double velocity_y);
void set_player_multiplier_x(Player *player, int multiplier);
void set_player_multiplier_y(Player *player, int multiplier);
void set_player_direction(Player *player, int direction_x, int direction_y);
void set_player_color(Player *player, Color color);

void set_player_power(Player *player, Power power);

int get_player_id(Player *player);
double get_player_velocity_x(Player *player);
double get_player_velocity_y(Player *player);
int get_player_x(Player *player);
int get_player_y(Player *player);
int get_player_w(Player *player);
int get_player_h(Player *player);
int get_player_multiplier_x(Player *player);
int get_player_multiplier_y(Player *player);
int get_player_direction_x(Player *player);
int get_player_direction_y(Player *player);

int get_player_heath(Player *player);

Color get_player_color(Player *player);

Power get_player_power(Player *player);