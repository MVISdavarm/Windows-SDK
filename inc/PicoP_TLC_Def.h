//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!
//! \file
//!
//! \brief ToF API (TLC) definitions for communication to the MVIS
//!        PicoP Display Engine.
//!
//! Copyright (C) 2017 MicroVision, Inc.
//!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef PICOP_TLC_DEF_H
#define PICOP_TLC_DEF_H

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define MAX_SPI_DATA_BYTES 7
// We need a minimum defined for the sake of TLC code generation
#define MAX_CAL_DATA_SIZE 4000
#define TOF_CAL_HEADER_SIGNATURE 4275164936U // 0xfed1d708U
#define TX_FALL_MAX 15U //max code for tx rising slope
#define TX_RISE_MAX 15U //max code for tx falling slope
#define DOUTB_SCALE_MAX 0x1000U //max data scale factor from TDC B

/**
* Sensing States
*/
typedef enum
{
    eSENSING_DISABLED = 0, /**< Sensing is Disabled */
    eSENSING_ENABLED       /**< Sensing is Enabled */
} PicoP_SensingStateE;

/**
* Sensing Data Interfaces
*/
typedef enum
{
    eSENSING_DATA_INTERFACE_USB = 0, /**< USB Interface */
    eSENSING_DATA_INTERFACE_MIPI,    /**< MIPI-CSI Interface */
    eSENSING_DATA_INTERFACE_USB_MIPI /**< Both USB and MIPI-CSI Interfaces */
} PicoP_SensingDataInterfaceE;

/**
* Tof Pulsing Modes
*/
typedef enum
{
    eTOF_PULSING_EQUAL_ANGLE = 0, /**< Equal Angle Pulsing */
    eTOF_PULSING_EQUAL_TIME,      /**< Equal Time Pulsing */
    eTOF_PULSING_POLYNOMIAL       /**< Polynomial Pulsing Pattern */
} PicoP_ToFPulsingModeE;

/**
* Sensing Data Format
*/
typedef enum
{
    eTOF_DATA_FUSED = 0, /**< Fused Depth & Amplitude Data */
    eTOF_DATA_LEFT_SENSOR_ONLY, /**< Left Detector Depth & Amplitude Data */
    eTOF_DATA_RIGHT_SENSOR_ONLY, /**< Right Detector Depth & Amplitude Data */
    eTOF_DATA_DEPTH_ONLY, /**< Depth data from both detectors, left then right */
    eTOF_DATA_AMPLITUDE_ONLY,   /**< Amplitude data from both detectors, left then right*/
    eTOF_DATA_ALL, /**<Left and Right Detector Depth & Amplitude Data (Note: 2 x bandwidth)*/
} PicoP_ToFDataFormatE;

/**
* Asynchronous PicoMagine Events
*/
typedef enum
{
    eEVENT_TOF_RESERVED = 0,        /**< Reserved Event */
    eEVENT_TOF_DATA_FRAMES_RECEIVED /**< One or more 3D TOF data frames received
                                       */
} PicoP_TofEventE;

typedef struct
{
    PicoP_ToFPulsingModeE pulsingMode; /**< Pulsing Mode */
    UINT16 nrPulsesPerLine; /**< number of pulses per line */
    UINT32 nrLinePhases;  /**< Number of phased lines: 0, 2, or 4 */
    UINT32 nrFramePhases; /**< Number of phased frames: 0 - 4     */
    UINT32 params0;       /**< For future expansion */
    UINT32 params1;       /**< For future expansion */
} PicoP_TofPulsingConfig;


#define N_PCD_HDR_CHARS 32


//! 
//! \brief PCD (point cloud data) header
//!
//! The size of each string was self-imposed to be fixed 
//! and large enough to hold the expected string and 
//! for future expansion.
//!
typedef struct
{
    char version[N_PCD_HDR_CHARS];
    char fields[N_PCD_HDR_CHARS];
    char size[N_PCD_HDR_CHARS];
    char type[N_PCD_HDR_CHARS];
    char count[N_PCD_HDR_CHARS];
    char width[N_PCD_HDR_CHARS];
    char height[N_PCD_HDR_CHARS];
    char viewpoint[N_PCD_HDR_CHARS];
    char point[N_PCD_HDR_CHARS];
    char dataType[N_PCD_HDR_CHARS];
} PicoP_Pcd_Hdr;

//! 
//! \brief PCD (point cloud data) pixel format
//!
//! Each pixel is in this data format where x, y, and z
//! is the cartesian coordinates in units of millimeters, 
//! and intensity is the amplitude data. 
//!
typedef struct
{
    INT32 x; /**< x coordinate */
    INT32 y; /**< y coordinate */
    INT32 z; /**< z coordinate */
    UINT32 intensity; /**< intensity */
} PicoP_Pcd_Data;

#endif // PICOP_TLC_DEF_H
