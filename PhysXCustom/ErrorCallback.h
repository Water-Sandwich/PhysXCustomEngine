#pragma once
#include "PxPhysicsAPI.h"
#include <iostream>

class ErrorCallback : public physx::PxErrorCallback
{
public:
    virtual void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file,
        int line)
    {
        std::cout << "Code: " << code << ", Message: " << message << "\nFile: " << file << ", Line: " << line << '\n';
    }
};