#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include "pcd8544.h"
#include "OpenMath.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define FOV 80
