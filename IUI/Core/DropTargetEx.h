
#pragma once


typedef struct
{
	__in LPDATAOBJECT lpDataObject;
	__in DWORD dwKeyState;
	__inout DWORD dropEffect;
	__in POINT point;
	__in HWND hWnd;
} DUI_DropInfo;

#define DUI_DROP_MSG                (_T("drop")) ///<�����޴���ק
typedef struct
{
	DUI_DropInfo info;
	DWORD_PTR        dwData;
} DUI_DropInfoMsg;

// ���Ǹ�HWND׼����IDropTarget��HWLWND��Ҫ��
class CHWNDDropTargetEx : public IDropTarget
{
public:
	CHWNDDropTargetEx(HWND hWnd);
	~CHWNDDropTargetEx(void);
public:
	bool DragDropRegister(HWND hWnd, DWORD AcceptKeyState = MK_LBUTTON);
	bool DragDropRevoke(HWND hWnd);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, __out void **ppvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

	HRESULT STDMETHODCALLTYPE DragEnter(__in IDataObject *pDataObj, DWORD grfKeyState,
		POINTL pt, __inout DWORD *pdwEffect);
	HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, __out DWORD *pdwEffect);
	HRESULT STDMETHODCALLTYPE DragLeave();
	HRESULT STDMETHODCALLTYPE Drop(__in IDataObject *pDataObj, DWORD grfKeyState, POINTL pt,
		__inout DWORD *pdwEffect);

private:
	HWND m_hWnd;
	IDropTargetHelper *m_piDropHelper;
	bool    m_bUseDnDHelper;
	DWORD m_dAcceptKeyState;
	ULONG  m_lRefCount;

	// Drag & dropʱ���һ�����еĿؼ�����Ҫ������������Leave�¼���
	// ֻ��m_hLastDragHitWnd->m_pDropTarget��Ч��HWLWND�Żᱻ��¼��
	HWLWND m_hLastDragHitWnd;
	IDataObject *m_pDataObject;
	BOOL m_bDraging;
};