#include "Input.h"
#include <stdio.h>
#include <conio.h>


enum Key { KEY_UP = 72, KEY_DOWN = 80, KEY_LEFT = 75, KEY_RIGHT = 77, KEY_A = 'a', KEY_B = 'b' };
enum Bool { false = 0, true };//true는 0,false는 1
struct K {
	int Up; int Down; int Left; int Right; int A; int B;

};
struct K Kb[1] = { false,false,false,false,false,false };

Key KeyPush() {
	int Pkey = _getch();
	//방향키입력받기
	if (Pkey == 0 || Pkey == 224)
	{
		return (Key)KeyPush();
	}
	if (Pkey == KEY_UP || Pkey == KEY_DOWN || Pkey == KEY_LEFT || Pkey == KEY_RIGHT)
	{
		if (Pkey == KEY_UP)
			KeyChange(KEY_UP);
		if (Pkey == KEY_DOWN)
			KeyChange(KEY_DOWN);
		if (Pkey == KEY_LEFT)
			KeyChange(KEY_LEFT);
		else if (Pkey == KEY_RIGHT)
			KeyChange(KEY_RIGHT);
	}
	if (Pkey == 'a' || Pkey == 'A')
		KeyChange('a');
	else if (Pkey == 'b' || Pkey == 'B')
		KeyChange('b');
}

void KeyChange(Key key) {

}

void RcvSgn() {
	int i;
	for (i = 0; i < 6; i++)
	{
		//if (Kb[i] == true);
	}
}

int Ke() {
	int x = 0, y = 0;
	struct K key;
	int Push;

	while (1)
	{
		KeyPush();
	};
	return 0;
}