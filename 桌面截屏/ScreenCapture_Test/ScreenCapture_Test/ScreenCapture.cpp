#include "stdafx.h"
#include "ScreenCapture.h"



BOOL PaintMouse(HDC hdc)
{
	HDC bufdc = NULL;
	CURSORINFO cursorInfo = { 0 };
	ICONINFO iconInfo = { 0 };
	HBITMAP bmpOldMask = NULL;

	bufdc = ::CreateCompatibleDC(hdc);
	::RtlZeroMemory(&iconInfo, sizeof(iconInfo));
	cursorInfo.cbSize = sizeof(cursorInfo);
	// ��ȡ�����Ϣ
	::GetCursorInfo(&cursorInfo);
	// ��ȡ���ͼ����Ϣ
	::GetIconInfo(cursorInfo.hCursor, &iconInfo);
	// ���� �׵׺����(AND)
	bmpOldMask = (HBITMAP)::SelectObject(bufdc, iconInfo.hbmMask);     
	::BitBlt(hdc, cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y, 20, 20,
		bufdc, 0, 0, SRCAND);
	// ���� �ڵײ�ɫ���(OR)
	::SelectObject(bufdc, iconInfo.hbmColor);
	::BitBlt(hdc, cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y, 20, 20,
		bufdc, 0, 0, SRCPAINT);

	// �ͷ���Դ
	::SelectObject(bufdc, bmpOldMask);
	::DeleteObject(iconInfo.hbmColor);
	::DeleteObject(iconInfo.hbmMask);
	::DeleteDC(bufdc);
	return TRUE;
}


BOOL ScreenCapture()
{

	HWND hDesktopWnd = GetDesktopWindow();
	HDC hdc = GetDC(hDesktopWnd);
	HDC mdc = CreateCompatibleDC(hdc);
	DWORD dwScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD dwScreenHeigh = GetSystemMetrics(SM_CYSCREEN);

	HBITMAP bmp = CreateCompatibleBitmap(hdc, dwScreenWidth, dwScreenHeigh);
	HGDIOBJ holdbmp = (HBITMAP)::SelectObject(mdc, bmp);
	::BitBlt(mdc,
		0, 0,
		dwScreenWidth,
		dwScreenHeigh,
		hdc,
		0, 0, SRCCOPY);
	PaintMouse(mdc);
	SaveBmp(bmp);
	return TRUE;


}
