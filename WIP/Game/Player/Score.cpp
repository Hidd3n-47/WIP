/***
	=============== Coded by Christian Lewis-Monto. ===============
																	***/
#include "pch.h"
#include "Score.h"

#include <Engine/Scene/SceneManager.h>
#include <Engine/ECS/Entity.h>
#include <Engine/IO/IOManager.h>

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

	std::string scoreString = jci::IOManager::Instance()->LoadTextFile("Assets/Highscore.txt");
	DLOG(scoreString);

	m_highScore = scoreString == "" ? 0 : std::stoi(scoreString);

	HighscoreUI();
}

void Score::HighscoreUI()
{
	m_startUi = jci::SceneManager::Instance()->GetCurrentScene()->CreateEmptyEntity();

	jci::UiText* uit = m_startUi->AddComponent<jci::UiText>();
	uit->SetTexture(jci::TextureManager::Instance()->CreateTexture("Assets/Texture/ScoreFont.png", 10, 1));
	uit->SetAnchorPoint(jci::AnchorPoints::Middle);
	uit->SetTextAlign(jci::TextAlignment::Center);
	uit->SetPadding(vec2(-0.35f, 0.35f));
	uit->SetText(m_highScore, 24);
}

void Score::UpdateUi()
{
	m_ui->GetComponent<jci::UiText>()->SetText(m_score);
}

void Score::Destroy()
{
	if (m_score > m_highScore)
	{
		jci::IOManager::Instance()->SaveToFile(std::to_string(m_score), "Assets/Highscore.txt");
	}
	delete m_instance;
}