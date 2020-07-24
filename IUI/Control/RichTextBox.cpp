// SkinRichEditCtrl.cpp : implementation file
//
// ����Windowless RichEdit�ؼ�������û�д��ھ����
// ���Դ���RichEdit�ؼ������꣬��Ӧ���������Host���ڵ����ꡣ

#include "stdafx.h"
#if(_MSC_VER <= 1200) // VC6.0
#include <ObjIdl.h>
#endif
#include <RichOle.h>
#include <atlbase.h>
#pragma comment (lib, "Imm32.lib")
#ifdef DEBUG_RICHEDIT
#include "ControlCore/RichTextBox/RichEditSrc/_common.h"
#include "ControlCore/RichTextBox/RichEditSrc/_edit.h"
#include "ControlCore/RichTextBox/RichEditSrc/_host.h"
#endif

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG


const LONG g_cInitTextMax = (32 * 1024) - 1;

RichTextBox::RichTextBox()
{
}

RichTextBox::~RichTextBox()
{
}

BOOL RichTextBox::Create(
	CWLWndHandler *pUserHandler,
	DWORD dwStyle,
	const RECT &rect,
	HWND hParent,
	CWLWnd *pParentWnd,
	LPCTSTR lpszName)
{
	if (CWLWnd::IsWindow())
	{
		_ASSERT(FALSE);
		return FALSE;
	}

	BOOL bRet = CWLWnd::Create(pUserHandler, IUI_RICHTEXTBOX, NULL, dwStyle, rect, hParent, pParentWnd, lpszName);
	if (!bRet)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL RichTextBox::CreateEx(
	CWLWndHandler *pUserHandler,
	DWORD dwExStyle,
	DWORD dwStyle,
	const RECT &rect,
	HWND hParent,
	CWLWnd *pParentWnd,
	LPCTSTR lpszName
)
{
	return Create(pUserHandler, dwStyle, rect, hParent, pParentWnd, lpszName);
}

CIUIString RichTextBox::GetClassName() const
{
	return IUI_RICHTEXTBOX;
}

// TxSendMessage��SendMessage������
// SendMessage��RichEditWndProc����δ�������Ϣ������ITextHost::TxWindowProc���Լ�ʵ�֣�����
// ITextHost::TxWindowProcδ�������Ϣ������ITextServices::TxSendMessage��ϵͳʵ�֣�����
// ��TxSendMessageֱ�ӽ���ITextServices::TxSendMessage��ϵͳʵ�֣�����
// ���ԣ�ʹ��SendMessage����ʹRichEdit�и���ؼ�Ȩ��ʹ��TxSendMessage�и��õ����ܡ�
LRESULT RichTextBox::TxSendMessage(UINT message, WPARAM wParam/* = 0*/, LPARAM lParam/* = 0*/)
{
	if (GetTextServices() != NULL)
	{
		LRESULT lRet = 0;
		HRESULT hr = GetTextServices()->TxSendMessage(message, wParam, lParam, &lRet);
		return lRet;
	}
	else
	{
		return 0;
	}
}

LRESULT RichTextBox::TxSendMessage(UINT message, WPARAM wParam/* = 0*/, LPARAM lParam/* = 0*/) const
{
	_ASSERT(CWLWnd::IsWindow());

	RichTextBox *pThis = (RichTextBox *)this;

	if (pThis->GetTextServices() != NULL)
	{
		LRESULT lRet = 0;
		HRESULT hr = pThis->GetTextServices()->TxSendMessage(message, wParam, lParam, &lRet);
		return lRet;
	}
	else
	{
		return 0;
	}
}

BOOL RichTextBox::CanUndo() const
{
	_ASSERT(CWLWnd::IsWindow());
	return (BOOL)SendMessage(EM_CANUNDO, 0, 0);
}
BOOL RichTextBox::CanRedo() const
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_CANREDO, 0, 0);
}
UNDONAMEID RichTextBox::GetUndoName() const
{
	_ASSERT(IsWindow());
	return (UNDONAMEID)SendMessage(EM_GETUNDONAME, 0, 0);
}
UNDONAMEID RichTextBox::GetRedoName() const
{
	_ASSERT(IsWindow());
	return (UNDONAMEID)SendMessage(EM_GETREDONAME, 0, 0);
}
int RichTextBox::GetLineCount() const
{
	_ASSERT(IsWindow());
	return (int)SendMessage(EM_GETLINECOUNT, 0, 0);
}
BOOL RichTextBox::GetModify() const
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_GETMODIFY, 0, 0);
}
void RichTextBox::SetModify(BOOL bModified /* = TRUE */)
{
	_ASSERT(IsWindow());
	SendMessage(EM_SETMODIFY, bModified, 0);
}
BOOL RichTextBox::SetTextMode(UINT fMode)
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_SETTEXTMODE, (WPARAM) fMode, 0);
}
UINT RichTextBox::GetTextMode() const
{
	_ASSERT(IsWindow());
	return (UINT)SendMessage(EM_GETTEXTMODE, 0, 0);
}
void RichTextBox::GetRect(LPRECT lpRect) const
{
	_ASSERT(IsWindow());
	SendMessage(EM_GETRECT, 0, (LPARAM)lpRect);
}
CIUIPoint RichTextBox::GetCharPos(long lChar) const
{
	// TODO: RichEdit�汾��ͬ��EM_POSFROMCHAR�����ͷ���ֵ������Ҳ��ͬ��
	// ��Ҫ�ȵõ�RichEdit�汾��������á�
	// EM_POSFROMCHAR�õ���ֵ��cp�ͻ�������ƫ��ITextHost::TxGetClientRect���ֵ��
	_ASSERT(IsWindow());
	CIUIPoint pt;
	SendMessage(EM_POSFROMCHAR, (WPARAM)&pt, (LPARAM)lChar);

	::ClientToScreen(IUI::GetHostWnd(m_hWnd), &pt);
	IUI::ScreenToClient(m_hWnd, &pt);
	return pt;
}
UINT RichTextBox::GetOptions() const
{
	_ASSERT(IsWindow());
	return (UINT)SendMessage(EM_GETOPTIONS, 0, 0);
}
void RichTextBox::SetOptions(WORD wOp, DWORD dwFlags)
{
	_ASSERT(IsWindow());
	SendMessage(EM_SETOPTIONS, (WPARAM)wOp, (LPARAM)dwFlags);
}
BOOL RichTextBox::SetAutoURLDetect(BOOL bEnable /* = TRUE */)
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_AUTOURLDETECT, (WPARAM) bEnable, 0);
}
void RichTextBox::EmptyUndoBuffer()
{
	_ASSERT(IsWindow());
	SendMessage(EM_EMPTYUNDOBUFFER, 0, 0);
}
UINT RichTextBox::SetUndoLimit(UINT nLimit)
{
	_ASSERT(IsWindow());
	return (UINT)SendMessage(EM_SETUNDOLIMIT, (WPARAM) nLimit, 0);
}
void RichTextBox::ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo)
{
	_ASSERT(IsWindow());
	SendMessage(EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText);
}
void RichTextBox::SetRect(LPCRECT lpRect)
{
	_ASSERT(IsWindow());
	SendMessage(EM_SETRECT, 0, (LPARAM)lpRect);
}
void RichTextBox::StopGroupTyping()
{
	_ASSERT(IsWindow());
	SendMessage(EM_STOPGROUPTYPING, 0, 0);
}
BOOL RichTextBox::Redo()
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_REDO, 0, 0);
}
BOOL RichTextBox::Undo()
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_UNDO, 0, 0);
}
void RichTextBox::Clear()
{
	_ASSERT(IsWindow());
	SendMessage(WM_CLEAR, 0, 0);
}
void RichTextBox::Copy()
{
	_ASSERT(IsWindow());
	SendMessage(WM_COPY, 0, 0);
}
void RichTextBox::Cut()
{
	_ASSERT(IsWindow());
	SendMessage(WM_CUT, 0, 0);
}
void RichTextBox::Paste()
{
	_ASSERT(IsWindow());
	SendMessage(WM_PASTE, 0, 0);
}
BOOL RichTextBox::SetReadOnly(BOOL bReadOnly /* = TRUE */)
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_SETREADONLY, bReadOnly, 0L);
}
int RichTextBox::GetFirstVisibleLine() const
{
	_ASSERT(IsWindow());
	return (int)SendMessage(EM_GETFIRSTVISIBLELINE, 0, 0L);
}
BOOL RichTextBox::DisplayBand(LPRECT pDisplayRect)
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_DISPLAYBAND, 0, (LPARAM)pDisplayRect);
}
void RichTextBox::GetSel(CHARRANGE &cr) const
{
	_ASSERT(IsWindow());
	SendMessage(EM_EXGETSEL, 0, (LPARAM)&cr);
}
BOOL RichTextBox::GetPunctuation(UINT fType, PUNCTUATION *lpPunc) const
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_GETPUNCTUATION, (WPARAM) fType, (LPARAM) lpPunc);
}
BOOL RichTextBox::SetPunctuation(UINT fType, PUNCTUATION *lpPunc)
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_SETPUNCTUATION, (WPARAM) fType, (LPARAM) lpPunc);
}
void RichTextBox::LimitText(long nChars)
{
	_ASSERT(IsWindow());
	SendMessage(EM_EXLIMITTEXT, 0, nChars);
}
long RichTextBox::LineFromChar(long nIndex) const
{
	_ASSERT(IsWindow());
	return (long)SendMessage(EM_EXLINEFROMCHAR, 0, nIndex);
}
CIUIPoint RichTextBox::PosFromChar(UINT nChar) const
{
	// TODO: RichEdit�汾��ͬ��EM_POSFROMCHAR�����ͷ���ֵ������Ҳ��ͬ��
	// ��Ҫ�ȵõ�RichEdit�汾��������á�
	// EM_POSFROMCHAR�õ���ֵ��cp�ͻ�������ƫ��ITextHost::TxGetClientRect���ֵ��
	_ASSERT(IsWindow());
	POINTL pt;
#ifdef DEBUG_RICHEDIT
	// Դ����汾��RichEditͨ������ֵ��������
	LRESULT lr = SendMessage(EM_POSFROMCHAR, nChar, 0);
	pt.x = LOWORD(lr);
	pt.y = HIWORD(lr);
#else
	LRESULT lr = SendMessage(EM_POSFROMCHAR, (WPARAM)&pt, nChar);
#endif // DEBUG

	POINT pt2 = {pt.x, pt.y};
	::ClientToScreen(IUI::GetHostWnd(m_hWnd), &pt2);
	IUI::ScreenToClient(m_hWnd, &pt2);

	return CIUIPoint(pt2.x, pt2.y);
}
int RichTextBox::CharFromPos(CIUIPoint pt) const
{
	_ASSERT(IsWindow());
	POINTL ptl = {pt.x, pt.y};
	return (int)SendMessage(EM_CHARFROMPOS, 0, (LPARAM)&ptl);
}
void RichTextBox::SetSel(CHARRANGE &cr)
{
	_ASSERT(IsWindow());
	SendMessage(EM_EXSETSEL, 0, (LPARAM)&cr);
}
DWORD RichTextBox::FindWordBreak(UINT nCode, DWORD nStart) const
{
	_ASSERT(IsWindow());
	return (DWORD)SendMessage(EM_FINDWORDBREAK, (WPARAM) nCode, (LPARAM) nStart);
}

long RichTextBox::FindText(DWORD dwFlags, FINDTEXTEX *pFindText) const
{
	_ASSERT(IsWindow());
	return (long)SendMessage(EM_FINDTEXTEX, dwFlags, (LPARAM)pFindText);
}

long RichTextBox::FormatRange(FORMATRANGE *pfr, BOOL bDisplay)
{
	_ASSERT(IsWindow());
	return (long)SendMessage(EM_FORMATRANGE, (WPARAM)bDisplay, (LPARAM)pfr);
}

long RichTextBox::GetEventMask() const
{
	_ASSERT(IsWindow());
	return (long)SendMessage(EM_GETEVENTMASK, 0, 0L);
}

long RichTextBox::GetLimitText() const
{
	if (IsWindow())
	{
		return (long)SendMessage(EM_GETLIMITTEXT, 0, 0L);
	}
	else
	{
		return g_cInitTextMax;
	}
}

//long RichTextBox::GetSelText(__out LPSTR lpBuf) const
//{
//	_ASSERT(IsCreated());
//	return (long)SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpBuf);
//}

void RichTextBox::HideSelection(BOOL bHide, BOOL bPerm)
{
	_ASSERT(IsWindow());
	SendMessage(EM_HIDESELECTION, bHide, bPerm);
}

void RichTextBox::RequestResize()
{
	_ASSERT(IsWindow());
	SendMessage(EM_REQUESTRESIZE, 0, 0L);
}

WORD RichTextBox::GetSelectionType() const
{
	_ASSERT(IsWindow());
	return (WORD)SendMessage(EM_SELECTIONTYPE, 0, 0L);
}

UINT RichTextBox::GetWordWrapMode() const
{
	_ASSERT(IsWindow());
	return (UINT) SendMessage(EM_GETWORDWRAPMODE, 0, 0);
}

UINT RichTextBox::SetWordWrapMode(UINT uFlags) const
{
	_ASSERT(IsWindow());
	return (UINT)SendMessage(EM_SETWORDWRAPMODE, (WPARAM) uFlags, 0);
}

COLORREF RichTextBox::SetBackgroundColor(BOOL bSysColor, COLORREF cr)
{
	_ASSERT(IsWindow());
	return (COLORREF)SendMessage(EM_SETBKGNDCOLOR, bSysColor, cr);
}

DWORD RichTextBox::SetEventMask(DWORD dwEventMask)
{
	_ASSERT(IsWindow());
	return (DWORD)SendMessage(EM_SETEVENTMASK, 0, dwEventMask);
}

BOOL RichTextBox::SetOLECallback(IRichEditOleCallback *pCallback)
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_SETOLECALLBACK, 0, (LPARAM)pCallback);
}

BOOL RichTextBox::SetTargetDevice(HDC hDC, long lLineWidth)
{
	_ASSERT(IsWindow());
	return (BOOL)SendMessage(EM_SETTARGETDEVICE, (WPARAM)hDC, lLineWidth);
}

long RichTextBox::StreamIn(int nFormat, EDITSTREAM &es)
{
	_ASSERT(IsWindow());
	return (long)SendMessage(EM_STREAMIN, nFormat, (LPARAM)&es);
}

long RichTextBox::StreamOut(int nFormat, EDITSTREAM &es)
{
	_ASSERT(IsWindow());
	return (long)SendMessage(EM_STREAMOUT, nFormat, (LPARAM)&es);
}

long RichTextBox::GetTextLength() const
{
	_ASSERT(IsWindow());
	return (long)SendMessage(WM_GETTEXTLENGTH, NULL, NULL);
}

int RichTextBox::GetLine(__in int nIndex, LPTSTR lpszBuffer) const
{
	_ASSERT(IsWindow());
	return (int)SendMessage(EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
}

int RichTextBox::LineIndex(int nLine /* = -1 */) const
{
	_ASSERT(IsWindow());
	return (int)SendMessage(EM_LINEINDEX, nLine, 0);
}

int RichTextBox::LineLength(int ncp /* = -1 */) const
{
	_ASSERT(IsWindow());
	return (int)SendMessage(EM_LINELENGTH, ncp, 0);
}

void RichTextBox::LineScroll(int nLines, int nChars /* = 0 */)
{
	_ASSERT(IsWindow());
	SendMessage(EM_LINESCROLL, nChars, nLines);
}

void RichTextBox::SetSel(long nStartChar, long nEndChar)
{
	_ASSERT(IsWindow());
	CHARRANGE cr;
	cr.cpMin = nStartChar;
	cr.cpMax = nEndChar;
	SendMessage(EM_EXSETSEL, 0, (LPARAM)&cr);
}

BOOL RichTextBox::CanPaste(UINT nFormat) const
{
	_ASSERT(IsWindow());
	//COleMessageFilter *pFilter = AfxOleGetMessageFilter();
	//if (pFilter != NULL)
	//{
	//	pFilter->BeginBusyState();
	//}
	BOOL b = (BOOL)SendMessage(EM_CANPASTE, nFormat, 0L);
	//if (pFilter != NULL)
	//{
	//	pFilter->EndBusyState();
	//}
	return b;
}

void RichTextBox::PasteSpecial(UINT nClipFormat, DWORD dvAspect, HMETAFILE hMF)
{
	_ASSERT(IsWindow());
	REPASTESPECIAL reps;
	reps.dwAspect = dvAspect;
	reps.dwParam = (DWORD_PTR)hMF;
	SendMessage(EM_PASTESPECIAL, nClipFormat, (LPARAM)&reps);
}

int RichTextBox::GetLine(__in int nIndex, LPTSTR lpszBuffer, __in int nMaxLength) const
{
	_ASSERT(IsWindow());
	_ASSERT(sizeof(nMaxLength) <= nMaxLength * sizeof(TCHAR) && nMaxLength > 0);
	*(LPINT)lpszBuffer = nMaxLength;
	return (int)SendMessage(EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
}

void RichTextBox::GetSel(long &nStartChar, long &nEndChar) const
{
	_ASSERT(IsWindow());
	CHARRANGE cr;
	SendMessage(EM_EXGETSEL, 0, (LPARAM)&cr);
	nStartChar = cr.cpMin;
	nEndChar = cr.cpMax;
}

CIUIString RichTextBox::GetSelText() const
{
	_ASSERT(IsWindow());
	CHARRANGE cr;
	cr.cpMin = cr.cpMax = 0;
	SendMessage(EM_EXGETSEL, 0, (LPARAM)&cr);
	CIUIString strText;
	LPTSTR lpsz = strText.GetBufferSetLength((cr.cpMax - cr.cpMin + 1) * 2);
	lpsz[0] = NULL;
	SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpsz);
	strText.ReleaseBuffer();
	return CIUIString(strText);
}

IRichEditOle *RichTextBox::GetIRichEditOle() const
{
	_ASSERT(IsWindow());
	IRichEditOle *pRichItem = NULL;
	SendMessage(EM_GETOLEINTERFACE, 0, (LPARAM)&pRichItem);
	return pRichItem;
}

long RichTextBox::GetTextLengthEx(DWORD dwFlags, UINT nCodePage/* = -1*/) const
{
	_ASSERT(IsWindow());
	GETTEXTLENGTHEX textLenEx;
	textLenEx.flags = dwFlags;

	if (nCodePage == -1)
	{
#ifdef _UNICODE
		// UNICODE code page
		textLenEx.codepage = 1200;
#else
		// default code page
		textLenEx.codepage = CP_ACP;
#endif
	}
	else
		// otherwise, use the code page specified
	{
		textLenEx.codepage = nCodePage;
	}

	return (long)SendMessage(EM_GETTEXTLENGTHEX, (WPARAM)&textLenEx, 0);
}

int RichTextBox::GetTextRange(int nFirst, int nLast, CIUIString &refString) const
{
	_ASSERT(IsWindow());

#ifdef _UNICODE
	TEXTRANGEW textRange;
#else
	TEXTRANGE textRange;
#endif
	textRange.chrg.cpMin = nFirst;
	textRange.chrg.cpMax = nLast;

	// can't be backwards
	int nLength = int(nLast - nFirst + 1);
	_ASSERT(nLength > 0);

	textRange.lpstrText = refString.GetBuffer(nLength);
	nLength = (int)SendMessage(EM_GETTEXTRANGE, 0, (LPARAM)&textRange);
	refString.ReleaseBuffer(nLength);

	return nLength;
}

BOOL RichTextBox::SetDefaultCharFormat(CHARFORMAT &cf)
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT);
	return (BOOL)SendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&cf);
}

BOOL RichTextBox::SetDefaultCharFormat(CHARFORMAT2 &cf)
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT2);
	return (BOOL)SendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&cf);
}

BOOL RichTextBox::SetSelectionCharFormat(CHARFORMAT &cf)
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT);
	return (BOOL)SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

BOOL RichTextBox::SetSelectionCharFormat(CHARFORMAT2 &cf)
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT2);
	return (BOOL)SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

BOOL RichTextBox::SetWordCharFormat(CHARFORMAT &cf)
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT);
	return (BOOL)SendMessage(EM_SETCHARFORMAT, SCF_SELECTION | SCF_WORD, (LPARAM)&cf);
}

BOOL RichTextBox::SetWordCharFormat(CHARFORMAT2 &cf)
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT2);
	return (BOOL)SendMessage(EM_SETCHARFORMAT, SCF_SELECTION | SCF_WORD, (LPARAM)&cf);
}

DWORD RichTextBox::GetDefaultCharFormat(CHARFORMAT &cf) const
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT);
	return (DWORD)SendMessage(EM_GETCHARFORMAT, 0, (LPARAM)&cf);
}

DWORD RichTextBox::GetDefaultCharFormat(CHARFORMAT2 &cf) const
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT2);
	return (DWORD)SendMessage(EM_GETCHARFORMAT, 0, (LPARAM)&cf);
}

DWORD RichTextBox::GetSelectionCharFormat(CHARFORMAT &cf) const
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT);
	return (DWORD)SendMessage(EM_GETCHARFORMAT, 1, (LPARAM)&cf);
}

DWORD RichTextBox::GetSelectionCharFormat(CHARFORMAT2 &cf) const
{
	_ASSERT(IsWindow());
	cf.cbSize = sizeof(CHARFORMAT2);
	return (DWORD)SendMessage(EM_GETCHARFORMAT, 1, (LPARAM)&cf);
}

DWORD RichTextBox::GetParaFormat(PARAFORMAT &pf) const
{
	_ASSERT(IsWindow());
	pf.cbSize = sizeof(PARAFORMAT);
	return (DWORD)SendMessage(EM_GETPARAFORMAT, 0, (LPARAM)&pf);
}

DWORD RichTextBox::GetParaFormat(PARAFORMAT2 &pf) const
{
	_ASSERT(IsWindow());
	pf.cbSize = sizeof(PARAFORMAT2);
	return (DWORD)SendMessage(EM_GETPARAFORMAT, 0, (LPARAM)&pf);
}

BOOL RichTextBox::SetParaFormat(PARAFORMAT &pf)
{
	_ASSERT(IsWindow());
	pf.cbSize = sizeof(PARAFORMAT);
	return (BOOL)SendMessage(EM_SETPARAFORMAT, 0, (LPARAM)&pf);
}

BOOL RichTextBox::SetParaFormat(PARAFORMAT2 &pf)
{
	_ASSERT(IsWindow());
	pf.cbSize = sizeof(PARAFORMAT2);
	return (BOOL)SendMessage(EM_SETPARAFORMAT, 0, (LPARAM)&pf);
}

//////////////////////////////////////////////////////////////////////

ITextServices *RichTextBox::GetTextServices()
{
	_ASSERT(IsWindow());

	return (ITextServices *)SendMessage(REM_GET_TEXT_SERVICES, 0, 0);
}

::ITextDocument *RichTextBox::GetITextDocument()
{
	_ASSERT(IsWindow());

	return (ITextDocument *)SendMessage(REM_GET_TEXT_DOCUMENT, 0, 0);
}

HDC RichTextBox::GetDC()
{
	return (HDC)SendMessage(REM_GET_DC, 0, 0);
}

int RichTextBox::SetBkImage(
	UINT uMask,
	LPCTSTR lpszImageNameN,
	LPCTSTR lpszImageNameH,
	LPCTSTR lpszImageNameP,
	LPCTSTR lpszImageNameD,
	BOOL bRedraw/* = TRUE*/)
{
	IUISetControlBkImage4(m_hWnd, FALSE, uMask,
		lpszImageNameN, lpszImageNameH, lpszImageNameP, lpszImageNameD);

	if (bRedraw)
	{
		Invalidate();
	}

	return 0;
}

int RichTextBox::GetBkImage(
	UINT uMask,
	BOOL *pbCombineImage,
	CIUIString *pstrCombineImageName,
	CIUIString *pstrImageNameN,
	CIUIString *pstrImageNameH,
	CIUIString *pstrImageNameP,
	CIUIString *pstrImageNameD) const
{
	_ASSERT(IsWindow());

	return IUIGetControlBkImage4(m_hWnd, FALSE, uMask, pbCombineImage, pstrCombineImageName,
			pstrImageNameN, pstrImageNameH, pstrImageNameP, pstrImageNameD);
}

int RichTextBox::InsertGif(LPCTSTR lpszGifPath, LONG cp)
{
	_ASSERT(IsWindow());

	return S_OK;
}

int RichTextBox::InsertOle(IOleObject *pOleObject, LONG cp, int nWidth, int nHeight)
{
	_ASSERT(IsWindow());

	try
	{
		//
		// 1. Get IRichEditOle and IOleClientSite interface
		//
		CComPtr<IRichEditOle> pRichEditOle = GetIRichEditOle();

		CComPtr<IOleClientSite> pClientSite = NULL;
		HRESULT hr = pRichEditOle->GetClientSite(&pClientSite);
		if (FAILED(hr))
		{
			return -1;
		}

		//
		// 2. Create ILockBytes interface
		//
		CComPtr<ILockBytes> pLockBytes = NULL;
		hr = ::CreateILockBytesOnHGlobal(NULL, TRUE, &pLockBytes);
		if (FAILED(hr))
		{
			return -2;
		}

		//
		// 3. Create IStorage interface
		//
		CComPtr<IStorage> pStorage = NULL;
		hr = ::StgCreateDocfileOnILockBytes(pLockBytes,
				STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &pStorage);
		if (FAILED(hr))
		{
			return -3;
		}

		//
		// 4. Add OLE to Richedit
		//
		CLSID clsid = CLSID_NULL;
		hr = pOleObject->GetUserClassID(&clsid);

		REOBJECT reobject;
		ZeroMemory(&reobject, sizeof(REOBJECT));
		reobject.cbStruct = sizeof(REOBJECT);
		reobject.clsid = clsid;
		reobject.cp = cp;
		reobject.dvaspect = DVASPECT_CONTENT;
		reobject.dwFlags = REO_BELOWBASELINE;
		reobject.dwUser = 7878; // ǩ������dwUserΪ7878ʱ������ʾ�����ǲ����ole
		reobject.poleobj = pOleObject;
		reobject.polesite = pClientSite;
		reobject.pstg = pStorage;

		// REOBJECT::sizel�ĵ�λ��0.01����
		SIZEL sizel = { GetXHimetricFromPixel(nWidth), GetYHimetricFromPixel(nHeight) };
		reobject.sizel = sizel;
		hr = pRichEditOle->InsertObject(&reobject);
		if (FAILED(hr))
		{
			return -4;
		}

		CComPtr<IOleClientSite> pOldClientSite = NULL;
		hr = pOleObject->GetClientSite(&pOldClientSite);
		if (pOldClientSite == NULL)
		{
			pOleObject->SetClientSite(pClientSite);
		}
	}
	catch (...)
	{
	}

	return 0;
}

int RichTextBox::InsertText(LPCTSTR lpszText, int iPos, COLORREF cr)
{
	_ASSERT(IsWindow());

	if (lpszText == NULL || _tcslen(lpszText) == 0)
	{
		return 1;
	}

	long iStartPos = 0;
	long iEndPos = 0;

	if (iPos == SEEK_END)
	{
		iStartPos = GetTextLengthEx(GTL_DEFAULT | GTL_NUMCHARS);
		SetSel(iStartPos, iStartPos);
	}
	else if (iPos == SEEK_CUR)
	{
		GetSel(iStartPos, iEndPos);
	}
	else if (iPos == SEEK_SET)
	{
		SetSel(0, 0);
	}

	// CHARFORMAT::yOffset��PARAFORMAT2�б����ĵ�λ��羣�1羵���1/1440Ӣ��
	CHARFORMAT cf = { 0 };
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask |= CFM_COLOR;
	cf.dwMask |= CFM_OFFSET;
	cf.dwEffects &= ~CFE_AUTOCOLOR;
	cf.crTextColor = cr;
	cf.yOffset = GetYTwipsFromPixel(10);

	ReplaceSel(lpszText);
	iEndPos = iStartPos + (long)_tcslen(lpszText);
	SetSel(iStartPos, iEndPos);
	SetSelectionCharFormat(cf);

	// 	if (iPos != SEEK_CUR)
	// 	{
	// 		m_reHost.SendMessage(WM_VSCROLL, (iPos == 0 ? SB_TOP : SB_BOTTOM), 0);
	// 	}

	return 0;
}

// ����RichEdit�ı���ָ����ȷ�Χ����ʾʱ����Ҫ��ߡ�
int GetNeedHeight(RichTextBox *pRe, int nCpFirst, int nCpLast, LONG lWidth)
{
	CIUIRect rcPage(0, 0, GetXTwipsFromPixel(lWidth), GetYTwipsFromPixel(9999));

	HDC hDC = GetDC(GetDesktopWindow());
	LRESULT lr = 0;
	FORMATRANGE sf = {0};
	sf.hdc = hDC;
	sf.hdcTarget = hDC;
	sf.rc = rcPage; // FORMATRANGE::rc�ĵ�λΪ�(twips)��
	sf.rcPage = rcPage;
	sf.chrg.cpMin = nCpFirst; // ���FORMATRANGE::chrg.cpMinΪ0����FORMATRANGE::chrg.cpMaxΪ-1�������Richedit�����ַ�
	sf.chrg.cpMax = nCpLast;

	// �ڶ������FormatRange��Ϊ���ͷ��ڴ棬������ο�MSDN:EM_FORMATRANGE
	pRe->FormatRange(&sf, FALSE);
	pRe->FormatRange(NULL, FALSE);

	::ReleaseDC(GetDesktopWindow(), hDC);

	// �²��������ĸ߶ȣ���λΪ羣���ת������ʹ�á�
	int nNeedHeight = GetYPixelFromTwips(sf.rc.bottom);

	return nNeedHeight;
}

// �õ�ָ���е����꣬����������������ΪNULL
// ��RichEdit��ָ��cp�����꣬�м��ַ�����
// 1. ʹ��PosFromChar��GetCharPos(�����ڲ����ǵ���EM_POSFROMCHAR)�����Եõ�ָ��cp���Ͻ����ꡣ
// ͨ��ָ��cp����һ��cp����һ��cp, ���Եõ�ָ��cp����������(ע�⣬������RichEdit��һ���ַ�ʱ��
// ��Ȼ����ͨ��PosFromChar(1)���õ�����ַ����Ͻ����꣬��Ȼ��û��cpΪ1���ַ�, ������Ϊÿ������
// ĩβ������һ������������� �����ǡ����һ��������ʾ�������У����һ�е���β��û�ж��������,
// ����ͨ����һ�����һ���ַ���cp + 1���޷��õ����һ���ַ����Ͻ����꣬���ǵõ���һ�е�һ���ַ�����
// �����ꡣ ����������ĳ��������ʾ�ɶ���ʱ�����ǲ���Ҫ����������������ݿ�ȣ���Ϊ����RichEdit
// �Ŀ�ȣ��������ݵĿ�ȣ�����Ҫ���м���)
// 2. ͨ��ʹ��FormatRange������ģ��������Ӷ��õ�����Ҫ�ĸ߶����꣨����Լ�ָ����
// 3. ͨ��ITextRange::GetPoint�����Եõ�ѡ�з�Χ�������ꡣ ���뷽��һ��΢��RichEdit�ڲ�������
// CDisplayML::PointFromTpʵ�֡� ����ʹ������ӿ��и�ע�������VS2008 sp1����MSDN�����У�
// ITextRange::GetPoint��һ������ֻ��tomStart��tomEnd��TA_TOP��TA_BASELINE��TA_BOTTOM��TA_LEFT��
// TA_CENTER��TA_RIGHT����ϡ� ������ֻ�ܵõ����ӷ�Χ��cp�����ꡣ ��cp�������ɼ���Χ��󣬵õ�����0��
// ������ ���ߵ�MSDN�ϣ��ṩ��һЩ����Ĳ��������Եõ����ӷ�Χ������꣬���в������£�
// None					0 		��ѡ�
// IncludeInset			1 		�����Ͷ���Ƕ����ӵ����ε����Ͷ������꣬����������Ҳ�͵ײ���ȥ�Ҳ�͵ײ�Ƕ�롣
// Start				32		�ı���Χ�Ŀ�ʼλ�á�
// ClientCoordinates	256		���ع����������������Ļ���ꡣ
// AllowOffClient		512 	��������֮��ĵ㡣
// Transform			1024 	ʹ������Ӧ�ó����ṩ������ת���ı任���ꡣ
// NoHorizontalScroll	65536 	ˮƽ�����ѽ��á�
// NoVerticalScroll		262144 	��ֱ�����ѽ��á�
// ����ITextRange::GetPoint�ĵ�һ��������ֻҪ����512���Ϳ��Եõ���������������ˡ� ��������Щ�µ���
// �ԣ���֧�־ɰ汾��RichEdit.
int RichTextBox::GetLineRect(
	int nLineIndex,
	__out POINT *pptStart,
	__out int *pnLineWidth,
	__out int *pnLineHeight)
{
	_ASSERT(IsWindow());

	if (pptStart == NULL && pnLineWidth == NULL && pnLineHeight == NULL)
	{
		return -1;
	}

	// �õ�������ʼcp
	int nCpFirst = LineIndex(nLineIndex);

	// �õ���ʼcp�����Ͻ�����
	CIUIPoint ptFirst = PosFromChar(nCpFirst);

	if (pptStart != NULL)
	{
		*pptStart = ptFirst;
	}

	if (pnLineWidth != NULL)
	{
		// nCpFirst�����е��ַ�����
		int nCharCount = LineLength(nCpFirst);

		CIUIPoint ptLast = PosFromChar(nCpFirst + nCharCount);

#ifdef _DEBUG
#endif // _DEBUG

		*pnLineWidth = ptLast.x - ptFirst.x;
	}

	if (pnLineHeight != NULL)
	{
		int nNextLineCpFirst = LineIndex(nLineIndex + 1);

		// �������һ�У��õ���һ����ʼcp������󣬾Ϳ��Եõ��и�
		if (nNextLineCpFirst != -1)
		{
			CIUIPoint ptNextLineFirst = PosFromChar(nNextLineCpFirst);

			*pnLineHeight = ptNextLineFirst.y - ptFirst.y;
		}

		// ���û����һ�У�ͨ��FormatRange�������и�
		else
		{
			// nCpFirst�����е��ַ�����
			int nCharCount = LineLength(nCpFirst);

			CIUIRect rcClient;
			GetClientRect(rcClient);
			int nLineHeight = GetNeedHeight(this, nCpFirst, nCpFirst + nCharCount, rcClient.Width());

			*pnLineHeight = nLineHeight;

#if 0
			CComPtr<ITextDocument> pTextDocument = GetITextDocument();

			ITextRange *pTextRange = NULL;
			pTextDocument->Range(nCpFirst, nCpFirst + nCharCount, &pTextRange);

#ifdef _DEBUG
			BSTR bstr;
			pTextRange->GetText(&bstr);
#endif // _DEBUG


			CIUIPoint pt;
			pTextRange->GetPoint(tomStart | TA_BOTTOM | TA_RIGHT | 256 | 512, &pt.x, &pt.y);
			if (pt.x == 0 || pt.y == 0)
			{
				int n = 0;
			}

			pTextRange->GetPoint(tomEnd | TA_BOTTOM | TA_RIGHT | 256 | 512, &pt.x, &pt.y);
			*pnLineHeight = pt.y - ptFirst.y;
#endif
		}
	}

	return 0;
}

int RichTextBox::GetFirstVisibleOleOjbect(__out REOBJECT *pObj)
{
	_ASSERT(IsWindow());

	if (NULL == pObj)
	{
		return -1;
	}

	// �ȵõ���һ���ɼ����ַ�λ��
	int nFirstVisibleLine = GetFirstVisibleLine();
	int nFirstVisibleCp = LineIndex(nFirstVisibleLine);

	CIUIRect rcRe;
	GetClientRect(rcRe);

	// ���ö��ֲ��ҷ����ɶ�λ��һ���ɼ���Ole object
	REOBJECT reObj;
	int nFirstVisibleOle = FindObjectNearCp(this, nFirstVisibleCp, &reObj);
	if (nFirstVisibleOle < 0)
	{
		return -1;
	}

	_ASSERT(NULL != reObj.poleobj);

	// �õ�Ole������
	CIUIPoint pt = PosFromChar(reObj.cp);
	CIUIRect rcOle;
	rcOle.left = pt.x;
	rcOle.top = pt.y;
	rcOle.right = rcOle.left + GetXPixelFromHimetric(reObj.sizel.cx);
	rcOle.bottom = rcOle.top + GetYPixelFromHimetric(reObj.sizel.cy);

	// ��Ole�Ƿ��ڿ��ӷ�Χ��
	rcRe.IntersectRect(rcRe, rcOle);
	if (rcRe.IsRectEmpty() || rcRe.IsRectNull())
	{
		return -1;
	}

	*pObj = reObj;

	return nFirstVisibleOle;
}

IOleObject *RichTextBox::HitTestOleObject(LPPOINT lpPt)
{
	_ASSERT(IsWindow());

	REOBJECT reObj;
	int nOleIndex = GetFirstVisibleOleOjbect(&reObj);
	if (nOleIndex < 0)
	{
		return NULL;
	}

	CIUIRect rcRe;
	GetClientRect(rcRe);

	IOleObject *pRet = NULL;

	CComPtr<IRichEditOle> pRichEditOle = GetIRichEditOle();
	LONG nOleCount = pRichEditOle->GetObjectCount();

	for (int i = nOleIndex; i < nOleCount; ++i)
	{
		REOBJECT ro;
		ro.cbStruct = sizeof(REOBJECT);
		HRESULT hr = pRichEditOle->GetObject(i, &ro, REO_GETOBJ_POLEOBJ);

		// �õ�Ole������
		CIUIPoint pt = PosFromChar(ro.cp);
		CIUIRect rcOle;
		rcOle.left = pt.x;
		rcOle.top = pt.y;
		rcOle.right = rcOle.left + GetXPixelFromHimetric(ro.sizel.cx);
		rcOle.bottom = rcOle.top + GetYPixelFromHimetric(ro.sizel.cy);

		// ��Ole�Ƿ��ڿ��ӷ�Χ��
		CIUIRect rcIntersect;
		rcIntersect.IntersectRect(rcRe, rcOle);
		if (rcIntersect.IsRectEmpty() || rcIntersect.IsRectNull())
		{
			continue;
		}

		if (rcOle.PtInRect(*lpPt))
		{
			pRet = ro.poleobj;
			break;
		}
	}

	return pRet;
}

int RichTextBox::RevokeDragDrop()
{
	_ASSERT(IsWindow());
	return SendMessage(REM_REVOKEDRAGDROP, 0, 0);
}

BOOL RichTextBox::SetDefaultProcHandleIfHitOleCtrl(BOOL bDefaultHandle)
{
	_ASSERT(IsWindow());
	return SendMessage(REM_SET_DEFAULTPROC_HANDLE, 0, bDefaultHandle);
}

BOOL RichTextBox::IsDefaultProcHandleIfHitOleCtrl() const
{
	_ASSERT(IsWindow());
	return SendMessage(REM_GET_DEFAULTPROC_HANDLE, 0, 0);
}

/////////////////////////////////////////////////////////////////////////////
// RichTextBox API
int IUI::RichTextBox_BindStyle(HWLWND hWnd, const CRichTextBoxProp *pCtrlProp)
{
	HWLWND_BindStyle(hWnd, pCtrlProp);

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(hWnd);

	// ����
	CIUIString strImageName[1 + COMBINEIMAGESIZE4];
	BOOL bCombineImage = TRUE;
	CControlProp::GetBackground4(pCtrlProp, &bCombineImage, strImageName);
	if (bCombineImage)
	{
		CombineBkImage(hWnd, TRUE);
		SetCombineBkImage(hWnd, strImageName[0]);
	}
	else
	{
		CombineBkImage(hWnd, FALSE);
		pRichTextBox->SetBkImage(CONTROL_STATE_ALL,
			strImageName[1], strImageName[2], strImageName[3], strImageName[4], FALSE);
	}
	SetBkImageResizeMode(hWnd, pCtrlProp->m_eBkImageResizeMode);
	SetBkImage9GridResizeParam(hWnd, &(RECT)pCtrlProp->m_rcBkImage9GridResizeArg);

	CIUIRect rc;
	pRichTextBox->GetClientRect(rc);
	rc.DeflateRect(&(RECT)pCtrlProp->m_rcPadding4Text);
	pRichTextBox->SetRect(rc);

	// Ĭ���ַ���ʽ
	CIUIString strFont;
	CControlProp::GetControlFont1(pCtrlProp, &strFont);
	CFontProp *pFontProp = GetProject(hWnd)->GetFontProp(strFont);
	if (pFontProp == NULL)
	{
		pFontProp = GetProject(hWnd)->GetDefaultFontProp();
	}
	if (pFontProp != NULL)
	{
		LOGFONT lf = (LOGFONT)pFontProp->m_logFont;

		if (_tcslen(lf.lfFaceName) == 0)
		{
			// ���������δָ��Ĭ�����壬������ʹ��Host���ڵ�����
			HFONT hFont = (HFONT)::SendMessage(GetHostWnd(hWnd), WM_GETFONT, 0, 0);
			if (NULL != hFont)
			{
				::GetObject(hFont, sizeof(LOGFONT), &lf);
			}
			else
			{
				// ���Host����δָ�����壬��ʹ��14�ŵ�Tahoma���塣
				memset(&lf, 0, sizeof(lf));
				lf.lfHeight = -14;
				lf.lfWeight = FW_NORMAL;
				StringCchCopy(lf.lfFaceName, LF_FACESIZE, _T("Tahoma"));
			}
		}

		CHARFORMAT2 cf;
		GenerateCharFormat(&cf, lf);
		pRichTextBox->SetDefaultCharFormat(cf);
	}

	COLORREF cr;
	GetProject(hWnd)->GetControlTextColor(pCtrlProp, &cr);
	CHARFORMAT2 cf;
	GenerateCharFormat(&cf, cr);
	pRichTextBox->SetDefaultCharFormat(cf);

	pRichTextBox = NULL;

	return 0;
}
