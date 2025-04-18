/****************************************************************************
 *
 *  Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dinputd.h
 *  Content:    DirectInput include file for device driver implementors
 *
 ****************************************************************************/

#ifndef __DINPUTD_INCLUDED__
#define __DINPUTD_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 *      Interfaces
 *
 ****************************************************************************/

#ifndef DIJ_RINGZERO

DEFINE_GUID(IID_IDirectInputEffectDriver,   0x02538130,0x898F,0x11D0,0x9A,0xD0,0x00,0xA0,0xC9,0xA0,0x6E,0x35);
DEFINE_GUID(IID_IDirectInputJoyConfig,      0x1DE12AB1,0xC9F5,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_GAMEENUM_BUS_ENUMERATOR, 0xcae56030, 0x684a, 0x11d0, 0xd6, 0xf6, 0x00, 0xa0, 0xc9, 0x0f, 0x57, 0xda);

#endif /* DIJ_RINGZERO */

/****************************************************************************
 *
 *      IDirectInputEffectDriver
 *
 ****************************************************************************/

typedef struct DIOBJECTATTRIBUTES {
    DWORD   dwFlags;
    WORD    wUsagePage;
    WORD    wUsage;
} DIOBJECTATTRIBUTES, *LPDIOBJECTATTRIBUTES;
typedef const DIOBJECTATTRIBUTES *LPCDIOBJECTATTRIBUTES;

typedef struct DIFFOBJECTATTRIBUTES {
    DWORD   dwFFMaxForce;
    DWORD   dwFFForceResolution;
} DIFFOBJECTATTRIBUTES, *LPDIFFOBJECTATTRIBUTES;
typedef const DIFFOBJECTATTRIBUTES *LPCDIFFOBJECTATTRIBUTES;

typedef struct DIOBJECTCALIBRATION {
    LONG    lMin;
    LONG    lCenter;
    LONG    lMax;
} DIOBJECTCALIBRATION, *LPDIOBJECTCALIBRATION;
typedef const DIOBJECTCALIBRATION *LPCDIOBJECTCALIBRATION;

typedef struct DIEFFECTATTRIBUTES {
    DWORD   dwEffectId;
    DWORD   dwEffType;
    DWORD   dwStaticParams;
    DWORD   dwDynamicParams;
    DWORD   dwCoords;
} DIEFFECTATTRIBUTES, *LPDIEFFECTATTRIBUTES;
typedef const DIEFFECTATTRIBUTES *LPCDIEFFECTATTRIBUTES;

typedef struct DIFFDEVICEATTRIBUTES {
    DWORD   dwFlags;
    DWORD   dwFFSamplePeriod;
    DWORD   dwFFMinTimeResolution;
} DIFFDEVICEATTRIBUTES, *LPDIFFDEVICEATTRIBUTES;
typedef const DIFFDEVICEATTRIBUTES *LPCDIFFDEVICEATTRIBUTES;

typedef struct DIDRIVERVERSIONS {
    DWORD   dwSize;
    DWORD   dwFirmwareRevision;
    DWORD   dwHardwareRevision;
    DWORD   dwFFDriverVersion;
} DIDRIVERVERSIONS, *LPDIDRIVERVERSIONS;
typedef const DIDRIVERVERSIONS *LPCDIDRIVERVERSIONS;

typedef struct DIDEVICESTATE {
    DWORD   dwSize;
    DWORD   dwState;
    DWORD   dwLoad;
} DIDEVICESTATE, *LPDIDEVICESTATE;

#define DEV_STS_EFFECT_RUNNING  DIEGES_PLAYING

#ifndef DIJ_RINGZERO

typedef struct DIHIDFFINITINFO {
    DWORD   dwSize;
    LPWSTR  pwszDeviceInterface;
} DIHIDFFINITINFO, *LPDIHIDFFINITINFO;

#undef INTERFACE
#define INTERFACE IDirectInputEffectDriver

DECLARE_INTERFACE_(IDirectInputEffectDriver, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirectInputEffectDriver methods ***/
    STDMETHOD(DeviceID)(THIS_ DWORD,DWORD,DWORD,DWORD,LPVOID) PURE;
    STDMETHOD(GetVersions)(THIS_ LPDIDRIVERVERSIONS) PURE;
    STDMETHOD(Escape)(THIS_ DWORD,DWORD,LPDIEFFESCAPE) PURE;
    STDMETHOD(SetGain)(THIS_ DWORD,DWORD) PURE;
    STDMETHOD(SendForceFeedbackCommand)(THIS_ DWORD,DWORD) PURE;
    STDMETHOD(GetForceFeedbackState)(THIS_ DWORD,LPDIDEVICESTATE) PURE;
    STDMETHOD(DownloadEffect)(THIS_ DWORD,DWORD,LPDWORD,LPCDIEFFECT,DWORD) PURE;
    STDMETHOD(DestroyEffect)(THIS_ DWORD,DWORD) PURE;
    STDMETHOD(StartEffect)(THIS_ DWORD,DWORD,DWORD,DWORD) PURE;
    STDMETHOD(StopEffect)(THIS_ DWORD,DWORD) PURE;
    STDMETHOD(GetEffectStatus)(THIS_ DWORD,DWORD,LPDWORD) PURE;
};

typedef struct IDirectInputEffectDriver *LPDIRECTINPUTEFFECTDRIVER;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirectInputEffectDriver_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectInputEffectDriver_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectInputEffectDriver_Release(p) (p)->lpVtbl->Release(p)
#define IDirectInputEffectDriver_DeviceID(p,a,b,c,d,e) (p)->lpVtbl->DeviceID(p,a,b,c,d,e)
#define IDirectInputEffectDriver_GetVersions(p,a) (p)->lpVtbl->GetVersions(p,a)
#define IDirectInputEffectDriver_Escape(p,a,b,c) (p)->lpVtbl->Escape(p,a,b,c)
#define IDirectInputEffectDriver_SetGain(p,a,b) (p)->lpVtbl->SetGain(p,a,b)
#define IDirectInputEffectDriver_SendForceFeedbackCommand(p,a,b) (p)->lpVtbl->SendForceFeedbackCommand(p,a,b)
#define IDirectInputEffectDriver_GetForceFeedbackState(p,a,b) (p)->lpVtbl->GetForceFeedbackState(p,a,b)
#define IDirectInputEffectDriver_DownloadEffect(p,a,b,c,d,e) (p)->lpVtbl->DownloadEffect(p,a,b,c,d,e)
#define IDirectInputEffectDriver_DestroyEffect(p,a,b) (p)->lpVtbl->DestroyEffect(p,a,b)
#define IDirectInputEffectDriver_StartEffect(p,a,b,c,d) (p)->lpVtbl->StartEffect(p,a,b,c,d)
#define IDirectInputEffectDriver_StopEffect(p,a,b) (p)->lpVtbl->StopEffect(p,a,b)
#define IDirectInputEffectDriver_GetEffectStatus(p,a,b,c) (p)->lpVtbl->GetEffectStatus(p,a,b,c)
#else
#define IDirectInputEffectDriver_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirectInputEffectDriver_AddRef(p) (p)->AddRef()
#define IDirectInputEffectDriver_Release(p) (p)->Release()
#define IDirectInputEffectDriver_DeviceID(p,a,b,c,d,e) (p)->DeviceID(a,b,c,d,e)
#define IDirectInputEffectDriver_GetVersions(p,a) (p)->GetVersions(a)
#define IDirectInputEffectDriver_Escape(p,a,b,c) (p)->Escape(a,b,c)
#define IDirectInputEffectDriver_SetGain(p,a,b) (p)->SetGain(a,b)
#define IDirectInputEffectDriver_SendForceFeedbackCommand(p,a,b) (p)->SendForceFeedbackCommand(a,b)
#define IDirectInputEffectDriver_GetForceFeedbackState(p,a,b) (p)->GetForceFeedbackState(a,b)
#define IDirectInputEffectDriver_DownloadEffect(p,a,b,c,d,e) (p)->DownloadEffect(a,b,c,d,e)
#define IDirectInputEffectDriver_DestroyEffect(p,a,b) (p)->DestroyEffect(a,b)
#define IDirectInputEffectDriver_StartEffect(p,a,b,c,d) (p)->StartEffect(a,b,c,d)
#define IDirectInputEffectDriver_StopEffect(p,a,b) (p)->StopEffect(a,b)
#define IDirectInputEffectDriver_GetEffectStatus(p,a,b,c) (p)->GetEffectStatus(a,b,c)
#endif


#endif /* DIJ_RINGZERO */


/****************************************************************************
 *
 *      IDirectInputJoyConfig
 *
 ****************************************************************************/

/****************************************************************************
 *
 *      Definitions copied from the DDK
 *
 ****************************************************************************/

#ifndef JOY_HW_NONE

/* pre-defined joystick types */
#define JOY_HW_NONE                     0
#define JOY_HW_CUSTOM                   1
#define JOY_HW_2A_2B_GENERIC            2
#define JOY_HW_2A_4B_GENERIC            3
#define JOY_HW_2B_GAMEPAD               4
#define JOY_HW_2B_FLIGHTYOKE            5
#define JOY_HW_2B_FLIGHTYOKETHROTTLE    6
#define JOY_HW_3A_2B_GENERIC            7
#define JOY_HW_3A_4B_GENERIC            8
#define JOY_HW_4B_GAMEPAD               9
#define JOY_HW_4B_FLIGHTYOKE            10
#define JOY_HW_4B_FLIGHTYOKETHROTTLE    11
#define JOY_HW_LASTENTRY                12

/* calibration flags */
#define JOY_ISCAL_XY            0x00000001l     /* XY are calibrated */
#define JOY_ISCAL_Z             0x00000002l     /* Z is calibrated */
#define JOY_ISCAL_R             0x00000004l     /* R is calibrated */
#define JOY_ISCAL_U             0x00000008l     /* U is calibrated */
#define JOY_ISCAL_V             0x00000010l     /* V is calibrated */
#define JOY_ISCAL_POV           0x00000020l     /* POV is calibrated */

/* point of view constants */
#define JOY_POV_NUMDIRS          4
#define JOY_POVVAL_FORWARD       0
#define JOY_POVVAL_BACKWARD      1
#define JOY_POVVAL_LEFT          2
#define JOY_POVVAL_RIGHT         3

/* Specific settings for joystick hardware */
#define JOY_HWS_HASZ            0x00000001l     /* has Z info? */
#define JOY_HWS_HASPOV          0x00000002l     /* point of view hat present */
#define JOY_HWS_POVISBUTTONCOMBOS 0x00000004l   /* pov done through combo of buttons */
#define JOY_HWS_POVISPOLL       0x00000008l     /* pov done through polling */
#define JOY_HWS_ISYOKE          0x00000010l     /* joystick is a flight yoke */
#define JOY_HWS_ISGAMEPAD       0x00000020l     /* joystick is a game pad */
#define JOY_HWS_ISCARCTRL       0x00000040l     /* joystick is a car controller */
/* X defaults to J1 X axis */
#define JOY_HWS_XISJ1Y          0x00000080l     /* X is on J1 Y axis */
#define JOY_HWS_XISJ2X          0x00000100l     /* X is on J2 X axis */
#define JOY_HWS_XISJ2Y          0x00000200l     /* X is on J2 Y axis */
/* Y defaults to J1 Y axis */
#define JOY_HWS_YISJ1X          0x00000400l     /* Y is on J1 X axis */
#define JOY_HWS_YISJ2X          0x00000800l     /* Y is on J2 X axis */
#define JOY_HWS_YISJ2Y          0x00001000l     /* Y is on J2 Y axis */
/* Z defaults to J2 Y axis */
#define JOY_HWS_ZISJ1X          0x00002000l     /* Z is on J1 X axis */
#define JOY_HWS_ZISJ1Y          0x00004000l     /* Z is on J1 Y axis */
#define JOY_HWS_ZISJ2X          0x00008000l     /* Z is on J2 X axis */
/* POV defaults to J2 Y axis, if it is not button based */
#define JOY_HWS_POVISJ1X        0x00010000l     /* pov done through J1 X axis */
#define JOY_HWS_POVISJ1Y        0x00020000l     /* pov done through J1 Y axis */
#define JOY_HWS_POVISJ2X        0x00040000l     /* pov done through J2 X axis */
/* R defaults to J2 X axis */
#define JOY_HWS_HASR            0x00080000l     /* has R (4th axis) info */
#define JOY_HWS_RISJ1X          0x00100000l     /* R done through J1 X axis */
#define JOY_HWS_RISJ1Y          0x00200000l     /* R done through J1 Y axis */
#define JOY_HWS_RISJ2Y          0x00400000l     /* R done through J2 X axis */
/* U & V for future hardware */
#define JOY_HWS_HASU            0x00800000l     /* has U (5th axis) info */
#define JOY_HWS_HASV            0x01000000l     /* has V (6th axis) info */

/* Usage settings */
#define JOY_US_HASRUDDER        0x00000001l     /* joystick configured with rudder */
#define JOY_US_PRESENT          0x00000002l     /* is joystick actually present? */
#define JOY_US_ISOEM            0x00000004l     /* joystick is an OEM defined type */

/* struct for storing x,y, z, and rudder values */
typedef struct joypos_tag {
    DWORD       dwX;
    DWORD       dwY;
    DWORD       dwZ;
    DWORD       dwR;
    DWORD       dwU;
    DWORD       dwV;
} JOYPOS, FAR *LPJOYPOS;

/* struct for storing ranges */
typedef struct joyrange_tag {
    JOYPOS      jpMin;
    JOYPOS      jpMax;
    JOYPOS      jpCenter;
} JOYRANGE,FAR *LPJOYRANGE;

/*
 *  dwTimeout - value at which to timeout joystick polling
 *  jrvRanges - range of values app wants returned for axes
 *  jpDeadZone - area around center to be considered
 *               as "dead". specified as a percentage
 *               (0-100). Only X & Y handled by system driver
 */
typedef struct joyreguservalues_tag {
    DWORD       dwTimeOut;
    JOYRANGE    jrvRanges;
    JOYPOS      jpDeadZone;
} JOYREGUSERVALUES, FAR *LPJOYREGUSERVALUES;

typedef struct joyreghwsettings_tag {
    DWORD       dwFlags;
    DWORD       dwNumButtons;
} JOYREGHWSETTINGS, FAR *LPJOYHWSETTINGS;

/* range of values returned by the hardware (filled in by calibration) */
/*
 *  jrvHardware - values returned by hardware
 *  dwPOVValues - POV values returned by hardware
 *  dwCalFlags  - what has been calibrated
 */
typedef struct joyreghwvalues_tag {
    JOYRANGE    jrvHardware;
    DWORD       dwPOVValues[JOY_POV_NUMDIRS];
    DWORD       dwCalFlags;
} JOYREGHWVALUES, FAR *LPJOYREGHWVALUES;

/* hardware configuration */
/*
 *  hws             - hardware settings
 *  dwUsageSettings - usage settings
 *  hwv             - values returned by hardware
 *  dwType          - type of joystick
 *  dwReserved      - reserved for OEM drivers
 */
typedef struct joyreghwconfig_tag {
    JOYREGHWSETTINGS    hws;
    DWORD               dwUsageSettings;
    JOYREGHWVALUES      hwv;
    DWORD               dwType;
    DWORD               dwReserved;
} JOYREGHWCONFIG, FAR *LPJOYREGHWCONFIG;

/* joystick calibration info structure */
typedef struct joycalibrate_tag {
    UINT    wXbase;
    UINT    wXdelta;
    UINT    wYbase;
    UINT    wYdelta;
    UINT    wZbase;
    UINT    wZdelta;
} JOYCALIBRATE;
typedef JOYCALIBRATE FAR *LPJOYCALIBRATE;

#endif

#ifndef DIJ_RINGZERO

#define MAX_JOYSTRING 256
typedef BOOL (FAR PASCAL * LPDIJOYTYPECALLBACK)(LPCWSTR, LPVOID);

#ifndef MAX_JOYSTICKOEMVXDNAME
#define MAX_JOYSTICKOEMVXDNAME 260
#endif

#define DITC_REGHWSETTINGS          0x00000001
#define DITC_CLSIDCONFIG            0x00000002
#define DITC_DISPLAYNAME            0x00000004
#define DITC_CALLOUT                0x00000008

typedef struct DIJOYTYPEINFO {
    DWORD dwSize;
    JOYREGHWSETTINGS hws;
    CLSID clsidConfig;
    WCHAR wszDisplayName[MAX_JOYSTRING];
    WCHAR wszCallout[MAX_JOYSTICKOEMVXDNAME];
} DIJOYTYPEINFO, *LPDIJOYTYPEINFO;
typedef const DIJOYTYPEINFO *LPCDIJOYTYPEINFO;

#define DIJC_GUIDINSTANCE           0x00000001
#define DIJC_REGHWCONFIGTYPE        0x00000002
#define DIJC_GAIN                   0x00000004
#define DIJC_CALLOUT                0x00000008

typedef struct DIJOYCONFIG {
    DWORD dwSize;
    GUID guidInstance;
    JOYREGHWCONFIG hwc;
    DWORD dwGain;
    WCHAR wszType[MAX_JOYSTRING];
    WCHAR wszCallout[MAX_JOYSTRING];
} DIJOYCONFIG, *LPDIJOYCONFIG;
typedef const DIJOYCONFIG *LPCDIJOYCONFIG;

#define DIJU_USERVALUES             0x00000001
#define DIJU_GLOBALDRIVER           0x00000002
#define DIJU_GAMEPORTEMULATOR       0x00000004

typedef struct DIJOYUSERVALUES {
    DWORD dwSize;
    JOYREGUSERVALUES ruv;
    WCHAR wszGlobalDriver[MAX_JOYSTRING];
    WCHAR wszGameportEmulator[MAX_JOYSTRING];
} DIJOYUSERVALUES, *LPDIJOYUSERVALUES;
typedef const DIJOYUSERVALUES *LPCDIJOYUSERVALUES;

DEFINE_GUID(GUID_KeyboardClass, 0x4D36E96B,0xE325,0x11CE,0xBF,0xC1,0x08,0x00,0x2B,0xE1,0x03,0x18);
DEFINE_GUID(GUID_MediaClass,    0x4D36E96C,0xE325,0x11CE,0xBF,0xC1,0x08,0x00,0x2B,0xE1,0x03,0x18);
DEFINE_GUID(GUID_MouseClass,    0x4D36E96F,0xE325,0x11CE,0xBF,0xC1,0x08,0x00,0x2B,0xE1,0x03,0x18);
DEFINE_GUID(GUID_HIDClass,      0x745A17A0,0x74D3,0x11D0,0xB6,0xFE,0x00,0xA0,0xC9,0x0F,0x57,0xDA);

#undef INTERFACE
#define INTERFACE IDirectInputJoyConfig

DECLARE_INTERFACE_(IDirectInputJoyConfig, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirectInputJoyConfig methods ***/
    STDMETHOD(Acquire)(THIS) PURE;
    STDMETHOD(Unacquire)(THIS) PURE;
    STDMETHOD(SetCooperativeLevel)(THIS_ HWND,DWORD) PURE;
    STDMETHOD(SendNotify)(THIS) PURE;
    STDMETHOD(EnumTypes)(THIS_ LPDIJOYTYPECALLBACK,LPVOID) PURE;
    STDMETHOD(GetTypeInfo)(THIS_ LPCWSTR,LPDIJOYTYPEINFO,DWORD) PURE;
    STDMETHOD(SetTypeInfo)(THIS_ LPCWSTR,LPCDIJOYTYPEINFO,DWORD) PURE;
    STDMETHOD(DeleteType)(THIS_ LPCWSTR) PURE;
    STDMETHOD(GetConfig)(THIS_ UINT,LPDIJOYCONFIG,DWORD) PURE;
    STDMETHOD(SetConfig)(THIS_ UINT,LPCDIJOYCONFIG,DWORD) PURE;
    STDMETHOD(DeleteConfig)(THIS_ UINT) PURE;
    STDMETHOD(GetUserValues)(THIS_ LPDIJOYUSERVALUES,DWORD) PURE;
    STDMETHOD(SetUserValues)(THIS_ LPCDIJOYUSERVALUES,DWORD) PURE;
    STDMETHOD(AddNewHardware)(THIS_ HWND,REFGUID) PURE;
    STDMETHOD(OpenTypeKey)(THIS_ LPCWSTR,DWORD,PHKEY) PURE;
    STDMETHOD(OpenConfigKey)(THIS_ UINT,DWORD,PHKEY) PURE;
};

typedef struct IDirectInputJoyConfig *LPDIRECTINPUTJOYCONFIG;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirectInputJoyConfig_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectInputJoyConfig_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectInputJoyConfig_Release(p) (p)->lpVtbl->Release(p)
#define IDirectInputJoyConfig_Acquire(p) (p)->lpVtbl->Acquire(p)
#define IDirectInputJoyConfig_Unacquire(p) (p)->lpVtbl->Unacquire(p)
#define IDirectInputJoyConfig_SetCooperativeLevel(p,a,b) (p)->lpVtbl->SetCooperativeLevel(p,a,b)
#define IDirectInputJoyConfig_SendNotify(p) (p)->lpVtbl->SendNotify(p)
#define IDirectInputJoyConfig_EnumTypes(p,a,b) (p)->lpVtbl->EnumTypes(p,a,b)
#define IDirectInputJoyConfig_GetTypeInfo(p,a,b,c) (p)->lpVtbl->GetTypeInfo(p,a,b,c)
#define IDirectInputJoyConfig_SetTypeInfo(p,a,b,c) (p)->lpVtbl->SetTypeInfo(p,a,b,c)
#define IDirectInputJoyConfig_DeleteType(p,a) (p)->lpVtbl->DeleteType(p,a)
#define IDirectInputJoyConfig_GetConfig(p,a,b,c) (p)->lpVtbl->GetConfig(p,a,b,c)
#define IDirectInputJoyConfig_SetConfig(p,a,b,c) (p)->lpVtbl->SetConfig(p,a,b,c)
#define IDirectInputJoyConfig_DeleteConfig(p,a) (p)->lpVtbl->DeleteConfig(p,a)
#define IDirectInputJoyConfig_GetUserValues(p,a,b) (p)->lpVtbl->GetUserValues(p,a,b)
#define IDirectInputJoyConfig_SetUserValues(p,a,b) (p)->lpVtbl->SetUserValues(p,a,b)
#define IDirectInputJoyConfig_AddNewHardware(p,a,b) (p)->lpVtbl->AddNewHardware(p,a,b)
#define IDirectInputJoyConfig_OpenTypeKey(p,a,b,c) (p)->lpVtbl->OpenTypeKey(p,a,b,c)
#define IDirectInputJoyConfig_OpenConfigKey(p,a,b,c) (p)->lpVtbl->OpenConfigKey(p,a,b,c)
#else
#define IDirectInputJoyConfig_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirectInputJoyConfig_AddRef(p) (p)->AddRef()
#define IDirectInputJoyConfig_Release(p) (p)->Release()
#define IDirectInputJoyConfig_Acquire(p) (p)->Acquire()
#define IDirectInputJoyConfig_Unacquire(p) (p)->Unacquire()
#define IDirectInputJoyConfig_SetCooperativeLevel(p,a,b) (p)->SetCooperativeLevel(a,b)
#define IDirectInputJoyConfig_SendNotify(p) (p)->SendNotify()
#define IDirectInputJoyConfig_EnumTypes(p,a,b) (p)->EnumTypes(a,b)
#define IDirectInputJoyConfig_GetTypeInfo(p,a,b,c) (p)->GetTypeInfo(a,b,c)
#define IDirectInputJoyConfig_SetTypeInfo(p,a,b,c) (p)->SetTypeInfo(a,b,c)
#define IDirectInputJoyConfig_DeleteType(p,a) (p)->DeleteType(a)
#define IDirectInputJoyConfig_GetConfig(p,a,b,c) (p)->GetConfig(a,b,c)
#define IDirectInputJoyConfig_SetConfig(p,a,b,c) (p)->SetConfig(a,b,c)
#define IDirectInputJoyConfig_DeleteConfig(p,a) (p)->DeleteConfig(a)
#define IDirectInputJoyConfig_GetUserValues(p,a,b) (p)->GetUserValues(a,b)
#define IDirectInputJoyConfig_SetUserValues(p,a,b) (p)->SetUserValues(a,b)
#define IDirectInputJoyConfig_AddNewHardware(p,a,b) (p)->AddNewHardware(a,b)
#define IDirectInputJoyConfig_OpenTypeKey(p,a,b,c) (p)->OpenTypeKey(a,b,c)
#define IDirectInputJoyConfig_OpenConfigKey(p,a,b,c) (p)->OpenConfigKey(a,b,c)
#endif

#endif /* DIJ_RINGZERO */

/****************************************************************************
 *
 *  Return Codes
 *
 ****************************************************************************/

#define DIERR_NOMOREITEMS               \
    MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_NO_MORE_ITEMS)

/*
 *  Device driver-specific codes.
 */
#define DIERR_DRIVERFIRST               0x80040300L
#define DIERR_DRIVERLAST                0x800403FFL

/*
 *  Device installer errors.
 */

/*
 *  Registry entry or DLL for class installer invalid
 *  or class installer not found.
 */
#define DIERR_INVALIDCLASSINSTALLER     0x80040400L

/*
 *  The user cancelled the install operation.
 */
#define DIERR_CANCELLED                 0x80040401L

/*
 *  The INF file for the selected device could not be
 *  found or is invalid or is damaged.
 */
#define DIERR_BADINF                    0x80040402L

#ifdef __cplusplus
};
#endif

#endif  /* __DINPUTD_INCLUDED__ */
