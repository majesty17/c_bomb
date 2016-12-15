#ifndef COMMON_H
#define COMMON_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define BO_HAVE_BOMB			0x7000
#define BO_NOHAVE_BOMB			0x0000
#define BO_1					0x0001
#define BO_2					0x0002
#define BO_3					0x0004
#define BO_4					0x0008
#define BO_5					0x0010
#define BO_6					0x0020
#define BO_7					0x0040
#define BO_8					0x0080

#define BOS_HAVE_BOMB			0x7F00
#define BOS_NOHAVE_BOMB			0x0F00
#define BOS_1					0x0F01
#define BOS_2					0x0F02
#define BOS_3					0x0F04
#define BOS_4					0x0F08
#define BOS_5					0x0F10
#define BOS_6					0x0F20
#define BOS_7					0x0F40
#define BOS_8					0x0F80

void initBombs(short **bombs,int weight,int height,int count);

#endif // COMMON_H
void showBombs(short **bombs,int weight,int height);
void killBombs(short **bombs,int weight,int height);

int clickToOpen(short **bombs,int x,int y);
void spreadOpen(short **bombs,int x,int y);
