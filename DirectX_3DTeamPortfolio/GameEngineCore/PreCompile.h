#pragma once

#include <GameEnginePlatform/PreCompile.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "GameEngineCore.h"
#include "GameEngineSprite.h"
#include "GameEngineDebugCore.h"

#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineGUI.h"
#include "GameEngineFBXMesh.h"
#include "GameEngineFBXAnimation.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

// PhysX
#include "PxConfig.h"
#include "GameEnginePhysX.h"

#pragma comment (lib, "PhysX_static_64.lib")
#pragma comment (lib, "PhysXCharacterKinematic_static_64.lib")
#pragma comment (lib, "PhysXCommon_static_64.lib")
#pragma comment (lib, "PhysXCooking_static_64.lib")
#pragma comment (lib, "PhysXExtensions_static_64.lib")
#pragma comment (lib, "PhysXFoundation_static_64.lib")
#pragma comment (lib, "PhysXPvdSDK_static_64.lib")
#pragma comment (lib, "PhysXVehicle_static_64.lib")