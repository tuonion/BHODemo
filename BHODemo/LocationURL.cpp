// LocationURL.cpp : CLocationURL µÄÊµÏÖ

#include "stdafx.h"
#include "LocationURL.h"


// CLocationURL
STDMETHODIMP CLocationURL::SetSite(IUnknown* pUnkSite) {

    if (pUnkSite != NULL)
    {

        // Cache the pointer to IWebBrowser2.
        CComQIPtr<IServiceProvider> sp = pUnkSite;
        HRESULT hr = sp->QueryService(IID_IWebBrowserApp, IID_IWebBrowser2, (void**)&m_pBrowser);
        hr = sp->QueryInterface(IID_IOleCommandTarget, (void**)&m_pTarget);
    } 
    else 
    {
        // Release cached pointers and other resources here.
        m_pBrowser.Release();
        m_pTarget.Release();
    }

    // Call base class implementation.
    return IObjectWithSiteImpl<CLocationURL>::SetSite(pUnkSite);
}

STDMETHODIMP CLocationURL::QueryStatus(const GUID *pguidCmdGroup, 
  ULONG cCmds, OLECMD *prgCmds, OLECMDTEXT *pCmdText) {

    return m_pTarget->QueryStatus(pguidCmdGroup, 
      cCmds, prgCmds, pCmdText);
}

STDMETHODIMP CLocationURL::Exec(const GUID *pguidCmdGroup, DWORD nCmdID, DWORD nCmdExecOpt, VARIANTARG *pvaIn, VARIANTARG *pvaOut) {

	//call LocationWebURL to save url and time with file.
	bool result=LocationWebURL();
    return result;
}

bool CLocationURL::GetSaveDir(TCHAR *pPath) {

    BROWSEINFO bi = { 0 };
    bi.lpszTitle = _T("Select the image destination");
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if ( pidl != 0 )
    {
        // Get the name of the folder
        SHGetPathFromIDList (pidl, pPath);
        // Free memory used
	    IMalloc * imalloc = 0;

        if (SUCCEEDED(SHGetMalloc(&imalloc)))
        {
            imalloc->Free(pidl);
            imalloc->Release();
        }

        return true;
    }

    return false;
}


// this function is designed for users' function targets
// what you want implement can be coded in this function. 

HRESULT CLocationURL::LocationWebURL(){

	 // Get save path.
    TCHAR path[MAX_PATH];
    if (!GetSaveDir(path))
    {
      return E_ABORT;
    }
	//get website url
	BSTR bstr;
	HRESULT hr=m_pBrowser->get_LocationURL(&bstr);
	MessageBox(NULL,bstr,_T("Hello"),MB_OK);

	//get website time 

	//create a file to save url and time 

	//remember to close the file .


	return hr;
}