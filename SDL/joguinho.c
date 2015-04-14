#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>

int move_ball(int status, SDL_Rect* r, int min, int max, float dx){
    switch(status)
    {
        case 0:
            r->x += dx;
            if(r->x >= max){
                return 1;
            }
            return 0;
            break;
        case 1:
            r->x -= dx;
            if(r->x <= min){
                return 0;
            }
            return 1;
            break;
        case 2:
            r->y += dx;
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
    float gravity = 0.15;
    float falling_speed = 0;
    float game_speed = 0.5;
    int dt = 0;
    int green = 0x00;
    int red = 0x00;
    int vidas = 3;
    SDL_Rect* ret_vidas = NULL;
    int acumulador = 0;
    Uint32 last = 0;
    SDL_Texture * ball_texture = SDL_CreateTextureFromSurface(renderer, ball_img);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dst = {0, 420, 200, 100};
    SDL_Rect ball = {20, 50, 100, 100};
    SDL_Event e;
    while (1)
    {
        SDL_WaitEventTimeout(&e, 10);
        if (e.type == SDL_QUIT) {
            break;
        } else if (e.type == SDL_MOUSEBUTTONDOWN){
            if(status == 0 || status == 1){
                status = 2;
                falling_speed = 0;
            }
        } else if (e.type == SDL_KEYDOWN){
            SDL_Keycode keyPressed = e.key.keysym.sym;
            if(keyPressed == SDLK_r){
                vidas = 3;
                status = 0;
                ball.x = 20;
                ball.y = 50;
            }
        }

        // update no tempo
        Uint32 now = SDL_GetTicks();
        if(now > last){
            dt = now-last;
            last = now;
        }

        // Se a bola está indo para a esquerda ou indo para a direita
        if(status == 0 || status == 1){
            // incrementa a sua posição
            status = move_ball(status, &ball, 20, 500, dt*game_speed);
        }else if (status == 2){ // bola caindo
            falling_speed = dt*gravity;
            status = move_ball(status, &ball, 20, 500, dt*falling_speed);
        }
        // acertou a cesta
        else if(status == 3){
            acumulador += 1;
            if(acumulador > 1 && vidas < 3){
                vidas++;
            }
            game_speed *= 2;
            red = 0x00;
            green = 0xff;
            status = 0;
        }
        // errou a cesta
        else if(status == 4){
            if(game_speed > 0.5){
                game_speed /= 2;
            }
            acumulador = 0;
            vidas -= 1;
            red = 0xff;
            green = 0x00;
            status = 0;
        }
        if(vidas == 0){
            status = 5;
        }


        SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderFillRect(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
        if(ret_vidas!=NULL){
            free(ret_vidas);     
        }
        ret_vidas = (SDL_Rect*)malloc(vidas*sizeof(SDL_Rect));
        for(int i=0; i<vidas; i++){
            ret_vidas[i].x = 500 + (i*30);
            ret_vidas[i].y = 50;
            ret_vidas[i].w = 25;
            ret_vidas[i].h = 25; 
            //life = {500+i*30, 50, 25, 25};
            SDL_RenderFillRect(renderer, &ret_vidas[i]);
        }
        SDL_RenderCopy(renderer, ball_texture, NULL, &ball);
        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_SetRenderDrawColor(renderer, red, green,0x00,0x00);
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
