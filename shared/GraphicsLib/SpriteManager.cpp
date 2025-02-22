#include "SpriteManager.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"

using namespace std;

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
	unordered_map<IDType,Sprite*>::iterator iter;

	for( iter = mpSprites.begin(); iter!=mpSprites.end(); ++iter )
	{
		delete iter->second;
	}
}

Sprite* SpriteManager::createAndManageSprite( const IDType& id, GraphicsBuffer* pBuffer, float sx, float sy, float sw, float sh )
{
	//already here?
	unordered_map<IDType,Sprite*>::iterator iter = mpSprites.find( id );

	if( iter != mpSprites.end() )//found
	{
		delete iter->second;
		mpSprites.erase( iter );
	}

	//either way create a new sprite and store it
	Sprite* pSprite = new Sprite( pBuffer, Vector2D(sx,sy), (int)sw, (int)sh );
	mpSprites[id] = pSprite;

	return pSprite;
}

Sprite* SpriteManager::getSprite( const IDType& id )
{
	unordered_map<IDType,Sprite*>::iterator iter = mpSprites.find( id );

	if( iter != mpSprites.end() )//found
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

void SpriteManager::destroySprite( const IDType& id )
{
	unordered_map<IDType,Sprite*>::iterator iter = mpSprites.find( id );

	if( iter != mpSprites.end() )//found
	{
		delete iter->second;
		mpSprites.erase( iter );
	}
}