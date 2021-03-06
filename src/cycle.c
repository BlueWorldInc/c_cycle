#include <cycle.h>

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color orange = {255, 127, 40, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    bool init_error = false;
    SDL_bool run = SDL_TRUE;
    srand(time(NULL));

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Cycle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 700, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (NULL == window)
    {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        init_error = true;
    }
    if (0 != SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = true;
    }

    if (0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = true;
    }

    if (!init_error)
    {


        Cycle* cycle;
        cycle = malloc(sizeof(*cycle));
        (*cycle).cycleX = 50; 

        while (run) {
            SDL_Event event;
            SDL_PollEvent(&event);

            drawWorld(renderer, cycle);

            SDL_Delay(10);
            switch (event.type) {
                case SDL_KEYDOWN:
                    run = SDL_FALSE;
                    break;
            }
        }

        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}

void drawWorld(SDL_Renderer *renderer, Cycle* cycle) {
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

     // clear window
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);

    // draw ground
    SDL_RenderDrawLine(renderer, 0, GROUND_Y, SCREEN_WIDTH, GROUND_Y);
    
    drawCycle(renderer, cycle);
    drawRock(renderer, cycle);
    SDL_RenderPresent(renderer);
}

void drawCycle(SDL_Renderer* renderer, Cycle* cycle) {

    (*cycle).cycleX++;
    int x = (*cycle).cycleX;
    // core
    SDL_RenderDrawLine(renderer, x, GROUND_Y - 30, x + 50, GROUND_Y - 30);
    SDL_RenderDrawLine(renderer, x + 25, GROUND_Y - 60, x + 75, GROUND_Y - 60);
    SDL_RenderDrawLine(renderer, x, GROUND_Y - 30, x + 25, GROUND_Y - 60);
    SDL_RenderDrawLine(renderer, x + 50, GROUND_Y - 30, x + 75, GROUND_Y - 60);
    SDL_RenderDrawLine(renderer, x + 100, GROUND_Y - 30, x + 50, GROUND_Y - 90);
    SDL_RenderDrawLine(renderer, x + 25, GROUND_Y - 60, x + 25, GROUND_Y - 65);
    SDL_RenderDrawLine(renderer, x + 20, GROUND_Y - 65, x + 30, GROUND_Y - 65);
    SDL_RenderDrawLine(renderer, x + 30, GROUND_Y - 90, x + 50, GROUND_Y - 90);
    // wheel
    SDL_Ellipse(renderer, x + 100, GROUND_Y - 30, 30, 30);
    SDL_Ellipse(renderer, x, GROUND_Y - 30, 30, 30);

}

void drawRock(SDL_Renderer* renderer, Cycle* cycle) {
    int x = ((*cycle).cycleX + SCREEN_WIDTH - 640) % SCREEN_WIDTH;
    SDL_Rect srcrect = {SCREEN_WIDTH - x, GROUND_Y - 5, 10, 5};
    SDL_RenderDrawRect(renderer, &srcrect);

}