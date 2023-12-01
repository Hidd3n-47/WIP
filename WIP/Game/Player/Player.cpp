#include "pch.h"
#include "Player.h"
#include <Game/Bullet/Bullet.h>

#include <Engine/src/Engine.h>
#include <Engine/Graphics/Texture/Texture.h>

//Player* Player::m_instance = nullptr;

Player::Player() :
	m_width((float)jci::Engine::Instance()->GetScreenWidth()),
	m_height((float)jci::Engine::Instance()->GetScreenHeight())
{
	m_currentScene = nullptr;
	playChar = nullptr;
}

Player::~Player()
{

}

void Player::Create(jci::Scene* scene, Levels map)
{
	uint32 text = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/circ.png");
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png");
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	//scene = jci::SceneManager::Instance()->GetCurrentScene();
	playChar = m_currentScene->CreateEmptyEntity();
	playChar->GetComponent<jci::Transform>()->SetPosition({ map.getSpawnPointX(),  map.getSpawnPointY() });
	playChar->AddComponent<jci::SpriteRenderer>()->SetTexture(text);
	jci::TextureManager::Instance()->GetTexture(jci::EngineTextureIndex::NoTexture);
	playChar->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
}

void Player::FireGun()
{
	DLOG("Firing");
	//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
	int num = bulletPool.size() - 1;
	jci::Entity* bulletObj;
	bulletObj = m_currentScene->CreateEmptyEntity();
	bulletObj->GetComponent<jci::Transform>()->SetPosition(playChar->GetComponent<jci::Transform>()->GetPosition());
	bulletObj->AddComponent<jci::SpriteRenderer>()->SetTexture(m_bulletTexture);
	bulletObj->GetComponent<jci::SpriteRenderer>()->SetSize({0.1f, 0.05f});
	bulletObj->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	bulletObj->GetComponent<jci::BoxCollider>()->SetSize({ 0.1f, 0.05f });

	vec2 moveDirection = jci::InputManager::Instance()->GetMousePosition() - vec2(m_width * 0.5f, m_height * 0.5f);
	moveDirection = glm::normalize(moveDirection);
	moveDirection.y *= -1;
	
	Bullet* aBullet = new Bullet(bulletObj, moveDirection);
	bulletPool.push_back(aBullet);
	//bulletPool.at(num)->GetComponent<jci::Transform>()->SetPosition({});
}

void Player::Update()
{
	vec2 direction = vec2(0.0f);

	const float SPEED = 0.05f;

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_w))
	{
		direction += vec2(0.0f, SPEED);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_s))
	{
		direction += vec2(0.0f, -SPEED);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_a))
	{
		direction += vec2(-SPEED, 0.0f);
	}
	if (jci::InputManager::Instance()->IsKeyPressed(jci::Keycode_d))
	{
		direction += vec2(SPEED, 0.0f);
	}

	glm::normalize(direction);

	playChar->GetComponent<jci::Transform>()->AddToPosition(direction);

	if (jci::InputManager::Instance()->IsKeyPressed(jci::Button_Left))
	{
		FireGun();
	}
	jci::SceneManager::Instance()->GetCurrentScene()->GetCamera()->SetPosition(playChar->GetComponent<jci::Transform>()->GetPosition());
	for(Bullet* b : bulletPool)
	{
		b->body->GetComponent<jci::Transform>()->AddToPosition(b->direction);
		DLOG("(" + std::to_string(b->body->GetComponent<jci::Transform>()->GetPosition().x) + "," + std::to_string(b->body->GetComponent<jci::Transform>()->GetPosition().y) + ")");
	}
}