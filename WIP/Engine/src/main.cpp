#include "pch.h"

#include "src/Memory.h"

#include "Engine.h"

int main(int argc, char** argv)
{
	jci::Engine::Instance()->Init();
	jci::Engine::Instance()->Run();
	jci::Engine::Instance()->Destroy();

	PrintMemory();
	system("PAUSE");
	return 0;
}