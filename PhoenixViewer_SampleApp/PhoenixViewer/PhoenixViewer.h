// ****************************************************************************
//  PhoenixViewer.h
//
// Header file for Windows app demonstrating how to use the 3D APIs
//    
// Copyright : (c)2018 Microvision
// This source code is subject to the Microvision Source Code License. 
// 
// THIS CODE IS FOR GUIDANCE ONLY. IT IS INTENDED AS AN EDUCATIONAL SAMPLE DEMONSTRATING 
// SIMPLIFIED USE OF THE MICROVISION PRODUCT. THE CODE AND INFORMATION ARE PROVIDED "AS IS" 
// WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
// ****************************************************************************
// ****************************************************************************

#pragma once

#include "resource.h"
#include <windows.h>
#include "PicoP_TLC_Api.h"

// ****************************************************************************

#define MAX_LOADSTRING 50
#define MESSAGE_BUFFER_SIZE     128
#define ID_TIMER    1

// Dimensions of the Window to display in
#define X_DIM           520
#define X_DIM_W_COLORS  (X_DIM * 3)
#define Y_DIM           200

#define NUM_PULSES 120
#define NUM_LINES 720

#define PIXEL_DATA_SIZE 2         // two pieces of data per pixel - time and amplitude
#define FRAME_SIZE (NUM_PULSES * NUM_LINES * PIXEL_DATA_SIZE)

//1, 2, 4 number of lines to combine due to phase/interleave
#define N_LINES_COMBINE		1 

#define PULSES_VIRTUAL  (NUM_PULSES * N_LINES_COMBINE)
#define LINES_VIRTUAL   (NUM_LINES / N_LINES_COMBINE)

#define IDC_TIME_DATA	        101
#define IDC_AMPLITUDE_DATA      102
#define IDC_DISTANCE_DATA       103

#define TIME_DATA       TRUE
#define AMPLITUDE_DATA  FALSE

// ****************************************************************************

TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HINSTANCE ghInst;								// current instance

HWND ghWndTimeData;
HWND ghWndAmplitudeData;
HGDIOBJ ghDefaultFont;
LRESULT gTimeData;
LRESULT gAmplitudeData;
UINT32 gRetFrame = 0;
UINT32 gCount = 0;
BOOL gWhichData = TIME_DATA;

PicoP_HANDLE LibraryHandle;
PICOP_RC PicopRc;
PicoP_HANDLE ConnectionHandle;
PicoP_USBInfo USB_Info = { 4, "1234" };

unsigned char gWindowsFrameData[Y_DIM][X_DIM_W_COLORS];

UINT32 gDataBuffer[FRAME_SIZE];
UINT32 gTimeFrameBuffer[NUM_PULSES * NUM_LINES];
UINT32 gAmplitudeFrameBuffer[NUM_PULSES * NUM_LINES];

// ****************************************************************************
