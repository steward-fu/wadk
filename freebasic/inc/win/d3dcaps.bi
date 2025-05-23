'' FreeBASIC binding for mingw-w64-v4.0.4
''
'' based on the C header files:
''   Copyright (C) 2000 Peter Hunnisett
''
''   This library is free software; you can redistribute it and/or
''   modify it under the terms of the GNU Lesser General Public
''   License as published by the Free Software Foundation; either
''   version 2.1 of the License, or (at your option) any later version.
''
''   This library is distributed in the hope that it will be useful,
''   but WITHOUT ANY WARRANTY; without even the implied warranty of
''   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
''   Lesser General Public License for more details.
''
''   You should have received a copy of the GNU Lesser General Public
''   License along with this library; if not, write to the Free Software
''   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
''
'' translated to FreeBASIC by:
''   FreeBASIC development team

#pragma once

#include once "ddraw.bi"

extern "Windows"

#define __WINE_D3DCAPS_H

#ifdef __FB_64BIT__
	type _D3DTRANSFORMCAPS
		dwSize as DWORD
		dwCaps as DWORD
	end type
#else
	type _D3DTRANSFORMCAPS field = 4
		dwSize as DWORD
		dwCaps as DWORD
	end type
#endif

type D3DTRANSFORMCAPS as _D3DTRANSFORMCAPS
type LPD3DTRANSFORMCAPS as _D3DTRANSFORMCAPS ptr
const D3DTRANSFORMCAPS_CLIP = &h00000001

#ifdef __FB_64BIT__
	type _D3DLIGHTINGCAPS
		dwSize as DWORD
		dwCaps as DWORD
		dwLightingModel as DWORD
		dwNumLights as DWORD
	end type
#else
	type _D3DLIGHTINGCAPS field = 4
		dwSize as DWORD
		dwCaps as DWORD
		dwLightingModel as DWORD
		dwNumLights as DWORD
	end type
#endif

type D3DLIGHTINGCAPS as _D3DLIGHTINGCAPS
type LPD3DLIGHTINGCAPS as _D3DLIGHTINGCAPS ptr
const D3DLIGHTINGMODEL_RGB = &h00000001
const D3DLIGHTINGMODEL_MONO = &h00000002
const D3DLIGHTCAPS_POINT = &h00000001
const D3DLIGHTCAPS_SPOT = &h00000002
const D3DLIGHTCAPS_DIRECTIONAL = &h00000004
const D3DLIGHTCAPS_PARALLELPOINT = &h00000008
const D3DLIGHTCAPS_GLSPOT = &h00000010

#ifdef __FB_64BIT__
	type _D3dPrimCaps
		dwSize as DWORD
		dwMiscCaps as DWORD
		dwRasterCaps as DWORD
		dwZCmpCaps as DWORD
		dwSrcBlendCaps as DWORD
		dwDestBlendCaps as DWORD
		dwAlphaCmpCaps as DWORD
		dwShadeCaps as DWORD
		dwTextureCaps as DWORD
		dwTextureFilterCaps as DWORD
		dwTextureBlendCaps as DWORD
		dwTextureAddressCaps as DWORD
		dwStippleWidth as DWORD
		dwStippleHeight as DWORD
	end type
#else
	type _D3dPrimCaps field = 4
		dwSize as DWORD
		dwMiscCaps as DWORD
		dwRasterCaps as DWORD
		dwZCmpCaps as DWORD
		dwSrcBlendCaps as DWORD
		dwDestBlendCaps as DWORD
		dwAlphaCmpCaps as DWORD
		dwShadeCaps as DWORD
		dwTextureCaps as DWORD
		dwTextureFilterCaps as DWORD
		dwTextureBlendCaps as DWORD
		dwTextureAddressCaps as DWORD
		dwStippleWidth as DWORD
		dwStippleHeight as DWORD
	end type
#endif

type D3DPRIMCAPS as _D3dPrimCaps
type LPD3DPRIMCAPS as _D3dPrimCaps ptr
const D3DPMISCCAPS_MASKPLANES = &h00000001
const D3DPMISCCAPS_MASKZ = &h00000002
const D3DPMISCCAPS_LINEPATTERNREP = &h00000004
const D3DPMISCCAPS_CONFORMANT = &h00000008
const D3DPMISCCAPS_CULLNONE = &h00000010
const D3DPMISCCAPS_CULLCW = &h00000020
const D3DPMISCCAPS_CULLCCW = &h00000040
const D3DPRASTERCAPS_DITHER = &h00000001
const D3DPRASTERCAPS_ROP2 = &h00000002
const D3DPRASTERCAPS_XOR = &h00000004
const D3DPRASTERCAPS_PAT = &h00000008
const D3DPRASTERCAPS_ZTEST = &h00000010
const D3DPRASTERCAPS_SUBPIXEL = &h00000020
const D3DPRASTERCAPS_SUBPIXELX = &h00000040
const D3DPRASTERCAPS_FOGVERTEX = &h00000080
const D3DPRASTERCAPS_FOGTABLE = &h00000100
const D3DPRASTERCAPS_STIPPLE = &h00000200
const D3DPRASTERCAPS_ANTIALIASSORTDEPENDENT = &h00000400
const D3DPRASTERCAPS_ANTIALIASSORTINDEPENDENT = &h00000800
const D3DPRASTERCAPS_ANTIALIASEDGES = &h00001000
const D3DPRASTERCAPS_MIPMAPLODBIAS = &h00002000
const D3DPRASTERCAPS_ZBIAS = &h00004000
const D3DPRASTERCAPS_ZBUFFERLESSHSR = &h00008000
const D3DPRASTERCAPS_FOGRANGE = &h00010000
const D3DPRASTERCAPS_ANISOTROPY = &h00020000
const D3DPRASTERCAPS_WBUFFER = &h00040000
const D3DPRASTERCAPS_TRANSLUCENTSORTINDEPENDENT = &h00080000
const D3DPRASTERCAPS_WFOG = &h00100000
const D3DPRASTERCAPS_ZFOG = &h00200000
const D3DPCMPCAPS_NEVER = &h00000001
const D3DPCMPCAPS_LESS = &h00000002
const D3DPCMPCAPS_EQUAL = &h00000004
const D3DPCMPCAPS_LESSEQUAL = &h00000008
const D3DPCMPCAPS_GREATER = &h00000010
const D3DPCMPCAPS_NOTEQUAL = &h00000020
const D3DPCMPCAPS_GREATEREQUAL = &h00000040
const D3DPCMPCAPS_ALWAYS = &h00000080
const D3DPBLENDCAPS_ZERO = &h00000001
const D3DPBLENDCAPS_ONE = &h00000002
const D3DPBLENDCAPS_SRCCOLOR = &h00000004
const D3DPBLENDCAPS_INVSRCCOLOR = &h00000008
const D3DPBLENDCAPS_SRCALPHA = &h00000010
const D3DPBLENDCAPS_INVSRCALPHA = &h00000020
const D3DPBLENDCAPS_DESTALPHA = &h00000040
const D3DPBLENDCAPS_INVDESTALPHA = &h00000080
const D3DPBLENDCAPS_DESTCOLOR = &h00000100
const D3DPBLENDCAPS_INVDESTCOLOR = &h00000200
const D3DPBLENDCAPS_SRCALPHASAT = &h00000400
const D3DPBLENDCAPS_BOTHSRCALPHA = &h00000800
const D3DPBLENDCAPS_BOTHINVSRCALPHA = &h00001000
const D3DPSHADECAPS_COLORFLATMONO = &h00000001
const D3DPSHADECAPS_COLORFLATRGB = &h00000002
const D3DPSHADECAPS_COLORGOURAUDMONO = &h00000004
const D3DPSHADECAPS_COLORGOURAUDRGB = &h00000008
const D3DPSHADECAPS_COLORPHONGMONO = &h00000010
const D3DPSHADECAPS_COLORPHONGRGB = &h00000020
const D3DPSHADECAPS_SPECULARFLATMONO = &h00000040
const D3DPSHADECAPS_SPECULARFLATRGB = &h00000080
const D3DPSHADECAPS_SPECULARGOURAUDMONO = &h00000100
const D3DPSHADECAPS_SPECULARGOURAUDRGB = &h00000200
const D3DPSHADECAPS_SPECULARPHONGMONO = &h00000400
const D3DPSHADECAPS_SPECULARPHONGRGB = &h00000800
const D3DPSHADECAPS_ALPHAFLATBLEND = &h00001000
const D3DPSHADECAPS_ALPHAFLATSTIPPLED = &h00002000
const D3DPSHADECAPS_ALPHAGOURAUDBLEND = &h00004000
const D3DPSHADECAPS_ALPHAGOURAUDSTIPPLED = &h00008000
const D3DPSHADECAPS_ALPHAPHONGBLEND = &h00010000
const D3DPSHADECAPS_ALPHAPHONGSTIPPLED = &h00020000
const D3DPSHADECAPS_FOGFLAT = &h00040000
const D3DPSHADECAPS_FOGGOURAUD = &h00080000
const D3DPSHADECAPS_FOGPHONG = &h00100000
const D3DPTEXTURECAPS_PERSPECTIVE = &h00000001
const D3DPTEXTURECAPS_POW2 = &h00000002
const D3DPTEXTURECAPS_ALPHA = &h00000004
const D3DPTEXTURECAPS_TRANSPARENCY = &h00000008
const D3DPTEXTURECAPS_BORDER = &h00000010
const D3DPTEXTURECAPS_SQUAREONLY = &h00000020
const D3DPTEXTURECAPS_TEXREPEATNOTSCALEDBYSIZE = &h00000040
const D3DPTEXTURECAPS_ALPHAPALETTE = &h00000080
const D3DPTEXTURECAPS_NONPOW2CONDITIONAL = &h00000100
const D3DPTEXTURECAPS_PROJECTED = &h00000400
const D3DPTEXTURECAPS_CUBEMAP = &h00000800
const D3DPTEXTURECAPS_COLORKEYBLEND = &h00001000
const D3DPTFILTERCAPS_NEAREST = &h00000001
const D3DPTFILTERCAPS_LINEAR = &h00000002
const D3DPTFILTERCAPS_MIPNEAREST = &h00000004
const D3DPTFILTERCAPS_MIPLINEAR = &h00000008
const D3DPTFILTERCAPS_LINEARMIPNEAREST = &h00000010
const D3DPTFILTERCAPS_LINEARMIPLINEAR = &h00000020
const D3DPTFILTERCAPS_MINFPOINT = &h00000100
const D3DPTFILTERCAPS_MINFLINEAR = &h00000200
const D3DPTFILTERCAPS_MINFANISOTROPIC = &h00000400
const D3DPTFILTERCAPS_MIPFPOINT = &h00010000
const D3DPTFILTERCAPS_MIPFLINEAR = &h00020000
const D3DPTFILTERCAPS_MAGFPOINT = &h01000000
const D3DPTFILTERCAPS_MAGFLINEAR = &h02000000
const D3DPTFILTERCAPS_MAGFANISOTROPIC = &h04000000
const D3DPTFILTERCAPS_MAGFAFLATCUBIC = &h08000000
const D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC = &h10000000
const D3DPTBLENDCAPS_DECAL = &h00000001
const D3DPTBLENDCAPS_MODULATE = &h00000002
const D3DPTBLENDCAPS_DECALALPHA = &h00000004
const D3DPTBLENDCAPS_MODULATEALPHA = &h00000008
const D3DPTBLENDCAPS_DECALMASK = &h00000010
const D3DPTBLENDCAPS_MODULATEMASK = &h00000020
const D3DPTBLENDCAPS_COPY = &h00000040
const D3DPTBLENDCAPS_ADD = &h00000080
const D3DPTADDRESSCAPS_WRAP = &h00000001
const D3DPTADDRESSCAPS_MIRROR = &h00000002
const D3DPTADDRESSCAPS_CLAMP = &h00000004
const D3DPTADDRESSCAPS_BORDER = &h00000008
const D3DPTADDRESSCAPS_INDEPENDENTUV = &h00000010

#ifdef __FB_64BIT__
	type _D3DDeviceDesc
		dwSize as DWORD
		dwFlags as DWORD
		dcmColorModel as D3DCOLORMODEL
		dwDevCaps as DWORD
		dtcTransformCaps as D3DTRANSFORMCAPS
		bClipping as WINBOOL
		dlcLightingCaps as D3DLIGHTINGCAPS
		dpcLineCaps as D3DPRIMCAPS
		dpcTriCaps as D3DPRIMCAPS
		dwDeviceRenderBitDepth as DWORD
		dwDeviceZBufferBitDepth as DWORD
		dwMaxBufferSize as DWORD
		dwMaxVertexCount as DWORD
		dwMinTextureWidth as DWORD
		dwMinTextureHeight as DWORD
		dwMaxTextureWidth as DWORD
		dwMaxTextureHeight as DWORD
		dwMinStippleWidth as DWORD
		dwMaxStippleWidth as DWORD
		dwMinStippleHeight as DWORD
		dwMaxStippleHeight as DWORD
		dwMaxTextureRepeat as DWORD
		dwMaxTextureAspectRatio as DWORD
		dwMaxAnisotropy as DWORD
		dvGuardBandLeft as D3DVALUE
		dvGuardBandTop as D3DVALUE
		dvGuardBandRight as D3DVALUE
		dvGuardBandBottom as D3DVALUE
		dvExtentsAdjust as D3DVALUE
		dwStencilCaps as DWORD
		dwFVFCaps as DWORD
		dwTextureOpCaps as DWORD
		wMaxTextureBlendStages as WORD
		wMaxSimultaneousTextures as WORD
	end type
#else
	type _D3DDeviceDesc field = 4
		dwSize as DWORD
		dwFlags as DWORD
		dcmColorModel as D3DCOLORMODEL
		dwDevCaps as DWORD
		dtcTransformCaps as D3DTRANSFORMCAPS
		bClipping as WINBOOL
		dlcLightingCaps as D3DLIGHTINGCAPS
		dpcLineCaps as D3DPRIMCAPS
		dpcTriCaps as D3DPRIMCAPS
		dwDeviceRenderBitDepth as DWORD
		dwDeviceZBufferBitDepth as DWORD
		dwMaxBufferSize as DWORD
		dwMaxVertexCount as DWORD
		dwMinTextureWidth as DWORD
		dwMinTextureHeight as DWORD
		dwMaxTextureWidth as DWORD
		dwMaxTextureHeight as DWORD
		dwMinStippleWidth as DWORD
		dwMaxStippleWidth as DWORD
		dwMinStippleHeight as DWORD
		dwMaxStippleHeight as DWORD
		dwMaxTextureRepeat as DWORD
		dwMaxTextureAspectRatio as DWORD
		dwMaxAnisotropy as DWORD
		dvGuardBandLeft as D3DVALUE
		dvGuardBandTop as D3DVALUE
		dvGuardBandRight as D3DVALUE
		dvGuardBandBottom as D3DVALUE
		dvExtentsAdjust as D3DVALUE
		dwStencilCaps as DWORD
		dwFVFCaps as DWORD
		dwTextureOpCaps as DWORD
		wMaxTextureBlendStages as WORD
		wMaxSimultaneousTextures as WORD
	end type
#endif

type D3DDEVICEDESC as _D3DDeviceDesc
type LPD3DDEVICEDESC as _D3DDeviceDesc ptr
#define D3DDEVICEDESCSIZE sizeof(D3DDEVICEDESC)

#ifdef __FB_64BIT__
	type _D3DDeviceDesc7
		dwDevCaps as DWORD
		dpcLineCaps as D3DPRIMCAPS
		dpcTriCaps as D3DPRIMCAPS
		dwDeviceRenderBitDepth as DWORD
		dwDeviceZBufferBitDepth as DWORD
		dwMinTextureWidth as DWORD
		dwMinTextureHeight as DWORD
		dwMaxTextureWidth as DWORD
		dwMaxTextureHeight as DWORD
		dwMaxTextureRepeat as DWORD
		dwMaxTextureAspectRatio as DWORD
		dwMaxAnisotropy as DWORD
		dvGuardBandLeft as D3DVALUE
		dvGuardBandTop as D3DVALUE
		dvGuardBandRight as D3DVALUE
		dvGuardBandBottom as D3DVALUE
		dvExtentsAdjust as D3DVALUE
		dwStencilCaps as DWORD
		dwFVFCaps as DWORD
		dwTextureOpCaps as DWORD
		wMaxTextureBlendStages as WORD
		wMaxSimultaneousTextures as WORD
		dwMaxActiveLights as DWORD
		dvMaxVertexW as D3DVALUE
		deviceGUID as GUID
		wMaxUserClipPlanes as WORD
		wMaxVertexBlendMatrices as WORD
		dwVertexProcessingCaps as DWORD
		dwReserved1 as DWORD
		dwReserved2 as DWORD
		dwReserved3 as DWORD
		dwReserved4 as DWORD
	end type
#else
	type _D3DDeviceDesc7 field = 4
		dwDevCaps as DWORD
		dpcLineCaps as D3DPRIMCAPS
		dpcTriCaps as D3DPRIMCAPS
		dwDeviceRenderBitDepth as DWORD
		dwDeviceZBufferBitDepth as DWORD
		dwMinTextureWidth as DWORD
		dwMinTextureHeight as DWORD
		dwMaxTextureWidth as DWORD
		dwMaxTextureHeight as DWORD
		dwMaxTextureRepeat as DWORD
		dwMaxTextureAspectRatio as DWORD
		dwMaxAnisotropy as DWORD
		dvGuardBandLeft as D3DVALUE
		dvGuardBandTop as D3DVALUE
		dvGuardBandRight as D3DVALUE
		dvGuardBandBottom as D3DVALUE
		dvExtentsAdjust as D3DVALUE
		dwStencilCaps as DWORD
		dwFVFCaps as DWORD
		dwTextureOpCaps as DWORD
		wMaxTextureBlendStages as WORD
		wMaxSimultaneousTextures as WORD
		dwMaxActiveLights as DWORD
		dvMaxVertexW as D3DVALUE
		deviceGUID as GUID
		wMaxUserClipPlanes as WORD
		wMaxVertexBlendMatrices as WORD
		dwVertexProcessingCaps as DWORD
		dwReserved1 as DWORD
		dwReserved2 as DWORD
		dwReserved3 as DWORD
		dwReserved4 as DWORD
	end type
#endif

type D3DDEVICEDESC7 as _D3DDeviceDesc7
type LPD3DDEVICEDESC7 as _D3DDeviceDesc7 ptr
#define D3DDEVICEDESC7SIZE sizeof(D3DDEVICEDESC7)
const D3DDD_COLORMODEL = &h00000001
const D3DDD_DEVCAPS = &h00000002
const D3DDD_TRANSFORMCAPS = &h00000004
const D3DDD_LIGHTINGCAPS = &h00000008
const D3DDD_BCLIPPING = &h00000010
const D3DDD_LINECAPS = &h00000020
const D3DDD_TRICAPS = &h00000040
const D3DDD_DEVICERENDERBITDEPTH = &h00000080
const D3DDD_DEVICEZBUFFERBITDEPTH = &h00000100
const D3DDD_MAXBUFFERSIZE = &h00000200
const D3DDD_MAXVERTEXCOUNT = &h00000400
const D3DDEVCAPS_FLOATTLVERTEX = &h00000001
const D3DDEVCAPS_SORTINCREASINGZ = &h00000002
const D3DDEVCAPS_SORTDECREASINGZ = &h00000004
const D3DDEVCAPS_SORTEXACT = &h00000008
const D3DDEVCAPS_EXECUTESYSTEMMEMORY = &h00000010
const D3DDEVCAPS_EXECUTEVIDEOMEMORY = &h00000020
const D3DDEVCAPS_TLVERTEXSYSTEMMEMORY = &h00000040
const D3DDEVCAPS_TLVERTEXVIDEOMEMORY = &h00000080
const D3DDEVCAPS_TEXTURESYSTEMMEMORY = &h00000100
const D3DDEVCAPS_TEXTUREVIDEOMEMORY = &h00000200
const D3DDEVCAPS_DRAWPRIMTLVERTEX = &h00000400
const D3DDEVCAPS_CANRENDERAFTERFLIP = &h00000800
const D3DDEVCAPS_TEXTURENONLOCALVIDMEM = &h00001000
const D3DDEVCAPS_DRAWPRIMITIVES2 = &h00002000
const D3DDEVCAPS_SEPARATETEXTUREMEMORIES = &h00004000
const D3DDEVCAPS_DRAWPRIMITIVES2EX = &h00008000
const D3DDEVCAPS_HWTRANSFORMANDLIGHT = &h00010000
const D3DDEVCAPS_CANBLTSYSTONONLOCAL = &h00020000
const D3DDEVCAPS_HWRASTERIZATION = &h00080000
const D3DSTENCILCAPS_KEEP = &h00000001
const D3DSTENCILCAPS_ZERO = &h00000002
const D3DSTENCILCAPS_REPLACE = &h00000004
const D3DSTENCILCAPS_INCRSAT = &h00000008
const D3DSTENCILCAPS_DECRSAT = &h00000010
const D3DSTENCILCAPS_INVERT = &h00000020
const D3DSTENCILCAPS_INCR = &h00000040
const D3DSTENCILCAPS_DECR = &h00000080
const D3DTEXOPCAPS_DISABLE = &h00000001
const D3DTEXOPCAPS_SELECTARG1 = &h00000002
const D3DTEXOPCAPS_SELECTARG2 = &h00000004
const D3DTEXOPCAPS_MODULATE = &h00000008
const D3DTEXOPCAPS_MODULATE2X = &h00000010
const D3DTEXOPCAPS_MODULATE4X = &h00000020
const D3DTEXOPCAPS_ADD = &h00000040
const D3DTEXOPCAPS_ADDSIGNED = &h00000080
const D3DTEXOPCAPS_ADDSIGNED2X = &h00000100
const D3DTEXOPCAPS_SUBTRACT = &h00000200
const D3DTEXOPCAPS_ADDSMOOTH = &h00000400
const D3DTEXOPCAPS_BLENDDIFFUSEALPHA = &h00000800
const D3DTEXOPCAPS_BLENDTEXTUREALPHA = &h00001000
const D3DTEXOPCAPS_BLENDFACTORALPHA = &h00002000
const D3DTEXOPCAPS_BLENDTEXTUREALPHAPM = &h00004000
const D3DTEXOPCAPS_BLENDCURRENTALPHA = &h00008000
const D3DTEXOPCAPS_PREMODULATE = &h00010000
const D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR = &h00020000
const D3DTEXOPCAPS_MODULATECOLOR_ADDALPHA = &h00040000
const D3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR = &h00080000
const D3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA = &h00100000
const D3DTEXOPCAPS_BUMPENVMAP = &h00200000
const D3DTEXOPCAPS_BUMPENVMAPLUMINANCE = &h00400000
const D3DTEXOPCAPS_DOTPRODUCT3 = &h00800000
const D3DFVFCAPS_TEXCOORDCOUNTMASK = &h0000FFFF
const D3DFVFCAPS_DONOTSTRIPELEMENTS = &h00080000
const D3DVTXPCAPS_TEXGEN = &h00000001
const D3DVTXPCAPS_MATERIALSOURCE7 = &h00000002
const D3DVTXPCAPS_VERTEXFOG = &h00000004
const D3DVTXPCAPS_DIRECTIONALLIGHTS = &h00000008
const D3DVTXPCAPS_POSITIONALLIGHTS = &h00000010
const D3DVTXPCAPS_LOCALVIEWER = &h00000020
type LPD3DENUMDEVICESCALLBACK as function(byval guid as GUID ptr, byval description as zstring ptr, byval name as zstring ptr, byval hal_desc as D3DDEVICEDESC ptr, byval hel_desc as D3DDEVICEDESC ptr, byval ctx as any ptr) as HRESULT
type LPD3DENUMDEVICESCALLBACK7 as function(byval description as zstring ptr, byval name as zstring ptr, byval desc as D3DDEVICEDESC7 ptr, byval ctx as any ptr) as HRESULT
const D3DFDS_COLORMODEL = &h00000001
const D3DFDS_GUID = &h00000002
const D3DFDS_HARDWARE = &h00000004
const D3DFDS_TRIANGLES = &h00000008
const D3DFDS_LINES = &h00000010
const D3DFDS_MISCCAPS = &h00000020
const D3DFDS_RASTERCAPS = &h00000040
const D3DFDS_ZCMPCAPS = &h00000080
const D3DFDS_ALPHACMPCAPS = &h00000100
const D3DFDS_SRCBLENDCAPS = &h00000200
const D3DFDS_DSTBLENDCAPS = &h00000400
const D3DFDS_SHADECAPS = &h00000800
const D3DFDS_TEXTURECAPS = &h00001000
const D3DFDS_TEXTUREFILTERCAPS = &h00002000
const D3DFDS_TEXTUREBLENDCAPS = &h00004000
const D3DFDS_TEXTUREADDRESSCAPS = &h00008000

#ifdef __FB_64BIT__
	type _D3DFINDDEVICESEARCH
		dwSize as DWORD
		dwFlags as DWORD
		bHardware as WINBOOL
		dcmColorModel as D3DCOLORMODEL
		guid as GUID
		dwCaps as DWORD
		dpcPrimCaps as D3DPRIMCAPS
	end type
#else
	type _D3DFINDDEVICESEARCH field = 4
		dwSize as DWORD
		dwFlags as DWORD
		bHardware as WINBOOL
		dcmColorModel as D3DCOLORMODEL
		guid as GUID
		dwCaps as DWORD
		dpcPrimCaps as D3DPRIMCAPS
	end type
#endif

type D3DFINDDEVICESEARCH as _D3DFINDDEVICESEARCH
type LPD3DFINDDEVICESEARCH as _D3DFINDDEVICESEARCH ptr

#ifdef __FB_64BIT__
	type _D3DFINDDEVICERESULT
		dwSize as DWORD
		guid as GUID
		ddHwDesc as D3DDEVICEDESC
		ddSwDesc as D3DDEVICEDESC
	end type
#else
	type _D3DFINDDEVICERESULT field = 4
		dwSize as DWORD
		guid as GUID
		ddHwDesc as D3DDEVICEDESC
		ddSwDesc as D3DDEVICEDESC
	end type
#endif

type D3DFINDDEVICERESULT as _D3DFINDDEVICERESULT
type LPD3DFINDDEVICERESULT as _D3DFINDDEVICERESULT ptr

#ifdef __FB_64BIT__
	type _D3DExecuteBufferDesc
		dwSize as DWORD
		dwFlags as DWORD
		dwCaps as DWORD
		dwBufferSize as DWORD
		lpData as any ptr
	end type
#else
	type _D3DExecuteBufferDesc field = 4
		dwSize as DWORD
		dwFlags as DWORD
		dwCaps as DWORD
		dwBufferSize as DWORD
		lpData as any ptr
	end type
#endif

type D3DEXECUTEBUFFERDESC as _D3DExecuteBufferDesc
type LPD3DEXECUTEBUFFERDESC as _D3DExecuteBufferDesc ptr
const D3DDEB_BUFSIZE = &h00000001
const D3DDEB_CAPS = &h00000002
const D3DDEB_LPDATA = &h00000004
const D3DDEBCAPS_SYSTEMMEMORY = &h00000001
const D3DDEBCAPS_VIDEOMEMORY = &h00000002
const D3DDEBCAPS_MEM = D3DDEBCAPS_SYSTEMMEMORY or D3DDEBCAPS_VIDEOMEMORY

#ifdef __FB_64BIT__
	type _D3DDEVINFO_TEXTUREMANAGER
		bThrashing as WINBOOL
		dwApproxBytesDownloaded as DWORD
		dwNumEvicts as DWORD
		dwNumVidCreates as DWORD
		dwNumTexturesUsed as DWORD
		dwNumUsedTexInVid as DWORD
		dwWorkingSet as DWORD
		dwWorkingSetBytes as DWORD
		dwTotalManaged as DWORD
		dwTotalBytes as DWORD
		dwLastPri as DWORD
	end type
#else
	type _D3DDEVINFO_TEXTUREMANAGER field = 4
		bThrashing as WINBOOL
		dwApproxBytesDownloaded as DWORD
		dwNumEvicts as DWORD
		dwNumVidCreates as DWORD
		dwNumTexturesUsed as DWORD
		dwNumUsedTexInVid as DWORD
		dwWorkingSet as DWORD
		dwWorkingSetBytes as DWORD
		dwTotalManaged as DWORD
		dwTotalBytes as DWORD
		dwLastPri as DWORD
	end type
#endif

type D3DDEVINFO_TEXTUREMANAGER as _D3DDEVINFO_TEXTUREMANAGER
type LPD3DDEVINFO_TEXTUREMANAGER as _D3DDEVINFO_TEXTUREMANAGER ptr

#ifdef __FB_64BIT__
	type _D3DDEVINFO_TEXTURING
		dwNumLoads as DWORD
		dwApproxBytesLoaded as DWORD
		dwNumPreLoads as DWORD
		dwNumSet as DWORD
		dwNumCreates as DWORD
		dwNumDestroys as DWORD
		dwNumSetPriorities as DWORD
		dwNumSetLODs as DWORD
		dwNumLocks as DWORD
		dwNumGetDCs as DWORD
	end type
#else
	type _D3DDEVINFO_TEXTURING field = 4
		dwNumLoads as DWORD
		dwApproxBytesLoaded as DWORD
		dwNumPreLoads as DWORD
		dwNumSet as DWORD
		dwNumCreates as DWORD
		dwNumDestroys as DWORD
		dwNumSetPriorities as DWORD
		dwNumSetLODs as DWORD
		dwNumLocks as DWORD
		dwNumGetDCs as DWORD
	end type
#endif

type D3DDEVINFO_TEXTURING as _D3DDEVINFO_TEXTURING
type LPD3DDEVINFO_TEXTURING as _D3DDEVINFO_TEXTURING ptr

end extern
