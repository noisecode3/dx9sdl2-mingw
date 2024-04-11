#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <cmath>
#include <vector>

class Screen
{
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;

public:
    Screen()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(640*1,480*1,0,&window,&renderer);
        SDL_RenderSetScale(renderer,1,1);
    }

    void pixel(float x, float y)
    {
        points.emplace_back(x,y);
    }

    void clear()
    {
        points.clear();
    }

    void show()
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        for(auto& point : points)
        {
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }

        SDL_RenderPresent(renderer);
    }

    void input()
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
    }
};

struct vec3
{
        float x,y,z;
};

struct connection
{
    int a,b;
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1)
{
    float rad = 0;

    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x =  std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
}

void line(Screen& screen, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = std::sqrt(dx * dx + dy * dy);
    float angle  = std::atan2(dy,dx);

    for(float i = 0; i < length; i++)
    {
        screen.pixel(
            x1 + std::cos(angle) * i,
            y1 + std::sin(angle) * i
        );

    }
}

int main(int argc, char* argv[])
{
    Screen screen;

    std::vector<vec3> points
    {
        {100,100,100},
        {200,100,100},
        {200,200,100},
        {100,200,100},

        {100,100,200},
        {200,100,200},
        {200,200,200},
        {100,200,200}
    };
    std::vector<connection> connections
    {
        {0,4},
        {1,5},
        {2,6},
        {3,7},

        {0,1},
        {1,2},
        {2,3},
        {3,0},

        {4,5},
        {5,6},
        {6,7},
        {7,4}
    };

    vec3 c{0,0,0};
    for(auto& p : points)
    {
        c.x += p.x;
        c.y += p.y;
        c.z += p.z;
    }
    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();

    while(true)
    {
        for(auto& p : points)
        {
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;
            rotate(p, 0.002, 0.001, 0.004);
            p.x += c.x;
            p.y += c.y;
            p.z += c.z;
            screen.pixel(p.x, p.y);
        }

        for(auto& conn : connections)
        {
            line(
                screen,
                points[conn.a].x,
                points[conn.a].y,
                points[conn.b].x,
                points[conn.b].y
            );
        }

        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);
    }
    return 0;
}
