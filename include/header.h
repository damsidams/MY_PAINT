/*
** EPITECH PROJECT, 2024
** HEADER FOR BOOTSTRAP
** File description:
** none
*/

#ifndef HEADER_H
    #define HEADER_H

    #include <SFML/Graphics.h>
    #include "my.h"

    #define WIN_HEIGHT 1080
    #define WIN_WIDTH 1920
    #define DRAW_WIDTH 1280
    #define DRAW_HEIGHT 720
    #define IS_PRESSED(button) (button->state == PRESSED)
    #define IS_HOVER(button) (button->state == HOVER)
    #define IS_RELEASED(button) (button->state == RELEASED)
    #define ERROR 84
    #define SUCCESS 0
    #define BITS_PER_PIXEL 32
    #define FONT_SIZE 16
    #define FONTPATH "src/assets/font.ttf"
    #define PENCIL_PNG_PATH "src/assets/sprites/paint-brush.png"
    #define ERASER_PNG_PATH "src/assets/sprites/eraser.png"
    #define DROP_MENU_NB 3
    #define TOP_BAR_HEIGHT 50
    #define TOP_BAR_WIDTH 100

/* tool bar */

    #define TOOL_SELECTOR_X WIN_WIDTH * 0.2
    #define TOOL_BAR_POURCENTAGE 0.2
    #define TOOL_SELECT_OT 2.3
    #define TOOL_MARGIN 25
    #define TOOL_SELECTOR_SIZE 70

enum e_gui_state {
    NONE = 0,
    HOVER,
    PRESSED,
    RELEASED
};

enum init_mode {
    Text,
    Image
};

typedef struct button_content_s {
    sfRectangleShape *rect;
    sfText *txt;
    sfTexture *texture;
    sfBool (*is_clicked)(struct button_content_s *, sfMouseButtonEvent *);
    sfBool (*is_hover)(struct button_content_s *, sfMouseMoveEvent *);
    enum e_gui_state state;
    int rank;
} b_content_t;

typedef struct options_s {
    b_content_t *option;
    struct options_s *next;
} options_t;

typedef struct drop_menu_s {
    b_content_t *button;
    options_t *options;
} drop_menu_t;

typedef struct toolbar_s {
    sfSprite *sprite;
    sfImage *image;
    sfTexture *texture;
    options_t *tool_list;
} toolbar_t;

typedef struct win_content_s {
    drop_menu_t **menu;
    sfImage *image;
    sfSprite *sprite;
    sfTexture *texture;
    toolbar_t *toolbar;
} win_content_t;

typedef struct w_data_s {
    sfRenderWindow *win;
    win_content_t *w_content;
    //struct sprite_list_s *sprites_list;
} w_data_t;

/*functions definition*/

//-> init
b_content_t *init_button(sfVector2f position, sfVector2f size);
drop_menu_t **create_drop_menu(sfVector2f position, sfVector2f size);
drop_menu_t *add_option_drop_menu(drop_menu_t *drop_menu, char const *text,
    enum init_mode, int rank_nb);
sfUint8 *init_pixel_array(void);
w_data_t *init_win(void);
toolbar_t *init_toolbar(void);

// --> button
sfBool set_rect_text(b_content_t *button, sfRectangleShape *rect,
    char const *text, unsigned int font_size);
sfBool set_rect_img(b_content_t *button, char const *img_path);

// --> display
int run_top_bar_event(sfRenderWindow *win, drop_menu_t **menu);
int display_top_bar(sfRenderWindow *win, drop_menu_t **drop_menu);
int display_tool_bar(sfRenderWindow *win, toolbar_t *toolbar);

// --> events
void analyse_events(sfRenderWindow *win,
    win_content_t *wc, sfEvent *event);

// --> draw
void draw_zone(sfImage *image);

#endif
