#include "PreCompile.h"
#include "ConnectIDPacket.h"

ConnectIDPacket::ConnectIDPacket()
{
	SetPacketID(ContentsPacketEnum::ConnectIDPacket);
}
