#include "stdafx.h"

void Hook_HUD_Frame(double time)
{
	Tick(); // update the round timer
	return CLIENT.HUD_Frame(time);
}