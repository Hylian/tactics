#include <stdio.h>
#include <stdlib.h>		/* srand, rand */

#include <3ds.h>
#include <sf2d.h>

#include "variables.h"

void save()
{
    /*
    char filename[13] = "/TACTICS.sav";

    FILE *file = fopen(filename,"w+b");

    //Write file
    fwrite(&level_time[i], sizeof(level_time[i]), 1, file);
    //Close file
    fclose(file);
    */
}


void load()
{

}

void handleInput()
{
    hidScanInput();

    kDown = hidKeysDown();
    kHeld = hidKeysHeld();
    kUp = hidKeysUp();

    hidTouchRead(&Stylus);

    if(kDown & (KEY_LEFT|KEY_CPAD_LEFT))
        if(cursorX > 0)
            cursorX--;

    if(kDown & (KEY_RIGHT|KEY_CPAD_RIGHT))
        if(cursorX < 400/TILE_SIZE - 1)
            cursorX++;

    if(kDown & (KEY_DOWN|KEY_CPAD_DOWN))
        if(cursorY < 240/TILE_SIZE - 1)
            cursorY++;

    if(kDown & (KEY_UP|KEY_CPAD_UP))
        if(cursorY > 0)
            cursorY--;
}

void renderTop()
{
    // Render to top screen, left eye
    sf2d_start_frame(GFX_TOP, GFX_LEFT);

    sf2d_draw_texture(plains_tex, 7*TILE_SIZE-5, 7*TILE_SIZE);

    sf2d_draw_texture(mountain_tex, 6*TILE_SIZE-5, 7*TILE_SIZE);

    sf2d_draw_texture_rotate(road_i_tex, 9*TILE_SIZE+TILE_SIZE/2, 5*TILE_SIZE+TILE_SIZE/2, 1.57079633);
    sf2d_draw_texture(road_c_tex, 8*TILE_SIZE-5, 5*TILE_SIZE);
    sf2d_draw_texture(road_i_tex, 8*TILE_SIZE-5, 6*TILE_SIZE);
    sf2d_draw_texture(road_i_tex, 8*TILE_SIZE-5, 7*TILE_SIZE);
    sf2d_draw_texture(road_i_tex, 8*TILE_SIZE-5, 8*TILE_SIZE);

    sf2d_draw_texture(r_infantry_tex, 7*TILE_SIZE-2, 7*TILE_SIZE);

    sf2d_draw_rectangle(cursorX*TILE_SIZE-2, cursorY*TILE_SIZE, TILE_SIZE, TILE_SIZE, RGBA8(180, 180, 255, 180));

    sf2d_end_frame();

    // Render to top screen, right eye
    sf2d_start_frame(GFX_TOP, GFX_RIGHT);

    sf2d_draw_texture(plains_tex, 7*TILE_SIZE+5, 7*TILE_SIZE);

    sf2d_draw_texture(mountain_tex, 6*TILE_SIZE+5, 7*TILE_SIZE);

    sf2d_draw_texture_rotate(road_i_tex, 9*TILE_SIZE+TILE_SIZE/2, 5*TILE_SIZE+TILE_SIZE/2, 1.57079633);
    sf2d_draw_texture(road_c_tex, 8*TILE_SIZE+5, 5*TILE_SIZE);
    sf2d_draw_texture(road_i_tex, 8*TILE_SIZE+5, 6*TILE_SIZE);
    sf2d_draw_texture(road_i_tex, 8*TILE_SIZE+5, 7*TILE_SIZE);
    sf2d_draw_texture(road_i_tex, 8*TILE_SIZE+5, 8*TILE_SIZE);

    sf2d_draw_texture(r_infantry_tex, 7*TILE_SIZE+2, 7*TILE_SIZE);

    sf2d_draw_rectangle(cursorX*TILE_SIZE+2, cursorY*TILE_SIZE, TILE_SIZE, TILE_SIZE, RGBA8(180, 180, 255, 180));

    sf2d_end_frame();
}

void renderBottom()
{
        static int xpos = 0;
        static int ypos = 0;

        // Render to bottom screen, left eye
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

        if(xpos >= 320)
            xpos = 0;

        if(ypos >= 240)
            ypos = 0;

        sf2d_draw_texture(r_infantry_tex, xpos++, ypos++);

	sf2d_end_frame();
}

void initTexture(sf2d_texture** t, const struct image* i)
{
        *t = sf2d_create_texture(i->width, i->height, GPU_RGBA8, SF2D_PLACE_RAM);
        sf2d_fill_texture_from_RGBA8(*t, i->pixel_data, i->width, i->height);
        sf2d_texture_tile32(*t);
}

void initAllTextures()
{
        initTexture(&r_infantry_tex, &r_infantry_img);
        initTexture(&plains_tex, &plains_img);
        initTexture(&mountain_tex, &mountain_img);
        initTexture(&forest_tex, &forest_img);
        initTexture(&road_i_tex, &road_i_img);
        initTexture(&road_c_tex, &road_c_img);
}

void freeAllTextures()
{
	sf2d_free_texture(r_infantry_tex);
	sf2d_free_texture(plains_tex);
	sf2d_free_texture(mountain_tex);
	sf2d_free_texture(forest_tex);
	sf2d_free_texture(road_i_tex);
	sf2d_free_texture(road_c_tex);
}

int main()
{
	sf2d_init();

        sf2d_set_3D(true);

	srand(osGetTime());

	sf2d_set_clear_color(RGBA8(0xFF, 0xFF, 0xFF, 0xFF));

        initAllTextures();

	//load();

	title_mode = true;

	while (aptMainLoop())
	{
		handleInput();

                // Start -> Quit Game
		if (hidKeysDown() & KEY_START) 
                    break;

		renderTop();
		renderBottom();

		sf2d_swapbuffers();
	}

        freeAllTextures();

	sf2d_fini();

        return 0;
}
