#pragma once
class Location
{
private:
	class Actor* location;

public:
	// @brief 트리거를 발동시킬 영역 생성자
	// @param scale 영역의 크기
	// @param pos 영역의 위치
	Location(Vector3 scale, Vector3 pos);
	~Location();
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

