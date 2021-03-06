// LocationURL.h : CLocationURL 的声明

#pragma once
#include "resource.h"       // 主符号


#include <shlguid.h>
#include <docobj.h>
#include <mshtml.h>
#include <urlmon.h>
#include <shlobj.h>

#include "BHODemo_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CLocationURL

class ATL_NO_VTABLE CLocationURL :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLocationURL, &CLSID_LocationURL>,
	public IObjectWithSiteImpl<CLocationURL>,
	public IDispatchImpl<ILocationURL, &IID_ILocationURL, &LIBID_BHODemoLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IOleCommandTarget
{
public:
	CLocationURL()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOCATIONURL)

DECLARE_NOT_AGGREGATABLE(CLocationURL)

BEGIN_COM_MAP(CLocationURL)
	COM_INTERFACE_ENTRY(ILocationURL)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IOleCommandTarget)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
STDMETHOD(SetSite)(IUnknown *pUnkSite);
STDMETHOD(QueryStatus)(const GUID *pguidCmdGroup, 
                       ULONG cCmds, 
                       OLECMD *prgCmds, 
                       OLECMDTEXT *pCmdText);
STDMETHOD(Exec)(const GUID *pguidCmdGroup, 
                DWORD nCmdID, 
                DWORD nCmdExecOpt, 
                VARIANTARG *pvaIn, 
                VARIANTARG *pvaOut );
private:
    CComPtr<IWebBrowser2> m_pBrowser;
    CComQIPtr<IOleCommandTarget, &IID_IOleCommandTarget> m_pTarget;
	
	//call LocationWebURL to save url and time with file.
	HRESULT LocationWebURL();
	//get the direction of where you want to save the file.
	bool GetSaveDir(TCHAR *pPath);

};

OBJECT_ENTRY_AUTO(__uuidof(LocationURL), CLocationURL)
