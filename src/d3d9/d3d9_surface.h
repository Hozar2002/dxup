#pragma once

#include "d3d9_resource.h"
#include "d3d9_d3d11_resource.h"
#include <vector>

namespace dxup {

  using Direct3DSurface9Base = Direct3DResource9<D3DRTYPE_SURFACE, IDirect3DSurface9>;

  // A d3d9 surface is essentially some subresource of a d3d11 texture.
  class Direct3DSurface9 final : public Direct3DSurface9Base {
    
  public:

    Direct3DSurface9(bool fakeSurface, UINT slice, UINT mip, Direct3DDevice9Ex* device, IUnknown* container, DXUPResource* resource, const D3D9ResourceDesc& desc);
    ~Direct3DSurface9();

    HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppv) override;
    HRESULT WINAPI GetContainer(REFIID riid, void** ppContainer) override;
    HRESULT WINAPI GetDesc(D3DSURFACE_DESC *pDesc) override;
    HRESULT WINAPI LockRect(D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags) override;
    HRESULT WINAPI UnlockRect() override;
    HRESULT WINAPI GetDC(HDC *phdc) override;
    HRESULT WINAPI ReleaseDC(HDC hdc) override;
    D3DRESOURCETYPE STDMETHODCALLTYPE GetType() override;

    UINT GetMip();
    UINT GetSlice();
    UINT GetSubresource();

    ULONG STDMETHODCALLTYPE AddRef() override;
    ULONG STDMETHODCALLTYPE Release() override;

    IDXGISurface1* GetDXGISurface();
    ID3D11RenderTargetView* GetD3D11RenderTarget(bool srgb);
    ID3D11DepthStencilView* GetD3D11DepthStencil();

    DXUPResource* GetDXUPResource();

  private:

    IUnknown* m_container;
    DXUPResource* m_resource;

    Com<IDXGISurface1> m_surface;
    Com<ID3D11RenderTargetView> m_rtView;
    Com<ID3D11RenderTargetView> m_rtViewSRGB;
    Com<ID3D11DepthStencilView> m_dsView;

    bool m_useRect;
    bool m_singletonSurface;

    UINT m_slice;
    UINT m_mip;
    UINT m_totalMips;
  };

}