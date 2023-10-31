#include "pch.h"

#include "Engine.h"

int main(int argc, char** argv)
{
	Engine::Instance()->Init();
	Engine::Instance()->Run();
	Engine::Instance()->Destroy();

	return 0;
}