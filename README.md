# dui-learn


1) main()是WINDOWS的控制台程序（32BIT）或DOS程序（16BIT）,
2) WinMain()是WINDOWS的GUI程序,
wmain()是UNICODE版本的main(),
3)_tmain()是个宏,如果是UNICODE则他是wmain()否则他是main()
外,wmain也是main的另一個别名,是为了支持二个字节的语言环境

//声明:
IsIconic(
  hWnd: HWND {窗口句柄}
): BOOL;

IsZoomed(
  hWnd: HWND {窗口句柄}
): BOOL;

OffsetRect
GetWindowRect
CreateRoundRectRgn

int CombineRgn(
  [in] HRGN hrgnDst,
  [in] HRGN hrgnSrc1,
  [in] HRGN hrgnSrc2,
  [in] int  iMode
);
