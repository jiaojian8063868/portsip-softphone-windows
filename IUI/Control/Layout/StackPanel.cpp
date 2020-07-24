#include "stdafx.h"

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG


namespace IUI
{
	StackPanel::StackPanel()
	{
		m_pvStackPanelChildList = NULL;
	}

	StackPanel::~StackPanel()
	{
		delete m_pvStackPanelChildList;
	}

	BOOL StackPanel::Create(
		__in CWLWndHandler *pUserHandler,
		DWORD dwStyle,
		const RECT &rect,
		HWND hParent,
		CWLWnd *pParentWnd,
		LPCTSTR lpszName)
	{
		return CWLWnd::Create(pUserHandler, IUI_STACKPANEL, NULL,
				dwStyle, rect, hParent, pParentWnd, lpszName);
	}

	int StackPanel::BindStyle(const CControlProp *pCtrlProp)
	{
		StackPanel_BindStyle(m_hWnd, (CStackPanelProp *)pCtrlProp);

		return 0;
	}

	int StackPanel::SetBkImage(
		UINT uMask,
		LPCTSTR lpszImageNameN,
		LPCTSTR lpszImageNameD,
		BOOL bRedraw)
	{
		IUISetControlBkImage2(m_hWnd, uMask, lpszImageNameN, lpszImageNameD);

		if (bRedraw)
		{
			Invalidate();
		}

		return 0;
	}

	int StackPanel::GetBkImage(
		UINT uMask,
		BOOL *pbCombineImage,
		CIUIString *pstrCombineImageName,
		CIUIString *pstrImageNameN, CIUIString *pstrImageNameD) const
	{
		_ASSERT(IsWindow());

		return IUIGetControlBkImage2(m_hWnd, uMask, pbCombineImage, pstrCombineImageName,
				pstrImageNameN, pstrImageNameD);
	}

	/////////////////////////////////////////////////////////////////////////////
	// Core

	int StackPanel_OnPaint(_LABEL *pLb, HDC hDC, LPCRECT lprcPaint)
	{
		if (!IsRedraw(pLb->hwnd))
		{
			return 1;
		}

		CIUIRect rcClient;
		GetClientRect(pLb->hwnd, rcClient);
		CIUIRect rcPaint;
		if (!::IntersectRect(&rcPaint, lprcPaint, rcClient))
		{
			return 2;
		}

		HDC hDCTarget = NULL;
		HDC hMemDC = NULL;
		HBITMAP hOldBmp = NULL;

		// ����GDI��֧�ָ��������꣬���Ե�ʹ��RectF����ʱ������GDI+����
		// RectF���곣��������ƽ���ƶ��Ķ����� ��ʱ���Ȱѿؼ����ݻ���һ��32λalphaλͼ��
		// ����ٰ�λͼ���Ƶ�ָ�����ꡣ
		HBITMAP hBmp = GetCachedAlphaBitmap(pLb->hwnd);
		if (IsUseRectF(pLb->hwnd))
		{
			hMemDC = ::CreateCompatibleDC(hDC);
			hDCTarget = hMemDC;

			void *pBits = NULL;
			if (hBmp != NULL)
			{
				DeleteObject(hBmp);
				hBmp = NULL;
			}

			hBmp = Create32BitsHBITMAP(rcClient.Width(), rcClient.Height(),
					32, BI_RGB, &pBits);
			SetCachedAlphaBitmap(pLb->hwnd, hBmp);
			hOldBmp = (HBITMAP)::SelectObject(hDCTarget, hBmp);
		}
		else
		{
			hDCTarget = hDC;
		}

		//
		// 1. �Ȼ����Լ�
		//
		BeforePaint(pLb->hwnd, hDCTarget);
		DrawBkColor(pLb->hwnd, hDCTarget, lprcPaint);
		Label_DrawBkImage(pLb, hDCTarget, NULL);
		DrawBorder(pLb->hwnd, hDCTarget);
		AfterPaint(pLb->hwnd, hDCTarget);

		if (IsUseRectF(pLb->hwnd))
		{
			if (hMemDC != NULL && hOldBmp != NULL)
			{
				// ����m_hCacheAlphaBmp
				::SelectObject(hMemDC, hOldBmp);
				DeleteDC(hMemDC);

				// ��ΪGDI+����ʱ�õ�������GDIʱ��ͬ�����������ӿ�
				POINT pt;
				SetViewportOrgEx(hDC, 0, 0, &pt);

				Gdiplus::Graphics g(hDC);

				// ��HBITMAPת��Bitmap��Bitmap::FromHBITMAP��Bug
				Gdiplus::Bitmap *pBmp = CreateBitmapFromHBITMAP(hBmp);
				g.DrawImage(pBmp, *GetRectF(pLb->hwnd));
				::delete pBmp;
				pBmp = NULL;

				// �����ӿ�
				SetViewportOrgEx(hDC, pt.x, pt.y, NULL);
			}
		}
		else
		{
			if (IsCachedMode(pLb->hwnd) && hMemDC != NULL && hOldBmp != NULL)
			{
				BitBlt(hDC, 0, 0, rcClient.Width(), rcClient.Height(),
					hDCTarget, 0, 0, SRCCOPY);
				::SelectObject(hMemDC, hOldBmp);
				DeleteDC(hMemDC);
			}
		}

		return 0;
	}

	LRESULT WINAPI StackPanel_WndProc(HWLWND hWnd, RoutedEventArgs *pe)
	{
		// StackPanel�Ǵ�Label�����ģ�����StackPanel��˽�г�Ա������Ҫ����_LABEL
		// ��ΪStackPanel::BindStyle�����Label::BindStyle����Label::BindStyle�ڲ���
		// ���m_pMemberת��_LABLE *ʹ�á�
		SP *pSp = (SP *)GetMember(hWnd);

		UINT uMsg = pe->RoutedEvent;
		WPARAM wParam = pe->wParam;
		LPARAM lParam = pe->lParam;

		if (pe->hOriginalSender == hWnd)
		{
			if (pe->eRoutingStrategy == RS_BUBBLE)
			{
				if (pSp == NULL)
				{
					if (uMsg == WM_NCCREATE)
					{
						// WM_NCCREATE�¼���ֻ�����Ա�ڴ棬����ʼ��
						// ��ʼ���ŵ�WM_CREATE��
						pSp = new SP;
						pSp->hwnd = hWnd;
						pSp->hwnd->ci.hwndParent = GetParent(hWnd);
						SetMember(hWnd, pSp);
						return 0;
					}

					return 0;
				}

				switch (uMsg)
				{
				case WM_DESTROY:
					pSp->Release();
					delete pSp;
					SetMember(hWnd, NULL);
					break;

				case WM_WINDOWPOSCHANGED:
				{
					HWLWND hPrevVisibleCtrl = NULL;
					HWLWND hChild = GetWindow(hWnd, GW_CHILD);
					for (; hChild != NULL; hChild = GetWindow(hChild, GW_HWNDNEXT))
					{
						if (!IsWindowVisible(hChild))
						{
							continue;
						}

						StackPanelLayoutCtrl(hPrevVisibleCtrl, hChild);
						hPrevVisibleCtrl = hChild;
					}
				}
				break;

				default:
					break;
				}
			}
			else if (pe->eRoutingStrategy == RS_TUNNEL)
			{
			}
			else if (pe->eRoutingStrategy == RS_DIRECT)
			{
				switch (uMsg)
				{
				case WM_PRINTCLIENT:
				case WM_PRINT:
				case WM_PAINT:
					StackPanel_OnPaint(pSp, HDC(wParam), LPCRECT(lParam));
					break;

				case SP_SET_DIRECTION:
				{
					Direction eOld = pSp->m_eDirection;
					pSp->m_eDirection = (Direction)lParam;
					return eOld;
				}

				case SP_GET_DIRECTION:
					return pSp->m_eDirection;

				default:
					break;
				}
			}
		}

		// StackPanel����Label
		return Label_WndProc(hWnd, pe);
	}

	////////////////////////////////////////////////////////////////////
	// StackPanel API
	int IUI::StackPanel_BindStyle(HWLWND hWnd, const CStackPanelProp *pCtrlProp)
	{
		Label_BindStyle(hWnd, pCtrlProp);

		CStackPanelProp *pProp = (CStackPanelProp *)pCtrlProp;

		return 0;
	}

}
