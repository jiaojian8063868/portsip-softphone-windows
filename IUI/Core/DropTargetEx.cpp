#include "stdafx.h"
#include <ShlGuid.h>
#include "DropTargetEx.h"

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG

#if(_MSC_VER <= 1200) // VC6.0
const GUID FAR CLSID_DragDropHelper = {0x4657278a, 0x411b, 0x11d2, {0x83, 0x9a, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0xd0}};
const GUID IID_IDropTargetHelper = {0x4657278b, 0x411b, 0x11d2, {0x83, 0x9a, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0xd0}};
#endif

CHWNDDropTargetEx::CHWNDDropTargetEx(HWND hWnd)
	: m_hWnd(hWnd)
	, m_piDropHelper(NULL)
	, m_bUseDnDHelper(false)
	, m_dAcceptKeyState(0)
	, m_lRefCount(0)
	, m_hLastDragHitWnd(NULL)
	, m_pDataObject(NULL)
	, m_bDraging(FALSE)
{
	if (SUCCEEDED(CoCreateInstance(CLSID_DragDropHelper, NULL, CLSCTX_INPROC_SERVER,
				IID_IDropTargetHelper, (void **) &m_piDropHelper)))
	{
		m_bUseDnDHelper = true;
	}
}

CHWNDDropTargetEx::~CHWNDDropTargetEx(void)
{
	if (m_piDropHelper)
	{
		m_piDropHelper->Release();
	}

	m_bUseDnDHelper = false;
	m_lRefCount = 0;
}

bool CHWNDDropTargetEx::DragDropRegister(HWND hWnd, DWORD AcceptKeyState)
{
	if (!IsWindow(hWnd))
	{
		_ASSERT(0);
		OutputDebugString(TEXT("hWnd error"));
		return false;
	}

	HRESULT s = ::RegisterDragDrop(hWnd, this);
	m_hWnd = hWnd;

	if (SUCCEEDED(s) || DRAGDROP_E_ALREADYREGISTERED == s)
	{
		m_dAcceptKeyState = AcceptKeyState;
		return true;
	}
	else
	{
		_ASSERT(0);
		//TRACE(TEXT("RegisterDragDrop error:%08x"), s);
		return false;
	}
}
bool CHWNDDropTargetEx::DragDropRevoke(HWND hWnd)
{
	if (!IsWindow(hWnd))
	{
		_ASSERT(0);
		OutputDebugString(TEXT("hWnd error"));
		return false;
	}

	return SUCCEEDED(::RevokeDragDrop(hWnd));
}

HRESULT STDMETHODCALLTYPE CHWNDDropTargetEx::QueryInterface(REFIID riid,
	__out void **ppvObject)
{
	if (!ppvObject)
	{
		return E_INVALIDARG;
	}

	*ppvObject = NULL;

	HRESULT hresult = E_NOINTERFACE;

	if (IsEqualIID(riid, IID_IUnknown))
	{
		*ppvObject = (IUnknown *)this;
		AddRef();
		hresult = NOERROR;
	}
	else if (IsEqualIID(riid, IID_IDropTarget))
	{
		*ppvObject = (IDropTarget *)this;
		AddRef();
		hresult = NOERROR;
	}

	return hresult;
}

ULONG STDMETHODCALLTYPE CHWNDDropTargetEx::AddRef()
{
	return InterlockedIncrement((volatile LONG *)&m_lRefCount);
}

ULONG STDMETHODCALLTYPE CHWNDDropTargetEx::Release()
{
	ULONG lRef = InterlockedDecrement((volatile LONG *)&m_lRefCount);

	if (0 == lRef)
	{
		CHWNDDropTargetEx *p = this;
		delete p;
		p = NULL;
		return 0;
	}

	return lRef;
}

// pt: ��Ļ����
HRESULT STDMETHODCALLTYPE CHWNDDropTargetEx::DragEnter(__in_opt IDataObject *pDataObject,
	DWORD dwKeyState, POINTL pt, __inout DWORD *pdwEffect)
{
	if (pDataObject == NULL || pdwEffect == NULL)
	{
		OutputDebugString(TEXT("pDataObject == NULL || pdwEffect == NULL"));
		return E_INVALIDARG;
	}

	m_bDraging = TRUE;
	m_pDataObject = pDataObject;

	POINT ptHost = { pt.x, pt.y };
	ScreenToClient(m_hWnd, &ptHost);

	DUI_DropInfo info = {0};
	info.dropEffect = *pdwEffect;
	info.dwKeyState = 0;
	info.lpDataObject = pDataObject;
	info.point = ptHost;
	info.hWnd = m_hWnd;

	// ������Ϣ��Ŀ�괰�ڣ�Ŀ�괰�ڷ����Ƿ������Ϸŵ����ݸ���Ȥ�� ��:�Ƿ�����Ϸţ���������Ϸţ�
	// ͨ������pdwEffect������DoDragDrop�����ƶ������ƻ������ӡ�
	LRESULT lr = ::SendMessage(m_hWnd, DDM_OLEDROPTARGET, DDT_DRAGENTER, (LPARAM)&info);
	*pdwEffect = info.dropEffect;
	if (0 != lr)
	{
		return S_OK;
	}

	if (m_bUseDnDHelper && m_piDropHelper)
	{
		m_piDropHelper->DragEnter(m_hWnd, pDataObject, (POINT *)&pt, 0);
	}

	// �����ӿؼ��󣬵����ӿؼ���IDropTarget�ӿڽ��н���
	// WindowFromPoint�������а󶨵�Item�ϵĿؼ�
	HWLWND hDest = IUI::WindowFromPoint(m_hWnd, ptHost);

	if (NULL != hDest && NULL != hDest->m_pDropTarget)
	{
		if (m_hLastDragHitWnd != hDest)
		{
			m_hLastDragHitWnd = hDest;

			POINT ptCtrl;
			ptCtrl.x = pt.x;
			ptCtrl.y = pt.y;
			IUI::ScreenToClient(hDest, &ptCtrl);

			IUITRACE(_T("===[Windowless DragEnter]: hWnd=%08x, Name=%s\r\n"),
				m_hLastDragHitWnd, GetName(m_hLastDragHitWnd));

			LRESULT hr = hDest->m_pDropTarget->DragEnter(pDataObject,
					dwKeyState, *(POINTL *)&ptCtrl, pdwEffect);
			return hr;
		}
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CHWNDDropTargetEx::DragOver(DWORD grfKeyState, POINTL pt,
	__inout DWORD *pdwEffect)
{
	if (pdwEffect == NULL)
	{
		OutputDebugString(TEXT("pdwEffect == NULL"));
		return E_INVALIDARG;
	}

	// TODO: ������Drop����Ȼ���Խ�DragOver���������ӿؼ�����DragEnter
	// ʱ��������ʱͨ��m_bDraging�����ơ�
	if (!m_bDraging)
	{
		return S_OK;
	}

	POINT ptHost = { pt.x, pt.y };
	ScreenToClient(m_hWnd, (LPPOINT)&ptHost);

	DUI_DropInfo info = {0};
	info.dropEffect = *pdwEffect;
	info.dwKeyState = 0;
	info.lpDataObject = NULL;
	info.point = ptHost;
	info.hWnd = m_hWnd;
	LRESULT lr = ::SendMessage(m_hWnd, DDM_OLEDROPTARGET, DDT_DRAGOVER, (LPARAM)&info);
	*pdwEffect = info.dropEffect;
	if (0 != lr)
	{
		return S_OK;
	}

	if (m_bUseDnDHelper && m_piDropHelper)
	{
		m_piDropHelper->DragOver((LPPOINT)&pt, 0);
	}

	// �����ӿؼ��󣬵����ӿؼ���IDropTarget�ӿڽ��н���
	// WindowFromPoint�������а󶨵�Item�ϵĿؼ�
	HWLWND hDest = IUI::WindowFromPoint(m_hWnd, ptHost);

	//
	// ����Ҫģ��DragEnter��DragOver��DragLeave
	//

	// ģ��DragEnter��DragLeave:
	// ���δ�����¿ؼ����������е��¿ؼ���m_pDropTarget�뵱ǰ�Ĳ���ͬһ��
	if (NULL == hDest || (hDest != m_hLastDragHitWnd))
	{
		HRESULT hr = S_OK;

		// �����ǰIDropTarget��Ч��ģ��DragLeave
		if (NULL != m_hLastDragHitWnd && NULL != m_hLastDragHitWnd->m_pDropTarget)
		{
			IUITRACE(_T("===[Windowless DragLeave]: hWnd=%08x, Name=%s\r\n"),
				m_hLastDragHitWnd, GetName(m_hLastDragHitWnd));

			m_hLastDragHitWnd->m_pDropTarget->DragLeave();
			m_hLastDragHitWnd = NULL;
		}

		// ������еĿؼ���Ч������ע����Ϸţ�ģ��DragEnter
		if (NULL != hDest && NULL != hDest->m_pDropTarget)
		{
			m_hLastDragHitWnd = hDest;

			IUITRACE(_T("===[Windowless DragEnter]: hWnd=%08x, Name=%s\r\n"),
				hDest, GetName(hDest));

			hr = hDest->m_pDropTarget->DragEnter(m_pDataObject, grfKeyState, pt, pdwEffect);
		}
	}

	// ģ��DragOver
	if (NULL != hDest)
	{
		if (NULL != hDest->m_pDropTarget)
		{
			if (m_hLastDragHitWnd == hDest)
			{
				static int i = 0;
				i++;
				if (i > 10000)
				{
					i = 0;
				}

				if (i / 10 == 0)
				{
					IUITRACE(_T("===[Windowless DragOver]: hWnd=%08x, Name=%s\r\n"),
						m_hLastDragHitWnd, GetName(m_hLastDragHitWnd));
				}

				return hDest->m_pDropTarget->DragOver(grfKeyState, pt, pdwEffect);
			}
			else
			{
				// ģ���DragEnter�У��Ѿ�������m_hLastDragHitWnd��
				_ASSERT(FALSE);
			}
		}
	}

	*pdwEffect = DROPEFFECT_NONE;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CHWNDDropTargetEx::DragLeave()
{
	m_pDataObject = NULL;

	if (m_bUseDnDHelper && m_piDropHelper)
	{
		m_piDropHelper->DragLeave();
	}

	HRESULT hr = S_OK;
	if (NULL != m_hLastDragHitWnd)
	{
		if (NULL != m_hLastDragHitWnd->m_pDropTarget)
		{
			hr = m_hLastDragHitWnd->m_pDropTarget->DragLeave();
			m_hLastDragHitWnd = NULL;
		}
		else
		{
			_ASSERT(FALSE);
		}
	}

	return hr;
}

HRESULT STDMETHODCALLTYPE CHWNDDropTargetEx::Drop(__in IDataObject *pDataObject,
	DWORD grfKeyState, POINTL pt, __inout DWORD *pdwEffect)
{
	if (pDataObject == NULL || pdwEffect == NULL)
	{
		OutputDebugString(TEXT("pDataObject == NULL || pdwEffect == NULL"));
		return E_INVALIDARG;
	}

	m_bDraging = FALSE;

	POINT ptHost = { pt.x, pt.y };
	ScreenToClient(m_hWnd, &ptHost);

	DUI_DropInfo info = {0};
	info.dropEffect = *pdwEffect;
	info.dwKeyState = 0;
	info.lpDataObject = pDataObject;
	info.point = ptHost;
	info.hWnd = m_hWnd;

	LRESULT lr = ::SendMessage(m_hWnd, DDM_OLEDROPTARGET, DDT_DROP, (LPARAM)&info);
	*pdwEffect = info.dropEffect;
	if (0 != lr)
	{
		return S_OK;
	}

	if (m_bUseDnDHelper && m_piDropHelper)
	{
		m_piDropHelper->Drop(pDataObject, (LPPOINT)&ptHost, *pdwEffect);
	}

	// �����ӿؼ��󣬵����ӿؼ���IDropTarget�ӿڽ��н���
	// WindowFromPoint�������а󶨵�Item�ϵĿؼ�
	HWLWND hDest = IUI::WindowFromPoint(m_hWnd, ptHost);
	HRESULT hr = S_OK;
	if (NULL != hDest)
	{
		if (NULL != hDest->m_pDropTarget)
		{
			if (m_hLastDragHitWnd == hDest)
			{
				IUITRACE(_T("===[Windowless Drop]: hWnd=%08x, Name=%s\r\n"),
					hDest, GetName(hDest));

				hr = hDest->m_pDropTarget->Drop(pDataObject, grfKeyState, pt, pdwEffect);
			}
			else
			{
				_ASSERT(FALSE);
			}
		}
	}

	m_hLastDragHitWnd = NULL;

	return hr;
}