#include "pch.h"
#include "BulletImpact.h"

BulletImpact::BulletImpact(uint32 textureId)
{
	m_entity = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();

	jci::SpriteRenderer* sr = m_entity->AddComponent<jci::SpriteRenderer>();
	sr->SetTexture(textureId);
	sr->SetSize(vec2(0.5f));
	sr->SetLayer(2);
	jci::Animation* anim = m_entity->AddComponent<jci::Animation>();
	anim->SetAnimationCount(3);
	anim->SetTimeBetweenFrames(0.05f);
	anim->SetLooping(false);

	m_entity->SetActive(false);
}

BulletImpact::~BulletImpact()
{

}

void BulletImpact::SetActive(vec2 position)
{
	m_entity->SetActive(true);
	m_entity->GetComponent<jci::Transform>()->SetPosition(position);
	m_entity->GetComponent<jci::Animation>()->SetAnimationCount(3);
}

void BulletImpact::Deactivate()
{
	m_entity->SetActive(false);
}
