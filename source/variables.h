#define TILE_SIZE 20

touchPosition Stylus;

u32 kDown;
u32 kHeld;
u32 kUp;

extern const struct 
{
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel;
  unsigned char	 pixel_data[];
} r_infantry_img, plains_img, mountain_img, forest_img, road_i_img, road_c_img;

sf2d_texture *r_infantry_tex, *plains_tex, *mountain_tex, *forest_tex, *road_i_tex, *road_c_tex;

enum UNIT
{
    INFANTRY,
    MECH,
    ARTILLERY,
    TANK,
    ROCKET
};

typedef struct 
{
	s16 row;
	s16 col;
        enum UNIT unit;
} tile;

tile tile_list[25][15];

u8 cursorX, cursorY;

bool title_mode;
