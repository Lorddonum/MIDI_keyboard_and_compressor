#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

// struct settings {};
struct nk_canvas {
  struct nk_command_buffer *painter;
  struct nk_vec2 item_spacing;
  struct nk_vec2 panel_padding;
  struct nk_style_item window_background;
};

static nk_bool canvas_begin(struct nk_context *ctx, struct nk_canvas *canvas,
                            const char *title, nk_flags flags, int x, int y,
                            int width, int height,
                            struct nk_color background_color) {
  /* save style properties which will be overwritten */
  canvas->panel_padding = ctx->style.window.padding;
  canvas->item_spacing = ctx->style.window.spacing;
  canvas->window_background = ctx->style.window.fixed_background;

  /* use the complete window space and set background */
  ctx->style.window.spacing = nk_vec2(0, 0);
  ctx->style.window.padding = nk_vec2(0, 0);
  ctx->style.window.fixed_background = nk_style_item_color(background_color);

  /* create/update window and set position + size */
  if (!nk_begin(ctx, title, nk_rect(x, y, width, height),
                NK_WINDOW_NO_SCROLLBAR | flags))
    return nk_false;

  /* allocate the complete window space for drawing */
  {
    struct nk_rect total_space;
    total_space = nk_window_get_content_region(ctx);
    nk_layout_row_dynamic(ctx, total_space.h, 1);
    nk_widget(&total_space, ctx);
    canvas->painter = nk_window_get_canvas(ctx);
  }

  return nk_true;
}

static void canvas_end(struct nk_context *ctx, struct nk_canvas *canvas) {
  nk_end(ctx);
  ctx->style.window.spacing = canvas->panel_padding;
  ctx->style.window.padding = canvas->item_spacing;
  ctx->style.window.fixed_background = canvas->window_background;
}

static void keyboard(struct nk_context *ctx) {
  struct nk_canvas canvas;
  if (canvas_begin(ctx, &canvas, "keyboard",
                   NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_TITLE, 10,
                   10, 1200, 700, nk_rgb(250, 250, 250))) {
    float x = canvas.painter->clip.x, y = canvas.painter->clip.y;

    nk_fill_rect(canvas.painter, nk_rect(x + 700 - 210, y + 210, 210, 210), 5,
                 nk_rgb(247, 230, 154));
    nk_fill_rect(canvas.painter, nk_rect(x, y, 210, 210), 5,
                 nk_rgb(247, 230, 154));
    nk_fill_rect(canvas.painter, nk_rect(x, y, 210, 210), 5,
                 nk_rgb(247, 230, 154));
    nk_fill_rect(canvas.painter, nk_rect(x, y, 210, 210), 5,
                 nk_rgb(247, 230, 154));
    nk_fill_rect(canvas.painter, nk_rect(x, y, 210, 210), 5,
                 nk_rgb(247, 230, 154));
  }
  canvas_end(ctx, &canvas);
}

static void player(struct nk_context *ctx) {
  if (nk_begin(ctx, "Player", nk_rect(10, 10, 180, 250),
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_NO_SCROLLBAR |
                   NK_WINDOW_TITLE)) {
  }
  nk_end(ctx);
}

static void settings(struct nk_context *ctx, struct nk_colorf bg) {
  if (nk_begin(ctx, "Settings", nk_rect(50, 50, 230, 250),
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                   NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
    enum { EASY, HARD };
    static int op = EASY;
    static int property = 20;

    nk_layout_row_static(ctx, 30, 80, 1);
    if (nk_button_label(ctx, "button"))
      fprintf(stdout, "button pressed\n");
    nk_layout_row_dynamic(ctx, 30, 2);
    if (nk_option_label(ctx, "easy", op == EASY))
      op = EASY;
    if (nk_option_label(ctx, "hard", op == HARD))
      op = HARD;
    nk_layout_row_dynamic(ctx, 25, 1);
    nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

    nk_layout_row_dynamic(ctx, 20, 1);
    nk_label(ctx, "background:", NK_TEXT_LEFT);
    nk_layout_row_dynamic(ctx, 25, 1);
    if (nk_combo_begin_color(ctx, nk_rgb_cf(bg),
                             nk_vec2(nk_widget_width(ctx), 400))) {
      nk_layout_row_dynamic(ctx, 120, 1);
      bg = nk_color_picker(ctx, bg, NK_RGBA);
      nk_layout_row_dynamic(ctx, 25, 1);
      bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
      bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
      bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
      bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
      nk_combo_end(ctx);
    }
  }
  nk_end(ctx);
}

int main(int argc, char *argv[]) {
  /* Platform initialization */
  SDL_Window *win;
  SDL_Renderer *renderer;
  int running = 1;
  int flags = 0;
  float font_scale = 1;

  /* GUI */
  struct nk_context *ctx;
  struct nk_colorf bg;

  /* SDL setup */
  SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
  SDL_Init(SDL_INIT_VIDEO);

  win = SDL_CreateWindow("Midi Interface", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                         SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI |
                             SDL_WINDOW_RESIZABLE);

  if (win == NULL) {
    SDL_Log("Error SDL_CreateWindow %s", SDL_GetError());
    exit(-1);
  }

  flags |= SDL_RENDERER_ACCELERATED;
  flags |= SDL_RENDERER_PRESENTVSYNC;

  renderer = SDL_CreateRenderer(win, -1, flags);

  if (renderer == NULL) {
    SDL_Log("Error SDL_CreateRenderer %s", SDL_GetError());
    exit(-1);
  }

  /* scale the renderer output for High-DPI displays */
  {
    int render_w, render_h;
    int window_w, window_h;
    float scale_x, scale_y;
    SDL_GetRendererOutputSize(renderer, &render_w, &render_h);
    SDL_GetWindowSize(win, &window_w, &window_h);
    scale_x = (float)(render_w) / (float)(window_w);
    scale_y = (float)(render_h) / (float)(window_h);
    SDL_RenderSetScale(renderer, scale_x, scale_y);
    font_scale = scale_y;
  }

  /* GUI */
  ctx = nk_sdl_init(win, renderer);
  {
    struct nk_font_atlas *atlas;
    struct nk_font_config config = nk_font_config(0);
    struct nk_font *font;

    /* set up the font atlas and add desired font; note that font sizes are
     * multiplied by font_scale to produce better results at higher DPIs */
    nk_sdl_font_stash_begin(&atlas);
    font = nk_font_atlas_add_default(atlas, 13 * font_scale, &config);
    nk_sdl_font_stash_end();

    /* this hack makes the font appear to be scaled down to the desired
     * size and is only necessary when font_scale > 1 */
    font->handle.height /= font_scale;
    /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
    nk_style_set_font(ctx, &font->handle);
  }

  /* default background definition */
  bg.r = 0.52f, bg.g = 0.64f, bg.b = 0.52f, bg.a = 1.0f;

  //------------------------------------------------------------------//
  //                          main gui loop                           //
  //------------------------------------------------------------------//
  while (running) {
    /* Input */
    SDL_Event evt;
    nk_input_begin(ctx);
    while (SDL_PollEvent(&evt)) {
      if (evt.type == SDL_QUIT)
        goto cleanup;
      nk_sdl_handle_event(&evt);
    }
    nk_input_end(ctx);

    settings(ctx, bg);

    keyboard(ctx);

    player(ctx);

    SDL_SetRenderDrawColor(renderer, bg.r * 255, bg.g * 255, bg.b * 255,
                           bg.a * 255);
    SDL_RenderClear(renderer);

    nk_sdl_render(NK_ANTI_ALIASING_ON);

    SDL_RenderPresent(renderer);
  }

cleanup:
  nk_sdl_shutdown();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
