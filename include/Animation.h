#pragma once

#include <vector>
#include <SDL3/SDL.h>

struct Frame
{
    SDL_Texture *texture;
    SDL_FRect src;
    SDL_FRect dest;
    void Render(SDL_Renderer *renderer)
    {
        SDL_RenderTexture(renderer, texture, &src, &dest);
    }
};

class Animation
{
private:
    std::vector<Frame> m_Frames;
    int m_FrameCount = 0;
    int m_CurrentFrame = 0;
    float m_DelayTime = 0;
    float m_ElapsedTime = 0;

public:
    void Load(std::vector<SDL_Texture *>, SDL_FRect, SDL_FRect, int, float);
    void Load(SDL_Texture *, std::vector<SDL_FRect>, std::vector<SDL_FRect>, int, float);
    void Update(float);
    void Render(SDL_Renderer *);
};