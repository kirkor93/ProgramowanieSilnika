#include "GameObject.h"

GameObject::GameObject(WCHAR* textureName, int bitmapWidth, int bitmapHeight, float positionX, float positionY, int animationFramesCount)
{
	this->textureName = textureName;
	this->bitmapHeight = bitmapWidth;
	this->bitmapWidth = bitmapHeight;
	this->Position.x = positionX;
	this->Position.y = positionY;
	this->animationFramesCount = animationFramesCount;
}

bool GameObject::Initialize(ID3D11Device* device, int screenWidth, int screenHeight)
{
	m_Sprite2D = new Sprite2D(this->animationFramesCount);
	return this->m_Sprite2D->Initialize(device, screenWidth, screenHeight, this->textureName, this->bitmapWidth, this->bitmapHeight);
}
void GameObject::Shutdown()
{
	this->m_Sprite2D->Shutdown();
	delete m_Sprite2D;
	m_Sprite2D = 0;
}

bool GameObject::Render(ID3D11DeviceContext* deviceContext)
{
	return m_Sprite2D->Render(deviceContext, this->Position.x, this->Position.y);
}

bool GameObject::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	return this->m_Sprite2D->LoadTexture(device, filename);
}

int GameObject::GetIndexCount()
{
	return m_Sprite2D->GetIndexCount();
}
ID3D11ShaderResourceView* GameObject::GetTexture()
{
	return m_Sprite2D->GetTexture();
}

void GameObject::SetNextAnimationFrame()
{
	m_Sprite2D->SetNextAnimationFrame();
}

void GameObject::SetModelPosition()
{
	this->m_Sprite2D->SetPosition(this->Position);
}

void GameObject::SetModelRotation()
{
	this->m_Sprite2D->SetRotation(this->Rotation);
}

void GameObject::SetModelScale()
{
	this->m_Sprite2D->SetScale(this->Scale);
}

void GameObject::Translate(float posX, float posY)
{
	this->Position.x += posX;
	this->Position.y += posY;
}