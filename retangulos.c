#include <SDL2/SDL.h>
#include <assert.h>

void draw(SDL_Renderer* renderer, SDL_Rect r1, SDL_Rect r2){
    SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, NULL);

    SDL_SetRenderDrawColor(renderer, 0x00,0x00,0xFF,0x00);
    SDL_RenderFillRect(renderer, &r1);
    SDL_RenderFillRect(renderer, &r2);

    SDL_RenderPresent(renderer);
}

int move_in_circle(int status, SDL_Rect* r, int initial_x, int initial_y, int radius, int speed){
    switch(status)
    {
        case 0:
            r->x+= speed;
            if(r->x >= initial_x + radius){
                return 1;
            }
            return 0;
            break;
        case 1:
            r->y+= speed;
            if(r->y >= initial_y + radius){
                return 2;
            }
            return 1;
            break;
        case 2:
            r->x-= speed;
            if(r->x <= initial_x)
            {
                return 3;
            }
            return 2;
            break;
        case 3:
            r->y-= speed;
            if(r->y <= initial_y)
            {
                return 0;
            }
            return 3;
            break;
    }
    return -1;
}

int is_in_area(SDL_Rect r, int x, int y)
{
    if(x >= r.x && x <= r.x + r.w && y >= r.y && y<= r.y + r.w )
        return 1;
    return 0;
}

int main (int argc, char* args[])
{
    /* INITIALIZATION */

    int err = SDL_Init(SDL_INIT_EVERYTHING);
    assert(err == 0);

    SDL_Window* window = SDL_CreateWindow("Hello World!",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            640, 480, SDL_WINDOW_SHOWN
                         );
    assert(window != NULL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    assert(renderer != NULL);

    /* EXECUTION */
    unsigned int ticks;
    unsigned int r1spd;
    unsigned int r2spd;
    r1spd = SDL_GetTicks();
    r2spd = r1spd;
    int r1status = 0;
    int r2status = 0;
    SDL_Rect r1 = { 50,50, 50, 50 };
    SDL_Rect r2 = { 250,250, 50, 50 };
    SDL_Event e;

    while (1)
    {
        SDL_WaitEventTimeout(&e, 50);
        if (e.type == SDL_QUIT) {
            break;
        } else if (e.type == SDL_MOUSEBUTTONDOWN){
            SDL_MouseButtonEvent* me = (SDL_MouseButtonEvent*) &e;
            if(is_in_area(r1, me->x, me->y))
            {
                r1status = -1;
            }
            if(is_in_area(r2, me->x, me->y))
            {
                r2status = -1;
            }
        }
        ticks = SDL_GetTicks();
        if(ticks - r1spd > 100){
            r1status = move_in_circle(r1status, &r1, 50, 50, 200, 5);
            r1spd = ticks;
        }
        if(ticks - r2spd > 50){
            r2status = move_in_circle(r2status, &r2, 250, 250, 50, 5);
            r2spd = ticks;
        }
        draw(renderer, r1, r2);   
    }

    /* FINALIZATION */

    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}
