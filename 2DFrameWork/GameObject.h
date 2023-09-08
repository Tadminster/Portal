#pragma once

enum class ObType
{
	GameObject,
	Actor,
	Camera
};

class GameObject : public Transform
{
	friend class Actor;
	//static -> non static
	//member -> method
	//private -> protected -> pulic

	//static
private:
	static GameObject* axis;
public:
	static GameObject* Create(string name = "GameObject");
	static void CreateStaticMember();
	static void DeleteStaticMember();
	static void RenderAxis();


	//non static
protected:
	ObType						type;

public:
	shared_ptr<Mesh>			mesh;
	shared_ptr<Shader>			shader;
	shared_ptr<Texture>			texture;



	class Collider*				collider;
	string						name;
	bool						visible;
	class Actor*				root;
	map<string, GameObject*>	children;

protected:
	GameObject();
	virtual ~GameObject();
	void	SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void	LoadObject(Xml::XMLElement* This);

public:
	virtual void	Release();
	void			AddChild(GameObject* child);
	virtual bool	RenderHierarchy();
	virtual void	RenderDetail();

	virtual void	Update();
	virtual void	Render();
	bool            Intersect(GameObject* target);
	bool            Intersect(Ray Ray, Vector3& Hit);
};

//배우
class Actor : public GameObject
{
public:
	static Actor* Create(string name = "Actor");
protected:
	Actor();
	virtual ~Actor();
public:
	string file;
	//해시테이블
	unordered_map<string, GameObject*>	obList;
public:
	void			ReleaseMember();
	GameObject*		Find(string name);
	bool            DeleteObject(string Name);
	bool            DeleteAllObject(string Name);
	virtual void	RenderDetail();
	void			SaveFile(string file);
	void			LoadFile(string file);
};