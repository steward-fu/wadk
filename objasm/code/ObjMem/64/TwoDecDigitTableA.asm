; ==================================================================================================
; Title:      TwoDecDigitTableA.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup64.inc
% include &ObjMemPath&ObjMemWin.cop

externdef TwoDecDigitTableA:DCHRA

.const

align ALIGN_DATA
TwoDecDigitTableA \
  DCHRA "00","10","20","30","40","50","60","70","80","90"
  DCHRA "01","11","21","31","41","51","61","71","81","91"
  DCHRA "02","12","22","32","42","52","62","72","82","92"
  DCHRA "03","13","23","33","43","53","63","73","83","93"
  DCHRA "04","14","24","34","44","54","64","74","84","94"
  DCHRA "05","15","25","35","45","55","65","75","85","95"
  DCHRA "06","16","26","36","46","56","66","76","86","96"
  DCHRA "07","17","27","37","47","57","67","77","87","97"
  DCHRA "08","18","28","38","48","58","68","78","88","98"
  DCHRA "09","19","29","39","49","59","69","79","89","99"

end
