#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Color.h"
#include "Renderer.h"
#include "Font.h"
#include "SDL_FontCache.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <cassert>

using namespace std;

Renderer* GraphicsSystem::mpRenderer = NULL;
GraphicsBuffer* GraphicsSystem::mpBackBuffer=NULL;
unsigned int GraphicsSystem::mWidth = 0;
unsigned int GraphicsSystem::mHeight = 0;


GraphicsSystem::GraphicsSystem()
{
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

bool GraphicsSystem::init(unsigned int width, unsigned int height)
{
	//possible enhancement - if width and height is different than current initted display - cleanup and re-init with new size
	if (!mIsInitted)
	{
		//create window
		mpWindow = SDL_CreateWindow("TEST APP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (mpWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}

		mpRenderer = new Renderer(mpWindow);
		mpBackBuffer = mpRenderer->makeBackBuffer();

		//enable PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return false;
		}

		//enable TTF support
		if (TTF_Init() < 0)
		{
			printf("SDL_TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
			return false;
		}

		mWidth = width;
		mHeight = height;

		mIsInitted = true;
	}
	return true;
}

void GraphicsSystem::cleanup()
{
	if (mIsInitted)
	{
		delete mpBackBuffer;
		mpBackBuffer = NULL;

		delete mpRenderer;
		mpRenderer = NULL;

		SDL_DestroyWindow(mpWindow);
		mpWindow = NULL;

		//Quit SDL subsystems
		IMG_Quit();
		TTF_Quit();
		mWidth = 0;
		mHeight = 0;
		mIsInitted = false;
	}
}

void GraphicsSystem::flip()
{
	assert(mIsInitted);

	//present renderer
	SDL_RenderPresent(mpRenderer->mpRenderer);
}

void GraphicsSystem::draw(const Vector2D& destLoc, const GraphicsBuffer& src, double rotationInRadians /*= 0.0*/, double scale /* = 1.0*/)
{
	draw(*getBackBuffer(), destLoc, src, rotationInRadians, scale);
}

void GraphicsSystem::draw(GraphicsBuffer& dest, const Vector2D& loc, const GraphicsBuffer& src, double rotationInRadians /* = 0.0*/, double scale /* = 1.0*/)
{
	SDL_Texture* pOldTarget = setRenderTarget(dest);

	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	Vector2D srcSize = src.getSize();
	Vector2D srcLoc = ZERO_VECTOR2D;
	SDL_Rect srcRect;
	srcRect.w = (int)srcSize.getX();
	srcRect.h = (int)srcSize.getY();
	srcRect.x = (int)srcLoc.getX();
	srcRect.y = (int)srcLoc.getY();
	SDL_Rect destRect;
	destRect.w = (int)(srcRect.w*scale);
	destRect.h = (int)(srcRect.h*scale);
	destRect.x = (int)loc.getX();
	destRect.y = (int)loc.getY();
	double rotationInDegrees = rotationInRadians * (180.0 / M_PI);
	//saveBufferToFile(src, "test.png");
	SDL_SetRenderTarget(pRenderer, dest.mpTexture);
	SDL_RenderCopyEx(pRenderer, src.mpTexture, &srcRect, &destRect, rotationInDegrees, NULL, SDL_FLIP_NONE);
	//saveBufferToFile(src, "test2.png");

	restoreRenderTarget(pOldTarget);
}

void GraphicsSystem::draw(const Vector2D& destLoc, const Sprite& sprite, double rotationInRadians /*= 0.0*/, double scale /* = 1.0*/)
{
	draw(*getBackBuffer(), destLoc, sprite, rotationInRadians, scale);
}

void GraphicsSystem::draw(GraphicsBuffer& dest, const Vector2D& loc, const Sprite& sprite, double rotationInRadians /* = 0.0*/, double scale /* = 1.0*/)
{
	SDL_Texture* pOldTarget = setRenderTarget(dest);

	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	Vector2D srcSize(sprite.getWidth(),sprite.getHeight());
	Vector2D srcLoc = sprite.getSourceLoc();
	SDL_Rect srcRect;
	srcRect.w = (int)srcSize.getX();
	srcRect.h = (int)srcSize.getY();
	srcRect.x = (int)srcLoc.getX();
	srcRect.y = (int)srcLoc.getY();
	SDL_Rect destRect;
	destRect.w = (int)(srcRect.w*scale);
	destRect.h = (int)(srcRect.h*scale);
	destRect.x = (int)loc.getX();
	destRect.y = (int)loc.getY();
	double rotationInDegrees = rotationInRadians * (180.0 / M_PI);
	SDL_SetRenderTarget(pRenderer, dest.mpTexture);
	SDL_RenderCopyEx(pRenderer, sprite.getBuffer()->mpTexture, &srcRect, &destRect, rotationInDegrees, NULL, SDL_FLIP_NONE);

	restoreRenderTarget(pOldTarget);
}

void GraphicsSystem::writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align /*= Font::LEFT*/)
{
	//FC_Draw(font.getFont(), mpRenderer->mpRenderer, destLoc.getX(), destLoc.getY(), text.c_str());
	FC_Effect effect;
	effect.alignment = (FC_AlignEnum)align;
	effect.color = getSDLColorFromColor(color);
	effect.scale = FC_MakeScale(1.0f, 1.0f);

	FC_DrawEffect(font.getFont(), mpRenderer->mpRenderer, destLoc.getX(), destLoc.getY(), effect, text.c_str());
};

void GraphicsSystem::writeText(GraphicsBuffer& dest, const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align /*= Font::LEFT*/)
{
	SDL_Texture* pOldTarget = setRenderTarget(dest);
	writeText(destLoc, font, color, text, align);
	restoreRenderTarget(pOldTarget);

}

void GraphicsSystem::setBufferToColor(GraphicsBuffer& buffer, const Color& color)
{
	SDL_Texture* pOldTarget = setRenderTarget(buffer);
	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;

	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(pRenderer, &r, &g, &b, &a);

	//SDL_SetRenderTarget(pRenderer, buffer.mpTexture);
	SDL_SetRenderDrawColor(pRenderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderClear(pRenderer);

	SDL_SetRenderDrawColor(pRenderer, r, g, b, a);

	restoreRenderTarget(pOldTarget);
}

void GraphicsSystem::saveBufferToFile(const GraphicsBuffer& buffer, const std::string& filename)
{
	//based on code found in this thread: https://stackoverflow.com/questions/34255820/save-sdl-texture-to-file

	SDL_Texture* target = SDL_GetRenderTarget(mpRenderer->mpRenderer);
	SDL_SetRenderTarget(mpRenderer->mpRenderer, buffer.mpTexture);
	int width, height;
	buffer.getDimensions(width, height);

	if (width == INVALID_DIMENSION || height == INVALID_DIMENSION)
	{
		width = mWidth;
		height = mHeight;
	}

	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(mpRenderer->mpRenderer, NULL, surface->format->format, surface->pixels, surface->pitch);
	IMG_SavePNG(surface, filename.c_str());
	SDL_FreeSurface(surface);
	SDL_SetRenderTarget(mpRenderer->mpRenderer, target);
}

void GraphicsSystem::renderFilledRect(GraphicsBuffer& dest, const Vector2D& destLoc, int width, int height, const Color& color)
{
	SDL_Texture* pOldTarget = setRenderTarget(dest);
	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;

	//get old render color
	unsigned char oldR, oldG, oldB, oldA;
	SDL_GetRenderDrawColor(pRenderer, &oldR, &oldG, &oldB, &oldA);

	SDL_SetRenderDrawColor(pRenderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_Rect rect = {(int)destLoc.getX(), (int)destLoc.getY(), width, height};
	int retVal = SDL_RenderFillRect(pRenderer, &rect);

	SDL_SetRenderDrawColor(pRenderer, oldR, oldG, oldB, oldA);
	restoreRenderTarget(pOldTarget);

}

SDL_Color GraphicsSystem::getSDLColorFromColor(const Color& color)
{
	SDL_Color theSDLColor;
	theSDLColor.r = color.getR();
	theSDLColor.g = color.getG();
	theSDLColor.b = color.getB();
	theSDLColor.a = color.getA();
	return theSDLColor;
}

SDL_Texture* GraphicsSystem::loadTexture(const std::string& filename)
{
	SDL_Surface* pSurface = IMG_Load(filename.c_str());

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(mpRenderer->mpRenderer, pSurface);

	SDL_FreeSurface(pSurface);
	return pTexture;
}

SDL_Texture* GraphicsSystem::createTexture(int width, int height)
{
	SDL_Texture* pTexture = SDL_CreateTexture(mpRenderer->mpRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	return pTexture;
}

SDL_Texture* GraphicsSystem::setRenderTarget(GraphicsBuffer& buffer)
{
	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	SDL_Texture* pOldTarget = SDL_GetRenderTarget(pRenderer);
	SDL_SetRenderTarget(pRenderer, buffer.mpTexture);
	return pOldTarget;
}

void GraphicsSystem::restoreRenderTarget(SDL_Texture* oldTarget)
{
	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	SDL_SetRenderTarget(pRenderer, oldTarget);
}
