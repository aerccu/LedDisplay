


#ifndef DISPBINDING_H
#define DISPBINDING_H

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


struct LRGBMatrix;
struct LCanvas;
struct LFont;

// New matrix options
struct LRGBMatrixOptions {
    const char* hw_mapping_name;    // default : 0
    int rows, cols;                 // default : 32x32
    int chain_size;                 // default : 1 display unit
    int group_size;                 // default : 1 chain
    int pwm_bits;                   // default : 11 bits
    int pwm_lsb_ns;                 // higher value higher quality
    int pwm_dither_bits;            // lsb dithering resultion bits
    int brightness;                 // 1...100
    int scan_mode;                  // 0=progressive | 1=interlaced
    int row_addr_type;              // default : 0
    int multiplexing;               // 0=direct | 1=stripe | 3=checker
    const char* rgb_sequence;       // colour mapping
    const char* pmapper_config;     // semicolon seperated values of
                                    // pixel mappers
    
    unsigned disable_hw_pulsing:1;  
    unsigned display_refresh_rate:1;
    unsigned inverse_colours:1;
};


// Matrix creation from options
struct LRGBMatrix* lmatrix_init_from_options(struct LRGBMatrixOptions* options, 
                                            int* argc, char*** argv);


void lmatrix_print_options(FILE* out);

// Matrix creation with minimal params
struct LRGBMatrix* lmatrix_init(int rows, int disps_in_chain, int chains_in_parallel);


// Matrix destruction
void lmatrix_uninit(struct LRGBMatrix* matrix);

// Fetch current canvas for further processing
struct LCanvas* lmatrix_get_active_canvas(struct LRGBMatrix* matrix);

void lcanvas_get_size(const struct LCanvas* canvas, int* width, int* height);

void lcanvas_set_pixel(struct LCanvas* canvas, int x, int y,
                        uint8_t r, uint8_t g, uint8_t b);

void lcanvas_clear(struct LCanvas* canvas);

void lcanvas_fill(struct LCanvas* canvas, uint8_t r, uint8_t g, uint8_t b);


// Double buffeing capabilities

struct LCanvas* lmatrix_init_offscreenCanvas(struct LRGBMatrix* matrix);

struct LCanvas* lmatrix_swap_on_vsync(struct LRGBMatrix* matrix,
                                    struct LCanvas* canvas);

uint8_t lmatrix_get_brightness(struct LRGBMatrix* matrix);
void    lmatrix_set_brightness(struct LRGBMatrix* matrix, uint8_t brightness);

struct LFont* load_font(const char* bdf_file);
void delete_font(struct LFont* font);

int draw_horizontal_text(struct LCanvas *canvas, struct LFont* font, int x, int y,
                        uint8_t r, int8_t g, int8_t b,
                        const char* utf8_text, int kerning_offset);

int draw_vertical_text(struct LCanvas *canvas, struct LFont* font, int x, int y,
                        uint8_t r, int8_t g, int8_t b,
                        const char* utf8_text, int kerning_offset);

void draw_circle(struct LCanvas* canvas, int x, int y, int radius, uint8_t r, uint8_t g, uint8_t b);

void draw_line(struct LCanvas* canvas, int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b);

//void draw_polygon(int num_of_vertices, int* coordinates);


#ifdef __cplusplus
}
#endif //  __cplusplus

#endif // DISPBINDING_H