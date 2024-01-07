#include "pch.h"
#include "BulletManager.h"

#include <Engine/Scene/SceneManager.h>

#include "Bullet.h"

BulletManager::BulletManager()
{
	pierceCount = 1;
}

BulletManager::~BulletManager()
{
	for (size_t i = 0; i < m_bulletPool.size(); i++)
	{
		delete m_bulletPool[i];
	}
	m_bulletPool.clear();
}

void BulletManager::Create()
{
	m_bulletTexture = jci::TextureManager::Instance()->CreateTexture("Assets/Texture/Bullet.png", 4, 1);
	jci::SceneManager::Instance()->GetCurrentScene();
	m_nextBullet = 0;
	for (int i = 0; i < POOLSIZE; i++)
	{
		jci::Entity* bulletObj = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();
		bulletObj->SetActive(false);
		bulletObj->GetComponent<jci::Transform>()->SetPosition(vec2(-15000000000000.0f));

		jci::SpriteRenderer* sr = bulletObj->AddComponent<jci::SpriteRenderer>();
		sr->SetTexture(m_bulletTexture);
		sr->SetSize(vec2(0.6f, 0.6f));

		jci::Animation* anim = bulletObj->AddComponent<jci::Animation>();
		anim->SetTimeBetweenFrames(.15f);
		anim->SetAnimationCount(4);
		anim->SetLooping(false);

		jci::BoxCollider* bc = bulletObj->AddComponent<jci::BoxCollider>();
		bc->SetBodyType(jci::BodyType::Kinematic);
		bc->SetTrigger(true);
		bulletObj->SetTag("Bullet");
		bulletObj->GetComponent<jci::BoxCollider>()->SetSize({ 0.1f, 0.05f });
		Bullet* aBullet = new Bullet(bulletObj);
		aBullet->PierceUp(pierceCount);
		m_bulletPool.push_back(aBullet);
	}
}

void BulletManager::Update(float dt)
{
	for (int i = 0; i < m_bulletPool.size(); i++)
	{
		if (m_bulletPool.at(i)->GetMove())
		{
			m_bulletPool.at(i)->m_body->GetComponent<jci::Transform>()->AddToPosition(m_bulletPool.at(i)->m_direction * dt);
		}
	}
}

void BulletManager::ShootBullet(vec2 d, vec2 playPos, float angle)
{
	if (m_nextBullet > POOLSIZE-1)
	{
		m_nextBullet = 0;
	}
	m_bulletPool.at(m_nextBullet)->SetActive(playPos, d, angle);
	m_bulletPool.at(m_nextBullet)->PierceUp(pierceCount);
	m_nextBullet += 1;
}

void BulletManager::SetBulletDamage(int bullDmg)
{
	for (auto i : m_bulletPool)
	{
		i->SetDmg(bullDmg);
	}
}

int BulletManager::GetBulletDamage()
{
	return m_bulletPool.at(m_nextBullet)->GetDmg();
}
