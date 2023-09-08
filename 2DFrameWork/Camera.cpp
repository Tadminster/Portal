#include "framework.h"

ID3D11Buffer* Camera::VPBuffer = nullptr;
Camera* Camera::main = nullptr;
float Camera::mainCamSpeed = 10.0f;

void Camera::CreateStaticMember()
{
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(Matrix);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &VPBuffer);
        assert(SUCCEEDED(hr));

    }
}

void Camera::DeleteStaticMember()
{
    SafeRelease(VPBuffer);
}

void Camera::ControlMainCam()
{
	if (not main) return;

	if (INPUT->KeyPress('W'))
	{
		//                                  초당100움직임 xyz/s
		main->MoveWorldPos(main->GetForward() * DELTA * mainCamSpeed);
	}
	if (INPUT->KeyPress('S'))
	{
		main->MoveWorldPos(-main->GetForward() * DELTA * mainCamSpeed);
	}
	if (INPUT->KeyPress('A'))
	{
		main->MoveWorldPos(-main->GetRight() * DELTA * mainCamSpeed);
	}
	if (INPUT->KeyPress('D'))
	{
		main->MoveWorldPos(main->GetRight() * DELTA * mainCamSpeed);
	}
	if (INPUT->KeyPress('Q'))
	{
		main->MoveWorldPos(-main->GetUp() * DELTA * mainCamSpeed);
	}
	if (INPUT->KeyPress('E'))
	{
		main->MoveWorldPos(main->GetUp() * DELTA * mainCamSpeed);
	}

	//마우스 우클릭시
	if (INPUT->KeyPress(VK_RBUTTON))
	{
		Vector3 Rot;
		Rot.x = INPUT->movePosition.y * 0.001f;
		Rot.y = INPUT->movePosition.x * 0.001f;
		main->rotation += Rot;
	}
	//휠키로 카메라 앞뒤조절
	main->MoveWorldPos(main->GetForward() * INPUT->wheelMoveValue.z * DELTA);
}

Camera* Camera::Create(string name)
{
	Camera* temp = new Camera();
	temp->name = name;
	temp->type = ObType::Camera;
	return temp;
}

Camera::Camera()
{
	fov = 60.0f * ToRadian;
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	width = App.GetWidth();
	height = App.GetHeight();
	viewport.width = App.GetWidth();
	viewport.height = App.GetHeight();
	nearZ = 0.1f;
	farZ = 500.0f;
	//type = ObType::Camera;
	ortho = false;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	GameObject::Update();
}

void Camera::Set()
{
	{
		//        RT역행렬
		view = RT.Invert();
		if (ortho)
			proj = Matrix::CreateOrthographic(width, height, nearZ, farZ);
		else
			proj = Matrix::CreatePerspectiveFieldOfView(fov, width / height, nearZ, farZ);


		Matrix TVP = view * proj;
		TVP = TVP.Transpose();
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(VPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Matrix), &TVP, sizeof(Matrix));
		D3D->GetDC()->Unmap(VPBuffer, 0);
	}
	D3D->GetDC()->VSSetConstantBuffers(1, 1, &VPBuffer);
	D3D->GetDC()->RSSetViewports(1, viewport.Get11());

}

void Camera::ResizeScreen()
{
    ////viewport.x = 100.0f;
    ////viewport.y = 100.0f;

    //viewport.width = App.GetWidth();
    //viewport.height = App.GetHeight();

    //D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}

