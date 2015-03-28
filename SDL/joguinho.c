#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
int move_ball(int status, SDL_Rect* r, int min, int max, int speed){
    switch(status)
    {
        case 0:
            r->x += speed;
            if(r->x >= max){
                return 1;
            }
            return 0;
            break;
        case 1:
            r->x -= speed;
            if(r->x <= min){
                return 0;
            }
            return 1;
            break;
        case 2:
            r->y += speed;
            if(r->y > 480){
                r->y = 20;
                if(r->x > 50 && r->x < 90)
                {
                    return 3;
                }
                return 4;
            }
            return 2;
            break;
    }
    return -1;
}
int main (int argc, char* args[])
{
    /* INITIALIZATION */

    int err = SDL_Init(SDL_INIT_EVERYTHING);
    assert(err == 0);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Game!!!",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            640, 480, SDL_WINDOW_SHOWN
                         );
    assert(window != NULL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    assert(renderer != NULL);
    SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, NULL);
    SDL_Rect score = {500, 300, 100, 100};

    /* EXECUTION */
    SDL_Surface * ball_img = SDL_LoadBMP("basketball.bmp");
    if(ball_img == NULL){
        printf("ERRO\n");
        assert(0);
    }
    SDL_Surface * image = SDL_LoadBMP("cesta.bmp");
    if (image == NULL){
        printf("ERRO\n");
        assert(0);
    }
    int status = 0;
    float gravity = 9.8;
    int fall_time = 0;
    float speed = 20;
    float game_speed = 20;
    int last_moved = 0;
    int green = 0x00;
    int red = 0x00;
    SDL_Texture * ball_texture = SDL_CreateTextureFromSurface(renderer, ball_img);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dst = {0, 420, 200, 100};
    SDL_Rect ball = {20, 50, 100, 100};
    SDL_Event e;
    while (1)
    {
        int ticks = SDL_GetTicks();
        SDL_WaitEventTimeout(&e, 10);
        if (e.type == SDL_QUIT) {
            break;
        } else if (e.type == SDL_MOUSEBUTTONDOWN){
            status = 2;
            fall_time = ticks-1;
        }

        if(ticks - last_moved > 30){
            if(fall_time == 0){
                printf("%f\n", game_speed);
                status = move_ball(status, &ball, 20, 500, game_speed);
            }
            else{
                speed = ((float)(ticks-fall_time)/100)*gravity;
                printf("speed:%f\n", speed);
                status = move_ball(status, &ball, 20, 500, speed);
                if(status != 2){
                    speed = 20;
                    fall_time = 0;
                }
            }
            if(status == 3)
            {
                game_speed *= 2;
                red = 0x00;
                green = 0xff;
                status = 0;
            }
            else if(status == 4)
            {
                if(game_speed > 20)
                {
                    game_speed /= 2;
                }
                red = 0xff;
                green = 0x00;
                status = 0;
            }
            last_moved = ticks;
        }


        SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderFillRect(renderer, NULL);
        SDL_RenderCopy(renderer, ball_texture, NULL, &ball);
        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_SetRenderDrawColor(renderer, red, green,0x00,0x00);
        SDL_RenderFillRect(renderer, &score);

        SDL_RenderPresent(renderer);
    }

    /* FINALIZATION */
    SDL_DestroyTexture(ball_texture);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(ball_img);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

	return 0;
}
