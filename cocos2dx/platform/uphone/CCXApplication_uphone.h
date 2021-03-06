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

#ifndef __CCX_APPLICATION_UPHONE_H__
#define __CCX_APPLICATION_UPHONE_H__

#include "CGGeometry.h"

#include "TG3.h"

#include "CCDirector.h"

namespace   cocos2d {

class CCX_DLL CCXApplication : public TApplication
{
public:
    CCXApplication();
    virtual ~CCXApplication();

    virtual Boolean EventHandler(EventType * pEvent);

    /**
    @brief	Implement CCDirector and sense init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    @brief	rotate main window by device orientation.
    @param  nOritation device orientation enum value.
    @see    ccDeviceOrientation
    */
	ccDeviceOrientation setDeviceOrientation(ccDeviceOrientation eOritation);

    /**
    @brief	Get status bar rectangle in EGLView window.
    */
    CGRect statusBarFrame();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground() {}

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground() {}

    /**
    @brief	Get current applicaiton instance.
    @return Current application instance pointer.
    */
    static CCXApplication * sharedApplication();

    void StartMainLoop();
    void StopMainLoop();

    /**
    @brief Get the data path of the Application.
    @return If the app is installed,the return value is the path of .so file.
            else the return value is "/NEWPLUS/TG3/APP/"
    */
    const char* getAppDataPath();

    void setAnimationInterval(double interval);
    bool isInBackground();

private:
    static Int32 _OnAppIdle(MESSAGE_t * pMsg, UInt32 uData);

    MESSAGE_t   m_tMsg;
    bool        m_bRunning;
    bool        m_bNeedStop;
    bool        m_bInBackground;
    char        m_AppDataPath[EOS_FILE_MAX_PATH];
};

}       // end of namespace   cocos2d

#endif	// end of __CCX_APPLICATION_UPHONE_H__
