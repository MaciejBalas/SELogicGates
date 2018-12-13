#pragma once
#include "SDL.h"

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
#define MenuButNum 9
#define ButNum 16

SDL_Color BackgroundColor{ 255,255,255 }; //white

enum TElementType { _and, _or , _not, _nor, _nand, _xor, _output, _wire, _junction, _inbus, _cbus };