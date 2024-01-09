#include "PreCompile.h"
#include "ObjectPacket.h"

ObjectPacket::ObjectPacket()
{
	SetPacketID(ContentsPacketEnum::ObjectPacket);
}

ObjectPacket::~ObjectPacket()
{
}