/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include <stdarg.h>
#include "CCLayer.h"
#include "CCTouchDispatcher.h"
#include "CCKeypadDispatcher.h"
#include "CCXUIAccelerometer.h"
#include "CCDirector.h"
#include "CGPointExtension.h"
namespace   cocos2d {

// CCLayer
CCLayer::CCLayer()
:m_bIsTouchEnabled(false)
,m_bIsAccelerometerEnabled(false)
,m_bIsKeypadEnabled(false)
,m_bIsMouseEnabled(false)
,m_bIsKeyboardEnabled(false)
{
	m_eTouchDelegateType = ccTouchDeletateAllBit;
	m_tAnchorPoint = ccp(0.5f, 0.5f);
	m_bIsRelativeAnchorPoint = false;
}

CCLayer::~CCLayer()
{
}

bool CCLayer::init()
{
	bool bRet = false;
	do 
	{
		CCDirector * pDirector;
		CCX_BREAK_IF( ! (pDirector = CCDirector::sharedDirector()) );
		this->setContentSize(pDirector->getWinSize());
		// success
		bRet = true;
	} while (0);
	return bRet;
}

CCLayer *CCLayer::node()
{
	CCLayer *pRet = new CCLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
    else
    {
	    CCX_SAFE_DELETE(pRet)
	    return NULL;
    }
}

/// Touch and Accelerometer related

void CCLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0);
}

void CCLayer::destroy(void)
{
	this->release();
}

void CCLayer::keep(void)
{
	this->retain();
}

void CCLayer::AccelerometerDestroy(void)
{
    this->release();
}

void CCLayer::AccelerometerKeep(void)
{
    this->retain();
}

void CCLayer::KeypadDestroy()
{
    this->release();
}

void CCLayer::KeypadKeep()
{
    this->retain();
}

void CCLayer::KeyboardDestroy(void)
{
    this->release();
}

void CCLayer::KeyboardKeep(void)
{
    this->retain();
}

void CCLayer::MouseDestroy()
{
    this->release();
}

void CCLayer::MouseKeep()
{
    this->retain();
}


bool CCLayer::getIsMouseEnabled()
{
    return m_bIsMouseEnabled;
}

void CCLayer::setIsMouseEnabled(bool enabled)
{
    CCLOG("cocos2d: CCLayer: unsupportted!");
}

bool CCLayer::getIsKeyboardEnabled()
{
    return m_bIsKeyboardEnabled;
}

void CCLayer::setIsKeyboardEnabled(bool enabled)
{
    CCLOG("cocos2d: CCLayer: unsupportted!");
}

/// isTouchEnabled getter
bool CCLayer::getIsTouchEnabled()
{
	return m_bIsTouchEnabled;
}
/// isTouchEnabled setter
void CCLayer::setIsTouchEnabled(bool enabled)
{
	if (m_bIsTouchEnabled != enabled)
	{
		m_bIsTouchEnabled = enabled;
		if (m_bIsRunning)
		{
			if (enabled)
			{
				this->registerWithTouchDispatcher();
			}
			else
			{
				// have problems?
				CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
			}
		}
	}
}

/// isAccelerometerEnabled getter
bool CCLayer::getIsAccelerometerEnabled()
{
	return m_bIsAccelerometerEnabled;
}
/// isAccelerometerEnabled setter
void CCLayer::setIsAccelerometerEnabled(bool enabled)
{
    if (enabled != m_bIsAccelerometerEnabled)
    {
        m_bIsAccelerometerEnabled = enabled;

        if (m_bIsRunning)
        {
            if (enabled)
            {
                UIAccelerometer::sharedAccelerometer()->addDelegate(this);
            }
            else
            {
                UIAccelerometer::sharedAccelerometer()->removeDelegate(this);
            }
        }
    }
}

/// isKeypadEnabled getter
bool CCLayer::getIsKeypadEnabled()
{
    return m_bIsKeypadEnabled;
}
/// isKeypadEnabled setter
void CCLayer::setIsKeypadEnabled(bool enabled)
{
    if (enabled != m_bIsKeypadEnabled)
    {
        m_bIsKeypadEnabled = enabled;

        if (m_bIsRunning)
        {
            if (enabled)
            {
                CCKeypadDispatcher::sharedDispatcher()->addDelegate(this);
            }
            else
            {
                CCKeypadDispatcher::sharedDispatcher()->removeDelegate(this);
            }
        }
    }
}


/// Callbacks
void CCLayer::onEnter()
{
	// register 'parent' nodes first
	// since events are propagated in reverse order
	if (m_bIsTouchEnabled)
	{
		this->registerWithTouchDispatcher();
	}

	// then iterate over all the children
	CCNode::onEnter();

    // add this layer to concern the Accelerometer Sensor
    if (m_bIsAccelerometerEnabled)
    {
        UIAccelerometer::sharedAccelerometer()->addDelegate(this);
    }

    // add this layer to concern the kaypad msg
    if (m_bIsKeypadEnabled)
    {
        CCKeypadDispatcher::sharedDispatcher()->addDelegate(this);
    }
}

void CCLayer::onExit()
{
	if( m_bIsTouchEnabled )
	{
		CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	}

    // remove this layer from the delegates who concern Accelerometer Sensor
    if (m_bIsAccelerometerEnabled)
    {
        UIAccelerometer::sharedAccelerometer()->removeDelegate(this);
    }

    // remove this layer from the delegates who concern the kaypad msg
    if (m_bIsKeypadEnabled)
    {
        CCKeypadDispatcher::sharedDispatcher()->removeDelegate(this);
    }

	CCNode::onExit();
}

void CCLayer::onEnterTransitionDidFinish()
{
    if (m_bIsAccelerometerEnabled)
    {
        UIAccelerometer::sharedAccelerometer()->addDelegate(this);
    }
    
    CCNode::onEnterTransitionDidFinish();
}

bool CCLayer::ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent)
{
	NSAssert(false, "Layer#ccTouchBegan override me");
	return true;
}

/// ColorLayer


CCLayerColor::CCLayerColor()
{
}
CCLayerColor::~CCLayerColor()
{
}

// Opacity and RGB color protocol
/// opacity getter
GLubyte CCLayerColor::getOpacity()
{
	return m_cOpacity;
}
/// opacity setter
void CCLayerColor::setOpacity(GLubyte var)
{
	m_cOpacity = var;
	updateColor();
}

/// color getter
ccColor3B CCLayerColor::getColor()
{
	return m_tColor;
}

/// color setter
void CCLayerColor::setColor(ccColor3B var)
{
	m_tColor = var;
	updateColor();
}


/// blendFunc getter
ccBlendFunc CCLayerColor::getBlendFunc()
{
	return m_tBlendFunc;
}
/// blendFunc setter
void CCLayerColor::setBlendFunc(ccBlendFunc var)
{
	m_tBlendFunc = var;
}


CCLayerColor * CCLayerColor::layerWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
	CCLayerColor * pLayer = new CCLayerColor();
	if( pLayer && pLayer->initWithColorWidthHeight(color,width,height))
	{
		pLayer->autorelease();
		return pLayer;
	}
	CCX_SAFE_DELETE(pLayer);
	return NULL;
}
CCLayerColor * CCLayerColor::layerWithColor(ccColor4B color)
{
	CCLayerColor * pLayer = new CCLayerColor();
	if(pLayer && pLayer->initWithColor(color))
	{
		pLayer->autorelease();
		return pLayer;
	}
	CCX_SAFE_DELETE(pLayer);
	return NULL;
}

bool CCLayerColor::initWithColorWidthHeight(ccColor4B color, GLfloat width, GLfloat height)
{
	// default blend function
	m_tBlendFunc.src = CC_BLEND_SRC;
	m_tBlendFunc.dst = CC_BLEND_DST;

	m_tColor.r = color.r;
	m_tColor.g = color.g;
	m_tColor.b = color.b;
	m_cOpacity = color.a;

	for (unsigned int i=0; i<sizeof(m_pSquareVertices) / sizeof(m_pSquareVertices[0]); i++ )
	{
		m_pSquareVertices[i] = 0.0f;
	}

	this->updateColor();
	this->setContentSize(CGSizeMake(width,height));
	return true;
}

bool CCLayerColor::initWithColor(ccColor4B color)
{
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	this->initWithColorWidthHeight(color, s.width, s.height);
	return true;
}

/// override contentSize
void CCLayerColor::setContentSize(CGSize size)
{
	m_pSquareVertices[2] = size.width * CC_CONTENT_SCALE_FACTOR();
	m_pSquareVertices[5] = size.height * CC_CONTENT_SCALE_FACTOR();
	m_pSquareVertices[6] = size.width * CC_CONTENT_SCALE_FACTOR();
	m_pSquareVertices[7] = size.height * CC_CONTENT_SCALE_FACTOR();

	CCLayer::setContentSize(size);
}

void CCLayerColor::changeWidthAndHeight(GLfloat w ,GLfloat h)
{
	this->setContentSize(CGSizeMake(w, h));
}

void CCLayerColor::changeWidth(GLfloat w)
{
	this->setContentSize(CGSizeMake(w, m_tContentSize.height));
}

void CCLayerColor::changeHeight(GLfloat h)
{
	this->setContentSize(CGSizeMake(m_tContentSize.width, h));
}

void CCLayerColor::updateColor()
{
	for( unsigned int i=0; i < 4; i++ )
	{
		m_pSquareColors[i * 4]     = m_tColor.r;
		m_pSquareColors[i * 4 + 1] = m_tColor.g;
		m_pSquareColors[i * 4 + 2] = m_tColor.b;
		m_pSquareColors[i * 4 + 3] = m_cOpacity;
	}
}

void CCLayerColor::draw()
{		
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, GL_COLOR_ARRAY
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

	glVertexPointer(2, GL_FLOAT, 0, m_pSquareVertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, m_pSquareColors);

	bool newBlend = false;
	if( m_tBlendFunc.src != CC_BLEND_SRC || m_tBlendFunc.dst != CC_BLEND_DST ) {
		newBlend = true;
		glBlendFunc(m_tBlendFunc.src, m_tBlendFunc.dst);
	}
	else if( m_cOpacity != 255 ) {
		newBlend = true;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if( newBlend )
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);

	// restore default GL state
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
}

//
// CCLayerGradient
// 
CCLayerGradient* CCLayerGradient::layerWithColor(ccColor4B start, ccColor4B end)
{
    CCLayerGradient * pLayer = new CCLayerGradient();
    if( pLayer && pLayer->initWithColor(start, end))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CCX_SAFE_DELETE(pLayer);
    return NULL;
}

CCLayerGradient* CCLayerGradient::layerWithColor(ccColor4B start, ccColor4B end, CGPoint v)
{
    CCLayerGradient * pLayer = new CCLayerGradient();
    if( pLayer && pLayer->initWithColor(start, end, v))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CCX_SAFE_DELETE(pLayer);
    return NULL;
}

bool CCLayerGradient::initWithColor(ccColor4B start, ccColor4B end)
{
    return initWithColor(start, end, ccp(0, -1));
}

bool CCLayerGradient::initWithColor(ccColor4B start, ccColor4B end, CGPoint v)
{
    m_endColor.r  = end.r;
    m_endColor.g  = end.g;
    m_endColor.b  = end.b;

    m_cEndOpacity   = end.a;
    m_cStartOpacity	= start.a;
    m_AlongVector   = v;

    start.a	= 255;
    return CCLayerColor::initWithColor(start);
}

void CCLayerGradient::updateColor()
{
    CCLayerColor::updateColor();

    float h = sqrtf(m_AlongVector.x * m_AlongVector.x + m_AlongVector.y * m_AlongVector.y);
    if (h == 0)
        return;

    double c = sqrt(2.0);
    CGPoint u = ccp(m_AlongVector.x / h, m_AlongVector.y / h);

    float opacityf = (float)m_cOpacity / 255.0f;

    ccColor4B S = {
        (unsigned char) m_tColor.r,
        (unsigned char) m_tColor.g,
        (unsigned char) m_tColor.b,
        (unsigned char) (m_cStartOpacity * opacityf)
    };

    ccColor4B E = {
        (unsigned char) m_endColor.r,
        (unsigned char) m_endColor.g,
        (unsigned char) m_endColor.b,
        (unsigned char) (m_cEndOpacity * opacityf)
    };

    // (-1, -1)
    m_pSquareColors[0]  = (GLubyte) (E.r + (S.r - E.r) * ((c + u.x + u.y) / (2.0f * c)));
    m_pSquareColors[1]  = (GLubyte) (E.g + (S.g - E.g) * ((c + u.x + u.y) / (2.0f * c)));
    m_pSquareColors[2]  = (GLubyte) (E.b + (S.b - E.b) * ((c + u.x + u.y) / (2.0f * c)));
    m_pSquareColors[3]  = (GLubyte) (E.a + (S.a - E.a) * ((c + u.x + u.y) / (2.0f * c)));
    // (1, -1)
    m_pSquareColors[4]  = (GLubyte) (E.r + (S.r - E.r) * ((c - u.x + u.y) / (2.0f * c)));
    m_pSquareColors[5]  = (GLubyte) (E.g + (S.g - E.g) * ((c - u.x + u.y) / (2.0f * c)));
    m_pSquareColors[6]  = (GLubyte) (E.b + (S.b - E.b) * ((c - u.x + u.y) / (2.0f * c)));
    m_pSquareColors[7]  = (GLubyte) (E.a + (S.a - E.a) * ((c - u.x + u.y) / (2.0f * c)));
    // (-1, 1)
    m_pSquareColors[8]  = (GLubyte) (E.r + (S.r - E.r) * ((c + u.x - u.y) / (2.0f * c)));
    m_pSquareColors[9]  = (GLubyte) (E.g + (S.g - E.g) * ((c + u.x - u.y) / (2.0f * c)));
    m_pSquareColors[10] = (GLubyte) (E.b + (S.b - E.b) * ((c + u.x - u.y) / (2.0f * c)));
    m_pSquareColors[11] = (GLubyte) (E.a + (S.a - E.a) * ((c + u.x - u.y) / (2.0f * c)));
    // (1, 1)
    m_pSquareColors[12] = (GLubyte) (E.r + (S.r - E.r) * ((c - u.x - u.y) / (2.0f * c)));
    m_pSquareColors[13] = (GLubyte) (E.g + (S.g - E.g) * ((c - u.x - u.y) / (2.0f * c)));
    m_pSquareColors[14] = (GLubyte) (E.b + (S.b - E.b) * ((c - u.x - u.y) / (2.0f * c)));
    m_pSquareColors[15] = (GLubyte) (E.a + (S.a - E.a) * ((c - u.x - u.y) / (2.0f * c)));
}

ccColor3B CCLayerGradient::getStartColor()
{
    return m_tColor;
}

void CCLayerGradient::setStartColor(ccColor3B colors)
{
    setColor(colors);
}

void CCLayerGradient::setEndColor(ccColor3B colors)
{
    m_endColor = colors;
    updateColor();
}

ccColor3B CCLayerGradient::getEndColor()
{
    return m_endColor;
}

void CCLayerGradient::setStartOpacity(GLubyte o)
{
    m_cStartOpacity = o;
    updateColor();
}

GLubyte CCLayerGradient::getStartOpacity()
{
    return m_cStartOpacity;
}

void CCLayerGradient::setEndOpacity(GLubyte o)
{
    m_cEndOpacity = o;
    updateColor();
}

GLubyte CCLayerGradient::getEndOpacity()
{
    return m_cEndOpacity;
}

void CCLayerGradient::setAlongVector(CGPoint var)
{
    m_AlongVector = var;
    updateColor();
}

CGPoint CCLayerGradient::getAlongVector()
{
    return m_AlongVector;
}

/// MultiplexLayer

CCMultiplexLayer::CCMultiplexLayer()
{
}
CCMultiplexLayer::~CCMultiplexLayer()
{
	m_pLayers->release();
}

CCMultiplexLayer * CCMultiplexLayer::layerWithLayers(CCLayer * layer, ...)
{
	va_list args;
	va_start(args,layer);

	CCMultiplexLayer * pMultiplexLayer = new CCMultiplexLayer();
	if(pMultiplexLayer && pMultiplexLayer->initWithLayers(layer, args))
	{
		pMultiplexLayer->autorelease();
		va_end(args);
		return pMultiplexLayer;
	}
	va_end(args);
	CCX_SAFE_DELETE(pMultiplexLayer);
	return NULL;
}

bool CCMultiplexLayer::initWithLayers(CCLayer *layer, va_list params)
{
	m_pLayers = new NSMutableArray<CCLayer*>(5);
	//m_pLayers->retain();

	m_pLayers->addObject(layer);

	CCLayer *l = va_arg(params,CCLayer*);
	while( l ) {
		m_pLayers->addObject(l);
		l = va_arg(params,CCLayer*);
	}

	m_nEnabledLayer = 0;
	this->addChild(m_pLayers->getObjectAtIndex(m_nEnabledLayer));

	return true;
}


void CCMultiplexLayer::switchTo(unsigned int n)
{
	NSAssert( n < m_pLayers->count(), "Invalid index in MultiplexLayer switchTo message" );

	this->removeChild(m_pLayers->getObjectAtIndex(m_nEnabledLayer), true);

	m_nEnabledLayer = n;

	this->addChild(m_pLayers->getObjectAtIndex(n));
}

void CCMultiplexLayer::switchToAndReleaseMe(unsigned int n)
{
	NSAssert( n < m_pLayers->count(), "Invalid index in MultiplexLayer switchTo message" );

	this->removeChild(m_pLayers->getObjectAtIndex(m_nEnabledLayer), true);

	//[layers replaceObjectAtIndex:enabledLayer withObject:[NSNull null]];
	m_pLayers->replaceObjectAtIndex(m_nEnabledLayer, NULL);

	m_nEnabledLayer = n;

	this->addChild(m_pLayers->getObjectAtIndex(n));
}
}//namespace   cocos2d 
