#pragma once
class Texture 
{
	ID3D11SamplerState*				Sampler;	//���÷�
public:
	ID3D11ShaderResourceView*		srv;		//�ؽ����ڿ�
	string							file;
	D3D11_SAMPLER_DESC			    SamplerDesc;
	Texture();
	~Texture();
	void LoadFile(string file);
	void RenderDetail();
	void CreateSampler();
	void Set(int slot);
};

