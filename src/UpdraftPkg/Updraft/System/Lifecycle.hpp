extern "C" {
#include <Uefi.h>
#include <Protocol/SimpleTextIn.h>
}

#include "../Utils/Types.hpp"

class Lifecycle
{
  static uint8 s_fps;

  static uint32 s_frameCount;

  static EFI_EVENT s_timerEvent;

  static EFI_EVENT s_eventList[1];

  static uintn s_eventIndex;

  static bool s_isExitting;

  static void CreateTimerEvent();

  static void SetTimer();

  static void CancelTimer();

  static void ResetTimer();

  static void WaitForTimerEvent();

public:
  static void Initialize();

  static bool Update();

  static void Exit();

  static uint8 FPS();

  static void FPS(const uint8 _fps);

  static uint32 FrameCount();
};
