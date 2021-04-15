#include "Debug.h"
#include "Object_Hero.h"
#include "st.h"

Debug* Debug::create()
{
	Debug* p = new Debug;
	p->init();
	return p;
}
bool Debug::init()
{
	if( !CCLayer::init() ) return false;

	CCLayer::setIsTouchEnabled( true );

	startPoint = ccp( 0.f, 0.f );

	schedule( schedule_selector(Debug::update) );
	return true;
}

void Debug::update( float dt )
{
	this->controller();
}
void Debug::controller() 
{
	if( GetAsyncKeyState('1') )
		Line();

	if( GetAsyncKeyState('2') )
		Inform();

	if( GetAsyncKeyState('3') )
		BoxVisible( true );

	if( !GetAsyncKeyState('1') )
		this->removeChild( this->getChildByTag(1), false );

	if( !GetAsyncKeyState('2') )
	{
		this->removeChild( this->getChildByTag(2), false );
		this->removeChild( this->getChildByTag(3), false );
	}
	if( !GetAsyncKeyState('3') )
	{
		BoxVisible( false );
	}
}
void Debug::Line()
{
		CCSprite* line = CCSprite::spriteWithFile( "resource/line.png" );

		CGSize winSize = CCDirector::sharedDirector()->getWinSize();
		CGPoint pos	= ccp( winSize.width * 0.5f, 0.f );

		line->setAnchorPoint( ccp(0.f, 0.f) );
		line->setPosition	( pos			);
		line->setScaleX		( 5.f			);
		line->setScaleY		( 10.f			);

		if( this->getChildByTag(1) == NULL )
			this->addChild( line, 0, 1 );
}

void Debug::Inform()
{
	if( this->getChildByTag(2) == NULL && this->getChildByTag(3) == NULL )
	{
		Object_Hero* pHero = (Object_Hero*)st::call()->worldNode->getChildByTag( S1_HERO );

		char szStr[64] = { 0 };
		sprintf_s( szStr, "HeroPosition X:%.1f, Y:%.1f", pHero->getPosition().x, pHero->getPosition().y );
		CCLabelTTF* pHeroPosition = CCLabelTTF::labelWithString( szStr, "", 20.f );

		memset( szStr, NULL, sizeof(szStr) );

		CGPoint pos = st::call()->worldNode->getPosition();
		sprintf_s( szStr, "MapPosition  X:%.1f, Y:%.1f", pos.x, pos.y );
		CCLabelTTF* pBGAPosition = CCLabelTTF::labelWithString( szStr, "", 20.f );
		
		this->addChild( pHeroPosition, 0, 2 );
		this->addChild( pBGAPosition , 0, 3 );

		for( int i = 2; i <= 3; i++ )
		{
			CGPoint pos;
			pos.x = 150.f;
			pos.y = 680.f + i*20.f;
			this->getChildByTag( i )->setPosition( pos );
		}
	}
	
	if( this->getChildByTag(2) != NULL && this->getChildByTag(3) != NULL )
	{
		Object_Hero* pHero = (Object_Hero*)st::call()->worldNode->getChildByTag( S1_HERO );

		CCLabelTTF* pLabelHero = (CCLabelTTF*)this->getChildByTag( 2 );
		CCLabelTTF* pLabelBGA  = (CCLabelTTF*)this->getChildByTag( 3 );

		char szStr[64] = { 0 };
		sprintf_s( szStr, "HeroPosition X:%.1f, Y:%.1f", pHero->getPosition().x, pHero->getPosition().y );
		pLabelHero->setString( szStr );

		memset( szStr, NULL, sizeof(szStr) );

		CGPoint pos = st::call()->worldNode->getPosition();
		sprintf_s( szStr, "MapPosition  X:%.1f, Y:%.1f", pos.x, pos.y );
		pLabelBGA->setString( szStr );
	}
}

void Debug::ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent)
{
	CCTouch*	pTouch	= (CCTouch*)pTouches->anyObject();
	CGPoint		UIPos	= pTouch->locationInView( pTouch->view() );
	CGPoint		GLPos	= CCDirector::sharedDirector()->convertToGL( UIPos );

	GLPos.x -= st::call()->worldNode->getPosition().x;

	startPoint = GLPos;
}
void Debug::ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent)
{
	CCTouch*	pTouch	= (CCTouch*)pTouches->anyObject();
	CGPoint		UIPos	= pTouch->locationInView( pTouch->view() );
	CGPoint		GLPos	= CCDirector::sharedDirector()->convertToGL( UIPos );
}
void Debug::ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent)
{
	CCTouch*	pTouch	= (CCTouch*)pTouches->anyObject();
	CGPoint		UIPos	= pTouch->locationInView( pTouch->view() );
	CGPoint		GLPos	= CCDirector::sharedDirector()->convertToGL( UIPos );

	GLPos.x -= st::call()->worldNode->getPosition().x;

	startPoint.x /= st::call()->worldNode->getScale();
	startPoint.y /= st::call()->worldNode->getScale();
	GLPos.x		 /= st::call()->worldNode->getScale();
	GLPos.y		 /= st::call()->worldNode->getScale();

	if( (GetAsyncKeyState('U') & 0x8001) == 0x8001 )
		st::call()->boxM.addBox( startPoint, GLPos, st::call()->worldNode, BOX_TEXTURE );
	else if( (GetAsyncKeyState('I') & 0x8001) == 0x8001 )
		st::call()->boxM.addBox( startPoint, GLPos, st::call()->worldNode, WALL	   );
 
	this->removeChild( this->getChildByTag(4), false );
	this->removeChild( this->getChildByTag(5), false );
}

void Debug::BoxVisible( bool _visible )
{
	st::call()->boxM.setVisible( _visible );
}