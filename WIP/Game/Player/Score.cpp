#include "pch.h"
#include "Score.h"
#include "fstream"

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
	/*std::ifstream hsFile("Highscore.txt");
	if (!hsFile.fail())
	{
		std::ofstream hsFile("Highscore.txt");
	}*/
}

void Score::Highscore()
{
	m_scoreStr = jci::IOManager::Instance()->LoadTextFile("Assets/Highscore.txt");
	DLOG(m_scoreStr);
	if (m_scoreStr == "")
	{
		m_highScore = 0;
	}
	else
	{
		m_highScore = std::stoi(m_scoreStr);
	}
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