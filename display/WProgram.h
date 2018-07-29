#pragma once

// Partial implementation of Arduino's WProgram.h based on: https://github.com/Railstars/ARMduino/blob/master/WProgram.h

#include <cmath>
#include <cinttypes>
#include <cstdio>
#include <cstring>

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)

// Using strncpy throws error C4996.
#define strncpy strncpy_s;

typedef bool boolean;

// Following types are used by Adafruit's GFX library

class Print {
public:
    virtual size_t print(const char[]) {
        return 0;
    };
};

class __FlashStringHelper {};
