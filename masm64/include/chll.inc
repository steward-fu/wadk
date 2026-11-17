start proc <4> uses rdi rsi rbx
LOCAL CmdLine:LPSTR
	call GetCommandLine
	mov rbx,rax
	invoke ArgCount,rbx
	.if eax
		mov esi,eax
		lea rdi,[8*rax+8]
		.if rdi&0Fh
			add rdi,8
		.endif
		invoke strlen,rbx
		inc rax
		mov CmdLine,fn(malloc,rax)
		invoke strcpy,CmdLine,rbx
		sub rsp,rdi
		sub rsp,4*8
		invoke FillArgv,CmdLine,&[rsp+4*8+8]
		invoke EraseArgvDQuotes,esi,&[rsp+4*8+8]
		add rsp,4*8
		mov qptr [rsp+8][8*rsi],0
		invoke main,esi,rspArg2,rspArg3,rspArg4
		add rsp,rdi
		mov rdi,rax
		invoke free,CmdLine
		mov rax,rdi
	.else
		invoke main,eax,0
	.endif
	ret
start endp
FillArgv proc <0> CommandLine:LPSTR,pargv:LPPSTR
	xor eax,eax
	mov r8,rdx
	.if bptr [rcx]
		mov dl,' '
		mov r11b,TAB_CHAR
		.if bptr [rcx]=='"'
			mov dl,'"'
			mov r11b,'"'
			inc rcx
		.endif
		mov [r8],rcx
		add r8,8
		.repeat
			mov r10b,[rcx]
			.goto EndCount .if ~r10b
			inc rcx
		.until r10b==dl || r10b==r11b
		mov bptr [rcx-1],0
		.while TRUE
			.while TRUE
				mov dl,[rcx]
				.goto EndCount .if ~dl
				.break .if dl~=SPACE_CHAR && dl~=TAB_CHAR
				inc rcx
			.endw
			mov [r8],rcx
			add r8,8
			mov dh,0
			inc eax
			.while TRUE
				mov dl,[rcx]
				.goto EndCount .if ~dl
				.if ~dh
					.if dl==SPACE_CHAR || dl==TAB_CHAR
						mov bptr [rcx],0
						inc rcx
						.break
					.endif
					.if dl=='"'
						mov dh,1
					.endif
				.elseif dh==1
					.if dl=='"'
						mov dh,0
					.endif
				.endif
				inc rcx
			.endw
		.endw
	EndCount:
	.endif
	.if eax
		inc eax
	.endif
	ret
FillArgv endp
ArgCount proc <0> CommandLine:LPSTR
	xor eax,eax
	.if bptr [rcx]
		mov dl,' '
		mov r11b,TAB_CHAR
		.if bptr [rcx]=='"'
			mov dl,'"'
			mov r11b,'"'
			inc rcx
		.endif
		.repeat
			mov r10b,[rcx]
			.goto EndCount .if ~r10b
			inc rcx
		.until r10b==dl || r10b==r11b
		.while TRUE
			.while TRUE
				mov dl,[rcx]
				.goto EndCount .if ~dl
				.break .if dl~=SPACE_CHAR && dl~=TAB_CHAR
				inc rcx
			.endw
			mov dh,0
			inc eax
			.while TRUE
				mov dl,[rcx]
				.goto EndCount .if ~dl
				.if ~dh
					.break .if dl==SPACE_CHAR || dl==TAB_CHAR
					.if dl=='"'
						mov dh,1
					.endif
				.elseif dh==1
					.if dl=='"'
						mov dh,0
					.endif
				.endif
				inc rcx
			.endw
		.endw
	EndCount:
	.endif
	.if eax
		inc eax
	.endif
	ret
ArgCount endp
EraseArgvDQuotes proc <0> uses rbx rsi argc:DWORD,argv:LPPSTR
	mov esi,ecx
	mov rbx,rdx
	.if esi
		.repeat
			invoke EraseDQuotes,LPSTR ptr [rbx]
			add rbx,sizeof LPSTR
			dec esi
		.until ZERO?
	.endif
	ret
EraseArgvDQuotes endp
EraseDQuotes proc ;<0> QuotedString:LPSTR
	.if bptr [rcx]=='"'
		lea rax,[rcx+1]
		.repeat
			mov dl,[rax]
			mov [rcx],dl
			inc rax
			inc rcx
		.until ~dl
		.if bptr [rcx-2]=='"'
			mov bptr [rcx-2],0
		.endif
	.endif
	ret
EraseDQuotes endp