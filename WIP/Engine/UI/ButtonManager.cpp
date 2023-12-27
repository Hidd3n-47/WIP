#include "pch.h"
#include "ButtonManager.h"

#include "Camera/Camera.h"
#include "ECS/ComponentManager.h"
#include "Input/InputManager.h"

namespace jci {

ButtonManager* ButtonManager::m_instance = nullptr;

void ButtonManager::Update()
{
	ASSERT(m_screenWidth != -1 && m_screenHeight != -1, "Screen dimensions have not been set correctly.");
	ASSERT(m_camera, "Invalid camera cached.");

	vec2 mousePosition = InputManager::Instance()->GetMousePosition();
	bool mouseDown = InputManager::Instance()->IsKeyPressed(Button_Left);
	
	UiButton* buttons = ComponentManager::Instance()->GetComponentVector<UiButton>();
	for (entId i = 0; i < ComponentManager::Instance()->GetComponentCount(ComponentTypes::UiButton); i++)
	{
		vec2 buttonPosition = GetAnchorPosition(buttons[i].m_anchorPoint) + buttons[i].m_padding;

		// Scale between 0.0f-1.0f, multiply by 2 and subtract 1 to get -1.0f-1.0f, half extents to get -cam.x-cam.x and similarly for cam.y.
		vec2 mouseP = (mousePosition / vec2(m_screenWidth, m_screenHeight) * 2.0f - 1.0f) * m_camera->GetHalfExtents();
		// Flip the y-axis due to SDL measuring from top left.
		mouseP.y *= -1.0f;
		
		vec2 positionVector = abs(buttonPosition - mouseP);

		*buttons[i].m_quad.position = buttonPosition + m_camera->GetPosition();
		
		vec2 size = buttons[i].m_size * 0.5f;
		if (positionVector.x >= size.x  || positionVector.y >= size.y)
		{
			continue;
		}

		if (buttons[i].m_buttonMethods)
		{
			if (mouseDown)
			{
				if (buttons[i].m_pressed)
				{
					// Return if the button is already pressed.
					return;
				}

				buttons[i].m_buttonMethods->OnButtonPress();
				buttons[i].m_pressed = true;
			}
			else
			{
				buttons[i].m_buttonMethods->OnButtonHover();
				buttons[i].m_pressed = false;
			}
		}
	}
}
vec2 ButtonManager::GetAnchorPosition(AnchorPoints anchor)
{
	switch (anchor)
	{
	case AnchorPoints::TopLeft:
		return vec2(-m_camera->GetHalfExtents().x, m_camera->GetHalfExtents().y);
	case AnchorPoints::TopMiddle:
		return vec2(0.0f, m_camera->GetHalfExtents().y);
	case AnchorPoints::TopRight:
		return vec2(m_camera->GetHalfExtents());
	case AnchorPoints::Middle:
		return vec2(0.0f);
	case AnchorPoints::BotRight:
		return vec2(m_camera->GetHalfExtents().x, -m_camera->GetHalfExtents().y);
	case AnchorPoints::BotMiddle:
		return vec2(0.0f, -m_camera->GetHalfExtents().y);
	case AnchorPoints::BotLeft:
		return vec2(-m_camera->GetHalfExtents());
	default:
		ASSERT(false, "Unhandled anchor position.");
		return vec2(-1.0f);
	}
}

} // Namespace jci.