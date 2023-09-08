
cbuffer VS_W : register(b0)
{
	matrix World;
}

cbuffer VS_VP : register(b1)
{
	matrix ViewProj;
}

Texture2D TextureD : register(t1);
SamplerState SamplerD : register(s1);