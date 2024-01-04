#include "pch.h"
#include "BulletManager.h"

BulletManager::~BulletManager()
{
	for (size_t i = 0; i < bulletPool.size(); i++)
	{
		delete bulletPool[i];
	}
	bulletPool.clear();
}

void BulletManager::Create()
{
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png", 4, 1);
	jci::SceneManager::Instance()->GetCurrentScene();
	nextBullet = 0;
	for (int i = 0; i < POOLSIZE; i++)
	{
		jci::Entity* bulletObj = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();
		bulletObj->SetActive(false);
		bulletObj->GetComponent<jci::Transform>()->SetPosition(vec2(-15000000000000.0f));

		jci::Animation* anim = bulletObj->AddComponent<jci::Animation>();
		anim->SetTexture(m_bulletTexture);
		anim->SetSize(vec2(0.6f, 0.6f));
		anim->SetTimeBetweenFrames(.15f);
		anim->SetAnimationCount(4);
		anim->SetLooping(false);

		//bulletObj->AddComponent<jci::SpriteRenderer>()->SetTexture(m_bulletTexture);
		//bulletObj->GetComponent<jci::SpriteRenderer>()->SetSize({ 0.35f, 0.1f });

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
	}
}

void BulletManager::ShootBullet(vec2 d, vec2 playPos, float angle)
{
	if (nextBullet > POOLSIZE-1)
	{
		nextBullet = 0;
	}
	bulletPool.at(nextBullet)->SetActive(playPos, d, angle);
	
	nextBullet += 1;
}

void BulletManager::SetBulletDamage(int bullDmg)
{
	for (auto i : bulletPool)
	{
		i->SetDmg(bullDmg);
	}
}

int BulletManager::GetBulletDamage()
{
	return 	bulletPool.at(nextBullet)->GetDmg();
}
