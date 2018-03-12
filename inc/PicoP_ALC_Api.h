// ****************************************************************************
//  Copyright : (c)2009-2017 Microvision
//
//  PicoP_ALC_Api.h
//
//  Application Level C API for communication to the MVIS PicoP Display Engine 
//
// ****************************************************************************

#ifndef _PICOP_ALC_API_H_
#define _PICOP_ALC_API_H_

// include common MVIS data types
#include "../../../interface/PicoP_Def.h"
#include "../../../interface/PicoP_RC.h"

#ifdef __cplusplus
extern "C" {    
#endif          

#ifdef MV_ALC_EXPORTS
#define MV_ALC_API __declspec(dllexport)
#else
#define MV_ALC_API
#endif

#ifdef __WINDOWS__
	#define CALLBACK  __stdcall
#else
	#define CALLBACK
#endif


// ************************************************************************************************
//                                     CONNECTION MANAGEMENT
// ************************************************************************************************
/// <summary>
/// This function must be the first call into the ALC library. It opens the library and allocates 
/// resources necessary for operation. It returns a handle to the library that must be used 
/// in subsequent calls.
/// </summary>
///
/// <param name = "libraryHandle">[OUT] A pointer to a PicoP_HANDLE that is set to an open handle
///	of the library  </param>
/// <returns> eSUCCESS- If the library is opened successfully .<br>
/// eFAILURE- If library open failed. <br>
/// eALREADY_OPENED- If ALC library opened already. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_OpenLibrary( PicoP_HANDLE* const libraryHandle);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function closes the ALC API library and releases all resources.
/// It also closes all the open connections
/// </summary>
///
/// <param name = "libraryHandle">[IN] A valid library handle previously obtained by a call 
/// to PicoP_ALC_OpenLibrary() </param>
/// <returns> eSUCCESS- If the library is closed successfully .<br>
/// eFAILURE- If library close failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_CloseLibrary( const PicoP_HANDLE libraryHandle);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function returns the version and capability information of the ALC API library. 
/// </summary>
///
/// <param name = "libraryHandle">[IN] A valid library handle previously obtained by a call 
/// to PicoP_ALC_OpenLibrary()</param>
/// <param name = "libraryInfo">[OUT] A pointer to an PicoP_LibraryInfo struct that will be filled with the information
/// </param>
/// <returns> eSUCCESS- If the library information is retrieved successfully .<br>
/// eFAILURE- If library information retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetLibraryInfo(const PicoP_HANDLE libraryHandle, PicoP_LibraryInfo* const libraryInfo);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function opens a connection to the Projector Display Engine using either USB or RS232 or BTH
/// </summary>
///
/// <param name = "libraryHandle">[IN] A valid library handle previously obtained by a call 
/// to PicoP_ALC_OpenLibrary()</param>
/// <param name = "connectionType">[IN] Type of connection to be opened.</param>
/// <param name = "connectionInfo">[IN] Information about the connection, includes items such 
/// as type, port#, baud rate, etc.</param>
/// <param name = "connectionHandle">[OUT] A pointer to an PicoP_HANDLE that is set if the connection is successful.
/// </param>
/// <returns> eSUCCESS- If the connection is opened successfully .<br>
/// eFAILURE- If connection open failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eALREADY_OPENED- If connection opened already. <br>
/// eNOT_CONNECTED- If no valid device connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_OpenConnection( const PicoP_HANDLE libraryHandle, const PicoP_ConnectionTypeE connectionType,
                                              const PicoP_ConnectionInfo connectionInfo, PicoP_HANDLE* connectionHandle);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function opens a connection to the Projector Display Engine using USB.
/// </summary>
///
/// <param name = "libraryHandle">[IN] A valid library handle previously obtained by a call 
/// to PicoP_ALC_OpenLibrary()</param>
/// <param name = "connectionInfo">[IN] Information about the connection, includes items such 
/// as product ID, serial number etc.</param>
/// <param name = "connectionHandle">[OUT] A pointer to an PicoP_HANDLE that is set if the connection is successful.
/// </param>
/// <returns> eSUCCESS- If the connection is opened successfully .<br>
/// eFAILURE- If connection open failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eALREADY_OPENED- If connection opened already. <br>
/// eNOT_CONNECTED- If no valid device connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_OpenConnectionUSB(const PicoP_HANDLE libraryHandle, const PicoP_USBInfo *const connectionInfo,
												PicoP_HANDLE *const connectionHandle);
 
///--------------------------------------------------------------------------------------------
/// <summary>
/// This function opens a connection to the Projector Display Engine using UART.
/// </summary>
///
/// <param name = "libraryHandle">[IN] A valid library handle previously obtained by a call 
/// to PicoP_ALC_OpenLibrary()</param>
/// <param name = "connectionInfo">[IN] Information about the connection, includes items such 
/// as port#, baud rate, etc.</param>
/// <param name = "connectionHandle">[OUT] A pointer to an PicoP_HANDLE that is set if the connection is successful.
/// </param>
/// <returns> eSUCCESS- If the connection is opened successfully .<br>
/// eFAILURE- If connection open failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eALREADY_OPENED- If connection opened already. <br>
/// eNOT_CONNECTED- If no valid device connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_OpenConnectionRS232(const PicoP_HANDLE libraryHandle, const PicoP_RS232Info *const connectionInfo,
													PicoP_HANDLE *const connectionHandle);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function Closes a previously opened connection to the Projector Display Engine
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open handle to the connection to be closed.
/// </param>
/// <returns> eSUCCESS- If the connection is closed successfully .<br>
/// eFAILURE- If connection close failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_CloseConnection( const PicoP_HANDLE connectionHandle);


// ************************************************************************************************
//                                     INPUT CONTROL
// ************************************************************************************************
/// <summary>
/// This function configures the information for custom video capture mode. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "modeHandle">[OUT] Handle to the custom video capture mode.</param>
/// <param name = "captureInfo">[IN] VideocaptureInfo structure populated with the Video Capture properties. </param>
/// <returns> eSUCCESS- If the video modes are set successfully .<br>
/// eFAILURE- If video mode set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetInputCaptureModeInfo(const PicoP_HANDLE connectionHandle, PicoP_VideoModeHandleE *const modeHandle, const PicoP_VideoCaptureInfo* const captureInfo);

///------------------------------------------------------------------------------------------------
/// <summary>
/// This function modifies an existing custom input video mode in the PicoP. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "modeHandle">[IN] Video mode handle returned by SetInputCaptureModeInfo</param>
/// <param name = "captureInfo">[IN] VideocaptureInfo structure populated with the Video Capture properties. </param>
/// <returns> eSUCCESS- If the video modes are modified successfully .<br>
/// eFAILURE- If video mode modification failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_ModifyInputCaptureModeInfo(const PicoP_HANDLE connectionHandle, const PicoP_VideoModeHandleE modeHandle, const PicoP_VideoCaptureInfo* const captureInfo);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function returns information on input video capture mode 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "modeHandle">[OUT] Handle to the video capture mode to be queried.</param>
/// <param name = "captureInfo">[OUT] VideoCaptureInfo struct that gets filled in with the current video capture mode properties.</param>
/// <returns> eSUCCESS- If the input video capture mode is got successfully .<br>
/// eFAILURE- If input video capture mode retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetInputCaptureModeInfo(const PicoP_HANDLE connectionHandle, const PicoP_VideoModeHandleE modeHandle, PicoP_VideoCaptureInfo* const captureInfo);


///------------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the active input video capture mode. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "modeHandle">[IN] Handle to the requested video capture mode.</param>
/// <returns> eSUCCESS- If the given video mode is set successfully .<br>
/// eFAILURE- If video capture mode set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetActiveCaptureMode(const PicoP_HANDLE connectionHandle, const PicoP_VideoModeHandleE modeHandle);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the current input video capture mode 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "modeHandle">[OUT] Handle to the retrieved video capture mode.</param>
/// <returns> eSUCCESS- If the input video capture mode is got successfully .<br>
/// eFAILURE- If input video capture mode retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetActiveCaptureMode(const PicoP_HANDLE connectionHandle, PicoP_VideoModeHandleE *const modeHandle);

///------------------------------------------------------------------------------------------------
/// <summary>
/// This function commits the given video capture mode info to NVRAM. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "modeHandle">[IN] Video mode handle returned by SetInputCaptureModeInfo</param>
/// <returns> eSUCCESS- If the video modes is commited successfully .<br>
/// eFAILURE- If video mode handle commit failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_CommitInputCaptureMode(const PicoP_HANDLE connectionHandle, const PicoP_VideoModeHandleE modeHandle);

///------------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the commited custom video capture mode. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "modeHandle">[OUT] Handle to the custom video capture mode.
///                 if no videomode is committed then it is filled with eVideoModeHandle_INVALID</param>
/// <returns> eSUCCESS- If the video modes are set successfully .<br>
/// eFAILURE- If video mode set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetCommitedInputCaptureMode(const PicoP_HANDLE connectionHandle, PicoP_VideoModeHandleE *const modeHandle);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets detected input video Frame Rate and Lines per Frame.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "frameRate">[OUT] Detected Frames per second</param>
/// <param name = "lines">[OUT] Detected number of vertical lines per frames</param>
/// <returns> eSUCCESS- If the input video properties is retrieved successfully .<br>
/// eFAILURE- If input video properties retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetInputVideoProperties(const PicoP_HANDLE connectionHandle, FP32 *const frameRate, UINT16 *const lines);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the video input state to enabled or disabled. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "state">[IN] Accepted values are eINPUT_VIDEO_DISABLED or eINPUT_VIDEO_ENABLED.</param>
/// <returns> eSUCCESS- If the input video state is set successfully .<br>
/// eFAILURE- If input video state set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetInputVideoState(const PicoP_HANDLE connectionHandle, const PicoP_InputVideoStateE state);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function returns the current video input state.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "state">[OUT] Current Video Input State. Returned value can be eINPUT_VIDEO_DISABLED or eINPUT_VIDEO_ENABLED.</param>
/// <returns> eSUCCESS- If the input video state is retrived successfully .<br>
/// eFAILURE- If input video state retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetInputVideoState(const PicoP_HANDLE connectionHandle, UINT32* const state);


// ************************************************************************************************
//                                     DISPLAY CONTROL
// ************************************************************************************************
/// <summary>
/// This function sets brightness for the output display. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "brightnessValue">[IN] Floating point value of brightness (0.0 to 1.0).</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit. </param>
/// <returns> eSUCCESS- If the brightness is set successfully .<br>
/// eFAILURE- If brightness set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetBrightnessVal( const PicoP_HANDLE connectionHandle, const FP32 brightnessValue, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets brightness for the output display. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "brightnessValue">[OUT] Pointer to floating point to get brightness.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the brightness is got successfully .<br>
/// eFAILURE- If brightness retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetBrightnessVal( const PicoP_HANDLE connectionHandle, FP32* const brightnessValue, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets aspect ratio for the output display. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "aspectRatio">[IN] Accepted values are eASPECT_RATIO_NORMAL, eASPECT_RATIO_WIDESCREEN and eASPECT_RATIO_ZOOM.</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit. </param>
/// <returns> eSUCCESS- If the aspect ratio is set successfully .<br>
/// eFAILURE- If aspect ratio set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetAspectRatioMode( const PicoP_HANDLE connectionHandle, const PicoP_AspectRatioModeE aspectRatio, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets aspect ratio for the output display. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "aspectRatio">[OUT] Pointer to hold aspect ratio.
/// Returned values can be eASPECT_RATIO_NORMAL, eASPECT_RATIO_WIDESCREEN and eASPECT_RATIO_ZOOM</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the aspect ratio is got successfully .<br>
/// eFAILURE- If aspect ratio retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetAspectRatioMode( const PicoP_HANDLE connectionHandle, UINT32* const aspectRatio, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets color mode for the output display. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "colorMode">[IN] Accepted values are eCOLOR_MODE_BRILLIANT, eCOLOR_MODE_STANDARD and eCOLOR_MODE_INVERTED.</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit. </param>
/// <returns> eSUCCESS- If the color mode is set successfully .<br>
/// eFAILURE- If color mode set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetColorMode( const PicoP_HANDLE connectionHandle, const PicoP_ColorModeE colorMode, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets color mode for the output display. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "colorMode">[OUT] Pointer to floating point to hold color mode.
///  0 = Brilliant, 1 = Standard, 2 = Inverted.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the color mode is got successfully .<br>
/// eFAILURE- If color mode retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetColorMode( const PicoP_HANDLE connectionHandle, UINT32* const colorMode, const PicoP_ValueStorageTypeE storageType);

///------------------------------------------------------------------------------------------------
/// <summary>
/// This function sets gamma value for the output display. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "color">[IN] Enumerated color value. Accepted values are eRED, eGREEN, eBLUE or eALL_COLORS.</param>
/// <param name = "gammaValue">[IN]Any floating point value. </param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit. </param>
/// <returns> eSUCCESS- If the gamma value is set successfully .<br>
/// eFAILURE- If gamma value set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetGammaVal( const PicoP_HANDLE connectionHandle, const PicoP_ColorE color, const FP32 gammaValue, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets gamma value for the output display. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "color">[IN] Enumerated color value. Accepted values are eRED, eGREEN, eBLUE or eALL.</param>
/// <param name = "gammaValue">[OUT] Pointer to floating point to get gamma value for the chosen color.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the gamma value is got successfully .<br>
/// eFAILURE- If gamma value retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetGammaVal( const PicoP_HANDLE connectionHandle, const PicoP_ColorE color, FP32* const gammaValue, const PicoP_ValueStorageTypeE storageType);

//--------------------------------------------------------------------------------------------
/// <summary>
/// This function Sets the Flip State. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "flipState">[IN] flipState.Accepted values are eFLIP_NEITHER or HORIZONTAL or eFLIP_VERTICAL or eFLIP_BOTH.</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit.</param>
/// <returns> eSUCCESS- If flip state is set successfully .<br>
/// eFAILURE- If flip state setting failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetFlipState(const PicoP_HANDLE connectionHandle, const PicoP_FlipStateE flipState, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function returns the current Flip state.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "flipState">[OUT] Current flip State. eFLIP_NEITHER or HORIZONTAL or eFLIP_VERTICAL or eFLIP_BOTH.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the flip state is retrieved successfully .<br>
/// eFAILURE- If flip state retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetFlipState(const PicoP_HANDLE connectionHandle, PicoP_FlipStateE *const flipState, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the video output state to enabled or disabled. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "state">[IN] Accepted values are eVIDEO_OUTPUT_DISABLED or eVIDEO_OUTPUT_ENABLED.</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit.< / param>
/// <returns> eSUCCESS- If the output video state is set successfully .<br>
/// eFAILURE- If output video state set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetOutputVideoState(const PicoP_HANDLE connectionHandle, const PicoP_OutputVideoStateE state, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function returns the current video output state.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "state">[OUT] Current Video Output State. Returned value can be eVIDEO_OUTPUT_DISABLED or eVIDEO_OUTPUT_ENABLED.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. < / param>
/// <returns> eSUCCESS- If the output video state is retrieved successfully .<br>
/// eFAILURE- If output video state retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetOutputVideoState(const PicoP_HANDLE connectionHandle, UINT32* const state, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function performs keystone correction.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "keyStoneCorrectionValue">[IN] This value ranges from +100 to -100.</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit.</param>
/// <returns> eSUCCESS- If the keystone correction is done successfully .<br>
/// eFAILURE- If keystone correction failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_CorrectKeystone(const PicoP_HANDLE connectionHandle, const INT32 keyStoneCorrectionValue, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function retrieves the Keystone Correction Value.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "keyStoneCorrectionValue">[OUT] Pointer to store returned Keystone Correction Value.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the Keystone Correction Value is got successfully .<br>
/// eFAILURE- If Keystone Correction Value retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetKeystoneCorrection(const PicoP_HANDLE connectionHandle, INT32 *const keyStoneCorrectionValue, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the scan line phase delay to align the forward and reverse scan video.  
/// This command will affect all three color channels.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "phaseValue">[IN] Phase Value(-50 to 50).</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit.</param>
/// <returns> eSUCCESS- If the phase delay value is set successfully .<br>
/// eFAILURE- If phase delay value set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetPhase(const PicoP_HANDLE connectionHandle, const INT16 phaseValue, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the scan line phase delay. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "phaseValue">[OUT] Pointer to get scan line phase delay value.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the phase delay value is got successfully .<br>
/// eFAILURE- If phase delay retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetPhase(const PicoP_HANDLE connectionHandle, INT16* const phaseValue, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function performs vertical or horizontal color alignment for the selected color.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "direction">[IN] Valid values are eHORIZONTAL and eVERTICAL.</param>
/// <param name = "color">[IN] Valid values are eRED, eGREEN or eBLUE.</param>
/// <param name = "offset">[IN] This value ranges from +32 to -32.</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit.</param>
/// <returns> eSUCCESS- If the color alignment is done successfully .<br>
/// eFAILURE- If the color alignment failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetColorAlignment(const PicoP_HANDLE connectionHandle, const PicoP_DirectionE direction, const PicoP_ColorE color, const INT16 offset, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the vertical or horizontal color alignment offset value for the selected color.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "direction">[IN] Valid values are eHORIZONTAL and eVERTICAL.</param>
/// <param name = "color">[IN] Valid values are eRED, eGREEN or eBLUE.</param>
/// <param name = "offset">[OUT] This value ranges from +32 to -32.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the get color alignment call is done successfully .<br>
/// eFAILURE- If the get color alignment call failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetColorAlignment(const PicoP_HANDLE connectionHandle, const PicoP_DirectionE direction, const PicoP_ColorE color, INT16 *const offset, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the color converter values.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "color">[IN] Valid values are eRED_TO_RED,eGREEN_TO_RED,eBLUE_TO_RED,eRED_TO_GREEN,eGREEN_TO_GREEN,eBLUE_TO_GREEN,eRED_TO_BLUE,eGREEN_TO_BLUE and eBLUE_TO_BLUE	</param>
/// <param name = "coefficient">[IN] This value ranges from -65536 to +65535.</param>
/// <param name = "commit">[IN] 0 = No Commit, 1 = Commit.</param>
/// <returns> eSUCCESS- If the color converter value is set successfully .<br>
/// eFAILURE- If the converter value failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetColorConverter(const PicoP_HANDLE connectionHandle,
    const PicoP_ColorConvertE color,
    const INT32 coefficient,
    const BOOL commit);
///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the color converter values.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "color">[IN] Valid values are eRED_TO_RED,eGREEN_TO_RED,eBLUE_TO_RED,eRED_TO_GREEN,eGREEN_TO_GREEN,eBLUE_TO_GREEN,eRED_TO_BLUE,eGREEN_TO_BLUE and eBLUE_TO_BLUE	</param>
/// <param name = "coefficient">[OUT] This value ranges from -65536 to +65535.</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the get color alignment call is done successfully .<br>
/// eFAILURE- If the get color alignment call failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetColorConverter(const PicoP_HANDLE connectionHandle, const PicoP_ColorConvertE color, INT32 *const coefficient, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the Viewport Distortion Parameters.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "offsetTopLeft">[IN] % of viewport to push top left corner inward.</param>
/// <param name = "offsetTopRight">[IN] % of viewport to push top right corner inward.</param>
/// <param name = "offsetLowerLeft">[IN] % of viewport to push lower left corner inward.</param>
/// <param name = "offsetLowerRight">[IN] % of viewport to push lower right corner inward.</param>
/// <param name = "commit">[IN] "commit">[IN] 0 = No commit, 1 = Commit</param
/// <returns> eSUCCESS- If the Viewport Distortion Parameters are set successfully .<br>
/// eFAILURE- If Viewport Distortion Parameters set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetViewportDistortion(const PicoP_HANDLE connectionHandle, const FP32 offsetTopLeft, const FP32 offsetTopRight,
                                                    const FP32 offsetLowerLeft, const FP32 offsetLowerRight, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function retrieves the Viewport Distortion Parameters.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "offsetTopLeft">[OUT] Returned value of top left corner distortion offset .</param>
/// <param name = "offsetTopRight">[OUT] Returned value of top right corner distortion offset .</param>
/// <param name = "offsetLowerLeft">[OUT] Returned value of lower left corner distortion offset .</param>
/// <param name = "offsetLowerRight">[OUT] Returned value of lower right corner distortion offset .</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the Viewport Distortion Parameters are retrieved successfully .<br>
/// eFAILURE- If Viewport Distortion Parameters retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetViewportDistortion(const PicoP_HANDLE connectionHandle, FP32 *const offsetTopLeft, FP32 *const offsetTopRight, FP32 *const offsetLowerLeft,
    FP32 *const offsetLowerRight, const PicoP_ValueStorageTypeE storageType);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the timeout for how long Splash Screen will be displayed.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "timeout">[IN] Length of SplashScreen Display in milliseconds, Range TBD .</param>
/// <param name = "commit">[IN] "commit">[IN] 0 = No commit, 1 = Commit</param
/// <returns> eSUCCESS- If the Splash Screen timeout is set successfully .<br>
/// eFAILURE- If Splash Screen timeout set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetSplashScreenTimeout(const PicoP_HANDLE connectionHandle, const UINT32 timeout, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function retrieves the Splash Screen timeout.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "timeout">[OUT] pointer to retrieved Length of SplashScreen Display in milliseconds, Range TBD .</param>
/// <param name = "storageType">[IN]  0 = Current Value, 1 = Value on system startup, 2 = Factory value. </param>
/// <returns> eSUCCESS- If the Splash Screen timeout is retrieved successfully .<br>
/// eFAILURE- If Splash Screen timeout retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetSplashScreenTimeout(const PicoP_HANDLE connectionHandle, UINT32 *const timeout, const PicoP_ValueStorageTypeE storageType);


// ************************************************************************************************
//                                     RENDERING
// ************************************************************************************************
/// <summary>
/// This function sets the OSD state to enabled or disabled. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "state">[IN] Accepted values are eOSD_DISABLED or eOSD_ENABLED.</param>
/// <returns> eSUCCESS- If the OSD state is set successfully .<br>
/// eFAILURE- If OSD state set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetOSDState(const PicoP_HANDLE connectionHandle, const PicoP_OSDStateE state);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function returns the current OSD state.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "state">[OUT] Current OSD State. Returned value can be eOSD_DISABLED or eOSD_ENABLED.</param>
/// <returns> eSUCCESS- If the OSD state is retrieved successfully .<br>
/// eFAILURE- If OSD state retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetOSDState(const PicoP_HANDLE connectionHandle, PicoP_OSDStateE* const state);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the current Position and Size of On-Screen Display (OSD) within the output video area.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "startPoint">[OUT] Upper left corner location of OSD</param>
/// <param name = "size">[OUT] Size of OSD</param>
/// <returns> eSUCCESS- If the OSD information is retrieved successfully .<br>
/// eFAILURE- If OSD information retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetOSDInfo(const PicoP_HANDLE connectionHandle, PicoP_Point* const startPoint, PicoP_RectSize* const size);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the Position and Size of On-Screen Display (OSD) within the output video area.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "startPoint">[IN] Upper left corner location of OSD</param>
/// <param name = "size">[IN] Size of OSD</param>
/// <returns> eSUCCESS- If the OSD information is set successfully .<br>
/// eFAILURE- If OSD information set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetOSDInfo(const PicoP_HANDLE connectionHandle, const PicoP_Point startPoint, const PicoP_RectSize size);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the maximum size of the Frame Buffer or OSD that can be used for rendering.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "renderTarget">[IN] FrameBuffer Render target to query.</param>
/// <param name = "size">[OUT] Size of the render target.</param>
/// <returns> eSUCCESS- If the display information is retrieved successfully .<br>
/// eFAILURE- If display information retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetDisplayInfo(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE renderTarget, PicoP_RectSize* const size);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the active OSD to be used for video output.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "renderTarget">[IN] OSD to be used for video output.</param>
/// <returns> eSUCCESS- If the active frame buffer is set successfully .<br>
/// eFAILURE- If active frame buffer set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetActiveOSD(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE renderTarget);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the active OSD used for video output.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "renderTarget">[OUT] OSD currently used for video output.</param>
/// <returns> eSUCCESS- If the active frame buffer is retrieved successfully .<br>
/// eFAILURE- If active frame buffer retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetActiveOSD(const PicoP_HANDLE connectionHandle, PicoP_RenderTargetE* const renderTarget);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function loads raw binary RGB565 encoded bitmap data from the buffer on to the specified frame buffer.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "target">[IN] Buffer to copy the image to.</param>
/// <param name = "startPoint">[IN] Upper left corner coordinates of the image.</param>
/// <param name = "dimensions">[IN] Dimensions of the bitmap; height and width to be rendered in the selected target.</param>
/// <param name = "image">[IN] Data of bitmap image; 16 bit RGB565.</param>
/// <param name = "size">[IN] Size of bitmap image.</param>
/// <returns> eSUCCESS- If the bitmap image is loaded successfully .<br>
/// eFAILURE- If bitmap image loading failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_LoadBitmapImage(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE target, const PicoP_Point startPoint, const PicoP_RectSize dimensions, const UINT8* const image, const UINT32 size);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function displays the test pattern selected. 
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "target">[IN] Target Buffer to draw to (FrameBuffer or OSD).</param>
/// <param name = "startPoint">[IN] Upper left corner coordinates of the test pattern.</param>
/// <param name = "dimensions">[IN] Dimensions of the pattern; height and width to be rendered in the selected target.</param>
/// <param name = "patternColor">[IN] Pattern Color - 24-Bit RGB pattern color value.</param>
/// <param name = "backgroundColor">[IN] Background Color - 24-Bit RGB background color value.</param>
/// <param name = "pattern">[IN] Test pattern enumeration definition. </param>
/// <returns> eSUCCESS- If the test pattern is displayed successfully .<br>
/// eFAILURE- If test pattern display failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_DrawTestPattern(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE target, const PicoP_Point startPoint, const PicoP_RectSize dimensions, const PicoP_Color patternColor, const PicoP_Color backgroundColor, const PicoP_TestPatternInfoE pattern);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function queues a command to display text in the OSD or FrameBuffer.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "target">[IN] Target Buffer to draw to (FrameBuffer or OSD).</param>
/// <param name = "text">[IN] Text to Draw.</param>
/// <param name = "length">[IN] Length of the Text (in characters).</param>
/// <param name = "startPoint">[IN] Starting position for the text (lower-left corner).</param>
/// <param name = "textColor">[IN] Text color to use.</param>
/// <param name = "backgroundColor">[IN] Background color to use.</param>
/// <returns> eSUCCESS- If the text is displayed successfully .<br>
/// eFAILURE- If text display failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_DrawText(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE target, const UINT8 *const text, const UINT16 length, const PicoP_Point startPoint, const PicoP_Color textColor, const PicoP_Color backgroundColor);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function queues a command to set a single pixel in the OSD or a FrameBuffer.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "target">[IN] Target Buffer to draw to (FrameBuffer or OSD).</param>
/// <param name = "pixel">[IN] Pixel to set to.</param>
/// <param name = "color">[IN] Color to use for drawing.</param>
/// <returns> eSUCCESS- If the point is displayed successfully .<br>
/// eFAILURE- If point display failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_DrawPoint(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE target, const PicoP_Point pixel, const PicoP_Color color);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function queues a command to draw a line segment between two points.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "target">[IN] Target Buffer to draw to (FrameBuffer or OSD).</param>
/// <param name = "pointA">[IN] Starting point of the line.</param>
/// <param name = "pointB">[IN] End point of the line.</param>
/// <param name = "color">[IN] Color to use for drawing.</param>
/// <returns> eSUCCESS- If the line is displayed successfully .<br>
/// eFAILURE- If line display failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_DrawLine(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE target, const PicoP_Point pointA, const PicoP_Point pointB, const PicoP_Color color);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function queues a command to draw a Triangle into the OSD or a FrameBuffer.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "target">[IN] Target Buffer to draw to (FrameBuffer or OSD).</param>
/// <param name = "pointA">[IN] Corner A of Triangle.</param>
/// <param name = "pointB">[IN] Corner B of Triangle.</param>
/// <param name = "pointC">[IN] Corner C of Triangle.</param>
/// <param name = "fillColor">[IN] Color to use for filling the triangle.</param>
/// <returns> eSUCCESS- If the triangle is displayed successfully .<br>
/// eFAILURE- If triangle display failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_DrawTriangle(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE target, const PicoP_Point pointA,const  PicoP_Point pointB, const PicoP_Point pointC, const PicoP_Color fillColor);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function queues a command to draw a Rectangle into the OSD or a FrameBuffer.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "target">[IN] Target Buffer to draw to (FrameBuffer or OSD).</param>
/// <param name = "startPoint">[IN] Upper left corner of the rectangle.</param>
/// <param name = "size">[IN] Size of the rectangle.</param>
/// <param name = "fillColor">[IN] Color to use for filling the rectangle.</param>
/// <returns> eSUCCESS- If the rectangle is displayed successfully .<br>
/// eFAILURE- If rectangle display failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_DrawRectangle(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE target, const PicoP_Point startPoint, const PicoP_RectSize size, const PicoP_Color fillColor);

///--------------------------------------------------------------------------------------------
/// <summary>
/// Renders queued draw commands into the render target.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <returns> eSUCCESS- If the draw commands are rendered successfully .<br>
/// eFAILURE- If draw commands rendering failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_Render(const PicoP_HANDLE connectionHandle);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function clears the selected render target.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "renderTarget">[IN] Target that needs to be cleared.</param>
/// <returns> eSUCCESS- If the active frame buffer is set successfully .<br>
/// eFAILURE- If active frame buffer set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_ClearTarget(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE renderTarget);

///--------------------------------------------------------------------------------------------
/// <summary>
/// Gets the dimensions of the bounding rectangle of the text as it will appear if drawn in the target.
/// This will provide the API user with feedback to determine where and how to draw text, how to determine 
/// line-breaks, how to dimension menu items etc.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "text">[IN] Text to Draw.</param>
/// <param name = "length">[IN] Length of the Text (in characters).</param>
/// <param name = "textBoxRegion">[OUT] Region that would be filled with the given text if rendered.</param>
/// <returns> eSUCCESS- If the text box information is retrieved successfully .<br>
/// eFAILURE- If text box information retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetTextBoxInfo(const PicoP_HANDLE connectionHandle, const char *const text, const UINT16 length, PicoP_RectSize *const textBoxRegion);


// ************************************************************************************************
//                                     SYSTEM MANAGEMENT
// ************************************************************************************************
/// <summary>
/// This function gets the system status
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "systemStatus">[OUT] Pointer to hold system status .32 bit value, 0 is system Ok and 
/// non-zero value indicates system not OK.</param>
/// <returns> eSUCCESS- If the system status is got successfully .<br>
/// eFAILURE- If system status retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetSystemStatus(const PicoP_HANDLE connectionHandle, PicoP_SystemStatus* const systemStatus);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets system information.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "SystemInfo">[OUT] Pointer to hold system information structure .</param>
/// <returns> eSUCCESS- If the system information is got successfully .<br>
/// eFAILURE- If system information retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetSystemInfo(const PicoP_HANDLE connectionHandle, PicoP_SystemInfo* const SystemInfo);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the system event log.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "numEvents">[IN] Number of event log to be retrieved.</param>
/// <param name = "pEvent">[OUT] Pointer to hold event log .</param>
/// <returns> eSUCCESS- If the event log is got successfully .<br>
/// eFAILURE- If event log retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetEventLog(const PicoP_HANDLE connectionHandle, const UINT16 numEvents, PicoP_Event* const pEvent);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function restores system configuration to factory configuration.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "commit">[IN] 0 = No commit, 1 = Commit All.</param>
/// <returns> eSUCCESS- If the system configuration is restored to factory configuration successfully .<br>
/// eFAILURE- If restore factory configuration failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_RestoreFactoryConfig(const PicoP_HANDLE connectionHandle, const BOOL commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function takes a snapshot of the specified frame buffer 
/// and saves the content as the Splash Screen.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "target">[IN] The frame buffer to take snapshot of. </param>
/// <returns> eSUCCESS- If the EP splash screen is set successfully.<br>
/// eFAILURE- If splash screen saving failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SaveAsSplash(const PicoP_HANDLE connectionHandle, const PicoP_RenderTargetE target);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function loads the EP software image for firmware upgrade.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "image">[IN] Data of SW image.</param>
/// <param name = "size">[IN] Size of SW image.</param>
/// <returns> eSUCCESS- If the EP software image is loaded successfully .<br>
/// eFAILURE- If EP software image loading failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_UpgradeSoftware(const PicoP_HANDLE connectionHandle, const UINT8* const image, const UINT32 size);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function loads the EP software image for firmware upgrade. It has a Callback function as an argument so that the current index can be passed to the application.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "image">[IN] Data of SW image.</param>
/// <param name = "size">[IN] Size of SW image.</param>
/// <param name = "callback">[IN] Callback function to pass current index of the packet, maximum index of the packets to be sent and destination device id.</param>
/// <returns> eSUCCESS- If the EP software image is loaded successfully .<br>
/// eFAILURE- If EP software image loading failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_UpgradeSoftware_Ex(const PicoP_HANDLE connectionHandle, const UINT8* const image, const UINT32 size, int(*callback)(UINT16* currentPacket, UINT16* numPackets, UINT8* destID));

// ************************************************************************************************
//                                     EXTRA
// ************************************************************************************************
/// <summary>
/// Sets the vertical scan angle.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "vertAngle">[IN] Vertical scan angle</param>
/// <param name = "Commit">[IN] 1 = Commit, 0 = No commit</param>
/// <returns> eSUCCESS- If the vertical scan angle is set successfully .<br>
/// eFAILURE- If vertical scan angle setting failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetVerticalScanAngle(const PicoP_HANDLE connectionHandle, const FP32 vertAngle, const BOOL Commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// Gets the Vertical Scan angle.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "vertAngle">[OUT] Vertical scan angle</param>
/// <returns> eSUCCESS- If the vertical scan angle was received successfully.<br>
/// eFAILURE- If the function failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetVerticalScanAngle(const PicoP_HANDLE connectionHandle, FP32* const vertAngle);

///--------------------------------------------------------------------------------------------
/// <summary>
/// Sets the horizontal scan angle.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "horizAngle">[IN] Horizontal scan angle</param>
/// <param name = "Commit">[IN] 1 = Commit, 0 = No commit</param>
/// <returns> eSUCCESS- If the horizontal scan angle is set successfully. <br>
/// eFAILURE- If horizontal scan angle setting failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetHorizontalScanAngle(const PicoP_HANDLE connectionHandle, const FP32 horizAngle, const BOOL Commit);

///--------------------------------------------------------------------------------------------
/// <summary>
/// Gets the horizontal Scan angle.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine.</param>
/// <param name = "horizAngle">[OUT] Horizontal scan angle</param>
/// <returns> eSUCCESS- If the horizontal scan angle was received successfully.<br>
/// eFAILURE- If the function failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetHorizontalScanAngle(const PicoP_HANDLE connectionHandle, FP32* const horizAngle);

///------------------------------------------------------------------------------------------------
/// <summary>
/// This function sets the color specific video gamma boost mode.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine. </param>
/// <param name = "color">[IN] Color. </param>
/// <param name = "boostMode">[IN] Video gamma boost mode. </param>
/// <returns> eSUCCESS- If the video mode is set successfully .<br>
/// eFAILURE- If set failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_SetVideoGammaBoostMode(const PicoP_HANDLE connectionHandle, const PicoP_ColorE color, const PicoP_GammaBoostModeE boostMode);

///--------------------------------------------------------------------------------------------
/// <summary>
/// This function gets the color specific video gamma boost mode.
/// </summary>
///
/// <param name = "connectionHandle">[IN] An open connection handle to the projector engine. </param>
/// <param name = "color">[IN] Color. </param>
/// <param name = "boostMode">[OUT] Video gamma boost mode. </param>
/// <returns> eSUCCESS- If the video gamma mode is retrieved successfully. <br>
/// eFAILURE- If retrieval failed. <br>
/// eNOT_INITIALIZED- If ALC library is not initialized. <br>
/// eINVALID_ARG- If any one of the arguments is invalid. <br>
/// eNOT_CONNECTED- If no valid device is connected. <br>
/// </returns>
///------------------------------------------------------------------------------------------------
MV_ALC_API PICOP_RC PicoP_ALC_GetVideoGammaBoostMode(const PicoP_HANDLE connectionHandle, const PicoP_ColorE color, PicoP_GammaBoostModeE *const boostMode);


// ****************************************************************************

#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // _PICOP_ALC_API_H_

              
