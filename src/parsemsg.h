#include "stdafx.h"

/***
 *
 *  Copyright (c) 1996-2002, Valve LLC. All rights reserved.
 *
 *  This product contains software technology licensed from Id
 *  Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
 *  All Rights Reserved.
 *
 *   Use, distribution, and modification of this source code and/or resulting
 *   object code is restricted to non-commercial enhancements to products from
 *   Valve LLC.  All other use, distribution, or modification is prohibited
 *   without written permission from Valve LLC.
 *
 ****/
//
//  parsemsg.h
//

#define ASSERT(x)

void BEGIN_READ(void *buf, int size);
auto READ_CHAR() -> int;
auto READ_BYTE() -> int;
auto READ_SHORT() -> int;
auto READ_WORD() -> int;
auto READ_LONG() -> int;
auto READ_FLOAT() -> float;
auto READ_STRING() -> char *;
auto READ_COORD() -> float;
auto READ_ANGLE() -> float;
auto READ_HIRESANGLE() -> float;
