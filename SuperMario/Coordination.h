#pragma once
#include "Bool.h" // Bool
typedef struct Coordination Coordination;
struct Coordination
{
	short x;
	short y;
};

Coordination NewCoordination(int x, int y);
Coordination AddCoordination(Coordination coordination1, Coordination coordination2);
Coordination MultiplyCoordination(Coordination coordination, int scalar);
Coordination DivideCoordination(Coordination coordination, int scalar);
Coordination InverseCoordination(Coordination coordination);
Bool CompareCoordination(Coordination coordination1, Coordination coordination2);