#pragma once

#include <windows.h>
#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

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
#endif // _DEBUG

class CLoginDialog : public CWindowWnd, public INotifyUI
{
public:
	explicit CLoginDialog(int a);
	virtual ~CLoginDialog();

	LPCTSTR GetWindowClassName() const { return _T("Login test"); }
	UINT GetClassStyle() const { return CS_DBLCLKS | UI_CLASSSTYLE_FRAME; }

	void OnFinalMessage(HWND hWnd);

	void Init();

	void OnPrepare();
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI& msg);

protected:
	CPaintManagerUI m_paintManagerUI;

private:
	CButtonUI* m_pMinBtn{ nullptr };
	CButtonUI* m_pCloseBtn{ nullptr };
};