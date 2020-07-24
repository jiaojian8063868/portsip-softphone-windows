#include "StdAfx.h"
#include <zmouse.h>
#pragma comment (lib, "comctl32.lib")

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG

DECLARE_HANDLE(HZIP);    // An HZIP identifies a zip file that has been opened
typedef DWORD ZRESULT;
#define OpenZip OpenZipU
#define CloseZip(hz) CloseZipU(hz)
extern HZIP OpenZipU(void *z, unsigned int len, DWORD flags);
//extern ZRESULT CloseZipU(HZIP hz);

namespace IUI
{

	enum CD_DUI
	{
		CD_DUI_FIRST = 0xFFFFFFFF - 111,

		CD_DUI_POINTER = 0xFFFFFFFF - 111, ///< �õ�IUI�ؼ�ָ��
		CD_DUI_CLASS = 0xFFFFFFFF - 110, ///< �õ�IUI�ؼ�����
		CD_DUI_NAME = 0xFFFFFFFF - 109, ///< �õ�IUI�ؼ����֣������ڿؼ�ID��������ʶ�ؼ���
		CD_DUI_CAPTION = 0xFFFFFFFF - 108, ///< �õ�IUI�ؼ�����
		CD_DUI_RECT = 0xFFFFFFFF - 107, ///< �õ�IUI�ؼ�λ��
		CD_DUI_COMMON = 0xFFFFFFFF - 106, ///< �õ�IUI��������
		CD_DUI_TEXT_COLOR = 0xFFFFFFFF - 105, ///< �õ�IUI�ؼ��ı���ɫ

		CD_DUI_LAST
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	//

	static UINT MapKeyState()
	{
		UINT uState = 0;

		if (::GetKeyState(VK_CONTROL) < 0)
		{
			uState |= MK_CONTROL;
		}

		if (::GetKeyState(VK_RBUTTON) < 0)
		{
			uState |= MK_RBUTTON;
		}

		if (::GetKeyState(VK_LBUTTON) < 0)
		{
			uState |= MK_LBUTTON;
		}

		if (::GetKeyState(VK_SHIFT) < 0)
		{
			uState |= MK_SHIFT;
		}

		if (::GetKeyState(VK_MENU) < 0)
		{
			uState |= MK_ALT;
		}

		return uState;
	}

	typedef struct tagFINDTABINFO
	{
		CWLWnd *pFocus;
		CWLWnd *pLast;
		bool bForward;
		bool bNextIsIt;
	} FINDTABINFO;

	typedef struct tagFINDSHORTCUT
	{
		TCHAR ch;
		bool bPickNext;
	} FINDSHORTCUT;

	/////////////////////////////////////////////////////////////////////////////////////

	static void GetChildWndRect(HWND hWnd, HWND hChildWnd, RECT &rcChildWnd)
	{
		::GetWindowRect(hChildWnd, &rcChildWnd);

		POINT pt;
		pt.x = rcChildWnd.left;
		pt.y = rcChildWnd.top;
		::ScreenToClient(hWnd, &pt);
		rcChildWnd.left = pt.x;
		rcChildWnd.top = pt.y;

		pt.x = rcChildWnd.right;
		pt.y = rcChildWnd.bottom;
		::ScreenToClient(hWnd, &pt);
		rcChildWnd.right = pt.x;
		rcChildWnd.bottom = pt.y;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	HPEN m_hUpdateRectPen = NULL;


	WindowCore::WindowCore()
		: m_pThis(NULL)
		, m_bEnableDPI(true)
		, m_hWndPaint(NULL)
		, m_hDcOffscreen(NULL)
		, m_hDcAlphaMask(NULL)
		, m_hbmpOffscreen(NULL)
		, m_pOffscreenBits(NULL)
		, m_hbmpAlphaMask(NULL)
		, m_pAlphaMaskBits(NULL)
		, m_hwndTooltip(NULL)
		, m_bShowUpdateRect(false)
		, m_uTimerID(0)
		, m_bPressedTabKey(false)
		, m_bNeedRelayoutChildren(FALSE)
		, m_bMouseCapture(false)
		, m_hInstance(NULL)
		, m_hResourceInstance(NULL)
		, m_pStrResourceZip(TEXT(""))
		, m_bCachedResourceZip(false)
		, m_hResourceZip(NULL)
		, m_pToolTip(NULL)
	{
		m_pToolTip = new TOOLINFO;

		if (m_hUpdateRectPen == NULL)
		{
			m_hUpdateRectPen = ::CreatePen(PS_SOLID, 1, RGB(220, 0, 0));
			// Boot Windows Common Controls (for the ToolTip control)
			::InitCommonControls();
		}

		m_szMinWindow.cx = 0;
		m_szMinWindow.cy = 0;
		m_szMaxWindow.cx = 0;
		m_szMaxWindow.cy = 0;
		::ZeroMemory(&m_rcCaption, sizeof(m_rcCaption));
		m_ptLastMousePos.x = m_ptLastMousePos.y = -1;
	}

	WindowCore::~WindowCore()
	{
		if (m_hUpdateRectPen)
		{
			::DeleteObject(m_hUpdateRectPen);
			m_hUpdateRectPen = NULL;
		}

		// Reset other parts...
		if (m_hwndTooltip != NULL)
		{
			::DestroyWindow(m_hwndTooltip);
		}

		if (m_hDcOffscreen != NULL)
		{
			::DeleteDC(m_hDcOffscreen);
		}

		if (m_hDcAlphaMask != NULL)
		{
			::DeleteDC(m_hDcAlphaMask);
		}

		if (m_hbmpOffscreen != NULL)
		{
			::DeleteObject(m_hbmpOffscreen);
		}

		if (m_hbmpAlphaMask != NULL)
		{
			::DeleteObject(m_hbmpAlphaMask);
		}

		delete m_pToolTip;
		m_pToolTip = NULL;
	}

	Window *WindowCore::GetBindWindow()
	{
		return m_pThis;
	}

	void WindowCore::Init(HWND hWnd)
	{
		_ASSERT(::IsWindow(hWnd));
		// Remember the window context we came from
		m_hWndPaint = hWnd;
	}

	HINSTANCE WindowCore::GetInstance()
	{
		return m_hInstance;
	}

	CIUIString WindowCore::GetInstancePath()
	{
		if (m_hInstance == NULL)
		{
			return _T('\0');
		}

		TCHAR tszModule[MAX_PATH + 1] = { 0 };
		::GetModuleFileName(m_hInstance, tszModule, MAX_PATH);
		CIUIString sInstancePath = tszModule;
		int pos = sInstancePath.ReverseFind(_T('\\'));

		if (pos >= 0)
		{
			sInstancePath = sInstancePath.Left(pos + 1);
		}

		return sInstancePath;
	}

	CIUIString WindowCore::GetCurrentPath()
	{
		TCHAR tszModule[MAX_PATH + 1] = { 0 };
		::GetCurrentDirectory(MAX_PATH, tszModule);
		return tszModule;
	}

	HINSTANCE WindowCore::GetResourceDll()
	{
		if (m_hResourceInstance == NULL)
		{
			return m_hInstance;
		}

		return m_hResourceInstance;
	}

	const CIUIString &WindowCore::GetResourceZip()
	{
		return m_pStrResourceZip;
	}

	bool WindowCore::IsCachedResourceZip()
	{
		return m_bCachedResourceZip;
	}

	HANDLE WindowCore::GetResourceZipHandle()
	{
		return m_hResourceZip;
	}

	void WindowCore::SetInstance(HINSTANCE hInst)
	{
		m_hInstance = hInst;
	}

	void WindowCore::SetCurrentPath(LPCTSTR pStrPath)
	{
		::SetCurrentDirectory(pStrPath);
	}

	void WindowCore::SetResourceDll(HINSTANCE hInst)
	{
		m_hResourceInstance = hInst;
	}

	void WindowCore::SetResourceZip(LPVOID pVoid, unsigned int len)
	{
		//if (m_pStrResourceZip == _T("membuffer"))
		//{
		//	return;
		//}

		//if (m_bCachedResourceZip && m_hResourceZip != NULL)
		//{
		//	CloseZip((HZIP)m_hResourceZip);
		//	m_hResourceZip = NULL;
		//}

		//m_pStrResourceZip = _T("membuffer");
		//m_bCachedResourceZip = true;

		//if (m_bCachedResourceZip)
		//{
		//	m_hResourceZip = (HANDLE)OpenZip(pVoid, len, 3);
		//}
	}

	void WindowCore::SetResourceZip(LPCTSTR pStrPath, bool bCachedResourceZip)
	{
		//if (m_pStrResourceZip == pStrPath && m_bCachedResourceZip == bCachedResourceZip)
		//{
		//	return;
		//}

		//if (m_bCachedResourceZip && m_hResourceZip != NULL)
		//{
		//	CloseZip((HZIP)m_hResourceZip);
		//	m_hResourceZip = NULL;
		//}

		//m_pStrResourceZip = pStrPath;
		//m_bCachedResourceZip = bCachedResourceZip;

		//if (m_bCachedResourceZip)
		//{
		//	CIUIString sFile = GetResourcePath();
		//	sFile += GetResourceZip();
		//	m_hResourceZip = (HANDLE)OpenZip((void *)sFile.GetBuffer(0), 0, 2);
		//}
	}

	HWND WindowCore::GetPaintWindow() const
	{
		return m_hWndPaint;
	}

	HWND WindowCore::GetTooltipWindow() const
	{
		return m_hwndTooltip;
	}

	HDC WindowCore::GetPaintDC() const
	{
		return m_hDcOffscreen;
	}

	HBITMAP WindowCore::GetOffscreenBitmap() const
	{
		return m_hbmpOffscreen;
	}

	void WindowCore::EnableDPI(bool bEnable)
	{
		m_bEnableDPI = bEnable;
	}

	bool WindowCore::IsDPIEnabled() const
	{
		return m_bEnableDPI;
	}

	POINT WindowCore::GetMousePos() const
	{
		return m_ptLastMousePos;
	}

	SIZE WindowCore::GetClientSize() const
	{
		RECT rcClient = { 0 };
		::GetClientRect(m_hWndPaint, &rcClient);
		return CIUISize(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
	}

	RECT &WindowCore::GetCaptionRect()
	{
		return m_rcCaption;
	}

	void WindowCore::SetCaptionRect(RECT &rcCaption)
	{
		if (rcCaption.bottom == -1)
		{
			// rcCaption.bottom == -1�Ǹ�����ֵ����ʾ������������λ�ö����Ա��϶��� ���Բ���DPI����
			m_rcCaption.left = JG_DPIGetDPIPointX(rcCaption.left, IsDPIEnabled());
			m_rcCaption.top = JG_DPIGetDPIPointY(rcCaption.top, IsDPIEnabled());
			m_rcCaption.right = JG_DPIGetDPIPointX(rcCaption.right, IsDPIEnabled());
			m_rcCaption.bottom = rcCaption.bottom;
		}
		else
		{
			m_rcCaption = JG_DPIGetDPIPadding(rcCaption, IsDPIEnabled());;
		}
	}

	SIZE WindowCore::GetMinInfo() const
	{
		return m_szMinWindow;
	}

	void WindowCore::SetMinInfo(int cx, int cy)
	{
		_ASSERT(cx >= 0 && cy >= 0);

		cx = JG_DPIGetDPIWidth(cx, IsDPIEnabled());
		cy = JG_DPIGetDPIHeight(cy, IsDPIEnabled());

		m_szMinWindow.cx = cx;
		m_szMinWindow.cy = cy;
	}

	SIZE WindowCore::GetMaxInfo() const
	{
		return m_szMaxWindow;
	}

	void WindowCore::SetMaxInfo(int cx, int cy)
	{
		_ASSERT(cx >= 0 && cy >= 0);
		m_szMaxWindow.cx = cx;
		m_szMaxWindow.cy = cy;
	}

	bool WindowCore::IsShowUpdateRect() const
	{
		return m_bShowUpdateRect;
	}

	void WindowCore::SetShowUpdateRect(bool show)
	{
		m_bShowUpdateRect = show;
	}

	int WindowCore::InitWindow(HWND hWnd, CWindowProp *pWindowPorp)
	{
		// �������ڳɹ��󣬴����ӿؼ��� �����ӿؼ����ŵ�WM_CREATE��Ϣ�С� �������ദ��WM_CREATEʱ��
		// �ӿؼ���û�д���������win32����rc�ĶԻ�����ʽһ�¡�
		Init(hWnd);

		m_pThis->m_rcXml = (RECT)pWindowPorp->m_rcControl;

		// ���ô�������
		m_pThis->BindStyle(pWindowPorp);

		// �����ӿؼ�
		int nChildCount = pWindowPorp->GetChildCount();
		for (int i = 0; i < nChildCount; ++i)
		{
			CControlBaseProp *pRootProp = pWindowPorp->GetChild(i);
			if (pRootProp->IsControl())
			{
				HWLWND hCtrl = CreatePreDefineChildControl(NULL, NULL,
						(CControlProp *)pRootProp, m_pThis->m_hVirtualRoot, m_hWndPaint, 0);
			}
		}

		// �����Ժ����
		m_pThis->m_pBindWindowProp = NULL;

		return 0;
	}

	int WindowCore::DestroyAllRootControls()
	{
		HWLWND hRoot = m_pThis->GetChild();
		for (; hRoot != NULL; hRoot = m_pThis->GetChild())
		{
			// IUI���û�����CWLWnd::DestroyWindow֮��
			// �������CWLWnd��������ĸ��ؼ��б����Ƴ�
			DestroyWindow(hRoot);
		}

		return 0;
	}

	int WindowCore::GetClipBox(LPCRECT lprcPSPaint, LPRECT lpRect)
	{
		if (lprcPSPaint == NULL || lpRect == NULL)
		{
			return -1;
		}

		CIUIRect rcClient;
		::GetClientRect(m_hWndPaint, &rcClient);

		CIUIRect rcClipHost;

		rcClipHost = lprcPSPaint;

		*lpRect = rcClipHost;

		return 0;
	}

	int WindowCore::DeleteDCResource()
	{
		if (m_hDcOffscreen != NULL)
		{
			::DeleteDC(m_hDcOffscreen);
			m_hDcOffscreen = NULL;
		}

		if (m_hbmpOffscreen != NULL)
		{
			::DeleteObject(m_hbmpOffscreen);
			m_hbmpOffscreen = NULL;
		}

		if (m_hDcAlphaMask != NULL)
		{
			::DeleteDC(m_hDcAlphaMask);
			m_hDcAlphaMask = NULL;
		}

		if (m_hbmpAlphaMask != NULL)
		{
			::DeleteObject(m_hbmpAlphaMask);
			m_hbmpAlphaMask = NULL;
		}

		return 0;
	}

	int WindowCore::PrepareDCResource(HDC hPaintDC)
	{
		if (m_hbmpOffscreen != NULL)
		{
			_ASSERT(FALSE);
			return -1;
		}

		CIUIRect rcClient;
		::GetClientRect(m_hWndPaint, rcClient);

		m_hDcOffscreen = ::CreateCompatibleDC(hPaintDC);

		m_hbmpOffscreen = ::CreateCompatibleBitmap(hPaintDC, rcClient.Width(), rcClient.Height());

		_ASSERT(m_hDcOffscreen);
		_ASSERT(m_hbmpOffscreen);

		return 0;
	}

	int WindowCore::ShowOffscreenDC(HDC hPaintDC, const CIUIRect &rcClipHost)
	{
		CIUIRect rcClient;
		::GetClientRect(m_hWndPaint, rcClient);

		::BitBlt(hPaintDC, rcClient.left, rcClient.top, rcClient.right - rcClient.left,
			rcClient.bottom - rcClient.top, m_hDcOffscreen, rcClient.left, rcClient.top, SRCCOPY);

		return 0;
	}

	void WindowCore::OnPaint(HDC hPaintDC, LPCRECT lprcPaint)
	{
		if (this == NULL)
		{
			return;
		}

#ifdef _DEBUG
		// ���ִ�е������CIUIString�ڲ��������󲿷�ԭ���ǰ�һ�����͵�ָ�룬ǿת����һ��
		// ���ͺ�ʹ�ã��Ӷ����ڴ��ƻ�����ġ� ��������CIUIString�޹ء�
		CIUIString strClass;
		::GetWindowText(m_hWndPaint, strClass.GetBufferSetLength(MAX_PATH), MAX_PATH);
		strClass.ReleaseBuffer();
#endif // _DEBUG

		// m_bNeedRelayoutΪtrue��ʾ��Ҫ���²��֡� �п����Ǵ��ڳߴ緢���˱仯,
		// ���߲������µ��ӿؼ��ȡ�
		// ֮������WM_PAINT�е������֣�����Ϊ��WM_SIZE�е����Ļ���ÿ���յ�WM_SIZE��Ҫ�������֡�
		// ��Ȼÿ��WM_SIZE����InvalidateRect����WM_PAINT���ȼ��Ƚϵ͡�
		// �����յ�WM_SIZE 100�Σ������п���ֻ�յ�WM_PAINT 20�Σ�����������ܡ�
		// Ϊ�˲���ÿ��WM_PAINT���ص����֣�����һ����־m_bNeedRelayout��
		// m_bNeedRelayout��WM_SIZE�л�����Ϊtrue�����������ؼ��Ȳ���ʱ��
		// Ҳ������Ϊtrue�� ԭ�������Ҫ���²���ʱ������Ϊtrue��
		int nRet = m_pThis->RelayoutChildren();

		DeleteDCResource();
		PrepareDCResource(hPaintDC);

		CIUIRect rcClipHost;
		GetClipBox(lprcPaint, rcClipHost);

		//
		// ������������
		//
		HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(m_hDcOffscreen, m_hbmpOffscreen);
		int iSaveDC = ::SaveDC(m_hDcOffscreen);

		m_pThis->OnDraw(m_hDcOffscreen, lprcPaint);

		::RestoreDC(m_hDcOffscreen, iSaveDC);

		// ��m_hDcOffscreen�е����ݿ�������Ļ�ϡ�
		ShowOffscreenDC(hPaintDC, rcClipHost);

		::SelectObject(m_hDcOffscreen, hOldBitmap);

#ifdef _DEBUG
		if (m_bShowUpdateRect)
		{
			RECT rcPaint = { 0 };
			::GetUpdateRect(m_hWndPaint, &rcPaint, FALSE);
			HPEN hOldPen = (HPEN)::SelectObject(hPaintDC, m_hUpdateRectPen);
			::SelectObject(hPaintDC, ::GetStockObject(HOLLOW_BRUSH));
			::Rectangle(hPaintDC, rcPaint.left, rcPaint.top, rcPaint.right, rcPaint.bottom);
			::SelectObject(hPaintDC, hOldPen);
		}
#endif
	}

	LRESULT WindowCore::OnSetCursor(WPARAM wParam, LPARAM lParam)
	{
		HWND hSender = HWND(wParam);
		if (m_hWndPaint == hSender)
		{
			// Get current cursor position relate to hwnd.
			CIUIPoint pt;
			GetCursorPos(&pt);
			::ScreenToClient(m_hWndPaint, &pt);

			HWLWND hNewHover = WindowFromPoint(m_hWndPaint, pt);

			if (IsWindow(hNewHover))
			{
				// Only enabled and visible window can handle mouse message.
				if (IsWindowEnabled(hNewHover) && IsWindowVisible(hNewHover))
				{
					// If the child windowless control's WM_SETCURSOR message return TRUE,
					// its parent window shouldn't receive WM_SETCURSOR message.
					// If the child handle the message, refuse parent to handle
					BOOL bRet = (BOOL)SendMessage(hNewHover, WM_SETCURSOR, wParam, lParam);
					if (bRet)
					{
						return 1;
					}
				}
			}
		}

		return 0;
	}

	LRESULT WindowCore::OnSpyControl(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		HWND hWndSender = (HWND)wParam;
		COPYDATASTRUCT *pcds = (COPYDATASTRUCT *)lParam;

		if (::IsWindow(hWndSender) && pcds != NULL && hWndSender != m_hWndPaint)
		{
			struct SIUIInfo
			{
				LONG lReserved;
				POINT pt;
				HWND hWndSender;
			};

			SIUIInfo *pUI = (SIUIInfo *)pcds->lpData;
			if (pUI == NULL || pUI->hWndSender == NULL)
			{
				return 0;
			}

			HWLWND hControlUI = WindowFromPoint(m_hWndPaint, pUI->pt);
			if (hControlUI == NULL)
			{
				return 0;
			}

			CIUIString strOld;
			::SendMessage(pUI->hWndSender, WM_GETTEXT, MAX_PATH, (LPARAM)strOld.GetBufferSetLength(MAX_PATH));
			strOld.ReleaseBuffer();

			if (pcds->dwData == CD_DUI_POINTER)
			{
				CIUIString strAddress;
				strAddress.Format(_T("%08x"), (DWORD_PTR)hControlUI);

				if (strOld != strAddress)
				{
					::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)strAddress.GetBuffer(0));
				}
			}
			else if (pcds->dwData == CD_DUI_TEXT_COLOR)
			{
				CIUIString strClass = GetClassName(hControlUI);
				if (strClass == _T("LabelUI")
					|| strClass == _T("ButtonUI")
					|| strClass == _T("TextUI")
					|| strClass == _T("OptionUI")
					|| strClass == _T("CheckBoxUI")
					|| strClass == _T("FaceButtonUI"))
				{
					Label *pLabel = (Label *)hControlUI->ci.pThis;

					CIUIString strColor;
					COLORREF crN;
					pLabel->GetTextColor(&crN, NULL);
					strColor.Format(_T("0x%08x"), crN);

					if (strOld != strColor)
					{
						::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)strColor.GetBuffer(0));
					}
				}
				else if (strClass == _T("RichEditUI"))
				{
					RichTextBox *pRichEdit = (RichTextBox *)hControlUI->ci.pThis;

					CHARFORMAT2 cf;
					pRichEdit->GetDefaultCharFormat(cf);

					CIUIString strColor;
					strColor.Format(_T("R:0x%x, G:0x%x, B:0x%x"),
						GetRValue(cf.crTextColor), GetGValue(cf.crTextColor), GetBValue(cf.crTextColor));

					if (strOld != strColor)
					{
						::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)strColor.GetBuffer(0));
					}
				}
				else
				{
					::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)_T("Not support"));
				}
			}
			else if (pcds->dwData == CD_DUI_CLASS)
			{
				CIUIString strClass;
				strClass = GetClassName(hControlUI);
				HWLWND hParent = GetParent(hControlUI);
				if (hParent != NULL)
				{
					strClass += _T(" /�� ");
					strClass += GetClassName(hParent);
				}

				if (strOld != strClass)
				{
					::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)strClass);
				}
			}
			else if (pcds->dwData == CD_DUI_NAME)
			{
				CIUIString strName;
				strName = GetName(hControlUI);
				HWLWND hParent = GetParent(hControlUI);
				if (hParent != NULL)
				{
					strName += _T(" /�� ");
					strName += GetName(hParent);
				}

				if (strOld != strName)
				{
					::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)strName);
				}
			}
			else if (pcds->dwData == CD_DUI_CAPTION)
			{
				if (strOld != (LPCTSTR)GetWindowText(hControlUI))
				{
					::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)GetWindowText(hControlUI));
				}
			}
			else if (pcds->dwData == CD_DUI_RECT)
			{
				RECT rcPos = GetWindowRectToParent(hControlUI);
				CIUIString strRect;
				strRect.Format(_T("(%d,%d)-(%d,%d) %d*%d"),
					rcPos.left, rcPos.top, rcPos.right, rcPos.bottom,
					rcPos.right - rcPos.left, rcPos.bottom - rcPos.top);

				CIUIRect rcPadding;
				GetLayoutInset(hControlUI, rcPadding);
				CIUIString strPadding;
				strPadding.Format(_T("  Padding: (%d, %d, %d, %d)"),
					rcPadding.left, rcPadding.top, rcPadding.right, rcPadding.bottom);

				strRect += strPadding;

				if (strOld != strRect)
				{
					::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)strRect.GetBuffer(0));
				}
			}
			else if (pcds->dwData == CD_DUI_COMMON)
			{
				CIUIString str;

				CIUIString strClass = GetClassName(hControlUI);
				if (strClass == _T("LabelUI")
					|| strClass == _T("ButtonUI")
					|| strClass == _T("TextUI")
					|| strClass == _T("OptionUI")
					|| strClass == _T("CheckBoxUI")
					|| strClass == _T("FaceButtonUI"))
				{
					Label *pLabel = (Label *)hControlUI->ci.pThis;

					//int nFontIndex = pLabel->GetFont();
					//TFontInfo *pFontInfo = NULL;
					//if (nFontIndex < 0 || nFontIndex >= m_aCustomFonts.GetSize())
					//{
					//	pFontInfo = GetDefaultFontInfo();
					//}
					//else
					//{
					//	pFontInfo = (TFontInfo *)m_aCustomFonts[nFontIndex];
					//}

					//if (pFontInfo != NULL)
					//{
					//	str.Format(_T("Font='%s'%d, FixedWidth: %s, FixedHeight: %s, "),
					//		pFontInfo->sFontName,
					//		pFontInfo->iSize,
					//		pLabel->IsFixedWidth() ? _T("true") : _T("false"),
					//		pLabel->IsFixedHeight() ? _T("true") : _T("false")
					//	);
					//}
				}
				else
				{
					str.Format(_T("FixedWidth: %s, FixedHeight: %s, "),
						IsFixedWidth(hControlUI) ? _T("true") : _T("false"),
						IsFixedHeight(hControlUI) ? _T("true") : _T("false")
					);
				}

				HWLWND hFocus = GetFocus();
				if (hFocus != NULL)
				{
					CIUIString strClass = GetClassName(hFocus);
					CIUIString strName = GetName(hFocus);
					CIUIString strText = GetWindowText(hFocus);

					CIUIString strFocus;
					strFocus.Format(_T("Focus:(cls:%s, name:%s)"), strClass, strName);
					str += strFocus;
				}

				if (strOld != str)
				{
					::SendMessage(pUI->hWndSender, WM_SETTEXT, 0, (LPARAM)str.GetBuffer(0));
				}
			}
			else
			{
				_ASSERT(FALSE);
			}

			return 1;
		}

		return 0;
	}

	void WindowCore::Term()
	{
		if (m_bCachedResourceZip && m_hResourceZip != NULL)
		{
			//CloseZip((HZIP)m_hResourceZip);
			m_hResourceZip = NULL;
		}
	}

	HWLWND WindowCore::GetFocus() const
	{
		return m_pThis->m_hFocus;
	}

	void WindowCore::SetCapture()
	{
		::SetCapture(m_hWndPaint);
		m_bMouseCapture = true;
	}

	void WindowCore::ReleaseCapture()
	{
		::ReleaseCapture();
		m_bMouseCapture = false;
	}

	BOOL WindowCore::IsCaptured()
	{
		return m_bMouseCapture;
	}

	CWLWnd *WindowCore::GetRoot() const
	{
		_ASSERT(FALSE);
		return NULL;//m_pThis->m_pRoot;
	}


	class CShadowWnd : public Window
	{
	public:
		CShadowWnd()
			: m_bCreated(FALSE)
			, m_pHostWnd(NULL)
		{
		}
		~CShadowWnd() {}

	protected:
		LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_GETMINMAXINFO:
			{
				MINMAXINFO *pmmi = (MINMAXINFO *)lParam;

				if (NULL != m_pHostWnd && m_bCreated)
				{
					// ��Ӱ���ڳߴ����Сֵ�����ֵ����Host��Ӱ��
					MINMAXINFO mmiHost;
					ZeroMemory(&mmiHost, sizeof(MINMAXINFO));
					::SendMessage(m_pHostWnd->GetSafeHwnd(), WM_GETMINMAXINFO, 0, (LPARAM)&mmiHost);

					CIUIRect rcShadowThinkness;
					Get9GridResizeParam(rcShadowThinkness);

					// ���Host�������������ߴ磬��ô��Ӱ����Ҳ��Ҫ�����������ߴ�
					if (0 != mmiHost.ptMaxSize.x || 0 != mmiHost.ptMaxSize.y)
					{
						pmmi->ptMaxSize.x = mmiHost.ptMaxSize.x + rcShadowThinkness.left + rcShadowThinkness.right;
						pmmi->ptMaxSize.y = mmiHost.ptMaxSize.y + rcShadowThinkness.top + rcShadowThinkness.bottom;
					}

					if (0 != mmiHost.ptMinTrackSize.x || 0 != mmiHost.ptMinTrackSize.y)
					{
						pmmi->ptMinTrackSize.x = mmiHost.ptMinTrackSize.x + rcShadowThinkness.left + rcShadowThinkness.right;
						pmmi->ptMinTrackSize.y = mmiHost.ptMinTrackSize.y + rcShadowThinkness.top + rcShadowThinkness.bottom;
					}

					if (0 != mmiHost.ptMaxTrackSize.x || 0 != mmiHost.ptMaxTrackSize.y)
					{
						pmmi->ptMaxTrackSize.x = mmiHost.ptMaxTrackSize.x + rcShadowThinkness.left + rcShadowThinkness.right;
						pmmi->ptMaxTrackSize.y = mmiHost.ptMaxTrackSize.y + rcShadowThinkness.top + rcShadowThinkness.bottom;
					}
				}
			}
			break;

			// ��Ӱ�������ŵ�ʱ��ͬ������Host���ڡ�
			// ��������£���Ӱ����ֻ��ͨ��������ţ�����ⲿ��ѯ����Ӱ���ھ����������
			// API������Ӱ���ں�Ҳ��Ҫͬ������Host���ڡ� ����Host�������ź�ҲҪͬ��������Ӱ
			// ���ڣ����ԣ�������ҪԤ����ѭ����
			case WM_WINDOWPOSCHANGED:
				if (NULL != m_pHostWnd && m_bCreated)
				{
					// ��Ϊ��Ӱ��������Topmostʱ��ҲΪHost��������WS_EX_TOPMOST���ԡ�
					LONG lExStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
					if ((lExStyle & WS_EX_TOPMOST) == WS_EX_TOPMOST)
					{
						LONG lParentExStyle = GetWindowLong(m_pHostWnd->GetSafeHwnd(), GWL_EXSTYLE);
						if ((lParentExStyle & WS_EX_TOPMOST) == 0)
						{
							::SetWindowPos(m_pHostWnd->GetSafeHwnd(), HWND_TOPMOST,
								0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
						}
					}

					//HDWP hDwp = BeginDeferWindowPos(2);
					//DeferWindowPos(hDwp, GetSafeHwnd(), NULL);
					// ͬ������
					//if (!m_bDragResizing)
					{
						CIUIRect rcShadow;
						::GetWindowRect(m_hWnd, rcShadow);

						CIUIRect rcShadowThinkness;
						Get9GridResizeParam(rcShadowThinkness);

						rcShadow.DeflateRect(rcShadowThinkness);

						CIUIRect rcOld;
						::GetWindowRect(m_pHostWnd->GetSafeHwnd(), rcOld);

						// Ϊ�˷�ֹ��ѭ��������¾�����һ���������ƶ�Host����
						if (rcOld != rcShadow)
						{
							::MoveWindow(m_pHostWnd->GetSafeHwnd(), rcShadow.left, rcShadow.top,
								rcShadow.Width(), rcShadow.Height(), TRUE);
							::UpdateWindow(m_pHostWnd->GetSafeHwnd());
						}
					}

					// �����Բ�ǣ�����rgn
				}
				break;

			// ��Host������仯�󣬻�����Ӱ���ڷ���WM_SYNC_HOST_POS��Ϣ
			case WM_SYNC_HOST_POS:
				if (NULL != m_pHostWnd && m_bCreated)
				{
					CIUIRect rcHost;
					::GetWindowRect(m_pHostWnd->GetSafeHwnd(), rcHost);

					CIUIRect rcShadowThinkness;
					Get9GridResizeParam(rcShadowThinkness);

					rcHost.InflateRect(rcShadowThinkness);

					CIUIRect rcOld;
					::GetWindowRect(GetSafeHwnd(), rcOld);

					// Ϊ�˷�ֹ��ѭ��������¾�����һ���������ƶ���Ӱ����
					if (rcOld != rcHost)
					{
						::MoveWindow(m_hWnd, rcHost.left, rcHost.top,
							rcHost.Width(), rcHost.Height(), TRUE);

						if (rcOld.Width() != rcHost.Width()
							|| rcOld.Height() != rcHost.Height())
						{
							Invalidate();
						}
					}
				}
				break;

			case WM_NCDESTROY:
			{
				Window::WindowProc(message, wParam, lParam);
				delete this;
				return 0;
			}

			default:
				break;
			}

			return Window::WindowProc(message, wParam, lParam);
		}

	public:
		BOOL m_bCreated;
		Window *m_pHostWnd;
	};

	// ʹ��˫���ڱ��߿���Ӱʱ��������Ӱ���ڡ� Ϊ��ʹHost���ڿͻ���͸������
	// ��Ӱ���ڵı���ͼֱ�������м��οյģ�alphaΪ0��
	int CreateShadowWindow(CWindowProp *pWindowProp, Window *pHostWnd)
	{
		if (!::IsWindow(pHostWnd->GetSafeHwnd()))
		{
			return -1;
		}

		CIUIString strShadowImage = (LPCTSTR)pWindowProp->m_strShadowBorder;
		if (strShadowImage.IsEmpty())
		{
			return -2;
		}

		CShadowWnd *pShadowWnd = new CShadowWnd;
		pShadowWnd->m_pHostWnd = pHostWnd;
		pShadowWnd->SetProject(pHostWnd->GetProject());

		DWORD dwExStyle = WS_EX_LAYERED;
		if ((bool)pWindowProp->m_bTransparentShadow)
		{
			dwExStyle |= WS_EX_TRANSPARENT;
		}

		CIUIRect rcHost;
		::GetWindowRect(pHostWnd->GetSafeHwnd(), rcHost);

		CIUIRect rcShadowThinkness = (RECT)pWindowProp->m_rcShadowThinkness;
		rcHost.InflateRect(rcShadowThinkness);

		BOOL bRet = pShadowWnd->CreateEx(dwExStyle, _T("IUI_Shadow"), NULL, WS_POPUP,
				rcHost, pHostWnd, 0);

		if (!bRet)
		{
			return -3;
		}

		::SendMessage(pHostWnd->GetSafeHwnd(), WM_SET_SHADOW_WINDOW, 0, (LPARAM)pShadowWnd->GetSafeHwnd());
		pShadowWnd->m_bCreated = TRUE;
		::SetProp(pShadowWnd->GetSafeHwnd(), _T("UpdateLayeredWindow"), (HANDLE)1);

		pShadowWnd->SetBkImage(strShadowImage);
		pShadowWnd->SetBkImageResizeMode(IRM_9GRID);
		pShadowWnd->Set9GridResizeParam(rcShadowThinkness);

		if ((bool)pWindowProp->m_bResizingBorder)
		{
			if ((bool)pWindowProp->m_bResizingShadow)
			{
				pShadowWnd->SetDragResizeFlag(TRUE);
			}
		}

		if (::IsWindowVisible(pHostWnd->GetSafeHwnd()))
		{
			pShadowWnd->Invalidate();
		}

		return 0;
	}

} // namespace IUI
