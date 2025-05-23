;Include file created by h2incX, Version C.01.00, 14/10/2022 22:00
;(C) 2018-today by Biterider, 2005-2009 by Japheth
;Source file: 'demux.h', last modified: 26/12/2019 20:24


ifndef WEBP_WEBP_DEMUX_INC_
  WEBP_WEBP_DEMUX_INC_ equ <>

  %include &WEBP_INC_PATH&\decode.inc
  %include &WEBP_INC_PATH&\mux_types.inc
  WEBP_DEMUX_ABI_VERSION equ 0107h
  WebPGetDemuxVersion proto WEBP_CALL_CONV
  WebPDemuxState typedef SDWORD
  WEBP_DEMUX_PARSE_ERROR equ -1
  WEBP_DEMUX_PARSING_HEADER equ 0
  WEBP_DEMUX_PARSED_HEADER equ 1
  WEBP_DEMUX_DONE equ 2

  WebPDemuxInternal proto WEBP_CALL_CONV :ptr WebPData, :SDWORD, :ptr WebPDemuxState, :SDWORD
  WebPDemux proto WEBP_CALL_CONV :ptr WebPData
  WebPDemuxPartial proto WEBP_CALL_CONV :ptr WebPData, :ptr WebPDemuxState
  WebPDemuxDelete proto WEBP_CALL_CONV :ptr WebPDemuxer
  WebPFormatFeature typedef SDWORD
  WEBP_FF_FORMAT_FLAGS equ 0
  WEBP_FF_CANVAS_WIDTH equ 1
  WEBP_FF_CANVAS_HEIGHT equ 2
  WEBP_FF_LOOP_COUNT equ 3
  WEBP_FF_BACKGROUND_COLOR equ 4
  WEBP_FF_FRAME_COUNT equ 5

  WebPDemuxGetI proto WEBP_CALL_CONV :ptr WebPDemuxer, :WebPFormatFeature
  WebPIterator struct
    frame_num SDWORD ?
    num_frames SDWORD ?
    x_offset SDWORD ?
    width_ SDWORD ?
    duration SDWORD ?
    dispose_method WebPMuxAnimDispose ?
    complete SDWORD ?
    fragment WebPData <>
    has_alpha SDWORD ?
    blend_method WebPMuxAnimBlend ?
    pad uint32_t 2 dup (?)
    private_ POINTER ?
  WebPIterator ends
  WebPDemuxGetFrame proto WEBP_CALL_CONV :ptr WebPDemuxer, :SDWORD, :ptr WebPIterator
  WebPDemuxNextFrame proto WEBP_CALL_CONV :ptr WebPIterator
  WebPDemuxPrevFrame proto WEBP_CALL_CONV :ptr WebPIterator
  WebPDemuxReleaseIterator proto WEBP_CALL_CONV :ptr WebPIterator
  WebPChunkIterator struct
    chunk_num SDWORD ?
    num_chunks SDWORD ?
    chunk WebPData <>
    pad uint32_t 6 dup (?)
    private_ POINTER ?
  WebPChunkIterator ends
  WebPDemuxGetChunk proto WEBP_CALL_CONV :ptr WebPDemuxer, :ptr SBYTE, :SDWORD, :ptr WebPChunkIterator
  WebPDemuxNextChunk proto WEBP_CALL_CONV :ptr WebPChunkIterator
  WebPDemuxPrevChunk proto WEBP_CALL_CONV :ptr WebPChunkIterator
  WebPDemuxReleaseChunkIterator proto WEBP_CALL_CONV :ptr WebPChunkIterator
  ;WebPAnimDecoder typedef WebPAnimDecoder

  WebPAnimDecoderOptions struct
    color_mode WEBP_CSP_MODE ?
    use_threads SDWORD ?
    padding uint32_t 7 dup (?)
  WebPAnimDecoderOptions ends
  WebPAnimDecoderOptionsInitInternal proto WEBP_CALL_CONV :ptr WebPAnimDecoderOptions, :SDWORD
  WebPAnimDecoderOptionsInit proto WEBP_CALL_CONV :ptr WebPAnimDecoderOptions
  WebPAnimDecoderNewInternal proto WEBP_CALL_CONV :ptr WebPData, :ptr WebPAnimDecoderOptions, :SDWORD
  WebPAnimDecoderNew proto WEBP_CALL_CONV :ptr WebPData, :ptr WebPAnimDecoderOptions
  WebPAnimInfo struct
    canvas_width uint32_t ?
    canvas_height uint32_t ?
    loop_count uint32_t ?
    bgcolor uint32_t ?
    frame_count uint32_t ?
    pad uint32_t 4 dup (?)
  WebPAnimInfo ends
  WebPAnimDecoderGetInfo proto WEBP_CALL_CONV :ptr WebPAnimDecoder, :ptr WebPAnimInfo
  WebPAnimDecoderGetNext proto WEBP_CALL_CONV :ptr WebPAnimDecoder, :ptr ptr uint8_t, :ptr SDWORD
  WebPAnimDecoderHasMoreFrames proto WEBP_CALL_CONV :ptr WebPAnimDecoder
  WebPAnimDecoderReset proto WEBP_CALL_CONV :ptr WebPAnimDecoder
  WebPAnimDecoderGetDemuxer proto WEBP_CALL_CONV :ptr WebPAnimDecoder
  WebPAnimDecoderDelete proto WEBP_CALL_CONV :ptr WebPAnimDecoder
endif
 