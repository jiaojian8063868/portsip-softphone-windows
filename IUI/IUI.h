#pragma once

// ���Ҫ�����DLL���붨��IUI_AS_DLL��IUI_EXPORT��
#ifdef IUI_AS_DLL
#ifdef IUI_EXPORT
#define IUIAPI __declspec(dllexport)
#else
#define IUIAPI __declspec(dllimport)
#endif // IUI_EXPORT
#else
#define IUIAPI
#endif // IUI_AS_DLL

#pragma warning (disable : 4786)

#define UILIB_COMDAT __declspec(selectany)

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stddef.h>
#ifdef DEBUG_RICHEDIT
#include "Control/ControlCore/RichTextBox/RichEditInc/richedit.h"
#else // DEBUG_RICHEDIT
#include <richedit.h>
#endif // DEBUG_RICHEDIT
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>
#include <objbase.h>
#include <comutil.h>
#if(_MSC_VER > 1200) // VC6.0
#include <atlstr.h> // for CString
#include <atltypes.h> // for CRect
#endif
#include <CommDlg.h> // for color dialog

#include <GdiPlus.h>
#pragma comment( lib, "GdiPlus.lib" )

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>

#include <RichOle.h>
#include <Imm.h>
#pragma comment(lib,"imm32.lib")
#include <mshtmhst.h>

#ifdef DEBUG_RICHEDIT
#include "Control\ControlCore\RichTextBox\RichEditSrc\textserv.h"
#include "Control\ControlCore\RichTextBox\RichEditInc\tom.h"
#else
#include <TextServ.h>
#include <TOM.h>
#endif

#include <oleidl.h>
#include <MsHTML.h>
#include <MSHTMHST.H>
#include <EXDISP.H>
#include <Shlwapi.h>

// for parse xml
#if(_MSC_VER > 1200) // VC6.0
#import <msxml6.dll> rename_namespace("XML")
#else
#include <MsXml2.h>
#import <msxml3.dll> rename_namespace("XML")
#endif

namespace IUI
{
#if (_MSC_VER <= 1200) // VC6.0
#define LVN_INCREMENTALSEARCHA   (LVN_FIRST-62)
#define LVN_INCREMENTALSEARCHW   (LVN_FIRST-63)

#ifdef UNICODE
#define LVN_INCREMENTALSEARCH    LVN_INCREMENTALSEARCHW
#else
#define LVN_INCREMENTALSEARCH    LVN_INCREMENTALSEARCHA
#endif

#define LVFI_SUBSTRING          0x0004  // Same as LVFI_PARTIAL
#define LVNI_PREVIOUS           0x0020

#define OLEsprintf wsprintf

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

#define _TRUNCATE ((size_t)-1)

#ifndef _NTDEF_
	typedef __success(return >= 0) LONG NTSTATUS;
	typedef NTSTATUS *PNTSTATUS;
#endif

	typedef int (__cdecl *_PNH)(size_t);

	typedef int (CALLBACK *PFNDAENUMCALLBACK)(__in_opt void *p, __in_opt void *pData);
	typedef int (CALLBACK *PFNDACOMPARE)(__in_opt void *p1, __in_opt void *p2, __in LPARAM lParam);

#endif // (_MSC_VER <= 1200) // VC6.0

#ifdef _UNICODE
#define CIUIString CIUIStringW
#else
#define CIUIString CIUIStringA
#endif

	class CIUIProject;
	class CControlProp;
	class CWindowProp;
	class UIVARIANT;
	class CControlBaseProp;
	class CFontProp;
	class CColorProp;
	class CStringProp;
	class CIUIStringA;
	class CIUIStringW;
	class CIUIPoint;
	class CButtonProp;
	class CCheckBoxProp;
	class CRadioButtonProp;
	class CComboBoxProp;
	class CLabelProp;
	class CRichTextBoxProp;
	class CSliderProp;
	class CProgressBarProp;
	class CSpinButtonProp;
	class CListViewProp;
	class CTreeViewProp;
	class CHtmlViewProp;
	class CDateTimePickerProp;
	class CColumnHeaderProp;
	class CScrollBarProp;
	class CToolTipCtrlProp;

	struct RoutedEventArgs;
	struct HTMLV;

	typedef Gdiplus::Bitmap *HGPBITMAP;
	typedef class IUIImage *HIUIIMAGE;
	typedef class CIUIFont *HIUIFONT;
	typedef void *HTIMER;
	typedef struct WLWND *HWLWND;
	typedef DWORD BITBOOL;
	typedef std::map<CIUIString, HANDLE> *HPROPLIST;
#if(_MSC_VER <= 1200) // VC6.0
	typedef int errno_t;
#endif

	typedef LRESULT(WINAPI *fnWLEventHandler)(HWLWND, RoutedEventArgs *);

	//////////////////////////////////////////////////////////////////////////
	// macro

#define IUI_LABEL						_T("Label")
#define IUI_BUTTON						_T("Button")
#define IUI_RICHTEXTBOX					_T("RichTextBox")
#define IUI_IM							_T("IMRichTextBox")
#define IUI_COMBOBOX					_T("ComboBox")
#define IUI_COMBOLBOX					_T("IUICOMBOLBOX")
#define IUI_REPEATBUTTON				_T("RepeatButton")
#define IUI_PROGRESSBAR					_T("ProgressBar")
#define IUI_SLIDER						_T("Slider")
#define IUI_SCROLLBAR					_T("ScrollBar")
#define IUI_COLUMNHEADER				_T("ColumnHeader")
#define IUI_LISTVIEW					_T("ListView")
#define IUI_TREEVIEW					_T("TreeView")
#define IUI_HTMLVIEW					_T("HtmlView")
#define IUI_SPLITTERBAR					_T("SplitterBar")
#define IUI_DATETIMEPICKER				_T("DateTimePicker")
#define IUI_SPINBUTTON					_T("SpinButton")
#define IUI_CANVAS						_T("Canvas")
#define IUI_TABCONTROL					_T("TabControl")
#define IUI_DOCKPANEL					_T("DockPanel")
#define IUI_STACKPANEL					_T("StackPanel")
#define IUI_WINDOW						_T("Window")
#define IUI_TOOLTIPS					_T("ToolTipCtrl")

#define XNAME_HORZSCROLLBAR				_T("InternalHScrollBar")
#define XNAME_VERTSCROLLBAR				_T("InternalVScrollBar")
#define XNAME_COLUMNHEADER				_T("InternalColumnHeader")
#define XNAME_COMBOBOX_EDIT				_T("ComboBoxEdit_{9FFB7ACB-06F3-466d-A65E-5465D72724EE}")
#define XNAME_COMBOBOX_LISTVIEW			_T("ComboBoxListView_{133DEC15-D4A8-4601-A454-5DF5C095E110}")
#define XNAME_DATETIME_SPIN				_T("DateTimePickerSpin_{3B5D76DA-2613-4743-B3B1-358A51A32870}")


#define ISEDITMODE						_T("ISEDITMODE")

	// TODO: ��Щ�¼����п��ܺ��û�ʹ�õĵ��������ж������Ϣֵ��ͻ��
	// ����Ӧ���ṩһ�����ƣ���������IUI��Ϣ��Χ����ʼֵ�����߲���ע����Ϣ�ķ�ʽ�����
	// �Զ����¼���ʹ��UE��ͷ����ʾUI Event������ֵ���������Զ���windows��Ϣ��ͬ��
#define WM_UPDATEWINDOW					WM_USER+97 // ����UpdateLayeredWindow����ͨ����
#define WM_INIT							WM_USER+98 // IUI::CreateWindowEx����ǰ����
#define UE_GET_HANDLER					WM_USER+99
#define UE_SETCONTROLPROP				WM_USER+100
#define UE_BUTTON_CLICK					WM_USER+101
#define UE_BEFOREPAINT					WM_USER+102
#define UE_AFTERPAINT					WM_USER+103
#define UE_AFTERPAINTBKCOLOR			WM_USER+104
#define UE_AFTERPAINTBKIMAGE			WM_USER+105
#define UE_AFTERCHILDRENPAINT			WM_USER+106
#define UE_DRAW_BK_IMAGE				WM_USER+107
#define UE_CONTROL_STATE_CHANGING		WM_USER+108
#define UE_CONTROL_STATE_CHANGED		WM_USER+109
#define UE_SUBCLASSING					WM_USER+110
#define UE_SUBCLASSED					WM_USER+111
#define UE_SETCAPTURE					WM_USER+200
#define UE_DRAWTHUMBCOLOR				WM_USER+600
#define UE_DRAWTHUMBIMAGE				WM_USER+601
#define UE_TAB_SWITCHING				WM_USER+700
#define UE_TAB_SWITCHED					WM_USER+701
#define UE_PROPERTYSHEET_SHOW			WM_USER+702	// ֪ͨ���л���������ҳ
#define UE_PROPERTYSHEET_HIDE			WM_USER+703
#define UE_IE_REQUEST_URL				WM_USER+800
#define UE_IE_INVOKE					WM_USER+801

#ifndef WM_KICKIDLE
#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#endif

	// WM_QUERYCENTERWND define in mfc header <afxpriv.h>
#ifndef WM_QUERYCENTERWND
#define WM_QUERYCENTERWND   0x036B  // lParam = HWND to use as centering parent
#endif

	// ���û����á� �ڴ��ڵ�һ�ε���UpdateWindow֮���û��򴰿ڷ���WM_FIRST_SHOW��Ϣ
	// �������յ�WM_FIRST_SHOW��Ϣʱ��������һЩֻ�е�һ����ʾʱ��Ҫ�������顣
#define WM_FIRST_SHOW					WM_USER+775
#define WM_CONTROLEVENT					WM_USER+776	// 0x0708
#define WM_MENUDESTROY					WM_USER+777
#define WM_UIMENUCOMMAND				WM_USER+778
#define WM_INITUIMENUPOPUP				WM_USER+779
#define WM_SETWLFOCUS					WM_USER+780	// return old focus control, if -1, means failed.
#define WM_GETWLFOCUS					WM_USER+781
#define WM_WL_ISUSERECTF				WM_USER+785
#define WM_WL_GETRECTF					WM_USER+786
#define WM_SET_PROJECT					WM_USER+787
#define WM_GET_PROJECT					WM_USER+788
#define WM_GET_INTERNAL_ROOT			WM_USER+789
#define WM_GETCHILD						WM_USER+790
#define WM_GETORIGRECT					WM_USER+791
#define WM_SET_LAYOUT_MARGIN			WM_USER+792
#define WM_GET_LAYOUT_MARGIN			WM_USER+793
#define WM_SET_LAYOUT_INSET				WM_USER+794
#define WM_GET_LAYOUT_INSET				WM_USER+795
#define WM_SET_XML_RECT					WM_USER+796
#define WM_GET_XML_RECT					WM_USER+797
#define WM_SET_BK_COLOR					WM_USER+798
#define WM_GET_BK_COLOR					WM_USER+799
#define WM_SET_HORZ_LAYOUT_MODE			WM_USER+800
#define WM_GET_HORZ_LAYOUT_MODE			WM_USER+801
#define WM_SET_VERT_LAYOUT_MODE			WM_USER+802
#define WM_GET_VERT_LAYOUT_MODE			WM_USER+803
#define WM_CAPTURECHANGING				WM_USER+804
#define WM_SET_THICKFRAME				WM_USER+805
#define WM_GET_THICKFRAME				WM_USER+806
#define WM_SET_SHADOW_WINDOW			WM_USER+807
#define WM_GET_SHADOW_WINDOW			WM_USER+808
#define WM_SYNC_HOST_POS				WM_USER+809

#define LAYEREDUPDATE_TIMERID			0x2000

#define WLM_SET_BK_COLOR				WM_USER + 2000
#define WLM_GET_BK_COLOR				WM_USER + 2001
#define WLM_COMBINE_BK_IMAGE			WM_USER + 2002
#define WLM_IS_COMBINE_BK_IMAGE			WM_USER + 2003
#define WLM_SET_BK_IMAGE				WM_USER + 2004
#define WLM_GET_BK_IMAGE				WM_USER + 2005
#define WLM_COMBINE_FG_IMAGE			WM_USER + 2006
#define WLM_IS_COMBINE_FG_IMAGE			WM_USER + 2007
#define WLM_SET_FG_IMAGE				WM_USER + 2008
#define WLM_GET_FG_IMAGE				WM_USER + 2009
#define WLM_SET_BORDER_COLOR			WM_USER + 2010
#define WLM_GET_BORDER_COLOR			WM_USER + 2011
#define WLM_SET_TEXT_COLOR				WM_USER + 2012
#define WLM_GET_TEXT_COLOR				WM_USER + 2013
#define WLM_SET_TEXT_FONT				WM_USER + 2014
#define WLM_GET_TEXT_FONT				WM_USER + 2015
#define WLM_SET_CLIP					WM_USER + 2016
#define WLM_GET_CLIP					WM_USER + 2017
#define WLM_BIND_STYLE					WM_USER + 2018
#define WLM_SET_BIND_SCROLLBAR_STYLE	WM_USER + 2019
#define WLM_GET_BIND_SCROLLBAR_STYLE	WM_USER + 2020
#define WLM_SETTOOLTIPS					WM_USER + 2021
#define WLM_GETTOOLTIPS					WM_USER + 2022
#define WLM_HITTESTBINDITEM				WM_USER + 2023
	// ShowWindow�ڲ������ػ���ʾ�����������к������WLM_PARENTSHOWWINDOW��Ϣ����֪�����������ʾ״̬�ı仯��
#define WLM_PARENTSHOWWINDOW			WM_USER + 2024
	// EnableWindow�ڲ���ʹ�ܻ���ú����������к������WLM_PARENTENABLE��Ϣ����֪���������ʹ��״̬�ı仯��
#define WLM_PARENTENABLE				WM_USER + 2025

	// WPARAM: MAKEWPARAM(Is Vert, CONTROL_STATE), LPARAM: TEXT_ALIGN_HOR or TEXT_ALIGN_VER
#define WLM_SET_TEXT_ALIGN_MODE			WM_USER + 2050
	// WPARAM: MAKEWPARAM(Is Vert, CONTROL_STATE), return: TEXT_ALIGN_HOR or TEXT_ALIGN_VER
#define WLM_GET_TEXT_ALIGN_MODE			WM_USER + 2051
	// WPARAM: MAKEWPARAM(0, CONTROL_STATE), LPARAM: LPCRECT
#define WLM_SET_TEXT_MARGIN				WM_USER + 2052
	// WPARAM: MAKEWPARAM(0, CONTROL_STATE), LPARAM: LPRECT
#define WLM_GET_TEXT_MARGIN				WM_USER + 2053

	// �Ƿ�����ָ��Item����
#define WLM_ENABLE_SPEC_ITEM_EFFECT			WM_USER + 2054
#define WLM_IS_SPEC_ITEM_EFFECT_ENABLED		WM_USER + 2055
#define WLM_SET_SPEC_ITEM_BK_TYPE			WM_USER + 2056
#define WLM_GET_SPEC_ITEM_BK_TYPE			WM_USER + 2057

	struct ITEM_COLOR
	{
		enum CONTROL_STATE eControlState;
		COLORREF color;
	};
	// LPARAM: ITEM_COLOR*
#define WLM_SET_SPEC_ITEM_BK_COLOR			WM_USER + 2058
#define WLM_GET_SPEC_ITEM_BK_COLOR			WM_USER + 2059

	struct ITEM_IMAGE
	{
		enum CONTROL_STATE eControlState;
		LPCTSTR lpszImage;
	};
	// LPARAM: ITEM_IMAGE*
#define WLM_SET_SPEC_ITEM_BK_IMAGE			WM_USER + 2060
#define WLM_GET_SPEC_ITEM_BK_IMAGE			WM_USER + 2061

#define WLM_SET_SPEC_ITEM_BK_IMAGE_RESIZE_MODE	WM_USER + 2062
#define WLM_GET_SPEC_ITEM_BK_IMAGE_RESIZE_MODE	WM_USER + 2063
#define WLM_SET_SPEC_ITEM_BK_IMAGE_9GRID_ARG	WM_USER + 2064
#define WLM_GET_SPEC_ITEM_BK_IMAGE_9GRID_ARG	WM_USER + 2065
#define WLM_SET_SPEC_ITEM_TEXT_COLOR			WM_USER + 2066
#define WLM_GET_SPEC_ITEM_TEXT_COLOR			WM_USER + 2067

	// ���ؼ��󶨵�OLE����ʱ���ṩ��OLE����Ľ�����
	// ��OLE�������ʱ��ѯ�ʰ󶨵Ŀؼ��Ƿ���ӰOLE�߿�
#define WLM_SETHIDEOLEBORDER					WM_USER + 2068
#define WLM_GETHIDEOLEBORDER					WM_USER + 2069
	// ð��·��
#define UE_ISHIDEOLEBORDER						WM_USER + 2070
#define UE_IM_RESEND_MSG						WM_USER + 2071
#define UE_IM_SHOW_MORE_MSG						WM_USER + 2072

	// ���͸���Item�Ŀؼ�������ListView��TreeView��ComboBox���˵��ȣ�����Ϣ
#define ITEM_NORMAL 1
#define ITEM_HIGHLIGHT 2
#define ITEM_SELECTED 3
#define ITEM_FOCUS 4
	// ���ÿؼ�ͨ��Item����
	// ����������Ϣ��WPARAM = MAKEWPARAM(ITEM״̬ITEM_*���ؼ�״̬CONTROL_STATE)
#define WLM_SET_ITEM_BK_TYPE			WM_USER + 2102
#define WLM_GET_ITEM_BK_TYPE			WM_USER + 2103
#define WLM_SET_ITEM_BK_COLOR			WM_USER + 2104
#define WLM_GET_ITEM_BK_COLOR			WM_USER + 2105
#define WLM_SET_ITEM_BK_IMAGE			WM_USER + 2106
#define WLM_GET_ITEM_BK_IMAGE			WM_USER + 2107
#define WLM_SET_ITEM_BK_IMAGE_RESIZE_MODE WM_USER + 2108
#define WLM_GET_ITEM_BK_IMAGE_RESIZE_MODE WM_USER + 2109
#define WLM_SET_ITEM_BK_IMAGE_9GRID_ARG	WM_USER + 2110
#define WLM_GET_ITEM_BK_IMAGE_9GRID_ARG	WM_USER + 2111
#define WLM_SET_ITEM_TEXT_COLOR			WM_USER + 2112
#define WLM_GET_ITEM_TEXT_COLOR			WM_USER + 2113

	// for drag & drop
	enum DRAGDROP_TYPE
	{
		DDT_DRAGENTER = 1,
		DDT_DRAGOVER,
		DDT_DROP,
		DDT_DROPEX,
		DDT_DRAGLEAVE
	};
#define DDM_OLEDROPTARGET				WM_USER + 2999	// WPARAM: DRAGDROP_TYPE

	// for ComboBox
#define CBM_SET_EDIT_MARGIN				WM_USER + 3000
#define CBM_GET_EDIT_MARGIN				WM_USER + 3001

#define CBM_SET_BUTTON_WIDTH			WM_USER + 3002
#define CBM_GET_BUTTON_WIDTH			WM_USER + 3003
#define CBM_SET_BUTTON_MARGIN			WM_USER + 3004
#define CBM_GET_BUTTON_MARGIN			WM_USER + 3005

#define CBM_SET_DRAW_DROP_BUTTON_BK_COLOR	WM_USER + 3006
#define CBM_GET_DRAW_DROP_BUTTON_BK_COLOR	WM_USER + 3007
#define CBM_SET_DROP_BUTTON_BK_COLOR	WM_USER + 3008
#define CBM_GET_DROP_BUTTON_BK_COLOR	WM_USER + 3009

#define CBM_SET_DROP_BUTTON_BK_IMAGE	WM_USER + 3010
#define CBM_GET_DROP_BUTTON_BK_IMAGE	WM_USER + 3011

#define CBM_SET_DRAW_DROP_BUTTON_BORDER_COLOR	WM_USER + 3012
#define CBM_GET_DRAW_DROP_BUTTON_BORDER_COLOR	WM_USER + 3013
#define CBM_SET_DROP_BUTTON_BORDER_COLOR		WM_USER + 3014
#define CBM_GET_DROP_BUTTON_BORDER_COLOR		WM_USER + 3015
#define CBM_SET_DROP_HEIGHT						WM_USER + 3016
#define CBM_GET_DROP_HEIGHT						WM_USER + 3017
#define CBM_GETDROPPEDWND						WM_USER + 3018
#define CBM_SET_ITEM_BIND						WM_USER + 3019
#define CBM_GET_ITEM_BIND						WM_USER + 3020

	// for ListBox
#define LBCB_DROPHEIGHT_CHANGED			WM_USER + 3050
#define LB_SET_ITEM_BIND				WM_USER + 3051
#define LB_GET_ITEM_BIND				WM_USER + 3052
#define LB_SET_ITEM_BK_COLOR			WM_USER + 3053
#define LB_GET_ITEM_BK_COLOR			WM_USER + 3054

	// for Button
#define BM_SET_BUTTON_CLICK_ARG			WM_USER + 3500
#define BM_GET_BUTTON_CLICK_ARG			WM_USER + 3501
#define BM_SET_BUTTON_TYPE				WM_USER + 3502
#define BM_GET_BUTTON_TYPE				WM_USER + 3503
#define BM_SET_RADIOBUTTON_TYPE			WM_USER + 3506
#define BM_GET_RADIOBUTTON_TYPE			WM_USER + 3507
#define BM_SETTOOLTIPS					WM_USER + 3508

	// for RichTextBox
#define REM_GET_TEXT_SERVICES			WM_USER + 3700
#define REM_GET_TEXT_DOCUMENT			WM_USER + 3701
#define REM_GET_DC						WM_USER + 3702
#define REN_ADDED_CUSTOM_OLE			WM_USER + 3703
#define REM_ISIMCTRL					WM_USER + 3704
#define REM_ADD_GIF_OLE					WM_USER + 3705
#define REM_REVOKEDRAGDROP				WM_USER + 3706
#define REM_SET_DEFAULTPROC_HANDLE		WM_USER + 3707
#define REM_GET_DEFAULTPROC_HANDLE		WM_USER + 3708
	// for IMRichTextBox
#define ODT_IMQIPAO						13
#define ODT_IMRESENDBUTTON				14
#define ODT_IMFACE						15
#define IMM_INSERT_MSG					WM_USER + 3800
#define IMM_DELETE_MSG					WM_USER + 3801
#define IMM_SET_QIPAO					WM_USER + 3805
#define IMM_SET_QIPAO_9GRIDARG			WM_USER + 3806
#define IMM_GET_QIPAO					WM_USER + 3807
#define IMM_GET_QIPAO_9GRIDARG			WM_USER + 3808
#define IMM_SHOW_RESEND_BUTTON			WM_USER + 3809
#define IMM_IS_RESEND_BUTTON_VISIBLE	WM_USER + 3810
#define IMM_SET_RESENDBUTTON_MARGIN		WM_USER + 3811
#define IMM_GET_RESENDBUTTON_MARGIN		WM_USER + 3812
#define IMM_SET_RESENDBUTTON_SIZE		WM_USER + 3813
#define IMM_GET_RESENDBUTTON_SIZE		WM_USER + 3814
#define IMM_SET_RESENDBUTTON_STYLE		WM_USER + 3815
#define IMM_GET_RESENDBUTTON_STYLE		WM_USER + 3816
#define IMM_INSERT_SHOW_MORE_MSG		WM_USER + 3817
#define IMM_INSERT_LABEL				WM_USER + 3818
#define IMM_SET_SHOWMOREMSG_BUTTON_STYLE WM_USER + 3830
#define IMM_GET_SHOWMOREMSG_BUTTON_STYLE WM_USER + 3831

	// for TreeView
#define TVM_DRAWITEM					WM_USER + 6000	// LPARAM: DRAWTREEITEMSTRUCT *
#define TVM_GET_SMOOTH_VSCROLL			WM_USER + 6002
#define TVM_SET_FLOAT_SCROLLBAR			WM_USER + 6003
#define TVM_IS_FLOAT_SCROLLBAR			WM_USER + 6004
#define TVM_SETITEMHEIGHTEX				WM_USER + 6005
#define TVM_GET_HIGHLIGHT_ITEM			WM_USER + 6006
#define TVM_ENABLE_ITEM_LINE			WM_USER + 6007
#define TVM_IS_ENABLE_ITEM_LINE			WM_USER + 6008
#define TVM_SET_ITEM_LINE_COLOR			WM_USER + 6009
#define TVM_GET_ITEM_LINE_COLOR			WM_USER + 6010

	// ������������+-��ͼ��
	// WPARAM = MAKEWPARAM(�Ƿ�+��(��CONTROL_STATEΪCONTROL_STATE_COMBINEʱ������),CONTROL_STATE);
	// LPARAM = LPCTSTR(λͼ)
#define TVM_SET_INDENT_IMAGE			WM_USER + 6011
	// WPARAM = MAKEWPARAM(�Ƿ�+��,CONTROL_STATE);
	// return = LPCTSTR(λͼ)
#define TVM_GET_INDENT_IMAGE			WM_USER + 6012

#define TVM_SET_HOVER_TIME				WM_USER + 6026
#define TVM_GET_HOVER_TIME				WM_USER + 6027
#define TVM_SET_MOUSE_WHEEL_STEP		WM_USER + 6028
#define TVM_GET_MOUSE_WHEEL_STEP		WM_USER + 6029

#define TVN_HOTCHANGING					WM_USER + 6100
#define TVN_HOTCHANGED					WM_USER + 6101
#define TVM_MOVEITEM					WM_USER + 6102

	// for ListView
#define LVM_SETITEMHEIGHT				WM_USER + 6500
#define LVM_GETITEMHEIGHT				WM_USER + 6501
#define LVM_SETGRIDLINECOLOR			WM_USER + 6502
#define LVM_GETGRIDLINECOLOR			WM_USER + 6503
#define LVM_SETGRIDLINEOFFSET			WM_USER + 6504
#define LVM_GETGRIDLINEOFFSET			WM_USER + 6505
#define LVM_SETDRAWFIRSTROWLINE			WM_USER + 6506
#define LVM_ISDRAWFIRSTROWLINE			WM_USER + 6507
#define LVM_SETITEMHEADERSPACE			WM_USER + 6508
#define LVM_GETITEMHEADERSPACE			WM_USER + 6509
#define LVM_ENABLE_SELECTED_FIT_CLIENT	WM_USER + 6510
#define LVM_IS_SELECTED_FIT_CLIENT_ENABLED WM_USER + 6511
#define LVM_GET_HIGHLIGHT_ITEM			WM_USER + 6512

	// for Slider
#define TBM_SET_DRAW_THUMB_COLOR		WM_USER + 6700
#define TBM_GET_DRAW_THUMB_COLOR		WM_USER + 6701
#define TBM_SET_THUMB_BK_COLOR			WM_USER + 6702
#define TBM_GET_THUMB_BK_COLOR			WM_USER + 6703
#define TBM_SET_THUMB_BORDER_COLOR		WM_USER + 6704
#define TBM_GET_THUMB_BORDER_COLOR		WM_USER + 6705
#define TBM_COMBINE_THUMB_IMAGE			WM_USER + 6706
#define TBM_IS_COMBINE_THUMB_IMAGE		WM_USER + 6707
#define TBM_SET_THUMB_IMAGE				WM_USER + 6708
#define TBM_GET_THUMB_IMAGE				WM_USER + 6709
#define TBM_SETTHUMBWIDTH				WM_USER + 6710
#define TBM_GETTHUMBWIDTH				WM_USER + 6711
#define TBM_SET_SCROLL_AREA_MARGIN		WM_USER + 6712
#define TBM_GET_SCROLL_AREA_MARGIN		WM_USER + 6713

	// for ProgressBar
#define PBM_SET_DRAW_THUMB_COLOR		WM_USER + 6850
#define PBM_GET_DRAW_THUMB_COLOR		WM_USER + 6851
#define PBM_SET_THUMB_BK_COLOR			WM_USER + 6852
#define PBM_GET_THUMB_BK_COLOR			WM_USER + 6853
#define PBM_SET_THUMB_BODER_COLOR		WM_USER + 6854
#define PBM_GET_THUMB_BODER_COLOR		WM_USER + 6855

	// for ScrollBar
	// ���ù�������ť����ͼ��
	// WPARAM: MAKEWPARAM(Left/Top?0:1, CONTROL_STATE)
	// LPARAM: LPCTSTR lpszImage
#define SBM_SET_BUTTON_IMAGE			WM_USER + 7000
#define SBM_GET_BUTTON_IMAGE			WM_USER + 7001
	// ���ù�������ť��С
	// WPARAM: MAKEWPARAM(Left/Top?0:1, 0)
	// LPARAM: int nWidth
#define SBM_SET_BUTTON_LENGTH			WM_USER + 7002
#define SBM_GET_BUTTON_LENGTH			WM_USER + 7003
#define SBM_SET_THUMB_IMAGE				WM_USER + 7004
#define SBM_GET_THUMB_IMAGE				WM_USER + 7005
#define SBM_GETMINTHUMBLENGTH			WM_USER + 7006
#define SBM_SETMINTHUMBLENGTH			WM_USER + 7007
#define SBM_REFRSHSELF					WM_USER + 7008
#define SBM_ISREFRESHSELF				WM_USER + 7009

	// for ColumnHeader
	// ����Header�߶ȣ�������FilterBar�� ͨ��GetWindowRect�õ�Header�ĸ߶�
	// ֮���Բ�ͨ��MoveWindow������Header�߶�����ΪHeader�ĸ߶Ȼ�Ӱ��ListView Item��λ�á�
#define HDM_SETHEIGHT					WM_USER + 7300
#define HDM_COMBINE_BUTTON_BK_IMAGE		WM_USER + 7301
#define HDM_IS_COMBINE_BUTTON_BK_IMAGE	WM_USER + 7302
#define HDM_SET_BUTTON_BK_IMAGE			WM_USER + 7303
#define HDM_GET_BUTTON_BK_IMAGE			WM_USER + 7304
#define HDM_ENABLE_HEADER_TRACK			WM_USER + 7305
#define HDM_IS_HEADER_TRACK_ENABLED		WM_USER + 7306
#define HDM_ENABLE_HEADER_DRAG			WM_USER + 7307
#define HDM_IS_HEADER_DRAG_ENABLED		WM_USER + 7308

	// for SplitterBar
#define SPB_SET_CURSOR					WM_USER + 7400
#define SPB_GET_CURSOR					WM_USER + 7401
#define SPB_SET_ORIENTATION				WM_USER + 7402
#define SPB_GET_ORIENTATION				WM_USER + 7403
#define SPB_ADD_PANEL					WM_USER + 7404
#define SPB_GET_PANEL					WM_USER + 7405
#define SPB_REPLACE_PANEL				WM_USER + 7406
#define SPB_START_TRACKING				WM_USER + 7407
#define SPB_STOP_TRACKING				WM_USER + 7408
#define SPB_SET_OFFSET					WM_USER + 7409

	// for DockPanel
#define DPM_SET_LAST_CHILD_FILL			WM_USER + 7500
#define DPM_IS_LAST_CHILD_FILL			WM_USER + 7501

	// for StackPanel
#define SP_SET_DIRECTION				WM_USER + 7700
#define SP_GET_DIRECTION				WM_USER + 7701

	// for ToolTipCtrl
#define TTN_COOL_TOOLTIP_BUBBLE			(TTN_FIRST - 20)	// LPARAM: NMCOOLBUBBLE *

	// �û��Զ����¼�����UE_CUSTOM��ʼ
#define UE_CUSTOM						WM_USER+9000
#define WM_CUSTOM						UE_CUSTOM

	// error code
#define E_SETUIPATH						-200    // failed to set .iui path, it cause by the ui path isn't exists.
#define E_OLDERVERSION					-203    // the version of .iui file older than IUI.
#define E_NEWERVERSION					-204    // the version of .iui file newer than IUI.
#define E_NOROOTELEMENT					-211    // Failed to load the root element of *.iui.
#define E_NOWINDOWSNODE					-213    // Not found the 'Windows' node.
#define E_NOIUIRC						-216

#define E_INVALIDLICENSE 201   // invalid license
#define E_NOTUNICODE 202    // the .ui file not support unicode when you define _UNICODE or UNICODE micro.
#define E_CHANGELIST_NOTMATCH 205    // the change list in *.uixproj file not match the IUI library.
#define E_NOFILE 206    // û�д��ļ�
#define E_OLEUNINIT 210    // Not call ::OleInitialize
#define E_CANCELTRANSFERTONEWVERSION 212    // Cancel to transfer to new version of *.uixproj.
#define E_NOMENUSNODE 214    // Not found the 'Windows' node.
#define E_NORESOURCENODE 215    // Not found the 'Resource' node.
#define E_LOADXML 217    // Failed to load xml document.

#define IDC_STA_TOOLTIP                    _T("IDC_STA_TOOLTIP")

	// for TreeView
#define TVS_EX_SMOOTHVSCROLL	0x8000
#define TVIF_BINDWL				0x00008000

	// for ListView
#define LVIF_BINDWL				0x00008000

#define TTW_TIMEOUT						0x0001            // �����õ�ʱ�䵽�˵�ʱ������Tooltip
#define TTW_KILLFOCUS					0x0002            // ��Tooltip����ʧȥ����ʱ����
#define TTW_TIMEOUTKILLFOCUS			(TTW_TIMEOUT | TTW_KILLFOCUS)


#define ES_COMBOBOX				0x0200L

	// List box id of Combo box
#define CBLISTBOXID 1000

#define GRF_LEFT				0x0001
#define GRF_RIGHT				0x0002
#define GRF_TOP					0x0004
#define GRF_TOPLEFT				0x0008
#define GRF_TOPRIGHT			0x0010
#define GRF_BOTTOM				0x0020
#define GRF_BOTTOMLEFT			0x0040
#define GRF_BOTTOMRIGHT			0x0080
#define GRF_ALL					0x00FF

	// for slider
	// �д˷���Slider�������������󣬻���һ����λ��ֱ���ƶ�����괦
#define TBS_THUMBPOSITION       0x8000


	// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_ME_FIRST      0x80000000

	// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040

	// for pcbox->CBoxStyle
#define SDROPPABLE			2
#define SEDITABLE			1

#define SSIMPLE				SEDITABLE
#define SDROPDOWNLIST		SDROPPABLE
#define SDROPDOWN			(SDROPPABLE | SEDITABLE)

#define UPPERCASE 1
#define LOWERCASE 2

	/**
		@brief �˵���highlight��ʱ�򣬾�ѡ���ˣ�����highlight��selected��ͬһ��Ч����\n
		�����Selected����ʾ��갴��δ�ͷţ��˵���û������ԡ� ����GMTC_HIGNLIGHT��GMTC_SELECTED����һ������
	*/
#define GMTC_NORMAL				0x0001
#define GMTC_HIGNLIGHT			0x0002
#define GMTC_SELECTED			0x0004
#define GMTC_DISABLED			0x0008

#define ULVHT_NOWHERE			0x0001
#define ULVHT_ITEM				0x0002
#define ULVHT_CHECKBOX			0x0004

#define UILIST_MAX_COLUMNS		32
#define EVENT_TIEM_ID			100

#define TPM_ALTNODESTROY		0x100000L ///< for TrackPopupMenu, ����Alt�������ٲ˵�
#define TPM_RETURNNAME			0x200000L ///< for TrackPopupMenu, ���ص����item��name�ַ���

	//////////////////////////////////////////////////////////////////////////

#ifndef ENSURE
#define ENSURE(conf) \
	if (!(conf)) \
	{\
		_ASSERT(FALSE); \
		IUITRACE(_T("[IUI]===Error\n"));\
	}
#endif

#ifndef RECTWIDTH
#define RECTWIDTH(rc)   ((rc).right-(rc).left)
#endif

#ifndef RECTHEIGHT
#define RECTHEIGHT(rc)  ((rc).bottom-(rc).top)
#endif

#ifndef MAXINT
#define MAXUINT     ((UINT)~((UINT)0))
#define MAXINT      ((INT)(MAXUINT >> 1))
#define MININT      ((INT)~MAXINT)
#endif

	/////////////////////////////////////////////////////////////////////////////////////
#ifndef _ASSERT
#define _ASSERT(expr)  _ASSERTE(expr)
#endif

#ifndef VERIFY
#ifdef _DEBUG
#define VERIFY(f)          _ASSERT(f)
#else
#define VERIFY(f)          ((void)(f))
#endif // _DEBUG
#endif


#if (_MSC_VER <= 1200) // VC6.0

	// DPA_*
	typedef int (WINAPI *fnDPA_InsertPtr)(HDPA, int, void *);
	extern fnDPA_InsertPtr IUI_DPA_InsertPtr;

	typedef void *(WINAPI *fnDPA_DeletePtr)(HDPA, int);
	extern fnDPA_DeletePtr IUI_DPA_DeletePtr;

	typedef void *(WINAPI *fnDPA_GetPtr)(HDPA, int);
	extern fnDPA_GetPtr IUI_DPA_GetPtr;

	typedef BOOL (WINAPI *fnDPA_SetPtr)(HDPA, int, void *);
	extern fnDPA_SetPtr IUI_DPA_SetPtr;

	typedef void (WINAPI *fnDPA_EnumCallback)(HDPA, PFNDPAENUMCALLBACK, void *);
	extern fnDPA_EnumCallback IUI_DPA_EnumCallback;

	typedef BOOL (WINAPI *fnDPA_DeleteAllPtrs)(HDPA);
	extern fnDPA_DeleteAllPtrs IUI_DPA_DeleteAllPtrs;

	typedef void (WINAPI *fnDPA_DestroyCallback)(HDPA, PFNDPAENUMCALLBACK, void *);
	extern fnDPA_DestroyCallback IUI_DPA_DestroyCallback;

	typedef BOOL (WINAPI *fnDPA_Destroy)(HDPA);
	extern fnDPA_Destroy IUI_DPA_Destroy;

	typedef BOOL (WINAPI *fnDPA_Sort)(HDPA, PFNDPACOMPARE, LPARAM);
	extern fnDPA_Sort IUI_DPA_Sort;

	typedef HDPA(WINAPI *fnDPA_Create)(int);
	extern fnDPA_Create IUI_DPA_Create;

	typedef HDPA(WINAPI *fnDPA_CreateEx)(int, HANDLE);
	extern fnDPA_CreateEx IUI_DPA_CreateEx;

	typedef BOOL (WINAPI *fnDPA_Grow)(HDPA, int);
	extern fnDPA_Grow IUI_DPA_Grow;

	typedef HDPA(WINAPI *fnDPA_Clone)(const HDPA, HDPA);
	extern fnDPA_Clone IUI_DPA_Clone;

	typedef int (WINAPI *fnDPA_GetPtrIndex)(HDPA, const void *);
	extern fnDPA_GetPtrIndex IUI_DPA_GetPtrIndex;

	// DSA_*
	typedef BOOL (WINAPI *fnDSA_Destroy)(HDSA);
	extern fnDSA_Destroy IUI_DSA_Destroy;

	typedef void *(WINAPI *fnDSA_GetItemPtr)(HDSA, int);
	extern fnDSA_GetItemPtr IUI_DSA_GetItemPtr;

	typedef int (WINAPI *fnDSA_InsertItem)(HDSA, int, void *);
	extern fnDSA_InsertItem IUI_DSA_InsertItem;

	typedef HDSA(WINAPI *fnDSA_Create)(int, int);
	extern fnDSA_Create IUI_DSA_Create;

	typedef BOOL (WINAPI *fnDSA_GetItem)(HDSA, int, void *);
	extern fnDSA_GetItem IUI_DSA_GetItem;

	typedef BOOL (WINAPI *fnDSA_SetItem)(HDSA, int, void *);
	extern fnDSA_SetItem IUI_DSA_SetItem;

	typedef BOOL (WINAPI *fnDSA_DeleteItem)(HDSA, int);
	extern fnDSA_DeleteItem IUI_DSA_DeleteItem;

	typedef void (WINAPI *fnDSA_DestroyCallback)(HDSA, PFNDSAENUMCALLBACK, void *);
	extern fnDSA_DestroyCallback IUI_DSA_DestroyCallback;

	typedef void (* fnReleaseActCtx)(HANDLE);
	extern fnReleaseActCtx IUI_ReleaseActCtx;

	// subclass functions
	typedef BOOL (WINAPI *fnSetWindowSubclass)(HWND, SUBCLASSPROC, UINT_PTR, DWORD_PTR);
	extern fnSetWindowSubclass _SetWindowSubclass;
	BOOL IUIAPI IUI_SetWindowSubclass(
		HWND hWnd,
		SUBCLASSPROC pfnSubclass,
		UINT_PTR uIdSubclass,
		DWORD_PTR dwRefData
	);


	typedef BOOL (WINAPI *fnGetWindowSubclass)(HWND, SUBCLASSPROC, UINT_PTR, DWORD_PTR *);
	extern fnGetWindowSubclass _GetWindowSubclass;
	BOOL IUIAPI IUI_GetWindowSubclass(
		HWND hWnd,
		SUBCLASSPROC pfnSubclass,
		UINT_PTR uIdSubclass,
		DWORD_PTR *pdwRefData
	);

	typedef BOOL (WINAPI *fnRemoveWindowSubclass)(HWND, SUBCLASSPROC, UINT_PTR);
	extern fnRemoveWindowSubclass _RemoveWindowSubclass;
	BOOL IUIAPI IUI_RemoveWindowSubclass(
		HWND hWnd,
		SUBCLASSPROC pfnSubclass,
		UINT_PTR uIdSubclass
	);

	typedef LRESULT(WINAPI *fnDefSubclassProc)(HWND, UINT, WPARAM, LPARAM);
	extern fnDefSubclassProc IUI_DefSubclassProc;

#define DPA_GetPtrCount(hdpa)       (*(int *)(hdpa))
#define DPA_SetPtrCount(hdpa, cItems) (*(int *)(hdpa) = (cItems))
#define DPA_FastDeleteLastPtr(hdpa) (--*(int *)(hdpa))
#define DPA_GetPtrPtr(hdpa)         (*((void * **)((BYTE *)(hdpa) + sizeof(void *))))
#define DPA_FastGetPtr(hdpa, i)     (DPA_GetPtrPtr(hdpa)[i])
#define DPA_AppendPtr(hdpa, pitem)  IUI_DPA_InsertPtr(hdpa, DA_LAST, pitem)

#define DSA_GetItemCount(hdsa)      (*(int *)(hdsa))
#define DSA_AppendItem(hdsa, pitem) IUI_DSA_InsertItem(hdsa, DA_LAST, pitem)

#else // (_MSC_VER <= 1200) // VC6.0

#define IUI_DPA_InsertPtr DPA_InsertPtr
#define IUI_DPA_DeletePtr DPA_DeletePtr
#define IUI_DPA_Destroy DPA_Destroy
#define IUI_DPA_GetPtr DPA_GetPtr
#define IUI_DPA_SetPtr DPA_SetPtr
#define IUI_DPA_EnumCallback DPA_EnumCallback
#define IUI_DPA_DeleteAllPtrs DPA_DeleteAllPtrs
#define IUI_DPA_DestroyCallback DPA_DestroyCallback
#define IUI_DPA_Sort DPA_Sort
#define IUI_DPA_Create DPA_Create
#define IUI_DPA_CreateEx DPA_CreateEx
#define IUI_DPA_Grow DPA_Grow
#define IUI_DPA_Clone DPA_Clone
#define IUI_DPA_GetPtrIndex DPA_GetPtrIndex

#define IUI_DSA_Destroy DSA_Destroy
#define IUI_DSA_GetItemPtr DSA_GetItemPtr
#define IUI_DSA_InsertItem DSA_InsertItem
#define IUI_DSA_Create DSA_Create
#define IUI_DSA_GetItem DSA_GetItem
#define IUI_DSA_SetItem DSA_SetItem
#define IUI_DSA_DeleteItem DSA_DeleteItem
#define IUI_DSA_DestroyCallback DSA_DestroyCallback

#define IUI_ReleaseActCtx ReleaseActCtx

#define IUI_SetWindowSubclass SetWindowSubclass
#define IUI_GetWindowSubclass GetWindowSubclass
#define IUI_RemoveWindowSubclass RemoveWindowSubclass
#define IUI_DefSubclassProc DefSubclassProc

#endif // (_MSC_VER <= 1200) // VC6.0

#if defined(_UNICODE)

#ifndef _ATL_EX_CONVERSION_MACROS_ONLY

#if (_MSC_VER < 1800) // vs2013
	_Ret_z_ inline LPCOLESTR T2COLE(__in LPCTSTR lp)
	{
		return lp;
	}
	_Ret_z_ inline LPCTSTR OLE2CT(__in LPCOLESTR lp)
	{
		return lp;
	}
	_Ret_z_ inline LPOLESTR T2OLE(__in LPTSTR lp)
	{
		return lp;
	}
	_Ret_z_ inline LPTSTR OLE2T(__in LPOLESTR lp)
	{
		return lp;
	}
#endif // #if (_MSC_VER < 1800) // vs2013

#endif	 // _ATL_EX_CONVERSION_MACROS_ONLY

#else // !defined(_UNICODE)

#ifndef _ATL_EX_CONVERSION_MACROS_ONLY

#define T2COLE(lpa) A2CW(lpa)
#define T2OLE(lpa) A2W(lpa)
#define OLE2CT(lpo) W2CA(lpo)
#define OLE2T(lpo) W2A(lpo)

#endif	// _ATL_EX_CONVERSION_MACROS_ONLY

#endif // defined(_UNICODE)


#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif



	//////////////////////////////////////////////////////////////////////////
	// enum

	enum VARENUMEX
	{
		VT_EX_STRUCT_SIZE = VT_EMPTY + 1,
		VT_EX_CONTROL_ID_MACRO,
		VT_EX_CONTROL_ID,
		VT_EX_CONTROL_TYPE,
		VT_EX_RECT,
		VT_EX_RECT_WH, // Width and Height mode
		VT_EX_POINT,
		VT_EX_COLOR,
		VT_EX_FONT,
		VT_EX_BITMAPPATH,
		VT_EX_IMAGE_RESIZE_MODE,
		VT_EX_LAYOUT_HOR,
		VT_EX_LAYOUT_VER,
		VT_EX_DOCK,
		VT_EX_ROOT_LAYOUT_TYPE,
		VT_EX_TEXT_ALIGN_HOR,
		VT_EX_TEXT_ALIGN_VER,
		VT_EX_FOREGROUND_ALIGN_HOR,
		VT_EX_FOREGROUND_ALIGN_VER,
		VT_EX_BUTTON_TYPE,
		VT_EX_CHECKBOX_TYPE,
		VT_EX_WINDOW_TYPE,
		VT_EX_COMBOBOX_STYLE,
		VT_EX_SPN_ALIGN,
		VT_EX_SLD_EXT_STYLE,
		VT_EX_LST_STYLE,
		VT_EX_LST_ALIGN,
		VT_EX_LST_SORT,
		VT_EX_DATETIME_FORMAT,
		VT_EX_BACKGROUND_TYPE,
		VT_EX_PROGRESS_THUMB_MODE,
		VT_EX_PROGRESS_THUMB_POSITION,
		VT_EX_ALPHA_FORMAT,
		VT_EX_MENU_BORDER_STYLE,
		VT_EX_SPLITTER_ORIENTATION,
		VT_EX_PEN_STYLE,
		// Windows
		VT_EX_WINDOW_ID,
		VT_EX_WINDOW_ID_NOT_INCLUDE_SELF,
		//
		VT_EX_TASKMGR_ID,

		// Resource
		VT_EX_RESOURCE_FONT,
		VT_EX_RESOURCE_COLOR,
		// Style
		VT_EX_STYLE_PUSHBUTTON,
		VT_EX_STYLE_CHECK,
		VT_EX_STYLE_RADIO,
		VT_EX_STYLE_COMBOBOX,
		VT_EX_STYLE_STATIC,
		VT_EX_STYLE_RICHEDIT,
		VT_EX_STYLE_SLIDER,
		VT_EX_STYLE_PROGRESS,
		VT_EX_STYLE_SPIN,
		VT_EX_STYLE_HOTKEY,
		VT_EX_STYLE_IPADDRESS,
		VT_EX_STYLE_LISTCTRL,
		VT_EX_STYLE_TREECTRL,
		VT_EX_STYLE_TREELIST,
		VT_EX_STYLE_HTMLCTRL,
		VT_EX_STYLE_DATETIMECTRL,
		VT_EX_STYLE_MENU,
		VT_EX_STYLE_MENUBAR,
		VT_EX_STYLE_HEADERCTRL,
		VT_EX_STYLE_SCROLLBAR,
		VT_EX_STYLE_TOOLTIPS
	};

	enum CONTROL_TYPE
	{
		CT_ARROW,
		CT_PUSHBUTTON,
		CT_CHECK,
		CT_RADIO,
		CT_COMBOBOX,
		CT_STATIC,
		CT_RICHEDIT,
		CT_SLIDER,
		CT_PROGRESS,
		CT_SPIN,
		CT_HOTKEY,
		CT_IPADDRESS,
		CT_LISTVIEW,
		CT_TREEVIEW,
		CT_SCROLLBAR,
		CT_TREELIST,
		CT_HTMLVIEW,
		CT_IM,
		CT_DATETIMEPICKER,
		CT_MENU,
		CT_MENUBAR,
		CT_HEADERCTRL,
		CT_SPLITTER,
		// Panel
		CT_PNL_TABCONTROL,
		CT_PNL_CANVAS,
		CT_PNL_DOCK,
		CT_UNIFORM_GRID,
		CT_PNL_STACK,
		CT_PNL_TILE,

		CT_UIWND,

		// Resource
		CT_RESOURCE_DEFAULT_FONT,
		CT_RESOURCE_FONT,

		CT_RESOURCE_DEFAULT_COLOR,
		CT_RESOURCE_COLOR,

		CT_RESOURCE_STRING,

		// Style
		CT_STYLE_PUSHBUTTON,
		CT_STYLE_CHECK,
		CT_STYLE_RADIO,
		CT_STYLE_COMBOBOX,
		CT_STYLE_STATIC,
		CT_STYLE_RICHEDIT,
		CT_STYLE_SLIDER,
		CT_STYLE_PROGRESS,
		CT_STYLE_SPIN,
		CT_STYLE_HOTKEY,
		CT_STYLE_IPADDRESS,
		CT_STYLE_LISTCTRL,
		CT_STYLE_TREECTRL,
		CT_STYLE_TREELIST,
		CT_STYLE_HTMLCTRL,
		CT_STYLE_DATETIMECTRL,
		CT_STYLE_MENU,
		CT_STYLE_MENUBAR,
		CT_STYLE_HEADERCTRL,
		CT_STYLE_SCROLLBAR,
		CT_STYLE_TOOLTIPS,
		CT_STYLE_SPLITTER,
		CT_LAST
	};

	// text horizontal align mode
	enum TEXT_ALIGN_HOR
	{
		TAH_UNKNOWN = -1,
		TAH_LEFT = 1,
		TAH_RIGHT = 2,
		TAH_CENTER = 3,
	};

	// text vertical align mode
	enum TEXT_ALIGN_VER
	{
		TAV_UNKNOWN = -1,
		TAV_TOP = 1,
		TAV_BOTTOM = 2,
		TAV_CENTER = 3,
	};

	// foreground image horizontal align mode
	enum FOREGROUND_ALIGN_HOR
	{
		FAH_UNKNOWN = -1,
		FAH_CENTER,
		FAH_LEFT,
		FAH_RIGHT,
		FAH_STRETCH
	};

	// foreground image vertical align mode
	enum FOREGROUND_ALIGN_VER
	{
		FAV_UNKNOWN = -1,
		FAV_CENTER,
		FAV_TOP,
		FAV_BOTTOM,
		FAV_STRETCH
	};

	enum IMAGE_RESIZE_MODE
	{
		IRM_UNKNOWN,
		IRM_9GRID,
		IRM_STRETCH,
		IRM_STRETCH_HIGH_QUALITY,
		IRM_TILE,
		IRM_CENTER,
		IRM_KEEPRATE	// ���ź���ʾ�����ֳ����
	};

	enum ROOT_LAYOUT_TYPE
	{
		ROOT_LAYOUT_TYPE_UNKNOWN,
		ROOT_LAYOUT_TYPE_CANVAS,
		ROOT_LAYOUT_TYPE_VERT,
		ROOT_LAYOUT_TYPE_HORZ,
		ROOT_LAYOUT_TYPE_TAB
	};

	// Control horizontal layout mode
	enum CONTROL_LAYOUT_HOR
	{
		CLH_UNKNOWN = -1,
		CLH_LEFT,
		CLH_RIGHT,
		CLH_CENTER,
		CLH_FILL,
		CLH_FREE,
	};

	// Control vertical layout mode
	enum CONTROL_LAYOUT_VER
	{
		CLV_UNKNOWN = -1,
		CLV_TOP,
		CLV_BOTTOM,
		CLV_CENTER,
		CLV_FILL,
		CLV_FREE,
	};

	enum DOCK
	{
		DOCK_UNKNOWN = -1,
		DOCK_LEFT,
		DOCK_TOP,
		DOCK_RIGHT,
		DOCK_BOTTOM
	};

	enum BTN_TYPE
	{
		BT_UNKNOWN = -1,
		BT_NORMAL,
		BT_MINIMIZEBOX,
		BT_CLOSEBOX
	};

	enum CHK_TYPE
	{
		CT_UNKNOWN = -1,
		CT_NORMAL,
		CT_MAXIMIZEBOX = 3
	};

	enum WINDOW_TYPE
	{
		WT_UNKNOWN = -1,
		WT_NORMAL,
		WT_TOOLTIPS
	};

	enum CMB_STYLE
	{
		CS_UNKNOWN = -1,
		CS_SIMPLE = CBS_SIMPLE,
		CS_DROPDOWN = CBS_DROPDOWN,
		CS_DROPDOWNLIST = CBS_DROPDOWNLIST
	};

	enum SPN_ALIGN
	{
		SPNA_UNKNOWN = -1,
		SPNA_UNATTACHED = 0,
		SPNA_LEFT = 1,
		SPNA_RIGHT = 2
	};

	enum SLD_EXT_STYLE
	{
		SLDES_UNKNOWN = -1,
		SLDES_NORMAL = 0,
		SLDES_PROGRESS = 1,
		SLDES_SPLITPROGRESS = 2
	};

	enum LST_STYLE
	{
		LSTS_UNKNOWN = -1,
		LSTS_ICON = 0,
		LSTS_SMALLICON = 1,
		LSTS_LIST = 2,
		LSTS_REPORT = 3,
	};

	enum LST_ALIGN
	{
		LSTA_UNKNOWN = -1,
		LSTA_TOP = 0,
		LSTA_LEFT = 1
	};

	enum LST_SORT
	{
		LSTST_UNKNOWN = -1,
		LSTST_UNSET,
		LSTST_ASCENDING = 1,
		LSTST_DESCENDING = 2
	};

	enum DATETIME_FORMAT
	{
		DTF_UNKNOWN = -1,
		DTF_SHORT_DATE,
		DTF_LONG_DATE,
		DTF_TIME
	};

	enum BACKGROUND_TYPE
	{
		BKT_UNKNOWN = -1,
		BKT_IMAGE,
		BKT_COLOR
	};

	enum PROGRESS_THUMB_MODE
	{
		PTM_UNKNOWN = -1,
		PTM_STRETCH,
		PTM_TILE,
		PTM_CLIP
	};

	enum PROGRESS_THUMB_POSITION
	{
		PTP_UNKNOWN = -1,
		PTP_DEFAULT,        // The thumb area is default
		PTP_SPECIFIED        // The thumb area is specified, not from (0, 0)
	};

	enum ALPHA_FORMAT
	{
		AF_UNKNOWN = -1,
		AF_NONE,
		AF_AC_SRC_ALPHA
	};

	enum GRID_PANEL_UINT
	{
		GPU_UNKNOWN = -1,
		GPU_PIXEL,
		GPU_PERCENT
	};

	enum MENU_BORDER_STYLE
	{
		MBS_UNKNOWN = -1,
		MBS_NORMAL,            // has 3D-like border
		MBS_FLAT,            // has one pix border
		MBS_NONE            // has no border
	};

	enum STACK_PANEL_ORIENTATION
	{
		SPO_UNKNOWN = -1,
		SPO_LEFT,
		SPO_TOP,
		SPO_RIGHT,
		SPO_BOTTOM,
		SPO_CENTER,
		SPO_VCENTER
	};

	enum SPLITTER_ORIENTATION
	{
		SO_UNKNOWN = -1,
		SO_WE,    // West east,   <- | ->, the bar is vertical, can adjust the width of left and right panel.
		SO_NS    // North South. the bar is Horizontal, can adjust the height of up and down panel.
	};

	enum SPLITTER_DRAG_ORIENTATION
	{
		SDO_UNKNOWN = -1,
		SDO_LEFT,
		SDO_UP,
		SDO_RIGHT,
		SDO_DOWN
	};

	enum SPLITTER_PANEL_POS
	{
		SPP_UNKNOWN = -1,
		SPP_LEFT,            // Left panel
		SPP_TOP,            // Top panel
		SPP_RIGHT,            // Right panel
		SPP_BOTTOM            // Bottom panel
	};

	enum GRID_ELEMENT_ALIGN_HOR
	{
		GEAH_UNKNOWN = -1,
		GEAH_LEFT,
		GEAH_CENTER,
		GEAH_RIGHT,
		GEAH_STRETCH
	};

	enum GRID_ELEMENT_ALIGN_VER
	{
		GEAV_UNKNOWN = -1,
		GEAV_TOP,
		GEAV_CENTER,
		GEAV_BOTTOM,
		GEAV_STRETCH
	};

	enum GRID_ELEMENT_TYPE
	{
		GET_UNKNOWN = -1,
		GET_WINDOW,
		GET_PANEL
	};

	enum PANEL_ELEMENT_TYPE
	{
		PET_UNKNOWN = -1,
		PET_WINODW,
		PET_PANEL
	};

	//

	enum RESOURCE_TYPE
	{
		REST_FONT,
		REST_COLOR
	};

	enum STYLE_TYPE
	{
		STYLET_PUSHBUTTON,
		STYLET_CHECK,
		STYLET_RADIO,
		STYLET_COMBOBOX,
		STYLET_LABEL,
		STYLET_RICHEDIT,
		STYLET_SLIDER,
		STYLET_PROGRESS,
		STYLET_SPIN,
		STYLET_HOTKEY,
		STYLET_IPADDRESS,
		STYLET_SLIDEREX,
		STYLET_LISTCTRL,
		STYLET_TREECTRL,
		STYLET_TREELIST,
		STYLET_HTMLCTRL,
		STYLET_DATETIMECTRL,
		STYLET_MENU,
		STYLET_MENUBAR,
		STYLET_HEADERCTRL,
		STYLET_SCROLLBAR,
		STYLET_TOOLTIPS,
		STYLET_SPLITTER,
	};

	enum Direction
	{
		D_UNKNOWN,
		D_LEFT,
		D_TOP,
		D_RIGHT,
		D_BOTTOM
	};

	enum LINE_PEN_STYLE
	{
		LPS_UNKNOWN,
		LPS_SOLID = PS_SOLID,
		LPS_DASH = PS_DASH,
		LPS_DOT = PS_DOT,
		LPS_DASHDOT = PS_DASHDOT,
		LPS_DASHDOTDOT = PS_DASHDOTDOT,
		LPS_NULL = PS_NULL,
		LPS_INSIDEFRAME = PS_INSIDEFRAME,
		LPS_USERSTYLE = PS_USERSTYLE,
		LPS_ALTERNATE = PS_ALTERNATE,
	};

	enum DRAW_PARENT_PART
	{
		DPP_DRAW,
		DPP_NODRAW,
		DPP_AUTO
	};

	enum DOCK_STYLE
	{
		DS_NONE,
		DS_TOP,
		DS_BOTTOM,
		DS_LEFT,
		DS_RIGHT,
		DS_FILL
	};

	enum CLICK_COMMAND_TYPE
	{
		CCT_COMMAND,///< �����ͨ�˵���󣬷���WM_COMMAND��Ϣ
		CCT_DUIMESSAGE, ///<�����ͨ�˵���󣬷���DUI_MSGTYPE_MENUITEMCLICK֪ͨ
		CCT_UIMENUCOMMAND ///<�����ͨ�˵���󣬷���WM_UIMENUCOMMAND��Ϣ
	};

	enum IMAGE_STRETCH_MODE
	{
		IMAGE_STRETCH_MODE_NONE, ///< ������
		IMAGE_STRETCH_MODE_9GRID, ///< ʹ��9�����㷨����
		IMAGE_STRETCH_MODE_15GRID, ///< ʹ��15�����㷨����
		IMAGE_STRETCH_MODE_STRETCH, ///< ����ģʽ
		IMAGE_STRETCH_MODE_TILE ///< ƽ��ģʽ
	};

	enum UILIB_RESOURCETYPE
	{
		UILIB_FILE = 1,                // ���Դ����ļ�
		UILIB_ZIP,                        // ���Դ���zipѹ����
		UILIB_RESOURCE,            // ������Դ
		UILIB_ZIPRESOURCE,    // ������Դ��zipѹ����
	};

	enum ROUTINGSTRATEGY
	{
		RS_TUNNEL,	// ·���¼�ʹ��������ԣ��Ա��¼�ʵ��ͨ��������·�ɣ��Ӹ���ԴԪ�أ���
		RS_BUBBLE,	// ·���¼�ʹ��ð�ݲ��ԣ��Ա��¼�ʵ��ͨ��������·�ɣ����¼�Ԫ�ص�������
		RS_DIRECT
	};

	enum CONTROL_STATE
	{
		CONTROL_STATE_UNKNOWN = 0,
		CONTROL_STATE_NORMAL = 0x0001,
		CONTROL_STATE_HOVER = 0x0002,
		CONTROL_STATE_PRESSED = 0x0004,
		CONTROL_STATE_DISABLED = 0x0008,
		CONTROL_STATE_SELECTED = 0x0010, // Not checked
		CONTROL_STATE_FOCUS = 0x0020,
		CONTROL_STATE_COMBINE = 0x1000, // combine bk/fg
		CONTROL_STATE_ND = CONTROL_STATE_NORMAL | CONTROL_STATE_DISABLED,
		CONTROL_STATE_ALL = 0xFFFF
	};

	struct DRAWTREEITEMSTRUCT
	{
		UINT CtlType;
		UINT CtlID;
		HTREEITEM hItem;
		HWLWND hwndItem;
		HDC hDC;
		RECT rcItem;
	};

	struct NMCOOLBUBBLE
	{
		NMHDR hdr;
		RECT rc;
		BOOL fAllowFade;
		BOOL fAllowAnimate;
	};

	//////////////////////////////////////////////////////////////////////////
	// ����������

	class CWLWnd;
	typedef VOID (CALLBACK *WLTIMERPROC)(HWLWND hOwner, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	/////////////////////////////////////////////////////////////////////////////////////
	//
	class IUIAPI CIUISize : public tagSIZE
	{
	public:
		CIUISize();
		CIUISize(const SIZE &src);
		CIUISize(const RECT rc);
		CIUISize(int cx, int cy);
		CIUISize(POINT initPt);
		CIUISize(DWORD dwSize);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class IUIAPI CIUIRect : public tagRECT
	{
		// Constructors
	public:
		// uninitialized rectangle
		CIUIRect() throw();
		// from left, top, right, and bottom
		CIUIRect(int l, int t, int r, int b) throw();
		// copy constructor
		CIUIRect(const RECT &srcRect) throw();
		// from a pointer to another rect
		CIUIRect(LPCRECT lpSrcRect) throw();
		// from a point and size
		CIUIRect(POINT point, SIZE size) throw();
		// from two points
		CIUIRect(POINT topLeft, POINT bottomRight) throw();

		// Attributes (in addition to RECT members)

		// retrieves the width
		int Width() const throw();
		// returns the height
		int Height() const throw();
		// returns the size
		CIUISize Size() const throw();
		// reference to the top-left point
		CIUIPoint &TopLeft() throw();
		// reference to the bottom-right point
		CIUIPoint &BottomRight() throw();
		// const reference to the top-left point
		const CIUIPoint &TopLeft() const throw();
		// const reference to the bottom-right point
		const CIUIPoint &BottomRight() const throw();
		// the geometric center point of the rectangle
		CIUIPoint CenterPoint() const throw();
		// swap the left and right
		void SwapLeftRight() throw();
		static void SwapLeftRight(LPRECT lpRect) throw();

		// convert between CIUIRect and LPRECT/LPCRECT (no need for &)
		operator LPRECT() throw();
		operator LPCRECT() const throw();

		// returns TRUE if rectangle has no area
		BOOL IsRectEmpty() const throw();
		// returns TRUE if rectangle is at (0,0) and has no area
		BOOL IsRectNull() const throw();
		// returns TRUE if point is within rectangle
		BOOL PtInRect(POINT point) const throw();

		// Operations

		// set rectangle from left, top, right, and bottom
		void SetRect(int x1, int y1, int x2, int y2) throw();
		void SetRect(POINT topLeft, POINT bottomRight) throw();
		// empty the rectangle
		void SetRectEmpty() throw();
		// copy from another rectangle
		void CopyRect(LPCRECT lpSrcRect) throw();
		// TRUE if exactly the same as another rectangle
		BOOL EqualRect(LPCRECT lpRect) const throw();

		// Inflate rectangle's width and height by
		// x units to the left and right ends of the rectangle
		// and y units to the top and bottom.
		void InflateRect(int x, int y) throw();
		// Inflate rectangle's width and height by
		// size.cx units to the left and right ends of the rectangle
		// and size.cy units to the top and bottom.
		void InflateRect(SIZE size) throw();
		// Inflate rectangle's width and height by moving individual sides.
		// Left side is moved to the left, right side is moved to the right,
		// top is moved up and bottom is moved down.
		void InflateRect(LPCRECT lpRect) throw();
		void InflateRect(int l, int t, int r, int b) throw();

		// deflate the rectangle's width and height without
		// moving its top or left
		void DeflateRect(int x, int y) throw();
		void DeflateRect(SIZE size) throw();
		void DeflateRect(LPCRECT lpRect) throw();
		void DeflateRect(int l, int t, int r, int b) throw();

		// translate the rectangle by moving its top and left
		void OffsetRect(int x, int y) throw();
		void OffsetRect(SIZE size) throw();
		void OffsetRect(POINT point) throw();
		void NormalizeRect() throw();

		// absolute position of rectangle
		void MoveToY(int y) throw();
		void MoveToX(int x) throw();
		void MoveToXY(int x, int y) throw();
		void MoveToXY(POINT point) throw();

		// set this rectangle to intersection of two others
		BOOL IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2) throw();

		// set this rectangle to bounding union of two others
		BOOL UnionRect(LPCRECT lpRect1, LPCRECT lpRect2) throw();

		// set this rectangle to minimum of two others
		BOOL SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw();

		// Additional Operations
		void operator=(const RECT &srcRect) throw();
		BOOL operator==(const RECT &rect) const throw();
		BOOL operator!=(const RECT &rect) const throw();
		void operator+=(POINT point) throw();
		void operator+=(SIZE size) throw();
		void operator+=(LPCRECT lpRect) throw();
		void operator-=(POINT point) throw();
		void operator-=(SIZE size) throw();
		void operator-=(LPCRECT lpRect) throw();
		void operator&=(const RECT &rect) throw();
		void operator|=(const RECT &rect) throw();

		// Operators returning CIUIRect values
		CIUIRect operator+(POINT point) const throw();
		CIUIRect operator-(POINT point) const throw();
		CIUIRect operator+(SIZE size) const throw();
		CIUIRect operator-(SIZE size) const throw();
		CIUIRect operator+(LPCRECT lpRect) const throw();
		CIUIRect operator-(LPCRECT lpRect) const throw();
		CIUIRect operator&(const RECT &rect2) const throw();
		CIUIRect operator|(const RECT &rect2) const throw();
		CIUIRect MulDiv(int nMultiplier, int nDivisor) const throw();
		// �õ�ָ����߱ȵľ��ηŵ������о��к�����ߴ�ʱ�����꣬���ȱ�������ʱ�����ֵ
		// nWidth��nHeight������Ŀ����εĿ�߱ȡ�
		CIUIRect FitRect(int nWidth, int nHeight) const throw();
	};

	class IUIAPI CIUIPoint : public tagPOINT
	{
	public:
		// Constructors

		// create an uninitialized point
		CIUIPoint() throw();
		// create from two integers
		CIUIPoint(int initX, int initY) throw();
		// create from another point
		CIUIPoint(POINT initPt) throw();
		// create from a size
		CIUIPoint(SIZE initSize) throw();
		// create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
		CIUIPoint(LPARAM dwPoint) throw();


		// Operations

		// translate the point
		void Offset(int xOffset, int yOffset) throw();
		void Offset(POINT point) throw();
		void Offset(SIZE size) throw();
		void SetPoint(int X, int Y) throw();

		BOOL operator==(POINT point) const throw();
		BOOL operator!=(POINT point) const throw();
		void operator+=(SIZE size) throw();
		void operator-=(SIZE size) throw();
		void operator+=(POINT point) throw();
		void operator-=(POINT point) throw();

		// Operators returning CIUIPoint values
		CIUIPoint operator+(SIZE size) const throw();
		CIUIPoint operator-(SIZE size) const throw();
		CIUIPoint operator-() const throw();
		CIUIPoint operator+(POINT point) const throw();

		// Operators returning CIUISize values
		CIUISize operator-(POINT point) const throw();

		// Operators returning CIUIRect values
		CIUIRect operator+(const RECT *lpRect) const throw();
		CIUIRect operator-(const RECT *lpRect) const throw();
	};

#ifndef _OLEAUTO_H_
#ifdef OLE2ANSI
	typedef LPSTR BSTR;
#else
	typedef LPWSTR BSTR;// must (semantically) match typedef in oleauto.h
#endif
#endif

	struct CIUIStringDataA
	{
		long nRefs;             // reference count
		int nDataLength;        // length of data (including terminator)
		int nAllocLength;       // length of allocation
		// TCHAR data[nAllocLength]

		CHAR *data()           // TCHAR* to managed data
		{
			return (CHAR *)(this + 1);
		}
	};

	struct CIUIStringDataW
	{
		long nRefs;             // reference count
		int nDataLength;        // length of data (including terminator)
		int nAllocLength;       // length of allocation
		// TCHAR data[nAllocLength]

		WCHAR *data()           // TCHAR* to managed data
		{
			return (WCHAR *)(this + 1);
		}
	};

	struct _AFX_DOUBLE
	{
		BYTE doubleBits[sizeof(double)];
	};

#ifdef _X86_
#define DOUBLE_ARG  _AFX_DOUBLE
#else
#define DOUBLE_ARG  double
#endif

	class IUIAPI CIUIStringA
	{
	public:
		// Constructors

		// constructs empty CIUIStringA
		CIUIStringA();
		// copy constructor
		CIUIStringA(const CIUIStringA &stringSrc);
		// from a single character
		CIUIStringA(CHAR ch, int nRepeat = 1);
		// from an ANSI string (converts to CHAR)
		CIUIStringA(LPCSTR lpsz);
		// from a UNICODE string (converts to CHAR)
		CIUIStringA(LPCWSTR lpsz);
		// subset of characters from an ANSI string (converts to CHAR)
		CIUIStringA(LPCSTR lpch, int nLength);
		// subset of characters from a UNICODE string (converts to CHAR)
		CIUIStringA(LPCWSTR lpch, int nLength);
		// from unsigned characters
		CIUIStringA(const unsigned char *psz);

		// Attributes & Operations

		// get data length
		int GetLength() const;
		// TRUE if zero length
		BOOL IsEmpty() const;
		// clear contents to empty
		void Empty();

		// return single character at zero-based index
		CHAR GetAt(int nIndex) const;
		// return single character at zero-based index
		CHAR operator[](int nIndex) const;
		// set a single character at zero-based index
		void SetAt(int nIndex, CHAR ch);
		// return pointer to const string
		operator LPCSTR() const;

		// overloaded assignment

		// ref-counted copy from another CIUIStringA
		const CIUIStringA &operator=(const CIUIStringA &stringSrc);
		// set string content to single character
		const CIUIStringA &operator=(CHAR ch);
		// copy string content from ANSI string (converts to CHAR)
		const CIUIStringA &operator=(LPCSTR lpsz);
		// copy string content from UNICODE string (converts to CHAR)
		const CIUIStringA &operator=(LPCWSTR lpsz);
		// copy string content from unsigned chars
		const CIUIStringA &operator=(const unsigned char *psz);

		// string concatenation

		// concatenate from another CIUIStringA
		const CIUIStringA &operator+=(const CIUIStringA &string);

		// concatenate a single character
		const CIUIStringA &operator+=(CHAR ch);
		// concatenate a UNICODE character after converting it to CHAR
		const CIUIStringA &operator+=(LPCSTR lpsz);

		friend CIUIStringA IUIAPI operator+(const CIUIStringA &string1,
			const CIUIStringA &string2);
		friend CIUIStringA IUIAPI operator+(const CIUIStringA &string, CHAR ch);
		friend CIUIStringA IUIAPI operator+(CHAR ch, const CIUIStringA &string);
		friend CIUIStringA IUIAPI operator+(const CIUIStringA &string, LPCSTR lpsz);
		friend CIUIStringA IUIAPI operator+(LPCSTR lpsz, const CIUIStringA &string);

		// string comparison

		// straight character comparison
		int Compare(LPCSTR lpsz) const;
		// compare ignoring case
		int CompareNoCase(LPCSTR lpsz) const;
		// NLS aware comparison, case sensitive
		int Collate(LPCSTR lpsz) const;
		// NLS aware comparison, case insensitive
		int CollateNoCase(LPCSTR lpsz) const;

		// simple sub-string extraction

		// return nCount characters starting at zero-based nFirst
		CIUIStringA Mid(int nFirst, int nCount) const;
		// return all characters starting at zero-based nFirst
		CIUIStringA Mid(int nFirst) const;
		// return first nCount characters in string
		CIUIStringA Left(int nCount) const;
		// return nCount characters from end of string
		CIUIStringA Right(int nCount) const;

		//  characters from beginning that are also in passed string
		CIUIStringA SpanIncluding(LPCSTR lpszCharSet) const;
		// characters from beginning that are not also in passed string
		CIUIStringA SpanExcluding(LPCSTR lpszCharSet) const;

		// upper/lower/reverse conversion

		// NLS aware conversion to uppercase
		void MakeUpper();
		// NLS aware conversion to lowercase
		void MakeLower();
		// reverse string right-to-left
		void MakeReverse();

		// trimming whitespace (either side)

		// remove whitespace starting from right edge
		void TrimRight();
		// remove whitespace starting from left side
		void TrimLeft();

		// trimming anything (either side)

		// remove continuous occurrences of chTarget starting from right
		void TrimRight(CHAR chTarget);
		// remove continuous occcurrences of characters in passed string,
		// starting from right
		void TrimRight(LPCSTR lpszTargets);
		// remove continuous occurrences of chTarget starting from left
		void TrimLeft(CHAR chTarget);
		// remove continuous occcurrences of characters in
		// passed string, starting from left
		void TrimLeft(LPCSTR lpszTargets);

		// advanced manipulation

		// replace occurrences of chOld with chNew
		int Replace(CHAR chOld, CHAR chNew);
		// replace occurrences of substring lpszOld with lpszNew;
		// empty lpszNew removes instances of lpszOld
		int Replace(LPCSTR lpszOld, LPCSTR lpszNew);
		// remove occurrences of chRemove
		int Remove(CHAR chRemove);
		// insert character at zero-based index; concatenates
		// if index is past end of string
		int Insert(int nIndex, CHAR ch);
		// insert substring at zero-based index; concatenates
		// if index is past end of string
		int Insert(int nIndex, LPCSTR pstr);
		// delete nCount characters starting at zero-based index
		int Delete(int nIndex, int nCount = 1);

		// searching

		// find character starting at left, -1 if not found
		int Find(CHAR ch) const;
		// find character starting at right
		int ReverseFind(CHAR ch) const;
		// find character starting at zero-based index and going right
		int Find(CHAR ch, int nStart) const;
		// find first instance of any character in passed string
		int FindOneOf(LPCSTR lpszCharSet) const;
		// find first instance of substring
		int Find(LPCSTR lpszSub) const;
		// find first instance of substring starting at zero-based index
		int Find(LPCSTR lpszSub, int nStart) const;

		// simple formatting

		// printf-like formatting using passed string
		void Format(LPCSTR lpszFormat, ...);
		// printf-like formatting using referenced string resource
		void Format(UINT nFormatID, ...);
		// printf-like formatting using variable arguments parameter
		void FormatV(LPCSTR lpszFormat, va_list argList);

		// formatting for localization (uses FormatMessage API)

		// format using FormatMessage API on passed string
		void FormatMessage(LPCSTR lpszFormat, ...);
		// format using FormatMessage API on referenced string resource
		void FormatMessage(UINT nFormatID, ...);

		// input and output
		// #ifdef _DEBUG
		// 		friend CDumpContext &operator<<(CDumpContext &dc,
		// 			const CIUIStringA &string);
		// #endif
		// 		friend CArchive &operator<<(CArchive &ar, const CIUIStringA &string);
		// 		friend CArchive &operator>>(CArchive &ar, CIUIStringA &string);

		// load from string resource
		BOOL LoadString(UINT nID);

#ifndef _UNICODE
		// ANSI <-> OEM support (convert string in place)

		// convert string from ANSI to OEM in-place
		void AnsiToOem();
		// convert string from OEM to ANSI in-place
		void OemToAnsi();
#endif

#ifndef _AFX_NO_BSTR_SUPPORT
		// OLE BSTR support (use for OLE automation)

		// return a BSTR initialized with this CIUIStringA's data
		BSTR AllocSysString() const;
		// reallocates the passed BSTR, copies content of this CIUIStringA to it
		BSTR SetSysString(BSTR *pbstr) const;
#endif

		// Access to string implementation buffer as "C" character array

		// get pointer to modifiable buffer at least as long as nMinBufLength
		LPSTR GetBuffer(int nMinBufLength);
		// release buffer, setting length to nNewLength (or to first nul if -1)
		void ReleaseBuffer(int nNewLength = -1);
		// get pointer to modifiable buffer exactly as long as nNewLength
		LPSTR GetBufferSetLength(int nNewLength);
		// release memory allocated to but unused by string
		void FreeExtra();

		// Use LockBuffer/UnlockBuffer to turn refcounting off

		// turn refcounting back on
		LPSTR LockBuffer();
		// turn refcounting off
		void UnlockBuffer();

		// Implementation
	public:
		~CIUIStringA();
		int GetAllocLength() const;

	protected:
		LPSTR m_pchData;   // pointer to ref counted string data
		// ������ANSIʱ����Unicode�ַ�������Unicodeʱ����ANSI�ַ�����
#ifdef _UNICODE
		LPSTR m_pchDataConvert;
#else
		LPWSTR m_pchDataConvert;
#endif

		// implementation helpers
		CIUIStringDataA *GetData() const;
		void Init();
		void AllocCopy(CIUIStringA &dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
		void AllocBuffer(int nLen);
		void AssignCopy(int nSrcLen, LPCSTR lpszSrcData);
		void ConcatCopy(int nSrc1Len, LPCSTR lpszSrc1Data, int nSrc2Len, LPCSTR lpszSrc2Data);
		void ConcatInPlace(int nSrcLen, LPCSTR lpszSrcData);
		void CopyBeforeWrite();
		void AllocBeforeWrite(int nLen);
		void Release();
		static void PASCAL Release(CIUIStringDataA *pData);
		static int PASCAL SafeStrlen(LPCSTR lpsz);
		static void FreeData(CIUIStringDataA *pData);
	};

	class IUIAPI CIUIStringW
	{
	public:
		// Constructors

		// constructs empty CIUIStringW
		CIUIStringW();
		// copy constructor
		CIUIStringW(const CIUIStringW &stringSrc);
		// from a single character
		CIUIStringW(WCHAR ch, int nRepeat = 1);
		// from an ANSI string (converts to WCHAR)
		CIUIStringW(LPCSTR lpsz);
		// from a UNICODE string (converts to WCHAR)
		CIUIStringW(LPCWSTR lpsz);
		// subset of characters from an ANSI string (converts to WCHAR)
		CIUIStringW(LPCSTR lpch, int nLength);
		// subset of characters from a UNICODE string (converts to WCHAR)
		CIUIStringW(LPCWSTR lpch, int nLength);
		// from unsigned characters
		CIUIStringW(const unsigned char *psz);

		// Attributes & Operations

		// get data length
		int GetLength() const;
		// TRUE if zero length
		BOOL IsEmpty() const;
		// clear contents to empty
		void Empty();

		// return single character at zero-based index
		WCHAR GetAt(int nIndex) const;
		// return single character at zero-based index
		WCHAR operator[](int nIndex) const;
		// set a single character at zero-based index
		void SetAt(int nIndex, WCHAR ch);
		// return pointer to const string
		operator LPCWSTR() const;

		// overloaded assignment

		// ref-counted copy from another CIUIStringW
		const CIUIStringW &operator=(const CIUIStringW &stringSrc);
		// set string content to single character
		const CIUIStringW &operator=(WCHAR ch);
		const CIUIStringW &operator=(char ch);
		// copy string content from ANSI string (converts to WCHAR)
		const CIUIStringW &operator=(LPCSTR lpsz);
		// copy string content from UNICODE string (converts to WCHAR)
		const CIUIStringW &operator=(LPCWSTR lpsz);
		// copy string content from unsigned chars
		const CIUIStringW &operator=(const unsigned char *psz);

		// string concatenation

		// concatenate from another CIUIStringW
		const CIUIStringW &operator+=(const CIUIStringW &string);

		// concatenate a single character
		const CIUIStringW &operator+=(WCHAR ch);
		// concatenate an ANSI character after converting it to WCHAR
		const CIUIStringW &operator+=(char ch);
		// concatenate a UNICODE character after converting it to WCHAR
		const CIUIStringW &operator+=(LPCWSTR lpsz);

		friend CIUIStringW IUIAPI operator+(const CIUIStringW &string1,
			const CIUIStringW &string2);
		friend CIUIStringW IUIAPI operator+(const CIUIStringW &string, WCHAR ch);
		friend CIUIStringW IUIAPI operator+(WCHAR ch, const CIUIStringW &string);
		friend CIUIStringW IUIAPI operator+(const CIUIStringW &string, LPCWSTR lpsz);
		friend CIUIStringW IUIAPI operator+(LPCWSTR lpsz, const CIUIStringW &string);
		friend CIUIStringW IUIAPI operator+(const CIUIStringW &string, char ch);
		friend CIUIStringW IUIAPI operator+(char ch, const CIUIStringW &string);

		// string comparison

		// straight character comparison
		int Compare(LPCWSTR lpsz) const;
		// compare ignoring case
		int CompareNoCase(LPCWSTR lpsz) const;
		// NLS aware comparison, case sensitive
		int Collate(LPCWSTR lpsz) const;
		// NLS aware comparison, case insensitive
		int CollateNoCase(LPCWSTR lpsz) const;

		// simple sub-string extraction

		// return nCount characters starting at zero-based nFirst
		CIUIStringW Mid(int nFirst, int nCount) const;
		// return all characters starting at zero-based nFirst
		CIUIStringW Mid(int nFirst) const;
		// return first nCount characters in string
		CIUIStringW Left(int nCount) const;
		// return nCount characters from end of string
		CIUIStringW Right(int nCount) const;

		//  characters from beginning that are also in passed string
		CIUIStringW SpanIncluding(LPCWSTR lpszCharSet) const;
		// characters from beginning that are not also in passed string
		CIUIStringW SpanExcluding(LPCWSTR lpszCharSet) const;

		// upper/lower/reverse conversion

		// NLS aware conversion to uppercase
		void MakeUpper();
		// NLS aware conversion to lowercase
		void MakeLower();
		// reverse string right-to-left
		void MakeReverse();

		// trimming whitespace (either side)

		// remove whitespace starting from right edge
		void TrimRight();
		// remove whitespace starting from left side
		void TrimLeft();

		// trimming anything (either side)

		// remove continuous occurrences of chTarget starting from right
		void TrimRight(WCHAR chTarget);
		// remove continuous occcurrences of characters in passed string,
		// starting from right
		void TrimRight(LPCWSTR lpszTargets);
		// remove continuous occurrences of chTarget starting from left
		void TrimLeft(WCHAR chTarget);
		// remove continuous occcurrences of characters in
		// passed string, starting from left
		void TrimLeft(LPCWSTR lpszTargets);

		// advanced manipulation

		// replace occurrences of chOld with chNew
		int Replace(WCHAR chOld, WCHAR chNew);
		// replace occurrences of substring lpszOld with lpszNew;
		// empty lpszNew removes instances of lpszOld
		int Replace(LPCWSTR lpszOld, LPCWSTR lpszNew);
		// remove occurrences of chRemove
		int Remove(WCHAR chRemove);
		// insert character at zero-based index; concatenates
		// if index is past end of string
		int Insert(int nIndex, WCHAR ch);
		// insert substring at zero-based index; concatenates
		// if index is past end of string
		int Insert(int nIndex, LPCWSTR pstr);
		// delete nCount characters starting at zero-based index
		int Delete(int nIndex, int nCount = 1);

		// searching

		// find character starting at left, -1 if not found
		int Find(WCHAR ch) const;
		// find character starting at right
		int ReverseFind(WCHAR ch) const;
		// find character starting at zero-based index and going right
		int Find(WCHAR ch, int nStart) const;
		// find first instance of any character in passed string
		int FindOneOf(LPCWSTR lpszCharSet) const;
		// find first instance of substring
		int Find(LPCWSTR lpszSub) const;
		// find first instance of substring starting at zero-based index
		int Find(LPCWSTR lpszSub, int nStart) const;

		// simple formatting

		// printf-like formatting using passed string
		void Format(LPCWSTR lpszFormat, ...);
		// printf-like formatting using referenced string resource
		void Format(UINT nFormatID, ...);
		// printf-like formatting using variable arguments parameter
		void FormatV(LPCWSTR lpszFormat, va_list argList);

		// formatting for localization (uses FormatMessage API)

		// format using FormatMessage API on passed string
		void FormatMessage(LPCWSTR lpszFormat, ...);
		// format using FormatMessage API on referenced string resource
		void FormatMessage(UINT nFormatID, ...);

		// input and output
		// #ifdef _DEBUG
		// 		friend CDumpContext &operator<<(CDumpContext &dc,
		// 			const CIUIStringW &string);
		// #endif
		// 		friend CArchive &operator<<(CArchive &ar, const CIUIStringW &string);
		// 		friend CArchive &operator>>(CArchive &ar, CIUIStringW &string);

		// load from string resource
		BOOL LoadString(UINT nID);

#ifndef _UNICODE
		// ANSI <-> OEM support (convert string in place)

		// convert string from ANSI to OEM in-place
		void AnsiToOem();
		// convert string from OEM to ANSI in-place
		void OemToAnsi();
#endif

#ifndef _AFX_NO_BSTR_SUPPORT
		// OLE BSTR support (use for OLE automation)

		// return a BSTR initialized with this CIUIStringW's data
		BSTR AllocSysString() const;
		// reallocates the passed BSTR, copies content of this CIUIStringW to it
		BSTR SetSysString(BSTR *pbstr) const;
#endif

		// Access to string implementation buffer as "C" character array

		// get pointer to modifiable buffer at least as long as nMinBufLength
		LPWSTR GetBuffer(int nMinBufLength);
		// release buffer, setting length to nNewLength (or to first nul if -1)
		void ReleaseBuffer(int nNewLength = -1);
		// get pointer to modifiable buffer exactly as long as nNewLength
		LPWSTR GetBufferSetLength(int nNewLength);
		// release memory allocated to but unused by string
		void FreeExtra();

		// Use LockBuffer/UnlockBuffer to turn refcounting off

		// turn refcounting back on
		LPWSTR LockBuffer();
		// turn refcounting off
		void UnlockBuffer();

		// Implementation
	public:
		~CIUIStringW();
		int GetAllocLength() const;

	protected:
		LPWSTR m_pchData;   // pointer to ref counted string data
		// ������ANSIʱ����Unicode�ַ�������Unicodeʱ����ANSI�ַ�����
#ifdef _UNICODE
		LPSTR m_pchDataConvert;
#else
		LPWSTR m_pchDataConvert;
#endif

		// implementation helpers
		CIUIStringDataW *GetData() const;
		void Init();
		void AllocCopy(CIUIStringW &dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
		void AllocBuffer(int nLen);
		void AssignCopy(int nSrcLen, LPCWSTR lpszSrcData);
		void ConcatCopy(int nSrc1Len, LPCWSTR lpszSrc1Data, int nSrc2Len, LPCWSTR lpszSrc2Data);
		void ConcatInPlace(int nSrcLen, LPCWSTR lpszSrcData);
		void CopyBeforeWrite();
		void AllocBeforeWrite(int nLen);
		void Release();
		static void PASCAL Release(CIUIStringDataW *pData);
		static int PASCAL SafeStrlen(LPCWSTR lpsz);
		static void FreeData(CIUIStringDataW *pData);
	};


	CIUIStringA IUIAPI operator+(const CIUIStringA &string1, const CIUIStringA &string2);
	CIUIStringA IUIAPI operator+(const CIUIStringA &string, CHAR ch);
	CIUIStringA IUIAPI operator+(CHAR ch, const CIUIStringA &string);
	CIUIStringA IUIAPI operator+(const CIUIStringA &string, LPCSTR lpsz);
	CIUIStringA IUIAPI operator+(LPCSTR lpsz, const CIUIStringA &string);

	CIUIStringW IUIAPI operator+(const CIUIStringW &string1, const CIUIStringW &string2);
	CIUIStringW IUIAPI operator+(const CIUIStringW &string, WCHAR ch);
	CIUIStringW IUIAPI operator+(WCHAR ch, const CIUIStringW &string);
	CIUIStringW IUIAPI operator+(const CIUIStringW &string, LPCWSTR lpsz);
	CIUIStringW IUIAPI operator+(LPCWSTR lpsz, const CIUIStringW &string);

	bool IUIAPI operator==(const CIUIStringA &s1, const CIUIStringA &s2);
	bool IUIAPI operator==(const CIUIStringA &s1, LPCSTR s2);
	bool IUIAPI operator==(LPCSTR s1, const CIUIStringA &s2);
	bool IUIAPI operator!=(const CIUIStringA &s1, const CIUIStringA &s2);
	bool IUIAPI operator!=(const CIUIStringA &s1, LPCSTR s2);
	bool IUIAPI operator!=(LPCSTR s1, const CIUIStringA &s2);
	bool IUIAPI operator<(const CIUIStringA &s1, const CIUIStringA &s2);
	bool IUIAPI operator<(const CIUIStringA &s1, LPCSTR s2);
	bool IUIAPI operator<(LPCSTR s1, const CIUIStringA &s2);
	bool IUIAPI operator>(const CIUIStringA &s1, const CIUIStringA &s2);
	bool IUIAPI operator>(const CIUIStringA &s1, LPCSTR s2);
	bool IUIAPI operator>(LPCSTR s1, const CIUIStringA &s2);
	bool IUIAPI operator<=(const CIUIStringA &s1, const CIUIStringA &s2);
	bool IUIAPI operator<=(const CIUIStringA &s1, LPCSTR s2);
	bool IUIAPI operator<=(LPCSTR s1, const CIUIStringA &s2);
	bool IUIAPI operator>=(const CIUIStringA &s1, const CIUIStringA &s2);
	bool IUIAPI operator>=(const CIUIStringA &s1, LPCSTR s2);
	bool IUIAPI operator>=(LPCSTR s1, const CIUIStringA &s2);

	bool IUIAPI operator==(const CIUIStringW &s1, const CIUIStringW &s2);
	bool IUIAPI operator==(const CIUIStringW &s1, LPCWSTR s2);
	bool IUIAPI operator==(LPCWSTR s1, const CIUIStringW &s2);
	bool IUIAPI operator!=(const CIUIStringW &s1, const CIUIStringW &s2);
	bool IUIAPI operator!=(const CIUIStringW &s1, LPCWSTR s2);
	bool IUIAPI operator!=(LPCWSTR s1, const CIUIStringW &s2);
	bool IUIAPI operator<(const CIUIStringW &s1, const CIUIStringW &s2);
	bool IUIAPI operator<(const CIUIStringW &s1, LPCWSTR s2);
	bool IUIAPI operator<(LPCWSTR s1, const CIUIStringW &s2);
	bool IUIAPI operator>(const CIUIStringW &s1, const CIUIStringW &s2);
	bool IUIAPI operator>(const CIUIStringW &s1, LPCWSTR s2);
	bool IUIAPI operator>(LPCWSTR s1, const CIUIStringW &s2);
	bool IUIAPI operator<=(const CIUIStringW &s1, const CIUIStringW &s2);
	bool IUIAPI operator<=(const CIUIStringW &s1, LPCWSTR s2);
	bool IUIAPI operator<=(LPCWSTR s1, const CIUIStringW &s2);
	bool IUIAPI operator>=(const CIUIStringW &s1, const CIUIStringW &s2);
	bool IUIAPI operator>=(const CIUIStringW &s1, LPCWSTR s2);
	bool IUIAPI operator>=(LPCWSTR s1, const CIUIStringW &s2);

	// Globals
	extern CHAR iuiChNilA;
	extern LPCSTR _iuiPchNilA;
#define iuiEmptyStringA ((CIUIStringA&)*(CIUIStringA*)&_iuiPchNilA)

	// Globals
	extern WCHAR iuiChNilW;
	extern LPCWSTR _iuiPchNilW;
#define iuiEmptyStringW ((CIUIStringW&)*(CIUIStringW*)&_iuiPchNilW)


	typedef const VARIANT *LPCVARIANT;

	class IUIAPI CIUIOleVariant : public tagVARIANT
	{
		// Constructors
	public:
		CIUIOleVariant();

		CIUIOleVariant(const VARIANT &varSrc);
		CIUIOleVariant(LPCVARIANT pSrc);
		CIUIOleVariant(const CIUIOleVariant &varSrc);

		CIUIOleVariant(LPCTSTR lpszSrc);
		CIUIOleVariant(LPCTSTR lpszSrc, VARTYPE vtSrc); // used to set to ANSI string
		CIUIOleVariant(CIUIString &strSrc);

		CIUIOleVariant(BYTE nSrc);
		CIUIOleVariant(short nSrc, VARTYPE vtSrc = VT_I2);
		CIUIOleVariant(long lSrc, VARTYPE vtSrc = VT_I4);
		// CIUIOleVariant(const COleCurrency &curSrc);

#if (_WIN32_WINNT >= 0x0501) || defined(_ATL_SUPPORT_VT_I8)
		CIUIOleVariant(LONGLONG nSrc);
		CIUIOleVariant(ULONGLONG nSrc);
#endif

		CIUIOleVariant(float fltSrc);
		CIUIOleVariant(double dblSrc);
		//CIUIOleVariant(const COleDateTime &timeSrc);

		//CIUIOleVariant(const CByteArray &arrSrc);
		//CIUIOleVariant(const CLongBinary &lbSrc);

		CIUIOleVariant(LPCITEMIDLIST pidl);

		// Operations
	public:
		void Clear();
		void ChangeType(VARTYPE vartype, LPVARIANT pSrc = NULL);
		void Attach(VARIANT &varSrc);
		VARIANT Detach();
		//void GetByteArrayFromVariantArray(CByteArray &bytes);

		BOOL operator==(const VARIANT &varSrc) const;
		BOOL operator==(LPCVARIANT pSrc) const;

		const CIUIOleVariant &operator=(const VARIANT &varSrc);
		const CIUIOleVariant &operator=(LPCVARIANT pSrc);
		const CIUIOleVariant &operator=(const CIUIOleVariant &varSrc);

		const CIUIOleVariant &operator=(const LPCTSTR lpszSrc);
		const CIUIOleVariant &operator=(const CIUIString &strSrc);

		const CIUIOleVariant &operator=(BYTE nSrc);
		const CIUIOleVariant &operator=(short nSrc);
		const CIUIOleVariant &operator=(long lSrc);
		//const CIUIOleVariant &operator=(const COleCurrency &curSrc);

#if (_WIN32_WINNT >= 0x0501) || defined(_ATL_SUPPORT_VT_I8)
		const CIUIOleVariant &operator=(LONGLONG nSrc);
		const CIUIOleVariant &operator=(ULONGLONG nSrc);
#endif

		const CIUIOleVariant &operator=(float fltSrc);
		const CIUIOleVariant &operator=(double dblSrc);
		//const CIUIOleVariant &operator=(const COleDateTime &dateSrc);

		//const CIUIOleVariant &operator=(const CByteArray &arrSrc);
		//const CIUIOleVariant &operator=(const CLongBinary &lbSrc);

		void SetString(LPCTSTR lpszSrc, VARTYPE vtSrc); // used to set ANSI string

		operator LPVARIANT();
		operator LPCVARIANT() const;

		// Implementation
	public:
		~CIUIOleVariant();
	};

	///////////////////////////////////////////////////////////////////////////

	typedef const SAFEARRAY *LPCSAFEARRAY;

	class IUIAPI COleSafeArray : public tagVARIANT
	{
		//Constructors
	public:
		COleSafeArray();
		COleSafeArray(const SAFEARRAY &saSrc, VARTYPE vtSrc);
		COleSafeArray(LPCSAFEARRAY pSrc, VARTYPE vtSrc);
		COleSafeArray(const COleSafeArray &saSrc);
		COleSafeArray(const VARIANT &varSrc);
		COleSafeArray(LPCVARIANT pSrc);
		//COleSafeArray(const CIUIOleVariant &varSrc);

		// Operations
	public:
		void Clear();
		void Attach(VARIANT &varSrc);
		VARIANT Detach();

		COleSafeArray &operator=(const COleSafeArray &saSrc);
		COleSafeArray &operator=(const VARIANT &varSrc);
		COleSafeArray &operator=(LPCVARIANT pSrc);
		//COleSafeArray &operator=(const CIUIOleVariant &varSrc);

		BOOL operator==(const SAFEARRAY &saSrc) const;
		BOOL operator==(LPCSAFEARRAY pSrc) const;
		BOOL operator==(const COleSafeArray &saSrc) const;
		BOOL operator==(const VARIANT &varSrc) const;
		BOOL operator==(LPCVARIANT pSrc) const;
		//BOOL operator==(const CIUIOleVariant &varSrc) const;

		operator LPVARIANT();
		operator LPCVARIANT() const;

		// One dim array helpers
		void CreateOneDim(VARTYPE vtSrc, DWORD dwElements,
			const void *pvSrcData = NULL, long nLBound = 0);
		DWORD GetOneDimSize();
		void ResizeOneDim(DWORD dwElements);

		// Multi dim array helpers
		void Create(VARTYPE vtSrc, DWORD dwDims, DWORD *rgElements);

		// SafeArray wrapper classes
		void Create(VARTYPE vtSrc, DWORD dwDims, SAFEARRAYBOUND *rgsabounds);
		void AccessData(void **ppvData);
		void UnaccessData();
		void AllocData();
		void AllocDescriptor(DWORD dwDims);
		void Copy(LPSAFEARRAY *ppsa);
		void GetLBound(DWORD dwDim, long *pLBound);
		void GetUBound(DWORD dwDim, long *pUBound);
		void GetElement(long *rgIndices, void *pvData);
		void PtrOfIndex(long *rgIndices, void **ppvData);
		void PutElement(long *rgIndices, void *pvData);
		void Redim(SAFEARRAYBOUND *psaboundNew);
		void Lock();
		void Unlock();
		DWORD GetDim();
		DWORD GetElemSize();
		void Destroy();
		void DestroyData();
		void DestroyDescriptor();

		//void GetByteArray(CByteArray &bytes);

		// Implementation
	public:
		~COleSafeArray();

		// Cache info to make element access (operator []) faster
		DWORD m_dwElementSize;
		DWORD m_dwDims;
	};

	//////////////////////////////////////////////////////////////////////////
	// Image

	class CImageMgr
	{
	public:
		CImageMgr();
		~CImageMgr();

	public:
		std::map<CIUIString, HIUIIMAGE> m_mapImages;
	};

	//////////////////////////////////////////////////////////////////////////
	// Font

	class CFontMgr
	{
	public:
		CFontMgr();
		~CFontMgr();

	public:
		HIUIFONT GetDefaultFont() const;

	public:
		std::map<CIUIString, HIUIFONT> m_mapFonts;
	};

	//////////////////////////////////////////////////////////////////////////

	typedef enum FILTER_TYPE
	{
		FILTER_TYPE_ROOT = 0, ///< ��ʾ��Filter
		FILTER_TYPE_FILTER ///< ��ͨfilter
	} FILTER_TYPE;

	/**
	 @struct CProjectFilter
	 @brief ����Filter��
	 @details ��������Ҳ��һ��Root filter
	 @author (Liusw), liusw
	 @date 2016/10/14 10:27
	 @todo (Liusw)
	 @note
	*/
	class IUIAPI CProjectFilter
	{
	public:
		CProjectFilter(CProjectFilter *pParentFilter, FILTER_TYPE eFilterType, CIUIProject *pProject);
		~CProjectFilter();

	public:
		FILTER_TYPE GetFilterType() const;
		CIUIString GetFilterName() const;

		// filter
		int SetFilterName(LPCTSTR lpszFilter);

		CProjectFilter *AddFilter(LPCTSTR lpszFilter);
		int DeleteFilter(LPCTSTR lpszFilter, BOOL bDeleteProjectItem);
		int RenameFilter(LPCTSTR lpszOldFilter, LPCTSTR lpszNewFilter);
		int GetFilterCount() const;
		CProjectFilter *FindFilter(LPCTSTR lpszFilter);
		CProjectFilter *GetFilter(int nIndex);
		const CProjectFilter *GetFilter(int nIndex) const;

		// item
		int AddWindow(LPCTSTR lpszItemPath);
		int AddProjectItem(CControlProp *pItemProp);
		int DeleteProjectItem(LPCTSTR lpszItemPath);
		CControlProp *GetProjectItem(int nIndex);
		const CControlProp *GetProjectItem(int nIndex) const;
		int GetProjectItemCount() const;
		CControlProp *FindProjectItem(LPCTSTR lpszItemPath);
		int MoveProjectItem(LPCTSTR lpszItemPath, LPCTSTR lpszFromFilter, LPCTSTR lpszToFilter);

		/**
		@brief ������������Ԫ�أ�����xml�ļ��б�
		@details
		<pre>
		Ԫ�ص�˳��Ϊ�ڹ����ļ��е�˳��
		</pre>
		@author (Liusw)
		@param[out] pvProjectItems: ������������Ԫ��
		@return
		- 0  �ɹ�
		- -1 ʧ��
		*/
		int GetProjectItemList(std::vector<CControlProp *> *pvProjectItems);
		int GetProjectItemList(std::vector<const CControlProp *> *pvProjectItems) const;

	protected:
		FILTER_TYPE m_eFilterType;
		CIUIString m_strFilter; ///< ��m_eFilterTypeΪFILTER_TYPE_FILTERʱ����¼Filter����
		std::vector<CProjectFilter *> m_vFilterItem; ///< һ��filter�п����ж����filter
		std::vector<CControlProp *> m_vProjectItem; ///< Filter�У�ÿ��Item��Ӧһ��xml�ļ�

		CProjectFilter *m_pParentFilter; ///< ��Filter
		CIUIProject *m_pIUIProject;
	};

	CProjectFilter *IUIAPI FindFilter(CProjectFilter *pParent, LPCTSTR lpszFilter);


	// IUI�����ļ�������
	// CIUIProject���ڽ���uixproj�����ļ���uixproj�����ļ�
	// ������һ����Ŀ���еĴ��ڡ��˵���������Դ�ļ���
	// ���ڴ����ļ����˵��ļ��Ľ�������CUIMgr�ฺ������uixproj�ļ�����CIUIProjectSave��
	// ����༭���С� ÿһ��UI���� *.uixproj �и��Ե�SkinFolder.
	// ���һ��UI��Ŀ����Ҫ����UI��¶���û�������UI������rc�У�����¶���ֵ�UI����һ��
	// UI����*.uixproj�������rc�е�������һ��*.uixproj��
	//
	// CIUIProject�ڽ���Fontʱ�������ܡ���ʱ����һ��CFontProp����Ȼ���XML������CFontProp��
	// ����CFontProp������HIUIFONT��֮��������CFontProp�� ��ȻCFontProp��HIUIFONT��ռ
	// �ڴ档 �������CIUIProject�б���HIUIFONT��������CFontProp����Ϊ�����ǵ�һ��ʹ�õ�ʱ��
	// ��ȥ��������HIUIFONT�У���û�б���LOGFONT�ṹ�壬�⽫���������޷�����������
	// ���HIUIFONT�У�����LOGFONT�Ļ������ڴ�ռ�þͲ�ռ���ˡ�
	// ���⣬����༭���ڱ༭����ʱ��
	// CPropertiesWnd�е������б�ؼ���չʾ������CFontProp�и�������
	// ���CIUIProject�������������CFontProp���������޷��������塣
	class IUIAPI CIUIProject
	{
	public:
		CIUIProject();
		~CIUIProject();

	public:
		int SetProjectFile(LPCTSTR lpszProjectFile);
		CIUIString GetProjectPath() const;
		CIUIString GetProjectPathWithoutTitle() const;

		int Load(LPCTSTR lpszProjectFile);
		int Release();

		int AddProjectItem(LPCTSTR lpszFilter, LPCTSTR lpszItemPath);
		int AddProjectItem(LPCTSTR lpszFilter, CControlProp *pItemProp);
		int DeleteProjectItem(LPCTSTR lpszFilter, LPCTSTR lpszItemPath);
		int DeleteFilter(LPCTSTR lpszFilter, BOOL bDeleteProjectItem);
		int GetProjectItemCount() const;
		int MoveProjectItem(LPCTSTR lpszItemPath, LPCTSTR lpszFromFilter, LPCTSTR lpszToFilter);
		CProjectFilter *GetFilter(LPCTSTR lpszFilter);
		CProjectFilter *GetRootFilter();
		CControlProp *FindProjectItem(LPCTSTR lpszWindowFileName);

		// �����Ƿ��rc��Դ����Ƥ���ļ�
		BOOL SetLoadSkinFromResource();
		BOOL IsLoadSkinFromResource();
		CIUIString GetUIResourceType();
		CIUIString GetXMLResourceID();

		CImageMgr *GetImageMgr();
		CFontMgr *GetFontMgr();

		// ������Դ����
		CFontProp *GetDefaultFontProp();

		std::vector<CFontProp *> *CIUIProject::GetResFonts();
		CFontProp *GetFontProp(LPCTSTR lpszFontID);

		// ��ɫ��Դ����
		CColorProp *GetDefaultColorProp();

		std::vector<CColorProp *> *GetResColors();
		CColorProp *GetColorProp(LPCTSTR lpszResID);

		// �ַ�����Դ
		std::list<CStringProp> *GetResStrings();

		COLORREF GetColor(LPCTSTR lpszColorResID);
		int GetControlBkColor(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlBkColor2(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlBkColor4(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlCheckedBkColor4(const CControlProp *pCtrlProp, COLORREF *pcr);

		int GetControlBorderColor(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlBorderColor2(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlBorderColor4(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlCheckedBorderColor4(const CControlProp *pCtrlProp, COLORREF *pcr);

		int GetControlTextColor(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlTextColor2(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlTextColor4(const CControlProp *pCtrlProp, COLORREF *pcr);
		int GetControlCheckedTextColor4(const CControlProp *pCtrlProp, COLORREF *pcr);

		// Style
		int GetStyleCount(STYLE_TYPE eStyleType);

		int AddStyleItem(STYLE_TYPE eStyleType, CControlProp *pStyle);

		int DeleteStyleItem(STYLE_TYPE eStyleType, int nIndex);
		int DeleteStyleItem(STYLE_TYPE eStyleType, const CControlProp *pStyleProp);

		CControlProp *GetStyleItem(STYLE_TYPE eStyleType, int nIndex);
		CControlProp *GetStyleItem(STYLE_TYPE eStyleType, LPCTSTR lpszStyleID);

		std::vector<CButtonProp *> *GetStylePushButton();
		std::vector<CCheckBoxProp *> *GetStyleCheckBox();
		std::vector<CRadioButtonProp *> *GetStyleRadioButton();
		std::vector<CComboBoxProp *> *GetStyleComboBox();
		std::vector<CLabelProp *> *GetStyleStatic();
		std::vector<CRichTextBoxProp *> *GetStyleEdit();
		std::vector<CSliderProp *> *GetStyleSlider();
		std::vector<CProgressBarProp *> *GetStyleProgress();
		std::vector<CSpinButtonProp *> *GetStyleSpin();
		//std::vector<HOTPROPERTIES *> *GetStyleHotKey();
		//std::vector<IPAPROPERTIES *> *GetStyleIPAddress();
		std::vector<CListViewProp *> *GetStyleListCtrl();
		std::vector<CTreeViewProp *> *GetStyleTreeCtrl();
		//std::vector<TREELISTPROPERTIES *> *GetStyleTreeList();
		std::vector<CHtmlViewProp *> *GetStyleHtmlCtrl();
		std::vector<CDateTimePickerProp *> *GetStyleDateTime();
		//std::vector<MENUPROPERTIES *> *GetStyleMenu();
		//std::vector<MENUBARPROPERTIES *> *GetStyleMenuBar();
		std::vector<CColumnHeaderProp *> *GetStyleHeader();
		std::vector<CScrollBarProp *> *GetStyleScrollBar();
		std::vector<CToolTipCtrlProp *> *GetStyleToolTips();
		//std::vector<SPLITTERPROPERTIES *> *GetStyleSplitter();
		//std::vector<STACKPNLPROPERTIES *> *GetStylePanelStack();
		//std::vector<LINEWLPROPERTIES *> *GetStyleWLLine();

		// ������
		CIUIStringW FindControlContent(LPCTSTR lpszKey, BOOL *pbFound) const;
		int SwitchLanguage(LPCTSTR lpszLanguageFile);

	protected:
		CIUIString m_strProjectFile;	// Full path of *.uixproj file.

		// IUI֧�ִ�Ӳ�̻���Դ����ͼƬ
		BOOL m_bLoadSkinFromResource;
		CIUIString m_strUIResourceType;
		CIUIString m_strXMLResourceID;

		// ����uixproj�����õ��Ĺ���ͼƬ������
		CImageMgr m_ImageMgr; // Using it's CImageMgr::~CImageMgr
		CFontMgr m_FontMgr; // Using it's CFontMgr::~CFontMg

		// ����
	protected:
		// m_RootProjectFilter���������д������ԣ������ڱ�����֮�󣬴�������Ӧ�ñ����ٵ�
		// �������֮����Ҫ���±������������¼��ش������Լ���
		// ����༭���У�Ӧ�����¼���m_RootProjectFilter�������ô�������ʹ�á�
		CProjectFilter m_RootProjectFilter;

		//
		// ���塣 �����屻������֮����������Ӧ�ñ�����
		//

		// Ĭ�����塣 ����֮���в���HIUIFONT����μ�CIUIProjectע�͡�
		CFontProp *m_pDefFontProp;

		// ��ͨ�����б�
		std::vector<CFontProp *> m_vpResFont;

		//
		// ��ɫ
		//
		CColorProp *m_pDefColorProp;
		std::vector<CColorProp *> m_vpResColor;

		// �ַ���
		std::list<CStringProp> m_lstResStrings;

		// ������
		std::map<std::wstring, std::wstring> m_mapContents;

	public:
		// Style
		std::vector<CButtonProp *> m_vpStylePushButton;
		std::vector<CCheckBoxProp *> m_vpStyleCheckBox;
		std::vector<CRadioButtonProp *> m_vpStyleRadioButton;
		std::vector<CComboBoxProp *> m_vpStyleComboBox;
		std::vector<CLabelProp *> m_vpStyleStatic;
		std::vector<CRichTextBoxProp *> m_vpStyleRichEdit;
		std::vector<CSliderProp *> m_vpStyleSlider;
		std::vector<CProgressBarProp *> m_vpStyleProgress;
		std::vector<CSpinButtonProp *> m_vpStyleSpin;
		//std::vector<HOTPROPERTIES *> m_vpStyleHotKey;
		//std::vector<IPAPROPERTIES *> m_vpStyleIPAddress;
		std::vector<CListViewProp *> m_vpStyleListCtrl;
		std::vector<CTreeViewProp *> m_vpStyleTreeCtrl;
		//std::vector<TREELISTPROPERTIES *> m_vpStyleTreeList;
		std::vector<CHtmlViewProp *> m_vpStyleHtmlCtrl;
		std::vector<CDateTimePickerProp *> m_vpStyleDateTime;
		//std::vector<MENUPROPERTIES *> m_vpStyleMenu;
		//std::vector<MENUBARPROPERTIES *> m_vpStyleMenuBar;
		std::vector<CColumnHeaderProp *> m_vpStyleHeader;
		std::vector<CScrollBarProp *> m_vpStyleScrollBar;
		std::vector<CToolTipCtrlProp *> m_vpStyleToolTips;
		//std::vector<SPLITTERPROPERTIES *> m_vpStyleSplitter;
		//std::vector<STACKPNLPROPERTIES *> m_vpStylePanelStack;
		//std::vector<LINEWLPROPERTIES *> m_vpStyleWLLine;
	};

	class IUIAPI CMemStdioFile
	{
	public:
		CMemStdioFile();
		virtual ~CMemStdioFile();
		virtual BOOL OpenResource(HINSTANCE hRes, LPCTSTR lpszID, LPCTSTR lpszType);
		virtual BOOL CloseResource();

		void Attach(BYTE *lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0);
		BYTE *Detach();

	public:
		BOOL IsUnicode();

		virtual BOOL ReadString(CIUIString *pString);
		virtual BOOL ReadStringA(std::string *pstring);
		virtual BOOL ReadStringW(std::wstring *pstring);

		virtual ULONGLONG Seek(LONGLONG lOff, UINT nFrom);
		virtual void SetLength(ULONGLONG dwNewLen);
		virtual ULONGLONG GetPosition() const;
		virtual void Close();

	protected:
		virtual BYTE *Alloc(SIZE_T nBytes);
		virtual BYTE *Realloc(BYTE *lpMem, SIZE_T nBytes);
		virtual BYTE *Memcpy(BYTE *lpMemTarget, const BYTE *lpMemSource, SIZE_T nBytes);
		virtual void Free(BYTE *lpMem);
		virtual void GrowFile(SIZE_T dwNewLen);

	protected:
		HINSTANCE m_hResource;
		SIZE_T m_nGrowBytes;
		SIZE_T m_nPosition;
		SIZE_T m_nBufferSize;
		SIZE_T m_nFileSize;
		BYTE *m_lpBuffer;
		BOOL m_bAutoDelete;
	};

	// �������ء����������ڵ�XML�ļ��� ������������XML�����ڽ���༭����
	// ����WPFҲ��һ��������һ��xaml�ļ�������IUIҲ����һ�����ڻ�һ������һ��XML�ļ���
	class IUIAPI CUIParse
	{
	public:
		CUIParse();
		virtual ~CUIParse();

	public:
		// Path
		;
		int SetDelayLoadWindow(BOOL bDelayLoadWindow);
		BOOL IsDelayLoadWindow();

		int SetProject(CIUIProject *pOwner);
		CIUIProject *GetProject();

		int SetUIPath(LPCTSTR lpszUIPath, BOOL bCheckVersion = TRUE);
		int SetSource(LPCTSTR lpszUIPath);

		CIUIString GetUIPath();
		CIUIString GetUIPathWithoutTitle();

		// Load, save and release skin
		;
		int LoadSkin();
		int LoadIDDefined();

		int DelayLoadWindow(CWindowProp *pUIWndProp);

		int ReleaseSkin();

		// Version
		LONG GetIUIMajorVersion();
		LONG GetIUIMinorVersion();
		LONG GetIUIBuildVersion();
		LONG GetIUIChangeList();

		// Window
		int SetWindowProp(CWindowProp *pUIWndProp);
		CWindowProp *GetWindowProp();
		static CWindowProp *AllocUIWNDPROPERTIES();
		static int FreeUIWNDPROPERTIES(CWindowProp *pUIProp);
		int InitRunningUIWnd();

		// Find
		int FindCtrlProp(
			IN const UIVARIANT *pVarCtrlProp,
			OUT CControlBaseProp **ppCtrlProp);

	private:
		BOOL m_bDelayLoadWindow;                // Load window properties delay.

		CIUIProject *m_pProject;

		// for hard disk skin
		CIUIString m_strUIPath;
		CIUIString m_strUIPathWithoutTitle;

		// for resource skin
		CIUIString m_strXmlID;

		// for version
		LONG m_lIUIMajorVersion;
		LONG m_lIUIMinorVersion;
		LONG m_lIUIBuildVersion;
		LONG m_lIUIChangeList;

		// for *.uixprog and resource.h
		bool m_bOutsizeSetWinProp;
		CWindowProp *m_pWindow;
		std::vector<std::pair<CIUIString, int> > *m_pvIDs;
		std::map<CIUIString, int> *m_pmapStrIntIDs;
		std::map<int, CIUIString> *m_pmapIntStrIDs;
		CMemStdioFile m_fileResourceH;

		// for multi-language
		std::map<CIUIString, CIUIString> *m_pmapLanguage;            // m_mapLanguage["WindowID/ControlID"] = Caption
		std::map<HWND, CIUIString> *m_pmapCreatedHWndStringID;    // m_mapCreatedHWndStringID[HWND] = "WindowStringID"
	};

	// CFontParse: �������ء�����������Դ���ࡣ ������������������Դ�����ڽ���༭����
	class IUIAPI CFontParse
	{
	public:
		CFontParse();
		virtual ~CFontParse();

	public:
		int SetProject(CIUIProject *pOwner);
		CIUIProject *GetProject();

		// pFonts���ͣ�XML::IXMLDOMElementPtr
		int Load(
			IN IUnknown *pFonts,
			__inout CFontProp **ppDefFontProp,
			__inout std::vector<CFontProp *> *pvpResFont);

		std::vector<CFontProp *> *GetResFonts();

	protected:
		CIUIProject *m_pProject;
	};

	// CColorParse: �������ء�������ɫ��Դ���ࡣ ��������������ɫ��Դ�����ڽ���༭����
	class IUIAPI CColorParse
	{
	public:
		CColorParse();
		virtual ~CColorParse();

	public:
		int SetProject(CIUIProject *pOwner);
		CIUIProject *GetProject();

		// pColors���ͣ�XML::IXMLDOMElementPtr
		int Load(
			IN IUnknown *pColors,
			__inout CColorProp **ppDefColorProp,
			__inout std::vector<CColorProp *> *pvpResColor);

	protected:
		CIUIProject *m_pProject;
	};

	// CImageParse: �������ء�����ͼƬ��Դ���ࡣ ������������ͼƬ��Դ�����ڽ���༭����
	class IUIAPI CImageParse
	{
	public:
		CImageParse();
		virtual ~CImageParse();
	};

	// ����Gifʱ����¼Gif��ǰ֡���Ѳ��Ŵ�������Ϣ
	// ����HIUIIMAGE�ǹ���ģʽ������Gif�ĵ�ǰ֡��ϢӦ���ɵ�����ά����������HIUIIMAGEά��
	// ����ͬһ��Gif�ļ��õ���ͬ�ط�ʱ����������ͬ���ģ���ʹ����Gif����ʼʱ�䲻ͬ��
	// HIUIIMAGE�ڣ�Ҳ��һ��m_nCurFrame����������������ⲿά���ĵ�ǰ֡���ã����ڻ���ʱ
	// ����Դͼˮƽ��ʼλ�á�
	class IUIAPI GifHelper
	{
	public:
		GifHelper();
		~GifHelper();

	public:
		int SetCurFrame(int nCur);
		int GetCurFrame() const;

		int SetCurLoop(int nCur);
		int GetCurLoop() const;

	protected:
		int m_nCurFrame;	// ��ǰ֡
		int m_nCurLoop;		// ��ǰ��ѭ�����Ŵ���
	};

	class IUIAPI IUIImage
	{
		enum DIBOrientation
		{
			DIBOR_DEFAULT,
			DIBOR_TOPDOWN,
			DIBOR_BOTTOMUP
		};

	public:
		IUIImage() throw();
		virtual ~IUIImage() throw();

		int AddRef();
		int Release();

	public:
		CIUIString GetSafeImageName() const throw();
		HBITMAP GetSafeHBITMAP() const throw();
		operator HBITMAP() const throw();

		// ����ͼƬ���ڵĹ��̣�ͼƬ�ǹ�����صģ�����A�е�ͼƬ�빤��B�еķ�����ͬ���ļ���
		// ���ԣ�Ҳ�ڲ�ͬ��CIUIProject::m_ImageMgr�б���
		int SetProject(CIUIProject *pProject);
		CIUIProject *GetOwner();

		int Load(LPCTSTR pszFileName) throw();
		int Load(__inout IStream *pStream) throw();
		void LoadFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName) throw();
		void LoadFromResource(HINSTANCE hInstance, UINT nIDResource) throw();
		int LoadFromResource(LPCTSTR lpszID, LPCTSTR lpszResType);
		int AutoLoad(LPCTSTR lpszImageName) throw();	// Auto load image from file or rc by CUIMgr::m_bLoadFromFile.
		int SafeLoadSavedImage(); // Load the image saved in m_strImageName. the ref count add 1.

		int Create(int nWidth, int nHeight, int nBPP, DWORD dwFlags = 0) throw();
		int CreateEx(int nWidth, int nHeight, int nBPP, DWORD eCompression, const DWORD *pdwBitmasks = NULL, DWORD dwFlags = 0) throw();

		int Attach(HBITMAP hBitmap, DIBOrientation eOrientation = DIBOR_DEFAULT) throw();
		int Attach(HGPBITMAP hgpBitmap);
		int Attach(IUIImage &himgSrc);	// Keep the alpha channel.
		HBITMAP Detach() throw();

		int ConvertToDPIImage(int nCurDPIX, int nCurDPIY);

		int Destroy() throw();

		int GetBPP() const throw();
		int GetHeight() const throw();
		int GetWidth() const throw();
		bool IsHasAlphaChannel() const throw();

		// for Gif
		BOOL IsGif() const throw();
		UINT GetGifFrameCount() const throw();
		int GetGifCurFrame() const throw();
		int SetGifCurFrame(int nCurFrame) throw();
		int GetGifFrameDelay(__out LONG **pplFrameDelay, __out UINT *pnFrameCount) const;
		int GetGifLoopCount() const;

		const void *GetPixelAddress(int x, int y) const throw();
		void *GetPixelAddress(int x, int y) throw();
		COLORREF GetPixel(int x, int y) const throw();

		void SetPixel(int x, int y, COLORREF color) throw();
		void SetPixelRGB(int x, int y, BYTE r, BYTE g, BYTE b) throw();
		void SetHasAlphaChannel(bool bHasAlphaChannel) throw();

		int SetShadow(LPCRECT lprcShadow) throw();
		CIUIRect GetShowdow() const throw();

	public:
		// ����HBITMAP
		static int NineGridBitmapG(
			HBITMAP *phDstBmp,
			int nDestWidth,
			int nDestHeight,
			HBITMAP hSrcBmp,
			LPCRECT lprcResizeArg
		);
		static int PartNineGridBitmapG(
			HBITMAP *phDstBmp,
			int nDestWidth,
			int nDestHeight,
			HBITMAP hSrcBmp,
			LPCRECT lprcResizeArg,
			int nXOriginSrc/* = 0*/, // Դͼ��ʼˮƽ����
			int nYOriginSrc/* = 0*/, // Դͼ��ʼ��ֱ����
			int nSrcWidth/* = -1*/,	 // Դͼָ����ȷ�Χ��������
			int nSrcHeight/* = -1*/  // Դͼָ���߶ȷ�Χ��������
		);

		static int StretchBitmapG(
			HBITMAP hSrcBmp,
			HBITMAP *phDstBmp,
			int nDestWidth,
			int nDestHeight,
			int nXOriginSrc/* = 0*/, // Դͼ��ʼˮƽ����
			int nYOriginSrc/* = 0*/, // Դͼ��ʼ��ֱ����
			int nSrcWidth/* = -1*/,	 // Դͼָ����ȷ�Χ��������
			int nSrcHeight/* = -1*/  // Դͼָ���߶ȷ�Χ��������
		);
		static int TileBitmapG(HBITMAP hSrcBmp, HBITMAP *phDstBmp,
			int nDestWidth, int nDestHeight,
			int nXOriginSrc/* = 0*/, int nYOriginSrc/* = 0*/, int nSrcWidth/* = -1*/, int nSrcHeight/* = -1*/);
		static int CopyBitmapG(HBITMAP hSrc, HBITMAP *phDest);
		static int SubBitmapG(HBITMAP hSrcBmp, HBITMAP *phDstBmp, const CIUIRect &rcSub);
		static int SubBitmapG(HBITMAP hSrcBmp, HBITMAP *phDstBmp, int nX, int nY, int nWidth, int nHeight);

		static int GetBitmapSizeG(HBITMAP obj, LPSIZE size);

		// ����HIUIIMAGE
		static int ZoomImage(
			HIUIIMAGE himgSrc,
			IMAGE_RESIZE_MODE eIrm,
			LPCRECT lprcResizeArg,
			HIUIIMAGE *phimgDest,
			int nDestWidth,
			int nDestHeight,
			int nXOriginSrc/* = 0*/, // Դͼ��ʼˮƽ����
			int nYOriginSrc/* = 0*/, // Դͼ��ʼ��ֱ����
			int nSrcWidth/* = -1*/,	 // Դͼָ����ȷ�Χ��������
			int nSrcHeight/* = -1*/  // Դͼָ���߶ȷ�Χ��������
		);
		static int NineGridBitmap(
			HIUIIMAGE himgSrc,
			LPCRECT lprcResizeArg,
			HIUIIMAGE *phimgDest,
			int nDestWidth,
			int nDestHeight
		);
		static int PartNineGridBitmap(
			HIUIIMAGE himgSrc,
			LPCRECT lprcReszeArg,
			int nPart,
			int nPartIndex,
			HIUIIMAGE *phimgDest,
			int nDestWidth,
			int nDestHeight
		);
		static int PartNineGridBitmap(
			HIUIIMAGE himgSrc,
			LPCRECT lprcResizeArg,
			HIUIIMAGE *phimgDest,
			int nDestWidth,
			int nDestHeight,
			int nXOriginSrc/* = 0*/, // Դͼ��ʼˮƽ����
			int nYOriginSrc/* = 0*/, // Դͼ��ʼ��ֱ����
			int nSrcWidth/* = -1*/,	 // Դͼָ����ȷ�Χ��������
			int nSrcHeight/* = -1*/  // Դͼָ���߶ȷ�Χ��������
		);
		static int StretchBitmap(
			HIUIIMAGE himgSrc,
			HIUIIMAGE *phimgDest,
			int nDestWidth,
			int nDestHeight,
			int nXOriginSrc/* = 0*/, // Դͼ��ʼˮƽ����
			int nYOriginSrc/* = 0*/, // Դͼ��ʼ��ֱ����
			int nSrcWidth/* = -1*/,	 // Դͼָ����ȷ�Χ��������
			int nSrcHeight/* = -1*/  // Դͼָ���߶ȷ�Χ��������
		);
		static int TileBitmap(
			HIUIIMAGE himgSrc,
			HIUIIMAGE *phimgDest,
			int nDestWidth,
			int nDestHeight,
			int nXOriginSrc/* = 0*/, // Դͼ��ʼˮƽ����
			int nYOriginSrc/* = 0*/, // Դͼ��ʼ��ֱ����
			int nSrcWidth/* = -1*/,	 // Դͼָ����ȷ�Χ����ƽ��
			int nSrcHeight/* = -1*/  // Դͼָ���߶ȷ�Χ����ƽ��
		);
		static int CopyBitmap(HIUIIMAGE himgSrc, HIUIIMAGE *phimgDest);
		static int SubBitmap(HIUIIMAGE himgSrc, HIUIIMAGE *phimgDst, const CIUIRect &rcSub);
		static int SubBitmap(
			HIUIIMAGE himgSrc,
			HIUIIMAGE *phimgDst,
			int nX,
			int nY,
			int nWidth,
			int nHeight
		);

		// ����ͼƬ
		static HBITMAP LoadHBITMAP(LPCTSTR lpszFile);
		static HBITMAP LoadHBITMAPFromRes(UINT uID);
		static HBITMAP AutoLoadHBITMAP(CIUIProject *pProject, LPCTSTR lpszFile);		// Auto load image from file or rc use gdi mode by CUIMgr::m_bLoadFromFile.
		static LPCTSTR GetFileNameHexCode(LPCTSTR lpszImageName, BOOL bEncodeExt);

	private:
		int CreateFromGdiplusBitmap(__inout Gdiplus::Bitmap &bmSrc) throw();
		static int ComputePitch(int nWidth, int nBPP)
		{
			return (((nWidth * nBPP) + 31) / 32) * 4;
		}
		int UpdateBitmapInfo(DIBOrientation eOrientation);
		IUIImage &operator=(const IUIImage &himgSrc);

	public:
		static const DWORD createAlphaChannel;
		CIUIString m_strImageName;

	private:
		int m_nAddRef;

		CIUIProject *m_pOwner;
		HBITMAP m_hBitmap;
		void *m_pBits;
		int m_nWidth;
		int m_nHeight;
		int m_nPitch;
		int m_nBPP;
		bool m_bIsDIBSection;
		bool m_bHasAlphaChannel;
		LONG m_iTransparentColor;
		COLORREF m_clrTransparentColor;

		// for gif ������֡ͼƬ
		BOOL m_bGif;
		UINT m_nFrameCount;
		int m_nCurFrame;
		LONG *m_plFrameDelay;	// ��¼֡��ʱ����λ����
		int m_nLoopCount;	// ѭ�����Ŵ�����0Ϊ����ѭ����

		CIUIRect m_rcShadow;
	};

	class IUIAPI CIUIFont
	{
	public:
		CIUIFont();
		CIUIFont(HFONT hFont);

		~CIUIFont();

	public:
		// �����������ڵĹ��̣������ǹ�����صģ�����A�е������빤��B�еķ�����ͬ���ļ���
		// ���ԣ�Ҳ�ڲ�ͬ��CIUIProject::m_FontMgr�б���
		int SetOwner(CIUIProject *pProject);
		CIUIProject *GetOwner();

		operator HFONT() const;

		int AddRef();
		int Release();
		int DeleteObject();

		int Load(LPCTSTR lpszFontResID);
		int SafeLoadSavedFont();
		HFONT GetSafeHFont();

	protected:
		int m_nAddRef;
		HFONT m_hFont;
		CIUIProject *m_pOwner;

	public:
		CIUIString m_strFontResID;
	};


	struct IUIPOSITION {};
	typedef IUIPOSITION *IUIPOS;


	namespace ImageManager
	{
		// ͼƬ����
		int IUIAPI IUISetControlImage(
			IN CIUIProject *pOwner,
			__inout HIUIIMAGE *phIUIImage,
			LPCTSTR lpszImage);
		int IUIAPI AddCustomImage(
			IN CIUIProject *pOwner,
			LPCTSTR lpszImageFile,
			HBITMAP hImage);
		int IUIAPI AddCustomImage(
			IN CIUIProject *pOwner,
			LPCTSTR lpszImageFile,
			HIUIIMAGE hImage);
		int IUIAPI AddCustomImage(
			IN CIUIProject *pOwner,
			HBITMAP hImage,
			__out CIUIString *pstrImageName);
		int IUIAPI AddCustomImage(
			IN CIUIProject *pOwner,
			HIUIIMAGE hImage);
		HIUIIMAGE IUIAPI CreateIUIImage(IN CIUIProject *pOwner, LPCTSTR lpszImageFile);
		// No Add ref, Needn't release. If the image not exist, no create.
		HIUIIMAGE IUIAPI GetIUIImage(IN CIUIProject *pOwner, LPCTSTR lpszImageFile);
		int IUIAPI ReleaseIUIImage(HIUIIMAGE hIUIImage);
		int IUIAPI ReleaseIUIImage(IN CIUIProject *pOwner, LPCTSTR lpszImageFile);
	} // namespace ImageManager

	namespace FontManager
	{
		// �������
		int AddCustomFont(IN CIUIProject *pOwner, LPCTSTR lpszFontResID, HFONT hFont);
		int UpdateIUIFont(IN CIUIProject *pOwner, LPCTSTR lpszFontResID, HFONT hFont, BOOL bDeleteOld);
		BOOL FindIUIFont(IN CIUIProject *pOwner, LPCTSTR lpszFontResID);
		HFONT CreateIUIFont(IN CIUIProject *pOwner, LPCTSTR lpszFontResID);
		int ReleaseIUIFont(IN CIUIProject *pOwner, LPCTSTR lpszFontResID);
	} // namespace FontManager

	namespace Render
	{
		Gdiplus::PointF IUIAPI Point2PointF(POINT pt);
		POINT IUIAPI PointF2Point(Gdiplus::PointF pt);
		Gdiplus::RectF IUIAPI Rect2RectF(LPCRECT lprc);
		RECT IUIAPI RectF2Rect(const Gdiplus::RectF *prc);

		// ��ƽ��Path����ɽڵ�
		class IUIAPI CFlattenPathPoint
		{
			friend class CFlattenAnimationSubPath;
			friend class CFlattenAnimationPath;

		public:
			CFlattenPathPoint();
			CFlattenPathPoint(const CFlattenPathPoint &rSrc);
			~CFlattenPathPoint();

			CFlattenPathPoint &operator=(const CFlattenPathPoint &rSrc);

		public:
			int SetPoint(Gdiplus::PointF pt);
			Gdiplus::PointF GetPoint() const;

			int SetLengthToStart(Gdiplus::REAL nLength);
			Gdiplus::REAL GetLengthToStart() const;

		protected:
			Gdiplus::PointF *m_pptF;
			// �뿪·�����ĳ���
			Gdiplus::REAL m_nLengthToStart;
		};

		class IUIAPI CFlattenAnimationSubPath
		{
			friend class CFlattenAnimationPath;

		public:
			CFlattenAnimationSubPath();
			CFlattenAnimationSubPath(const CFlattenAnimationSubPath &rSrc);
			virtual ~CFlattenAnimationSubPath();

			CFlattenAnimationSubPath &operator=(const CFlattenAnimationSubPath &rSrc);

		public:
			Gdiplus::REAL SetPath(Gdiplus::GraphicsPath *pPath);
			Gdiplus::REAL GetLength() const;

		protected:
			std::vector<CFlattenPathPoint *> *m_pvpPoints;
			bool m_bArc;	// �Ƿ�����������
			Gdiplus::RectF *m_prcArcBoundsF;// Arc�����о���
			Gdiplus::REAL m_nStartAngle;	// ��ʼ�Ƕ�
			Gdiplus::REAL m_nSweepAngle;	// ɨ���ĽǶ�
		};

		// ��ƽ����֧�ֶ������ݵ�Path
		class IUIAPI CFlattenAnimationPath
		{
		public:
			CFlattenAnimationPath();
			CFlattenAnimationPath(const CFlattenAnimationPath &rSrc);
			virtual ~CFlattenAnimationPath();

			CFlattenAnimationPath &operator=(const CFlattenAnimationPath &rSrc);

		public:
			int AddPath(Gdiplus::GraphicsPath *pPath);
			int AddArcPath(Gdiplus::GraphicsPath *pPath,
				Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL width, Gdiplus::REAL height,
				Gdiplus::REAL startAngle, Gdiplus::REAL sweepAngle);

			int SetDuration(DWORD dwDuration);
			DWORD GetDuration() const;

			// �õ�ָ��ʱ�̣�֡�����꣬������꣬�����ǲ�ֵ������
			int GetPos(DWORD t, __out CFlattenPathPoint *pOutPoint);

		protected:
			std::vector<CFlattenAnimationSubPath *> *m_pvpPaths;
			DWORD m_dwDuration;
			Gdiplus::REAL m_nTotalLength;

			// ���������ߵ�4���㣬�������ƶ����ġ��ٶȡ�
			Gdiplus::PointF *m_pPtFBezier[4];
		};

		//
		// HDC ����
		//
		void IUIAPI TransparentBlt2(HDC hdcDest,
			int nXOriginDest, int nYOriginDest, int nDestWidth, int nDestHeight,
			HDC hdcSrc,
			int nXOriginSrc, int nYOriginSrc, int nSrcWidth, int nSrcHeight, UINT crTransparent);

		int IUIAPI TileBlt(HDC hdcDest,
			int nXOriginDest, int nYOriginDest, int nDestWidth, int nDestHeight,
			HDC hdcSrc,
			int nXOriginSrc, int nYOriginSrc, int nSrcWidth, int nSrcHeight, BYTE btSourceConstantAlpha/* = 255*/);
		int IUIAPI AlphaTileBlt(HDC hdcDest,
			int nXOriginDest, int nYOriginDest, int nDestWidth, int nDestHeight,
			HDC hdcSrc,
			int nXOriginSrc, int nYOriginSrc, int nSrcWidth, int nSrcHeight, BYTE btSourceConstantAlpha/* = 255*/);

		int IUIAPI StretchAlphaBlend(HDC hdcDest,
			int nXOriginDest, int nYOriginDest, int nDestWidth, int nDestHeight,
			HDC hdcSrc,
			int nXOriginSrc, int nYOriginSrc, int nSrcWidth, int nSrcHeight,
			BYTE btSourceConstantAlpha);

		//////////////////////////////////////////////////////////////////////////
		// Draw format text
		int IUIAPI DrawFormatText(
			HDC hdcDest,
			// Text
			LPCTSTR lpszText,
			int nTextLength,
			// Target
			LPCRECT lprcDest,
			LPCRECT lprcPadding4Text,
			TEXT_ALIGN_HOR eTextHorAlign,
			TEXT_ALIGN_VER eTextVerAlign,
			UINT uTextFormat,
			// Text font and color property
			HFONT hTextFont,
			COLORREF crText,
			BOOL bUseGdiplus);
		// format: see ::DrawText
		int IUIAPI DrawTextGp(
			Gdiplus::Graphics *pGraphicsDst,
			LPCTSTR lpszString,
			int nLength,
			HFONT hFont,
			COLORREF crText,
			const Gdiplus::RectF *prc,
			UINT format);
		int IUIAPI DrawLine(HDC hDstDC, COLORREF crLine, int nLineWidht, POINT ptBegin, POINT ptEnd);
		int IUIAPI DrawLine(HDC hDstDC, COLORREF crLine, int nLineWidht, int nX1, int nY1, int nX2, int nY2);

		//
		// HBITMAP ����
		//
		void IUIAPI TransparentBltHBITMAP(HDC hdcDest,
			int nXOriginDest, int nYOriginDest, int nDestWidth, int nDestHeight,
			HBITMAP hBmpSrc,
			int nXOriginSrc, int nYOriginSrc, int nSrcWidth, int nSrcHeight, UINT crTransparent);

		int IUIAPI NineGridBltG(
			HDC hdcDest,
			int nXDest,
			int nYDest,
			int nDestWidth,
			int nDestHeight,
			HBITMAP hbmpSrc,
			LPCRECT lprcResizeArg
		);
		int IUIAPI NineGridBltG(
			HDC hdcDest,
			LPCRECT lprcDest,
			HBITMAP hbmpSrc,
			LPCRECT lprcResizeArg
		);
		int IUIAPI PartNineGridBltG(
			HDC hdcDest,
			int nXDest,
			int nYDest,
			int nDestWidth,
			int nDestHeight,
			HBITMAP hbmpSrc,
			int nPart,
			int nPartIndex,
			LPCRECT lprcResizeArg
		);
		int IUIAPI PartNineGridBltG(
			HDC hdcDest,
			LPCRECT lprcDest,
			HBITMAP hbmpSrc,
			int nPart,
			int nPartIndex,
			LPCRECT lprcResizeArg
		);
		int IUIAPI PartNineGridBltG(
			HDC hdcDest,
			LPCRECT lprcDest,
			HBITMAP hbmpSrc,
			LPCRECT lprcSrc,
			LPCRECT lprcResizeArg
		);

		int IUIAPI StretchBltG(HDC hdcDest, LPCRECT lprcDest, HBITMAP hbmpSrc);
		int IUIAPI BitBltG(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HBITMAP hSrcBmp, int nXSrc, int nYSrc, DWORD dwRop);
		int IUIAPI BitBltG(HDC hdcDest, LPCRECT lprcDest, HBITMAP hSrcBmp, int nXSrc, int nYSrc, DWORD dwRop);

		int IUIAPI CenterBitBltG(HDC hDC, LPCRECT lprcDest, HBITMAP hBmp, DWORD dwRop);

		// For windowless control, pDstDC is parent DC, rcClient is control coordinate relate to parent.
		int IUIAPI DrawForegroundG(HDC hDstDC, LPCRECT lprcClient, LPCRECT lprcForegroundMargin,
			HBITMAP hbmpFg,
			FOREGROUND_ALIGN_HOR eForegroundAlignHor, FOREGROUND_ALIGN_VER eForegroundAlignVer,
			COLORREF crMask);
		int IUIAPI DrawImageG(
			HDC hDstDC,
			LPCRECT lprcImage,
			HBITMAP hImage,
			IMAGE_RESIZE_MODE eImgResizeMode,
			LPCRECT lprcResizeArg
		);

		//
		// HIUIIMAGE ����
		//
		int IUIAPI IUINineGridBlt(HDC hdcDest,
			int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg);
		int IUIAPI IUINineGridBlt(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE hbmpSrc, LPCRECT lprcResizeArg);

		int IUIAPI IUINineGridBltEx(HDC hdcDest,
			int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg,
			COLORREF crColorKey, BYTE btSourceConstantAlpha);
		int IUIAPI IUINineGridBltEx(HDC hdcDest,
			LPCRECT lprcDest,
			HIUIIMAGE hbmpSrc, LPCRECT lprcResizeArg,
			COLORREF crColorKey, BYTE btSourceConstantAlpha);

		int IUIAPI IUIPartNineGridBlt(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg, int nPart, int nPartIndex);
		int IUIAPI IUIPartNineGridBlt(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg, int nPart, int nPartIndex);
		int IUIAPI IUIPartNineGridBlt(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg, LPCRECT lprcSrc);
		int IUIAPI IUIPartNineGridBltResetResizePoint(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg, LPCRECT lprcSrc);

		int IUIAPI IUIPartNineGridBltEx(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg, int nPart, int nPartIndex,
			COLORREF crColorKey, BYTE btSourceConstantAlpha, BOOL bResetResizePoint);
		int IUIAPI IUIPartNineGridBltEx(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg, int nPart, int nPartIndex,
			COLORREF crColorKey, BYTE btSourceConstantAlpha, BOOL bResetResizePoint);
		int IUIAPI IUIPartNineGridBltEx(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE himgSrc, LPCRECT lprcResizeArg, LPCRECT lprcSrc,
			COLORREF crColorKey, BYTE btSourceConstantAlpha, BOOL bResetResizePoint);

		// ������ͼ
		int IUIAPI IUIStretchBlt(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc, int nXSrc, int nYSrc, int nSrcWidth, int nSrcHeight);
		int IUIAPI IUIStretchBlt(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc);
		int IUIAPI IUIStretchBlt(HDC hdcDest, LPCRECT lprcDest, HIUIIMAGE himgSrc);

		// while himgSrc has alpha channel, and btSourceConstantAlpha is 255, IUIAlphaStretchBlt and IUIStretchBlt are same.
		int IUIAPI IUIAlphaStretchBlt(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc, BYTE btSourceConstantAlpha, IMAGE_RESIZE_MODE eStretchQuality);
		int IUIAPI IUIAlphaStretchBlt(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE himgSrc, BYTE btSourceConstantAlpha, IMAGE_RESIZE_MODE eStretchQuality);

		int IUIAPI IUIPartStretchBlt(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc, int nXSrc, int nYSrc, int nSrcWidth, int nSrcHeight,
			IMAGE_RESIZE_MODE eStretchQuality);
		int IUIAPI IUIPartStretchBlt(HDC hdcDest, LPCRECT lprcDest, HIUIIMAGE himgSrc, LPCRECT lprcSrc,
			IMAGE_RESIZE_MODE eStretchQuality);
		int IUIAPI IUIPartStretchBlt(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE himgSrc, int nPart, int nPartIndex, IMAGE_RESIZE_MODE eStretchQuality);
		int IUIAPI IUIPartStretchBlt(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE himgSrc, int nPart, int nPartIndex, IMAGE_RESIZE_MODE eStretchQuality);

		// ƽ����ͼ
		int IUIAPI IUITileBlt(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE himgSrc, int nXOriginSrc/* = 0*/, int nYOriginSrc/* = 0*/,
			int nSrcWidth/* = -1*/, int nSrcHeight/* = -1*/);

		// ������ͼ
		int IUIAPI IUICenterBitBlt(HDC hDC, LPCRECT lprcDest, HIUIIMAGE himgSrc, DWORD dwRop);

		// 1��1��ͼ
		int IUIAPI IUIBitBlt(HDC hdcDest, int nXDest, int nYDest, int nDestWidth, int nDestHeight,
			HIUIIMAGE hSrcBmp, int nXSrc, int nYSrc, DWORD dwRop);
		int IUIAPI IUIBitBlt(HDC hdcDest, LPCRECT lprcDest,
			HIUIIMAGE hSrcBmp, int nXSrc, int nYSrc, DWORD dwRop);

		// Same as IUITileBlt, but with a clip area. a board of the clip
		// area is smoothing. If lprcSrc, use the entire image to tile.
		// ����������Բ�ο����ͷ��
		int IUIAPI IUITileClipImage(
			Gdiplus::Graphics *pGraphics,
			Gdiplus::GraphicsPath *pDestClipPath,
			Gdiplus::Image *pSrcImage,
			LPCRECT lprcSrc
		);

		// ������������Ļ������棬��װ�ļ��׵���
		// For windowless control, pDstDC is parent DC, rcClient is control coordinate relate to parent.
		int IUIAPI IUIDrawForeground(HDC hDstDC, LPCRECT lprcClient, LPCRECT lprcForegroundMargin,
			HIUIIMAGE himgFg,
			FOREGROUND_ALIGN_HOR eForegroundAlignHor, FOREGROUND_ALIGN_VER eForegroundAlignVer,
			COLORREF crMask, BYTE btSourceConstantAlpha/* = 255*/);

		// Draw himgFg with rcFgPart part to DC.
		int IUIAPI IUIPartDrawForeground(HDC hDstDC, LPCRECT lprcDest, LPCRECT lprcForegroundMargin,
			HIUIIMAGE himgFg, LPCRECT lprcFgPart,
			FOREGROUND_ALIGN_HOR eForegroundAlignHor, FOREGROUND_ALIGN_VER eForegroundAlignVer,
			COLORREF crMask, BYTE btSourceConstantAlpha/* = 255*/);

		int IUIAPI IUIDrawImage(HDC hDstDC, LPCRECT lprcDest,
			HIUIIMAGE hImage, IMAGE_RESIZE_MODE eImageResizeMode, LPCRECT lprcResizeArg);
		int IUIAPI IUIPartDrawImage(HDC hDstDC, LPCRECT lprcDest,
			HIUIIMAGE hImage, IMAGE_RESIZE_MODE eImageResizeMode, LPCRECT lprcResizeArg,
			LPCRECT lprcSrc);
		int IUIAPI IUIPartDrawImage(HDC hDstDC, LPCRECT lprcDest,
			HIUIIMAGE hImage, IMAGE_RESIZE_MODE eImageResizeMode, LPCRECT lprcResizeArg,
			int nPartCount, int nPartIndex);

	} // namespace Render


	//////////////////////////////////////////////////////////////////////////
	//

	// for warning C4275
	struct UIVARIANTTHIS
	{
		_variant_t varThis;
	};
	// for warning C2451
	struct UIVARIANTVAR
	{
		_bstr_t strVarName;        // variable name
		_variant_t varDefaultValue;    // The default value
		_bstr_t strIUIElementName;        // element name in the.iui file
		_bstr_t strIUIAttributeName;    // attribute name in the.iui file
		std::vector<CIUIString> lstStringOptions;        // options value of the variable
	};

	class IUIAPI UIVARIANT
	{
	public:
		// Constructors
		//
		UIVARIANT();

		UIVARIANT(const _variant_t &varSrc) ;
		UIVARIANT(const _variant_t *pSrc) ;
		UIVARIANT(const UIVARIANT &varSrc) ;

		UIVARIANT(_variant_t &varSrc, bool fCopy) ;          // Attach _variant_t if !fCopy

		UIVARIANT(short sSrc, VARTYPE vtSrc = VT_I2) ;    // Creates a VT_I2, or a VT_BOOL
		UIVARIANT(long lSrc, VARTYPE vtSrc = VT_I4) ;     // Creates a VT_I4, a VT_ERROR, or a VT_BOOL
		UIVARIANT(float fltSrc);                                   // Creates a VT_R4
		UIVARIANT(double dblSrc, VARTYPE vtSrc = VT_R8) ; // Creates a VT_R8, or a VT_DATE
		UIVARIANT(const CY &cySrc);                                // Creates a VT_CY
		UIVARIANT(const _bstr_t &bstrSrc) ;               // Creates a VT_BSTR
		UIVARIANT(const wchar_t *pSrc) ;                  // Creates a VT_BSTR
		UIVARIANT(const char *pSrc) ;                     // Creates a VT_BSTR
		UIVARIANT(IDispatch *pSrc, bool fAddRef = true);           // Creates a VT_DISPATCH
		UIVARIANT(bool boolSrc);                                   // Creates a VT_BOOL
		UIVARIANT(IUnknown *pSrc, bool fAddRef = true);            // Creates a VT_UNKNOWN
		UIVARIANT(const DECIMAL &decSrc);                          // Creates a VT_DECIMAL
		UIVARIANT(BYTE bSrc);                                      // Creates a VT_UI1

#if(_MSC_VER > 1200) // VC6.0
		UIVARIANT(char cSrc);                                      // Creates a VT_I1
		UIVARIANT(unsigned short usSrc);                           // Creates a VT_UI2
		UIVARIANT(unsigned long ulSrc);                            // Creates a VT_UI4
		UIVARIANT(int iSrc);                                       // Creates a VT_INT
		UIVARIANT(unsigned int uiSrc);                             // Creates a VT_UINT
#if (_WIN32_WINNT >= 0x0501)
		UIVARIANT(__int64 i8Src);                                  // Creates a VT_I8
		UIVARIANT(unsigned __int64 ui8Src);                        // Creates a VT_UI8
#endif
#endif
		UIVARIANT(BYTE *pbVal);                            // Creates a
		UIVARIANT(RECT rcSrc);
		UIVARIANT(POINT ptSrc);
		UIVARIANT(LOGFONT lf);
		UIVARIANT(CONTROL_TYPE eSrc);
		UIVARIANT(IMAGE_RESIZE_MODE eSrc);
		UIVARIANT(CONTROL_LAYOUT_HOR eSrc);
		UIVARIANT(CONTROL_LAYOUT_VER eSrc);
		UIVARIANT(DOCK eSrc);
		UIVARIANT(ROOT_LAYOUT_TYPE eSrc);
		UIVARIANT(TEXT_ALIGN_HOR eSrc);
		UIVARIANT(TEXT_ALIGN_VER eSrc);
		UIVARIANT(FOREGROUND_ALIGN_HOR eSrc);
		UIVARIANT(FOREGROUND_ALIGN_VER eSrc);
		UIVARIANT(BTN_TYPE eSrc);
		UIVARIANT(CHK_TYPE eSrc);
		UIVARIANT(WINDOW_TYPE eSrc);
		UIVARIANT(CMB_STYLE eSrc);
		UIVARIANT(SPN_ALIGN eSrc);
		UIVARIANT(SLD_EXT_STYLE eSrc);
		UIVARIANT(LST_STYLE eSrc);
		UIVARIANT(LST_ALIGN eSrc);
		UIVARIANT(LST_SORT eSrc);
		UIVARIANT(DATETIME_FORMAT eSrc);
		UIVARIANT(BACKGROUND_TYPE eSrc);
		UIVARIANT(PROGRESS_THUMB_MODE eSrc);
		UIVARIANT(PROGRESS_THUMB_POSITION eSrc);
		UIVARIANT(ALPHA_FORMAT eSrc);
		UIVARIANT(MENU_BORDER_STYLE eSrc);
		UIVARIANT(SPLITTER_ORIENTATION eSrc);
		UIVARIANT(LINE_PEN_STYLE eSrc);

		// Destructor
		//
		~UIVARIANT();

		// Extractors
		//
#if(_MSC_VER <= 1200) // VC6.0
		operator int() const;
#endif

		operator LONG() const;
		operator bool() const;

		operator BYTE *() const;
		operator _variant_t() const;
		operator LPCWSTR() const;
		operator LPCSTR() const;
		operator RECT() const;
		//operator CIUIRect() const;
		operator POINT() const;
		operator COLORREF() const;
		operator LOGFONT() const;
		operator CONTROL_TYPE() const;
		operator IMAGE_RESIZE_MODE() const;
		operator CONTROL_LAYOUT_HOR() const;
		operator CONTROL_LAYOUT_VER() const;
		operator DOCK() const;
		operator ROOT_LAYOUT_TYPE() const;
		operator TEXT_ALIGN_HOR() const;
		operator TEXT_ALIGN_VER() const;
		operator FOREGROUND_ALIGN_HOR() const;
		operator FOREGROUND_ALIGN_VER() const;
		operator BTN_TYPE() const;
		operator CHK_TYPE() const;
		operator WINDOW_TYPE() const;
		operator CMB_STYLE() const;
		operator SPN_ALIGN() const;
		operator SLD_EXT_STYLE() const;
		operator LST_STYLE() const;
		operator LST_ALIGN() const;
		operator LST_SORT() const;
		operator DATETIME_FORMAT() const;
		operator BACKGROUND_TYPE() const;
		operator PROGRESS_THUMB_MODE() const;
		operator PROGRESS_THUMB_POSITION() const;
		operator ALPHA_FORMAT() const;
		operator MENU_BORDER_STYLE() const;
		operator SPLITTER_ORIENTATION() const;
		operator LINE_PEN_STYLE() const;

		// Assignment operations
		//
		UIVARIANT &operator=(const _variant_t &varSrc) ;
		UIVARIANT &operator=(const _variant_t *pSrc) ;
		UIVARIANT &operator=(const UIVARIANT &varSrc) ;

		UIVARIANT &operator=(short sSrc) ;                // Assign a VT_I2, or a VT_BOOL
		UIVARIANT &operator=(long lSrc) ;                 // Assign a VT_I4, a VT_ERROR or a VT_BOOL
		UIVARIANT &operator=(float fltSrc) ;              // Assign a VT_R4
		UIVARIANT &operator=(double dblSrc) ;             // Assign a VT_R8, or a VT_DATE
		UIVARIANT &operator=(const CY &cySrc) ;           // Assign a VT_CY
		UIVARIANT &operator=(const _bstr_t &bstrSrc) ;    // Assign a VT_BSTR
		UIVARIANT &operator=(const wchar_t *pSrc) ;       // Assign a VT_BSTR
		UIVARIANT &operator=(const char *pSrc) ;          // Assign a VT_BSTR
		UIVARIANT &operator=(IDispatch *pSrc) ;           // Assign a VT_DISPATCH
		UIVARIANT &operator=(bool boolSrc) ;              // Assign a VT_BOOL
		UIVARIANT &operator=(IUnknown *pSrc) ;            // Assign a VT_UNKNOWN
		UIVARIANT &operator=(const DECIMAL &decSrc) ;     // Assign a VT_DECIMAL
		UIVARIANT &operator=(BYTE bSrc) ;                 // Assign a VT_UI1

#if (_MSC_VER > 1200) // VC6.0
		UIVARIANT &operator=(char cSrc) ;                 // Assign a VT_I1
		UIVARIANT &operator=(unsigned short usSrc) ;      // Assign a VT_UI2
		UIVARIANT &operator=(unsigned long ulSrc) ;       // Assign a VT_UI4
		UIVARIANT &operator=(int iSrc) ;                  // Assign a VT_INT
		UIVARIANT &operator=(unsigned int uiSrc) ;        // Assign a VT_UINT
#if (_WIN32_WINNT >= 0x0501)
		UIVARIANT &operator=(__int64 i8Src) ;             // Assign a VT_I8
		UIVARIANT &operator=(unsigned __int64 ui8Src) ;   // Assign a VT_UI8
#endif
#endif
		UIVARIANT &operator=(BYTE *pbVal);
		UIVARIANT &operator=(const RECT &rcSrc);
		UIVARIANT &operator=(const POINT &ptSrc);
		UIVARIANT &operator=(const LOGFONT &lfSrc);
		UIVARIANT &operator=(CONTROL_TYPE eSrc);
		UIVARIANT &operator=(IMAGE_RESIZE_MODE eSrc);
		UIVARIANT &operator=(CONTROL_LAYOUT_HOR eSrc);
		UIVARIANT &operator=(CONTROL_LAYOUT_VER eSrc);
		UIVARIANT &operator=(DOCK eSrc);
		UIVARIANT &operator=(ROOT_LAYOUT_TYPE eSrc);
		UIVARIANT &operator=(TEXT_ALIGN_HOR eSrc);
		UIVARIANT &operator=(TEXT_ALIGN_VER eSrc);
		UIVARIANT &operator=(FOREGROUND_ALIGN_HOR eSrc);
		UIVARIANT &operator=(FOREGROUND_ALIGN_VER eSrc);
		UIVARIANT &operator=(BTN_TYPE eSrc);
		UIVARIANT &operator=(CHK_TYPE eSrc);
		UIVARIANT &operator=(WINDOW_TYPE eSrc);
		UIVARIANT &operator=(CMB_STYLE eSrc);
		UIVARIANT &operator=(SPN_ALIGN eSrc);
		UIVARIANT &operator=(SLD_EXT_STYLE eSrc);
		UIVARIANT &operator=(LST_STYLE eSrc);
		UIVARIANT &operator=(LST_ALIGN eSrc);
		UIVARIANT &operator=(LST_SORT eSrc);
		UIVARIANT &operator=(DATETIME_FORMAT eSrc);
		UIVARIANT &operator=(BACKGROUND_TYPE eSrc);
		UIVARIANT &operator=(PROGRESS_THUMB_MODE eSrc);
		UIVARIANT &operator=(PROGRESS_THUMB_POSITION eSrc);
		UIVARIANT &operator=(ALPHA_FORMAT eSrc);
		UIVARIANT &operator=(MENU_BORDER_STYLE eSrc);
		UIVARIANT &operator=(SPLITTER_ORIENTATION eSrc);
		UIVARIANT &operator=(LINE_PEN_STYLE eSrc);

		// Comparison operations
		//
		bool operator==(const _variant_t &varSrc) const;
		bool operator==(const _variant_t *pSrc) const;
		bool operator==(const UIVARIANT &varSrc) const;
		bool operator!=(const _variant_t &varSrc) const;
		bool operator!=(const _variant_t *pSrc) const;

		bool operator==(LPCTSTR lpszSrc) const;
		bool operator!=(LPCTSTR lpszSrc) const;


		// Low-level operations
		//
		void Init();
		void IUI_VARIANT_Copy(const UIVARIANT &varSrc);
		void IUI_VARIANT_Clear();
		_variant_t &GetVARIANT();
		_variant_t *GetAddress() ;
		void SetString(const char *pSrc) ; // used to set ANSI string
		int SetPointX(LONG x);
		int SetPointY(LONG y);

		// For VT_EX_RECT_WH
		int SetRectLeftNoSize(LONG lLeft);
		int SetRectTopNoSize(LONG lTop);
		int SetRectWidth(LONG lWidth);
		int SetRectHeight(LONG lHeight);

		// For VT_EX_RECT
		int SetRectLeft(LONG lLeft);
		int SetRectTop(LONG lTop);
		int SetRectRight(LONG lRight);
		int SetRectBottom(LONG lBottom);

		_bstr_t GetEnumString() const;
		int InitByEnumString(LPCTSTR lpszValue);

		// For binding property
		int SetBindVariant(const UIVARIANT *pvarBind);
		const UIVARIANT *GetBindVariant() const;
		int RemoveBindVariant();
		int SetBindCompareValue(const UIVARIANT &var);
		const UIVARIANT GetBindCompareValue() const;

		int SetVarName(LPCTSTR lpszName);
		LPCTSTR GetVarName();

		int SetDefaultValue(_variant_t varDefault);

		int SetAttributeValue(LPCTSTR lpszValue);
		LPCTSTR GetAttributeValue();

		int SetIUIElementName(LPCTSTR lpszIUIEleName);
		LPCTSTR GetIUIElementName() const;

		int SetIUIAttributeName(LPCTSTR lpszIUIAttibuteName);
		LPCTSTR GetIUIAttributeName();

		int SetGroupName(LPCTSTR lpszGroupName);
		LPCTSTR GetGroupName();

		int SetPropWndName(LPCTSTR lpszName);
		LPCTSTR GetPropWndName();

		int SetDescription(LPCTSTR lpszDes);
		LPCTSTR GetDescription();

		int AddStringOption(LPCTSTR lpszOption);

	protected:
		mutable char *strA;
		UIVARIANT *pvarBind;
		UIVARIANT *pvarCompare;

	public:
		class CControlProp *m_pBindCtrlProp;
		CIUIString strAttributeValue;        // �����������XMLʱ������ֵ��ԭʼ�ַ����� �����_bstr_t���ڿ�ģ�����ʱ������������Crash���⡣
		CIUIString strGroupName;        // valid while bGroup is TRUE.
		CIUIString strPropWndName;        // name in CPropertiesWnd
		CIUIString strDescription;        // description of the variable
		UIVARIANTVAR varC4251;        // ���warning C4251���ⶨ��ı�����
		UIVARIANTTHIS varC4275;        // ���warning C4275���ⶨ��ı�����
		bool bSet;                // ���ֵ�Ƿ��ⲿ���ù���
		VARTYPE vtEx;            // extended variant type. the value if enum VARENUMEX.
		bool bSaveToSkinFile;    // specifies the variable save to *.iui file or not.
		bool bNeedToConvert;    // specifies the variable is only valid in old version, it has been instead of by new property, it need to be convert to the new version.
		bool bReadOnly;
		bool bShowInPropertiesWnd;        // specifies the variable show in CPropertiesWnd or not. the following three variable is valid while bShowInPropertiesWnd is TRUE.
		bool bGroup;
		int nMinValue;            // specifies the minimize value while vt is VT_I4 etc.
		int nMaxValue;            // specifies the maximize value while vt is VT_I4 etc.

		// Disabled while bind property is...
		// Disabled while bind property isn't ...
		bool bDisabledWhileBindIs;
		bool bDisabledWhileBindIsnot;
		long lBeBindCount;
	};

	// ʹ��ָ�뱣����󡣵����߲���Ҫά���ڴ�
	template<class _Ty>
	class CAutoObject
	{
	public:
		CAutoObject()
		{
			m_pObj = NULL;
		}

		~CAutoObject()
		{
			Clear();
		}

	public:
		void operator=(const _Ty &obj)
		{
			if (NULL == m_pObj)
			{
				m_pObj = new _Ty;
			}

			if (NULL == m_pObj)
			{
				return;
			}

			*m_pObj = obj;
		}
		void operator=(const _Ty *pobj)
		{
			if (NULL == pobj)
			{
				return;
			}

			if (NULL == m_pObj)
			{
				m_pObj = new _Ty;
			}

			if (NULL == m_pObj)
			{
				return;
			}

			*m_pObj = *pobj;
		}

		_Ty &GetObject()
		{
			return *m_pObj;
		}

		void Clear()
		{
			if (NULL != m_pObj)
			{
				delete m_pObj;
				m_pObj = NULL;
			}
		}

		bool IsEmpty()
		{
			return m_pObj == NULL ? true : false;
		}

	protected:
		_Ty *m_pObj;
	};

	// TEMPLATE CLASS CAutoPtr, copy from auto_ptr
	// ����ָ��, ��new��ָ�봫��CAutoPtr���治��ҪҲ�����ͷš�
	template<class _Ty>
	class CAutoPtr
	{
	public:
		explicit CAutoPtr(_Ty *_P = 0)
			: _Owns(_P != 0),
			  _Ptr(_P)
		{
		}
		CAutoPtr(const CAutoPtr<_Ty> &_Right)
			: _Owns(_Right._Owns)
			, _Ptr(_Right.release())
		{
		}
		~CAutoPtr()
		{
			if (_Owns)
			{
				delete _Ptr;
			}
		}

	public:
		CAutoPtr<_Ty> &operator=(const CAutoPtr<_Ty> &_Right)
		{
			if (this != &_Right)
			{
				if (_Ptr != _Right.get())
				{
					if (_Owns)
					{
						delete _Ptr;
					}
					_Owns = _Right._Owns;
				}
				else if (_Right._Owns)
				{
					_Owns = true;
				}
				_Ptr = _Right.release();
			}
			return (*this);
		}
		CAutoPtr<_Ty> &operator=(_Ty *_P)
		{
			if (_Ptr != _P)
			{
				if (_Owns)
				{
					delete _Ptr;
				}
				_Owns = true;
			}
			_Ptr = _P;
			return (*this);
		}

		_Ty &operator*() const
		{
			return (*get());
		}
		_Ty *operator->() const
		{
			return (get());
		}
		_Ty *get() const
		{
			return (_Ptr);
		}
		_Ty *release() const
		{
			((CAutoPtr<_Ty> *)this)->_Owns = false;
			return (_Ptr);
		}
	private:
		bool _Owns;
		_Ty *_Ptr;
	};

	struct RoutedEventArgs
	{
		RoutedEventArgs()
			: RoutedEvent(0)
			, eRoutingStrategy(RS_DIRECT)
			, hSender(NULL)
			, hOriginalSender(NULL)
			, wParam(0)
			, lParam(0)
			, lResult(0)
			, bHandled(FALSE)
		{

		}
		UINT RoutedEvent;
		ROUTINGSTRATEGY eRoutingStrategy;
		HWLWND hSender;
		HWLWND hOriginalSender;
		WPARAM wParam;
		LPARAM lParam;
		LRESULT lResult; // RoutedEvent�¼��ķ���ֵ
		BOOL bHandled;
	};

	struct SProgressBarThumbMember
	{
		SProgressBarThumbMember()
			: m_bDrawThumbColor(false)
			, m_crThumbColorStart(RGB(255, 0, 0))
			, m_crThumbColorEnd(-1)
			, m_bCombineThumbImage(true)
			, m_bStretchThumbImage(true)
		{

		}
		virtual ~SProgressBarThumbMember() {}

		bool m_bDrawThumbColor;
		COLORREF m_crThumbColorStart;
		COLORREF m_crThumbColorEnd;	// ����ɫ��ֹ�����Ϊ-1����ʾ��ʹ�ý���ɫ

		bool m_bCombineThumbImage;
		CIUIString m_strCombineThumbImage;	// ��m_bCombineThumbImageΪfalseʱ����������״̬thumb image
		CIUIString m_strDisabledThumbImage;
		bool m_bStretchThumbImage;
	};

	// WindowCore�޶���ֻ��Windowʹ�á� CWLWnd��Ӧ����WindowCore�򽻵�
	// ����࣬Ҳ��Ӧ�ñ�¶���û�
	class IUIAPI WindowCore
	{
		friend class Window;

	public:
		WindowCore();
		~WindowCore();

	public:
		Window *GetBindWindow();

		void Init(HWND hWnd);

		LRESULT OnSpyControl(UINT uMsg, WPARAM wParam, LPARAM lParam);

		HDC GetPaintDC() const;
		HBITMAP GetOffscreenBitmap() const;
		HWND GetPaintWindow() const;
		HWND GetTooltipWindow() const;

		void EnableDPI(bool bEnable);
		bool IsDPIEnabled() const;

		POINT GetMousePos() const;
		SIZE GetClientSize() const;
		RECT &GetCaptionRect();

		// �涨һ�����򵱳ɱ�����������������϶������ƶ����ڣ�˫������󻯴��ڣ��������Ļ���
		void SetCaptionRect(RECT &rcCaption);

		SIZE GetMinInfo() const;
		void SetMinInfo(int cx, int cy);
		SIZE GetMaxInfo() const;
		void SetMaxInfo(int cx, int cy);
		bool IsShowUpdateRect() const;
		void SetShowUpdateRect(bool show);

		HINSTANCE GetInstance();
		CIUIString GetInstancePath();
		static CIUIString GetCurrentPath();
		HINSTANCE GetResourceDll();
		const CIUIString &GetResourceZip();
		bool IsCachedResourceZip();
		HANDLE GetResourceZipHandle();
		void SetInstance(HINSTANCE hInst);
		static void SetCurrentPath(LPCTSTR pStrPath);
		void SetResourceDll(HINSTANCE hInst);
		void SetResourceZip(LPVOID pVoid, unsigned int len);
		void SetResourceZip(LPCTSTR pstrZip, bool bCachedResourceZip = false);

		HWLWND GetFocus() const;

		void SetCapture();
		void ReleaseCapture();
		BOOL IsCaptured();

		CWLWnd *GetRoot() const;

		void Term();

		int InitWindow(HWND hWnd, CWindowProp *pWindowPorp);
		int DestroyAllRootControls();

	private:
		int GetClipBox(LPCRECT lprcPSPaint, LPRECT lpRect);
		int DeleteDCResource();
		int PrepareDCResource(HDC hPaintDC);
		int ShowOffscreenDC(HDC hPaintDC, const CIUIRect &rcClipHost);
		void OnPaint(HDC hdc, LPCRECT lprcPaint);
		LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);

	private:
		Window *m_pThis;
		bool m_bEnableDPI;
		HWND m_hWndPaint;
		HDC m_hDcOffscreen;                // �ڴ����DC��Ŀǰ������Layered���ڻ�����ͨ���ڣ���������ȫ�����Ƶ����������һ���Ի��Ƶ������ϡ�
		HDC m_hDcAlphaMask;                // ����ULW����ʱ��Alpha����DC.
		HBITMAP m_hbmpOffscreen;
		COLORREF *m_pOffscreenBits;
		HBITMAP m_hbmpAlphaMask;        // ����ULW����ʱ��Alpha�����ڴ����λͼ����ѡ��m_hDcAlphaMask.
		COLORREF *m_pAlphaMaskBits;        // m_hbmpAlphaMask�����ݲ��֡�
		HWND m_hwndTooltip;

		// TOOLINFO���붨��Ϊָ�룬�����������������
		// // A�ඨ����IUI�в�����
		// class IUIAPI A : public Window
		// {
		// public:
		//     void SetValue(n)
		//     {
		//         m_n = n;
		//     }
		//     int m_n;
		// };
		//
		// // B�ඨ������Ŀ��
		// class B: public A
		// {
		// };
		// // ������Ŀ�е���SetValue��ֵʱ�����뵽SetValue����ʱ��m_n�ĵ�ַ��������SetValue��ĵ�ַ�ǲ���ͬ��
		// B b;
		// b.SetValue(5);
		TOOLINFO *m_pToolTip;

		bool m_bShowUpdateRect;

		// �Ƿ�����Tab���л����㣬�����¹�Tab������ť��ʾ�����
		// һ��ʹ����������ؼ���������ʾ����򣬼�ʹĳ�ؼ�ӵ�н��㡣
		BOOL m_bPressedTabKey;
		//
		POINT m_ptLastMousePos;
		SIZE m_szMinWindow;
		SIZE m_szMaxWindow;
		CIUIRect m_rcCaption;
		UINT m_uTimerID;
		BOOL m_bNeedRelayoutChildren;
		BOOL m_bMouseCapture;

		//Դ��ʹ�õ��Ǿ�̬��Ա�����Ǿ�̬��Ա�ڶ��DLLģ��֮�乲��������⣬���Ըĳɳ�Ա���������������⡣
		HINSTANCE m_hInstance;
		HINSTANCE m_hResourceInstance;
		CIUIString m_pStrResourceZip;
		bool m_bCachedResourceZip;
		HANDLE m_hResourceZip;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class IUIAPI CControlBaseProp
	{
	public:
		CControlBaseProp();
		virtual ~CControlBaseProp();

		static int Copy(const CControlBaseProp *pSrc, CControlBaseProp *pDest);

	public:
		virtual BOOL IsControl() const;

		virtual LONG GetPropertyCount() const;
		virtual UIVARIANT *GetProperty(int nIndex);
		virtual const UIVARIANT *GetProperty(int nIndex) const;
		int SetVariant(int nIndex, const UIVARIANT *pVariant);
		int GetIndex(const UIVARIANT *pVar) const;

		virtual LONG GetUIVariantCount(void *pLastUiVariant) const;
		static CIUIString GetIDPrefix(CONTROL_TYPE eControlType);

		// Resource
		virtual bool IsFontResource() const;
		virtual bool IsColorResource() const;

		/**
		 @brief ������IUI�еĿؼ���C++������
		 @details
		 <pre>
		 </pre>
		 @author (Liusw)
		 @param[in]
		 @param[out]
		 @return
		  - ����IUI�еĿؼ���C++����
		*/
		virtual CIUIString GetClassName(BOOL bInCode = FALSE) const;
		/**
		 @brief �õ��ؼ���XML�ļ��е���������
		*/
		virtual LPCTSTR GetVariablePrefix() const;
		virtual CIUIString GetVariableName() const;

		void SetFileName(LPCTSTR lpszFileName);
		CIUIString GetFileName() const;

		virtual int AddChild(CControlBaseProp *pChildProp);
		virtual int InsertChild(int nIndex, CControlBaseProp *pChildProp);
		virtual int DeleteChild(CControlBaseProp *pProp);
		// RemoveChild��DeleteChild�������ǣ�ǰ��ֻ�Ƴ������ͷ��ڴ�
		virtual int RemoveChild(int nIndex);
		virtual int DeleteAllChildren();
		CControlBaseProp *GetChild(int nIndex);
		const CControlBaseProp *GetChild(int nIndex) const;
		int GetChildCount() const;
		// �ݹ����ָ�����ֵĺ���
		CControlBaseProp *FindChild(LPCTSTR lpszName);
		const CControlBaseProp *FindChild(LPCTSTR lpszName) const;

		/**
		 @brief ������������Ԫ��
		 @details
		 <pre>
		 Ԫ�ص�˳��Ϊ����˳��
		 </pre>
		 @author (Liusw)
		 @param[out] pvControls: ������������Ԫ��
		 @param[in] bIncludeSelf: ���ص��б��У��Ƿ��������
		 @return
		  - 0  �ɹ�
		  - -1 ʧ��
		*/
		int GetChildList(
			std::vector<CControlBaseProp *> *pvControls,
			BOOL bIncludeSelf);

		int GetChildList(
			std::vector<const CControlBaseProp *> *pvControls,
			BOOL bIncludeSelf) const;

		CControlBaseProp *GetParent();
		const CControlBaseProp *GetParent() const;

		int SetBindCtrl(HWLWND hBindCtrl);
		HWLWND GetBindCtrl() const;

	protected:
		static int InitBoolVariant(
			UIVARIANT *pVariant,
			bool bInitValue,
			LPCTSTR lpszIUIElementName,
			LPCTSTR lpszPropWndName,
			bool bGroup = false,
			LPCTSTR lpszGroupName = NULL);

		static int InitResFontIDVariant(
			UIVARIANT *pVariant,
			LPCTSTR lpszIUIElementName,
			LPCTSTR lpszPropWndName,
			bool bGroup = false,
			LPCTSTR lpszGroupName = NULL);

		static int InitResColorIDVariant(
			UIVARIANT *pVariant,
			LPCTSTR lpszIUIElementName,
			LPCTSTR lpszPropWndName,
			bool bGroup = false,
			LPCTSTR lpszGroupName = NULL);

	protected:
		CIUIString m_strFileName;
		CControlBaseProp *m_pParent;
		HWLWND m_hBindCtrl;
		std::vector<CControlBaseProp *> *m_pvControls; ///< m_pvControls������Ϊ��UIVARIANT���͵ĵ�һ��

	public:
		/**
		 @brief ������������UIVARIANT��������
		*/
		UIVARIANT m_lStructSize; ///< m_lStructSize������ΪUIVARIANT���͵ĵ�һ��
		UIVARIANT m_eControlType; ///< m_eControlType������ΪUIVARIANT���͵ĵڶ���

		/**
		 @brief ����������������ŵ�UIVARIANT���ͱ�������ǰ�棬\n
		 ���ұ���˳�򲻱䣬Ҳ�������м��������������\n
		 �Է����������UIVARIANT�ĸ���������UIVARIANT����forѭ����\n
		 ���Ҫ���ӷ�UIVARIANT���ͱ���������ӵ�pvControls֮�󣬲��Ҽӵ�lStructSize֮ǰ��
		*/

		// General group.
		UIVARIANT m_strName;
	};

	class IUIAPI CControlProp : public CControlBaseProp
	{
	public:
		CControlProp();
		virtual ~CControlProp();

	public:
		virtual BOOL IsControl() const;

		// disable some properties
		int DisableBackgroundProperties(BOOL bKeepND, BOOL bDisabelChecked);
		int DisableCheckedBackgroundColorProperties();
		int DisableCheckedBackgroundImageProperties();
		int DisableFontProperties(BOOL bKeepND);
		int DisableTextColorProperties(BOOL bKeepND);
		int DisableBkColorProperties(BOOL bKeepND, BOOL bDisabelChecked);
		int DisableBorderColorGroup(BOOL bKeepND, BOOL bDisabelChecked);
		int DisableCheckedBorderColorProperties();
		int DisableCaptionGroup();
		int DisableTooltipsGroup();

		static int GetControlFont1(const CControlProp *pCtrlProp, CIUIString *pstrFontResID);
		static int GetControlFont2(const CControlProp *pCtrlProp, CIUIString *pstrFontResID);
		static int GetControlFont4(const CControlProp *pCtrlProp, CIUIString *pstrFontResID);
		static int GetControlFont8(
			const struct CToggleButtonProp *pCtrlProp,
			CIUIString *pstrFontResID);

		static int GetBackground2(
			const CControlProp *pCtrlProp,
			BOOL *pbCombineImage,
			CIUIString *pstrImageName);
		static int GetBackground4(
			const CControlProp *pCtrlProp,
			BOOL *pbCombineImage,
			CIUIString *pstrImageName);

		static int GetToggleButtonBackground8(
			const CToggleButtonProp *pCtrlProp,
			BOOL *pbCombineImage,
			CIUIString *pstrImageName);
		static int GetToggleButtonForeground8(
			const CToggleButtonProp *pCtrlProp,
			BOOL *pbCombineImage,
			CIUIString *pstrImageName);

		static int GetButtonForeground4(
			const class CButtonBaseProp *pCtrlProp,
			BOOL *pbCombineImage,
			CIUIString *pstrImageName);

		//static int GetThumbImages4(
		//	const class HORSBPROPERTIES *pCtrlProp,
		//	BOOL *pbCombineImage,
		//	CIUIString *pstrImageName);
		//static int GetThumbImages4(
		//	const class VERSBPROPERTIES *pCtrlProp,
		//	BOOL *pbCombineImage,
		//	CIUIString *pstrImageName);
		static int GetThumbImages4(
			const class CSliderProp *pCtrlProp,
			BOOL *pbCombineImage,
			CIUIString *pstrImageName);

		static CIUIStringW GetLanguageKey(
			const CIUIProject *pProject,
			const class CControlProp *pCtrlProp,
			BOOL *pbFound);

	public:
		UIVARIANT m_lWidth;
		UIVARIANT m_lHeight;
		UIVARIANT m_rcControl;
		UIVARIANT m_bVisible;
		UIVARIANT m_bEnabled;
		UIVARIANT m_bTabStop;
		// ����Ϊ��������ʱ����ʾΪ���ڼ���WS_CLIPCHILDREN���
		// ����Ϊ�ؼ�����ʱ����ʾ�ü����������ؼ���Χ���ӿؼ����֡�
		UIVARIANT m_bClipChildren;
		UIVARIANT m_lTitlebarHeight;
		UIVARIANT m_bMouseTransparent;
		UIVARIANT m_strBindXml;

		// Layout group
		UIVARIANT m_eHorLayoutMode;
		UIVARIANT m_eVerLayoutMode;
		UIVARIANT m_eDockProperty;

		/**
		 @brief ��߾࣬��ؼ����ڵĸ������йأ���������Ϊˮƽ��ֱ���֣���ʾ������ֵܵļ�࣬
		 ��������ΪCanvasʱ����ʾ��Եظ����ֱ߿�ı߾�
		*/
		UIVARIANT m_rcLayoutMargin;
		UIVARIANT m_rcInset; ///< �ڱ߾�

		// Background group.
		UIVARIANT m_bDrawBkColor;
		// Ϊ��ʹÿ�ֿؼ����������Զ����ţ���Щ���Զ����嵽CControlProp��
		UIVARIANT m_strBkColorResIDN;
		UIVARIANT m_strBkColorResIDH;
		UIVARIANT m_strBkColorResIDP;
		UIVARIANT m_strBkColorResIDD;
		UIVARIANT m_strBkColorResIDCN;
		UIVARIANT m_strBkColorResIDCH;
		UIVARIANT m_strBkColorResIDCP;
		UIVARIANT m_strBkColorResIDCD;

		UIVARIANT m_bCombineBackgroundImages;
		UIVARIANT m_strBKCombine;
		UIVARIANT m_strBKImageN;
		UIVARIANT m_strBKImageH;
		UIVARIANT m_strBKImageP;
		UIVARIANT m_strBKImageD;
		UIVARIANT m_strBKImageCN;
		UIVARIANT m_strBKImageCH;
		UIVARIANT m_strBKImageCP;
		UIVARIANT m_strBKImageCD;
		UIVARIANT m_lBkImgTransparent; // 0-255
		UIVARIANT m_eBkImageResizeMode; // IMAGE_RESIZE_MODE
		UIVARIANT m_rcBkImage9GridResizeArg; // 9��������ʱ�Ĳ���

		// Border group.
		UIVARIANT m_bDrawBorderColor;
		UIVARIANT m_strBorderColorResIDN;
		UIVARIANT m_strBorderColorResIDH;
		UIVARIANT m_strBorderColorResIDP;
		UIVARIANT m_strBorderColorResIDD;
		UIVARIANT m_strBorderColorResIDCN;
		UIVARIANT m_strBorderColorResIDCH;
		UIVARIANT m_strBorderColorResIDCP;
		UIVARIANT m_strBorderColorResIDCD;
		UIVARIANT m_ptBorderRound;

		// Caption group.
		UIVARIANT m_strCaption;
		UIVARIANT m_rcPadding4Text;

		// ������ɫ
		UIVARIANT m_strTextColorResIDN;
		UIVARIANT m_strTextColorResIDH;
		UIVARIANT m_strTextColorResIDP;
		UIVARIANT m_strTextColorResIDD;
		UIVARIANT m_strTextColorResIDCN;
		UIVARIANT m_strTextColorResIDCH;
		UIVARIANT m_strTextColorResIDCP;
		UIVARIANT m_strTextColorResIDCD;

		// Font(Size) group.
		UIVARIANT m_strResFontIDN;
		UIVARIANT m_strResFontIDH;
		UIVARIANT m_strResFontIDP;
		UIVARIANT m_strResFontIDD;

		// ToolTip group.
		UIVARIANT m_bUseToolTip;
		UIVARIANT m_strToolTip;
		UIVARIANT m_strToolTipStyle;
	};

	class IUIAPI CLabelProp : public CControlProp
	{
	public:
		CLabelProp();
		virtual ~CLabelProp();

		UIVARIANT m_strButtonClickArg;

		// Caption group.
		UIVARIANT m_eTextHorAlignMode;
		UIVARIANT m_eTextVerAlignMode;
		UIVARIANT m_bR2LReadOrder;
		UIVARIANT m_bMultiline;
		UIVARIANT m_bPathEllipsis; ///< only valid while m_bNoWrap is TRUE.
		UIVARIANT m_bEndEllipsis; ///< only valid while m_bNoWrap is TRUE.

		// Shadow Text group.
		UIVARIANT m_bShadowText;
		UIVARIANT m_strTextShadowColorResID;
		UIVARIANT m_ptTextShadowOffset;
	};

	class IUIAPI CButtonBaseProp : public CLabelProp
	{
	public:
		CButtonBaseProp();
		virtual ~CButtonBaseProp();

		// Background group.
		UIVARIANT m_strMaskBmp;

		// Foreground group.
		UIVARIANT m_bSpecifyForegroundImages;
		UIVARIANT m_bCombineForegroundImages;
		UIVARIANT m_strFGCombine;
		UIVARIANT m_strFGImageN;
		UIVARIANT m_strFGImageH;
		UIVARIANT m_strFGImageP;
		UIVARIANT m_strFGImageD;
		UIVARIANT m_strFGImageCN;
		UIVARIANT m_strFGImageCH;
		UIVARIANT m_strFGImageCP;
		UIVARIANT m_strFGImageCD;
		UIVARIANT m_eForegroundHorAlignMode;
		UIVARIANT m_eForegroundVerAlignMode;
		UIVARIANT m_rcPadding4Foreground;

		// ToolTip group.
		UIVARIANT m_lAutoPopDelayTime; ///< See MSDN: CToolTipCtrl::GetDelayTime.
		UIVARIANT m_lInitialDelayTime;
		UIVARIANT m_lReshowDelayTime;

		// Misc group.
		UIVARIANT m_strModalDlgID; ///< Click the button will popup a modal dialog;
		UIVARIANT m_strModelessWndID; ///< Click the button will popup a modeless window.
	};

	class IUIAPI CButtonProp : public CButtonBaseProp
	{
	public:
		CButtonProp();
		virtual ~CButtonProp();

	public:
		UIVARIANT m_eBtnType;
		UIVARIANT m_bDefPushButton;
	};

	struct IUIAPI CToggleButtonProp : public CButtonProp
	{
		CToggleButtonProp();
		virtual ~CToggleButtonProp();

		UIVARIANT m_strResFontIDCN;
		UIVARIANT m_strResFontIDCH;
		UIVARIANT m_strResFontIDCS;
		UIVARIANT m_strResFontIDCD;

		UIVARIANT m_bCNSameNColor;
		UIVARIANT m_strResColorIDCN;
		UIVARIANT m_bCHSameNColor;
		UIVARIANT m_strResColorIDCH;
		UIVARIANT m_bCSSameNColor;
		UIVARIANT m_strResColorIDCS;
		UIVARIANT m_bCDSameNColor;
		UIVARIANT m_strResColorIDCD;
	};

	class IUIAPI CCheckBoxProp : public CToggleButtonProp
	{
	public:
		CCheckBoxProp();
		virtual ~CCheckBoxProp();

		UIVARIANT m_eChkType;
	};

	class IUIAPI CRadioButtonProp : public CToggleButtonProp
	{
	public:
		CRadioButtonProp();
		virtual ~CRadioButtonProp();

		UIVARIANT m_bGroup;

		// �󶨵�����ҳ��ID��
		UIVARIANT m_strBindTaskWndID;
		// �󶨵�TabControl ID
		UIVARIANT m_strBindTaskMgrID;
	};

	class IUIAPI CRichTextBoxProp : public CControlProp
	{
	public:
		CRichTextBoxProp();
		virtual ~CRichTextBoxProp();

		UIVARIANT m_bHScroll;
		UIVARIANT m_bVScroll;
		UIVARIANT m_bAutoHScroll;
		UIVARIANT m_bAutoVScroll;
		UIVARIANT m_bDisableNoScroll; ///< For Rich Edit
		UIVARIANT m_bLowercase;
		UIVARIANT m_bUppercase;
		UIVARIANT m_bNumber;
		UIVARIANT m_bPassword;
		UIVARIANT m_bReadOnly;
		UIVARIANT m_bMultiline;
		UIVARIANT m_bWantReturn;
		UIVARIANT m_bR2LReadOrder;

		UIVARIANT m_eTextHorAlignMode;
	};

	class IUIAPI CIMRichTextBoxProp : public CRichTextBoxProp
	{
	public:
		CIMRichTextBoxProp();
		virtual ~CIMRichTextBoxProp();

	};

	class IUIAPI CComboBoxProp : public CLabelProp
	{
	public:
		CComboBoxProp();
		virtual ~CComboBoxProp();

		UIVARIANT m_eComboStyle;
		UIVARIANT m_bVScroll;
		UIVARIANT m_bAutoHScroll;
		UIVARIANT m_bDisableNoScroll;
		UIVARIANT m_bSort;
		UIVARIANT m_bUppercase;
		UIVARIANT m_bLowercase;

		// Edit Box Group
		UIVARIANT m_rcEditMargin;

		// Button Group
		UIVARIANT m_lBtnWidth;
		UIVARIANT m_rcButtonMargin;

		// Button Bk
		UIVARIANT m_bDrawDropButtonBkColor;
		UIVARIANT m_strDropButtonBkResColorIDN;
		UIVARIANT m_strDropButtonBkResColorIDH;
		UIVARIANT m_strDropButtonBkResColorIDP;
		UIVARIANT m_strDropButtonBkResColorIDD;
		UIVARIANT m_strDropButtonBkResColorIDS;
		UIVARIANT m_strDropButtonCombineBkImage;
		UIVARIANT m_strDropButtonBkImageN;
		UIVARIANT m_strDropButtonBkImageH;
		UIVARIANT m_strDropButtonBkImageP;
		UIVARIANT m_strDropButtonBkImageD;
		UIVARIANT m_strDropButtonBkImageS;
		UIVARIANT m_bDrawDropButtonBorderColor;
		UIVARIANT m_strDropButtonBorderResColorIDN;
		UIVARIANT m_strDropButtonBorderResColorIDH;
		UIVARIANT m_strDropButtonBorderResColorIDP;
		UIVARIANT m_strDropButtonBorderResColorIDD;
		UIVARIANT m_strDropButtonBorderResColorIDS;
		// Button Arrow image.
		UIVARIANT m_bSpecifyButtonArrowImage;
		UIVARIANT m_bCombineButtonArrowImage;
		UIVARIANT m_strCombineButtonArrowImage;
		UIVARIANT m_strButtonArrowN;
		UIVARIANT m_strButtonArrowH;
		UIVARIANT m_strButtonArrowS;
		UIVARIANT m_strButtonArrowD;
		UIVARIANT m_eButtonArrowHorAlignMode;
		UIVARIANT m_eButtonArrowVerAlignMode;
		UIVARIANT m_rcPadding4ButtonArrow;

		// Drop List Group.
		UIVARIANT m_lDropListItemHeight;
		UIVARIANT m_lDropListHeight;

		UIVARIANT m_strHighlightItemBkColorResID;
	};

	class IUIAPI CSpinButtonProp : public CControlProp
	{
	public:
		CSpinButtonProp();
		virtual ~CSpinButtonProp();

		UIVARIANT m_eAlignMode;
		UIVARIANT m_bVertical;
		UIVARIANT m_bAutoBuddy;
		UIVARIANT m_bSetBuddyInt;
		UIVARIANT m_bNoThousands;
		UIVARIANT m_bWrap;
		UIVARIANT m_bArrowKeys;
		UIVARIANT m_bHotTrack;
	};

	class IUIAPI CSliderProp : public CControlProp
	{
	public:
		CSliderProp();
		virtual ~CSliderProp();

		UIVARIANT m_eExtendedStyle;
		UIVARIANT m_bVertical;
		UIVARIANT m_bUseMark;
		UIVARIANT m_bMarkToThumb; ///< TRUE: Stretch(9 Grid or tile) mark image to thumb; FALSE: to all client.
		// TRUE: ����ֱ�ӻ������������������FALSE������ģʽ�����鲽�����������
		UIVARIANT m_bThumbPositionMode;

		// Thumb group
		UIVARIANT m_bDrawThumbColor;
		UIVARIANT m_strThumbBkColorRes;
		UIVARIANT m_strThumbBorderColorRes;

		UIVARIANT m_bCombineThumbImages;
		UIVARIANT m_strThumbCombine;
		UIVARIANT m_strThumbN;
		UIVARIANT m_strThumbH;
		UIVARIANT m_strThumbP;
		UIVARIANT m_strThumbD;

		// ˮƽSlider����ĳߴ�
		UIVARIANT m_lThumbWidth;
		UIVARIANT m_lThumbHeight;

		// TRACKBAR::rc����߾�
		UIVARIANT m_rcScrollAreaMargin;

		UIVARIANT m_bEnableTipWindow;
		UIVARIANT m_sizeTipWindowOffset;
	};

	class IUIAPI CProgressBarProp : public CLabelProp
	{
	public:
		CProgressBarProp();
		virtual ~CProgressBarProp();

		UIVARIANT m_bVertical;

		UIVARIANT m_eThumbMode; ///< PROGRESS_THUMB_MODE
		UIVARIANT m_bCombineThumbImages;
		UIVARIANT m_strThumbCombine;
		UIVARIANT m_strThumbN;
		UIVARIANT m_strThumbD;
		UIVARIANT m_eThumbPosition; ///< PROGRESS_THUMB_POSITION
		UIVARIANT m_rcThumbOriginalSpecified;
		UIVARIANT m_bDrawThumbColor;
		UIVARIANT m_strThumbBkColorRes;
		UIVARIANT m_strThumbBorderColorRes;

		UIVARIANT m_bShowText;
		UIVARIANT m_lHorAlignN;
		UIVARIANT m_lVerAlignN;
	};

	class IUIAPI CColumnHeaderProp : public CControlProp
	{
	public:
		CColumnHeaderProp();
		virtual ~CColumnHeaderProp();

		UIVARIANT m_bHeaderTrack;
		UIVARIANT m_bHeaderDragDrop;

		UIVARIANT m_bCombineButtonImage;
		UIVARIANT m_strButtonBkCombine;
		UIVARIANT m_strButtonBKImageN;
		UIVARIANT m_strButtonBKImageH;
		UIVARIANT m_strButtonBKImageP;
		UIVARIANT m_strButtonBKImageD;
		UIVARIANT m_eButtonBkImageResizeMode;
		UIVARIANT m_rcButtonBkImage9GridResizeArg;
	};

	class IUIAPI CListViewProp : public CControlProp
	{
	public:
		CListViewProp();
		virtual ~CListViewProp();

		UIVARIANT m_eListStyle;
		UIVARIANT m_eListSort;
		UIVARIANT m_bEditLabels;
		UIVARIANT m_bShowSelAlways;
		UIVARIANT m_bSingleSel;
		UIVARIANT m_bHoldCtrlKey; ///< Only valid while m_bSingleSel is false.
		UIVARIANT m_bOwnerData;
		UIVARIANT m_bCheckBoxes;
		UIVARIANT m_bInfoTooltip;
		UIVARIANT m_bTwoClickActivate;
		UIVARIANT m_lItemHeight;

		UIVARIANT m_bFullRowSelect;
		UIVARIANT m_bSubItemImages;

		UIVARIANT m_eListAlign;
		UIVARIANT m_bAutoArrange; ///< for icon and small icon view
		UIVARIANT m_bNoScroll; ///< This style is not compatible with the LVS_LIST or LVS_REPORT styles
		UIVARIANT m_bNoLabelWrap; ///< for icon view

		UIVARIANT m_bShowGridLine;
		UIVARIANT m_bDraw0Row; ///< Draw 0 row or not. Only valid while bEnableOwnerDraw is true.
		UIVARIANT m_lXOffset; ///< The horizontal offset of the line. Only valid while bEnableOwnerDraw is true.
		UIVARIANT m_strGridLineColorRes; ///< Only valid while bEnableOwnerDraw is true.

		// Focus(Caret) Item
		UIVARIANT m_eFocusItemBkType;
		UIVARIANT m_strFocusItemBkColorResID;
		UIVARIANT m_strFocusItemBkImage;
		UIVARIANT m_rcFocusItemBkImage9GridArg;

		// Highlight Item
		UIVARIANT m_bEnableHighlightItemEffect;	// LVS_EX_TRACKSELECT
		UIVARIANT m_eHighlightItemBkType;
		UIVARIANT m_strHighlightItemBkColorResID;
		UIVARIANT m_strHighlightItemBkImage;
		UIVARIANT m_rcHighlightItemBkImage9GridArg;

		// Selected Item
		UIVARIANT m_bSelectedFitClient; ///< Only valid while list with report style
		UIVARIANT m_eSelectedItemBkType;
		UIVARIANT m_strSelectedItemBkColorResID;
		UIVARIANT m_strSelectedItemBkImage;
		UIVARIANT m_rcSelectedItemBkImage9GridArg;

		// Selected Disabled Item
		UIVARIANT m_eSelectedDisabledItemBkType;
		UIVARIANT m_strSelectedDisabledItemBkColorResID;
		UIVARIANT m_strSelectedDisabledItemBkImage;
		UIVARIANT m_rcSelectedDisabledItemBkImage9GridArg;
		UIVARIANT m_strResFontIDSD;
		UIVARIANT m_strResColorIDSD;

		// ������Iconģʽʱ��Item��࣬������Ϊ������Item������Է����ѡItem������
		UIVARIANT m_lIconModeTotalItemWidth;
		UIVARIANT m_lIconModeTotalItemHeight;

		// Header
		UIVARIANT m_bNoHeader;
		UIVARIANT m_bNoSortHeader;
		UIVARIANT m_nHeaderHeight;
		UIVARIANT m_lItemHeaderSpace; // Header��report view Item�䴹ֱ���
		UIVARIANT m_bHeaderTrack;
		UIVARIANT m_bHeaderDragDrop;
		UIVARIANT m_strHeaderStyleID;

		// Scroll Bar
		UIVARIANT m_lScrollBarWidth;
		UIVARIANT m_strHorScrollbarID;
		UIVARIANT m_strVerScrollbarID;
	};

	class IUIAPI CTreeViewProp : public CControlProp
	{
	public:
		CTreeViewProp();
		virtual ~CTreeViewProp();

		UIVARIANT m_bCheckBoxes;
		UIVARIANT m_bHasButtons;
		UIVARIANT m_bHasLines;
		UIVARIANT m_bLinesAtRoot;
		UIVARIANT m_bFullRowSel;
		UIVARIANT m_bShowSelAlways;
		UIVARIANT m_bDisableDragDrop;
		UIVARIANT m_bEditLabels;
		UIVARIANT m_bScroll;
		UIVARIANT m_bSmoothVScroll;
		UIVARIANT m_bNonEvenHeight;
		UIVARIANT m_bSingleExpand;
		UIVARIANT m_bInfoTip;
		UIVARIANT m_bToolTips;
		UIVARIANT m_bDefaultItemHeight;
		UIVARIANT m_nItemHeight;

		// Item Line
		UIVARIANT m_bEnableItemLineEffect;
		UIVARIANT m_strItemLineColorResID;

		// Collapse and Expand image
		UIVARIANT m_strCombineCollapseExpandedImage;
		UIVARIANT m_strCollapseImageN;
		UIVARIANT m_strCollapseImageH;
		UIVARIANT m_strCollapseImageS;
		UIVARIANT m_strCollapseImageD;
		UIVARIANT m_strExpandedImageN;
		UIVARIANT m_strExpandedImageH;
		UIVARIANT m_strExpandedImageS;
		UIVARIANT m_strExpandedImageD;

		// Text horizontal alignment
		UIVARIANT m_eTextHorAlignModeN;
		UIVARIANT m_eTextHorAlignModeH;
		UIVARIANT m_eTextHorAlignModeS;
		UIVARIANT m_eTextHorAlignModeD;

		// Text vertical alignment
		UIVARIANT m_eTextVerAlignModeN;
		UIVARIANT m_eTextVerAlignModeH;
		UIVARIANT m_eTextVerAlignModeS;
		UIVARIANT m_eTextVerAlignModeD;

		// Text Margin
		UIVARIANT m_rcTextMarginN;
		UIVARIANT m_rcTextMarginH;
		UIVARIANT m_rcTextMarginP;
		UIVARIANT m_rcTextMarginD;

		// Focus Item
		UIVARIANT m_eFocusItemBkType;
		UIVARIANT m_strFocusItemBkColorResID;
		UIVARIANT m_strFocusItemBkImage;
		UIVARIANT m_rcFocusItemBkImage9GridResize;

		// Selected Item
		UIVARIANT m_eSelectedItemBkType;
		UIVARIANT m_strSelectedItemBkColorResID;
		UIVARIANT m_strSelectedItemBkImageN;
		UIVARIANT m_strSelectedItemBkImageD;
		UIVARIANT m_rcSelectedItemBkImage9GridResize;

		// Highlight Item
		UIVARIANT m_bEnableHighlightItemEffect;
		UIVARIANT m_eHighlightItemBkType;
		UIVARIANT m_strHighlightItemBkColorResID;
		UIVARIANT m_strHighlightItemBkImageN;
		UIVARIANT m_strHighlightItemBkImageD;
		UIVARIANT m_rcHighlightItemBkImage9GridResize;

		// Scroll bar
		UIVARIANT m_lScrollBarWidth;
		UIVARIANT m_strHorScrollbarID;
		UIVARIANT m_strVerScrollbarID;
	};

	class IUIAPI CHtmlViewProp : public CControlProp
	{
	public:
		CHtmlViewProp();
		virtual ~CHtmlViewProp();

		UIVARIANT m_bHideBorder;
		UIVARIANT m_bHideScrollBar;
		UIVARIANT m_bHideContextMenu;
		UIVARIANT m_strStartPage;
	};

	class IUIAPI CSplitterBarProp : public CControlProp
	{
	public:
		CSplitterBarProp();
		virtual ~CSplitterBarProp();
	};

	class IUIAPI CDateTimePickerProp : public CControlProp
	{
	public:
		CDateTimePickerProp();
		virtual ~CDateTimePickerProp();

		UIVARIANT m_eFormat; ///< DATETIME_FORMAT
		UIVARIANT m_bUseSpinControl; ///< Must be true while format is time.
		UIVARIANT m_strSpinButtonStyleID;
		UIVARIANT m_bShowNone;
		UIVARIANT m_bAllowEdit;
		UIVARIANT m_lButtonWidth;
		UIVARIANT m_ptTextOffset;
	};

	class IUIAPI CScrollBarProp : public CControlProp
	{
	public:
		CScrollBarProp();
		virtual ~CScrollBarProp();

		UIVARIANT m_bCombineButton1Image;
		UIVARIANT m_strButton1Combine;
		UIVARIANT m_strButton1ImageN;
		UIVARIANT m_strButton1ImageH;
		UIVARIANT m_strButton1ImageP;
		UIVARIANT m_strButton1ImageD;
		UIVARIANT m_rcButton1Image9GridResize;

		UIVARIANT m_bCombineButton2Image;
		UIVARIANT m_strButton2Combine;
		UIVARIANT m_strButton2ImageN;
		UIVARIANT m_strButton2ImageH;
		UIVARIANT m_strButton2ImageP;
		UIVARIANT m_strButton2ImageD;
		UIVARIANT m_rcButton2Image9GridResize;

		UIVARIANT m_bCombineThumbImage;
		UIVARIANT m_strThumbCombine;
		UIVARIANT m_strThumbN;
		UIVARIANT m_strThumbH;
		UIVARIANT m_strThumbP;
		UIVARIANT m_strThumbD;
		UIVARIANT m_rcThumbResize;

		UIVARIANT m_strArrow1; ///< ����ϰ�ť
		UIVARIANT m_strArrow2; ///< �һ��°�ť

		UIVARIANT m_nButton1Width; /// ����ϰ�ť�ķ�Χ
		UIVARIANT m_nButton2Width; /// �һ��°�ť�ķ�Χ
	};

	class IUIAPI CPanelBaseProp : public CLabelProp
	{
	public:
		CPanelBaseProp();
		virtual ~CPanelBaseProp();
	};

	class IUIAPI CTabControlProp : public CPanelBaseProp
	{
	public:
		CTabControlProp();
		virtual ~CTabControlProp();
	};

	class IUIAPI CDockPanelProp : public CPanelBaseProp
	{
	public:
		CDockPanelProp();
		virtual ~CDockPanelProp();

		// ����ؼ���DockPanel�ĺ��ӣ��ؼ�ͬʱ������Layout Mode���Ժ�DockProperty���ԣ�
		// ���������ֶ��뷽ʽ����г�ͻ����ôIUI����ô�����أ�IUI�Ĵ���ʽ���WPF��
		// �������£�
		// 1.���һ���ؼ���LastChildFill���Ե�Ӱ�죬��LastChildFillΪtrueʱ��
		// ��Layout Mode�����ö���; ��Ϊfalseʱ����DockProperty�����ö���;
		// 2.����ǰ��Ŀؼ���DockProperty��Ӱ�죬��Layout Mode�����޹ء�
		UIVARIANT m_bLastChildFill;
	};

	class IUIAPI CUniformGridProp : public CPanelBaseProp
	{
	public:
		CUniformGridProp();
		virtual ~CUniformGridProp();
	};

	class IUIAPI CCanvasProp : public CPanelBaseProp
	{
	public:
		CCanvasProp();
		virtual ~CCanvasProp();
	};

	class IUIAPI CStackPanelProp : public CPanelBaseProp
	{
	public:
		CStackPanelProp();
		virtual ~CStackPanelProp();
	};
	/**
	 @class CStringTableProp
	 @brief XML�ж�����ַ�����
	 @details ��Դ��������ڶ���ַ�����
	 @author (Liusw)
	 @date 2016/10/29 13:54
	*/
	class IUIAPI CStringTableProp : public CControlProp
	{
	public:
		CStringTableProp();
		virtual ~CStringTableProp();
	};

	/**
	 @class CFontProp
	 @brief ������Դ����
	*/
	class IUIAPI CFontProp : public CControlBaseProp
	{
	public:
		CFontProp();
		virtual ~CFontProp();

		virtual bool IsFontResource() const;

	public:
		UIVARIANT m_logFont;
	};

	// ��ɫ��Դ
	class IUIAPI CColorProp : public CControlBaseProp
	{
	public:
		CColorProp();
		virtual ~CColorProp();

	public:
		UIVARIANT m_crColor;
	};

	// �ַ�����Դ
	class IUIAPI CStringProp : public CControlBaseProp
	{
	public:
		CStringProp();
		virtual ~CStringProp();

	public:
		UIVARIANT m_strStringValue;
	};

	class IUIAPI CWindowProp : public CControlProp
	{
	public:
		CWindowProp();
		virtual ~CWindowProp();

	public:
		UIVARIANT m_bNoActivate;
		UIVARIANT m_bClipSiblings;
		UIVARIANT m_bAppWindow;
		UIVARIANT m_bLayeredWindow;
		UIVARIANT m_bAlpha;
		UIVARIANT m_btAlphaValue;
		UIVARIANT m_bUpdateLayeredWindow;
		UIVARIANT m_eAlphaFormat; // ALPHA_FORMAT
		UIVARIANT m_bTopmost;
		UIVARIANT m_bAcceptFiles;
		UIVARIANT m_bToolWindow;
		UIVARIANT m_eWindowType;
		UIVARIANT m_bWindow;

		// Border Group
		UIVARIANT m_bResizingBorder;
		UIVARIANT m_bTrueResizingBorder; // Add WS_THICKFRAME style

		// ʹ��˫����������Ӱ�߿�
		// m_rcShadowThinknessΪ�߿���Ӱ�ĺ�ȣ�ͬʱҲ��9�������Ų���,
		// m_bTransparentBorder��ʾ�߿���Ӱ�Ƿ�͸���
		// m_bResizingShadow��ʾ�Ƿ������������shadow�ı䴰�ڳߴ磬����
		// (m_bResizingBorder && !m_bTrueResizingBorder && !m_bTransparentShadow)ʱ��Ч
		UIVARIANT m_strShadowBorder;
		UIVARIANT m_rcShadowThinkness;
		UIVARIANT m_bTransparentShadow;
		UIVARIANT m_bResizingShadow;
	};

	class IUIAPI CToolTipCtrlProp : public CWindowProp
	{
	public:
		CToolTipCtrlProp();
		virtual ~CToolTipCtrlProp();

		UIVARIANT m_rcTextMargin;
	};

	//////////////////////////////////////////////////////////////////////////

	class IUIAPI CWLWndHandler
	{
		friend class CWLWnd;
		friend struct WLWND;
		friend class Window;
		friend LRESULT CallIUIHandlerMap(HWLWND, RoutedEventArgs *);
		friend HWLWND CreateWindowEx(CWLWndHandler *, DWORD, LPCTSTR, LPCTSTR, DWORD, int, int, int, int, HWND, HWLWND, LPCTSTR, HINSTANCE, LPVOID);

	public:
		CWLWndHandler();
		virtual ~CWLWndHandler();

		virtual LRESULT EventHandler(HWLWND hWnd, RoutedEventArgs *pe);

		HWLWND GetBindWLWnd();

		LPARAM SetUserData(LPARAM lParam);
		LPARAM GetUserData() const;

	protected:
		int m_nMsgHandlerCount;

	private:
		HWLWND m_hBindWLWnd;
		LPARAM m_lParam;	// User data
	};

	typedef LRESULT(CWLWndHandler::*IUI_PWLMSGHANDLER)(HWLWND, RoutedEventArgs *);

	struct IUIAPI IUI_WLMSGHANDLER_MAP	// See also: AFX_MSGMAP_ENTRY, BEGIN_MESSAGE_MAP
	{
		UINT RoutedEvent;
		ROUTINGSTRATEGY eRoutingStrategy;
		CIUIString strControlName;
		IUI_PWLMSGHANDLER pfn;	// routine to call (or special value)
	};


	class IUIAPI CWndHandler
	{
		friend class Window;

	public:
		CWndHandler();
		virtual ~CWndHandler();

		//virtual const struct IUI_MSGHANDLER_MAP *GetMessageMap() const;

		int SetBindWindow(Window *pBindWindow);
		Window *GetBindWindow();
		const Window *GetBindWindow() const;

		LPARAM SetUserData(LPARAM lParam);
		LPARAM GetUserData() const;

	protected:
		virtual LRESULT WindowProc(Window *pThis, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		int m_nMsgHandlerCount;

	private:
		Window *m_pBindWindow;
		LPARAM m_lParam;	// User data
	};

	LRESULT CALLBACK IUIWndProcBase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	class IUIAPI Window
	{
		friend class WindowCore;
		friend class CWLWnd;
		friend LRESULT CALLBACK IUI::IUIWndProcBase(HWND, UINT, WPARAM, LPARAM);
		friend int ResizeWindowByMouse(HWND, POINT, POINT, UINT, LPCRECT);
		friend LRESULT CALLBACK IUICbtFilterHook(int, WPARAM, LPARAM);

	public:
		Window();
		virtual ~Window();

		HWND GetHWND() const;
		HWND GetSafeHwnd() const;
		operator HWND() const;

		bool RegisterWindowClass();

		// ������ģʽ��������
		virtual int SetXml(LPCTSTR lpszXml);
		virtual CIUIString GetXml() const;

		// Create�ӿڽ����ڴ����Ӵ��ڣ����Ҫ����pupop���ڣ���ʹ��CreateEx
		virtual BOOL Create(
			LPCTSTR lpszClassName,
			LPCTSTR lpszWindowName,
			DWORD dwStyle,
			const RECT &rect,
			HWND hwndParent,
			UINT nID,
			LPVOID pContext = NULL
		);

		// CreateEx�ӿڼ����Դ����Ӵ��ڣ�Ҳ���Դ���pupop����
		virtual BOOL CreateEx(
			DWORD dwExStyle,
			LPCTSTR lpszClassName,
			LPCTSTR lpszWindowName,
			DWORD dwStyle,
			int x,
			int y,
			int nWidth,
			int nHeight,
			HWND hWndParent,
			HMENU nIDorHMenu,
			LPVOID lpParam = NULL
		);
		virtual BOOL CreateEx(
			DWORD dwExStyle,
			LPCTSTR lpszClassName,
			LPCTSTR lpszWindowName,
			DWORD dwStyle,
			const RECT &rect,
			Window *pParentWnd,
			UINT nID,
			LPVOID lpParam = NULL
		);

		// ��XML����Ϊģ�壬�����Ӵ���
		BOOL Create(LPCTSTR lpszXMLTemplateName, HWND hParentWnd);
		BOOL CreateChildIndirect(CWindowProp *pWindowPorp, HWND hParentWnd);

		// ��XML����Ϊģ�壬����Popup����
		BOOL CreatePopupWindow(LPCTSTR lpszXMLTemplateName, HWND hParentWnd);
		BOOL CreatePopupIndirect(CWindowProp *pWindowPorp, HWND hParentWnd);

		virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
		virtual void PostNcDestroy();

		WNDPROC *GetSuperWndProcAddr();

		HWND PreModal();
		void PostModal();

		INT_PTR DoModal();
		void EndDialog(int nRetCode);

		int BindStyle(const CWindowProp *pWindowProp);

		BOOL ShowWindow(int nCmdShow);
		UINT ShowModal();
		void Close(UINT nRet = IDOK);
		void SetIcon(UINT nRes);
		void SetResInstance(HINSTANCE hInst);

		LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		void ResizeClient(int cx = -1, int cy = -1);

		int UseLayeredWindow(BOOL bUsed);
		BOOL IsLayeredWindow() const;

		// ������Ҫ���²���
		int NeedRelayoutChildren();
		void Invalidate(BOOL bErase = TRUE);

		// ����
		CONTROL_LAYOUT_HOR SetHorzLayoutMode(CONTROL_LAYOUT_HOR eLayout);
		CONTROL_LAYOUT_HOR GetHorzLayoutMode() const;

		CONTROL_LAYOUT_VER SetVertLayoutMode(CONTROL_LAYOUT_VER eLayout);
		CONTROL_LAYOUT_VER GetVertLayoutMode() const;

		int SetLayoutMargin(LPCRECT lprcMargin);
		int GetLayoutMargin(LPRECT lprcMargin) const;

		int SetLayoutInset(LPCRECT lprcInset);
		int GetLayoutInset(LPRECT lprcInset) const;

		// �õ���һ������
		HWLWND GetChild();

		HWND SetFocus();
		HWLWND GetWLFocus();
		static HWLWND GetWLFocus(HWND hWnd);

		WindowCore *GetPaintManager();

		static Window *FromHandlePermanent(HWND hWnd);
		BOOL Attach(HWND hWndNew);
		HWND Detach();

		// subclassing/unsubclassing functions
		virtual void PreSubclassWindow();

		int AddHandler(CWndHandler *pHandler);
		int RemoveHandler(CWndHandler *pHandler);
		int RemoveAllHanlders();
		int GetHandlerCount() const;

	public:
		HWLWND FindControl(LPCTSTR lpszControlName);
		static BOOL PASCAL WalkPreTranslateTree(HWND hWndStop, MSG *pMsg);
		virtual BOOL PreTranslateMessage(MSG *pMsg);

		// Properties
	public:
		BOOL SetDrawBkColor(BOOL bDraw);
		BOOL IsDrawBkColor() const;
		COLORREF SetBkColor(COLORREF dwColor);
		COLORREF GetBkColor() const;

		int SetBkImage(LPCTSTR lpszImage);
		LPCTSTR GetBkImage() const;

		// ����ͼƬ����ģʽ
		int SetBkImageResizeMode(IMAGE_RESIZE_MODE eImageResizeMode);
		IMAGE_RESIZE_MODE GetBkImageResizeMode() const;

		// ����ͼƬ��9����ʽ����ʱ�����Ų���
		int Set9GridResizeParam(__in LPCRECT lpResize);
		int Get9GridResizeParam(__out LPRECT lpResize);

		bool SetDrawFalseBorderColor(bool bDraw);
		bool IsDrawFalseBorderColor() const;
		DWORD SetFalseBorderColor(DWORD dwColor);
		DWORD GetFalseBorderColor() const;
		int SetTrueBorderThickness(LPCRECT lprcBorder);
		int GetTrueBorderThickness(LPRECT lprcBorder) const;

		int SetTitleBarHeight(int nHeight);
		int GetTitleBarHeight() const;

		int GetClientRect(__out LPRECT lpRect) const;
		int GetWindowRect(__out LPRECT lpRect) const;
		int CenterWindow(HWND hAlternateOwner);
		void CenterWindow();    // ���У�֧����չ��Ļ

		int SetDragResizeFlag(BOOL bDragResize);
		BOOL GetDragResizeFlag() const;

		virtual int SetWindowClassName(LPCTSTR lpszClassName);
		virtual CIUIString GetWindowClassName() const;
		virtual UINT GetClassStyle() const;

		int SetProject(CIUIProject *pProject);
		CIUIProject *GetProject();
		const CIUIProject *GetProject() const;

	protected:
		// OnInitDialog��WM_CREATE�������ǣ�ǰ���Ǵ��ں��ӿؼ������ɹ��󷢳���
		// �����Ǵ����Ѵ��������ӿؼ���δ����ʱ����
		virtual LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnDestroy();
		virtual LRESULT OnNcDestroy();
		virtual int HitTest(CIUIPoint pt, BOOL bSetCursor);
		virtual BOOL IsMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
		// �൱��CWnd::WindowProc
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual int OnDraw(HDC hMemDC, LPCRECT lprcPaint);
		virtual int OnDeforeDraw(HDC hMemDC);
		// ��lprcDest��ΪNULLʱ��Ŀ������ΪlprcDest������Ϊ���ڿͻ���
		virtual int OnDrawBackground(HDC hMemDC, LPCRECT lprcDest);
		virtual int OnDrawBorder(HDC hMemDC);
		virtual int OnDrawControls(HDC hMemDC, LPCRECT lprcPaint);
		virtual int OnAfterDraw(HDC hMemDC);

		virtual int RelayoutChildren();

		// Window message
		virtual LRESULT OnControlEvent(WPARAM wParam, LPARAM lParam);

		int HandleTabKey(MSG *pMsg);

	private:
		LRESULT CallIUIHandlerMap(UINT message, WPARAM wParam, LPARAM lParam);

	public:
		HWND m_hWnd;
		HWND m_hWndOwner;   // implementation of SetOwner and GetOwner

	protected:
		// ���໯����ʱ������ɵĴ��ڹ���
		WNDPROC m_pfnSuper;
		HINSTANCE m_hResInstance; ///��Դ���
		CIUIString m_strClassName;
		UINT m_uIDD;
		WindowCore m_WindowHelper;
		// ���ڴ��ڴ���ǰ��Ч�����������ΪNULL�ˡ�
		CWindowProp *m_pBindWindowProp;

		// ������ؼ��� ģ��TreeView�ؼ���������ڵ㡣 ��������ؼ���Զ������ʾ��
		// ����Ϊ���ؼ��Ĵ��ڣ������벼�֡���Ϣ�����ҵ��
		HWLWND m_hVirtualRoot;

		// ���ڵĽ����ӿؼ��� ֮���Բ��ŵ�_IUI_THREAD_STATE�У�����Ϊÿ�����ڶ����Լ���
		// �����ӿؼ�����һ������ʧȥ����󣬽����ӿؼ�������Ч�ģ��������ٴλ�ý����
		// ��Ҫ��ԭ�ȵĽ����ӿؼ����µõ����㡣
		HWLWND m_hFocus;

		CIUIString m_strXml;
		CIUIRect m_rcXML;	// ��XML�е�ԭʼ����.
		CONTROL_LAYOUT_HOR m_eHAlign; // ���ڸ��ؼ�ˮƽ���뷽ʽ
		CONTROL_LAYOUT_VER m_eVAlign;
		CIUIRect m_rcMargin; // ��߾�
		CIUIRect m_rcInset;	 // �ڱ߾�

		BOOL m_bUseMaskColor;	// �Ƿ�ʹ��͸��ɫ
		BOOL m_bAlpha;			// LWA_ALPHA flag for SetLayeredWindowAttributes
		COLORREF m_crMask;		// ����͸��ɫ
		BYTE m_btAlphaValue;	// ����͸����
		bool m_bDrawBkColor;
		COLORREF m_crBk;
		HIUIIMAGE m_hImageBk;
		IMAGE_RESIZE_MODE m_eImageResizeMode;
		CIUIRect m_rc9GridResizeParam;
		bool m_bDrawBorderColor;
		COLORREF m_crBorderColor;
		CIUIRect m_rcTrueBorder;
		int m_nTitleBarHeight;
		bool m_bCreateAsDialog;
		CWndHandler *m_pWndHandler;

		// Is TRUE if the window can be resized by dragging the board, default to FALSE
		BOOL m_bDragResize;
		BOOL m_bDragResizing; // ��ǰ�Ƿ��������Ź�����
		CIUIPoint m_ptLButtonDown;
		// the result of Hit test the resizing window witch
		// can be resizing by dragging its board. default to HTCLIENT;
		int m_nHitTestRet;
		CIUIRect m_rcLButtonDown;
		CIUIRect m_rcXml;
		CIUISize m_sizeScroll;
		int m_nCXBorder; // see SM_CXBORDER of GetSystemMetrics
		int m_nCYBorder; // see SM_CYBORDER of GetSystemMetrics
		HWND m_hShadowWnd;
	};

	/**
	 @brief ��std::map<std::wstring, std::wstring>��Ƴ�VC�е���Դ�ľ����
	 X��ʾXML��S��ʾString����CParseLanguageFile����
	 map.first���ַ���ID���ڵ��������ַ�����ͬ��ϣ���ʽΪ"����ID/�ַ���ID"
	*/
	typedef std::map<std::wstring, std::wstring> *HXSRESOURCE;

	// for warning C2451
	typedef struct SParseLanguageFileVar
	{
		CIUIString m_strLanguageFile;
		std::map<std::wstring, std::wstring> m_mapControlText; ///< �ؼ�����ؼ�caption��Ӧ��ϵ
	} SParseLanguageFileVar;

	class IUIAPI CParseLanguageFile
	{
	public:
		CParseLanguageFile(CIUIProject *pProject);
		~CParseLanguageFile();

	public:
		int SetLanguageFile(
			LPCTSTR lpszFile,
			__out std::map<std::wstring, std::wstring> *pmapContents);
		int SetLanguageFile(HINSTANCE hRes, LPCTSTR lpszResType, UINT uResID);

		static LPCWSTR LoadXMLString(HXSRESOURCE hMultiLanguageRes, LPCTSTR lpszSectionID, LPCTSTR lpszStringID);

	protected:
		CIUIProject *m_pProject;
	};

	fnWLEventHandler IUIAPI SubclassWindowless(HWLWND hWnd, fnWLEventHandler lpfnNew);
	fnWLEventHandler IUIAPI SuperclassWindowless(LPCTSTR lpszClassName, fnWLEventHandler lpfnNew);
	int IUIAPI AddEventHandler(HWLWND hWnd, CWLWndHandler *pHandler);
	LRESULT IUIAPI WINAPI CallEventHandler(fnWLEventHandler lpPrevEventHandler, HWLWND hWnd, RoutedEventArgs *pe);
	LRESULT IUIAPI DefEventHandler(HWLWND hWnd, RoutedEventArgs *pe);

	//////////////////////////////////////////////////////////////////////////
	// controls

	namespace TimeLine
	{
		enum ANIMATION_TARGET_PROPERTY
		{
			APT_NULL,

			// X/y����ƽ�Ʊ任
			ATP_TRANSLATE_TRANSFORM_X,
			ATP_TRANSLATE_TRANSFORM_Y,
			ATP_TRANSLATE_TRANSFORM_POS,

			// ��ת�任
			ATP_RENDER_TRANSFORM_ANGLE,

			// Ŀ��ؼ���Leftֵ/Topֵ�任
			ATP_LEFT,
			APT_TOP,

			// Ŀ��ؼ����/�߶ȱ任
			ATP_WIDHT,
			ATP_HEIGHT,

			// Ŀ��ؼ�����/ǰ����ɫ�任
			ATP_BK_COLOR,
			ATP_FG_COLOR,
		};

		// ָ�� Timeline �ڲ���������Ϊ��ʽ��
		enum FILL_BEHAVIOR
		{
			FB_HOLDEND,	// �ڴﵽ��ڵ��յ��ʱ���߽���������ȣ�ֱ���丸���Ļ�ںͱ����ڽ���Ϊֹ��
			FB_STOP		// ���ʱ���߳�����ڣ����丸���ڻ���ڣ����ʱ���߽�ֹͣ��
		};

		// ָ���¶���������Ѿ�Ӧ�������Ե��κ����ж������н���
		// ��ο�WPF�е�HandoffBehavior ö��
		enum HANDOFF_BEHAVIOR
		{
			// �¶������滻������Ӧ�õ��������ϵ��κ����ж�����
			// ���磬�����밴ť�󣬴���һ��2��Ķ������ð�ť�������뿪��ť��
			// ����һ��1��Ķ���, �ð�ť�ص�ԭʼ��С�� ������ΪHB_SNAPSHOT_AND_REPLACEʱ��
			// ��������밴ť�������뿪����һ����������ֹͣ����ť����ֹͣ���
			// �ڶ���������ʼ���ð�ť�ص�ԭʼ��С��
			HB_SNAPSHOT_AND_REPLACE,

			// ��ͨ�����¶���׷�ӵ��������ĩβ������¶��������ж�����
			// ���磬�����밴ť�󣬴���һ��2��Ķ������ð�ť�������뿪��ť��
			// ����һ��1��Ķ���, �ð�ť�ص�ԭʼ��С�� ������ΪHB_COMPOSEʱ��
			// ��������밴ť�������뿪���ڶ���������ʼ֮ǰ����ť���������
			HB_COMPOSE
		};

		// �¼�������������ʲô�¼������Դ�������
		enum EVENT_TRIGGER
		{
			ET_BUTTON_CLICK,
			ET_MOUSE_ENTER,
			ET_MOUSE_LEAVE,
			ET_LOADED,
		};

		enum KEY_FRAME
		{
			KF_DISCRETE,	// ��ʾ��һ��ֱ֡����Ծ����֡
			KF_LINEAR,		// ��ʾ��һ��֡���Թ��ȵ���֡
			KF_SPLINE		// ��ʾ��һ��֡���ݱ��������߹��ȵ���֡
		};

		// ��ο�MSDN: WPF�е�PathAnimationSource
		enum PATH_ANIMATION_SOURCE
		{
			// ����Ŀ���ˮƽ/��ֱλ��
			PAS_X,
			PAS_Y,

			// ����Path��б��������ĳ�����ԣ�ͨ������ת�仯��Angle��
			PAS_Angle
		};

		class IUIAPI Animation
		{
			friend LRESULT IUI::DefEventHandler(HWLWND hWnd, RoutedEventArgs *pe);

		protected:
			Animation();
			~Animation();

		public:
			// ���ö���Ӧ�õ��ĸ��ؼ���
			int SetTargetCtrlID(UINT nCtrlID);
			UINT GetTargetCtrlID() const;

			int SetTargetName(LPCTSTR lpszCtrlName);
			LPCTSTR GetTargetName() const;

			int SetTarget(CWLWnd *pTarget);
			CWLWnd *GetTarget();

			int SetTargetWindow(Window *pTarget);
			Window *GetTargetWindow();

			// ���ö���Ӧ�õ��ؼ����ĸ�������(�����ȡ���ɫ��λ�á��Ƕȡ�͸���ȵ�)
			int SetTargetProperty(ANIMATION_TARGET_PROPERTY eAtp);
			ANIMATION_TARGET_PROPERTY GetTargetProperty() const;

			virtual int SetDuration(DWORD dwDuration);
			virtual DWORD GetDuration() const;

			// ָ�� Timeline �ڲ���������Ϊ��ʽ��
			int SetFillBehavior(FILL_BEHAVIOR eFb);
			FILL_BEHAVIOR GetFillBehavior() const;

			// ָ���¶���������Ѿ�Ӧ�������Ե��κ����ж������н���
			// ����ӿڿ��ܲ�Ӧ�ö���������μ���wpf�������ָ�ϡ�p877
			int SetHandoffBehavior(HANDOFF_BEHAVIOR eHb);
			HANDOFF_BEHAVIOR GetHandoffBehavior() const;

			// ���򲥷�����Ƿ��Զ����򲥷�
			int AutoReverse(bool bReverse);
			bool IsAutoReverse() const;

			// ���Ŵ���
			int SetRepeatBehaviorTimes(DWORD nRepeat);
			DWORD GetRepeatBehaviorTimes() const;

			// ����ʱ��
			int SetRepeatBehaviorDuration(DWORD nRepeat);
			DWORD GetRepeatBehaviorDuration() const;

			int SetBeginTime(int nBegin);
			int GetBeginTime() const;

			int SetSpeedRatio(int nRatio);
			int GetSpeedRatio() const;

			int SetCumulative(bool bCumulative);
			bool IsCumulative() const;

			// ���õ�һ֡ʱ���Ѷ���������ʾ������ ���ڿؼ��ڴ���ʱ�����꣬�붯����һ֡�����п���
			// ��ͬ���������Ŷ���ʱ���ؼ���ӳ�ʼλ��ֱ��������һ֡��λ�ã��û����鲻��
			// ���ԣ������ڳ�ʼʱ�����ؿؼ����ڵ�һ֡ʱ����ʾ���ؼ�
			int SetFirstFrameShow(bool bShow);
			bool IsFirstFrameShow() const;

		protected:
			// ����ִ�е��ٽ�㣨������ɡ������������л���ʱ�̣�ʱ�Ĳ���
			int TimerBehaviorStrategy(HTIMER hTimer, DWORD *pdwCurTime, bool *pbEnd);

		protected:
			// ����Ҳ����Ӧ�õ����ڵı���ɫ��͸���ȵ������ϣ�
			// ���ԣ�����Ŀ�꼴������CWLWnd��Ҳ������Window
			CWLWnd *m_pTargetControl;
			Window *m_pTargetWindow;

			ANIMATION_TARGET_PROPERTY m_eAnimationTargetProperty;

			DWORD m_dwDuration;
			FILL_BEHAVIOR m_eFillBehavior;
			HANDOFF_BEHAVIOR m_eHandoffBehavior;

			// ���򲥷�����Ƿ��Զ����򲥷�
			bool m_bAutoReverse;

			// �ظ����ٴΡ� �����Duration����Ϊ2�룬AutoReverse����Ϊtrue����RepeatBehaviorTimes����Ϊ3��
			// ���������������12�롣
			DWORD m_dwRepeatBehaviorTimes;

			// �ظ��೤ʱ��, Ĭ��Ϊ0����ʾ����m_nDurationʱ�����������Ϊ-1����ʾ��Զ����
			// ��Ϊ-1ʱ��m_eFillBehavior��������
			DWORD m_dwRepeatBehaviorDuration;

			// �����������¼��Ͷ�����ʼ֮��ļ������λ���롣 ��ֵΪ��ʱ�������֮��Ķ����Ĳ������κ�Ӱ��
			// ����ֵΪ��1000ʱ��������1��ʱ��״̬��ʼ����(��ʱ������1��)
			int m_nBeginTime;

			// �������ʣ���λ��1%����������Ϊ150ʱ����������150%�����ʼӿ첥��
			int m_nSpeedRatio;

			// ʹ������һ�����ڵ�From��Toֵ�ۻ�������From=12, to=24, RepeatBehaviorTimes=3, AutoReverse=true
			// ��һ�δ�12��24��Ȼ��ص�12���ڶ��δ�24��36��Ȼ��ص�24�������δ�36��48��Ȼ��ص�36.
			bool m_bCumulative;

		protected:
			bool m_bHasSetFrom;
			bool m_bHasSetTo;
			bool m_bFirstFrameShow;
			// ֧�����򲥷ŵĶ�������ǰ�Ƿ��������򲥷��С�
			bool m_bCurReverse;
		};

		// �ؼ�֡������
		class IUIAPI KeyFrame
		{
		protected:
			KeyFrame();
			virtual ~KeyFrame();

		protected:
			KEY_FRAME m_eKeyFrame;

			// �ؼ�֡��ʱ�����λ�ã���λ���롣 ������йؼ�֡��û��ָ��KeyTime��
			// ��һ�����������йؼ�֡��������ͬ��ʱ�䳤�ȣ�������Duration�ᱻ���ƽ̯��
			// ���Ҳû��ָ��������Duration����Ĭ��Ϊ1�롣
			// KeyTime�����Ա����óɰٷֱȣ���λ1%��
			bool m_bHasSetKeyTime;
			bool m_bKeyTimeIsTime;	// ָʾKeyTime��ʱ�仹�ǰٷֱ�
			DWORD m_dwKeyTime;

			bool m_bHasSetValue;

			// �������������߿��ƵĹؼ�֡ʹ��
			POINT m_ptKeySpline1;
			POINT m_ptKeySpline2;
		};

		// �ؼ�֡��
		class IUIAPI DataKeyFrame : public KeyFrame
		{
		public:
			DataKeyFrame();
			virtual ~DataKeyFrame();

			int m_nValue;
		};

		// ����ʱ���ߣ�������������������ִ�С� �����԰�������Ӷ���
		class IUIAPI ParallelTimeLine : public Animation
		{
		public:
			ParallelTimeLine();
			virtual ~ParallelTimeLine();

		public:

		protected:
			std::vector<Animation *> *m_pvpAnimation;
		};

		// ���°壬��0�������������, �������Ϊ��Ƶ���������ʱ����
		class IUIAPI Storyboard
		{
		public:
			// ��Ϊ���ڵı�����ɫ��͸���ȵ����ԣ�Ҳ���ܻ�ִ�ж�����
			// ���ԣ�������Window *��������CWLWnd *
			Storyboard(Window *pParent);
			virtual ~Storyboard();

		public:
			int Begin();
			int Pause();
			int Resume();
			int Stop();
			int SkipToFill();
			int Seek(DWORD dwOffset);

			// ���Ӷ�������Ǹ�Ϊһ���������ڣ�����AutoReverse��BeginTime�������
			// �����������Ӷ�������һ��DurationΪ2�룬AutoReverseΪTrue��
			// �ڶ���DurationΪ3�룬���ܶ���ʱ��Ϊ4�롣 �������ڶ���3��ģ���ֻ��ÿ��4��Ŀ�ʼ����

			// ���Ŵ���
			int SetRepeatBehaviorTimes(DWORD nRepeat);
			DWORD GetRepeatBehaviorTimes() const;

			// ����ʱ��
			int SetRepeatBehaviorDuration(DWORD nRepeat);
			DWORD GetRepeatBehaviorDuration() const;

			//  ָ���ڽ�ʱ�����Ŵ�����ٵ���������ʹ�������ռ��ʱ���ߵ� Duration �İٷֱȣ�
			// ��λ1%��ȡֵ��Χ0-100
			// �ο�MSDN: Timeline..::.AccelerationRatio ����
			// ���磺�������Ϊ25����ʾ�ö�����Duration��������ġ�25%����ʱ�䡿��᡾���١����������
			// DecelerationRatio��ʾ��ָ����Duration�ġ�����ж��١��������ġ�ʱ�䡿�����١���
			int SetAccelerationRatio(int nRatio);
			int GetAccelerationRatio() const;

			int SetDecelerationRatio(int nRatio);
			int GetDecelerationRatio() const;

			int AddAnimation(Animation *pA);

		protected:
			Window *m_pParentWnd;

			DWORD m_dwRepeatTimes;
			DWORD m_dwRepeatDuration;
			int m_nAccelerationRatio;
			int m_nDecelerationRatio;

			std::vector<Animation *> *m_pvpAnimation;
		};

		// �����ֵ����int��COLORREF��POINT��͸���ȣ����еĶ�����
		class IUIAPI DataAnimation : public Animation
		{
		public:
			DataAnimation();
			virtual ~DataAnimation();

		public:
			// �����ָ��Fromֵ����Ӷ����󶨵Ŀؼ��ĵ�ǰֵ��ʼ
			int SetFrom(Gdiplus::REAL nFrom);
			Gdiplus::REAL GetFrom() const;

			// �����ָ��Toֵ����Ӷ����󶨵Ŀؼ��ĵ�ǰֵ����
			int SetTo(Gdiplus::REAL nTo);
			Gdiplus::REAL GetTo() const;

		private:
			Gdiplus::REAL m_nFrom;
			Gdiplus::REAL m_nTo;
		};

		// ʹ�ùؼ�֡����ָ������ֵ
		class IUIAPI DataAnimationUsingKeyFrames : public Animation
		{
		public:
			DataAnimationUsingKeyFrames();
			~DataAnimationUsingKeyFrames();

		protected:
			std::vector<DataKeyFrame *> *m_pvpKeyFrames;
		};

		// ��ָ��·������ָ������ֵ
		class IUIAPI DataAnimationUsingPath : public Animation
		{
		public:
			DataAnimationUsingPath();
			virtual ~DataAnimationUsingPath();

		public:
			// 			// ��ο�MSDN: DoubleAnimationUsingPath::Source
			// 			int SetSource(PATH_ANIMATION_SOURCE eSource);
			// 			PATH_ANIMATION_SOURCE GetSource() const;

			virtual int SetDuration(DWORD dwDuration);
			virtual DWORD GetDuration() const;

			int AddPath(Gdiplus::GraphicsPath *pPath);
			int AddArcPath(Gdiplus::GraphicsPath *pPath,
				Gdiplus::REAL x, Gdiplus::REAL y, Gdiplus::REAL width, Gdiplus::REAL height,
				Gdiplus::REAL startAngle, Gdiplus::REAL sweepAngle);

			int SetTargetValue(int nTarget);
			int GetTargetValue() const;

			int GetPoint(DWORD t, __out Render::CFlattenPathPoint *pPoint);

		protected:
			// ����·������ͼ��
			Render::CFlattenAnimationPath m_FlattenPath;

			// ����Ŀ��ֵ����Ŀ��ؼ��ϵ��ĸ�ֵ����·�����ƶ�
			// ���磺m_nTargetͨ������ǿת������ΪĿ��ؼ��ϵ����Ͻ�POINTֵ
			// ��Ŀ��ؼ������Ͻǣ���ָ����·���ƶ���
			int m_nTarget;

			PATH_ANIMATION_SOURCE m_ePathAnimationSource;
		};

		class IUIAPI RectAnimation : public Animation
		{
		public:
			RectAnimation();
			virtual ~RectAnimation();

		public:
			// �����ָ��Fromֵ����Ӷ����󶨵Ŀؼ��ĵ�ǰֵ��ʼ
			int SetFrom(LPCRECT lprcFrom);
			int GetFrom(LPRECT lprcFrom) const;

			// �����ָ��Toֵ����Ӷ����󶨵Ŀؼ��ĵ�ǰֵ����
			int SetTo(LPCRECT lprcTo);
			int GetTo(LPRECT lprcTo) const;

		private:
			CIUIRect m_rcFrom;
			CIUIRect m_rcTo;
		};

		// ��ָ��·������ָ���ľ���ƽ�ơ����š���ת�ȣ�
		// ��һ����ť��һ��·��һ���ƶ���һ������ʱ����ʹ�ñ�����
		class IUIAPI MatrixAnimationUsingPath : public Animation
		{
		};

	} // TimeLine

	typedef class ScrollBar *HSCROLLBAR;

	// CWLWndֻ��ʹ����ɫ��Ⱦ������֧��ͼƬ��Ⱦ
	class IUIAPI CWLWnd
	{
		friend class WindowCore;
		friend class Window;
		friend CWLWnd *GetWindow(CWLWnd *pWnd, UINT uCmd);
		friend LRESULT DefEventHandler(HWLWND, RoutedEventArgs *);
		friend LRESULT WINAPI CWLWnd_EventHandler(HWLWND, RoutedEventArgs *);
		friend LRESULT WINAPI IUIHookWLCreate(HWLWND, RoutedEventArgs *);

	public:
		CWLWnd();
		virtual ~CWLWnd();

		virtual int SetXml(LPCTSTR lpszXml);
		virtual LPCTSTR GetXml() const;

		// As mfc CWnd::Create and CWnd::CreateEx
		virtual BOOL Create(
			CWLWndHandler *pUserHandler,
			LPCTSTR lpszClassName,
			LPCTSTR lpszCaption,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParent,
			LPCTSTR lpszName,
			LPVOID lpParam = NULL);
		virtual BOOL CreateEx(
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
			CWLWnd *pParent,
			LPCTSTR lpszName,
			LPVOID lpParam = NULL);
		virtual BOOL CreateEx(
			CWLWndHandler *pUserHandler,
			DWORD dwExStyle,
			LPCTSTR lpszClassName,
			LPCTSTR lpszCaption,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParent,
			LPCTSTR lpszName,
			LPVOID lpParam = NULL);

		// ����RECT����
		virtual BOOL Create(
			CWLWndHandler *pUserHandler,
			LPCTSTR lpszCaption,
			DWORD dwStyle,
			HWND hParent,
			CWLWnd *pParent,
			LPCTSTR lpszName,
			LPVOID lpParam = NULL
		);
		// ��XMLֱ�Ӵ����ɿؼ���XML�а���Create�����е�����������
		virtual BOOL Create(
			CWLWndHandler *pUserHandler,
			LPCTSTR lpszXmlName,
			HWND hParent,
			CWLWnd *pParent
		);
		// �ɿؼ�����ֱ�Ӵ����ɿؼ����ؼ������а���Create�����е�����������
		virtual BOOL CreateIndirect(
			CWLWndHandler *pUserHandler,
			CControlProp *pCtrlProp,
			HWND hParent,
			CWLWnd *pParent
		);

		static CWLWnd *FromHandle(HWLWND hWnd);

		BOOL Attach(HWLWND hWndNew);
		HWLWND Detach();
		HWLWND GetSafeHwnd();

		virtual BOOL DestroyWindow();

		virtual int BindStyle(const CControlProp *pCtrlProp);

		BOOL IsWindow() const;
		virtual CWLWnd *SetParent(CWLWnd *pNewParent);
		virtual CWLWnd *GetParent() const;
		// ����ZOrder�����Լ����뵽pAfter֮�����pAfterΪNULL����������λ
		virtual int SetZOrder(CWLWnd *pAfter);

	protected:
		virtual LRESULT DefEventHandler(RoutedEventArgs *pe);
		virtual LRESULT EventHandler(RoutedEventArgs *pe);
		virtual LRESULT OnCreate(RoutedEventArgs *pe);
		virtual LRESULT OnSize(RoutedEventArgs *pe);
		virtual LRESULT OnWindowPosChanged(RoutedEventArgs *pe);

		LRESULT CallIUIHandlerMap(RoutedEventArgs *pe);

	public:
		virtual CIUIString SetName(LPCTSTR pstrName);
		virtual CIUIString GetName() const;
		virtual CIUIString GetClassName() const;

		virtual int SetDlgCtrlID(int nID);
		virtual int GetDlgCtrlID() const;

		// ���ú������Ƿ񷢳�֪ͨ
		int SetNotify(BOOL bNotify);
		BOOL IsNotify() const;

		virtual LONG SetStyle(LONG lStyle);
		virtual LONG GetStyle() const;
		virtual LONG AddStyle(LONG lAdd);
		virtual LONG RemoveStyle(LONG lRemove);

		virtual LONG SetExStyle(LONG lExStyle);
		virtual LONG GetExStyle() const;
		virtual LONG AddExStyle(LONG lAdd);
		virtual LONG RemoveExStyle(LONG lRemove);

		virtual HWND GetHostWnd() const;

		virtual HWND GetNativeWindow() const;

		virtual CIUIProject *GetProject();
		virtual const CIUIProject *GetProject() const;

		//
		HWLWND SetCapture();

		CWLWnd *GetTopLevelWindow();

		// �ı����
		virtual CIUIString GetWindowText() const;
		virtual void SetWindowText(LPCTSTR pstrText);
		virtual void SetResText(HINSTANCE hRes, UINT uID);
		int SetTextPadding(RECT rc);
		RECT GetTextPadding() const;

		// �ı���ɫ
		int SetTextColor(COLORREF crN, COLORREF crD);
		int GetTextColor(COLORREF *pcrN, COLORREF *pcrD) const;

#if (_MSC_VER > 1200)	// VC6.0
		/**
		 @brief ���ÿؼ��ı�
		 @details
		 <pre>
		 ͨ������XML�ַ�����Դ���ַ������ڵ�Section�����ַ���ID����ѯ��Ӧ���ַ�����Ȼ�����ø��ؼ���
		 </pre>
		 @author (Liusw)
		 @param[in] hXRes: �ַ�����Դ�����ͨ��CParseLanguageFile�����õ�
		 @param[in] uSectionID: �ַ������ڵ�Section
		 @param[in] uStringID: �ַ���ID
		 @param[out]
		 @return
		  - 0  �ɹ�
		  - -1 ʧ��
		*/
		virtual void SetXResText(HXSRESOURCE hXRes, LPCTSTR lpszSectionID, LPCTSTR lpszStringID);
#endif // #if (_MSC_VER > 1200)	// VC6.0

		void SetRedraw(BOOL bRedraw = true);
		BOOL IsRedraw();

		int SetClip(BOOL bClip);
		BOOL IsClip() const;

		// ����
		BOOL SetDrawBkColor(BOOL bDraw);
		BOOL IsDrawBkColor() const;

		int SetBkColor(COLORREF crBkN, COLORREF crBkD);
		int GetBkColor(COLORREF *pcrBkN, COLORREF *pcrBkD) const;

		BOOL CombineBkImage(BOOL bCombine);
		BOOL IsCombineBkImage() const;
		int SetCombineBkImage(LPCTSTR lpszImage);
		int GetCombineBkImage(CIUIString *pstrCombineImage) const;

		int SetBkImageResizeMode(IMAGE_RESIZE_MODE eImageResizeMode);
		IMAGE_RESIZE_MODE GetBkImageResizeMode() const;
		int SetBkImage9GridResizeParam(LPCRECT lprcParam);
		int GetBkImage9GirdResizeParam(LPRECT lprcParam) const;

		SIZE GetBorderRound() const;
		void SetBorderRound(SIZE cxyRound);

		//�߿����
		BOOL SetDrawBorderColor(BOOL bDraw);
		BOOL IsDrawBorderColor() const;

		int SetBorderColor(COLORREF crN, COLORREF crD);
		int GetBorderColor(COLORREF *pcrN, COLORREF *pcrD) const;

		DWORD GetFocusBorderColor() const;
		void SetFocusBorderColor(DWORD dwBorderColor);

		int SetBorderRect(const RECT &rcBorder);
		CIUIRect GetBorderRect() const;

		// λ�����
		// �ڲ�����HRGN�Ŀ����������û�Ҫע��������������
		// �ᷢ��WM_WINDOWPOSCHANGING and WM_WINDOWPOSCHANGED ð���¼�
		virtual int SetWindowRgn(HRGN hRgn, BOOL bRedraw);
		virtual int GetWindowRgn(HRGN hRgn) const;
		virtual int RelayoutChild();
		virtual void EnableDPI(BOOL bEnable);
		virtual BOOL IsDPIEnabled() const;
		virtual void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);
		virtual void MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE);
		virtual BOOL SetWindowPos(HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
		virtual int GetClientRect(LPRECT lpRect) const;
		virtual int GetWindowRect(LPRECT lpRect) const; // �������Ļ
		virtual int GetWindowRectToHWND(LPRECT lpRect) const; // �������������
		virtual int GetWindowRectToParent(LPRECT lprc) const;
		virtual const CIUIRect &GetWindowRectToParent() const;
		virtual int GetWindowRectFToParent(Gdiplus::RectF *pRect) const;
		virtual int ClientToScreen(LPRECT lpRect);
		virtual int ClientToScreen(LPPOINT lpPt);
		virtual int ScreenToClient(LPRECT lpRect);
		virtual int ScreenToClient(LPPOINT lpPt);
		virtual int GetFixedWidth() const;       // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
		virtual void SetFixedWidth(int cx);      // Ԥ��Ĳο�ֵ
		virtual BOOL IsFixedWidth() const;
		virtual BOOL IsFixedHeight() const;
		virtual void ClearFixedWidth();
		virtual void ClearFixedHeight();
		virtual int GetFixedHeight() const;      // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
		virtual void SetFixedHeight(int cy);     // Ԥ��Ĳο�ֵ
		virtual int GetMinWidth() const;
		virtual void SetMinWidth(int cx);
		virtual int GetMaxWidth() const;
		virtual void SetMaxWidth(int cx);
		virtual int GetMinHeight() const;
		virtual void SetMinHeight(int cy);
		virtual int GetMaxHeight() const;
		virtual void SetMaxHeight(int cy);
		virtual int SetTitleBarHeight(int nHeight);
		virtual int GetTitleBarHeight() const;
		virtual int SetBorderThickness(LPCRECT lprcBorder);
		virtual int GetBorderThickness(LPRECT lprcBorder) const;

		// ����/�õ��ؼ��ڽ��������ļ��е�ԭʼ����
		int SetControlMargin(LPCRECT lprc);
		int GetControlMargin(LPRECT lprc) const;

		virtual UINT SetResizeFlag(UINT uFlag);
		virtual UINT GetResizeFlag() const;
		virtual int HitTest(LPPOINT lpPt);
		virtual CWLWnd *HitTestChild(LPPOINT lpPt);
		// ����������׼��ͨ������϶�������ʱ������ӿؼ������в��ԣ������Ե����ؼ�ʱ
		// �����������ڣ����ؼ��Ƿ���괩͸����괩͸�Ŀؼ�����������в��ԡ�
		virtual BOOL SetMouseTransparent(BOOL bMouseTransparent);
		virtual BOOL IsMouseTransparent() const;

		CONTROL_LAYOUT_HOR SetHorzLayoutMode(CONTROL_LAYOUT_HOR eLayout);
		CONTROL_LAYOUT_HOR GetHorzLayoutMode() const;

		CONTROL_LAYOUT_VER SetVertLayoutMode(CONTROL_LAYOUT_VER eLayout);
		CONTROL_LAYOUT_VER GetVertLayoutMode() const;

		DOCK SetDockProperty(DOCK eDock);
		DOCK GetDockProperty() const;

		int SetLayoutMargin(LPCRECT lprcMargin);
		int GetLayoutMargin(LPRECT lprcMargin) const;

		int SetLayoutInset(LPCRECT lprcInset);
		int GetLayoutInset(LPRECT lprcInset) const;

		// �����ʾ
		virtual CIUIString GetToolTip() const;
		virtual void SetToolTip(LPCTSTR pstrText);
		virtual void SetResToolTip(HINSTANCE hRes, UINT uID);
#if (_MSC_VER > 1200)	// VC6.0
		virtual void SetXResToolTip(HXSRESOURCE hXRes, LPCTSTR lpszSectionID, LPCTSTR lpszStringID);
#endif // #if (_MSC_VER > 1200)	// VC6.0
		virtual void SetToolTipWidth(int nWidth);
		virtual int GetToolTipWidth(void);    // ����ToolTip��������

		// �û�����
		virtual LPARAM GetUserData(); // �������������û�ʹ��
		virtual void SetUserData(LPARAM lParam); // �������������û�ʹ��
		virtual LPCTSTR GetTag() const; // �������������û�ʹ��
		virtual void SetTag(LPCTSTR lpszTag); // �������������û�ʹ��
		virtual UINT SetState(UINT uState);
		virtual UINT GetState() const;
		virtual UINT AddState(UINT uState);
		virtual UINT RemoveState(UINT uState);

		// һЩ��Ҫ������
		virtual BOOL IsWindowVisible() const;
		virtual BOOL ShowWindow(int nCmdShow);
		virtual BOOL IsWindowEnabled() const;
		// return value: Nonzero indicates that the window was previously disabled.
		// Zero indicates that the window was not previously disabled
		virtual BOOL EnableWindow(BOOL bEnable = true);
		virtual BOOL IsFocused() const;
		virtual void SetFocus();

		int SetControlState(CONTROL_STATE eNewState);
		CONTROL_STATE GetControlState() const;

		virtual CWLWnd *FindControl(LPCTSTR lpszName);
		BOOL Invalidate();
		BOOL InvalidateRect(LPCRECT lpRect);

		UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT uElapse, WLTIMERPROC lpTimerFunc);
		BOOL KillTimer(UINT_PTR nIDEvent);
		BOOL IsTimerExist(UINT_PTR nIDEvent);

		virtual SIZE EstimateSize(SIZE szAvailable);

		// �������Paint�����԰�CWLWnd�����ݣ���ӡ��ָ��DC�ϡ�
		virtual int Paint(HDC hDC, const RECT &rcPaint);

		virtual int BeginAnimation(TimeLine::ANIMATION_TARGET_PROPERTY eTarget, TimeLine::Animation *pAnimation);

	public:
		LRESULT SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) const;

		// �����¼�����ο�MSDN: UIElement::RaiseEvent
		LRESULT RaiseEvent(RoutedEventArgs *pe);

		// �������
		virtual void EnableScrollBar(BOOL bEnableVertical = TRUE, BOOL bEnableHorizontal = FALSE);
		virtual void EnableFloatScrollBar(BOOL bFloatVBar, BOOL bFloatHBar);
		virtual HWLWND GetVerticalScrollBar() const;
		virtual HWLWND GetHorizontalScrollBar() const;
		virtual BOOL IsFloatVBar() const;
		virtual BOOL IsFloatHBar() const;
		virtual int SetScrollRange(int nBar, int nMinPos, int nMaxPos, BOOL bRedraw = TRUE);
		virtual int GetScrollRange(int nBar, int *pnMinPos, int *pnMaxPos);
		int SetScrollPos(int nBar, int nPos, BOOL bRedraw = TRUE);
		int GetScrollPos(int nBar) const;

		// ֻ���ⲿ����SetScrollInfoΪCWLWnd�����˹�����Ϣ��CWLWnd�Ĺ���λ�òŻ�ı�
		// ֻ�϶�CWLWnd�Ĺ��������飬�ͷ����󣬻��黹��ص�ԭ����λ�á�
		virtual BOOL SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE);
		virtual BOOL GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
		virtual void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
		virtual int SetHScrollBarHeight(int nHeight);
		virtual int GetHScrollBarHeight() const;
		virtual int SetVScrollBarWidth(int nWidth);
		virtual int GetVScrollBarWidth() const;

		void SetMember(void *pMember);
		void *GetMember() const;

	public:
		HWLWND m_hWnd;

	protected:
		fnWLEventHandler m_pfnSuper;	// �ؼ�ԭʼ���ڹ���
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	typedef BOOL (WINAPI *LPALPHABLEND)(HDC, int, int, int, int, HDC, int, int, int, int,
		BLENDFUNCTION);

	/**
	@brief
	X��ʾXML����CParseResourceFile����
	map.firstΪ�ַ���ID��map.secondΪID��ֵ
	*/
	typedef std::map<std::string, UINT> *HXRESOURCE;

	// for warning C2451
	typedef struct SParseResourceFileVar
	{
		CIUIString m_strResourceFile;
		std::map<std::string, UINT> m_mapIDs; ///< �ؼ�ID������ֵ��Ӧ��ϵ
	} SParseResourceFileVar;

	class IUIAPI CParseResourceFile
	{
	public:
		CParseResourceFile();
		~CParseResourceFile();

	public:
		int SetResourceFile(LPCTSTR lpszFile);
		int SetResourceFile(HINSTANCE hRes, LPCTSTR lpszResType, UINT uResID);
		LPCTSTR GetResourceFile() const;

		HXRESOURCE GetResourceHandle();

		/**
		@brief �õ�ID���Ӧ����ֵ
		@details
		<pre>
		</pre>
		@author (Liusw)
		@param[in] hResource: ID��Դ�����ͨ��CParseResourceFile�����õ�
		@param[in] lpszID: �ؼ�ID���ַ���
		@return
		- > 0: ���������ַ���
		- <= 0: ʧ��
		*/
		static UINT GetID(HXRESOURCE hResource, LPCTSTR lpszID);

	protected:
		SParseResourceFileVar m_varMember;
	};

	class IUIAPI CChildInfo
	{
	public:
		CChildInfo()
		{
			m_pChildCtrl = NULL;
			memset(&m_rcOriginal, 0, sizeof(RECT));
			m_eControlType = CT_ARROW;
			m_pCtrlProperties = NULL;
		}

	public:
		CWLWnd *m_pChildCtrl;
		CIUIRect m_rcOriginal;
		CONTROL_TYPE m_eControlType;
		const class CControlProp *m_pCtrlProperties;
	};

	class IUIAPI Gdiplus::RectF;
	struct IUIAPI Gdiplus::GdiplusStartupInput;

	// ��CWLWnd�����ϣ����ϱ���ͼƬ֧�֡� ��������ʾhtml�ı�
	class IUIAPI Label : public CWLWnd
	{
	public:
		Label();
		~Label();

		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			LPCTSTR lpszCaption,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParent,
			LPCTSTR lpszName
		);

		virtual int BindStyle(const CControlProp *pCtrlProp);

	public:
		// �ı����룬���������ο�MSDN: DrawText���һ������
		UINT SetTextStyle(UINT uStyle);
		UINT GetTextStyle() const;
		UINT AddTextStyle(UINT uAddStyle);
		UINT RemoveTextStyle(UINT uRomoveStyle);

		// ����
		int SetTextFont(UINT uMask,	LPCTSTR lpszFontIDN, LPCTSTR lpszFontIDD, BOOL bRedraw);
		int GetTextFont(UINT uMask,	CIUIString *pstrFontIDN, CIUIString *pstrFontIDD) const;

		// �ı���ؼ����
		int SetTextMargin(
			UINT uMask,
			LPCRECT lprcTextMarginN,
			LPCRECT lprcTextMarginD,
			BOOL bRedraw);
		int GetTextMargin(
			UINT uMask,
			LPRECT lprcTextMarginN,
			LPRECT lprcTextMarginD) const;

		// �ı�����ģʽ
		int SetTextAlignHor(
			UINT uMask,
			TEXT_ALIGN_HOR eHorAlignModeN,
			TEXT_ALIGN_HOR eHorAlignModeD,
			BOOL bRedraw);
		int GetTextAlignHor(
			UINT uMask,
			TEXT_ALIGN_HOR *peHorAlignModeN,
			TEXT_ALIGN_HOR *peHorAlignModeD) const;
		int SetTextAlignVer(
			UINT uMask,
			TEXT_ALIGN_VER eVerAlignModeN,
			TEXT_ALIGN_VER eVerAlignModeD,
			BOOL bRedraw);
		int GetTextAlignVer(
			UINT uMask,
			TEXT_ALIGN_VER *peVerAlignModeN,
			TEXT_ALIGN_VER *peVerAlignModeD) const;

		// ���ÿ���ƥ���ı��Ŀ��ߣ��ı��߾�Կ����Ӱ�죬���ؾɵ�ֵ
		BOOL SetWidthMatchText(BOOL bMatch);
		BOOL IsWidthMatchText() const;

		BOOL SetHeightMatchText(BOOL bMatch);
		BOOL IsHeightMatchText() const;

		// ����
		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameD) const;

		int SetButtonClickArg(LPCTSTR lpszArg);
		CIUIString GetButtonClickArg() const;

		virtual SIZE EstimateSize(SIZE szAvailable);
		// ʹ�ÿؼ������壬�ⶨ���������ַ����ĳߴ�
		virtual SIZE EstimateTextSize(LPCTSTR lpszText);
	};

	class IUIAPI Button : public CWLWnd
	{
	public:
		Button();
		virtual ~Button();

		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			LPCTSTR lpszCaption,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParent,
			LPCTSTR lpszName
		);

		virtual int BindStyle(const CControlProp *pCtrlProp);

	public:
		int SetButtonClickArg(LPCTSTR lpszArg);
		CIUIString GetButtonClickArg() const;

		// ����
		int SetBkColor(COLORREF crBkN, COLORREF crBkH, COLORREF crBkS, COLORREF crBkD);
		int GetBkColor(COLORREF *pcrBkN, COLORREF *pcrBkH, COLORREF *pcrBkS, COLORREF *pcrBkD) const;
		int SetCheckedBkColor(COLORREF crCN, COLORREF crCH, COLORREF crCS, COLORREF crCD);
		int GetCheckedBkColor(COLORREF *pcrCN, COLORREF *pcrCH, COLORREF *pcrCS, COLORREF *pcrCD) const;

		// TODO: SetXXX����ӿڵ�bRedraw����ȥ����Ĭ�϶���Redraw��
		// �����SetXXX֮��Redraw��ʹ��IUI::SetRedraw������
		// ������Windows����
		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameS,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameS,
			CIUIString *pstrImageNameD) const;
		int SetCheckedBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameCN,
			LPCTSTR lpszImageNameCH,
			LPCTSTR lpszImageNameCP,
			LPCTSTR lpszImageNameCD,
			BOOL bRedraw);
		int GetCheckedBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameCN,
			CIUIString *pstrImageNameCH,
			CIUIString *pstrImageNameCP,
			CIUIString *pstrImageNameCD) const;

		int SetFocusedBkImage(LPCTSTR lpszImage);
		LPCTSTR GetFocusedBkImage() const;

		// ǰ��
		BOOL CombineFgImage(BOOL bCombine);
		BOOL IsCombineFgImage() const;

		int SetCombineFgImage(LPCTSTR lpszImage);
		LPCTSTR GetCombineFgImage() const;

		int SetFgImage(
			UINT uMask,
			LPCTSTR lpszImageNameForegroundN,
			LPCTSTR lpszImageNameForegroundH,
			LPCTSTR lpszImageNameForegroundS,
			LPCTSTR lpszImageNameForegroundD,
			BOOL bRedraw);
		int GetFgImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameForegroundN,
			CIUIString *pstrImageNameForegroundH,
			CIUIString *pstrImageNameForegroundS,
			CIUIString *pstrImageNameForegroundD) const;
		int SetCheckedFgImage(
			UINT uMask,
			LPCTSTR lpszImageNameCN,
			LPCTSTR lpszImageNameCH,
			LPCTSTR lpszImageNameCP,
			LPCTSTR lpszImageNameCD,
			BOOL bRedraw);
		int GetCheckedFgImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameCN,
			CIUIString *pstrImageNameCH,
			CIUIString *pstrImageNameCP,
			CIUIString *pstrImageNameCD) const;

		int SetFgImageMargin(LPCRECT lprcMargin);
		int GetFgImageMargin(LPRECT lprcMargin) const;

		FOREGROUND_ALIGN_HOR SetFgImageAlignHor(FOREGROUND_ALIGN_HOR eAlign);
		FOREGROUND_ALIGN_HOR GetFgImageAlignHor() const;
		FOREGROUND_ALIGN_VER SetFgImageAlignVer(FOREGROUND_ALIGN_VER eAlign);
		FOREGROUND_ALIGN_VER GetFgImageAlignVer() const;

		// �߿�
		int SetBorderColor(
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD,
			BOOL bRedraw);
		int GetBorderColor(
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD) const;
		int SetCheckedBorderColor(COLORREF crCN, COLORREF crCH, COLORREF crCS, COLORREF crCD);
		int GetCheckedBorderColor(COLORREF *pcrCN, COLORREF *pcrCH, COLORREF *pcrCS, COLORREF *pcrCD) const;

		// �ı�
		int SetTextColor(
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD,
			BOOL bRedraw);
		int GetTextColor(
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD) const;
		int SetCheckedTextColor(
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD,
			BOOL bRedraw);
		int GetCheckedTextColor(
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD) const;

		int SetFocusedTextColor(COLORREF cr);
		COLORREF GetFocusedTextColor() const;

		int SetTextFont(
			UINT uMask,
			LPCTSTR lpszFontIDN,
			LPCTSTR lpszFontIDH,
			LPCTSTR lpszFontIDS,
			LPCTSTR lpszFontIDD,
			BOOL bRedraw);
		int GetTextFont(
			UINT uMask,
			CIUIString *pstrFontIDN,
			CIUIString *pstrFontIDH,
			CIUIString *pstrFontIDS,
			CIUIString *pstrFontIDD) const;
		int SetCheckedTextFont(
			UINT uMask,
			LPCTSTR lpszFontIDCN,
			LPCTSTR lpszFontIDCH,
			LPCTSTR lpszFontIDCS,
			LPCTSTR lpszFontIDCD,
			BOOL bRedraw);
		int GetCheckedTextFont(
			UINT uMask,
			CIUIString *pstrFontIDCN,
			CIUIString *pstrFontIDCH,
			CIUIString *pstrFontIDCS,
			CIUIString *pstrFontIDCD) const;

		// �ı���ؼ����
		int SetTextMargin(
			UINT uMask,
			LPCRECT lprcTextMarginN,
			LPCRECT lprcTextMarginH,
			LPCRECT lprcTextMarginS,
			LPCRECT lprcTextMarginD,
			BOOL bRedraw);
		int GetTextMargin(
			UINT uMask,
			LPRECT lprcTextMarginN,
			LPRECT lprcTextMarginH,
			LPRECT lprcTextMarginS,
			LPRECT lprcTextMarginD) const;

		// �ı�����ģʽ
		int SetTextAlignHor(
			UINT uMask,
			TEXT_ALIGN_HOR eHorAlignModeN,
			TEXT_ALIGN_HOR eHorAlignModeH,
			TEXT_ALIGN_HOR eHorAlignModeS,
			TEXT_ALIGN_HOR eHorAlignModeD,
			BOOL bRedraw);
		int GetTextAlignHor(
			UINT uMask,
			TEXT_ALIGN_HOR *peHorAlignModeN,
			TEXT_ALIGN_HOR *peHorAlignModeH,
			TEXT_ALIGN_HOR *peHorAlignModeS,
			TEXT_ALIGN_HOR *peHorAlignModeD) const;
		int SetTextAlignVer(
			UINT uMask,
			TEXT_ALIGN_VER eVerAlignModeN,
			TEXT_ALIGN_VER eVerAlignModeH,
			TEXT_ALIGN_VER eVerAlignModeS,
			TEXT_ALIGN_VER eVerAlignModeD,
			BOOL bRedraw);
		int GetTextAlignVer(
			UINT uMask,
			TEXT_ALIGN_VER *peVerAlignModeN,
			TEXT_ALIGN_VER *peVerAlignModeH,
			TEXT_ALIGN_VER *peVerAlignModeS,
			TEXT_ALIGN_VER *peVerAlignModeD) const;

		int SetCheck(int nCheck);
		int GetCheck() const;

		int SetBindModalDlgID(UINT uID);
		UINT GetBindModalDlgID() const;

		int SetBindModelessWndID(UINT uID);
		UINT GetBindModelessWndID() const;

		int SetBindTabControl(LPCTSTR lpszTabControlName);
		LPCTSTR GetBindTabControl() const;

		int SetBindPropertySheet(LPCTSTR lpszTabControlName);
		LPCTSTR GetBindPropertySheet() const;

		int SetButtonType(int nButtonType);
		int GetButtonType() const;
	};

	class IUIAPI RepeatButton : public Button
	{
	public:
		RepeatButton();
		virtual ~RepeatButton();

		virtual BOOL Create(
			CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParent,
			LPCTSTR lpszName
		);

		virtual int BindStyle(const CControlProp *pCtrlProp);
	};

	class IUIAPI ScrollBar : public CWLWnd
	{
	public:
		ScrollBar();
		virtual ~ScrollBar();

		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParentWnd,
			CWLWnd *pParent,
			LPCTSTR lpszName
		);

		// Attributes
		int GetScrollPos() const;
		int SetScrollPos(int nPos, BOOL bRedraw = TRUE);
		int GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const;
		int SetScrollRange(int nMinPos, int nMaxPos, BOOL bRedraw = TRUE);
		void ShowScrollBar(BOOL bShow = TRUE);

		BOOL EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH);

		BOOL SetScrollInfo(LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE);
		BOOL GetScrollInfo(LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
		int GetScrollLimit();
		BOOL GetScrollBarInfo(PSCROLLBARINFO pScrollInfo) const;
	};

	/////////////////////////////////////////////////////////////
	// HostWnd: ����Win32�Ӵ���
	class IUIAPI HostWnd : public CWLWnd
	{
	public:
		HostWnd();
		virtual ~HostWnd();

	public:
		HWND GetHWND() const;
		int SetHWND(HWND hWnd);

	protected:
		virtual LRESULT EventHandler(RoutedEventArgs *pe);

	protected:
		HWND m_hHost;
	};

	// C++����JS�ű�
	class IUIAPI CJScript
	{
	public:
		CJScript();
		virtual ~CJScript();

	protected:
		const CIUIString GetSystemErrorMessage(DWORD dwError);
		CIUIString GetNextToken(CIUIString &strSrc, const CIUIString strDelim, BOOL bTrim = FALSE, BOOL bFindOneOf = TRUE);
		BOOL GetJScript(OUT IDispatch **pDisp);
		BOOL GetJScripts(IHTMLElementCollection *pColl);
		CIUIString ScanJScript(CIUIString &strAText, std::vector<CIUIString> &args);

	public:
		BOOL SetScriptDocument(LPDISPATCH pDisp);
		BOOL JScriptOK();

		BOOL CallJScript(const CIUIString strFunc, _variant_t *pVarResult = NULL);
		BOOL CallJScript(const CIUIString strFunc, const CIUIString strArg1, _variant_t *pVarResult = NULL);
		BOOL CallJScript(const CIUIString strFunc, const CIUIString strArg1, const CIUIString strArg2, _variant_t *pVarResult = NULL);
		BOOL CallJScript(const CIUIString strFunc, const CIUIString strArg1, const CIUIString strArg2, const CIUIString strArg3, _variant_t *pVarResult = NULL);
		BOOL CallJScript(const CIUIString strFunc, const std::vector<CIUIString> &paramArray, _variant_t *pVarResult = NULL);

		// �޸���ҳԪ�ص�����
		BOOL PutElementHtml(CIUIString ElemID, CIUIString Html);
		// ȡ��Ԫ�ص�ֵ
		BOOL GetElementValue(CIUIString ElemID, CIUIString &Value);
		// ����Ԫ�ص�ֵ
		BOOL PutElementValue(CIUIString ElemID, CIUIString Value);
		// ��Ԫ�����ý���
		void ElementSetFocus(CIUIString EleName);
		IHTMLStyle *GetElementStyle(CIUIString ElemID);
		HRESULT GetElement(LPCTSTR szElementId, IDispatch **ppdisp, BOOL *pbCollection = NULL);
		HRESULT GetElement(LPCTSTR szElementId, IHTMLElement **pphtmlElement);
		HRESULT GetElementInterface(LPCTSTR szElementId, REFIID riid, void **ppvObj);

	protected:
		IHTMLDocument2 *m_pDoc;
	};

	struct IUIAPI SHtmlViewInvoke
	{
		DISPID dispIdMember;
		//REFIID riid;
		LCID lcid;
		WORD wFlags;
		DISPPARAMS *pDispParams;
		VARIANT *pVarResult;
		EXCEPINFO *pExcepInfo;
		UINT *puArgErr;
	};

	class IUIAPI HtmlViewCore
		: public IDispatch
		, public IOleClientSite
		, public IOleInPlaceSite
		, public IOleInPlaceFrame
		, public IDocHostUIHandler
	{
	public:
		HtmlViewCore();
		virtual ~HtmlViewCore();

	protected:
		//IUnKnown
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
		virtual ULONG STDMETHODCALLTYPE AddRef(void);
		virtual ULONG STDMETHODCALLTYPE Release(void);

		//IDispatch
		virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT *pctinfo);
		virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
		virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
		virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
			DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);

		//IOleWindow
		virtual HRESULT STDMETHODCALLTYPE GetWindow(HWND *phwnd);
		virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode);

		//IOleInPlaceUIWindow
		virtual HRESULT STDMETHODCALLTYPE GetBorder(LPRECT lprectBorder);
		virtual HRESULT STDMETHODCALLTYPE RequestBorderSpace(LPCBORDERWIDTHS pborderwidths);
		virtual HRESULT STDMETHODCALLTYPE SetBorderSpace(LPCBORDERWIDTHS pborderwidths);
		virtual HRESULT STDMETHODCALLTYPE SetActiveObject(IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName);

		//IOleInPlaceFrame
		virtual HRESULT STDMETHODCALLTYPE InsertMenus(HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths);
		virtual HRESULT STDMETHODCALLTYPE SetMenu(HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject);
		virtual HRESULT STDMETHODCALLTYPE RemoveMenus(HMENU hmenuShared);
		virtual HRESULT STDMETHODCALLTYPE SetStatusText(LPCOLESTR pszStatusText);
		virtual HRESULT STDMETHODCALLTYPE EnableModeless(BOOL fEnable);
		virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpmsg, WORD wID);

		//IOleClientSite
		virtual HRESULT STDMETHODCALLTYPE SaveObject(void);
		virtual HRESULT STDMETHODCALLTYPE GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);
		virtual HRESULT STDMETHODCALLTYPE GetContainer(IOleContainer **ppContainer);
		virtual HRESULT STDMETHODCALLTYPE ShowObject(void);
		virtual HRESULT STDMETHODCALLTYPE OnShowWindow(BOOL fShow);
		virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout(void);

		//IDocHostUIHandler
		virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved);
		virtual HRESULT STDMETHODCALLTYPE GetHostInfo(DOCHOSTUIINFO *pInfo);
		virtual HRESULT STDMETHODCALLTYPE ShowUI(DWORD dwID, IOleInPlaceActiveObject *pActiveObject,
			IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc);
		virtual HRESULT STDMETHODCALLTYPE HideUI(void);
		virtual HRESULT STDMETHODCALLTYPE UpdateUI(void);
		virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate(BOOL fActivate);
		virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(BOOL fActivate);
		virtual HRESULT STDMETHODCALLTYPE ResizeBorder(LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow);
		virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID);
		virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath(LPOLESTR *pchKey, DWORD dw);
		virtual HRESULT STDMETHODCALLTYPE GetDropTarget(IDropTarget *pDropTarget, IDropTarget **ppDropTarget);
		virtual HRESULT STDMETHODCALLTYPE GetExternal(IDispatch **ppDispatch);
		virtual HRESULT STDMETHODCALLTYPE TranslateUrl(DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut);
		virtual HRESULT STDMETHODCALLTYPE FilterDataObject(IDataObject *pDO, IDataObject **ppDORet);

		//IOleInPlaceSite
		virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate(void);
		virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate(void);
		virtual HRESULT STDMETHODCALLTYPE OnUIActivate(void);
		virtual HRESULT STDMETHODCALLTYPE GetWindowContext(IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc,
			LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo);
		virtual HRESULT STDMETHODCALLTYPE Scroll(SIZE scrollExtant);
		virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate(BOOL fUndoable);
		virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate(void);
		virtual HRESULT STDMETHODCALLTYPE DiscardUndoState(void);
		virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo(void);
		virtual HRESULT STDMETHODCALLTYPE OnPosRectChange(LPCRECT lprcPosRect);

	public:
		HTMLV *pHtml;
	};

	class IUIAPI HtmlView : public CWLWnd
	{
	public:
		HtmlView();
		virtual ~HtmlView();
		virtual int BindStyle(const CControlProp *pCtrlProp);

	public:
		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParentWnd,
			LPCTSTR lpszName
		);

		IOleObject *GetIOleObject();
		IWebBrowser2 *GetIWebBrowser2();
		IOleInPlaceObject *GetIOleInPlaceObject();
		IOleInPlaceActiveObject *GetIOleInPlaceActiveObject();

		// Attributes
	public:
		CIUIString GetType() const;
		HWND GetHWND() const;
		long GetLeft() const;
		void SetLeft(long nNewValue);
		long GetTop() const;
		void SetTop(long nNewValue);
		virtual int GetHeight() const;
		void SetHeight(long nNewValue);
		virtual int GetWidth() const;
		void SetWidth(long nNewValue);
		void SetVisible(BOOL bNewValue);
		BOOL GetVisible() const;
		CIUIString GetLocationName() const;
		READYSTATE GetReadyState() const;
		BOOL GetOffline() const;
		void SetOffline(BOOL bNewValue);
		BOOL GetSilent() const;
		void SetSilent(BOOL bNewValue);
		BOOL GetTopLevelContainer() const;
		CIUIString GetLocationURL() const;
		BOOL GetBusy() const;
		LPDISPATCH GetApplication() const;
		LPDISPATCH GetParentBrowser() const;
		LPDISPATCH GetContainer() const;
		LPDISPATCH GetHtmlDocument() const;
		CIUIString GetFullName() const;
		int GetToolBar() const;
		void SetToolBar(int nNewValue);
		BOOL GetMenuBar() const;
		void SetMenuBar(BOOL bNewValue);
		BOOL GetFullScreen() const;
		void SetFullScreen(BOOL bNewValue);
		OLECMDF QueryStatusWB(OLECMDID cmdID) const;
		BOOL GetRegisterAsBrowser() const;
		void SetRegisterAsBrowser(BOOL bNewValue);
		BOOL GetRegisterAsDropTarget() const;
		void SetRegisterAsDropTarget(BOOL bNewValue);
		BOOL GetTheaterMode() const;
		void SetTheaterMode(BOOL bNewValue);
		BOOL GetAddressBar() const;
		void SetAddressBar(BOOL bNewValue);
		BOOL GetStatusBar() const;
		void SetStatusBar(BOOL bNewValue);

		// Operations
	public:
		void GoBack();
		void GoForward();
		void GoHome();
		void GoSearch();
		void Navigate(LPCTSTR URL, DWORD dwFlags = 0,
			LPCTSTR lpszTargetFrameName = NULL,
			LPCTSTR lpszHeaders = NULL, LPVOID lpvPostData = NULL,
			DWORD dwPostDataLen = 0);
		void Navigate2(LPITEMIDLIST pIDL, DWORD dwFlags = 0,
			LPCTSTR lpszTargetFrameName = NULL);
		void Navigate2(LPCTSTR lpszURL, DWORD dwFlags = 0,
			LPCTSTR lpszTargetFrameName = NULL,	LPCTSTR lpszHeaders = NULL,
			LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0);
		//void Navigate2(LPCTSTR lpszURL, DWORD dwFlags,
		//	CByteArray &baPostedData,
		//	LPCTSTR lpszTargetFrameName = NULL, LPCTSTR lpszHeader = NULL);
		void Refresh();
		void Refresh2(int nLevel);
		void Stop();
		void PutProperty(LPCTSTR lpszProperty, const VARIANT &vtValue);
		void PutProperty(LPCTSTR lpszPropertyName, double dValue);
		void PutProperty(LPCTSTR lpszPropertyName, LPCTSTR lpszValue);
		void PutProperty(LPCTSTR lpszPropertyName, long lValue);
		void PutProperty(LPCTSTR lpszPropertyName, short nValue);
		BOOL GetProperty(LPCTSTR lpszProperty, CIUIString &strValue);
		CIUIOleVariant GetProperty(LPCTSTR lpszProperty);
		void ExecWB(OLECMDID cmdID, OLECMDEXECOPT cmdexecopt, VARIANT *pvaIn,
			VARIANT *pvaOut);
		virtual BOOL GetSource(CIUIString &strRef);
		BOOL LoadFromResource(LPCTSTR lpszResource);
		BOOL LoadFromResource(UINT nRes);

		HRESULT QueryFormsCommand(DWORD dwCommandID, BOOL *pbSupported,
			BOOL *pbEnabled, BOOL *pbChecked);
		HRESULT ExecFormsCommand(DWORD dwCommandID, VARIANT *pVarIn,
			VARIANT *pVarOut);

		void FilePrint();

		// Events
		virtual void OnNavigateComplete2(LPCTSTR strURL);
		virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
			LPCTSTR lpszTargetFrameName, std::vector<BYTE> &baPostedData,
			LPCTSTR lpszHeaders, BOOL *pbCancel);
		virtual void OnStatusTextChange(LPCTSTR lpszText);
		virtual void OnProgressChange(long nProgress, long nProgressMax);
		virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
		virtual void OnDownloadBegin();
		virtual void OnDownloadComplete();
		virtual void OnTitleChange(LPCTSTR lpszText);
		virtual void OnPropertyChange(LPCTSTR lpszProperty);
		virtual void OnNewWindow2(LPDISPATCH *ppDisp, BOOL *Cancel);
		virtual void OnDocumentComplete(LPCTSTR lpszURL);
		virtual void OnQuit();
		virtual void OnVisible(BOOL bVisible);
		virtual void OnToolBar(BOOL bToolBar);
		virtual void OnMenuBar(BOOL bMenuBar);
		virtual void OnStatusBar(BOOL bStatusBar);
		virtual void OnFullScreen(BOOL bFullScreen);
		virtual void OnTheaterMode(BOOL bTheaterMode);
		virtual void OnNavigateError(LPCTSTR lpszURL, LPCTSTR lpszFrame, DWORD dwError, BOOL *pbCancel);

		// Extended
		int ShowBorder(BOOL bShow, BOOL bRedraw = TRUE);
		int ShowIEScrollBar(BOOL bShow, BOOL bRedraw = TRUE);
		int ShowContextMenu(BOOL bShow);

		/*
		 ��HTML������ʽ��ʾ��ҳ(����ҳ)
		 ����:<P>����һ��ͼƬ<P><IMG src="mypic.jpg">
		 ע:����Ҫ<BODY></BODY>��ǩ
		*/
		virtual BOOL PutHtmlCode(IN PWCHAR pszCode);
		virtual BOOL GetHtmlCode(OUT PWCHAR pszCode, IN OUT int *iszCount/*�ַ���*/);
		virtual BOOL ClickElementByID(PWCHAR pID);
		// ���ݿؼ�ID����ֵ, �����Զ����
		virtual BOOL SetElementValueByID(IN PWCHAR pID, IN PWCHAR pszValue);
		// ���ݿؼ�ID��ȡֵ
		virtual BOOL GetElementValueByID(IN PWCHAR pID, IN PWCHAR pszValue, IN OUT int *iszCount/*�ַ���*/);
	};

	class IUIAPI SplitterBar : public CWLWnd
	{
	public:
		SplitterBar();
		virtual ~SplitterBar();

		virtual BOOL Create(
			CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParent,
			LPCTSTR lpszName
		);

	public:
		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameP,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw
		);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameP,
			CIUIString *pstrImageNameD
		) const;

		int SetHCursor(HCURSOR hCursor);
		HCURSOR GetHCursor();

		int SetVCursor(HCURSOR hCursor);
		HCURSOR GetVCursor();

		int SetOrientation(SPLITTER_ORIENTATION eOrientation);
		SPLITTER_ORIENTATION GetOrientation() const;

		// hPanel1: left or top panel, hPanel2: right or bottom panel.
		int AddPanel(HWLWND hPanel1, HWLWND hPanel2);
		HWLWND GetPanel1();
		HWLWND GetPanel2();
		// Replace panel1 pointer to another.
		HWLWND ReplacePanel1(HWLWND hNewPanel1);
		// Replace panel1 pointer to another.
		HWLWND ReplacePanel2(HWLWND hNewPanel2);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class Label;
	class Button;
	class ToolTipCtrl;

	class IUIAPI ProgressBar : public CWLWnd
	{
	public:
		ProgressBar();
		virtual ~ProgressBar();

		virtual int BindStyle(const CControlProp *pCtrlProp);

		BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hParent,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName);

		// Generic creator allowing extended style bits
		BOOL CreateEx(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwExStyle,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hParent,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName);

		// Attributes

		// Sets range of values for the control. (16-bit limit)
		void SetRange(__in short nLower, __in short nUpper);

		// Sets range of values for the control. (32-bit limit)
		void SetRange32(__in int nLower, __in int nUpper);

		// Retrieves range of values for the control. (32-bit limit)
		void GetRange(__out int &nLower, __out int &nUpper) const;

		// Gets the current position within the set range of the control.
		int GetPos() const;

		// Sets the current position within the set range of the control.
		int SetPos(__in int nPos);

		// Displaces the current position within the set range of the
		// control by the passed value.
		int OffsetPos(__in int nPos);

		// Sets the step by which increments happen with a call to StepIt().
		int SetStep(__in int nStep);

		// Sets the control's background color.
		COLORREF SetBkColor(__in COLORREF clrNew);

#if (_WIN32_IE >= 0x0400)
		// Sets the color of the progress indicator bar in the progress bar control.
		COLORREF SetBarColor(__in COLORREF clrBar);
#endif	// _WIN32_IE >= 0x0400

#if (_WIN32_WINNT >= 0x0501) && defined(UNICODE)
		// Sets the progress bar control to marquee mode.
		BOOL SetMarquee(__in BOOL fMarqueeMode, __in int nInterval);
#endif	// _WIN32_WINNT >= 0x0501 && defined(UNICODE)

		// Operations

		// Steps the control by the value set with SetStep().
		int StepIt();

		// IUI Add
		// Thumb
		BOOL SetDrawThumbColor(BOOL bDraw);
		BOOL IsDrawThumbColor() const;

		int SetThumbBkColor(COLORREF crStart, COLORREF crEnd);
		int GetThumbBkColor(OUT COLORREF *pcrStart, OUT COLORREF *pcrEnd) const;

		COLORREF SetThumbBorderColor(COLORREF cr);
		COLORREF GetThumbBorderColor() const;

		BOOL CombineThumbImage(BOOL bCombine);
		BOOL IsCombineThumbImage() const;

		int SetCombineThumbImage(LPCTSTR lpszImage);
		LPCTSTR GetCombineThumbImage() const;

		int SetNormalThumbImage(LPCTSTR lpszImage);
		LPCTSTR GetNormalThumbImage() const;

		int SetDisabledThumbImage(LPCTSTR lpszImage);
		LPCTSTR GetDisabledThumbImage() const;
	};

	class IUIAPI Slider : public CWLWnd
	{
		// Constructors
	public:
		Slider();
		virtual ~Slider();

		virtual int BindStyle(const CControlProp *pCtrlProp);

		// Generic creator
		BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hParent,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName);

		// Generic creator allowing extended style bits
		BOOL CreateEx(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwExStyle,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hParent,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName);

		// Attributes
		// Retrieves the number of logical positions the trackbar control's slider
		// moves in response to keyboard input from the up/down arrow keys.
		int GetLineSize() const;

		// Sets the number of logical positions the trackbar control's slider
		// moves in response to keyboard input from the up/down arrow keys.
		int SetLineSize(__in int nSize);

		// Retrieves the number of logical positions the trackbar control's slider
		// moves in response to keyboard input from the PgUp/PgDn keys.
		int GetPageSize() const;

		// Sets the number of logical positions the trackbar control's slider
		// moves in response to keyboard input from the PgUp/PgDn keys.
		int SetPageSize(__in int nSize);

		// Retrieves the maximum position for the slider in the trackbar control.
		int GetRangeMax() const;

		// Retrieves the minimum position for the slider in the trackbar control.
		int GetRangeMin() const;

		// Retrieves the minimum and maximum positions for the slider in the trackbar control.
		void GetRange(__out int &nMin, __out int &nMax) const;

		// Sets the minimum position for the slider in the trackbar control.
		void SetRangeMin(__in int nMin, __in BOOL bRedraw = FALSE);

		// Sets the maximum position for the slider in the trackbar control.
		void SetRangeMax(__in int nMax, __in BOOL bRedraw = FALSE);

		// Sets the minimum and maximum positions for the slider in the trackbar control.
		void SetRange(__in int nMin, __in int nMax, __in BOOL bRedraw = FALSE);

		// Retrieves the starting and ending positions of the selection in the trackbar control.
		void GetSelection(__out int &nMin, __out int &nMax) const;

		// Sets the starting and ending positions of the selection in the trackbar control.
		void SetSelection(__in int nMin, __in int nMax);

		// Retrieves the bounding rectangle for the trackbar control's channel.
		void GetChannelRect(__out LPRECT lprc) const;

		// Retrieves the bounding rectangle for the slider in the trackbar control.
		void GetThumbRect(__out LPRECT lprc) const;

		// Retrieves the current logical position of the slider in the trackbar control.
		int GetPos() const;

		// Sets the current logical position of the slider in the trackbar control.
		void SetPos(__in int nPos);

		// Retrieves the number of tick marks in a trackbar control.
		UINT GetNumTics() const;

		// Retrieves an array of positions of tick marks in the trackbar control.
		DWORD *GetTicArray() const;

		// Retrieves the logical position of the specified tick mark in the trackbar control.
		int GetTic(__in int nTic) const;

		// Retrieves the current physical position of the specified tick mark in the trackbar control.
		int GetTicPos(__in int nTic) const;

		// Sets a tick mark in the trackbar control at the specified logical position.
		BOOL SetTic(__in int nTic);

		// Sets the interval frequency for tick marks in the trackbar control.
		void SetTicFreq(__in int nFreq);

		// Retrieves the trackbar control buddy window at the specified location.
		HWLWND GetBuddy(__in BOOL fLocation = TRUE) const;

		// Assigns the specified window as the buddy window for the trackbar control.
		HWLWND SetBuddy(__in HWLWND hWndBuddy, __in BOOL fLocation = TRUE);

		// Retrieves the ToolTip control assigned to the trackbar control.
		ToolTipCtrl *GetToolTips() const;

		// Assigns a ToolTip control to the trackbar control.
		void SetToolTips(__in ToolTipCtrl *pWndTip);

		// Positions the ToolTip control used by the trackbar control.
		int SetTipSide(__in int nLocation);

		// ����ˮƽSlider����ĸ߶Ȼ��ߴ�ֱSlider����Ŀ��
		// ˮƽSlider����Ŀ�Ȼ��ߴ�ֱSlider����ĸ߶�Ĭ����ThumbLength��ֵ����2�õ���
		// ���ɵ�������
		void SetThumbLength(__in int nLength);

		// Retrieves the length of the slider in the trackbar control.
		int GetThumbLength() const;

		void SetThumbWidth(__in int nWidth);
		int GetThumbWidth() const;

		// Operations
		// Clears the current selection range in the trackbar control.
		void ClearSel(__in BOOL bRedraw = FALSE);

		// Removes the current tick marks from the trackbar control.
		void ClearTics(__in BOOL bRedraw = FALSE);

		// IUI Add
		int SetScrollAreaMargin(__in LPCRECT lprcMargin);
		int GetScrollAreaMargin(__out LPRECT lprcMargin) const;

		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameS,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameS,
			CIUIString *pstrImageNameD) const;

		// Thumb
		BOOL SetDrawThumbColor(BOOL bDraw);
		BOOL IsDrawThumbColor() const;

		COLORREF SetThumbBkColor(COLORREF cr);
		COLORREF GetThumbBkColor() const;

		COLORREF SetThumbBorderColor(COLORREF cr);
		COLORREF GetThumbBorderColor() const;

		BOOL CombineThumbImage(BOOL bCombine);
		BOOL IsCombineThumbImage() const;

		int SetCombineThumbImage(LPCTSTR lpszImage);
		LPCTSTR GetCombineThumbImage() const;

		int SetNormalThumbImage(LPCTSTR lpszImage);
		LPCTSTR GetNormalThumbImage() const;

		int SetHoverThumbImage(LPCTSTR lpszImage);
		LPCTSTR GetHoverThumbImage() const;

		int SetPressedThumbImage(LPCTSTR lpszImage);
		LPCTSTR GetPressedThumbImage() const;

		int SetDisabledThumbImage(LPCTSTR lpszImage);
		LPCTSTR GetDisabledThumbImage() const;
	};

	class IUIAPI SpinButton : public CWLWnd
	{
	public:
		SpinButton();
		virtual ~SpinButton();

	public:
		// Generic creator
		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hHost,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName);

		// Generic creator allowing extended style bits
		virtual BOOL CreateEx(
			CWLWndHandler *pUserHandler,
			DWORD dwExStyle,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParentWnd,
			LPCTSTR lpszName
		);

		// Attributes
		// Sets acceleration information for the up-down control.
		BOOL SetAccel(_In_ int nAccel, _In_ UDACCEL *pAccel);

		// Retrieves acceleration information for the up-down control.
		UINT GetAccel(_In_ int nAccel, _Out_ UDACCEL *pAccel) const;

		// Sets the radix base for the up-down control.
		int SetBase(_In_ int nBase);

		// Retrieves the current radix base for the up-down control.
		UINT GetBase() const;

		// Sets the up-down control's buddy window.
		HWLWND SetBuddy(_In_ HWLWND pWndBuddy);

		// Retrieves the up-down control's current buddy window.
		HWLWND GetBuddy() const;

		// Sets the current position of an up-down control with 16-bit precision.
		int SetPos(_In_ int nPos);

		// Retrieves the current position of an up-down control with 16-bit precision.
		int GetPos() const;

		// Sets the minimum and maximum positions (range) for the up-down control.
		void SetRange(_In_ short nLower, _In_ short nUpper);
		void SetRange32(_In_ int nLower, _In_ int nUpper);

		// Retrieves the minimum and maximum positions (range) for the up-down control.
		DWORD GetRange() const;
		void GetRange(_Out_ int &lower, _Out_ int &upper) const;
		void GetRange32(_Out_ int &lower, _Out_ int &upper) const;

		// Retrieves the current position of the up-down control with 32-bit precision.
		int GetPos32(_Out_opt_ LPBOOL lpbError = NULL) const;

		// Sets the current position of an up-down control with 32-bit precision.
		int SetPos32(_In_ int nPos);
	};

	class IUIAPI DateTimePicker : public CWLWnd
	{
	public:
		DateTimePicker();
		virtual ~DateTimePicker();

	public:
		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hHost,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName);

		// Attributes
		// Retrieves the color for the specified portion of the calendar within the datetime picker control.
		COLORREF GetMonthCalColor(_In_ int iColor) const;

		// Sets the color for the specified portion of the calendar within the datetime picker control.
		COLORREF SetMonthCalColor(_In_ int iColor, _In_ COLORREF ref);

		// Sets the display of the datetime picker control based on the specified format string.
		BOOL SetFormat(_In_z_ LPCTSTR pstrFormat);

		// Retrieves the datetime picker's child calendar control.
		HWND GetMonthCalCtrl() const;

		// Retrieves the font of the datetime picker control's child calendar control.
		HFONT GetMonthCalFont() const;

		// Sets the font of the datetime picker control's child calendar control.
		void SetMonthCalFont(_In_ HFONT hFont, _In_ BOOL bRedraw = TRUE);

		// Sets the minimum and maximum allowable times for the datetime picker control.
		BOOL SetRange(_In_ const SYSTEMTIME *pMinRange, _In_ const SYSTEMTIME *pMaxRange);

		// Retrieves the current minimum and maximum allowable times for the datetime picker control.
		DWORD GetRange(_Out_ SYSTEMTIME *pMinRange, _Out_ SYSTEMTIME *pMaxRange) const;

#if (NTDDI_VERSION >= NTDDI_VISTA) && defined(UNICODE)
		// REVIEW: Sets the style of the datetime picker control's child calendar control.
		DWORD SetMonthCalStyle(_In_ DWORD dwStyle);

		// REVIEW: Retrieves the style of the datetime picker control's child calendar control.
		DWORD GetMonthCalStyle() const;

		// Retrieves information from the datetime picker control.
		BOOL GetDateTimePickerInfo(_Out_ LPDATETIMEPICKERINFO pDateTimePickerInfo) const;

		// Retrieves the ideal size for the control (so that all the text fits).
		BOOL GetIdealSize(_Out_ LPSIZE pSize) const;
#endif // (NTDDI_VERSION >= NTDDI_VISTA) && defined(UNICODE)

		// Operations
		// Sets the time in the datetime picker control.
		BOOL SetTime(_In_ LPSYSTEMTIME pTimeNew = NULL);

		// Retrieves the currently selected time from the datetime picker control.
		DWORD GetTime(_Out_ LPSYSTEMTIME pTimeDest) const;

#if defined(UNICODE)
		// REVIEW: Closes the datetime picker control.
		void CloseMonthCal();
#endif // defined(UNICODE)

		// IUI Add
		//int SetBkImage(
		//	UINT uMask,
		//	LPCTSTR lpszImageNameN,
		//	LPCTSTR lpszImageNameH,
		//	LPCTSTR lpszImageNameP,
		//	LPCTSTR lpszImageNameD,
		//	BOOL bRedraw
		//);
		//int GetBkImage(
		//	UINT uMask,
		//	BOOL *pbCombineImage,
		//	CIUIString *pstrCombineImageName,
		//	CIUIString *pstrImageNameN,
		//	CIUIString *pstrImageNameH,
		//	CIUIString *pstrImageNameP,
		//	CIUIString *pstrImageNameD
		//) const;
	};

	enum IUIAPI IUITXTEFFECT
	{
		IUITXTEFFECT_NONE = 0,				//@emem	no special backgoround effect
		IUITXTEFFECT_SUNKEN,				//@emem	draw a "sunken 3-D" look
	};

	// CreateTextServices�ĵڶ�������
	// ��RichEdit����ʱ������ITextHost����DC�����ꡢ������ɫ���ַ���ʽ�������ʽ�Ȳ���
	// ���ԣ�ITextHostҪ��ʱ��RichEdit�ṩ��Щ������ ����RichEdit�ڲ������¼�ʱ��Ҳ��ͨ��
	// ����ITextHost::TxNotify�������档 ����ITextHost��RichEdit�ڲ������湵ͨ��������
	// ����ʾ���ַ�����꣩ʱ��Ҳ��֪ͨITextHost���ȵȡ�
	// ����: RichEdit�ڲ���Ҫ����һ��Timerʱ������RichEdit�ڲ���ͨ��RichEdit��������HWND
	// Ҳ����Windowless�����ԣ����ڲ���Ѵ���Timer�����飬����ITextHost::TxSetTimer
	// ������д������麯����ʱ�򣬾�Ҫ�Լ�����һ��timer��
	// ����RichEditҪ��ITextHost���������������Щ��������Ӧ�ö�����CTextHost��
	// ���������ڴ󲿷ֲ�����RichTextBox�ж��ж��壬������CTextHost�У�ֻ�����RichTextBox
	// �е���Ӧ�������ɣ�����CTextHost�Լ��Ͳ��ö����ˡ�
	// RichEdit���޾��ʱ��ITextHost�������д���ǲ�һ���ġ� CTextHost������޾��RichEdit�ġ�
	// �о���ģ���ο�΢������е�CTxtWinHost
	class IUIAPI CTxtWinHost : public ITextHost
	{
		friend LRESULT WINAPI RichTextBox_WndProc(HWLWND, RoutedEventArgs *);

	public:
		CTxtWinHost();
		~CTxtWinHost();
		void Shutdown();

	protected:
		// Initialization
		BOOL Init(HWLWND hRichTextBox, const CREATESTRUCT *pcs);

		void ResizeInset();
		void SetScrollBarsForWmEnable(BOOL fEnable);
		void OnSetMargins(DWORD fwMargin, DWORD xLeft, DWORD xRight);
		void SetScrollInfo(INT fnBar, BOOL fRedraw);

		// helpers
		void RevokeDragDrop(void);
		void RegisterDragDrop(void);
		void DrawSunkenBorder(HWND hwnd, HDC hdc);
		VOID OnSunkenWindowPosChanging(HWND hwnd, WINDOWPOS *pwndpos);
		LRESULT OnSize(HWND hwnd, WORD fwSizeType, int nWidth, int nHeight);
		IUITXTEFFECT TxGetEffects() const;
		HRESULT	OnTxVisibleChange(BOOL fVisible);
		void SetDefaultInset();
		void ImmAssociateNULLContext(BOOL fReadOnly);
		BOOL IsTransparentMode()
		{
			return (m_dwExStyle & WS_EX_TRANSPARENT);
		}

		// Keyboard messages
		LRESULT	OnKeyDown(WORD vKey, DWORD dwFlags);
		LRESULT	OnChar(WORD vKey, DWORD dwFlags);

		// System notifications
		void OnSysColorChange();
		LRESULT OnGetDlgCode(WPARAM wparam, LPARAM lparam);

		// Other messages
		LRESULT OnGetOptions() const;
		void OnSetOptions(WORD wOp, DWORD eco);
		void OnSetReadOnly(BOOL fReadOnly);
		void OnGetRect(LPRECT prc);
		void OnSetRect(LPRECT prc, BOOL fNewBehavior);

	public:
		// Window creation/destruction
		static void OnNCDestroy(CTxtWinHost *ped);
		LRESULT OnCreate(const CREATESTRUCT *pcs);

		// Window proc
		virtual LRESULT	TxWindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

		// Accumulate two WM_CHARs for ANSI DBC
		BOOL IsAccumulateDBCMode()
		{
			return m_fAccumulateDBC;
		}

		// Set/Clear Cumulate mode
		void SetAccumulateDBCMode(WORD fSetClearMode)
		{
			m_fAccumulateDBC = fSetClearMode;
		}

		// -----------------------------
		//	IUnknown interface
		// -----------------------------
		virtual HRESULT _stdcall QueryInterface(REFIID riid, void **ppvObject);
		virtual ULONG _stdcall AddRef(void);
		virtual ULONG _stdcall Release(void);

		// -----------------------------
		//	ITextHost interface
		// -----------------------------
		virtual HDC TxGetDC();
		virtual INT TxReleaseDC(HDC hdc);
		virtual BOOL TxShowScrollBar(INT fnBar, BOOL fShow);
		virtual BOOL TxEnableScrollBar(INT fuSBFlags, INT fuArrowflags);
		virtual BOOL TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw);
		virtual BOOL TxSetScrollPos(INT fnBar, INT nPos, BOOL fRedraw);
		virtual void TxInvalidateRect(LPCRECT prc, BOOL fMode);
		virtual void TxViewChange(BOOL fUpdate);
		virtual BOOL TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight);
		virtual BOOL TxShowCaret(BOOL fShow);
		virtual BOOL TxSetCaretPos(INT x, INT y);
		virtual BOOL TxSetTimer(UINT idTimer, UINT uTimeout);
		virtual void TxKillTimer(UINT idTimer);
		virtual void TxScrollWindowEx(INT dx, INT dy, LPCRECT lprcScroll, LPCRECT lprcClip,
			HRGN hrgnUpdate, LPRECT lprcUpdate, UINT fuScroll);
		virtual void TxSetCapture(BOOL fCapture);
		virtual void TxSetFocus();
		virtual void TxSetCursor(HCURSOR hcur, BOOL fText);
		virtual BOOL TxScreenToClient(LPPOINT lppt);
		virtual BOOL TxClientToScreen(LPPOINT lppt);
		virtual HRESULT TxActivate(LONG *plOldState);
		virtual HRESULT TxDeactivate(LONG lNewState);
		virtual HRESULT TxGetClientRect(LPRECT prc);
		virtual HRESULT TxGetViewInset(LPRECT prc);
		virtual HRESULT TxGetCharFormat(const CHARFORMATW **ppCF);
		virtual HRESULT TxGetParaFormat(const PARAFORMAT **ppPF);
		virtual COLORREF TxGetSysColor(int nIndex);
		virtual HRESULT	TxGetBackStyle(TXTBACKSTYLE *pstyle);
		virtual HRESULT TxGetMaxLength(DWORD *plength);
		virtual HRESULT TxGetScrollBars(DWORD *pdwScrollBar);
		virtual HRESULT TxGetPasswordChar(TCHAR *pch);
		virtual HRESULT TxGetAcceleratorPos(LONG *pcp);
		virtual HRESULT TxGetExtent(LPSIZEL lpExtent);
		virtual HRESULT OnTxCharFormatChange(const CHARFORMATW *pcf);
		virtual HRESULT OnTxParaFormatChange(const PARAFORMAT *ppf);
		virtual HRESULT TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits);
		virtual HRESULT TxNotify(DWORD iNotify, void *pv);
		//L virtual HRESULT TxGetUndoManager(IUndoActionManager **ppUndoMgr);
		virtual HIMC TxImmGetContext(void);
		virtual void TxImmReleaseContext(HIMC himc);
		virtual HRESULT TxGetSelectionBarWidth(LONG *lSelBarWidth);

		// ITextHost2 methods
		virtual BOOL TxIsDoubleClickPending();
		virtual HRESULT TxGetWindow(HWND *phwnd);
		virtual HRESULT TxSetForegroundWindow();
		virtual HPALETTE TxGetPalette();

	public:
		ITextServices *GetTextServices()
		{
			return m_pserv;
		}

	protected:
		static LONG _xWidthSys;
		static LONG _yHeightSys;

	protected:
		HMODULE m_hRichEdit20Mod;
		// �����������HWND��RichEdit������Ӧ����HWND _hwnd;
		HWLWND m_hRichTextBox;
		HWND _hwndParent;			// parent window
		HWND m_hwndListBox;			// List box of combobox

		ITextServices *m_pserv;			// pointer to Text Services object

		ULONG m_crefs; // reference count

		// Properties
		DWORD m_dwStyle;				// style bits
		DWORD m_dwExStyle;				// extended style bits

		unsigned m_fBorder : 1;	// control has border
		unsigned m_fInBottomless : 1;	// inside bottomless callback
		unsigned m_fInDialogBox : 1;	// control is in a dialog box
		unsigned m_fEnableAutoWordSel : 1;	// enable Word style auto word selection?
		unsigned m_fIconic : 1;	// control window is iconic
		unsigned m_fHidden : 1;	// control window is hidden
		unsigned m_fNotSysBkgnd : 1;	// not using system background color
		unsigned m_fWindowLocked : 1;	// window is locked (no update)
		unsigned m_fRegisteredForDrop : 1; // whether host has registered for drop
		unsigned m_fVisible : 1;	// Whether window is visible or not.
		unsigned m_fResized : 1;	// resized while hidden
		unsigned m_fDisabled : 1;	// Window is disabled.
		unsigned m_fKeyMaskSet : 1;	// if ENM_KEYEVENTS has been set
		unsigned m_fMouseMaskSet : 1;	// if ENM_MOUSEEVENTS has been set
		unsigned m_fScrollMaskSet : 1;	// if ENM_SCROLLEVENTS has been set
		unsigned m_fUseSpecialSetSel : 1; // TRUE = use EM_SETSEL hack to not select
		// empty controls to make dialog boxes work.
		unsigned m_fEmSetRectCalled	: 1;	// TRUE - application called EM_SETRECT
		unsigned m_fAccumulateDBC : 1;	// TRUE - need to cumulate ytes from 2 WM_CHAR msgs
		// we are in this mode when we receive VK_PROCESSKEY

		TCHAR m_chPassword; // Password char. If null, no password
		COLORREF m_crBackground; // background color
		RECT m_rcViewInset;  // view rect inset /r client rect

		HIMC m_oldhimc;	 // previous IME Context
		DWORD m_usIMEMode; // mode of IME operation
		// either 0 or ES_SELFIME or ES_NOIME
		LONG m_yInset;
		LONG m_xInset;

		HPALETTE m_hpal;					// Logical palette to use.

		TCHAR m_chLeadByte;			// use when we are in m_fAccumulateDBC mode
		// Ĭ���ַ���ʽ
		CHARFORMATW m_cfDefault;
	};

	// ���뵽RichEdit�е�Ole�ؼ���
	// OLE�ؼ�����Ҫ��װ��DLL�� ����ҪCoCreateInstance������Ole����
	// OLE�ؼ�����HWLWND�ؼ���������ΪHWLWND�ؼ�������
	// �����Ҫ������ͬ���͵�OLE�ؼ���ֻ�����ò�ͬ�����HWLWND��Ȼ�����SetOleBindWindowless
	// �󶨵�OLE�ϼ��ɡ�
	// �������RichEdit�е�OLE��OleControl������ͨ��
	// QueryInterface(IID_IUIOleControl, OleControl **)
	// ���Եõ�OleControl��ָ��
	extern const IID IID_IUIOleControl;
	class OleControl : public IOleObject, public IViewObject2
	{
	public:
		OleControl(UINT uID, HWLWND hParent);
		~OleControl();

	public:
		// IUnknown������ӿ�
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
		virtual ULONG STDMETHODCALLTYPE AddRef(void);
		virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		// IOleObject������ӿ�
		virtual HRESULT STDMETHODCALLTYPE SetHostNames(
			/* [in] */ LPCOLESTR szContainerApp,
			/* [unique][in] */ LPCOLESTR szContainerObj)
		{
			return S_OK;
		}
		virtual HRESULT STDMETHODCALLTYPE Close(
			/* [in] */ DWORD dwSaveOption)
		{
			return S_OK;
		}
		virtual HRESULT STDMETHODCALLTYPE SetMoniker(
			/* [in] */ DWORD dwWhichMoniker,
			/* [unique][in] */ IMoniker *pmk)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE GetMoniker(
			/* [in] */ DWORD dwAssign,
			/* [in] */ DWORD dwWhichMoniker,
			/* [out] */ IMoniker **ppmk)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE InitFromData(
			/* [unique][in] */ IDataObject *pDataObject,
			/* [in] */ BOOL fCreation,
			/* [in] */ DWORD dwReserved)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE GetClipboardData(
			/* [in] */ DWORD dwReserved,
			/* [out] */ IDataObject **ppDataObject)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE DoVerb(
			/* [in] */ LONG iVerb,
			/* [unique][in] */ LPMSG lpmsg,
			/* [unique][in] */ IOleClientSite *pActiveSite,
			/* [in] */ LONG lindex,
			/* [in] */ HWND hwndParent,
			/* [unique][in] */ LPCRECT lprcPosRect)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE EnumVerbs(
			/* [out] */ IEnumOLEVERB **ppEnumOleVerb)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE Update(void)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE IsUpToDate(void)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE GetUserType(
			/* [in] */ DWORD dwFormOfType,
			/* [out] */ LPOLESTR *pszUserType)
		{
			return E_NOTIMPL;
		}

		virtual HRESULT STDMETHODCALLTYPE EnumAdvise(
			/* [out] */ IEnumSTATDATA **ppenumAdvise)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE GetMiscStatus(
			/* [in] */ DWORD dwAspect,
			/* [out] */ DWORD *pdwStatus)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE SetColorScheme(
			/* [in] */ LOGPALETTE *pLogpal)
		{
			return E_NOTIMPL;
		}

		// ��Ҫʵ��
		virtual HRESULT STDMETHODCALLTYPE SetClientSite(
			/* [unique][in] */ IOleClientSite *pClientSite);
		virtual HRESULT STDMETHODCALLTYPE GetClientSite(
			/* [out] */ IOleClientSite **ppClientSite);
		virtual HRESULT STDMETHODCALLTYPE GetUserClassID(
			/* [out] */ CLSID *pClsid);
		virtual HRESULT STDMETHODCALLTYPE SetExtent(
			/* [in] */ DWORD dwDrawAspect,
			/* [in] */ SIZEL *psizel);
		virtual HRESULT STDMETHODCALLTYPE GetExtent(
			/* [in] */ DWORD dwDrawAspect,
			/* [out] */ SIZEL *psizel);
		virtual HRESULT STDMETHODCALLTYPE Advise(
			/* [unique][in] */ IAdviseSink *pAdvSink,
			/* [out] */ DWORD *pdwConnection);
		virtual HRESULT STDMETHODCALLTYPE Unadvise(
			/* [in] */ DWORD dwConnection);

	public:
		// IViewObject2 �ķ���
		HRESULT STDMETHODCALLTYPE GetColorSet(DWORD, LONG, void *, DVTARGETDEVICE *, HDC, LOGPALETTE **)
		{
			return E_NOTIMPL;
		}
		HRESULT STDMETHODCALLTYPE Freeze(DWORD, LONG, void *, DWORD *)
		{
			return S_OK;
		}
		HRESULT STDMETHODCALLTYPE Unfreeze(DWORD dwFreeze)
		{
			return S_OK;
		}

		// ���½ӿ���Ҫʵ��
		HRESULT STDMETHODCALLTYPE SetAdvise(DWORD aspects, DWORD advf, IAdviseSink *pAdvSink);
		HRESULT STDMETHODCALLTYPE GetAdvise(DWORD *pAspects, DWORD *pAdvf, IAdviseSink **ppAdvSink);
		HRESULT STDMETHODCALLTYPE Draw(
			DWORD dwDrawAspect, LONG lindex,
			void *pvAspect,
			DVTARGETDEVICE *ptd,
			HDC hdcTargetDev,
			HDC hdcDraw,
			LPCRECTL lprcBounds,
			LPCRECTL lprcWBounds,
			BOOL(STDMETHODCALLTYPE *pfnContinue)(ULONG_PTR dwContinue),
			ULONG_PTR dwContinue);
		HRESULT STDMETHODCALLTYPE GetExtent(DWORD dwDrawAspect, LONG lindex,
			DVTARGETDEVICE *ptd, LPSIZEL lpsizel);

	public:
		HWLWND SetOleBindWindowless(HWLWND hNewBind);
		HWLWND GetOleBindWindowless();

		LPARAM SetUserData(LPARAM lParam);
		LPARAM GetUserData() const;

		// �����Ƿ�����OLE�߿�OLE�����ڻ��Ʊ߿�ǰ��������û�һ���޸�"�Ƿ���Ʊ߿�"�Ļ���
		// ͨ����󶨵Ŀؼ�·��WLM_GETHIDEOLEBORDER��Ϣ���û����Ըı������Ϊ��
		BOOL SetHideBorder(BOOL bHide);
		BOOL IsHideBorder() const;

	protected:
		UINT IDD; // Same as CDialog::IDD

	protected:
		IOleClientSite *m_pOleClientSite;
		SIZEL m_sizeExtent;
		// �����RichEdit�����꣬����OLE�ɼ�ʱ��Ч
		CIUIRect m_rect;
		// �û��Զ�������
		LPARAM m_lParam;
		// �Ƿ�����OLE�߿�
		BOOL m_bHideBorder;

		// OLE�ؼ��ĸ��ؼ�
		HWLWND m_hParent;
		// OLE�ؼ���Ϊ�󶨿ؼ���������
		HWLWND m_hBindWindowless;
	};

	class IUIAPI CImageOleCtrl : public OleControl
	{
	public:
		CImageOleCtrl(HWLWND hRichEdit);
		virtual ~CImageOleCtrl();

		virtual int ReleaseObject();

	protected:
		HRESULT STDMETHODCALLTYPE SetClientSite(
			/* [unique][in] */ IOleClientSite *pClientSite);

		HRESULT STDMETHODCALLTYPE Draw(
			DWORD dwDrawAspect, LONG lindex,
			void *pvAspect,
			DVTARGETDEVICE *ptd,
			HDC hdcTargetDev,
			HDC hdcDraw,
			LPCRECTL lprcBounds,
			LPCRECTL lprcWBounds,
			BOOL(STDMETHODCALLTYPE *pfnContinue)(ULONG_PTR dwContinue),
			ULONG_PTR dwContinue);

	public:
		int SetImage(LPCTSTR lpszImagePath);
		int SetImage(HBITMAP hBitmap);
		HIUIIMAGE GetImage() const;

	protected:
		HIUIIMAGE m_hIUIImage;
	};

	class IUIAPI RichTextBox : public CWLWnd
	{
		friend class CTxtWinHost;
	public:
		RichTextBox();
		~RichTextBox();

		virtual BOOL Create(
			CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParentWnd,
			LPCTSTR lpszName);

		virtual BOOL CreateEx(
			CWLWndHandler *pUserHandler,
			DWORD dwExStyle,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParentWnd,
			LPCTSTR lpszName
		);

		virtual CIUIString GetClassName() const;

		virtual LRESULT TxSendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
		virtual LRESULT TxSendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const;

		//<<Begin Copy from CRichEditCtrl
	public:
		// Attributes
		BOOL CanUndo() const;
		BOOL CanRedo() const;
		UNDONAMEID GetUndoName() const;
		UNDONAMEID GetRedoName() const;
		int GetLineCount() const;
		BOOL GetModify() const;
		void SetModify(__in BOOL bModified = TRUE);
		BOOL SetTextMode(__in UINT fMode);
		UINT GetTextMode() const;
		void GetRect(__out LPRECT lpRect) const;
		CIUIPoint GetCharPos(__in long lChar) const;
		UINT GetOptions() const;
		void SetOptions(__in WORD wOp, __in DWORD dwFlags);
		BOOL SetAutoURLDetect(__in BOOL bEnable = TRUE);
		UINT GetWordWrapMode() const;
		UINT SetWordWrapMode(__in UINT uFlags) const;
		BOOL GetPunctuation(__in UINT fType, __out PUNCTUATION *lpPunc) const;
		BOOL SetPunctuation(__in UINT fType, __in PUNCTUATION *lpPunc);

		// NOTE: first word in lpszBuffer must contain the size of the buffer!
		// NOTE: Copied line does not contain null character!
		int GetLine(__in int nIndex, LPTSTR lpszBuffer) const;
		// NOTE: Copied line does not contain null character!
		int GetLine(__in int nIndex, LPTSTR lpszBuffer, __in int nMaxLength) const;

		BOOL CanPaste(__in UINT nFormat = 0) const;
		void GetSel(__out long &nStartChar, __out long &nEndChar) const;
		void GetSel(__out CHARRANGE &cr) const;
		void LimitText(__in long nChars = 0);
		long LineFromChar(__in long nIndex) const;
		CIUIPoint PosFromChar(__in UINT nChar) const;
		int CharFromPos(__in CIUIPoint pt) const;

		void SetSel(__in long nStartChar, __in long nEndChar);
		void SetSel(__in CHARRANGE &cr);
		DWORD GetDefaultCharFormat(__out CHARFORMAT &cf) const;
		DWORD GetDefaultCharFormat(__out CHARFORMAT2 &cf) const;
		DWORD GetSelectionCharFormat(__out CHARFORMAT &cf) const;
		DWORD GetSelectionCharFormat(__out CHARFORMAT2 &cf) const;
		long GetEventMask() const;
		long GetLimitText() const;
		DWORD GetParaFormat(__out PARAFORMAT &pf) const;
		DWORD GetParaFormat(__out PARAFORMAT2 &pf) const;
		// #if(_MSC_VER > 1310) // VC2003
		// 		// richedit EM_GETSELTEXT is ANSI
		// 		_AFX_INSECURE_DEPRECATE("GetSelText(char *) is unsafe. Instead, use GetSelText(void) returning CIUIString")
		// #endif
		// 		long GetSelText(__out LPSTR lpBuf) const;
		int GetTextRange(__in int nFirst, __in int nLast, __out CIUIString &refString) const;
		CIUIString GetSelText() const;
		WORD GetSelectionType() const;
		COLORREF SetBackgroundColor(__in BOOL bSysColor, __in COLORREF cr);
		BOOL SetDefaultCharFormat(__in CHARFORMAT &cf);
		BOOL SetDefaultCharFormat(__in CHARFORMAT2 &cf);
		BOOL SetSelectionCharFormat(__in CHARFORMAT &cf);
		BOOL SetSelectionCharFormat(__in CHARFORMAT2 &cf);
		BOOL SetWordCharFormat(__in CHARFORMAT &cf);
		BOOL SetWordCharFormat(__in CHARFORMAT2 &cf);
		DWORD SetEventMask(__in DWORD dwEventMask);
		BOOL SetParaFormat(__in PARAFORMAT &pf);
		BOOL SetParaFormat(__in PARAFORMAT2 &pf);
		BOOL SetTargetDevice(__in HDC hDC, __in long lLineWidth);
		//BOOL SetTargetDevice(__in CDC &dc, __in long lLineWidth);
		long GetTextLength() const;
		long GetTextLengthEx(__in DWORD dwFlags, __in UINT uCodePage = -1) const;
		BOOL SetReadOnly(__in BOOL bReadOnly = TRUE);
		int GetFirstVisibleLine() const;

		// Operations
		void EmptyUndoBuffer();
		void StopGroupTyping();
		UINT SetUndoLimit(__in UINT nLimit);

		// Gets the character index of the first character of a specified line in a multiline edit control
		int LineIndex(__in int nLine = -1) const;

		// ncp: ��һ��������һ���ַ�������
		int LineLength(__in int ncp = -1) const;
		void LineScroll(__in int nLines, __in int nChars = 0);
		void ReplaceSel(LPCTSTR lpszNewText, __in BOOL bCanUndo = FALSE);
		void SetRect(__in LPCRECT lpRect);

		BOOL DisplayBand(__in LPRECT pDisplayRect);
		long FindText(__in DWORD dwFlags, __out FINDTEXTEX *pFindText) const;
		DWORD FindWordBreak(__in UINT nCode, __in DWORD nStart) const;
		long FormatRange(__in FORMATRANGE *pfr, __in BOOL bDisplay = TRUE);
		void HideSelection(__in BOOL bHide, __in BOOL bPerm);
		void PasteSpecial(__in UINT nClipFormat, __in DWORD dvAspect = 0, __in HMETAFILE hMF = 0);
		void RequestResize();
		long StreamIn(__in int nFormat, EDITSTREAM &es);
		long StreamOut(__in int nFormat, EDITSTREAM &es);

		// Clipboard operations
		BOOL Undo();
		BOOL Redo();
		void Clear();
		void Copy();
		void Cut();
		void Paste();

		// OLE support
		IRichEditOle *GetIRichEditOle() const;
		BOOL SetOLECallback(IRichEditOleCallback *pCallback);
		//<< End Copy from CRichEditCtrl

	public:
		ITextHost *GetTextHost();
		ITextServices *GetTextServices();
		ITextDocument *GetITextDocument();
		HDC GetDC();

		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameS,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameS,
			CIUIString *pstrImageNameD) const;

		// cp: see REOBJECT::cp����ʾ�ַ�λ��
		int InsertGif(LPCTSTR lpszGifPath, LONG cp);
		int InsertOle(IOleObject *pOleObject, LONG cp, int nWidth, int nHeight);
		int InsertText(LPCTSTR lpszText, int iPos, COLORREF cr);

		int GetLineRect(int nLineIndex,
			__out POINT *pptStart, __out int *pnLineWidth, __out int *pnLineHeight);

		int GetFirstVisibleOleOjbect(__out REOBJECT *pObj);
		IOleObject *HitTestOleObject(LPPOINT lpPt);

		int RevokeDragDrop();

		// ��������Ϣ�����˰󶨵�OLE�����ϵĿؼ����Ƿ�
		// ��������Ĭ�ϴ��ڹ��̴���
		BOOL SetDefaultProcHandleIfHitOleCtrl(BOOL bDefaultHandle);
		BOOL IsDefaultProcHandleIfHitOleCtrl() const;
	};

	// ��һ����Ϣ��ͼ�Ļ��ʱ����Ҫ��ֳɶ�Σ���CRichMsgItem��¼ÿһ��
	class CRichMsgItem
	{
	public:
		CRichMsgItem();
		~CRichMsgItem();

	public:
		// �Ƿ�ΪOLE�ؼ�
		BOOL m_bOleControl;
		// ��ͨ�ı�
		CIUIString m_strMsgContent;
		// ��m_bOleControlΪTRUEʱ����ʾOLE�ؼ��󶨵�Windowless�ؼ���
		HWLWND m_hOleBindWindowless;
		// ��m_bOleControlΪTRUEʱ��m_size��ʾOLE�ؼ��ĳߴ�.
		CIUISize m_size;
		// �ı���ɫ
		COLORREF m_crText;
		// ��m_bOleControlΪTRUEʱ�� m_lParam��ʾ�û��Զ������ݣ�
		// IM�ؼ������������ش����û�
		LPARAM m_lParam;
	};

	class CTimeStampParam
	{
	public:
		CTimeStampParam();
		~CTimeStampParam();

	public:
		int m_nIndex;
		UINT m_uMsgID;
		time_t m_time;
	};

	class CLabelMsg
	{
	public:
		CLabelMsg();
		~CLabelMsg();

	public:
		int m_nIndex;
		UINT m_uMsgID;
		LPCTSTR m_lpszText;
		CIUISize m_size;
		const CLabelProp *m_pBindStyle;
	};

	// ������ʾ��IM�ؼ��е���Ϣ���ͣ�������ʾ��IM�ؼ��е�����ȫ������Ϣ��
	enum IMMSGTYPE
	{
		MSGTYPE_MSG = 0,
		MSGTYPE_SHOW_MORE_MSG_BUTTON,
		MSGTYPE_LABEL
	};

	// CIMMsg: �����¼�����е�һ����Ϣ
	// ʱ�䡢����ʾ������Ϣ����ť������Ϣ��
	class CIMMsg
	{
		friend class IMRichTextBox;

	public:
		CIMMsg();
		CIMMsg(const CIMMsg &rSrc);
		~CIMMsg();
		CIMMsg &operator=(const CIMMsg &rSrc);

	public:
		int GetVer() const;

		int SetMsgID(LPARAM nID);
		LPARAM GetMsgID() const;

		int SetMsgType(IMMSGTYPE eType);
		IMMSGTYPE GetMsgType() const;

		int SetMsgSenderID(LPCTSTR lpszOwner);
		LPCTSTR GetMsgSenderID() const;

		int SetSelf(BOOL bSelf);
		BOOL IsSelf() const;

		int SetHorzLayoutMode(CONTROL_LAYOUT_HOR eAlignHor);
		CONTROL_LAYOUT_HOR GetHorzLayoutMode() const;

		int ShowResendButton(BOOL bShow);
		BOOL IsShowResendButton() const;

		int SetResendButton(HWLWND hResendButton);
		HWLWND GetResendButton();

		int SetFace(HIUIIMAGE hImage);
		HIUIIMAGE GetFace() const;

		int SetMsgSenderTitle(int nTitle);
		int GetMsgSenderTitle() const;

		int SetMsgSender(LPCTSTR lpszSender);
		CIUIString GetMsgSender() const;

		int SetMsgStart(int nStart);
		int GetMsgStart() const;

		int SetMsgContentStart(int nStart);
		int GetMsgContentStart() const;

		int SetMsgEnd(int nEnd);
		int GetMsgEnd() const;

		int SetMsgFirstParagraphEnd(int nEnd);
		int GetMsgFirstParagraphEnd() const;

		int SetMsgParagraphCount(int nCount);
		int GetMsgParagraphCount() const;

		LPARAM SetUserData(LPARAM lParam);
		LPARAM GetUserData() const;

		int AddMsgItem(const CRichMsgItem *pMsgItem);
		std::list<CRichMsgItem> *GetMsgItems();
		const std::list<CRichMsgItem> *GetMsgItems() const;

	private:
		void Copy(const CIMMsg &rSrc);

		// ��Ϣ��������
	private:
		int m_nVer; // CIMMsg�汾��
		LPARAM m_nMsgID; // ��ϢID��Ψһ��ʶ��Ϣ��������IDΪ�ַ�������Ѷ��ϵ��ַ���ָ�븳ֵ������
		IMMSGTYPE m_eMsgType;
		CIUIString m_strSenderID; // ��Ϣ������ΨһID, ������ʶ��Ϣ����˭���͵ġ�
		time_t m_tMsg; // ��Ϣʱ���
		BOOL m_bSelf; // �Ƿ����Լ�������Ϣ
		CONTROL_LAYOUT_HOR m_eMsgAlignHor; // ��Ϣ�ڿؼ��е�ˮƽλ��
		BOOL m_bShowResendButton;
		HWLWND m_hResendButton;
		HIUIIMAGE m_himgFace; // ͷ��
		int m_nMsgSenderTitle; // ��Ϣ������ͷ�μ���
		CIUIString m_strMsgSender; // ��Ϣ����������
		CIUIString m_strRichMsg; // ԭʼ��Ϣ��
		LPARAM m_lParam; // �û��Զ�������

		// ��ʾʱ��Ҫ��Ϣ
	private:
		HWLWND m_hImCtrl;

		// cp=char position. ������Ϣ���Ӽ���+���ֿ�ʼ�����뵽RichEdit�����ʼλ�á�
		// ������˲鿴���࣬�����Ǵ�RichEditǰ������µ���Ϣ��
		// ����Ҫ���¸���m_nMsgStartCp
		int m_nMsgStartCp;

		// ��Ϣ���ݵ�һ���ַ���ʼλ�ã��������Ϣ��ʼcp
		int m_nMsgContentStartCp;

		// ������Ϣ���뵽RichEdit�����һ���ַ��ĵ�λ�á��������Ϣ��ʼcp
		int m_nMsgEndCp;

		// ��¼��Ϣ����һ�����ٸ����䡣 �����������а���һ��\n��
		// �ͱ�ʾ��һ�����䡣 ����ʾʱ�������ʾ�����������뱾ֵ��һ����
		// ��ʾRichedit�����ݽ����˻��С�
		int m_nMsgParagraphCount;

		// ��Ϣ���ݣ���Ϣ���ܰ������ı���ͼƬ��OLE�����
		// ͼƬ��OLE��ʹ��Ԥ�����Э���ַ���
		// �ر�ע�⣺��Ϣ�ַ���Ӧʹ��"\r"���ֶΣ�������"\r\n"��"\n".
		std::list<CRichMsgItem> m_lstpStrRichMsg;
	};

	class IMRichTextBox: public RichTextBox
	{
	public:
		IMRichTextBox();
		virtual ~IMRichTextBox();

		virtual int ReleaseObject();

	public:
		virtual int BindStyle(const CIMRichTextBoxProp *pCtrlProp);

		// ���ز�������Ϣ����
		int InsertMsg(int nIndex, const CIMMsg *pMsg);

		int DeleteMsg(int nIndex);

		// Ϊָ����Ϣ���ӡ����·��͡���ť�����Լ�����Ϣ֧�֡�
		int ShowResendButton(UINT uMsgID, BOOL bShow);
		BOOL IsMsgShowResendButton(UINT uMsgID) const;

		// IMM_INSERT_MSG�����������롰��ʾ������Ϣ����ť
		int InsertShowMoreMessage(UINT uMsgID, LPCTSTR lpszText);
		// IMM_INSERT_MSG����������ָ��λ�ò����ı�
		int InsertLabel(
			UINT nIndex,
			UINT uMsgID,
			LPCTSTR lpszText,
			SIZE sizeLabel,
			const CLabelProp *pBindStyle
		);

		int SetSenderIndent(int nLeftIndent);
		int GetSenderIndent() const;

		int SetMsgLeftIndent(int nLeftIndent);
		int GetMsgLeftIndent() const;
		int SetMsgRightIndent(int nRightIndent);
		int GetMsgRightIndent() const;

		int SetMaxRelayoutWidth(int nWidth);
		int GetMaxRelayoutWidth() const;

		int SetMsgSenderTitleAlias(int nLevel, LPCTSTR lpszAlias);

		int ShowMsgSenderTitle(BOOL bShow);
		BOOL IsShowMsgSenderTitle() const;

		int ShowMsgSenderAlias(BOOL bShow);
		BOOL IsShowMsgSenderAlias() const;

		// ���÷����߱����м��
		int SetTitleSpaceBefore(int nY);
		int GetTitleSpaceBefor() const;
		int SetTitleSpaceAfter(int nY);
		int GetTitleSpaceAfter() const;
		// ���÷����߱�����������������Ѿ������˵�ֵ��
		int SetTitleIndents(int nLeft);
		int GetTitleIndents() const;
		// ���÷����߱�����ɫ
		int SetTitleColor(COLORREF cr);
		COLORREF GetTitleColor() const;

		int SetFaceSize(SIZE sizeFace);
		SIZE GetFaceSize() const;

		int ShowLeftFace(BOOL bShow);
		BOOL IsShowLeftFace() const;

		int ShowRightFace(BOOL bShow);
		BOOL IsShowRightFace() const;

		// �Ƿ�ϲ�ͬһʱ�����ͬһ�������ߵ���Ϣ�����ؾɵ�״̬
		BOOL SetCombineMsg(BOOL bCombine);
		BOOL IsCombineMsg() const;

		// ��ʹ�úϲ���Ϣģʽʱ�����ö��֮�ڵ���Ϣ��Ҫ�ϲ�����λ����
		int SetCombineMsgTimeSpan(int nSecond);
		int GetCombineMsgTimeSpan() const;

		int SetSenderTopQiPao(LPCTSTR lpszQiPaoFile, LPCRECT lprc9GridArg);
		int GetSenderTopQiPao(__out CIUIString *pstrQiPaoFile, __out LPRECT lprc9GridArg);
		int SetSenderMidQiPao(LPCTSTR lpszQiPaoFile, LPCRECT lprc9GridArg);
		int GetSenderMidQiPao(__out CIUIString *pstrQiPaoFile, __out LPRECT lprc9GridArg);
		int SetSenderBottomQiPao(LPCTSTR lpszQiPaoFile, LPCRECT lprc9GridArg);
		int GetSenderBottomQiPao(__out CIUIString *pstrQiPaoFile, __out LPRECT lprc9GridArg);

		int SetSelfTopQiPao(LPCTSTR lpszQiPaoFile, LPCRECT lprc9GridArg);
		int GetSelfTopQiPao(__out CIUIString *pstrQiPaoFile, __out LPRECT lprc9GridArg);
		int SetSelfMidQiPao(LPCTSTR lpszQiPaoFile, LPCRECT lprc9GridArg);
		int GetSelfMidQiPao(__out CIUIString *pstrQiPaoFile, __out LPRECT lprc9GridArg);
		int SetSelfBottomQiPao(LPCTSTR lpszQiPaoFile, LPCRECT lprc9GridArg);
		int GetSelfBottomQiPao(__out CIUIString *pstrQiPaoFile, __out LPRECT lprc9GridArg);

		int SetResendButtonMarign(int nHor, int nVer);
		int GetResendButtonMargin(LPPOINT lpptMargin);

		int SetResendButtonSize(int nWidth, int nHeight);
		int GetResendButtonSize(LPSIZE lpsizeResendButton);

		// ����Resend Button��ۣ��ڲ����ᱣ��pButtonProp�ı��ݣ�����Ҫע��������������
		int SetResendButtonStyle(const CButtonProp *pButtonProp);
		const CButtonProp *GetResendButtonStyle() const;

		// ����Shore More Msg Button��ۣ��ڲ����ᱣ��pButtonProp�ı��ݣ�����Ҫע��������������
		int SetShowMoreMsgButtonStyle(const CButtonProp *pButtonProp);
		const CButtonProp *GetShowMoreMsgButtonStyle() const;

		int GetFirstVisibleMsg() const;
		// ��������
		int FindMsg(int nMsgID, __out CIMMsg *pMsg);
		int GetMsg(int nMsgIndex, __out CIMMsg *pMsg);
		int GetMsgPosInGroup(int nMsgIndex);

		int EnsureMsgVisible(UINT uMsgID);

#ifdef _DEBUG
		int Test();
#endif // _DEBUG
	};

	class IUIAPI ColumnHeader : public CWLWnd
	{
		friend LRESULT Header_WndProc(ColumnHeader *, UINT, WPARAM, LPARAM);

		// Constructors
	public:
		ColumnHeader();
		virtual ~ColumnHeader();

		// Generic creator
		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParentWnd,
			CWLWnd *pParent,
			LPCTSTR lpszName
		);

		// Generic creator allowing extended style bits
		virtual BOOL CreateEx(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwExStyle,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParentWnd,
			CWLWnd *pParent,
			LPCTSTR lpszName
		);

		virtual int BindStyle(const CControlProp *pProp);

		// Attributes
		// Retrieves a count of the items in the header control.
		int GetItemCount() const;

		// Retrieves information about an item in the header control.
		BOOL GetItem(__in int nPos, __out HDITEM *pHeaderItem) const;

		// Sets the attributes of the specified item in the header control.
		BOOL SetItem(__in int nPos, __in HDITEM *pHeaderItem);

		// Retrieves the bounding rectangle for the specified item in the header control.
		BOOL GetItemRect(__in int nIndex, __out LPRECT lpRect) const;

		// Retrieves the current left-to-right order of items in the header control.
		BOOL GetOrderArray(__in LPINT piArray, __in int iCount) const;

		// Sets the left-to-right order of items in the header control.
		BOOL SetOrderArray(__in int iCount, __in LPINT piArray);

		// Retrieves an index value for an item based on its order in the header control.
		int OrderToIndex(__in int nOrder) const;

		// Determines which header item, if any, is at the specified point.
		int HitTest(__inout LPHDHITTESTINFO pHeaderHitTestInfo);

#if _WIN32_IE >= 0x0500
		// Retrieves the width of the bitmap margin for the header control.
		int GetBitmapMargin() const;

		// Sets the width of the bitmap margin for the header control.
		int SetBitmapMargin(__in int nWidth);
#endif

#if (_WIN32_WINNT >= 0x600) && defined(UNICODE)
		// REVIEW:
		BOOL GetItemDropDownRect(__in int iItem, __out LPRECT lpRect) const;

		// REVIEW:
		BOOL GetOverflowRect(__out LPRECT lpRect) const;

		// REVIEW: Gets the item in the header control that has the focus.
		int GetFocusedItem() const;

		// Sets the focus to the specified item in the header control.
		BOOL SetFocusedItem(__in int iItem);
#endif // _WIN32_WINNT >= 0x600 && defined(UNICODE)

		// Operations
		// Inserts a new item into the header control.
		int InsertItem(__in int nPos, __in HDITEM *phdi);

		// Deletes an item from a header control.
		BOOL DeleteItem(__in int nPos);

		// Retrieves the correct size and position of the header control within the parent window.
		BOOL Layout(__in HDLAYOUT *pHeaderLayout);

		// Creates a semi-transparent version of an item's image for use as a dragging image.
		HIMAGELIST CreateDragImage(__in int nIndex);

		// Changes the color of a divider between header items to indicate
		// the destination of an external drag-and-drop operation.
		int SetHotDivider(__in CIUIPoint pt);
		int SetHotDivider(__in int nIndex);

#if _WIN32_IE >= 0x0500
		// Sets the timeout interval between the time a change takes place in the
		// filter attributes and the posting of an HDN_FILTERCHANGE notification.
		int SetFilterChangeTimeout(__in DWORD dwTimeOut);

		// Starts editing the filter for the specified column.
		int EditFilter(__in int nColumn, __in BOOL bDiscardChanges);

		// Clears the filter for the specified column in the header control.
		BOOL ClearFilter(__in int nColumn);

		// Clears all filters for all columns in the header control.
		BOOL ClearAllFilters();
#endif

		// IUI Add

		// Header�ؼ�����
		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameBkN,
			LPCTSTR lpszImageNameBkD
		);
		int GetBkImage(
			UINT uMask,
			CIUIString *pstrImageNameBkN,
			CIUIString *pstrImageNameBkD
		) const;
		int SetBkImageResizeMode(IMAGE_RESIZE_MODE eImageResizeMode);
		IMAGE_RESIZE_MODE GetBkImageResizeMode();
		int SetBkImage9GridArg(LPCRECT lpRect);
		int GetBkImage9GridArg(LPRECT lpRect);

		// Header Item����
		int CombineButtonBkImage(BOOL bCombine);
		int IsCombineButtonBkImage() const;
		int SetButtonCombineImage(LPCTSTR lpszImageNameBk);
		int SetButtonImage(
			UINT uMask,
			LPCTSTR lpszImageNameBkN,
			LPCTSTR lpszImageNameBkH,
			LPCTSTR lpszImageNameBkS,
			LPCTSTR lpszImageNameBkD
		);
		int GetButtonImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameBkN,
			CIUIString *pstrImageNameBkH,
			CIUIString *pstrImageNameBkS,
			CIUIString *pstrImageNameBkD
		) const;

		int SetButtonBkImageResizeArg(IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
		int GetButtonBkImageResizeArg(IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid) const;

		int SetTextColor(COLORREF crN, COLORREF crH, COLORREF crS, COLORREF crD);
		int GetTextColor(COLORREF *pcrN, COLORREF *pcrH, COLORREF *pcrS, COLORREF *pcrD) const;

		int SetTextFont(
			UINT uMask,
			LPCTSTR lpszFontIDN,
			LPCTSTR lpszFontIDH,
			LPCTSTR lpszFontIDS,
			LPCTSTR lpszFontIDD
		);
		int GetTextFont(
			UINT uMask,
			CIUIString *pstrFontIDN,
			CIUIString *pstrFontIDH,
			CIUIString *pstrFontIDS,
			CIUIString *pstrFontIDD
		) const;

		int SetHeaderHeight(int nHeight);
		int GetHeaderHeight() const;

		int EnableHeaderTrack(BOOL bEnable);
		BOOL IsHeaderTrackEnable() const;

		int EnableHeaderDragDrop(BOOL bEnable);
		BOOL IsHeaderDragDropEnable() const;

		int HitTest(CIUIPoint pt);
	};

	// ��������������ʾģʽ
	// LVS_ICON��     Item���з�ʽ��LVS_SMALLICONһ�������Ǵ��������У�һ��ֻ��ʾ��ֱ��������
	//                ��LVS_SMALLICON�������ǣ�LVS_ICON��Item�ڣ�ͼ����ı����������У�ͼ��
	//                ���ϣ��ı����¡� LVS_ICON����������������ͼ�ؼ�
	//
	// LVS_REPORT��   ������
	//
	// LVS_SMALLICON��Item���з�ʽ��LVS_ICONһ�������Ǵ��������У�һ��ֻ��ʾ��ֱ��������
	//                ��LVS_ICON�������ǣ�LVS_SMALLICON��Item�ڣ�ͼ����ı���ˮƽ���У�
	//                ͼ�������ı����ҡ� ������ȥ��LVS_LIST������ƣ�
	//                ֻ����LVS_LIST���Ĭ���Ǵ��ϵ�������Item��
	//
	// LVS_LIST��     Item���з�ʽ�Ǵ��ϵ��¡� ��һ����ʾ���£��Զ���ʾ������һ�С� ֻ��ˮƽ
	//                �������� ���������LVS_SMALLICON��Щ���ƣ�ֻ��Item���з���ͬ
	//                (LVS_LISTҲ���Լ�ͼ��)�� �������������и�COLUMN_VIEW�꣬���δ��������꣬
	//                ��ô�������з�ʽ����ʾ��ʽ��LVS_SMALLICON����ȫһ���ˣ�����������Item��
	//                ֻ�д�ֱ���������� ����LVS_SMALLICONģʽ�����Դ���COLUMN_VIEWδ����ʱ��
	//                LVS_LISTģʽ�����ԣ�������Ҫ����COLUMN_VIEW�꣬���ң�Ҳû��Ҫ��
	//                COLUMN_VIEW����һ��ѡ�����û�����

	// LVITEMEX����Set��Get Item��ListView�ڲ��������Ǳ���LVITEMEX����
	typedef struct tagLVITEMEXA
	{
		tagLVITEMEXA()
			: mask(0)
			, iItem(0)
			, iSubItem(0)
			, state(0)
			, stateMask(0)
			, pszText(NULL)
			, cchTextMax(0)
			, iImage(0)
			, lParam(0)
			, iIndent(0)
			, hBindWindowless(NULL)
		{}
		UINT mask;
		int iItem;
		int iSubItem;
		UINT state;
		UINT stateMask;
		LPSTR pszText;
		int cchTextMax;
		int iImage;
		LPARAM lParam;
		int iIndent;
		HWLWND hBindWindowless; // �󶨵Ŀؼ�
	} LVITEMEXA, *LPLVITEMEXA;

	typedef struct tagLVITEMEXW
	{
		tagLVITEMEXW()
			: mask(0)
			, iItem(0)
			, iSubItem(0)
			, state(0)
			, stateMask(0)
			, pszText(NULL)
			, cchTextMax(0)
			, iImage(0)
			, lParam(0)
			, iIndent(0)
			, hBindWindowless(NULL)
		{}
		UINT mask;
		int iItem;
		int iSubItem;
		UINT state;
		UINT stateMask;
		LPWSTR pszText;
		int cchTextMax;
		int iImage;
		LPARAM lParam;
		int iIndent;
		HWLWND hBindWindowless; // �󶨵Ŀؼ�
	} LVITEMEXW, *LPLVITEMEXW;

#ifdef UNICODE
#define LVITEMEX    LVITEMEXW
#define LPLVITEMEX  LPLVITEMEXW
#else
#define LVITEMEX    LVITEMEXA
#define LPLVITEEXM  LPLVITEMEXA
#endif

	typedef struct tagLVDISPINFOEX
	{
		NMHDR hdr;
		LVITEMEXA item;
	} NMLVDISPINFOEXA, *LPNMLVDISPINFOEXA;

	typedef struct tagLVDISPINFOEXW
	{
		NMHDR hdr;
		LVITEMEXW item;
	} NMLVDISPINFOEXW, *LPNMLVDISPINFOEXW;

#ifdef UNICODE
#define  NMLVDISPINFOEX           NMLVDISPINFOEXW
#else
#define  NMLVDISPINFOEX           NMLVDISPINFOEXA
#endif


	class IUIAPI ListView : public CWLWnd
	{
	public:
		ListView();
		virtual ~ListView();

		virtual int BindStyle(const CControlProp *pCtrlProp);

	public:
		// Generic creator
		BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hParent,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName);

		// Generic creator allowing extended style bits
		BOOL CreateEx(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwExStyle,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hParent,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName);

		// Attributes
		// Retrieves the background color for the control.
		COLORREF GetBkColor() const;

		// Sets background color for the control.
		BOOL SetBkColor(__in COLORREF cr);

		// Retrieves the image list associated with the control.
		HIMAGELIST GetImageList(__in int nImageList) const;

		// Sets the image list associated with this control.
		HIMAGELIST SetImageList(__in HIMAGELIST ImageList, __in int nImageList);

		// Retrieves the tool tip control associated with this control.
		HWND GetToolTips() const;

		// Sets the tool tip control to be used by this control.
		HWND SetToolTips(__in HWND pWndTip);

		// Retrieves the number of items in the control.
		int GetItemCount() const;

		// Retrieves a description of a particular item in the control.
		BOOL GetItem(__out LVITEMEX *pItem) const;

		// Sets information to an existing item in the control.
		BOOL SetItem(__in const LVITEMEX *pItem);
		BOOL SetItem(
			__in int nItem,
			__in int nSubItem,
			__in UINT nMask,
			__in LPCTSTR lpszItem,
			__in int nImage,
			__in UINT nState,
			__in UINT nStateMask,
			__in LPARAM lParam,
			__in int nIndent,
			__in HWLWND hBindWL
		);

		// Determines which item attributes are maintained by the application
		// instead of the control itself.
		UINT GetCallbackMask() const;

		// Specifies which item attributes are maintained by the application
		// instead of the control itself.
		BOOL SetCallbackMask(__in UINT nMask);

		// Get the next item after nItem matching flags in nFlags.
		int GetNextItem(__in int nItem, __in int nFlags) const;

		// Gets first item selected in the control and prepares for
		// finding other selected items (if the control has the multiple
		// selection style).
		IUIPOS GetFirstSelectedItemPosition() const;

		// Finds the next selected item, after a previous call
		// to GetFirstSelectedItemPosition().
		int GetNextSelectedItem(__inout IUIPOS &pos) const;

		// Retrieves the bounding rectangle for a particular item.
		BOOL GetItemRect(__in int nItem, __out LPRECT lpRect, __in UINT nCode) const;

		// Find the location of a particular item in the control,
		// relative to the control's client area.
		BOOL SetItemPosition(__in int nItem, __in POINT pt);
		BOOL GetItemPosition(__in int nItem, __out LPPOINT lpPoint) const;

		// Determines the width of a string as displayed in report mode.
		int GetStringWidth(__in LPCTSTR lpsz) const;

		// Retrieves the edit control associated with the currently edited
		// item in the control.
		HWND GetEditControl() const;

		// Retrieves information about a column in a report-mode control.
		BOOL GetColumn(__in int nCol, __out LVCOLUMN *pColumn) const;

		// Sets information about a column in a report-mode control.
		BOOL SetColumn(__in int nCol, __in const LVCOLUMN *pColumn);

		// Retrieves the width of a column in a report-mode control.
		int GetColumnWidth(__in int nCol) const;

		// Sets the width of a column in a report-mode control.
		BOOL SetColumnWidth(__in int nCol, __in int cx);

		BOOL GetViewRect(__out LPRECT lpRect) const;

		// Retrieves the index of the topmost visible item in the control.
		int GetTopIndex() const;

		// Retrieves the number of items displayed at one time
		// the control's client area.
		int GetCountPerPage() const;

		// Retrieves the current origin of the client area.
		BOOL GetOrigin(__out LPPOINT lpPoint) const;

		// Sets the state of a particular item.
		BOOL SetItemState(__in int nItem, __in LVITEMEX *pItem);
		BOOL SetItemState(__in int nItem, __in UINT nState, __in UINT nMask);

		// Retrieves the state of a particular item.
		UINT GetItemState(__in int nItem, __in UINT nMask) const;

		// Retrieves the text associated with a particular item.
		CIUIString GetItemText(__in int nItem, __in int nSubItem) const;
		int GetItemText(__in int nItem, __in int nSubItem, __in LPTSTR lpszText, __in int nLen) const;

		// Sets the text associated with a particular item.
		BOOL SetItemText(__in int nItem, __in int nSubItem, __in LPCTSTR lpszText);

		// Sets the count of items in the control. The control will use
		// this value to preallocate memory for its own storage; you may
		// exceed the item count at any time, but accurate preallocation
		// can help performance.
		void SetItemCount(__in int nItems);

		// Sets the data (lParam) associated with a particular item.
		BOOL SetItemData(__in int nItem, __in DWORD_PTR dwData);

		// Retrieves the data (lParam) associated with a particular item.
		DWORD_PTR GetItemData(__in int nItem) const;

		// Retrieves the number of selected items in the control.
		UINT GetSelectedCount() const;

		// Retrieves the spacing between items in the control.
		BOOL GetItemSpacing(__in BOOL fSmall, __out int *pnHorzSpacing, __out int *pnVertSpacing) const;

		BOOL SetColumnOrderArray(__in int iCount, __in LPINT piArray);
		BOOL GetColumnOrderArray(__out LPINT piArray, __in int iCount = -1) const;

		// Sets minimum spacing of items in the icon view.
		CIUISize SetIconSpacing(__in CIUISize size);
		CIUISize SetIconSpacing(__in int cx, __in int cy);

		// Retrieves a reference to the header control in
		// a report-mode control.
		ColumnHeader *GetHeaderCtrl() const;

		// Retrieves the cursor used over hot items. (Only valid for
		// controls with the LVS_EX_TRACKSELECT style.)
		HCURSOR GetHotCursor() const;

		// Sets cursor to be used over hot items. (Only used in controls
		// with the LVS_EX_TRACKSELECT style.)
		HCURSOR SetHotCursor(__in HCURSOR hc);

		BOOL GetSubItemRect(__in int iItem, __in int iSubItem, __in int nArea, __out CIUIRect &ref) const;

		// Retrieves the item currently hot-selected, or -1 if none.
		int GetHotItem() const;

		// Sets the item to be currently hot-selected.
		int SetHotItem(__in int iIndex);

		// Retrieves the item with the selection mark, or -1 if none.
		int GetSelectionMark() const;

		// Sets the item with the selection mark.
		int SetSelectionMark(__in int iIndex);

		// Retrieves the control-specific extended style bits.
		DWORD GetExtendedStyle() const;

		// Sets the control-specific extended style bits.
		DWORD SetExtendedStyle(__in DWORD dwNewStyle);

		// Determines the visual feature of a subitem control under
		// the specified point.
		int SubItemHitTest(__in LPLVHITTESTINFO pInfo);

		// Sets up virtual work areas within the control.
		void SetWorkAreas(__in int nWorkAreas, __in LPRECT lpRect);

		// Updates expected item count for a virtual control.
		BOOL SetItemCountEx(__in int iCount, __in DWORD dwFlags = LVSICF_NOINVALIDATEALL);

		// Calculates the approximate minimum size required to
		// display the passed number of items.
		CIUISize ApproximateViewRect(__in CIUISize sz = CIUISize(-1, -1),
			int iCount = -1) const;

		// Retrieves information about the background image in the control.
		BOOL GetBkImage(__out LVBKIMAGE *plvbkImage) const;

		// Retrieves the delay (in milliseconds) for the mouse to hover
		// over an item before it is selected.
		DWORD GetHoverTime() const;

		// Retrieves the rectangles defining the workareas in the control.
		void GetWorkAreas(__in int nWorkAreas, __out LPRECT prc) const;

		// Sets the image used in the background of the control.
		BOOL SetBkImage(__in HBITMAP hbm, __in BOOL fTile = TRUE,
			__in int xOffsetPercent = 0, __in int yOffsetPercent = 0);
		BOOL SetBkImage(__in LPTSTR pszUrl, __in BOOL fTile = TRUE,
			__in int xOffsetPercent = 0, __in int yOffsetPercent = 0);
		BOOL SetBkImage(__in LVBKIMAGE *plvbkImage);

		// Sets the delay (in milliseconds) for the mouse to hover
		// over an item before it is selected.
		DWORD SetHoverTime(__in DWORD dwHoverTime = (DWORD)(-1));

		// Returns the number of work areas in the control.
		UINT GetNumberOfWorkAreas() const;

		// Retrieves the checked state of a particular item. Only useful
		// on controls with the LVS_EX_CHECKBOXES style.
		BOOL GetCheck(__in int nItem) const;

		// Sets the checked state of a particular item. Only useful
		// on controls with the LVS_EX_CHECKBOXES style.
		BOOL SetCheck(__in int nItem, __in BOOL fCheck = TRUE);

		// Operations

		// Adds an item to the control.
		int InsertItem(__in const LVITEMEX *pItem);
		int InsertItem(__in int nItem, __in LPCTSTR lpszItem);
		int InsertItem(__in int nItem, __in LPCTSTR lpszItem, __in int nImage);

		// Removes a single item from the control.
		BOOL DeleteItem(__in int nItem);

		// Removes all items from the control.
		BOOL DeleteAllItems();

		// Finds an item in the control matching the specified criteria.
		int FindItem(__in LVFINDINFO *pFindInfo, __in int nStart = -1) const;

		// Determines the visual feature of the control under
		// the specified point.
		int HitTest(__in LVHITTESTINFO *pHitTestInfo) const;
		int HitTest(__in CIUIPoint pt, __in UINT *pFlags = NULL) const;

		// Causes the control to scroll its content so the specified item
		// is completely (or at least partially, depending on the
		// bPartialOK parameter) visible.
		BOOL EnsureVisible(__in int nItem, __in BOOL bPartialOK);

		// Forces the control to scroll its client area
		// by the specified amount.
		BOOL Scroll(__in CIUISize size);

		// Forces the control to repaint a specific range of items.
		BOOL RedrawItems(__in int nFirst, __in int nLast);

		// Causes the control to rearrange items within its client area.
		BOOL Arrange(__in UINT nCode);

		// Causes the control to enter edit mode on the speficied item.
		HWND EditLabel(__in int nItem);

		// Inserts a column into a report-mode control.
		int InsertColumn(__in int nCol, __in const LVCOLUMN *pColumn);
		int InsertColumn(__in int nCol, __in LPCTSTR lpszColumnHeading,
			__in int nFormat = LVCFMT_LEFT, __in int nWidth = -1, __in int nSubItem = -1);

		// Deletes a column from a report-mode control.
		BOOL DeleteColumn(__in int nCol);

		// Creates a drag-time image from a particular item in the control.
		HIMAGELIST CreateDragImage(__in int nItem, __in LPPOINT lpPoint);

		// Forces the control to repaint a specific item.
		BOOL Update(__in int nItem);

		// Call to sort items using a custom comparison function.
		BOOL SortItems(__in PFNLVCOMPARE pfnCompare, __in DWORD_PTR dwData);
		BOOL SortItemsEx(__in PFNLVCOMPARE pfnCompare, __in DWORD_PTR dwData);

		// Implementation
	public:
		int InsertItem(__in UINT nMask, __in int nItem, __in LPCTSTR lpszItem, __in UINT nState,
			__in UINT nStateMask, __in int nImage, __in LPARAM lParam);

		BOOL SetItemBindWindowless(__in int nItem, __in int nSubItem, __in HWLWND hBind);
		HWLWND GetItemBindWindowless(int nItem, int nSubItem) const;

		// for ListBox
	public:
		int FindString(LPCTSTR lpszText);
		int FindStringExact(LPCTSTR lpszText);
		int SetCurSel(int nSel);
		int GetCurSel() const;
		int SetCaretIndex(int nItem);
		int SetTopIndex(int nItem);
		CIUIString GetText(int nItem) const;
		int CaretOn();

		// IUI Add
	public:
		// Header
		int SetHeaderHeight(int nHeight);
		int GetHeaderHeight() const;

		int SetHeaderBkImage(LPCTSTR lpszImageNameHeaderBk);
		int GetHeaderBkImage(CIUIString *pstrImageNameHeaderBk) const;

		int SetHeaderButtonImage(
			UINT uMask,
			LPCTSTR lpszImageNameHeaderN,
			LPCTSTR lpszImageNameHeaderH,
			LPCTSTR lpszImageNameHeaderS,
			LPCTSTR lpszImageNameHeaderD
		);
		int GetHeaderButtonImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameHeaderN,
			CIUIString *pstrImageNameHeaderH,
			CIUIString *pstrImageNameHeaderS,
			CIUIString *pstrImageNameHeaderD
		) const;

		// �Ƿ�����ʹ��������Header Item���
		int EnableHeaderTrack(BOOL bEnable);
		BOOL IsHeaderTrackEnable() const;

		// Background
		int SetBkImage(UINT uMask, LPCTSTR lpszImageNameBkN, LPCTSTR lpszImageNameBkD);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameBkN,
			CIUIString *pstrImageNameBkD
		) const;

		// For grid line
		int ShowGridLine(BOOL bShow);
		BOOL IsGridLineVisible();

		int DrawFirstRow(BOOL bDraw0Row);
		BOOL IsDrawFirstRow() const;

		int SetGridLineOffset(const LPPOINT lpPtOffset);
		int GetGridLineOffset(LPPOINT lpPtOffset) const;

		int SetGridLineColor(COLORREF crGridLine);
		COLORREF GetGridLineColor() const;

		// For spec item
		int EnableItemBkEffect(int nItem, BOOL bEnable);
		BOOL IsItemBkEffectEnabled(int nItem) const;

		int SetItemBkType(int nItem, BACKGROUND_TYPE eBkType);
		int GetItemBkType(int nItem, BACKGROUND_TYPE *peBkType) const;

		int SetItemBkColor(
			int nItem,
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD
		);
		int GetItemBkColor(
			int nItem,
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD
		) const;

		int SetItemBkImage(
			int nItem,
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameS,
			LPCTSTR lpszImageNameD
		);
		int GetItemBkImage(
			int nItem,
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameS,
			CIUIString *pstrImageNameD
		) const;

		int SetItemBkImageResizeArg(int nItem, IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
		int GetItemBkImageResizeArg(int nItem, IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid) const;

		int SetItemTextColor(
			int nItem,
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD);
		int GetItemTextColor(
			int nItem,
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD) const;

		// For selected item
		// draw selected background fit to the width of client, not to the right of last header item.
		int EnableSelectedFitClient(BOOL bEnable);
		BOOL IsEnableSelectedFitClient() const;

		int SetSelectedItemBkType(
			UINT uMask,
			BACKGROUND_TYPE eBkTypeN,
			BACKGROUND_TYPE eBkTypeD
		);
		int GetSelectedItemBkType(
			UINT uMask,
			BACKGROUND_TYPE *peBkTypeN,
			BACKGROUND_TYPE *peBkTypeD
		) const;

		int SetSelectedItemBkColor(UINT uMask, COLORREF crN, COLORREF crD);
		int GetSelectedItemBkColor(UINT uMask, COLORREF *pcrN, COLORREF *pcrD) const;

		int SetSelectedItemBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameBkN,
			LPCTSTR lpszImageNameBkD
		);
		int GetSelectedItemBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameBkN,
			CIUIString *pstrImageNameBkD
		);

		int SetSelectedItemBkImageResizeArg(IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
		int GetSelectedItemBkImageResizeArg(IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid) const;

		int SetSelectedItemTextColor(UINT uMask, COLORREF crN, COLORREF crD);
		int GetSelectedItemTextColor(UINT uMask, COLORREF *pcrN, COLORREF *pcrD) const;

		// for focus(caret) item��
		// ����Item��Disabled״̬����Ϊ�ؼ�Disabled��ʱ�򣬲�����õ����㡣
		int SetFocusItemBkType(BACKGROUND_TYPE eBkType);
		BACKGROUND_TYPE GetFocusItemBkType() const;

		int SetFocusItemBkColor(COLORREF cr);
		COLORREF GetFocusItemBkColor() const;

		int SetFocusItemBkImage(LPCTSTR lpszImageNameBk);
		int GetFocusItemBkImage(CIUIString *pstrImageNameBk) const;
		int SetFocusItemBkImageResizeArg(IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
		int GetFocusItemBkImageResizeArg(IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid) const;

		int SetFocusItemTextColor(COLORREF cr);
		COLORREF GetFocusItemTextColor() const;

		// For highlight item
		int SetHighlightItemBkType(BACKGROUND_TYPE eBkType);
		BACKGROUND_TYPE GetHighlightItemBkType() const;

		int SetHighlightItemBkColor(COLORREF cr, BOOL bRedraw = TRUE);
		COLORREF GetHighlightItemBkColor() const;

		int SetHighlightItemBkImage(LPCTSTR lpszImageName);
		int GetHighlightItemBkImage(CIUIString *pstrImageName);

		int SetHighlightItemBkImageResizeArg(IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
		int GetHighlightItemBkImageResizeArg(IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid) const;

		int SetHighlightItemTextColor(COLORREF cr);
		COLORREF GetHighlightItemTextColor() const;

		int GetHighlightItem() const;

		// For text font
		int SetItemTextFont(
			LPCTSTR lpszFontIDN,
			LPCTSTR lpszFontIDH,
			LPCTSTR lpszFontIDS,
			LPCTSTR lpszFontIDND,
			LPCTSTR lpszFontIDSD
		);
		int GetItemTextFont(
			CIUIString *pstrFontIDN,
			CIUIString *pstrFontIDH,
			CIUIString *pstrFontIDS,
			CIUIString *pstrFontIDND,
			CIUIString *pstrFontIDSD
		) const;
	};

	typedef struct tagXTVITEMA
	{
		UINT      mask;
		HTREEITEM hItem;
		UINT      state;
		UINT      stateMask;
		LPSTR     pszText;
		int       cchTextMax;
		int       iImage;
		int       iSelectedImage;
		int       cChildren;
		LPARAM    lParam;
		int       iIntegral;
		HWLWND hBindWindowless;
	} XTVITEMA, *LPXTVITEMA;

	typedef struct tagXTVITEMW
	{
		UINT      mask;
		HTREEITEM hItem;
		UINT      state;
		UINT      stateMask;
		LPWSTR    pszText;
		int       cchTextMax;
		int       iImage;
		int       iSelectedImage;
		int       cChildren;
		LPARAM    lParam;
		int       iIntegral;
		HWLWND hBindWindowless;
	} XTVITEMW, *LPXTVITEMW;

#ifdef UNICODE
	typedef XTVITEMW XTVITEM;
	typedef XTVITEMW *LPXTVITEM;
	typedef const XTVITEMW *LPCXTVITEM;
#else
	typedef XTVITEMA XTVITEM;
	typedef XTVITEMA *LPXTVITEM;
	typedef const XTVITEMA *LPCXTVITEM;
#endif // UNICODE

	class IUIAPI TreeView : public CWLWnd
	{
	public:
		TreeView();
		virtual ~TreeView();

		virtual int BindStyle(const CControlProp *pCtrlProp);

	public:
		// Generic creator
		BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hParent,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName,
			__in BOOL bSmoothVScroll);

		// Generic creator allowing extended style bits
		BOOL CreateEx(
			__inout CWLWndHandler *pUserHandler,
			__in DWORD dwExStyle,
			__in DWORD dwStyle,
			__in const RECT &rect,
			__in HWND hParent,
			__in CWLWnd *pParent,
			__in LPCTSTR lpszName,
			__in BOOL bSmoothVScroll);

		// Attributes

		// Retrieves the bounding rectangle for the specified item.
		BOOL GetItemRect(__in HTREEITEM hItem, __out LPRECT lpRect, __in BOOL bTextOnly) const;

		// Gets the count of items in the control.
		UINT GetCount() const;

		// Returns the level-to-level indentation (in pixels).
		UINT GetIndent() const;

		// Sets the level-to-level indentation (in pixels).
		void SetIndent(__in UINT nIndent);

		// Retrieves the image list associated with the control.
		HIMAGELIST GetImageList(__in int nImageList) const;

		// Sets the image list associated with this control.
		HIMAGELIST SetImageList(__in HIMAGELIST pImageList, __in int nImageList);

		// Retrieves the next item having the given relationship with the
		// specified item.
		HTREEITEM GetNextItem(__in HTREEITEM hItem, __in UINT nCode) const;

		// Retrieves the next child item after the specified item.
		HTREEITEM GetChildItem(__in HTREEITEM hItem) const;

		// Retrieves the next sibling item after the specified item.
		HTREEITEM GetNextSiblingItem(__in HTREEITEM hItem) const;

		// Retrieves the previous sibling item of the specified item.
		HTREEITEM GetPrevSiblingItem(__in HTREEITEM hItem) const;

		// Retrieves the parent of the specified item.
		HTREEITEM GetParentItem(__in HTREEITEM hItem) const;

		// Retrieves the topmost visible item in the control.
		HTREEITEM GetFirstVisibleItem() const;

		// Retrieves the next visible item after the specified item.
		HTREEITEM GetNextVisibleItem(__in HTREEITEM hItem) const;

		// Retrieves the previous visible item before the specified item.
		HTREEITEM GetPrevVisibleItem(__in HTREEITEM hItem) const;

		// Retrieves the last expanded item in the tree. This does not retrieve the last item visible in the tree-view window.
		HTREEITEM GetLastVisibleItem() const;

		// Retrieves the higlighted item, NULL if none.
		HTREEITEM GetSelectedItem() const;

		// Retrieves the currently drop-highlighted item, NULL if none.
		HTREEITEM GetDropHilightItem() const;

		// Retrieves the root item of the control, NULL if none.
		HTREEITEM GetRootItem() const;

		// Retrieves information about a particular item in the control.
		BOOL GetItem(__out XTVITEM *pItem) const;

		// Retrieves the text associated with the given item.
		CIUIString GetItemText(__in HTREEITEM hItem) const;

		// Retrieves the images associated with the given item.
		BOOL GetItemImage(__in HTREEITEM hItem, __out int &nImage,
			__out int &nSelectedImage) const;

		// Retrieves the state of the given item.
		UINT GetItemState(__in HTREEITEM hItem, __in UINT nStateMask) const;

		// Retrieves the user-supplied data associated with the given item.
		DWORD_PTR GetItemData(__in HTREEITEM hItem) const;

		// Sets the state of the an item.
		BOOL SetItem(__in XTVITEM *pItem);
		BOOL SetItem(
			__in HTREEITEM hItem,
			__in UINT nMask,
			__in LPCTSTR lpszItem,
			__in int nImage,
			__in int nSelectedImage,
			__in UINT nState,
			__in UINT nStateMask,
			__in LPARAM lParam,
			__in HWLWND hBindWL);

#if (_WIN32_IE >= 0x0600)
		BOOL SetItemEx(__in HTREEITEM hItem, __in UINT nMask, __in LPCTSTR lpszItem, __in int nImage,
			__in int nSelectedImage, __in UINT nState, __in UINT nStateMask, __in LPARAM lParam,
			__in UINT uStateEx, __in HWND hWnd, __in int iExpandedImage);
#endif

		// Sets the text of the specified item.
		BOOL SetItemText(__in HTREEITEM hItem, __in LPCTSTR lpszItem);

		// Sets the image on the specified item.
		BOOL SetItemImage(__in HTREEITEM hItem, __in int nImage, __in int nSelectedImage);

		// Sets the state of the specified item.
		BOOL SetItemState(__in HTREEITEM hItem, __in UINT nState, __in UINT nStateMask);

		// Sets the user data on the specified item.
		BOOL SetItemData(__in HTREEITEM hItem, __in DWORD_PTR dwData);

		// Determines if the specified item has children.
		BOOL ItemHasChildren(__in HTREEITEM hItem) const;

		// Retrieves the edit control used to perform in-place editing.
		HWND GetEditControl() const;

		// Gets the count of items presently visible in the control.
		UINT GetVisibleCount() const;

		// Retrieves the tool tip control associated with this control.
		HWND GetToolTips() const;

		// Sets the tool tip control to be used by this control.
		HWND SetToolTips(__in HWND pWndTip);

		// Retrieves the background colour used throughout the control.
		COLORREF GetBkColor() const;

		// Sets the background color to be used throughout the control.
		COLORREF SetBkColor(__in COLORREF clr);

		// Retrieves the height of items in the control.
		SHORT GetItemHeight() const;

		// Sets the height of items in the control.
		SHORT SetItemHeight(__in SHORT cyHeight);

		SHORT SetItemHeightEx(__in HTREEITEM hItem, __in SHORT cyHeight);

		// Retrieves the text color used for all items in the control.
		COLORREF GetTextColor() const;

		// Sets the text color used for all items in the control.
		COLORREF SetTextColor(__in COLORREF clr);

		// Sets the insertion mark to the specified item in the control.
		BOOL SetInsertMark(__in HTREEITEM hItem, __in BOOL fAfter = TRUE);

		// Gets the checked state of the specified item in the control.
		// (Only useful on a control with the TVS_CHECKBOXES style.)
		BOOL GetCheck(__in HTREEITEM hItem) const;

		// Sets the checked state of the specified item in the control.
		// (Only useful on a control with the TVS_CHECKBOXES style.)
		BOOL SetCheck(__in HTREEITEM hItem, __in BOOL fCheck = TRUE);

		COLORREF GetInsertMarkColor() const;
		COLORREF SetInsertMarkColor(__in COLORREF clrNew);

		// Sets the maximum time (in milliseconds) the control will
		// spend smooth scrolling its content.
		UINT SetScrollTime(__in UINT uScrollTime);

		// Retrieves the maximum time (in milliseconds) the control will
		// spend smooth scrolling its content.
		UINT GetScrollTime() const;

#if _WIN32_IE >= 0x0500
		COLORREF GetLineColor() const;
		COLORREF SetLineColor(__in COLORREF clrNew = CLR_DEFAULT);
#endif

#if (_WIN32_IE >= 0x0600)
#endif

#if (_WIN32_WINNT >= 0x0501) && defined(UNICODE)
		// Maps treeview item id to accessibility identifier.
		UINT MapItemToAccId(HTREEITEM hItem) const;

		// Maps accessibility identifier id to treeview item.
		HTREEITEM MapAccIdToItem(UINT uAccId) const;

		// Set autoscrolling rate and delay (?).
		BOOL SetAutoscrollInfo(UINT uPixelsPerSec, UINT uUpdateTime);
#endif

#if (_WIN32_WINNT >= 0x0600) && defined(UNICODE)
		// Get count of selected items in the tree control.
		UINT GetSelectedCount();

		// Get rectangle for the specified part of the specified item.
		BOOL GetItemPartRect(HTREEITEM hItem, TVITEMPART nPart, LPRECT lpRect);

		// Get the extended state of the item
		UINT GetItemStateEx(HTREEITEM hItem) const;

		// Set the extended state of the item
		BOOL SetItemStateEx(HTREEITEM hItem, UINT uStateEx);

		// Get the expanded image index for the specified item
		int GetItemExpandedImageIndex(HTREEITEM hItem) const;

		// Set the expanded image index for the specified item
		BOOL SetItemExpandedImageIndex(HTREEITEM hItem, int nIndex);

		// Get extended styles for the tree control.
		DWORD GetExtendedStyle() const;

		// Set extended styles on the tree control.
		DWORD SetExtendedStyle(DWORD dwExMask, DWORD dwExStyles);
#endif

		// Operations

		// Inserts a new item to the control.
		HTREEITEM InsertItem(__in LPTVINSERTSTRUCT lpInsertStruct);
		HTREEITEM InsertItem(__in UINT nMask, __in LPCTSTR lpszItem, __in int nImage,
			__in int nSelectedImage, __in UINT nState, __in UINT nStateMask, __in LPARAM lParam,
			__in HTREEITEM hParent, __in HTREEITEM hInsertAfter);
		HTREEITEM InsertItem(__in LPCTSTR lpszItem, __in HTREEITEM hParent = TVI_ROOT,
			__in HTREEITEM hInsertAfter = TVI_LAST);
		HTREEITEM InsertItem(__in LPCTSTR lpszItem, __in int nImage, __in int nSelectedImage,
			__in HTREEITEM hParent = TVI_ROOT, __in HTREEITEM hInsertAfter = TVI_LAST);

		// ��hItemBeMove�ƶ���hParent��Item hInsertAfter ֮��
		BOOL MoveItemTo(__in HTREEITEM hItemBeMove,
			__in HTREEITEM hParent = TVI_ROOT, __in HTREEITEM hInsertAfter = TVI_LAST);

		// Removes the specified item from the control.
		BOOL DeleteItem(__in HTREEITEM hItem);

		// Removes all items from the control.
		BOOL DeleteAllItems();

		// Expands the children of the specified item.
		BOOL Expand(__in HTREEITEM hItem, __in UINT nCode);

		// Selects the specified item.
		BOOL Select(__in HTREEITEM hItem, __in UINT nCode);

		// Selects the specified item.
		BOOL SelectItem(__in HTREEITEM hItem);

		// Selects an item to be the drop target in the control.
		BOOL SelectDropTarget(__in HTREEITEM hItem);

		// Draws the specified item as the drop target for the control.
		BOOL SelectSetFirstVisible(__in HTREEITEM hItem);

		// Begins editing the label of the specified item.
		HWND EditLabel(__in HTREEITEM hItem);

		// Determines the visual feature of the control under
		// the specified point.
		HTREEITEM HitTest(__in CIUIPoint pt, __in UINT *pFlags = NULL) const;
		HTREEITEM HitTest(__in TVHITTESTINFO *pHitTestInfo) const;

		// Create a drag image for the specified item.
		HIMAGELIST CreateDragImage(__in HTREEITEM hItem);

		// Sorts all children of the specified item.
		BOOL SortChildren(__in HTREEITEM hItem);

		// Scrolls the control to ensure the specified item is visible.
		BOOL EnsureVisible(__in HTREEITEM hItem);

		// Sorts items in the control using the provided callback function.
		BOOL SortChildrenCB(__in LPTVSORTCB pSort);

		// Terminates label editing operation.
		BOOL EndEditLabelNow(BOOL fCancelWithoutSave);

#if (_WIN32_WINNT >= 0x0600) && defined(UNICODE)
		// Shows information tooltip on the specified item.
		void ShowInfoTip(HTREEITEM hItem);
#endif

		BOOL IsSmoothVScroll() const;
		BOOL SetItemBindWindowless(HTREEITEM hItem, HWLWND hBind);
		HWLWND GetItemBindWindowless(HTREEITEM hItem) const;

		// Implementation
	protected:
		void RemoveImageList(__in int nImageList);

	public:
		// 		//{{AFX_MSG(CTreeCtrl)
		void OnDestroy();
		// 		//}}AFX_MSG
		// 		DECLARE_MESSAGE_MAP()

		// IUI Add
		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameD) const;

		int SetTextAlignHor(
			TEXT_ALIGN_HOR eHorAlignModeN,
			TEXT_ALIGN_HOR eHorAlignModeH,
			TEXT_ALIGN_HOR eHorAlignModeS,
			TEXT_ALIGN_HOR eHorAlignModeD,
			BOOL bRedraw
		);
		int GetTextAlignHor(
			TEXT_ALIGN_HOR *peHorAlignModeN,
			TEXT_ALIGN_HOR *peHorAlignModeH,
			TEXT_ALIGN_HOR *peHorAlignModeS,
			TEXT_ALIGN_HOR *peHorAlignModeD
		);

		int SetTextAlignVer(
			TEXT_ALIGN_VER eVerAlignModeN,
			TEXT_ALIGN_VER eVerAlignModeH,
			TEXT_ALIGN_VER eVerAlignModeS,
			TEXT_ALIGN_VER eVerAlignModeD,
			BOOL bRedraw
		);
		int GetTextAlignVer(
			TEXT_ALIGN_VER *peVerAlignModeN,
			TEXT_ALIGN_VER *peVerAlignModeH,
			TEXT_ALIGN_VER *peVerAlignModeS,
			TEXT_ALIGN_VER *peVerAlignModeD
		);

		int SetTextMargin(
			LPCRECT lprcTextMarginN,
			LPCRECT lprcTextMarginH,
			LPCRECT lprcTextMarginS,
			LPCRECT lprcTextMarginD,
			BOOL bRedraw
		);
		int GetTextMargin(
			LPRECT lprcTextMarginN,
			LPRECT lprcTextMarginH,
			LPRECT lprcTextMarginS,
			LPRECT lprcTextMarginD
		) const;

		// For item line
		int EnableItemLine(BOOL bEnable);
		BOOL IsEnableItemLine() const;

		int SetItemLineColor(COLORREF cr);
		COLORREF GetItemLineColor() const;

		// For �۵���Item Image(+��)
		int SetCombineCollapseExpandedImage(LPCTSTR lpszImage);
		int SetCollapseImage(
			UINT uMask,
			LPCTSTR lpszImageNameCollapseN,
			LPCTSTR lpszImageNameCollapseH,
			LPCTSTR lpszImageNameCollapseS,
			LPCTSTR lpszImageNameCollapseD
		);
		int GetCollapseImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameS,
			CIUIString *pstrImageNameD
		) const;

		// For Expand item image
		int SetExpandedImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameS,
			LPCTSTR lpszImageNameD
		);
		int GetExpandedImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameS,
			CIUIString *pstrImageNameD
		) const;

		// ����ָ��Item����

		// �Ƿ񵥶�����ָ��Item���������δ���ã���ʹ��ͨ��Item������
		int EnableItemBkEffect(HTREEITEM hItem, BOOL bEnable);
		BOOL IsItemBkEffectEnabled(HTREEITEM hItem) const;

		int SetItemBkType(HTREEITEM hItem, BACKGROUND_TYPE eBkType);
		BACKGROUND_TYPE GetItemBkType(HTREEITEM hItem) const;

		int SetItemBkColor(
			HTREEITEM hItem,
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD
		);
		int GetItemBkColor(
			HTREEITEM hItem,
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD
		) const;

		int SetItemBkImage(
			HTREEITEM hItem,
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameS,
			LPCTSTR lpszImageNameD
		);
		int GetItemBkImage(
			HTREEITEM hItem,
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameS,
			CIUIString *pstrImageNameD
		);
		int SetItemBkImageResizeArg(
			HTREEITEM hItem,
			IMAGE_RESIZE_MODE eIrm,
			LPCRECT lprc9Grid
		);
		int GetItemBkImageResizeArg(
			HTREEITEM hItem,
			IMAGE_RESIZE_MODE *peIrm,
			LPRECT lprc9Grid
		);

		int SetItemTextColor(
			HTREEITEM hItem,
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD
		);
		int GetItemTextColor(
			HTREEITEM hItem,
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD
		) const;

		// for focus item
		// ����Item��Disabled״̬����Ϊ�ؼ�Disabled��ʱ�򣬲�����õ����㡣
		int SetFocusItemBkType(BACKGROUND_TYPE eBkType);
		BACKGROUND_TYPE GetFocusItemBkType() const;

		int SetFocusItemBkColor(COLORREF cr);
		COLORREF GetFocusItemBkColor() const;

		int SetFocusItemBkImage(LPCTSTR lpszImageNameBk);
		int GetFocusItemBkImage(CIUIString *pstrImageNameBk) const;
		int SetFocusItemBkImageResizeArg(IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
		int GetFocusItemBkImageResizeArg(IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid) const;

		int SetFocusItemTextColor(COLORREF cr);
		COLORREF GetFocusItemTextColor() const;

		// for selected item
		int SetSelectedItemBkType(BACKGROUND_TYPE eBkType);
		BACKGROUND_TYPE GetSelectedItemBkType() const;

		int SetSelectedItemBkColor(COLORREF cr);
		COLORREF GetSelectedItemBkColor() const;

		int SetSelectedItemBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameBkN,
			LPCTSTR lpszImageNameBkD
		);
		int GetSelectedItemBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameBkN,
			CIUIString *pstrImageNameBkD
		) const;
		int SetSelectedItemBkImageResizeArg(IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
		int GetSelectedItemBkImageResizeArg(IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid) const;

		int SetSelectedItemTextColor(COLORREF cr);
		COLORREF GetSelectedItemTextColor() const;

		// for highlight item
		int EnableHighlightItemEffect(BOOL bEnable);
		BOOL IsHighlightItemEffectEnabled() const;
		HTREEITEM GetHighlightItem() const;

		int SetHighlightItemBkType(BACKGROUND_TYPE eBkType);
		BACKGROUND_TYPE GetHighlightItemBkType() const;

		int SetHighlightItemBkColor(COLORREF cr);
		COLORREF GetHighlightItemBkColor() const;

		int SetHighlightItemBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameBkFocus,
			LPCTSTR lpszImageNameBkNoFocus
		);
		int GetHighlightItemBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameBkFocus,
			CIUIString *pstrImageNameBkNoFocus
		);
		int SetHighlightItemBkImageResizeArg(IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
		int GetHighlightItemBkImageResizeArg(IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid) const;

		int SetHighlightItemTextColor(COLORREF cr);
		COLORREF GetHighlightItemTextColor() const;

		// for disable text color
		int SetDisabledItemTextColor(COLORREF cr);
		COLORREF GetDisabledItemTextColor() const;

		// for mouse hover
		int SetHoverTime(DWORD dwHoverTime, BOOL bRepeat/* = FALSE*/);
		int GetHoverTime(DWORD *pdwHoverTime, BOOL *pbRepeat) const;

		//// for scroll bar
		//int SetHoverScrollBarMode(BOOL bHoverShow);
		//BOOL IsHoverScrollBarMode() const;

		int SetTextFont(UINT uMask, LPCTSTR lpszFontIDN, LPCTSTR lpszFontIDD);
		int GetTextFont(UINT uMask, CIUIString *pstrFontIDN, CIUIString *pstrFontIDD) const;

		int GetChildrenCount(HTREEITEM hItem) const;
		int CollapseAll();

		// ����/�õ�	WM_MOUSEWHEEL�Ĳ���
		int SetMouseWheelStep(int nStep);
		int GetMouseWheelStep() const;
	};

	class IUIAPI ComboBox : public CWLWnd
	{
	public:
		ComboBox();
		virtual ~ComboBox();

		// ��dwStyle����WS_VSCROLL���ʱ��ComboBox�������б�Ż�����Ҫ��ʱ����ִ�ֱ��������
		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParentWnd,
			LPCTSTR lpszName
		);

		virtual int BindStyle(const CControlProp *pCtrlProp);

	public:
		int SetButtonWidth(int nWidth);
		int GetButtonWidth() const;

		int SetButtonMargin(LPCRECT lprcMargin);
		int GetButtonMargin(LPRECT lprcMargin) const;

		// ����
		int SetBkColor(
			UINT uMask,
			COLORREF crBkN,
			COLORREF crBkH,
			COLORREF crBkS,
			COLORREF crBkD);
		int GetBkColor(
			UINT uMask,
			COLORREF *pcrBkN,
			COLORREF *pcrBkH,
			COLORREF *pcrBkS,
			COLORREF *pcrBkD) const;

		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameS,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameS,
			CIUIString *pstrImageNameD) const;

		// �߿�
		int SetBorderColor(
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD,
			BOOL bRedraw);
		int GetBorderColor(
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD) const;

		// �ı�
		int SetTextColor(
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crS,
			COLORREF crD,
			BOOL bRedraw);
		int GetTextColor(
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrS,
			COLORREF *pcrD) const;
		int SetFocusedTextColor(COLORREF cr);
		COLORREF GetFocusedTextColor() const;

		int SetTextFont(
			UINT uMask,
			LPCTSTR lpszFontIDN,
			LPCTSTR lpszFontIDH,
			LPCTSTR lpszFontIDS,
			LPCTSTR lpszFontIDD,
			BOOL bRedraw);
		int GetTextFont(
			UINT uMask,
			CIUIString *pstrFontIDN,
			CIUIString *pstrFontIDH,
			CIUIString *pstrFontIDS,
			CIUIString *pstrFontIDD) const;

		// �ı���ؼ����
		int SetTextMargin(
			UINT uMask,
			LPCRECT lprcTextMarginN,
			LPCRECT lprcTextMarginH,
			LPCRECT lprcTextMarginS,
			LPCRECT lprcTextMarginD,
			BOOL bRedraw);
		int GetTextMargin(
			UINT uMask,
			LPRECT lprcTextMarginN,
			LPRECT lprcTextMarginH,
			LPRECT lprcTextMarginS,
			LPRECT lprcTextMarginD) const;

		int SetEditMargin(LPCRECT lprcMargin);
		int GetEditMargin(LPRECT lprcMargin);

		// �ı�����ģʽ
		int SetTextAlignHor(
			UINT uMask,
			TEXT_ALIGN_HOR eHorAlignModeN,
			TEXT_ALIGN_HOR eHorAlignModeH,
			TEXT_ALIGN_HOR eHorAlignModeS,
			TEXT_ALIGN_HOR eHorAlignModeD,
			BOOL bRedraw);
		int GetTextAlignHor(
			UINT uMask,
			TEXT_ALIGN_HOR *peHorAlignModeN,
			TEXT_ALIGN_HOR *peHorAlignModeH,
			TEXT_ALIGN_HOR *peHorAlignModeS,
			TEXT_ALIGN_HOR *peHorAlignModeD) const;
		int SetTextAlignVer(
			UINT uMask,
			TEXT_ALIGN_VER eVerAlignModeN,
			TEXT_ALIGN_VER eVerAlignModeH,
			TEXT_ALIGN_VER eVerAlignModeS,
			TEXT_ALIGN_VER eVerAlignModeD,
			BOOL bRedraw);
		int GetTextAlignVer(
			UINT uMask,
			TEXT_ALIGN_VER *peVerAlignModeN,
			TEXT_ALIGN_VER *peVerAlignModeH,
			TEXT_ALIGN_VER *peVerAlignModeS,
			TEXT_ALIGN_VER *peVerAlignModeD) const;

		// ������ť
		BOOL SetDrawDropButtonBkColor(BOOL bDraw);
		BOOL IsDrawDropButtonBkColor() const;

		int SetDropButtonBkColor(
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crP,
			COLORREF crD,
			COLORREF crS,
			BOOL bRedraw);
		int GetDropButtonBkColor(
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrP,
			COLORREF *pcrD,
			COLORREF *pcrS) const;

		int SetDropButtonCombineBkImage(LPCTSTR lpszImage);
		CIUIString GetDropButtonCombineBkImage() const;

		int SetDropButtonBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameH,
			LPCTSTR lpszImageNameP,
			LPCTSTR lpszImageNameD,
			LPCTSTR lpszImageNameS,
			BOOL bRedraw);

		int GetDropButtonBkImage(
			UINT uMask,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameH,
			CIUIString *pstrImageNameP,
			CIUIString *pstrImageNameD,
			CIUIString *pstrImageNameS) const;

		BOOL SetDrawDropButtonBorderColor(BOOL bDraw);
		BOOL IsDrawDropButtonBorderColor() const;

		int SetDropButtonBorderColor(
			UINT uMask,
			COLORREF crN,
			COLORREF crH,
			COLORREF crP,
			COLORREF crD,
			COLORREF crS,
			BOOL bRedraw);
		int GetDropButtonBorderColor(
			UINT uMask,
			COLORREF *pcrN,
			COLORREF *pcrH,
			COLORREF *pcrP,
			COLORREF *pcrD,
			COLORREF *pcrS) const;

	public:
		// Attributes
		// for entire combo box
		int GetCount() const;
		int GetCurSel() const;
		int SetCurSel(int nSelect);
		LCID GetLocale() const;
		LCID SetLocale(LCID nNewLocale);
		// Win4
		int GetTopIndex() const;
		int SetTopIndex(int nIndex);
		int InitStorage(int nItems, UINT nBytes);
		void SetHorizontalExtent(UINT nExtent);
		UINT GetHorizontalExtent() const;
		int SetDroppedWidth(UINT nWidth);
		int GetDroppedWidth() const;
		HWND GetDroppedWnd() const;

		// for edit control
		DWORD GetEditSel() const;
		BOOL LimitText(int nMaxChars);
		BOOL SetEditSel(int nStartChar, int nEndChar);

		// for combobox item
		DWORD GetItemData(int nIndex) const;
		int SetItemData(int nIndex, DWORD dwItemData);
		void *GetItemDataPtr(int nIndex) const;
		int SetItemDataPtr(int nIndex, void *pData);
		int GetLBText(int nIndex, LPTSTR lpszText) const;
		void GetLBText(int nIndex, CIUIString &rString) const;
		int GetLBTextLen(int nIndex) const;

		int SetItemHeight(int nIndex, UINT cyItemHeight);
		int GetItemHeight(int nIndex) const;
		int FindStringExact(int nIndexStart, LPCTSTR lpszFind) const;
		int SetExtendedUI(BOOL bExtended = TRUE);
		BOOL GetExtendedUI() const;
		void GetDroppedControlRect(LPRECT lprect) const;
		BOOL GetDroppedState() const;

		// Operations
		// for drop-down combo boxes
		void ShowDropDown(BOOL bShowIt = TRUE);

		// manipulating listbox items
		int AddString(LPCTSTR lpszString);
		int DeleteString(UINT nIndex);
		int InsertString(int nIndex, LPCTSTR lpszString);
		void ResetContent();
		int Dir(UINT attr, LPCTSTR lpszWildCard);

		// selection helpers
		int FindString(int nStartAfter, LPCTSTR lpszString) const;
		int SelectString(int nStartAfter, LPCTSTR lpszString);

		// Clipboard operations
		void Clear();
		void Copy();
		void Cut();
		void Paste();

		// Overridables (must override draw, measure and compare for owner draw)
		//virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
		//virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
		//virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
		//virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);

		// IUI Add
		BOOL SetItemBindWindowless(int nItem, HWLWND hBind);
		HWLWND GetItemBindWindowless(int nItem) const;

		int SetHighlightItemBkColor(COLORREF cr);
		COLORREF GetHighlightItemBkColor();
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class IUIAPI Canvas : public CWLWnd
	{
	public:
		Canvas();
		virtual ~Canvas();

		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParentWnd,
			LPCTSTR lpszName
		);

		virtual int BindStyle(const CControlProp *pCtrlProp);

		// ����
		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameD) const;

	public:
		/**
		@brief Canvas���ֵ���Ԫ���б�
		*/
		std::vector<CChildInfo> *m_pvCanvasChildList;
	};

	class IUIAPI DockPanel : public CWLWnd
	{
	public:
		DockPanel();
		virtual ~DockPanel();

		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParentWnd,
			LPCTSTR lpszName
		);

		virtual int BindStyle(const CControlProp *pCtrlProp);

		// ����
		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameD) const;

		int SetLastChildFill(BOOL bFill);
		BOOL IsLastChildFill() const;

	public:
		// DockPanel���ֵ���Ԫ���б�
		std::vector<CChildInfo> *m_pvDockChildList;
	};

	class CPropertySheetInfo
	{
	public:
		CPropertySheetInfo();
		~CPropertySheetInfo();

	public:
		// ID��RadioButton���
		void *m_Key;
		BOOL m_bKeyIsRadioButton;
		HWLWND m_hPropertySheet;
		CIUIString m_strPropertySheetXml;
		CWLWndHandler *m_pUserHandler;
	};

	class IUIAPI TabControl : public CWLWnd
	{
	public:
		TabControl();
		virtual ~TabControl();

		virtual BOOL Create(
			CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParent,
			LPCTSTR lpszName);

		virtual int BindStyle(const CControlProp *pCtrlProp);

	public:
		BOOL Remove(CWLWnd *pControl);
		void RemoveAll();
		UINT GetCurPropertySheet() const;

		int AddPropertySheet(UINT_PTR uKey, HWLWND hSheet, CWLWndHandler *pUserHandler);
		int AddPropertySheet(HWLWND hRadioButton, HWLWND hSheet, CWLWndHandler *pUserHandler);
		int AddPropertySheet(UINT_PTR uKey, LPCTSTR lpszXml, CWLWndHandler *pUserHandler);
		int AddPropertySheet(HWLWND hRadioButton, LPCTSTR lpszXml, CWLWndHandler *pUserHandler);
		int SwitchPropertySheet(UINT_PTR uKey);
		int SwitchPropertySheet(HWLWND hRadioButton);
		int DetachPropertySheetHandler(UINT_PTR uKey);
		int DetachPropertySheetHandler(HWLWND hRadioButton);
		CPropertySheetInfo *GetPropertySheet(UINT_PTR uKey) const;
		CPropertySheetInfo *GetPropertySheet(HWLWND hRadioButton) const;

	protected:
		virtual int RelayoutChild();
	};

	class IUIAPI StackPanel : public CWLWnd
	{
	public:
		StackPanel();
		virtual ~StackPanel();

		virtual BOOL Create(
			__inout CWLWndHandler *pUserHandler,
			DWORD dwStyle,
			const RECT &rect,
			HWND hParent,
			CWLWnd *pParentWnd,
			LPCTSTR lpszName
		);

		virtual int BindStyle(const CControlProp *pCtrlProp);

		// ����
		int SetBkImage(
			UINT uMask,
			LPCTSTR lpszImageNameN,
			LPCTSTR lpszImageNameD,
			BOOL bRedraw);
		int GetBkImage(
			UINT uMask,
			BOOL *pbCombineImage,
			CIUIString *pstrCombineImageName,
			CIUIString *pstrImageNameN,
			CIUIString *pstrImageNameD) const;

	public:
		// StackPanel���ֵ���Ԫ���б�
		std::vector<CChildInfo> *m_pvStackPanelChildList;
	};

	/////////////////////////////////////////////////////////////////////////////
	// CToolInfo

#ifdef _UNICODE
	class CToolInfo : public tagTOOLINFOW
#else
	class CToolInfo : public tagTOOLINFOA
#endif
	{
	public:
		TCHAR szText[256];
	};

	class ToolTipCtrl : public Window
	{
		// Constructors
	public:
		ToolTipCtrl();
		virtual ~ToolTipCtrl();

		// ���ToolTipsʹ��CToolTipCtrlProp����������ҪCIUIProject
		// ���hParentWnd�Ƿ�IUI���ڣ��޷���hParentWnd���CIUIProject��������Ҫ����ָ��
		virtual BOOL Create(
			__in HWND hParentWnd,
			__in const CIUIProject *pProject,
			__in DWORD dwStyle);

		// Attributes
		// Retrieves the text for a tool in the ToolTip control .
		void GetText(__out CIUIString &str, __in HWND hWnd, __in UINT_PTR nIDTool = 0) const;

		// Retrieves the information that the ToolTip control maintains about a tool.
		BOOL GetToolInfo(__out CToolInfo &ToolInfo, __in HWND hWnd, __in UINT_PTR nIDTool = 0) const;

		// Sets the information that the ToolTip control maintains about a tool.
		void SetToolInfo(__in LPTOOLINFO lpToolInfo);

		// Sets a new bounding rectangle for a tool.
		void SetToolRect(__in HWND hWnd, __in UINT_PTR nIDTool, __in LPCRECT lpRect);

		// Retrieves a count of the tools maintained by the ToolTip control.
		int GetToolCount() const;

		// Retrieves the initial, pop-up, or reshow duration currently set for the ToolTip control.
		int GetDelayTime(__in DWORD dwDuration) const;

		// Sets the initial, pop-up, or reshow duration for the ToolTip control.
		void SetDelayTime(__in DWORD dwDuration, __in int iTime);

		// Retrieves the top, left, bottom, and right margins set for the ToolTip window.
		void GetMargin(__out LPRECT lprc) const;

		// Sets the top, left, bottom, and right margins for the ToolTip window.
		void SetMargin(__in LPRECT lprc);

		// Retrieves the maximum width for the ToolTip window.
		int GetMaxTipWidth() const;

		// Sets the maximum width for the ToolTip window.
		int SetMaxTipWidth(__in int iWidth);

		// Retrieves the background color in the ToolTip window.
		COLORREF GetTipBkColor() const;

		// Sets the background color in the ToolTip window.
		void SetTipBkColor(__in COLORREF clr);

		// Retrieves the text color in the ToolTip window.
		COLORREF GetTipTextColor() const;

		// Sets the text color in the ToolTip window.
		void SetTipTextColor(__in COLORREF clr);

		// Retrieves the information for the current tool in the ToolTip control.
		BOOL GetCurrentTool(__out LPTOOLINFO lpToolInfo) const;

#if _WIN32_IE >= 0x0500
		// Returns the width and height of the ToolTip control.
		CIUISize GetBubbleSize(__in LPTOOLINFO lpToolInfo) const;
#endif

#if (_WIN32_WINNT >= 0x0501)
		// Sets the visual style of the ToolTip control.
		HRESULT SetWindowTheme(__in LPCWSTR pszSubAppName);
#endif

		// Operations
		// Activates or deactivates the ToolTip control.
		void Activate(__in BOOL bActivate);

		// һ��ToolTips�ؼ�����Ϊ���Ŀ�����
		// ����һ������"����"��ʹ�ñ�׼���ƣ�ӵ�о�����ۡ� �ı�����Դ����
		BOOL AddTool(
			__in HWND hWnd,
			__in UINT nIDText,
			__in LPCRECT lpRectTool,
			__in UINT_PTR nIDTool
		);
		// ����һ������"����"��ʹ�ñ�׼���ƣ�ӵ�о�����ۡ� ָ���ı�����ͨ���ص�����ı�
		BOOL AddTool(
			__in HWND hWnd,
			__in LPCTSTR lpszText/* = LPSTR_TEXTCALLBACK*/,
			__in LPCRECT lpRectTool,
			__in UINT_PTR nIDTool
		);
		// ����һ��IUI����"����"��ʹ�ý���༭�����ƵĽ��档 ָ���ı�����ͨ���ص�����ı�
		BOOL AddTool(
			__in HWND hWnd,
			__in const CToolTipCtrlProp *pToolTipCtrlProp,
			__in LPCTSTR lpszText/* = LPSTR_TEXTCALLBACK*/,
			__in LPCRECT lpRectTool,
			__in UINT_PTR nIDTool
		);
		// ����һ��IUI����"������"��ʹ�ý���༭�����ƵĽ��档 ��ָ���ı���
		// ��������ó�ʲô������ʾʲô����
		BOOL AddTool(
			__in HWND hWnd,
			__in const CToolTipCtrlProp *pToolTipCtrlProp,
			__in LPCRECT lpRectTool,
			__in UINT_PTR nIDTool
		);

		// Removes a tool from the ToolTip control.
		void DelTool(__in HWND hWnd, __in UINT_PTR nIDTool = 0);

		// Tests a point to determine whether it is within the bounding rectangle of
		// the specified tool and, if it is, retrieves information about the tool.
		BOOL HitTest(__in HWND hWnd, __in CIUIPoint pt, __in LPTOOLINFO lpToolInfo) const;

		// Passes a mouse message to the ToolTip control for processing.
		void RelayEvent(__in LPMSG lpMsg);

		void SetDelayTime(__in UINT nDelay);

		// Sets the ToolTip text for a tool.
		void UpdateTipText(__in LPCTSTR lpszText, __in HWND hWnd, __in UINT_PTR nIDTool = 0);
		void UpdateTipText(__in UINT nIDText, __in HWND hWnd, __in UINT_PTR nIDTool = 0);

		// Forces the current tool to be redrawn.
		void Update();

		// Removes the displayed ToolTip window from view.
		void Pop();

#if _WIN32_IE >= 0x0500
		// Calculates a ToolTip control's text display rectangle
		// from its window rectangle, or the ToolTip window rectangle
		// needed to display a specified text display rectangle.
		BOOL AdjustRect(__out LPRECT lprc, __in BOOL bLarger = TRUE);

		// Adds a standard icon and title string to the ToolTip.
		BOOL SetTitle(__in UINT uIcon, __in LPCTSTR lpstrTitle);
#endif

#if (_WIN32_WINNT >= 0x0501) && defined(UNICODE)
		// Causes the ToolTip to display at the coordinates of the last mouse message.
		void Popup();

		// Retrieves information concerning the title of a tooltip control.
		void GetTitle(__out PTTGETTITLE pTTGetTitle) const;
#endif

		// Implementation
	public:
		void FillInToolInfo(__out TOOLINFO &ti, __in HWND hWnd, __in UINT_PTR nIDTool) const;
#ifndef _AFXDLL
		virtual BOOL DestroyToolTipCtrl();
#else
		BOOL DestroyToolTipCtrl();
#endif
	};

	class IUIAPI CColorDialogUI
	{
	public:
		CColorDialogUI(COLORREF clrInit = 0, DWORD dwFlags = 0, HWND hParent = NULL);
		virtual ~CColorDialogUI();

	public:
		INT DoModal();
		COLORREF GetColor();

	protected:
		HWND m_hParent;
		HWND m_hWndTop;                 // top level parent window (may be disabled)
		CHOOSECOLOR m_cc;
	};

	class IUIAPI CFontDialogUI
	{
	public:
		CFontDialogUI(LPLOGFONT lplfInitial = NULL,
			DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS,
			HWND hParent = NULL);
		virtual ~CFontDialogUI();

	public:
		INT DoModal();

	protected:
		HWND m_hParent;
		HWND m_hWndTop;                 // top level parent window (may be disabled)

		TCHAR m_szStyleName[64];        // contains style name after return

	public:
		LOGFONT m_lf;                    // default LOGFONT to store the info
		CHOOSEFONT m_cf;
	};

	class IUIAPI FileDialog
	{
	public:
		FileDialog(LPCTSTR lpszFilter);
		virtual ~FileDialog();

	public:
		virtual INT DoModal();

		// Helpers for parsing file name after successful return
		// or during Overridable callbacks if OFN_EXPLORER is set
		CIUIString GetPathName() const;  // return full path and filename
		CIUIString GetFileName() const;  // return only filename
		CIUIString GetFileExt() const;   // return only ext
		CIUIString GetFileTitle() const; // return file title
		// Other operations available while the dialog is visible
		CIUIString GetFolderPath() const; // return full path

	protected:
		TCHAR *m_pszFilters;
		TCHAR m_szFile[MAX_PATH];
		TCHAR m_szFileTitle[64];
		TCHAR m_szTitle[MAX_PATH];
		TCHAR m_szDefExt[MAX_PATH];

	public:
		OPENFILENAME m_ofn;
	};

	class IUIAPI CFileDialogUI
	{
	public:
		CFileDialogUI(
			BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
			LPCTSTR lpszDefExt = NULL,
			LPCTSTR lpszFileName = NULL,
			DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			LPCTSTR lpszFilter = NULL,
			HWND hParentWnd = NULL,
			DWORD dwSize = 0,
			BOOL bVistaStyle = TRUE);
		virtual ~CFileDialogUI();

	public:
		virtual INT DoModal();

		// Helpers for parsing file name after successful return
		// or during Overridable callbacks if OFN_EXPLORER is set
		CIUIString GetPathName() const;  // return full path and filename
		CIUIString GetFileName() const;  // return only filename
		CIUIString GetFileExt() const;   // return only ext
		CIUIString GetFileTitle() const; // return file title
		BOOL GetReadOnlyPref() const; // return TRUE if readonly checked

		// Enumerating multiple file selections
		IUIPOS GetStartPosition() const;
		CIUIString GetNextPathName(IUIPOS &pos) const;

		// Helpers for custom templates
		void SetTemplate(UINT nWin3ID, UINT nWin4ID);
		void SetTemplate(LPCTSTR lpWin3ID, LPCTSTR lpWin4ID);

		// Other operations available while the dialog is visible
		CIUIString GetFolderPath() const; // return full path
		void SetControlText(int nID, LPCSTR lpsz);
#ifdef UNICODE
		void SetControlText(int nID, const wchar_t  *lpsz);
#endif
		void HideControl(int nID);
		void SetDefExt(LPCSTR lpsz);

		//    virtual void UpdateOFNFromShellDialog();
		void ApplyOFNToShellDialog();

	protected:
		HWND m_hParent;
		HWND m_hWndTop;                 // top level parent window (may be disabled)

		BOOL m_bVistaStyle;
		BOOL m_bPickFoldersMode;
		DWORD m_dwCookie;
		void *m_pIFileDialog;
		void *m_pIFileDialogCustomize;

		BOOL m_bOpenFileDialog;       // TRUE for file open, FALSE for file save
		CIUIString m_strFilter;          // filter string
		// separate fields with '|', terminate with '||\0'
		TCHAR m_szFileTitle[64];       // contains file title after return
		TCHAR m_szFileName[_MAX_PATH]; // contains full path name after return

		OPENFILENAME  *m_pofnTemp;

	public:
		OPENFILENAME m_ofn;
		LPOPENFILENAME m_pOFN;
		HWND m_hWnd;
	};


	struct DropInfo
	{
		__in LPDATAOBJECT lpDataObject;
		__in DWORD dwKeyState;
		__inout DWORD dropEffect;
		__in POINT point;
		__in HWLWND hWnd;
	};

	class CHWLWNDDropTarget : public IDropTarget
	{
	public:
		CHWLWNDDropTarget(HWLWND hWnd);
		~CHWLWNDDropTarget();

	public:
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, __RPC__deref_out void **ppvObject);
		ULONG STDMETHODCALLTYPE AddRef();
		ULONG STDMETHODCALLTYPE Release();

		HRESULT STDMETHODCALLTYPE DragEnter(
			__RPC__in_opt IDataObject *pDataObj,
			DWORD grfKeyState,
			POINTL pt,
			__RPC__inout DWORD *pdwEffect
		);
		HRESULT STDMETHODCALLTYPE DragOver(
			DWORD grfKeyState,
			POINTL pt,
			__RPC__inout DWORD *pdwEffect
		);
		HRESULT STDMETHODCALLTYPE DragLeave();
		HRESULT STDMETHODCALLTYPE Drop
		(__RPC__in_opt IDataObject *pDataObj,
			DWORD grfKeyState,
			POINTL pt,
			__RPC__inout DWORD *pdwEffect
		);

	private:
		HWLWND m_hWnd;
		ULONG m_lRefCount;
	};


	class IUIAPI CIUINoTrackObject
	{
	public:
		void *PASCAL operator new (size_t nSize);
		void PASCAL operator delete (void *);

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
		void *PASCAL operator new (size_t nSize, LPCSTR, int);
#if _MSC_VER >= 1200
		void PASCAL operator delete (void *pObject, LPCSTR, int);
#endif
#endif
		virtual ~IUIAPI CIUINoTrackObject() { }
	};

	class CIUIWinThread/* : public CCmdTarget*/
	{
		// friend BOOL AfxInternalPreTranslateMessage(MSG *pMsg);

	public:
		// Constructors
		CIUIWinThread();
		BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
			LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

		// Attributes
		//Window *m_pMainWnd;      // main window (usually same AfxGetApp()->m_pMainWnd)
		//Window *m_pActiveWnd;     // active main window (may not be m_pMainWnd)
		BOOL m_bAutoDelete;     // enables 'delete this' after thread termination

		// only valid while running
		HANDLE m_hThread;       // this thread's HANDLE
		operator HANDLE() const;
		DWORD m_nThreadID;      // this thread's ID

		int GetThreadPriority();
		BOOL SetThreadPriority(int nPriority);

		// Operations
		DWORD SuspendThread();
		DWORD ResumeThread();
		BOOL PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);

		// Overridables
		// thread initialization
		virtual BOOL InitInstance();

		// running and idle processing
		virtual int Run();
		virtual BOOL PreTranslateMessage(MSG *pMsg);
		virtual BOOL PumpMessage();     // low level message pump
		virtual BOOL OnIdle(LONG lCount); // return TRUE if more idle processing
		virtual BOOL IsIdleMessage(MSG *pMsg);  // checks for special messages

		// thread termination
		virtual int ExitInstance(); // default will 'delete this'

		// Advanced: exception handling
		//virtual LRESULT ProcessWndProcException(CException *e, const MSG *pMsg);

		// Advanced: handling messages sent to message filter hook
		virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);

		// Advanced: virtual access to m_pMainWnd
		virtual Window *GetMainWnd();

		// Implementation
	public:
		virtual ~CIUIWinThread();
#ifdef _DEBUG
		virtual void AssertValid() const;
		//virtual void Dump(CDumpContext &dc) const;
#endif
		void CommonConstruct();
		virtual void Delete();
		// 'delete this' only if m_bAutoDelete == TRUE

	public:
		// constructor used by implementation of AfxBeginThread
		//CIUIWinThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam);

		// valid after construction
		LPVOID m_pThreadParams; // generic parameters passed to starting function
		//AFX_THREADPROC m_pfnThreadProc;

		// set after OLE is initialized
		//void (AFXAPI *m_lpfnOleTermOrFreeLib)(BOOL, BOOL);
		//COleMessageFilter *m_pMessageFilter;

	protected:
		BOOL DispatchThreadMessageEx(MSG *msg);  // helper
		void DispatchThreadMessage(MSG *msg);  // obsolete
	};

	// IUI_MODULE_THREAD_STATE (local to thread *and* module)
	class IUI_MODULE_THREAD_STATE : public CIUINoTrackObject
	{
	public:
		IUI_MODULE_THREAD_STATE();
		virtual ~IUI_MODULE_THREAD_STATE();

		// current CIUIWinThread pointer
		CIUIWinThread *m_pCurrentWinThread;

		// list of CFrameWnd objects for thread
		//CTypedSimpleList<CFrameWnd *> m_frameList;

		// temporary/permanent map state
		DWORD m_nTempMapLock;           // if not 0, temp maps locked
		std::map<HWND, Window *> *m_pmapHWND;
		//CHandleMap *m_pmapHMENU;
		//CHandleMap *m_pmapHDC;
		//CHandleMap *m_pmapHGDIOBJ;
		//CHandleMap *m_pmapHIMAGELIST;

		// IUI Add.
		// ����comctl32.dll 5.8�汾δ����GetWindowSubclass��
		// ���ֵ������¼SetWindowSubclass���õ���Ϣ
		std::map<HWND, std::set<void *> > *m_pmapSubclassInfo;// TODO����Ҫ�ͷ��ڴ�

		// SetTimer(NULL, 0, xxx, xxx)���ص�Timer ID��HTIMER�Ķ�Ӧ��ϵ
		std::map<UINT_PTR, HTIMER> m_mapTimer;

		// thread-local MFC new handler (separate from C-runtime)
		_PNH m_pfnNewHandler;

#ifndef _AFX_NO_SOCKET_SUPPORT
		// WinSock specific thread state
		HWND m_hSocketWindow;
#ifdef _AFXDLL
		// 		CEmbeddedButActsLikePtr<CMapPtrToPtr> m_pmapSocketHandle;
		// 		CEmbeddedButActsLikePtr<CMapPtrToPtr> m_pmapDeadSockets;
		// 		CEmbeddedButActsLikePtr<CPtrList> m_plistSocketNotifications;
#else
		//CMapPtrToPtr *m_pmapSocketHandle;
		//CMapPtrToPtr *m_pmapDeadSockets;
		//CPtrList *m_plistSocketNotifications;
#endif
#endif

		// common controls thread state
		//CToolTipCtrl *m_pToolTip;
		Window *m_pLastHit;       // last window to own tooltip
		INT_PTR m_nLastHit;         // last hittest code
		TOOLINFO *m_pLastInfo;    // last TOOLINFO structure
		INT_PTR m_nLastStatus;      // last flyby status message
		//CControlBar *m_pLastStatus; // last flyby status control bar
	};

	class IUIAPI CIUIThreadLocalObject
	{
	public:
		// Attributes
		CIUINoTrackObject *GetData(CIUINoTrackObject * (*pfnCreateObject)());
		CIUINoTrackObject *GetDataNA();

		// Implementation
		int m_nSlot;
		~CIUIThreadLocalObject();
	};

	template<class TYPE>
	class CIUIThreadLocal : public CIUIThreadLocalObject
	{
		// Attributes
	public:
		inline TYPE *GetData()
		{
			TYPE *pData = (TYPE *)CIUIThreadLocalObject::GetData(&CreateObject);
			ENSURE(pData != NULL);
			return pData;
		}
		inline TYPE *GetDataNA()
		{
			TYPE *pData = (TYPE *)CIUIThreadLocalObject::GetDataNA();
			return pData;
		}
		inline operator TYPE *()
		{
			return GetData();
		}
		inline TYPE *operator->()
		{
			return GetData();
		}

		// Implementation
	public:
		static CIUINoTrackObject *CreateObject()
		{
			return new TYPE;
		}
	};

	class CIUISimpleList
	{
	public:
		CIUISimpleList(int nNextOffset = 0);
		void Construct(int nNextOffset);

		// Operations
		BOOL IsEmpty() const;
		void AddHead(void *p);
		void RemoveAll();
		void *GetHead() const;
		void *GetNext(void *p) const;
		BOOL Remove(void *p);

		// Implementation
		void *m_pHead;
		size_t m_nNextOffset;

		void **GetNextPtr(void *p) const;   // somewhat trusting...
	};

	inline CIUISimpleList::CIUISimpleList(int nNextOffset)
	{
		m_pHead = NULL;
		m_nNextOffset = nNextOffset;
	}
	inline void CIUISimpleList::Construct(int nNextOffset)
	{
		_ASSERT(m_pHead == NULL);
		m_nNextOffset = nNextOffset;
	}
	inline BOOL CIUISimpleList::IsEmpty() const
	{
		return m_pHead == NULL;
	}
	inline void **CIUISimpleList::GetNextPtr(void *p) const
	{
		_ASSERT(p != NULL);
		return (void **)((BYTE *)p + m_nNextOffset);
	}
	inline void CIUISimpleList::RemoveAll()
	{
		m_pHead = NULL;
	}
	inline void *CIUISimpleList::GetHead() const
	{
		return m_pHead;
	}
	inline void *CIUISimpleList::GetNext(void *prevElement) const
	{
		return *GetNextPtr(prevElement);
	}

	template<class TYPE>
	class CIUITypedSimpleList : public CIUISimpleList
	{
	public:
		CIUITypedSimpleList(int nNextOffset = 0)
			: CIUISimpleList(nNextOffset) { }
		void AddHead(TYPE p)
		{
			CIUISimpleList::AddHead(p);
		}
		TYPE GetHead()
		{
			return (TYPE)CIUISimpleList::GetHead();
		}
		TYPE GetNext(TYPE p)
		{
			return (TYPE)CIUISimpleList::GetNext(p);
		}
		BOOL Remove(TYPE p)
		{
			return CIUISimpleList::Remove((TYPE)p);
		}
		operator TYPE();
	};
	template<class TYPE>
	inline CIUITypedSimpleList<TYPE>::operator TYPE()
	{
		return (TYPE)CIUISimpleList::GetHead();
	}

	struct CIUIThreadData; // private to implementation
	struct CIUISlotData;   // private to implementation

	class CIUIThreadSlotData
	{
	public:
		CIUIThreadSlotData();

		// Operations
		int AllocSlot();
		void FreeSlot(int nSlot);
		void SetValue(int nSlot, void *pValue);
		// delete all values in process/thread
		void DeleteValues(HINSTANCE hInst, BOOL bAll = FALSE);
		// assign instance handle to just constructed slots
		void AssignInstance(HINSTANCE hInst);

		// Implementation
		DWORD m_tlsIndex;   // used to access system thread-local storage

		int m_nAlloc;       // number of slots allocated (in UINTs)
		int m_nRover;       // (optimization) for quick finding of free slots
		int m_nMax;         // size of slot table below (in bits)
		CIUISlotData *m_pSlotData; // state of each slot (allocated or not)

		// ������ÿ���̵߳�TlsSetValue������CThreadData(CThreadData�ֱ�����_AFX_THREAD_STATE)��
		// ֮����Ҫ���棬����Ϊ��Щ�������Ƕ�̬��������ģ��߳��˳�ʱ����������ͷš�
		// ���Լ��б��浽�б��У���ȫ�ֱ���_afxThreadData����ʱ��ͳһ�ͷš�
		CIUITypedSimpleList<CIUIThreadData *> m_list; // list of CThreadData structures
		CRITICAL_SECTION m_sect;

		void *GetThreadValue(int nSlot); // special version for threads only!
		void *PASCAL operator new (size_t, void *p)
		{
			return p;
		}
		void DeleteValues(CIUIThreadData *pData, HINSTANCE hInst);
		~CIUIThreadSlotData();
	};

	// AFX_MODULE_STATE (global data for a module)
	class IUI_MODULE_STATE : public CIUINoTrackObject
	{
	public:
#ifdef _AFXDLL
		IUI_MODULE_STATE(BOOL bDLL, WNDPROC pfnAfxWndProc, DWORD dwVersion,
			BOOL bSystem = FALSE);
#else
		explicit IUI_MODULE_STATE(BOOL bDLL);
#endif
		~IUI_MODULE_STATE();

		//CWinApp *m_pCurrentWinApp;
		HINSTANCE m_hCurrentInstanceHandle;
		HINSTANCE m_hCurrentResourceHandle;
		LPCTSTR m_lpszCurrentAppName;
		BYTE m_bDLL;    // TRUE if module is a DLL, FALSE if it is an EXE
		BYTE m_bSystem; // TRUE if module is a "system" module, FALSE if not
		BYTE m_bReserved[2]; // padding

		DWORD m_fRegisteredClasses; // flags for registered window classes

		// runtime class data
#ifdef _AFXDLL
		// 		CRuntimeClass *m_pClassInit;
#endif
		//CIUITypedSimpleList<CRuntimeClass *> m_classList;

		// OLE object factories
#ifndef _AFX_NO_OLE_SUPPORT
#ifdef _AFXDLL
		// 		COleObjectFactory *m_pFactoryInit;
#endif
		//CTypedSimpleList<COleObjectFactory *> m_factoryList;
#endif
		// number of locked OLE objects
		long m_nObjectCount;
		BOOL m_bUserCtrl;

		// AfxRegisterClass and AfxRegisterWndClass data

		CIUIString m_strUnregisterList;

#ifdef _AFXDLL
		WNDPROC m_pfnAfxWndProc;
		DWORD m_dwVersion;  // version that module linked against
#endif

		// variables related to a given process in a module
		//  (used to be AFX_MODULE_PROCESS_STATE)
		void (PASCAL *m_pfnFilterToolTipMessage)(MSG *, Window *);

#ifdef _AFXDLL
		// CDynLinkLibrary objects (for resource chain)
		// 		CTypedSimpleList<CDynLinkLibrary *> m_libraryList;
		//
		// 		// special case for MFCXXLLL.DLL (localized MFC resources)
		// 		HINSTANCE m_appLangDLL;
#endif

#ifndef _AFX_NO_OCC_SUPPORT
		// OLE control container manager
		//COccManager *m_pOccManager;
		// locked OLE controls
		//CTypedSimpleList<COleControlLock *> m_lockList;
#endif

#ifndef _AFX_NO_DAO_SUPPORT
		//_AFX_DAO_STATE *m_pDaoState;
#endif

#ifndef _AFX_NO_OLE_SUPPORT
		// Type library caches
		//CTypeLibCache m_typeLibCache;
		//CTypeLibCacheMap *m_pTypeLibCacheMap;
#endif

		// define thread local portions of module state
		CIUIThreadLocal<IUI_MODULE_THREAD_STATE> m_thread;

		//Fusion: declare pointer to array of pointers to isolation aware dll wrappers (ex: comctl32).
		//CDllIsolationWrapperBase **m_pDllIsolationWrappers;
		//Defaults to TRUE. When FALSE - MFC will not activate context in AFX_MAINTAIN_STATE2 (used by AFX_MANAGE_STATE).
		BOOL	m_bSetAmbientActCtx;
		//Handle of the module context.
		HANDLE	m_hActCtx;
		//void CreateActivationContext();

		// bool indicating the return value of InitNetworkAddressControl() (from shell32.dll)
		BOOL m_bInitNetworkAddressControl;
		// bool indicating whether or not InitNetworkAddressControl() (from shell32.dll) have been called for CNetAddressCtrl
		BOOL m_bInitNetworkAddressControlCalled;

		CIUIProject *m_pProject;
	};

#define _AFX_TEMP_CLASS_NAME_SIZE 96
	class _IUI_THREAD_STATE : public IUIAPI CIUINoTrackObject
	{
	public:
		_IUI_THREAD_STATE();
		virtual ~_IUI_THREAD_STATE();

		// override for m_pModuleState in _AFX_APP_STATE
		IUI_MODULE_STATE *m_pModuleState;
		IUI_MODULE_STATE *m_pPrevModuleState;

		// memory safety pool for temp maps
		void *m_pSafetyPoolBuffer;    // current buffer

		// thread local exception context
		//AFX_EXCEPTION_CONTEXT m_exceptionContext;

		// Window create, gray dialog hook, and other hook data
		Window *m_pWndInit;
		CWLWnd *m_pWLWndInit;
		Window *m_pAlternateWndInit;      // special case commdlg hooking
		DWORD m_dwPropStyle;
		DWORD m_dwPropExStyle;
		HWND m_hWndInit;
		HHOOK m_hHookOldCbtFilter;
		HHOOK m_hHookOldMsgFilter;
		fnWLEventHandler m_hHookWLCreate;

		// message pump for Run
		MSG m_msgCur;                   // current message
		CIUIPoint m_ptCursorLast;          // last mouse position
		UINT m_nMsgLast;                // last mouse message

#ifdef _DEBUG
		int m_nDisablePumpCount; // Diagnostic trap to detect illegal re-entrancy
#endif

		// other Window modal data
		MSG m_lastSentMsg;              // see CWnd::WindowProc
		HWND m_hTrackingWindow;         // see CWnd::TrackPopupMenu
		HMENU m_hTrackingMenu;
		TCHAR m_szTempClassName[_AFX_TEMP_CLASS_NAME_SIZE];    // see AfxRegisterWndClass
		HWND m_hLockoutNotifyWindow;    // see CWnd::OnCommand
		BOOL m_bInMsgFilter;

		// other framework modal data
		Window *m_pRoutingView;          // see CCmdTarget::GetRoutingView
		//CPushRoutingView *m_pPushRoutingView;
		//CFrameWnd *m_pRoutingFrame;     // see CCmdTarget::GetRoutingFrame
		//CPushRoutingFrame *m_pPushRoutingFrame;

		// MFC/DB thread-local data
		BOOL m_bWaitForDataSource;

		// OLE control thread-local data
		Window *m_pWndPark;       // "parking space" window
		long m_nCtrlRef;        // reference count on parking window
		BOOL m_bNeedTerm;       // TRUE if OleUninitialize needs to be called

		// IUI Add
		HWLWND m_pWLCapture;			// current windowless window that get the capture.
		HWLWND m_pWLMouseIn;			// current windowless window that mouse in.
		RoutedEventArgs m_LastEvent;

		// TODO: ��������������Ӧ����CIUIWinThread�У�
		// ��ĿǰIUI����֧��CWinApp(��CWinThread����)ģʽ������ʱ�ŵ�_IUI_THREAD_STATE��
		Window *m_pMainWnd;      // main window (usually same AfxGetApp()->m_pMainWnd)
		Window *m_pActiveWnd;     // active main window (may not be m_pMainWnd)
	};

	class IUIAPI CIUIProcessLocalObject
	{
	public:
		// Attributes
		CIUINoTrackObject *GetData(CIUINoTrackObject * (*pfnCreateObject)());

		// Implementation
		CIUINoTrackObject *volatile m_pObject;
		~CIUIProcessLocalObject();
	};

	template<class TYPE>
	class CIUIProcessLocal : public CIUIProcessLocalObject
	{
		// Attributes
	public:
		inline TYPE *GetData()
		{
			TYPE *pData = (TYPE *)CIUIProcessLocalObject::GetData(&CreateObject);
			ENSURE(pData != NULL);
			return pData;
		}
		inline TYPE *GetDataNA()
		{
			return (TYPE *)m_pObject;
		}
		inline operator TYPE *()
		{
			return GetData();
		}
		inline TYPE *operator->()
		{
			return GetData();
		}

		// Implementation
	public:
		static CIUINoTrackObject *CreateObject()
		{
			return new TYPE;
		}
	};

	extern CIUIThreadLocal<_IUI_THREAD_STATE> _iuiThreadState;

	_IUI_THREAD_STATE *IUIAPI IUIGetThreadState();


	IUI_MODULE_STATE *IUIAPI IUIGetModuleState();
#define iuiCurrentInstanceHandle    IUIGetModuleState()->m_hCurrentInstanceHandle
#define iuiCurrentWinApp    IUIGetModuleState()->m_pCurrentWinApp
#define iuiCurrentInstanceHandle    IUIGetModuleState()->m_hCurrentInstanceHandle
#define iuiCurrentResourceHandle    IUIGetModuleState()->m_hCurrentResourceHandle
#define iuiCurrentAppName   IUIGetModuleState()->m_lpszCurrentAppName
#define iuiContextIsDLL     IUIGetModuleState()->m_bDLL
#define iuiRegisteredClasses    IUIGetModuleState()->m_fRegisteredClasses
#define iuiAmbientActCtx    IUIGetModuleState()->m_bSetAmbientActCtx

	inline HINSTANCE IUIAPI IUIGetInstanceHandle()
	{
		IUI_MODULE_STATE *pState = IUIGetModuleState();
		_ASSERT(pState->m_hCurrentInstanceHandle != NULL);
		return pState->m_hCurrentInstanceHandle;
	}
	inline HINSTANCE IUIAPI IUIGetResourceHandle()
	{
		_ASSERT(iuiCurrentResourceHandle != NULL);
		return iuiCurrentResourceHandle;
	}
	inline void IUIAPI IUISetResourceHandle(HINSTANCE hInstResource)
	{
		_ASSERT(hInstResource != NULL);
		iuiCurrentResourceHandle = hInstResource;
	}
	inline LPCTSTR IUIAPI IUIGetAppName()
	{
		_ASSERT(iuiCurrentAppName != NULL);
		return iuiCurrentAppName;
	}

	IUI_MODULE_THREAD_STATE *IUIAPI IUIGetModuleThreadState();
	CIUIWinThread *IUIAPI IUIGetThread();

	inline Window *IUIAPI IUIGetMainWnd()
	{
		_IUI_THREAD_STATE *pThreadState = IUIGetThreadState();
		return pThreadState != NULL ? pThreadState->m_pMainWnd : NULL;

		// TODO: Ӧ��ʹ������Ĵ��룬��ĿǰIUI��֧��CIUIWinThreadģʽ��
		CIUIWinThread *pThread = IUIGetThread();
		return pThread != NULL ? pThread->GetMainWnd() : NULL;
	}

	void IUIAPI IUIInitThread();

	BOOL IUIAPI IUIInit(
		__in HINSTANCE hInstance,
		__in HINSTANCE hPrevInstance,
		__in LPTSTR lpCmdLine,
		__in int nCmdShow);

	BOOL IUIAPI IUIUninit();

	std::map<HWND, Window *> *IUIAPI iuiMapHWND(BOOL bCreate = FALSE);
	std::map<HWND, std::set<void *> > *IUIAPI iuiMapSubclass(BOOL bCreate = FALSE);
	std::map<UINT_PTR, HTIMER> *IUIAPI iuiMapTimer(BOOL bCreate = FALSE);

#ifndef AFX_STATIC
#define AFX_STATIC extern
#define AFX_STATIC_DATA extern __declspec(selectany)
#endif

#define CRIT_PROCESSLOCAL   16
#define CRIT_MAX    17  // Note: above plus one!
	void IUIAPI IUICriticalTerm();
	void IUIAPI IUILockGlobals(int nLockType);
	void IUIAPI IUIUnlockGlobals(int nLockType);
	void IUIAPI IUITermLocalData(HINSTANCE hInst, BOOL bAll);
	void IUIAPI IUITlsRelease();

	class IUIAPI GLOBALVAR
	{
	public:
		GLOBALVAR();
		~GLOBALVAR();

		BOOL g_fSmoothScroll;

		CIUIString c_szNULL;
		CIUIString c_szEllipses;
		CIUIString c_szHeaderClass;
		CIUIString c_szSelect;
		CIUIString c_szSpace;

		COLORREF g_clrBtnFace;
		COLORREF g_clrWindow;
		COLORREF g_clrHighlight;
		COLORREF g_clrHighlightText;
		COLORREF g_clrBtnText;
		COLORREF g_clrWindowText;
		COLORREF g_clrGrayText;
		HBRUSH g_hbrHighlight;
		HBRUSH g_hbrBtnFace;
		HBRUSH g_hbrWindow;

		int g_cxBorder;
		int g_cyBorder;
		int g_cxScrollbar;
		int g_cyScrollbar;
		int g_cxVScroll;
		int g_cyVScroll;
		int g_cxHScroll;
		int g_cyHScroll;
		int g_cxIcon;
		int g_cyIcon;
		int g_cxEdge;
		int g_cyEdge;
		int g_cxIconSpacing;
		int g_cyIconSpacing;
		int g_cxFrame;
		int g_cyFrame;

		int g_cxLabelMargin;
		UINT g_uDragImages;
		UINT g_msgMSWheel;
		int g_fDBCSInputEnabled;
		int g_fDBCSEnabled;
		int gcWheelDelta;
		UINT g_ucScrollLines;
		int g_cxIconMargin;
		int g_cyIconMargin;

		DWORD dwExStyleRTLMirrorWnd;
		UINT g_uiACP;
		int g_cyLabelSpace;
		HANDLE g_hSharedHeap;

		COLORREF g_clrInfoText;
		COLORREF g_clrInfoBk;

		int g_cxDoubleClk;
		HBRUSH g_hbrWindowText;
		HBRUSH g_hbrGrayText;
		HFONT g_hfontSystem;
	};
	namespace DPI
	{
		bool IsEnableDPI();
		int GetDPIRect(__inout LPRECT lprc);
		int GetDPIPadding(__inout LPRECT lprc);
		int GetDPIWidth(__in int nWidth);
		int GetDPIHeight(__in int nHeight);

	} // namespace DPI

	/////////////////////////////////////////////////////////////////////////////////////
	// function

	namespace CreateControls
	{
		DWORD GetControlBaseStyle(const CControlProp *pCtrlProp);

		// Create controls.
		HWLWND CreateLabel(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CLabelProp *pSta,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateButton(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CButtonProp *pBtn,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateCheckBox(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CCheckBoxProp *pChk,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateRadioButton(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CRadioButtonProp *pRad,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateComboBox(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CComboBoxProp *pCmb,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateListView(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CListViewProp *pList,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateSpinButton(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CSpinButtonProp *pSpinProp,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateProgressBar(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CProgressBarProp *pPrg,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateSlider(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CSliderProp *pSld,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		//CSkinHotKeyCtrl *CreateHotKey(__inout CWLWndHandler *pUserHandler,HOTPROPERTIES *pHot, HWLWND hWLParent, LPARAM lCreateParam);
		//CSkinIPAddressCtrl *CreateIPAddress(__inout CWLWndHandler *pUserHandler,IPAPROPERTIES *pIPA, HWLWND hWLParent, LPARAM lCreateParam);
		HWLWND CreateTreeView(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CTreeViewProp *pTree,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateRichTextBox(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CRichTextBoxProp *pRichEdt,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateIM(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CIMRichTextBoxProp *pIMProp,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		//CTreeListCtrl *CreateTreeList(TREELISTPROPERTIES *pTreeList, HWLWND hWLParent, LPARAM lCreateParam);
		HWLWND CreateHtmlView(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CHtmlViewProp *pHtmlViewProp,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateSplitterBar(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CSplitterBarProp *pSplitterProp,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateDateTimePicker(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CDateTimePickerProp *pDateTimeCtrlProp,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		//CMenuBar *CreateMenuBar(__inout CWLWndHandler *pUserHandler,MENUBARPROPERTIES *pMenuBar, HWLWND hWLParent, LPARAM lCreateParam);
		//CSplitterBar *CreateSplitter(__inout CWLWndHandler *pUserHandler,SPLITTERPROPERTIES *pSplitter, HWLWND hWLParent, LPARAM lCreateParam);
		HWLWND CreateCanvas(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CCanvasProp *pCanvas,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateTabControl(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CTabControlProp *pTabControlProp,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateDockPanel(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CDockPanelProp *pDockPanelProp,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);
		HWLWND CreateStackPanel(
			__inout CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CStackPanelProp *pStackPanelProp,
			HWND hHost,
			HWLWND hWLParent,
			LPARAM lCreateParam
		);

		// ����IUI���õĿؼ�������ؼ����ӿؼ���Ҳ��һ�𱻴�������
		HWLWND IUIAPI CreatePreDefineChildControl(
			CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			CControlProp *pCtrlProp,
			HWLWND hParent,
			HWND hHost,
			LPARAM lCreateParam
		);

		// ����ָ��XML�ļ����ѵ�һ�����Ӵ����ɿؼ�
		HWLWND CreateXMLWindowChild(
			CWLWndHandler *pUserHandler,
			HINSTANCE hInst,
			LPCTSTR lpszXML,
			HWLWND hParent,
			HWND hHost,
			LPARAM lCreateParam
		);

	} // namespace CreateControls

	namespace Metrics
	{
		extern COLORREF g_crButtonBkN;
		extern COLORREF g_crButtonBkH;
		extern COLORREF g_crButtonBkS;
		extern COLORREF g_crButtonBkD;
		extern COLORREF g_crButtonBkCN;
		extern COLORREF g_crButtonBkCH;
		extern COLORREF g_crButtonBkCS;
		extern COLORREF g_crButtonBkCD;
		extern COLORREF g_crButtonBorderN;
		extern COLORREF g_crButtonBorderH;
		extern COLORREF g_crButtonBorderS;
		extern COLORREF g_crButtonBorderD;
		extern COLORREF g_crButtonBorderCN;
		extern COLORREF g_crButtonBorderCH;
		extern COLORREF g_crButtonBorderCS;
		extern COLORREF g_crButtonBorderCD;

		// ��������ť������ɫ
		extern COLORREF g_crScrollButtonBkN;
		extern COLORREF g_crScrollButtonBkH;
		extern COLORREF g_crScrollButtonBkP;
		extern COLORREF g_crScrollButtonBkD;
		// �����������ɫ
		extern COLORREF g_crScrollGroove;
		// ������������ɫ
		extern COLORREF g_crScrollThumbBkN;
		extern COLORREF g_crScrollThumbBkH;
		extern COLORREF g_crScrollThumbBkP;
		extern COLORREF g_crScrollThumbBkD;

		extern const CScrollBarProp *g_pHorScrollBarBindProp;
		extern const CScrollBarProp *g_pVerScrollBarBindProp;
		extern int g_nScrollBarWidth;

		// ȫ��ʹ������������
		extern BOOL g_bFloatScrollBar;

		void InitWin10Style();

		COLORREF GetButtonBkColorN();
		COLORREF GetButtonBkColorH();
		COLORREF GetButtonBkColorS();
		COLORREF GetButtonBkColorD();

		COLORREF GetButtonBkColorCN();
		COLORREF GetButtonBkColorCH();
		COLORREF GetButtonBkColorCS();
		COLORREF GetButtonBkColorCD();

		COLORREF GetButtonBorderColorN();
		COLORREF GetButtonBorderColorH();
		COLORREF GetButtonBorderColorS();
		COLORREF GetButtonBorderColorD();

		COLORREF GetButtonBorderColorCN();
		COLORREF GetButtonBorderColorCH();
		COLORREF GetButtonBorderColorCS();
		COLORREF GetButtonBorderColorCD();

		COLORREF GetScrollButtonBkColorN();
		COLORREF GetScrollButtonBkColorH();
		COLORREF GetScrollButtonBkColorP();
		COLORREF GetScrollButtonBkColorD();

		COLORREF GetScrollGrooveColor();

		COLORREF GetScrollThumbBkColorN();
		COLORREF GetScrollThumbBkColorH();
		COLORREF GetScrollThumbBkColorP();
		COLORREF GetScrollThumbBkColorD();

		void SetFloatScrollBar(BOOL bSet);
		BOOL IsFloatScrollBar();

		void SetHorScrollBarBindStyle(const CScrollBarProp *pBindProp);
		const CScrollBarProp *GetHorScrollBarBindStyle();
		void SetVerScrollBarBindStyle(const CScrollBarProp *pBindProp);
		const CScrollBarProp *GetVerScrollBarBindStyle();

		void SetScrollBarWidth(int nWidth);
		int GetScrollBarWidth();

	} // namespace Metrics

	// Verify that a pointer points to valid memory
	BOOL IUIAPI IUIIsValidAddress(const void *p, size_t nBytes, BOOL bReadWrite = TRUE);
	// Verify that a null-terminated string points to valid memory
	BOOL IUIAPI IUIIsValidStringA(LPCSTR psz, size_t nMaxLength = UINT_MAX);
	BOOL IUIAPI IUIIsValidStringW(LPCWSTR psz, size_t nMaxLength = UINT_MAX);
#ifdef _UNICODE
#define IUIIsValidString IUIIsValidStringW
#else
#define IUIIsValidString IUIIsValidStringA
#endif

	errno_t IUIAPI IUICopyMemory(
		void *dest,
		size_t numberOfElements,
		const void *src,
		size_t count);

	errno_t IUIAPI IUIStringCopy(
		TCHAR *_Dest,
		size_t _SizeInChars,
		const TCHAR *_Source,
		size_t _Count);

	void IUIAPI InitPdata(WCHAR **pDest, CIUIString str);

	CIUIString IUIAPI StringFromInt(int nValue);
	CIUIString IUIAPI StringFromUINT(UINT n);

	// IntFromString returns the converted value, if any, or ULONG_MAX on overflow
	unsigned long IUIAPI UINTFromString(LPCTSTR lpString);
	unsigned long IUIAPI UINTFromHexString(LPCTSTR lpString);

	// IntFromString returns the value represented in the string strValue,
	// except when the representation would cause an overflow,
	// in which case it returns LONG_MAX or LONG_MIN.
	// IntFromString returns 0 if no conversion can be performed
	int IUIAPI IntFromString(LPCTSTR lpString);
	int IUIAPI IntFromHexString(LPCTSTR lpString);

	long IUIAPI LongFromString(LPCTSTR lpString);

	CIUIString IUIAPI GetExecutePath();
	// ����ļ�·��
	int IUIAPI TSPLITPATH(LPCTSTR path,
		LPTSTR drive, size_t driveSizeInCharacters,
		LPTSTR dir, size_t dirSizeInCharacters,
		LPTSTR fname, size_t nameSizeInCharacters,
		LPTSTR ext, size_t extSizeInBytes);

	void IUIAPI TMAKEPATH(
		LPTSTR path,
		size_t sizeInBytes,
		LPCTSTR drive,
		LPCTSTR dir,
		LPCTSTR fname,
		LPCTSTR ext);

	// �õ��ļ���չ��
	CIUIString IUIAPI GetFileExt(const CIUIString &strFile, BOOL bHasDot = TRUE);

	int IUIAPI StretchAlphaBlend(
		HDC hdcDest,
		int nXOriginDest, int nYOriginDest, int nDestWidth, int nDestHeight,
		HDC hdcSrc,
		int nXOriginSrc, int nYOriginSrc, int nSrcWidth, int nSrcHeight,
		BOOL bAlphaFormat = TRUE,
		BYTE btSourceConstantAlpha = 255);

	int IUIAPI StretchAlphaBlendImage(
		HDC hdcDest,
		LPCRECT lprcDest,
		HBITMAP hbmpSrc,
		LPCRECT lprcSrc,
		BYTE btSourceConstantAlpha = 255);

	Gdiplus::Bitmap *CreateBitmapFromHBITMAP(HBITMAP hBitmap);

	HBITMAP IUIAPI Create32BitsHBITMAP(int nWidth, int nHeight, int nBPP, DWORD eCompression,
		void **m_ppBits, const DWORD *pdwBitmasks = NULL, DWORD dwFlags = 0);
	int IUIAPI CopyHBITMAP(HBITMAP hbmpSrc, HBITMAP *phbmpDest, BOOL bAlphaFormat);

	HWND IUIAPI GetSafeOwner_(HWND hParent, HWND *pWndTop);

	BOOL IUIAPI AfxExtractSubStringA(
		std::string *pString,
		LPCSTR lpszFullString,
		int nFullStringCount,
		int iSubString,
		CHAR chSep);

	BOOL IUIAPI AfxExtractSubStringW(
		std::wstring *pString,
		LPCWSTR lpszFullString,
		int nFullStringCount,
		int iSubString,
		WCHAR chSep);

	void IUIAPI JG_DPIEnableDPI(BOOL);
	int IUIAPI JG_DPIGetDPILogFont(LOGFONT *plf, BOOL bDPI);
	RECT IUIAPI JG_DPIGetDPIRect(RECT rcSrc, BOOL bDPI);
	RECT IUIAPI JG_DPIGetDPIPadding(RECT rcSrc, BOOL bDPI);
	SIZE JG_DPIGetDPISize(SIZE sizeSrc, BOOL bDPI);
	BOOL IUIAPI JG_DPIIsSmoothStretch(BOOL bDPI);
	int IUIAPI JG_DPIGetDPIPointX(int nSrc, BOOL bDPI);
	int IUIAPI JG_DPIGetDPIPointY(int nSrc, BOOL bDPI);
	int IUIAPI JG_DPIGetDPIWidth(int nSrc, BOOL bDPI);
	int IUIAPI JG_DPIGetDPIHeight(int nSrc, BOOL bDPI);

	int IUIAPI FillSolidRect(HDC hDC, LPCRECT lpRect, COLORREF clr, BOOL bUseGdiplus);
	int IUIAPI FillSolidRect(HDC hDC, int x, int y, int cx, int cy, COLORREF clr, BOOL bUseGdiplus);

	// Bind Style
	int IUIAPI HWLWND_BindStyle(HWLWND hWnd, const CControlProp *pCtrlProp);
	int IUIAPI ScrollBar_BindStyle(HWLWND hWnd, const CScrollBarProp *pProp);
	int IUIAPI Label_BindStyle(HWLWND hWnd, const CLabelProp *pCtrlProp);
	int IUIAPI PushButton_BindStyle(HWLWND hWnd, const CButtonProp *pProp);
	int IUIAPI ToggleButton_BindStyle(HWLWND hWnd, const CToggleButtonProp *pCtrlProp);
	int IUIAPI ComboBox_BindStyle(HWLWND hWnd, const CComboBoxProp *pCtrlProp);
	int IUIAPI ListView_BindStyle(HWLWND hWnd, const CListViewProp *pCtrlProp);
	int IUIAPI TreeView_BindStyle(HWLWND hWnd, const CTreeViewProp *pCtrlProp);
	int IUIAPI RichTextBox_BindStyle(HWLWND hWnd, const CRichTextBoxProp *pCtrlProp);
	int IUIAPI IMRichTextBox_BindStyle(HWLWND hWnd, const CIMRichTextBoxProp *pCtrlProp);
	int IUIAPI ProgressBar_BindStyle(HWLWND hWnd, const CProgressBarProp *pCtrlProp);
	int IUIAPI Slider_BindStyle(HWLWND hWnd, const CSliderProp *pCtrlProp);
	int IUIAPI HtmlView_BindStyle(HWLWND hWnd, const CHtmlViewProp *pCtrlProp);
	int IUIAPI SplitterBar_BindStyle(HWLWND hWnd, const CSplitterBarProp *pCtrlProp);
	int IUIAPI DateTimePicker_BindStyle(HWLWND hWnd, const CDateTimePickerProp *pCtrlProp);
	int IUIAPI SpinButton_BindStyle(HWLWND hWnd, const CSpinButtonProp *pCtrlProp);
	int IUIAPI Canvas_BindStyle(HWLWND hWnd, const CCanvasProp *pCtrlProp);
	int IUIAPI DockPanel_BindStyle(HWLWND hWnd, const CDockPanelProp *pCtrlProp);
	int IUIAPI TabControl_BindStyle(HWLWND hWnd, const CTabControlProp *pCtrlProp);
	int IUIAPI StackPanel_BindStyle(HWLWND hWnd, const CStackPanelProp *pCtrlProp);

	/////////////////////////////////////////////////////////////////////

	BOOL IUIPreTranslateMessage(MSG *pMsg);

	BOOL IUIAPI SetProp(HWLWND hCtrl, LPCTSTR lpString, HANDLE hData);
	HANDLE IUIAPI GetProp(HWLWND hCtrl, LPCTSTR lpString);
	HANDLE IUIAPI RemoveProp(HWLWND hCtrl, LPCTSTR lpString);

	HWND IUIAPI SetToolTips(HWLWND hWnd, HWND pWndTip);
	HWND IUIAPI GetToolTips(HWLWND hWnd);

	typedef FILE *TFILE;
	TFILE IUIAPI TFOPEN(LPCTSTR filename, LPCTSTR mode);
	CIUIString IUIAPI StringFromVariant(const _variant_t &rVariant);

	// UTF16 means Unicode or wide char.
	std::wstring IUIAPI MultiByteToUTF16(LPCSTR lpMultiByteStr, int cbMultiByte, UINT uCodePage);
	BOOL IUIAPI IsStringExist(const std::vector<CIUIString> *pvStrings, const CIUIString &rString, BOOL bNoCase);
	CIUIString IUIAPI GetControlTypeString(CONTROL_TYPE eControlType, BOOL bInCode = FALSE);
	BOOL IUIAPI ExtractSubString(CIUIString &rString, LPCTSTR lpszFullString, int iSubString, TCHAR chSep);
	int IUIAPI LoadCustomResourceA(LPCSTR lpszResName, LPCSTR lpType, LPVOID *lpData, DWORD *pdwSize);

	BOOL IUIAPI IsIncludeFlag(UINT uFlags, UINT uFlag);
	int IUIAPI IUIClientToScreen(HWND hWnd, LPRECT lpRect);
	int IUIAPI IUIScreenToClient(HWND hWnd, LPRECT lpRect);

	void IUIAPI DUI__Trace(LPCTSTR pstrFormat, ...);

	typedef GLOBALVAR *HGLOBALVAR;
	HGLOBALVAR IUIAPI IUIGetGloabelVar();

	CIUIString IUIAPI GetRunFolder();

	CIUIString IUIAPI GetFileDrive(LPCTSTR lpszFullPath);    // return drive name.
	CIUIString IUIAPI GetFilePath(LPCTSTR lpszFullPath);    // return only path, not include title and ext.
	CIUIString IUIAPI GetFileName(LPCTSTR lpszFullPath);    // return title and ext.

	CIUIString IUIAPI IUIGetFileTitle(LPCTSTR lpszFullPath);
	std::wstring IUIAPI GetFileTitleExW(LPCWSTR lpszFile);	// return only title, not include ext.
	std::wstring IUIAPI GetFileExtW(LPCWSTR lpszFile, BOOL bHasDot);		// return ext.

	int MakeControlMargin(
		HWND hParent,
		HWLWND pParent,
		int x,
		int y,
		int nWidth,
		int nHeight,
		__out LPRECT lprcMargin
	);
	int MakeControlMargin(
		HWND hParent,
		HWLWND pParent,
		__in LPCRECT lprcControl,
		__out LPRECT lprcMargin
	);

	// ��Canvas�����㷨����ؼ��޹�
	int IUIAPI CanvasLayout(
		LPCRECT lprcCtrlOld,
		CONTROL_LAYOUT_HOR eControlLayoutHor,
		CONTROL_LAYOUT_VER eControlLayoutVer,
		LPCRECT lprcCtrlMargin,
		LPCRECT lprcLayoutMargin,
		int nParentWidth,
		int nParentHeight,
		OUT LPRECT lprcNew
	);

	// �ѿؼ���Cancas��ʽ����
	int IUIAPI CanvasLayoutElement(
		HWLWND hCtrl,
		int nParentWidth,
		int nParentHeight,
		OUT CIUIRect &rcNew
	);
	int IUIAPI CanvasLayoutCtrl(HWLWND hWnd);
	int IUIAPI CanvasLayoutWindow(HWND hWnd, BOOL bExcludeTaskBar, __out LPRECT lprcNew);

	// �ѿؼ���StackPanel��ʽ����
	int IUIAPI StackPanelLayoutElement(
		HWLWND hPrevVisibleCtrl,	// ��һ�����ӵ��ֵܿؼ�
		HWLWND hCtrl,
		int nParentWidth,
		int nParentHeight,
		OUT CIUIRect &rcNew);
	int IUIAPI StackPanelLayoutCtrl(HWLWND hPrevVisiableCtrl, HWLWND hWnd);

	int IUIAPI GetChildren(const CControlProp *pParent,
		std::vector<const CControlProp *> *pvpChilren);


	/////////////////////////////////////////////////////////////////////////////
	// HWLWND Core
	HWLWND IUIAPI CreateWindowEx(
		CWLWndHandler *pUserHandler,
		DWORD dwExStyle,
		LPCTSTR lpClassName,
		LPCTSTR lpWindowName,
		DWORD dwStyle,
		int x,
		int y,
		int nWidth,
		int nHeight,
		HWND hWndParent,
		HWLWND hWlWndParent,
		LPCTSTR lpszName,
		HINSTANCE hInstance,
		LPVOID lpParam
	);

	BOOL IUIAPI DestroyWindow(HWLWND hWnd);
	BOOL IUIAPI IsWindow(HWLWND hWnd);
	HWLWND IUIAPI SetParent(HWLWND hWndChild, HWLWND hWndNewParent);
	HWLWND IUIAPI GetParent(HWLWND hWnd);
	// ����Parent
	HWLWND IUIAPI GetOwner(HWLWND hWnd);
	int IUIAPI SetZOrder(HWLWND hWnd, HWLWND hAfter);
	CIUIString IUIAPI SetName(HWLWND hWnd, LPCTSTR pstrName);
	CIUIString IUIAPI GetName(HWLWND hWnd);
	int IUIAPI SetNotify(HWLWND hWnd, BOOL bNotify);
	BOOL IUIAPI IsNotify(HWLWND hWnd);
	LONG IUIAPI SetStyle(HWLWND hWnd, LONG lStyle);
	LONG IUIAPI GetStyle(HWLWND hWnd);
	LONG IUIAPI AddStyle(HWLWND hWnd, LONG lAdd);
	LONG IUIAPI RemoveStyle(HWLWND hWnd, LONG lRemove);
	LONG IUIAPI SetExStyle(HWLWND hWnd, LONG lExStyle);
	LONG IUIAPI GetExStyle(HWLWND hWnd);
	LONG IUIAPI AddExStyle(HWLWND hWnd, LONG lAdd);
	LONG IUIAPI RemoveExStyle(HWLWND hWnd, LONG lRemove);
	// ֻ����õ�Host���ھ��������������Host���ھ�����ؼ���Host�����������ؼ���ȡ��
	// ��������ؼ�����������ָ��Ϊ����Host���ڵ�������ؼ�
	HWND IUIAPI GetHostWnd(HWLWND hWnd);
	CIUIString IUIAPI GetClassName(HWLWND hWnd);
	int IUIAPI GetClassName(HWLWND hWnd, LPTSTR lpClassName, int nMaxCount);
	int IUIAPI SetDlgCtrlID(HWLWND hWnd, int nID);
	int IUIAPI GetDlgCtrlID(HWLWND hWnd);
	CIUIProject *IUIAPI GetProject(HWLWND hWnd);
	HWLWND IUIAPI SetCapture(HWLWND hWnd);
	HWLWND IUIAPI GetCapture(HWLWND hWnd);
	BOOL IUIAPI ReleaseCapture(HWLWND hWnd);
	HWLWND IUIAPI GetTopLevelWindow(HWLWND hWnd);
	int GetWindowTextLength(HWLWND hWnd);
	CIUIString IUIAPI GetWindowText(HWLWND hWnd);
	int IUIAPI GetWindowText(HWLWND hWnd, LPTSTR lpString, int nMaxCount);
	BOOL IUIAPI SetWindowText(HWLWND hWnd, LPCTSTR pstrText);
	BOOL IUIAPI SetResText(HWLWND hWnd, HINSTANCE hRes, UINT uID);
#if (_MSC_VER > 1200)	// VC6.0
	BOOL IUIAPI SetXResText(HWLWND hWnd, HXSRESOURCE hXRes, LPCTSTR lpszSectionID, LPCTSTR lpszStringID);
#endif // #if (_MSC_VER > 1200)	// VC6.0
	RECT IUIAPI GetTextPadding(HWLWND hWnd);
	int IUIAPI SetTextPadding(HWLWND hWnd, RECT rc);
	int IUIAPI SetTextColor(HWLWND hWnd, COLORREF crN, COLORREF crD);
	int IUIAPI GetTextColor(HWLWND hWnd, COLORREF *pcrN, COLORREF *pcrD);

	BOOL IUIAPI SetDrawBkColor(HWLWND hWnd, BOOL bDraw);
	BOOL IUIAPI IsDrawBkColor(HWLWND hWnd);
	int IUIAPI SetBkColor(HWLWND hWnd, COLORREF crBkN, COLORREF crBkD);
	int IUIAPI GetBkColor(HWLWND hWnd, COLORREF *pcrBkN, COLORREF *pcrBkD);

	BOOL IUIAPI CombineBkImage(HWLWND hWnd, BOOL bCombine);
	BOOL IUIAPI IsCombineBkImage(HWLWND hWnd);
	int IUIAPI SetCombineBkImage(HWLWND hWnd, LPCTSTR lpszImage);
	int IUIAPI GetCombineBkImage(HWLWND hWnd, CIUIString *pstrCombineImage);

	int IUIAPI SetBkImage(
		HWLWND hWnd,
		BOOL bChecked,
		CONTROL_STATE eControlState,
		LPCTSTR lpszImage
	);
	int IUIAPI GetBkImage(
		HWLWND hWnd,
		BOOL bChecked,
		CONTROL_STATE
		eControlState,
		CIUIString *pstrImage
	);
	int SetBkImageResizeMode(HWLWND hWnd, IMAGE_RESIZE_MODE eImageResizeMode);
	IMAGE_RESIZE_MODE GetBkImageResizeMode(HWLWND hWnd);
	int SetBkImage9GridResizeParam(HWLWND hWnd, LPCRECT lprcParam);
	int GetBkImage9GridResizeParam(HWLWND hWnd, LPRECT lprcParam);

	BOOL IUIAPI CombineFgImage(HWLWND hWnd, BOOL bCombine);
	BOOL IUIAPI IsCombineFgImage(HWLWND hWnd);
	int IUIAPI SetCombineFgImage(HWLWND hWnd, LPCTSTR lpszImage);
	int IUIAPI GetCombineFgImage(HWLWND hWnd, CIUIString *pstrCombineImage);

	int IUIAPI SetFgImage(
		HWLWND hWnd,
		BOOL bChecked,
		CONTROL_STATE eControlState,
		LPCTSTR lpszImage
	);
	int IUIAPI GetFgImage(
		HWLWND hWnd,
		BOOL bChecked,
		CONTROL_STATE
		eControlState,
		CIUIString *pstrImage
	);

	BOOL IUIAPI SetDrawBorderColor(HWLWND hWnd, BOOL bDraw);
	BOOL IUIAPI IsDrawBorderColor(HWLWND hWnd);
	int IUIAPI SetBorderColor(HWLWND hWnd, COLORREF crN, COLORREF crD);
	int IUIAPI GetBorderColor(HWLWND hWnd, COLORREF *pcrN, COLORREF *pcrD);

	DWORD IUIAPI GetFocusBorderColor(HWLWND hWnd);
	void IUIAPI SetFocusBorderColor(HWLWND hWnd, DWORD dwBorderColor);
	int IUIAPI SetBorderRect(HWLWND hWnd, const RECT &rcBorder);
	CIUIRect IUIAPI GetBorderRect(HWLWND hWnd);
	void IUIAPI SetBorderRound(HWLWND hWnd, SIZE cxyRound);
	SIZE IUIAPI GetBorderRound(HWLWND hWnd);

	int IUIAPI SetWindowRgn(HWLWND hWnd, HRGN hRgn, BOOL bRedraw);
	int IUIAPI GetWindowRgn(HWLWND hWnd, HRGN hRgn);

	int IUIAPI RelayoutChild(HWLWND hWnd);

	void IUIAPI EnableDPI(HWLWND hWnd, BOOL bEnable);
	BOOL IUIAPI IsDPIEnabled(HWLWND hWnd);

	const CIUIRect &IUIAPI GetWindowRectToParent(HWLWND hWnd);
	int IUIAPI GetWindowRectToParent(HWLWND hWnd, LPRECT lprc);
	int IUIAPI GetWindowRectFToParent(HWLWND hWnd, Gdiplus::RectF *pRect);
	int IUIAPI ClientToScreen(HWLWND hWnd, LPRECT lpRect);
	int IUIAPI ClientToScreen(HWLWND hWnd, LPPOINT lpPt);
	int IUIAPI ScreenToClient(HWLWND hWnd, LPRECT lpRect);
	int IUIAPI ScreenToClient(HWLWND hWnd, LPPOINT lpPt);
	void IUIAPI MoveWindow(HWLWND hWnd, int x, int y, int nWidth, int nHeight, BOOL bRepaint);
	void IUIAPI MoveWindow(HWLWND hWnd, LPCRECT lpRect, BOOL bRepaint);
	BOOL IUIAPI SetWindowPos(HWLWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
	int IUIAPI GetClientRect(HWLWND hWnd, LPRECT lpRect);
	int IUIAPI GetWindowRect(HWLWND hWnd, LPRECT lpRect);
	int IUIAPI GetWindowRectToHWND(HWLWND hWnd, LPRECT lpRect);
	void IUIAPI SetFixedWidth(HWLWND hWnd, int cx);
	int IUIAPI GetFixedWidth(HWLWND hWnd);
	void IUIAPI SetFixedHeight(HWLWND hWnd, int cy);
	int IUIAPI GetFixedHeight(HWLWND hWnd);
	BOOL IUIAPI IsFixedWidth(HWLWND hWnd);
	BOOL IUIAPI IsFixedHeight(HWLWND hWnd);
	void IUIAPI ClearFixedWidth(HWLWND hWnd);
	void IUIAPI ClearFixedHeight(HWLWND hWnd);
	void IUIAPI SetMinWidth(HWLWND hWnd, int cx);
	int IUIAPI GetMinWidth(HWLWND hWnd);
	void IUIAPI SetMaxWidth(HWLWND hWnd, int cx);
	int IUIAPI GetMaxWidth(HWLWND hWnd);
	void IUIAPI SetMinHeight(HWLWND hWnd, int cy);
	int IUIAPI GetMinHeight(HWLWND hWnd);
	void IUIAPI SetMaxHeight(HWLWND hWnd, int cy);
	int IUIAPI GetMaxHeight(HWLWND hWnd);
	int IUIAPI SetTitleBarHeight(HWLWND hWnd, int nHeight);
	int IUIAPI GetTitleBarHeight(HWLWND hWnd);
	int IUIAPI SetBorderThickness(HWLWND hWnd, LPCRECT lprcBorder);
	int IUIAPI GetBorderThickness(HWLWND hWnd, LPRECT lprcBorder);
	// ��XML�е�ԭʼ������Ը��ؼ��ĸ��ߵı߾�
	// ע������m_rcLayoutMargin�����߶����������ֵģ��ڲ���ʱ�����ߵ�ֵ���е��ӡ�
	// ����ؼ���m_rcControlMargin.left��ֵΪ5��m_rcLayoutMargin.left��ֵΪ10��
	// ����ؼ���ˮƽ���뷽ʽ��Left����ؼ���Canvas��left������ֵΪ15.
	// m_rcLayoutMargin���m_rcControlMargin�Ƕ�����������֡�
	int IUIAPI SetControlMargin(HWLWND hWnd, LPCRECT lprc);
	int IUIAPI GetControlMargin(HWLWND hWnd, LPRECT lprc);
	Gdiplus::RectF *IUIAPI GetRectF(HWLWND hWnd);
	UINT IUIAPI SetResizeFlag(HWLWND hWnd, UINT uFlag);
	UINT IUIAPI GetResizeFlag(HWLWND hWnd);
	int IUIAPI HitTest(HWLWND hWnd, LPPOINT lpScreenPoint);
	BOOL IUIAPI SetMouseTransparent(HWLWND hWnd, BOOL bMouseTransparent);
	BOOL IUIAPI IsMouseTransparent(HWLWND hWnd);
	CONTROL_LAYOUT_HOR IUIAPI SetHorzLayoutMode(HWLWND hWnd, CONTROL_LAYOUT_HOR eLayout);
	CONTROL_LAYOUT_HOR IUIAPI GetHorzLayoutMode(HWLWND hWnd);
	CONTROL_LAYOUT_VER IUIAPI SetVertLayoutMode(HWLWND hWnd, CONTROL_LAYOUT_VER eLayout);
	CONTROL_LAYOUT_VER IUIAPI GetVertLayoutMode(HWLWND hWnd);
	DOCK IUIAPI SetDockProperty(HWLWND hWnd, DOCK eNewDock);
	DOCK IUIAPI GetDockProperty(HWLWND hWnd);
	int IUIAPI SetLayoutMargin(HWLWND hWnd, LPCRECT lprcMargin);
	int IUIAPI GetLayoutMargin(HWLWND hWnd, LPRECT lprcMargin);
	int IUIAPI SetLayoutInset(HWLWND hWnd, LPCRECT lprcInset);
	int IUIAPI GetLayoutInset(HWLWND hWnd, LPRECT lprcInset);
	BOOL IUIAPI IsWindowVisible(HWLWND hWnd);
	// �ж����Ѽ������Ƿ񶼿ɼ���ֻҪ��һ�����ɼ����ͷ���FALSE
	BOOL IUIAPI IsAncestryVisible(HWLWND hWnd);
	SIZE IUIAPI EstimateSize(HWLWND hWnd);

	BOOL IUIAPI ShowWindow(HWLWND hWnd, int nCmdShow);
	BOOL IUIAPI EnableWindow(HWLWND hWnd, BOOL bEnabled);
	BOOL IUIAPI IsWindowEnabled(HWLWND hWnd);

	void IUIAPI SetToolTip(HWLWND hWnd, LPCTSTR pstrText);
	CIUIString IUIAPI GetToolTip(HWLWND hWnd);
	void IUIAPI SetResToolTip(HWLWND hWnd, HINSTANCE hRes, UINT uID);
#if (_MSC_VER > 1200)	// VC6.0
	void IUIAPI SetXResToolTip(HWLWND hWnd, HXSRESOURCE hXRes, LPCTSTR lpszSectionID, LPCTSTR lpszStringID);
#endif // #if (_MSC_VER > 1200)	// VC6.0
	void IUIAPI SetToolTipWidth(HWLWND hWnd, int nWidth);
	int IUIAPI GetToolTipWidth(HWLWND hWnd);

	void IUIAPI SetUserData(HWLWND hWnd, LPARAM lParam);
	LPARAM IUIAPI GetUserData(HWLWND hWnd);
	void IUIAPI SetTag(HWLWND hWnd, LPCTSTR lpszTag);
	LPCTSTR IUIAPI GetTag(HWLWND hWnd);
	UINT IUIAPI SetState(HWLWND hWnd, UINT uState);
	UINT IUIAPI GetState(HWLWND hWnd);
	UINT IUIAPI AddState(HWLWND hWnd, UINT uState);
	UINT IUIAPI RemoveState(HWLWND hWnd, UINT uState);

	HWLWND IUIAPI SetFocus(HWND hHost, HWLWND hWnd);
	BOOL IUIAPI IsFocused(HWLWND hWnd);
	int IUIAPI SetControlState(HWLWND hWnd, CONTROL_STATE eNewState);
	CONTROL_STATE IUIAPI GetControlState(HWLWND hWnd);

	int IUIAPI BindHorzScrollBarStyle(HWLWND hTreeView, const CScrollBarProp *pBindStyle);
	int IUIAPI BindVertScrollBarStyle(HWLWND hTreeView, const CScrollBarProp *pBindStyle);

	HWLWND IUIAPI SetBindItemControlParent(
		HWLWND hBindItemControl,
		HWLWND hParent,
		DWORD_PTR dwBindItemData
	);
	ULONG_PTR IUIAPI GetBindItemControlData(HWLWND hBindItemControl);

	/////////////////////////////////////////////////////
	// Button API
	int IUIAPI Button_SetBindModalDlgID(HWLWND hWnd, UINT uID);
	UINT IUIAPI Button_GetBindModalDlgID(HWLWND hWnd);

	int IUIAPI Button_SetBindModelessWndID(HWLWND hWnd, UINT uID);
	UINT IUIAPI Button_GetBindModelessWndID(HWLWND hWnd);

	int IUIAPI RadioButton_SetBindTabControl(HWLWND hWnd, LPCTSTR lpszTabControlName);
	LPCTSTR IUIAPI RadioButton_GetBindTabControl(HWLWND hWnd);

	int IUIAPI RadioButton_SetBindPropertySheet(HWLWND hWnd, LPCTSTR lpszPropertySheetName);
	LPCTSTR IUIAPI RadioButton_GetBindPropertySheet(HWLWND hWnd);

	// ����/��ȡ��ť�����͡� nButtonTypeȡֵ���£�
	// ����ťΪPushButtonʱ:
	//		0: ���水ť
	//		1: ��С����ť
	//		2: �رհ�ť
	// ����ťΪCheckBoxʱ��
	//		0: ���渴ѡ��
	//		3: ��󻯸�ѡ��
	int IUIAPI Button_SetButtonType(HWLWND hWnd, int nButtonType);
	int IUIAPI Button_GetButtonType(HWLWND hWnd);

	// ���pToolTipsCtrlProp��ΪNULL��ʹ��pToolTipsCtrlProp�����ToolTips��ۣ�����ʹ�ñ�׼���
	int IUIAPI Button_SetToolTips(
		HWLWND hButton,
		const CToolTipCtrlProp *pToolTipsCtrlProp,
		LPCTSTR lpszText
	);

	////////
	// ComboBox API
	int IUIAPI ComboBox_SetDropHeight(HWLWND hComboBox, LONG lHeight);
	int IUIAPI ComboBox_GetDropHeight(HWLWND hComboBox);

	////////
	// TabControl API
	// ������ͷ�CWLWndHandler
#define ALLOC_HANDLER(CLASSNAME) (CLASSNAME *)new (CLASSNAME)
#define RELEASE_HANDLER(handler) delete (handler); (handler) = NULL;

	BOOL IUIAPI TabControl_Remove(HWLWND hWnd, HWLWND hControl);
	int IUIAPI TabControl_RemoveAll(HWLWND hWnd);
	UINT IUIAPI TabControl_GetCurPropertySheet(HWLWND hWnd);
	int IUIAPI TabControl_AddPropertySheet(HWLWND hWnd, UINT uKey, HWLWND hSheet, CWLWndHandler *pUserHandler);
	int IUIAPI TabControl_AddPropertySheet(HWLWND hWnd, HWLWND hRadioButton, HWLWND hSheet, CWLWndHandler *pUserHandler);
	int IUIAPI TabControl_AddPropertySheet(HWLWND hWnd, UINT uKey, LPCTSTR lpszXml, CWLWndHandler *pUserHandler);
	int IUIAPI TabControl_AddPropertySheet(HWLWND hWnd, HWLWND hRadioButton, LPCTSTR lpszXml, CWLWndHandler *pUserHandler);
	int IUIAPI TabControl_SwitchPropertySheet(HWLWND hWnd, UINT uKey);
	int IUIAPI TabControl_SwitchPropertySheet(HWLWND hWnd, HWLWND hRadioButton);
	int IUIAPI TabControl_DetachPropertySheetHandler(HWLWND hWnd, UINT uKey);
	int IUIAPI TabControl_DetachPropertySheetHandler(HWLWND hWnd, HWLWND hRadioButton);
	CPropertySheetInfo *IUIAPI TabControl_FindPropertySheet(HWLWND hWnd, UINT uKey);
	CPropertySheetInfo *IUIAPI TabControl_FindPropertySheet(HWLWND hWnd, HWLWND hRadioButton);
	int IUIAPI TabControl_RelayoutChild(HWLWND hWnd);


	///////
	// ScrollBar API
	// ���ù����ϱ���
	int IUIAPI ScrollBar_SetCombineGrooveImage(HWLWND hSb, LPCTSTR lpszImage);
	// ���ù������ϱ���
	int IUIAPI ScrollBar_SetGrooveImage(
		HWLWND hSb,
		UINT uMask,
		LPCTSTR lpszImageNameN,
		LPCTSTR lpszImageNameH,
		LPCTSTR lpszImageNameP,
		LPCTSTR lpszImageNameD,
		BOOL bRedraw);
	int IUIAPI ScrollBar_SetGrooveImage9GridResizeParam(HWLWND hSb, LPCRECT lpszResize);
	int IUIAPI ScrollBar_GetGrooveImage9GridResizeParam(HWLWND hSb, LPRECT lpszResize);

	int IUIAPI ScrollBar_SetButton1Length(HWLWND hSb, int nWidth);
	int IUIAPI ScrollBar_GetButton1Length(HWLWND hSb);
	int IUIAPI ScrollBar_SetCombineButton1BkImage(HWLWND hSb, LPCTSTR lpszImage);
	int IUIAPI ScrollBar_SetButton1BkImage(
		HWLWND hSb,
		UINT uMask,
		LPCTSTR lpszImageNameN,
		LPCTSTR lpszImageNameH,
		LPCTSTR lpszImageNameP,
		LPCTSTR lpszImageNameD,
		BOOL bRedraw
	);

	int IUIAPI ScrollBar_SetButton2Length(HWLWND hSb, int nWidth);
	int IUIAPI ScrollBar_GetButton2Length(HWLWND hSb);
	int IUIAPI ScrollBar_SetCombineButton2BkImage(HWLWND hSb, LPCTSTR lpszImage);
	int IUIAPI ScrollBar_SetButton2BkImage(
		HWLWND hSb,
		UINT uMask,
		LPCTSTR lpszImageNameN,
		LPCTSTR lpszImageNameH,
		LPCTSTR lpszImageNameP,
		LPCTSTR lpszImageNameD,
		BOOL bRedraw
	);

	int IUIAPI ScrollBar_SetCombineThumbBkImage(HWLWND hSb, LPCTSTR lpszImage);
	int IUIAPI ScrollBar_SetThumbBkImage(
		HWLWND hSb,
		UINT uMask,
		LPCTSTR lpszImageNameN,
		LPCTSTR lpszImageNameH,
		LPCTSTR lpszImageNameP,
		LPCTSTR lpszImageNameD,
		BOOL bRedraw
	);
	int IUIAPI ScrollBar_SetThumb9GridResizeParam(HWLWND hSb, LPCRECT lprcParam);
	int IUIAPI ScrollBar_GetThumb9GridResizeParam(HWLWND hSb, LPRECT lprcParam);

	/////////////
	// ListView API
	int IUIAPI ListView_SetItemHeight(HWLWND hListView, int nHeight);
	int IUIAPI ListView_GetItemHeight(HWLWND hListView);
	int IUIAPI ListView_SetItemHeaderSpace(HWLWND hListView, int nSpace);
	int IUIAPI ListView_GetItemHeaderSpace(HWLWND hListView);
	int IUIAPI ListView_SetGridLineColor(HWLWND hListView, COLORREF cr);
	COLORREF IUIAPI ListView_GetGridLineColor(HWLWND hListView);
	int IUIAPI ListView_SetDrawFirstRowGridLine(HWLWND hListView, BOOL bDraw);
	BOOL IUIAPI ListView_IsDrawFirstRowGridLine(HWLWND hListView);
	int IUIAPI ListView_SetGridLineOffset(HWLWND hListView, POINT pt);
	POINT IUIAPI ListView_GetGridLineOffset(HWLWND hListView);
	int IUIAPI ListView_EnableSelectedFitClient(HWLWND hListView, BOOL bEnable);
	BOOL IUIAPI ListView_IsEnableSelectedFitClient(HWLWND hListView);

	//////////////////
	// Window API

	int IUIAPI Window_BindStyle(HWND hWnd, const CWindowProp *pWindowProp);
	CONTROL_LAYOUT_HOR IUIAPI Window_SetHorzLayoutMode(HWND hWnd, CONTROL_LAYOUT_HOR eLayout);
	CONTROL_LAYOUT_VER IUIAPI Window_SetVertLayoutMode(HWND hWnd, CONTROL_LAYOUT_VER eLayout);
	// ����ʹ��UpdateLayeredWindow�Ĵ����Ƿ�����ˢ��
	void IUIAPI SetULWNoRedraw(HWND hWnd, BOOL bNoRedraw);
	BOOL IUIAPI IsULWNoDraw(HWND hWnd);
	int IUIAPI IUIUpdateWindow(HWND hWnd);

	///////////////
	// ColumnHeader API
	// ����Header�߶ȣ�������FilterBar
	int IUIAPI ColumnHeader_BindStyle(HWLWND hHeader, const CColumnHeaderProp *pProp);
	int IUIAPI ColumnHeader_GetItemCount(HWLWND hHeader);

	BOOL IUIAPI ColumnHeader_GetItem(HWLWND hHeader, __in int nPos, __out HDITEM *pHeaderItem);
	BOOL IUIAPI ColumnHeader_SetItem(HWLWND hHeader, __in int nPos, __in HDITEM *pHeaderItem);
	BOOL IUIAPI ColumnHeader_GetItemRect(HWLWND hHeader, __in int nIndex, __out LPRECT lpRect);
	BOOL IUIAPI ColumnHeader_GetOrderArray(HWLWND hHeader, __in LPINT piArray, __in int iCount);
	BOOL IUIAPI ColumnHeader_SetOrderArray(HWLWND hHeader, __in int iCount, __in LPINT piArray);
	int IUIAPI ColumnHeader_OrderToIndex(HWLWND hHeader, __in int nOrder);
	int IUIAPI ColumnHeader_HitTest(HWLWND hHeader, __inout LPHDHITTESTINFO pHeaderHitTestInfo);

#if _WIN32_IE >= 0x0500
	int IUIAPI ColumnHeader_GetBitmapMargin(HWLWND hHeader);
	int IUIAPI ColumnHeader_SetBitmapMargin(HWLWND hHeader, __in int nWidth);
#endif

#if (_WIN32_WINNT >= 0x600) && defined(UNICODE)
	BOOL IUIAPI ColumnHeader_GetItemDropDownRect(HWLWND hHeader, __in int iItem, __out LPRECT lpRect);
	BOOL IUIAPI ColumnHeader_GetOverflowRect(HWLWND hHeader, __out LPRECT lpRect);
	int IUIAPI ColumnHeader_GetFocusedItem(HWLWND hHeader);
	BOOL IUIAPI ColumnHeader_SetFocusedItem(HWLWND hHeader, __in int iItem);
#endif // _WIN32_WINNT >= 0x600 && defined(UNICODE)

	int IUIAPI ColumnHeader_InsertItem(HWLWND hHeader, __in int nPos, __in HDITEM *phdi);
	BOOL IUIAPI ColumnHeader_DeleteItem(HWLWND hHeader, __in int nPos);
	BOOL IUIAPI ColumnHeader_Layout(HWLWND hHeader, __in HDLAYOUT *pHeaderLayout);
	HIMAGELIST IUIAPI ColumnHeader_CreateDragImage(HWLWND hHeader, __in int nIndex);
	int IUIAPI ColumnHeader_SetHotDivider(HWLWND hHeader, __in CIUIPoint pt);
	int IUIAPI ColumnHeader_SetHotDivider(HWLWND hHeader, __in int nIndex);

#if _WIN32_IE >= 0x0500
	int IUIAPI ColumnHeader_SetFilterChangeTimeout(HWLWND hHeader, __in DWORD dwTimeOut);
	int IUIAPI ColumnHeader_EditFilter(HWLWND hHeader, __in int nColumn, __in BOOL bDiscardChanges);
	BOOL IUIAPI ColumnHeader_ClearFilter(HWLWND hHeader, __in int nColumn);
	BOOL IUIAPI ColumnHeader_ClearAllFilters(HWLWND hHeader);
#endif

	int IUIAPI ColumnHeader_SetBkImage(
		HWLWND hHeader,
		UINT uMask,
		LPCTSTR lpszImageNameBkN,
		LPCTSTR lpszImageNameBkD
	);
	int IUIAPI ColumnHeader_GetBkImage(
		HWLWND hHeader,
		UINT uMask,
		CIUIString *pstrImageNameBkN,
		CIUIString *pstrImageNameBkD
	);
	int IUIAPI ColumnHeader_SetBkImageResizeMode(HWLWND hHeader, IMAGE_RESIZE_MODE eImageResizeMode);
	IMAGE_RESIZE_MODE IUIAPI ColumnHeader_GetBkImageResizeMode(HWLWND hHeader);
	int IUIAPI ColumnHeader_SetBkImage9GridArg(HWLWND hHeader, LPCRECT lpRect);
	int IUIAPI ColumnHeader_GetBkImage9GridArg(HWLWND hHeader, LPRECT lpRect);

	// Header Item����
	int IUIAPI ColumnHeader_CombineButtonBkImage(HWLWND hHeader, BOOL bCombine);
	int IUIAPI ColumnHeader_IsCombineButtonBkImage(HWLWND hHeader);
	int IUIAPI ColumnHeader_SetButtonCombineImage(HWLWND hHeader, LPCTSTR lpszImageNameBk);
	int IUIAPI ColumnHeader_SetButtonImage(
		HWLWND hHeader,
		UINT uMask,
		LPCTSTR lpszImageNameBkN,
		LPCTSTR lpszImageNameBkH,
		LPCTSTR lpszImageNameBkS,
		LPCTSTR lpszImageNameBkD
	);
	int IUIAPI ColumnHeader_GetButtonImage(
		HWLWND hHeader,
		UINT uMask,
		BOOL *pbCombineImage,
		CIUIString *pstrCombineImageName,
		CIUIString *pstrImageNameBkN,
		CIUIString *pstrImageNameBkH,
		CIUIString *pstrImageNameBkS,
		CIUIString *pstrImageNameBkD
	);

	int IUIAPI ColumnHeader_SetButtonBkImageResizeArg(HWLWND hHeader, IMAGE_RESIZE_MODE eIrm, LPCRECT lprc9Grid);
	int IUIAPI ColumnHeader_GetButtonBkImageResizeArg(HWLWND hHeader, IMAGE_RESIZE_MODE *peIrm, LPRECT lprc9Grid);

	int IUIAPI ColumnHeader_SetTextColor(HWLWND hHeader, COLORREF crN, COLORREF crH, COLORREF crS, COLORREF crD);
	int IUIAPI ColumnHeader_GetTextColor(HWLWND hHeader, COLORREF *pcrN, COLORREF *pcrH, COLORREF *pcrS, COLORREF *pcrD);

	int IUIAPI ColumnHeader_SetTextFont(
		HWLWND hHeader,
		UINT uMask,
		LPCTSTR lpszFontIDN,
		LPCTSTR lpszFontIDH,
		LPCTSTR lpszFontIDS,
		LPCTSTR lpszFontIDD
	);
	int IUIAPI ColumnHeader_GetTextFont(
		HWLWND hHeader,
		UINT uMask,
		CIUIString *pstrFontIDN,
		CIUIString *pstrFontIDH,
		CIUIString *pstrFontIDS,
		CIUIString *pstrFontIDD
	);

	int IUIAPI ColumnHeader_SetHeaderHeight(HWLWND hHeader, int nHeight);
	int IUIAPI ColumnHeader_GetHeaderHeight(HWLWND hHeader);

	int IUIAPI ColumnHeader_EnableHeaderTrack(HWLWND hHeader, BOOL bEnable);
	BOOL IUIAPI ColumnHeader_IsHeaderTrackEnable(HWLWND hHeader);

	int IUIAPI ColumnHeader_EnableHeaderDragDrop(HWLWND hHeader, BOOL bEnable);
	BOOL IUIAPI ColumnHeader_IsHeaderDragDropEnable(HWLWND hHeader);

	int IUIAPI ColumnHeader_HitTest(HWLWND hHeader, CIUIPoint pt);

	////////////////////////////////////////////////////////////////////
	// ͨ::GetWindow
#define GW_CHILDBINDITEM	7
	HWLWND IUIAPI GetWindow(HWLWND hWnd, UINT uCmd);
	CWLWnd *IUIAPI GetWindow(CWLWnd *pWnd, UINT uCmd);

	// ��hwndParent��ֱ�Ӻ���hwndChildAfter����һ���ֵܿؼ�����
	// hwndChildAfter������hwndParent��ֱ�Ӻ��ӣ������Ǻ���
	// ���hwndChildAfterΪNULL,���hwndParent�ĵ�һ����������
	// FindControlEx�ݹ�������к���
	HWLWND IUIAPI FindControlEx(
		HWND hHost,
		HWLWND hwndParent,
		HWLWND hwndChildAfter,
		LPCTSTR lpszClass,
		LPCTSTR lpszWindow);

	HWLWND IUIAPI FindControl(HWLWND hWndParent, LPCTSTR lpszName);

	// ���hWnd�Ƿ���hParent����
	// ���hWndΪNULL, hParent��ΪNULL, ����TRUE
	BOOL IUIAPI IsDescendant(HWLWND hParent, HWLWND hWnd);

	// ���в��ԣ���hWnd��ʼ�� HitTestChild�������а󶨵�Item�ϵĿؼ���
	// ����Ҫ����Item�Ŀؼ�������TreeView���Լ�����WLM_HITTESTBINDITEM��Ϣ
	// lpPt�������hWnd���׵�
	HWLWND IUIAPI HitTestChild(HWLWND hWnd, LPPOINT lpPt);
	// ���в��ԣ���hHost��ʼ�� Point�������hHost������
	// WindowFromPoint�������а󶨵�Item�ϵĿؼ�
	// ����Ҫ����Item�Ŀؼ�������TreeView���Լ�����WLM_HITTESTBINDITEM��Ϣ
	HWLWND IUIAPI WindowFromPoint(HWND hHost, POINT Point);

	BOOL IUIAPI Invalidate(HWLWND hWnd);
	BOOL IUIAPI InvalidateRect(HWLWND hWnd, LPCRECT lpRect);
	BOOL IUIAPI SetUseRectF(HWLWND hWnd, BOOL bUse);
	BOOL IUIAPI IsUseRectF(HWLWND hWnd);
	BOOL IUIAPI IsCachedMode(HWLWND hWnd);
	HBITMAP IUIAPI GetCachedAlphaBitmap(HWLWND hWnd);
	int IUIAPI SetCachedAlphaBitmap(HWLWND hWnd, HBITMAP hbmp);

	UINT_PTR IUIAPI SetTimer(HWLWND hWnd, UINT_PTR nIDEvent, UINT uElapse, WLTIMERPROC lpTimerFunc);
	BOOL IUIAPI KillTimer(HWLWND hWnd, UINT_PTR nIDEvent);
	BOOL IUIAPI IsTimerExist(HWLWND hWnd, UINT_PTR nIDEvent);

	// ��Ϊֻ��HWND���ܽ����Ϸţ�����һ��HWNDֻ��ָ��һ��IDropTarget,
	// ���ԣ����������һ��HWLWND��Ҫ���գ�����Host����ע��һ��IDropTarget
	// Ȼ���������ע�����Ϸŵ�HWLWND�󣬵���HWLWND�����IDropTarget��������
	HRESULT IUIAPI RegisterDragDrop(HWLWND hwnd, IDropTarget *pDropTarget);
	HRESULT IUIAPI RevokeDragDrop(HWLWND hwnd);

	int IUIAPI BeforePaint(HWLWND hWnd, HDC hDC);
	// hDC���ӿ����hWndΪ(0, 0)
	int IUIAPI AfterPaint(HWLWND hWnd, HDC hDC);
	int IUIAPI AfterPaintBkColor(HWLWND hWnd, HDC hDC);
	int IUIAPI AfterPaintBkImage(HWLWND hWnd, HDC hDC);
	// hDC���ӿ������HostΪ(0, 0)
	int IUIAPI AfterChildrenPaint(HWLWND hWnd, HDC hDC);
	int IUIAPI DrawBkColor(HWLWND hWnd, HDC hDC, LPCRECT lpRect);
	int IUIAPI DrawBorder(HWLWND hWnd, HDC hDC);

	int IUIAPI BeginAnimation(HWLWND hWnd, TimeLine::ANIMATION_TARGET_PROPERTY eTarget, TimeLine::Animation *pAnimation);
	void IUIAPI SetRedraw(HWLWND hWnd, BOOL bRedraw);
	BOOL IUIAPI IsRedraw(HWLWND hWnd);
	int IUIAPI SetClip(HWLWND hWnd, BOOL bClip);
	BOOL IUIAPI IsClip(HWLWND hWnd);

	LRESULT IUIAPI SendMessage(HWLWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL IUIAPI EnableScrollBar(HWLWND hWnd, UINT wSBflags, UINT wArrows);
	void IUIAPI EnableFloatScrollBar(HWLWND hWnd, BOOL bFloatVBar, BOOL bFloatHBar);
	BOOL IUIAPI IsFloatVBar(HWLWND hWnd);
	BOOL IUIAPI IsFloatHBar(HWLWND hWnd);
	int IUIAPI SetScrollRange(HWLWND hWnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw);
	int IUIAPI GetScrollRange(HWLWND hWnd, int nBar, int *pnMinPos, int *pnMaxPos);
	int IUIAPI SetScrollPos(HWLWND hWnd, int nBar, int nPos, BOOL bRedraw);
	int IUIAPI GetScrollPos(HWLWND hWnd, int nBar);
	int IUIAPI SetScrollInfo(HWLWND hWnd, int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw);
	BOOL IUIAPI GetScrollInfo(HWLWND hWnd, int nBar, LPSCROLLINFO lpScrollInfo);
	BOOL IUIAPI ShowScrollBar(HWLWND hWnd, int wBar, BOOL bShow);
	int IUIAPI SetHScrollBarHeight(HWLWND hWnd, int nHeight);
	int IUIAPI GetHScrollBarHeight(HWLWND hWnd);
	int IUIAPI SetVScrollBarWidth(HWLWND hWnd, int nWidth);
	int IUIAPI GetVScrollBarWidth(HWLWND hWnd);
	HWLWND IUIAPI GetVerticalScrollBar(HWLWND hWnd);
	HWLWND IUIAPI GetHorizontalScrollBar(HWLWND hWnd);
	void IUIAPI SetMember(HWLWND hWnd, void *pMember);
	void *IUIAPI GetMember(HWLWND hWnd);
	int IUIAPI BindStyle(HWLWND hWnd, const CControlProp *pProp);

	LRESULT IUIAPI CallIUIHandlerMap(HWLWND hWnd, RoutedEventArgs *pe);
	LRESULT IUIAPI RaiseEvent(HWLWND hWnd, RoutedEventArgs *pe);

	BOOL IUIAPI InitToolTipsClass(HINSTANCE hInstance);

	///////////////////////////////////////////////////////////////////////////////////

	// �õ�ָ�����ڵ������Ӵ���
	int GetAllChildren(IN HWLWND hWnd, BOOL bIncludeSelf, OUT std::vector<HWLWND> *pvChildren);

	int BindTextAlignStyle(HWLWND hWnd, const CLabelProp *pLabelProp);

	int IUISetControlBkImage2(
		HWLWND hWnd,
		UINT uMask,
		LPCTSTR lpszImageNameN,
		LPCTSTR lpszImageNameD
	);

	int IUIGetControlBkImage2(
		HWLWND hWnd,
		UINT uMask,
		BOOL *pbCombineImage,
		CIUIString *pstrCombineImageName,
		CIUIString *pstrImageNameN,
		CIUIString *pstrImageNameD
	);

	int IUISetControlBkImage4(
		HWLWND hWnd,
		BOOL bChecked,
		UINT uMask,
		LPCTSTR lpszImageNameN,
		LPCTSTR lpszImageNameH,
		LPCTSTR lpszImageNameP,
		LPCTSTR lpszImageNameD
	);

	int IUIGetControlBkImage4(
		HWLWND hWnd,
		BOOL bChecked,
		UINT uMask,
		BOOL *pbCombineImage,
		CIUIString *pstrCombineImageName,
		CIUIString *pstrImageNameN,
		CIUIString *pstrImageNameH,
		CIUIString *pstrImageNameP,
		CIUIString *pstrImageNameD
	);

	int IUISetControlFgImage4(
		HWLWND hWnd,
		BOOL bChecked,
		UINT uMask,
		LPCTSTR lpszImageNameN,
		LPCTSTR lpszImageNameH,
		LPCTSTR lpszImageNameP,
		LPCTSTR lpszImageNameD
	);

	int IUIGetControlFgImage4(
		HWLWND hWnd,
		BOOL bChecked,
		UINT uMask,
		BOOL *pbCombineImage,
		CIUIString *pstrCombineImageName,
		CIUIString *pstrImageNameN,
		CIUIString *pstrImageNameH,
		CIUIString *pstrImageNameP,
		CIUIString *pstrImageNameD
	);

	// for TreeView

	// ����TreeView��WalkTreeCallBack����TRUE�������������������������
	typedef BOOL (CALLBACK *WalkTreeCallBack)(HWLWND, HTREEITEM, void *pCallbackParam);
	// ��ǰ����������TRUE�����򷵻�FALSE
	BOOL IUIAPI WalkTree(HWLWND hTree, HTREEITEM hItemFrom, WalkTreeCallBack fn, void *pCallbackParam);

	// ����HWLWND��WalkHWLWNDCallBack����TRUE�������������������������
	typedef int (CALLBACK *WalkHWLWNDCallBack)(HWLWND, void *pCallbackParam);
	// ��ǰ����������TRUE�����򷵻�FALSE
	BOOL IUIAPI WalkHWLWNDChild(HWLWND hWndFrom, WalkHWLWNDCallBack fn, void *pCallbackParam);

	LRESULT CALLBACK IUICbtFilterHook(int, WPARAM, LPARAM);

	CIUIString IUIAPI HexStringFromInt(int n, BOOL bHasPrefix, BOOL b0Fill, int nBits/* = 8*/);
	std::string IUIAPI GetHexCodeW(LPCWSTR lpszSource);
	CIUIString IUIAPI GetFileNameHexCode(LPCTSTR lpszImageName, BOOL bEncodeExt);

	HRESULT GenerateCharFormat(__out CHARFORMAT2 *pcf, LOGFONT &lf);
	HRESULT GenerateCharFormat(__out CHARFORMAT2 *pcf, COLORREF crText);

	// 1 twips equal to 1/1440 inch.
	int IUIAPI GetXTwipsFromPixel(int nPixel);
	int IUIAPI GetYTwipsFromPixel(int nPixel);

	int IUIAPI GetXPixelFromTwips(int nTwips);
	int IUIAPI GetYPixelFromTwips(int nTwips);

	// 1 FPPTS equal to 1/20 twips
	float IUIAPI GetXFPPTSFromPixel(int nPixel);
	float IUIAPI GetYFPPTSFromPixel(int nPixel);

	// 1 himetric equal to 1/100 mm.
	int IUIAPI GetXHimetricFromPixel(int nPixel);
	int IUIAPI GetYHimetricFromPixel(int nPixel);

	int IUIAPI GetXPixelFromHimetric(int nHimetric);
	int IUIAPI GetYPixelFromHimetric(int nHimetric);

	void HookWindowCreate(Window *pThis);
	BOOL UnhookWindowCreate();
	// ������ΪUpdateLayeredWindowʱ������ʹ��32λpng��Ϊ���ںͿؼ�����
	// ��Ϊһ��ʹ��24λpng�Ļ���IUI�ڲ����Ż�ʹ��GDI���ƣ������¶�ʧAlpha��Ϣ��
	BOOL IsUpdateLayeredWindow(HWND hWnd);
	int IUIAPI SetLayeredWindow(HWND hWnd, BOOL bSet);

	CIUIString IUIAPI GetDefaultFontID();
	CIUIString IUIAPI GetDefaultColorID();

	// for menu
	typedef struct tagMENU *HIUIMENU;
	HIUIMENU HIUIMENUFromHMENU(HMENU hMenu);
	HIUIMENU IUILoadMenu(HINSTANCE hInstance, LPCTSTR lpMenuName);
	int IUITrackPopupMenuEx(
		HIUIMENU pMenu,
		UINT dwFlags,
		int x,
		int y,
		HWND pwndOwner,
		CONST TPMPARAMS *lpTpm);


	void IUIAPI IUITRACEA(LPCSTR lpszFormat, ...);
	void IUIAPI IUITRACE(LPCTSTR lpszFormat, ...);

	struct WLWNDCLASS
	{
		UINT style;
		fnWLEventHandler lpfnEventHandler; // �ؼ��¼�����
		int cbClsExtra;
		int cbWndExtra;
		HINSTANCE hInstance;
		HCURSOR hCursor;
		LPCTSTR lpszClassName;
	};

	BOOL IUIAPI RegisterWLClass(CONST WLWNDCLASS *lpWndClass);

	/*
	* SBDATA are the values for one scrollbar
	*/
	typedef struct tagSBDATA
	{
		int    posMin;
		int    posMax;
		int    page;
		int    pos;
	} SBDATA, *PSBDATA;

	// ���������ע�ͣ����ǵ�SBCALCӦ���ڴ�ֱ������ʱ�ġ�
	typedef struct tagSBCALC
	{
		// �������������ڵ�һλ����Ϊ���ǿ�����Ҫ��tagSBCALC *ǿת��SBDATA *
		SBDATA sbd;
		int    pxTop;			// ��������top����
		int    pxBottom;		// ��������bottom����
		int    pxLeft;			// ��������leftֵ��һ��Ϊ0��
		int    pxRight;			// ��������rightֵ��һ��Ϊ��������ȣ�
		int    cpxThumb;		// ������
		int nButton1MaxLength; // �ϰ�ť���߶�
		int nButton2MaxLength;

		// �ϰ�ť��bottom���ꡣ ����ϰ�ť��0��ʼ�����ֵҲ��ʾ�ϰ�ť�ĸ߶�
		// �������߶Ȳ�������������������ťʱ�����ֵҲ���С
		int    pxUpArrow;
		int    pxDownArrow;		// �°�ť��top���꣨ע�ⲻ���°�ť�߶ȣ�

		// ����ť�����϶�����ʱ��������λ���������Զ��ĳ��ֵ��
		// ���������ԭ����λ�ã�����������Ǽ�¼��갴�»���ʱ��topֵ
		int    pxStart;

		int    pxThumbTop;		// �����topֵ
		int    pxThumbBottom;	// �����bottomֵ
		int    cpx;				// ������ƶ��߶ȣ����������ܸ߶�-������ť�߶�-����߶�
		int nTrackPos;			// ��ǰ����Trackλ��
		int    pxMin;			// ֵΪpSBCalc->pxTop + min((pSBCalc->pxBottom - pSBCalc->pxTop) / 2, pSBCalc->cpxThumb);
	} SBCALC, *PSBCALC;

	typedef struct tagSBTRACK
	{
		DWORD  fHitOld : 1; // ��ʾ����Ƿ���������Ч��Ԫ�أ����°�ť�����¹����
		DWORD  fTrackVert : 1;	// �Ƿ��Ǵ�ֱ������
		DWORD: 1;
		DWORD  fTrackRecalc: 1;
		HWLWND spwndSB;			// ���������ڱ���
		HWLWND spwndSBNotify;	// �������󶨵Ĵ���
		RECT   rcTrack;			// �ڹ���ǰ����¼�����Ԫ�أ��ϰ�ť���Ϲ���������¹�����°�ť��������

		// �ڹ���ǰ����¼�����Ԫ�ؽ�Ҫ�ص��ĺ�����
		// ���磬���������ǻ��飬xxxpfnSB������ֵΪxxxTrackThumb
		VOID (*xxxpfnSB)(HWLWND, UINT, WPARAM, LPARAM, PSBCALC);

		UINT   cmdSB;			// �ڹ���ǰ����¼�����Ԫ����Ҫ���ᴥ�����¼�
		UINT_PTR hTimerSB;		// ����ʱ�������ͷ����ʱ��Ҫ����ʱ���������������ֵ��ʾTimer ID
		int    dpxThumb;        // ����Topֵ�����Yֵ
		int    pxOld;           // ����ɵ�Topֵ
		int    posOld;			// ����ɵ�posֵ
		int    posNew;			// �����µ�posֵ
		int    nBar;			// SB_VERT or SB_HORZ ?
		PSBCALC pSBCalc;		// �������и�Ԫ������
	} SBTRACK, *PSBTRACK;

	/*
	* SBINFO is the set of values that hang off of a window structure, if the
	* window has scrollbars.
	*/
	typedef struct tagSBINFO
	{
		int WSBflags;
		SBDATA Horz;
		SBDATA Vert;
	} SBINFO, *PSBINFO;

	typedef struct tagControlInfo
	{
		HWND        hwnd;
		HWND        hwndParent;
		DWORD       style;
		DWORD       dwCustom;
		BITBOOL     bUnicode : 1;
		BITBOOL     bInFakeCustomDraw: 1;
		UINT        uiCodePage;
		DWORD       dwExStyle;
		LRESULT     iVersion;
#ifdef KEYBOARDCUES
		WORD        wUIState;
#endif
	} IUICONTROLINFO, FAR *LPIUICONTROLINFO;

	typedef struct IUI_CONTROL_INFO
	{
		IUI_CONTROL_INFO()
		{
			pThis = NULL;
			hwndParent = NULL;
			style = 0;
			dwCustom = 0;
			bUnicode = TRUE;
			bInFakeCustomDraw = FALSE;
			uiCodePage = CP_ACP;
			dwExStyle = 0;
			iVersion = 0;
#ifdef KEYBOARDCUES
			wUIState = 0;
#endif

			m_crBkN = RGB(255, 255, 255); // �ŵ�Metric��
			m_crBkD = RGB(255, 255, 255); // �ŵ�Metric��

			m_bCombineBkImage = TRUE;
			m_himgCombineBk = NULL;
			m_eBkImageResizeMode = IRM_9GRID;

			m_crBorderN = RGB(255, 255, 255);
			m_crBorderD = RGB(255, 255, 255);

			m_uTextStyle = 0;
			m_eControlState = CONTROL_STATE_NORMAL;
		}

		int Release()
		{
			ImageManager::ReleaseIUIImage(m_himgCombineBk);
			m_himgCombineBk = NULL;

			return 0;
		}

		CWLWnd *pThis; // TODO: HWLWND��Ӧ��CWLWnd *��������CWnd::FromHandlePermanent()��Ӧ����
		HWLWND hwnd; // �ؼ��ľ��

		HWLWND hwndParent;
		DWORD       style;
		DWORD       dwCustom;
		BITBOOL     bUnicode;
		BITBOOL     bInFakeCustomDraw;
		UINT        uiCodePage;
		DWORD       dwExStyle;
		LRESULT     iVersion;
#ifdef KEYBOARDCUES
		WORD        wUIState;
#endif

	public:
		// ����
		COLORREF m_crBkN;
		COLORREF m_crBkD;

		BOOL m_bCombineBkImage;
		HIUIIMAGE m_himgCombineBk;

		IMAGE_RESIZE_MODE m_eBkImageResizeMode;
		CIUIRect m_rcBkImage9GridResizeArg;

		// �߿�
		COLORREF m_crBorderN;
		COLORREF m_crBorderD;

		// �ı���CWLWnd��֧�ֻ����ı�����֧�ֶ���
		UINT m_uTextStyle;			// ����MSDN: DrawText���һ������
		// �ؼ�״̬
		CONTROL_STATE m_eControlState;
	} *LibUIDK_LPCONTROLINFO;

	// Windowless�����ṹ�壬������HWND
	struct WLWND
	{
		WLWND()
			: spwndPrev(NULL)
			, spwndNext(NULL)
			, spwndParent(NULL)
			, spwndChild(NULL)
			, spwndBindItemChild(NULL)
			, m_bInBindChild(FALSE)
			, lpfnEventHandler(NULL)
			, hrgnUpdate(NULL)
			, pSBInfo(NULL)
			, spmenuSys(NULL)
			, spmenu(NULL)
			, m_hrgnClip(NULL)
			, cbwndExtra(NULL)
			, spwndLastActive(NULL)
			, hImc(NULL)
			, dwUserData(0)
			, m_dwBindItemData(0)
			, m_uID(0)
			, m_rcBorderThickness(4, 4, 4, 4)
			, m_dwCanDragResize(0)
			, m_nTitlebarHeight(0)
			, m_bMouseTransparent(false)
			, m_bCacheMode(false)
			, m_hCacheAlphaBmp(NULL)
			, m_bUseRectF(false)
			, m_pRectF(::new Gdiplus::RectF)
			, m_bDrawBkColor(false)
			, m_bDrawBorderColor(false)
			, m_dwFocusBorderColor(0)
			, m_rcBorder(1, 1, 1, 1)
			, m_nTooltipWidth(300)
			, m_eHAlign(CLH_LEFT)
			, m_eVAlign(CLV_TOP)
			, m_eDockProperty(DOCK_LEFT)
			, m_bEnableDPI(true)
			, m_hHostWnd(NULL)
			, m_bSetPos(false)
			, m_uLButtonDownHitTestRet(HTCLIENT)
			, m_lUserData(NULL)
			, m_uState(0)
			, m_bRedraw(true)
			, m_hVerticalScrollBar(NULL)
			, m_hHorizontalScrollBar(NULL)
			, m_bFloatVBar(false)
			, m_bFloatHBar(false)
			, m_pUserBindWLWndHandler(NULL)
			, m_bClip(TRUE) // �Ƿ���ü��ӿؼ����Լ����ڽ���༭���༭ģʽʱ�����ü���
			, m_bHideOleBorder(FALSE)
			, m_pMember(NULL)
			, m_pBindHorzScrollBarStyle(NULL)
			, m_pBindVertScrollBarStyle(NULL)
			, m_pDropTarget(NULL)
		{
			m_bNotify = TRUE;

			::ZeroMemory(&rcWindow, sizeof(RECT));
			::ZeroMemory(&rcClient, sizeof(RECT));
			::ZeroMemory(&m_rcPaint, sizeof(RECT));

			m_bFloatVBar = FALSE;
			m_bFloatHBar = FALSE;
			m_nHScrollBarHeight = Metrics::g_nScrollBarWidth;
			m_nVScrollBarWidth = Metrics::g_nScrollBarWidth;

			m_pMapProp = new std::map<CIUIString, HANDLE>;
			m_ptRenderTransformOrigin.x = 50;
			m_ptRenderTransformOrigin.y = 50;
		}

		~WLWND()
		{
			::delete m_pRectF;
			m_pRectF = NULL;

			// �Լ������Ŀؼ����Լ��������٣�ע�⣺
			// ��MFC����У�������ֻ���������ӿؼ���������ɾ���ӿؼ�ָ��
			// ���ԣ�����XML�󴴽����ӿؼ�ָ�룬Ӧ��������ɾ���������XML����CWLWnd������
			// ��������ָ�룬��CWLWndɾ���� ���ԣ�Ӧ��ΪCWLWnd�ṩһ��������ָ������˭ɾ��
			// m_hVerticalScrollBar��m_hHorizontalScrollBar�ɸ�������DestroyWindowʱ���١�

			delete (HPROPLIST)m_pMapProp;

			delete pSBInfo;

			delete ci.pThis;

			if (NULL != m_pUserBindWLWndHandler)
			{
				m_pUserBindWLWndHandler->m_hBindWLWnd = NULL;
			}
		}

		// IUI Add
		IUI_CONTROL_INFO ci;

		// ��һ���ֵܿؼ����������������Ŀ����HitTest��Ҫ�������в���
		// ��HitTest����Ƶ��ִ�еĶ�����
		HWLWND spwndPrev;
		// ��һ���ֵܿؼ�
		HWLWND spwndNext;
		// ���ؼ�
		HWLWND spwndParent;
		// ��һ���ӿؼ�
		HWLWND spwndChild;
		// ��һ���󶨵�Item���ӿؼ��� IUI�Ѱ󶨵�Item���ӿؼ����볣���ӿؼ��ֿ����档
		// ������Ϊ�󶨵�Item���ӿؼ��볣���ӿؼ����ۻ��ơ�HitTest�����ֵȶ���ͬ��
		// ���ҳ����ӿؼ���Z-Orderһ���ڰ󶨵�Item�ϵĿؼ�֮�ϡ�
		HWLWND spwndBindItemChild;
		// �����ǲ����ڸ��ؼ���BindChild�б���
		BOOL m_bInBindChild;

		CIUIString m_strClassName;
		CIUIString m_strName;

		RECT rcWindow;     // Window outer rectangle
		RECT rcClient;     // Client rectangle

		fnWLEventHandler lpfnEventHandler; // Event Handler

		//tagCLS *pcls;         // Pointer to window class

		HRGN hrgnUpdate;   // Accumulated paint region
		HRGN m_hrgnClip;     // Clipping region for this window������������Լ�

		std::map<CIUIString, HANDLE> *ppropList;
		// PPROPLIST ppropList;    // Pointer to property list
		PSBINFO pSBInfo;   // Words used for scrolling

		HMENU spmenuSys;  // Handle to system menu
		HMENU spmenu;     // Menu handle or ID


		int cbwndExtra;   // Extra bytes in window
		HWLWND spwndLastActive; // Last active in owner/ownee list
		HIMC hImc;         // Associated input context handle
		ULONG_PTR dwUserData;   // Reserved for random application data
		// ���ؼ��󶨵�Item��Ϊ�ؼ������Զ������ݣ�������ݳ����������ǰ󶨵��ĸ�Item�ϡ�
		ULONG_PTR m_dwBindItemData;

		BOOL m_bNotify;	// �Ƿ���֪ͨ

		CIUIString m_sToolTip;

		UINT m_uID;

		// ��XML�е�ԭʼ������Ը��ؼ��ĸ��ߵı߾�
		// ע������m_rcLayoutMargin�����߶����������ֵģ��ڲ���ʱ�����ߵ�ֵ���е��ӡ�
		// ����ؼ���m_rcControlMargin.left��ֵΪ5��m_rcLayoutMargin.left��ֵΪ10��
		// ����ؼ���ˮƽ���뷽ʽ��Left����ؼ���Canvas��left������ֵΪ15.
		// m_rcLayoutMargin���m_rcControlMargin�Ƕ�����������֡�
		CIUIRect m_rcControlMargin;

		CIUIRect m_rcItem;
		CIUIRect m_rcPadding;
		CIUIRect m_rcInset;
		CIUIRect m_rcBorderThickness;
		DWORD m_dwCanDragResize;
		int m_nTitlebarHeight;

		// �ڸ��ؼ��еĲ���
		CONTROL_LAYOUT_HOR m_eHAlign; // ��Canvas�У�����ڸ��ؼ�ˮƽ���뷽ʽ
		CONTROL_LAYOUT_VER m_eVAlign;
		DOCK m_eDockProperty;	// ��DockPanl�еĶ�������
		CIUIRect m_rcLayoutMargin; // ��߾�
		bool m_bFixedWidth; ///< �Ƿ���ù�SetFixedWidth
		bool m_bFixedHeight; ///< �Ƿ���ù�SetFixedHeight;
		SIZE m_cxyFixed;
		SIZE m_cxyMin;
		SIZE m_cxyMax;
		BOOL m_bMouseTransparent;

		// �����Cacheģʽ����ؼ��Ļ��ƣ����浽һ��HBITMAP�У�����Ҫˢ�¿ؼ�ʱ��ֱ�Ӱ�HBITMAP
		// �����ݣ����Ƶ����ؼ��ϡ�
		BOOL m_bCacheMode;
		HBITMAP m_hCacheAlphaBmp;
		BOOL m_bUseRectF;
		Gdiplus::RectF *m_pRectF;

		// ����
		BOOL m_bDrawBkColor;

		// �߿�
		BOOL m_bDrawBorderColor;
		DWORD m_dwFocusBorderColor;
		CIUIRect m_rcBorder;	// Border�ĸ��ߵĺ��
		SIZE m_cxyBorderRound;

		// �ı�
		CIUIString m_strCaption;
		CIUIRect m_rcTextPadding;

		CIUIRect  m_rcTitlebar; ///< left: ����߿��ࣻtop�����ϱ߿���; right: ���ұ߿���; bottom: �롾�ϡ��߿���
		int m_nTooltipWidth;

		//
		CIUIString m_strXml;

		// ������
		HWLWND m_hVerticalScrollBar;
		HWLWND m_hHorizontalScrollBar;
		UINT m_bFloatVBar; // ����ScrollBar��ռ�ÿͻ���λ�ã������ἷѹ�ͻ�������
		UINT m_bFloatHBar;
		int m_nHScrollBarHeight;
		int m_nVScrollBarWidth;
		CScrollBarProp *m_pBindHorzScrollBarStyle;
		CScrollBarProp *m_pBindVertScrollBarStyle;

		// Timer
		std::map<UINT_PTR, HTIMER> m_mapTimer;

		// Drag drop
		IDropTarget *m_pDropTarget;

		BOOL m_bEnableDPI;
		// ֻ��������ؼ���m_hHostWnd��Ч��
		// ������Ϊ�����ؼ�����ͨ��SetParent���ó�����HWND��ĳ��HWLWND���ӿؼ�
		// ���ÿ���ؼ���m_hHostWnd����Ч�Ļ��������ؼ��ж���ӿؼ�ʱ��Ҫһ�����ӿؼ�ȫ���޸�
		// m_hHostWnd��ֵ��
		HWND m_hHostWnd;
		BOOL m_bSetPos; // ��ֹSetPosѭ������
		CIUIRect m_rcPaint;
		CIUIRect m_rcLButtonDownRelateParent;	// record the rect while left mouse button down.
		UINT m_uLButtonDownHitTestRet;
		CIUIPoint m_ptLButtonDown;

		LPARAM m_lUserData;
		CIUIString m_strTag;
		UINT m_uState;
		// for SetProp
		std::map<CIUIString, HANDLE> *m_pMapProp;

		BOOL m_bRedraw;

		// Animation
		std::map<TimeLine::ANIMATION_TARGET_PROPERTY, TimeLine::Animation *> m_mapAnimation;

		// �ο�MSDN:UIElement..::.RenderTransformOrigin ����
		// ������תʱ��Բ�ģ���λ1%��������԰�ť��������Ϊ(50, 50)ʱ����ʾ�԰�ť������Ϊ
		// Բ�ģ�������Ϊ��100, 100)ʱ���԰�ť���½�ΪԲ�ģ������õ�ֵ����100ʱ����ʾ��
		// Զ�밴ť�����·�ĳһ��ΪԲ�ģ�ͬ������Ϊ��ֵʱ����ʾ�ڰ�ť֮�����Ͻ�ĳһ��ΪԲ��
		// ������ֻӰ����ƣ���Ӱ�첼��
		POINT m_ptRenderTransformOrigin;

		// TODO: Ӧ��Ϊ��ʽ�ṹ
		CWLWndHandler *m_pUserBindWLWndHandler;
		BOOL m_bClip;
		BOOL m_bHideOleBorder;

		// ��ͬ���Ϳؼ���˽������
		void *m_pMember;
	};

#define COMBINEIMAGESIZE2					2
#define COMBINEIMAGESIZE4					4
#define COMBINEIMAGESIZE8					8

	struct _LABEL
	{
		_LABEL()
			: hwnd(NULL)
			, m_bWidthMatchText(false)
			, m_bHeightMatchText(false)
			, m_pGifHelper(NULL)
			, m_bGifAnimationBegun(FALSE)
			, m_bRecordLButtonDown(FALSE)
		{
			for (int i = 0; i < COMBINEIMAGESIZE2; ++i)
			{
				m_himgBk[i] = NULL;
				m_crText[i] = RGB(0, 0, 0);
				m_eTextHorAlignMode[i] = TAH_LEFT;
				m_eTextVerAlignMode[i] = TAV_TOP;
				m_hIUIFont[i] = NULL;
			}
		}

		int Release()
		{
			hwnd->ci.Release();
			hwnd = NULL;

			for (int i = 0; i < COMBINEIMAGESIZE2; ++i)
			{
				ImageManager::ReleaseIUIImage(m_himgBk[i]);
				m_himgBk[i] = NULL;

				if (m_hIUIFont[i] != NULL)
				{
					FontManager::ReleaseIUIFont(m_hIUIFont[i]->GetOwner(),
						m_hIUIFont[i]->m_strFontResID);
					m_hIUIFont[i] = NULL;
				}
			}

			if (m_pGifHelper != NULL)
			{
				delete m_pGifHelper;
				m_pGifHelper = NULL;
			}
			m_bGifAnimationBegun = FALSE;

			return 0;
		}

		HWLWND hwnd;

		BOOL m_bWidthMatchText: 1;
		BOOL m_bHeightMatchText: 1;

		// ����ͼ������Ҫǰ��ͼ�������ǰ��ͼ�����󣬿���ΪLabel�ؼ�����һ����Label�ؼ���
		HIUIIMAGE m_himgBk[COMBINEIMAGESIZE2];
		GifHelper *m_pGifHelper;
		// ���������Gif��Gif��ʱ���Ƿ��Ѿ������������������������������
		BOOL m_bGifAnimationBegun;

		// �ı�
		COLORREF m_crText[COMBINEIMAGESIZE2];
		TEXT_ALIGN_HOR m_eTextHorAlignMode[COMBINEIMAGESIZE2];
		TEXT_ALIGN_VER m_eTextVerAlignMode[COMBINEIMAGESIZE2];
		CIUIRect m_rcTextMargin[COMBINEIMAGESIZE2];
		HIUIFONT m_hIUIFont[COMBINEIMAGESIZE2];

		// Label���UE_BUTTON_CLICK�¼��Ĳ���
		CIUIString m_strButtonClickArg;

		//ToolTipCtrl m_wndToolTip;

		// Helper
	public:
		BOOL m_bRecordLButtonDown;	// ��¼����Ƿ��ڱ��ؼ��ڰ��¹�
	};

	// RichTextBox˽�б���
	struct REBox
	{
		REBox()
			: hwnd(NULL)
			, m_pTextHost(NULL)
			, m_hDC(NULL)
			, m_pTextDocument(NULL)
			, m_pTextRange(NULL)
			, m_bDefaultProcHandleIfHitOleCtrl(TRUE)
		{
			for (int i = 0; i < COMBINEIMAGESIZE4; ++i)
			{
				m_himgBk[i] = NULL;
			}
		}

		int Release();

		HWLWND hwnd;

		CTxtWinHost *m_pTextHost;
		HDC m_hDC;
		ITextDocument *m_pTextDocument;
		ITextRange *m_pTextRange;

		HIUIIMAGE m_himgBk[COMBINEIMAGESIZE4];
		CIUIRect m_rcInset;
		// TODO: �ͻ����ɳߴ磬��RichEdit���ź�����ߴ��б仯�������ڴ�DC�л���һ�Σ�
		// ����ʹ��EM_POSFROMCHAR�õ�cp�����п����Ǵ����
		CIUIRect m_rcOldClient;

		BOOL m_bDefaultProcHandleIfHitOleCtrl;
	};

	struct IMBox
	{
		IMBox()
			: m_pREBox(NULL)
			, m_bQiPaoMode(TRUE)
			, m_nSenderLeftIndent(0)
			, m_nMsgLeftIndent(0)
			, m_nMsgRightIndent(0)
			, m_nMaxRelayoutWidth(1200)
			, m_bShowMsgSenderTitle(TRUE)
			, m_bShowMsgSenderAlias(TRUE)
			, m_nTitleSpaceBefore(15)
			, m_nTitleSpaceAfter(15)
			, m_nTitleLeftIndents(10)
			, m_crTitle(RGB(0, 0, 0))
			, m_bShowLeftFace(TRUE)
			, m_bShowRightFace(TRUE)
			, m_bCombineMsg(FALSE)
			, m_nCombineMsgTimeSpan(0)
			, m_pRichEditOleCallback(NULL)
			, m_pResendButtoStyle(NULL)
		{
			m_sizeFace.cx = m_sizeFace.cy = 32;

			for (int i = 0; i < 3; ++i)
			{
				m_himgSenderQiPao[i] = NULL;
				m_himgSelfQiPao[i] = NULL;
			}

			m_sizeResendButton.cx = m_sizeResendButton.cy = 20;
		}

		int Release()
		{
			for (int i = 0; i < 3; ++i)
			{
				ImageManager::ReleaseIUIImage(m_himgSenderQiPao[i]);
				m_himgSenderQiPao[i] = NULL;
				ImageManager::ReleaseIUIImage(m_himgSelfQiPao[i]);
				m_himgSelfQiPao[i] = NULL;
			}

			return 0;
		}

		REBox *m_pREBox;

		// ���˷�����Ϣ�����ݱ���ͼ��֧�����������ֲ�ͬ��ʽ
		HIUIIMAGE m_himgSenderQiPao[3];
		CIUIRect m_rcSenderQiPao9GridArg[3];
		// �Լ�������Ϣ�����ݱ���ͼ��֧�����������ֲ�ͬ��ʽ
		HIUIIMAGE m_himgSelfQiPao[3];
		CIUIRect m_rcSelfQiPao9GridArg[3];

		std::list<CIMMsg> m_lstMsg;

		BOOL m_bQiPaoMode; // �Ƿ�������ģʽ��ʾ��Ĭ��ΪTRUE

		// ������ģʽ�£�������Ϣ���������ֵ����������ճ���λ�ã�������ʾͷ��
		int m_nSenderLeftIndent;

		// ������ģʽ�£�������Ϣ���ݵ���������
		int m_nMsgLeftIndent;
		int m_nMsgRightIndent;

		// ������²��ֿ�ȣ���С��������ʱ���Լ�����Ϣ����ʾ���Ҳ࣬
		// ������������ʱ��������Ϣ������ʾ����ࡣ
		int m_nMaxRelayoutWidth;
		std::map<int, HBITMAP> m_mapDefineFace; // Ԥ����ͷ��
		// ��Ϣ�����߼���ı�ƣ��磺������Ӫ���ȡ� ��һ��������ͣ�����Խ�󣬼���Խ�ߡ�
		std::map<int, CIUIString> m_mapMsgSenderTitleAlias;
		// �Ƿ���ʾ����������
		BOOL m_bShowMsgSenderTitle;
		// �Ƿ���ʾ�����߱��������磺���೤������m_bShowMsgSenderTitleΪTRUEʱ��Ч
		BOOL m_bShowMsgSenderAlias;
		int m_nTitleSpaceBefore;
		int m_nTitleSpaceAfter;
		int m_nTitleLeftIndents;
		COLORREF m_crTitle;
		SIZE m_sizeFace;
		BOOL m_bShowLeftFace;
		BOOL m_bShowRightFace;
		// �Ƿ�ϲ�ͬһʱ�����ͬһ�������ߵ���Ϣ
		BOOL m_bCombineMsg;
		// ��m_bCombineMsgΪTRUE(ʹ�úϲ���Ϣģʽ)ʱ�����ö��֮�ڵ���Ϣ��Ҫ�ϲ�
		int m_nCombineMsgTimeSpan;
		// �����·�����Ϣ����ť���½�������������½ǵ�ƫ��, ˮƽ����ʹ�ֱ����Ϊ����
		CIUIPoint m_ptResendButtonMargin;
		// "���·�����Ϣ"��ť�ĳߴ�
		CIUISize m_sizeResendButton;
		// "���·�����Ϣ"��ť�󶨵İ�ť���
		CButtonProp *m_pResendButtoStyle;
		// ��ʾ���ఴť�󶨵İ�ť���
		CButtonProp *m_pShowMoreMsgStyle;

		IRichEditOleCallback *m_pRichEditOleCallback;
	};

	// ComboBox˽�б���
	typedef struct tagCBox
	{
		tagCBox()
		{
			hwnd = NULL;

			ZeroMemory(&editrc, sizeof(RECT));
			ZeroMemory(&buttonrc, sizeof(RECT));

			cxCombo = 0;
			cyCombo = 0;
			cxDrop = 0;
			cyDrop = 0;

			spwndEdit = NULL;
			spwndList = NULL;

			CBoxStyle = 0;
			fFocus = 0;
			fNoRedraw = 0;
			fMouseDown = 0;
			//fButtonPressed = 0;
			fLBoxVisible = 0;
			OwnerDraw = 0;
			fKeyboardSelInListBox = 0;
			fExtendedUI = 0;
			fCase = 0;
			fNoEdit = 0;
#ifdef COLOR_HOTTRACKING
			fButtonHotTracked = 0;
#endif // COLOR_HOTTRACKING
			m_eButtonState = CONTROL_STATE_NORMAL;
			fRightAlign = 0;
			fRtoLReading = 0;
			hFont = NULL;
			styleSave = 0;

			m_rcListMargin.SetRect(1, 1, 1, 1);
			m_crFocusedText = RGB(0, 0, 0);

			for (int i = 0; i < COMBINEIMAGESIZE4; ++i)
			{
				m_himgBk[i] = NULL;
				m_crText[i] = RGB(0, 0, 0);
				m_eTextHorAlignMode[i] = TAH_CENTER;
				m_eTextVerAlignMode[i] = TAV_CENTER;
				m_hIUIFont[i] = NULL;
			}

			for (int j = 0; j < COMBINEIMAGESIZE4 + 1; ++j)
			{
				m_crButtonBk[j] = RGB(128, 128, 128);
				m_himgButtonBk[j] = NULL;
				m_crButtonBorder[j] = NULL;
			}
			m_bDrawButtonBkColor = TRUE;
			m_himgCombineButtonBk = NULL;
			m_bDrawButtonBorderColor = TRUE;

			m_crBk[0] = Metrics::GetButtonBkColorN();
			m_crBk[1] = Metrics::GetButtonBkColorH();
			m_crBk[2] = Metrics::GetButtonBkColorS();
			m_crBk[3] = Metrics::GetButtonBkColorD();

			m_crBorder[0] = Metrics::GetButtonBorderColorN();
			m_crBorder[1] = Metrics::GetButtonBorderColorH();
			m_crBorder[2] = Metrics::GetButtonBorderColorS();
			m_crBorder[3] = Metrics::GetButtonBorderColorD();

			m_nButtonWidth = 16;
		}

		int Release();

		HWLWND hwnd;

		RECT    editrc;            /* Rectangle for the edit control/static text area */
		RECT    buttonrc;          /* Rectangle where the dropdown button is */

		int     cxCombo;            // Width of sunken area
		int     cyCombo;            // Height of sunken area
		int     cxDrop;             // 0x24 Width of dropdown
		int     cyDrop;             // Height of dropdown or shebang if simple

		UINT    CBoxStyle: 2;        /* Combo box style */
		UINT    fFocus: 1;         /* Combo box has focus? */
		UINT    fNoRedraw: 1;      /* Stop drawing? */

		// Helper
		UINT    fMouseDown: 1;      // ������ť�����£����������Ȼ�ǰ���״̬
		UINT    /*fButtonPressed*/: 1;	// ������ť�����£���״ֻ̬Ӱ��ˢ�£���Ӱ����Ϊ
		UINT    fLBoxVisible: 1;   // �����б�ǰ�Ƿ�ɼ�
		UINT    OwnerDraw: 2;       /* Owner draw combo box if nonzero. value
                                * specifies either fixed or varheight
                                */
		UINT    fKeyboardSelInListBox: 1; /* Is the user keyboarding through the
                                      * listbox. So that we don't hide the
                                      * listbox on selchanges caused by the
                                      * user keyboard through it but we do
                                      * hide it if the mouse causes the
                                      * selchange.
                                      */
		UINT    fExtendedUI: 1;     /* Are we doing TandyT's UI changes on this
                                * combo box?
                                */
		UINT    fCase: 2;

		UINT    : 1;        // 3D or flat border?
		UINT    fNoEdit: 1;         /* True if editing is not allowed in the edit
                                * window.
                                */
#ifdef COLOR_HOTTRACKING
		UINT    fButtonHotTracked: 1; /* Is the dropdown hot-tracked? */
#endif // COLOR_HOTTRACKING

		CONTROL_STATE m_eButtonState;
		UINT    fRightAlign: 1;    /* used primarily for MidEast right align */
		UINT    fRtoLReading: 1;   /* used only for MidEast, text rtol reading order */
		HANDLE  hFont;             /* Font for the combo box */
		LONG    styleSave;         /* Temp to save the style bits when creating
                                * window.  Needed because we strip off some
                                * bits and pass them on to the listbox or
                                * edit box.
                                */



		// ����
		COLORREF m_crBk[4];
		HIUIIMAGE m_himgBk[COMBINEIMAGESIZE4];

		// �߿�
		COLORREF m_crBorder[COMBINEIMAGESIZE4];

		// �ı�
		COLORREF m_crText[COMBINEIMAGESIZE4];
		COLORREF m_crFocusedText;
		TEXT_ALIGN_HOR m_eTextHorAlignMode[COMBINEIMAGESIZE4];
		TEXT_ALIGN_VER m_eTextVerAlignMode[COMBINEIMAGESIZE4];
		CIUIRect m_rcTextMargin[COMBINEIMAGESIZE4];
		HIUIFONT m_hIUIFont[COMBINEIMAGESIZE4];

		Window m_wndDropList;

		// RichTextBox
		HWLWND spwndEdit;
		CIUIRect m_rcEditMargin;

		// Button
		int m_nButtonWidth;
		CIUIRect m_rcButtonMargin;
		BOOL m_bDrawButtonBkColor;
		COLORREF m_crButtonBk[COMBINEIMAGESIZE4 + 1];
		HIUIIMAGE m_himgCombineButtonBk;
		HIUIIMAGE m_himgButtonBk[COMBINEIMAGESIZE4 + 1];
		BOOL m_bDrawButtonBorderColor;
		COLORREF m_crButtonBorder[COMBINEIMAGESIZE4 + 1];

		// Drop list
		HWND spwndList;  /* List box control window handle */
		CIUIString m_strDropListXML;
		CIUIRect m_rcListMargin;	// List box����������ڱ߾�
	} CBOX, *PCBOX;


#include <iimgctx.h>

	// ����������Incremental search��������ListView��TreeView�У���������Itemǰ������ĸʱ
	// ListView��TreeView����ֱ�ӹ�������Ӧ��Itemλ�á�
	typedef struct ISEARCHINFO
	{
		ISEARCHINFO()
			: iIncrSearchFailed(0)
			, pszCharBuf(0)
			, cbCharBuf(0)
			, ichCharBuf(0)
			, timeLast(0)
#if defined(FE_IME) || !defined(WINNT)
			, fReplaceCompChar(0)
#endif
		{

		}

		int iIncrSearchFailed;
		LPTSTR pszCharBuf;                  // isearch string lives here
		int cbCharBuf;                      // allocated size of pszCharBuf
		int ichCharBuf;                     // number of live chars in pszCharBuf
		DWORD timeLast;                     // time of last input event
#if defined(FE_IME) || !defined(WINNT)
		BOOL fReplaceCompChar;
#endif

	} ISEARCHINFO, *PISEARCHINFO;

	struct LV_ITEMPROPERTIES
	{
		LV_ITEMPROPERTIES()
		{
			m_eBkType = BKT_COLOR;
			m_crItemBk = RGB(255, 255, 255);
			m_hItemBkBmp = NULL;
			m_crItemText = RGB(0, 0, 0);
			m_hIUIFont = NULL;
		}
		~LV_ITEMPROPERTIES()
		{
			ImageManager::ReleaseIUIImage(m_hItemBkBmp);
			m_hItemBkBmp = NULL;
		}

		// Background
		BACKGROUND_TYPE m_eBkType;
		COLORREF m_crItemBk;		// If the item background image is valid, the background color is ignored.
		HIUIIMAGE m_hItemBkBmp;
		CIUIRect m_rcItemBkImage9GridArg;

		// Text
		COLORREF m_crItemText;
		HIUIFONT m_hIUIFont;
	};

	struct SListViewData
	{
		HWLWND hwnd;

		BOOL fNoDismissEdit: 1; // don't dismiss in-place edit control
		BOOL fButtonDown: 1;    // we're tracking the mouse with a button down
		BOOL fOneClickOK: 1;    // true from creation to double-click-timeout
		BOOL fOneClickHappened: 1; // true from item-activate to double-click-timeout
		BOOL fPlaceTooltip: 1;  // should we do the placement of tooltip over the text?
		BOOL fImgCtxComplete: 1; // TRUE if we have complete bk image
		BOOL fNoEmptyText: 1;   // we don't have text for an empty view.

		HDPA hdpa;          // item array structure
		DWORD flags;        // LVF_ state bits
		DWORD exStyle;      // the listview LVM_SETEXTENDEDSTYLE
		DWORD dwExStyle;    // the windows ex style
		HFONT hfontLabel;   // font to use for labels
		COLORREF clrBk;     // Background color
		COLORREF clrBkSave; // Background color saved during disable
		COLORREF clrText;   // text color
		COLORREF clrTextBk; // text background color
		HBRUSH hbrBk;
		HANDLE hheap;        // The heap to use to allocate memory from.
		int cyLabelChar;    // height of '0' in hfont
		int cxLabelChar;    // width of '0'
		int cxEllipses;     // width of "..."
		int iDrag;          // index of item being dragged
		int iFocus;         // index of currently-focused item
		int iSubItemEditLabel; // ��Ҫ�༭����Item����
		int iMark;          // index of "mark" for range selection
		int iItemDrawing;   // item currently being drawn
		int iFirstChangedNoRedraw;  // Index of first item added during no redraw.
		UINT stateCallbackMask; // item state callback mask
		SIZE sizeClient;      // current client rectangle
		int nWorkAreas;                            // Number of workareas
		LPRECT prcWorkAreas;      // The workarea rectangles -- nWorkAreas of them.
		UINT nSelected;
		UINT uDBCSChar;         // DBCS character for incremental search
		int iPuntChar;
		HRGN hrgnInval;
		HWND hwndToolTips;      // handle of the tooltip window for this view
		int iTTLastHit;         // last item hit for text
		int iTTLastSubHit;      // last subitem hit for text
		LPTSTR pszTip;          // buffer for tip

		// Small icon view fields

		HIMAGELIST himlSmall;   // small icons
		int cxSmIcon;          // image list x-icon size
		int cySmIcon;          // image list y-icon size
		int g_cxIconMargin;
		int g_cyIconMargin;
		int xOrigin;        // Horizontal scroll posiiton
		int cxItem;         // Width of small icon items
		// Item�߶ȣ�����small icon view��
		// Win32��List�߶��Ǹ���Item�ı��ĸ߶���Image�ĸ߶ȼ�������ģ�
		// ȡ�ı��߶ȡ�Small Image�߶ȡ�State Image�߶ȵ����ֵ�����Ҽ��ϱ߿�ĸ߶�
		// IUI�У�ͨ���û�����Item�߶ȡ�
		int cyItem;
		int cItemCol;       // Number of items per column

		// for icon view.
		// �����Icon view���ֳ�N��M�еı��Item���ڵ�Ԫ���ڣ�
		// ��cxIconSpacing��cyIconSpacing��ʾ��Ԫ��Ŀ�͸ߡ�
		// ͨ��LVM_SETICONSPACING��Ϣ������cxIconSpacing��cyIconSpacing��ֵ
		// LPARAM: MAKELONG(cx, cy)
		// cx��cy��ֵ�����ͼ��λͼ�����Ͻǡ� ��ˣ�Ϊ�����ò��ص���ͼ��֮��ļ�࣬
		// cx��cyֵ�������ͼ��Ĵ�С���Լ�ͼ��֮������ļ�ࡣ ������ͼ���ȵ�ֵ�������ص���
		// ������ͼ����ʱ��cx��cy��������Ϊ4����� ��С��ֵ������������Ĳ��֡�
		// ��Ҫ��cx��cy����ΪĬ�ϼ�࣬�뽫LPARAMֵ����Ϊ-1.
		int cxIconSpacing;
		int cyIconSpacing;

		// Icon view fields

		HIMAGELIST himl;
		int cxIcon;             // image list x-icon size
		int cyIcon;             // image list y-icon size
		HDPA hdpaZOrder;        // Large icon Z-order array
		POINT ptOrigin;         // Scroll position
		RECT rcView;            // Bounds of all icons (ptOrigin relative)
		int iFreeSlot;          // Most-recently found free icon slot since last reposition (-1 if none)

		HWND hwndEdit;          // edit field for edit-label-in-place
		int iEdit;              // item being edited
		WNDPROC pfnEditWndProc; // edit field subclass proc

		NMITEMACTIVATE nmOneClickHappened;

		// Report view fields

		int cCol;
		HDPA hdpaSubItems;
		HWLWND hwndHdr;           // Header control
		// Report���ʱ��Header�����0��Item��Top����
		int yTop;
		int xTotalColumnWidth;  // Total width of all columns
		// Report���List�Ĺ���λ�ã�ˮƽ�ʹ�ֱ���Ͻ�ƫ�ƣ�
		POINTL ptlRptOrigin;
		int iSelCol;            // to handle column width changing. changing col
		int iSelOldWidth;       // to handle column width changing. changing col width
		int cyItemSave;        // in ownerdrawfixed mode, we put the height into cyItem.  use this to save the old value

		// state image stuff
		HIMAGELIST himlState;
		int cxState;
		int cyState;

		// OWNERDATA stuff
		//L ILVRange *plvrangeSel;  // selection ranges
		//ILVRange *plvrangeCut;  // Cut Range
		int cTotalItems;        // number of items in the ownerdata lists
		int iDropHilite;        // which item is drop hilited, assume only 1
		int iMSAAMin, iMSAAMax; // keep track of what we told accessibility

		UINT uUnplaced;     // items that have been added but not placed (pt.x == RECOMPUTE)

		int iHot;  // which item is hot
		HFONT hFontHot; // the underlined font .. assume this has the same size metrics as hFont
		int iNoHover; // don't allow hover select on this guy because it's the one we just hover selected (avoids toggling)
		DWORD dwHoverTime;      // Defaults to HOVER_DEFAULT
		HCURSOR hCurHot; // the cursor when we're over a hot item

		// BkImage stuff
		IImgCtx *pImgCtx;       // Background image interface
		ULONG ulBkImageFlags;   // LVBKIF_*
		HBITMAP hbmBkImage;     // Background bitmap (LVBKIF_SOURCE_HBITMAP)
		LPTSTR pszBkImage;      // Background URL (LVBKIF_SOURCE_URL)
		int xOffsetPercent;     // X offset for LVBKIF_STYLE_NORMAL images
		int yOffsetPercent;     // Y offset for LVBKIF_STYLE_NORMAL images
		HPALETTE hpalHalftone;  // Palette for drawing bk images BUGBUG ImgCtx supposed to do this

		LPTSTR pszEmptyText;    // buffer for empty view text.

		COLORREF clrHotlight;     // Hot light color set explicitly for this listview.
		POINT ptCapture;

		//incremental search stuff
		ISEARCHINFO is;

		// IUI Add
		// Header�͵�0��Item��Ŀ�϶�߶�
		int cyItemHeaderSpace;
		// Grid line��ɫ
		COLORREF crGridLine;
		// �Ƿ���Ƶ�0��Item�����ˮƽGrid line
		BOOL bDrawFirstRowLine;
		// Grid Lineƫ��
		POINT ptGridLineOffset;

		// for selected item
		BOOL m_bEnableSelectedFitClient;	// the selected background fit all client width while item is selected.
		HIUIIMAGE m_himgSelectedItemCombineBk;
		LV_ITEMPROPERTIES m_lvpItemS[2];

		// for focus(caret) item
		HIUIIMAGE m_himgFocusItemCombineBk;
		LV_ITEMPROPERTIES m_lvpItemFocus;

		// for highlight item
		BOOL m_bEnableHighlightItemEffect;
		int m_nCurHighlightItem;
		LV_ITEMPROPERTIES m_lvpItemH;

		// Report header
		BOOL m_bHeaderTrack;
	};

	struct _BTN : public _LABEL
	{
		_BTN()
			: m_nButtonType(BT_NORMAL)
			, m_dwFocusedTextColor(0)
			, m_himgFocusedImage(NULL)
			, m_bCombineFgImage(true)
			, m_himgCombineFg(NULL)
			, m_eForegroundImageAlignHor(FAH_LEFT)
			, m_eForegroundImageAlignVer(FAV_CENTER)
			, m_bRecordLButtonDown(FALSE)
			, m_nCheck(BST_UNCHECKED)
			, m_uBindModalDialogID(0)
			, m_uBindModelessWndID(0)
		{
			int i = 0;
			for (i = 0; i < COMBINEIMAGESIZE4; ++i)
			{
				m_himgBk[i] = NULL;
				m_himgFg[i] = NULL;
				m_eTextHorAlignMode[i] = TAH_CENTER;
				m_eTextVerAlignMode[i] = TAV_CENTER;
				m_crText[i] = RGB(0, 0, 0);
				m_hIUIFont[i] = NULL;
			}

			m_crBk[0] = Metrics::GetButtonBkColorN();
			m_crBk[1] = Metrics::GetButtonBkColorH();
			m_crBk[2] = Metrics::GetButtonBkColorS();
			m_crBk[3] = Metrics::GetButtonBkColorD();

			m_crBorder[0] = Metrics::GetButtonBorderColorN();
			m_crBorder[1] = Metrics::GetButtonBorderColorH();
			m_crBorder[2] = Metrics::GetButtonBorderColorS();
			m_crBorder[3] = Metrics::GetButtonBorderColorD();

			m_crBk[0] = Metrics::g_crButtonBkCN;
			m_crBk[1] = Metrics::g_crButtonBkCH;
			m_crBk[2] = Metrics::g_crButtonBkCS;
			m_crBk[3] = Metrics::g_crButtonBkCD;

			m_crBkC[0] = Metrics::g_crButtonBkCN;
			m_crBkC[1] = Metrics::g_crButtonBkCH;
			m_crBkC[2] = Metrics::g_crButtonBkCS;
			m_crBkC[3] = Metrics::g_crButtonBkCD;

			for (i = 0; i < COMBINEIMAGESIZE4; ++i)
			{
				m_himgBkC[i] = NULL;
				m_himgFgC[i] = NULL;
				m_hIUIFontC[i] = NULL;
			}

			m_crBorderC[0] = Metrics::g_crButtonBorderCN;
			m_crBorderC[1] = Metrics::g_crButtonBorderCH;
			m_crBorderC[2] = Metrics::g_crButtonBorderCS;
			m_crBorderC[3] = Metrics::g_crButtonBorderCD;

			for (i = 0; i < COMBINEIMAGESIZE4 ; i++)
			{
				m_crTextC[0] = RGB(0, 0, 0);
			}
		}

		int Release();

		// ����
	public:
		int m_nButtonType;

		// ����
		COLORREF m_crBk[4];
		HIUIIMAGE m_himgBk[COMBINEIMAGESIZE4];

		DWORD m_dwFocusedTextColor;

		// ����ͼ��һ�����ŵ���ؼ�һ����
		HIUIIMAGE m_himgFocusedImage;

		// ǰ��ͼһ�㲻���ţ���1:1��ʾ������ȥ��ǰ��ͼ���ԣ���Ϊ������Label����ǰ��ͼ��
		BOOL m_bCombineFgImage;
		HIUIIMAGE m_himgCombineFg;
		HIUIIMAGE m_himgFg[COMBINEIMAGESIZE4];
		CIUIRect m_rcForegroundImageMargin;
		FOREGROUND_ALIGN_HOR m_eForegroundImageAlignHor;
		FOREGROUND_ALIGN_VER m_eForegroundImageAlignVer;

		// �߿�
		COLORREF m_crBorder[COMBINEIMAGESIZE4];

		// �ı�
		COLORREF m_crText[COMBINEIMAGESIZE4];
		TEXT_ALIGN_HOR m_eTextHorAlignMode[COMBINEIMAGESIZE4];
		TEXT_ALIGN_VER m_eTextVerAlignMode[COMBINEIMAGESIZE4];
		CIUIRect m_rcTextMargin[COMBINEIMAGESIZE4];
		HIUIFONT m_hIUIFont[COMBINEIMAGESIZE4];

		// ��ť���UE_BUTTON_CLICK�¼��Ĳ���
		CIUIString m_strButtonClickArg;

		// for Check Box and Radio Button
		COLORREF m_crBkC[COMBINEIMAGESIZE4];
		HIUIIMAGE m_himgBkC[COMBINEIMAGESIZE4];
		HIUIIMAGE m_himgFgC[COMBINEIMAGESIZE4];
		COLORREF m_crBorderC[COMBINEIMAGESIZE4];
		COLORREF m_crTextC[COMBINEIMAGESIZE4];
		HIUIFONT m_hIUIFontC[COMBINEIMAGESIZE4];

		int m_nCheck;

		// for popup bind window
		UINT m_uBindModalDialogID;
		UINT m_uBindModelessWndID;

		// �����ؼ���ΪRadio Buttonʱ����¼�󶨵�TabControl��Ϣ
		CIUIString m_strBindTabControlName;
		CIUIString m_strBindPropertySheetName;

		// Helper
	public:
		BOOL m_bRecordLButtonDown;	// ��¼����Ƿ��ڱ���ť�ڰ��¹�
	};

	// �����ؼ�˽�б���
#define IMM_START        0
#define IMM_DATEFIRST    1
#define IMM_MONTHSTART   1
#define IMM_YEARSTART    2
#define IMM_MONTHEND     3
#define IMM_YEAREND      4
#define IMM_DATELAST     4
#define DMM_STARTEND    2           // Difference between START and END
#define CCH_MARKERS      4          // There are four markers

#define CCHMAXMONTH     42
#define CCHMAXABBREVDAY 11
#define CCHMAXMARK      10

#define MCSC_COLORCOUNT   6

#define CALMONTHMAX     12
#define CALROWMAX       6
#define CALCOLMAX       7
#define CAL_DEF_SELMAX  7

	typedef struct MONTHMETRICS
	{
		int     rgi[5];
	} MONTHMETRICS, *PMONTHMETRICS;

	typedef struct tagLOCALEINFO
	{
		TCHAR szToday[32];        // "Today:"
		TCHAR szGoToToday[64];    // "&Go to today"

		TCHAR szMonthFmt[8];      // "MMMM"
		TCHAR szMonthYearFmt[16 + CCH_MARKERS]; // "\1MMMM\3 \2yyyy\4" -- see MCInsertMarkers

		TCHAR rgszMonth[12][CCHMAXMONTH];
		TCHAR rgszDay[7][CCHMAXABBREVDAY];
		int dowStartWeek;       // LOCALE_IFIRSTDAYOFWEEK (0 = mon, 1 = tue, 6 = sat)
		int firstWeek;          // LOCALE_IFIRSTWEEKOFYEAR

		TCHAR *rgpszMonth[12];  // pointers into rgszMonth
		TCHAR *rgpszDay[7];     // pointers into rgszDay
	} LOCALEINFO, *PLOCALEINFO, *LPLOCALEINFO;

	typedef struct tagCALENDARTYPE
	{
		CALID   calid;        // Calendar id number (CAL_GREGORIAN, etc.)
		LCID    lcid;         // Usually LOCALE_USER_DEFAULT, but forced to US for unsupported calendars
		int     dyrOffset;    // The calendar offset (0 for Gregorian and Era)
		HDPA    hdpaYears;    // If fEra, then array of year info
		HDPA    hdpaEras;     // If fEra, then array of era names
	} CALENDARTYPE, *PCALENDARTYPE;

	// �����DataTime�ؼ��������������Ĵ��ڵ�˽�����ԣ�
	typedef struct tagMONTHCAL
	{
		HWND spwnd;     // all controls start with this

		LOCALEINFO li;      // stuff that used to be global

		HINSTANCE hinstance;

		HWND    hwndEdit;   // non-NULL iff dealing with user-click on year
		HWND    hwndUD;     // UpDown control associated with the hwndEdit

		HPEN    hpen;
		HPEN    hpenToday;

		HFONT   hfont;                // stock font, don't destroy
		HFONT   hfontBold;            // created font, so we need to destroy

		COLORREF clr[MCSC_COLORCOUNT];

		int     dxCol;             // font info, based on bold to insure that we get enough space
		int     dyRow;
		int     dxMonth;
		int     dyMonth;
		int     dxYearMax;
		int     dyToday;
		int     dxToday;

		int     dxArrowMargin;
		int     dxCalArrow;
		int     dyCalArrow;

		HMENU   hmenuCtxt;
		HMENU   hmenuMonth;

		SYSTEMTIME  stMin;          // minimum selectable date
		SYSTEMTIME  stMax;          // maximum selectable date

		DWORD   cSelMax;

		SYSTEMTIME  stToday;
		SYSTEMTIME  st;             // the selection if not multiselect
		// the beginning of the selection if multiselect
		SYSTEMTIME  stEndSel;       // the end of the selection if multiselect
		SYSTEMTIME  stStartPrev;    // prev selection beginning (only in multiselect)
		SYSTEMTIME  stEndPrev;      // prev selection end (only in multiselect)

		SYSTEMTIME  stAnchor;       // anchor date in shift-click selection

		SYSTEMTIME  stViewFirst;    // first visible date (DAYSTATE - grayed out)
		SYSTEMTIME  stViewLast;     // last visible date (DAYSTATE - grayed out)

		SYSTEMTIME  stMonthFirst;   // first month (stMin adjusted)
		SYSTEMTIME  stMonthLast;    // last month (stMax adjusted)
		int         nMonths;        // number of months being shown (stMonthFirst..stMonthLast)

		UINT_PTR    idTimer;
		UINT_PTR    idTimerToday;

		int     nViewRows;          // number of rows of months shown
		int     nViewCols;          // number of columns of months shown

		RECT    rcPrev;             // rect for prev month button (in window coords)
		RECT    rcNext;             // rect for next month button (in window coords)

		RECT    rcMonthName;        // rect for the month name (in relative coords)
		// (actually, the rect for the titlebar area of
		// each month).

		RECT    rcDow;              // rect for days of week (in relative coords)
		RECT    rcWeekNum;          // rect for week numbers (in relative coords)
		RECT    rcDayNum;           // rect for day numbers  (in relative coords)

		int     iMonthToday;
		int     iRowToday;
		int     iColToday;

		RECT    rcDayCur;            // rect for the current selected day
		RECT    rcDayOld;

		RECT    rc;                  // window rc.
		RECT    rcCentered;          // rect containing the centered months

		// The following 4 ranges hold info about the displayed (DAYSTATE) months:
		// They are filled in from 0 to nMonths+1 by MCUpdateStartEndDates
		// NOTE: These are _one_ based indexed arrays of the displayed months
		int     rgcDay[CALMONTHMAX + 2];    // # days in this month
		int     rgnDayUL[CALMONTHMAX + 2];  // last day in this month NOT visible when viewing next month

		int     dsMonth;             // first month stored in rgdayState
		int     dsYear;              // first year stored in rgdayState
		int     cds;                 // number of months stored in rgdayState
		MONTHDAYSTATE   rgdayState[CALMONTHMAX + 2];

		int     nMonthDelta;        // the amount to move on button press

		BOOL    fControl;
		BOOL    fShift;

		CALENDARTYPE ct;            // information about the calendar

		WORD    fFocus : 1;
		WORD    fEnabled : 1;
		WORD    fCapture : 1;         // mouse captured

		WORD    fSpinPrev : 1;
		WORD    fFocusDrawn : 1;      // is focus rect currently drawn?
		WORD    fToday : 1;           // today's date currently visible in calendar
		WORD    fNoNotify : 1;        // don't notify parent window
		WORD    fMultiSelecting : 1;  // Are we actually in the process of selecting?
		WORD    fForwardSelect : 1;
		WORD    fFirstDowSet : 1;
		WORD    fTodaySet : 1;
		WORD    fMinYrSet : 1;        // stMin has been set
		WORD    fMaxYrSet : 1;        // stMax has been set
		WORD    fMonthDelta : 1;      // nMonthDelta has been set
		WORD    fHeaderRTL : 1;       // Is header string RTL ?

		//
		//  Metrics for each month we display.
		//
		MONTHMETRICS rgmm[CALMONTHMAX];

	} MONTHCAL, *PMONTHCAL, *LPMONTHCAL;

	typedef struct tagSUBEDIT
	{
		int     id;         // SE_ value above
		RECT    rc;         // bounding box for display

		LPWORD  pval;       // current value (in a SYSTEMTIME struct)
		UINT    min;        // min value
		UINT    max;        // max value
		int     cIncrement; // increment value

		int     cchMax;     // max allowed chars
		int     cchEdit;    // current number chars entered so far
		UINT    valEdit;    // value entered so far
		UINT    flDrawText; // flags for DrawText

		LPCTSTR pv;         // formatting string

		BOOL    fReadOnly;  // can this subedit be edited (receive focus)?
	} SUBEDIT, *PSUBEDIT, *LPSUBEDIT;

	typedef struct SUBEDITCONTROL
	{
		SUBEDITCONTROL()
			: fNone(FALSE)
			, hfont(NULL)
			, xScroll(0)
			, iseCur(0)
			, cse(0)
			, szFormat(NULL)
			, pse(NULL)
			, cDelimeter(0)
			, fMirrorSEC(FALSE)
			, fSwapTimeMarker(FALSE)
		{
			memset(&rc, 0, sizeof(RECT));
			memset(&st, 0, sizeof(SYSTEMTIME));
			memset(szDelimeters, 0, sizeof(TCHAR) * 15);
			memset(&rc, 0, sizeof(RECT));
		}

		IUI_CONTROL_INFO *pci;  // looks like this guy needs access to the hwnd
		BOOL fNone;         // allow scrolling into SUBEDIT_NONE
		HFONT hfont;        // font to draw text with
		RECT rc;            // rect for subedits
		int xScroll;        // amount pse array is scrolled
		int iseCur;         // subedit with current selection (SUBEDIT_NONE for no selection)
		int cse;            // count of subedits in pse array
		SYSTEMTIME st;      // current time pse represents (pse points into this)
		LPTSTR szFormat;    // format string as parsed (pse points into this)
		PSUBEDIT pse;       // subedit array
		TCHAR   cDelimeter; // delimiter between subedits (parsed from fmt string)
		TCHAR szDelimeters[15]; // delimiters between date/time fields (from resfile)
		CALENDARTYPE ct;    // information about the calendar
		BITBOOL fMirrorSEC : 1; // Whether or not to mirror the SubEditControls
		BITBOOL fSwapTimeMarker : 1; // Whether we need to swap the AM/PM symbol around or not
	} *PSUBEDITCONTROL, *LPSUBEDITCONTROL;

	// �����ComboBox����DataTime�ؼ���˽�����ԣ�
	typedef struct DATEPICK
	{
		DATEPICK()
			: hwnd(NULL)
			, hwndUD(NULL)
			, hwndMC(NULL)
			, hfontMC(NULL)

			, iseLastActive(0)
			, gdtr(0)
			, fEnabled(FALSE)
			, fUseUpDown(FALSE)
			, fFocus(FALSE)
			, fNoNotify(FALSE)
			, fCapture(FALSE)
			, fShow(FALSE)

			, fCheck(FALSE)
			, fCheckFocus(FALSE)

			, fLocale(FALSE)
			, fHasMark(FALSE)
			, fFreeEditing(FALSE)
		{
			memset(clr, 0, sizeof(COLORREF) * MCSC_COLORCOUNT);
			memset(m_crBk, RGB(255, 255, 255), sizeof(COLORREF) * COMBINEIMAGESIZE4);
			memset(m_himgBk, NULL, sizeof(HIUIIMAGE) * COMBINEIMAGESIZE4);

			memset(&stMin, 0, sizeof(SYSTEMTIME));
			memset(&stMax, 0, sizeof(SYSTEMTIME));
			memset(&stPrev, 0, sizeof(SYSTEMTIME));

			memset(&rcCheck, 0, sizeof(RECT));
			memset(&rc, 0, sizeof(RECT));
			memset(&rcBtn, 0, sizeof(RECT));
		}

		int Release();

		HWLWND hwnd;

		HWLWND      hwndUD;	// ����DTS_UPDOWN���ʱ���贴������Spin��ť
		HWND        hwndMC;	// ������������
		HFONT       hfontMC;    // font for drop down cal

		COLORREF clr[MCSC_COLORCOUNT];

		// ����
		COLORREF m_crBk[COMBINEIMAGESIZE4];
		HIUIIMAGE m_himgBk[COMBINEIMAGESIZE4];

		// HACK! stMin and stMax must remain in order and adjacent
		SYSTEMTIME  stMin;      // minimum date we allow
		SYSTEMTIME  stMax;      // maximum date we allow
		SYSTEMTIME  stPrev;     // most recent date notified
		SUBEDITCONTROL sec;     // current date

		RECT        rcCheck;    // location of checkbox iff fShowNone
		RECT        rc;         // size of SEC space
		RECT        rcBtn;      // location of dropdown or updown
		int         iseLastActive; // which subedit was active when we were last active?
		WPARAM      gdtr;       // Did app set min and/or max? (GDTR_MIN|GDTR_MAX)

		BITBOOL         fEnabled : 1;
		BITBOOL         fUseUpDown : 1;
		BITBOOL         fFocus : 1;
		BITBOOL         fNoNotify : 1;
		BITBOOL         fCapture : 1;
		BITBOOL         fShow : 1;        // TRUE iff we should continue to show MonthCal

		BITBOOL         fCheck : 1;       // TRUE iff the checkbox is checked
		BITBOOL         fCheckFocus : 1;  // TRUE iff the checkbox has focus

		BITBOOL         fLocale : 1;      // TRUE iff the format string is LOCALE dependent
		BITBOOL         fHasMark : 1;      // true iff has am/pm in current format
		BITBOOL         fFreeEditing : 1; // TRUE if in the middle of a free-format edit
	} *PDATEPICK, *LPDATEPICK;

	struct HTMLV
	{
		HTMLV()
			: hwnd(NULL)
			, m_hHostWnd(NULL)
			, m_dwXDocHostUI_Flag(0)
			, m_dwXDocHostUI_DblClk(0)
			, m_pStorage(NULL)
			, m_pOleObject(NULL)
			, m_pOleInPlaceObject(NULL)
			, m_pBrowserApp(NULL)
			, m_bInPlaced(FALSE)
			, m_dwRefCount(0)
			, m_pOleInPlaceActiveObject(NULL)
			, pHtmlViewCore(NULL)
		{

		}

		HWLWND hwnd;
		HWND m_hHostWnd;
		DWORD m_dwXDocHostUI_Flag;
		DWORD m_dwXDocHostUI_DblClk;

		IStorage *m_pStorage;				//�洢������
		IOleObject *m_pOleObject;			//OLE����
		IOleInPlaceObject *m_pOleInPlaceObject;	//InPlace����
		IWebBrowser2 *m_pBrowserApp;		//IWebBrowser2����
		BOOL m_bInPlaced;					//�Ƿ����???
		DWORD m_dwRefCount;					//���ü���
		IOleInPlaceActiveObject *m_pOleInPlaceActiveObject;

		HtmlViewCore *pHtmlViewCore;
		CJScript m_JScript;
	};

	struct WLTIMERINFO
	{
		HWLWND hOwner;
		UINT_PTR uTimerID;	// ::SetTimer���ص�����Timer ID
		UINT_PTR uIDEvent;	// CWLWnd::SetTimer�е�����Timer ID
		UINT uElapse;
		WLTIMERPROC lpTimerFunc;
		DWORD dwStartTime;	// Timer��ʼʱ�䣬��Timer����ʱGetTickCount()����
	};

	// TabControl��˽�г�Ա
	struct TB : public _LABEL
	{
		TB()
			: m_pvSheets(NULL)
			, m_uCurKey(0)
		{
			m_pvSheets = new std::vector<CPropertySheetInfo>;
		}

		int Release();

		std::vector<CPropertySheetInfo> *m_pvSheets;
		UINT_PTR m_uCurKey;
	};

	struct _DOCK : public _LABEL
	{
		_DOCK()
			: m_bLastChildFill(TRUE)
		{
			m_pvChildren = new std::vector<CChildInfo>;
		}

		int Release();

		std::vector<CChildInfo> *m_pvChildren;
		BOOL m_bLastChildFill;
	};

	// StackPanel˽�г�Ա
	struct  SP : public _LABEL
	{
		SP()
			: m_eDirection(D_LEFT)
		{
			m_pvChildren = new std::vector<CChildInfo>;
		}

		int Release();

		std::vector<CChildInfo> *m_pvChildren;
		Direction m_eDirection;
	};

} // namespace IUI

