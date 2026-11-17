; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    include \masm64\include64\masm64rt.inc

    .code

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

entry_point proc

    LOCAL hMem  :QWORD
    LOCAL lMem  :QWORD
    LOCAL pMem  :QWORD
    LOCAL aLen  :QWORD
    LOCAL wLen  :QWORD
    LOCAL hIcon :QWORD
    LOCAL hInstance :QWORD

    mov hInstance, rv(GetModuleHandle,0)        ; unneeded, added for crap AV scanners

    mov hMem, rvcall(load_file,"icon.ico")      ; load the file
    mov lMem, rcx                               ; get its length
    mov rax, lMem

    lea rax, [rax*4]                            ; mul length by 4
    mov aLen, rax

    mov pMem, alloc(aLen)                       ; allocate the output buffer
    mov wLen, rvcall(bin2hex,hMem,lMem,pMem)    ; convert the source to hex
    rcall save_file,"bin2hex.txt",pMem,wLen     ; write the file to disk

    mfree pMem                                  ; free the allocated memory
    mfree hMem                                  ; free the file memory

    exec "\masm64\teditor.exe bin2hex.txt"

    invoke ExitProcess,0

    ret

entry_point endp

; いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい

    end
