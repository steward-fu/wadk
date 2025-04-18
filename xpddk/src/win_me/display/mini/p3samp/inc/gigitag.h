/******************************Module*Header**********************************\
 *
 *                           *****************************
 *                           * Permedia 2: SAMPLE CODE   *
 *                           *****************************
 *
 * Module Name: gigitag.h
 *
 * Copyright (c) 1994-1998 3Dlabs Inc. Ltd. All rights reserved.
 * Copyright (c) 1995-2001 Microsoft Corporation.  All rights reserved.
 *
\*****************************************************************************/

#ifndef gigitag_h
#define gigitag_h

#define	__GigiTagStartXDom                	0
#define	__GigiTagdXDom                    	0x1
#define	__GigiTagStartXSub                	0x2
#define	__GigiTagdXSub                    	0x3
#define	__GigiTagStartY                   	0x4
#define	__GigiTagdY                       	0x5
#define	__GigiTagCount                    	0x6
#define	__GigiTagRender                   	0x7
#define	__GigiTagContinueNewLine          	0x8
#define	__GigiTagContinueNewDom           	0x9
#define	__GigiTagContinueNewSub           	0xa
#define	__GigiTagContinue                 	0xb
#define	__GigiTagBitMaskPattern           	0xd
#define	__GigiTagRasterizerMode           	0x14
#define	__GigiTagYLimits                  	0x15
#define	__GigiTagWaitForCompletion        	0x17
#define	__GigiTagXLimits                  	0x19
#define	__GigiTagRectangleOrigin          	0x1a
#define	__GigiTagRectangleSize            	0x1b
#define	__GigiTagPrepareToRender          	0x21
#define	__GigiTagActiveStepX              	0x22
#define	__GigiTagPassiveStepX             	0x23
#define	__GigiTagActiveStepYDomEdge       	0x24
#define	__GigiTagPassiveStepYDomEdge      	0x25
#define	__GigiTagFastBlockLimits          	0x26
#define	__GigiTagFastBlockFill            	0x27
#define	__GigiTagSubPixelCorrection       	0x28
#define	__GigiTagForceBackgroundColor     	0x29
#define	__GigiTagPackedDataLimits         	0x2a
#define	__GigiTagSpanMask                 	0x2d
#define	__GigiTagScissorMode              	0x30
#define	__GigiTagScissorMinXY             	0x31
#define	__GigiTagScissorMaxXY             	0x32
#define	__GigiTagScreenSize               	0x33
#define	__GigiTagAreaStippleMode          	0x34
#define	__GigiTagWindowOrigin             	0x39
#define	__GigiTagAreaStipplePattern0      	0x40
#define	__GigiTagAreaStipplePattern1      	0x41
#define	__GigiTagAreaStipplePattern2      	0x42
#define	__GigiTagAreaStipplePattern3      	0x43
#define	__GigiTagAreaStipplePattern4      	0x44
#define	__GigiTagAreaStipplePattern5      	0x45
#define	__GigiTagAreaStipplePattern6      	0x46
#define	__GigiTagAreaStipplePattern7      	0x47
#define	__GigiTagTextureAddressMode       	0x70
#define	__GigiTagSStart                   	0x71
#define	__GigiTagdSdx                     	0x72
#define	__GigiTagdSdyDom                  	0x73
#define	__GigiTagTStart                   	0x74
#define	__GigiTagdTdx                     	0x75
#define	__GigiTagdTdyDom                  	0x76
#define	__GigiTagQStart                   	0x77
#define	__GigiTagdQdx                     	0x78
#define	__GigiTagdQdyDom                  	0x79
#define	__GigiTagTextureAddress           	0x80
#define	__GigiTagLUTData                  	0x96
#define	__GigiTagTexelLUTIndex            	0x98
#define	__GigiTagTexelLUTData             	0x99
#define	__GigiTagTexelLUTAddress          	0x9a
#define	__GigiTagTexelLUTTransfer         	0x9b
#define	__GigiTagTextureBaseAddress       	0xb0
#define	__GigiTagTextureMapFormat         	0xb1
#define	__GigiTagTextureDataFormat        	0xb2
#define	__GigiTagTextureReadPad           	0xb5
#define	__GigiTagTexel0                   	0xc0
#define	__GigiTagTextureReadMode          	0xce
#define	__GigiTagTexelLUTMode             	0xcf
#define	__GigiTagTextureColorMode         	0xd0
#define	__GigiTagFogMode                  	0xd2
#define	__GigiTagFogColor                 	0xd3
#define	__GigiTagFStart                   	0xd4
#define	__GigiTagdFdx                     	0xd5
#define	__GigiTagdFdyDom                  	0xd6
#define	__GigiTagKsStart                  	0xd9
#define	__GigiTagdKsdx                    	0xda
#define	__GigiTagdKsdyDom                 	0xdb
#define	__GigiTagKdStart                  	0xdc
#define	__GigiTagdKddx                    	0xdd
#define	__GigiTagdKddyDom                 	0xde
#define	__GigiTagRStart                   	0xf0
#define	__GigiTagdRdx                     	0xf1
#define	__GigiTagdRdyDom                  	0xf2
#define	__GigiTagGStart                   	0xf3
#define	__GigiTagdGdx                     	0xf4
#define	__GigiTagdGdyDom                  	0xf5
#define	__GigiTagBStart                   	0xf6
#define	__GigiTagdBdx                     	0xf7
#define	__GigiTagdBdyDom                  	0xf8
#define	__GigiTagAStart                   	0xf9
#define	__GigiTagdAdx                     	0xfa
#define	__GigiTagdAdyDom                  	0xfb
#define	__GigiTagColorDDAMode             	0xfc
#define	__GigiTagConstantColor            	0xfd
#define	__GigiTagColor                    	0xfe
#define	__GigiTagAlphaBlendMode           	0x102
#define	__GigiTagDitherMode               	0x103
#define	__GigiTagFBSoftwareWriteMask      	0x104
#define	__GigiTagLogicalOpMode            	0x105
#define	__GigiTagFBWriteData              	0x106
#define	__GigiTagActiveColorStepX         	0x108
#define	__GigiTagActiveColorStepYDomEdge  	0x109
#define	__GigiTagActiveFBSourceDataStepX  	0x10a
#define	__GigiTagActiveFBSourceDataStepYDomEdge	0x10b
#define	__GigiTagActiveFBWriteDataStepX   	0x10c
#define	__GigiTagActiveFBWriteDataStepYDomEdge	0x10d
#define	__GigiTagActiveTexelStepX         	0x10e
#define	__GigiTagActiveTexelStepYDomEdge  	0x10f
#define	__GigiTagLBReadMode               	0x110
#define	__GigiTagLBReadFormat             	0x111
#define	__GigiTagLBSourceOffset           	0x112
#define	__GigiTagLBData                   	0x113
#define	__GigiTagLBSourceData             	0x114
#define	__GigiTagLBStencil                	0x115
#define	__GigiTagLBDepth                  	0x116
#define	__GigiTagLBWindowBase             	0x117
#define	__GigiTagLBWriteMode              	0x118
#define	__GigiTagLBWriteFormat            	0x119
#define	__GigiTagLBWriteBase              	0x11a
#define	__GigiTagLBWriteConfig            	0x11b
#define	__GigiTagLBReadPad                	0x11c
#define	__GigiTagTextureData              	0x11d
#define	__GigiTagTextureDownloadOffset    	0x11e
#define	__GigiTagWindow                   	0x130
#define	__GigiTagStencilMode              	0x131
#define	__GigiTagStencilData              	0x132
#define	__GigiTagStencil                  	0x133
#define	__GigiTagDepthMode                	0x134
#define	__GigiTagDepth                    	0x135
#define	__GigiTagZStartU                  	0x136
#define	__GigiTagZStartL                  	0x137
#define	__GigiTagdZdxU                    	0x138
#define	__GigiTagdZdxL                    	0x139
#define	__GigiTagdZdyDomU                 	0x13a
#define	__GigiTagdZdyDomL                 	0x13b
#define	__GigiTagLBWriteData              	0x13e
#define	__GigiTagFBReadMode               	0x150
#define	__GigiTagFBSourceOffset           	0x151
#define	__GigiTagFBPixelOffset            	0x152
#define	__GigiTagFBColor                  	0x153
#define	__GigiTagFBData                   	0x154
#define	__GigiTagFBSourceData             	0x155
#define	__GigiTagFBWindowBase             	0x156
#define	__GigiTagFBWriteMode              	0x157
#define	__GigiTagFBHardwareWriteMask      	0x158
#define	__GigiTagFBBlockColor             	0x159
#define	__GigiTagFBReadPixel              	0x15a
#define	__GigiTagFBWritePixel             	0x15b
#define	__GigiTagFBWriteBase              	0x15c
#define	__GigiTagFBWriteConfig            	0x15d
#define	__GigiTagFBReadPad                	0x15e
#define	__GigiTagFilterMode               	0x180
#define	__GigiTagStatisticMode            	0x181
#define	__GigiTagMinRegion                	0x182
#define	__GigiTagMaxRegion                	0x183
#define	__GigiTagResetPickResult          	0x184
#define	__GigiTagMinHitRegion             	0x185
#define	__GigiTagMaxHitRegion             	0x186
#define	__GigiTagPickResult               	0x187
#define	__GigiTagSync                     	0x188
#define	__GigiTagFBBlockColorU            	0x18d
#define	__GigiTagFBBlockColorL            	0x18e
#define	__GigiTagSuspendUntilFrameBlank   	0x18f
#define	__GigiTagFBSourceBase             	0x1b0
#define	__GigiTagFBSourceDelta            	0x1b1
#define	__GigiTagConfig                   	0x1b2
#define	__GigiTagActiveLBDataStepX        	0x1c0
#define	__GigiTagActiveLBDataStepYDomEdge 	0x1c1
#define	__GigiTagActiveLBWriteDataStepX   	0x1c2
#define	__GigiTagActiveLBWriteDataStepYDomEdge	0x1c3
#define	__GigiTagActiveTextureAddressStepX	0x1c4
#define	__GigiTagActiveTextureAddressStepYDomEdge	0x1c5
#define	__GigiTagFastBlockTextureAddress  	0x1c6
#define	__GigiTagTexelLUT0                	0x1d0
#define	__GigiTagTexelLUT1                	0x1d1
#define	__GigiTagTexelLUT2                	0x1d2
#define	__GigiTagTexelLUT3                	0x1d3
#define	__GigiTagTexelLUT4                	0x1d4
#define	__GigiTagTexelLUT5                	0x1d5
#define	__GigiTagTexelLUT6                	0x1d6
#define	__GigiTagTexelLUT7                	0x1d7
#define	__GigiTagTexelLUT8                	0x1d8
#define	__GigiTagTexelLUT9                	0x1d9
#define	__GigiTagTexelLUT10               	0x1da
#define	__GigiTagTexelLUT11               	0x1db
#define	__GigiTagTexelLUT12               	0x1dc
#define	__GigiTagTexelLUT13               	0x1dd
#define	__GigiTagTexelLUT14               	0x1de
#define	__GigiTagTexelLUT15               	0x1df
#define	__GigiTagYUVMode                  	0x1e0
#define	__GigiTagChromaUpperBound         	0x1e1
#define	__GigiTagChromaLowerBound         	0x1e2
#define	__GigiTagAlphaMapUpperBound       	0x1e3
#define	__GigiTagAlphaMapLowerBound       	0x1e4
#define	__GigiTagTextureID                	0x1ee
#define	__GigiTagTexelLUTID               	0x1ef
#define	__GigiTagV0FixedS                 	0x200
#define	__GigiTagV0FixedT                 	0x201
#define	__GigiTagV0FixedQ                 	0x202
#define	__GigiTagV0FixedKs                	0x203
#define	__GigiTagV0FixedKd                	0x204
#define	__GigiTagV0FixedR                 	0x205
#define	__GigiTagV0FixedG                 	0x206
#define	__GigiTagV0FixedB                 	0x207
#define	__GigiTagV0FixedA                 	0x208
#define	__GigiTagV0FixedF                 	0x209
#define	__GigiTagV0FixedX                 	0x20a
#define	__GigiTagV0FixedY                 	0x20b
#define	__GigiTagV0FixedZ                 	0x20c
#define	__GigiTagV0FixedW                 	0x20d
#define	__GigiTagV0FixedPacked            	0x20e
#define	__GigiTagV0FixedU2                	0x20f
#define	__GigiTagV1FixedS                 	0x210
#define	__GigiTagV1FixedT                 	0x211
#define	__GigiTagV1FixedQ                 	0x212
#define	__GigiTagV1FixedKs                	0x213
#define	__GigiTagV1FixedKd                	0x214
#define	__GigiTagV1FixedR                 	0x215
#define	__GigiTagV1FixedG                 	0x216
#define	__GigiTagV1FixedB                 	0x217
#define	__GigiTagV1FixedA                 	0x218
#define	__GigiTagV1FixedF                 	0x219
#define	__GigiTagV1FixedX                 	0x21a
#define	__GigiTagV1FixedY                 	0x21b
#define	__GigiTagV1FixedZ                 	0x21c
#define	__GigiTagV1FixedW                 	0x21d
#define	__GigiTagV1FixedPacked            	0x21e
#define	__GigiTagV1FixedU2                	0x21f
#define	__GigiTagV2FixedS                 	0x220
#define	__GigiTagV2FixedT                 	0x221
#define	__GigiTagV2FixedQ                 	0x222
#define	__GigiTagV2FixedKs                	0x223
#define	__GigiTagV2FixedKd                	0x224
#define	__GigiTagV2FixedR                 	0x225
#define	__GigiTagV2FixedG                 	0x226
#define	__GigiTagV2FixedB                 	0x227
#define	__GigiTagV2FixedA                 	0x228
#define	__GigiTagV2FixedF                 	0x229
#define	__GigiTagV2FixedX                 	0x22a
#define	__GigiTagV2FixedY                 	0x22b
#define	__GigiTagV2FixedZ                 	0x22c
#define	__GigiTagV2FixedW                 	0x22d
#define	__GigiTagV2FixedPacked            	0x22e
#define	__GigiTagV2FixedU2                	0x22f
#define	__GigiTagV0FloatS                 	0x230
#define	__GigiTagV0FloatT                 	0x231
#define	__GigiTagV0FloatQ                 	0x232
#define	__GigiTagV0FloatKs                	0x233
#define	__GigiTagV0FloatKd                	0x234
#define	__GigiTagV0FloatR                 	0x235
#define	__GigiTagV0FloatG                 	0x236
#define	__GigiTagV0FloatB                 	0x237
#define	__GigiTagV0FloatA                 	0x238
#define	__GigiTagV0FloatF                 	0x239
#define	__GigiTagV0FloatX                 	0x23a
#define	__GigiTagV0FloatY                 	0x23b
#define	__GigiTagV0FloatZ                 	0x23c
#define	__GigiTagV0FloatW                 	0x23d
#define	__GigiTagV0FloatPacked            	0x23e
#define	__GigiTagV0FloatU2                	0x23f
#define	__GigiTagV1FloatS                 	0x240
#define	__GigiTagV1FloatT                 	0x241
#define	__GigiTagV1FloatQ                 	0x242
#define	__GigiTagV1FloatKs                	0x243
#define	__GigiTagV1FloatKd                	0x244
#define	__GigiTagV1FloatR                 	0x245
#define	__GigiTagV1FloatG                 	0x246
#define	__GigiTagV1FloatB                 	0x247
#define	__GigiTagV1FloatA                 	0x248
#define	__GigiTagV1FloatF                 	0x249
#define	__GigiTagV1FloatX                 	0x24a
#define	__GigiTagV1FloatY                 	0x24b
#define	__GigiTagV1FloatZ                 	0x24c
#define	__GigiTagV1FloatW                 	0x24d
#define	__GigiTagV1FloatPacked            	0x24e
#define	__GigiTagV1FloatU2                	0x24f
#define	__GigiTagV2FloatS                 	0x250
#define	__GigiTagV2FloatT                 	0x251
#define	__GigiTagV2FloatQ                 	0x252
#define	__GigiTagV2FloatKs                	0x253
#define	__GigiTagV2FloatKd                	0x254
#define	__GigiTagV2FloatR                 	0x255
#define	__GigiTagV2FloatG                 	0x256
#define	__GigiTagV2FloatB                 	0x257
#define	__GigiTagV2FloatA                 	0x258
#define	__GigiTagV2FloatF                 	0x259
#define	__GigiTagV2FloatX                 	0x25a
#define	__GigiTagV2FloatY                 	0x25b
#define	__GigiTagV2FloatZ                 	0x25c
#define	__GigiTagV2FloatW                 	0x25d
#define	__GigiTagV2FloatPacked            	0x25e
#define	__GigiTagV2FloatU2                	0x25f
#define	__GigiTagDeltaMode                	0x260
#define	__GigiTagDrawTriangle             	0x261
#define	__GigiTagRepeatTriangle           	0x262
#define	__GigiTagDrawLine01               	0x263
#define	__GigiTagDrawLine10               	0x264
#define	__GigiTagRepeatLine               	0x265
#define	__GigiTagDeltaReserved0           	0x266
#define	__GigiTagDeltaReserved1           	0x267
#define	__GigiTagDeltaReserved2           	0x268
#define	__GigiTagDeltaReserved3           	0x269
#define	__GigiTagDeltaReserved4           	0x26a
#define	__GigiTagDeltaReserved5           	0x26b
#define	__GigiTagDeltaReserved6           	0x26c
#define	__GigiTagDeltaReserved7           	0x26d
#define	__GigiTagDeltaReserved8           	0x26e
#define	__GigiTagBroadcastMask            	0x26f

typedef long __GigiTag ;

#endif /* gigitag_h */

