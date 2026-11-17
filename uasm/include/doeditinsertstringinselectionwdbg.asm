DoEditInsertStringInSelectionW PROC

; 1871 : {

$LN77:
	mov	QWORD PTR [rsp+24], r8
	mov	DWORD PTR [rsp+16], edx
	mov	QWORD PTR [rsp+8], rcx
	push	rsi
	push	rdi
	sub	rsp, 328				; 00000148H

; 1872 :   AECHARRANGE crRange;
; 1873 :   AETEXTRANGEW tr;
; 1874 :   wchar_t *wszRange=NULL;

	mov	QWORD PTR wszRange$[rsp], 0

; 1875 :   INT_PTR nRangeLen;
; 1876 :   INT_PTR nStringLenAll;
; 1877 :   INT_PTR nBufferLen;
; 1878 :   int nStringLen;
; 1879 :   int nStringBytes;
; 1880 :   int nFirstLine=0;

	mov	DWORD PTR nFirstLine$[rsp], 0

; 1881 :   INT_PTR a=0;

	mov	QWORD PTR a$[rsp], 0

; 1882 :   INT_PTR b=0;

	mov	QWORD PTR b$[rsp], 0

; 1883 :   INT_PTR i;
; 1884 :   BOOL bColumnSel;
; 1885 :   BOOL bCaretAtStart=FALSE;

	mov	DWORD PTR bCaretAtStart$[rsp], 0

; 1886 :   BOOL bResult=FALSE;

	mov	DWORD PTR bResult$[rsp], 0

; 1887 : 
; 1888 :   if (!(nAction & STRSEL_CHECK) && IsReadOnly(hWnd))

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 1
	test	eax, eax
	jne	SHORT $LN66@DoEditInse
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	IsReadOnly
	test	eax, eax
	je	SHORT $LN66@DoEditInse

; 1889 :     return FALSE;

	xor	eax, eax
	jmp	$LN67@DoEditInse
$LN66@DoEditInse:

; 1890 :   if (!AEC_IndexCompare(&crCurSel.ciMin, &ciCurCaret))

	lea	rdx, OFFSET FLAT:ciCurCaret
	lea	rcx, OFFSET FLAT:crCurSel
	call	AEC_IndexCompare
	test	eax, eax
	jne	SHORT $LN65@DoEditInse

; 1891 :     bCaretAtStart=TRUE;

	mov	DWORD PTR bCaretAtStart$[rsp], 1
$LN65@DoEditInse:

; 1892 :   crRange.ciMin=crCurSel.ciMin;

	lea	rax, QWORD PTR crRange$[rsp]
	lea	rcx, OFFSET FLAT:crCurSel
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 1893 :   crRange.ciMax=crCurSel.ciMax;

	lea	rax, QWORD PTR crRange$[rsp+24]
	lea	rcx, OFFSET FLAT:crCurSel+24
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 1894 : 
; 1895 :   if (crRange.ciMin.nLine != crRange.ciMax.nLine)

	mov	eax, DWORD PTR crRange$[rsp+24]
	cmp	DWORD PTR crRange$[rsp], eax
	je	$LN64@DoEditInse

; 1896 :   {
; 1897 :     if (nAction & STRSEL_CHECK) return TRUE;

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN63@DoEditInse
	mov	eax, 1
	jmp	$LN67@DoEditInse
$LN63@DoEditInse:

; 1898 : 
; 1899 :     if (!(bColumnSel=(BOOL)SendMessage(hWnd, AEM_GETCOLUMNSEL, 0, 0)))

	xor	r9d, r9d
	xor	r8d, r8d
	mov	edx, 3127				; 00000c37H
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA
	mov	DWORD PTR bColumnSel$[rsp], eax
	cmp	DWORD PTR bColumnSel$[rsp], 0
	jne	SHORT $LN62@DoEditInse

; 1900 :     {
; 1901 :       SendMessage(hWnd, AEM_GETINDEX, AEGI_WRAPLINEBEGIN, (LPARAM)&crRange.ciMin);

	lea	r9, QWORD PTR crRange$[rsp]
	mov	r8d, 18
	mov	edx, 3130				; 00000c3aH
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 1902 :       if (!AEC_IsFirstCharInLine(&crRange.ciMax))

	lea	rcx, QWORD PTR crRange$[rsp+24]
	call	AEC_IsFirstCharInLine
	test	eax, eax
	jne	SHORT $LN61@DoEditInse

; 1903 :       {
; 1904 :         SendMessage(hWnd, AEM_GETINDEX, AEGI_WRAPLINEEND, (LPARAM)&crRange.ciMax);

	lea	r9, QWORD PTR crRange$[rsp+24]
	mov	r8d, 19
	mov	edx, 3130				; 00000c3aH
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA
$LN61@DoEditInse:
$LN62@DoEditInse:

; 1905 :         //SendMessage(hWnd, AEM_GETINDEX, AEGI_NEXTLINE, (LPARAM)&crRange.ciMax);
; 1906 :       }
; 1907 :     }
; 1908 : 
; 1909 :     if (nRangeLen=IndexSubtract(hWnd, &crRange.ciMax, &crRange.ciMin, AELB_ASIS, bColumnSel))

	mov	eax, DWORD PTR bColumnSel$[rsp]
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, 3
	lea	r8, QWORD PTR crRange$[rsp]
	lea	rdx, QWORD PTR crRange$[rsp+24]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	IndexSubtract
	mov	QWORD PTR nRangeLen$[rsp], rax
	cmp	QWORD PTR nRangeLen$[rsp], 0
	je	$LN60@DoEditInse

; 1910 :     {
; 1911 :       nStringLen=(int)xstrlenW(wpString);

	mov	rcx, QWORD PTR wpString$[rsp]
	call	xstrlenW
	mov	DWORD PTR nStringLen$[rsp], eax

; 1912 :       nStringBytes=nStringLen * sizeof(wchar_t);

	movsxd	rax, DWORD PTR nStringLen$[rsp]
	shl	rax, 1
	mov	DWORD PTR nStringBytes$[rsp], eax

; 1913 : 
; 1914 :       //Save scroll
; 1915 :       nFirstLine=SaveLineScroll(hWnd);

	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SaveLineScroll
	mov	DWORD PTR nFirstLine$[rsp], eax

; 1916 : 
; 1917 :       if (!bColumnSel)

	cmp	DWORD PTR bColumnSel$[rsp], 0
	jne	SHORT $LN59@DoEditInse

; 1918 :         SetSel(hWnd, &crRange, AESELT_LOCKSCROLL, NULL);

	xor	r9d, r9d
	mov	r8d, 8
	lea	rdx, QWORD PTR crRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SetSel
$LN59@DoEditInse:

; 1919 : 
; 1920 :       if (nAction & STRSEL_INSERT)

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 2
	test	eax, eax
	je	$LN58@DoEditInse

; 1921 :       {
; 1922 :         nStringLenAll=(crRange.ciMax.nLine - crRange.ciMin.nLine + 1) * nStringLen;

	mov	eax, DWORD PTR crRange$[rsp]
	mov	ecx, DWORD PTR crRange$[rsp+24]
	sub	ecx, eax
	mov	eax, ecx
	inc	eax
	imul	eax, DWORD PTR nStringLen$[rsp]
	cdqe
	mov	QWORD PTR nStringLenAll$[rsp], rax

; 1923 :         nBufferLen=nRangeLen + nStringLenAll;

	mov	rax, QWORD PTR nStringLenAll$[rsp]
	mov	rcx, QWORD PTR nRangeLen$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR nBufferLen$[rsp], rax

; 1924 : 
; 1925 :         if (wszRange=AllocWideStr(nBufferLen + 1))

	mov	rax, QWORD PTR nBufferLen$[rsp]
	inc	rax
	mov	rcx, rax
	call	AllocWideStr
	mov	QWORD PTR wszRange$[rsp], rax
	cmp	QWORD PTR wszRange$[rsp], 0
	je	$LN57@DoEditInse

; 1926 :         {
; 1927 :           tr.cr.ciMin=crRange.ciMin;

	lea	rax, QWORD PTR tr$[rsp]
	lea	rcx, QWORD PTR crRange$[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 1928 :           tr.cr.ciMax=crRange.ciMax;

	lea	rax, QWORD PTR tr$[rsp+24]
	lea	rcx, QWORD PTR crRange$[rsp+24]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 1929 :           tr.bColumnSel=bColumnSel;

	mov	eax, DWORD PTR bColumnSel$[rsp]
	mov	DWORD PTR tr$[rsp+48], eax

; 1930 :           tr.pBuffer=wszRange + nStringLenAll;

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR nStringLenAll$[rsp]
	lea	rax, QWORD PTR [rax+rcx*2]
	mov	QWORD PTR tr$[rsp+56], rax

; 1931 :           tr.dwBufferMax=(UINT_PTR)-1;

	mov	QWORD PTR tr$[rsp+64], -1

; 1932 :           tr.nNewLine=AELB_ASIS;

	mov	DWORD PTR tr$[rsp+72], 3

; 1933 :           tr.bFillSpaces=TRUE;

	mov	DWORD PTR tr$[rsp+96], 1

; 1934 :           SendMessage(hWnd, AEM_GETTEXTRANGEW, 0, (LPARAM)&tr);

	lea	r9, QWORD PTR tr$[rsp]
	xor	r8d, r8d
	mov	edx, 3032				; 00000bd8H
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 1935 :           b=nStringLenAll;

	mov	rax, QWORD PTR nStringLenAll$[rsp]
	mov	QWORD PTR b$[rsp], rax

; 1936 : 
; 1937 :           xmemcpy(wszRange, wpString, nStringBytes);

	movsxd	rax, DWORD PTR nStringBytes$[rsp]
	mov	r8, rax
	mov	rdx, QWORD PTR wpString$[rsp]
	mov	rcx, QWORD PTR wszRange$[rsp]
	call	xmemcpy

; 1938 :           a=nStringLen;

	movsxd	rax, DWORD PTR nStringLen$[rsp]
	mov	QWORD PTR a$[rsp], rax
$LN75@DoEditInse:
$LN56@DoEditInse:

; 1939 : 
; 1940 :           while (b < nBufferLen)

	mov	rax, QWORD PTR nBufferLen$[rsp]
	cmp	QWORD PTR b$[rsp], rax
	jge	$LN55@DoEditInse

; 1941 :           {
; 1942 :             if (wszRange[b] == '\r' && wszRange[b + 1] == '\r' && wszRange[b + 2] == '\n')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 13
	jne	$LN54@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2+2]
	cmp	eax, 13
	jne	$LN54@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2+4]
	cmp	eax, 10
	jne	$LN54@DoEditInse

; 1943 :             {
; 1944 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 1945 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 1946 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
	jmp	$LN53@DoEditInse
$LN54@DoEditInse:

; 1947 :             }
; 1948 :             else if (wszRange[b] == '\r' && wszRange[b + 1] == '\n')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 13
	jne	$LN52@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2+2]
	cmp	eax, 10
	jne	SHORT $LN52@DoEditInse

; 1949 :             {
; 1950 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 1951 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
	jmp	$LN51@DoEditInse
$LN52@DoEditInse:

; 1952 :             }
; 1953 :             else if (wszRange[b] == '\r')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 13
	jne	SHORT $LN50@DoEditInse

; 1954 :             {
; 1955 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
	jmp	$LN49@DoEditInse
$LN50@DoEditInse:

; 1956 :             }
; 1957 :             else if (wszRange[b] == '\n')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 10
	jne	SHORT $LN48@DoEditInse

; 1958 :             {
; 1959 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 1960 :             }
; 1961 :             else

	jmp	SHORT $LN47@DoEditInse
$LN48@DoEditInse:

; 1962 :             {
; 1963 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 1964 :               continue;

	jmp	$LN56@DoEditInse
$LN47@DoEditInse:
$LN49@DoEditInse:
$LN51@DoEditInse:
$LN53@DoEditInse:

; 1965 :             }
; 1966 : 
; 1967 :             if (b < nBufferLen || bColumnSel)

	mov	rax, QWORD PTR nBufferLen$[rsp]
	cmp	QWORD PTR b$[rsp], rax
	jl	SHORT $LN45@DoEditInse
	cmp	DWORD PTR bColumnSel$[rsp], 0
	je	SHORT $LN46@DoEditInse
$LN45@DoEditInse:

; 1968 :             {
; 1969 :               xmemcpy(wszRange + a, wpString, nStringBytes);

	movsxd	rax, DWORD PTR nStringBytes$[rsp]
	mov	rcx, QWORD PTR wszRange$[rsp]
	mov	rdx, QWORD PTR a$[rsp]
	lea	rcx, QWORD PTR [rcx+rdx*2]
	mov	r8, rax
	mov	rdx, QWORD PTR wpString$[rsp]
	call	xmemcpy

; 1970 :               a+=nStringLen;

	movsxd	rax, DWORD PTR nStringLen$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR a$[rsp], rax
$LN46@DoEditInse:

; 1971 :             }
; 1972 :           }

	jmp	$LN75@DoEditInse
$LN55@DoEditInse:

; 1973 :           wszRange[a]='\0';

	xor	eax, eax
	mov	rcx, QWORD PTR wszRange$[rsp]
	mov	rdx, QWORD PTR a$[rsp]
	mov	WORD PTR [rcx+rdx*2], ax

; 1974 :           bResult=TRUE;

	mov	DWORD PTR bResult$[rsp], 1
$LN57@DoEditInse:

; 1975 :         }

	jmp	$LN44@DoEditInse
$LN58@DoEditInse:

; 1976 :       }
; 1977 :       else if (nAction & STRSEL_DELETE)

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 4
	test	eax, eax
	je	$LN43@DoEditInse

; 1978 :       {
; 1979 :         if (wszRange=AllocWideStr(nRangeLen + 1))

	mov	rax, QWORD PTR nRangeLen$[rsp]
	inc	rax
	mov	rcx, rax
	call	AllocWideStr
	mov	QWORD PTR wszRange$[rsp], rax
	cmp	QWORD PTR wszRange$[rsp], 0
	je	$LN42@DoEditInse

; 1980 :         {
; 1981 :           tr.cr.ciMin=crRange.ciMin;

	lea	rax, QWORD PTR tr$[rsp]
	lea	rcx, QWORD PTR crRange$[rsp]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 1982 :           tr.cr.ciMax=crRange.ciMax;

	lea	rax, QWORD PTR tr$[rsp+24]
	lea	rcx, QWORD PTR crRange$[rsp+24]
	mov	rdi, rax
	mov	rsi, rcx
	mov	ecx, 24
	rep movsb

; 1983 :           tr.bColumnSel=bColumnSel;

	mov	eax, DWORD PTR bColumnSel$[rsp]
	mov	DWORD PTR tr$[rsp+48], eax

; 1984 :           tr.pBuffer=wszRange;

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	QWORD PTR tr$[rsp+56], rax

; 1985 :           tr.dwBufferMax=(UINT_PTR)-1;

	mov	QWORD PTR tr$[rsp+64], -1

; 1986 :           tr.nNewLine=AELB_ASIS;

	mov	DWORD PTR tr$[rsp+72], 3

; 1987 :           tr.bFillSpaces=TRUE;

	mov	DWORD PTR tr$[rsp+96], 1

; 1988 :           SendMessage(hWnd, AEM_GETTEXTRANGEW, 0, (LPARAM)&tr);

	lea	r9, QWORD PTR tr$[rsp]
	xor	r8d, r8d
	mov	edx, 3032				; 00000bd8H
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	QWORD PTR __imp_SendMessageA

; 1989 : 
; 1990 :           if (nAction & STRSEL_TAB)

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 8
	test	eax, eax
	je	SHORT $LN41@DoEditInse

; 1991 :           {
; 1992 :             if (wszRange[b] == '\t')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 9
	jne	SHORT $LN40@DoEditInse

; 1993 :               ++b;

	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 1994 :             else

	jmp	SHORT $LN39@DoEditInse
$LN40@DoEditInse:

; 1995 :               for (i=0; i < lpFrameCurrent->nTabStopSize && wszRange[b] == ' '; ++i, ++b);

	mov	QWORD PTR i$[rsp], 0
	jmp	SHORT $LN38@DoEditInse
$LN37@DoEditInse:
	mov	rax, QWORD PTR i$[rsp]
	inc	rax
	mov	QWORD PTR i$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
$LN38@DoEditInse:
	mov	rax, QWORD PTR lpFrameCurrent
	movsxd	rax, DWORD PTR [rax+1132]
	cmp	QWORD PTR i$[rsp], rax
	jge	SHORT $LN36@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 32					; 00000020H
	jne	SHORT $LN36@DoEditInse
	jmp	SHORT $LN37@DoEditInse
$LN36@DoEditInse:
$LN39@DoEditInse:
	jmp	$LN35@DoEditInse
$LN41@DoEditInse:

; 1996 :           }
; 1997 :           else if (nAction & STRSEL_SPACE)

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 16
	test	eax, eax
	je	SHORT $LN34@DoEditInse

; 1998 :           {
; 1999 :             if (wszRange[b] == ' ' || wszRange[b] == '\t')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 32					; 00000020H
	je	SHORT $LN32@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 9
	jne	SHORT $LN33@DoEditInse
$LN32@DoEditInse:

; 2000 :               ++b;

	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
$LN33@DoEditInse:

; 2001 :           }
; 2002 :           else if (nAction & STRSEL_COMENT)

	jmp	$LN31@DoEditInse
$LN34@DoEditInse:
	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 256				; 00000100H
	test	eax, eax
	je	SHORT $LN30@DoEditInse

; 2003 :           {
; 2004 : 			  if (wszRange[b] == ';'|| wszRange[b] == '\t')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 59					; 0000003bH
	je	SHORT $LN28@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 9
	jne	SHORT $LN29@DoEditInse
$LN28@DoEditInse:

; 2005 :               ++b;

	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
$LN29@DoEditInse:

; 2006 :           }
; 2007 :           else

	jmp	SHORT $LN27@DoEditInse
$LN30@DoEditInse:

; 2008 :           {
; 2009 :             if (!xmemcmp(wszRange + b, wpString, nStringBytes))

	movsxd	rax, DWORD PTR nStringBytes$[rsp]
	mov	rcx, QWORD PTR wszRange$[rsp]
	mov	rdx, QWORD PTR b$[rsp]
	lea	rcx, QWORD PTR [rcx+rdx*2]
	mov	r8, rax
	mov	rdx, QWORD PTR wpString$[rsp]
	call	xmemcmp
	test	eax, eax
	jne	SHORT $LN26@DoEditInse

; 2010 :               b+=nStringLen;

	movsxd	rax, DWORD PTR nStringLen$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR b$[rsp], rax
$LN26@DoEditInse:
$LN27@DoEditInse:
$LN31@DoEditInse:
$LN35@DoEditInse:
$LN76@DoEditInse:
$LN25@DoEditInse:

; 2011 :           }
; 2012 : 
; 2013 :           while (b < nRangeLen)

	mov	rax, QWORD PTR nRangeLen$[rsp]
	cmp	QWORD PTR b$[rsp], rax
	jge	$LN24@DoEditInse

; 2014 :           {
; 2015 :             if (wszRange[b] == '\r' && wszRange[b + 1] == '\r' && wszRange[b + 2] == '\n')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 13
	jne	$LN23@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2+2]
	cmp	eax, 13
	jne	$LN23@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2+4]
	cmp	eax, 10
	jne	$LN23@DoEditInse

; 2016 :             {
; 2017 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 2018 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 2019 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
	jmp	$LN22@DoEditInse
$LN23@DoEditInse:

; 2020 :             }
; 2021 :             else if (wszRange[b] == '\r' && wszRange[b + 1] == '\n')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 13
	jne	$LN21@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2+2]
	cmp	eax, 10
	jne	SHORT $LN21@DoEditInse

; 2022 :             {
; 2023 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 2024 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
	jmp	$LN20@DoEditInse
$LN21@DoEditInse:

; 2025 :             }
; 2026 :             else if (wszRange[b] == '\r')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 13
	jne	SHORT $LN19@DoEditInse

; 2027 :             {
; 2028 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
	jmp	$LN18@DoEditInse
$LN19@DoEditInse:

; 2029 :             }
; 2030 :             else if (wszRange[b] == '\n')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 10
	jne	SHORT $LN17@DoEditInse

; 2031 :             {
; 2032 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 2033 :             }
; 2034 :             else

	jmp	SHORT $LN16@DoEditInse
$LN17@DoEditInse:

; 2035 :             {
; 2036 :               wszRange[a++]=wszRange[b++];

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rdi, QWORD PTR b$[rsp]
	movzx	edx, WORD PTR [rdx+rdi*2]
	mov	WORD PTR [rax+rcx*2], dx
	mov	rax, QWORD PTR a$[rsp]
	inc	rax
	mov	QWORD PTR a$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 2037 :               continue;

	jmp	$LN25@DoEditInse
$LN16@DoEditInse:
$LN18@DoEditInse:
$LN20@DoEditInse:
$LN22@DoEditInse:

; 2038 :             }
; 2039 : 
; 2040 :             if (b < nRangeLen)

	mov	rax, QWORD PTR nRangeLen$[rsp]
	cmp	QWORD PTR b$[rsp], rax
	jge	$LN15@DoEditInse

; 2041 :             {
; 2042 :               if (nAction & STRSEL_TAB)

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 8
	test	eax, eax
	je	SHORT $LN14@DoEditInse

; 2043 :               {
; 2044 :                 if (wszRange[b] == '\t')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 9
	jne	SHORT $LN13@DoEditInse

; 2045 :                   ++b;

	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax

; 2046 :                 else

	jmp	SHORT $LN12@DoEditInse
$LN13@DoEditInse:

; 2047 :                   for (i=0; i < lpFrameCurrent->nTabStopSize && wszRange[b] == ' '; ++i, ++b);

	mov	QWORD PTR i$[rsp], 0
	jmp	SHORT $LN11@DoEditInse
$LN10@DoEditInse:
	mov	rax, QWORD PTR i$[rsp]
	inc	rax
	mov	QWORD PTR i$[rsp], rax
	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
$LN11@DoEditInse:
	mov	rax, QWORD PTR lpFrameCurrent
	movsxd	rax, DWORD PTR [rax+1132]
	cmp	QWORD PTR i$[rsp], rax
	jge	SHORT $LN9@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 32					; 00000020H
	jne	SHORT $LN9@DoEditInse
	jmp	SHORT $LN10@DoEditInse
$LN9@DoEditInse:
$LN12@DoEditInse:
	jmp	SHORT $LN8@DoEditInse
$LN14@DoEditInse:

; 2048 :               }
; 2049 :               else if (nAction & STRSEL_SPACE)

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 16
	test	eax, eax
	je	SHORT $LN7@DoEditInse

; 2050 :               {
; 2051 :                 if (wszRange[b] == ' ' || wszRange[b] == '\t')

	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 32					; 00000020H
	je	SHORT $LN5@DoEditInse
	mov	rax, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	movzx	eax, WORD PTR [rax+rcx*2]
	cmp	eax, 9
	jne	SHORT $LN6@DoEditInse
$LN5@DoEditInse:

; 2052 :                   ++b;

	mov	rax, QWORD PTR b$[rsp]
	inc	rax
	mov	QWORD PTR b$[rsp], rax
$LN6@DoEditInse:

; 2053 :               }
; 2054 :               else

	jmp	SHORT $LN4@DoEditInse
$LN7@DoEditInse:

; 2055 :               {
; 2056 :                 if (!xmemcmp(wszRange + b, wpString, nStringBytes))

	movsxd	rax, DWORD PTR nStringBytes$[rsp]
	mov	rcx, QWORD PTR wszRange$[rsp]
	mov	rdx, QWORD PTR b$[rsp]
	lea	rcx, QWORD PTR [rcx+rdx*2]
	mov	r8, rax
	mov	rdx, QWORD PTR wpString$[rsp]
	call	xmemcmp
	test	eax, eax
	jne	SHORT $LN3@DoEditInse

; 2057 :                   b+=nStringLen;

	movsxd	rax, DWORD PTR nStringLen$[rsp]
	mov	rcx, QWORD PTR b$[rsp]
	add	rcx, rax
	mov	rax, rcx
	mov	QWORD PTR b$[rsp], rax
$LN3@DoEditInse:
$LN4@DoEditInse:
$LN8@DoEditInse:
$LN15@DoEditInse:

; 2058 :               }
; 2059 :             }
; 2060 :           }

	jmp	$LN76@DoEditInse
$LN24@DoEditInse:

; 2061 :           wszRange[a]='\0';

	xor	eax, eax
	mov	rcx, QWORD PTR wszRange$[rsp]
	mov	rdx, QWORD PTR a$[rsp]
	mov	WORD PTR [rcx+rdx*2], ax

; 2062 :           bResult=TRUE;

	mov	DWORD PTR bResult$[rsp], 1
$LN42@DoEditInse:
$LN43@DoEditInse:
$LN44@DoEditInse:

; 2063 :         }
; 2064 :       }
; 2065 : 
; 2066 :       if (bResult)

	cmp	DWORD PTR bResult$[rsp], 0
	je	$LN2@DoEditInse

; 2067 :       {
; 2068 :         ReplaceSelW(hWnd, wszRange, a, AELB_ASINPUT, (bColumnSel?AEREPT_COLUMNON:0)|AEREPT_LOCKSCROLL, &crRange.ciMin, &crRange.ciMax);

	cmp	DWORD PTR bColumnSel$[rsp], 0
	je	SHORT $LN69@DoEditInse
	mov	DWORD PTR tv474[rsp], 1
	jmp	SHORT $LN70@DoEditInse
$LN69@DoEditInse:
	mov	DWORD PTR tv474[rsp], 0
$LN70@DoEditInse:
	mov	eax, DWORD PTR tv474[rsp]
	or	eax, 4
	lea	rcx, QWORD PTR crRange$[rsp+24]
	mov	QWORD PTR [rsp+48], rcx
	lea	rcx, QWORD PTR crRange$[rsp]
	mov	QWORD PTR [rsp+40], rcx
	mov	DWORD PTR [rsp+32], eax
	mov	r9d, 1
	mov	r8, QWORD PTR a$[rsp]
	mov	rdx, QWORD PTR wszRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	ReplaceSelW

; 2069 :         SetSel(hWnd, &crRange, (bColumnSel?AESELT_COLUMNON:0)|AESELT_LOCKSCROLL, bCaretAtStart?&crRange.ciMin:&crRange.ciMax);

	cmp	DWORD PTR bCaretAtStart$[rsp], 0
	je	SHORT $LN71@DoEditInse
	lea	rax, QWORD PTR crRange$[rsp]
	mov	QWORD PTR tv482[rsp], rax
	jmp	SHORT $LN72@DoEditInse
$LN71@DoEditInse:
	lea	rax, QWORD PTR crRange$[rsp+24]
	mov	QWORD PTR tv482[rsp], rax
$LN72@DoEditInse:
	cmp	DWORD PTR bColumnSel$[rsp], 0
	je	SHORT $LN73@DoEditInse
	mov	DWORD PTR tv485[rsp], 1
	jmp	SHORT $LN74@DoEditInse
$LN73@DoEditInse:
	mov	DWORD PTR tv485[rsp], 0
$LN74@DoEditInse:
	mov	eax, DWORD PTR tv485[rsp]
	or	eax, 8
	mov	r9, QWORD PTR tv482[rsp]
	mov	r8d, eax
	lea	rdx, QWORD PTR crRange$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	SetSel
$LN2@DoEditInse:

; 2070 :       }
; 2071 : 
; 2072 :       //Restore scroll
; 2073 :       RestoreLineScroll(hWnd, nFirstLine);

	mov	edx, DWORD PTR nFirstLine$[rsp]
	mov	rcx, QWORD PTR hWnd$[rsp]
	call	RestoreLineScroll

; 2074 : 
; 2075 :       FreeWideStr(wszRange);

	mov	rcx, QWORD PTR wszRange$[rsp]
	call	FreeWideStr

; 2076 :       return bResult;

	mov	eax, DWORD PTR bResult$[rsp]
	jmp	SHORT $LN67@DoEditInse
$LN60@DoEditInse:
$LN64@DoEditInse:

; 2077 :     }
; 2078 :   }
; 2079 :   if (nAction & STRSEL_CHECK) return FALSE;

	mov	eax, DWORD PTR nAction$[rsp]
	and	eax, 1
	test	eax, eax
	je	SHORT $LN1@DoEditInse
	xor	eax, eax
	jmp	SHORT $LN67@DoEditInse
$LN1@DoEditInse:

; 2080 : 
; 2081 :   return TRUE;

	mov	eax, 1
$LN67@DoEditInse:

; 2082 : }

	add	rsp, 328				; 00000148H
	pop	rdi
	pop	rsi
	ret	0
DoEditInsertStringInSelectionW ENDP
