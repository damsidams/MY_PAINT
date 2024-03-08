/*
** EPITECH PROJECT, 2024
** HEADER FOR BOOTSTRAP
** File description:
** none
*/

#ifndef HEADER_H
    #define HEADER_H

    #define WIN_HEIGHT 1080
    #define WIN_WIDTH 1920
    #define IS_PRESSED(button) (button->state == PRESSED)
    #define IS_HOVER(button) (button->state == HOVER)
    #define IS_RELEASED(button) (button->state == RELEASED)
    #define ERROR 84
    #define SUCCESS 0
    #define BITS_PER_PIXEL 32

    #include <SFML/Graphics.h>

enum e_gui_state {
    NONE = 0,
    HOVER,
    PRESSED,
    RELEASED
};

struct s_gui_object {
    sfRectangleShape *rect;
    sfBool (*is_clicked)(struct s_gui_object*, sfMouseButtonEvent*);
    sfBool (*is_hover)(struct s_gui_object*, sfMouseMoveEvent*);
    enum e_gui_state state;
};

struct s_gui_options {
    struct s_gui_object *option;
    struct s_gui_options *next;
};

struct s_gui_drop_menu {
    struct s_gui_object* button;
    struct s_gui_options* options;
};

/*typedef struct sprite_list_s {
    sfSprite *sprite;
    sfSprite *next;
} sprite_list_t;*/

typedef struct win_content_s {
    struct s_gui_drop_menu *menu;
    //sfColor **pixel_array;
    sfImage *image;
    sfSprite *sprite;
    sfTexture *texture;
} win_content_t;

typedef struct w_data_s {
    sfRenderWindow *win;
    win_content_t *w_content;
    //struct sprite_list_s *sprites_list;
} w_data_t;

/*functions definition*/

//-> init

struct s_gui_object *init_button(sfVector2f position, sfVector2f size);
struct s_gui_drop_menu *create_drop_menu(sfVector2f position, sfVector2f size);
struct s_gui_drop_menu *add_option_drop_menu(struct s_gui_drop_menu *drop_menu);
sfUint8 *init_pixel_array(void);
w_data_t *init_win(void);

//display
int display_options(sfRenderWindow *win, struct s_gui_drop_menu *menu);

#endif
