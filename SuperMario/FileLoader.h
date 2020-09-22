#pragma once
#define DATA_WIDTH		18
#define DATA_HEIGHT		22
#define DATA_START		118

#include "Color.h"
#include "Image.h"
Image* LoadBitmapFile(char* name, Color transparent);