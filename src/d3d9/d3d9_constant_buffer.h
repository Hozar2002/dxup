#pragma once

#include "../dx9asm/dx9asm_meta.h"
#include "d3d9_base.h"
#include <array>
#include <memory>

namespace dxup {

  using ShaderType = dx9asm::ShaderType;

  enum BufferType {
    Float = 0,
    Int = 1,
    Bool,
    Count,
  };

  class D3D9ConstantBuffer {

  public:

    D3D9ConstantBuffer(ID3D11Device1* device, ID3D11DeviceContext1* context, ShaderType type, BufferType bufferType);

    void prepareDraw();

    HRESULT set(uint32_t index, const void* values, uint32_t count);

    HRESULT get(uint32_t index, void* values, uint32_t count);

  private:

    void pushData();

    // I exist as long as my parent D3D9 device exists. No need for COM.
    ID3D11Device1* m_device;
    ID3D11DeviceContext1* m_context;

    std::shared_ptr<uint8_t> m_elements;
    uint32_t m_elementSize;
    uint32_t m_elementCount;

    Com<ID3D11Buffer> m_buffer;

  };

  class D3D9ConstantBuffers {

  public:

    D3D9ConstantBuffers(ID3D11Device1* device, ID3D11DeviceContext1* context);

    HRESULT set(ShaderType shdrType, BufferType bufferType, uint32_t index, const void* values, uint32_t count);
    HRESULT get(ShaderType shdrType, BufferType bufferType, uint32_t index, void* values, uint32_t count);

    void prepareDraw();

  private:

    static constexpr uint32_t permutations = ShaderType::Count * BufferType::Count;

    D3D9ConstantBuffer& getBuffer(ShaderType shdrType, BufferType bufferType);
    std::array<std::shared_ptr<D3D9ConstantBuffer>, permutations> m_buffers;
  };
}