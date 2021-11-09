#include "app.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr))
		return -1;

	CLoginDialog* ploginDlg = new CLoginDialog(10);
	if (!ploginDlg)
	{
		return -1;
	}
	ploginDlg->Create(nullptr, _T("Login"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 400, 240);
	ploginDlg->CenterWindow();
	::ShowWindow(*ploginDlg, SW_SHOW);
	CPaintManagerUI::MessageLoop();
	::CoUninitialize();
	return 0;
}