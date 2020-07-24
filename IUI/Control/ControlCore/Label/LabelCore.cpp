#include "stdafx.h"

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG


#define IDT_GIF			USER_TIMER_MAXIMUM - 1

int IUI::Label_BindStyle(HWLWND hWnd, const CLabelProp *pProp)
{
	if (NULL == hWnd || NULL == pProp)
	{
		return -1;
	}

	HWLWND_BindStyle(hWnd, pProp);

	Label *pLabel = (Label *)CWLWnd::FromHandle(hWnd);

	//
	// �ı�
	//
	BindTextAlignStyle(hWnd, pProp);

	pLabel->SetTextAlignHor(CONTROL_STATE_ND,
		pProp->m_eTextHorAlignMode, pProp->m_eTextHorAlignMode, FALSE);

	pLabel->SetTextAlignVer(CONTROL_STATE_ND,
		pProp->m_eTextVerAlignMode, pProp->m_eTextVerAlignMode, FALSE);

	CIUIString strResFontID[2];
	CControlProp::GetControlFont2(pProp, strResFontID);
	pLabel->SetTextFont(CONTROL_STATE_ND, strResFontID[0], strResFontID[1], FALSE);

	RECT rcTextMargin = pProp->m_rcPadding4Text;
	//GetDPIPadding(&rcTextMargin);
	pLabel->SetTextMargin(CONTROL_STATE_ND, &rcTextMargin, &rcTextMargin, FALSE);

	pLabel->SetTextAlignHor(CONTROL_STATE_ND,
		pProp->m_eTextHorAlignMode, pProp->m_eTextHorAlignMode, FALSE);
	pLabel->SetTextAlignVer(CONTROL_STATE_ND,
		pProp->m_eTextVerAlignMode, pProp->m_eTextVerAlignMode, FALSE);

	// SetWidthMatchText();
	// SetHeightMatchText();

	//
	// ����
	//
	pLabel->SetBkImageResizeMode(pProp->m_eBkImageResizeMode);

	CIUIString strImageName[1 + COMBINEIMAGESIZE2];
	BOOL bCombineImage = TRUE;
	CControlProp::GetBackground2(pProp, &bCombineImage, strImageName);
	CombineBkImage(hWnd, bCombineImage);
	if (bCombineImage)
	{
		SetCombineBkImage(hWnd, strImageName[0]);
	}
	else
	{
		pLabel->SetBkImage(CONTROL_STATE_ND, strImageName[1], strImageName[2], FALSE);
	}

	SetBkImageResizeMode(hWnd, pProp->m_eBkImageResizeMode);
	SetBkImage9GridResizeParam(hWnd, &(RECT)pProp->m_rcBkImage9GridResizeArg);

	//
	pLabel->SetButtonClickArg((LPCTSTR)pProp->m_strButtonClickArg);

	pLabel = NULL;

	return 0;
}

int IUI::Label_DrawBkImage(_LABEL *pLb, HDC hDC, LPCRECT lprcDest)
{
	CIUIRect rcDest;
	if (lprcDest == NULL)
	{
		GetClientRect(pLb->hwnd, rcDest);
	}
	else
	{
		rcDest = lprcDest;
	}

	// �����ؼ�һ���Ի�Ļ���
	RoutedEventArgs arg;
	arg.hSender = pLb->hwnd;
	arg.hOriginalSender = pLb->hwnd;
	arg.RoutedEvent = UE_DRAW_BK_IMAGE;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.wParam = (WPARAM)hDC;
	arg.lParam = (LPARAM)(LPCRECT)rcDest;
	LRESULT lr = IUI::RaiseEvent(arg.hOriginalSender, &arg);
	if (lr != 0)
	{
		return 0;
	}

	int nStateIndex = 0;
	if (!IsWindowEnabled(pLb->hwnd))
	{
		nStateIndex = 1;
	}

	if (pLb->hwnd->ci.m_bCombineBkImage)
	{
		IUIPartDrawImage(hDC, rcDest,
			pLb->hwnd->ci.m_himgCombineBk, pLb->hwnd->ci.m_eBkImageResizeMode,
			pLb->hwnd->ci.m_rcBkImage9GridResizeArg, COMBINEIMAGESIZE2, nStateIndex);
	}
	else
	{
		// ������õı���ͼ��Gif����������ʱ��
		HIUIIMAGE hImage = pLb->m_himgBk[nStateIndex];
		hImage->SafeLoadSavedImage();
		if (hImage->IsGif() && !pLb->m_bGifAnimationBegun)
		{
			if (pLb->hwnd->ci.m_eBkImageResizeMode == IRM_CENTER
				|| pLb->hwnd->ci.m_eBkImageResizeMode == IRM_STRETCH
				|| pLb->hwnd->ci.m_eBkImageResizeMode == IRM_STRETCH_HIGH_QUALITY
				|| pLb->hwnd->ci.m_eBkImageResizeMode == IRM_TILE
				|| pLb->hwnd->ci.m_eBkImageResizeMode == IRM_KEEPRATE)
			{
				LONG *plFrameDelay = NULL;
				UINT nFrameCount = 0;
				hImage->GetGifFrameDelay(&plFrameDelay, &nFrameCount);

				if (nFrameCount > 0)
				{
					if (pLb->m_pGifHelper == NULL)
					{
						pLb->m_pGifHelper = new GifHelper;
					}

					// ��ѭ���������޵�gif���Ž�����plb->m_bGifAnimationBegun
					// Ҳ����Ҫ��FALSE����Ϊһ����FALSE���´λ���Label��ʱ��
					// �����ֻ����²��ţ������������޴β��ű������ѭ���ˡ�
					pLb->m_bGifAnimationBegun = TRUE;

					// ������һ֡
					SetTimer(pLb->hwnd, IDT_GIF, *plFrameDelay, NULL);
				}
			}
		}

		IUIDrawImage(hDC, rcDest, hImage,
			pLb->hwnd->ci.m_eBkImageResizeMode, pLb->hwnd->ci.m_rcBkImage9GridResizeArg);
	}

	return 0;
}

int Label_DrawText(_LABEL *pLb, HDC hDC)
{
	CIUIString strText = GetWindowText(pLb->hwnd);
	if (strText.IsEmpty())
	{
		return 1;
	}

	CIUIRect rcClient;
	GetClientRect(pLb->hwnd, rcClient);

	int nStateIndex = 0;
	if (IsWindowEnabled(pLb->hwnd))
	{
		if (IsUseRectF(pLb->hwnd))
		{
			Gdiplus::Graphics g(hDC);

			DrawTextGp(&g, strText, strText.GetLength(),
				pLb->m_hIUIFont[0]->GetSafeHFont(), pLb->m_crText[0],
				GetRectF(pLb->hwnd), pLb->hwnd->ci.m_uTextStyle);

			return 0;
		}
	}
	else
	{
		nStateIndex = 1;
	}

	DrawFormatText(hDC, strText, strText.GetLength(),
		rcClient, pLb->m_rcTextMargin[nStateIndex],
		pLb->m_eTextHorAlignMode[nStateIndex], pLb->m_eTextVerAlignMode[nStateIndex],
		pLb->hwnd->ci.m_uTextStyle, pLb->m_hIUIFont[nStateIndex]->GetSafeHFont(),
		pLb->m_crText[nStateIndex], IsUpdateLayeredWindow(GetHostWnd(pLb->hwnd)));

	return 0;
}

int Label_OnPaint(_LABEL *pLb, HDC hDC, LPCRECT lprcPaint)
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
	// �����Լ�
	//
	BeforePaint(pLb->hwnd, hDCTarget);
	DrawBkColor(pLb->hwnd, hDCTarget, lprcPaint);
	Label_DrawBkImage(pLb, hDCTarget, NULL);
	if (!IsUseRectF(pLb->hwnd))
	{
		// ����ʹ��RectF����ʱ�������ǻ���Alpha HBITMAP�ϣ������ֻ���alpha HBITMAP�Ϻ�
		// �����ź����ֱ���֧��alpha�����壬��ʾ�������⡣
		// ��������������alpha HBITMAP���й�ϵ��
		Label_DrawText(pLb, hDCTarget);
	}
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

			// �������ı���
			Label_DrawText(pLb, hDC);

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

LRESULT Label_OnNcCreate(HWLWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	_LABEL *pLb = new _LABEL;
	if (pLb == NULL)
	{
		return -1;    // fail the create window
	}

	pLb->hwnd = hWnd;
	pLb->hwnd->ci.hwndParent = GetParent(hWnd);

	SetMember(hWnd, pLb);

	return 0;
}

LRESULT WINAPI IUI::Label_WndProc(HWLWND hWnd, RoutedEventArgs *pe)
{
	_LABEL *pLb = (_LABEL *)GetMember(hWnd);

	UINT uMsg = pe->RoutedEvent;
	WPARAM wParam = pe->wParam;
	LPARAM lParam = pe->lParam;

	if (pe->hOriginalSender == hWnd)
	{
		if (pe->eRoutingStrategy == RS_BUBBLE)
		{
			if (pLb == NULL)
			{
				if (uMsg == WM_NCCREATE)
				{
					return Label_OnNcCreate(hWnd, (LPCREATESTRUCT)lParam);
				}

				return 0;
			}

			switch (uMsg)
			{
			case WM_DESTROY:
				pLb->Release();
				delete pLb;
				SetMember(hWnd, NULL);
				return 0;

			case WM_KILLFOCUS:
				pLb->m_bRecordLButtonDown = FALSE;
				return 0;

			default:
				break;
			}
		}
		else if (pe->eRoutingStrategy == RS_TUNNEL)
		{
			switch (uMsg)
			{
			case WM_LBUTTONDOWN:
				if (!hWnd->m_bMouseTransparent)
				{
					if (hWnd->m_uLButtonDownHitTestRet == HTCLIENT)
					{
						// Win32�İ�ť�����ڰ�ť�ڰ��������������ڰ�ť���ͷ���꣬Ҳ���յ�
						// WM_LBUTTONUP����������win32�ڲ����ڴ���WM_LBUTTONDOWNʱ��������
						// SetCapture()��ͬʱ�������˽���

						SetCapture(hWnd);
						SetFocus(GetHostWnd(hWnd), hWnd);
						pLb->m_bRecordLButtonDown = TRUE;

						SetControlState(hWnd, CONTROL_STATE_PRESSED);
						InvalidateRect(hWnd, NULL);
					}
				}
				break;

			case WM_LBUTTONUP:
			{
				ReleaseCapture(hWnd);

				InvalidateRect(hWnd, NULL);

				BOOL bOld = pLb->m_bRecordLButtonDown;
				pLb->m_bRecordLButtonDown = FALSE;

				// ת�ɰ�ť����¼�
				if (bOld)
				{
					// �����Label
					CIUIPoint pt(lParam);

					CIUIRect rcClient;
					GetClientRect(hWnd, rcClient);

					if (rcClient.PtInRect(pt))
					{
						RoutedEventArgs arg;
						arg.hSender = hWnd;
						arg.hOriginalSender = hWnd;
						arg.RoutedEvent = UE_BUTTON_CLICK;
						arg.eRoutingStrategy = RS_BUBBLE;
						// IUI�еİ�ť���ʱ�����Ը���һ���Զ����ַ�������
						arg.wParam = (LPARAM)(LPCTSTR)pLb->m_strButtonClickArg;
						RaiseEvent(arg.hOriginalSender, &arg);

						// �����ť��Close Button��ִ����RaiseEvent��
						// this�ͱ��ͷ��ˡ�
						arg.bHandled = TRUE;
						return 1;
					}
				}
			}
			break;

			default:
				break;
			}
		}
		else if (pe->eRoutingStrategy == RS_DIRECT)
		{
			switch (uMsg)
			{
			case WM_PRINTCLIENT:
			case WM_PRINT:
			case WM_PAINT:
				Label_OnPaint(pLb, (HDC)wParam, LPCRECT(lParam));
				return 0;

			case WLM_BIND_STYLE:
				Label_BindStyle(hWnd, (CLabelProp *)lParam);
				return 0;

			case WLM_SET_BK_IMAGE:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);
				LPCTSTR lpszImage = LPCTSTR(lParam);

				if (eControlState == CONTROL_STATE_NORMAL
					|| eControlState == CONTROL_STATE_DISABLED)
				{
					int nStateIndex = GetLabelStateIndex(eControlState);

					return IUISetControlImage(GetProject(hWnd),
							&pLb->m_himgBk[nStateIndex], lpszImage);
				}
				else if (eControlState == CONTROL_STATE_COMBINE)
				{
					return IUISetControlImage(GetProject(hWnd),
							&pLb->hwnd->ci.m_himgCombineBk, lpszImage);
				}
			}
			return 0;

			case WLM_GET_BK_IMAGE:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);

				if (eControlState == CONTROL_STATE_NORMAL
					|| eControlState == CONTROL_STATE_DISABLED)
				{
					int nStateIndex = GetLabelStateIndex(eControlState);

					return (LRESULT)(LPCTSTR)pLb->m_himgBk[nStateIndex]->GetSafeImageName();
				}
				else if (eControlState == CONTROL_STATE_COMBINE)
				{
					return (LRESULT)(LPCTSTR)pLb->hwnd->ci.m_himgCombineBk->GetSafeImageName();
				}
			}
			return 0;

			case WLM_SET_TEXT_COLOR:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);
				COLORREF cr = lParam;

				if (eControlState == CONTROL_STATE_NORMAL)
				{
					pLb->m_crText[0] = cr;
					return 0;
				}
				else if (eControlState == CONTROL_STATE_DISABLED)
				{
					pLb->m_crText[1] = cr;
					return 0;
				}
				else
				{
					_ASSERT(FALSE);
				}
			}
			return 0;

			case WLM_GET_TEXT_COLOR:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);

				if (eControlState == CONTROL_STATE_NORMAL)
				{
					return pLb->m_crText[0];
				}
				else if (eControlState == CONTROL_STATE_DISABLED)
				{
					return pLb->m_crText[1];
				}
				else
				{
					_ASSERT(FALSE);
				}
			}
			return 0;

			case WLM_SET_TEXT_FONT:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);

				return IUISetControlFont2(GetProject(hWnd),
						eControlState, pLb->m_hIUIFont, (LPCTSTR)lParam, (LPCTSTR)lParam);
			}
			return 0;

			case WLM_GET_TEXT_FONT:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);

				if (eControlState == CONTROL_STATE_NORMAL)
				{
					return pLb->m_hIUIFont[0] == NULL ? NULL : (LRESULT)(LPCTSTR)pLb->m_hIUIFont[0]->m_strFontResID;
				}
				else if (eControlState == CONTROL_STATE_DISABLED)
				{
					return pLb->m_hIUIFont[1] == NULL ? NULL : (LRESULT)(LPCTSTR)pLb->m_hIUIFont[1]->m_strFontResID;
				}
			}
			return 0;

			case WLM_SET_TEXT_ALIGN_MODE:
			{
				BOOL bVert = LOWORD(wParam);
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);
				int nIndex = GetLabelStateIndex(eControlState);
				_ASSERT(nIndex >= 0 && nIndex < COMBINEIMAGESIZE2);

				if (bVert)
				{
					TEXT_ALIGN_VER eHorAlignMode = (TEXT_ALIGN_VER)lParam;
					pLb->m_eTextVerAlignMode[nIndex] = eHorAlignMode;
				}
				else
				{
					TEXT_ALIGN_HOR eHorAlignMode = (TEXT_ALIGN_HOR)lParam;
					pLb->m_eTextHorAlignMode[nIndex] = eHorAlignMode;
				}
			}
			return 0;

			case WLM_GET_TEXT_ALIGN_MODE:
			{
				BOOL bVert = LOWORD(wParam);
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);
				int nIndex = GetLabelStateIndex(eControlState);
				_ASSERT(nIndex >= 0 && nIndex < COMBINEIMAGESIZE2);

				if (bVert)
				{
					return pLb->m_eTextVerAlignMode[nIndex];
				}
				else
				{
					return pLb->m_eTextHorAlignMode[nIndex];
				}
			}
			return 0;

			case WLM_SET_TEXT_MARGIN:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);
				int nIndex = GetLabelStateIndex(eControlState);
				_ASSERT(nIndex >= 0 && nIndex < COMBINEIMAGESIZE2);

				LPCRECT lprcTextMargin = (LPCRECT)lParam;
				pLb->m_rcTextMargin[nIndex] = *lprcTextMargin;
			}
			return 0;

			case WLM_GET_TEXT_MARGIN:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);
				int nIndex = GetLabelStateIndex(eControlState);
				_ASSERT(nIndex >= 0 && nIndex < COMBINEIMAGESIZE2);

				LPRECT lprcTextMargin = (LPRECT)lParam;
				if (lprcTextMargin == NULL)
				{
					return -1;
				}

				*lprcTextMargin = pLb->m_rcTextMargin[nIndex];
			}
			return 0;

			case WM_TIMER:
			{
				// ������Gif
				if (wParam == IDT_GIF)
				{
					// ���ö�ʱ��
					int nStateIndex = 0;
					if (!IsWindowEnabled(hWnd))
					{
						nStateIndex = 1;
					}

					BOOL bContinue = FALSE;
					if (!pLb->hwnd->ci.m_bCombineBkImage)
					{
						HIUIIMAGE hImage = pLb->m_himgBk[nStateIndex];
						if (hImage->GetSafeHBITMAP() != NULL)
						{
							if (hImage->IsGif())
							{
								if (pLb->hwnd->ci.m_eBkImageResizeMode == IRM_CENTER
									|| pLb->hwnd->ci.m_eBkImageResizeMode == IRM_STRETCH
									|| pLb->hwnd->ci.m_eBkImageResizeMode == IRM_STRETCH_HIGH_QUALITY
									|| pLb->hwnd->ci.m_eBkImageResizeMode == IRM_TILE
									|| pLb->hwnd->ci.m_eBkImageResizeMode == IRM_KEEPRATE)
								{
									int nCurLoop = pLb->m_pGifHelper->GetCurLoop();
									int nLoopCount = hImage->GetGifLoopCount();
									if (nLoopCount == 0 || nCurLoop < nLoopCount)
									{
										LONG *plFrameDelay = NULL;
										UINT nFrameCount = 0;
										hImage->GetGifFrameDelay(&plFrameDelay, &nFrameCount);

										if (nFrameCount > 0)
										{
											int nCurFrame = pLb->m_pGifHelper->GetCurFrame();

											if (nCurFrame < int(nFrameCount) - 1)
											{
												nCurFrame++;

												pLb->m_pGifHelper->SetCurFrame(nCurFrame);
												hImage->SetGifCurFrame(nCurFrame);

												// ����Kill�ɵ�Timer���Ḳ�Ǿɵ�Timer��ʱ������
												int nDelay = plFrameDelay[nCurFrame];
												SetTimer(hWnd, IDT_GIF, nDelay, NULL);
												bContinue = TRUE;
											}
											else
											{
												if (nLoopCount == 0
													|| nCurLoop < hImage->GetGifLoopCount() - 1)
												{
													pLb->m_pGifHelper->SetCurLoop(nCurLoop + 1);

													pLb->m_pGifHelper->SetCurFrame(0);
													hImage->SetGifCurFrame(0);

													// ����Kill�ɵ�Timer���Ḳ�Ǿɵ�Timer��ʱ������
													int nDelay = plFrameDelay[0];
													SetTimer(hWnd, IDT_GIF, nDelay, NULL);
													bContinue = TRUE;
												}
											}
										}
									}
								}
							}
						}
					}

					if (!bContinue)
					{
						KillTimer(hWnd, IDT_GIF);
						delete pLb->m_pGifHelper;
						pLb->m_pGifHelper = NULL;
					}

					Invalidate(hWnd);
					UpdateWindow(GetHostWnd(hWnd));

					return 0;
				}
			}
			return 0;

			case BM_SET_BUTTON_CLICK_ARG:
			{
				pLb->m_strButtonClickArg = (LPCTSTR)wParam;
				return 0;
			}
			return 0;

			case BM_GET_BUTTON_CLICK_ARG:
				return (LRESULT)(LPCTSTR)pLb->m_strButtonClickArg;

			default:
				break;
			}
		}
	}

	return DefEventHandler(hWnd, pe);
}
