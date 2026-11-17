DoEditDeleteTrailingWhitespacesW PROC

; 2141 : {

$LN24:
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 232				; 000000e8H

; 2142 :   AECHARRANGE crRange;
; 2143 :   AECHARINDEX ciInitialCaret=ciCurCaret;

	lea	rax, QWORD PTR ciInitialCaret$[rsp]
	lea	rcx, OFFSET FLAT:ciCurCaret
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 2144 :   wchar_t *wszRange;
; 2145 :   INT_PTR nRangeLen;
; 2146 :   INT_PTR nNewRangeLen;
; 2147 :   wchar_t *wpRead;
; 2148 :   wchar_t *wpWrite;
; 2149 :   wchar_t *wpMaxRead;
; 2150 :   int nFirstLine=0;

	mov	DWORD PTR nFirstLine$[rsp], 0

; 2151 :   BOOL bSelection;
; 2152 :   BOOL bCaretAtStart=FALSE;

	mov	DWORD PTR bCaretAtStart$[rsp], 0

; 2153 :   BOOL bResult=FALSE;

	mov	DWORD PTR bResult$[rsp], 0

; 2154 : 
; 2155 :   if (IsReadOnly(hWnd))

	mov	rcx, QWORD PTR hWnd$[rsp]
	call	IsReadOnly
	test	eax, eax
	je	SHORT $LN19@DoEditDele

; 2156 :     return FALSE;

	xor	eax, eax
	jmp	$LN20@DoEditDele
$LN19@DoEditDele:

; 2157 :   if (!AEC_IndexCompare(&crCurSel.ciMin, &ciCurCaret))

	lea	rdx, OFFSET FLAT:ciCurCaret
	lea	rcx, OFFSET FLAT:crCurSel
	call	AEC_IndexCompare
	test	eax, eax
	jne	SHORT $LN18@DoEditDele

; 2158 :     bCaretAtStart=TRUE;

	mov	DWORD PTR bCaretAtStart$[rsp], 1
$LN18@DoEditDele:

; 2159 : 
; 2160 :   //Save scroll
; 2161 :   nFirstLine=SaveLineScroll(hWnd);

	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SaveLineScroll
	mov	DWORD PTR nFirstLine$[rsp], eax

; 2162 : 
; 2163 :   if (!AEC_IndexCompare(&crCurSel.ciMin, &crCurSel.ciMax))

	lea	rdx, OFFSET FLAT:crCurSel+24
	lea	rcx, OFFSET FLAT:crCurSel
	call	AEC_IndexCompare
	test	eax, eax
	jne	SHORT $LN17@DoEditDele

; 2164 :   {
; 2165 :     SendMessage(hWnd, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&crRange.ciMin);

	lea	r9, QWORD PTR crRange$[rsp]
	mov	r8d, 1
	mov	edx, 3130				; 00000c3aH
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 2166 :     SendMessage(hWnd, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&crRange.ciMax);

	lea	r9, QWORD PTR crRange$[rsp+24]
	mov	r8d, 2
	mov	edx, 3130				; 00000c3aH
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 2167 :     bSelection=FALSE;

	mov	DWORD PTR bSelection$[rsp], 0

; 2168 :   }
; 2169 :   else

	jmp	SHORT $LN16@DoEditDele
$LN17@DoEditDele:

; 2170 :   {
; 2171 :     crRange.ciMin=crCurSel.ciMin;

	lea	rax, QWORD PTR crRange$[rsp]
	lea	rcx, OFFSET FLAT:crCurSel
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 2172 :     crRange.ciMax=crCurSel.ciMax;

	lea	rax, QWORD PTR crRange$[rsp+24]
	lea	rcx, OFFSET FLAT:crCurSel+24
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 2173 :     bSelection=TRUE;

	mov	DWORD PTR bSelection$[rsp], 1
$LN16@DoEditDele:

; 2174 :   }
; 2175 : 
; 2176 :   if (nRangeLen=ExGetRangeTextW(hWnd, &crRange.ciMin, &crRange.ciMax, -1, &wszRange, AELB_ASIS, TRUE))

	mov	DWORD PTR [rsp+48], 1
	mov	DWORD PTR [rsp+40], 3
	lea	rax, QWORD PTR wszRange$[rsp]
	mov	QWORD PTR [rsp+32], rax
	mov	r9d, -1
	lea	r8, QWORD PTR crRange$[rsp+24]
	lea	rdx, QWORD PTR crRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	ExGetRangeTextW
	mov	QWORD PTR nRangeLen$[rsp], rax
	cmp	QWORD PTR nRangeLen$[rsp], 0
	je	$LN15@DoEditDele

; 2177 :   {
; 2178 :     wpMaxRead=wszRange + nRangeLen;

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR nRangeLen$[rsp]
	lea	rax, QWORD PTR [rax+rcx*2]
	mov	QWORD PTR wpMaxRead$[rsp], rax

; 2179 : 
; 2180 :     for (wpWrite=wszRange, wpRead=wszRange; wpRead < wpMaxRead; *wpWrite++=*wpRead++)

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	QWORD PTR wpWrite$[rsp], rax
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	QWORD PTR wpRead$[rsp], rax
	jmp	SHORT $LN14@DoEditDele
$LN13@DoEditDele:
	mov	rax, QWORD PTR wpWrite$[rsp]
	mov	rcx, QWORD PTR wpRead$[rsp]
	movzx	ecx, WORD PTR [rcx]
	mov	WORD PTR [rax], cx
	mov	rax, QWORD PTR wpWrite$[rsp]
	add	rax, 2
	mov	QWORD PTR wpWrite$[rsp], rax
	mov	rax, QWORD PTR wpRead$[rsp]
	add	rax, 2
	mov	QWORD PTR wpRead$[rsp], rax
$LN14@DoEditDele:
	mov	rax, QWORD PTR wpMaxRead$[rsp]
	cmp	QWORD PTR wpRead$[rsp], rax
	jae	SHORT $LN12@DoEditDele

; 2181 :     {
; 2182 :       if (*wpRead == '\r' || *wpRead == '\n')

	mov	rax, QWORD PTR wpRead$[rsp]
	movzx	eax, WORD PTR [rax]
	cmp	eax, 13
	je	SHORT $LN10@DoEditDele
	mov	rax, QWORD PTR wpRead$[rsp]
	movzx	eax, WORD PTR [rax]
	cmp	eax, 10
	jne	SHORT $LN11@DoEditDele
$LN10@DoEditDele:
$LN9@DoEditDele:

; 2183 :       {
; 2184 :         while (--wpWrite >= wszRange && (*wpWrite == '\t' || *wpWrite == ' '));

	mov	rax, QWORD PTR wpWrite$[rsp]
	sub	rax, 2
	mov	QWORD PTR wpWrite$[rsp], rax
	mov	rax, QWORD PTR wszRange$[rsp]
	cmp	QWORD PTR wpWrite$[rsp], rax
	jb	SHORT $LN8@DoEditDele
	mov	rax, QWORD PTR wpWrite$[rsp]
	movzx	eax, WORD PTR [rax]
	cmp	eax, 9
	je	SHORT $LN7@DoEditDele
	mov	rax, QWORD PTR wpWrite$[rsp]
	movzx	eax, WORD PTR [rax]
	cmp	eax, 32					; 00000020H
	jne	SHORT $LN8@DoEditDele
$LN7@DoEditDele:
	jmp	SHORT $LN9@DoEditDele
$LN8@DoEditDele:

; 2185 :         ++wpWrite;

	mov	rax, QWORD PTR wpWrite$[rsp]
	add	rax, 2
	mov	QWORD PTR wpWrite$[rsp], rax
$LN11@DoEditDele:

; 2186 :       }
; 2187 :     }

	jmp	$LN13@DoEditDele
$LN12@DoEditDele:
$LN6@DoEditDele:

; 2188 :     while (--wpWrite >= wszRange && (*wpWrite == '\t' || *wpWrite == ' '));

	mov	rax, QWORD PTR wpWrite$[rsp]
	sub	rax, 2
	mov	QWORD PTR wpWrite$[rsp], rax
	mov	rax, QWORD PTR wszRange$[rsp]
	cmp	QWORD PTR wpWrite$[rsp], rax
	jb	SHORT $LN5@DoEditDele
	mov	rax, QWORD PTR wpWrite$[rsp]
	movzx	eax, WORD PTR [rax]
	cmp	eax, 9
	je	SHORT $LN4@DoEditDele
	mov	rax, QWORD PTR wpWrite$[rsp]
	movzx	eax, WORD PTR [rax]
	cmp	eax, 32					; 00000020H
	jne	SHORT $LN5@DoEditDele
$LN4@DoEditDele:
	jmp	SHORT $LN6@DoEditDele
$LN5@DoEditDele:

; 2189 :     ++wpWrite;

	mov	rax, QWORD PTR wpWrite$[rsp]
	add	rax, 2
	mov	QWORD PTR wpWrite$[rsp], rax

; 2190 :     *wpWrite=L'\0';

	xor	eax, eax
	mov	rcx, QWORD PTR wpWrite$[rsp]
	mov	WORD PTR [rcx], ax

; 2191 :     nNewRangeLen=wpWrite - wszRange;

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR wpWrite$[rsp]
	sub	rcx, rax
	mov	rax, rcx
	sar	rax, 1
	mov	QWORD PTR nNewRangeLen$[rsp], rax

; 2192 : 
; 2193 :     if (nRangeLen != nNewRangeLen)

	mov	rax, QWORD PTR nNewRangeLen$[rsp]
	cmp	QWORD PTR nRangeLen$[rsp], rax
	je	$LN3@DoEditDele

; 2194 :     {
; 2195 :       if (!bSelection)

	cmp	DWORD PTR bSelection$[rsp], 0
	jne	SHORT $LN2@DoEditDele

; 2196 :         SetSel(hWnd, &crRange, AESELT_LOCKSCROLL, &crRange.ciMax);

	lea	r9, QWORD PTR crRange$[rsp+24]
	mov	r8d, 8
	lea	rdx, QWORD PTR crRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SetSel
$LN2@DoEditDele:

; 2197 : 
; 2198 :       ReplaceSelW(hWnd, wszRange, nNewRangeLen, AELB_ASINPUT, AEREPT_COLUMNASIS|AEREPT_LOCKSCROLL, &crRange.ciMin, &crRange.ciMax);

	lea	rax, QWORD PTR crRange$[rsp+24]
	mov	QWORD PTR [rsp+48], rax
	lea	rax, QWORD PTR crRange$[rsp]
	mov	QWORD PTR [rsp+40], rax
	mov	DWORD PTR [rsp+32], 6
	mov	r9d, 1
	mov	r8, QWORD PTR nNewRangeLen$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	ReplaceSelW

; 2199 : 
; 2200 :       //Update selection
; 2201 :       if (!bSelection)

	cmp	DWORD PTR bSelection$[rsp], 0
	jne	SHORT $LN1@DoEditDele

; 2202 :       {
; 2203 :         SendMessage(hWnd, AEM_INDEXUPDATE, 0, (LPARAM)&ciInitialCaret);

	lea	r9, QWORD PTR ciInitialCaret$[rsp]
	xor	r8d, r8d
	mov	edx, 3132				; 00000c3cH
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 2204 :         crRange.ciMin=ciInitialCaret;

	lea	rax, QWORD PTR crRange$[rsp]
	lea	rcx, QWORD PTR ciInitialCaret$[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 2205 :         crRange.ciMax=ciInitialCaret;

	lea	rax, QWORD PTR crRange$[rsp+24]
	lea	rcx, QWORD PTR ciInitialCaret$[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb
$LN1@DoEditDele:

; 2206 :       }
; 2207 :       SetSel(hWnd, &crRange, AESELT_COLUMNASIS|AESELT_LOCKSCROLL, bCaretAtStart?&crRange.ciMin:&crRange.ciMax);

	cmp	DWORD PTR bCaretAtStart$[rsp], 0
	je	SHORT $LN22@DoEditDele
	lea	rax, QWORD PTR crRange$[rsp]
	mov	QWORD PTR tv170[rsp], rax
	jmp	SHORT $LN23@DoEditDele
$LN22@DoEditDele:
	lea	rax, QWORD PTR crRange$[rsp+24]
	mov	QWORD PTR tv170[rsp], rax
$LN23@DoEditDele:
	mov	r9, QWORD PTR tv170[rsp]
	mov	r8d, 10
	lea	rdx, QWORD PTR crRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SetSel

; 2208 :       bResult=TRUE;

	mov	DWORD PTR bResult$[rsp], 1
$LN3@DoEditDele:

; 2209 :     }
; 2210 :     FreeText(wszRange);

	mov	rcx, QWORD PTR wszRange$[rsp]
	call	FreeText
$LN15@DoEditDele:

; 2211 :   }
; 2212 : 
; 2213 :   //Restore scroll
; 2214 :   RestoreLineScroll(hWnd, nFirstLine);

	mov	edx, DWORD PTR nFirstLine$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	RestoreLineScroll

; 2215 : 
; 2216 :   return bResult;

	mov	eax, DWORD PTR bResult$[rsp]
$LN20@DoEditDele:

; 2217 : }

	add	rsp, 232				; 000000e8H
	pop	rdi
	pop	rsi
	ret	0
DoEditDeleteTrailingWhitespacesW ENDP
