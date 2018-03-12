//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!
//! \file
//!
//! \brief ToF API (TLC) for communication to the MVIS
//!        PicoP Display Engine.
//!
//! Copyright (C) 2017 MicroVision, Inc.
//!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef PICOP_TLC_API_H
#define PICOP_TLC_API_H

#include "PicoP_Def.h"
#include "PicoP_TLC_Def.h"
#include "PicoP_RC.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MV_TLC_EXPORTS
#define MV_TLC_API __declspec(dllexport)
#else
#define MV_TLC_API
#endif

#ifdef __WINDOWS__
#define CALLBACK __stdcall
#else
#ifndef CALLBACK
#define CALLBACK
#endif
#endif


typedef UINT32 (*PICOP_EVENT_CALLBACK)(void *pvParam,
                                       PicoP_TofEventE eEventType,
                                       void *pEvent);

MV_TLC_API PICOP_RC PicoP_TLC_OpenLibrary(PicoP_HANDLE *library_handle);

MV_TLC_API PICOP_RC PicoP_TLC_CloseLibrary(const PicoP_HANDLE library_handle);

MV_TLC_API PICOP_RC
PicoP_TLC_OpenConnection(const PicoP_HANDLE library_handle,
                         const PicoP_ConnectionTypeE connection_type,
                         const PicoP_ConnectionInfo connection_info,
                         PicoP_HANDLE *connection_handle);

MV_TLC_API PICOP_RC
PicoP_TLC_CloseConnection(const PicoP_HANDLE connection_handle);

MV_TLC_API PICOP_RC
PicoP_TLC_OpenConnectionUsb(const PicoP_HANDLE library_handle,
                            const PicoP_USBInfo connection_info,
                            PicoP_HANDLE *connection_handle);

MV_TLC_API PICOP_RC
PicoP_TLC_OpenConnectionRs232(const PicoP_HANDLE library_handle,
                              const PicoP_RS232Info connection_info,
                              PicoP_HANDLE *connection_handle);

MV_TLC_API PICOP_RC
PicoP_TLC_SetCalData(const PicoP_HANDLE connection_handle,
                     const UINT32 cal_data_size,
                     const UINT8 cal_data_block[MAX_CAL_DATA_SIZE]);

MV_TLC_API PICOP_RC
PicoP_TLC_GetCalData(const PicoP_HANDLE connection_handle,
                     UINT32 *cal_data_size,
                     UINT8 cal_data_block[MAX_CAL_DATA_SIZE]);


MV_TLC_API PICOP_RC PicoP_TLC_SetSensingState(
    const PicoP_HANDLE connection_handle, /**< [IN] Connection handle */
    const PicoP_SensingStateE state,      /**< [IN] Enabled or Disabled */
    const BOOL commit                     /**< [IN] Commit */
    );

MV_TLC_API PICOP_RC PicoP_TLC_GetSensingState(
    const PicoP_HANDLE connection_handle,     /**< [IN] Connection handle */
    PicoP_SensingStateE *const pState,        /**< [OUT] Sensing State */
    const PicoP_ValueStorageTypeE storageType /**< [IN] Current Value, Value on
                                                 system startup, or Factory
                                                 value */
    );

MV_TLC_API PICOP_RC PicoP_TLC_SetSensingDataInterface(
    const PicoP_HANDLE connection_handle,     /**< [IN] Connection handle */
    const PicoP_SensingDataInterfaceE dataIf, /**< [IN] Data interface */
    const BOOL commit                         /**< [IN] Commit */
    );

MV_TLC_API PICOP_RC PicoP_TLC_GetSensingDataInterface(
    const PicoP_HANDLE connection_handle,       /**< [IN] Connection handle */
    PicoP_SensingDataInterfaceE *const pDataIf, /**< [OUT] Data interface */
    const PicoP_ValueStorageTypeE storageType /**< [IN] Current Value, Value on
                                                 system startup, or Factory
                                                 value */
    );


MV_TLC_API PICOP_RC PicoP_TLC_SetTofPulsingConfig(
    const PicoP_HANDLE connection_handle, /**< [IN] Connection handle */
    const PicoP_TofPulsingConfig *
        pTofPulsingConfig, /**< [IN] ToF Pulsing Config Structure */
    const BOOL commit      /**< [IN] Commit */
    );


MV_TLC_API PICOP_RC PicoP_TLC_GetTofPulsingConfig(
    const PicoP_HANDLE connection_handle, /**< [IN] Connection handle */
    PicoP_TofPulsingConfig *const
        pTofPulsingConfig, /**< [OUT] Returned ToF Pulsing Config Structure */
    const PicoP_ValueStorageTypeE storageType /**< [IN] Current Value, Value on
                                                 system startup, or Factory
                                                 value */
    );

MV_TLC_API PICOP_RC PicoP_TLC_SetTofDataFormat(
    const PicoP_HANDLE connection_handle,  /**< [IN] Connection handle */
    const PicoP_ToFDataFormatE dataFormat, /**< [IN] Data format */
    const BOOL commit                      /**< [IN] Commit */
    );

MV_TLC_API PICOP_RC PicoP_TLC_GetTofDataFormat(
    const PicoP_HANDLE connection_handle,     /**< [IN] Connection handle */
    PicoP_ToFDataFormatE *const pDataFormat,  /**< [OUT] Data format */
    const PicoP_ValueStorageTypeE storageType /**< [IN] Current Value, Value on
                                                 system startup, or Factory
                                                 value */
    );

MV_TLC_API PICOP_RC
PicoP_TLC_SetEventCallbackFunction(const PicoP_HANDLE connection_handle,
                                   const PICOP_EVENT_CALLBACK pfnEventCallback,
                                   const UINT32 dwFlags);

MV_TLC_API PICOP_RC PicoP_TLC_GetTofFrameCount(
    const PicoP_HANDLE connection_handle, /**< [IN] Connection handle */
    UINT32 *const pCount                  /**< [OUT] Number of Frames available */
    );

MV_TLC_API PICOP_RC PicoP_TLC_GetTofFrameDimensions(const PicoP_HANDLE connection_handle,
                                                    UINT32* const pFrameDimensions /**< [OUT] Size fo frame in bytes */
                                                    );

MV_TLC_API PICOP_RC PicoP_TLC_AcquireTofFrame(
    const PicoP_HANDLE connection_handle, /**< [IN] Connection handle */
    const UINT32 frameCount,              /**< [IN] Number of frames to acquire */
    UINT32 *const pData,                   /**< [OUT] Data Buffer */
    UINT32 *const pRetFrameCount          /**< [OUT] Returned frame count */
    );

//! 
//! \brief Retrieves TOF data into PCD (point cloud data) format
//!
//! Puts the TOF frame data into PCD format. The format starts
//! with a PCD header, in a format of PicoP_Pcd_Hdr, as defined in PicoP_TLC_Def.h.
//! This is followed by pixel data where each pixel is in format of 
//! PicoP_Pcd_Data as defined PicoP_TLC_Def.h
//!
//! \param[in] pData Pointer to data buffer to store data
//! \return result of PicoP_TLC_AcquireTofFramePcd
//!
MV_TLC_API PICOP_RC PicoP_TLC_AcquireTofFramePcd(
    UINT32 *const pData                   /**< [OUT] Data Buffer */
);

//!
//! \brief Sets TOF tx chip fall and rise time registers
//!
//! \param[in] connection_handle
//! \param[in] tx_fall code to set the IR laser fall time slope, min 0, max TX_FALL_MAX
//! \param[in] tx_rise code to set the IR laser rise time slope, min 0, max TX_RISE_MAX
//! \param[in] commit commit change to persistent memory, commit 1, don't commit 0
//! \return result of PicoP_TLC_SetTxFallRise
//!
MV_TLC_API PICOP_RC PicoP_TLC_SetTxFallRise(
    const PicoP_HANDLE connection_handle, /**< [IN] Connection handle */
    UINT32 const tx_fall,                  /**< [IN] TX fall time slope code */
    UINT32 const tx_rise,                  /**< [IN] TX rise time slope code*/
    const BOOL commit                     /**< [IN] Commit */
    );

//!
//! \brief Returns the TOF tx chip fall and rise time storageType values
//!
//! \param[in] connection_handle
//! \param[out] ptx_fall TX fall time code
//! \param[out] ptx_rise TX rise time code
//! \param[in] storageType Current Value, Value on system startup, or Factory value
//! \return result of PicoP_TLC_GetTxFallRise
//!
MV_TLC_API PICOP_RC PicoP_TLC_GetTxFallRise(
    const PicoP_HANDLE connection_handle,     /**< [IN] Connection handle */
    UINT32 *const ptx_fall,                   /**< [OUT] TX fall time code */
    UINT32 *const ptx_rise,                   /**< [OUT] TX rise time code */
    const PicoP_ValueStorageTypeE storageType /**< [IN] Current Value, Value on
                                                     system startup, or Factory
                                                     value */
    );

//!
//! \brief Sets TOF d out b TDC depth data scale factor
//!
//! \param[in] connection_handle
//! \param[in] dout_b_scale TDC B depth data scale factor for reducing the
//!            amount of data read from TDC B by a scale of
//!            (dout_b_scale/DOUTB_SCALE_MAX), min 0, max DOUTB_SCALE_MAX
//! \param[in] commit commit change to persistent memory, commit 1, don't commit 0
//! \return result of PicoP_TLC_SetDOutBScale
//!
MV_TLC_API PICOP_RC PicoP_TLC_SetDOutBScale(
    const PicoP_HANDLE connection_handle, /**< [IN] Connection handle */
    UINT32 const dout_b_scale,            /**< [IN] TDC B depth data scale factor */
    const BOOL commit                     /**< [IN] Commit */
    );

//!
//! \brief Returns the TOF dout b scale storageType values
//!
//! \param[in] connection_handle
//! \param[in] pdout_b_scale TDC B depth data scale factor
//! \param[in] storageType Current Value, Value on system startup, or Factory value
//! \return result of PicoP_TLC_GetDOutBScale
//!
MV_TLC_API PICOP_RC PicoP_TLC_GetDOutBScale(
    const PicoP_HANDLE connection_handle,     /**< [IN] Connection handle */
    UINT32 *const pdout_b_scale,              /**< [OUT] TDC B depth data scale factor */
    const PicoP_ValueStorageTypeE storageType /**< [IN] Current Value, Value on
                                                     system startup, or Factory
                                                     value */
    );


//!
//! \brief Returns the SDK sw version
//!
//! \param[in] libraryInfo is ptr to buffer where sw version info will be stored
//!
MV_TLC_API PICOP_RC PicoP_TLC_GetLibraryInfo(
    PicoP_LibraryInfo* const libraryInfo
    );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // PICOP_TLC_API_H
