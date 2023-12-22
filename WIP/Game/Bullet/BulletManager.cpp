#include "pch.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
	
}

void BulletManager::Create()
{
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png");
	jci::SceneManager::Instance()->GetCurrentScene();
	nextBullet = 0;
	for (int i = 0; i < POOLSIZE; i++)
	{
		jci::Entity* bulletObj = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();
		bulletObj->SetActive(false);
		bulletObj->GetComponent<jci::Transform>()->SetPosition(vec2(-15000000000000.0f));
		bulletObj->AddComponent<jci::SpriteRenderer>()->SetTexture(m_bulletTexture);
		bulletObj->GetComponent<jci::SpriteRenderer>()->SetSize({ 0.35f, 0.1f });
		jci::BoxCollider* bc = bulletObj->AddComponent<jci::BoxCollider>();
		bc->SetBodyType(jci::BodyType::Kinematic);
		bc->SetTrigger(true);
		bulletObj->SetTag("Bullet");
		bulletObj->GetComponent<jci::BoxCollider>()->SetSize({ 0.1f, 0.05f });
		Bullet* aBullet = new Bullet(bulletObj);
		bulletPool.push_back(aBullet);
	}
}

void BulletManager::Update(float dt)
{
	for (int i = 0; i < bulletPool.size(); i++)
	{
		if (bulletPool.at(i)->GetMove())
		{
			bulletPool.at(i)->body->GetComponent<jci::Transform>()->AddToPosition(bulletPool.at(i)->direction * dt);
		}
		if (bulletPool.at(i)->GetSpawnTime() + 5000 <= SDL_GetTicks() && bulletPool.at(i)->GetMove())
		{
			//DLOG("Despawn");
			//bulletPool.at(i)->Delete();
		}
	}
}

void BulletManager::ShootBullet(vec2 d, vec2 playPos)
{
	if (nextBullet > POOLSIZE-1)
	{
		nextBullet = 0;
	}
	bulletPool.at(nextBullet)->SetActive(playPos, d);
	/*bulletPool.at(nextBullet)->body->GetComponent<jci::Transform>()->SetPosition(playPos);
	bulletPool.at(nextBullet)->bulletFire(d);*/
	nextBullet += 1;
}