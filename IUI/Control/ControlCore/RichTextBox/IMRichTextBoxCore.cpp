// ����������IM��������¼��ʾ���ڵĿؼ���֧�����������ʽ��
// ͨ�����໯RichTextBoxʵ�֡�

// ���˵���IMRichTextBox::InsertMsgʱ��IM�ؼ��ǿ�д�ģ��������ȫ��ֻ����
// �����������ڣ����롢ɾ���ַ������롢�ϳ����ڲ��Ϸ��ı������С�ճ���ı���Redo|Undo�ı��ȡ�
#include "stdafx.h"
#if(_MSC_VER <= 1200) // VC6.0
#include <ObjIdl.h>
#endif
#include <RichOle.h>
#include <atlbase.h>
#pragma comment (lib, "Imm32.lib")
#include <time.h>

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG

#define GetProp_IMDATA _T("GetProp_IMDATA")
INT	DCT;				// Double Click Time in milliseconds
INT	cxDoubleClk;		// Double click distances
INT cyDoubleClk;		// Double click distances

int DoSetParaFormat(IMBox *pBox);

CTimeStampParam::CTimeStampParam()
	: m_nIndex(-1)
	, m_uMsgID(0)
	, m_time(0)
{

}

CTimeStampParam::~CTimeStampParam()
{

}

CLabelMsg::CLabelMsg()
	: m_nIndex(-1)
	, m_uMsgID(0)
	, m_lpszText(NULL)
	, m_pBindStyle(NULL)
{

}

CLabelMsg::~CLabelMsg()
{

}

CIMMsg::CIMMsg()
{
	m_nVer = 1000;
	m_nMsgID = 0;
	m_eMsgType = MSGTYPE_MSG;
	m_tMsg = GetCurrentTime();
	m_bSelf = FALSE;
	m_eMsgAlignHor = CLH_LEFT;
	m_bShowResendButton = FALSE;
	m_hResendButton = NULL;
	m_himgFace = NULL;
	m_nMsgSenderTitle = 1;
	m_lParam = 0;
	m_hImCtrl = NULL;
	m_nMsgStartCp = 0;
	m_nMsgContentStartCp = 0;
	m_nMsgEndCp = 0;
	m_nMsgParagraphCount = 1;
}

CIMMsg::CIMMsg(const CIMMsg &rSrc)
{
	Copy(rSrc);
}

CIMMsg::~CIMMsg()
{
}

CIMMsg &CIMMsg::operator=(const CIMMsg &rSrc)
{
	if (&rSrc == this)
	{
		return *this;
	}

	Copy(rSrc);
	return *this;
}

int CIMMsg::GetVer() const
{
	return m_nVer;
}

int CIMMsg::SetMsgID(LPARAM nID)
{
	m_nMsgID = nID;

	return 0;
}

LPARAM CIMMsg::GetMsgID() const
{
	return m_nMsgID;
}

int CIMMsg::SetMsgType(IMMSGTYPE eType)
{
	m_eMsgType = eType;

	return 0;
}

IMMSGTYPE CIMMsg::GetMsgType() const
{
	return m_eMsgType;
}

int CIMMsg::SetMsgSenderID(LPCTSTR lpszOwner)
{
	m_strSenderID = lpszOwner;
	return 0;
}

LPCTSTR CIMMsg::GetMsgSenderID() const
{
	return m_strSenderID;
}

int CIMMsg::SetSelf(BOOL bSelf)
{
	m_bSelf = bSelf;
	if (m_bSelf)
	{
		m_eMsgAlignHor = CLH_RIGHT;
	}
	else
	{
		m_eMsgAlignHor = CLH_LEFT;
	}

	return 0;
}

BOOL CIMMsg::IsSelf() const
{
	return m_bSelf;
}

int CIMMsg::SetHorzLayoutMode(CONTROL_LAYOUT_HOR eAlignHor)
{
	m_eMsgAlignHor = eAlignHor;
	return 0;
}

CONTROL_LAYOUT_HOR CIMMsg::GetHorzLayoutMode() const
{
	return m_eMsgAlignHor;
}

int CIMMsg::ShowResendButton(BOOL bShow)
{
	m_bShowResendButton = bShow;

	return 0;
}

BOOL CIMMsg::IsShowResendButton() const
{
	return m_bShowResendButton;
}

int CIMMsg::SetResendButton(HWLWND hResendButton)
{
	m_hResendButton = hResendButton;

	return 0;
}

HWLWND CIMMsg::GetResendButton()
{
	return m_hResendButton;
}

int CIMMsg::SetFace(HIUIIMAGE hImgFace)
{
	m_himgFace = hImgFace;

	return 0;
}

HIUIIMAGE CIMMsg::GetFace() const
{
	return m_himgFace;
}

int CIMMsg::SetMsgSenderTitle(int nTitle)
{
	m_nMsgSenderTitle = nTitle;

	return 0;
}

int CIMMsg::GetMsgSenderTitle() const
{
	return m_nMsgSenderTitle;
}

int CIMMsg::SetMsgSender(LPCTSTR lpszSender)
{
	m_strMsgSender = lpszSender;

	return 0;
}

CIUIString CIMMsg::GetMsgSender() const
{
	return m_strMsgSender;
}

int CIMMsg::SetMsgStart(int nStart)
{
	m_nMsgStartCp = nStart;

	return 0;
}

int CIMMsg::GetMsgStart() const
{
	return m_nMsgStartCp;
}

int CIMMsg::SetMsgContentStart(int nStart)
{
	m_nMsgContentStartCp = nStart;

	return 0;
}

int CIMMsg::GetMsgContentStart() const
{
	return m_nMsgContentStartCp;
}

int CIMMsg::SetMsgEnd(int nEnd)
{
	m_nMsgEndCp = nEnd;

	return 0;
}

int CIMMsg::GetMsgEnd() const
{
	return m_nMsgEndCp;
}

int CIMMsg::SetMsgParagraphCount(int nCount)
{
	m_nMsgParagraphCount = nCount;

	return 0;
}

int CIMMsg::GetMsgParagraphCount() const
{
	return m_nMsgParagraphCount;
}

LPARAM CIMMsg::SetUserData(LPARAM lParam)
{
	LPARAM lOldParam = m_lParam;
	m_lParam = lParam;
	return lOldParam;
}

LPARAM CIMMsg::GetUserData() const
{
	return m_lParam;
}

int CIMMsg::AddMsgItem(const CRichMsgItem *pMsgItem)
{
	if (pMsgItem == NULL)
	{
		return -1;
	}

	CRichMsgItem rmi;
	rmi = *pMsgItem;

	// TODO:
	// ms - help://MS.MSDNQTR.v90.chs/shellcc/platform/commctls/richedit/richeditcontrols/aboutricheditcontrols.htm#_win32_Rich_Edit_Version_1.0
	// �����MSDN�ĵ�������Rich Edit 1.0ʹ��CR/LF�ַ������Ϊ�����ǣ�Rich Edit 2.0��ʹ��\r
	// Rich Edit 3.0ֻʹ�ûس��ַ���������ģ��Rich Edit 1.0
	// ��ͨ��Ϣ���ѻ��з�����\r
	if (!rmi.m_bOleControl)
	{
		// ����Ϣ�е�\r\n�滻��\r�� Ȼ���\nҲ�滻Ϊ\r�� ��ΪRichEditֻ��\r
		rmi.m_strMsgContent.Replace(_T("\r\n"), _T("\r"));
		rmi.m_strMsgContent.Replace(_T("\n"), _T("\r"));

		// ��¼��Ϣ���ж��ٸ�\r�����䣩
		int nMsgLength = rmi.m_strMsgContent.GetLength();
		for (int i = 0; i < nMsgLength; ++i)
		{
			if (rmi.m_strMsgContent[i] == '\r')
			{
				int nOldCount = GetMsgParagraphCount();
				SetMsgParagraphCount(nOldCount + 1);
			}
		}
	}

	m_lstpStrRichMsg.push_back(rmi);

	return 0;
}

std::list<CRichMsgItem> *CIMMsg::GetMsgItems()
{
	return &m_lstpStrRichMsg;
}

const std::list<CRichMsgItem> *CIMMsg::GetMsgItems() const
{
	return &m_lstpStrRichMsg;
}

void CIMMsg::Copy(const CIMMsg &rSrc)
{
	// ���������Ա���Զ����ԣ�������Ҫ���Ӹ�ֵ���
	int nSize = sizeof(CIMMsg);
#ifdef _UNICODE
	_ASSERT(nSize == 112);
#else
	_ASSERT(nSize == 92);
#endif
	m_nVer = rSrc.m_nVer;
	m_nMsgID = rSrc.m_nMsgID;
	m_eMsgType = rSrc.m_eMsgType;
	m_strSenderID = rSrc.m_strSenderID;
	m_tMsg = rSrc.m_tMsg;
	m_bSelf = rSrc.m_bSelf;
	m_eMsgAlignHor = rSrc.m_eMsgAlignHor;
	m_bShowResendButton = rSrc.m_bShowResendButton;
	m_hResendButton = rSrc.m_hResendButton;
	m_himgFace = rSrc.m_himgFace;
	if (NULL != m_himgFace)
	{
		m_himgFace->AddRef();
	}
	m_nMsgSenderTitle = rSrc.m_nMsgSenderTitle;
	m_strMsgSender = rSrc.m_strMsgSender;
	m_strRichMsg = m_strRichMsg;
	m_lParam = rSrc.m_lParam;

	m_hImCtrl = rSrc.m_hImCtrl;
	m_nMsgStartCp = rSrc.m_nMsgStartCp;
	m_nMsgContentStartCp = rSrc.m_nMsgContentStartCp;
	m_nMsgEndCp = rSrc.m_nMsgEndCp;
	m_nMsgParagraphCount = rSrc.m_nMsgParagraphCount;
	m_lstpStrRichMsg = rSrc.m_lstpStrRichMsg;
}

BOOL IsMsgShowSender(IMBox *pBox, const CIMMsg *pMsg, BOOL *pbShowAlias)
{
	BOOL bShowSender = TRUE; // �Ƿ���ʾ��Ϣ����������
	if (MSGTYPE_MSG != pMsg->GetMsgType())
	{
		bShowSender = FALSE;
	}
	else if (pBox->m_bQiPaoMode)
	{
		if (CLH_RIGHT == pMsg->GetHorzLayoutMode())
		{
			bShowSender = FALSE;
		}

		if (!pBox->m_bShowMsgSenderTitle)
		{
			bShowSender = FALSE;
		}

		// ����ʱ��ֻ�����ڵ�һ����ʾ
		IMRichTextBox *pIMCtrl = (IMRichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);
		int nMsgIndex = pIMCtrl->FindMsg(pMsg->GetMsgID(), NULL);
		int nPos = pIMCtrl->GetMsgPosInGroup(nMsgIndex);
		if (DT_TOP != nPos)
		{
			bShowSender = FALSE;
		}

		if (bShowSender && NULL != pbShowAlias)
		{
			*pbShowAlias = pBox->m_bShowMsgSenderAlias;
		}
	}

	return bShowSender;
}

int GetMsgInsertCp(IMBox *pBox, const CIMMsg *pMsg, BOOL *pbAddTail)
{
	std::list<CIMMsg>::const_iterator it = pBox->m_lstMsg.begin();
	for (; it != pBox->m_lstMsg.end(); ++it)
	{
		if (it->GetMsgID() == pMsg->GetMsgID())
		{
			break;
		}
	}
	if (it == pBox->m_lstMsg.end())
	{
		_ASSERT(FALSE);
		return -2;
	}

	// Դ����汾��RichEdit����֧��ʹ��-1��ΪRichEdit�Ľ�βcp��
	// MSDN�У�˵�����ʼΪ-1, ��ȡ��ѡ�С�
	// CTxtEdit::OnSetSel�д�����ʾ�����cpMin��cpMost����-1�����ջᱻ����Ϊ(0, -1)����ʾȫѡ�����ĵ�
	IMRichTextBox *pIM = (IMRichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);
	int nEnd = pIM->GetTextLengthEx(GTL_DEFAULT | GTL_NUMCHARS);

	// ָ����һ����Ϣ
	it++;

	BOOL bAddTail = TRUE;
	int nInsertCp = nEnd;
	if (it == pBox->m_lstMsg.end())
	{
		nInsertCp = nEnd;
		bAddTail = TRUE;
	}
	else
	{
		nInsertCp = it->GetMsgStart();
		bAddTail = FALSE;
	}

	if (NULL != pbAddTail)
	{
		*pbAddTail = bAddTail;
	}

	return nInsertCp;
}

// ����Ϣ��ʽ������������RichEdit�����������������
// �����Ϣ�ǲ������м������β��������Ҫ���º���������Ϣ����ʼcp
int DoInsertMsg(IMBox *pBox, const CIMMsg *pMsg)
{
	if (pMsg == NULL)
	{
		_ASSERT(FALSE);
		return -1;
	}

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);
	CComPtr<ITextDocument> pTextDocument = pRichTextBox->GetITextDocument();
	_ASSERT(NULL != (ITextDocument *)pTextDocument);

	//
	// ������Ϣ�Ĳ���λ��
	//
	BOOL bAddTail = TRUE;
	const int nInsertCp = GetMsgInsertCp(pBox, pMsg, &bAddTail);
	if (nInsertCp < -1)
	{
		return -2;
	}

	//
	// ѡ�в���λ��׼��������Ϣ
	// TODO: SetSel��Ӱ����ѡ�е��ı�����Range���ԡ�
	//
	pRichTextBox->SetSel(nInsertCp, nInsertCp);

	//
	// �������β�����Ȳ���һ������
	//
	int nCurPos = nInsertCp;
	if (bAddTail)
	{
		pRichTextBox->ReplaceSel(_T("\r"));
		nCurPos = pRichTextBox->GetTextLengthEx(GTL_DEFAULT | GTL_NUMCHARS);
	}

	//
	// ��¼����Ŀ�ʼλ��
	//
	pRichTextBox->SetSel(nCurPos, nCurPos);
	((CIMMsg *)pMsg)->SetMsgStart(nCurPos);

	//
	// ������Ϣ����Ϣ����ǰ�ȸ�ʽ��
	//

	// �Ƿ���ʾ��Ϣ����������
	BOOL bShowAlias = TRUE;
	BOOL bShowSender = IsMsgShowSender(pBox, pMsg, &bShowAlias);

	int nInsertLength = 0;	// ��Ϣ����RichEdit��ռ�õĳ��ȣ������Ϣ�����м䣬������Ϣ����ʼλ��Ҫ˳�ӡ�
	int nCurCp = 0;
	if (bShowSender)
	{
		CIUIString strName;

		if (bShowAlias)
		{
			strName = _T("��");
			strName += pBox->m_mapMsgSenderTitleAlias[pMsg->GetMsgSenderTitle()];
			strName += _T("�� ");
		}
		strName += pMsg->GetMsgSender();
		strName += _T("\r");

		pRichTextBox->ReplaceSel(strName);
		LONG lSelStart = 0;
		LONG lSelEnd = 0;
		pRichTextBox->GetSel(lSelStart, lSelEnd);
		int nNameLength = pRichTextBox->LineLength(pMsg->GetMsgStart());

		// ����Title��ɫ
		pRichTextBox->SetSel(pMsg->GetMsgStart(), pMsg->GetMsgStart() + nNameLength);
		CHARFORMAT cf = { 0 };
		cf.cbSize = sizeof(CHARFORMAT);
		cf.dwMask |= CFM_COLOR;
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		cf.crTextColor = pBox->m_crTitle;
		pRichTextBox->SetSelectionCharFormat(cf);

		// ������Title��ɫ�󣬱������¶�λ����λ��
		pRichTextBox->SetSel(lSelEnd, lSelEnd);

		// �������ֵĶ����ʽ��ֻ�б��˲���ʾ���������֣��Լ��ǲ���ʾ�ġ�
		// ������Զ��ʾ����࣬���ԣ�ֻ��Ҫ�ڲ�����Ϣʱ���������ֵĶ����ʽ���ɣ�֮�󶼲���Ҫ���á�
		CComPtr<ITextRange> pTextRangeSender = NULL;
		pTextDocument->Range(pMsg->GetMsgStart(), pMsg->GetMsgStart() + nNameLength, &pTextRangeSender);

#ifdef _DEBUG
		BSTR bstr;
		pTextRangeSender->GetText(&bstr);
#endif // _DEBUG

		CComPtr<ITextPara> pTextParaSender = NULL;
		pTextRangeSender->GetPara(&pTextParaSender);
		// �����м��
		pTextParaSender->SetSpaceBefore(GetXFPPTSFromPixel(pBox->m_nTitleSpaceBefore));
		pTextParaSender->SetSpaceAfter(GetXFPPTSFromPixel(pBox->m_nTitleSpaceAfter));
		pTextParaSender->SetIndents((float)pBox->m_nTitleLeftIndents,
			GetXFPPTSFromPixel(pBox->m_nSenderLeftIndent), 0);
		pTextRangeSender->SetPara(pTextParaSender);
	}

	//
	// ������Ϣ���ĵ�cp
	//
	if (bAddTail)
	{
		nCurCp = pRichTextBox->GetTextLengthEx(GTL_DEFAULT | GTL_NUMCHARS);
		((CIMMsg *)pMsg)->SetMsgContentStart(nCurCp - pMsg->GetMsgStart());
	}
	else
	{
		LONG lSelStart = 0;
		LONG lSelEnd = 0;
		pRichTextBox->GetSel(lSelStart, lSelEnd);
		((CIMMsg *)pMsg)->SetMsgContentStart(lSelStart - pMsg->GetMsgStart());
	}

	//
	// 2. ������Ϣ����
	//
	std::list<CRichMsgItem>::const_iterator itItem = pMsg->GetMsgItems()->begin();
	for (; itItem != pMsg->GetMsgItems()->end(); ++itItem)
	{
		const CRichMsgItem *pRichMsgItem = &(*itItem);

		//
		// 1 Ole�ؼ�
		//
		if (pRichMsgItem->m_bOleControl)
		{
			OleControl *pCustomOleCtrl = new OleControl(1, pBox->m_pREBox->hwnd);

			// ��IUI�ؼ��󶨵�OLE�ؼ���
			pCustomOleCtrl->SetOleBindWindowless(pRichMsgItem->m_hOleBindWindowless);

			// ��OLE����Rich Text Box.
			int nDPIedWidth = GetDPIWidth(pRichMsgItem->m_size.cx);
			int nDPIedHeight = GetDPIHeight(pRichMsgItem->m_size.cy);
			pRichTextBox->InsertOle(pCustomOleCtrl, REO_CP_SELECTION, nDPIedWidth, nDPIedHeight);

			// ֪ͨRichEdit�����ڣ�������һ���µ��Զ���OLE�ؼ�
			RoutedEventArgs arg;
			arg.hSender = pRichTextBox->GetSafeHwnd();
			arg.hOriginalSender = pRichTextBox->GetSafeHwnd();
			arg.RoutedEvent = REN_ADDED_CUSTOM_OLE;
			arg.eRoutingStrategy = RS_BUBBLE;
			arg.lParam = (LPARAM)pCustomOleCtrl;
			LRESULT lr = IUI::RaiseEvent(arg.hOriginalSender, &arg);
		}
		else
		{
			//
			// ��ͨ�ı�
			//

			long nStartCp = -1;
			long nEndCp = -1;
			pRichTextBox->GetSel(nStartCp, nEndCp);

			_ASSERT(nStartCp == nEndCp);
			pRichTextBox->ReplaceSel(pRichMsgItem->m_strMsgContent);

			long nStartCp2 = -1;
			long nEndCp2 = -1;
			pRichTextBox->GetSel(nStartCp2, nEndCp2);
			_ASSERT(nStartCp2 == nEndCp2);

			// �����ı���ɫ
			pRichTextBox->SetSel(nStartCp, nEndCp2);
			CHARFORMAT cf = { 0 };
			cf.cbSize = sizeof(CHARFORMAT);
			cf.dwMask |= CFM_COLOR;
			cf.dwEffects &= ~CFE_AUTOCOLOR;
			cf.crTextColor = pRichMsgItem->m_crText;
			pRichTextBox->SetSelectionCharFormat(cf);

			// ��������ɫ�󣬱���Ѳ���λ�ö�λ���ղ���ĵط�������������ľͰ��ı������ˡ�
			pRichTextBox->SetSel(nEndCp2, nEndCp2);
		}
	}

	// ��¼����Ľ���λ��
	if (bAddTail)
	{
		nCurCp = pRichTextBox->GetTextLengthEx(GTL_DEFAULT | GTL_NUMCHARS);
	}
	else
	{
		LONG lSelStart = 0;
		LONG lSelEnd = 0;
		pRichTextBox->GetSel(lSelStart, lSelEnd);
		nCurCp = lSelEnd;
	}
	((CIMMsg *)pMsg)->SetMsgEnd(nCurCp - pMsg->GetMsgStart());

	//
	// 3. ������Ϣ��Ķ����ʽ�� ���˷�����Ϣ����Զ��ʾ����ֻ࣬��Ҫ�ڲ�����Ϣʱ����һ�μ��ɡ�
	//
	CComPtr<ITextRange> pTextRangeMsg = NULL;
	pTextDocument->Range(pMsg->GetMsgStart() + pMsg->GetMsgContentStart(),
		pMsg->GetMsgStart() + pMsg->GetMsgEnd(), &pTextRangeMsg);

#ifdef _DEBUG
	BSTR bstr;
	pTextRangeMsg->GetText(&bstr);
#endif // _DEBUG

	CComPtr<ITextPara> pTextParaMsg = NULL;
	pTextRangeMsg->GetPara(&pTextParaMsg);
	pTextParaMsg->SetIndents(0, GetXFPPTSFromPixel(pBox->m_nMsgLeftIndent),
		GetXFPPTSFromPixel(pBox->m_nMsgRightIndent));
	pTextRangeMsg->SetPara(pTextParaMsg);

	// Ϊ�˷�������иߣ�ÿ����Ϣ������������һ�����С�
	if (bAddTail)
	{
		pRichTextBox->ReplaceSel(_T("\r"));
	}
	else
	{
		pRichTextBox->ReplaceSel(_T("\r\r"));
	}

	//
	// ƽ��֮�����Ϣ
	//
	if (!bAddTail)
	{
		// �õ���ǰ��λ��
		LONG lSelStart = 0;
		LONG lSelEnd = 0;
		pRichTextBox->GetSel(lSelStart, lSelEnd);

		// ��Ϣ��������ӵĳ���
		int nAddLength = lSelStart - nInsertCp;

		std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
		for (; it != pBox->m_lstMsg.end(); ++it)
		{
			if (it->GetMsgID() == pMsg->GetMsgID())
			{
				++it;
				for (; it != pBox->m_lstMsg.end(); ++it)
				{
					int nOldStartCp = it->GetMsgStart();
					it->SetMsgStart(nOldStartCp + nAddLength);
				}

				break;
			}
		}
	}

	DoSetParaFormat(pBox);

	return 0;
}

// ����Ϣ��RichEdit������ɾ����ɾ���󣬻���Ҫ���º���������Ϣ����ʼcp
int DoDeleteMsg(IMBox *pBox, int nIndex)
{
	std::list<CIMMsg>::iterator itMsgItem = pBox->m_lstMsg.begin();
	std::advance(itMsgItem, nIndex);

	if (itMsgItem == pBox->m_lstMsg.end())
	{
		return -1;
	}

	CIMMsg *pMsg = &(*itMsgItem);
	if (pMsg == NULL)
	{
		_ASSERT(FALSE);
		return -2;
	}

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);
	CComPtr<ITextDocument> pTextDocument = pRichTextBox->GetITextDocument();
	_ASSERT(NULL != (ITextDocument *)pTextDocument);

	//
	// ѡ��������Ϣ���滻Ϊ��
	// TODO: SetSel��Ӱ����ѡ�е��ı�����Range���ԡ�
	//
	int nStartCp = pMsg->GetMsgStart();
	if (0 == nIndex)
	{
		nStartCp = 0;
	}
	else
	{
		// ����Ϣǰ��Ļ��з�Ҳɾ������
		std::list<CIMMsg>::iterator itMsgItemPrev = pBox->m_lstMsg.begin();
		std::advance(itMsgItemPrev, nIndex - 1);
		CIMMsg *pMsgPrev = &(*itMsgItemPrev);
		nStartCp = pMsgPrev->GetMsgStart() + pMsgPrev->GetMsgEnd();
	}

	int nEndCp = pMsg->GetMsgEnd();
	pRichTextBox->SetSel(nStartCp, pMsg->GetMsgStart() + nEndCp);
	pRichTextBox->ReplaceSel(_T(""));

	// ɾ������cp����
	int nDeleteLength = pMsg->GetMsgStart() + nEndCp - nStartCp;

	//
	// ƽ��֮�����Ϣ
	//
	std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
	for (; it != pBox->m_lstMsg.end(); ++it)
	{
		if (it->GetMsgID() == pMsg->GetMsgID())
		{
			++it;
			for (; it != pBox->m_lstMsg.end(); ++it)
			{
				int nOldStartCp = it->GetMsgStart();
				it->SetMsgStart(nOldStartCp - nDeleteLength);
			}

			break;
		}
	}

	return 0;
}

// ��Ϣ��ʾ��RichEdit����໹���Ҳ�
BOOL IsMsgShowRight(IMBox *pBox, const CIMMsg *pMsg)
{
	// ֻ��������ģʽ�£��Լ����͵���Ϣ����RichEdit���С��ĳ��ֵʱ����Ϣ����ʾ��RichEdit�Ҳ�
	BOOL bShowLeft = TRUE;
	if (pBox->m_bQiPaoMode && CLH_RIGHT == pMsg->GetHorzLayoutMode())
	{
		CIUIRect rcClient;
		GetClientRect(pBox->m_pREBox->hwnd, rcClient);

		if (rcClient.Width() < pBox->m_nMaxRelayoutWidth)
		{
			bShowLeft = FALSE;
		}
	}

	return !bShowLeft;
}

BOOL IsMsgNewLine(
	IMBox *pBox,
	const CIMMsg *pMsg,
	__out int *pnStartLine,
	__out int *pnEndLine)
{
	if (pMsg == NULL)
	{
		return FALSE;
	}

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);

	// ��û��������������£������Ƿ���Ҫ������ʾ
	int nStartLine = pRichTextBox->LineFromChar(pMsg->GetMsgStart() + pMsg->GetMsgContentStart());
	int nEndLine = pRichTextBox->LineFromChar(pMsg->GetMsgStart() + pMsg->GetMsgEnd());
	_ASSERT(nEndLine - nStartLine + 1 >= pMsg->GetMsgParagraphCount());

	if (pnStartLine != NULL)
	{
		*pnStartLine = nStartLine;
	}

	if (pnEndLine != NULL)
	{
		*pnEndLine = nEndLine;
	}

	BOOL bNewLine = (nEndLine - nStartLine + 1 > pMsg->GetMsgParagraphCount());

	return bNewLine;
}

int DoLayoutRightMsg(IMBox *pBox, const CIMMsg *pMsg)
{
	_ASSERT(pBox->m_bQiPaoMode);

	if (IsIconic(GetHostWnd(pBox->m_pREBox->hwnd)))
	{
		return 1;
	}

	CIUIRect rcClient;
	GetClientRect(pBox->m_pREBox->hwnd, rcClient);

	// ��Ϣ�Ƿ��л��У��ڲ�����ʱ������Լ����͵���Ϣ����Ҫ��ʾ���Ҳࣩ�Ķ����ʽ��������������Ϊ0.
	int nStartLine = 0;
	int nEndLine = 0;

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);

	BOOL bNewLine = IsMsgNewLine(pBox, pMsg, &nStartLine, &nEndLine);

	// �����е���Ϣ������Ҫ����������
	if (bNewLine)
	{
		return 1;
	}

	// û�����е���Ϣ����Ҫ����������������Ϣ����ƽ��
	CIUIRect rcQiPao;

	int nMinLeftLine = MAXINT; // �����У�left����Сֵ
	int nMaxRightLine = 0; // �����У�right�����ֵ

	for (int i = nStartLine; i <= nEndLine; ++i)
	{
		CIUIPoint ptLine;
		int nLineWidth = 0;
		int nLineHeight = 0;

		if (i == nEndLine)
		{
			pRichTextBox->GetLineRect(i, &ptLine, &nLineWidth, &nLineHeight);
		}
		else
		{
			pRichTextBox->GetLineRect(i, &ptLine, &nLineWidth, NULL);
		}

		if (i == nStartLine)
		{
			rcQiPao.top = ptLine.y;
		}

		if (i == nEndLine)
		{
			rcQiPao.bottom = ptLine.y + nLineHeight;
		}

		nMinLeftLine = min(nMinLeftLine, ptLine.x);
		nMaxRightLine = max(nMaxRightLine, ptLine.x + nLineWidth);
	}

	rcQiPao.left = nMinLeftLine;
	rcQiPao.right = nMaxRightLine;

	// ��������Ҫ��ʾ���Ҳࡢ����������ʱ��������������richedit��ȼ�
	// ���ݿ�ȣ�����ᵼ��ԭ�����Ե�����ʾ�Ķ��任���С�
	// �²��ǻ�Ҫ������β�Ļس����еĿռ䣬
	// ������ռ�Ŀ���ǿո�Ŀ�ȡ��� RichEdit���Զ��Ѹ�ƫ������Ϊ0����
	// nQiPaoLeftOffsetAdjust����������ֵ
	const int nQiPaoLeftOffsetAdjust = 20; // ���ֵ����ʱ��һ���ַ���ȱȽϺ��ʣ�ֻ��󲻻�С��
	//nQiPaoLeftOffsetAdjust = GetCharWidthW(hdc, 0, 1, "");

	CIUIRect rcInset;
	IUI::GetLayoutInset(pBox->m_pREBox->hwnd, rcInset);

	rcClient.DeflateRect(rcInset);

	int nXOffset = rcClient.Width() - pBox->m_nMsgRightIndent - rcQiPao.Width() - nQiPaoLeftOffsetAdjust;
	if (nXOffset < 0)
	{
		_ASSERT(FALSE);
		nXOffset = 0;
		return 0;
	}

	rcQiPao.OffsetRect(-rcQiPao.left, 0);
	rcQiPao.OffsetRect(nXOffset, 0);

	CComPtr<ITextDocument> pTextDocument = pRichTextBox->GetITextDocument();

	CComPtr<ITextRange> pTextRange = NULL;
	pTextDocument->Range(pMsg->GetMsgStart() + pMsg->GetMsgContentStart(),
		pMsg->GetMsgStart() + pMsg->GetMsgEnd(), &pTextRange);

#ifdef _DEBUG
	BSTR bstr;
	pTextRange->GetText(&bstr);
#endif // _DEBUG

	CComPtr<ITextPara> pTextPara = NULL;
	pTextRange->GetPara(&pTextPara);
	pTextPara->SetIndents(0, GetXFPPTSFromPixel(nXOffset),
		GetXFPPTSFromPixel(pBox->m_nMsgRightIndent));
	pTextRange->SetPara(pTextPara);

	return 0;
}

// ����ʾ������Ϣ������ʱ���������Ϣ��Ҫ������ʾ���ҵ��С�
int DoLayoutCenterMsg(IMBox *pBox, const CIMMsg *pMsg)
{
	_ASSERT(pBox->m_bQiPaoMode);

	if (IsIconic(GetHostWnd(pBox->m_pREBox->hwnd)))
	{
		return 1;
	}

	CIUIRect rcClient;
	GetClientRect(pBox->m_pREBox->hwnd, rcClient);

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);

	CIUIPoint ptLine;
	int nLineWidth = 0;
	int nLineHeight = 0;
	int nLineIndex = pRichTextBox->LineFromChar(pMsg->GetMsgStart() + pMsg->GetMsgContentStart());
	pRichTextBox->GetLineRect(nLineIndex, &ptLine, &nLineWidth, &nLineHeight);

	int nXOffset = (rcClient.Width() - nLineWidth) / 2;
	if (nXOffset < 0)
	{
		_ASSERT(FALSE);
		nXOffset = 0;
		return 0;
	}

	CComPtr<ITextDocument> pTextDocument = pRichTextBox->GetITextDocument();

	CComPtr<ITextRange> pTextRange = NULL;
	pTextDocument->Range(pMsg->GetMsgStart() + pMsg->GetMsgContentStart(),
		pMsg->GetMsgStart() + pMsg->GetMsgEnd(), &pTextRange);

#ifdef _DEBUG
	BSTR bstr;
	pTextRange->GetText(&bstr);
#endif // _DEBUG

	CComPtr<ITextPara> pTextPara = NULL;
	pTextRange->GetPara(&pTextPara);
	pTextPara->SetIndents(0, GetXFPPTSFromPixel(nXOffset),
		GetXFPPTSFromPixel(pBox->m_nMsgRightIndent));
	pTextRange->SetPara(pTextPara);

	return 0;
}

// �ڿؼ����Ż�������Ҫ���µ�ʱ�������������ݵĶ����ʽ��
// ���ڱ��˷��͵���Ϣ���Ѿ��ڲ����ʱ�����ù������ʽ�����������У����ᷢ���仯
// ���Ա��ӿڣ�ֻ��Ҫ���²����Լ����͵���Ϣ���ɡ�
int DoSetParaFormat(IMBox *pBox)
{
	if (pBox->m_lstMsg.empty())
	{
		return 1;
	}

	SetULWNoRedraw(GetHostWnd(pBox->m_pREBox->hwnd), TRUE);

	CIUIRect rcClient;
	GetClientRect(pBox->m_pREBox->hwnd, rcClient);

	// ����Ҫ���ö����ʽʱ������RichEdit�Ŀ���б仯����Ҫ��RichEdit��������Ϣ���ã�������Ϊ
	// ��ʹ���ص���Ϣ����RichEdit��ȱ仯��Ҳ���ܷ������У���ͻᵼ�¹�����Χ�ı仯��
	// ���磬һ���Լ�������Ϣ�������ǲ��ɼ�״̬����ʾ�ڴ����Ҳ࣬�����У�
	// ����������Ϊ200���ı�����Ϊ20���ַ���20���ַ�ռ�õĿ��Ϊ400����ʱRichedit�Ŀ��Ϊ600����
	// ��RichEdit��ȵ�������200�󣬵��޷�����20���ַ�ʱ�������ȵ�����500����20���ַ���Ҫ���С�
	// �⽫���¹�����Χ��󡣵�ʵ���ϣ�����500��ȵ�RichEdit����20���ַ��ǲ���Ҫ���еġ�
	// ���ԣ����ڲ��ɼ�����Ϣ������ֻ��Ҫ����������������Ϊ0���ɡ�����Ҫ�������ݺ�ͷ������꣬
	// ��Ϊ���ڹ������ɼ���Χ��ʱ��ͷ������ݵ����꣬��ʵʱ��ȡ�ġ�

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);
	CComPtr<ITextDocument> pTextDocument = pRichTextBox->GetITextDocument();

	// ��һ��ѭ�����������Լ����͵���Ϣ��������������Ϊ0(����й̶������Ļ�������Ϊ�̶�����)
	// �������ڵڶ���ѭ��ʱ��ȡ�õĿɼ���Χ��Ϣ�ž�ȷ��
	std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
	for (; it != pBox->m_lstMsg.end(); ++it)
	{
		const CIMMsg *pMsg = &(*it);

		// ���ڶԷ����͵���Ϣ����Ϊ��Զ��ʾ����࣬�����ڲ�����Ϣ��ʱ�򣬾��Ѿ�Ϊ�������˶����ʽ��
		// ������RichEdit��ʱ�򣬲���Ҫ���á� ���ԣ�ֻ��Ҫ�����Լ����͵���Ϣ����
		if (pBox->m_bQiPaoMode && pMsg->GetHorzLayoutMode() == CLH_RIGHT)
		{
			//
			// ���Լ�������Ϣ֮ǰ�Ļ��з����Ƶ�RichEdit�Ҳ�����
			//
			CIUIRect rcWnd;
			pRichTextBox->GetWindowRectToParent(rcWnd);

			// ʹ��Comָ�룬��Range���ֽ���ڲ������������ñ��淵�ص�ITextRange
			// ������Ҫʹ��Comָ�룬�����ͷţ�����������ڴ�й¶��
			CComPtr<ITextRange> pTextRangeEnter = NULL;
			pTextDocument->Range(pMsg->GetMsgStart(), pMsg->GetMsgStart() + pMsg->GetMsgContentStart(),
				&pTextRangeEnter);

#ifdef _DEBUG
			BSTR bstr;
			pTextRangeEnter->GetText(&bstr);
#endif // _DEBUG

			CComPtr<ITextPara> pTextParaEnter = NULL;
			pTextRangeEnter->GetPara(&pTextParaEnter);
			pTextParaEnter->SetIndents(0, GetXFPPTSFromPixel(rcWnd.Width() + 100), 0);
			pTextRangeEnter->SetPara(pTextParaEnter);

			//
			// ����Ϣ����������
			//
			CComPtr<ITextRange> pTextRangeMsg = NULL;
			pTextDocument->Range(pMsg->GetMsgStart() + pMsg->GetMsgContentStart(),
				pMsg->GetMsgStart() + pMsg->GetMsgEnd(), &pTextRangeMsg);

#ifdef _DEBUG
			pTextRangeMsg->GetText(&bstr);
#endif // _DEBUG

			CComPtr<ITextPara> pTextParaMsg = NULL;
			pTextRangeMsg->GetPara(&pTextParaMsg);
			pTextParaMsg->SetIndents(0, GetXFPPTSFromPixel(pBox->m_nMsgLeftIndent),
				GetXFPPTSFromPixel(pBox->m_nMsgRightIndent));
			pTextRangeMsg->SetPara(pTextParaMsg);
		}
	}

	// �ڶ���ѭ����������Ҫ��ʾ���Ҳ��������Ϣ
	for (it = pBox->m_lstMsg.begin(); it != pBox->m_lstMsg.end(); ++it)
	{
		const CIMMsg *pMsg = &(*it);

		if (IsMsgShowRight(pBox, pMsg))
		{
			// ������Ϣ
			DoLayoutRightMsg(pBox, pMsg);
		}
		else if (CLH_CENTER == pMsg->GetHorzLayoutMode())
		{
			// ������Ҫ������ʾ����Ϣ
			DoLayoutCenterMsg(pBox, pMsg);
		}
	}

	SetULWNoRedraw(GetHostWnd(pBox->m_pREBox->hwnd), FALSE);

	return 0;
}

int DoCalFaceRect(IMBox *pBox, const CIMMsg *pMsg, __out LPRECT lprcFace)
{
	if (pMsg == NULL || lprcFace == NULL)
	{
		return -1;
	}

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);

	CIUIRect rcClient;
	GetClientRect(pBox->m_pREBox->hwnd, rcClient);

	CIUIRect rcInset;
	IUI::GetLayoutInset(pBox->m_pREBox->hwnd, rcInset);

	// ����ͷ������
	CIUIRect rcFace(0, 0, 0, 0);

	// �����о����RichEdit��GetCharPos���ص��ǵ�ǰ����λ�����RichEdit�����꣬
	// ���ԣ����ص����꣬����Ҫ���й���λ��������
	CIUIPoint ptFace = pRichTextBox->GetCharPos(pMsg->GetMsgStart());

	if (IsMsgShowRight(pBox, pMsg))
	{
		rcFace.right = rcClient.right - rcInset.right - (pBox->m_nMsgRightIndent - pBox->m_sizeFace.cx) / 2;
		rcFace.left = rcFace.right - pBox->m_sizeFace.cx;
		rcFace.top = rcClient.top + ptFace.y;
		rcFace.bottom = rcFace.top + pBox->m_sizeFace.cy;
	}
	else
	{
		rcFace.left = rcClient.left + rcInset.left + (pBox->m_nSenderLeftIndent - pBox->m_sizeFace.cx) / 2;
		rcFace.right = rcFace.left + pBox->m_sizeFace.cx;
		rcFace.top = rcClient.top + ptFace.y;
		rcFace.bottom = rcFace.top + pBox->m_sizeFace.cy;
	}

	*lprcFace = rcFace;

	return 0;
}

// ���㻻��(��ʾ�������Ƿ����CIMMsg::m_nMsgParagraphCount)��Ϣ����������
int DoCalNewLineQiPaoRect(IMBox *pBox, const CIMMsg *pMsg, __out LPRECT lprcQiPao)
{
	if (lprcQiPao == NULL)
	{
		return -1;
	}

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);

	CIUIRect rcClient;
	GetClientRect(pBox->m_pREBox->hwnd, rcClient);

	CIUIRect rcInset;
	IUI::GetLayoutInset(pBox->m_pREBox->hwnd, rcInset);
	rcClient.DeflateRect(rcInset);

	// �õ���Ϣ��һ���ַ���������
	CIUIPoint ptFirstChar = pRichTextBox->GetCharPos(pMsg->GetMsgStart() + pMsg->GetMsgContentStart());

	lprcQiPao->left = rcClient.left + pBox->m_nMsgLeftIndent;
	lprcQiPao->right = rcClient.right - pBox->m_nMsgRightIndent;
	lprcQiPao->top = ptFirstChar.y;

	// ������Ϣ���һ�����һ���ַ������½�����
	int nLine = pRichTextBox->LineFromChar(pMsg->GetMsgStart() + pMsg->GetMsgEnd());
	CIUIPoint ptLastMsgLine;
	int nLineHeight = 0;
	pRichTextBox->GetLineRect(nLine, &ptLastMsgLine, NULL, &nLineHeight);

	lprcQiPao->bottom = ptLastMsgLine.y + nLineHeight;

	return 0;
}

// ���㲻����(��ʾ�������Ƿ����CIMMsg::m_nMsgParagraphCount)��Ϣ��ʾʱ����������
int DoCalSingleLineQiPaoRect(IMBox *pBox, const CIMMsg *pMsg, int nStartLine, int nEndLine,
	__out LPRECT lprcQiPao)
{
	if (lprcQiPao == NULL)
	{
		return -1;
	}

	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pBox->m_pREBox->hwnd);

	CIUIRect rcQiPao;

	int nMinLeftLine = MAXINT; // �����У�left����Сֵ
	int nMaxRightLine = 0; // �����У�right�����ֵ

	for (int i = nStartLine; i <= nEndLine; ++i)
	{
		CIUIPoint ptLine;
		int nLineWidth = 0;
		int nLineHeight = 0;

		if (i == nEndLine)
		{
			pRichTextBox->GetLineRect(i, &ptLine, &nLineWidth, &nLineHeight);
		}
		else
		{
			pRichTextBox->GetLineRect(i, &ptLine, &nLineWidth, NULL);
		}

		if (i == nStartLine)
		{
			rcQiPao.top = ptLine.y;
		}

		if (i == nEndLine)
		{
			rcQiPao.bottom = ptLine.y + nLineHeight;
		}

		nMinLeftLine = min(nMinLeftLine, ptLine.x);
		nMaxRightLine = max(nMaxRightLine, ptLine.x + nLineWidth);
	}

	rcQiPao.left = nMinLeftLine;
	rcQiPao.right = nMaxRightLine;

	*lprcQiPao = rcQiPao;

	return 0;
}

// Ϊ�����ܺͽ����ʾ���������
// �ڴ�ֱ����ʱ��ֻ�����������꣬�����ö����ʽ������ʹ����Ϣ�ڻ�������б�־
int DoCalQiPaoRect(IMBox *pBox, const CIMMsg *pMsg, __out LPRECT lprcQiPao)
{
	if (lprcQiPao == NULL)
	{
		return -1;
	}

	// ��Ϣ�Ƿ��л��У��ڲ�����ʱ������Լ����͵���Ϣ����Ҫ��ʾ���Ҳࣩ�Ķ����ʽ��������������Ϊ0.
	int nStartLine = 0;
	int nEndLine = 0;
	BOOL bNewLine = IsMsgNewLine(pBox, pMsg, &nStartLine, &nEndLine);

	// ����Ĵ��룬���ٴΰѶ����������������Ϊ����ֵ��
	if (bNewLine)
	{
		DoCalNewLineQiPaoRect(pBox, pMsg, lprcQiPao);
	}
	else
	{
		DoCalSingleLineQiPaoRect(pBox, pMsg, nStartLine, nEndLine, lprcQiPao);
	}

	return 0;
}

// ��������������㡰���·��͡���ť������
int DoCalResendButtonRect(
	IMBox *pBox,
	const CIMMsg *pMsg,
	__in LPCRECT lprcQiPao,
	__out LPRECT lprcResendButton)
{
	if (lprcResendButton == NULL)
	{
		return -1;
	}

	if (pBox->m_bQiPaoMode)
	{
		if (NULL == lprcQiPao)
		{
			return -2;
		}

		if (IsMsgShowRight(pBox, pMsg))
		{
			lprcResendButton->bottom = lprcQiPao->bottom - pBox->m_ptResendButtonMargin.y;
			lprcResendButton->top = lprcResendButton->bottom - pBox->m_sizeResendButton.cy;
			lprcResendButton->right = lprcQiPao->left - pBox->m_ptResendButtonMargin.x;
			lprcResendButton->left = lprcResendButton->right - pBox->m_sizeResendButton.cx;
		}
		else
		{
			lprcResendButton->bottom = lprcQiPao->bottom - pBox->m_ptResendButtonMargin.y;
			lprcResendButton->top = lprcResendButton->bottom - pBox->m_sizeResendButton.cy;
			lprcResendButton->left = lprcQiPao->right + pBox->m_ptResendButtonMargin.x;
			lprcResendButton->right = lprcResendButton->left + pBox->m_sizeResendButton.cx;
		}
	}
	else
	{
		// TODO: ��ʹ������ģʽʱ��ҲҪ��������ꡣ
		_ASSERT(FALSE);
	}

	return 0;
}

int OnIMInsertMsg(IMBox *pBox, int nIndex, const CIMMsg *pMsg)
{
	if (NULL == pBox || NULL == pMsg)
	{
		return -1;
	}

	if (nIndex < -1)
	{
		return -2;
	}

	CIMMsg msg;
	msg = *pMsg;

	int nInsertIndex = -1;
	// ������������Ϊ������Ӳ���������Է��ز�����ָ����в�����
	if (-1 == nIndex)
	{
		pBox->m_lstMsg.push_back(msg);
		pMsg = &(pBox->m_lstMsg.back());
		nInsertIndex = (int)pBox->m_lstMsg.size() - 1;
	}
	else
	{
		if (nIndex > (int)pBox->m_lstMsg.size())
		{
			nIndex = (int)pBox->m_lstMsg.size();
		}

		std::list<CIMMsg>::iterator itInsertPos = pBox->m_lstMsg.begin();
		std::advance(itInsertPos, nIndex);
		std::list<CIMMsg>::iterator itInsert =  pBox->m_lstMsg.insert(itInsertPos, msg);
		pMsg = &(*itInsert);
		nInsertIndex = std::distance(pBox->m_lstMsg.begin(), itInsert);
	}

	// ��¼����λ�á� ��ǰ�Ƿ������ĩβ
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLBARINFO);
	si.fMask = SIF_ALL;
	BOOL bRet = GetScrollInfo(pBox->m_pREBox->hwnd, SB_VERT, &si);
	BOOL bScrollToBottom = FALSE;
	if (bRet)
	{
		if (si.nPos >= si.nMax - (int)si.nPage)
		{
			bScrollToBottom = TRUE;
		}
	}

	DoInsertMsg(pBox, pMsg);

	// ��������ʱ�����ݹ����������棬��������Ȼ�������档
	// ��������ʱ���������м䣬����󲻹���������Ӱ���û�������������ݡ�
	if (bScrollToBottom)
	{
		SendMessage(pBox->m_pREBox->hwnd, WM_VSCROLL, MAKEWPARAM(SB_BOTTOM, 0), 0);
	}

	// ��������
	return nInsertIndex;
}

int OnIMDeleteMsg(IMBox *pBox, int nIndex)
{
	if (NULL == pBox)
	{
		return -1;
	}

	if (nIndex < 0 || nIndex >= (int)pBox->m_lstMsg.size())
	{
		return -2;
	}

	// ��RichEdit��ɾ��
	DoDeleteMsg(pBox, nIndex);

	// �����ݽṹ��ɾ��
	std::list<CIMMsg>::iterator itMsgItem = pBox->m_lstMsg.begin();
	std::advance(itMsgItem, nIndex);
	pBox->m_lstMsg.erase(itMsgItem);

	return 0;
}

class COleResendButtonHandler : public CWLWndHandler
{
public:
	COleResendButtonHandler()
		: m_pBindMsg(NULL)
	{}
	virtual ~COleResendButtonHandler() {}

protected:
	virtual LRESULT EventHandler(HWLWND hWndThis, RoutedEventArgs *pe)
	{
		if (pe->hOriginalSender == hWndThis)
		{
			if (RS_BUBBLE == pe->eRoutingStrategy)
			{
				if (UE_BUTTON_CLICK == pe->RoutedEvent)
				{
					RoutedEventArgs args;
					args.RoutedEvent = UE_IM_RESEND_MSG;
					args.eRoutingStrategy = RS_BUBBLE;
					args.hSender = args.hOriginalSender = hWndThis;
					args.wParam = (m_pBindMsg == NULL) ? NULL : m_pBindMsg->GetMsgID();
					args.lParam = (LPARAM)m_pBindMsg;
					RaiseEvent(hWndThis, &args);
					if (args.bHandled)
					{
						pe->bHandled = TRUE;
						return 0;
					}
				}
				else if (WM_NCDESTROY == pe->RoutedEvent)
				{
					delete this;
					return 0;
				}
			}
		}

		return 0;
	}

public:
	CIMMsg *m_pBindMsg;
};

// IMM_SHOW_RESEND_BUTTON handler
int OnShowResendButton(IMBox *pBox, UINT uMsgID, BOOL bShow)
{
	if (pBox == NULL)
	{
		return -1;
	}

	int nRet = -2;

	// ���ҵ�ָ����Ϣ
	std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
	for (; it != pBox->m_lstMsg.end(); ++it)
	{
		CIMMsg *pMsg = &(*it);
		if (pMsg->GetMsgID() == uMsgID)
		{
			nRet = 0;

			pMsg->ShowResendButton(bShow);

			if (pMsg->IsShowResendButton())
			{
				if (NULL == pMsg->GetResendButton())
				{
					// ����Resend��ť�ؼ�
					COleResendButtonHandler *pHandler = new COleResendButtonHandler;
					HWLWND hBtnResend = IUI::CreateWindowEx(pHandler,
							0, IUI_BUTTON, NULL, WS_VISIBLE,
							0, 0, 0, 0,
							GetHostWnd(pBox->m_pREBox->hwnd), pBox->m_pREBox->hwnd,
							_T("IDC_BTN_RESEND"), 0, NULL);
					if (NULL == hBtnResend)
					{
						_ASSERT(FALSE);
						return -3;
					}

					pHandler->m_pBindMsg = pMsg;
					PushButton_BindStyle(hBtnResend, pBox->m_pResendButtoStyle);
					SendMessage(hBtnResend, WLM_SETHIDEOLEBORDER, 0, TRUE);

					pMsg->SetResendButton(hBtnResend);
				}
			}
			else
			{
				if (NULL != pMsg->GetResendButton())
				{
					DestroyWindow(pMsg->GetResendButton());
					pMsg->SetResendButton(NULL);
				}
			}
		}
	}

	IUI::Invalidate(pBox->m_pREBox->hwnd);

	return nRet;
}

BOOL OnIsMsgShowResendButton(IMBox *pBox, UINT uMsgID)
{
	if (pBox == NULL)
	{
		return -1;
	}

	BOOL bShowRet = FALSE;

	// ���ҵ�ָ����Ϣ
	std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
	for (; it != pBox->m_lstMsg.end(); ++it)
	{
		CIMMsg *pMsg = &(*it);
		if (pMsg->GetMsgID() == uMsgID)
		{
			// ֻ���Լ����͵���Ϣ���ſ�����Ҫ�����·��͡���ť
			if (CLH_RIGHT == pMsg->GetHorzLayoutMode())
			{
				bShowRet = pMsg->IsShowResendButton();
			}
		}
	}

	return bShowRet;
}

// "��ʾ������Ϣ"��ť��Ӧ��
// ����Ӧ����༭���еĴ���
class COleLoadMoreMsgHandler : public CWLWndHandler
{
public:
	COleLoadMoreMsgHandler()
	{}
	virtual ~COleLoadMoreMsgHandler()
	{}

protected:
	virtual LRESULT EventHandler(HWLWND hWndThis, RoutedEventArgs *pe)
	{
		if (pe->hOriginalSender == hWndThis)
		{
			if (UE_BUTTON_CLICK == pe->RoutedEvent)
			{
				RoutedEventArgs args;
				args.RoutedEvent = UE_IM_SHOW_MORE_MSG;
				args.eRoutingStrategy = RS_BUBBLE;
				args.hSender = args.hOriginalSender = hWndThis;
				RaiseEvent(hWndThis, &args);
			}
			else if (WM_NCDESTROY == pe->RoutedEvent)
			{
				delete this;
				return 0;
			}
		}
		return CWLWndHandler::EventHandler(hWndThis, pe);
	}
};

int OnInsertShowMoreMsg(IMBox *pBox, UINT uMsgID, LPCTSTR lpszText)
{
	if (!pBox->m_lstMsg.empty())
	{
		if (MSGTYPE_SHOW_MORE_MSG_BUTTON == pBox->m_lstMsg.begin()->GetMsgType())
		{
			// �Ѿ����ˣ�����Ҫ�ٲ���
			return 1;
		}
	}

	CIMMsg msg;
	msg.SetMsgType(MSGTYPE_SHOW_MORE_MSG_BUTTON);
	msg.SetHorzLayoutMode(CLH_CENTER);
	msg.SetMsgID(uMsgID);

	{
		// ����OLE�󶨵Ŀؼ�
		COleLoadMoreMsgHandler *pOleLoadMoreMsgHandler = new COleLoadMoreMsgHandler;
		HWLWND hBtnLoadMoreMsg = IUI::CreateWindowEx(pOleLoadMoreMsgHandler, 0,
				IUI_BUTTON, lpszText, WS_VISIBLE,
				0, 0, 0, 0,
				GetHostWnd(pBox->m_pREBox->hwnd), pBox->m_pREBox->hwnd,
				_T("IDC_BTN_LOAD_MORE_MSG"), 0, NULL);
		if (NULL == hBtnLoadMoreMsg)
		{
			return -3;
		}

		PushButton_BindStyle(hBtnLoadMoreMsg, pBox->m_pShowMoreMsgStyle);

		CRichMsgItem item;
		item.m_bOleControl = TRUE;
		item.m_hOleBindWindowless = hBtnLoadMoreMsg;
		item.m_size = CIUISize(200, 30);

		msg.AddMsgItem(&item);
	}

	if (!msg.GetMsgItems()->empty())
	{
		IUI::SendMessage(pBox->m_pREBox->hwnd, IMM_INSERT_MSG, 0, (LPARAM)&msg);
	}

	return 0;
}

int OnInsertLabel(IMBox *pBox, const CLabelMsg *pLabelMsg)
{
	if (NULL == pBox || NULL == pLabelMsg)
	{
		return -1;
	}

	CIMMsg msg;
	msg.SetMsgType(MSGTYPE_LABEL);

	if (NULL != pLabelMsg->m_pBindStyle)
	{
		msg.SetHorzLayoutMode(pLabelMsg->m_pBindStyle->m_eHorLayoutMode);
	}
	msg.SetMsgID(pLabelMsg->m_uMsgID);

	{
		// ����OLE�󶨵Ŀؼ�
		HWLWND hStaLabel = IUI::CreateWindowEx(NULL, 0,
				IUI_LABEL, pLabelMsg->m_lpszText, WS_VISIBLE,
				0, 0, 0, 0,
				GetHostWnd(pBox->m_pREBox->hwnd), pBox->m_pREBox->hwnd,
				_T("IDC_STA_LABEL"), 0, NULL);
		if (NULL == hStaLabel)
		{
			return -3;
		}

		BindStyle(hStaLabel, pLabelMsg->m_pBindStyle);
		SendMessage(hStaLabel, WLM_SETHIDEOLEBORDER, 0, TRUE);

		CRichMsgItem item;
		item.m_bOleControl = TRUE;
		item.m_hOleBindWindowless = hStaLabel;
		item.m_size = pLabelMsg->m_size;

		msg.AddMsgItem(&item);
	}

	if (!msg.GetMsgItems()->empty())
	{
		return IUI::SendMessage(pBox->m_pREBox->hwnd, IMM_INSERT_MSG, pLabelMsg->m_nIndex, (LPARAM)&msg);
	}

	return -1;
}

// Ⱥ��ͷ���ÿ����
enum GROUP_FACE_PART
{
	GFP_FULL = 0,		// ��������ͷ��
	GFP_LEFT = 1,		// Ⱥ����ֻ��������ʱ����ʾ��벿��
	GFP_TOP_LEFT,		// Ⱥ�������������ĸ���ʱ����ʾ���ϲ���
	GFP_TOP_RIGHT,		// Ⱥ�������������ĸ���ʱ����ʾ���ϲ���
	GFP_RIGHT,			// Ⱥ����ֻ��������ʱ����ʾ�Ұ벿��
	GFP_LEFT_BOTTOM,	// Ⱥ�������ĸ���ʱ����ʾ���²���
	GFP_RIGHT_BOTTOM,	// Ⱥ�������ĸ���ʱ����ʾ���²���
	GFP_BOTTOM			// Ⱥ������������ʱ����ʾ�°벿��
};
int _DrawFaceToPart(HDC hDC, LPCRECT lprcTarget, HIUIIMAGE himgFace, GROUP_FACE_PART ePart)
{
	CIUIRect rc = lprcTarget;

	CIUIRect rcPart = rc;
	rcPart.OffsetRect(-rcPart.TopLeft());
	CIUIRect rcSrc;
	rcSrc.right = himgFace->GetWidth();
	rcSrc.bottom = himgFace->GetHeight();

	switch (ePart)
	{
	case GFP_FULL:
		break;
	case GFP_LEFT:
		rcPart.right = rcPart.left + rc.Width() / 2;

		rcSrc.left = himgFace->GetWidth() / 4;
		rcSrc.right = rcSrc.left + himgFace->GetWidth() / 2;
		break;
	case GFP_TOP_LEFT:
		rcPart.right = rcPart.left + rc.Width() / 2;
		rcPart.bottom = rcPart.top + rc.Height() / 2;
		break;
	case GFP_TOP_RIGHT:
		rcPart.left = rcPart.right - rc.Width() / 2 + 1;
		rcPart.bottom = rcPart.top + rc.Height() / 2;
		break;
	case GFP_RIGHT:
		rcPart.left = rcPart.right - rc.Width() / 2 + 1;

		rcSrc.left = himgFace->GetWidth() / 4;
		rcSrc.right = rcSrc.left + himgFace->GetWidth() / 2;
		break;
	case GFP_LEFT_BOTTOM:
		rcPart.top = rcPart.bottom - rc.Height() / 2 + 1;
		rcPart.right = rcPart.left + rc.Width() / 2;
		break;
	case GFP_RIGHT_BOTTOM:
		rcPart.left = rcPart.right - rc.Width() / 2 + 1;
		rcPart.top = rcPart.bottom - rc.Height() / 2 + 1;
		break;
	case GFP_BOTTOM:
		rcPart.top = rcPart.bottom - rc.Height() / 2 + 1;

		rcSrc.top = himgFace->GetHeight() / 4;
		rcSrc.bottom = rcSrc.top + himgFace->GetHeight() / 2;
		break;
	default:
		_ASSERT(FALSE);
		break;
	}

	IUIStretchBlt(hDC, rcPart.left, rcPart.top, rcPart.Width(), rcPart.Height(),
		himgFace, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height());

	return 0;
}

int _DrawFace(
	HDC hDC,
	LPCRECT lprcTarget,
	HIUIIMAGE himgFace)
{
	CIUIRect rc = lprcTarget;

	// ��ͷ�񻭵�һ����ʱDC��
	HDC hdcMem = CreateCompatibleDC(hDC);
	HBITMAP hbmpMem = CreateCompatibleBitmap(hDC, rc.Width(), rc.Height());
	HBITMAP hbmpOld = (HBITMAP)SelectObject(hdcMem, hbmpMem);

	// ������ɫ
	BitBlt(hdcMem, 0, 0, rc.Width(), rc.Height(), hDC, 0, 0, SRCCOPY);

	_DrawFaceToPart(hdcMem, lprcTarget, himgFace, GFP_FULL);
	SelectObject(hdcMem, hbmpOld);

	{
		Gdiplus::Graphics g(hDC);
		g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

		Gdiplus::GraphicsPath gp;
		// �������ִ���ٶȺܿ죬�ŵ�forѭ����ִ��1000�Σ���ŵ�forѭ������ִ��һ�Σ���ʱ���ࡣ
		gp.AddEllipse(rc.left, rc.top, rc.Width() - 1, rc.Height() - 1);
		Gdiplus::Bitmap *pImage = Gdiplus::Bitmap::FromHBITMAP(hbmpMem, NULL);
		Gdiplus::TextureBrush *ptBrush = ::new Gdiplus::TextureBrush(pImage);
		if (NULL != ptBrush)
		{
			// ע�⣬���������FillPath���ſ��Զ�Ŀ��������б�Ե����ݡ������FillRegion��
			// ��ʹ������g.SetSmoothingMode(SmoothingModeAntiAlias)����ԵҲ�������ˡ�
			// ���������ΪRegionֻ���ڲ����򣬶�Path�����Ǳ߽硣
			ptBrush->TranslateTransform(Gdiplus::REAL(rc.left), Gdiplus::REAL(rc.top));
			g.FillPath(ptBrush, &gp);
		}
		if (NULL != ptBrush)
		{
			::delete ptBrush;
			ptBrush = NULL;
		}
		if (NULL != pImage)
		{
			delete pImage;
			pImage = NULL;
		}
	}

	DeleteObject(hbmpMem);
	hbmpMem = NULL;
	DeleteDC(hdcMem);
	hdcMem = NULL;

	return 0;
}

// ��ͷ��, lprcFace�������RichEdit�ؼ��ģ����ͷ�񻭵��������ϣ�Ҫ��������ת��
int OnDrawFace(HWLWND hImCtrl, IMBox *pBox, HDC hMemDCParent, int nMsgIndex, LPCRECT lprcFace)
{
	if (lprcFace == NULL)
	{
		return -1;
	}

	int nMsgCount = (int)pBox->m_lstMsg.size();
	if (nMsgCount <= 0 || nMsgIndex >= nMsgCount)
	{
		return -2;
	}

	IMRichTextBox *pIMCtrl = (IMRichTextBox *)CWLWnd::FromHandle(hImCtrl);

	CIUIRect rcNew = *lprcFace;

	// ���㱾��Ϣ����Ϣ���е�λ�ã������£���DT_TOP��DT_VCENTER��DT_BOTTOM��ʾ��
	UINT uMsgPos = pIMCtrl->GetMsgPosInGroup(nMsgIndex);

	if (uMsgPos == DT_TOP)
	{
		std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
		std::advance(it, nMsgIndex);
		const CIMMsg *pMsg = &(*it);
		rcNew.OffsetRect(0, 5);

		HIUIIMAGE hImage = pMsg->GetFace();
		if (hImage->GetSafeHBITMAP() != NULL)
		{
			// ��������һ���Ի�ͷ��Ļ���
			DRAWITEMSTRUCT dis;
			dis.CtlType = ODT_IMFACE;
			dis.itemID = nMsgIndex;
			dis.itemAction = pIMCtrl->IsCombineMsg();
			dis.itemState = uMsgPos;
			dis.hwndItem = (HWND)hImCtrl;
			dis.hDC = hMemDCParent;
			dis.rcItem = rcNew;
			dis.itemData = (ULONG_PTR)pMsg;

			RoutedEventArgs arg;
			arg.hSender = hImCtrl;
			arg.hOriginalSender = hImCtrl;
			arg.RoutedEvent = WM_DRAWITEM;
			arg.eRoutingStrategy = RS_BUBBLE;
			arg.lParam = (LPARAM)&dis;
			LRESULT lr = RaiseEvent(hImCtrl, &arg);
			if (0 == lr)
			{
				_DrawFace(hMemDCParent, rcNew, hImage);
			}
		}
	}

	return 0;
}

// ������, lprcQiPao�������RichEdit�ؼ��ģ�������ݻ����������ϣ�Ҫ��������ת��
int OnDrawQiPao(HWLWND hImCtrl, IMBox *pBox, HDC hMemDCParent, int nMsgIndex, LPCRECT lprcQiPao)
{
	if (lprcQiPao == NULL)
	{
		return -1;
	}

	int nMsgCount = (int)pBox->m_lstMsg.size();
	if (nMsgCount <= 0 || nMsgIndex >= nMsgCount)
	{
		return -2;
	}

	std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
	std::advance(it, nMsgIndex);
	const CIMMsg *pMsg = &(*it);

	if (pMsg->GetMsgType() == MSGTYPE_SHOW_MORE_MSG_BUTTON
		|| pMsg->GetMsgType() == MSGTYPE_LABEL)
	{
		return 1;
	}

	IMRichTextBox *pIMCtrl = (IMRichTextBox *)CWLWnd::FromHandle(hImCtrl);

	CIUIRect rcNew = *lprcQiPao;

	// ���㱾��Ϣ����Ϣ���е�λ�ã������£���DT_TOP��DT_VCENTER��DT_BOTTOM��ʾ��
	UINT uMsgPos = DT_TOP;
	if (pIMCtrl->IsCombineMsg())
	{
		uMsgPos = pIMCtrl->GetMsgPosInGroup(nMsgIndex);
	}

	// ��������һ���Ի����ݵĻ���
	DRAWITEMSTRUCT dis;
	dis.CtlType = ODT_IMQIPAO;
	dis.itemID = nMsgIndex;
	dis.itemAction = pIMCtrl->IsCombineMsg();
	dis.itemState = uMsgPos;
	dis.hwndItem = (HWND)hImCtrl;
	dis.hDC = hMemDCParent;
	dis.rcItem = rcNew;
	dis.itemData = (ULONG_PTR)pMsg;

	RoutedEventArgs arg;
	arg.hSender = hImCtrl;
	arg.hOriginalSender = hImCtrl;
	arg.RoutedEvent = WM_DRAWITEM;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)&dis;
	RaiseEvent(hImCtrl, &arg);
	if (arg.bHandled)
	{
		return 0;
	}

	if (pIMCtrl->IsCombineMsg())
	{
		rcNew.InflateRect(5, 10, 5, 10);

		CIUIProject *pProject = GetProject(hImCtrl);

		HIUIIMAGE hImg = NULL;
		CIUIRect rc9GridArg;
		if (CLH_RIGHT == pMsg->GetHorzLayoutMode())
		{
			if (uMsgPos == DT_TOP)
			{
				hImg = pBox->m_himgSelfQiPao[0];
				rc9GridArg = pBox->m_rcSelfQiPao9GridArg[0];
			}
			else if (uMsgPos == DT_VCENTER)
			{
				hImg = pBox->m_himgSelfQiPao[1];
				rc9GridArg = pBox->m_rcSelfQiPao9GridArg[1];
			}
			else if (uMsgPos == DT_BOTTOM)
			{
				hImg = pBox->m_himgSelfQiPao[2];
				rc9GridArg = pBox->m_rcSelfQiPao9GridArg[2];
			}
			else
			{
				_ASSERT(FALSE);
			}
		}
		else
		{
			if (uMsgPos == DT_TOP)
			{
				hImg = pBox->m_himgSenderQiPao[0];
				rc9GridArg = pBox->m_rcSenderQiPao9GridArg[0];
			}
			else if (uMsgPos == DT_VCENTER)
			{
				hImg = pBox->m_himgSenderQiPao[1];
				rc9GridArg = pBox->m_rcSenderQiPao9GridArg[1];
			}
			else if (uMsgPos == DT_BOTTOM)
			{
				hImg = pBox->m_himgSenderQiPao[2];
				rc9GridArg = pBox->m_rcSenderQiPao9GridArg[2];
			}
			else
			{
				_ASSERT(FALSE);
			}
		}
		IUINineGridBlt(hMemDCParent, rcNew, hImg, rc9GridArg);
	}

	return 0;
}

// ������, lprcResendButton�������RichEdit�ؼ��ģ������ť�����������ϣ�Ҫ��������ת��
int OnDrawResendButton(
	HWLWND hImCtrl,
	IMBox *pBox,
	HDC hMemDCParent,
	int nMsgIndex,
	LPCRECT lprcResendButton)
{
	if (lprcResendButton == NULL)
	{
		return -1;
	}

	int nMsgCount = (int)pBox->m_lstMsg.size();
	if (nMsgCount <= 0 || nMsgIndex >= nMsgCount)
	{
		return -2;
	}

	IMRichTextBox *pIMCtrl = (IMRichTextBox *)CWLWnd::FromHandle(hImCtrl);

	CIUIRect rcNew = *lprcResendButton;

	std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
	std::advance(it, nMsgIndex);
	const CIMMsg *pMsg = &(*it);

	// ���㱾��Ϣ����Ϣ���е�λ�ã������£���DT_TOP��DT_VCENTER��DT_BOTTOM��ʾ��
	UINT uMsgPos = DT_TOP;
	if (pIMCtrl->IsCombineMsg())
	{
		uMsgPos = pIMCtrl->GetMsgPosInGroup(nMsgIndex);
	}

	// ��������һ���Ի桰���·�����Ϣ����ť�Ļ���
	DRAWITEMSTRUCT dis;
	dis.CtlType = ODT_IMRESENDBUTTON;
	dis.itemID = nMsgIndex;
	dis.itemAction = pIMCtrl->IsCombineMsg();
	dis.itemState = uMsgPos;
	dis.hwndItem = (HWND)hImCtrl;
	dis.hDC = hMemDCParent;
	dis.rcItem = rcNew;
	dis.itemData = (ULONG_PTR)pMsg;

	RoutedEventArgs arg;
	arg.hSender = hImCtrl;
	arg.hOriginalSender = hImCtrl;
	arg.RoutedEvent = WM_DRAWITEM;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)&dis;
	RaiseEvent(hImCtrl, &arg);
	if (arg.bHandled)
	{
		return 0;
	}

	if (pIMCtrl->IsCombineMsg())
	{
		CIUIProject *pProject = GetProject(hImCtrl);

		IUI::ShowWindow(((CIMMsg *)pMsg)->GetResendButton(), SW_SHOW);

		// ����ǧ��Ҫ��TRUE����ΪOnDrawResendButton����Host��WM_PAINT���õ�
		// �����TRUE�������������ѭ����
		IUI::MoveWindow(((CIMMsg *)pMsg)->GetResendButton(), rcNew, FALSE);
	}

	return 0;
}

// ���Ʒ�Rich Text������ͷ�����ݺ͡����·��͡���ť�ȣ�ֻ���ƿ���Ƶ��Χ�ڵ���Ϣ��¼
// �ڻ���ǰ����ͷ����������꣬��������ܺ�׼ȷ�ȡ�
// �����WM_VSCROLLʱ���㣬�ᷢ�ֹ��������У����ݱ����ݹ��������ģ���ʹ�ȵ��û����OnVScroll����
int OnDrawNonRichText(HWLWND hImCtrl, IMBox *pBox, HDC hMemDCParent)
{
	IMRichTextBox *pImCtrl = (IMRichTextBox *)CWLWnd::FromHandle(hImCtrl);

	// �����һ�ɼ���С��0
	int nFirstVisibleMsg = pImCtrl->GetFirstVisibleMsg();
	if (nFirstVisibleMsg < 0)
	{
		return 1;
	}

	CIUIRect rcClient;
	GetClientRect(hImCtrl, rcClient);

	//
	// ����
	//
	int nMsgCount = (int)pBox->m_lstMsg.size();
	int i = nFirstVisibleMsg;
	for (; i < nMsgCount; ++i)
	{
		std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
		std::advance(it, i);
		const CIMMsg *pMsg = &(*it);

		// �¶˳�����ʾ��Χ��ֹͣ����
		CIUIPoint pt = pImCtrl->PosFromChar(pMsg->GetMsgStart());
		if (pt.y >= rcClient.Height())
		{
			break;
		}

		// �õ�ͷ������
		CIUIRect rcFace;
		DoCalFaceRect(pBox, pMsg, rcFace);

		// ����ͷ��
		OnDrawFace(hImCtrl, pBox, hMemDCParent, i, rcFace);

		// ��������
		CIUIRect rcQiPao;
		if (pBox->m_bQiPaoMode)
		{
			DoCalQiPaoRect(pBox, pMsg, rcQiPao);

			OnDrawQiPao(hImCtrl, pBox, hMemDCParent, i, rcQiPao);
		}

		// ���ơ����·��͡���ť
		if (pMsg->IsShowResendButton())
		{
			CIUIRect rcResendButton;
			DoCalResendButtonRect(pBox, pMsg, rcQiPao, rcResendButton);
			OnDrawResendButton(hImCtrl, pBox, hMemDCParent, i, rcResendButton);
		}
	}

	int nLastVisible = i;

	// �Ѳ��ɼ���Χ�ڵ����԰�ť����
	for (int i = 0; i < nFirstVisibleMsg; ++i)
	{
		std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
		std::advance(it, i);
		const CIMMsg *pMsg = &(*it);
		HWLWND hButton = ((CIMMsg *)pMsg)->GetResendButton();
		if (NULL != hButton)
		{
			ShowWindow(hButton, SW_HIDE);
		}
	}
	for (int i = nLastVisible; i < nMsgCount; ++i)
	{
		std::list<CIMMsg>::iterator it = pBox->m_lstMsg.begin();
		std::advance(it, i);
		const CIMMsg *pMsg = &(*it);
		HWLWND hButton = ((CIMMsg *)pMsg)->GetResendButton();
		if (NULL != hButton)
		{
			ShowWindow(hButton, SW_HIDE);
		}
	}

	return 0;
}

int IMRichTextBox_OnPaint(REBox *pREBox, IMBox *pIMBox, HDC hDC, const RECT &rcClip)
{
	pREBox->m_hDC = hDC;

	ITextServices *pTextServices = pREBox->m_pTextHost->GetTextServices();

	LRESULT lr = S_OK;
	if (NULL != pTextServices)
	{
		CIUIRect rc;
		GetClientRect(pREBox->hwnd, rc);

		if (!rc.IsRectEmpty())
		{
			int nWidth = rc.Width();
			int nHeight = rc.Height();

			int nStateIndex = 0;

			HDC hDrawDC = NULL;
			HBITMAP hTempBmp = NULL;
			HBITMAP hOldBmp = NULL;
			void *pBits = NULL;
			BOOL bUpdateLayeredWindow = IsUpdateLayeredWindow(GetHostWnd(pREBox->hwnd));
			//bUpdateLayeredWindow = FALSE;
			if (bUpdateLayeredWindow)
			{
				HDC hTempDC = CreateCompatibleDC(hDC);
				if (hTempDC == NULL)
				{
					_ASSERT(FALSE);
					return -1;
				}

				hTempBmp = Create32BitsHBITMAP(nWidth, nHeight, 32, BI_RGB, &pBits);
				//HBITMAP hTempBmp = CreateCompatibleBitmap(hDC, nWidth, nHeight);
				if (hTempBmp == NULL)
				{
					_ASSERT(FALSE);
					return -2;
				}

				hOldBmp = (HBITMAP)::SelectObject(hTempDC, hTempBmp);

				// ����RichEdit��������
				BitBlt(hTempDC, 0, 0, nWidth, nHeight, hDC, 0, 0, SRCCOPY);

				// ��hTempBmp�����ص�Alphaֵ����Ϊ0xFF
				// ͼ�������Ǵ����ҡ��������ϵġ�
				for (int y = 0; y < nHeight; y++)
				{
					for (int x = 0; x < nWidth; x++)
					{
						byte *pByte = (byte *)(pBits) + (y * nWidth * 4 + x * 4);
						//pByte[0] = 0x00; // B
						//pByte[1] = 0x00; // G
						//pByte[2] = 0xFF; // R
						pByte[3] = 0xFF; // alpha
					}
				}

				hDrawDC = hTempDC;
			}
			else
			{
				hDrawDC = hDC;
			}

			BeforePaint(pREBox->hwnd, hDrawDC);
			RichTextBox_DrawBkColor(pREBox, hDrawDC, rcClip);
			AfterPaintBkColor(pREBox->hwnd, hDrawDC);
			RichTextBox_DrawBkImage(pREBox, hDrawDC, rcClip);
			AfterPaintBkImage(pREBox->hwnd, hDrawDC);
			OnDrawNonRichText(pREBox->hwnd, pIMBox, hDrawDC);
			lr = RichTextBox_DrawText(pREBox, hDrawDC, rcClip);

			if (bUpdateLayeredWindow)
			{
				// ��hTempBmp��alphaΪ0�����ص�Alphaֵ����Ϊ0xFF
				for (int y = 0; SUCCEEDED(lr) && y < nHeight; y++)
				{
					for (int x = 0; x < nWidth; x++)
					{
						byte *pByte = (byte *)(pBits) + (y * nWidth * 4 + x * 4);
						if (pByte[3] == 0x00)
						{
							pByte[3] = 0xFF; // Alpha
						}
					}
				}

				// ���޸��ú��λͼ������Ŀ��DC�ϡ�
				if (SUCCEEDED(lr))
				{
					BitBlt(hDC, 0, 0, nWidth, nHeight, hDrawDC, 0, 0, SRCCOPY);
				}

				// �ͷ�
				::SelectObject(hDrawDC, hOldBmp);
				hOldBmp = NULL;
				::DeleteObject(hTempBmp);
				hTempBmp = NULL;
				DeleteDC(hDrawDC);
				hDrawDC = NULL;
			}
		}
	}

	AfterPaint(pREBox->hwnd, hDC);

	return SUCCEEDED(lr) ? 0 : -1;
}

HRESULT RangeToDataObject(
	HWLWND hRe,
	LONG lStreamFormat,
	IDataObject **ppdo)
{
	if (ppdo)
	{
		CProtectedDataObject *pdo = CProtectedDataObject::Create(hRe, lStreamFormat);
		*ppdo = pdo;
		return NOERROR;
	}

	return E_INVALIDARG;
}

HRESULT StartDrag(HWLWND hIM)
{
	IMBox *pIMBox = (IMBox *)GetProp(hIM, GetProp_IMDATA);
	if (NULL == pIMBox)
	{
		_ASSERT(FALSE);
		return E_FAIL;
	}

	IMRichTextBox *pIMRe = (IMRichTextBox *)CWLWnd::FromHandle(pIMBox->m_pREBox->hwnd);
	if (NULL == pIMRe)
	{
		_ASSERT(FALSE);
		return E_FAIL;
	}

	DWORD			dwEffect = 0;
	HRESULT			hr = S_OK;
	IDataObject 	*pdo = NULL;
	IDropSource 	*pds = NULL;

	do
	{
		if (pIMBox->m_pRichEditOleCallback)
		{
			CHARRANGE chrg;

			// give the callback a chance to give us its own IDataObject
			pIMRe->GetSel(chrg.cpMin, *(&chrg.cpMin + 1));
			hr = pIMBox->m_pRichEditOleCallback->GetClipboardData(&chrg, RECO_COPY, &pdo);
		}
		else
		{
			// we need to build our own data object.
			hr = S_FALSE;
		}

		// If we didn't get an IDataObject from the callback, build our own
		if (hr != NOERROR || pdo == NULL)
		{
			// Don't include trailing EOP
			//prg->AdjustEndEOP(NONEWCHARS);		//  in some selection cases
			// ����ֻ��¼ѡ�еķ�Χ����׼�����ݣ����ͷ����ʱ���Ϸ�Ŀ��ͨ��IDataObject.GetData����������
			hr = RangeToDataObject(hIM, SF_TEXT | SF_RTF, &pdo);
			if (hr != NOERROR)
			{
				break;
			}
		}

		pds = new CProtectedDropSource();
		if (pds == NULL)
		{
			pds->Release();
			hr = E_OUTOFMEMORY;
			break;
		}

		// Set allowable effects
		dwEffect = DROPEFFECT_COPY;
		LONG lStyle = GetStyle(hIM);
		if (!(lStyle & ES_READONLY))
		{
			dwEffect |= DROPEFFECT_MOVE;
		}

		// Let the client decide what it wants.
		if (pIMBox->m_pRichEditOleCallback)
		{
			hr = pIMBox->m_pRichEditOleCallback->GetDragDropEffect(TRUE, 0, &dwEffect);
		}

		if (!FAILED(hr) || hr == E_NOTIMPL)
		{
			// start drag-drop operation
			hr = ::DoDragDrop(pdo, pds, dwEffect, &dwEffect);
		}

		if (SUCCEEDED(hr))
		{
			hr = NOERROR;
		}
	}
	while (false);

	if (NULL != pdo)
	{
		pdo->Release();
	}
	if (NULL != pds)
	{
		pds->Release();
	}

	//if ((_ped->GetEventMask() & ENM_DRAGDROPDONE))
	//{
	//	NMHDR	hdr;

	//	ZeroMemory(&hdr, sizeof(NMHDR));
	//	_ped->TxNotify(EN_DRAGDROPDONE, &hdr);
	//}

	return hr;
}

// ��ΪRichEdit��Drop������DoDragDrop���غ�
// ���DropĿ���Drop effect���ó�DROPEFFECT_MOVE��RichEdit���ѡ�е�����ɾ������ʹReadOnly��
// ���������IM�ؼ����ǲ�����ġ���������IM�ؼ��������Ϣ���Լ�����Drag������
BOOL WantDrag(HWLWND hIM, RoutedEventArgs *pe)
{
	if (pe->RoutedEvent == WM_LBUTTONDOWN)
	{
		IMRichTextBox *pIMRe = (IMRichTextBox *)CWLWnd::FromHandle(hIM);
		if (NULL == pIMRe)
		{
			_ASSERT(FALSE);
			return FALSE;
		}

		// TODO: ����CharFromPos�����������RichEdit�����꣬��IUIʵ�ֵ�������
		// ��ʱ���������Host����
		CIUIPoint pt(pe->lParam);
		IUI::ClientToScreen(hIM, &pt);
		ScreenToClient(GetHostWnd(hIM), &pt);
		int nCp = pIMRe->CharFromPos(pt);

		LONG lCpMin = -1;
		LONG lCpMost = -1;
		pIMRe->GetSel(lCpMin, lCpMost);

		if (lCpMost - lCpMin > 0 && nCp >= lCpMin && nCp <= lCpMost)
		{
			BOOL bRet = CheckForDragBegin(hIM, LOWORD(pe->lParam), HIWORD(pe->lParam));
			if (bRet)
			{
				StartDrag(hIM);
				return TRUE;
			}
		}
	}

	return FALSE;
}

// �ͷ�Ole����
void RelaseObject(IMBox *pIMBox)
{
	RichTextBox *pRichTextBox = (RichTextBox *)CWLWnd::FromHandle(pIMBox->m_pREBox->hwnd);
	CComPtr<IRichEditOle> pRichEditOle = pRichTextBox->GetIRichEditOle();
	_ASSERT(NULL != (IRichEditOle *)pRichEditOle);

	LONG lOleCount = pRichEditOle->GetObjectCount();
	for (LONG i = 0; i < lOleCount; ++i)
	{
		REOBJECT reObj;
		reObj.cbStruct = sizeof(REOBJECT);
		pRichEditOle->GetObject(i, &reObj, REO_GETOBJ_POLEOBJ);

		// OLE��λ��
		int cp = reObj.cp;

		reObj.poleobj->Release();

		// �����OLE���ļ�OLE����ƵOLE�ȣ���Ϊһ��������Ϣ������ϲ����ı���Ϣ
		OleControl *pOleControl = NULL;
		reObj.poleobj->QueryInterface(IID_IUIOleControl, (void **)&pOleControl);
		if (NULL != pOleControl)
		{
			delete pOleControl;
			pOleControl = NULL;
		}
		else
		{
			// ������е�OLE��Ӧ�ö������ǲ���ġ�
			_ASSERT(FALSE);
		}
	}
}

// ͨ��Subclass�滻��RichEdit�Ĵ��ڹ��̣����ԣ�IMRichTextBox_EventHandler
// ������WM_NCCREATE��WM_CREATE��Ϣ��
LRESULT WINAPI IUI::IMRichTextBox_WndProc(HWLWND hWnd, RoutedEventArgs *pe)
{
	fnWLEventHandler fnOldHandler = (fnWLEventHandler)GetProp(hWnd, _T("GetProp_Old_Handler"));

	IMBox *pIMBox = (IMBox *)GetProp(hWnd, GetProp_IMDATA);
	if (pIMBox == NULL)
	{
		pIMBox = new IMBox;
		pIMBox->m_pREBox = (REBox *)GetMember(hWnd);
		SetProp(hWnd, GetProp_IMDATA, pIMBox);
	}

	UINT uMsg = pe->RoutedEvent;
	WPARAM wParam = pe->wParam;
	LPARAM lParam = pe->lParam;

	if (pe->hOriginalSender == hWnd)
	{
		if (RS_BUBBLE == pe->eRoutingStrategy)
		{
			if (pe->RoutedEvent == WM_DESTROY)
			{
				// �ͷ�OLE
				RelaseObject(pIMBox);

				LRESULT lr = CallEventHandler(fnOldHandler, hWnd, pe);

				// RichEdit�Ѿ���REBox�����ˣ�����NULL��
				pIMBox->m_pREBox = NULL;

				return lr;
			}
			else if (pe->RoutedEvent == WM_NCDESTROY)
			{
				pIMBox->Release();
				delete pIMBox;
				pIMBox = NULL;
				SetProp(hWnd, GetProp_IMDATA, NULL);
				return 0;
			}
			else if (pe->RoutedEvent == WM_WINDOWPOSCHANGED)
			{
				// ���ö����ʽ
				IMRichTextBox *pImCtrl = (IMRichTextBox *)CWLWnd::FromHandle(hWnd);

				// TODO: �����ڴ�DC�л�һ�飬����ʹ��EM_POSFROMCHAR�õ�cp�����п����Ǵ����
				// ֮�����о����õĽ��������Ŀǰ���û��Ƶ��ڴ�DCһ�ν����
				CIUIRect rcClient;
				IUI::GetClientRect(hWnd, rcClient);

				if (rcClient != pIMBox->m_pREBox->m_rcOldClient)
				{
					pIMBox->m_pREBox->m_rcOldClient = rcClient;

					REBox *pREBox = (REBox *)GetMember(hWnd);

					HDC hMemDC = CreateCompatibleDC(HDC(wParam));

					// ��Font�õ�, for BoundsChecker
					HFONT hFontOld = (HFONT)::GetCurrentObject(hMemDC, OBJ_FONT);

					HBITMAP hMemBmp = CreateCompatibleBitmap(HDC(wParam),
							rcClient.Width(), rcClient.Height());
					HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hMemBmp);
					IMRichTextBox_OnPaint(pREBox, pIMBox, HDC(hMemDC), *(LPCRECT)lParam);
					SelectObject(hMemDC, hOldBmp);
					DeleteObject(hMemBmp);
					hMemBmp = NULL;

					// ��Fontѡ��
					if (hFontOld != NULL)
					{
						::SelectObject(hMemDC, hFontOld);
					}
					DeleteDC(hMemDC);
					hMemDC = NULL;
				}

				DoSetParaFormat(pIMBox);
			}

			// ���ڰ�RichEdit���ó�Readonly�󣬻�ʹHost��ֹ�������뷨IME
			// ���Բ���������Readonly�ķ�ʽ�����Ǹ��ý�ֹ��Ӧ������Ϣ��ĳЩ��Ϣ
			// ����������ȡ����⻹Ҫ��ֹ�Ϸ�
			BOOL bKeyboardMsg = (uMsg >= WM_KEYFIRST && uMsg <= WM_KEYLAST);
			if (bKeyboardMsg)
			{
				// �����������ҳ��
				if (wParam >= VK_PRIOR && wParam <= VK_DOWN)
				{
					// ���������Home, end, page up, page down����
					return CallEventHandler(fnOldHandler, hWnd, pe);
				}

				// ����Ctrl + Aȫѡ��Ctrl+C, Ctrl+X����
				if ('A' == wParam || 'C' == wParam || 'X' == wParam)
				{
					if ('X' == wParam)
					{
						wParam = 'C';
						pe->wParam = wParam;
					}

					if (GetKeyState(VK_CONTROL) < 0)
					{
						return CallEventHandler(fnOldHandler, hWnd, pe);
					}
				}
			}

			BOOL bIMEMsg = ((uMsg >= WM_IME_STARTCOMPOSITION && uMsg <= WM_IME_KEYLAST)
					|| (uMsg >= WM_IME_SETCONTEXT && uMsg <= WM_IME_CHAR)
					|| WM_IME_REQUEST == uMsg
					|| WM_IME_KEYDOWN == uMsg
					|| WM_IME_KEYUP == uMsg);
			if (bKeyboardMsg || bIMEMsg)
			{
				pe->bHandled = TRUE;
				return 1;
			}
		}

		if (RS_DIRECT == pe->eRoutingStrategy)
		{
			switch (uMsg)
			{
			case UE_SUBCLASSED:
			{
				DCT = GetDoubleClickTime();
				cxDoubleClk = GetSystemMetrics(SM_CXDOUBLECLK);
				cyDoubleClk = GetSystemMetrics(SM_CYDOUBLECLK);

				IMRichTextBox *pImCtrl = (IMRichTextBox *)CWLWnd::FromHandle(hWnd);
				_ASSERT(NULL != pImCtrl);
				pImCtrl->SetDefaultProcHandleIfHitOleCtrl(FALSE);
			}
			break;

			case REM_ISIMCTRL:
				return TRUE;

			case WM_PRINTCLIENT:
			case WM_PRINT:
			case WM_PAINT:
			{
				REBox *pREBox = (REBox *)GetMember(hWnd);
				IMRichTextBox_OnPaint(pREBox, pIMBox, HDC(wParam), *(LPCRECT)lParam);
			}
			return 0;

			case IMM_INSERT_MSG:
				return OnIMInsertMsg(pIMBox, wParam, (const CIMMsg *)lParam);

			case IMM_DELETE_MSG:
				return OnIMDeleteMsg(pIMBox, wParam);

			case IMM_SHOW_RESEND_BUTTON:
				return OnShowResendButton(pIMBox, UINT(wParam), lParam);

			case IMM_IS_RESEND_BUTTON_VISIBLE:
				return OnIsMsgShowResendButton(pIMBox, wParam);

			case IMM_INSERT_SHOW_MORE_MSG:
				return OnInsertShowMoreMsg(pIMBox, wParam, LPCTSTR(lParam));

			case IMM_INSERT_LABEL:
				return OnInsertLabel(pIMBox, (CLabelMsg *)lParam);

			case IMM_SET_QIPAO:
			{
				BOOL bSelf = LOWORD(wParam);
				UINT uDirection = HIWORD(wParam);

				HIUIIMAGE *phImg = NULL;
				if (bSelf)
				{
					if (DT_TOP == uDirection)
					{
						phImg = &pIMBox->m_himgSelfQiPao[0];
					}
					else if (DT_VCENTER == uDirection)
					{
						phImg = &pIMBox->m_himgSelfQiPao[1];
					}
					else if (DT_BOTTOM == uDirection)
					{
						phImg = &pIMBox->m_himgSelfQiPao[2];
					}
				}
				else
				{
					if (DT_TOP == uDirection)
					{
						phImg = &pIMBox->m_himgSenderQiPao[0];
					}
					else if (DT_VCENTER == uDirection)
					{
						phImg = &pIMBox->m_himgSenderQiPao[1];
					}
					else if (DT_BOTTOM == uDirection)
					{
						phImg = &pIMBox->m_himgSenderQiPao[2];
					}
				}
				IUISetControlImage(GetProject(pe->hOriginalSender),	phImg, LPCTSTR(lParam));
			}
			return 0;

			case IMM_SET_QIPAO_9GRIDARG:
			{
				BOOL bSelf = LOWORD(wParam);
				UINT uDirection = HIWORD(wParam);

				LPRECT lpRect = (LPRECT)lParam;
				if (lpRect == 0)
				{
					return -1;
				}

				if (bSelf)
				{
					if (DT_TOP == uDirection)
					{
						pIMBox->m_rcSelfQiPao9GridArg[0] = lpRect;
					}
					else if (DT_VCENTER == uDirection)
					{
						pIMBox->m_rcSelfQiPao9GridArg[1] = lpRect;
					}
					else if (DT_BOTTOM == uDirection)
					{
						pIMBox->m_rcSelfQiPao9GridArg[2] = lpRect;
					}
				}
				else
				{
					if (DT_TOP == uDirection)
					{
						pIMBox->m_rcSenderQiPao9GridArg[0] = lpRect;
					}
					else if (DT_VCENTER == uDirection)
					{
						pIMBox->m_rcSenderQiPao9GridArg[1] = lpRect;
					}
					else if (DT_BOTTOM == uDirection)
					{
						pIMBox->m_rcSenderQiPao9GridArg[2] = lpRect;
					}
				}
			}
			return 0;

			case IMM_GET_QIPAO:
			{
				BOOL bSelf = LOWORD(wParam);
				UINT uDirection = HIWORD(wParam);

				HIUIIMAGE hImg = NULL;
				if (bSelf)
				{
					if (DT_TOP == uDirection)
					{
						hImg = pIMBox->m_himgSelfQiPao[0];
					}
					else if (DT_VCENTER == uDirection)
					{
						hImg = pIMBox->m_himgSelfQiPao[1];
					}
					else if (DT_BOTTOM == uDirection)
					{
						hImg = pIMBox->m_himgSelfQiPao[2];
					}
				}
				else
				{
					if (DT_TOP == uDirection)
					{
						hImg = pIMBox->m_himgSenderQiPao[0];
					}
					else if (DT_VCENTER == uDirection)
					{
						hImg = pIMBox->m_himgSenderQiPao[1];
					}
					else if (DT_BOTTOM == uDirection)
					{
						hImg = pIMBox->m_himgSenderQiPao[2];
					}
				}
				return (LRESULT)(LPCTSTR)hImg->GetSafeImageName();
			}
			return 0;

			case IMM_GET_QIPAO_9GRIDARG:
			{
				BOOL bSelf = LOWORD(wParam);
				UINT uDirection = HIWORD(wParam);

				LPRECT lpRect = (LPRECT)lParam;
				if (lpRect == 0)
				{
					return -1;
				}

				if (bSelf)
				{
					if (DT_TOP == uDirection)
					{
						*lpRect = pIMBox->m_rcSelfQiPao9GridArg[0];
					}
					else if (DT_VCENTER == uDirection)
					{
						*lpRect = pIMBox->m_rcSelfQiPao9GridArg[1];
					}
					else if (DT_BOTTOM == uDirection)
					{
						*lpRect = pIMBox->m_rcSelfQiPao9GridArg[2];
					}
				}
				else
				{
					if (DT_TOP == uDirection)
					{
						*lpRect = pIMBox->m_rcSenderQiPao9GridArg[0];
					}
					else if (DT_VCENTER == uDirection)
					{
						*lpRect = pIMBox->m_rcSenderQiPao9GridArg[1];
					}
					else if (DT_BOTTOM == uDirection)
					{
						*lpRect = pIMBox->m_rcSenderQiPao9GridArg[2];
					}
				}
			}
			return 0;

			case IMM_SET_RESENDBUTTON_MARGIN:
				pIMBox->m_ptResendButtonMargin.x = wParam;
				pIMBox->m_ptResendButtonMargin.y = lParam;
				return 0;

			case IMM_GET_RESENDBUTTON_MARGIN:
				if (0 != wParam)
				{
					*((LONG *)wParam) = pIMBox->m_ptResendButtonMargin.x;
				}
				if (0 != lParam)
				{
					*((LONG *)lParam) = pIMBox->m_ptResendButtonMargin.y;
				}
				return 0;

			case IMM_SET_RESENDBUTTON_SIZE:
				pIMBox->m_sizeResendButton.cx = wParam;
				pIMBox->m_sizeResendButton.cy = lParam;
				return 0;

			case IMM_GET_RESENDBUTTON_SIZE:
				if (0 != wParam)
				{
					*((LONG *)wParam) = pIMBox->m_sizeResendButton.cx;
				}
				if (0 != lParam)
				{
					*((LONG *)lParam) = pIMBox->m_sizeResendButton.cy;
				}
				return 0;

			case IMM_SET_RESENDBUTTON_STYLE:
				pIMBox->m_pResendButtoStyle = ((CButtonProp *)lParam);
				return 0;

			case IMM_GET_RESENDBUTTON_STYLE:
				return (LRESULT)pIMBox->m_pResendButtoStyle;

			case IMM_SET_SHOWMOREMSG_BUTTON_STYLE:
				pIMBox->m_pShowMoreMsgStyle = ((CButtonProp *)lParam);
				return 0;

			case IMM_GET_SHOWMOREMSG_BUTTON_STYLE:
				return (LRESULT)pIMBox->m_pShowMoreMsgStyle;

			// ���ر���һ��
			case EM_SETOLECALLBACK:
				pIMBox->m_pRichEditOleCallback = (IRichEditOleCallback *)lParam;
				break;

			default:
				break;
			}
		}
		else if (RS_TUNNEL == pe->eRoutingStrategy)
		{
			BOOL bWantDrag = WantDrag(hWnd, pe);
			if (bWantDrag)
			{
				pe->bHandled = TRUE;
				return 0;
			}
		}
	}

	return CallEventHandler(fnOldHandler, hWnd, pe);
}
