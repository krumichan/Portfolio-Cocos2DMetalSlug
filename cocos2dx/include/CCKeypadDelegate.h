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

#ifndef __CCKEYPAD_DELEGATE_H__
#define __CCKEYPAD_DELEGATE_H__


#include "ccxCommon.h"
#include "NSObject.h"

namespace   cocos2d {

class CCX_DLL CCKeypadDelegate
{
public:
    //! call the release() in child layer
    virtual void KeypadDestroy() {}
    //! call the retain() in child layer
    virtual void KeypadKeep() {}

    // The back key clicked
    virtual void keyBackClicked() {}

    // The menu key clicked. only avialble on uphone & android
    virtual void keyMenuClicked() {};
};

/**
@brief
CCKeypadHandler
Object than contains the CCKeypadDelegate.
*/
class CCX_DLL CCKeypadHandler : public NSObject
{
public:
    virtual ~CCKeypadHandler(void);

    /** delegate */
    CCKeypadDelegate* getDelegate();
    void setDelegate(CCKeypadDelegate *pDelegate);

    /** initializes a CCKeypadHandler with a delegate */
    virtual bool initWithDelegate(CCKeypadDelegate *pDelegate);

public:
    /** allocates a CCKeypadHandler with a delegate */
    static CCKeypadHandler* handlerWithDelegate(CCKeypadDelegate *pDelegate);

protected:
    CCKeypadDelegate* m_pDelegate;
};

} //namespace   cocos2d 

#endif // __CCKEYPAD_DELEGATE_H__
