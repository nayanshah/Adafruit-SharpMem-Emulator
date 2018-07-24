#pragma once

// This will set up the DisplayDriver class based on whether you are using the
// emulator, or coding for the real watch.

#ifdef ARDUINO
#include "Adafruit_SharpMem.h"
using DisplayDriver = Adafruit_SharpMem;
#else
#include "Adafruit_Iup.h"
using DisplayDriver = Adafruit_Iup;
#endif // ARDUINO
