#include "CCXApplication.h"
#include "CCXEGLView.h"
#include "cocos2d.h"
using namespace cocos2d;
class  AppDelegate  :  public cocos2d::CCXApplication{
public:
	AppDelegate(){m_pMainWnd = NULL;}
	~AppDelegate(){CCX_SAFE_DELETE(m_pMainWnd);}

	virtual bool    applicationDidFinishLaunching();
	virtual void    applicationDidEnterBackground(){;}
	virtual void    applicationWillEnterForeground(){;}

protected:
    cocos2d::CCXEGLView *   m_pMainWnd;
};