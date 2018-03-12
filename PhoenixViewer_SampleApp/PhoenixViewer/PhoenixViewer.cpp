// ****************************************************************************
// PhoenixViewer.cpp
//
// Simple Windows app demonstrating how to use the 3D APIs
//    
// Copyright : (c)2018 Microvision
// This source code is subject to the Microvision Source Code License. 
// 
// THIS CODE IS FOR GUIDANCE ONLY. IT IS INTENDED AS AN EDUCATIONAL SAMPLE DEMONSTRATING 
// SIMPLIFIED USE OF THE MICROVISION PRODUCT. THE CODE AND INFORMATION ARE PROVIDED "AS IS" 
// WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
// ****************************************************************************

#include "stdafx.h"
#include <stdlib.h>  
#include <stdio.h>  
#include <math.h> 
#include "PhoenixViewer.h"

// ****************************************************************************

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

// ****************************************************************************

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG Msg;

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PHOENIXVIEWER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if ( ! InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return (int) Msg.wParam;
}

// ****************************************************************************

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PHOENIXVIEWER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

// ****************************************************************************
//   Saves instance handle and creates main window
// ****************************************************************************

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   DWORD Err = 0;


   ghInst = hInstance;       // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                        100, 0, 300, 280, NULL, NULL, hInstance, NULL);

   if ( ! hWnd)
   {
      Err = GetLastError();
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// ****************************************************************************

void CreateAndBlitBitmap(HDC hWinDC)
{
    BOOL RetBlit;
    HBITMAP OldBitmap;
    UINT32 Frame_X = 0;
    UINT32 Frame_Y = 0;
    UINT32 TofValue = 0;
    unsigned char TofColorLow = 0;
    unsigned char TofColorHigh = 0;


    BITMAPINFO info;
    ZeroMemory(&info, sizeof(BITMAPINFO));
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biBitCount = 24;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biWidth = X_DIM;
    info.bmiHeader.biHeight = Y_DIM;

    HDC memDC = CreateCompatibleDC(hWinDC);
    HBITMAP memBM = CreateCompatibleBitmap(hWinDC, X_DIM, Y_DIM);

    for (int Line = 0; Line < LINES_VIRTUAL; Line++)
    {
        for (int Row = 0; Row < PULSES_VIRTUAL; Row++)
        {
            // "Line * PULSES_VIRTUAL" points to the beginning of the line.
            // " + Row" points to the particular pixel value on that line.

            if (gWhichData == TIME_DATA)
            {
                TofValue = gTimeFrameBuffer[Line * PULSES_VIRTUAL + Row];
            }
            else
            {
                TofValue = gAmplitudeFrameBuffer[Line * PULSES_VIRTUAL + Row];
            }

            // determine the x and y for the pixel to be displayed
            Frame_X = (Row * (NUM_PULSES * N_LINES_COMBINE)) / PULSES_VIRTUAL;

            // offset from the edge of the window
            Frame_X += 80;

            // 3 colors - RGB
            Frame_X *= 3;
            Frame_Y = ((LINES_VIRTUAL - Line) * 180) / LINES_VIRTUAL;

            // convert to 8 bits to use for painting
            TofColorLow = (char)(TofValue & 0x000000ff);
            TofColorHigh = (char)((TofValue & 0x0000ff00) >> 8);

            if (gWhichData == TIME_DATA)
            {
                // blue
                gWindowsFrameData[Frame_Y][Frame_X++] = TofColorLow;
                // green
                gWindowsFrameData[Frame_Y][Frame_X++] = TofColorLow;
                // red
                gWindowsFrameData[Frame_Y][Frame_X++] = TofColorLow;
            }
            else
            {
                // blue
                gWindowsFrameData[Frame_Y][Frame_X++] = 0;
                // green
                gWindowsFrameData[Frame_Y][Frame_X++] = TofColorLow;
                // red
                gWindowsFrameData[Frame_Y][Frame_X++] = TofColorLow;
            }
        }
    }

    SetDIBits(memDC, memBM, 0, Y_DIM, (void*)gWindowsFrameData, &info, DIB_RGB_COLORS);
    OldBitmap = (HBITMAP)SelectObject(memDC, memBM);
    RetBlit = BitBlt(hWinDC, 0, 0, X_DIM, Y_DIM, memDC, 0, 0, SRCCOPY);

    if (RetBlit == false)
    {
        MessageBox(NULL, "Blit Failed", "Error", MB_OK);
        return;
    }

    SelectObject(memDC, OldBitmap);
    DeleteDC(memDC);
    DeleteObject(memBM);
}

// ****************************************************************************
//  Processes messages for the main window.
// ****************************************************************************

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT PaintStruct;
	HDC Hdc;
    PicoP_SensingStateE SensingState;
    PicoP_TofPulsingConfig PulsingConfig;
    UINT32 FrameSize = 0;
    char Buffer[MESSAGE_BUFFER_SIZE];


	switch (message)
	{
    case WM_CREATE:
        ghDefaultFont = GetStockObject(DEFAULT_GUI_FONT);

        // Create a checkbox
        ghWndTimeData = CreateWindowEx(NULL, "BUTTON", "Time Data",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            20, 200, 100, 25, hWnd, (HMENU)IDC_TIME_DATA, ghInst, NULL);
        SendMessage(ghWndTimeData, WM_SETFONT, (WPARAM)ghDefaultFont, MAKELPARAM(FALSE, 0));

        // Create a checkbox
        ghWndAmplitudeData = CreateWindowEx(NULL, "BUTTON", "Amplitude Data",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            150, 200, 120, 25, hWnd, (HMENU)IDC_AMPLITUDE_DATA, ghInst, NULL);
        SendMessage(ghWndAmplitudeData, WM_SETFONT, (WPARAM)ghDefaultFont, MAKELPARAM(FALSE, 0));

        PostMessage(ghWndTimeData, BM_SETCHECK, BST_CHECKED, 0);
        gWhichData = TIME_DATA;

        // connect to the DLL
        PicopRc = PicoP_TLC_OpenLibrary(&LibraryHandle);

        if (PicopRc != eSUCCESS) 
        {
            memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
            sprintf_s(Buffer, "PicoP_TLC_OpenLibrary() failed:  %d", PicopRc);
            MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
            break;
        }

        // Make the connection over USB
        PicopRc = PicoP_TLC_OpenConnectionUsb(LibraryHandle, USB_Info, &ConnectionHandle);

        if (PicopRc != eSUCCESS)
        {
            memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
            sprintf_s(Buffer, "PicoP_TLC_OpenConnectionUsb() failed:  %d", PicopRc);
            MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
            break;
        }

        // ****************************

        // Get the current sensing state
        PicopRc = PicoP_TLC_GetSensingState(ConnectionHandle, &SensingState, eCURRENT_VALUE);

        if (PicopRc != eSUCCESS)
        {
            memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
            sprintf_s(Buffer, "PicoP_TLC_GetSensingState failed:  %d", PicopRc);
            MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
            break;
        }
        else
        {
            // If it is currently sensing, turn it off
            if (SensingState == eSENSING_ENABLED)
            {
                PicopRc = PicoP_TLC_SetSensingState(ConnectionHandle, eSENSING_DISABLED, 0);

                if (PicopRc != eSUCCESS)
                {
                    memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
                    sprintf_s(Buffer, "PicoP_TLC_SetSensingState(eSENSING_DISABLED) failed:  %d", PicopRc);
                    MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
                    break;
                }
            }
        }

        // Get the configuration paramaters of the pulsing engine
        PicopRc = PicoP_TLC_GetTofPulsingConfig(ConnectionHandle, &PulsingConfig, eCURRENT_VALUE);

        if (PicopRc != eSUCCESS)
        {
            memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
            sprintf_s(Buffer, "PicoP_TLC_GetTofPulsingConfig() failed:  %d", PicopRc);
            MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
            break;
        }

        // Here you would make any changes you want concerning the pulsing parameters.
        // Then, write them back
        PicopRc = PicoP_TLC_SetTofPulsingConfig(ConnectionHandle, &PulsingConfig, FALSE);

        if (PicopRc != eSUCCESS)
        {
            memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
            sprintf_s(Buffer, "PicoP_TLC_SetTofPulsingConfig() failed:  %d", PicopRc);
            MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
            break;
        }

        // Reenable the sensing engine
        PicopRc = PicoP_TLC_SetSensingState(ConnectionHandle, eSENSING_ENABLED, 0);

        if (PicopRc != eSUCCESS)
        {
            memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
            sprintf_s(Buffer, "PicoP_TLC_SetSensingState(eSENSING_ENABLED) failed:  %d", PicopRc);
            MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
            break;
        }

        // Set a timer to start getting 3D data
        ::SetTimer(hWnd, ID_TIMER, 250, 0);
        break;

    case WM_COMMAND:
		switch (wParam)
		{
        case IDC_TIME_DATA:
            gTimeData = SendMessage(ghWndTimeData, BM_GETCHECK, 0, 0);

            if (gTimeData == BST_UNCHECKED)
            {
                PostMessage(ghWndTimeData, BM_SETCHECK, BST_CHECKED, 0);
                PostMessage(ghWndAmplitudeData, BM_SETCHECK, BST_UNCHECKED, 0);
                gWhichData = TIME_DATA;
            }
            else
            {
                PostMessage(ghWndTimeData, BM_SETCHECK, BST_UNCHECKED, 0);
                PostMessage(ghWndAmplitudeData, BM_SETCHECK, BST_CHECKED, 0);
                gWhichData = AMPLITUDE_DATA;
            }

            break;

        case IDC_AMPLITUDE_DATA:
            gAmplitudeData = SendMessage(ghWndAmplitudeData, BM_GETCHECK, 0, 0);

            if (gAmplitudeData == BST_UNCHECKED)
            {
                PostMessage(ghWndAmplitudeData, BM_SETCHECK, BST_CHECKED, 0);
                PostMessage(ghWndTimeData, BM_SETCHECK, BST_UNCHECKED, 0);
                gWhichData = AMPLITUDE_DATA;
            }
            else
            {
                PostMessage(ghWndAmplitudeData, BM_SETCHECK, BST_UNCHECKED, 0);
                PostMessage(ghWndTimeData, BM_SETCHECK, BST_CHECKED, 0);
                gWhichData = TIME_DATA;
            }

            break;

        default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		break;

    case WM_TIMER:
        ::KillTimer(hWnd, ID_TIMER);

        // See if there are frames buffered
        PicopRc = PicoP_TLC_GetTofFrameCount(ConnectionHandle, &gCount);

        if (PicopRc != eSUCCESS)
        {
            memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
            sprintf_s(Buffer, "PicoP_TLC_GetTofFrameCount() failed:  %d", PicopRc);
            MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
            break;
        }

        // If there are no frames available wait a little longer
        if (gCount == 0)
        {
            ::SetTimer(hWnd, ID_TIMER, 250, 0);
            break;
        }

        // If so, drain the cache until there is just one left
        while (gCount != 1)
        {
            // Get the 3D data
            PicopRc = PicoP_TLC_AcquireTofFrame(ConnectionHandle, 1, &gDataBuffer[0], &gRetFrame);

            if (PicopRc != eSUCCESS)
            {
                memset((void*)Buffer, 0, MESSAGE_BUFFER_SIZE);
                sprintf_s(Buffer, "PicoP_TLC_AcquireTofFrame() failed:  %d", PicopRc);
                MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION);
                break;
            }

            gCount--;
        }

        // Store the 3D data in an array for later use
        for (UINT32 i = 0; i < (NUM_PULSES * NUM_LINES); i++)
        {
            gTimeFrameBuffer[i] = gDataBuffer[i];
            gAmplitudeFrameBuffer[i] = gDataBuffer[i + NUM_PULSES * NUM_LINES];
        }

        ::InvalidateRect(hWnd, 0, false);
        ::SetTimer(hWnd, ID_TIMER, USER_TIMER_MINIMUM, 0);
        break;

    case WM_PAINT:
		Hdc = BeginPaint(hWnd, &PaintStruct);
        CreateAndBlitBitmap(Hdc);
		EndPaint(hWnd, &PaintStruct);
        break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// ****************************************************************************
