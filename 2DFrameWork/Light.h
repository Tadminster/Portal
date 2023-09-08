#pragma once
class Light : public Singleton<Light>
{
private:
	struct LightDesc
	{
		Vector2 screenPos; //��ũ����ǥ
		float radius; //������ũ��
		float select; //���°�
		Vector4 lightColor; //���� ��
		Vector4 outColor; //�ܰ� ��
	} light;
	ID3D11Buffer* lightBuffer;
public:
	Light();
	~Light();
	LightDesc* Get() { return &light; }
	void        Set();
};

