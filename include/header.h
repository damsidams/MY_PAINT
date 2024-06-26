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
    #define IS_PRESSED(button) (button->state == PRESSED)
    #define IS_HOVER(button) (button->state == HOVER)
    #define IS_RELEASED(button) (button->state == RELEASED)
    #define ERROR 84
    #define SUCCESS 0
    #define BITS_PER_PIXEL 32
    #define FONT_SIZE 16

/* path */

    #define FONTPATH "src/assets/font.ttf"
    #define PENCIL_PNG_PATH "src/assets/sprites/paint-brush.png"
    #define ERASER_PNG_PATH "src/assets/sprites/eraser.png"
    #define HELP_PNG_PATH "src/assets/sprites/help.png"
    #define ABOUT_PNG_PATH "src/assets/sprites/help.png"
    #define COLOR_PICKER_PNG_PATH "src/assets/sprites/color_palette.png"
    #define SQUARE_PNG_PATH "src/assets/sprites/square.png"
    #define CIRCLE_PNG_PATH "src/assets/sprites/circle.png"

/* top nav bar */

    #define DROP_MENU_NB 3
    #define TOP_BAR_HEIGHT 50
    #define TOP_BAR_WIDTH 100
    #define SAVE_NAME "creation.jpg"
    #define SAVE_COOLDOWN 3.0

/* tool bar */

    #define TOOL_SELECTOR_X WIN_WIDTH * 0.2
    #define TOOL_BAR_POURCENTAGE 0.15
    #define TOOL_SELECT_OT 2.3
    #define TOOL_MARGIN 25
    #define TOOL_SELECTOR_SIZE 70
    #define TOOL_BAR_HEIGHT WIN_HEIGHT * TOOL_BAR_POURCENTAGE
    #define SIZE_SELECTOR_WIDTH 70
    #define SIZE_SELECTOR_HEIGHT 40
    #define SIZE_SELECTOR_FONT_SIZE 8
    #define COLOR_PICKER_HEIGHT TOOL_BAR_HEIGHT * 0.8
    #define COLOR_PICKER_WIDTH COLOR_PICKER_HEIGHT * 1.5
    #define COLOR_PICKER_X WIN_WIDTH * 0.8
    #define CP_IMAGE_WIDTH 820
    #define CP_IMAGE_HEIGHT 528
    #define SHAPE_SELECTOR_X WIN_WIDTH * 0.6
    #define SHAPE_SELECTOR_SIZE TOOL_SELECTOR_SIZE
    #define SHAPE_SELECTOR_OT TOOL_SELECT_OT

/* draw info */

    #define DEFAULT_DRAW_SIZE 8
    #define DEFAULT_DRAW_COLOR sfBlack

/* draw zone infos */
    #define DRAW_WIDTH WIN_WIDTH
    #define DRAW_HEIGHT WIN_HEIGHT - TOP_BAR_HEIGHT - TOOL_BAR_HEIGHT

/* draw zone infos */
    #define HELP_WIDTH 650
    #define HELP_HEIGHT 400

/* help */

    #define HELP_MSG_WIDTH 485
    #define HELP_MSG_HEIGHT 307
    #define ABOUT_WIDTH 251
    #define ABOUT_HEIGHT 51

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

enum shape_mode {
    Circle = 0,
    Square = 1
};

enum draw_mode {
    Pencil,
    Erase
};

typedef struct picker_s {
    sfRectangleShape *rect;
    sfTexture *texture;
    sfImage *image;
} picker_t;

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
    b_content_t *button;
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
    options_t *shape_list;
    drop_menu_t *size_selector;
    picker_t *color_picker;
} toolbar_t;

typedef struct draw_param_s {
    int size;
    sfColor color;
    enum draw_mode draw_mode;
    enum shape_mode shape;
} draw_param_t;

typedef struct win_content_s {
    drop_menu_t **menu;
    sfImage *image;
    sfSprite *sprite;
    sfTexture *texture;
    toolbar_t *toolbar;
    draw_param_t *draw;
    sfSprite *help;
} win_content_t;

typedef struct w_data_s {
    sfRenderWindow *win;
    win_content_t *w_content;
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
void init_color_picker(toolbar_t *toolbar);
void init_color_picker(toolbar_t *toolbar);
void init_shape_selector(toolbar_t *toolbar);

// --> button
sfBool set_rect_text(b_content_t *button, sfRectangleShape *rect,
    char const *text, unsigned int font_size);
sfBool set_rect_img(b_content_t *button, char const *img_path);

// --> display
void display(w_data_t *w_data);
int display_top_bar(sfRenderWindow *win, drop_menu_t **drop_menu);
int display_tool_bar(sfRenderWindow *win, toolbar_t *toolbar);
int display_options(sfRenderWindow *win, drop_menu_t *menu);

// --> events
int run_top_bar_event(win_content_t *wc,
    sfRenderWindow *win, drop_menu_t **menu);
void analyse_events(sfRenderWindow *win,
    win_content_t *wc, sfEvent *event);
int run_tool_bar_event(win_content_t *wc);
int array_size(int nb);
void run_help_event(win_content_t *wc, drop_menu_t *dm);
void color_pick_event(win_content_t *wc, toolbar_t *toolbar, sfEvent *event);

// --> draw
void draw_zone(sfImage *image, sfColor color);
int mouse_in_draw_area(w_data_t *wdata);
void draw_or_not(w_data_t *w_data);

// --> free
void free_everything(w_data_t *w_data);

#endif
