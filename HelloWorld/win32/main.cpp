#include "main.h"
#include "../AppDelegate.h"

HINSTANCE g_hInstance;

#include "st.h"
st* st::instance = NULL;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	g_hInstance = hInstance;

	int nRet = 0;
	AppDelegate app;
	nRet = app.Run();

	return nRet;
}
