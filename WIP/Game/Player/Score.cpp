#include "pch.h"
#include "Score.h"

#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Entity.h>

Score* Score::m_instance = nullptr;

void Score::Init()
{
	m_ui = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();

	jci::UiText* ut = m_ui->AddComponent<jci::UiText>();
	ut->SetTexture(jci::TextureManager::Instance()->CreateTexture("Assets/Texture/ScoreFont.png", 10, 1));
	ut->SetAnchorPoint(jci::AnchorPoints::BotRight);
	ut->SetTextAlign(jci::TextAlignment::Right);
	ut->SetPadding(vec2(-0.35f, 0.35f));
	ut->SetText(m_score, 24);
}

void Score::UpdateUi()
{
	m_ui->GetComponent<jci::UiText>()->SetText(m_score);
}