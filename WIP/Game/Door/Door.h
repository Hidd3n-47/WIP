#pragma once
class Door
{
private:
	jci::Entity* door;
public:
	Door();
	~Door();
	jci::Entity* Create(vec2 point, uint32 TextureID);
	void setTexture(uint32 TextureID);
	jci::Entity* getDoor();
};

