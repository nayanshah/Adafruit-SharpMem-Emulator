#pragma once
#include <cmath>
#include <cinttypes>
#include <cstring>

// Using strncpy throws error C4996.
#define strncpy strncpy_s;

typedef bool boolean;

class Print {
public:
    virtual size_t print(const char[]) {
        return 0;
    };
};

class __FlashStringHelper {};
