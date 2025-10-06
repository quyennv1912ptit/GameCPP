#include "HPBar.h"

HPBar::HPBar(float &MaxHP, float &CurrentHP, Transform &EntityTransform,
             SDL_Color BackgroundColor, SDL_Color ForegroundColor,
             float Height, float VerticalOffset, float Width)
    : maxHP(MaxHP), currentHP(CurrentHP),
      entityTransform(EntityTransform),
      backgroundColor(BackgroundColor), foregroundColor(ForegroundColor),
      height(Height), verticalOffset(VerticalOffset), width(Width)
{
    backgroundRect = {entityTransform.pos.x, entityTransform.pos.y - verticalOffset, width, height};
    barRect = backgroundRect;
}

void HPBar::Update()
{
    float hpRatio = std::max(0.0f, currentHP / maxHP);
    backgroundRect.x = entityTransform.pos.x + (entityTransform.size.x - width) / 2.0f;
    backgroundRect.y = entityTransform.pos.y - verticalOffset;

    barRect.x = backgroundRect.x;
    barRect.y = backgroundRect.y;
    barRect.w = width * hpRatio;
    barRect.h = height;
}

void HPBar::Render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &backgroundRect);
    SDL_SetRenderDrawColor(renderer, foregroundColor.r, foregroundColor.g, foregroundColor.b, foregroundColor.a);
    SDL_RenderFillRect(renderer, &barRect);
}