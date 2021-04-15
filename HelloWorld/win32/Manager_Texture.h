#pragma once

#include "Object_Texture.h"
#define MAX_TEXTURE	20

class TextureManager
{
protected:
	Object_Texture* pTexture[ MAX_TEXTURE ];
public:
	TextureManager();

	virtual void addTexture( CGPoint _pos, TEXTURETYPE _type, CCNode* _ground );
	virtual void addTexture( CGPoint _pos, TEXTURETYPE _type, CCNode* _ground, int _tag );
	virtual void addTexture( CGPoint _pos, TEXTURETYPE _type, CCNode* _ground, int _tag, int zOrder );

	virtual Object_Texture* getChildByType( TEXTURETYPE _type );
};
