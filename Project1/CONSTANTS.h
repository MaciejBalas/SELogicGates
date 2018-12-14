#ifndef constants
#define constants


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

static SDL_Color BackgroundColour{ 255,255,255 }; //white
static SDL_Color LowColour{ 0,0,255 }; //blue
static SDL_Color HighColour{ 255,0,0 }; //red
static SDL_Color ErrorColour{ 255,192,203 }; //pink

static SDL_Renderer *renderer = NULL;


enum TOutput { low = 0, high = 1, error = -1 };
enum TElementType { _and, _or , _not, _nor, _nand, _xor, _output, _wire, _junction, _inbus, _cbus };
#endif // !constants
