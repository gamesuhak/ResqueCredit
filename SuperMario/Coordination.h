#pragma once
#include "Bool.h" // Bool
typedef struct Coordination Coordination;
struct Coordination
{
	short x;
	short y;
};

Coordination ToCoordination(int x, int y);
Coordination AddCoordination(Coordination coordination1, Coordination coordination2);
Coordination InverseCoordination(Coordination coordination);
Bool CompareCoordination(Coordination coordination1, Coordination coordination2);