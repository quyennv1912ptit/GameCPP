#include "Animation.h"

void Animation::Load(std::vector<SDL_Texture *> textureArr, SDL_FRect src, SDL_FRect dest, int count, float delay)
{
    m_FrameCount = count;
    m_DelayTime = delay;
    for (int i = 0; i < m_FrameCount; i++)
    {
        Frame frame = {textureArr[i], src, dest};
        m_Frames.push_back(frame);
    }
}

void Animation::Load(SDL_Texture *spriteSheet, std::vector<SDL_FRect> srcRects, std::vector<SDL_FRect> destRects, int count, float delay)
{
    m_FrameCount = count;
    m_DelayTime = delay;
    for (int i = 0; i < m_FrameCount; i++)
    {
        Frame frame = {spriteSheet, srcRects[i], destRects[i]};
        m_Frames.push_back(frame);
    }
}

void Animation::Update(float dt)
{
    m_ElapsedTime += dt;
    if (m_ElapsedTime >= m_DelayTime)
    {
        m_CurrentFrame = (m_CurrentFrame + 1) % m_FrameCount;
        m_ElapsedTime -= m_DelayTime;
    }
}

void Animation::Render(SDL_Renderer *renderer)
{
    m_Frames[m_CurrentFrame].Render(renderer);
}