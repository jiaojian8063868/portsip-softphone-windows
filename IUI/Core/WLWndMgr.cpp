#include "stdafx.h"

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG


int CWLWndMgr::SetEditMode(HWLWND hWnd, BOOL bEditMode)
{
	if (hWnd == NULL)
	{
		return -1;
	}

	return SetProp(hWnd, ISEDITMODE, (HANDLE)bEditMode);
}

BOOL CWLWndMgr::IsEditMode(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return FALSE;
	}

	return (BOOL)GetProp(hWnd, ISEDITMODE);
}

// ���õ��ؼ��Լ���Rgn
HRGN GetOnlyControlRgn(HWLWND hCtrl, BOOL bClientArea)
{
	if (hCtrl == NULL)
	{
		return NULL;
	}

	HRGN hRgnRet = NULL;

	CIUIRect rect;
	if (bClientArea)
	{
		GetClientRect(hCtrl, rect);
		ClientToScreen(hCtrl, rect);
		IUIScreenToClient(GetHostWnd(hCtrl), rect);
	}
	else
	{
		GetWindowRectToHWND(hCtrl, rect);
	}

	hRgnRet = CreateRectRgnIndirect(rect);

	HRGN hWindowRgn = NULL;
	GetWindowRgn(hCtrl, hWindowRgn);
	if (hWindowRgn != NULL)
	{
		HRGN hRgnCopy = NULL;
		CopyRgn(hRgnCopy, hWindowRgn);
		OffsetRgn(hRgnCopy, rect.left, rect.top);

		CombineRgn(hRgnRet, hRgnRet, hRgnCopy, RGN_AND);
		DeleteObject(hRgnCopy);
	}

	return hRgnRet;
}

// �ݹ��ô���Rgn���������������
HRGN GetCombineRgn(HWLWND hCtrl, BOOL bClientArea)
{
	if (hCtrl == NULL)
	{
		return NULL;
	}

	HRGN hRgnRet = GetOnlyControlRgn(hCtrl, bClientArea);

	HWLWND hParentCtrl = GetParent(hCtrl);

	if (hParentCtrl != NULL)
	{
		HRGN hParetnRgn = GetCombineRgn(hParentCtrl, FALSE);
		if (hParetnRgn != NULL)
		{
			CombineRgn(hRgnRet, hRgnRet, hParetnRgn, RGN_AND);
			DeleteObject(hParetnRgn);
		}
		else
		{
			_ASSERT(hParetnRgn != NULL);
		}
	}

	return hRgnRet;
}

int CWLWndMgr::SetClip(HWLWND hCtrl, HDC hDC, BOOL bClientArea)
{
	if (hCtrl == NULL || hDC == NULL)
	{
		return -1;
	}

	// ��ϸ����ڻ�Ϻ�HRGN������SetWindowRgn���õģ����Լ����ꡢ�Լ�SetWindowRgn���õ�HRGN
	// �������ڻ�Ϻ��HRGN��Ҳ�������ĸ����ڻ�Ϻ��Rgn�����ꡢSetWindowRgn��Щ���ɵ�.
	// ���ԣ���Ҫ�ݹ���
	HRGN hRgn = NULL;
	if (SendMessage(hCtrl, WM_WL_ISUSERECTF, 0, 0))
	{
		Gdiplus::RectF rectF;
		GetWindowRectFToParent(hCtrl, &rectF);
		//TODO: ������겻��
		hRgn = CreateRectRgn(0, 0, (int)rectF.Width, (int)rectF.Height);
	}
	else
	{
		hRgn = GetCombineRgn(hCtrl, bClientArea);

#ifdef _DEBUG
		POINT pt;
		GetViewportOrgEx(hDC, &pt);

		CIUIRect rcRgn;
		GetRgnBox(hRgn, rcRgn);

		//IUITRACE(_T("%s(%08x) Viewport: x=%d, y=%d; HRGN(left=%d, top=%d, width=%d, height=%d\n"),
		//	pCtrl->GetClassName(), pCtrl,
		//	pt.x, pt.y, rcRgn.left, rcRgn.top, rcRgn.Width(), rcRgn.Height());
		int n = 0;
#endif
	}

	// SelectClipRgn�ڲ�������HRGN�Ŀ��������ԣ�����SelectClipRgn֮��
	// �����HRGN���Ա�ѡ�������HDC�����߿�ֱ��ɾ����
	// ��ע��SelectClipRgnѡ���HRGN������HDC�ӵ�Ӱ�죬������HRGN������Ϊ(0, 0, 100, 100)
	// ���ӵ�Ϊ(100, 100)���򲻻����κ����ݱ����ƣ����ӵ�Ϊ(80, 80)ʱ����ֻ��(80,80)��
	// (100, 100)֮�䡢���Ϊ��20 * 20����������ݿɱ����Ƴ�����
	SelectClipRgn(hDC, hRgn);
	DeleteObject(hRgn);

	return 0;
}
