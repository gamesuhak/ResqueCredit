#include "Player.h"

#include "Coordination.h" // Coordination
#include "Input.h" // Key
#include "Object.h" // Creature, CheckMove
#include "Stage.h" // CheckMove
#include "Sprite.h" // PIXELPERUNIT
#include "Render.h"

extern char ASCIIMODE; // Render.c
extern Bool KeyState[KEY_COUNT]; // InputProcess.c
extern int KeyCharge[KEY_COUNT]; // InputProcess.c
extern Stage* Stage1; // Stage.c
extern const Coordination DIRECTIONS[DIRECTION_COUNT]; // Object.c
Bool PlayerFour = False;
Bool PlayerDouble = False;

Creature* Player;
Coordination PlayerRoomPosition = { 0, 0 };
Room* PlayerRoom;
//int PlayerAttackSpeed = 20;
int PlayerAttackCooltime = 15;

void InitializePlayer()
{
	Player = NewCreature();
	Player->hp = 6;
	Player->enable = True;
	Player->power = 1;
	Player->cooltime = 20;
	PlayerRoomPosition = Stage1->start;
	Player->object.position = NewCoordination(5 * PIXELPERUNIT + 4, 3 * PIXELPERUNIT + 4);
	int frame[4] = { 4, 4, 4, 4 };
	Player->object.animator = NewAnimator(SPRITE_PLAYER, STATE_WALK + 1, DIRECTION_COUNT, 20, frame);
	PlayerRoom = Stage1->rooms[Stage1->roomData[PlayerRoomPosition.x][PlayerRoomPosition.y]];
}

void PlayerMove()
{
	Coordination move = { 0,0 };
	if (KeyState[KEY_C])
	{
		ASCIIMODE = !ASCIIMODE;
	}
	if (KeyState[KEY_UP])
	{
		if ((KeyCharge[KEY_UP] < KeyCharge[KEY_DOWN]) || !KeyState[KEY_DOWN])
		{
			move.y = -1;
			Player->object.direction = DIRECTION_UP;
		}
	}
	if (KeyState[KEY_DOWN])
	{
		if ((KeyCharge[KEY_DOWN] < KeyCharge[KEY_UP]) || !KeyState[KEY_UP])
		{
			move.y += 1;
			Player->object.direction = DIRECTION_DOWN;
		}
	}
	if (KeyState[KEY_LEFT])
	{
		if ((KeyCharge[KEY_LEFT] < KeyCharge[KEY_RIGHT]) || !KeyState[KEY_RIGHT])
		{
			move.x -= 1;
			Player->object.direction = DIRECTION_LEFT;
		}
	}
	if (KeyState[KEY_RIGHT])
	{
		if ((KeyCharge[KEY_RIGHT] < KeyCharge[KEY_LEFT]) || !KeyState[KEY_LEFT])
		{
			move.x += 1;
			Player->object.direction = DIRECTION_RIGHT;
		}
	}
	if (KeyState[KEY_A])
	{
		if (++PlayerAttackCooltime >= Player->cooltime)
		{
			PlayerAttackCooltime = 0;
			if (PlayerFour)
			{
				for (int i = 0; i < DIRECTION_COUNT; i++)
				{
					ShootProjectile(0, Player->object.position, i, PROJECTILE_ARROW, Player->power, 1);
				}
				
			}
			else
			{
				ShootProjectile(0, Player->object.position, Player->object.direction, PROJECTILE_ARROW, Player->power, 1);
			}
			if (PlayerDouble)
			{
				if (PlayerFour)
				{
					for (int i = 0; i < DIRECTION_COUNT; i++)
					{
						ShootProjectile(0, Player->object.position, i, PROJECTILE_ARROW, Player->power, 1);
					}

				}
				else
				{
					ShootProjectile(0, Player->object.position, Player->object.direction, PROJECTILE_ARROW, Player->power, 1);
				}
			}
		}
	}
	if (move.x != 0 || move.y != 0)
	{
		move = CheckMove(PlayerRoom, &Player->object, move);
		Player->object.position = AddCoordination(Player->object.position, move);
		Player->object.state = STATE_WALK;

		if (GetTileTag(PlayerRoom, Player->object.position) == TILETAG_DOOR)
		{
			StartTransition(Player->object.direction);
		}
	}
	else
	{
		Player->object.state = STATE_IDLE;
	}
	//printf("%d, %d\n", move.x, move.y);
	Sleep(50);
}