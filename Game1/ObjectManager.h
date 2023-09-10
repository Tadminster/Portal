#pragma once
class ObjectManager
{
private:
	list<class Feature*> features;

public:
	~ObjectManager() {};

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();
	void	RenderHierarchy();

	void	AddFeature(Feature* feature, Vector3 position = Vector3());
	list<class Feature*>& GetFeatures() { return features; }
};