#include "GameObject.h"

GameObject::GameObject(char shape, int x, int y) 
	: 
	m_pos(x, y), 
	m_dim(1, 1), 
	m_shape(nullptr)
{
	this->m_shape = (char*)new char[m_dim.size() + 1];
	this->m_shape[0] = shape;
	this->m_shape[m_dim.size()] = '\0';
}

GameObject::~GameObject()
{
	delete m_shape;
}
