DoEditChangeCaseW PROC

; 2220 : {

$LN46:
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 216				; 000000d8H

; 2221 :   AECHARRANGE crRange;
; 2222 :   AECHARINDEX ciInitialCaret=ciCurCaret;

	lea	rax, QWORD PTR ciInitialCaret$[rsp]
	lea	rcx, OFFSET FLAT:ciCurCaret
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 2223 :   wchar_t *wszRange;
; 2224 :   wchar_t *wpStart;
; 2225 :   wchar_t *wpEnd;
; 2226 :   int nFirstLine=0;

	mov	DWORD PTR nFirstLine$[rsp], 0

; 2227 :   INT_PTR nRangeLen;
; 2228 :   INT_PTR i;
; 2229 :   BOOL bSelection;
; 2230 :   BOOL bCaretAtStart=FALSE;

	mov	DWORD PTR bCaretAtStart$[rsp], 0

; 2231 :   BOOL bResult=FALSE;

	mov	DWORD PTR bResult$[rsp], 0

; 2232 : 
; 2233 :   if (IsReadOnly(hWnd))

	mov	rcx, QWORD PTR hWnd$[rsp]
	call	IsReadOnly
	test	eax, eax
	je	SHORT $LN41@DoEditChan

; 2234 :     return FALSE;

	xor	eax, eax
	jmp	$LN42@DoEditChan
$LN41@DoEditChan:

; 2235 :   if (!AEC_IndexCompare(&crCurSel.ciMin, &ciCurCaret))

	lea	rdx, OFFSET FLAT:ciCurCaret
	lea	rcx, OFFSET FLAT:crCurSel
	call	AEC_IndexCompare
	test	eax, eax
	jne	SHORT $LN40@DoEditChan

; 2236 :     bCaretAtStart=TRUE;

	mov	DWORD PTR bCaretAtStart$[rsp], 1
$LN40@DoEditChan:

; 2237 : 
; 2238 :   //Save scroll
; 2239 :   nFirstLine=SaveLineScroll(hWnd);

	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SaveLineScroll
	mov	DWORD PTR nFirstLine$[rsp], eax

; 2240 : 
; 2241 :   if (!AEC_IndexCompare(&crCurSel.ciMin, &crCurSel.ciMax))

	lea	rdx, OFFSET FLAT:crCurSel+24
	lea	rcx, OFFSET FLAT:crCurSel
	call	AEC_IndexCompare
	test	eax, eax
	jne	SHORT $LN39@DoEditChan

; 2242 :   {
; 2243 :     SendMessage(hWnd, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&crRange.ciMin);

	lea	r9, QWORD PTR crRange$[rsp]
	mov	r8d, 1
	mov	edx, 3130				; 00000c3aH
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 2244 :     SendMessage(hWnd, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&crRange.ciMax);

	lea	r9, QWORD PTR crRange$[rsp+24]
	mov	r8d, 2
	mov	edx, 3130				; 00000c3aH
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 2245 :     bSelection=FALSE;

	mov	DWORD PTR bSelection$[rsp], 0

; 2246 :   }
; 2247 :   else

	jmp	SHORT $LN38@DoEditChan
$LN39@DoEditChan:

; 2248 :   {
; 2249 :     crRange.ciMin=crCurSel.ciMin;

	lea	rax, QWORD PTR crRange$[rsp]
	lea	rcx, OFFSET FLAT:crCurSel
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 2250 :     crRange.ciMax=crCurSel.ciMax;

	lea	rax, QWORD PTR crRange$[rsp+24]
	lea	rcx, OFFSET FLAT:crCurSel+24
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 2251 :     bSelection=TRUE;

	mov	DWORD PTR bSelection$[rsp], 1
$LN38@DoEditChan:

; 2252 :   }
; 2253 : 
; 2254 :   if (nRangeLen=ExGetRangeTextW(hWnd, &crRange.ciMin, &crRange.ciMax, -1, &wszRange, AELB_ASIS, TRUE))

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
	je	$LN37@DoEditChan

; 2255 :   {
; 2256 :     wpStart=wszRange;

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	QWORD PTR wpStart$[rsp], rax

; 2257 :     wpEnd=wpStart + nRangeLen;

	mov	rax, QWORD PTR wpStart$[rsp]
	mov	rcx, QWORD PTR nRangeLen$[rsp]
	lea	rax, QWORD PTR [rax+rcx*2]
	mov	QWORD PTR wpEnd$[rsp], rax

; 2258 : 
; 2259 :     if (nCase == UPPERCASE)

	cmp	DWORD PTR nCase$[rsp], 1
	jne	SHORT $LN36@DoEditChan

; 2260 :     {
; 2261 :       for (i=0; i < nRangeLen; ++i)

	mov	QWORD PTR i$[rsp], 0
	jmp	SHORT $LN35@DoEditChan
$LN34@DoEditChan:
	mov	rax, QWORD PTR i$[rsp]
	inc	rax
	mov	QWORD PTR i$[rsp], rax
$LN35@DoEditChan:
	mov	rax, QWORD PTR nRangeLen$[rsp]
	cmp	QWORD PTR i$[rsp], rax
	jge	SHORT $LN33@DoEditChan

; 2262 :         wszRange[i]=WideCharUpper(wszRange[i]);

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR i$[rsp]
	movzx	ecx, WORD PTR [rax+rcx*2]
	call	WideCharUpper
	mov	rcx, QWORD PTR wszRange$[rsp]
	mov	rdx, QWORD PTR i$[rsp]
	mov	WORD PTR [rcx+rdx*2], ax
	jmp	SHORT $LN34@DoEditChan
$LN33@DoEditChan:

; 2263 :     }
; 2264 :     else if (nCase == LOWERCASE)

	jmp	$LN32@DoEditChan
$LN36@DoEditChan:
	cmp	DWORD PTR nCase$[rsp], 2
	jne	SHORT $LN31@DoEditChan

; 2265 :     {
; 2266 :       for (i=0; i < nRangeLen; ++i)

	mov	QWORD PTR i$[rsp], 0
	jmp	SHORT $LN30@DoEditChan
$LN29@DoEditChan:
	mov	rax, QWORD PTR i$[rsp]
	inc	rax
	mov	QWORD PTR i$[rsp], rax
$LN30@DoEditChan:
	mov	rax, QWORD PTR nRangeLen$[rsp]
	cmp	QWORD PTR i$[rsp], rax
	jge	SHORT $LN28@DoEditChan

; 2267 :         wszRange[i]=WideCharLower(wszRange[i]);

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR i$[rsp]
	movzx	ecx, WORD PTR [rax+rcx*2]
	call	WideCharLower
	mov	rcx, QWORD PTR wszRange$[rsp]
	mov	rdx, QWORD PTR i$[rsp]
	mov	WORD PTR [rcx+rdx*2], ax
	jmp	SHORT $LN29@DoEditChan
$LN28@DoEditChan:

; 2268 :     }
; 2269 :     else if (nCase == SENTENCECASE)

	jmp	$LN27@DoEditChan
$LN31@DoEditChan:
	cmp	DWORD PTR nCase$[rsp], 3
	jne	$LN26@DoEditChan
$LN25@DoEditChan:

; 2270 :     {
; 2271 :       while (wpStart < wpEnd)

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	$LN24@DoEditChan
$LN23@DoEditChan:

; 2272 :       {
; 2273 :         while (wpStart < wpEnd && (AKD_wcschr(lpFrameCurrent->wszWordDelimiters, *wpStart) || AKD_wcschr(STR_SENTENCE_DELIMITERSW, *wpStart)))

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	SHORT $LN22@DoEditChan
	mov	rax, QWORD PTR lpFrameCurrent
	add	rax, 1948				; 0000079cH
	mov	rcx, QWORD PTR wpStart$[rsp]
	movzx	edx, WORD PTR [rcx]
	mov	rcx, rax
	call	AKD_wcschr
	test	rax, rax
	jne	SHORT $LN21@DoEditChan
	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	edx, WORD PTR [rax]
	lea	rcx, OFFSET FLAT:$SG110953
	call	AKD_wcschr
	test	rax, rax
	je	SHORT $LN22@DoEditChan
$LN21@DoEditChan:

; 2274 :         {
; 2275 :           ++wpStart;

	mov	rax, QWORD PTR wpStart$[rsp]
	add	rax, 2
	mov	QWORD PTR wpStart$[rsp], rax

; 2276 :         }

	jmp	SHORT $LN23@DoEditChan
$LN22@DoEditChan:

; 2277 :         if (wpStart < wpEnd)

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	SHORT $LN20@DoEditChan

; 2278 :         {
; 2279 :           *wpStart=WideCharUpper(*wpStart);

	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	ecx, WORD PTR [rax]
	call	WideCharUpper
	mov	rcx, QWORD PTR wpStart$[rsp]
	mov	WORD PTR [rcx], ax

; 2280 :           ++wpStart;

	mov	rax, QWORD PTR wpStart$[rsp]
	add	rax, 2
	mov	QWORD PTR wpStart$[rsp], rax
$LN20@DoEditChan:
$LN19@DoEditChan:

; 2281 :         }
; 2282 :         while (wpStart < wpEnd && !AKD_wcschr(STR_SENTENCE_DELIMITERSW, *wpStart))

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	SHORT $LN18@DoEditChan
	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	edx, WORD PTR [rax]
	lea	rcx, OFFSET FLAT:$SG110958
	call	AKD_wcschr
	test	rax, rax
	jne	SHORT $LN18@DoEditChan

; 2283 :         {
; 2284 :           *wpStart=WideCharLower(*wpStart);

	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	ecx, WORD PTR [rax]
	call	WideCharLower
	mov	rcx, QWORD PTR wpStart$[rsp]
	mov	WORD PTR [rcx], ax

; 2285 :           ++wpStart;

	mov	rax, QWORD PTR wpStart$[rsp]
	add	rax, 2
	mov	QWORD PTR wpStart$[rsp], rax

; 2286 :         }

	jmp	SHORT $LN19@DoEditChan
$LN18@DoEditChan:

; 2287 :       }

	jmp	$LN25@DoEditChan
$LN24@DoEditChan:

; 2288 :     }
; 2289 :     else if (nCase == TITLECASE)

	jmp	$LN17@DoEditChan
$LN26@DoEditChan:
	cmp	DWORD PTR nCase$[rsp], 4
	jne	$LN16@DoEditChan
$LN15@DoEditChan:

; 2290 :     {
; 2291 :       while (wpStart < wpEnd)

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	$LN14@DoEditChan
$LN13@DoEditChan:

; 2292 :       {
; 2293 :         while (wpStart < wpEnd && AKD_wcschr(lpFrameCurrent->wszWordDelimiters, *wpStart))

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	SHORT $LN12@DoEditChan
	mov	rax, QWORD PTR lpFrameCurrent
	add	rax, 1948				; 0000079cH
	mov	rcx, QWORD PTR wpStart$[rsp]
	movzx	edx, WORD PTR [rcx]
	mov	rcx, rax
	call	AKD_wcschr
	test	rax, rax
	je	SHORT $LN12@DoEditChan

; 2294 :         {
; 2295 :           ++wpStart;

	mov	rax, QWORD PTR wpStart$[rsp]
	add	rax, 2
	mov	QWORD PTR wpStart$[rsp], rax

; 2296 :         }

	jmp	SHORT $LN13@DoEditChan
$LN12@DoEditChan:

; 2297 :         if (wpStart < wpEnd)

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	SHORT $LN11@DoEditChan

; 2298 :         {
; 2299 :           *wpStart=WideCharUpper(*wpStart);

	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	ecx, WORD PTR [rax]
	call	WideCharUpper
	mov	rcx, QWORD PTR wpStart$[rsp]
	mov	WORD PTR [rcx], ax

; 2300 :           ++wpStart;

	mov	rax, QWORD PTR wpStart$[rsp]
	add	rax, 2
	mov	QWORD PTR wpStart$[rsp], rax
$LN11@DoEditChan:
$LN10@DoEditChan:

; 2301 :         }
; 2302 :         while (wpStart < wpEnd && !AKD_wcschr(lpFrameCurrent->wszWordDelimiters, *wpStart))

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	SHORT $LN9@DoEditChan
	mov	rax, QWORD PTR lpFrameCurrent
	add	rax, 1948				; 0000079cH
	mov	rcx, QWORD PTR wpStart$[rsp]
	movzx	edx, WORD PTR [rcx]
	mov	rcx, rax
	call	AKD_wcschr
	test	rax, rax
	jne	SHORT $LN9@DoEditChan

; 2303 :         {
; 2304 :           *wpStart=WideCharLower(*wpStart);

	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	ecx, WORD PTR [rax]
	call	WideCharLower
	mov	rcx, QWORD PTR wpStart$[rsp]
	mov	WORD PTR [rcx], ax

; 2305 :           ++wpStart;

	mov	rax, QWORD PTR wpStart$[rsp]
	add	rax, 2
	mov	QWORD PTR wpStart$[rsp], rax

; 2306 :         }

	jmp	SHORT $LN10@DoEditChan
$LN9@DoEditChan:

; 2307 :       }

	jmp	$LN15@DoEditChan
$LN14@DoEditChan:

; 2308 :     }
; 2309 :     else if (nCase == INVERTCASE)

	jmp	SHORT $LN8@DoEditChan
$LN16@DoEditChan:
	cmp	DWORD PTR nCase$[rsp], 5
	jne	SHORT $LN7@DoEditChan
$LN6@DoEditChan:

; 2310 :     {
; 2311 :       while (wpStart < wpEnd)

	mov	rax, QWORD PTR wpEnd$[rsp]
	cmp	QWORD PTR wpStart$[rsp], rax
	jae	SHORT $LN5@DoEditChan

; 2312 :       {
; 2313 :         if (WideCharLower(*wpStart) == *wpStart)

	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	ecx, WORD PTR [rax]
	call	WideCharLower
	movzx	eax, ax
	mov	rcx, QWORD PTR wpStart$[rsp]
	movzx	ecx, WORD PTR [rcx]
	cmp	eax, ecx
	jne	SHORT $LN4@DoEditChan

; 2314 :         {
; 2315 :           *wpStart=WideCharUpper(*wpStart);

	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	ecx, WORD PTR [rax]
	call	WideCharUpper
	mov	rcx, QWORD PTR wpStart$[rsp]
	mov	WORD PTR [rcx], ax

; 2316 :           ++wpStart;

	mov	rax, QWORD PTR wpStart$[rsp]
	add	rax, 2
	mov	QWORD PTR wpStart$[rsp], rax

; 2317 :         }
; 2318 :         else

	jmp	SHORT $LN3@DoEditChan
$LN4@DoEditChan:

; 2319 :         {
; 2320 :           *wpStart=WideCharLower(*wpStart);

	mov	rax, QWORD PTR wpStart$[rsp]
	movzx	ecx, WORD PTR [rax]
	call	WideCharLower
	mov	rcx, QWORD PTR wpStart$[rsp]
	mov	WORD PTR [rcx], ax

; 2321 :           ++wpStart;

	mov	rax, QWORD PTR wpStart$[rsp]
	add	rax, 2
	mov	QWORD PTR wpStart$[rsp], rax
$LN3@DoEditChan:

; 2322 :         }
; 2323 :       }

	jmp	SHORT $LN6@DoEditChan
$LN5@DoEditChan:
$LN7@DoEditChan:
$LN8@DoEditChan:
$LN17@DoEditChan:
$LN27@DoEditChan:
$LN32@DoEditChan:

; 2324 :     }
; 2325 : 
; 2326 :     if (!bSelection)

	cmp	DWORD PTR bSelection$[rsp], 0
	jne	SHORT $LN2@DoEditChan

; 2327 :       SetSel(hWnd, &crRange, AESELT_LOCKSCROLL, &crRange.ciMax);

	lea	r9, QWORD PTR crRange$[rsp+24]
	mov	r8d, 8
	lea	rdx, QWORD PTR crRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SetSel
$LN2@DoEditChan:

; 2328 : 
; 2329 :     ReplaceSelW(hWnd, wszRange, -1, AELB_ASINPUT, AEREPT_COLUMNASIS|AEREPT_LOCKSCROLL, &crRange.ciMin, &crRange.ciMax);

	lea	rax, QWORD PTR crRange$[rsp+24]
	mov	QWORD PTR [rsp+48], rax
	lea	rax, QWORD PTR crRange$[rsp]
	mov	QWORD PTR [rsp+40], rax
	mov	DWORD PTR [rsp+32], 6
	mov	r9d, 1
	mov	r8, -1
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	ReplaceSelW

; 2330 : 
; 2331 :     //Update selection
; 2332 :     if (!bSelection)

	cmp	DWORD PTR bSelection$[rsp], 0
	jne	SHORT $LN1@DoEditChan

; 2333 :     {
; 2334 :       SendMessage(hWnd, AEM_INDEXUPDATE, 0, (LPARAM)&ciInitialCaret);

	lea	r9, QWORD PTR ciInitialCaret$[rsp]
	xor	r8d, r8d
	mov	edx, 3132				; 00000c3cH
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 2335 :       crRange.ciMin=ciInitialCaret;

	lea	rax, QWORD PTR crRange$[rsp]
	lea	rcx, QWORD PTR ciInitialCaret$[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 2336 :       crRange.ciMax=ciInitialCaret;

	lea	rax, QWORD PTR crRange$[rsp+24]
	lea	rcx, QWORD PTR ciInitialCaret$[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb
$LN1@DoEditChan:

; 2337 :     }
; 2338 :     SetSel(hWnd, &crRange, AESELT_COLUMNASIS|AESELT_LOCKSCROLL, bCaretAtStart?&crRange.ciMin:&crRange.ciMax);

	cmp	DWORD PTR bCaretAtStart$[rsp], 0
	je	SHORT $LN44@DoEditChan
	lea	rax, QWORD PTR crRange$[rsp]
	mov	QWORD PTR tv224[rsp], rax
	jmp	SHORT $LN45@DoEditChan
$LN44@DoEditChan:
	lea	rax, QWORD PTR crRange$[rsp+24]
	mov	QWORD PTR tv224[rsp], rax
$LN45@DoEditChan:
	mov	r9, QWORD PTR tv224[rsp]
	mov	r8d, 10
	lea	rdx, QWORD PTR crRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SetSel

; 2339 : 
; 2340 :     FreeText(wszRange);

	mov	rcx, QWORD PTR wszRange$[rsp]
	call	FreeText

; 2341 :     bResult=TRUE;

	mov	DWORD PTR bResult$[rsp], 1
$LN37@DoEditChan:

; 2342 :   }
; 2343 : 
; 2344 :   //Restore scroll
; 2345 :   RestoreLineScroll(hWnd, nFirstLine);

	mov	edx, DWORD PTR nFirstLine$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	RestoreLineScroll

; 2346 : 
; 2347 :   return bResult;

	mov	eax, DWORD PTR bResult$[rsp]
$LN42@DoEditChan:

; 2348 : }

	add	rsp, 216				; 000000d8H
	pop	rdi
	pop	rsi
	ret	0
DoEditChangeCaseW ENDP
