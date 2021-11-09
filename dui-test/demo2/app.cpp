#include "app.h"

CLoginDialog::CLoginDialog(int a)
{

}

CLoginDialog::~CLoginDialog()
{

}

LRESULT CLoginDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	case WM_CREATE: lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCLBUTTONDBLCLK: break;

	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
		//去除显示的标题栏
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
		//解决按住左键或右键时会出现边框的问题
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
		//实现按住窗口（除按钮外）拖动窗口
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
		//获取边框最大最小值
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       ::PostQuitMessage(0); break;
	default:				bHandled = FALSE; break;
	}

	if (bHandled)
		return lRes;
	if (m_paintManagerUI.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CLoginDialog::Notify(TNotifyUI& msg)
{
	if (msg.sType == DUI_MSGTYPE_WINDOWINIT)
	{
		OnPrepare();
	}
	else if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender == m_pCloseBtn) {
			::PostQuitMessage(0);
			return;
		}
		if (msg.pSender == m_pMinBtn) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return;
		}
	} 
	else
	{
	}
}

void CLoginDialog::OnFinalMessage(HWND hWnd)
{
	(void)hWnd;
	delete this;
}

void CLoginDialog::Init()
{
	m_pMinBtn = static_cast<CButtonUI*>(m_paintManagerUI.FindControl(_T("minbtn")));
	m_pCloseBtn = static_cast<CButtonUI*>(m_paintManagerUI.FindControl(_T("closebtn")));
}

void CLoginDialog::OnPrepare()
{

}

LRESULT CLoginDialog::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleVal = ::GetWindowLong(*this, GWL_STYLE);
	styleVal &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleVal | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	m_paintManagerUI.Init(m_hWnd);
	CDialogBuilder bulider;
	CControlUI* pRoot = bulider.Create(_T("skin_nor.xml"), 0, NULL, &m_paintManagerUI);
	m_paintManagerUI.AttachDialog(pRoot);
	m_paintManagerUI.AddNotifier(this);
	Init();
	return 0;
}

LRESULT CLoginDialog::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	if (::IsZoomed(*this))
	{
		bHandled = TRUE;
		return 0;
	}
#endif

	SIZE szRoundCorner = m_paintManagerUI.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CLoginDialog::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right;
	lpMMI->ptMaxSize.y = rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT CLoginDialog::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (::IsIconic(*this)) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CLoginDialog::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CLoginDialog::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; 
	pt.x = GET_X_LPARAM(lParam); 
	pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_paintManagerUI.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_paintManagerUI.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}