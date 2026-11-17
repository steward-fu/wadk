
FrameTimerStart PROTO
FrameTimerEnd   PROTO
TrackRealTime   PROTO

.data

	startFrameTime dq 0
	endFrameTime   dq 0
	currentFPS     dq 60
	fpsCount       dq 0
	fpsStartTime   dq 0
	frameFreq      dq 0
	frameTime      REAL4 0.0
	fCurrentFPS    REAL4 60.0
	frameCount     dq 0
	real_time      REAL4 0.0		; total elapsed milliseconds.
				
timer_begin MACRO loopcount:REQ, priority
	
	LOCAL label
	
    IFNDEF __timer__stuff__defined__
      __timer__stuff__defined__ equ <1>
    .data
    	ALIGN 8             ;; Optimal alignment for QWORD
        __timer__pc__frequency__    dq 0
        __timer__pc__count1__       dq 0
        __timer__pc__count2__       dq 0
        __timer__loop__counter__    dq 0
        __timer__dw_count__         dq 0
        __timer__overhead__         dq 0
      .code
    ENDIF

	invoke GetCurrentProcess
	invoke SetPriorityClass,rax,priority

	; Time an empty loop @ count.
	invoke QueryPerformanceCounter,ADDR __timer__pc__count1__
	mov __timer__loop__counter__,loopcount
align 16
@@:
	sub __timer__loop__counter__,1
	jnz short @B
	invoke QueryPerformanceCounter,ADDR __timer__pc__count2__
	
	mov rax,__timer__pc__count2__
	sub rax,__timer__pc__count1__
	mov __timer__overhead__,rax
	
	xor rax,rax
	mov __timer__pc__count1__,rax
	mov __timer__pc__count2__,rax

	invoke QueryPerformanceCounter,ADDR __timer__pc__count1__
	mov __timer__loop__counter__,loopcount
align 16
label:
	 __timer__loop__label__ equ <label>
ENDM

timer_end MACRO
    
    sub   __timer__loop__counter__, 1
    jnz   __timer__loop__label__
        
    invoke QueryPerformanceFrequency, ADDR __timer__pc__frequency__
    invoke QueryPerformanceCounter, ADDR __timer__pc__count2__
    
    mov rax,__timer__pc__count2__
    sub rax,__timer__pc__count1__
    mov __timer__pc__count1__,rax
                        
    invoke GetCurrentProcess
    invoke SetPriorityClass, rax, NORMAL_PRIORITY_CLASS
    emms
    
    finit
    fild qword ptr __timer__pc__count1__	
 	fild qword ptr __timer__pc__frequency__
	fdiv
    mov   __timer__dw_count__, 1000
    fild  __timer__dw_count__
    fmul
    fistp __timer__dw_count__
	mov   rax, __timer__dw_count__
                
ENDM
 
.code

;=====================================================================================================================================
; Frame Timer Start.
;=====================================================================================================================================
FrameTimerStart proc FRAME
	invoke QueryPerformanceCounter,ADDR startFrameTime
	ret
FrameTimerStart endp

;=====================================================================================================================================
; Frame Timer End.
; -> Returns: EAX = current avg. fps.
;=====================================================================================================================================
FrameTimerEnd proc FRAME uses rbx
	invoke QueryPerformanceCounter,ADDR endFrameTime
	mov rax,endFrameTime
	sub rax,startFrameTime
	mov endFrameTime,rax
	fild qword ptr endFrameTime
	fild qword ptr timerFreq
	fdiv
	fld FP4(1000.0)
	fmul
	fstp dword ptr frameTime
	vmovss xmm0,frameTime
	vmovss xmm1,FP4(1000.0)
	vdivss xmm1,xmm1,xmm0
	xor rbx,rbx
	vcvttss2si ebx,xmm1
	mov currentFPS,rbx
	vmovss fCurrentFPS,xmm1	
	inc frameCount
	ret
	
FrameTimerEnd endp

TrackRealTime PROC FRAME

	vmovss xmm0,real_time
	vaddss xmm0,xmm0,frameTime
	vmovss real_time,xmm0
	
	ret
TrackRealTime ENDP