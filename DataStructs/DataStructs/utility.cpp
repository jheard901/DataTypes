
#include "utility.h"
#include <Windows.h>	//need to figure out how to set this up for cross platform, so that it uses a specific include based off if the OS is Mac, Linux, or Windows
#include <cstdlib>		//for mbstowcs

//Ultimately, instead of using this Windows based function I want to output debug information
//to a separate console window aside from the main one used for testing stuff like the driver.
//I would probably hide this window by default and create an optional parameter for when the program
//is run to show the debug console window.
//		|
//		V
//Converting char* to LPWSTR: http://stackoverflow.com/questions/6858524/convert-char-to-lpwstr
//Simple way to get DebugOutput: http://stackoverflow.com/questions/9540594/simple-way-to-send-debug-information-to-the-visual-studio-output-window
//Explanation for DebugOutput: http://stackoverflow.com/questions/1333527/how-do-i-print-to-the-debug-output-window-in-a-win32-app
void DP(char chs[])
{
	if (strlen(chs) < 256) { chs += '\0'; } //append null char to end
	wchar_t wTxt[256]; //max of 256 char limit
	mbstowcs(wTxt, chs, strlen(chs)); //converts format
	LPWSTR input = wTxt;
	OutputDebugString(input);
}