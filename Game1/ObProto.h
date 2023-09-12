#include "stdafx.h"

#pragma once
class ObProto
{
protected:
	class Actor* actor;
	
	
	Vector3 dir			{};
	float	gravity		{ 0 };
	float	moveSpeed	{ 0 };

public:
	ObProto():actor(nullptr) {};
	virtual ~ObProto() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;

	Actor* GetActor() { return actor; }
};

