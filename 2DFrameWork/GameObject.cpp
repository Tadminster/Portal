#include "framework.h"

GameObject* GameObject::Create(string name)
{
	GameObject* temp = new GameObject();
	temp->name = name;
	temp->type = ObType::GameObject;
	return temp;
}

GameObject* GameObject::axis = nullptr;
void GameObject::CreateStaticMember()
{
	axis = new GameObject();
	axis->mesh = RESOURCE->meshes. Load("1.Transform.mesh");
	axis->shader = RESOURCE->shaders.Load("1.Cube.hlsl");
}

void GameObject::DeleteStaticMember()
{
	SafeDelete(axis);
}

void GameObject::RenderAxis()
{
	if (not GUI->target)return;
	GameObject* target = GUI->target;
	axis->S = Matrix::CreateScale(App.GetHeight() * 0.1f);
	if (not target->parent)
		axis->W = axis->S * target->T;
	else if (worldPos)
		axis->W = axis->S * Matrix::CreateTranslation(target->GetWorldPos());
	else
		axis->W = axis->S * target->T * target->parent->W;

	axis->Render();
}

GameObject::GameObject()
{
	root = nullptr;
	
	visible = true;
	name = " ";

	mesh = nullptr;
	shader = nullptr;
	collider = nullptr;
	texture = nullptr;

	//mesh = make_shared<Mesh>();

	/*mesh = new Mesh();
	shader = new Shader();
	shader->LoadFile("0.Cube.hlsl");*/
}

GameObject::~GameObject()
{
	SafeReset(mesh);
	SafeReset(shader);
	SafeDelete(collider);
}

void GameObject::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}


void GameObject::AddChild(GameObject* child)
{
	if (root->Find(child->name))
		return;

	root->obList[child->name] = child;
	children[child->name] = child;

	child->parent = this;
	child->root = root;
}

void GameObject::Update()
{
	Transform::Update();

	if (collider)
		collider->Update(this);

	for (auto it = children.begin(); it != children.end(); it++)
		it->second->Update();
}

void GameObject::Render()
{
	if (visible)
	{
		if (mesh and shader)
		{
			mesh->Set();
			Transform::Set();
			shader->Set();

			if (texture)
				texture->Set(1);

			D3D->GetDC()->DrawIndexed(mesh->indexCount, 0, 0);
		}

		for (auto it = children.begin(); it != children.end(); it++)
			it->second->Render();
	}

	if (collider)
		collider->Render();
}

bool GameObject::Intersect(GameObject* target)
{
	if (collider and target->collider)
	{
		return collider->Intersect(target->collider);
	}
	return false;
}

bool GameObject::Intersect(Ray Ray, Vector3& Hit)
{
	if (collider)
	{
		return collider->Intersect(Ray, Hit);
	}
	return false;
}

Actor* Actor::Create(string name)
{
	Actor* temp = new Actor();
	temp->name = name;
	temp->type = ObType::Actor;
	return temp;
}

Actor::Actor()
{
	root = this;
}

Actor::~Actor()
{
}


//하위노드 삭제
void Actor::ReleaseMember()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		it->second->Release();
	}
	obList.clear();
	children.clear();
}

GameObject* Actor::Find(string name)
{
	auto it = obList.find(name);
	//찾았다
	if (it != obList.end())
	{
		return it->second;
	}
	return nullptr;
}

bool Actor::DeleteObject(string Name)
{
	if (Name == name) return false;

	auto temp = obList.find(Name);

	if (temp == obList.end())  return false;

	//지워질대상,지워질대상의 부모 포인터
	GameObject* Target = temp->second;
	GameObject* Parent = temp->second->parent;
	//부모리스트에서 타겟 비우기
	Parent->children.erase(Parent->children.find(Name));

	for (auto it = Target->children.begin();
		it != Target->children.end(); it++)
	{
		Parent->children[it->second->name] = it->second;
		it->second->parent = Parent;
		//SafeRelease(it->second);
	}
	SafeDelete(Target);
	obList.erase(temp);
	return true;
}

bool Actor::DeleteAllObject(string Name)
{
	//루트삭제 방지
	if (Name == name) return false;

	//리스트에서 찾기
	auto temp = obList.find(Name);
	//없으면 되돌아기
	if (temp == obList.end())  return false;

	//지워질대상,지워질대상의 부모 포인터
	GameObject* Target = temp->second;
	GameObject* Parent = temp->second->parent;
	//부모리스트에서 타겟 비우기
	Parent->children.erase(Parent->children.find(Name));
	root->obList.erase(root->obList.find(Name));

	//number;

	while (1)
	{
		if (Target->children.empty())break;

		auto it = Target->children.begin();

		DeleteAllObject(it->first);
	}
	SafeDelete(Target);
	return true;



}

