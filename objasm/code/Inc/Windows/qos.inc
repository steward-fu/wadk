;Include file created by h2incX, Version B.01.01, 29/10/2018 18:21
;(C) 2018-today by Biterider, 2005-2009 by Japheth
;Source file: '\ObjAsm\Projects\h2IncX\header\qos.h', last modified: 19/04/2018 09:44
;Creation parameters: 

ifndef __QOS_H_
  __QOS_H_ equ <>
  include winapifamily.inc
  if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
    SERVICETYPE typedef ULONG
    SERVICETYPE_NOTRAFFIC equ 00000000h
    SERVICETYPE_BESTEFFORT equ 00000001h
    SERVICETYPE_CONTROLLEDLOAD equ 00000002h
    SERVICETYPE_GUARANTEED equ 00000003h
    SERVICETYPE_NETWORK_UNAVAILABLE equ 00000004h
    SERVICETYPE_GENERAL_INFORMATION equ 00000005h
    SERVICETYPE_NOCHANGE equ 00000006h
    SERVICETYPE_NONCONFORMING equ 00000009h
    SERVICETYPE_NETWORK_CONTROL equ 0000000Ah
    SERVICETYPE_QUALITATIVE equ 0000000Dh
    SERVICE_BESTEFFORT equ 80010000h
    SERVICE_CONTROLLEDLOAD equ 80020000h
    SERVICE_GUARANTEED equ 80040000h
    SERVICE_QUALITATIVE equ 80200000h
    SERVICE_NO_TRAFFIC_CONTROL equ 81000000h
    SERVICE_NO_QOS_SIGNALING equ 40000000h
    FLOWSPEC struct
      TokenRate ULONG ?
      TokenBucketSize ULONG ?
      PeakBandwidth ULONG ?
      Latency ULONG ?
      DelayVariation ULONG ?
      ServiceType SERVICETYPE ?
      MaxSduSize ULONG ?
      MinimumPolicedSize ULONG ?
    FLOWSPEC ends

    _flowspec typedef FLOWSPEC
    PFLOWSPEC typedef ptr FLOWSPEC
    LPFLOWSPEC typedef ptr FLOWSPEC
    
    QOS_NOT_SPECIFIED equ 0FFFFFFFFh
    POSITIVE_INFINITY_RATE equ 0FFFFFFFEh
    QOS_OBJECT_HDR struct
      ObjectType ULONG ?
      ObjectLength ULONG ?
    QOS_OBJECT_HDR ends

    LPQOS_OBJECT_HDR typedef ptr QOS_OBJECT_HDR
    
    QOS_GENERAL_ID_BASE equ 2000
    QOS_OBJECT_END_OF_LIST equ (00000001h + QOS_GENERAL_ID_BASE)
    QOS_OBJECT_SD_MODE equ (00000002h + QOS_GENERAL_ID_BASE)
    QOS_OBJECT_SHAPING_RATE equ (00000003h + QOS_GENERAL_ID_BASE)
    QOS_OBJECT_DESTADDR equ (00000004h + QOS_GENERAL_ID_BASE)
    QOS_SD_MODE struct
      ObjectHdr QOS_OBJECT_HDR <>
      ShapeDiscardMode ULONG ?
    QOS_SD_MODE ends

    _QOS_SD_MODE typedef QOS_SD_MODE
    LPQOS_SD_MODE typedef ptr QOS_SD_MODE
    
    TC_NONCONF_BORROW equ 0
    TC_NONCONF_SHAPE equ 1
    TC_NONCONF_DISCARD equ 2
    TC_NONCONF_BORROW_PLUS equ 3
    QOS_SHAPING_RATE struct
      ObjectHdr QOS_OBJECT_HDR <>
      ShapingRate ULONG ?
    QOS_SHAPING_RATE ends

    _QOS_SHAPING_RATE typedef QOS_SHAPING_RATE
    LPQOS_SHAPING_RATE typedef ptr QOS_SHAPING_RATE
    
  endif
endif

