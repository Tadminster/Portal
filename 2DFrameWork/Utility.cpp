#include "framework.h"
void Utility::Replace(string* str, string comp, string rep)
{
    string temp = *str;

    size_t start_pos = 0;
    while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
    {
        temp.replace(start_pos, comp.length(), rep);
        start_pos += rep.length();
    }
    *str = temp;
}

void Utility::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}
wstring Utility::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}
string Utility::ToString(wstring value)
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}

Ray Utility::MouseToRay(Camera* Cam)
{
	Vector3 Mouse = INPUT->position;

	Mouse.x -= Cam->viewport.x;
	Mouse.y -= Cam->viewport.y;

	Vector2 MousePos;

	//ndc로의 변환
	MousePos.x = ((2.0f * Mouse.x) / Cam->viewport.width - 1.0f);
	MousePos.y = ((-2.0f * Mouse.y) / Cam->viewport.height + 1.0f);

	// view로의 변환
	MousePos.x /= Cam->proj._11;
	MousePos.y /= Cam->proj._22;

	Ray CamToMouse;
	CamToMouse.position = Cam->GetWorldPos();
	CamToMouse.direction = Vector3(MousePos.x, MousePos.y, 1.0f);
	Matrix inverse = Cam->view.Invert();
	CamToMouse.direction = Vector3::TransformNormal(CamToMouse.direction, inverse);
	CamToMouse.direction.Normalize();
	return CamToMouse;
}

Vector3 Utility::MouseToNDC(Camera* Cam)
{
	Vector3 Mouse = INPUT->position;

	Mouse.x -= Cam->viewport.x;
	Mouse.y -= Cam->viewport.y;

	Vector3 MousePos;

	//ndc로의 변환
	MousePos.x = ((2.0f * Mouse.x) / Cam->viewport.width - 1.0f);
	MousePos.y = ((-2.0f * Mouse.y) / Cam->viewport.height + 1.0f);
	MousePos.z = 0.0f;
	return MousePos;
}
