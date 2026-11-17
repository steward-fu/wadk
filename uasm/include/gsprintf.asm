; size_t gsprintf(char *buf, const char *formatstr, ...);
; Returns a count of the characters it has written.
;

_gsprintf:
    ;create stack frame to access variables
    push    ebp
    mov     ebp, esp
    
    ;save registers we're going to trash; by convention
    ;we don't need to save EAX, ECX, EDX or ES. The rest
    ;of the registers need to be saved.
    push    esi
    push    edi
    push    ebx
    pushfd          ;save flags register
    
    ;make ES = DS
    push    ds
    pop     es
    
    ; DS:[ESI] will point to format string, ES:[EDI]
    ; will point to our character buffer.
    mov     edi, [ebp + 8]
    mov     esi, [ebp + 12]
    ;set the count of characters we've printed to 0.
    xor     eax, eax
    ;keep track of what argument we're at
    xor     ecx, ecx
    
    ;start processing characters!
    
    PROCESS_CHAR:
        ;load the next character from our format
        ;string into DL
        mov     dl, [esi]

        ;check to see if we hit a format specifier
        cmp     dl, '%'
        je      PROCESS_ARG

        ;no format specifier, it's something else.
        ;just write it to the buffer.
        mov     [edi], dl
        
        ;increment the pointers, go on to next char
        inc     edi
        inc     esi
        inc     eax

        ;check to see if we hit a null
        or      dl, dl
        jz      EXIT_FUNC

        ;not a null.
        jmp     PROCESS_CHAR
        
        PROCESS_ARG:
            ;skip over '%' and see what comes next.
            ;should be 'd'.
            inc     esi
            mov     dl, [esi]
            cmp     dl, 'd'
            je      PRINT_INT
            ;invalid format specifier, print out '%'
            ;followed by whatever character comes
            ;next.
            mov     BYTE PTR [edi], '%'
            inc     edi
            mov     [edi], dl
            ;next character
            inc     esi
            inc     edi
            add     eax, 2
            jmp     PROCESS_CHAR
            
        PRINT_INT:
            ;if we get here then it's an integer. let's
            ;cheat and call itoa() to make it a string.
            ;itoa takes three args: the int to convert,
            ;the buffer, and the radix, which'll always
            ;be 10. note that atoi returns a pointer,
            ;so we have to save EAX to avoid trashing
            ;our own return value.
            push    eax
            
            ;push arguments backwards...
            mov     ebx, 10
            push    ebx         ;radix 10
            push    edi         ;output buffer
            
            ;calculate address of next integer arg
            lea     ebx, [ebp + ecx*4 + 16]
            push    DWORD PTR [ebx]     ;integer to convert
            call    _itoa

            ;restore our character count
            pop     eax
            
            ;increment character count by whatever
            ;itoa printed...
            COUNT_ITOA_CHARS:
                ;edi still points to the beginning of the
                ;string that itoa printed out. we can just
                ;keep going until we hit a null, which is
                ;the end of the itoa string.
                cmp     BYTE PTR [edi], 0
                jz      END_PRINT_INT
                
                ;not a null, increment character count
                ;and destination pointer
                inc     eax
                inc     edi
                jmp     COUNT_ITOA_CHARS

            END_PRINT_INT:
            ;increment argument counter
            inc     ecx
            
            ;go on to next character in format string
            inc     esi
            jmp     PROCESS_CHAR
    
    EXIT_FUNC:
    ;restore the registers we trashed
    popfd
    pop     ebx
    pop     edi
    pop     esi
    
    ;clean up stack and return
    pop     ebp
    ret