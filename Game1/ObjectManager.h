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

	// @brief �������� �����ϰ� ����Ʈ�� �߰�
	// @param structure ������
	// @param position �������� ��ġ
	// @param rotationY �������� y�� ȸ����
	void	AddStructure(Structure* structure, Vector3 position = Vector3(), float rotationY = 0.0f);
	list<class Structure*>& GetStructures() { return structures; }
};