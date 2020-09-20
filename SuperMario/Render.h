#pragma once
typedef enum Color Color;
void Render();
void InitializeRender();
void SetPoint(int x, int y);
void SetPixelColor(int x, int y, Color textColor, Color backColor);