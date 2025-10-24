#include "Button.h"

TextButton::TextButton(SDL_Renderer *rdr, const char *fontPath, std::string txt,
                       float sz, SDL_Color defaultClr, SDL_Color hoveredClr)
    : renderer(rdr), text(txt), size(sz) {
	font = TTF_OpenFont(fontPath, size);
	SDL_Surface *textSuf =
	    TTF_RenderText_Blended(font, text.c_str(), 0, defaultClr);
	defaultTex = SDL_CreateTextureFromSurface(renderer, textSuf);
	textSuf = TTF_RenderText_Blended(font, text.c_str(), 0, hoveredClr);
	hoverdTex = SDL_CreateTextureFromSurface(renderer, textSuf);
	dims.size = {(float)textSuf->w, (float)textSuf->h};
	SDL_DestroySurface(textSuf);
}

bool TextButton::getIsHovered() { return isHoverd; }

void TextButton::setHovered(bool hovered) { isHoverd = hovered; }

void TextButton::update(SDL_FPoint *mousePos) {
	SDL_FRect dest = dims.toRect();
	isHoverd = SDL_PointInRectFloat(mousePos, &dest);
}

void TextButton::render() {
	SDL_FRect dest = dims.toRect();
	SDL_RenderTexture(renderer, (isHoverd ? hoverdTex : defaultTex), nullptr,
	                  &dest);
}

void TextButton::setPos(Vector2 pos) { dims.pos = pos; }

Transform TextButton::getDims() { return dims; }

TextButton::~TextButton() {
	SDL_DestroyTexture(defaultTex);
	SDL_DestroyTexture(hoverdTex);
	TTF_CloseFont(font);
}

ImageButton::ImageButton(SDL_Renderer *rdr, const char *path1,
                         const char *path2)
    : renderer(rdr) {
	defaultTex = IMG_LoadTexture(renderer, path1);
	hoverdTex = IMG_LoadTexture(renderer, path2);

	dims.size = texSSize = {(float)defaultTex->w, (float)defaultTex->h};
}

ImageButton::ImageButton(SDL_Renderer *rdr, const char *path1,
                         const char *path2, float w, float h)
    : renderer(rdr) {
	defaultTex = IMG_LoadTexture(renderer, path1);
	hoverdTex = IMG_LoadTexture(renderer, path2);

	texSSize = {(float)defaultTex->w, (float)defaultTex->h};

	dims.size = {w, h};
}

void ImageButton::update(SDL_FPoint *mousePos) {
	SDL_FRect dest = dims.toRect();
	isHovered = SDL_PointInRectFloat(mousePos, &dest);
}

void ImageButton::render() {
	SDL_FRect dest = dims.toRect();
	SDL_RenderTexture(renderer, (isHovered ? hoverdTex : defaultTex), nullptr,
	                  &dest);
}

void ImageButton::setPos(Vector2 pos) { dims.pos = pos; }

void ImageButton::setSize(Vector2 size) { dims.size = size; }

bool ImageButton::getIsHovered() { return isHovered; }

void ImageButton::setHovered(bool hovered) { isHovered = hovered; }

Transform ImageButton::getDims() { return dims; }

ImageButton::~ImageButton() {
	SDL_DestroyTexture(defaultTex);
	SDL_DestroyTexture(hoverdTex);
}

CombinedButton::CombinedButton(SDL_Renderer *rdr, const char *imgNormal,
                               const char *imgHover, const char *fontPath,
                               std::string text, float textSize,
                               SDL_Color textClr, SDL_Color textHoverClr)
    : renderer(rdr) {
	imgBtn = new ImageButton(renderer, imgNormal, imgHover);
	textBtn = new TextButton(renderer, fontPath, text, textSize, textClr,
	                         textHoverClr);
}

CombinedButton::CombinedButton(SDL_Renderer *rdr, const char *imgNormal,
                               const char *imgHover, float w, float h,
                               const char *fontPath, std::string text,
                               float textSize, SDL_Color textClr,
                               SDL_Color textHoverClr)
    : renderer(rdr) {
	imgBtn = new ImageButton(renderer, imgNormal, imgHover, w, h);
	textBtn = new TextButton(renderer, fontPath, text, textSize, textClr,
	                         textHoverClr);
}

void CombinedButton::setPos(Vector2 pos) {
	imgBtn->setPos(pos);

	Transform imgDims = imgBtn->getDims();
	Transform txtDims = textBtn->getDims();

	Vector2 textPos;

	textPos.x = imgDims.pos.x + imgDims.size.x + 5.0f;

	textPos.y = imgDims.pos.y + (imgDims.size.y - txtDims.size.y) / 2;

	textBtn->setPos(textPos);
}

void CombinedButton::update(SDL_FPoint *mousePos) {
	SDL_FRect imgRect = imgBtn->getDims().toRect();
	SDL_FRect textRect = textBtn->getDims().toRect();

	bool b1 = SDL_PointInRectFloat(mousePos, &imgRect);
	bool b2 = SDL_PointInRectFloat(mousePos, &textRect);

	isHovered = (b1 || b2);

	imgBtn->setHovered(isHovered);
	textBtn->setHovered(isHovered);
}

void CombinedButton::render() {
	imgBtn->render();
	textBtn->render();
}

bool CombinedButton::getIsHovered() { return isHovered; }

Transform CombinedButton::getDims() {
	Transform imgDims = imgBtn->getDims();
	Transform txtDims = textBtn->getDims();

	Transform combinedDims;

	combinedDims.pos = imgDims.pos;

	float totalWidth = (imgDims.size.x + 5.0f) + txtDims.size.x;
	combinedDims.size.x = totalWidth;

	combinedDims.size.y =
	    (imgDims.size.y > txtDims.size.y) ? imgDims.size.y : txtDims.size.y;

	return combinedDims;
}

CombinedButton::~CombinedButton() {
	delete imgBtn;
	delete textBtn;
}