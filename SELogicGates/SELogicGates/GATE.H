#ifndef DefGate
#define DefGate

#include <dos.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <io.h>
#include <SYS\STAT.H>
#include <graphics.h>
#include <alloc.h>
#include <malloc.h>
#include <process.h>

#define BackSpace 8
#define Enter 13
#define Esc 27
#define MenuButNum 9
#define ButNum 16
#define HighColour 4
#define LowColour 1
#define ErrorColour 2
#define BasketColour 1
#define FrameColour 7
#define BackgroundColour 15
#define HeadingColour 1
#define HeadingTextColour 15
#define LineColour 16
#define InsertTextColour 12
#define CustomTextColour 16
#define NumberOfInBuses 6
#define NumberOfImages 8
#define MaxBreakpointsNum 4
#define MaxJunctionNum 10
#define MaxBusJunctionNum 30
#define MaxNumOfElem 100
#define MaxWinNum 99
#define MaxNextElemNum 1
#define MaxPrevElemNum 2
#define MaxSmallWinLinesNum 4

enum TElementType{and,or,not,nor,nand,xor,output,wire,junction,inbus,cbus};

void InitGraph(char *path="f:/borlandc/bgi");

int CheckMouse();

void FirstInfo();

char ConfirmQuit();

main();
#endif