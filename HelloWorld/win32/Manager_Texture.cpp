#include "Manager_Texture.h"

TextureManager::TextureManager()
{
	memset( pTexture, NULL, sizeof(pTexture) );
}
void TextureManager::addTexture( CGPoint _pos, TEXTURETYPE _type, CCNode* _ground )
{
	for( int i = 0; i < MAX_TEXTURE; i++ )
	{
		if( pTexture[i] != NULL ) continue;
		pTexture[i] = new Object_Texture;
		pTexture[i]-> init			( _type );
		pTexture[i]-> setPosition	( _pos  );
		pTexture[i]-> setIsVisible	( true  );
		_ground	   -> addChild		( pTexture[i] );
		return;
	}
}
void TextureManager::addTexture( CGPoint _pos, TEXTURETYPE _type, CCNode* _ground, int _tag )
{
	for( int i = 0; i < MAX_TEXTURE; i++ )
	{
		if( pTexture[i] != NULL ) continue;
		pTexture[i] = new Object_Texture;
		pTexture[i]-> init			( _type );
		pTexture[i]-> setPosition	( _pos  );
		pTexture[i]-> setIsVisible	( true  );
		_ground	   -> addChild		( pTexture[i], 0, _tag );
		return;
	}
}
void TextureManager::addTexture( CGPoint _pos, TEXTURETYPE _type, CCNode* _ground, int _tag, int zOrder )
{
	for( int i = 0; i < MAX_TEXTURE; i++ )
	{
		if( pTexture[i] != NULL ) continue;
		pTexture[i] = new Object_Texture;
		pTexture[i]-> init			( _type );
		pTexture[i]-> setPosition	( _pos  );
		pTexture[i]-> setIsVisible	( true  );
		_ground	   -> addChild		( pTexture[i], zOrder, _tag );
		return;
	}
}

Object_Texture* TextureManager::getChildByType( TEXTURETYPE _type )
{
	for( int i = 0; i < MAX_TEXTURE; i++ )
	{
		if( pTexture[i] == NULL ) continue;

		if( pTexture[i]->GetType() == _type )
			return pTexture[i];
	}

	return NULL;
}