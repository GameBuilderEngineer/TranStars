#pragma once
#include "image.h"
#include <string>

void initializeTextW();
void uninitializeTextW();
void updateTextW();
void drawTextW();
void printTextW();

void setTextW(const std::string &text);
void releaseTextW();
