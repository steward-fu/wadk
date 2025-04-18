; ==================================================================================================
; Title:      webp.inc.inc
; Author:     G. Friedrich
; Version:    1.0.0
; Purpose:    WebP (1.2.4) master include file.
; Notes:      Version 1.0.0, October 2022
;               - First release.
; Links:      https://storage.googleapis.com/downloads.webmproject.org/releases/webp/index.html
;             https://developers.google.com/speed/webp/docs/cwebp
; Notes:      Translation of header files was done using h2incX.exe and some manual adjustments.
; ==================================================================================================


if @WordSize eq 4                       ;32 bit
  WEBP_CALL_CONV textequ <C>
else
  WEBP_CALL_CONV textequ <fastcall>     ;64 bit
endif

WEBP_INC_PATH textequ <.>

%include &WEBP_INC_PATH&\encode.inc
%include &WEBP_INC_PATH&\decode.inc
%include &WEBP_INC_PATH&\mux.inc
%include &WEBP_INC_PATH&\demux.inc
 