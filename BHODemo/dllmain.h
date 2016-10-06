// dllmain.h : 模块类的声明。

class CBHODemoModule : public ATL::CAtlDllModuleT< CBHODemoModule >
{
public :
	DECLARE_LIBID(LIBID_BHODemoLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_BHODEMO, "{39A655BA-233E-4810-B768-585B699BCEF2}")
};

extern class CBHODemoModule _AtlModule;
