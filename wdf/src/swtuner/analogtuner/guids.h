//==========================================================================;
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (c) Microsoft Corporation.  All Rights Reserved.
//
//==========================================================================;

/***************************************************************************
    File    : guids.h
    Abstract: Contains guids for pin names, mediums and categories
****************************************************************************/

DEFINE_GUIDSTRUCT("{0F6F4F80-3C26-4de2-A9CF-22FB4F7F5F48}", PINNAME_ANALOGVIDEOOUT);
#define PINNAME_ANALOGVIDEOOUT DEFINE_GUIDNAMED(PINNAME_ANALOGVIDEOOUT)

DEFINE_GUIDSTRUCT("{10DF9484-88D1-4a80-8D34-633ACE36FA6D}", PINNAME_ANALOGAUDIOOUT);
#define PINNAME_ANALOGAUDIOOUT DEFINE_GUIDNAMED(PINNAME_ANALOGAUDIOOUT)

DEFINE_GUIDSTRUCT("{606AB02F-7318-47ce-943D-BB40B6EF9D52}", PINNAME_TVAUDIOIN);
#define PINNAME_TVAUDIOIN DEFINE_GUIDNAMED(PINNAME_TVAUDIOIN)

DEFINE_GUIDSTRUCT("{E70B2AAE-EF21-41ca-9364-A05BE93D59E9}", PINNAME_TVAUDIOOUT);
#define PINNAME_TVAUDIOOUT DEFINE_GUIDNAMED(PINNAME_TVAUDIOOUT)

DEFINE_GUIDSTRUCT("{65BAC61C-FACB-4d5f-A0B8-4B6FEEB59873}", PINNAME_VIDEOTUNERIN);
#define PINNAME_VIDEOTUNERIN DEFINE_GUIDNAMED(PINNAME_VIDEOTUNERIN)

DEFINE_GUIDSTRUCT("{667F65C5-699D-4eca-9BC4-334AB5F9C34E}", PINNAME_AUDIOTUNERIN);
#define PINNAME_AUDIOTUNERIN DEFINE_GUIDNAMED(PINNAME_AUDIOTUNERIN)

DEFINE_GUIDSTRUCT("{1DFE880F-7C65-4715-B3A9-39BCED70AAB7}", PINNAME_VIDEODECOUT);
#define PINNAME_VIDEODECOUT DEFINE_GUIDNAMED(PINNAME_VIDEODECOUT)

DEFINE_GUIDSTRUCT("{5AF09A2D-2A4C-4074-BB0C-6D62908F8617}", PINNAME_AUDIODECOUT);
#define PINNAME_AUDIODECOUT DEFINE_GUIDNAMED(PINNAME_AUDIODECOUT)

DEFINE_GUIDSTRUCT("{CD09343D-64B7-4ff5-9781-0324B1F2ED63}", PINNAME_ANALOGVIDEOIN);
#define PINNAME_ANALOGVIDEOIN DEFINE_GUIDNAMED(PINNAME_ANALOGVIDEOIN)

DEFINE_GUIDSTRUCT("{236519F5-3784-4040-86B7-D67FFB1D9B18}", PINNAME_ANALOGAUDIOIN);
#define PINNAME_ANALOGAUDIOIN DEFINE_GUIDNAMED(PINNAME_ANALOGAUDIOIN)

DEFINE_GUIDSTRUCT("{C7C496C1-B78B-4168-80B2-C1CB718C3C5E}", PINNAME_YUVOUT);
#define PINNAME_YUVOUT DEFINE_GUIDNAMED(PINNAME_YUVOUT)

DEFINE_GUIDSTRUCT("{AC3299B6-A273-487d-92D2-4A20F3C48200}", PINNAME_AUDIOPCMOUT);
#define PINNAME_AUDIOPCMOUT DEFINE_GUIDNAMED(PINNAME_AUDIOPCMOUT)

DEFINE_GUIDSTRUCT("{2A8A6A98-CD7D-4065-8A43-0EFE41C44F39}", PINNAME_YUVIN);
#define PINNAME_YUVIN DEFINE_GUIDNAMED(PINNAME_YUVIN)

DEFINE_GUIDSTRUCT("{3D328BDC-EB2C-43dd-941A-4CB5A43819A1}", PINNAME_AUDIOPCMIN);
#define PINNAME_AUDIOPCMIN DEFINE_GUIDNAMED(PINNAME_AUDIOPCMIN)

DEFINE_GUIDSTRUCT("{1987C6F9-88DE-49df-B5F3-5336A4ED56C4}", PINNAME_VBI);
#define PINNAME_VBI DEFINE_GUIDNAMED(PINNAME_VBI)

//  Medium GUIDs for the Sample filter pins.
#define GUID_BdaSWRcv                      0xf102c41f, 0x7fa1, 0x4842, 0xa0, 0xc8, 0xdc, 0x41, 0x17, 0x6e, 0xc8, 0x44
#define GUID_AnlgTunerPinMediumAudioOut    0xc8d6c6ec, 0xa9ea, 0x40e3, 0x94, 0x8d, 0xc3, 0xea, 0xd6, 0x63, 0x44, 0xd1
#define GUID_AnlgTunerPinMediumVideoOut    0x2e561fff, 0xadb8, 0x4386, 0x95, 0xbc, 0xd, 0x9f, 0x93, 0x3d, 0x94, 0x68
#define GUID_TVAudioPinMediumAudioOut      0xcd4e6a5f, 0xfa2d, 0x47b2, 0xa3, 0x84, 0xf6, 0xd7, 0x3f, 0x2a, 0x3f, 0x4f
#define GUID_XBarPinMediumAudioOut         0xa6f8d830, 0xfe77, 0x4881, 0xaa, 0xea, 0x9f, 0xf1, 0x6b, 0xea, 0x97, 0x5d
#define GUID_XBarPinMediumVideoOut         0x33eba766, 0xfbb7, 0x40bc, 0x83, 0xc8, 0x1f, 0xcb, 0x5e, 0x15, 0x63, 0xf
#define GUID_XBarPinMediumAudioAUX         0x86574ee3, 0x948b, 0x4bc7, 0x86, 0x74, 0xb0, 0x54, 0x92, 0xa6, 0x37, 0x5b
#define GUID_XBarPinMediumVideoAUX         0x7e962fa2, 0x8723, 0x4338, 0x94, 0x35, 0x31, 0xf1, 0xc8, 0x15, 0xee, 0x94
#define GUID_AnlgCapturePinMediumAudioOut  0x3bfcc4c, 0xc637, 0x46ab, 0xae, 0xf3, 0xa0, 0x46, 0x87, 0x6, 0x7c, 0xb5
#define GUID_AnlgCapturePinMediumVideoOut  0xbaf27d7b, 0x602c, 0x4f08, 0x93, 0x74, 0x2e, 0xa7, 0x72, 0xd6, 0x86, 0x58
#define GUID_XBarPinMediumVBIOut           0xe981a09d, 0xc016, 0x4e1c, 0xbf, 0xf9, 0x78, 0x30, 0xba, 0x76, 0xf7, 0x34
#define GUID_AnlgCapturePinMediumVBIOut    0x4747b320, 0x62ce, 0x11cf, 0xa5, 0xd6, 0x28, 0xdb, 0x04, 0xc1, 0x00, 0x00


// These filter guids must match the interface guids in the INFs

DEFINE_GUIDSTRUCT("{8D118811-289C-4138-8EB9-DC7E2CE44000}", KSNAME_BdaSWAnlgTunerFilter);
#define KSNAME_BdaSWAnlgTunerFilter DEFINE_GUIDNAMED(KSNAME_BdaSWAnlgTunerFilter)

DEFINE_GUIDSTRUCT("{54ACCE3E-6484-470e-9EFE-22860812D40D}", KSNAME_BdaTVAudioFilter);
#define KSNAME_BdaTVAudioFilter DEFINE_GUIDNAMED(KSNAME_BdaTVAudioFilter)

DEFINE_GUIDSTRUCT("{0D741D45-01E3-4581-B009-C7843E1F6835}", KSNAME_BdaXBarFilter);
#define KSNAME_BdaXBarFilter DEFINE_GUIDNAMED(KSNAME_BdaXBarFilter)

DEFINE_GUIDSTRUCT("{03CB1A33-BE78-45eb-B276-AA8F201B00F2}", KSNAME_BdaAnlgCaptureFilter);
#define KSNAME_BdaAnlgCaptureFilter DEFINE_GUIDNAMED(KSNAME_BdaAnlgCaptureFilter)

DEFINE_GUIDSTRUCT("{26E74D4F-D5E0-425d-847D-C478AA8DC4AA}", KSNAME_BdaEncoderFilter);
#define KSNAME_BdaEncoderFilter DEFINE_GUIDNAMED(KSNAME_BdaEncoderFilter)

/*
// Special category for the encoder filter
#define STATIC_KSCATEGORY_ENCODER \
   0x19689BF6L, 0xC384, 0x48FD, 0xAD, 0x51, 0x90, 0xE5, 0x8C, 0x79, 0xF7, 0x0B  
DEFINE_GUIDSTRUCT("19689BF6-C384-48FD-AD51-90E58C79F70B", KSCATEGORY_ENCODER);
#define KSCATEGORY_ENCODER DEFINE_GUIDNAMED(KSCATEGORY_ENCODER)

#define STATIC_KSCATEGORY_MULTIPLEXER \
   0x7A5DE1D3L, 0x01A1, 0x452C, 0xB4, 0x81, 0x4F, 0xA2, 0xB9, 0x62, 0x71, 0xE8
DEFINE_GUIDSTRUCT("7A5DE1D3-01A1-452C-B481-4FA2B96271E8", KSCATEGORY_MULTIPLEXER);
#define KSCATEGORY_MULTIPLEXER DEFINE_GUIDNAMED(KSCATEGORY_MULTIPLEXER)
*/


