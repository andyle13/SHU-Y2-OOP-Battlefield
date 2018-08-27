#include <Windows.h>
#include <crtdbg.h>

#include "BattleField.h"

/*
  Please note that you should fully integrate your OO-based designed into BattleField to make the most of OO techniques.  This will actually reduce some of the
  the provided code since I've avoided giving you any OO-classes and I've had to work around the pure use of imperative-style
  There is some really horrible code in the skeleton to help you with the processes, so please rework in the context of your OO-based designs
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int show)
{
#ifdef _DEBUG
  //_CrtSetBreakAlloc(101);
  _onexit(_CrtDumpMemoryLeaks);
#endif

  BattleField game(hInstance);

  return 0;
}