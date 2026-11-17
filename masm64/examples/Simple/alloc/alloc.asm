; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

    include \masm64\include64\masm64rt.inc

    .code

; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

entry_point proc

    LOCAL pmem :QWORD
    LOCAL nlen :QWORD
    LOCAL real :QWORD

    conout lf,"  realloc test",lf,lf

  ; ---------------------------------------

    conout "  -------------------------",lf
    conout "  Increase allocated memory",lf
    conout "  -------------------------",lf

    mov pmem, alloc(1024)

    mov nlen, msize(pmem)
    conout "  old length = ",str$(nlen),lf

    mov pmem, realloc(pmem,1024*1024)

    mov nlen, msize(pmem)
    conout "  new length = ",str$(nlen),lf,lf

    mfree pmem

  ; ---------------------------------------

    conout "  -------------------------",lf
    conout "  Truncate allocated memory",lf
    conout "  -------------------------",lf

    mov pmem, alloc(1024*1024)

    mov nlen, msize(pmem)
    conout "  old length = ",str$(nlen),lf

    mov pmem, realloc(pmem,1024)

    mov nlen, msize(pmem)
    conout "  new length = ",str$(nlen),lf,lf

    mfree pmem

  ; ---------------------------------------

    waitkey "  Press any key to continue ..."

    invoke ExitProcess,0

    ret

entry_point endp

; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

 ; realloc proc pmem:QWORD,nlen:QWORD
 ; 
 ;     LOCAL ream :QWORD       ; re allocated memory
 ;     LOCAL olen :QWORD       ; original length
 ;     LOCAL clen :QWORD       ; copy length
 ; 
 ;     mov [rbp+16], rcx
 ;     mov [rbp+24], rdx
 ; 
 ;     mov olen, rv(GlobalSize,pmem)
 ; 
 ;     mov rax, nlen
 ;     mov rcx, olen
 ;     cmp rax, rcx
 ;     jb lb1
 ;     mov clen, rcx       ; use original length as copy length
 ;     jmp nxt
 ;   lb1:
 ;     mov clen, rax       ; use new length as copy length
 ;   nxt:
 ;     mov ream, rv(GlobalAlloc,GMEM_FIXED or GMEM_ZEROINIT,nlen)
 ;     invoke mcopy,pmem,ream,clen
 ;     invoke GlobalFree,pmem
 ; 
 ;     mov rax, ream
 ;     ret
 ; 
 ; realloc endp

; ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

    end
