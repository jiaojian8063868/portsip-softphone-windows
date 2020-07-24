// ��HWNDʵ��
//
//  HWND�ı��ʾ���һ�����ڹ���DefWindowProc��ȥ����������Ϣ����������HWND���ݽṹ
//  ��ͬ���͵Ĵ��ڣ��и���˽�����ݽṹ��ͨ��SetWindowLong(HWND, 0, void *)���õ������ϡ�
//  ����ͬ���͵Ĵ��ڣ�Ҳ�и���˽�еĴ��ڹ��̣�˽�еĴ��ڹ��̣�����˽�����ݡ�
//  Windowless���ڵ����ݽṹΪHWLWND��Ĭ�ϴ��ڹ���ΪDefEventHandler
//
//  ��ͬ���Ϳؼ����в�ͬ��˽�д��ڹ��̡� ˽�д��ڹ���ͨ��RegisterWLClass����ע��windowless
//  �ؼ���ʱ����ؼ������󶨡�
//
//  IUI�������¼�·�ɻ��ƣ���ĳ���ؼ�����һ��·���¼����¼��ɰ�ָ����ʽ���ϡ����»�ֱ����
//  �ؼ���Host����֮�������ϵĿؼ����� ���ԣ�Windowless�Ĵ��ڹ��̿��Դ������������·���¼�

#include "stdafx.h"
#include "../../../Core/DropTargetEx.h"

#ifdef _DEBUG
#define new	IUI_DEBUG_NEW
#endif // _DEBUG


#define IDT_TRANSLATE_TRANSFORM_X		10
#define IDT_TRANSLATE_TRANSFORM_Y		11
#define IDT_TRANSLATE_TRANSFORM_POS		12

// ģ��	RegisterClass�� ��ע���������Ϣ����ŵ�ȫ�ֱ���m_gWLClassMap.m_mapWLSuperClasses�С�
class CWLClassMap
{
public:
	CWLClassMap() {}
	~CWLClassMap()
	{
		std::map<CIUIString, CONST WLWNDCLASS *>::iterator it = m_mapWLSuperClasses.begin();
		for (; it != m_mapWLSuperClasses.end(); ++it)
		{
			const WLWNDCLASS *p = it->second;
			delete (WLWNDCLASS *)p;
		}
	}

public:
	std::map<CIUIString, CONST WLWNDCLASS *> m_mapWLSuperClasses;
};

CWLClassMap m_gWLClassMap;


BOOL IUI::RegisterWLClass(CONST WLWNDCLASS *lpWndClass)
{
	if (lpWndClass == NULL)
	{
		return FALSE;
	}

	if (m_gWLClassMap.m_mapWLSuperClasses.find(lpWndClass->lpszClassName) != m_gWLClassMap.m_mapWLSuperClasses.end())
	{
		return TRUE;
	}

	WLWNDCLASS *pNew = new WLWNDCLASS;
	*pNew = *lpWndClass;

	m_gWLClassMap.m_mapWLSuperClasses[lpWndClass->lpszClassName] = pNew;

	return TRUE;
}

// ʧ�ܷ���0���ɹ����ط�0ֵ
int RegisterWindowlessClass(
	LPCTSTR lpszClassName,
	fnWLEventHandler lpfnEventHandler)
{
	if (lpszClassName == NULL || lpfnEventHandler == NULL)
	{
		_ASSERT(FALSE);
		return 0;
	}

	WLWNDCLASS wc = { 0 };
	wc.style = 0;
	wc.lpfnEventHandler = lpfnEventHandler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = IUIGetInstanceHandle();
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = lpszClassName;
	BOOL bRet = RegisterWLClass(&wc);
	if (bRet)
	{
		return 1;
	}

	return 0;
}

int PreRegisterWLClass(LPCTSTR lpszClassName)
{
	if (lpszClassName == NULL)
	{
		return -1;
	}

	// �Ƿ���ע��
	BOOL bAlreadyRegist = (m_gWLClassMap.m_mapWLSuperClasses.find(lpszClassName) != m_gWLClassMap.m_mapWLSuperClasses.end());
	if (bAlreadyRegist)
	{
		return 0;
	}

	// ������������ͣ�������ע��
	CIUIString strClass = lpszClassName;
	if (strClass == IUI_LABEL)
	{
		RegisterWindowlessClass(IUI_LABEL, Label_WndProc);
		return 0;
	}
	else if (strClass == IUI_BUTTON)
	{
		RegisterWindowlessClass(IUI_BUTTON, Button_WndProc);
		return 0;
	}
	else if (strClass == IUI_RICHTEXTBOX)
	{
		RegisterWindowlessClass(IUI_RICHTEXTBOX, RichTextBox_WndProc);
		return 0;
	}
	else if (strClass == IUI_IM)
	{
		RegisterWindowlessClass(IUI_IM, RichTextBox_WndProc);
		return 0;
	}
	else if (strClass == IUI_COMBOBOX)
	{
		RegisterWindowlessClass(IUI_COMBOBOX, ComboBox_WndProc);
		return 0;
	}
	else if (strClass == IUI_COMBOLBOX)
	{
		_ASSERT(FALSE);
		return 0;
	}
	else if (strClass == IUI_REPEATBUTTON)
	{
		_ASSERT(FALSE);
		return 0;
	}
	else if (strClass == IUI_PROGRESSBAR)
	{
		RegisterWindowlessClass(IUI_PROGRESSBAR, ProgressBar_WndProc);
		return 0;
	}
	else if (strClass == IUI_SLIDER)
	{
		RegisterWindowlessClass(IUI_SLIDER, Slider_WndProc);
		return 0;
	}
	else if (strClass == IUI_COLUMNHEADER)
	{
		RegisterWindowlessClass(IUI_COLUMNHEADER, Header_WndProc);
		return 0;
	}
	else if (strClass == IUI_LISTVIEW)
	{
		RegisterWindowlessClass(IUI_LISTVIEW, ListView_WndProc);
		return 0;
	}
	else if (strClass == IUI_TREEVIEW)
	{
		RegisterWindowlessClass(IUI_TREEVIEW, TV_WndProc);
		return 0;
	}
	else if (strClass == IUI_HTMLVIEW)
	{
		RegisterWindowlessClass(IUI_HTMLVIEW, HtmlView_WndProc);
		return 0;
	}
	else if (strClass == IUI_SPLITTERBAR)
	{
		RegisterWindowlessClass(IUI_SPLITTERBAR, SplitterBar_WndProc);
		return 0;
	}
	else if (strClass == IUI_DATETIMEPICKER)
	{
		RegisterWindowlessClass(IUI_DATETIMEPICKER, DateTimePicker_WndProc);
		return 0;
	}
	else if (strClass == IUI_SPINBUTTON)
	{
		RegisterWindowlessClass(IUI_SPINBUTTON, SpinButton_WndProc);
		return 0;
	}
	else if (strClass == IUI_CANVAS)
	{
		RegisterWindowlessClass(IUI_CANVAS, Canvas_WndProc);
		return 0;
	}
	else if (strClass == IUI_TABCONTROL)
	{
		RegisterWindowlessClass(IUI_TABCONTROL, TabControl_WndProc);
		return 0;
	}
	else if (strClass == IUI_DOCKPANEL)
	{
		RegisterWindowlessClass(IUI_DOCKPANEL, DockPanel_WndProc);
		return 0;
	}
	else if (strClass == IUI_STACKPANEL)
	{
		RegisterWindowlessClass(IUI_STACKPANEL, StackPanel_WndProc);
		return 0;
	}
	else if (strClass == IUI_SCROLLBAR)
	{
		RegisterWindowlessClass(IUI_SCROLLBAR, SB_WndProc);
		return 0;
	}
	else if (strClass == IUI_WINDOW)
	{
		_ASSERT(FALSE);
		return 0;
	}
	else
	{
		_ASSERT(FALSE);
	}

	return -1;
}

fnWLEventHandler GetClassEventHandler(LPCTSTR lpszClassName)
{
	if (lpszClassName == NULL)
	{
		return NULL;
	}

	std::map<CIUIString, CONST WLWNDCLASS *>::iterator it = m_gWLClassMap.m_mapWLSuperClasses.find(lpszClassName);
	if (it == m_gWLClassMap.m_mapWLSuperClasses.end())
	{
		return NULL;
	}

	return it->second->lpfnEventHandler;
}

// ��hWnd��HWLWND����ɾ��
BOOL IUI::RemoveHWLWND(HWLWND hWnd)
{
	HWLWND hPrev = hWnd->spwndPrev;
	HWLWND hNext = hWnd->spwndNext;

	if (hPrev == NULL)
	{
		if (NULL != hWnd->spwndParent)
		{
			if (hWnd->m_bInBindChild)
			{
				hWnd->spwndParent->spwndBindItemChild = hNext;
			}
			else
			{
				hWnd->spwndParent->spwndChild = hNext;
			}
		}

		if (hNext != NULL)
		{
			hNext->spwndPrev = NULL;
		}
	}
	else
	{
		hPrev->spwndNext = hNext;
		if (hNext != NULL)
		{
			hNext->spwndPrev = hPrev;
		}
	}

	hWnd->spwndPrev = NULL;
	hWnd->spwndNext = NULL;
	hWnd->spwndParent = NULL;

	return TRUE;
}

BOOL AddHWLWND(HWLWND hWnd, HWLWND hParent, BOOL bAddToBindItemList)
{
	if (hParent == NULL || hWnd == NULL)
	{
		return FALSE;
	}

	// �ȿ�һ��hParent�У��Ƿ��Ѱ���hWnd
	BOOL bExist = FALSE;
	HWLWND hChild = NULL;
	if (bAddToBindItemList)
	{
		hChild = GetWindow(hParent, GW_CHILDBINDITEM);
	}
	else
	{
		hChild = GetWindow(hParent, GW_CHILD);
	}
	HWLWND hLast = NULL;
	for (; hChild != NULL; hChild = GetWindow(hChild, GW_HWNDNEXT))
	{
		if (hChild == hWnd)
		{
			bExist = TRUE;
			break;
		}

		hLast = hChild;
	}

	if (bExist)
	{
		return TRUE;
	}

	hWnd->spwndParent = hParent;
	hWnd->m_bInBindChild = bAddToBindItemList;

	if (hLast == NULL)
	{
		if (bAddToBindItemList)
		{
			hParent->spwndBindItemChild = hWnd;
		}
		else
		{
			hParent->spwndChild = hWnd;
		}
	}
	else
	{
		hLast->spwndNext = hWnd;
		hWnd->spwndPrev = hLast;
	}

	return TRUE;
}

// �ͷ�HWLWND����Ա������ʼ��
int ReleaseHWLWND(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return -1;
	}

	if (-1 == int(hWnd->m_uID))
	{
		hWnd->m_hHostWnd = NULL;
	}

	return 0;
}

// ��ο�xxxCreateWindowEx���߼�
HWLWND IUI::CreateWindowEx(
	CWLWndHandler *pUserHandler,
	DWORD dwExStyle,
	LPCTSTR lpszClassName,
	LPCTSTR lpszCaption,
	DWORD dwStyle,
	int x,
	int y,
	int nWidth,
	int nHeight,
	HWND hParent,
	HWLWND pParent,
	LPCTSTR lpszName,
	HINSTANCE hInstance,
	LPVOID lpParam)
{
	if (lpszClassName == NULL
		|| lpszName == NULL
		|| !::IsWindow(hParent))
	{
		_ASSERT(FALSE);
		return NULL;
	}

	// ���pParentΪNULL��������Ϊ����������ؼ�
	if (pParent == NULL)
	{
		HWLWND hVirtualRoot = (HWLWND)::SendMessage(hParent, WM_GET_INTERNAL_ROOT, 0, 0);
		_ASSERT(hVirtualRoot != NULL);
		pParent = hVirtualRoot;
		_ASSERT(pParent->m_hHostWnd == hParent);
	}

	// TODO: �ж�hParent�Ƿ���IUI Window����

	// ������õĴ�����δע�ᣬ��ע�ᴰ����
	int nRet = PreRegisterWLClass(lpszClassName);
	if (nRet != 0)
	{
		return NULL;
	}

	HWLWND hWnd = new WLWND;
	hWnd->m_strClassName = lpszClassName;
	hWnd->lpfnEventHandler = GetClassEventHandler(lpszClassName);

	// ����CIInitialize
	hWnd->ci.hwnd = hWnd;
	hWnd->ci.style = dwStyle;
	hWnd->ci.dwExStyle = dwExStyle;
	hWnd->ci.uiCodePage = CP_ACP;
	hWnd->ci.bUnicode = 1;

	hWnd->m_strCaption = lpszCaption;
	hWnd->m_rcItem = CIUIRect(x, y, x + nWidth, y + nHeight);
	MakeControlMargin(hParent, pParent, x, y, nWidth, nHeight, hWnd->m_rcControlMargin);
	hWnd->spwndParent = pParent;
	hWnd->m_strName = lpszName;

	//
	// �ӵ�HWLWND����
	//
	AddHWLWND(hWnd, pParent, FALSE);

	// CWLWnd *��HWLWND��
	_IUI_THREAD_STATE *pThreadState = _iuiThreadState.GetData();
	if (pThreadState->m_pWLWndInit != NULL)
	{
		pThreadState->m_pWLWndInit->Attach(hWnd);
		hWnd->ci.pThis = pThreadState->m_pWLWndInit;

		// ����Hook����
		if (pThreadState->m_hHookWLCreate != NULL)
		{
			pThreadState->m_hHookWLCreate(hWnd, NULL);
		}

		pThreadState->m_pWLWndInit = NULL;
	}

	//
	// ����WM_NCCREATE��Ϣʱ�����ڱ����Ѿ�������
	// ������֤��WM_NCCREATE��WM_CREATE�е�LPARAM(CREATESTRUCT *)����
	// ��ֻ���ģ��ⲿ�ڴ����������¼�ʱ����ʹ�޸���LPARAM�е�ֵ��
	// ������Ҳ��Ӧ��ʹ����Щֵ��
	// ���⣬����û���Ӧ��WM_NCCREATE�¼������ҵ���SetStyle�������µķ��
	// �����ڴ���WM_CREATE�¼���LPARAMʱ����ȻҪ���ɵġ�
	// ���⣬��Win32����У�CREATESTRUCT::style��ֵ����GetWindowLong(HWND, GWL_STYLE)
	// �õ���ֵ������һ����ͬ��
	//
	CREATESTRUCT cs;
	cs.lpCreateParams = lpParam;
	cs.hInstance = IUIGetInstanceHandle();
	cs.hMenu = 0;
	cs.hwndParent = hParent;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.y = y;
	cs.x = x;
	cs.style = dwStyle;
	cs.lpszName = lpszName;
	cs.lpszClass = lpszClassName;
	cs.dwExStyle = dwExStyle;

	CREATESTRUCT csBackup = cs;

#ifdef _DEBUG
	HWLWND hWLParent = GetParent(hWnd);
	IUITRACE(_T("Create %s(%08x), its parent is %s(%08x)\n"),
		lpszClassName, hWnd, hWLParent == NULL ? _T("NULL") : GetClassName(hWLParent), hWLParent);
#endif

	// ����Handler�� ͨ��ΪCreateWindowExָ��CWLWndHandler *��������Handler�Ⱥ���
	// ��UE_GET_HANDLER��ʡ�ڴ����Ĵ��룬����Ҳ��������⣬
	// Ҳ����UE_GET_HANDLER����ȷ����Ϊ������ڴ���ʱ��CREATESTRUCT *������ֵ������ȫ��ͬ
	// �⽫�����ⲿ�޷��������ĸ������ڴ�����
	// TODO�����Կ��ǰ�CWLWndHandler *��HWLWND����Key-Value�����浽map�У�
	// ��CWLWndHandler����ʱ�������Զ���HWLWND->m_pUserBindWLWndHandler��NULL��
	// �����ɼ�С��������ķ���������HWLWND->m_pUserBindWLWndHandler�����׳�ΪҰָ�롣
	if (pUserHandler == NULL)
	{
		RoutedEventArgs arg;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.RoutedEvent = UE_GET_HANDLER;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&csBackup;
		LRESULT lr = RaiseEvent(arg.hOriginalSender, &arg);
		if (arg.bHandled)
		{
			hWnd->m_pUserBindWLWndHandler = (CWLWndHandler *)arg.lResult;
		}
	}
	else
	{
		hWnd->m_pUserBindWLWndHandler = pUserHandler;
	}
	if (hWnd->m_pUserBindWLWndHandler != NULL)
	{
		hWnd->m_pUserBindWLWndHandler->m_hBindWLWnd = hWnd;
	}

	{
		RoutedEventArgs arg;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_NCCREATE;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&cs;
		LRESULT lr = RaiseEvent(arg.hOriginalSender, &arg);
		if (lr != 0)
		{
			DestroyWindow(hWnd);

			return NULL;
		}
	}

	cs = csBackup;

	{
		RoutedEventArgs arg;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_CREATE;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&cs;
		RaiseEvent(arg.hOriginalSender, &arg);
	}

	// ���ʹ����ƶ��¼�
	{
		RoutedEventArgs arg;
		arg.RoutedEvent = WM_SIZE;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.lParam = MAKELPARAM(hWnd->m_rcItem.Width(), hWnd->m_rcItem.Height());
		RaiseEvent(arg.hOriginalSender, &arg);
	}

	if (x != 0 && y != 0 && nWidth != 0 && nHeight != 0)
	{
		MoveWindow(hWnd, CIUIRect(x, y, x + nWidth, y + nHeight), FALSE);
	}

	{
		RoutedEventArgs arg;
		arg.RoutedEvent = WM_INIT;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.lParam = (LPARAM)&cs;
		arg.lResult = 0;
		arg.bHandled = FALSE;
		RaiseEvent(arg.hOriginalSender, &arg);
	}

	return hWnd;
}

BOOL IUI::DestroyWindow(HWLWND hWnd)
{
	if (!IsWindow(hWnd))
	{
		return FALSE;
	}

	if (IsWindowVisible(hWnd))
	{
		// �������¼����������洦������¼����ٵ��ÿؼ���ShowWindow(SW_SHOW)��
		// ������ѭ����
		RemoveStyle(hWnd, WS_VISIBLE);
	}

	// ���ٶ�ʱ��
	// ���������Ķ�ʱ������HWND�ϣ����ԣ��������HWLWNDʱ������HWLWND�Ķ�ʱ����
	// �ᵼ�¶�ʱ����Ȼ��Ч������Ӧ��HWLWND��Ч�����⣬�������������ʱ������HWLWNDʱ��
	// �ͻᷢ��������
	std::map<UINT_PTR, HTIMER>::iterator it = hWnd->m_mapTimer.begin();
	for (; it != hWnd->m_mapTimer.end(); it = hWnd->m_mapTimer.begin())
	{
		WLTIMERINFO *pTimerInfo = (WLTIMERINFO *)(it->second);
		_ASSERT(pTimerInfo != NULL);

		IUI::KillTimer(hWnd, pTimerInfo->uIDEvent);
	}

	// Win32��WM_DESTROY��Ϣ���������յ�WM_DESTROY��Ϣʱ���Ӵ��ڣ�����У���Ȼ��Ч
	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = WM_DESTROY;
	arg.eRoutingStrategy = RS_BUBBLE;
	RaiseEvent(hWnd, &arg);

	// �����ӿؼ�
	HWLWND hChild = GetWindow(hWnd, GW_CHILD);
	for (; hChild != NULL; hChild = GetWindow(hWnd, GW_CHILD))
	{
		// �����DestroyWindow���hChild��HWLWND��ϵ��ɾ��������for��ʹ��GW_CHILD
		DestroyWindow(hChild);
	}
	HWLWND hChildBind = GetWindow(hWnd, GW_CHILDBINDITEM);
	for (; hChildBind != NULL; hChildBind = GetWindow(hWnd, GW_CHILDBINDITEM))
	{
		DestroyWindow(hChildBind);
	}

	// Win32��WM_NCDESTROY��Ϣ���������յ�WM_NCDESTROY��Ϣʱ���Ӵ��ڣ�����У��ѱ�����
	{
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_NCDESTROY;
		arg.eRoutingStrategy = RS_BUBBLE;
		RaiseEvent(hWnd, &arg);
	}

	// IUI::DestroyWindowֻ�൱����CWnd��m_hWndΪNULL�������ͷ�CWnd����
	// �ͷ��ڴ�ŵ�Window������������С�
	if (-1 == int(hWnd->m_uID))
	{
		hWnd->m_hHostWnd = NULL;
	}

	_IUI_THREAD_STATE *pThreadState = IUIGetThreadState();
	if (pThreadState != NULL)
	{
		if (pThreadState->m_pWLMouseIn == hWnd)
		{
			pThreadState->m_pWLMouseIn = NULL;
		}

		if (pThreadState->m_pWLCapture == hWnd)
		{
			pThreadState->m_pWLCapture = NULL;
		}
	}

	// TODO: �о��ؼ��Լ�ɾ��ʱ�����ؼ����Ƿ����Լ������ؼ�ʲôʱ��û�е��Լ���
	// ��������δ��룬�ŵ����ʵ�ʱ��
	// ���Լ���HWLWND����ɾ��
	RemoveHWLWND(hWnd);
	delete hWnd;

	return TRUE;
}

BOOL IUI::IsWindow(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return FALSE;
	}

	_ASSERT(NULL != hWnd->spwndParent->spwndChild || NULL != hWnd->spwndParent->spwndBindItemChild);

	if (hWnd->spwndPrev != NULL)
	{
		_ASSERT(hWnd->spwndPrev->spwndNext == hWnd);
	}

	if (hWnd->spwndNext != NULL)
	{
		_ASSERT(hWnd->spwndNext->spwndPrev == hWnd);
	}

	return GetHostWnd(hWnd) == NULL ? FALSE : TRUE;
}

HWLWND IUI::SetBindItemControlParent(
	HWLWND hBindItemControl,
	HWLWND hWndNewParent,
	DWORD_PTR dwBindItemData)
{
	if (NULL == hBindItemControl || NULL == hWndNewParent)
	{
		return NULL;
	}

	HWLWND hOld = hBindItemControl->spwndParent;
	if (NULL != hOld && (int)hOld->m_uID == -1)
	{
		// ������ؼ��Ǹ��ؼ������������ó������ӿؼ��ĺ���
		return NULL;
	}

	// ��ԭ���ؼ����Ƴ�
	RemoveHWLWND(hBindItemControl);

	AddHWLWND(hBindItemControl, hWndNewParent, TRUE);

	hBindItemControl->m_dwBindItemData = dwBindItemData;

	return hOld;
}

ULONG_PTR IUI::GetBindItemControlData(HWLWND hBindItemControl)
{
	if (NULL == hBindItemControl)
	{
		return NULL;
	}

	if (-1 == (int)hBindItemControl->m_uID)
	{
		return NULL;
	}

	return hBindItemControl->m_dwBindItemData;
}

HWLWND IUI::SetParent(HWLWND hWndChild, HWLWND hWndNewParent)
{
	if (hWndChild == NULL || hWndNewParent == NULL)
	{
		return NULL;
	}

	HWLWND hOld = hWndChild->spwndParent;
	if (NULL != hOld && (int)hOld->m_uID == -1)
	{
		// ������ؼ��Ǹ��ؼ������������ó������ӿؼ��ĺ���
		return NULL;
	}

	if (hOld == hWndNewParent)
	{
		return hOld;
	}

	// ��ԭ���ؼ����Ƴ�
	RemoveHWLWND(hWndChild);

	AddHWLWND(hWndChild, hWndNewParent, FALSE);

	// ����hWndChild��hWndNewParent����ͬһ��Host�����ڣ�
	// �������Ǵ�������ؼ�ȡHost���ھ�������ԣ�����Ҫ����Host���ڡ�
	return hOld;
}

HWLWND IUI::GetParent(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return NULL;
	}

	// ���ɿؼ��ĸ��ؼ�ΪNULL
	if (hWnd->spwndParent == NULL || hWnd->spwndParent->m_uID == (UINT)(-1))
	{
		return NULL;
	}

	return hWnd->spwndParent;
}

HWLWND IUI::GetOwner(HWLWND hWnd)
{
	return GetWindow(hWnd, GW_OWNER);
}

int IUI::SetZOrder(HWLWND hWnd, HWLWND hAfter)
{
	if (hWnd == NULL || hAfter == NULL || hAfter == hWnd)
	{
		return 0;
	}

	if (hWnd->spwndParent == NULL)
	{
		return 1;
	}

	if (hAfter == (HWLWND)HWND_TOP)
	{
		// hWnd�Ѿ���Top��(��󴴽�����������)
		if (NULL == hWnd->spwndNext)
		{
			return 0;
		}

		// ���������ڵ�
		HWLWND hOldParentChild = hWnd->m_bInBindChild
			? hWnd->spwndBindItemChild : hWnd->spwndParent->spwndChild;
		_ASSERT(hOldParentChild != NULL);
		HWLWND hOldPrev = hWnd->spwndPrev;
		HWLWND hOldNext = hWnd->spwndNext;
		_ASSERT(hOldNext != NULL);

		if (hOldPrev != NULL)
		{
			hOldPrev->spwndNext = hOldNext;
		}

		// ���hWnd�Ǹ��ؼ���һ�����ӣ��򸸿ؼ���һ������������ָ��
		if (hWnd == hOldParentChild)
		{
			hWnd->spwndPrev = NULL;
			if (hWnd->m_bInBindChild)
			{
				hWnd->spwndParent->spwndBindItemChild = hOldNext;
			}
			else
			{
				hWnd->spwndParent->spwndChild = hOldNext;
			}
		}

		hOldNext->spwndPrev = hOldPrev;

		// �ӵ�ĩβ
		AddHWLWND(hWnd, hWnd->spwndParent, FALSE);

		hWnd->spwndNext = NULL;
	}
	else if (hAfter == (HWLWND)HWND_BOTTOM)
	{
		// hWnd�Ѿ���Bottom�ˡ�
		if (hWnd->spwndPrev == NULL)
		{
			return 0;
		}

		// ���������ڵ�
		HWLWND hOldParentChild = hWnd->m_bInBindChild
			? hWnd->spwndParent->spwndBindItemChild : hWnd->spwndParent->spwndChild;
		_ASSERT(hOldParentChild != NULL);
		HWLWND hOldPrev = hWnd->spwndPrev;
		_ASSERT(hOldPrev != NULL);
		HWLWND hOldNext = hWnd->spwndNext;

		// ����ָ��
		if (hWnd->m_bInBindChild)
		{
			hWnd->spwndParent->spwndBindItemChild = hWnd;
		}
		else
		{
			hWnd->spwndParent->spwndChild = hWnd;
		}

		hWnd->spwndPrev = NULL;
		hWnd->spwndNext = hOldParentChild;

		hOldParentChild->spwndPrev = hWnd;

		hOldPrev->spwndNext = hOldNext;

		if (hOldNext != NULL)
		{
			hOldNext->spwndPrev = hOldPrev;
		}
	}
	else
	{
		// TODO: ����ָ��
		_ASSERT(FALSE);
		RemoveHWLWND(hWnd);
		hAfter->spwndNext = hWnd;
	}

	return 0;
}

CIUIString IUI::GetName(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return _T("");
	}

	return hWnd->m_strName;
}

CIUIString IUI::SetName(HWLWND hWnd, LPCTSTR pstrName)
{
	CIUIString strOld = hWnd->m_strName;
	hWnd->m_strName = pstrName;
	return strOld;
}

int IUI::SetNotify(HWLWND hWnd, BOOL bNotify)
{
	hWnd->m_bNotify = bNotify;

	return 0;
}

BOOL IUI::IsNotify(HWLWND hWnd)
{
	return hWnd->m_bNotify;
}

LONG IUI::SetStyle(HWLWND hWnd, LONG lStyle)
{
	LONG lOldStyle = hWnd->ci.style;

	if (lOldStyle == lStyle)
	{
		return lOldStyle;
	}

	STYLESTRUCT ss;
	ss.styleOld = lOldStyle;
	ss.styleNew = lStyle;

	// WM_STYLECHANGING
	if (hWnd->m_bNotify)
	{
		RoutedEventArgs arg;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_STYLECHANGING;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.wParam = GWL_STYLE;
		arg.lParam = (LPARAM)&ss;
		LRESULT lr = RaiseEvent(hWnd, &arg);
	}

	// WM_STYLECHANGING�¼��У������޸Ĺ��Ĵ��ڷ��
	hWnd->ci.style = ss.styleNew;

	// WM_STYLECHANGED
	if (hWnd->m_bNotify)
	{
		RoutedEventArgs arg;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_STYLECHANGED;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.wParam = GWL_STYLE;
		arg.lParam = (LPARAM)&ss;
		LRESULT lr = RaiseEvent(hWnd, &arg);
	}

	return lOldStyle;
}

LONG IUI::GetStyle(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return 0;
	}

	return hWnd->ci.style;
}

LONG IUI::AddStyle(HWLWND hWnd, LONG lAdd)
{
	LONG lOld = hWnd->ci.style;

	LONG lNew = (lOld | lAdd);

	SetStyle(hWnd, lNew);

	return lOld;
}

LONG IUI::RemoveStyle(HWLWND hWnd, LONG lRemove)
{
	LONG lOld = hWnd->ci.style;

	LONG lNew = lOld;
	lNew &= ~lRemove;

	SetStyle(hWnd, lNew);

	return lOld;
}

LONG IUI::SetExStyle(HWLWND hWnd, LONG lExStyle)
{
	LONG lOld = hWnd->ci.dwExStyle;

	if (lOld == lExStyle)
	{
		return lOld;
	}

	STYLESTRUCT ss;
	ss.styleOld = lOld;
	ss.styleNew = lExStyle;

	// WM_STYLECHANGING
	if (hWnd->m_bNotify)
	{
		RoutedEventArgs arg;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_STYLECHANGING;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.wParam = GWL_EXSTYLE;
		arg.lParam = (LPARAM)&ss;
		LRESULT lr = RaiseEvent(hWnd, &arg);
	}

	// WM_STYLECHANGING�¼��У������޸Ĺ��Ĵ�����չ���
	hWnd->ci.dwExStyle = ss.styleNew;

	// WM_STYLECHANGED
	if (hWnd->m_bNotify)
	{
		RoutedEventArgs arg;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_STYLECHANGED;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.wParam = GWL_EXSTYLE;
		arg.lParam = (LPARAM)&ss;
		LRESULT lr = RaiseEvent(hWnd, &arg);
	}

	return lOld;
}

LONG IUI::GetExStyle(HWLWND hWnd)
{
	return hWnd->ci.dwExStyle;
}

LONG IUI::AddExStyle(HWLWND hWnd, LONG lAdd)
{
	LONG lOld = hWnd->ci.dwExStyle;

	LONG lNew = (lOld | lAdd);

	SetExStyle(hWnd, lNew);

	Invalidate(hWnd);

	return lOld;
}

LONG IUI::RemoveExStyle(HWLWND hWnd, LONG lRemove)
{
	LONG lOld = hWnd->ci.dwExStyle;

	LONG lNew = lOld;
	lNew &= ~lRemove;

	SetExStyle(hWnd, lNew);

	Invalidate(hWnd);

	return lOld;
}

HWND IUI::GetHostWnd(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return NULL;
	}

	// ��������ؼ�ȡHost���ھ��
	HWND hRet = NULL;
	HWLWND hParent = hWnd;
	while (NULL != hParent)
	{
		if (-1 == int(hParent->m_uID))
		{
			hRet = hParent->m_hHostWnd;
			break;
		}

		hParent = hParent->spwndParent;
	}

	return hRet;
}

CIUIString IUI::GetClassName(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return _T("");
	}

	return hWnd->m_strClassName;
}

int IUI::GetClassName(HWLWND hWnd, LPTSTR lpClassName, int nMaxCount)
{
	if (hWnd == NULL)
	{
		return 0;
	}

	int nTextLen = hWnd->m_strClassName.GetLength();
	StringCchCopy(lpClassName, nMaxCount, hWnd->m_strClassName);

	if (nTextLen >= nMaxCount)
	{
		return nMaxCount - 1;
	}
	else
	{
		return nTextLen;
	}
}

int IUI::SetDlgCtrlID(HWLWND hWnd, int nID)
{
	hWnd->m_uID = nID;

	return 0;
}

int IUI::GetDlgCtrlID(HWLWND hWnd)
{
	return hWnd->m_uID;
}

CIUIProject *IUI::GetProject(HWLWND hWnd)
{
	_ASSERT(GetHostWnd(hWnd) != NULL);
	return (CIUIProject *)::SendMessage(GetHostWnd(hWnd), WM_GET_PROJECT, 0, 0);
}

// xxxSetCapture
// ע�⣺Win32�У�Disabled���ڻ򲻿ɼ�����Ҳ���Բ������
// ����֤�������ִ��ڲ�������Ҳ������Ӧ�����Ϣ�ˡ�
HWLWND IUI::SetCapture(HWLWND hWnd)
{
	_IUI_THREAD_STATE *pThreadState = IUIGetThreadState();
	HWLWND hOld = pThreadState->m_pWLCapture;

	// xxxCapture
	{
		if (hWnd == NULL && hOld != NULL)
		{
			//zzzSetFMouseMoved();
		}

		// send  WM_CAPTURECHANGED.
		if (hOld != NULL)
		{
			SendMessage(hOld, WM_CAPTURECHANGED, FALSE, LPARAM(hWnd));
		}

		RoutedEventArgs arg;
		arg.hSender = hWnd;
		arg.hOriginalSender = hWnd;
		arg.RoutedEvent = UE_SETCAPTURE;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.wParam = (WPARAM)hWnd;
		arg.lParam = (LPARAM)hOld;
		LRESULT lr = RaiseEvent(hWnd, &arg);
		// ���׽�ֹ����Capture
		if (lr != 0)
		{
			return hOld;
		}

		HWND hOld = ::GetCapture();
		HWND hHost = GetHostWnd(hWnd);
		if (hOld != hHost)
		{
			::SetCapture(hHost);
		}

		pThreadState->m_pWLCapture = hWnd;
	}

	return hOld;
}

HWLWND IUI::GetCapture(HWLWND hWnd)
{
	_IUI_THREAD_STATE *pThreadState = IUIGetThreadState();
	return pThreadState->m_pWLCapture;
}

BOOL IUI::ReleaseCapture(HWLWND hWnd)
{
	_IUI_THREAD_STATE *pThreadState = IUIGetThreadState();
	HWLWND hOld = pThreadState->m_pWLCapture;
	pThreadState->m_pWLCapture = NULL;

	RoutedEventArgs arg;
	arg.hSender = hOld;
	arg.hOriginalSender = hOld;
	arg.RoutedEvent = WM_CAPTURECHANGING;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)GetCapture(hWnd);
	LRESULT lr = RaiseEvent(hOld, &arg);
	if (!arg.bHandled && lr == 0)
	{
		// ComboBox�����б��У�������Զ���Ĺ��������ڹ�����ֹͣ������
		// �����IUI::ReleaseCapture�ͷ���꣬����ᵼ�°������б�����겶���ͷŵ�
		// ͨ������WM_CAPTURECHANGING���ɽ�ֹ�ͷŵ������б�����겶��
		::ReleaseCapture();
	}

	if (hOld != NULL)
	{
		RoutedEventArgs arg;
		arg.hSender = hOld;
		arg.hOriginalSender = hOld;
		arg.RoutedEvent = WM_CAPTURECHANGED;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)GetCapture(hWnd);// TODO, GetCapture��Ӧ�ô�HWLWND����
		LRESULT lr = RaiseEvent(hOld, &arg);
	}

	return TRUE;
}

HWLWND IUI::GetTopLevelWindow(HWLWND hWnd)
{
	_ASSERT(IsWindow(hWnd));

	HWLWND hWndParent = hWnd;
	HWLWND hWndTmp = hWnd;

	do
	{
		hWndParent = hWndTmp;
		hWndTmp = GetParent(hWndParent);
	}
	while (hWndTmp != NULL && hWndTmp->m_uID != UINT(-1));

	return hWndParent;
}

int IUI::GetWindowTextLength(HWLWND hWnd)
{
	_ASSERT(IsWindow(hWnd));
	return SendMessage(hWnd, WM_GETTEXTLENGTH, 0, 0);
}

CIUIString IUI::GetWindowText(HWLWND hWnd)
{
	if (!IsWindow(hWnd))
	{
		return _T("");
	}

	int nLen = GetWindowTextLength(hWnd);
	nLen = max(4, nLen + 1);
	TCHAR *p = new TCHAR[nLen];
	p[0] = 0;

	// ����ΪANSI������RichEdit����WM_GETTEXTʱ������RichEdit�ڲ�ʹ��Unicode��
	// �ڲ����ܻ�Ѵ���ĳ��ȳ���2�ټ�ȥ1��Ϊ��ʹ�������0���������С����Ϊ4.
	// �������ͷ�p��ʱ�򣬿��ܻ�������Դ���
	SendMessage(hWnd, WM_GETTEXT, nLen, (LPARAM)p);

	CIUIString rString = p;
	delete []p;
	p = NULL;
	return rString;
}

int IUI::GetWindowText(HWLWND hWnd, LPTSTR lpString, int nMaxCount)
{
	if (!IsWindow(hWnd))
	{
		return 0;
	}

	int nLen = GetWindowTextLength(hWnd);

	nLen = max(4, nLen + 1);
	TCHAR *p = new TCHAR[nLen];
	p[0] = 0;

	// ����ΪANSI������RichEdit����WM_GETTEXTʱ������RichEdit�ڲ�ʹ��Unicode��
	// �ڲ����ܻ�Ѵ���ĳ��ȳ���2�ټ�ȥ1��Ϊ��ʹ�������0���������С����Ϊ4.
	// �������ͷ�p��ʱ�򣬿��ܻ�������Դ���
	SendMessage(hWnd, WM_GETTEXT, nLen, (LPARAM)p);

	size_t nTextLen = 0;
	StringCchLength(p, nLen, &nTextLen);

	StringCchCopy(lpString, nMaxCount, p);
	delete[]p;
	p = NULL;

	if (nTextLen >= (size_t)nMaxCount)
	{
		return nMaxCount - 1;
	}
	else
	{
		return nTextLen;
	}
}

BOOL IUI::SetWindowText(HWLWND hWnd, LPCTSTR pstrText)
{
	if (pstrText == NULL)
	{
		return FALSE;
	}

	return SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)pstrText);
}

BOOL IUI::SetResText(HWLWND hWnd, HINSTANCE hRes, UINT uID)
{
	CIUIString strText;
	BOOL bRet = strText.LoadString(uID);

	if (!bRet)
	{
		return FALSE;
	}

	SetWindowText(hWnd, strText);

	return TRUE;
}

#if (_MSC_VER > 1200)	// VC6.0
BOOL IUI::SetXResText(HWLWND hWnd, HXSRESOURCE hXRes, LPCTSTR lpszSectionID, LPCTSTR lpszStringID)
{
	LPCWSTR lpszString = CParseLanguageFile::LoadXMLString(hXRes, lpszSectionID, lpszStringID);

	if (lpszString != NULL)
	{
		USES_CONVERSION;
		IUI::SetWindowText(hWnd, W2T((LPWSTR)lpszString));
	}

	return TRUE;
}
#endif // #if (_MSC_VER > 1200)	// VC6.0

RECT IUI::GetTextPadding(HWLWND hWnd)
{
	return hWnd->m_rcTextPadding;
}

int IUI::SetTextPadding(HWLWND hWnd, RECT rc)
{
	hWnd->m_rcTextPadding = rc;

	Invalidate(hWnd);

	return 0;
}

int IUI::SetTextColor(HWLWND hWnd, COLORREF crN, COLORREF crD)
{
	_ASSERT(IsWindow(hWnd));

	SendMessage(hWnd, WLM_SET_TEXT_COLOR, MAKEWPARAM(0, CONTROL_STATE_NORMAL), crN);
	SendMessage(hWnd, WLM_SET_TEXT_COLOR, MAKEWPARAM(0, CONTROL_STATE_DISABLED), crD);

	Invalidate(hWnd);

	return 0;
}

int IUI::GetTextColor(HWLWND hWnd, COLORREF *pcrN, COLORREF *pcrD)
{
	_ASSERT(IsWindow(hWnd));

	if (pcrN != NULL)
	{
		*pcrN = SendMessage(hWnd, WLM_GET_TEXT_COLOR, MAKEWPARAM(0, CONTROL_STATE_NORMAL), 0);
	}
	if (pcrD != NULL)
	{
		*pcrD = SendMessage(hWnd, WLM_GET_TEXT_COLOR, MAKEWPARAM(0, CONTROL_STATE_DISABLED), 0);
	}

	return 0;
}

BOOL IUI::SetDrawBkColor(HWLWND hWnd, BOOL bDraw)
{
	BOOL bOld = hWnd->m_bDrawBkColor;

	hWnd->m_bDrawBkColor = bDraw;

	return bOld;
}

BOOL IUI::IsDrawBkColor(HWLWND hWnd)
{
	return hWnd->m_bDrawBkColor;
}

int IUI::SetBkColor(HWLWND hWnd, COLORREF crBkN, COLORREF crBkD)
{
	_ASSERT(IsWindow(hWnd));

	SendMessage(hWnd, WLM_SET_BK_COLOR, MAKEWPARAM(0, CONTROL_STATE_NORMAL), crBkN);
	SendMessage(hWnd, WLM_SET_BK_COLOR, MAKEWPARAM(0, CONTROL_STATE_DISABLED), crBkD);

	Invalidate(hWnd);

	return 0;
}

int IUI::GetBkColor(HWLWND hWnd, COLORREF *pcrBkN, COLORREF *pcrBkD)
{
	_ASSERT(IsWindow(hWnd));

	if (pcrBkN != NULL)
	{
		*pcrBkN = SendMessage(hWnd, WLM_GET_BK_COLOR, MAKEWPARAM(0, CONTROL_STATE_NORMAL), 0);
	}
	if (pcrBkD != NULL)
	{
		*pcrBkD = SendMessage(hWnd, WLM_GET_BK_COLOR, MAKEWPARAM(0, CONTROL_STATE_DISABLED), 0);
	}

	return 0;
}

BOOL IUI::CombineBkImage(HWLWND hWnd, BOOL bCombine)
{
	BOOL bOld = hWnd->ci.m_bCombineBkImage;
	hWnd->ci.m_bCombineBkImage = bCombine;
	return bOld;
}

BOOL IUI::IsCombineBkImage(HWLWND hWnd)
{
	return hWnd->ci.m_bCombineBkImage;
}

int IUI::SetCombineBkImage(HWLWND hWnd, LPCTSTR lpszImage)
{
	// TODO: Ӧ�÷�WLM_SET_BK_IMAGE��Ϣ�����ҿؼ���Ӧ����Ӧ�����Ϣ
	return IUISetControlImage(GetProject(hWnd), &hWnd->ci.m_himgCombineBk, lpszImage);
}

int IUI::GetCombineBkImage(HWLWND hWnd, CIUIString *pstrCombineImage)
{
	if (pstrCombineImage == NULL)
	{
		return -1;
	}

	*pstrCombineImage = hWnd->ci.m_himgCombineBk->GetSafeImageName();

	return 0;
}

int IUI::SetBkImage(HWLWND hWnd, BOOL bChecked, CONTROL_STATE eControlState, LPCTSTR lpszImage)
{
	return SendMessage(hWnd, WLM_SET_BK_IMAGE,
			MAKEWPARAM(bChecked ? BST_CHECKED : BST_UNCHECKED, eControlState), LPARAM(lpszImage));
}

int IUI::GetBkImage(HWLWND hWnd, BOOL bChecked, CONTROL_STATE eControlState, CIUIString *pstrImage)
{
	if (pstrImage == NULL)
	{
		return -1;
	}

	*pstrImage = (LPCTSTR)SendMessage(hWnd, WLM_GET_BK_IMAGE,
			MAKEWPARAM(bChecked ? BST_CHECKED : BST_UNCHECKED, eControlState), 0);

	return 0;
}

int IUI::SetBkImageResizeMode(HWLWND hWnd, IMAGE_RESIZE_MODE eImageResizeMode)
{
	if (!IsWindow(hWnd))
	{
		return -1;
	}

	hWnd->ci.m_eBkImageResizeMode = eImageResizeMode;
	return 0;
}

IMAGE_RESIZE_MODE IUI::GetBkImageResizeMode(HWLWND hWnd)
{
	if (!IsWindow(hWnd))
	{
		return IRM_UNKNOWN;
	}

	return hWnd->ci.m_eBkImageResizeMode;
}

int IUI::SetBkImage9GridResizeParam(HWLWND hWnd, LPCRECT lprcParam)
{
	if (!IsWindow(hWnd))
	{
		return -1;
	}

	if (lprcParam == NULL)
	{
		return -2;
	}

	hWnd->ci.m_rcBkImage9GridResizeArg = lprcParam;
	return 0;
}

int IUI::GetBkImage9GridResizeParam(HWLWND hWnd, LPRECT lprcParam)
{
	if (!IsWindow(hWnd))
	{
		return -1;
	}

	if (lprcParam == NULL)
	{
		return -2;
	}

	*lprcParam = hWnd->ci.m_rcBkImage9GridResizeArg;
	return 0;
}

BOOL IUI::CombineFgImage(HWLWND hWnd, BOOL bCombine)
{
	return SendMessage(hWnd, WLM_COMBINE_FG_IMAGE, 0, bCombine);
}

BOOL IUI::IsCombineFgImage(HWLWND hWnd)
{
	return SendMessage(hWnd, WLM_IS_COMBINE_FG_IMAGE, 0, 0);
}

int IUI::SetCombineFgImage(HWLWND hWnd, LPCTSTR lpszImage)
{
	return SendMessage(hWnd, WLM_SET_FG_IMAGE,
			MAKEWPARAM(BST_UNCHECKED, CONTROL_STATE_COMBINE), LPARAM(lpszImage));
}

int IUI::GetCombineFgImage(HWLWND hWnd, CIUIString *pstrCombineImage)
{
	if (pstrCombineImage == NULL)
	{
		return -1;
	}

	*pstrCombineImage = (LPCTSTR)SendMessage(hWnd, WLM_GET_FG_IMAGE,
			MAKEWPARAM(BST_UNCHECKED, CONTROL_STATE_COMBINE), 0);

	return 0;
}

int IUI::SetFgImage(HWLWND hWnd, BOOL bChecked, CONTROL_STATE eControlState, LPCTSTR lpszImage)
{
	return SendMessage(hWnd, WLM_SET_FG_IMAGE,
			MAKEWPARAM(bChecked ? BST_CHECKED : BST_UNCHECKED, eControlState), LPARAM(lpszImage));
}

int IUI::GetFgImage(HWLWND hWnd, BOOL bChecked, CONTROL_STATE eControlState, CIUIString *pstrImage)
{
	if (pstrImage == NULL)
	{
		return -1;
	}

	*pstrImage = (LPCTSTR)SendMessage(hWnd, WLM_GET_FG_IMAGE,
			MAKEWPARAM(bChecked ? BST_CHECKED : BST_UNCHECKED, eControlState), 0);

	return 0;
}

BOOL IUI::SetDrawBorderColor(HWLWND hWnd, BOOL bDraw)
{
	BOOL bOld = hWnd->m_bDrawBorderColor;
	hWnd->m_bDrawBorderColor = bDraw;

	Invalidate(hWnd);

	return bOld;
}

BOOL IUI::IsDrawBorderColor(HWLWND hWnd)
{
	return hWnd->m_bDrawBorderColor;
}

int IUI::SetBorderColor(HWLWND hWnd, COLORREF crN, COLORREF crD)
{
	_ASSERT(IsWindow(hWnd));

	SendMessage(hWnd, WLM_SET_BORDER_COLOR, MAKEWPARAM(0, CONTROL_STATE_NORMAL), crN);
	SendMessage(hWnd, WLM_SET_BORDER_COLOR, MAKEWPARAM(0, CONTROL_STATE_DISABLED), crD);

	Invalidate(hWnd);

	return 0;
}

int IUI::GetBorderColor(HWLWND hWnd, COLORREF *pcrN, COLORREF *pcrD)
{
	_ASSERT(IsWindow(hWnd));

	if (pcrN != NULL)
	{
		*pcrN = SendMessage(hWnd, WLM_GET_BORDER_COLOR, MAKEWPARAM(0, CONTROL_STATE_NORMAL), 0);
	}
	if (pcrD != NULL)
	{
		*pcrD = SendMessage(hWnd, WLM_GET_BORDER_COLOR, MAKEWPARAM(0, CONTROL_STATE_DISABLED), 0);
	}

	return 0;
}

DWORD IUI::GetFocusBorderColor(HWLWND hWnd)
{
	return hWnd->m_dwFocusBorderColor;
}

void IUI::SetFocusBorderColor(HWLWND hWnd, DWORD dwBorderColor)
{
	if (hWnd->m_dwFocusBorderColor == dwBorderColor)
	{
		return;
	}

	hWnd->m_dwFocusBorderColor = dwBorderColor;
	Invalidate(hWnd);
}

int IUI::SetBorderRect(HWLWND hWnd, const RECT &rcBorder)
{
	hWnd->m_rcBorder = rcBorder;
	return 0;
}

CIUIRect IUI::GetBorderRect(HWLWND hWnd)
{
	return hWnd->m_rcBorder;
}

void IUI::SetBorderRound(HWLWND hWnd, SIZE cxyRound)
{
	hWnd->m_cxyBorderRound = cxyRound;
	Invalidate(hWnd);
}

SIZE IUI::GetBorderRound(HWLWND hWnd)
{
	return hWnd->m_cxyBorderRound;
}

int IUI::SetWindowRgn(HWLWND hWnd, HRGN hRgn, BOOL bRedraw)
{
	WINDOWPOS wp;
	wp.cx = hWnd->m_rcItem.Width();
	wp.cy = hWnd->m_rcItem.Height();
	wp.flags = SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER;
	wp.hwnd = (HWND)hWnd;
	wp.hwndInsertAfter = NULL;
	wp.x = hWnd->m_rcItem.left;
	wp.y = hWnd->m_rcItem.top;

	{
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_WINDOWPOSCHANGING;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&wp;
		RaiseEvent(hWnd, &arg);
	}

	hWnd->m_hrgnClip = hRgn;

	{
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_WINDOWPOSCHANGED;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&wp;
		RaiseEvent(hWnd, &arg);
	}

	if (bRedraw)
	{
		Invalidate(hWnd);
	}

	return 0;
}

int IUI::GetWindowRgn(HWLWND hWnd, HRGN hRgn)
{
	if (NULL == hWnd)
	{
		return -1;
	}

	hRgn = hWnd->m_hrgnClip;

	return 0;
}

int IUI::RelayoutChild(HWLWND hWnd)
{
	CanvasLayoutCtrl(hWnd);

	return 0;
}

void IUI::EnableDPI(HWLWND hWnd, BOOL bEnable)
{
	if (NULL == hWnd)
	{
		return;
	}

	hWnd->m_bEnableDPI = bEnable;
}

BOOL IUI::IsDPIEnabled(HWLWND hWnd)
{
	if (NULL == hWnd)
	{
		return FALSE;
	}

	return hWnd->m_bEnableDPI;
}

const CIUIRect &IUI::GetWindowRectToParent(HWLWND hWnd)
{
	if (NULL == hWnd)
	{
		_ASSERT(FALSE);
	}

	return hWnd->m_rcItem;
}

int IUI::GetWindowRectToParent(HWLWND hWnd, LPRECT lprc)
{
	if (NULL == hWnd || NULL == lprc)
	{
		return -1;
	}

	*lprc = hWnd->m_rcItem;

	return 0;
}

int IUI::GetWindowRectFToParent(HWLWND hWnd, Gdiplus::RectF *pRect)
{
	return SendMessage(hWnd, WM_WL_GETRECTF, 0, (LPARAM)pRect);
}

int IUI::ClientToScreen(HWLWND hWnd, LPRECT lpRect)
{
	if (hWnd == NULL || lpRect == NULL)
	{
		return -1;
	}

	CIUIRect rcThis;
	GetWindowRectToHWND(hWnd, rcThis);
	CIUIRect rcHost;
	::GetWindowRect(GetHostWnd(hWnd), rcHost);

	// �õ��Լ�����Ļ����
	rcThis.OffsetRect(rcHost.TopLeft());

	CIUIRect rcNew = lpRect;
	rcNew.OffsetRect(rcThis.TopLeft());

	*lpRect = rcNew;

	return 0;
}

int IUI::ClientToScreen(HWLWND hWnd, LPPOINT lpPt)
{
	if (lpPt == NULL)
	{
		return -1;
	}

	CIUIRect rcThis;
	GetWindowRectToHWND(hWnd, rcThis);
	CIUIRect rcHost;
	::GetWindowRect(GetHostWnd(hWnd), rcHost);

	// �õ��Լ�����Ļ����
	rcThis.OffsetRect(rcHost.TopLeft());

	CIUIPoint ptNew = *lpPt;
	ptNew += rcThis.TopLeft();

	*lpPt = ptNew;

	return 0;
}

int IUI::ScreenToClient(HWLWND hWnd, LPRECT lpRect)
{
	if (lpRect == NULL)
	{
		return -1;
	}

	CIUIRect rcThis;
	GetWindowRectToHWND(hWnd, rcThis);
	CIUIRect rcHost;
	::GetWindowRect(GetHostWnd(hWnd), rcHost);

	// �õ��Լ�����Ļ����
	rcThis.OffsetRect(rcHost.TopLeft());

	CIUIRect rcNew = lpRect;
	rcNew.OffsetRect(-rcThis.TopLeft());

	*lpRect = rcNew;

	return 0;
}

int IUI::ScreenToClient(HWLWND hWnd, LPPOINT lpPt)
{
	if (lpPt == NULL)
	{
		return -1;
	}

	CIUIRect rcThis;
	GetWindowRectToHWND(hWnd, rcThis);
	CIUIRect rcHost;
	::GetWindowRect(GetHostWnd(hWnd), rcHost);

	// �õ��Լ�����Ļ����
	rcThis.OffsetRect(rcHost.TopLeft());

	CIUIPoint ptNew = *lpPt;
	ptNew -= rcThis.TopLeft();

	*lpPt = ptNew;

	return 0;
}

// TODO: ��Ҫ�о�API MoveWindow��SetWindowPos�߼��������ⲿ��ͷ����Ϣ��˳��
void IUI::MoveWindow(HWLWND hWnd, int x, int y, int nWidth, int nHeight, BOOL bRepaint/* = TRUE*/)
{
	if (GetHostWnd(hWnd) == NULL)
	{
		_ASSERT(FALSE);
		return;
	}

	CIUIRect rc(x, y, x + nWidth, y + nHeight);
	if (rc.right < rc.left)
	{
		rc.right = rc.left;
	}

	if (rc.bottom < rc.top)
	{
		rc.bottom = rc.top;
	}

	// ���������η��ͳߴ�ı���Ϣ
	WINDOWPOS wp;
	wp.cx = rc.Width();
	wp.cy = rc.Height();
	wp.flags = SWP_NOZORDER;
	wp.hwnd = (HWND)hWnd;
	wp.hwndInsertAfter = NULL;
	wp.x = rc.left;
	wp.y = rc.top;

	{
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_WINDOWPOSCHANGING;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&wp;
		RaiseEvent(hWnd, &arg);
	}

	// ��WM_WINDOWPOSCHANGING�¼��У��ⲿ�û������޸�������ֵ
	rc.SetRect(wp.x, wp.y, wp.x + wp.cx, wp.y + wp.cy);

	// WM_MOVING��LPARAMΪ�ؼ���Ļ����
	HWLWND hOwner = GetOwner(hWnd);
	HWND hHost = GetHostWnd(hWnd);
	RECT rect = rc;
	if (hOwner == NULL)
	{
		IUIClientToScreen(hHost, &rect);
	}
	else
	{
		ClientToScreen(hOwner, &rect);
	}
	{
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_MOVING;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&rect;
		RaiseEvent(hWnd, &arg);
	}
	if (hOwner == NULL)
	{
		IUIScreenToClient(hHost, &rect);
	}
	else
	{
		ScreenToClient(hOwner, &rect);
	}
	rc = rect;

	//
	CIUIRect rcOld;
	GetWindowRectToHWND(hWnd, rcOld);

	hWnd->m_rcItem = rc;

	// ���������η��ͳߴ�ı���Ϣ
	{
		wp.cx = hWnd->m_rcItem.Width();
		wp.cy = hWnd->m_rcItem.Height();
		wp.flags = SWP_NOZORDER;
		wp.hwnd = (HWND)hWnd;
		wp.hwndInsertAfter = NULL;
		wp.x = hWnd->m_rcItem.left;
		wp.y = hWnd->m_rcItem.top;

		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_WINDOWPOSCHANGED;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&wp;
		RaiseEvent(hWnd, &arg);
	}

	{
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_MOVE;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = MAKELPARAM(hWnd->m_rcItem.left, hWnd->m_rcItem.top);
		RaiseEvent(hWnd, &arg);
	}

	// ˢ���¾�����Ĳ���
	if (bRepaint)
	{
		CIUIRect rcNew;
		GetWindowRectToHWND(hWnd, rcNew);

		CIUIRect rcInvalid;
		BOOL bRet = UnionRect(rcInvalid, rcOld, rcNew);
		if (bRet && GetHostWnd(hWnd) != NULL)
		{
			::InvalidateRect(GetHostWnd(hWnd), rcInvalid, FALSE);
		}
	}
}

void IUI::MoveWindow(HWLWND hWnd, LPCRECT lpRect, BOOL bRepaint/* = TRUE*/)
{
	if (lpRect == NULL || GetHostWnd(hWnd) == NULL)
	{
		_ASSERT(FALSE);
		return;
	}

	IUI::MoveWindow(hWnd, lpRect->left, lpRect->top,
		RECTWIDTH(*lpRect), RECTHEIGHT(*lpRect), bRepaint);
}

BOOL IUI::SetWindowPos(HWLWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
	CIUIRect rcNew = hWnd->m_rcItem;
	int nOldX = hWnd->m_rcItem.left;
	int nOldY = hWnd->m_rcItem.top;
	int nOldWidth = hWnd->m_rcItem.Width();
	int nOldHeight = hWnd->m_rcItem.Height();
	if (!IsIncludeFlag(uFlags, SWP_NOMOVE))
	{
		rcNew.left = X;
		rcNew.top = Y;
		rcNew.right = rcNew.left + nOldWidth;
		rcNew.bottom = rcNew.top + nOldHeight;
	}

	if (!IsIncludeFlag(uFlags, SWP_NOSIZE))
	{
		rcNew.right = rcNew.left + cx;
		rcNew.bottom = rcNew.top + cy;
	}

	BOOL bRedraw = !IsIncludeFlag(uFlags, SWP_NOREDRAW);

	MoveWindow(hWnd, rcNew, bRedraw);

	return 0;
}

int IUI::GetClientRect(HWLWND hWnd, LPRECT lpRect)
{
	if (lpRect == NULL)
	{
		return -1;
	}

	CIUIRect rcClient = hWnd->m_rcItem;
	rcClient.OffsetRect(-rcClient.TopLeft());

	// �鿴�Ƿ���ˮƽ�ͣ��򣩴�ֱ������
	BOOL bVert = IsIncludeFlag(GetStyle(hWnd), WS_VSCROLL);
	if (bVert)
	{
		if (IsWindow(hWnd->m_hVerticalScrollBar))
		{
			CIUIRect rcScroll;
			GetWindowRect(hWnd->m_hVerticalScrollBar, rcScroll);

			rcClient.right -= rcScroll.Width();
		}
	}

	BOOL bHorz = IsIncludeFlag(GetStyle(hWnd), WS_HSCROLL);
	if (bHorz)
	{
		if (IsWindow(hWnd->m_hHorizontalScrollBar))
		{
			CIUIRect rcScroll;
			GetWindowRect(hWnd->m_hHorizontalScrollBar, rcScroll);

			rcClient.bottom -= rcScroll.Height();
		}
	}

	*lpRect = rcClient;

	return 0;
}

// �������Ļ
int IUI::GetWindowRect(HWLWND hWnd, LPRECT lpRect)
{
	if (lpRect == NULL || !IsWindow(hWnd))
	{
		return -1;
	}

	HWLWND hParent = GetParent(hWnd);
	CIUIRect rcWnd = hWnd->m_rcItem;

	if (hParent == NULL)
	{
		IUIClientToScreen(GetHostWnd(hWnd), rcWnd);
		*lpRect = rcWnd;
	}
	else
	{
		CIUIRect rcParent;
		GetWindowRect(hParent, rcParent);

		rcWnd.OffsetRect(rcParent.TopLeft());
		*lpRect = rcWnd;
	}

	return 0;
}

// �������������
int IUI::GetWindowRectToHWND(HWLWND hWnd, LPRECT lpRect)
{
	if (lpRect == NULL || hWnd == NULL || GetHostWnd(hWnd) == NULL)
	{
		return -1;
	}

	HWLWND hParent = GetParent(hWnd);

	if (hParent == NULL)
	{
		*lpRect = hWnd->m_rcItem;
	}
	else
	{
		CIUIRect rcWnd = hWnd->m_rcItem;

		CIUIRect rcParent;
		GetWindowRectToHWND(hParent, rcParent);

		rcWnd.OffsetRect(rcParent.TopLeft());
		*lpRect = rcWnd;
	}

	return 0;
}

void IUI::SetFixedWidth(HWLWND hWnd, int cx)
{
	if (cx < 0)
	{
		return;
	}

	hWnd->m_bFixedWidth = true;

	cx = JG_DPIGetDPIWidth(cx, IsDPIEnabled(hWnd));

	hWnd->m_cxyFixed.cx = cx;

	// ���������η��ͳߴ�ı���Ϣ
	{
		WINDOWPOS wp;
		wp.cx = hWnd->m_rcItem.Width();
		wp.cy = hWnd->m_rcItem.Height();
		wp.flags = SWP_NOMOVE;
		wp.hwnd = (HWND)hWnd;
		wp.hwndInsertAfter = NULL;
		wp.x = hWnd->m_rcItem.left;
		wp.y = hWnd->m_rcItem.top;

		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_WINDOWPOSCHANGED;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&wp;
		RaiseEvent(hWnd, &arg);
	}

	Invalidate(hWnd);
}

int IUI::GetFixedWidth(HWLWND hWnd)
{
	return hWnd->m_cxyFixed.cx;
}

void IUI::SetFixedHeight(HWLWND hWnd, int cy)
{
	if (cy < 0)
	{
		return;
	}

	hWnd->m_bFixedHeight = true;

	hWnd->m_cxyFixed.cy = cy;

	// ���������η��ͳߴ�ı���Ϣ
	{
		WINDOWPOS wp;
		wp.cx = hWnd->m_rcItem.Width();
		wp.cy = hWnd->m_rcItem.Height();
		wp.flags = SWP_NOMOVE;
		wp.hwnd = (HWND)hWnd;
		wp.hwndInsertAfter = NULL;
		wp.x = hWnd->m_rcItem.left;
		wp.y = hWnd->m_rcItem.top;

		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = WM_WINDOWPOSCHANGED;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.lParam = (LPARAM)&wp;
		RaiseEvent(hWnd, &arg);
	}

	Invalidate(hWnd);
}

int IUI::GetFixedHeight(HWLWND hWnd)
{
	return hWnd->m_cxyFixed.cy;
}

BOOL IUI::IsFixedWidth(HWLWND hWnd)
{
	return hWnd->m_bFixedWidth;
}

BOOL IUI::IsFixedHeight(HWLWND hWnd)
{
	return hWnd->m_bFixedHeight;
}

void IUI::ClearFixedWidth(HWLWND hWnd)
{
	hWnd->m_bFixedWidth = false;
	hWnd->m_cxyFixed.cx = 0;

	Invalidate(hWnd);
}

void IUI::ClearFixedHeight(HWLWND hWnd)
{
	hWnd->m_bFixedHeight = false;
	hWnd->m_cxyFixed.cy = 0;

	Invalidate(hWnd);
}

void IUI::SetMinWidth(HWLWND hWnd, int cx)
{
	if (hWnd->m_cxyMin.cx == cx)
	{
		return;
	}

	if (cx < 0)
	{
		return;
	}

	hWnd->m_cxyMin.cx = JG_DPIGetDPIWidth(cx, IsDPIEnabled(hWnd));

	Invalidate(hWnd);
}

int IUI::GetMinWidth(HWLWND hWnd)
{
	return hWnd->m_cxyMin.cx;
}

void IUI::SetMaxWidth(HWLWND hWnd, int cx)
{
	if (hWnd->m_cxyMax.cx == cx)
	{
		return;
	}

	if (cx < 0)
	{
		return;
	}

	cx = JG_DPIGetDPIWidth(cx, IsDPIEnabled(hWnd));

	hWnd->m_cxyMax.cx = cx;

	Invalidate(hWnd);
}

int IUI::GetMaxWidth(HWLWND hWnd)
{
	return hWnd->m_cxyMax.cx;
}

void IUI::SetMinHeight(HWLWND hWnd, int cy)
{
	if (hWnd->m_cxyMin.cy == cy)
	{
		return;
	}

	if (cy < 0)
	{
		return;
	}

	hWnd->m_cxyMin.cy = cy;

	Invalidate(hWnd);
}

int IUI::GetMinHeight(HWLWND hWnd)
{
	return hWnd->m_cxyMin.cy;
}

void IUI::SetMaxHeight(HWLWND hWnd, int cy)
{
	if (hWnd->m_cxyMax.cy == cy)
	{
		return;
	}

	if (cy < 0)
	{
		return;
	}

	hWnd->m_cxyMax.cy = JG_DPIGetDPIHeight(cy, IsDPIEnabled(hWnd));

	Invalidate(hWnd);
}

int IUI::GetMaxHeight(HWLWND hWnd)
{
	return hWnd->m_cxyMax.cy;
}

int IUI::SetTitleBarHeight(HWLWND hWnd, int nHeight)
{
	hWnd->m_nTitlebarHeight = nHeight;
	return 0;
}

int IUI::GetTitleBarHeight(HWLWND hWnd)
{
	return hWnd->m_nTitlebarHeight;
}

int IUI::SetBorderThickness(HWLWND hWnd, LPCRECT lprcBorder)
{
	if (lprcBorder == NULL)
	{
		return -1;
	}

	hWnd->m_rcBorderThickness = lprcBorder;

	return 0;
}

int IUI::GetBorderThickness(HWLWND hWnd, LPRECT lprcBorder)
{
	if (lprcBorder == NULL)
	{
		return -1;
	}

	*lprcBorder = hWnd->m_rcBorderThickness;

	return 0;
}

int IUI::SetControlMargin(HWLWND hWnd, LPCRECT lprc)
{
	if (lprc == NULL)
	{
		return -1;
	}

	hWnd->m_rcControlMargin = *lprc;

	return 0;
}

int IUI::GetControlMargin(HWLWND hWnd, LPRECT lprc)
{
	if (lprc == NULL)
	{
		return -1;
	}

	*lprc = hWnd->m_rcControlMargin;

	return 0;
}

Gdiplus::RectF *IUI::GetRectF(HWLWND hWnd)
{
	return hWnd->m_pRectF;
}

UINT IUI::SetResizeFlag(HWLWND hWnd, UINT uFlag)
{
	UINT uOldFlag = hWnd->m_dwCanDragResize;

	hWnd->m_dwCanDragResize = uFlag;

	return uOldFlag;
}

UINT IUI::GetResizeFlag(HWLWND hWnd)
{
	return hWnd->m_dwCanDragResize;
}

// lpScreenPoint: �����Ļ���ꡣ ��ΪMSDN�У�WM_NCHITTEST��������������Ļ�ġ�
int IUI::HitTest(HWLWND hWnd, LPPOINT lpScreenPoint)
{
	if (hWnd == NULL || lpScreenPoint == NULL)
	{
		return -1;
	}

	// Disabled control refuse hit test.
	if (!IsWindowEnabled(hWnd) || !IsWindowVisible(hWnd))
	{
		return -2;
	}

	// ������һ���ı�HitTest����Ļ���
	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = WM_NCHITTEST;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = MAKELPARAM(lpScreenPoint->x, lpScreenPoint->y);
	arg.lResult = HTCLIENT;
	LRESULT lr = RaiseEvent(hWnd, &arg);
	if (arg.bHandled)
	{
		hWnd->m_uLButtonDownHitTestRet = lr;
		return arg.lResult;
	}

	return arg.lResult;
}

BOOL IUI::SetMouseTransparent(HWLWND hWnd, BOOL bMouseTransparent)
{
	if (NULL == hWnd)
	{
		return FALSE;
	}

	BOOL bOld = hWnd->m_bMouseTransparent;
	hWnd->m_bMouseTransparent = bMouseTransparent;
	return bOld;
}

BOOL IUI::IsMouseTransparent(HWLWND hWnd)
{
	if (NULL == hWnd)
	{
		return FALSE;
	}

	return hWnd->m_bMouseTransparent;
}

CONTROL_LAYOUT_HOR IUI::SetHorzLayoutMode(HWLWND hWnd, CONTROL_LAYOUT_HOR eLayout)
{
	if (NULL == hWnd)
	{
		return CLH_UNKNOWN;
	}

	CONTROL_LAYOUT_HOR eOld = hWnd->m_eHAlign;
	hWnd->m_eHAlign = eLayout;
	return eOld;
}

CONTROL_LAYOUT_HOR IUI::GetHorzLayoutMode(HWLWND hWnd)
{
	return hWnd->m_eHAlign;
}

CONTROL_LAYOUT_VER IUI::SetVertLayoutMode(HWLWND hWnd, CONTROL_LAYOUT_VER eLayout)
{
	if (NULL == hWnd)
	{
		return CLV_UNKNOWN;
	}

	CONTROL_LAYOUT_VER eOld = hWnd->m_eVAlign;
	hWnd->m_eVAlign = eLayout;
	return eOld;
}

CONTROL_LAYOUT_VER IUI::GetVertLayoutMode(HWLWND hWnd)
{
	return hWnd->m_eVAlign;
}

DOCK IUI::SetDockProperty(HWLWND hWnd, DOCK eNewDock)
{
	if (NULL == hWnd)
	{
		return DOCK_UNKNOWN;
	}

	DOCK eOld = hWnd->m_eDockProperty;
	hWnd->m_eDockProperty = eNewDock;
	return eOld;
}

DOCK IUI::GetDockProperty(HWLWND hWnd)
{
	return hWnd->m_eDockProperty;
}

int IUI::SetLayoutMargin(HWLWND hWnd, LPCRECT lprcMargin)
{
	if (lprcMargin == NULL)
	{
		return -1;
	}

	hWnd->m_rcLayoutMargin = *lprcMargin;

	if (hWnd->m_bRedraw)
	{
		Invalidate(hWnd);
	}

	return 0;
}

int IUI::GetLayoutMargin(HWLWND hWnd, LPRECT lprcMargin)
{
	if (NULL == hWnd || NULL == lprcMargin)
	{
		return -1;
	}

	*lprcMargin = hWnd->m_rcLayoutMargin;

	return 0;
}

int IUI::SetLayoutInset(HWLWND hWnd, LPCRECT lprcInset)
{
	if (NULL == hWnd || lprcInset == NULL)
	{
		return -1;
	}

	hWnd->m_rcInset = *lprcInset;

	if (hWnd->m_bRedraw)
	{
		Invalidate(hWnd);
	}

	return 0;
}

int IUI::GetLayoutInset(HWLWND hWnd, LPRECT lprcInset)
{
	if (NULL == hWnd || lprcInset == NULL)
	{
		return -1;
	}

	*lprcInset = hWnd->m_rcInset;

	return 0;
}

void IUI::SetToolTip(HWLWND hWnd, LPCTSTR pstrText)
{
	if (NULL == hWnd)
	{
		return;
	}

	CIUIString strTemp(pstrText);
	strTemp.Replace(_T("<n>"), _T("\r\n"));
	hWnd->m_sToolTip = strTemp;
}

CIUIString IUI::GetToolTip(HWLWND hWnd)
{
	if (NULL == hWnd)
	{
		return _T("");
	}

	return hWnd->m_sToolTip;
}

void IUI::SetResToolTip(HWLWND hWnd, HINSTANCE hRes, UINT uID)
{
	if (NULL == hWnd)
	{
		return;
	}

	CIUIString strText;
	BOOL bRet = strText.LoadString(uID);

	if (!bRet)
	{
		return;
	}

	SetToolTip(hWnd, strText);
}

#if (_MSC_VER > 1200)	// VC6.0
void IUI::SetXResToolTip(HWLWND hWnd, HXSRESOURCE hXRes, LPCTSTR lpszSectionID, LPCTSTR lpszStringID)
{
	LPCWSTR lpszString = CParseLanguageFile::LoadXMLString(hXRes, lpszSectionID, lpszStringID);

	if (lpszString != NULL)
	{
		USES_CONVERSION;
		SetToolTip(hWnd, W2T((LPWSTR)lpszString));
	}
}
#endif // #if (_MSC_VER > 1200)	// VC6.0

void IUI::SetToolTipWidth(HWLWND hWnd, int nWidth)
{
	hWnd->m_nTooltipWidth = nWidth;
}

int IUI::GetToolTipWidth(HWLWND hWnd)
{
	return hWnd->m_nTooltipWidth;
}

void IUI::SetUserData(HWLWND hWnd, LPARAM lParam)
{
	hWnd->m_lUserData = lParam;
}

LPARAM IUI::GetUserData(HWLWND hWnd)
{
	return hWnd->m_lUserData;
}

void IUI::SetTag(HWLWND hWnd, LPCTSTR lpszTag)
{
	hWnd->m_strTag = lpszTag;
}

LPCTSTR IUI::GetTag(HWLWND hWnd)
{
	return hWnd->m_strTag;
}

UINT IUI::SetState(HWLWND hWnd, UINT uState)
{
	UINT uOld = hWnd->m_uState;
	hWnd->m_uState = uState;
	return uOld;
}

UINT IUI::GetState(HWLWND hWnd)
{
	return hWnd->m_uState;
}

UINT IUI::AddState(HWLWND hWnd, UINT uState)
{
	hWnd->m_uState |= uState;

	if (hWnd->m_bRedraw)
	{
		Invalidate(hWnd);
	}

	return hWnd->m_uState;
}

UINT IUI::RemoveState(HWLWND hWnd, UINT uState)
{
	hWnd->m_uState &= ~uState;
	return hWnd->m_uState;
}

BOOL IUI::IsWindowVisible(HWLWND hWnd)
{
	return IsIncludeFlag(GetStyle(hWnd), WS_VISIBLE);
}

BOOL IUI::IsAncestryVisible(HWLWND hWnd)
{
	HWLWND hParent = hWnd;

	while (NULL != hParent)
	{
		if (!IsIncludeFlag(GetStyle(hParent), WS_VISIBLE))
		{
			return FALSE;
		}

		hParent = GetParent(hParent);
	}

	return ::IsWindowVisible(GetHostWnd(hWnd));
}

BOOL CALLBACK WalkShowWindowHWLWnd(HWLWND hWndShowWindow, void *pCallbackParam)
{
	SendMessage(hWndShowWindow, WLM_PARENTSHOWWINDOW, 0, LPARAM(pCallbackParam));

	return FALSE;
}

BOOL IUI::ShowWindow(HWLWND hWnd, int nCmdShow)
{
	if (!IsWindow(hWnd))
	{
		return FALSE;
	}

	// 	if (IsWindowVisible(hWnd))
	// 	{
	// 		if (nCmdShow == SW_SHOW)
	// 		{
	// 			return TRUE;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (nCmdShow == SW_HIDE)
	// 		{
	// 			return TRUE;
	// 		}
	// 	}

	BOOL v = IsWindowVisible(hWnd);
	if (nCmdShow == SW_SHOW)
	{
		AddStyle(hWnd, WS_VISIBLE);

		// ���ԭ�����ɼ�����ɿɼ���Ҫ���²���һ�£���Ϊ�������ڼ䣬���ؼ�����ʱ������ӿؼ�
		if (!v)
		{
			// ��������ù��������������ر���ʾ�󣬲����²���
			// ��������ʹ��CanvasLayoutCtrl����
			// TODO: ��ʵ����Ҳ��Ӧ����CanvasLayoutCtrl�����Ǹ��ݿؼ��Լ��Ĳ����������������ֲ��֡�
			BOOL bWithinScrollBar = FALSE;
			BOOL bParentIsCanvas = FALSE;
			HWLWND hParent = GetParent(hWnd);
			if (NULL != hParent)
			{
				if (GetHorizontalScrollBar(hParent) == hWnd
					|| GetVerticalScrollBar(hParent) == hWnd)
				{
					bWithinScrollBar = TRUE;
				}
				else if (GetClassName(hParent) == IUI_CANVAS)
				{
					bParentIsCanvas = TRUE;
				}
			}
			else
			{
				bParentIsCanvas = TRUE;
			}

			if (!bWithinScrollBar)
			{
				if (bParentIsCanvas)
				{
					CanvasLayoutCtrl(hWnd);
				}
			}
		}
	}
	else
	{
		RemoveStyle(hWnd, WS_VISIBLE);
	}

	// �������������η�����Ϣ
	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = WM_SHOWWINDOW;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)IsWindowVisible(hWnd);
	RaiseEvent(hWnd, &arg);

	// �������к��������Ϣ����Ϊ���ĺ��������Ҫ��֪���ȱ���ʾ�������ˡ�
	WalkHWLWNDChild(hWnd, WalkShowWindowHWLWnd, (void *)IsWindowVisible(hWnd));

	if (IsWindowVisible(hWnd) != v)
	{
		Invalidate(hWnd);
	}

	//if (nCmdShow == SW_HIDE)
	//{
	//	IUITRACE(_T("���ؿؼ�%s[%s]\r\n"), GetClassName(hWnd), GetWindowText(hWnd));
	//}
	//else
	//{
	//	IUITRACE(_T("��ʾ�ؼ�%s[%s]\r\n"), GetClassName(hWnd), GetWindowText(hWnd));
	//}

	return TRUE;
}

BOOL IUI::EnableWindow(HWLWND hWnd, BOOL bEnabled)
{
	BOOL bOld = IsWindowEnabled(hWnd);

	if (bOld == bEnabled)
	{
		return !bOld;
	}

	if (bEnabled)
	{
		RemoveStyle(hWnd, WS_DISABLED);
	}
	else
	{
		AddStyle(hWnd, WS_DISABLED);
	}

	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = WM_ENABLE;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.wParam = bOld;
	arg.lParam = bEnabled;
	RaiseEvent(hWnd, &arg);

	if (hWnd->m_bRedraw)
	{
		Invalidate(hWnd);
	}

	return !bOld;
}

BOOL IUI::IsWindowEnabled(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return FALSE;
	}

	return !IsIncludeFlag(GetStyle(hWnd), WS_DISABLED);
}

// IUI::SetFocus�Ĵ������ ��ʧȥ�͵õ�����Ŀؼ�����WM_KILLFOCUS��WM_SETFOCUS�¼�
// ������hHost�еĽ���ؼ���
void xxxSendFocusMessages(HWND hHost, HWLWND hWnd)
{
	if (hHost == NULL)
	{
		return;
	}

	HWLWND hLoseFocus = (HWLWND)::SendMessage(hHost, WM_GETWLFOCUS, 0, 0);
	HWLWND hOldFocus = (HWLWND)::SendMessage(hHost, WM_SETWLFOCUS, 0, (LPARAM)hWnd);

	// ���WM_SETWLFOCUS����-1,��ʾ����ʧ��
	if (hOldFocus == HWLWND(-1))
	{
		return;
	}

	_ASSERT(hLoseFocus == hOldFocus);

	if (hLoseFocus != NULL)
	{
		// �ڱ��ؼ��õ��������֪ͨ���ؼ�
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hLoseFocus;
		arg.RoutedEvent = WM_KILLFOCUS;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.wParam = (WPARAM)hWnd;
		RaiseEvent(arg.hOriginalSender, &arg);
	}

	if (hWnd != NULL)
	{
		// ����WM_SETFOCUS
		// �����������������õĽ�����Ȼ���ǽ���ؼ��Ƿ��ͣ�
		// ��Ϊ�������������ͨ������WM_NCACTIVATE��Ϣ��return FALSE
		// ������WM_KILLFOCUS��������е���IUI::SetFocus��ֹʧȥ����
		HWLWND hNowFocus = (HWLWND)::SendMessage(hHost, WM_GETWLFOCUS, 0, 0);
		if (hWnd == hNowFocus)
		{
			// �ڱ��ؼ��õ��������֪ͨ���ؼ�
			RoutedEventArgs arg;
			arg.hSender = arg.hOriginalSender = hWnd;
			arg.RoutedEvent = WM_SETFOCUS;
			arg.eRoutingStrategy = RS_BUBBLE;
			arg.wParam = (WPARAM)hOldFocus;
			RaiseEvent(arg.hOriginalSender, &arg);
		}
	}
}

// TODO: ������Windows��Ϊ�ǣ�
// ������������ý���Ĵ���A����ʱ����ͨ��GetFocus�õ�A��
// ����ʧȥ����Ĵ���B����WM_KILLFOCUS��Ϣ��������B�У�ͨ��GetFocus�ǿ��Եõ�A��
// ����򴰿�A����WM_SETFOCUS
// ��Ϊ�����������ý���ؼ�ΪNULL������hWndΪNULLʱ���޷�ͨ��hWnd�õ�Host����
// �⽫���������޷�ΪHost�����ڵĽ���ؼ����ó�NULL������ҪhHost������
// ������Windows API SetFocus�߼�
HWLWND IUI::SetFocus(HWND hHost, HWLWND hWnd)
{
	if (hHost == NULL)
	{
		return NULL;
	}

	HWLWND hwndOldFocus = (HWLWND)::SendMessage(hHost, WM_GETWLFOCUS, 0, 0);

	// ����ΪNULL
	if (hWnd == NULL)
	{
		xxxSendFocusMessages(hHost, hWnd);
		return hwndOldFocus;
	}

	// ��������ȵĴ��ڱ���С������ã���Ҫ���ý��㡣
	HWLWND hwndTemp = hWnd;
	for (; hwndTemp != NULL; hwndTemp = GetParent(hwndTemp))
	{
		if (!IsWindowEnabled(hwndTemp)/* || IsIconic(hwndTemp)*/)
		{
			return NULL;
		}
	}

	// ����Host���ý���
	if (::GetFocus() != GetHostWnd(hWnd))
	{
		::SetFocus(GetHostWnd(hWnd));
	}

	if (hWnd != hwndOldFocus)
	{
		xxxSendFocusMessages(GetHostWnd(hWnd), hWnd);
	}

	return hwndOldFocus;
}

BOOL IUI::IsFocused(HWLWND hWnd)
{
	HWLWND hFocus = Window::GetWLFocus(GetHostWnd(hWnd));

	return (hFocus == hWnd);
}

int IUI::SetControlState(HWLWND hWnd, CONTROL_STATE eNewState)
{
	if (!IsWindow(hWnd))
	{
		return -1;
	}

	CONTROL_STATE eOldControlState = hWnd->ci.m_eControlState;

	{
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = UE_CONTROL_STATE_CHANGING;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.wParam = eOldControlState;// Old
		arg.lParam = eNewState; // New
		LRESULT lr = RaiseEvent(hWnd, &arg);
		if (arg.lResult != 0)
		{
			return 1;
		}
	}

	hWnd->ci.m_eControlState = eNewState;

	{
		RoutedEventArgs arg;
		arg.hSender = arg.hOriginalSender = hWnd;
		arg.RoutedEvent = UE_CONTROL_STATE_CHANGED;
		arg.eRoutingStrategy = RS_BUBBLE;
		arg.wParam = eOldControlState;// Old
		arg.lParam = hWnd->ci.m_eControlState; // New
		LRESULT lr = RaiseEvent(hWnd, &arg);
	}

	return 0;
}

CONTROL_STATE IUI::GetControlState(HWLWND hWnd)
{
	if (hWnd == NULL)
	{
		return CONTROL_STATE_UNKNOWN;
	}

	return hWnd->ci.m_eControlState;
}

int IUI::BindHorzScrollBarStyle(HWLWND hTreeView, const CScrollBarProp *pBindStyle)
{
	_ASSERT(IsWindow(hTreeView));
	return SendMessage(hTreeView, WLM_SET_BIND_SCROLLBAR_STYLE, TRUE, (LPARAM)pBindStyle);
}

int IUI::BindVertScrollBarStyle(HWLWND hTreeView, const CScrollBarProp *pBindStyle)
{
	_ASSERT(IsWindow(hTreeView));
	return SendMessage(hTreeView, WLM_SET_BIND_SCROLLBAR_STYLE, FALSE, (LPARAM)pBindStyle);
}

HWLWND IUI::FindControl(HWLWND hWndParent, LPCTSTR lpszName)
{
	if (NULL == hWndParent || NULL == lpszName)
	{
		return NULL;
	}

	HWLWND hFound = NULL;

	HWLWND hChild = hWndParent->spwndChild;
	for (; hChild != NULL; hChild = GetWindow(hChild, GW_HWNDNEXT))
	{
		// ѡ�жϺ����Լ��ǲ���Ҫ�ҵ�
		if (hChild->m_strName == lpszName)
		{
			hFound = hChild;
			break;
		}

		// �ٵݹ��жϺ��ӵĺ���
		hFound = FindControl(hChild, lpszName);
		if (hFound != NULL)
		{
			break;
		}
	}

	return hFound;
}

HWLWND IUI::HitTestChild(HWLWND hWnd, LPPOINT lpPt)
{
	// �����������꣬�������hWnd���׵�
	if (lpPt == NULL)
	{
		return NULL;
	}

	BOOL bVirtualRoot = (hWnd->m_uID == UINT(-1));
	HWLWND hRet = NULL;

	if (!bVirtualRoot)
	{
		// ���Բ��ɼ���disabled��
		if (!IsWindowVisible(hWnd))
		{
			return NULL;
		}

		if (!IsWindowEnabled(hWnd))
		{
			return NULL;
		}

		if (IsEditMode(hWnd))
		{
			// TODO: HWLWND֧����������ˡ�
			// �༭ģʽʱ���ڸ�����������ӿؼ���ҲӦ�ñ����У���Ϊ����Ҫ�ƶ��������ӿؼ���
			std::vector<HWLWND> vChildren;
			GetAllChildren(hWnd, TRUE, &vChildren);

			// �������
			std::vector<HWLWND>::reverse_iterator it = vChildren.rbegin();
			for (; it != vChildren.rend(); ++it)
			{
				HWLWND hChildWnd = *it;

				if (!IsWindowVisible(hChildWnd))
				{
					continue;
				}

				if (!IsWindowEnabled(hChildWnd))
				{
					continue;
				}

				CIUIRect rcChild;
				GetWindowRectToHWND(hChildWnd, rcChild);

				if (rcChild.PtInRect(*lpPt))
				{
					hRet = hChildWnd;
					break;
				}
			}
		}
		else
		{
			//
			// �ȿ����Ƿ������Լ������û���У��϶�Ҳ���������Լ��ĺ��ӣ��༭�����
			//
			CIUIPoint ptNew = *lpPt;
			if (!hWnd->m_rcItem.PtInRect(*lpPt))
			{
				return NULL;
			}

			//
			// ������ת�������hWnd�Լ��ģ���Ϊ���ӵ����꣬��������Լ���
			//
			ptNew.Offset(-hWnd->m_rcItem.TopLeft());

			// ����SetWindowRgn���õĲü�����
			if (hWnd->m_hrgnClip != NULL)
			{
				if (!PtInRegion(hWnd->m_hrgnClip, ptNew.x, ptNew.y))
				{
					return NULL;
				}
			}

			// �����������Լ�(���ԡ�͸�����ؼ�)
			if (!IsMouseTransparent(hWnd))
			{
				hRet = hWnd;
			}

			//
			// ���к��Ӳ��ԡ� ������ԣ���Ϊ�󴴽��������档
			// TreeView֮��ؼ����������ӿؼ������ȼ����ڰ󶨵�Item�ϵĿؼ�
			//
			BOOL bHittestChild = FALSE;
			HWLWND hChild = GetWindow(hWnd, GW_CHILD);
			hChild = GetWindow(hChild, GW_HWNDLAST);

			for (; hChild != NULL; hChild = GetWindow(hChild, GW_HWNDPREV))
			{
				// �ݹ����в���
				HWLWND hChildRet = HitTestChild(hChild, &ptNew);
				if (hChildRet != NULL)
				{
					if (!IsMouseTransparent(hChildRet))
					{
						bHittestChild = TRUE;
						hRet = hChildRet;
						break;
					}
				}
			}

			//
			// ���hWnd��TreeView��ListView��ComboBox�����б��˵����
			// ���а󶨵�Item�ϵĿؼ���ͨ��������Ϣ���ÿؼ��Լ��������ȼ����ڿؼ��������ӿؼ�
			// ���ԣ�ֻ�����ӿؼ�û������ʱ������Bind��Item�ϵĿؼ������в��ԡ�
			//
			if (!bHittestChild)
			{
				HWLWND hBindItem = (HWLWND)IUI::SendMessage(hWnd, WLM_HITTESTBINDITEM,
						0, MAKELPARAM(ptNew.x, ptNew.y));
				if (NULL != hBindItem)
				{
					hRet = hBindItem;
				}
			}
		}
	}

	// �����������ؼ����������������ĺ���
	if (bVirtualRoot)
	{
		// �������
		HWLWND hRoot = GetWindow(hWnd, GW_CHILD);
		hRoot = GetWindow(hRoot, GW_HWNDLAST);

		for (; hRoot != NULL; hRoot = GetWindow(hRoot, GW_HWNDPREV))
		{
			hRet = HitTestChild(hRoot, lpPt);
			if (hRet != NULL)
			{
				break;
			}
		}
	}

	return hRet;
}

// Point�������hHost������
HWLWND IUI::WindowFromPoint(HWND hHost, POINT Point)
{
	HWLWND hFound = NULL;

	// ��������
	HWLWND hChild = (HWLWND)::SendMessage(hHost, WM_GETCHILD, 0, 0);
	hChild = GetWindow(hChild, GW_HWNDLAST);
	for (; hChild != NULL; hChild = GetWindow(hChild, GW_HWNDPREV))
	{
		hFound = HitTestChild(hChild, &Point);
		if (hFound != NULL)
		{
			break;
		}
	}

	return hFound;
}

BOOL IUI::Invalidate(HWLWND hWnd)
{
	if (!IsWindowVisible(hWnd))
	{
		// ����ؼ������أ���ˢ�¸��ؼ�
		CIUIRect rcInParent;
		IUI::GetWindowRectToParent(hWnd, rcInParent);

		HWLWND hParent = GetParent(hWnd);
		if (NULL != hParent)
		{
			IUI::InvalidateRect(hParent, rcInParent);
		}
		else
		{
			::InvalidateRect(GetHostWnd(hWnd), rcInParent, FALSE);
		}

		return TRUE;
	}

	if (!hWnd->m_bRedraw)
	{
		return FALSE;
	}

	BOOL bUpdateLayeredWindow = IsUpdateLayeredWindow(GetHostWnd(hWnd));

	if (bUpdateLayeredWindow)
	{
		Window *pWnd = Window::FromHandlePermanent(GetHostWnd(hWnd));
		_ASSERT(pWnd != NULL);
		pWnd->Invalidate();
	}
	else
	{
		CIUIRect rcInvalidate;
		GetClientRect(hWnd, rcInvalidate);
		return InvalidateRect(hWnd, rcInvalidate);
	}

	return TRUE;
}

BOOL IUI::InvalidateRect(HWLWND hWnd, LPCRECT lpRect)
{
	// �Լ���������ֻҪ��һ�����ɼ����ͷ��ء�
	if (!IsAncestryVisible(hWnd))
	{
		return FALSE;
	}

// 	static int m = 0;
// 	IUITRACE(_T("%d InvalidateRect 0x%08x %s %s\r\n"), m++, hWnd, (LPCTSTR)GetClassName(hWnd), (LPCTSTR)GetName(hWnd));

	if (GetHostWnd(hWnd) != NULL)
	{
		if (IsUpdateLayeredWindow(GetHostWnd(hWnd)))
		{
			Window *pWindow = Window::FromHandlePermanent(GetHostWnd(hWnd));
			_ASSERT(pWindow != NULL);
			pWindow->Invalidate(FALSE);
		}
		else
		{
			CIUIRect rc;
			if (lpRect == NULL)
			{
				// �󲿷�����£�����������Ҳ��Ҫˢ�£�����ʹ�ÿؼ������������ꡣ
				GetWindowRectToHWND(hWnd, rc);
			}
			else
			{
				rc = lpRect;

				// ת�������Host������
				ClientToScreen(hWnd, rc);
				IUIScreenToClient(GetHostWnd(hWnd), rc);
			}

			::InvalidateRect(GetHostWnd(hWnd), rc, FALSE);
		}
	}
	else
	{
		_ASSERT(FALSE);
	}

	return TRUE;
}

BOOL IUI::SetUseRectF(HWLWND hWnd, BOOL bUse)
{
	BOOL bOld = hWnd->m_bUseRectF;
	hWnd->m_bUseRectF = bUse;
	return bOld;
}

BOOL IUI::IsUseRectF(HWLWND hWnd)
{
	return hWnd->m_bUseRectF;
}

BOOL IUI::IsCachedMode(HWLWND hWnd)
{
	return hWnd->m_bCacheMode;
}

// TODO: ��Ӧ���ṩ����ӿ�
HBITMAP IUI::GetCachedAlphaBitmap(HWLWND hWnd)
{
	return hWnd->m_hCacheAlphaBmp;
}

int IUI::SetCachedAlphaBitmap(HWLWND hWnd, HBITMAP hbmp)
{
	hWnd->m_hCacheAlphaBmp = hbmp;

	return 0;
}

// uIDEvent: ::SetTimerָ����Timer ID.
HTIMER FromTimerEventPermanent(UINT_PTR uIDEvent)
{
	std::map<UINT_PTR, HTIMER> *pMap = iuiMapTimer(TRUE);
	HTIMER hTimer = NULL;
	if (pMap != NULL)
	{
		// only look in the permanent map - does no allocations
		std::map<UINT_PTR, HTIMER>::iterator it = pMap->find(uIDEvent);
		if (it != pMap->end())
		{
			hTimer = it->second;
		}
		_ASSERT(hTimer == NULL || ((WLTIMERINFO *)hTimer)->uTimerID == uIDEvent);
	}

	return hTimer;
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	// IUITRACE(_T("TimerProc hWnd: 0x%08x, id: %d\r\n"), hwnd, idEvent);

	if (hwnd == NULL && uMsg == WM_TIMER)
	{
		HTIMER hTimer = FromTimerEventPermanent(idEvent);
		_ASSERT(hTimer != NULL);

		WLTIMERINFO *pTimer = (WLTIMERINFO *)hTimer;

		if (pTimer->lpTimerFunc != NULL)
		{
			// ���Timer�ص���ΪNULL����ִ�лص�
			pTimer->lpTimerFunc(pTimer->hOwner, uMsg, pTimer->uIDEvent, dwTime);
		}
		else
		{
			// ���Timer�ص�ΪNULL������WM_TIMER��Ϣ
			SendMessage(pTimer->hOwner, WM_TIMER, pTimer->uIDEvent, NULL);
		}
	}
}

UINT_PTR IUI::SetTimer(HWLWND hWnd, UINT_PTR nIDEvent, UINT uElapse, WLTIMERPROC lpTimerFunc)
{
	// �Ȳ���IDΪnIDEvent��Timer�Ƿ����
	BOOL bAlreadExist = FALSE;

	std::map<UINT_PTR, HTIMER>::iterator it;
	if (!hWnd->m_mapTimer.empty())
	{
		it = hWnd->m_mapTimer.find(nIDEvent);
		if (it != hWnd->m_mapTimer.end())
		{
			bAlreadExist = TRUE;
		}
	}

	UINT_PTR uRet = 0;
	// ����Ѵ��ڣ��滻�ɵ�
	if (bAlreadExist)
	{
		WLTIMERINFO *pTimerInfo = (WLTIMERINFO *)(it->second);
		_ASSERT(pTimerInfo != NULL);

		pTimerInfo->uElapse = uElapse;
		pTimerInfo->lpTimerFunc = lpTimerFunc;

		// �滻Timer
		uRet = ::SetTimer(NULL, pTimerInfo->uTimerID, uElapse, TimerProc);
		if (uRet != 0)
		{
			uRet = nIDEvent;
		}
		else
		{
			_ASSERT(FALSE);
		}
	}
	// ��������ڣ������µġ�
	else
	{
		UINT uNewID = ::SetTimer(NULL, 0, uElapse, TimerProc);
		if (uNewID != 0)
		{
			WLTIMERINFO *pTimerInfo = new WLTIMERINFO;
			pTimerInfo->hOwner = hWnd;
			pTimerInfo->uTimerID = uNewID;
			pTimerInfo->uIDEvent = nIDEvent;
			pTimerInfo->uElapse = uElapse;
			pTimerInfo->lpTimerFunc = lpTimerFunc;
			pTimerInfo->dwStartTime = GetTickCount();

			uRet = nIDEvent;

			// һ��������Timer map����һ����HWLWND::m_mapTimer����¼HWLWND��
			// Timer ID��HTIMER�Ĺ�ϵ���ڶ�����IUI_MODULE_THREAD_STATE::m_pmapTimer
			// ��¼::SetTimer������Timer ID��HHTIMER��Ӧ��ϵ��
			hWnd->m_mapTimer[pTimerInfo->uIDEvent] = pTimerInfo;

			// ���浽ȫ��map�С�
			std::map<UINT_PTR, HTIMER> *pMap = iuiMapTimer(TRUE);
			_ASSERT(pMap != NULL);
			(*pMap)[uNewID] = pTimerInfo;
		}
		else
		{
			_ASSERT(FALSE);
		}
	}

	return uRet;
}

BOOL IUI::KillTimer(HWLWND hWnd, UINT_PTR nIDEvent)
{
	// �Ȳ���IDΪnIDEvent��Timer�Ƿ����
	BOOL bAlreadExist = FALSE;

	std::map<UINT_PTR, HTIMER>::iterator it;
	if (!hWnd->m_mapTimer.empty())
	{
		it = hWnd->m_mapTimer.find(nIDEvent);
		if (it != hWnd->m_mapTimer.end())
		{
			bAlreadExist = TRUE;
		}
	}

	if (!bAlreadExist)
	{
		return FALSE;
	}

	WLTIMERINFO *pTimerInfo = (WLTIMERINFO *)(it->second);
	_ASSERT(pTimerInfo != NULL);

	UINT_PTR uTimerID = pTimerInfo->uTimerID;
	BOOL bRet = ::KillTimer(NULL, uTimerID);
	if (!bRet)
	{
		return bRet;
	}

	// ������map���Ƴ�
	hWnd->m_mapTimer.erase(it);

	std::map<UINT_PTR, HTIMER> *pMap = iuiMapTimer(FALSE);
	_ASSERT(pMap != NULL);
	pMap->erase(pTimerInfo->uTimerID);

	delete pTimerInfo;

	return bRet;
}

BOOL IUI::IsTimerExist(HWLWND hWnd, UINT_PTR nIDEvent)
{
	BOOL bAlreadExist = FALSE;

	if (!hWnd->m_mapTimer.empty())
	{
		std::map<UINT_PTR, HTIMER>::iterator it = hWnd->m_mapTimer.find(nIDEvent);
		if (it != hWnd->m_mapTimer.end())
		{
			bAlreadExist = TRUE;
		}
	}

	return bAlreadExist;
}

HRESULT IUI::RegisterDragDrop(HWLWND hwnd, IDropTarget *pDropTarget)
{
	if (!IsWindow(hwnd))
	{
		return DRAGDROP_E_INVALIDHWND;
	}

	if (NULL != hwnd->m_pDropTarget)
	{
		return DRAGDROP_E_ALREADYREGISTERED;
	}

	// ��Host����ע�ᡣHost���ں�hwnd�ؼ��õ��ǲ�ͬ��IDropTarget
	// ��Host����ע���pDropTargetHost���ڴ���WM_NCDESTROY��Ϣִ�к���OnNcDestroy
	// �е���RevokeDragDropʱ���ڲ������pDropTargetHost->Release���ͷš�
	CHWNDDropTargetEx *pDropTargetHost = new CHWNDDropTargetEx(GetHostWnd(hwnd));
	HRESULT hr = ::RegisterDragDrop(GetHostWnd(hwnd), pDropTargetHost);
	if (DRAGDROP_E_ALREADYREGISTERED == hr)
	{
		// ʧ��ʱ��RegisterDragDrop�������pDropTargetHost->AddRef��������delete���ͷ�
		delete pDropTargetHost;
	}
	else if (DRAGDROP_E_INVALIDHWND == hr)
	{
		delete pDropTargetHost;
		return DRAGDROP_E_INVALIDHWND;
	}
	else if (E_OUTOFMEMORY == hr)
	{
		delete pDropTargetHost;
		OutputDebugString(_T("���ڵ���RegisterDragDropǰ����OleInitialize.\r\n"));
		return E_OUTOFMEMORY;
	}

	ULONG uRef = pDropTarget->AddRef();
	hwnd->m_pDropTarget = pDropTarget;

	return S_OK;
}

HRESULT IUI::RevokeDragDrop(HWLWND hwnd)
{
	if (!IsWindow(hwnd))
	{
		return DRAGDROP_E_INVALIDHWND;
	}

	if (NULL == hwnd->m_pDropTarget)
	{
		return DRAGDROP_E_NOTREGISTERED;
	}

	hwnd->m_pDropTarget->Release();
	hwnd->m_pDropTarget = NULL;

	return S_OK;
}

SIZE IUI::EstimateSize(HWLWND hWnd)
{
	return hWnd->m_cxyFixed;
}

// TODO: TimerӦ�����ڶ����У������ǿؼ��С�
int IUI::BeginAnimation(HWLWND hWnd, ANIMATION_TARGET_PROPERTY eTarget, Animation *pAnimation)
{
	// ��ʱ��Ӧ�÷ŵ������У������ǿؼ���
	if (pAnimation == NULL)
	{
		return -1;
	}

	hWnd->m_mapAnimation[eTarget] = pAnimation;

	if (eTarget == ATP_TRANSLATE_TRANSFORM_X)
	{
		SetTimer(hWnd, IDT_TRANSLATE_TRANSFORM_X, 10, NULL);
	}
	else if (eTarget == ATP_TRANSLATE_TRANSFORM_Y)
	{
		SetTimer(hWnd, IDT_TRANSLATE_TRANSFORM_Y, 10, NULL);
	}
	else if (eTarget == ATP_TRANSLATE_TRANSFORM_POS)
	{
		int nDuration = pAnimation->GetDuration();

		SetTimer(hWnd, IDT_TRANSLATE_TRANSFORM_POS, 10, NULL);
	}

	return 0;
}

int IUI::BeforePaint(HWLWND hWnd, HDC hDC)
{
	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = UE_BEFOREPAINT;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)hDC;
	RaiseEvent(hWnd, &arg);
	return 0;
}

int IUI::AfterPaint(HWLWND hWnd, HDC hDC)
{
	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = UE_AFTERPAINT;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)hDC;
	RaiseEvent(hWnd, &arg);
	return 0;
}

int IUI::AfterPaintBkColor(HWLWND hWnd, HDC hDC)
{
	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = UE_AFTERPAINTBKCOLOR;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)hDC;
	RaiseEvent(hWnd, &arg);
	return 0;
}

int IUI::AfterPaintBkImage(HWLWND hWnd, HDC hDC)
{
	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = UE_AFTERPAINTBKIMAGE;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)hDC;
	RaiseEvent(hWnd, &arg);
	return 0;
}

int IUI::AfterChildrenPaint(HWLWND hWnd, HDC hDC)
{
	RoutedEventArgs arg;
	arg.hSender = arg.hOriginalSender = hWnd;
	arg.RoutedEvent = UE_AFTERCHILDRENPAINT;
	arg.eRoutingStrategy = RS_BUBBLE;
	arg.lParam = (LPARAM)hDC;
	RaiseEvent(hWnd, &arg);
	return 0;
}

int IUI::DrawBkColor(HWLWND hWnd, HDC hDC, LPCRECT lpRect)
{
	if (!IsDrawBkColor(hWnd))
	{
		return 1;
	}

	// Prepare state index
	COLORREF crBk = hWnd->ci.m_crBkN;
	if (!IsWindowEnabled(hWnd))
	{
		crBk = hWnd->ci.m_crBkD;
	}

	CIUIRect rcClient;
	GetClientRect(hWnd, rcClient);

	FillSolidRect(hDC, rcClient, crBk, IsUpdateLayeredWindow(GetHostWnd(hWnd)));

	return 0;
}

// hDC: Ϊ�������ڵ��ڴ����DC��������ԭ�㣬������Ϊ����Լ�Ϊ(0, 0)
// rcClip: BeginPaint�з��صĲü����Σ�����������Ϊ����Լ�������
int DefPaint(HWLWND hWnd, HDC hDC, const RECT &rcClip)
{
	if (!hWnd->m_bRedraw)
	{
		return 1;
	}

	CIUIRect rcClient;
	GetClientRect(hWnd, rcClient);

	if (hWnd->m_bClip)
	{
		if (!::IntersectRect(&hWnd->m_rcPaint, &rcClip, rcClient))
		{
			return 2;
		}
	}
	else
	{
		hWnd->m_rcPaint = rcClient;
	}

	BeforePaint(hWnd, hDC);
	DrawBkColor(hWnd, hDC, hWnd->m_rcPaint);
	AfterPaint(hWnd, hDC);

	return 0;
}

int WL_DrawBorder(HWLWND hWnd, HDC hDC, IUI_CONTROL_INFO *pci)
{
	if (pci == NULL)
	{
		return -1;
	}

	// Prepare state index
	COLORREF crBorder = hWnd->ci.m_crBorderN;
	if (!IsWindowEnabled(hWnd))
	{
		crBorder = hWnd->ci.m_crBorderD;
	}

	CIUIRect rcWnd;
	GetWindowRect(hWnd, rcWnd);
	rcWnd.OffsetRect(-rcWnd.TopLeft());

	HBRUSH hbrBorder = CreateSolidBrush(crBorder);
	FrameRect(hDC, rcWnd, hbrBorder);
	DeleteObject(hbrBorder);

	return 0;
}

int IUI::DrawBorder(HWLWND hWnd, HDC hDC)
{
	if (!IsDrawBorderColor(hWnd))
	{
		return 1;
	}

	return WL_DrawBorder(hWnd, hDC, &hWnd->ci);
}

void IUI::SetRedraw(HWLWND hWnd, BOOL bRedraw/* = true*/)
{
	SendMessage(hWnd, WM_SETREDRAW, bRedraw, 0);
}

BOOL IUI::IsRedraw(HWLWND hWnd)
{
	return hWnd->m_bRedraw;
}

int IUI::SetClip(HWLWND hWnd, BOOL bClip)
{
	return SendMessage(hWnd, WLM_SET_CLIP, bClip, 0);
}

BOOL IUI::IsClip(HWLWND hWnd)
{
	return SendMessage(hWnd, WLM_GET_CLIP, 0, 0);
}

// xxxSendMessage�ڲ�����xxxSendMessageTimeout
// ֱ�ӵ���hWnd�Ĵ��ڹ���
LRESULT IUI::SendMessage(HWLWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (NULL == hWnd)
	{
		return 0;
	}

	RoutedEventArgs arg;
	arg.hSender = hWnd;
	arg.hOriginalSender = hWnd;
	arg.RoutedEvent = uMsg;
	arg.eRoutingStrategy = RS_DIRECT;
	arg.wParam = wParam;
	arg.lParam = lParam;
	LRESULT lr = RaiseEvent(hWnd, &arg);

	return lr;
}

// ����ǿͻ��������Ϣ
LRESULT OnNcMouseMessage(HWLWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCLBUTTONDOWN)
	{
		CIUIPoint pt(lParam);
		hWnd->m_ptLButtonDown = pt;
		hWnd->m_rcLButtonDownRelateParent = hWnd->m_rcItem;

		if (hWnd->m_uLButtonDownHitTestRet != HTCLIENT)
		{
			SetCapture(hWnd);
		}
		else
		{
			//TODO: Ӧ��ֻ�������м��̽��㣨��Tab���ؼ����������ý��㡣
			// RichTextBox�Ľ�������ʱ������RichEdit�ڲ�������
			// ͨ��ITextHost.TxSetFocus���߿ؼ���
			if (GetClassName(hWnd) != IUI_RICHTEXTBOX
				&& GetClassName(hWnd) != IUI_IM)
			{
				SetFocus(GetHostWnd(hWnd), hWnd);
			}
		}
	}
	else if (uMsg == WM_NCLBUTTONUP)
	{
		if (IUI::GetCapture(NULL) == hWnd)
		{
			RoutedEventArgs arg;
			arg.hSender = hWnd;
			arg.hOriginalSender = hWnd;
			arg.RoutedEvent = WM_EXITSIZEMOVE;
			arg.eRoutingStrategy = RS_BUBBLE;
			RaiseEvent(arg.hOriginalSender, &arg);
		}

		hWnd->m_ptLButtonDown = CIUIPoint(-1, -1);
		hWnd->m_rcLButtonDownRelateParent.SetRectEmpty();
		ReleaseCapture(hWnd);
		hWnd->m_uLButtonDownHitTestRet = HTCLIENT;
	}
	else if (uMsg == WM_NCMOUSEMOVE)
	{
		CIUIPoint pt(lParam);

		// ����갴�º�Ҫô���ƶ��ؼ���Ҫô�����ſؼ�����ʱ�򣬲��ٽ���HitTest
		BOOL bSelected = GetKeyState(VK_LBUTTON) < 0;
		if (!bSelected)
		{
			CIUIPoint ptScreen = pt;
			ClientToScreen(hWnd, &ptScreen);
			hWnd->m_uLButtonDownHitTestRet = HitTest(hWnd, &ptScreen);
		}

		if (IUI::GetCapture(NULL) == hWnd)
		{
			if (hWnd->m_uLButtonDownHitTestRet == HTCAPTION)	// Drag move the windowless window
			{
				if (bSelected)
				{
					CIUIRect rcOld;
					GetWindowRectToParent(hWnd, rcOld);

					if (pt.x != hWnd->m_ptLButtonDown.x
						&& pt.y != hWnd->m_ptLButtonDown.y)
					{
						rcOld.OffsetRect(pt.x - hWnd->m_ptLButtonDown.x,
							pt.y - hWnd->m_ptLButtonDown.y);
						MoveWindow(hWnd, rcOld, TRUE);
					}
				}
			}
			else	// Drag resize the windowless window.
			{
				if (bSelected)
				{
					CIUIRect rcOld;
					GetWindowRectToParent(hWnd, rcOld);

					if ((hWnd->m_uLButtonDownHitTestRet == HTLEFT)
						&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_LEFT))
					{
						rcOld.left += (pt.x - hWnd->m_ptLButtonDown.x);

						if (rcOld.left > rcOld.right)
						{
							rcOld.left = rcOld.right;
						}
					}
					else if ((hWnd->m_uLButtonDownHitTestRet == HTTOPLEFT)
						&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_TOPLEFT))
					{
						rcOld.left += (pt.x - hWnd->m_ptLButtonDown.x);
						rcOld.top += (pt.y - hWnd->m_ptLButtonDown.y);

						if (rcOld.left > rcOld.right)
						{
							rcOld.left = rcOld.right;
						}
						if (rcOld.top > rcOld.bottom)
						{
							rcOld.top = rcOld.bottom;
						}
					}
					else if ((hWnd->m_uLButtonDownHitTestRet == HTTOP)
						&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_TOP))
					{
						rcOld.top += (pt.y - hWnd->m_ptLButtonDown.y);

						if (rcOld.top > rcOld.bottom)
						{
							rcOld.top = rcOld.bottom;
						}
					}
					else if ((hWnd->m_uLButtonDownHitTestRet == HTTOPRIGHT)
						&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_TOPRIGHT))
					{
						rcOld.top += (pt.y - hWnd->m_ptLButtonDown.y);
						rcOld.right = hWnd->m_rcLButtonDownRelateParent.right + (pt.x - hWnd->m_ptLButtonDown.x);

						if (rcOld.top > rcOld.bottom)
						{
							rcOld.top = rcOld.bottom;
						}
						if (rcOld.right < rcOld.left)
						{
							rcOld.right = rcOld.left;
						}
					}
					else if ((hWnd->m_uLButtonDownHitTestRet == HTRIGHT)
						&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_RIGHT))
					{
						rcOld.right = hWnd->m_rcLButtonDownRelateParent.right + (pt.x - hWnd->m_ptLButtonDown.x);

						if (rcOld.right < rcOld.left)
						{
							rcOld.right = rcOld.left;
						}
					}
					else if ((hWnd->m_uLButtonDownHitTestRet == HTBOTTOMRIGHT)
						&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_BOTTOMRIGHT))
					{
						rcOld.right = hWnd->m_rcLButtonDownRelateParent.right + (pt.x - hWnd->m_ptLButtonDown.x);
						rcOld.bottom = hWnd->m_rcLButtonDownRelateParent.bottom + (pt.y - hWnd->m_ptLButtonDown.y);

						if (rcOld.right < rcOld.left)
						{
							rcOld.right = rcOld.left;
						}
						if (rcOld.bottom < rcOld.top)
						{
							rcOld.bottom = rcOld.top;
						}
					}
					else if ((hWnd->m_uLButtonDownHitTestRet == HTBOTTOM)
						&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_BOTTOM))
					{
						rcOld.bottom = hWnd->m_rcLButtonDownRelateParent.bottom + (pt.y - hWnd->m_ptLButtonDown.y);

						if (rcOld.bottom < rcOld.top)
						{
							rcOld.bottom = rcOld.top;
						}
					}
					else if ((hWnd->m_uLButtonDownHitTestRet == HTBOTTOMLEFT)
						&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_BOTTOMLEFT))
					{
						rcOld.left += (pt.x - hWnd->m_ptLButtonDown.x);
						rcOld.bottom = hWnd->m_rcLButtonDownRelateParent.bottom + (pt.y - hWnd->m_ptLButtonDown.y);

						if (rcOld.left > rcOld.right)
						{
							rcOld.left = rcOld.right;
						}
						if (rcOld.bottom < rcOld.top)
						{
							rcOld.bottom = rcOld.top;
						}
					}

					MoveWindow(hWnd, rcOld, TRUE);
				}
			}
		}
	}

	return 0;
}

int IUI::AddEventHandler(HWLWND hWnd, CWLWndHandler *pHandler)
{
	if (hWnd == NULL)
	{
		return -1;
	}

	hWnd->m_pUserBindWLWndHandler = pHandler;

	return 0;
}

LRESULT IUI::DefEventHandler(HWLWND hWnd, RoutedEventArgs *pe)
{
	if (!::IsWindow(GetHostWnd(hWnd)))
	{
		return -1;
	}

	UINT uMsg = pe->RoutedEvent;
	WPARAM wParam = pe->wParam;
	LPARAM lParam = pe->lParam;

	if (pe->hOriginalSender == hWnd)
	{
		if (pe->eRoutingStrategy == RS_BUBBLE)
		{
			switch (uMsg)
			{
			case WM_DESTROY:
			{
				// Kill All Timers
				std::map<UINT_PTR, HTIMER>::iterator it = hWnd->m_mapTimer.begin();
				for (; it != hWnd->m_mapTimer.end(); ++it)
				{
					WLTIMERINFO *pTimer = (WLTIMERINFO *)it->second;

					::KillTimer(NULL, pTimer->uTimerID);
				}
				hWnd->m_mapTimer.clear();
			}
			break;

			case WM_NCHITTEST:
			{
				BOOL bSetCursor = wParam;
				CIUIPoint pt(lParam); // LPARAM�������Ļ����
				ScreenToClient(hWnd, &pt);

				CIUIRect rcClient;
				GetWindowRectToParent(hWnd, &rcClient);
				rcClient.OffsetRect(-rcClient.TopLeft());

				BOOL bSizingBorder = (GetStyle(hWnd) & WS_THICKFRAME);
				CIUIRect rc;

				// left top
				rc.left = rc.top = 0;
				rc.right = hWnd->m_rcBorderThickness.left;
				rc.bottom = hWnd->m_rcBorderThickness.top;
				if (bSizingBorder && PtInRect(&rc, pt)
					&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_TOPLEFT))
				{
					if (bSetCursor)
					{
						SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
					}
					pe->lResult = HTTOPLEFT;
					return 0;
				}

				// top
				rc.left = hWnd->m_rcBorderThickness.left;
				rc.right = rcClient.right - hWnd->m_rcBorderThickness.right;
				rc.bottom = hWnd->m_rcBorderThickness.top;
				if (bSizingBorder && PtInRect(&rc, pt)
					&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_TOP))
				{
					if (bSetCursor)
					{
						SetCursor(LoadCursor(NULL, IDC_SIZENS));
					}
					pe->lResult = HTTOP;
					return 0;
				}

				// right top
				rc.left = rcClient.right - hWnd->m_rcBorderThickness.right;
				rc.right = rcClient.right;
				rc.bottom = hWnd->m_rcBorderThickness.top;
				if (bSizingBorder && PtInRect(&rc, pt)
					&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_TOPRIGHT))
				{
					if (bSetCursor)
					{
						SetCursor(LoadCursor(NULL, IDC_SIZENESW));
					}
					pe->lResult = HTTOPRIGHT;
					return 0;
				}

				// right
				rc.top = hWnd->m_rcBorderThickness.top;
				rc.bottom = rcClient.bottom - hWnd->m_rcBorderThickness.bottom;
				rc.left = rcClient.right - hWnd->m_rcBorderThickness.right;
				if (bSizingBorder && PtInRect(&rc, pt)
					&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_RIGHT))
				{
					if (bSetCursor)
					{
						SetCursor(LoadCursor(NULL, IDC_SIZEWE));
					}
					pe->lResult = HTRIGHT;
					return 0;
				}

				// right bottom
				rc.top = rcClient.bottom - hWnd->m_rcBorderThickness.bottom;
				rc.bottom = rcClient.bottom;
				rc.left = rcClient.right - hWnd->m_rcBorderThickness.right;
				if (bSizingBorder && PtInRect(&rc, pt)
					&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_BOTTOMRIGHT))
				{
					if (bSetCursor)
					{
						SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
					}
					pe->lResult = HTBOTTOMRIGHT;
					return 0;
				}

				// bottom
				rc.left = hWnd->m_rcBorderThickness.left;
				rc.right = rcClient.right - hWnd->m_rcBorderThickness.right;
				rc.top = rcClient.bottom - hWnd->m_rcBorderThickness.bottom;
				if (bSizingBorder && PtInRect(&rc, pt)
					&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_BOTTOM))
				{
					if (bSetCursor)
					{
						SetCursor(LoadCursor(NULL, IDC_SIZENS));
					}
					pe->lResult = HTBOTTOM;
					return 0;
				}

				// left bottom
				rc.left = 0;
				rc.right = hWnd->m_rcBorderThickness.left;
				rc.top = rcClient.bottom - hWnd->m_rcBorderThickness.bottom;
				if (bSizingBorder && PtInRect(&rc, pt)
					&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_BOTTOMLEFT))
				{
					if (bSetCursor)
					{
						SetCursor(LoadCursor(NULL, IDC_SIZENESW));
					}
					pe->lResult = HTBOTTOMLEFT;
					return 0;
				}

				// left
				rc.top = hWnd->m_rcBorderThickness.top;
				rc.bottom = rcClient.bottom - hWnd->m_rcBorderThickness.bottom;
				rc.right = hWnd->m_rcBorderThickness.left;
				if (bSizingBorder && PtInRect(&rc, pt)
					&& IsIncludeFlag(hWnd->m_dwCanDragResize, GRF_LEFT))
				{
					if (bSetCursor)
					{
						SetCursor(LoadCursor(NULL, IDC_SIZEWE));
					}
					pe->lResult = HTLEFT;
					return 0;
				}

				// Title bar
				rc.top = hWnd->m_rcBorderThickness.top;
				rc.left = hWnd->m_rcBorderThickness.left;
				rc.right = rcClient.right - hWnd->m_rcBorderThickness.right;
				if (hWnd->m_nTitlebarHeight == -1)	// All client as title bar
				{
					rc.bottom = rcClient.bottom - hWnd->m_rcBorderThickness.bottom;
				}
				else
				{
					rc.bottom = hWnd->m_nTitlebarHeight;
				}

				if (PtInRect(&rc, pt))
				{
					pe->lResult = HTCAPTION;
					return 0;
				}
			}
			break;

			case UE_ISHIDEOLEBORDER:
				pe->lResult = hWnd->m_bHideOleBorder;
				return 0;

			case WM_WINDOWPOSCHANGED:
			{
				HWLWND hChild = GetWindow(hWnd, GW_CHILD);
				for (; hChild != NULL; hChild = GetWindow(hChild, GW_HWNDNEXT))
				{
					if (hChild != hWnd->m_hHorizontalScrollBar
						&& hChild != hWnd->m_hVerticalScrollBar)
					{
						CanvasLayoutCtrl(hChild);
					}
				}
			}
			return 0;

			default:
				break;
			}


		}
		else if (pe->eRoutingStrategy == RS_TUNNEL)
		{
			// �����������Ϣ��ת�����ڹ��̴���
			// ע�⣬WM_MOUSELEAVE�������Ϣ���������������Χ��
			// ��Ϊ����¼������³�·�ɣ�����ð��·�ɣ����ԣ�ֻ�����³�·��
			if (pe->RoutedEvent >= WM_NCMOUSEMOVE
				&& pe->RoutedEvent <= WM_NCXBUTTONDBLCLK)
			{
				OnNcMouseMessage(hWnd, uMsg, wParam, lParam);
			}
		}
		else if (pe->eRoutingStrategy == RS_DIRECT)
		{
			switch (uMsg)
			{
			case WM_PRINTCLIENT:
			case WM_PRINT:
			case WM_PAINT:
				DefPaint(hWnd, (HDC)wParam, *LPCRECT(lParam));
				return 0;

			case WM_SETREDRAW:
				hWnd->m_bRedraw = wParam;
				return 0;

			case WM_SETTEXT:
				if (hWnd->m_strCaption == (LPCTSTR)lParam)
				{
					return FALSE;
				}

				hWnd->m_strCaption = (LPCTSTR)lParam;
				Invalidate(hWnd);

				return TRUE;

			case WM_GETTEXTLENGTH:
				return hWnd->m_strCaption.GetLength();

			case WM_GETTEXT:
			{
				int nLen = wParam;
				LPTSTR lpszBuffer = (LPTSTR)lParam;
				int nCaptionLen = hWnd->m_strCaption.GetLength();
				if (nCaptionLen >= nLen)
				{
					_tcsncpy(lpszBuffer, (LPCTSTR)hWnd->m_strCaption, nLen - 1);
					return nLen - 1;
				}
				else
				{
					StringCchCopy(lpszBuffer, nLen, (LPCTSTR)hWnd->m_strCaption);
					return nCaptionLen;
				}
			}
			return 0;

			case WLM_SET_CLIP:
				hWnd->m_bClip = wParam == 0 ? FALSE : TRUE;
				return 0;

			case WLM_GET_CLIP:
				return hWnd->m_bClip;

			case WM_WL_ISUSERECTF:
				return hWnd->m_bUseRectF;

			case WM_WL_GETRECTF:
			{
				Gdiplus::RectF *pRectF = (Gdiplus::RectF *)lParam;
				*pRectF = *hWnd->m_pRectF;
			}
			return 0;

			case WM_TIMER:
			{
				UINT_PTR uIDEvent = wParam;

				WLTIMERINFO *pTimer = NULL;
				std::map<UINT_PTR, HTIMER>::iterator it = hWnd->m_mapTimer.begin();
				if (it != hWnd->m_mapTimer.end())
				{
					pTimer = (WLTIMERINFO *)it->second;
				}
				if (pTimer != NULL)
				{
					if (uIDEvent == IDT_TRANSLATE_TRANSFORM_X
						|| uIDEvent == IDT_TRANSLATE_TRANSFORM_Y)
					{
						DataAnimation *pAnimation = NULL;

						if (uIDEvent == IDT_TRANSLATE_TRANSFORM_X)
						{
							pAnimation = (DataAnimation *)hWnd->m_mapAnimation[ATP_TRANSLATE_TRANSFORM_X];
						}
						else if (uIDEvent == IDT_TRANSLATE_TRANSFORM_Y)
						{
							pAnimation = (DataAnimation *)hWnd->m_mapAnimation[ATP_TRANSLATE_TRANSFORM_Y];
						}
						else
						{
							_ASSERT(FALSE);
						}

						if (pAnimation->GetDuration() > 0)
						{
							bool bEnd = false;
							DWORD dwCurTime = GetTickCount();
							if (dwCurTime - pTimer->dwStartTime >= pAnimation->GetDuration())
							{
								// ��Duration����ʱ��׼����һ������
								pAnimation->TimerBehaviorStrategy(pTimer, &dwCurTime, &bEnd);
							}

							if (dwCurTime - pTimer->dwStartTime > pAnimation->GetDuration())
							{
								dwCurTime = pTimer->dwStartTime + pAnimation->GetDuration();
							}

							Gdiplus::REAL nRange = pAnimation->GetTo() - pAnimation->GetFrom();
							Gdiplus::REAL nCurValue = 0;
							if (pAnimation->m_bCurReverse)
							{
								nCurValue = pAnimation->GetTo() - (dwCurTime - pTimer->dwStartTime) * nRange / pAnimation->GetDuration();
							}
							else
							{
								nCurValue = pAnimation->GetFrom() + (dwCurTime - pTimer->dwStartTime) * nRange / pAnimation->GetDuration();
							}

							CIUIRect rect;
							GetWindowRectToParent(hWnd, rect);

							hWnd->m_bUseRectF = true;

							if (uIDEvent == IDT_TRANSLATE_TRANSFORM_X)
							{
								Gdiplus::RectF r;
								r.X = nCurValue;
								r.Y = (Gdiplus::REAL)rect.top;
								r.Width = (Gdiplus::REAL)rect.Width();
								r.Height = (Gdiplus::REAL)rect.Height();
								*hWnd->m_pRectF = r;
							}
							else if (uIDEvent == IDT_TRANSLATE_TRANSFORM_Y)
							{
								Gdiplus::RectF r;
								r.X = (Gdiplus::REAL)rect.left;
								r.Y = nCurValue;
								r.Width = (Gdiplus::REAL)rect.Width();
								r.Height = (Gdiplus::REAL)rect.Height();
								*hWnd->m_pRectF = r;
							}
							else
							{
								_ASSERT(FALSE);
							}

							if (bEnd)
							{
								if (pAnimation->GetFillBehavior() == FB_STOP)
								{
									if (uIDEvent == IDT_TRANSLATE_TRANSFORM_X)
									{
										rect.OffsetRect((int)pAnimation->GetFrom() - rect.left, 0);
									}
									else if (uIDEvent == IDT_TRANSLATE_TRANSFORM_Y)
									{
										rect.OffsetRect(0, (int)pAnimation->GetFrom() - rect.top);
									}
									else
									{
										_ASSERT(FALSE);
									}
									MoveWindow(hWnd, rect, TRUE);
								}
							}

							::InvalidateRect(GetHostWnd(hWnd), NULL, FALSE);
							::UpdateWindow(GetHostWnd(hWnd));
						}
					}
					else if (uIDEvent == IDT_TRANSLATE_TRANSFORM_POS)
					{
						DataAnimationUsingPath *pAnimation = (DataAnimationUsingPath *)hWnd->m_mapAnimation[ATP_TRANSLATE_TRANSFORM_POS];

						if (pAnimation->GetDuration() > 0)
						{
							if (!IsWindowVisible(hWnd))
							{
								ShowWindow(hWnd, SW_SHOW);
							}

							bool bEnd = false;
							DWORD dwCurTime = GetTickCount();
							if (dwCurTime - pTimer->dwStartTime >= pAnimation->GetDuration())
							{
								// ��Duration����ʱ��׼����һ������
								pAnimation->TimerBehaviorStrategy(pTimer, &dwCurTime, &bEnd);
							}

							if (dwCurTime - pTimer->dwStartTime > pAnimation->GetDuration())
							{
								dwCurTime = pTimer->dwStartTime + pAnimation->GetDuration();
							}

							CFlattenPathPoint pt;
							if (pAnimation->m_bCurReverse)
							{
								pAnimation->GetPoint(pAnimation->GetDuration() - (dwCurTime - pTimer->dwStartTime), &pt);
							}
							else
							{
								pAnimation->GetPoint(dwCurTime - pTimer->dwStartTime, &pt);
							}

							CIUIRect rect;
							GetWindowRectToParent(hWnd, rect);

							CIUIPoint ptBase = (LPARAM)pAnimation->GetTargetValue();

							Gdiplus::RectF r;
							r.X = pt.GetPoint().X - ptBase.x;
							r.Y = pt.GetPoint().Y - ptBase.y;
							r.Width = (Gdiplus::REAL)rect.Width();
							r.Height = (Gdiplus::REAL)rect.Height();

							hWnd->m_bUseRectF = true;
							*hWnd->m_pRectF = r;

							if (bEnd)
							{
								if (pAnimation->GetFillBehavior() == FB_STOP)
								{
								}
							}

							::InvalidateRect(GetHostWnd(hWnd), NULL, FALSE);
							::UpdateWindow(GetHostWnd(hWnd));
						}
					}
				}
			}
			return 0;

			case WLM_COMBINE_BK_IMAGE:
			{
				BOOL bOld = hWnd->ci.m_bCombineBkImage;
				hWnd->ci.m_bCombineBkImage = wParam;
				return bOld;
			}

			case WLM_IS_COMBINE_BK_IMAGE:
				return hWnd->ci.m_bCombineBkImage;

			case WLM_SET_BK_COLOR:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);
				COLORREF cr = lParam;

				if (eControlState == CONTROL_STATE_NORMAL)
				{
					hWnd->ci.m_crBkN = cr;
					return 0;
				}
				else if (eControlState == CONTROL_STATE_DISABLED)
				{
					hWnd->ci.m_crBkD = cr;
					return 0;
				}
				else
				{
					_ASSERT(FALSE);
				}
			}
			return 0;

			case WLM_GET_BK_COLOR:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);

				if (eControlState == CONTROL_STATE_NORMAL)
				{
					return hWnd->ci.m_crBkN;
				}
				else if (eControlState == CONTROL_STATE_DISABLED)
				{
					return hWnd->ci.m_crBkD;
				}
				else
				{
					_ASSERT(FALSE);
				}
			}
			return 0;

			case WLM_SET_BORDER_COLOR:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);
				COLORREF cr = lParam;

				if (eControlState == CONTROL_STATE_NORMAL)
				{
					hWnd->ci.m_crBorderN = cr;
				}
				else if (eControlState == CONTROL_STATE_DISABLED)
				{
					hWnd->ci.m_crBorderD = cr;
				}
				else
				{
					_ASSERT(FALSE);
				}
			}
			return 0;

			case WLM_GET_BORDER_COLOR:
			{
				CONTROL_STATE eControlState = (CONTROL_STATE)HIWORD(wParam);

				if (eControlState == CONTROL_STATE_NORMAL)
				{
					return hWnd->ci.m_crBorderN;
				}
				else if (eControlState == CONTROL_STATE_DISABLED)
				{
					return hWnd->ci.m_crBorderD;
				}
				else
				{
					_ASSERT(FALSE);
				}
			}
			return 0;

			case WLM_SET_BIND_SCROLLBAR_STYLE:
				if (wParam)
				{
					hWnd->m_pBindHorzScrollBarStyle = (CScrollBarProp *)lParam;

					if (IsWindow(hWnd->m_hHorizontalScrollBar))
					{
						ScrollBar_BindStyle(hWnd->m_hHorizontalScrollBar,
							hWnd->m_pBindHorzScrollBarStyle);
					}
				}
				else
				{
					hWnd->m_pBindVertScrollBarStyle = (CScrollBarProp *)lParam;

					if (IsWindow(hWnd->m_hVerticalScrollBar))
					{
						ScrollBar_BindStyle(hWnd->m_hVerticalScrollBar,
							hWnd->m_pBindVertScrollBarStyle);
					}
				}
				return 0;

			case WLM_GET_BIND_SCROLLBAR_STYLE:
				if (wParam)
				{
					return (LRESULT)hWnd->m_pBindHorzScrollBarStyle;
				}
				else
				{
					return (LRESULT)hWnd->m_pBindVertScrollBarStyle;
				}
				break;

			case WLM_SETHIDEOLEBORDER:
			{
				BOOL bOld = hWnd->m_bHideOleBorder;
				hWnd->m_bHideOleBorder = lParam;
				return bOld;
			}
			case WLM_GETHIDEOLEBORDER:
				return hWnd->m_bHideOleBorder;

			default:
				break;
			}
		}
	}

	return 0;
}

LRESULT IUI::CallIUIHandlerMap(HWLWND hWnd, RoutedEventArgs *pe)
{
	if (hWnd == NULL || pe == NULL)
	{
		_ASSERT(FALSE);
		return 0;
	}

	if (hWnd->m_pUserBindWLWndHandler == NULL)
	{
		// Must return 0 to continue message
		return 0;
	}

	return hWnd->m_pUserBindWLWndHandler->EventHandler(hWnd, pe);
}

LRESULT IUI::RaiseEvent(HWLWND hTargetWnd, RoutedEventArgs *pe)
{
	_IUI_THREAD_STATE *pThreadState = IUIGetThreadState();
	if (pThreadState != NULL)
	{
		pThreadState->m_LastEvent = *pe;
	}
	else
	{
		_ASSERT(FALSE);
	}

	if (!IsWindow(hTargetWnd))
	{
		return -1;
	}

	LRESULT lr = 0;
	if (pe->eRoutingStrategy == RS_BUBBLE)
	{
		// ������Ŀ�괰�ڼ������ڷַ��¼�
		HWLWND hCurTargetWnd = hTargetWnd;
		while (hCurTargetWnd != NULL)
		{
			// ��ǰ����Ϣ��˭���͵�
			pe->hSender = hCurTargetWnd;

			// �ַ��¼�
			if (hCurTargetWnd->lpfnEventHandler != NULL)
			{
				// ��ִ���û�ָ����Handler
				if (hCurTargetWnd->m_pUserBindWLWndHandler != NULL)
				{
					lr = CallIUIHandlerMap(hCurTargetWnd, pe);
					if (pe->bHandled)
					{
						break;
					}
				}

				// ��ִ�пؼ��Լ���Handler
				lr = hCurTargetWnd->lpfnEventHandler(hCurTargetWnd, pe);
			}
			else
			{
				_ASSERT(FALSE);
			}

			if (pe->bHandled)
			{
				break;
			}

			// �������hParent->EventHandler�У����ܻ��ͷŵ��ؼ�
			if (!::IsWindow(GetHostWnd(hTargetWnd)))
			{
				pe->bHandled = true;
				break;
			}

			hCurTargetWnd = GetParent(hCurTargetWnd);
		}

		// ÿһ���¼��������Ӿ�����ÿһ���ؼ�Ӧ���յ�����������ҲӦ���յ���
		// ���ԣ�������������ڷ�����Ϣ��
		// ִ�е����hTargetWnd�����Ѿ���Ч�ˣ�����GetHostWnd(hTargetWnd)����������������
		// �������ж�pe->bHandled
		if (!pe->bHandled && GetHostWnd(hTargetWnd) != NULL)
		{
			lr = ::SendMessage(GetHostWnd(hTargetWnd), WM_CONTROLEVENT, pe->RoutedEvent, (LPARAM)pe);
		}
	}
	else if (pe->eRoutingStrategy == RS_TUNNEL)
	{
		// ��¼�Ӿ���
		std::vector<HWLWND> vElement;

		HWLWND hParent = hTargetWnd;
		while (hParent != NULL)
		{
			vElement.push_back(hParent);
			hParent = GetParent(hParent);
		}

		// ���ε����Ӿ���ÿ��Ԫ�ص�

		// ÿһ���¼��������Ӿ�����ÿһ���ؼ�Ӧ���յ�����������ҲӦ���յ���
		// ���ԣ��������������ڷ�����Ϣ��
		if (GetHostWnd(hTargetWnd) != NULL)
		{
			lr = ::SendMessage(GetHostWnd(hTargetWnd), WM_CONTROLEVENT, pe->RoutedEvent, (LPARAM)pe);
		}

		if (pe->bHandled)
		{
			return lr;
		}
		// �������WM_CONTROLEVENT�У����ܻ��ͷŵ��ؼ�
		if (!::IsWindow(GetHostWnd(hTargetWnd)))
		{
			pe->bHandled = true;
			return -1;
		}

		std::vector<HWLWND>::reverse_iterator it = vElement.rbegin();
		for (; it != vElement.rend(); it++)
		{
			HWLWND hCurTargetWnd = *it;

			pe->hSender = hCurTargetWnd;

			// �ַ��¼�
			if (hCurTargetWnd->lpfnEventHandler != NULL)
			{
				// ��ִ���û�ָ����Handler
				if (hCurTargetWnd->m_pUserBindWLWndHandler != NULL)
				{
					lr = CallIUIHandlerMap(hCurTargetWnd, pe);
					if (pe->bHandled)
					{
						break;
					}
				}

				lr = hCurTargetWnd->lpfnEventHandler(hCurTargetWnd, pe);
			}
			else
			{
				_ASSERT(FALSE);
			}

			// �������EventHandler�У����ܻ��ͷŵ��ؼ�, ���ԣ�����һ����Ҫ���ʿؼ�������ڴ档
			if (pe->bHandled)
			{
				break;
			}
		}

		if (!pe->bHandled)
		{
			// Ȼ���ٷ���ð���¼�
			RoutedEventArgs arg;
			arg.hSender = pe->hSender;
			arg.hOriginalSender = pe->hOriginalSender;
			arg.RoutedEvent = pe->RoutedEvent;
			arg.eRoutingStrategy = RS_BUBBLE;
			arg.wParam = pe->wParam;
			arg.lParam = pe->lParam;
			RaiseEvent(arg.hOriginalSender, &arg);

			int n = 0;
		}
	}
	else if (pe->eRoutingStrategy == RS_DIRECT)
	{
		if (hTargetWnd->lpfnEventHandler != NULL)
		{
			// ��ִ���û�ָ����Handler
			if (hTargetWnd->m_pUserBindWLWndHandler != NULL)
			{
				lr = CallIUIHandlerMap(hTargetWnd, pe);
				if (pe->bHandled)
				{
					return lr;
				}
			}

			lr = hTargetWnd->lpfnEventHandler(hTargetWnd, pe);
			return lr;
		}
		else
		{
			_ASSERT(FALSE);
			return 0;
		}
	}

	return lr;
}

BOOL IUI::EnableScrollBar(HWLWND hWnd, UINT wSBflags, UINT wArrows)
{
	if (!IsWindow(hWnd))
	{
		return FALSE;
	}

	BOOL bEnableVertical = ((wSBflags == SB_BOTH) || (wSBflags == SB_VERT));
	BOOL bEnableHorizontal = ((wSBflags == SB_BOTH) || (wSBflags == SB_HORZ));

	if (bEnableVertical && hWnd->m_hVerticalScrollBar == NULL)
	{
		HWLWND hVertScrollBar = CreateWindowEx(NULL, 0, IUI_SCROLLBAR, NULL, SBS_VERT,
				0, 0, 0, 0, GetHostWnd(hWnd), hWnd, XNAME_VERTSCROLLBAR, NULL, NULL);

		hWnd->m_hVerticalScrollBar = hVertScrollBar;
	}
	else if (!bEnableVertical && hWnd->m_hVerticalScrollBar)
	{
		delete hWnd->m_hVerticalScrollBar;
		hWnd->m_hVerticalScrollBar = NULL;
	}

	if (bEnableHorizontal && hWnd->m_hHorizontalScrollBar == NULL)
	{
		HWLWND hHorzScrollBar = CreateWindowEx(NULL, 0, IUI_SCROLLBAR, NULL, SBS_HORZ,
				0, 0, 0, 0, GetHostWnd(hWnd), hWnd, XNAME_HORZSCROLLBAR, NULL, NULL);

		hWnd->m_hHorizontalScrollBar = hHorzScrollBar;
	}
	else if (!bEnableHorizontal && hWnd->m_hHorizontalScrollBar)
	{
		delete hWnd->m_hHorizontalScrollBar;
		hWnd->m_hHorizontalScrollBar = NULL;
	}

	Invalidate(hWnd);

	return TRUE;
}

void IUI::EnableFloatScrollBar(HWLWND hWnd, BOOL bFloatVBar, BOOL bFloatHBar)
{
	hWnd->m_bFloatVBar = bFloatVBar;
	hWnd->m_bFloatHBar = bFloatHBar;
}

BOOL IUI::IsFloatVBar(HWLWND hWnd)
{
	return hWnd->m_bFloatVBar;
}

BOOL IUI::IsFloatHBar(HWLWND hWnd)
{
	return hWnd->m_bFloatHBar;
}

int IUI::SetScrollRange(HWLWND hWnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
	if (nMaxPos < nMinPos)
	{
		nMaxPos = nMinPos;
	}

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE;
	si.nMin = nMinPos;
	si.nMax = nMaxPos;

	return SetScrollInfo(hWnd, nBar, &si, bRedraw);
}

int IUI::GetScrollRange(HWLWND hWnd, int nBar, int *pnMinPos, int *pnMaxPos)
{
	if (pnMinPos == NULL || pnMaxPos == NULL)
	{
		return -1;
	}

	if (nBar == SB_VERT)
	{
		return SendMessage(hWnd->m_hVerticalScrollBar,
				SBM_GETRANGE, (WPARAM)pnMinPos, (LPARAM)pnMaxPos);
	}
	else if (nBar == SB_HORZ)
	{
		return SendMessage(hWnd->m_hHorizontalScrollBar,
				SBM_GETRANGE, (WPARAM)pnMinPos, (LPARAM)pnMaxPos);
	}

	return 0;
}

int IUI::SetScrollPos(HWLWND hWnd, int nBar, int nPos, BOOL bRedraw/* = TRUE*/)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_POS;
	si.nPos = nPos;

	return SetScrollInfo(hWnd, nBar, &si, bRedraw);
}

int IUI::GetScrollPos(HWLWND hWnd, int nBar)
{
	if (hWnd->pSBInfo == NULL)
	{
		return 0;
	}

	SBDATA *pSBData = NULL;
	if (nBar == SB_HORZ)
	{
		pSBData = &hWnd->pSBInfo->Horz;
	}
	else if (nBar == SB_VERT)
	{
		pSBData = &hWnd->pSBInfo->Vert;
	}

	if (pSBData == NULL)
	{
		return 0;
	}

	return pSBData->pos;
}

int LayoutScrollBar(HWLWND hWnd)
{
	CIUIRect rcWnd;
	GetWindowRectToParent(hWnd, rcWnd);
	rcWnd.OffsetRect(-rcWnd.TopLeft());

	DWORD dwStyle = GetStyle(hWnd);
	BOOL bShowHScrollBar = IsIncludeFlag(dwStyle, WS_HSCROLL);
	BOOL bShowVScrollBar = IsIncludeFlag(dwStyle, WS_VSCROLL);

	DWORD dwExStyle = GetExStyle(hWnd);
	BOOL bLeftVScrollBar = IsIncludeFlag(dwExStyle, WS_EX_LEFTSCROLLBAR);

	// ���ˮƽ��ֱ������ΪNULL���򴴽�
	if (bShowHScrollBar && hWnd->m_hHorizontalScrollBar == NULL)
	{
		HWLWND hHorzScrollBar = CreateWindowEx(NULL, 0, IUI_SCROLLBAR, NULL, SBS_HORZ,
				0, 0, 0, 0, GetHostWnd(hWnd), hWnd, XNAME_HORZSCROLLBAR, NULL, NULL);
		if (hHorzScrollBar == NULL)
		{
			return -1;
		}

		hWnd->m_hHorizontalScrollBar = hHorzScrollBar;
		// Bind Style
		const CScrollBarProp *pBindStyle = (CScrollBarProp *)SendMessage(hWnd,
				WLM_GET_BIND_SCROLLBAR_STYLE, TRUE, 0);
		if (NULL == pBindStyle)
		{
			pBindStyle = g_pHorScrollBarBindProp;
		}
		ScrollBar_BindStyle(GetHorizontalScrollBar(hWnd), pBindStyle);
	}

	if (bShowVScrollBar && hWnd->m_hVerticalScrollBar == NULL)
	{
		HWLWND hVertScrollBar = CreateWindowEx(NULL, 0, IUI_SCROLLBAR, NULL, SBS_VERT,
				0, 0, 0, 0, GetHostWnd(hWnd), hWnd, XNAME_VERTSCROLLBAR, NULL, NULL);
		if (hVertScrollBar == NULL)
		{
			return -2;
		}

		hWnd->m_hVerticalScrollBar = hVertScrollBar;
		// Bind Style
		const CScrollBarProp *pBindStyle = (CScrollBarProp *)SendMessage(hWnd,
				WLM_GET_BIND_SCROLLBAR_STYLE, FALSE, 0);
		if (NULL == pBindStyle)
		{
			pBindStyle = g_pVerScrollBarBindProp;
		}
		ScrollBar_BindStyle(GetVerticalScrollBar(hWnd), pBindStyle);
	}

	if (bShowHScrollBar)
	{
		CIUIRect rcHScrollBar(rcWnd);
		rcHScrollBar.top = rcHScrollBar.bottom - GetHScrollBarHeight(hWnd);

		if (bShowVScrollBar)
		{
			if (bLeftVScrollBar)
			{
				rcHScrollBar.left += GetVScrollBarWidth(hWnd);
			}
			else
			{
				rcHScrollBar.right -= GetVScrollBarWidth(hWnd);
			}
		}

		CIUIRect rcOld;
		GetWindowRectToParent(GetHorizontalScrollBar(hWnd), rcOld);
		if (rcOld != rcHScrollBar)
		{
			IUI::MoveWindow(GetHorizontalScrollBar(hWnd), rcHScrollBar, TRUE);
		}

		if (!IsWindowVisible(GetHorizontalScrollBar(hWnd)))
		{
			ShowWindow(GetHorizontalScrollBar(hWnd), SW_SHOW);
		}
	}
	else
	{
		ShowWindow(GetHorizontalScrollBar(hWnd), SW_HIDE);
	}

	if (bShowVScrollBar)
	{
		CIUIRect rcVScrollBar(rcWnd);

		if (bLeftVScrollBar)
		{
			rcVScrollBar.right = rcVScrollBar.left + GetVScrollBarWidth(hWnd);
		}
		else
		{
			rcVScrollBar.left = rcVScrollBar.right - GetVScrollBarWidth(hWnd);
		}

		if (bShowHScrollBar)
		{
			rcVScrollBar.bottom -= GetHScrollBarHeight(hWnd);
		}

		CIUIRect rcOld;
		GetWindowRectToParent(GetVerticalScrollBar(hWnd), rcOld);
		if (rcOld != rcVScrollBar)
		{
			MoveWindow(GetVerticalScrollBar(hWnd), rcVScrollBar, TRUE);
		}

		// ��ULWģʽ��ShowWindow������UpdateLayeredWindow����
		// �ж�һ�£���С���ô���
		if (!IsWindowVisible(GetVerticalScrollBar(hWnd)))
		{
			ShowWindow(GetVerticalScrollBar(hWnd), SW_SHOW);
		}
	}
	else
	{
		ShowWindow(GetVerticalScrollBar(hWnd), SW_HIDE);
	}

	return 0;
}

// ���ع�������ǰλ��
int IUI::SetScrollInfo(HWLWND hWnd, int fnBar, LPSCROLLINFO lpsi, BOOL fRedraw)
{
	if (hWnd == NULL || lpsi == NULL)
	{
		return 0;
	}

	if (hWnd->pSBInfo == NULL)
	{
		hWnd->pSBInfo = new SBINFO;
		ZeroMemory(hWnd->pSBInfo, sizeof(SBINFO));
	}

	SBDATA *pSBData = NULL;
	if (fnBar == SB_HORZ)
	{
		pSBData = &hWnd->pSBInfo->Horz;
	}
	else if (fnBar == SB_VERT)
	{
		pSBData = &hWnd->pSBInfo->Vert;
	}

	if (pSBData == NULL)
	{
		return 0;
	}

	if (IsIncludeFlag(lpsi->fMask, SIF_RANGE))
	{
		pSBData->posMin = lpsi->nMin;
		pSBData->posMax = lpsi->nMax;
		if (pSBData->posMax < pSBData->posMin)
		{
			pSBData->posMax = pSBData->posMin;
		}
	}

	if (IsIncludeFlag(lpsi->fMask, SIF_POS))
	{
		pSBData->pos = lpsi->nPos;
	}

	if (IsIncludeFlag(lpsi->fMask, SIF_PAGE))
	{
		pSBData->page = lpsi->nPage;
	}

	if (pSBData->page < 0)
	{
		pSBData->page = 0;
	}
	if (pSBData->page > pSBData->posMax - pSBData->posMin + 1)
	{
		pSBData->page = pSBData->posMax - pSBData->posMin + 1;
	}

	if (pSBData->pos < pSBData->posMin)
	{
		pSBData->pos = pSBData->posMin;
	}
	if (pSBData->pos > pSBData->posMax - max(pSBData->page - 1, 0))
	{
		pSBData->pos = pSBData->posMax - max(pSBData->page - 1, 0);
	}

	// �ж��Ƿ���Ҫ���ֹ�����
	// ������lpsi�ж��Ƿ���ֹ���������Ϊlpsi->fMask����ֻ����SIF_POS
	BOOL bShowScroll = FALSE;
	if (int(pSBData->page) < (pSBData->posMax + 1) && pSBData->page > 0)
	{
		bShowScroll = TRUE;
	}

	if (fnBar == SB_VERT)
	{
		if (bShowScroll)
		{
			AddStyle(hWnd, WS_VSCROLL);
		}
		else
		{
			RemoveStyle(hWnd, WS_VSCROLL);
		}
	}
	else if (fnBar == SB_HORZ)
	{
		if (bShowScroll)
		{
			AddStyle(hWnd, WS_HSCROLL);
		}
		else
		{
			RemoveStyle(hWnd, WS_HSCROLL);
		}
	}

	// �����ù�����λ�ã���Ϊ����Ϊ����������SetScrollInfoʱ����
	// ���ù��������꣬�������°�ť����������
	LayoutScrollBar(hWnd);

	if (IsIncludeFlag(lpsi->fMask, SIF_TRACKPOS))
	{
		// MSDN�е�SetScrollInfo����������Track pos
		_ASSERT(FALSE);
	}

	// �ѹ�����Ϣ���õ��������ؼ���
	HWLWND hScrollBar = (fnBar == SB_HORZ ? hWnd->m_hHorizontalScrollBar : hWnd->m_hVerticalScrollBar);
	if (hScrollBar != NULL)
	{
		SCROLLINFO si;
		si = *lpsi;

		// ��ΪSBM_SETSCROLLINFO�ڲ���SCROLLINFO��ֵ���кϷ��Լ��ʱ�����ܻ��޸�����ֵ
		// ���������SetScrollInfo�󣬿��ܻ�Ҫʹ��lpsi�����ԣ����ﴫһ��lpsi�Ŀ�����
		// SBM_SETSCROLLINFO��Ϣ�� (�������Header ���Ҳ�Item���ҷָ���ʱ��ListViewˮƽ����
		// ���ҵ�����)
		SendMessage(hScrollBar, SBM_SETSCROLLINFO, fRedraw, (LPARAM)&si);
	}

	return pSBData->pos;
}

BOOL IUI::GetScrollInfo(HWLWND hWnd, int nBar, LPSCROLLINFO lpScrollInfo)
{
	if (lpScrollInfo == NULL)
	{
		return FALSE;
	}

	if (hWnd->pSBInfo == NULL)
	{
		return FALSE;
	}

	SBDATA *pSBData = NULL;
	if (nBar == SB_HORZ)
	{
		pSBData = &hWnd->pSBInfo->Horz;
	}
	else if (nBar == SB_VERT)
	{
		pSBData = &hWnd->pSBInfo->Vert;
	}

	if (pSBData == NULL)
	{
		return FALSE;
	}

	if (IsIncludeFlag(lpScrollInfo->fMask, SIF_RANGE))
	{
		lpScrollInfo->nMin = pSBData->posMin;
		lpScrollInfo->nMax = pSBData->posMax;
	}

	if (IsIncludeFlag(lpScrollInfo->fMask, SIF_PAGE))
	{
		lpScrollInfo->nPage = pSBData->page;
	}

	if (IsIncludeFlag(lpScrollInfo->fMask, SIF_POS))
	{
		lpScrollInfo->nPos = pSBData->pos;
	}

	if (IsIncludeFlag(lpScrollInfo->fMask, SIF_TRACKPOS))
	{
		// Track Pos�ǹ������ؼ������ʵʱλ�ã�ֻ�ܴӿؼ��ϵõ���
		HWLWND hScrollBar = NULL;
		if (nBar == SB_VERT)
		{
			hScrollBar = hWnd->m_hVerticalScrollBar;
		}
		else if (nBar == SB_HORZ)
		{
			hScrollBar = hWnd->m_hHorizontalScrollBar;
		}

		if (hScrollBar == NULL)
		{
			return FALSE;
		}

		SCROLLINFO si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_TRACKPOS;
		SendMessage(hScrollBar, SBM_GETSCROLLINFO, 0, (LPARAM)&si);

		lpScrollInfo->nTrackPos = si.nTrackPos;
	}

	return TRUE;
}

BOOL IUI::ShowScrollBar(HWLWND hWnd, int wBar, BOOL bShow)
{
	if (wBar == SB_VERT)
	{
		if (hWnd->m_hVerticalScrollBar != NULL)
		{
			ShowWindow(hWnd->m_hVerticalScrollBar, bShow ? SW_SHOW : SW_HIDE);
			return TRUE;
		}
	}
	else if (wBar == SB_HORZ)
	{
		if (hWnd->m_hHorizontalScrollBar != NULL)
		{
			ShowWindow(hWnd->m_hHorizontalScrollBar, bShow ? SW_SHOW : SW_HIDE);
			return TRUE;
		}
	}

	return FALSE;
}

int IUI::SetHScrollBarHeight(HWLWND hWnd, int nHeight)
{
	int nOld = hWnd->m_nHScrollBarHeight;
	hWnd->m_nHScrollBarHeight = nHeight;
	return nOld;
}

int IUI::GetHScrollBarHeight(HWLWND hWnd)
{
	return hWnd->m_nHScrollBarHeight;
}

int IUI::SetVScrollBarWidth(HWLWND hWnd, int nWidth)
{
	int nOld = hWnd->m_nVScrollBarWidth;
	hWnd->m_nVScrollBarWidth = nWidth;
	return nOld;
}

int IUI::GetVScrollBarWidth(HWLWND hWnd)
{
	return hWnd->m_nVScrollBarWidth;
}

HWLWND IUI::GetVerticalScrollBar(HWLWND hWnd)
{
	return hWnd->m_hVerticalScrollBar;
}

HWLWND IUI::GetHorizontalScrollBar(HWLWND hWnd)
{
	return hWnd->m_hHorizontalScrollBar;
}

void IUI::SetMember(HWLWND hWnd, void *pMember)
{
	hWnd->m_pMember = pMember;
}

void *IUI::GetMember(HWLWND hWnd)
{
	return hWnd->m_pMember;
}

// See: InternalSetProp
// ԭ��SetProp/GetProp��ͨ����Ϣ�����ã���������Ҳ��ͨ����Ϣ������.
// ���ǰѿؼ��ľɵ�EventHandlerͨ��SetProp���ø��ؼ���
// �ڿؼ��µ�EventHandler�У�ͨ��GetProp���õ��ɵ�EventHandler��
// ���SetProp/GetProp��ͨ����Ϣ�����ã�����������ѭ����
BOOL IUI::SetProp(HWLWND hCtrl, LPCTSTR lpString, HANDLE hData)
{
	if (hCtrl == NULL || lpString == NULL)
	{
		return FALSE;
	}

	HPROPLIST pmapProp = hCtrl->m_pMapProp;
	if (pmapProp == NULL)
	{
		return FALSE;
	}

	(*pmapProp)[lpString] = hData;

	return TRUE;
}

HANDLE IUI::GetProp(HWLWND hCtrl, LPCTSTR lpString)
{
	if (hCtrl == NULL || lpString == NULL)
	{
		return NULL;
	}

	HPROPLIST pmapProp = hCtrl->m_pMapProp;
	if (pmapProp == NULL)
	{
		return NULL;
	}

	std::map<CIUIString, HANDLE>::iterator it = pmapProp->find(lpString);
	if (it == pmapProp->end())
	{
		return NULL;
	}

	return it->second;
}

HANDLE IUI::RemoveProp(HWLWND hCtrl, LPCTSTR lpString)
{
	if (hCtrl == NULL || lpString == NULL)
	{
		return NULL;
	}

	HPROPLIST pmapProp = hCtrl->m_pMapProp;
	if (pmapProp == NULL)
	{
		return NULL;
	}

	std::map<CIUIString, HANDLE>::iterator it = pmapProp->find(lpString);
	if (it == pmapProp->end())
	{
		return NULL;
	}

	HANDLE hRet = it->second;

	pmapProp->erase(it);

	return hRet;
}

HWND IUI::SetToolTips(HWLWND hWnd, HWND pWndTip)
{
	_ASSERT(IsWindow(hWnd));
	return (HWND)SendMessage(hWnd, WLM_SETTOOLTIPS, 0, (LPARAM)pWndTip);
}

HWND IUI::GetToolTips(HWLWND hWnd)
{
	_ASSERT(IsWindow(hWnd));
	return (HWND)SendMessage(hWnd, WLM_GETTOOLTIPS, 0, 0L);
}

// ���໯windowless�ؼ�
fnWLEventHandler IUI::SubclassWindowless(HWLWND hWnd, fnWLEventHandler lpfnNew)
{
	if (hWnd == NULL || lpfnNew == NULL)
	{
		_ASSERT(FALSE);
		return NULL;
	}

	RoutedEventArgs arg;
	arg.hSender = hWnd;
	arg.hOriginalSender = hWnd;
	arg.RoutedEvent = UE_SUBCLASSING;
	arg.eRoutingStrategy = RS_DIRECT;
	arg.wParam = (WPARAM)hWnd->lpfnEventHandler;
	arg.lParam = (LPARAM)lpfnNew;
	LRESULT lr = RaiseEvent(hWnd, &arg);
	if (arg.bHandled)
	{
		return hWnd->lpfnEventHandler;
	}

	fnWLEventHandler lpfnOld = hWnd->lpfnEventHandler;
	hWnd->lpfnEventHandler = lpfnNew;
	SetProp(hWnd, _T("GetProp_Old_Handler"), lpfnOld);

	arg.hSender = hWnd;
	arg.hOriginalSender = hWnd;
	arg.RoutedEvent = UE_SUBCLASSED;
	arg.eRoutingStrategy = RS_DIRECT;
	arg.wParam = (WPARAM)lpfnOld;
	arg.lParam = (LPARAM)lpfnNew;
	lr = RaiseEvent(hWnd, &arg);

	return lpfnOld;
}

// ���໯windowless�ؼ�
fnWLEventHandler IUI::SuperclassWindowless(LPCTSTR lpszClassName, fnWLEventHandler lpfnNew)
{
	if (lpszClassName == NULL || lpfnNew == NULL)
	{
		_ASSERT(FALSE);
		return NULL;
	}

	std::map<CIUIString, CONST WLWNDCLASS *>::iterator it = m_gWLClassMap.m_mapWLSuperClasses.find(lpszClassName);
	if (it == m_gWLClassMap.m_mapWLSuperClasses.end())
	{
		return NULL;
	}

	WLWNDCLASS *pwc = (WLWNDCLASS *)it->second;

	fnWLEventHandler lpfnOld = pwc->lpfnEventHandler;

	//RegisterWindowlessClass(lpszClassName, lpfnNew);
	pwc->lpfnEventHandler = lpfnNew;

	return lpfnOld;
}

LRESULT WINAPI IUI::CallEventHandler(fnWLEventHandler lpPrevEventHandler, HWLWND hWnd, RoutedEventArgs *pe)
{
	if (lpPrevEventHandler == NULL)
	{
		return 0;
	}

	return lpPrevEventHandler(hWnd, pe);
}

int IUI::BindStyle(HWLWND hWnd, const CControlProp *pProp)
{
	return SendMessage(hWnd, WLM_BIND_STYLE, 0, (LPARAM)pProp);
}

BOOL IUI::WalkHWLWNDChild(HWLWND hWndParent, WalkHWLWNDCallBack fn, void *pCallbackParam)
{
	if (hWndParent == NULL)
	{
		return FALSE;
	}

	HWLWND hChild = GetWindow(hWndParent, GW_CHILD);

	while (hChild != NULL)
	{
#ifdef _DEBUG
		CIUIString str = GetName(hChild);
#endif // _DEBUG

		BOOL bRet = fn(hChild, pCallbackParam);
		if (bRet)
		{
			// ���ٱ�������ǰ����
			return TRUE;
		}

		bRet = WalkHWLWNDChild(hChild, fn, pCallbackParam);
		if (bRet)
		{
			// ������ǰ����
			return TRUE;
		}

		hChild = GetWindow(hChild, GW_HWNDNEXT);
	}

	return FALSE;
}
