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

	void	AddStructure(Structure* structure, Vector3 position = Vector3(), float rotationY = 0.0f);
	list<class Structure*>& GetStructures() { return structures; }
};