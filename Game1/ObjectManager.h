#pragma once
class ObjectManager
{
private:
	list<class Structure*> structures;

public:
	~ObjectManager() {};

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();
	void	RenderHierarchy();

	// @brief 구조물을 생성하고 리스트에 추가
	// @param structure 구조물
	// @param position 구조물의 위치
	// @param rotationY 구조물의 y축 회전값
	void	AddStructure(Structure* structure, Vector3 position = Vector3(), float rotationY = 0.0f);
	list<class Structure*>& GetStructures() { return structures; }
};