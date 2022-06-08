#include "SandBox.h"

#include "imgui.h"
#include "Tests/HLSLParserTest.h"
#include "Tests/HJSONTesting.h"

#include "IntermediateRepresentation/IntermediateRepresentation.h"

#include "Memory/RefPtr.h"

SandBox::SandBox()
	: m_overlay("Test")
	, m_relativePosition(BlueBell::Vector2D::Zero)
	, m_absolutePosition(BlueBell::Vector2D::Zero)
{
	BB_LOG_INFO("Sandbox loading up...");

	CreateEntities();

	BlueBell::EventManager::GetInstance()->AddReceiverToEvent<BlueBell::OnImGuiRenderArgs>(BB_BIND_FUNC(OnImGuiRender, this));

	BlueBell::GameObject gameObject;

	BlueBell::CameraComponent* pCameraComponent = gameObject.CreateComponent<BlueBell::CameraComponent>(0, 0, 1960, 1080, -1, 1000);
	gameObject.CreateComponent<BlueBell::CameraControllerComponent>();
	
	float aspectRatio = 2564.0f / 990.0f;
	float fov = 45;
	pCameraComponent->ApplyPerspective(aspectRatio, fov);

	m_overlay.AddVariable(&m_relativePosition, "Relative position", BlueBell::Overlay::VariableType::Vector2D);
	m_overlay.AddVariable(&m_absolutePosition, "Absolute position", BlueBell::Overlay::VariableType::Vector2D);

	BlueBell::EventManager::GetInstance()->AddReceiverToEvent<BlueBell::OnInputArgs>(BB_BIND_FUNC(OnInput, this));

	//HJSONTesting testing;
	//testing.Test();

	//BlueFBX::Scene scene = BlueFBX::Scene(BlueBell::BlueBerry()->GetAllocator());

	//BlueFBX::Importer importer;
	//importer.Import("../../game/models/simpleCube2.fbx", scene);
}

SandBox::~SandBox()
{
}

void SandBox::CreateEntities()
{
	// Create entities here

}

void SandBox::OnImGuiRender(BlueBell::OnImGuiRenderArgs& args)
{
	m_overlay.Render();
}

void SandBox::OnInput(BlueBell::OnInputArgs& args)
{
	if (args.device == BlueBell::InputDevice::Mouse)
	{
		if (args.mouse.mouseType == BlueBell::InputMouseType::Position)
		{
			m_relativePosition = args.mouse.mousePosition.relative;
			m_absolutePosition = args.mouse.mousePosition.absolute;
		}
		else if (args.mouse.mouseType == BlueBell::InputMouseType::Button)
		{
			int i = 0;
		}
	}
}

BlueBell::Application* BlueBell::CreateApplication()
{
	return new SandBox();
}


