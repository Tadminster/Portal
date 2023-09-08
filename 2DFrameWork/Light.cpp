#include "framework.h"

Light::Light()
{
    light.screenPos =
        Vector2(App.GetHalfWidth(), App.GetHalfHeight());
    //조명 반지름
    light.radius = sqrtf(App.GetHalfWidth() * App.GetHalfWidth()
        + App.GetHalfHeight()* App.GetHalfHeight());
    //조명색
    light.lightColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
    //경계밖 색
    light.outColor = Color(0.0f, 0.0f, 0.0f, 0.5f);
    //조명 0번
    light.select = 0;

    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(LightDesc);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &lightBuffer);
        assert(SUCCEEDED(hr));
    }
    D3D->GetDC()->PSSetConstantBuffers(0, 1, &lightBuffer);
}

Light::~Light()
{
    lightBuffer->Release();
}

void Light::Set()
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    D3D->GetDC()->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy_s(mappedResource.pData, sizeof(LightDesc), &light, sizeof(LightDesc));
    D3D->GetDC()->Unmap(lightBuffer, 0);
}
