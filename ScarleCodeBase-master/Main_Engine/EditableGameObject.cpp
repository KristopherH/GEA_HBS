#include "EditableGameObject.h"
#include "TextBox.h"
#include "Object_Factory.h"

EditableGameObject::EditableGameObject()
	:GameObject()
{
}

EditableGameObject::EditableGameObject(Sprite * sprite, std::string _name, std::string _tag)
	:GameObject(sprite, _name, _tag)
{
}

EditableGameObject::EditableGameObject(Sprite * _sprite)
	:GameObject(_sprite)
{
}

EditableGameObject::EditableGameObject(std::vector<Sprite*> _sprite)
	:GameObject(_sprite)
{
}

EditableGameObject::~EditableGameObject()
{
	for (auto& ui_go : ui_elements)
	{
		delete ui_go;
	}
	ui_elements.clear();
}

bool EditableGameObject::Update(float dt)
{
	if (reToggleEditing)
	{
		toggleEditing();
		toggleEditing();
		reToggleEditing = false;
	}
	for (auto& ui_go : ui_elements)
	{
		ui_go->Update(dt);
	}
	return GameObject::Update(dt);
}

bool EditableGameObject::Draw()
{
	for (auto& ui_go : ui_elements)
	{
		ui_go->Draw();
	}
	return GameObject::Draw();
}

void EditableGameObject::toggleEditing()
{
	editing = !editing;
	if (editing)
	{
		TextBox* nameEdit = new TextBox(new Sprite(ObjectFactory::texture_pool[BUTTON]), "NameChanger", "NULL", name);
		nameEdit->setSize(new Vec2(max(size.x, 100), 50));
		nameEdit->setPosition(new Vec2(position.x, position.y - nameEdit->getSize().y));
		nameEdit->setOnEnterCallback([this, nameEdit]()
		{
			name = nameEdit->getText();
			return;
		});
		nameEdit->setScreenSpace(false);
		ui_elements.push_back(nameEdit);
	}
	else
	{
		for (auto& ui_go : ui_elements)
		{
			delete ui_go;
		}
		ui_elements.clear();
	}
	return;
}

void EditableGameObject::movePosition(Vec2 * _translation)
{
	for (auto& ui_go : ui_elements)
	{
		ui_go->movePosition(_translation);
	}
	GameObject::movePosition(_translation);
}

void EditableGameObject::setPosition(Vec2 * _pos)
{
	movePosition(new Vec2(*_pos - position));
}
