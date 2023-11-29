#include "pch.h"
#include "Player.h"
#include <Game/Bullet/Bullet.h>



//Player* Player::m_instance = nullptr;

Player::Player()
{
	m_currentScene = nullptr;
	playChar = nullptr;
}

Player::~Player()
{

}

void Player::Create(jci::Scene* scene, Levels map)
{
	m_currentScene = jci::SceneManager::Instance()->GetCurrentScene();
	//scene = jci::SceneManager::Instance()->GetCurrentScene();
	playChar = m_currentScene->CreateEmptyEntity();
	playChar->GetComponent<jci::Transform>()->SetPosition({ map.getSpawnPointX(),  map.getSpawnPointY() });
	playChar->AddComponent<jci::SpriteRenderer>();
	playChar->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
}

void Player::FireGun()
{
	jci::DLOG("Firing");
	//find angle: (y-jci::InputManager::Instance()->GetMousePosition().y)/(x-jci::InputManager::Instance()->GetMousePosition().x)
	int num = bulletPool.size() - 1;
	jci::Entity* bulletObj;
	bulletObj = m_currentScene->CreateEmptyEntity();
	bulletObj->GetComponent<jci::Transform>()->SetPosition(playChar->GetComponent<jci::Transform>()->GetPosition());
	bulletObj->AddComponent<jci::SpriteRenderer>()->SetTexture(new jci::Texture("Assets/Texture/Bullet.png"));
	bulletObj->GetComponent<jci::SpriteRenderer>()->SetSize({0.1f, 0.05f});
	//bulletObj->AddComponent<jci::BoxCollider>()->SetBodyType(jci::BodyType::Kinematic);
	//bulletObj->GetComponent<jci::BoxCollider>()->SetSize({ 0.1f, 0.05f });
	vec2 moveDirection = vec2(0.0f);
	
	/*moveDirection.x = x - jci::InputManager::Instance()->GetMousePosition().x;
	moveDirection.y = y - jci::InputManager::Instance()->GetMousePosition().y;  //THIS MAKES THE BULLET SPAWN AT -420?????
	glm::normalize(moveDirection);*/
	
	moveDirection.x = 0.05;
	moveDirection.y = 0;
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
		jci::DLOG("(" + std::to_string(b->body->GetComponent<jci::Transform>()->GetPosition().x) + "," + std::to_string(b->body->GetComponent<jci::Transform>()->GetPosition().y) + ")");
	}
}