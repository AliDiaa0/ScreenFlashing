/* Project: ScreenFlashing
* 
Description: A simple console application that does some screen flashing GDI for Windows using the BitBlt function from wingdi.h, written completely in C Programming. This program allows the user to specify the number of times to flash the screen and the interval between flashes. It also provides an option for endless flashing until the program is terminated by the user.

Compatibilty: Windows XP and above, 32-bit or 64-bit, on all versions.

Author: Ali Diaa */

#include "screen_flashing.h"

HWND hwnd;
HDC hdc;
RECT rect;
int width;
int height;

int timesFlashed;
int flashingInterval;

int clean;

int screen_flashing() {

	for (int i = 0; i < timesFlashed; i++) {

		BitBlt(hdc, null, null, width, height, hdc, null, null, NOTSRCCOPY);

		Sleep(flashingInterval);
	}

	return null;

}

int forever_flashing() {

	while (true) {

		BitBlt(hdc, null, null, width, height, hdc, null, null, NOTSRCCOPY);

		Sleep(flashingInterval);
	}

	return null;

}

int clean_screen() {

	for (clean = 0; clean < 10; clean++) {

		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, NULL, SPIF_SENDCHANGE);

		Sleep(10);

	}

	return null;

}

int is_valid_integer(const char* str) {

	if (str[0] == '\0') return 0;

	for (int i = 0; str[i]; i++) {
		if (!isdigit((unsigned char)str[i])) return 0;
	}

	return true;

}

int main() {

	// Set the console title
	SetConsoleTitleW(TEXT("Screen Flashing Program"));

	// Set the console window size
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { 80, 25 });

	// Set the console text color to light blue
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	// Get the handle to the desktop window
	hwnd = GetDesktopWindow();

	// Get the device context of the desktop window
	hdc = GetWindowDC(hwnd);

	// Get the dimensions of the screen
	GetWindowRect(hwnd, &rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	char inputBuffer[100];

	printf("Enter the number of times to flash the screen. If you want it to be forever (endless unless you terminate the program yourself, enter 0 - to terminate it, press Alt + F4) (must be integer):\n");
	scanf_s("%99s", inputBuffer, (unsigned)_countof(inputBuffer));

	if (!is_valid_integer(inputBuffer)) {

		MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer for specific times of flashing or 0 for endless flashing."), TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
		return true;

	}

	timesFlashed = atoi(inputBuffer);

	if (timesFlashed == 0) {

		printf("Enter the flashing interval in milliseconds (must be integer):\n");
		scanf_s("%99s", inputBuffer, (unsigned)_countof(inputBuffer));

		if (!is_valid_integer(inputBuffer)) {

			MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer value for the interval."), TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
			return true;

		}

		flashingInterval = atoi(inputBuffer);

		// Call the function for endless flashing
		forever_flashing();

	}

	else if (timesFlashed < 0) {

		MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer for specific times of flashing or 0 for endless flashing."), TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);

		// If the input is invalid, return an error code
		return true;

	}

	else if (timesFlashed > 0) {

		// LOL, the user can enter a value like 7598475498357984759874389675 and the program will still run the flashing that value. XD

		printf("Enter the flashing interval in milliseconds (must be integer):\n");
		scanf_s("%99s", inputBuffer, (unsigned)_countof(inputBuffer));

		if (!is_valid_integer(inputBuffer)) {

			MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer value for the interval."), TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
			return true;

		}

		flashingInterval = atoi(inputBuffer);

		// Call the function for specific times of flashing
		screen_flashing();

		// Clean the screen from the GDI mess once the flashing is done
		clean_screen();

		// Inform the user that the flashing is done
		MessageBoxW(null, TEXT("Flashing is done!"), TEXT("Flashing done"), MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);

	}

	else {

		MessageBoxW(null, TEXT("Invalid input. Please enter a positive integer for specific times of flashing or 0 for endless flashing.\n"), TEXT("Error detected"), MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);

		// If the input is invalid, return an error code
		return true;

	}

	return null;

}
