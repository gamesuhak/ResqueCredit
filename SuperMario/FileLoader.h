#pragma once
#define DATA_WIDTH			18
#define DATA_HEIGHT			22
#define DATA_START			118

#include "Color.h" // Color
#include "Image.h" // Image
#include "Room.h" // RoomInfo

Image* LoadBitmapFile(char* name, Color transparent);
void SaveRoomInfoFile(char* name, RoomInfo* room);
RoomInfo* LoadRoomInfoFile(char* name);

void SaveMonsterInfoFile(char* name, MonsterInfo* monsterInfo);
MonsterInfo* LoadMonsterInfoFile(char* name);