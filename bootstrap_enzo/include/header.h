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

typedef struct button_content_s {
    sfRectangleShape *rect;
    sfBool (*is_clicked)(struct button_content_s*, sfMouseButtonEvent*);
    sfBool (*is_hover)(struct button_content_s*, sfMouseMoveEvent*);
    enum e_gui_state state;
} b_content_t;

typedef struct options_s {
    b_content_t *option;
    struct options_s *next;
} options_t;

typedef struct drop_menu_s {
    b_content_t* button;
    options_t* options;
} drop_menu_t;

/*typedef struct sprite_list_s {
    sfSprite *sprite;
    sfSprite *next;
} sprite_list_t;*/

typedef struct win_content_s {
    drop_menu_t *menu;
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

b_content_t *init_button(sfVector2f position, sfVector2f size);
drop_menu_t *create_drop_menu(sfVector2f position, sfVector2f size);
drop_menu_t *add_option_drop_menu(drop_menu_t *drop_menu);
sfUint8 *init_pixel_array(void);
w_data_t *init_win(void);

//display
int display_options(sfRenderWindow *win, drop_menu_t *menu);

#endif
