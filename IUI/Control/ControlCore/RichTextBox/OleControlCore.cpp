#include "stdafx.h"

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG

// {F8A25CD9-7C66-4daf-947A-02E0089C6C57}
static const IID IUI::IID_IUIOleControl =
{ 0xf8a25cd9, 0x7c66, 0x4daf, { 0x94, 0x7a, 0x2, 0xe0, 0x8, 0x9c, 0x6c, 0x57 } };

//////////////////////////////////////////////////////////////////////////

CRichMsgItem::CRichMsgItem()
	: m_bOleControl(FALSE)
	, m_hOleBindWindowless(NULL)
	, m_crText(RGB(0, 0, 0))
	, m_lParam(0)
{
}

CRichMsgItem::~CRichMsgItem()
{

}

// OleControl��ΪOLE�ӿؼ���������
// OleControl���Լ��ؽ���༭���еĴ��ڣ����ز�ͬ�Ĵ��ڣ�ʵ�ֲ�ͬ��OLE
// ���磬�ڽ���༭���д���һ�����ڣ������ﴴ��һ��ͼƬ�ؼ��� OleControl����������ں󣬾ͱ��һ��Image Ole
// �ڽ���༭���д���һ�����ڣ����洴��һ����Ƶ�ؼ���OleControl���غ󣬾ͱ��һ����ƵOLE
// OleControlֻ��Ҫ�ṩ���������๦�ܼ��ɣ�
// 1. OleControl�����ӿؼ��Ľ���
// 2. �����ӿؼ���RichEdit����
// 3. �����ӿؼ�
// IUI����������IM����������ͼƬOLE�� ���������ļ�����ƬOLE�����û���OleControl�����Լ�ʵ��
OleControl::OleControl(UINT uID, HWLWND hParent)
{
	IDD = uID;
	m_pOleClientSite = NULL;
	m_lParam = 0;
	m_bHideBorder = FALSE;
	m_hParent = hParent;
	_ASSERT(NULL != m_hParent);
}

OleControl::~OleControl()
{

}

// IUnknown������ӿ�
HRESULT OleControl::QueryInterface(
	/* [in] */ REFIID riid,
	/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
{
	if (this == NULL)
	{
		return S_FALSE;
	}

	// �����thisָ������ת��Ϊ��Ӧ��ָ�롣 ����Ole�޷����뵽RichEdit�С�
	if (riid == IID_IViewObject)
	{
		*ppvObject = (IViewObject *)this;
	}
	else if (riid == IID_IViewObject2)
	{
		*ppvObject = (IViewObject2 *)this;
	}
	else if (riid == IID_IUnknown || riid == IID_IOleObject)
	{
		*ppvObject = (IOleObject *)this;
	}
	else if (riid == IID_IUIOleControl)
	{
		*ppvObject = this;
	}
	else
	{
		return E_NOINTERFACE;
	}

	// �Ӳ��Ӷ��У�����һ��Ole��Ӧһ��C++����
	AddRef();

	return S_OK;
}

ULONG OleControl::AddRef(void)
{
	return S_OK;
}

ULONG OleControl::Release(void)
{
	return S_OK;
}

// ����CRichEditCtrlBase::InsertOle��InsertObject֮�󣬻����SetClientSite
// ���Կ�����Ϊ����m_pOleClientSite��ֵ��Чʱ���ͱ�ʾOLE�ѱ����뵽��RichEdit�С�
HRESULT OleControl::SetClientSite(/* [unique][in] */ IOleClientSite *pClientSite)
{
	m_pOleClientSite = pClientSite;

	if (m_pOleClientSite == NULL)
	{
		return S_FALSE;
	}

	return S_OK;
}

HRESULT OleControl::GetClientSite(/* [out] */IOleClientSite **ppClientSite)
{
	if (ppClientSite == NULL)
	{
		return E_INVALIDARG;
	}

	*ppClientSite = m_pOleClientSite;

	return S_OK;
}

HRESULT OleControl::GetUserClassID(/* [out] */ CLSID *pClsid)
{
	*pClsid = GUID_NULL;

	return S_OK;
}

HRESULT OleControl::SetExtent(/* [in] */ DWORD dwDrawAspect, /* [in] */ SIZEL *psizel)
{
	m_sizeExtent = *psizel;
	return S_OK;
}

HRESULT OleControl::GetExtent(/* [in] */ DWORD dwDrawAspect, /* [out] */ SIZEL *psizel)
{
	if (psizel == NULL)
	{
		return E_INVALIDARG;
	}

	*psizel = m_sizeExtent;

	return S_OK;
}

HRESULT OleControl::Advise(/* [unique][in] */ IAdviseSink *pAdvSink, /* [out] */ DWORD *pdwConnection)
{

	return S_OK;
}

HRESULT OleControl::Unadvise(
	/* [in] */ DWORD dwConnection)
{

	return S_OK;
}

// IViewObject2 ��Ҫʵ�ֵķ���
HRESULT OleControl::SetAdvise(DWORD aspects, DWORD advf, IAdviseSink *pAdvSink)
{
	return S_OK;
}

HRESULT OleControl::GetAdvise(DWORD *pAspects, DWORD *pAdvf, IAdviseSink **ppAdvSink)
{
	return S_OK;
}

HRESULT OleControl::Draw(
	DWORD dwDrawAspect,
	LONG lindex,
	void *pvAspect,
	DVTARGETDEVICE *ptd,
	HDC hdcTargetDev,
	HDC hdcDraw,
	LPCRECTL lprcBounds,
	LPCRECTL lprcWBounds,
	BOOL(STDMETHODCALLTYPE *pfnContinue)(ULONG_PTR dwContinue),
	ULONG_PTR dwContinue)
{
	HDC hDC = hdcDraw;

	// lprcBounds�����꣬�������RichEdit�ؼ��ġ�
	m_rect = (RECT *)lprcBounds;

	// �����Լ�
	if (IDD == -1)
	{
		return S_FALSE;
	}

	// ���ư󶨵Ŀؼ�
	if (NULL != m_hBindWindowless)
	{
		CIUIRect rcOld;
		GetWindowRectToParent(m_hBindWindowless, rcOld);

		if (rcOld != m_rect)
		{
			MoveWindow(m_hBindWindowless, &m_rect, FALSE);
		}

		// �����ӿڡ��ü�����
		POINT ptOrg;
		GetViewportOrgEx(hDC, &ptOrg);

		HRGN hOldRgn = CreateRectRgn(0, 0, 0, 0);
		GetClipRgn(hDC, hOldRgn);

		// ���ư󶨵Ŀؼ�
		DrawControlAndChildren(m_hBindWindowless, hDC, &m_rect);

		// �ָ��ӿڣ�
		// ע�⣺IUIĬ�ϻ��ƻ������Ȼ��Ƹ��ؼ����ȸ��ؼ�������������ٻ����ӿؼ���
		// ��Ȼ�ӿؼ�����ʱ�����޸�HDC���ӿڣ�����ʱ���ؼ��ѳ��׻������ˣ������ӿؼ�
		// �޸�HDC�ӿڣ�Ҳ����Ӱ�츸�ؼ��Ļ��ơ�
		// ������ListView�������ԣ�ListView���ڻ����Լ���ʱ��ͬʱ��Item�󶨵Ŀؼ�
		// �����˻��ƣ����ڻ�����Item�󶨵Ŀؼ���HDC���ӿ��Ѳ���ListView���ӿ��ˣ�
		// ����ʱ��ListView��δ�����꣬�⽫����ListView֮��Ļ���λ��ȫ������
		// ͬ���ü�����Ҳ��Ҫ�ָ�
		SetViewportOrgEx(hDC, ptOrg.x, ptOrg.y, NULL);
		SelectClipRgn(hDC, hOldRgn);
		DeleteObject(hOldRgn);
		hOldRgn = NULL;

	}

	// ͨ����ɫ���ﵽ������OLE�߿��Ч��
	// ֻ��OLE�ؼ�����ѡʱ���Ż���OLE�߿�
	BOOL bHideBorder = m_bHideBorder;
	if (NULL != m_hBindWindowless)
	{
		RoutedEventArgs args;
		args.eRoutingStrategy = RS_BUBBLE;
		args.hOriginalSender = m_hBindWindowless;
		args.hSender = m_hBindWindowless;
		args.RoutedEvent = UE_ISHIDEOLEBORDER;
		RaiseEvent(m_hBindWindowless, &args);
		bHideBorder = args.lResult;
	}

	if (bHideBorder)
	{
		RichTextBox *pRe = (RichTextBox *)CWLWnd::FromHandle(m_hParent);
		_ASSERT(NULL != pRe);
		LONG nSelMinCp = -1;
		LONG nSelMostCp = -1;
		pRe->GetSel(nSelMinCp, nSelMostCp);
		if (nSelMinCp >= 0 && nSelMinCp + 1 == nSelMostCp) // ��ѡ
		{
			REOBJECT reo;
			reo.cbStruct = sizeof(REOBJECT);
			int nOleIndex = FindObjectNearCp(pRe, nSelMinCp, &reo);
			// �Լ�����ѡ
			if (reo.cp == nSelMinCp
				&& reo.poleobj == this
				&& (reo.dwFlags & REO_SELECTED))
			{
				CIUIRect rcLeft = m_rect;
				rcLeft.right = rcLeft.left + 1;
				InvertRect(hDC, rcLeft);
				CIUIRect rcTop = m_rect;
				rcTop.bottom = rcTop.top + 1;
				rcTop.left += 1;
				InvertRect(hDC, rcTop);
				CIUIRect rcRight = m_rect;
				rcRight.left = rcRight.right - 1;
				rcRight.top += 1;
				InvertRect(hDC, rcRight);
				CIUIRect rcBottom = m_rect;
				rcBottom.DeflateRect(1, 1, 1, 0);
				rcBottom.top = rcBottom.bottom - 1;
				InvertRect(hDC, rcBottom);
			}
		}
	}

	return S_OK;
}

HRESULT OleControl::GetExtent(
	DWORD dwDrawAspect,
	LONG lindex,
	DVTARGETDEVICE *ptd,
	LPSIZEL lpsizel)
{
	return S_OK;
}

HWLWND OleControl::SetOleBindWindowless(HWLWND hNewBind)
{
	HWLWND hOld = m_hBindWindowless;

	m_hBindWindowless = hNewBind;
	// �󶨵�OLE��Ŀؼ�����HWLND�ӿؼ���ϵ���Ƴ������뵽HWLWND���ӿؼ���ϵ�С�
	SetBindItemControlParent(m_hBindWindowless, m_hParent, (ULONG_PTR)this);

	IUI::SetProp(m_hBindWindowless, _T("GETPROP_BINDOLE"), this);

	return hOld;
}

HWLWND OleControl::GetOleBindWindowless()
{
	return m_hBindWindowless;
}

LPARAM OleControl::SetUserData(LPARAM lParam)
{
	LPARAM lOld = m_lParam;
	m_lParam = lParam;
	return lOld;
}

LPARAM OleControl::GetUserData() const
{
	return m_lParam;
}

BOOL OleControl::SetHideBorder(BOOL bHide)
{
	BOOL bOld = m_bHideBorder;
	m_bHideBorder = bHide;
	return bOld;
}

BOOL OleControl::IsHideBorder() const
{
	return m_bHideBorder;
}
