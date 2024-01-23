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
					MsgBoxAssert("���� ó������ ���� �Լ��Դϴ�.");
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
		
		ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::AABBBOX3D)] = [](const CollisionParameter& _Data)
		{
			DirectX::BoundingBox Left = _Data.Left.AABB;
			DirectX::BoundingBox Right = _Data.Right.AABB;
			return Left.Intersects(Right);
		};

		ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::SPHERE3D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::OBBBOX3D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.AABB;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::AABBBOX3D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				DirectX::BoundingBox Right = _Data.Right.AABB;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::SPHERE3D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::OBBBOX3D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.SPHERE;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
				return Left.Intersects(Right);
			};


		ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::AABBBOX3D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				DirectX::BoundingBox Right = _Data.Right.AABB;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::SPHERE3D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				DirectX::BoundingSphere Right = _Data.Right.SPHERE;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::OBBBOX3D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.OBB;
				DirectX::BoundingOrientedBox Right = _Data.Right.OBB;
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
	DebugCheck();

	// setworld
	// setlocal
	// ������ ���� ��� ������ �޶����� �Ұſ���.

	if (nullptr != Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
	}
	else 
	{
		TransData.ParentMatrix = float4x4::Iden;
	}

	if (true == AbsoluteScale || true == AbsoluteRotation || true == AbsolutePosition)
	{
		// ���� ���
		// ���� => ����
		float4 WScale, WRotation, WPosition;
		float4 LScale, LRotation, LPosition;

		TransData.WorldMatrix.Decompose(WScale, WRotation, WPosition);

		if (true == AbsoluteScale)
		{
			WScale = TransData.WorldScale; 
		}

		if (true == AbsoluteRotation)
		{
			WRotation = TransData.WorldRotation.EulerDegToQuaternion(); 
		}

		if (true == AbsolutePosition)
		{
			WPosition = TransData.WorldPosition;
		}

		TransData.WorldMatrix.Compose(WScale, WRotation, WPosition);
		TransData.LocalWorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix.InverseReturn();
	}
	else 
	{
		TransData.LocalCalculation(TransData.ParentMatrix);
	}

	TransData.WorldDecompos();
	TransData.LocalDecompos();


	// world local

	// postion
	// �θ�
	// 100, 100
	// ����
	// 100, 100
	// ���� local 100, 100
	// ���� World 200, 200
	// 
	// setworldpostion(300, 300) ���� ���� ��� �ְ�.
	// ���� ��ġ�� 300, 300���� �����ȴٴ� ���̳׿�?
	
	// �ܼ��ϰ� �����غ��� �θ��� ��ġ���� ���� ��ġ�� ����
	// ȸ���ϰ� 

	//if (nullptr != Parent)
	//{
	//	TransData.ParentMatrix = Parent->TransData.WorldMatrix;
	//	TransData.WorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix;

	//	// ���� �θ��� ����� ���ؼ� ���� ����� ������ �Ǿ���.
	//	// ������ ��ҵ��� ������

	//	if (true == AbsoluteScale || true == AbsoluteRotation || true == AbsolutePosition)
	//	{
	//		// ��ġ�� ������Ű��� ����� �����Դ�.
	//		float4 WScale, WRotation, WPosition;
	//		float4 LScale, LRotation, LPosition;

	//		TransData.WorldMatrix.Decompose(WScale, WRotation, WPosition);

	//		if (true == AbsoluteScale)
	//		{
	//			WScale = TransData.Scale; 
	//		}

	//		if (true == AbsoluteRotation)
	//		{
	//			WRotation = TransData.Rotation.EulerDegToQuaternion(); 
	//		}

	//		if (true == AbsolutePosition)
	//		{
	//			WPosition = TransData.Position;
	//		}

	//		TransData.WorldMatrix.Compose(WScale, WRotation, WPosition);
	//		TransData.LocalWorldMatrix = TransData.WorldMatrix * TransData.ParentMatrix.InverseReturn();
	//	}
	//}

	// ���ο��� ������� ���ֱ� ������
	//TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	//TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();

	//TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	//TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();

	// ������ 
	ColData.OBB.Extents = TransData.WorldScale.ToABS().Half().Float3;
	ColData.OBB.Center = TransData.WorldPosition.Float3;
	ColData.OBB.Orientation = TransData.WorldQuaternion.Float4;
	// Ʈ�������� ������Ʈ�� �Ǿ����Ƿ�


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

bool GameEngineTransform::TriToRay(const float4& _Origin, const float4& _Dir, const float4& _TriV0, const float4& _TriV1, const float4& _TriV2, float& _Dis)
{
	return DirectX::TriangleTests::Intersects(_Origin.DirectXVector, _Dir.DirectXVector, _TriV0.DirectXVector, _TriV1.DirectXVector, _TriV2.DirectXVector, _Dis);
}