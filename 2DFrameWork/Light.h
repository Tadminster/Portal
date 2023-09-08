#pragma once
class Light : public Singleton<Light>
{
private:
	struct LightDesc
	{
		Vector2 screenPos; //스크린좌표
		float radius; //반지름크기
		float select; //남는값
		Vector4 lightColor; //조명 색
		Vector4 outColor; //외곽 색
	} light;
	ID3D11Buffer* lightBuffer;
public:
	Light();
	~Light();
	LightDesc* Get() { return &light; }
	void        Set();
};

