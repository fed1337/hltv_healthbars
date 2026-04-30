#include "stdafx.h" 

struct playerInfo_s
{
	char* szWeapon;
	char* szModel;
	char* szName;
	int team;
	int hp;
	int sequence;
	bool kitbomb;
};

class CHealthBars
{
public:
	void Draw();
};