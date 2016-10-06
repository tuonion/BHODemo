// LocationURL.h : CLocationURL ������

#pragma once
#include "resource.h"       // ������


#include <shlguid.h>
#include <docobj.h>
#include <mshtml.h>
#include <urlmon.h>
#include <shlobj.h>

#include "BHODemo_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
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
