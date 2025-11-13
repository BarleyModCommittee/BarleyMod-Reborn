#include "../PVZ.h"

PVZ::TrackInstance::TrackInstance(int idoraddress) : BaseClass(0)
{
	if (idoraddress >= 1024)
		this->BaseAddress = idoraddress;
	else
		this->BaseAddress = Memory::ReadPointer(0x6A9EC0, 0x820, 0xC, 0) + idoraddress * 0x30C;
}

PVZ::AttachmentID PVZ::TrackInstance::GetAttachmentID()
{
	return PVZ::AttachmentID(BaseAddress + 0x40);
}

PVZ::Attachment PVZ::TrackInstance::GetAttachment()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x40);
	return (PVZ::Attachment(ID & 0x00FFFF));
}
