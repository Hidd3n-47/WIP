#pragma once

#include <Engine/Collision/ICollision.h>

class Levels;
struct Bullet;

namespace jci {
class Scene;
class Entity;
} // Namespace jci.

//Firegun thing
//Create projectile object

class Player : public jci::ICollision
{
public:
	Player();
	~Player();
	void Create(jci::Scene* scene, Levels map);
	void FireGun(float time);
	void Update(float time);

	inline vec2		GetPos()		const	{ return *m_position; }
	inline vec2*	GetPosPointer()	const	{ return m_position; }
private:
	//static Player* m_instance;
	std::vector<Bullet*>	bulletPool;
	jci::Entity*			m_playChar;

	jci::Entity*	m_knife;
	jci::Scene*		m_currentScene;
	uint32			m_bulletTexture;
	vec2*			m_position;

	const float m_width;
	const float m_height;

	bool		m_canFire;
	bool		m_isDashing;
	bool		m_isMelee;
	float		m_fireTime;
	float		m_gunfireTimer;
	float		m_dashTimer;
	float		m_meleeTimer;
	int			m_reloadMeleeSpeed;
	int			m_reloadSpeed; //GET FROM GUN LATER
	int			m_reloadDashSpeed;
	vec2		m_backupDirection = vec2(0.0f);
	uint32		m_knifeTexture;
	uint32		m_blankTexture;

	// Player Collision Methods.
	void OnCollisionEnter(jci::Entity* other) final;
	void OnCollisionStay(jci::Entity* other) final;
	void OnCollisionExit() final;

};

