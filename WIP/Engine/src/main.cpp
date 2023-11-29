#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include "src/Memory.h"

#include "Engine.h"

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	jci::Engine::Instance()->Init();
	jci::Engine::Instance()->Run();
	jci::Engine::Instance()->Destroy();

	//PrintMemory();
#ifdef _DEBUG
	system("PAUSE");
#endif
	return 0;
}