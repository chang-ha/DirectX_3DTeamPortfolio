#include "PreCompile.h"
#include "GameEngineTransform.h"

// int ArrColFunction[7][7];

std::function<bool(const CollisionParameter& _Data)> ArrColFunction[static_cast<int>(ColType::MAX)][static_cast<int>(ColType::MAX)];

class InitColFunction
{
public:
	InitColFunction() 
	{
		for (size_t Left = 0; Left < static_cast<size_t>(ColType::MAX); Left++)
		{
			for (size_t Right = 0; Right < static_cast<size_t>(ColType::MAX); Right++)
			{
				ArrColFunction[Left][Right] = [](const CollisionParameter& _Data)
				{
					MsgBoxAssert("아직 처리되지 않은 함수입니다.");
					return false;
				};
			}
		}

		ArrColFunction[static_cast<int>(ColType::LINE2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.AABB;
				Right.Center.z = 0.0f;

				float4 Start = Left.Center;
				float4 End = Left.Extents;

				float4 Direction = End - Start;
				Direction.Normalize();

				float Dist = 0.0f;
				return Right.Intersects(Start.DirectXVector, Direction.DirectXVector, Dist);
			};

		ArrColFunction[static_cast<int>(ColType::LINE2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				Right.Center.z = 0.0f;

				float4 Start = Left.Center;
				float4 End = Left.Extents;

				float4 Direction = End - Start;
				Direction.Normalize();

				float Dist = 0.0f;
				return Right.Intersects(Start.DirectXVector, Direction.DirectXVector, Dist);
			};

		ArrColFunction[static_cast<int>(ColType::LINE2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				Right.Center.z = 0.0f;

				float4 Start = Left.Center;
				float4 End = Left.Extents;

				float4 Direction = End - Start;
				Direction.Normalize();

				float Dist = 0.0f;
				return Right.Intersects(Start.DirectXVector, Direction.DirectXVector, Dist);
			};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingBox Left = _Data.Left.AABB;
			Left.Center.z = 0.0f;
			DirectX::BoundingBox Right = _Data.Right.AABB;
			Right.Center.z = 0.0f;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.AABB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};


		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.AABB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

	}
};

InitColFunction Inst;

GameEngineTransform::GameEngineTransform() 
{
}

GameEngineTransform::~GameEngineTransform() 
{
}


void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();

	// world local

	// postion
	// 부모
	// 100, 100
	// 나도
	// 100, 100
	// 나의 local 100, 100
	// 나의 World 200, 200
	// 
	// setworldpostion(300, 300) 지금 내가 어디에 있건.
	// 나의 위치가 300, 300으로 고정된다는 것이네요?
	
	// 단순하게 생각해보면 부모의 위치에서 나의 위치를 빼면
	// 회전하고 

	if (nullptr != Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix;

		// 나는 부모의 행렬을 곱해서 나의 행렬이 나오게 되었다.
		// 기존의 요소들은 유지하

		if (true == AbsoluteScale || true == AbsoluteRotation || true == AbsolutePosition)
		{
			// 수치를 고정시키라는 명령이 내려왔다.
			float4 WScale, WRotation, WPosition;
			float4 LScale, LRotation, LPosition;

			TransData.WorldMatrix.Decompose(WScale, WRotation, WPosition);

			if (true == AbsoluteScale)
			{
				WScale = TransData.Scale; 
			}

			if (true == AbsoluteRotation)
			{
				WRotation = TransData.Rotation.EulerDegToQuaternion(); 
			}

			if (true == AbsolutePosition)
			{
				WPosition = TransData.Position;
			}

			TransData.WorldMatrix.Compose(WScale, WRotation, WPosition);
			TransData.LocalWorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix.InverseReturn();
		}
	}

	// 내부에서 디컴포즈를 해주기 때문에
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();

	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();


	// 반지름 
	ColData.OBB.Extents = TransData.WorldScale.ToABS().Half().Float3;
	ColData.OBB.Center = TransData.WorldPosition.Float3;
	ColData.OBB.Orientation = TransData.WorldQuaternion.Float4;
	// 트랜스폼도 업데이트가 되었으므로


	CalChilds();

	AbsoluteScale = false;
	AbsoluteRotation = false;
	AbsolutePosition = false;
}

void GameEngineTransform::CalculationViewAndProjection(const TransformData& _Transform)
{
	CalculationViewAndProjection(_Transform.ViewMatrix, _Transform.ProjectionMatrix);
}

void GameEngineTransform::CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection)
{
	TransData.ViewMatrix = _View;
	TransData.ProjectionMatrix = _Projection;
	TransData.WorldViewProjectionCalculation();
}

void GameEngineTransform::CalChilds()
{
	if (0 == Childs.size())
	{
		return;
	}

	for (GameEngineTransform* Trans : Childs)
	{
		Trans->TransformUpdate();
	}
}

bool GameEngineTransform::Collision(const CollisionParameter& _Data)
{
	return ArrColFunction[_Data.GetLeftTypeToInt()][_Data.GetRightTypeToInt()](_Data);
}