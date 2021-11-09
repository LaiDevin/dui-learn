#include <windows.h>
#include "UIlib.h"

using namespace DuiLib;

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#ifdef _DEBUG
#ifdef _UNICODE
#pragma comment(lib, "..\\lib\\DuiLib_ud.lib")
#else
#pragma comment(lib, "..\\lib\\DuiLib_d.lib")
#endif

#else
#ifdef _UNICODE
#pragma comment(lib, "..\\lib\\DuiLib_u.lib")
#else
#pragma comment(lib, "..\\lib\\DuiLib.lib")
#endif
#endif

class CTestWindow : public CWindowWnd, public INotifyUI
{
public:
	CTestWindow() 
	{
	
	}

	LPCTSTR GetWindowClassName() const { return _T("Test Window"); }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; }

	void OnFinalMessage(HWND hWnd) { (void)hWnd; delete this; }

	void Notify(TNotifyUI& msg)
	{
		if (msg.sType == DUI_MSGTYPE_CLICK) 
		{
			if (msg.pSender->GetName() == _T("closebtn"))
			{
				Close();
			}
		}
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_CREATE)
		{
			m_pm.Init(m_hWnd);
			CControlUI* pBtn = new CButtonUI;
			pBtn->SetName(_T("closebtn"));
			pBtn->SetBkColor(0Xffff0000);
			m_pm.AttachDialog(pBtn);
			m_pm.AddNotifier(this);
			return 0;
		} 
		else if (uMsg == WM_DESTROY)
		{
			::PostQuitMessage(0);
		}
		LRESULT res;
		if (m_pm.MessageHandler(uMsg, wParam, lParam, res))
		{
			return res;
		}

		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

	~CTestWindow() 
	{
	
	}

protected:
	CPaintManagerUI m_pm;

};

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CTestWindow* testWnd = new CTestWindow;
	if (!testWnd)
	{
		return -1;
	}

	testWnd->Create(nullptr, _T("test window"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	testWnd->CenterWindow();
	testWnd->ShowModal();
	CPaintManagerUI::MessageLoop();
	return 0;
}