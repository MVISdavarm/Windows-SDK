//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!
//! \file
//!
//! \brief Common data types used by various MicroVision PicoP APIs.
//!
//! Copyright (C) 2017 MicroVision, Inc.
//!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef PICOP_DEF_H
#define PICOP_DEF_H

// ****************************************************************************
// All API function require a valid PicoP_HANDLE except MvXXX_OpenLibrary

typedef void* PicoP_HANDLE;

typedef signed char INT8;       // An 8 bit wide signed type
typedef signed short INT16;     // A 16 bit wide signed type
typedef signed int INT32;       // A 32 bit wide signed type
typedef unsigned char UINT8;    // An 8 bit wide signed type
typedef unsigned short UINT16;  // A 16 bit wide signed type
typedef unsigned int UINT32;    // A 32 bit wide signed type
typedef float FP32;             // A 32 bit IEEE754 floating point type
typedef int BOOL;               // A 32 bit wide signed type

// ****************************************************************************
// \See mv350_software/SW/MV3xx_Platform/Source/
//                      Application/inc/manufacturing_info_definition.hpp
#define SYSTEM_SN_LEN       17  // System_SN_LEN (Serial Number)
#define SYSTEM_PN_LEN       15  // System_PN_LEN (Part Number)
#define SAAS_PASSFAIL_LEN   5   // Scan_Angle_Adjust_Station_Pass_Fail_LEN
#define LPAS_PASSFAIL_LEN   5   // Laser_Power_Adjust_Station_Pass_Fail_LEN
#define FTS_PASSFAIL_LEN    5   // Functional_Test_Station_Pass_Fail_LEN

// ****************************************************************************
// Selects the RS232, USB, or Bluetooth interface for host communication
typedef enum
{
    eRS232 = 0,             // RS232 interface
    eUSB,                   // USB interface
    eBTH                    // Bluetooth interface
} PicoP_ConnectionTypeE;

// ****************************************************************************
// Data Types enumerations used as the type of the discriminated union in PicoP_Data

typedef enum
{
    eBOOL,          // A boolean type
    eINT8,          // An 8 bit wide signed type
    eINT16,         // A 16 bit wide signed type
    eINT32,         // A 32 bit wide signed type
    eUINT8,         // An 8 bit wide signed type
    eUINT16,        // A 16 bit wide signed type
    eUINT32,        // A 32 bit wide signed type
    eFP32,          // A 32 bit IEEE754 floating point type
    eVOIDP          // A pointer to void, can be cast to the appropriate pointer type
} PicoP_DataTypeE;

// ****************************************************************************
// Defines enums for RS232 parity selection

typedef enum
{
    eRS232ParityNone,           // No parity required
    eRS232ParityEven,           // Even parity required
    eRS232ParityOdd             // Odd parity required
} PicoP_RS232ParityE;

// ****************************************************************************
//    Used to pass data of a specified type across library interfaces.

typedef struct
{
    PicoP_DataTypeE dataType;   // Type of data being stored
    union
    {
        INT8    int8;           // 8 bit signed value
        INT16   int16;          // 16 bit signed value
        INT32   int32;          // 32 bti signed value
        UINT8   uint8;          // 8 bit unsigned value
        UINT16  uint16;         // 16 bit unsigned value
        UINT32  uint32;         // 32 bit unsigned value
        FP32    fp32;           // 32 bit IEEE754 floating point value
        void*   voidp;          // A pointer to a void, must be cast to the appropriate type
    };
} PicoP_Data;

// ****************************************************************************
// Library information

typedef struct
{
    UINT8    majorVersion;      // Contains the major version of the library
    UINT8    minorVersion;      // Contains the minor version of the library
    UINT8    patchVersion;      // Contains the patch version of the library
    UINT32   capabilityFlags;   // Flags that describe the capbility of this version of the ALC library
} PicoP_LibraryInfo;

// ****************************************************************************
// Parameters for RS232 communication

typedef struct
{
    union
    {
        char const* portName;   // Windows port name, COM1, COM2, etc.
        char const* deviceName; // Linux device name /dev/ttyS0, /dev/ttyS1, etc.
    };

    UINT32 baudRate;            // The baud rate, valid values are:
                                //        4800
                                //        9600
                                //        115200

    PicoP_RS232ParityE parity;  // The parity type
    UINT8 stopBitCount;         // Stop bit count, valid values are 1, and 2
} PicoP_RS232Info;

// ****************************************************************************
// Describes any attributes required for a successful USB connection

typedef struct
{
    UINT32 productID;           // Product ID
    char const*  serialNumber;  // Serial Number
} PicoP_USBInfo;

// ****************************************************************************
// Parameters for Bluetooth communication

typedef struct
{
    const char    *bthMacAddr;  // Bluetooth MAC address.
    const char    *passKey;     // Bluetooth authentication key
} PicoP_BTHInfo;

// ****************************************************************************
// Contains physical connection parameters for RS232, USB, or Bluetooth
//     Only one is valid at a time, parameter type is given by connectionType.

typedef union
{
    PicoP_RS232Info rs232Info;  // Parameters for an RS232 connection
    PicoP_USBInfo usbInfo;      // Parameter for a USB connection
    PicoP_BTHInfo bthInfo;      // Parameter for a Bluetooth connection
} PicoP_ConnectionInfo;

// ****************************************************************************
// Contains physical connection parameters for both USB or RS232
//     Only one is valid at a time, parameter type is given by connectionType.

typedef struct
{
    PicoP_ConnectionTypeE connectionType; // Defines whether the struct contains
                                          // info for an RS232, USB, or Bluetooth connection

    union
    {
        PicoP_RS232Info rs232Info;        // Parameters for an RS232 connection
        PicoP_USBInfo usbInfo;            // Parameter for a USB connection
        PicoP_BTHInfo bthInfo;            // Parameter for a Bluetooth connection
    };
} PicoP_ConnectionInfoEx;

// ****************************************************************************
// System information struct

typedef struct
{
    char serialNumber[SYSTEM_SN_LEN];   // System serial number
    UINT32 softwareVersion;             // Software version information
    UINT32 FPGAVersion;                 // FPGA version
} PicoP_SystemInfo;

// ****************************************************************************
// System Event struct

typedef struct
{
    UINT16 session;     // session number when event occureed
    UINT16 eventId;     // Event ID
    UINT32 time;        // Event time stamp
    UINT32 data;        // Event data
    UINT16 cid;         // Event component ID
    UINT16 line;        // Event line number
} PicoP_Event;

// ****************************************************************************
// Defines enums for vsync, hsync and clock polarities

typedef enum
{
    ePOLARITY_NEGATIVE,         // Negative polarity
    ePOLARITY_POSITIVE,         // Positive polarity
} PicoP_PolarityE;

// ****************************************************************************
// Aspect Ratio Modes - Display Output Scaling.

typedef enum
{
    eASPECT_RATIO_NORMAL,           // Normal Mode
    eASPECT_RATIO_WIDESCREEN,       // Widescreen Mode, 16:9 aspect ratio.
    eASPECT_RATIO_ZOOM_HORIZONTAL,  // Zoom To Fit Horizontally, retaining aspect ratio
    eASPECT_RATIO_ZOOM_VERTICAL,    // Zoom To Fit Vertically, retaining aspect ratio
    eASPECT_RATIO_ZOOM_ANAMORPHIC   // Zoom To Fit Horizonally and Vertically, regardless of original aspect ratio
} PicoP_AspectRatioModeE;


// ****************************************************************************
// Defines enums for color space property selection

typedef enum
{
    eCOLOR_SPACE_RGB = 0,       // Deprecated
    eCOLOR_SPACE_YCBCR,         // Deprecated
    eCOLOR_SPACE_YPBPR,         // Deprecated
    eCOLOR_SPACE_RGB_DIRECT,
    eCOLOR_SPACE_REC601_YCBCR,
    eCOLOR_SPACE_REC601_BT656,
    eCOLOR_SPACE_REC709_YCBCR   // Reserved for Future use
} PicoP_VideoColorSpaceE;

// ****************************************************************************
// Defines enums for interlace property selection

typedef enum
{
    eINTERLACE_NONE,
    eINTERLACE_EVEN_FIELD,
    eINTERLACE_ODD_FIELD
} PicoP_InterlaceE;

// ****************************************************************************
// Defines enums for Color selection

typedef enum
{
    eRED = 0,                   // Enumeration definition for Color Red
    eGREEN,                     // Enumeration definition for Color Green
    eBLUE,                      // Enumeration definition for Color Blue
    eALL_COLORS                 // Enumeration definition for All 3 colors
} PicoP_ColorE;

// ****************************************************************************
// A color represents a (R,G,B) color value

typedef struct
{
    UINT8 R;            // Red color value
    UINT8 G;            // Green color value
    UINT8 B;            // Blue color value
    UINT8 A;            // Alpha value (for future use)
} PicoP_Color;

// ****************************************************************************
// Defines enums for types of storage for the value queried on the system

typedef enum
{
    eCURRENT_VALUE = 0,         // Current value
    eVALUE_ON_STARTUP,          // Value on system startup
    eFACTORY_VALUE              // Value set at the Factory
} PicoP_ValueStorageTypeE;

// ****************************************************************************
// Color Modes

typedef enum
{
    eCOLOR_MODE_BRILLIANT,      // Brilliant color mode
    eCOLOR_MODE_STANDARD,       // Standard Color mode
    eCOLOR_MODE_INVERTED,       // Inverted Color Mode
} PicoP_ColorModeE;

// ****************************************************************************
// Directions

typedef enum
{
    eHORIZONTAL = 0,            // Horizontal direction
    eVERTICAL,                  // Vertical direction
    eBOTH                       // Both directions
} PicoP_DirectionE;

// ****************************************************************************
// Test Patterns

typedef enum
{
    eCHECKER_BOARD_PATTERN  = 0,    // Checker board pattern      
    eSPLASH_SCREEN          = 2,    // Splash screen
    eGRID_PATTERN_16x12     = 3,    // Grid Pattern
    eCROSS_HAIR_PATTERN     = 4,    // Cross hair in a square
    eALL_ON                 = 5,    // Full color specified
    eALL_OFF                = 6,    // Blank
    eNINE_POINT_PATTERN     = 8,    // 9 rectangles divided to be 27% of the screen
    e9x7_DOTS_PATTERN       = 36,   // eTEST_PATTERN_9x7_DOTS
    eNUM_PATTERNS
} PicoP_TestPatternInfoE;

// ****************************************************************************
// Warping Operations

typedef enum
{
    eROTATE = 0,                // Rotation
    eSMILE,                     // Smile and De-smile
    ePARALLELOGRAM,             // Parallelogram
    eSTRETCH_UPPER_LEFT,        // Stretch Upper left
    eSTRETCH_UPPER_RIGHT,       // Stretch Upper right
    eSTRETCH_LOWER_LEFT,        // Stretch lower left
    eSTRETCH_LOWER_RIGHT,       // Stretch lower right
    eSCALE_HORIZONTAL,          // Scale image horizontally
    eSCALE_VERTICAL             // Scale image vertically
} PicoP_WarpOperationE;

// ****************************************************************************
// Warp Function States

typedef enum
{
    eWARP_DISABLED,             // Warp is Disabled
    eWARP_ENABLED               // Warp is Enabled
} PicoP_WarpStateE;

// ****************************************************************************
// Output Video States

typedef enum
{
    eOUTPUT_VIDEO_DISABLED,     // Output video is Disabled
    eOUTPUT_VIDEO_ENABLED       // Output video is Enabled
} PicoP_OutputVideoStateE;

// ****************************************************************************
// Input Video States

typedef enum
{
    eINPUT_VIDEO_DISABLED,      // Input video is Disabled
    eINPUT_VIDEO_ENABLED        // Input video is Enabled
} PicoP_InputVideoStateE;

// ****************************************************************************
// On-Screen Display (OSD) States

typedef enum
{
    eOSD_DISABLED,              // OSD is Disabled
    eOSD_ENABLED                // OSD is Enabled
} PicoP_OSDStateE;

// ****************************************************************************
// Video Capture Modes

typedef enum
{
    eCAPTURE_MODE_848x480,      // Built-in Capture Mode for 848x480
    eCAPTURE_MODE_800x480,      // Built-in Capture Mode for 800x480
    eCAPTURE_MODE_640x480       // Built-in Capture Mode for 640x480
} PicoP_VideoCaptureModeE;

// ****************************************************************************
// Target rendering buffers for draw functions

typedef enum
{
    eFRAME_BUFFER_0,            // FrameBuffer 0
    eFRAME_BUFFER_1,            // FrameBuffer 1
    eFRAME_BUFFER_2,            // FrameBuffer 2
    eOSD_0,                     // On Screen Display 0
    eOSD_1                      // On Screen Display 1
} PicoP_RenderTargetE;

// ****************************************************************************
// Color Converter

typedef enum
{
    eRED_TO_RED = 0,    // Red to Red
    eGREEN_TO_RED,      // Green to Red
    eBLUE_TO_RED,       // Blue to Red
    eRED_TO_GREEN,      // Red to Green
    eGREEN_TO_GREEN,    // Green to Green
    eBLUE_TO_GREEN,     // Blue to Green
    eRED_TO_BLUE,       // Red to Blue
    eGREEN_TO_BLUE,     // Green to Blue
    eBLUE_TO_BLUE       // Blue to Blue
} PicoP_ColorConvertE;

// ****************************************************************************
// Color Converter States

typedef enum
{
    eCOLORCONVERT_DISABLED = 0, // Color Converer is Disabled
    eCOLORCONVERT_ENABLED       // Color Converer is Enabled
} PicoP_ColorConvertStateE;

// ****************************************************************************
// A point represents a location in (x,y) display space.

typedef struct
{
    UINT16 x;       // horizontal x coordinate
    UINT16 y;       // vertical y coordinate
} PicoP_Point;

typedef struct
{
    UINT16 width;   // horizontal x extents
    UINT16 height;  // vertical y extents
} PicoP_Extents;

typedef struct
{
    UINT16 width;   // horizontal width
    UINT16 height;  // vertical height
} PicoP_RectSize;

typedef enum
{
    eRUNNING,       // System Running
    eSTANDBY,       // System Standby
    eSHUTDOWN       // System Shutdown
} PicoP_PowerStateE;

// ****************************************************************************
// Built in video formats

typedef enum
{
    eVideoModeHandle_640x480 = 3,
    eVideoModeHandle_800x480 = 8,
    eVideoModeHandle_848x480 = 15,
    eVideoModeHandle_INVALID = 13,
    eVideoModeHandle_720p    = 40,
    eVideoModeHandle_USER    = 41
} PicoP_VideoModeHandleE;

// ****************************************************************************
// Video information struct

typedef struct
{
    PicoP_Point                 videoStartPosition; // video capture start line and pixel.
    PicoP_PolarityE             hSyncPolarity;      // polarity of HYSNC signal
    PicoP_PolarityE             vSyncPolarity;      // polarity of VSYNC signal
    PicoP_PolarityE             pixelClockEdge;     // active edge of pixel clock
    PicoP_Extents               resolution;         // x & y resolution of video mode
    FP32                        pixelAspectRatio;   // Pixel aspect ratio ranges from 0.8 to 1.2.
    PicoP_VideoColorSpaceE      colorSpace;         // color space of the input video mode
    PicoP_InterlaceE            interlaceField;     // interlace field to capture
}PicoP_VideoCaptureInfo;

// ****************************************************************************
// System Status

typedef struct
{
       UINT32 status;           // 32 bit value, 0 is system OK and non-zero value indicates system not OK
       UINT32 state;            // System State. Bit pattern describing system state.  E.g. ready accept video
       FP32 temperature;        // PDE Temperature
       UINT32 data0;            // Data 0 for future expansion
       UINT32 data1;            // Data 1 for future expansion
       UINT32 data2;            // Data 2 for future expansion
       UINT32 data3;            // Data 3 for future expansion
       UINT32 data4;            // Data 4 for future expansion
} PicoP_SystemStatus;

// ****************************************************************************
// FlipState

typedef enum
{
    eFLIP_NEITHER = 0,      // Neither direction
    eFLIP_HORIZONTAL,       // Horizontal Flip
    eFLIP_VERTICAL,         // Vertical Flip
    eFLIP_BOTH              // Both directions
} PicoP_FlipStateE;

// ****************************************************************************
// Gamma Boost Modes

typedef enum
{
    eGAMMA_BOOST_MODE_NONE = 0,
    eGAMMA_BOOST_MODE_VIRTUAL_LUMENS_30PCT,
    eNUM_GAMMA_BOOST_MODES
} PicoP_GammaBoostModeE;

// ****************************************************************************
// SPI CS definitions
// These must be the same as PicoP_ChipE in mv350_software:mv_defs.h

typedef enum
{
    eSPI_CHIP_MV250,
    eSPI_CHIP_RESERVED,
    eSPI_CHIP_LDD,
    eSPI_CHIP_MV117,
    eSPI_CHIP_MTOF_MV601,
    eSPI_CHIP_MTOF_TX,
    eSPI_CHIP_MTOF_RX0,
    eSPI_CHIP_MTOF_RX1,
} PicoP_ChipE;

#endif // PICOP_DEF_H
