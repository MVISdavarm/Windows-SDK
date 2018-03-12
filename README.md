# Windows-SDK

Using Microvision's Windows SDK is done in a few easy steps.

- Copy the MVFiles directory to the directory of your source files in your Windows project.
	Example:

	MyProject
		MyProjectFiles
			MyProject.cpp
			MyProject.h
			MVFiles
		MyProject.sln

- Copy the DLLs in the runtimeDLLs directory to the same directory you copied the MVFiles directory:
	Example:

	MyProject
		MyProjectFiles
			MyProject.cpp
			MyProject.h
			MVFiles
			PicoP_ALC_Api.dll
			PicoP_LLC_Api_amd64.dll
			PicoP_TLC_Api_amd64.dll
		MyProject.sln

- In your main header file add these includes:
	#include "PicoP_ALC_Api.h"
	#include "PicoP_TLC_Api.h"

- In your Visual Studio project properties add these:
	Additional include path: .\MVFiles\inc
	Additional Linker files: .\MVFiles\lib\PicoP_ALC_Api.lib;.\MVFiles\lib\PicoP_TLC_Api.lib

- Make sure your project is setup to build Release 64 bit code. Debug builds are not supported at this time.

- Once you have your project built like you want it and you want to release it package your release like this:
	MyProject.exe
	PicoP_ALC_Api.dll
	PicoP_LLC_Api_amd64.dll
	PicoP_TLC_Api_amd64.dll

