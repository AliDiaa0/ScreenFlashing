#pragma once

// ScreenFlashing.h : Header file for screen flashing functionality

// Necessary header files for the program
#include <stdio.h>
#include <Windows.h>

// Define constants for flashing intervals
#define true 1
#define null 0

// Function to flash the screen a specific number of times
int screen_flashing();

// Function to flash the screen forever
int forever_flashing();

// Function to clean the screen from the GDI mess
int clean_screen();

// Function to check if the input is a valid integer
int is_valid_integer(const char* input);

// Global variables for screen flashing
extern HWND hwnd;
extern HDC hdc;
extern RECT rect;
extern int width;
extern int height;
extern int timesFlashed;
extern int flashingInterval;
extern int clean;