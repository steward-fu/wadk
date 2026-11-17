;¬–≈Ã≈ÕÕ€≈ Ã¿ –Œ—€ ¬€—Œ Œ”–Œ¬Õ≈¬Œ√Œ —»Õ“¿ —»—¿
;¬ ÕŒ¬€’ ¬≈–—»ﬂ’ ml64 ŒÕ» ¬Œ«ÃŒ∆ÕŒ ¡”ƒ”“ ¬—“–Œ≈ÕÕ€ 
;Œœ÷»ﬂ DOTNAME - Õ≈Œ¡’Œƒ»Ã¿
;	vasil211@yandex.ru
comment * Comparison run-time operators

     Operator      Meaning
 
     ==            Equal
     {}            Not equal
     }             Greater than
     }=            Greater than or equal to
     {             Less than
     {=            Less than or equal to
     &             Bit test (format: expression & bitnumber)
     ~             Logical NOT
     |	         Bit test
     &&            Logical AND

     ||            Logical OR
 
     CARRY?        Carry bit set
     OVERFLOW?     Overflow bit set
     PARITY?       Parity bit set
     SIGN?         Sign bit set
     ZERO?         Zero bit set
     CARRY?|ZERO?	ÏÂÌ¸ÌÂ ËÎË ‡‚ÌÓ
     ~(CARRY?|ZERO?)	·ÓÎ¸¯Â
     ‰Îˇ Ò‡‚ÌÂÌËˇ ˜ËÒÂÎ ÒÓ ÁÌ‡ÍÓÏ
     ~ZERO?&(SIGN?==OVERFLOW?)	·ÓÎ¸¯Â(greate than)
     SIGN?==OVERFLOW?		·ÓÎ¸¯Â ËÎË ‡‚ÌÓ(greate than or equal)
     SIGN?{}OVERFLOW?		ÏÂÌ¸¯Â(less than)
     ZERO?|(SIGN?{}OVERFLOW?)		ÏÂÌ¸¯Â ËÎË ‡‚ÌÓ(less than or equal)
*
ld macro ld_arg1,ld_arg2
	movst ld_arg1,ld_arg2
	EXITM<ld_arg1>
endm
lda macro ld_arg1
	movReg64Arg rax,ld_arg1
	EXITM<rax>
endm
ldea macro ld_arg1
	movReg32Arg eax,ld_arg1
	EXITM<eax>
endm
ldc macro ld_arg1
	movReg64Arg rcx,ld_arg1
	EXITM<rcx>
endm
ldd macro ld_arg1
	movReg64Arg rdx,ld_arg1
	EXITM<rdx>
endm
IMM_EXPR	equ 100b
MEM_EXPR	equ 10b
REG_EXPR	equ 10000b
LABEL_EXPR	equ 1b
VALID_REF	equ 100000b
DIRECT_ADDR	equ 1000b
VIMM_EXPR	equ (VALID_REF OR IMM_EXPR)
TAB_CHAR		equ 9
SPACE_CHAR		equ 20h
CR_CHAR			equ 13
LF_CHAR			equ 10
COMMA_CHAR		equ 2Ch
COLON_CHAR		equ 3Ah
SEMICOLON_CHAR	equ 3Bh
LEFT_PARENTHESES	equ 28h
RIGHT_PARENTHESES	equ 29h
EXCLAMATION_MARK	equ 21h
LEFT_ANGLE	equ 3Ch
RIGHT_ANGLE	equ 3Eh
LEFT_SLASH	equ 5Ch	;\
RIGHT_SLASH	equ 2Fh	;/
NOT_A_REG64	equ 16
NOT_A_REG32	equ 16
NOT_A_REG16	equ 16
NOT_A_REG8	equ 16
NOT_A_REG	equ 16
LOWER_MASK	equ 20202020h
SHORT_LOW	equ 2020h
LOW_CHAR	equ 20h
LT_CHAR	equ 3Ch
GT_CHAR	equ 3Eh
IFNDEF retn
retn MACRO stackBytes
	IFIDN <stackBytes>,<>
		db 0C3h
	ELSE
		db 0C2h
		dw stackBytes
	ENDIF
ENDM
retnw MACRO stackBytes
	db 66h
	retn stackBytes
ENDM
enterw MACRO toStackRes,lvlEmb
	dw 0C866h,toStackRes
	db lvlEmb
ENDM
leavew MACRO
	dw 0C966h
ENDM
ENDIF
TotalIfs = 0
TotalRept = 0
TotalWhile = 0
UntilConds0 TEXTEQU <>
UntilConds1 TEXTEQU <>
UntilConds2 TEXTEQU <>
UntilConds3 TEXTEQU <>
UntilConds4 TEXTEQU <>
UntilConds5 TEXTEQU <>
UntilConds6 TEXTEQU <>
UntilConds7 TEXTEQU <>
UntilConds8 TEXTEQU <>
UntilConds9 TEXTEQU <>
UntilConds10 TEXTEQU <>
UntilConds11 TEXTEQU <>
UntilConds12 TEXTEQU <>
UntilConds13 TEXTEQU <>
UntilConds14 TEXTEQU <>
UntilConds15 TEXTEQU <>
UntilConds16 TEXTEQU <>
UntilConds17 TEXTEQU <>
UntilConds18 TEXTEQU <>
UntilConds19 TEXTEQU <>
LastUntilConds TEXTEQU <>
SaveUntilCondsLabel MACRO
	IFIDN UntilConds0,<>
		UntilConds0 CATSTR <locconds0_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds0
	ELSEIFIDN UntilConds1,<> 
		UntilConds1 CATSTR <locconds1_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds1
	ELSEIFIDN UntilConds2,<>
		UntilConds2 CATSTR <locconds2_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds2
	ELSEIFIDN UntilConds3,<>
		UntilConds3 CATSTR <locconds3_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds3
	ELSEIFIDN UntilConds4,<>
		UntilConds4 CATSTR <locconds4_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds4
	ELSEIFIDN UntilConds5,<>
		UntilConds5 CATSTR <locconds5_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds5
	ELSEIFIDN UntilConds6,<>
		UntilConds6 CATSTR <locconds6_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds6
	ELSEIFIDN UntilConds7,<>
		UntilConds7 CATSTR <locconds7_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds7
	ELSEIFIDN UntilConds8,<>
		UntilConds8 CATSTR <locconds8_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds8
	ELSEIFIDN UntilConds9,<>
		UntilConds9 CATSTR <locconds9_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds9
	ELSEIFIDN UntilConds10,<>
		UntilConds10 CATSTR <locconds10_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds10
	ELSEIFIDN UntilConds11,<>
		UntilConds11 CATSTR <locconds11_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds11
	ELSEIFIDN UntilConds12,<>
		UntilConds12 CATSTR <locconds12_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds12
	ELSEIFIDN UntilConds13,<>
		UntilConds13 CATSTR <locconds13_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds13
	ELSEIFIDN UntilConds14,<>
		UntilConds14 CATSTR <locconds14_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds14
	ELSEIFIDN UntilConds15,<>
		UntilConds15 CATSTR <locconds15_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds15
	ELSEIFIDN UntilConds16,<>
		UntilConds16 CATSTR <locconds16_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds16
	ELSEIFIDN UntilConds17,<>
		UntilConds17 CATSTR <locconds17_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds17
	ELSEIFIDN UntilConds18,<>
		UntilConds18 CATSTR <locconds18_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds18
	ELSEIFIDN UntilConds19,<>
		UntilConds19 CATSTR <locconds19_>,@CatStr(%TotalWhile)
		LastUntilConds TEXTEQU UntilConds19
	ELSE
		.err <Too much nesting level.>
	ENDIF
	TotalWhile = TotalWhile+1
ENDM
GetUntilCondsLabel MACRO
	IFDIF UntilConds19,<>
		LastUntilConds TEXTEQU UntilConds19
	ELSEIFDIF UntilConds18,<>
		LastUntilConds TEXTEQU UntilConds18
	ELSEIFDIF UntilConds17,<>
		LastUntilConds TEXTEQU UntilConds17
	ELSEIFDIF UntilConds16,<>
		LastUntilConds TEXTEQU UntilConds16
	ELSEIFDIF UntilConds15,<>
		LastUntilConds TEXTEQU UntilConds15
	ELSEIFDIF UntilConds14,<>
		LastUntilConds TEXTEQU UntilConds14
	ELSEIFDIF UntilConds13,<>
		LastUntilConds TEXTEQU UntilConds13	
	ELSEIFDIF UntilConds12,<>
		LastUntilConds TEXTEQU UntilConds12
	ELSEIFDIF UntilConds11,<>
		LastUntilConds TEXTEQU UntilConds11	
	ELSEIFDIF UntilConds10,<>
		LastUntilConds TEXTEQU UntilConds10
	ELSEIFDIF UntilConds9,<>
		LastUntilConds TEXTEQU UntilConds9
	ELSEIFDIF UntilConds8,<>
		LastUntilConds TEXTEQU UntilConds8
	ELSEIFDIF UntilConds7,<>
		LastUntilConds TEXTEQU UntilConds7
	ELSEIFDIF UntilConds6,<>
		LastUntilConds TEXTEQU UntilConds6
	ELSEIFDIF UntilConds5,<>
		LastUntilConds TEXTEQU UntilConds5
	ELSEIFDIF UntilConds4,<>
		LastUntilConds TEXTEQU UntilConds4
	ELSEIFDIF UntilConds3,<>
		LastUntilConds TEXTEQU UntilConds3	
	ELSEIFDIF UntilConds2,<>
		LastUntilConds TEXTEQU UntilConds2
	ELSEIFDIF UntilConds1,<>
		LastUntilConds TEXTEQU UntilConds1	
	ELSEIFDIF UntilConds0,<>
		LastUntilConds TEXTEQU UntilConds0
	ELSE
		LastUntilConds TEXTEQU <>
	ENDIF		
ENDM
DelUntilCondsLabel MACRO
	IFDIF UntilConds19,<>
		UntilConds19 TEXTEQU <>
	ELSEIFDIF UntilConds18,<>
		UntilConds18 TEXTEQU <>
	ELSEIFDIF UntilConds17,<>
		UntilConds17 TEXTEQU <>
	ELSEIFDIF UntilConds16,<>
		UntilConds16 TEXTEQU <>
	ELSEIFDIF UntilConds15,<>
		UntilConds15 TEXTEQU <>
	ELSEIFDIF UntilConds14,<>
		UntilConds14 TEXTEQU <>
	ELSEIFDIF UntilConds13,<>
		UntilConds13 TEXTEQU <>	
	ELSEIFDIF UntilConds12,<>
		UntilConds12 TEXTEQU <>
	ELSEIFDIF UntilConds11,<>
		UntilConds11 TEXTEQU <>	
	ELSEIFDIF UntilConds10,<>
		UntilConds10 TEXTEQU <>
	ELSEIFDIF UntilConds9,<>
		UntilConds9 TEXTEQU <>
	ELSEIFDIF UntilConds8,<>
		UntilConds8 TEXTEQU <>
	ELSEIFDIF UntilConds7,<>
		UntilConds7 TEXTEQU <>
	ELSEIFDIF UntilConds6,<>
		UntilConds6 TEXTEQU <>
	ELSEIFDIF UntilConds5,<>
		UntilConds5 TEXTEQU <>
	ELSEIFDIF UntilConds4,<>
		UntilConds4 TEXTEQU <>
	ELSEIFDIF UntilConds3,<>
		UntilConds3 TEXTEQU <>	
	ELSEIFDIF UntilConds2,<>
		UntilConds2 TEXTEQU <>
	ELSEIFDIF UntilConds1,<>
		UntilConds1 TEXTEQU <>	
	ELSEIFDIF UntilConds0,<>
		UntilConds0 TEXTEQU <>
	ENDIF
ENDM
UntilLevel0 TEXTEQU <>
UntilLevel1 TEXTEQU <>
UntilLevel2 TEXTEQU <>
UntilLevel3 TEXTEQU <>
UntilLevel4 TEXTEQU <>
UntilLevel5 TEXTEQU <>
UntilLevel6 TEXTEQU <>
UntilLevel7 TEXTEQU <>
UntilLevel8 TEXTEQU <>
UntilLevel9 TEXTEQU <>
UntilLevel10 TEXTEQU <>
UntilLevel11 TEXTEQU <>
UntilLevel12 TEXTEQU <>
UntilLevel13 TEXTEQU <>
UntilLevel14 TEXTEQU <>
UntilLevel15 TEXTEQU <>
UntilLevel16 TEXTEQU <>
UntilLevel17 TEXTEQU <>
UntilLevel18 TEXTEQU <>
UntilLevel19 TEXTEQU <>
LastUntilLabel TEXTEQU <>
SaveUntilLabel MACRO
	IFIDN UntilLevel0,<>
		UntilLevel0 CATSTR <locuntil0_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel0
	ELSEIFIDN UntilLevel1,<> 
		UntilLevel1 CATSTR <locuntil1_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel1
	ELSEIFIDN UntilLevel2,<> 
		UntilLevel2 CATSTR <locuntil2_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel2
	ELSEIFIDN UntilLevel3,<> 
		UntilLevel3 CATSTR <locuntil3_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel3
	ELSEIFIDN UntilLevel4,<> 
		UntilLevel4 CATSTR <locuntil4_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel4
	ELSEIFIDN UntilLevel5,<> 
		UntilLevel5 CATSTR <locuntil5_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel5
	ELSEIFIDN UntilLevel6,<> 
		UntilLevel6 CATSTR <locuntil6_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel6
	ELSEIFIDN UntilLevel7,<> 
		UntilLevel7 CATSTR <locuntil7_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel7
	ELSEIFIDN UntilLevel8,<> 
		UntilLevel8 CATSTR <locuntil8_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel8
	ELSEIFIDN UntilLevel9,<> 
		UntilLevel9 CATSTR <locuntil9_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel9
	ELSEIFIDN UntilLevel10,<>
		UntilLevel10 CATSTR <locuntil10_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel10
	ELSEIFIDN UntilLevel11,<> 
		UntilLevel11 CATSTR <locuntil11_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel11
	ELSEIFIDN UntilLevel12,<> 
		UntilLevel12 CATSTR <locuntil12_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel12
	ELSEIFIDN UntilLevel13,<> 
		UntilLevel13 CATSTR <locuntil13_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel13
	ELSEIFIDN UntilLevel14,<> 
		UntilLevel14 CATSTR <locuntil14_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel14
	ELSEIFIDN UntilLevel15,<> 
		UntilLevel15 CATSTR <locuntil15_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel15
	ELSEIFIDN UntilLevel16,<> 
		UntilLevel16 CATSTR <locuntil16_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel16
	ELSEIFIDN UntilLevel17,<> 
		UntilLevel17 CATSTR <locuntil17_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel17
	ELSEIFIDN UntilLevel18,<> 
		UntilLevel18 CATSTR <locuntil18_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel18
	ELSEIFIDN UntilLevel19,<> 
		UntilLevel19 CATSTR <locuntil19_>,@CatStr(%TotalRept)
		LastUntilLabel TEXTEQU UntilLevel19
	ELSE
		.err <Too much nesting level.>
	ENDIF
	TotalRept = TotalRept+1
ENDM
GetUntilLabel MACRO
	IFDIF UntilLevel19,<>
		LastUntilLabel TEXTEQU UntilLevel19
	ELSEIFDIF UntilLevel18,<>
		LastUntilLabel TEXTEQU UntilLevel18
	ELSEIFDIF UntilLevel17,<>
		LastUntilLabel TEXTEQU UntilLevel17
	ELSEIFDIF UntilLevel16,<>
		LastUntilLabel TEXTEQU UntilLevel16
	ELSEIFDIF UntilLevel15,<>
		LastUntilLabel TEXTEQU UntilLevel15
	ELSEIFDIF UntilLevel14,<>
		LastUntilLabel TEXTEQU UntilLevel14
	ELSEIFDIF UntilLevel13,<>
		LastUntilLabel TEXTEQU UntilLevel13	
	ELSEIFDIF UntilLevel12,<>
		LastUntilLabel TEXTEQU UntilLevel12
	ELSEIFDIF UntilLevel11,<>
		LastUntilLabel TEXTEQU UntilLevel11	
	ELSEIFDIF UntilLevel10,<>
		LastUntilLabel TEXTEQU UntilLevel10
	ELSEIFDIF UntilLevel9,<>
		LastUntilLabel TEXTEQU UntilLevel9
	ELSEIFDIF UntilLevel8,<>
		LastUntilLabel TEXTEQU UntilLevel8
	ELSEIFDIF UntilLevel7,<>
		LastUntilLabel TEXTEQU UntilLevel7
	ELSEIFDIF UntilLevel6,<>
		LastUntilLabel TEXTEQU UntilLevel6
	ELSEIFDIF UntilLevel5,<>
		LastUntilLabel TEXTEQU UntilLevel5
	ELSEIFDIF UntilLevel4,<>
		LastUntilLabel TEXTEQU UntilLevel4
	ELSEIFDIF UntilLevel3,<>
		LastUntilLabel TEXTEQU UntilLevel3	
	ELSEIFDIF UntilLevel2,<>
		LastUntilLabel TEXTEQU UntilLevel2
	ELSEIFDIF UntilLevel1,<>
		LastUntilLabel TEXTEQU UntilLevel1	
	ELSEIFDIF UntilLevel0,<>
		LastUntilLabel TEXTEQU UntilLevel0
	ELSE
		LastUntilLabel TEXTEQU <>
	ENDIF		
ENDM
DelUntilLabel MACRO
	IFDIF UntilLevel19,<>
		UntilLevel19 TEXTEQU <>
	ELSEIFDIF UntilLevel18,<>
		UntilLevel18 TEXTEQU <>
	ELSEIFDIF UntilLevel17,<>
		UntilLevel17 TEXTEQU <>
	ELSEIFDIF UntilLevel16,<>
		UntilLevel16 TEXTEQU <>
	ELSEIFDIF UntilLevel15,<>
		UntilLevel15 TEXTEQU <>
	ELSEIFDIF UntilLevel14,<>
		UntilLevel14 TEXTEQU <>
	ELSEIFDIF UntilLevel13,<>
		UntilLevel13 TEXTEQU <>	
	ELSEIFDIF UntilLevel12,<>
		UntilLevel12 TEXTEQU <>
	ELSEIFDIF UntilLevel11,<>
		UntilLevel11 TEXTEQU <>	
	ELSEIFDIF UntilLevel10,<>
		UntilLevel10 TEXTEQU <>
	ELSEIFDIF UntilLevel9,<>
		UntilLevel9 TEXTEQU <>
	ELSEIFDIF UntilLevel8,<>
		UntilLevel8 TEXTEQU <>
	ELSEIFDIF UntilLevel7,<>
		UntilLevel7 TEXTEQU <>
	ELSEIFDIF UntilLevel6,<>
		UntilLevel6 TEXTEQU <>
	ELSEIFDIF UntilLevel5,<>
		UntilLevel5 TEXTEQU <>
	ELSEIFDIF UntilLevel4,<>
		UntilLevel4 TEXTEQU <>
	ELSEIFDIF UntilLevel3,<>
		UntilLevel3 TEXTEQU <>	
	ELSEIFDIF UntilLevel2,<>
		UntilLevel2 TEXTEQU <>
	ELSEIFDIF UntilLevel1,<>
		UntilLevel1 TEXTEQU <>	
	ELSEIFDIF UntilLevel0,<>
		UntilLevel0 TEXTEQU <>
	ENDIF
ENDM
TotalRept = 0
UntilOut0 TEXTEQU <>
UntilOut1 TEXTEQU <>
UntilOut2 TEXTEQU <>
UntilOut3 TEXTEQU <>
UntilOut4 TEXTEQU <>
UntilOut5 TEXTEQU <>
UntilOut6 TEXTEQU <>
UntilOut7 TEXTEQU <>
UntilOut8 TEXTEQU <>
UntilOut9 TEXTEQU <>
UntilOut10 TEXTEQU <>
UntilOut11 TEXTEQU <>
UntilOut12 TEXTEQU <>
UntilOut13 TEXTEQU <>
UntilOut14 TEXTEQU <>
UntilOut15 TEXTEQU <>
UntilOut16 TEXTEQU <>
UntilOut17 TEXTEQU <>
UntilOut18 TEXTEQU <>
UntilOut19 TEXTEQU <>
LastUntilOutLabel TEXTEQU <>
SaveUntilOutLabel MACRO
	IFIDN UntilOut0,<>
		UntilOut0 CATSTR <locuntilout0_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut0
	ELSEIFIDN UntilOut1,<> 
		UntilOut1 CATSTR <locuntilout1_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut1
	ELSEIFIDN UntilOut2,<> 
		UntilOut2 CATSTR <locuntilout2_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut2
	ELSEIFIDN UntilOut3,<> 
		UntilOut3 CATSTR <locuntilout3_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut3
	ELSEIFIDN UntilOut4,<> 
		UntilOut4 CATSTR <locuntilout4_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut4
	ELSEIFIDN UntilOut5,<> 
		UntilOut5 CATSTR <locuntilout5_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut5
	ELSEIFIDN UntilOut6,<> 
		UntilOut6 CATSTR <locuntilout6_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut6
	ELSEIFIDN UntilOut7,<> 
		UntilOut7 CATSTR <locuntilout7_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut7
	ELSEIFIDN UntilOut8,<> 
		UntilOut8 CATSTR <locuntilout8_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut8
	ELSEIFIDN UntilOut9,<> 
		UntilOut9 CATSTR <locuntilout9_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut9
	ELSEIFIDN UntilOut10,<>
		UntilOut10 CATSTR <locuntilout10_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut10
	ELSEIFIDN UntilOut11,<> 
		UntilOut11 CATSTR <locuntilout11_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut11
	ELSEIFIDN UntilOut12,<> 
		UntilOut12 CATSTR <locuntilout12_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut12
	ELSEIFIDN UntilOut13,<> 
		UntilOut13 CATSTR <locuntilout13_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut13
	ELSEIFIDN UntilOut14,<> 
		UntilOut14 CATSTR <locuntilout14_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut14
	ELSEIFIDN UntilOut15,<> 
		UntilOut15 CATSTR <locuntilout15_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut15
	ELSEIFIDN UntilOut16,<> 
		UntilOut16 CATSTR <locuntilout16_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut16
	ELSEIFIDN UntilOut17,<> 
		UntilOut17 CATSTR <locuntilout17_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut17
	ELSEIFIDN UntilOut18,<> 
		UntilOut18 CATSTR <locuntilout18_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut18
	ELSEIFIDN UntilOut19,<> 
		UntilOut19 CATSTR <locuntilout19_>,@CatStr(%TotalRept)
		LastUntilOutLabel TEXTEQU UntilOut19
	ELSE
		.err <Too much nesting level.>
	ENDIF
ENDM
GetUntilOutLabel MACRO
	IFDIF UntilOut19,<>
		LastUntilOutLabel TEXTEQU UntilOut19
	ELSEIFDIF UntilOut18,<>
		LastUntilOutLabel TEXTEQU UntilOut18
	ELSEIFDIF UntilOut17,<>
		LastUntilOutLabel TEXTEQU UntilOut17
	ELSEIFDIF UntilOut16,<>
		LastUntilOutLabel TEXTEQU UntilOut16
	ELSEIFDIF UntilOut15,<>
		LastUntilOutLabel TEXTEQU UntilOut15
	ELSEIFDIF UntilOut14,<>
		LastUntilOutLabel TEXTEQU UntilOut14
	ELSEIFDIF UntilOut13,<>
		LastUntilOutLabel TEXTEQU UntilOut13	
	ELSEIFDIF UntilOut12,<>
		LastUntilOutLabel TEXTEQU UntilOut12
	ELSEIFDIF UntilOut11,<>
		LastUntilOutLabel TEXTEQU UntilOut11	
	ELSEIFDIF UntilOut10,<>
		LastUntilOutLabel TEXTEQU UntilOut10
	ELSEIFDIF UntilOut9,<>
		LastUntilOutLabel TEXTEQU UntilOut9
	ELSEIFDIF UntilOut8,<>
		LastUntilOutLabel TEXTEQU UntilOut8
	ELSEIFDIF UntilOut7,<>
		LastUntilOutLabel TEXTEQU UntilOut7
	ELSEIFDIF UntilOut6,<>
		LastUntilOutLabel TEXTEQU UntilOut6
	ELSEIFDIF UntilOut5,<>
		LastUntilOutLabel TEXTEQU UntilOut5
	ELSEIFDIF UntilOut4,<>
		LastUntilOutLabel TEXTEQU UntilOut4
	ELSEIFDIF UntilOut3,<>
		LastUntilOutLabel TEXTEQU UntilOut3	
	ELSEIFDIF UntilOut2,<>
		LastUntilOutLabel TEXTEQU UntilOut2
	ELSEIFDIF UntilOut1,<>
		LastUntilOutLabel TEXTEQU UntilOut1	
	ELSEIFDIF UntilOut0,<>
		LastUntilOutLabel TEXTEQU UntilOut0
	ELSE
		LastUntilOutLabel TEXTEQU <>
	ENDIF		
ENDM
DelUntilOutLabel MACRO
	IFDIF UntilOut19,<>
		UntilOut19 TEXTEQU <>
	ELSEIFDIF UntilOut18,<>
		UntilOut18 TEXTEQU <>
	ELSEIFDIF UntilOut17,<>
		UntilOut17 TEXTEQU <>
	ELSEIFDIF UntilOut16,<>
		UntilOut16 TEXTEQU <>
	ELSEIFDIF UntilOut15,<>
		UntilOut15 TEXTEQU <>
	ELSEIFDIF UntilOut14,<>
		UntilOut14 TEXTEQU <>
	ELSEIFDIF UntilOut13,<>
		UntilOut13 TEXTEQU <>	
	ELSEIFDIF UntilOut12,<>
		UntilOut12 TEXTEQU <>
	ELSEIFDIF UntilOut11,<>
		UntilOut11 TEXTEQU <>	
	ELSEIFDIF UntilOut10,<>
		UntilOut10 TEXTEQU <>
	ELSEIFDIF UntilOut9,<>
		UntilOut9 TEXTEQU <>
	ELSEIFDIF UntilOut8,<>
		UntilOut8 TEXTEQU <>
	ELSEIFDIF UntilOut7,<>
		UntilOut7 TEXTEQU <>
	ELSEIFDIF UntilOut6,<>
		UntilOut6 TEXTEQU <>
	ELSEIFDIF UntilOut5,<>
		UntilOut5 TEXTEQU <>
	ELSEIFDIF UntilOut4,<>
		UntilOut4 TEXTEQU <>
	ELSEIFDIF UntilOut3,<>
		UntilOut3 TEXTEQU <>	
	ELSEIFDIF UntilOut2,<>
		UntilOut2 TEXTEQU <>
	ELSEIFDIF UntilOut1,<>
		UntilOut1 TEXTEQU <>	
	ELSEIFDIF UntilOut0,<>
		UntilOut0 TEXTEQU <>
	ENDIF
ENDM
OutLevel0 TEXTEQU <>
OutLevel1 TEXTEQU <>
OutLevel2 TEXTEQU <>
OutLevel3 TEXTEQU <>
OutLevel4 TEXTEQU <>
OutLevel5 TEXTEQU <>
OutLevel6 TEXTEQU <>
OutLevel7 TEXTEQU <>
OutLevel8 TEXTEQU <>
OutLevel9 TEXTEQU <>
OutLevel10 TEXTEQU <>
OutLevel11 TEXTEQU <>
OutLevel12 TEXTEQU <>
OutLevel13 TEXTEQU <>
OutLevel14 TEXTEQU <>
OutLevel15 TEXTEQU <>
OutLevel16 TEXTEQU <>
OutLevel17 TEXTEQU <>
OutLevel18 TEXTEQU <>
OutLevel19 TEXTEQU <>
LastOutLabel TEXTEQU <>
SaveOutLabel MACRO
	IFIDN OutLevel0,<>
		OutLevel0 CATSTR <locout0_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel1,<> 
		OutLevel1 CATSTR <locout1_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel2,<> 
		OutLevel2 CATSTR <locout2_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel3,<> 
		OutLevel3 CATSTR <locout3_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel4,<> 
		OutLevel4 CATSTR <locout4_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel5,<> 
		OutLevel5 CATSTR <locout5_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel6,<> 
		OutLevel6 CATSTR <locout6_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel7,<> 
		OutLevel7 CATSTR <locout7_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel8,<> 
		OutLevel8 CATSTR <locout8_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel9,<> 
		OutLevel9 CATSTR <locout9_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel10,<>
		OutLevel10 CATSTR <locout10_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel11,<> 
		OutLevel11 CATSTR <locout11_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel12,<> 
		OutLevel12 CATSTR <locout12_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel13,<> 
		OutLevel13 CATSTR <locout13_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel14,<> 
		OutLevel14 CATSTR <locout14_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel15,<> 
		OutLevel15 CATSTR <locout15_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel16,<> 
		OutLevel16 CATSTR <locout16_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel17,<> 
		OutLevel17 CATSTR <locout17_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel18,<> 
		OutLevel18 CATSTR <locout18_>,@CatStr(%TotalIfs)
	ELSEIFIDN OutLevel19,<> 
		OutLevel19 CATSTR <locout19_>,@CatStr(%TotalIfs)
	ELSE
		.err <Too much nesting level.>
	ENDIF
ENDM
GetOutLabel MACRO
	IFDIF OutLevel19,<>
		LastOutLabel TEXTEQU OutLevel19
	ELSEIFDIF OutLevel18,<>
		LastOutLabel TEXTEQU OutLevel18
	ELSEIFDIF OutLevel17,<>
		LastOutLabel TEXTEQU OutLevel17
	ELSEIFDIF OutLevel16,<>
		LastOutLabel TEXTEQU OutLevel16
	ELSEIFDIF OutLevel15,<>
		LastOutLabel TEXTEQU OutLevel15
	ELSEIFDIF OutLevel14,<>
		LastOutLabel TEXTEQU OutLevel14
	ELSEIFDIF OutLevel13,<>
		LastOutLabel TEXTEQU OutLevel13	
	ELSEIFDIF OutLevel12,<>
		LastOutLabel TEXTEQU OutLevel12
	ELSEIFDIF OutLevel11,<>
		LastOutLabel TEXTEQU OutLevel11	
	ELSEIFDIF OutLevel10,<>
		LastOutLabel TEXTEQU OutLevel10
	ELSEIFDIF OutLevel9,<>
		LastOutLabel TEXTEQU OutLevel9
	ELSEIFDIF OutLevel8,<>
		LastOutLabel TEXTEQU OutLevel8
	ELSEIFDIF OutLevel7,<>
		LastOutLabel TEXTEQU OutLevel7
	ELSEIFDIF OutLevel6,<>
		LastOutLabel TEXTEQU OutLevel6
	ELSEIFDIF OutLevel5,<>
		LastOutLabel TEXTEQU OutLevel5
	ELSEIFDIF OutLevel4,<>
		LastOutLabel TEXTEQU OutLevel4
	ELSEIFDIF OutLevel3,<>
		LastOutLabel TEXTEQU OutLevel3	
	ELSEIFDIF OutLevel2,<>
		LastOutLabel TEXTEQU OutLevel2
	ELSEIFDIF OutLevel1,<>
		LastOutLabel TEXTEQU OutLevel1	
	ELSEIFDIF OutLevel0,<>
		LastOutLabel TEXTEQU OutLevel0
	ELSE
		LastOutLabel TEXTEQU <>
	ENDIF		
ENDM
DelOutLabel MACRO
	IFDIF OutLevel19,<>
		OutLevel19 TEXTEQU <>
	ELSEIFDIF OutLevel18,<>
		OutLevel18 TEXTEQU <>
	ELSEIFDIF OutLevel17,<>
		OutLevel17 TEXTEQU <>
	ELSEIFDIF OutLevel16,<>
		OutLevel16 TEXTEQU <>
	ELSEIFDIF OutLevel15,<>
		OutLevel15 TEXTEQU <>
	ELSEIFDIF OutLevel14,<>
		OutLevel14 TEXTEQU <>
	ELSEIFDIF OutLevel13,<>
		OutLevel13 TEXTEQU <>	
	ELSEIFDIF OutLevel12,<>
		OutLevel12 TEXTEQU <>
	ELSEIFDIF OutLevel11,<>
		OutLevel11 TEXTEQU <>	
	ELSEIFDIF OutLevel10,<>
		OutLevel10 TEXTEQU <>
	ELSEIFDIF OutLevel9,<>
		OutLevel9 TEXTEQU <>
	ELSEIFDIF OutLevel8,<>
		OutLevel8 TEXTEQU <>
	ELSEIFDIF OutLevel7,<>
		OutLevel7 TEXTEQU <>
	ELSEIFDIF OutLevel6,<>
		OutLevel6 TEXTEQU <>
	ELSEIFDIF OutLevel5,<>
		OutLevel5 TEXTEQU <>
	ELSEIFDIF OutLevel4,<>
		OutLevel4 TEXTEQU <>
	ELSEIFDIF OutLevel3,<>
		OutLevel3 TEXTEQU <>	
	ELSEIFDIF OutLevel2,<>
		OutLevel2 TEXTEQU <>
	ELSEIFDIF OutLevel1,<>
		OutLevel1 TEXTEQU <>	
	ELSEIFDIF OutLevel0,<>
		OutLevel0 TEXTEQU <>
	ENDIF
ENDM
IfLevel0 TEXTEQU <>
IfLevel1 TEXTEQU <>
IfLevel2 TEXTEQU <>
IfLevel3 TEXTEQU <>
IfLevel4 TEXTEQU <>
IfLevel5 TEXTEQU <>
IfLevel6 TEXTEQU <>
IfLevel7 TEXTEQU <>
IfLevel8 TEXTEQU <>
IfLevel9 TEXTEQU <>
IfLevel10 TEXTEQU <>
IfLevel11 TEXTEQU <>
IfLevel12 TEXTEQU <>
IfLevel13 TEXTEQU <>
IfLevel14 TEXTEQU <>
IfLevel15 TEXTEQU <>
IfLevel16 TEXTEQU <>
IfLevel17 TEXTEQU <>
IfLevel18 TEXTEQU <>
IfLevel19 TEXTEQU <>
LastDefLabel TEXTEQU <>
SaveCurrentLabel MACRO
	IFIDN IfLevel0,<>
		IfLevel0 CATSTR <locif0_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel0
	ELSEIFIDN IfLevel1,<> 
		IfLevel1 CATSTR <locif1_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel1
	ELSEIFIDN IfLevel2,<> 
		IfLevel2 CATSTR <locif2_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel2
	ELSEIFIDN IfLevel3,<> 
		IfLevel3 CATSTR <locif3_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel3
	ELSEIFIDN IfLevel4,<> 
		IfLevel4 CATSTR <locif4_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel4
	ELSEIFIDN IfLevel5,<> 
		IfLevel5 CATSTR <locif5_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel5
	ELSEIFIDN IfLevel6,<> 
		IfLevel6 CATSTR <locif6_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel6
	ELSEIFIDN IfLevel7,<> 
		IfLevel7 CATSTR <locif7_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel7
	ELSEIFIDN IfLevel8,<> 
		IfLevel8 CATSTR <locif8_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel8
	ELSEIFIDN IfLevel9,<> 
		IfLevel9 CATSTR <locif9_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel9
	ELSEIFIDN IfLevel10,<>
		IfLevel10 CATSTR <locif10_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel10
	ELSEIFIDN IfLevel11,<> 
		IfLevel11 CATSTR <locif11_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel11
	ELSEIFIDN IfLevel12,<> 
		IfLevel12 CATSTR <locif12_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel12
	ELSEIFIDN IfLevel13,<> 
		IfLevel13 CATSTR <locif13_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel13
	ELSEIFIDN IfLevel14,<> 
		IfLevel14 CATSTR <locif14_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel14
	ELSEIFIDN IfLevel15,<> 
		IfLevel15 CATSTR <locif15_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel15
	ELSEIFIDN IfLevel16,<> 
		IfLevel16 CATSTR <locif16_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel16
	ELSEIFIDN IfLevel17,<> 
		IfLevel17 CATSTR <locif17_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel17
	ELSEIFIDN IfLevel18,<> 
		IfLevel18 CATSTR <locif18_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel18
	ELSEIFIDN IfLevel19,<> 
		IfLevel19 CATSTR <locif19_>,@CatStr(%TotalIfs)
		LastDefLabel TEXTEQU IfLevel19
	ELSE
		.err <Too much nesting level.>
	ENDIF
	TotalIfs = TotalIfs+1
ENDM
GetCurrentLabel MACRO
	IFDIF IfLevel19,<>
		LastDefLabel TEXTEQU IfLevel19
	ELSEIFDIF IfLevel18,<>
		LastDefLabel TEXTEQU IfLevel18
	ELSEIFDIF IfLevel17,<>
		LastDefLabel TEXTEQU IfLevel17
	ELSEIFDIF IfLevel16,<>
		LastDefLabel TEXTEQU IfLevel16
	ELSEIFDIF IfLevel15,<>
		LastDefLabel TEXTEQU IfLevel15
	ELSEIFDIF IfLevel14,<>
		LastDefLabel TEXTEQU IfLevel14
	ELSEIFDIF IfLevel13,<>
		LastDefLabel TEXTEQU IfLevel13	
	ELSEIFDIF IfLevel12,<>
		LastDefLabel TEXTEQU IfLevel12
	ELSEIFDIF IfLevel11,<>
		LastDefLabel TEXTEQU IfLevel11	
	ELSEIFDIF IfLevel10,<>
		LastDefLabel TEXTEQU IfLevel10
	ELSEIFDIF IfLevel9,<>
		LastDefLabel TEXTEQU IfLevel9
	ELSEIFDIF IfLevel8,<>
		LastDefLabel TEXTEQU IfLevel8
	ELSEIFDIF IfLevel7,<>
		LastDefLabel TEXTEQU IfLevel7
	ELSEIFDIF IfLevel6,<>
		LastDefLabel TEXTEQU IfLevel6
	ELSEIFDIF IfLevel5,<>
		LastDefLabel TEXTEQU IfLevel5
	ELSEIFDIF IfLevel4,<>
		LastDefLabel TEXTEQU IfLevel4
	ELSEIFDIF IfLevel3,<>
		LastDefLabel TEXTEQU IfLevel3	
	ELSEIFDIF IfLevel2,<>
		LastDefLabel TEXTEQU IfLevel2
	ELSEIFDIF IfLevel1,<>
		LastDefLabel TEXTEQU IfLevel1	
	ELSEIFDIF IfLevel0,<>
		LastDefLabel TEXTEQU IfLevel0
	ELSE
		LastDefLabel TEXTEQU <>
	ENDIF		
ENDM
DelCurrentLabel MACRO
	IFDIF IfLevel19,<>
		IfLevel19 TEXTEQU <>
	ELSEIFDIF IfLevel18,<>
		IfLevel18 TEXTEQU <>
	ELSEIFDIF IfLevel17,<>
		IfLevel17 TEXTEQU <>
	ELSEIFDIF IfLevel16,<>
		IfLevel16 TEXTEQU <>
	ELSEIFDIF IfLevel15,<>
		IfLevel15 TEXTEQU <>
	ELSEIFDIF IfLevel14,<>
		IfLevel14 TEXTEQU <>
	ELSEIFDIF IfLevel13,<>
		IfLevel13 TEXTEQU <>	
	ELSEIFDIF IfLevel12,<>
		IfLevel12 TEXTEQU <>
	ELSEIFDIF IfLevel11,<>
		IfLevel11 TEXTEQU <>	
	ELSEIFDIF IfLevel10,<>
		IfLevel10 TEXTEQU <>
	ELSEIFDIF IfLevel9,<>
		IfLevel9 TEXTEQU <>
	ELSEIFDIF IfLevel8,<>
		IfLevel8 TEXTEQU <>
	ELSEIFDIF IfLevel7,<>
		IfLevel7 TEXTEQU <>
	ELSEIFDIF IfLevel6,<>
		IfLevel6 TEXTEQU <>
	ELSEIFDIF IfLevel5,<>
		IfLevel5 TEXTEQU <>
	ELSEIFDIF IfLevel4,<>
		IfLevel4 TEXTEQU <>
	ELSEIFDIF IfLevel3,<>
		IfLevel3 TEXTEQU <>	
	ELSEIFDIF IfLevel2,<>
		IfLevel2 TEXTEQU <>
	ELSEIFDIF IfLevel1,<>
		IfLevel1 TEXTEQU <>	
	ELSEIFDIF IfLevel0,<>
		IfLevel0 TEXTEQU <>
	ENDIF
ENDM
;”—ÀŒ¬»ﬂ
.if MACRO args:VARARG
	SaveOutLabel
	SaveCurrentLabel
	J_POLY_COND LastDefLabel,FALSE,<args>
ENDM
.elseif MACRO args:VARARG
	GetOutLabel
	jmp LastOutLabel
	GetCurrentLabel
LastDefLabel:
	DelCurrentLabel
	SaveCurrentLabel
	J_POLY_COND LastDefLabel,FALSE,<args>	
ENDM
.nextif MACRO args:VARARG
	GetCurrentLabel
	J_POLY_COND LastDefLabel,TRUE,<args>
ENDM
.else MACRO
	GetOutLabel
	jmp LastOutLabel	
	GetCurrentLabel
LastDefLabel:
	DelCurrentLabel
	SaveCurrentLabel
ENDM
.endif MACRO
	GetCurrentLabel
LastDefLabel:
	DelCurrentLabel
	GetOutLabel
LastOutLabel:
	DelOutLabel
ENDM
;SaveUntilCondsLabel
;GetUntilCondsLabel
;DelUntilCondsLabel
while_cnt=0
.repeat MACRO
	while_cnt=while_cnt+1
	SaveUntilCondsLabel
	SaveUntilOutLabel
	SaveUntilLabel	
LastUntilLabel:
ENDM
j_test equ 1
.break MACRO args:VARARG
	GetUntilOutLabel
	IF @SizeStr(<args>) NE 0
		J_POLY_COND LastUntilOutLabel,TRUE,@SubStr(<args>,5,@SizeStr(<args>)-4)
		GOTO EndBreak		
	ELSE
		jmp LastUntilOutLabel
	ENDIF
:EndBreak
ENDM
.continue MACRO args:VARARG
	GetUntilCondsLabel
	IF @SizeStr(<args>) NE 0
		J_POLY_COND LastUntilConds,TRUE,@SubStr(<args>,5,@SizeStr(<args>)-4)		
	ELSE
		jmp LastUntilConds
	ENDIF
ENDM
.skip MACRO args:VARARG
	GetUntilLabel
	IF @SizeStr(<args>) NE 0
		J_POLY_COND LastUntilLabel,TRUE,@SubStr(<args>,5,@SizeStr(<args>)-4)		
	ELSE
		jmp LastUntilLabel
	ENDIF
ENDM
.until MACRO args:VARARG
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	IF @SizeStr(<args>) NE 0
		J_POLY_COND LastUntilLabel,FALSE,args
	ELSE
		jmp LastUntilLabel
	ENDIF
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1	
ENDM
.untilcxz MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loop LastUntilLabel
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM
.untilcxzd MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loopd LastUntilLabel
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM
.untilcxze MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loope LastUntilLabel
	DelUntilLabel	
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM
.untilcxzne MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loopne LastUntilLabel
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM
.untilcxzed MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	looped LastUntilLabel
	DelUntilLabel	
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM
.untilcxzned MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	loopned LastUntilLabel
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM
WhileLevel0 TEXTEQU <>
WhileLevel1 TEXTEQU <>
WhileLevel2 TEXTEQU <>
WhileLevel3 TEXTEQU <>
WhileLevel4 TEXTEQU <>
WhileLevel5 TEXTEQU <>
WhileLevel6 TEXTEQU <>
WhileLevel7 TEXTEQU <>
WhileLevel8 TEXTEQU <>
WhileLevel9 TEXTEQU <>
WhileLevel10 TEXTEQU <>
WhileLevel11 TEXTEQU <>
WhileLevel12 TEXTEQU <>
WhileLevel13 TEXTEQU <>
WhileLevel14 TEXTEQU <>
WhileLevel15 TEXTEQU <>
WhileLevel16 TEXTEQU <>
WhileLevel17 TEXTEQU <>
WhileLevel18 TEXTEQU <>
WhileLevel19 TEXTEQU <>
wcond0l=0
wcond1l=0
wcond2l=0
wcond3l=0
wcond4l=0
wcond5l=0
wcond6l=0
wcond7l=0
wcond8l=0
wcond9l=0
wcond10l=0
wcond11l=0
wcond12l=0
wcond13l=0
wcond14l=0
wcond15l=0
wcond16l=0
wcond17l=0
wcond18l=0
wcond19l=0
.while MACRO args:VARARG
	SaveUntilCondsLabel
	IFDIF <args>,<TRUE>
		jmp LastUntilConds
	ENDIF
	SaveUntilOutLabel
	SaveUntilLabel	
LastUntilLabel:
	while_cnt=while_cnt+1
	IF while_cnt EQ 1
		WhileLevel0 TEXTEQU <args>
		wcond0l SIZESTR <args>
	ELSEIF while_cnt EQ 2
		WhileLevel1 TEXTEQU <args>
		wcond1l SIZESTR <args>
	ELSEIF while_cnt EQ 3
		WhileLevel2 TEXTEQU <args>
		wcond2l SIZESTR <args>
	ELSEIF while_cnt EQ 4
		WhileLevel3 TEXTEQU <args>
		wcond3l SIZESTR <args>
	ELSEIF while_cnt EQ 5
		WhileLevel4 TEXTEQU <args>
		wcond4l SIZESTR <args>
	ELSEIF while_cnt EQ 6
		WhileLevel5 TEXTEQU <args>
		wcond5l SIZESTR <args>
	ELSEIF while_cnt EQ 7
		WhileLevel6 TEXTEQU <args>
		wcond6l SIZESTR <args>
	ELSEIF while_cnt EQ 8
		WhileLevel7 TEXTEQU <args>
		wcond7l SIZESTR <args>
	ELSEIF while_cnt EQ 9
		WhileLevel8 TEXTEQU <args>
		wcond8l SIZESTR <args>
	ELSEIF while_cnt EQ 10
		WhileLevel9 TEXTEQU <args>
		wcond9l SIZESTR <args>
	ELSEIF while_cnt EQ 11
		WhileLevel10 TEXTEQU <args>
		wcond10l SIZESTR <args>
	ELSEIF while_cnt EQ 12
		WhileLevel11 TEXTEQU <args>
		wcond11l SIZESTR <args>
	ELSEIF while_cnt EQ 13
		WhileLevel12 TEXTEQU <args>
		wcond12l SIZESTR <args>
	ELSEIF while_cnt EQ 14
		WhileLevel13 TEXTEQU <args>
		wcond13l SIZESTR <args>
	ELSEIF while_cnt EQ 15
		WhileLevel14 TEXTEQU <args>
		wcond14l SIZESTR <args>
	ELSEIF while_cnt EQ 16
		WhileLevel15 TEXTEQU <args>
		wcond15l SIZESTR <args>
	ELSEIF while_cnt EQ 17
		WhileLevel16 TEXTEQU <args>
		wcond16l SIZESTR <args>
	ELSEIF while_cnt EQ 18
		WhileLevel17 TEXTEQU <args>
		wcond17l SIZESTR <args>
	ELSEIF while_cnt EQ 19
		WhileLevel18 TEXTEQU <args>
		wcond18l SIZESTR <args>
	ELSEIF while_cnt EQ 20
		WhileLevel19 TEXTEQU <args>
		wcond19l SIZESTR <args>
	ELSE
		.err <Too much nesting level.>
	ENDIF
ENDM
.endw MACRO
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	IF (while_cnt EQ 1) AND (wcond0l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel0
	ELSEIF (while_cnt EQ 2) AND (wcond1l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel1
	ELSEIF (while_cnt EQ 3) AND (wcond2l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel2
	ELSEIF (while_cnt EQ 4) AND (wcond3l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel3
	ELSEIF (while_cnt EQ 5) AND (wcond4l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel4
	ELSEIF (while_cnt EQ 6) AND (wcond5l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel5
	ELSEIF (while_cnt EQ 7) AND (wcond6l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel6
	ELSEIF (while_cnt EQ 8) AND (wcond7l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel7
	ELSEIF (while_cnt EQ 9) AND (wcond8l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel8
	ELSEIF (while_cnt EQ 10) AND (wcond9l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel9
	ELSEIF (while_cnt EQ 11) AND (wcond10l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel10
	ELSEIF (while_cnt EQ 12) AND (wcond11l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel11
	ELSEIF (while_cnt EQ 13) AND (wcond12l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel12
	ELSEIF (while_cnt EQ 14) AND (wcond13l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel13
	ELSEIF (while_cnt EQ 15) AND (wcond14l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel14
	ELSEIF (while_cnt EQ 16) AND (wcond15l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel15
	ELSEIF (while_cnt EQ 17) AND (wcond16l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel16
	ELSEIF (while_cnt EQ 18) AND (wcond17l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel17
	ELSEIF (while_cnt EQ 19) AND (wcond18l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel18
	ELSEIF (while_cnt EQ 20) AND (wcond19l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel19
	ENDIF
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM
;¡” ¬¿ »À» ÷»‘–¿
IS_ALNUM MACRO char
CharPosition INSTR 1,<0123456789abcdefghijklmnopqrstvuwxyzABCDEFGHIJKLMNOPQRSTVUWXYZ>,<char>
	exitm <@CatStr(%CharPosition)>
ENDM
IS_INT_REG MACRO val
RegPosition INSTR 1,< rsi al bl cl dl ah bh ch dh sil dil bpl spl r8b r9b r10b r11b r12b r13b r14b r15b eax ebx ecx edx esi edi ebp esp r14d r15d >,<val>
	IF RegPosition EQ 0
		RegPosition INSTR 1,< rax rbx rdx rcx rsi rdi rbp rsp r8w r9w r10w r11w r12w r13w r14w r15w r8d r9d r10d r11d r12d r13d r8 r9 r10 r11 r12 r13 r14 r15 >,<val>
	ENDIF
	exitm <@CatStr(%RegPosition)>
ENDM
constStringsNum=0
regIndex=0
ItemLen=0
AddrArg TEXTEQU <>
constStr TEXTEQU <>
itemSize=0
reg32v TEXTEQU <>
movReg64Arg MACRO reg:REQ,item:REQ,____regIndex:=<NOT_A_REG64>
	IFDIF <reg>,<item>
		IF ____regIndex EQ NOT_A_REG64
			regIndex=Reg64Index(reg)
		ELSE
			regIndex=____regIndex
		ENDIF
		itemSize=8
		itemOpattr=0
		imm_nullification=0
		IF regIndex NE NOT_A_REG64
			ItemLen=@SizeStr(<item>)
			IF (ItemLen GE 6) and (@InStr(1,%ToLower(<item>),<addr >) EQ 1)
				AddrArg SUBSTR <item>,6,ItemLen-5
				lea reg,AddrArg
			ELSEIF (ItemLen GE 2) and (@InStr(1,<item>,<&>) EQ 1)
				AddrArg SUBSTR <item>,2,ItemLen-1
				lea reg,AddrArg
			ELSE
				IFIDN @SubStr(<item>,1,1),<">
					constStr	CATSTR <constString>,@CatStr(%constStringsNum)
					CONSTANT constStr db item,0
					lea reg,constStr
					constStringsNum=constStringsNum+1
				ELSE
					itemOpattr=OPATTR (item)
					IF itemOpattr and (MEM_EXPR or REG_EXPR)
						itemSize=TYPE (item)
						IF (itemSize EQ 8) or (itemSize EQ 0)
							mov reg,item
						ELSE
							reg32v	TEXTEQU <GetReg32(regIndex)>
							IF itemSize EQ 4
								mov reg32v,item
							ELSEIF (itemSize EQ 2) or (itemSize EQ 1)
								movzx reg32v,item
							ENDIF
						ENDIF
					ELSEIF itemOpattr and LABEL_EXPR
						mov reg,item
					ELSEIF itemOpattr and IMM_EXPR
						imm_nullification=4
						itemSize=TYPE (item)
						IF itemSize EQ 1
							reg32v	TEXTEQU <GetReg8(regIndex)>
							IF (item) EQ 0
								xor reg32v,reg32v
								imm_nullification=1
							ELSE
								mov reg32v,item
							ENDIF
						ELSEIF itemSize EQ 2
							reg32v	TEXTEQU <GetReg16(regIndex)>
							IF (item) EQ 0
								xor reg32v,reg32v
								imm_nullification=1
							ELSE
								mov reg32v,item
							ENDIF
						ELSEIF itemSize EQ 4
							reg32v	TEXTEQU <GetReg32(regIndex)>
							IF (item) EQ 0
								xor reg32v,reg32v
								imm_nullification=1
							ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFFFFFh)
								or reg32v,-1
							ELSE
								mov reg32v,item
							ENDIF
						ELSE
							imm_nullification=3
							IF (item) LT 0
								IF ((item) EQ -1) or ((item) EQ 0FFFFFFFFFFFFFFFFh)
									or reg,-1
								ELSE
									mov reg,item
								ENDIF
								itemSize=8
							ELSE
								itemSize=4
								reg32v	TEXTEQU <GetReg32(regIndex)>
								IF (item) EQ 0
									xor reg32v,reg32v
									imm_nullification=2
								ELSEIF ((item) EQ 0FFFFFFFFh)
									or reg32v,-1
								ELSEIF ((item) LE 0FFFFFFFEh)
									mov reg32v,item
								ELSE
									itemSize=8
									mov reg,item
								ENDIF
							ENDIF
						ENDIF
					ELSE
						mov reg,item
					ENDIF
				ENDIF
			ENDIF
		ELSE
			.err <NOT_A_REG64>
		ENDIF
	ENDIF
ENDM
movReg32Arg MACRO reg:REQ,item:REQ,____regIndex:=<NOT_A_REG32>
	IFDIF <reg>,<item>
		IF ____regIndex EQ NOT_A_REG32
			regIndex=Reg32Index(reg)
		ELSE
			regIndex=____regIndex
		ENDIF
		itemSize=4
		itemOpattr=0
		imm_nullification=0
		IF regIndex NE NOT_A_REG32
			ItemLen=@SizeStr(<item>)
			IF (ItemLen GE 6) and (@InStr(1,%ToLower(<item>),<addr >) EQ 1)
				AddrArg SUBSTR <item>,6,ItemLen-5
				lea reg,AddrArg
			ELSEIF (ItemLen GE 2) and (@InStr(1,<item>,<&>) EQ 1)
				AddrArg SUBSTR <item>,2,ItemLen-1
				lea reg,AddrArg
			ELSE
				IFIDN @SubStr(<item>,1,1),<">
					constStr	CATSTR <constString>,@CatStr(%constStringsNum)
					CONSTANT constStr db item,0
					lea reg,constStr
					constStringsNum=constStringsNum+1
				ELSE
					itemOpattr=OPATTR (item)
					IF itemOpattr and (MEM_EXPR or REG_EXPR)
						itemSize=TYPE (item)
							IF (itemSize EQ 4) or (itemSize EQ 0)
								mov reg,item
							ELSEIF (itemSize EQ 2) or (itemSize EQ 1)
								movzx reg,item
							ELSE
								mov reg,dword ptr item
							ENDIF
					ELSEIF itemOpattr and LABEL_EXPR
						mov reg,item
					ELSEIF itemOpattr and IMM_EXPR
						imm_nullification=4
						itemSize=TYPE (item)
						IF itemSize EQ 1
							IF (item) EQ 0
								xor reg,reg
								imm_nullification=1
							ELSE
								mov reg,item
							ENDIF
						ELSEIF itemSize EQ 2
							IF (item) EQ 0
								xor reg,reg
								imm_nullification=1
							ELSE
								mov reg,item
							ENDIF
						ELSEIF itemSize EQ 4
							IF (item) EQ 0
								xor reg,reg
								imm_nullification=1
							ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFFFFFh)
								or reg,-1
							ELSE
								mov reg,item
							ENDIF
						ELSE
							imm_nullification=3
							IF (item) LT 0
								IF ((item) EQ -1)
									or reg,-1
								ELSE
									mov reg,item
								ENDIF
								itemSize=4
							ELSE
								itemSize=4
								IF (item) EQ 0
									xor reg,reg
									imm_nullification=2
								ELSEIF ((item) LE 7FFFFFFFh)
									mov reg,item
								ELSE
									itemSize=4
									mov reg,item
								ENDIF
							ENDIF
						ENDIF
					ELSE
						mov reg,item
					ENDIF
				ENDIF
			ENDIF
		ELSE
			.err <NOT_A_REG32>
		ENDIF
	ENDIF
ENDM
movReg16Arg MACRO reg:REQ,item:REQ,____regIndex:=<NOT_A_REG16>
	IFDIF <reg>,<item>
		IF ____regIndex EQ NOT_A_REG16
			regIndex=Reg16Index(reg)
		ELSE
			regIndex=____regIndex
		ENDIF
		itemSize=2
		itemOpattr=0
		imm_nullification=0
		IF regIndex NE NOT_A_REG16
			ItemLen=@SizeStr(<item>)
			IF (ItemLen GE 6) and (@InStr(1,%ToLower(<item>),<addr >) EQ 1)
				AddrArg SUBSTR <item>,6,ItemLen-5
				lea reg,AddrArg
			ELSEIF (ItemLen GE 2) and (@InStr(1,<item>,<&>) EQ 1)
				AddrArg SUBSTR <item>,2,ItemLen-1
				lea reg,AddrArg
			ELSE
				IFIDN @SubStr(<item>,1,1),<">
					constStr	CATSTR <constString>,@CatStr(%constStringsNum)
					CONSTANT constStr db item,0
					lea reg,constStr
					constStringsNum=constStringsNum+1
				ELSE
					itemOpattr=OPATTR (item)
					IF itemOpattr and (MEM_EXPR or REG_EXPR)
						itemSize=TYPE (item)
							IF (itemSize EQ 2) or (itemSize EQ 0)
								mov reg,item
							ELSEIF (itemSize EQ 1)
								movzx reg,item
							ELSE
								mov reg,word ptr item
							ENDIF
					ELSEIF itemOpattr and LABEL_EXPR
						mov reg,item
					ELSEIF itemOpattr and IMM_EXPR
						imm_nullification=4
						itemSize=TYPE (item)
						IF itemSize EQ 1
							IF (item) EQ 0
								xor reg,reg
								imm_nullification=1
							ELSE
								mov reg,item
							ENDIF
						ELSEIF itemSize EQ 2
							IF (item) EQ 0
								xor reg,reg
								imm_nullification=1
							ELSE
								mov reg,item
							ENDIF
						ELSEIF itemSize EQ 4
							IF (item) EQ 0
								xor reg,reg
								imm_nullification=1
							ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFh)
								or reg,-1
							ELSE
								mov reg,item
							ENDIF
						ELSE
							imm_nullification=3
							IF (item) LT 0
								IF ((item) EQ -1)
									or reg,-1
								ELSE
									mov reg,item
								ENDIF
								itemSize=2
							ELSE
								itemSize=2
								IF (item) EQ 0
									xor reg,reg
									imm_nullification=2
								ELSEIF ((item) LE 7FFFh)
									mov reg,item
								ELSE
									itemSize=2
									mov reg,item
								ENDIF
							ENDIF
						ENDIF
					ELSE
						mov reg,item
					ENDIF
				ENDIF
			ENDIF
		ELSE
			.err <NOT_A_REG16>
		ENDIF
	ENDIF
ENDM
movMem64Arg MACRO mem64:REQ,item:REQ
LOCAL AddrArg,ItemLen
LOCAL constStr
	itemSize=8
	itemOpattr=0
	imm_nullification=0
	IFDIF <mem64>,<item>
		ItemLen=@SizeStr(<item>)
		IF (ItemLen GE 6) and (@InStr(1,%ToLower(<item>),<addr >) EQ 1)
			AddrArg SUBSTR <item>,6,ItemLen-5
			lea rax,AddrArg
			mov qword ptr mem64,rax
		ELSEIF (ItemLen GE 2) and (@InStr(1,<item>,<&>) EQ 1)
			AddrArg SUBSTR <item>,2,ItemLen-1
			lea rax,AddrArg
			mov qword ptr mem64,rax
		ELSE
			IFIDN @SubStr(<item>,1,1),<">
				constStr	CATSTR <constString>,@CatStr(%constStringsNum)
				CONSTANT constStr db item,0
				lea rax,constStr
				mov qword ptr mem64,rax
				constStringsNum=constStringsNum+1
			ELSE
				itemOpattr=OPATTR (item)
				IF itemOpattr and REG_EXPR
					itemSize=TYPE (item)
					IF itemSize EQ 8
						mov qword ptr mem64,item
					ELSEIF itemSize EQ 4
						mov dword ptr mem64,item
					ELSEIF itemSize EQ 2
						mov word ptr mem64,item
					ELSEIF itemSize EQ 1
						mov byte ptr mem64,item
					ENDIF
				ELSEIF itemOpattr and MEM_EXPR
					itemSize=TYPE (item)
					IF (itemSize EQ 8) or (itemSize EQ 0)
						mov rax,item
						mov qword ptr mem64,rax
					ELSEIF itemSize EQ 4
						mov eax,item
						mov dword ptr mem64,eax
					ELSEIF itemSize EQ 2
						mov ax,item
						mov word ptr mem64,ax
					ELSEIF itemSize EQ 1
						mov al,item
						mov byte ptr mem64,al
					ENDIF
				ELSEIF itemOpattr and LABEL_EXPR
					mov rax,item
					mov qword ptr mem64,rax
				ELSEIF itemOpattr and IMM_EXPR
					imm_nullification=4
					itemSize=TYPE (item)
					IF (itemSize EQ 0) or (itemSize EQ 8)
						imm_nullification=3
						IF (item) EQ 0
							and qword ptr mem64,0
							imm_nullification=2
						ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFFFFFFFFFFFFFh)
							or qword ptr mem64,-1
						ELSEIF ((item) GE -80000000h) AND ((item) LE 7FFFFFFFh)
							mov qword ptr mem64,item
						ELSE
							mov rax,item
							mov mem64,rax
						ENDIF
					ELSEIF itemSize EQ 2
						IF (item) EQ 0
							and word ptr mem64,0
							imm_nullification=1
						ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFh)
							or word ptr mem64,-1
						ELSE
							mov word ptr mem64,item
						ENDIF
					ELSEIF itemSize EQ 4
						IF (item) EQ 0
							and dword ptr mem64,0
							imm_nullification=1
						ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFFFFFh)
							or dword ptr mem64,-1
						ELSE
							mov dword ptr mem64,item
						ENDIF
					ELSE
						mov mem64,item
					ENDIF
				ELSE
					mov rax,item
					mov mem64,rax
				ENDIF
			ENDIF
		ENDIF
	ENDIF
ENDM
movst MACRO reg:REQ,item:REQ
	IFDIF <reg>,<item>
		movst_rid=Reg64Index(reg)
		IF movst_rid NE NOT_A_REG64
			movReg64Arg reg,item,movst_rid
		ELSE
			movst_rid=Reg32Index(reg)
			IF movst_rid NE NOT_A_REG32
				movReg32Arg reg,item,movst_rid
			ELSE
				movst_rid=Reg16Index(reg)
				IF movst_rid NE NOT_A_REG16
					movReg16Arg reg,item,movst_rid
				ELSE
					movst_rid=Reg8Index(reg)
					IF movst_rid NE NOT_A_REG8
						mov reg,item
					ELSE
						movMem64Arg reg,item
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ENDIF
ENDM
SetType MACRO mem64:REQ,item:REQ
LOCAL AddrArg,ItemLen
LOCAL constStr
	itemSize=8
	itemOpattr=0
	imm_nullification=0
	must_be_gt=1
	IFDIF <mem64>,<item>
		ItemLen=@SizeStr(<item>)
		IF (ItemLen GE 6) and (@InStr(1,%ToLower(<item>),<addr >) EQ 1)
			
		ELSEIF (ItemLen GE 2) and (@InStr(1,<item>,<&>) EQ 1)
			
		ELSE
			IFDIF @SubStr(<item>,1,1),<">
				itemOpattr=OPATTR (item)
				IF itemOpattr and REG_EXPR
					itemSize=TYPE (item)
				ELSEIF itemOpattr and MEM_EXPR
					itemSize=TYPE (item)
				ELSEIF itemOpattr and IMM_EXPR
					imm_nullification=4
					itemSize=TYPE (item)
					IF (itemSize EQ 0) or (itemSize EQ 8)
						imm_nullification=3
						IF (item) EQ 0
							imm_nullification=2
							must_be_gt=2
						ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFFFFFFFFFFFFFh)
							must_be_gt=4
						ENDIF
					ELSEIF itemSize EQ 2
						IF (item) EQ 0
							imm_nullification=1
							must_be_gt=2
						ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFh)
							must_be_gt=3
						ENDIF
					ELSEIF itemSize EQ 4
						IF (item) EQ 0
							imm_nullification=1
							must_be_gt=2
						ELSEIF ((item) EQ -1) or ((item) EQ 0FFFFFFFFh)
							must_be_gt=3
						ENDIF
					ELSEIF itemSize EQ 1
						IF (item) EQ 0
							imm_nullification=1
							must_be_gt=2
						ELSEIF ((item) EQ -1) or ((item) EQ 0FFh)
							must_be_gt=3
						ENDIF
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ENDIF
ENDM
fb MACRO FuncName:REQ,ArgumentList:VARARG
	IFIDN <ArgumentList>,<>
		call FuncName
	ELSE
		invoke FuncName,ArgumentList
	ENDIF
	EXITM<al>
ENDM
fw MACRO FuncName:REQ,ArgumentList:VARARG
	IFIDN <ArgumentList>,<>
		call FuncName
	ELSE
		invoke FuncName,ArgumentList
	ENDIF
	EXITM<ax>
ENDM
fd MACRO FuncName:REQ,ArgumentList:VARARG
	IFIDN <ArgumentList>,<>
		call FuncName
	ELSE
		invoke FuncName,ArgumentList
	ENDIF
	EXITM<eax>
ENDM
fn MACRO FuncName:REQ,ArgumentList:VARARG
	IFIDN <ArgumentList>,<>
		call FuncName
	ELSE
		invoke FuncName,ArgumentList
	ENDIF
	EXITM<rax>
ENDM
mrm MACRO FirstArgument:REQ,SecondArgument:REQ
	itemSize=TYPE (FirstArgument)
	IF itemSize EQ 1
		mov al,SecondArgument
		mov FirstArgument,al
	ELSEIF itemSize EQ 2
		itemSize=TYPE (SecondArgument)
		IF (itemSize EQ 2) or (itemSize EQ 0)
			mov ax,SecondArgument
			mov FirstArgument,ax
		ELSE
			movzx eax,SecondArgument
			mov FirstArgument,ax
		ENDIF
	ELSEIF itemSize EQ 4
		itemSize=TYPE (SecondArgument)
		IF (itemSize EQ 4) or (itemSize EQ 0)
			mov eax,SecondArgument
			mov FirstArgument,eax
		ELSE
			movzx eax,SecondArgument
			mov FirstArgument,eax
		ENDIF	
	ELSE
		movReg64Arg rax,SecondArgument
		mov FirstArgument,rax
	ENDIF
ENDM
return macro valopt
	IFDIF <valopt>,<>
		movReg64Arg rax,valopt
	ENDIF
	IF ((OPATTR (ToProcsReturnPoint)) AND VALID_REF)
		IF (RegCnt NE 0)
			jmp ToProcsReturnPoint
		ELSE
			ret
		ENDIF
	ELSE
	ToProcsReturnPoint:
		ret
	ENDIF
endm
register MACRO reg,item
TEX TEXTEQU <>
address TEXTEQU <>
IFDIF <reg>,<item>
	IF @SizeStr(<item>) GE 6
		TEX SUBSTR <item>,1,4
		address SUBSTR <item>, 6, @SizeStr(<item>) - 5
		IFIDN TEX,<addr>
			lea reg,address
		ELSEIFIDN TEX,<ADDR>
			lea reg,address
		ELSEIFIDN TEX,<Addr>
			lea reg,address
		ELSE
			mov reg,item
		ENDIF
	ELSE
		mov reg,item
	ENDIF
ENDIF
ENDM
ToUpper MACRO String:VARARG
LOCAL UpperStr,LowNum
	UpperStr TEXTEQU <>
%	FORC char,<String>
		LowNum INSTR 1,<abcdefghijklmnopqrstuvwxyz>,<char>
		IF LowNum NE 0
			UpperStr CATSTR UpperStr,@SubStr(<ABCDEFGHIJKLMNOPQRSTUVWXYZ>,LowNum,1)
		ELSE
			UpperStr CATSTR UpperStr,<char>
		ENDIF
	ENDM
	EXITM <UpperStr>
ENDM
ToLower MACRO String:VARARG
LOCAL UpperStr,LowNum
	UpperStr TEXTEQU <>
%	FORC char,<String>
		LowNum INSTR 1,<ABCDEFGHIJKLMNOPQRSTUVWXYZ>,<char>
		IF LowNum NE 0
			UpperStr CATSTR UpperStr,@SubStr(<abcdefghijklmnopqrstuvwxyz>,LowNum,1)
		ELSE
			UpperStr CATSTR UpperStr,<char>
		ENDIF
	ENDM
	EXITM <UpperStr>
ENDM
JustLeaveFrame = 0
leavef MACRO
	JustLeaveFrame = 1
	ret
	JustLeaveFrame = 0
ENDM
altm MACRO Consts:VARARG 
    EXITM <>
ENDM
rbpFrame=0
rspFrame=0
rbpFirstArgBias=0
userParmsHandler MACRO mips:=<7>,save_rcx:=<0>,save_rdx:=<0>,save_r8:=<0>,save_r9:=<0>
    MaxInvokeParms=mips
	SaveRCX=save_rcx
	SaveRDX=save_rdx
	SaveR8=save_r8
	SaveR9=save_r9
ENDM
SaveRegArgs MACRO
	IF SaveRCX EQ 1
		mov [rbp+10h],cl
	ELSEIF SaveRCX EQ 2
		mov [rbp+10h],cx
	ELSEIF SaveRCX EQ 4
		mov [rbp+10h],ecx
	ELSEIF SaveRCX EQ 8
		mov [rbp+10h],rcx
	ENDIF
	IF SaveRDX EQ 1
		mov [rbp+18h],dl
	ELSEIF SaveRDX EQ 2
		mov [rbp+18h],dx
	ELSEIF SaveRDX EQ 4
		mov [rbp+18h],edx
	ELSEIF SaveRDX EQ 8
		mov [rbp+18h],rdx
	ENDIF
	IF SaveR8 EQ 1
		mov [rbp+20h],r8b
	ELSEIF SaveR8 EQ 2
		mov [rbp+20h],r8w
	ELSEIF SaveR8 EQ 4
		mov [rbp+20h],r8d
	ELSEIF SaveR8 EQ 8
		mov [rbp+20h],r8
	ENDIF
	IF SaveR9 EQ 1
		mov [rbp+28h],r9b
	ELSEIF SaveR9 EQ 2
		mov [rbp+28h],r9w
	ELSEIF SaveR9 EQ 4
		mov [rbp+28h],r9d
	ELSEIF SaveR9 EQ 8
		mov [rbp+28h],r9
	ENDIF
ENDM
rbpFramePrologue MACRO procname,flags,argbytes,localbytes,reglist,userparms:VARARG
	RegCnt=0
	IFNB <reglist>
	    FOR reg,reglist
	    	RegCnt=RegCnt+1
	    ENDM
    ENDIF
    userParmsHandler userparms
    allbytes=localbytes+8*(RegCnt+MaxInvokeParms)
    IF (allbytes AND 7) NE 0
    	allbytes=allbytes-(allbytes AND 7)+8
    ENDIF
    IF (allbytes AND 8) NE 0
    	allbytes=allbytes+8
    ENDIF
    IF (localbytes+argbytes-8) EQ 0
		IFDIF reglist,<>
			FOR reg,reglist
				push reg
			ENDM
			allbytes=8*(RegCnt+MaxInvokeParms)
			IF (allbytes AND 8) EQ 0
				allbytes=(8*MaxInvokeParms)+8
			ELSE
				allbytes=8*MaxInvokeParms
			ENDIF
			IF allbytes LE 4096
				sub rsp,allbytes
			ELSE
				IFDEF __chkstk
					mov rax,allbytes
					call __chkstk
					sub rsp,rax
				ELSE
					sub rsp,allbytes
				ENDIF
			ENDIF
		ENDIF
		rbpFrame=2
		rspFrame=1
	ELSEIF allbytes LE 4096
		rbpFrame=1
		rspFrame=0
		enter allbytes,0
		rbpFirstArgBias=allbytes
		allbytes=allbytes-8*MaxInvokeParms
		IFNB <reglist>
			FOR reg,reglist
				mov [rbp-allbytes],reg
				allbytes=allbytes-8
			ENDM
		ENDIF
		SaveRegArgs
	ELSE
		rbpFrame=1
		rspFrame=0
		push rbp
		mov rbp,rsp
		IFDEF __chkstk
			mov rax,allbytes
			call __chkstk
			sub rsp,rax
		ELSE
			sub rsp,allbytes
		ENDIF
		rbpFirstArgBias=allbytes
		allbytes=allbytes-8*MaxInvokeParms
		IFNB <reglist>
			FOR reg,reglist
				mov [rbp-allbytes],reg
				allbytes=allbytes-8
			ENDM
		ENDIF
		SaveRegArgs
    ENDIF  
	EXITM <localbytes>
ENDM
rbpFrameEpilogue MACRO procname,flags,argbytes,localbytes,reglist,userparms:VARARG
	RegCnt=0
	IFNB <reglist>
	    FOR reg,reglist
	    	RegCnt=RegCnt+1
	    ENDM
    ENDIF
    userParmsHandler userparms
    allbytes=localbytes+8*(RegCnt+MaxInvokeParms)
    IF (allbytes AND 7) NE 0
    	allbytes=allbytes-(allbytes AND 7)+8
    ENDIF
    IF (allbytes AND 8) NE 0
    	allbytes=allbytes+8
    ENDIF
    IF (localbytes+argbytes-8) EQ 0
		allbytes=8*(RegCnt+MaxInvokeParms)
		IF (allbytes AND 8) EQ 0
			allbytes=(8*MaxInvokeParms)+8
		ELSE
			allbytes=8*MaxInvokeParms
		ENDIF
		IFDIF reglist,<>
			add rsp,allbytes
			FOR reg,reglist
				pop reg
			ENDM
		ENDIF	
	ELSE
		allbytes=allbytes-8*(MaxInvokeParms+RegCnt)
		IFNB <reglist>
			FOR reg,reglist
				allbytes=allbytes+8
				mov reg,[rbp-allbytes]
			ENDM
		ENDIF
		leave
    ENDIF
    IF JustLeaveFrame EQ 0
		db 0C3h
	ENDIF
ENDM
StdPrologue MACRO procname, flags, argbytes, localbytes, reglist, userparms:VARARG
pushed_regs=0
FillStack = 1
;;%echo @CatStr(%argbytes)
	IF (localbytes LT 4096) AND (localbytes NE 0)
		enter localbytes,0
	ELSEIF localbytes NE 0
        push rbp
        mov rbp,rsp
        sub rsp,localbytes
    ELSEIF argbytes GT 8
    	enter 0,0
    ENDIF
    ;; USES clause
    IFNB <reglist>
        FOR reg,reglist
        	pushed_regs=pushed_regs+1
            push reg
        ENDM
    ENDIF    
    IFNB <userparms>
    	IF (localbytes EQ 0) AND (argbytes EQ 0)
    		IF (8*(userparms+pushed_regs) AND 8) EQ 0
      			sub rsp,8*userparms+8
      		ELSE
      			sub rsp,8*userparms
      		ENDIF
      	ELSE
      		IF ((8*(userparms+pushed_regs)+localbytes) AND 8) EQ 0
      			sub rsp,8*userparms
      		ELSE
      			sub rsp,8*userparms+8
      		ENDIF
      	ENDIF
    ENDIF
    EXITM <localbytes>
endm
StdEpilogue MACRO procname, flags, argbytes, localbytes, reglist, userparms:VARARG
FillStack = 0
    IFNB <userparms>
    	IF (localbytes EQ 0) AND (argbytes EQ 0)
    		IF (8*(userparms+pushed_regs) AND 8) EQ 0
      			add rsp,8*userparms+8
      		ELSE
      			add rsp,8*userparms
      		ENDIF
      	ELSE
      		IF ((8*(userparms+pushed_regs)+localbytes) AND 8) EQ 0
      			add rsp,8*userparms
      		ELSE
      			add rsp,8*userparms+8
      		ENDIF
      	ENDIF
    ENDIF
    IFNB <reglist>
        FOR reg,reglist
            pop reg
        ENDM
    ENDIF
    IF (argbytes GT 8) OR (localbytes GT 0)
        leave
	ENDIF
	db 0C3h
ENDM
MaxArgs MACRO ArgsNum
	sub rsp,8*ArgsNum
	.if rsp&0Fh
		sub rsp,8
	.endif
ENDM
FillStack = 1
rbpArg14	equ <[rbp-rbpFirstArgBias+8*14-8]>
rbpArg13	equ <[rbp-rbpFirstArgBias+8*13-8]>
rbpArg12	equ <[rbp-rbpFirstArgBias+8*12-8]>
rbpArg11	equ <[rbp-rbpFirstArgBias+8*11-8]>
rbpArg10	equ <[rbp-rbpFirstArgBias+8*10-8]>
rbpArg9		equ <[rbp-rbpFirstArgBias+8*9-8]>
rbpArg8		equ <[rbp-rbpFirstArgBias+8*8-8]>
rbpArg7		equ <[rbp-rbpFirstArgBias+8*7-8]>
rbpArg6		equ <[rbp-rbpFirstArgBias+8*6-8]>
rbpArg5		equ <[rbp-rbpFirstArgBias+8*5-8]>
rbpArg4		equ <[rbp-rbpFirstArgBias+8*4-8]>
rbpArg3		equ <[rbp-rbpFirstArgBias+8*3-8]>
rbpArg2		equ <[rbp-rbpFirstArgBias+8*2-8]>
rbpArg1		equ <[rbp-rbpFirstArgBias+8*1-8]>
rspBorder	= 0A8h
rspArg14	equ <[rsp+8*14-8]>
rspArg13	equ <[rsp+8*13-8]>
rspArg12	equ <[rsp+8*12-8]>
rspArg11	equ <[rsp+8*11-8]>
rspArg10	equ <[rsp+8*10-8]>
rspArg9		equ <[rsp+8*9-8]>
rspArg8		equ <[rsp+8*8-8]>
rspArg7		equ <[rsp+8*7-8]>
rspArg6		equ <[rsp+8*6-8]>
rspArg5		equ <[rsp+8*5-8]>
rspArg4		equ <[rsp+8*4-8]>
rspArg3		equ <[rsp+8*3-8]>
rspArg2		equ <[rsp+8*2-8]>
rspArg1		equ <[rsp+8*1-8]>
invoke14 MACRO procname,args:VARARG
LOCAL numics,is_addr
	txt TEXTEQU <>
	ArgNum = 0
%	FOR item, <args>
		IF ArgNum EQ 0
			movReg64Arg rcx,item
		ELSEIF ArgNum EQ 1
			movReg64Arg rdx,item
		ELSEIF ArgNum EQ 2
			movReg64Arg r8,item
		ELSEIF ArgNum EQ 3
			movReg64Arg r9,item
		ELSE
			txt CATSTR <item>,<!,>,txt
		ENDIF
%		ArgNum=ArgNum+1
	ENDM
	IF rbpFrame EQ 1
		IF ArgNum GT 4
			txt SUBSTR  txt, 1, @SizeStr( %txt ) - 1
			ArgNum=rbpFirstArgBias-8*ArgNum
		%	FOR item,<txt>
				ArgNum=ArgNum+8
				IFDIF <item>,<ready>
					movMem64Arg [rbp-ArgNum],item
				ENDIF
			ENDM	
		ENDIF
		IF (OPATTR (procname)) EQ (VALID_REF OR IMM_EXPR)
			mov rax,[rcx]
			call procname[rax]
		ELSE
			call procname
		ENDIF
	ELSEIF rspFrame EQ 1
		IF ArgNum GT 4
			txt SUBSTR  txt, 1, @SizeStr( %txt ) - 1
		%	FOR item,<txt>
				ArgNum = ArgNum-1
				;;%echo item
				IF IS_INT_REG(< item >) NE 0
					mov [rsp+8*ArgNum],item
				ELSE
					IF (@InStr(1,<0123456789>,@SubStr(<item>,1,1)) NE 0) AND (@SizeStr(<item>) LE 10)
						mov qword ptr [rsp+8*ArgNum],item
					ELSE
						IF ( (@SizeStr(<item>) GE 4) AND (@InStr(1,<item>,<addr >) EQ 1) ) ;;OR (@SubStr(item,1,4),<ADDR>) ;;OR (@SubStr(item,1,4),<Addr>)
							lea rax,@SubStr(<item>,6,@SizeStr(<item>)-5)
						ELSE
							mov rax,item
						ENDIF
						mov [rsp+8*ArgNum],rax
					ENDIF
				ENDIF
			ENDM
		ENDIF
		call procname
	ELSE
		IF ArgNum GT 4
			txt SUBSTR  txt, 1, @SizeStr( %txt ) - 1
			%pushm txt
		ENDIF
		sub rsp,8*4
		call procname
		IF ArgNum GT 4
			add rsp,8*ArgNum
		ELSE
			add rsp,8*4
		ENDIF
	ENDIF	
ENDM
FREE_RAX equ (1 shl 0)
FREE_RBX equ (1 shl 1)
FREE_RCX equ (1 shl 2)
FREE_RDX equ (1 shl 3)
FREE_RSP equ (1 shl 4)
FREE_RBP equ (1 shl 5)
FREE_RDI equ (1 shl 6)
FREE_RSI equ (1 shl 7)
FREE_R8  equ (1 shl 8)
FREE_R9  equ (1 shl 9)
FREE_R10 equ (1 shl 10)
FREE_R11 equ (1 shl 11)
FREE_R12 equ (1 shl 12)
FREE_R13 equ (1 shl 13)
FREE_R14 equ (1 shl 14)
FREE_R15 equ (1 shl 15)
FreeRegs=(FREE_RAX or FREE_RCX or FREE_RDX or FREE_R8 or FREE_R9 or FREE_R10 or FREE_R11)
GetVolatileReg macro
	IF FreeRegs and FREE_RAX
		FreeRegs=FreeRegs and (not FREE_RAX)
		EXITM<0>
	ELSEIF FreeRegs and FREE_RCX
		FreeRegs=FreeRegs and (not FREE_RCX)
		EXITM<1>
	ELSEIF FreeRegs and FREE_RDX
		FreeRegs=FreeRegs and (not FREE_RDX)
		EXITM<2>
	ELSEIF FreeRegs and FREE_R8
		FreeRegs=FreeRegs and (not FREE_R8)
		EXITM<8>
	ELSEIF FreeRegs and FREE_R9
		FreeRegs=FreeRegs and (not FREE_R9)
		EXITM<9>
	ELSEIF FreeRegs and FREE_R10
		FreeRegs=FreeRegs and (not FREE_R10)
		EXITM<10>
	ELSEIF FreeRegs and FREE_R11
		FreeRegs=FreeRegs and (not FREE_R11)
		EXITM<11>
	ENDIF
	EXITM<16>
endm
IN_ARG1_READY equ (1 shl 1)
IN_ARG2_READY equ (1 shl 2)
IN_ARG3_READY equ (1 shl 3)
IN_ARG4_READY equ (1 shl 4)
IN_ARG5_READY equ (1 shl 5)
IN_ARG6_READY equ (1 shl 6)
IN_ARG7_READY equ (1 shl 7)
IN_ARG8_READY equ (1 shl 8)
IN_ARG9_READY equ (1 shl 9)
IN_ARG10_READY equ (1 shl 10)
IN_ARG11_READY equ (1 shl 11)
IN_ARG12_READY equ (1 shl 12)
IN_ARG13_READY equ (1 shl 13)
IN_ARG14_READY equ (1 shl 14)
invoke macro procname,in_arg1,in_arg2,in_arg3,in_arg4,in_arg5,in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
	ReadyInArgs=0
	IFB <in_arg14>
		ReadyInArgs=ReadyInArgs or IN_ARG14_READY
	ENDIF
	IFB <in_arg13>
		ReadyInArgs=ReadyInArgs or IN_ARG13_READY
	ENDIF
	IFB <in_arg12>
		ReadyInArgs=ReadyInArgs or IN_ARG12_READY
	ENDIF
	IFB <in_arg11>
		ReadyInArgs=ReadyInArgs or IN_ARG11_READY
	ENDIF
	IFB <in_arg10>
		ReadyInArgs=ReadyInArgs or IN_ARG10_READY
	ENDIF
	IFB <in_arg9>
		ReadyInArgs=ReadyInArgs or IN_ARG9_READY
	ENDIF
	IFB <in_arg8>
		ReadyInArgs=ReadyInArgs or IN_ARG8_READY
	ENDIF
	IFB <in_arg7>
		ReadyInArgs=ReadyInArgs or IN_ARG7_READY
	ENDIF
	IFB <in_arg6>
		ReadyInArgs=ReadyInArgs or IN_ARG6_READY
	ENDIF
	IFB <in_arg5>
		ReadyInArgs=ReadyInArgs or IN_ARG5_READY
	ENDIF
	IFB <in_arg4>
		ReadyInArgs=ReadyInArgs or IN_ARG4_READY
	ENDIF
	IFB <in_arg3>
		ReadyInArgs=ReadyInArgs or IN_ARG3_READY
	ENDIF
	IFB <in_arg2>
		ReadyInArgs=ReadyInArgs or IN_ARG2_READY
	ENDIF
	IFB <in_arg1>
		ReadyInArgs=ReadyInArgs or IN_ARG1_READY
	ENDIF
	IF rbpFirstArgBias LT rspBorder
	%	LoadEAX rbpArg5,in_arg5,IN_ARG5_READY
	%	LoadEAX rbpArg6,in_arg6,IN_ARG6_READY
	%	LoadEAX rbpArg7,in_arg7,IN_ARG7_READY
	%	LoadEAX rbpArg8,in_arg8,IN_ARG8_READY
	%	LoadEAX rbpArg9,in_arg9,IN_ARG9_READY
	%	LoadEAX rbpArg10,in_arg10,IN_ARG10_READY
	%	LoadEAX rbpArg11,in_arg11,IN_ARG11_READY
	%	LoadEAX rbpArg12,in_arg12,IN_ARG12_READY
	%	LoadEAX rbpArg13,in_arg13,IN_ARG13_READY
	%	LoadEAX rbpArg14,in_arg14,IN_ARG14_READY
		IF (ReadyInArgs and IN_ARG1_READY) EQ 0
		%	movReg64Arg rcx,in_arg1
			ReadyInArgs=ReadyInArgs or IN_ARG1_READY
		%	LoadSameInEDX in_arg1,in_arg2,IN_ARG2_READY,rcx,ecx
		%	LoadSameInR8 in_arg1,in_arg3,IN_ARG3_READY,rcx,ecx
		%	LoadSameInR9 in_arg1,in_arg4,IN_ARG4_READY,rcx,ecx
		%	LoadSameInMemR rbpArg5,in_arg1,in_arg5,IN_ARG5_READY,rcx,ecx
		%	LoadSameInMemR rbpArg6,in_arg1,in_arg6,IN_ARG6_READY,rcx,ecx
		%	LoadSameInMemR rbpArg7,in_arg1,in_arg7,IN_ARG7_READY,rcx,ecx
		%	LoadSameInMemR rbpArg8,in_arg1,in_arg8,IN_ARG8_READY,rcx,ecx
		%	LoadSameInMemR rbpArg9,in_arg1,in_arg9,IN_ARG9_READY,rcx,ecx
		%	LoadSameInMemR rbpArg10,in_arg1,in_arg10,IN_ARG10_READY,rcx,ecx
		%	LoadSameInMemR rbpArg11,in_arg1,in_arg11,IN_ARG11_READY,rcx,ecx
		%	LoadSameInMemR rbpArg12,in_arg1,in_arg12,IN_ARG12_READY,rcx,ecx
		%	LoadSameInMemR rbpArg13,in_arg1,in_arg13,IN_ARG13_READY,rcx,ecx
		%	LoadSameInMemR rbpArg14,in_arg1,in_arg14,IN_ARG14_READY,rcx,ecx
		ENDIF
		IF (ReadyInArgs and IN_ARG2_READY) EQ 0
		%	movReg64Arg rdx,in_arg2
			ReadyInArgs=ReadyInArgs or IN_ARG2_READY
		%	LoadSameInR8 in_arg2,in_arg3,IN_ARG3_READY,rdx,edx
		%	LoadSameInR9 in_arg2,in_arg4,IN_ARG4_READY,rdx,edx
		%	LoadSameInMemR rbpArg5,in_arg2,in_arg5,IN_ARG5_READY,rdx,edx
		%	LoadSameInMemR rbpArg6,in_arg2,in_arg6,IN_ARG6_READY,rdx,edx
		%	LoadSameInMemR rbpArg7,in_arg2,in_arg7,IN_ARG7_READY,rdx,edx
		%	LoadSameInMemR rbpArg8,in_arg2,in_arg8,IN_ARG8_READY,rdx,edx
		%	LoadSameInMemR rbpArg9,in_arg2,in_arg9,IN_ARG9_READY,rdx,edx
		%	LoadSameInMemR rbpArg10,in_arg2,in_arg10,IN_ARG10_READY,rdx,edx
		%	LoadSameInMemR rbpArg11,in_arg2,in_arg11,IN_ARG11_READY,rdx,edx
		%	LoadSameInMemR rbpArg12,in_arg2,in_arg12,IN_ARG12_READY,rdx,edx
		%	LoadSameInMemR rbpArg13,in_arg2,in_arg13,IN_ARG13_READY,rdx,edx
		%	LoadSameInMemR rbpArg14,in_arg2,in_arg14,IN_ARG14_READY,rdx,edx
		ENDIF
		IF (ReadyInArgs and IN_ARG3_READY) EQ 0
		%	movReg64Arg r8,in_arg3
			ReadyInArgs=ReadyInArgs or IN_ARG3_READY
		%	LoadSameInR9 in_arg3,in_arg4,IN_ARG4_READY,r8,r8d
		%	LoadSameInMemR rbpArg5,in_arg3,in_arg5,IN_ARG5_READY,r8,r8d
		%	LoadSameInMemR rbpArg6,in_arg3,in_arg6,IN_ARG6_READY,r8,r8d
		%	LoadSameInMemR rbpArg7,in_arg3,in_arg7,IN_ARG7_READY,r8,r8d
		%	LoadSameInMemR rbpArg8,in_arg3,in_arg8,IN_ARG8_READY,r8,r8d
		%	LoadSameInMemR rbpArg9,in_arg3,in_arg9,IN_ARG9_READY,r8,r8d
		%	LoadSameInMemR rbpArg10,in_arg3,in_arg10,IN_ARG10_READY,r8,r8d
		%	LoadSameInMemR rbpArg11,in_arg3,in_arg11,IN_ARG11_READY,r8,r8d
		%	LoadSameInMemR rbpArg12,in_arg3,in_arg12,IN_ARG12_READY,r8,r8d
		%	LoadSameInMemR rbpArg13,in_arg3,in_arg13,IN_ARG13_READY,r8,r8d
		%	LoadSameInMemR rbpArg14,in_arg3,in_arg14,IN_ARG14_READY,r8,r8d
		ENDIF
		IF (ReadyInArgs and IN_ARG4_READY) EQ 0
		%	movReg64Arg r9,in_arg4
			ReadyInArgs=ReadyInArgs or IN_ARG4_READY
		%	LoadSameInMemR rbpArg5,in_arg4,in_arg5,IN_ARG5_READY,r9,r9d
		%	LoadSameInMemR rbpArg6,in_arg4,in_arg6,IN_ARG6_READY,r9,r9d
		%	LoadSameInMemR rbpArg7,in_arg4,in_arg7,IN_ARG7_READY,r9,r9d
		%	LoadSameInMemR rbpArg8,in_arg4,in_arg8,IN_ARG8_READY,r9,r9d
		%	LoadSameInMemR rbpArg9,in_arg4,in_arg9,IN_ARG9_READY,r9,r9d
		%	LoadSameInMemR rbpArg10,in_arg4,in_arg10,IN_ARG10_READY,r9,r9d
		%	LoadSameInMemR rbpArg11,in_arg4,in_arg11,IN_ARG11_READY,r9,r9d
		%	LoadSameInMemR rbpArg12,in_arg4,in_arg12,IN_ARG12_READY,r9,r9d
		%	LoadSameInMemR rbpArg13,in_arg4,in_arg13,IN_ARG13_READY,r9,r9d
		%	LoadSameInMemR rbpArg14,in_arg4,in_arg14,IN_ARG14_READY,r9,r9d
		ENDIF
		IF (ReadyInArgs and IN_ARG5_READY) EQ 0
		%	SetType rbpArg5,in_arg5
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg5,in_arg5
			ELSE
			%	AppearsCount in_arg5,in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg5
				%	LoadSameInMemR rbpArg5,in_arg5,in_arg5,IN_ARG5_READY,rax,eax
				%	LoadSameInMemR rbpArg6,in_arg5,in_arg6,IN_ARG6_READY,rax,eax
				%	LoadSameInMemR rbpArg7,in_arg5,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rbpArg8,in_arg5,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rbpArg9,in_arg5,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg5,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg5,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg5,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg5,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg5,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg5,in_arg5
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG5_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG6_READY) EQ 0
		%	SetType rbpArg6,in_arg6
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg6,in_arg6
			ELSE
			%	AppearsCount in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg6
				%	LoadSameInMemR rbpArg6,in_arg6,in_arg6,IN_ARG6_READY,rax,eax
				%	LoadSameInMemR rbpArg7,in_arg6,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rbpArg8,in_arg6,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rbpArg9,in_arg6,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg6,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg6,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg6,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg6,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg6,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg6,in_arg6
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG6_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG7_READY) EQ 0
		%	SetType rbpArg7,in_arg7
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg7,in_arg7
			ELSE
			%	AppearsCount in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg7
				%	LoadSameInMemR rbpArg7,in_arg7,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rbpArg8,in_arg7,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rbpArg9,in_arg7,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg7,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg7,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg7,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg7,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg7,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg7,in_arg7
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG7_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG8_READY) EQ 0
		%	SetType rbpArg8,in_arg8
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg8,in_arg8
			ELSE
			%	AppearsCount in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg8
				%	LoadSameInMemR rbpArg8,in_arg8,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rbpArg9,in_arg8,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg8,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg8,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg8,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg8,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg8,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg8,in_arg8
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG8_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG9_READY) EQ 0
		%	SetType rbpArg9,in_arg9
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg9,in_arg9
			ELSE
			%	AppearsCount in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg9
				%	LoadSameInMemR rbpArg9,in_arg9,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg9,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg9,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg9,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg9,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg9,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg9,in_arg9
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG9_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG10_READY) EQ 0
		%	SetType rbpArg10,in_arg10
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg10,in_arg10
			ELSE
			%	AppearsCount in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg10
				%	LoadSameInMemR rbpArg10,in_arg10,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg10,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg10,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg10,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg10,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg10,in_arg10
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG10_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG11_READY) EQ 0
			SetType rbpArg11,in_arg11
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg11,in_arg11
			ELSE
			%	AppearsCount in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg11
				%	LoadSameInMemR rbpArg11,in_arg11,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg11,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg11,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg11,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg11,in_arg11
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG11_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG12_READY) EQ 0
		%	SetType rbpArg12,in_arg12
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg12,in_arg12
			ELSE
			%	AppearsCount in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg12
				%	LoadSameInMemR rbpArg12,in_arg12,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg12,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg12,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg12,in_arg12
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG12_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG13_READY) EQ 0
		%	SetType rbpArg13,in_arg13
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg13,in_arg13
			ELSE
			%	AppearsCount in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg13
				%	LoadSameInMemR rbpArg13,in_arg13,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg13,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg13,in_arg13
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG13_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG14_READY) EQ 0
		%	movMem64Arg rbpArg13,in_arg14
		%	ReadyInArgs=ReadyInArgs or IN_ARG14_READY
		ENDIF
	ELSE
	%	LoadEAX rspArg5,in_arg5,IN_ARG5_READY
	%	LoadEAX rspArg6,in_arg6,IN_ARG6_READY
	%	LoadEAX rspArg7,in_arg7,IN_ARG7_READY
	%	LoadEAX rspArg8,in_arg8,IN_ARG8_READY
	%	LoadEAX rspArg9,in_arg9,IN_ARG9_READY
	%	LoadEAX rspArg10,in_arg10,IN_ARG10_READY
	%	LoadEAX rspArg11,in_arg11,IN_ARG11_READY
	%	LoadEAX rspArg12,in_arg12,IN_ARG12_READY
	%	LoadEAX rspArg13,in_arg13,IN_ARG13_READY
	%	LoadEAX rspArg14,in_arg14,IN_ARG14_READY
		IF (ReadyInArgs and IN_ARG1_READY) EQ 0
		%	movReg64Arg rcx,in_arg1
			ReadyInArgs=ReadyInArgs or IN_ARG1_READY
		%	LoadSameInEDX in_arg1,in_arg2,IN_ARG2_READY,rcx,ecx
		%	LoadSameInR8 in_arg1,in_arg3,IN_ARG3_READY,rcx,ecx
		%	LoadSameInR9 in_arg1,in_arg4,IN_ARG4_READY,rcx,ecx
		%	LoadSameInMemR rspArg5,in_arg1,in_arg5,IN_ARG5_READY,rcx,ecx
		%	LoadSameInMemR rspArg6,in_arg1,in_arg6,IN_ARG6_READY,rcx,ecx
		%	LoadSameInMemR rspArg7,in_arg1,in_arg7,IN_ARG7_READY,rcx,ecx
		%	LoadSameInMemR rspArg8,in_arg1,in_arg8,IN_ARG8_READY,rcx,ecx
		%	LoadSameInMemR rspArg9,in_arg1,in_arg9,IN_ARG9_READY,rcx,ecx
		%	LoadSameInMemR rspArg10,in_arg1,in_arg10,IN_ARG10_READY,rcx,ecx
		%	LoadSameInMemR rspArg11,in_arg1,in_arg11,IN_ARG11_READY,rcx,ecx
		%	LoadSameInMemR rspArg12,in_arg1,in_arg12,IN_ARG12_READY,rcx,ecx
		%	LoadSameInMemR rspArg13,in_arg1,in_arg13,IN_ARG13_READY,rcx,ecx
		%	LoadSameInMemR rspArg14,in_arg1,in_arg14,IN_ARG14_READY,rcx,ecx
		ENDIF
		IF (ReadyInArgs and IN_ARG2_READY) EQ 0
		%	movReg64Arg rdx,in_arg2
			ReadyInArgs=ReadyInArgs or IN_ARG2_READY
		%	LoadSameInR8 in_arg2,in_arg3,IN_ARG3_READY,rdx,edx
		%	LoadSameInR9 in_arg2,in_arg4,IN_ARG4_READY,rdx,edx
		%	LoadSameInMemR rspArg5,in_arg2,in_arg5,IN_ARG5_READY,rdx,edx
		%	LoadSameInMemR rspArg6,in_arg2,in_arg6,IN_ARG6_READY,rdx,edx
		%	LoadSameInMemR rspArg7,in_arg2,in_arg7,IN_ARG7_READY,rdx,edx
		%	LoadSameInMemR rspArg8,in_arg2,in_arg8,IN_ARG8_READY,rdx,edx
		%	LoadSameInMemR rspArg9,in_arg2,in_arg9,IN_ARG9_READY,rdx,edx
		%	LoadSameInMemR rspArg10,in_arg2,in_arg10,IN_ARG10_READY,rdx,edx
		%	LoadSameInMemR rspArg11,in_arg2,in_arg11,IN_ARG11_READY,rdx,edx
		%	LoadSameInMemR rspArg12,in_arg2,in_arg12,IN_ARG12_READY,rdx,edx
		%	LoadSameInMemR rspArg13,in_arg2,in_arg13,IN_ARG13_READY,rdx,edx
		%	LoadSameInMemR rspArg14,in_arg2,in_arg14,IN_ARG14_READY,rdx,edx
		ENDIF
		IF (ReadyInArgs and IN_ARG3_READY) EQ 0
		%	movReg64Arg r8,in_arg3
			ReadyInArgs=ReadyInArgs or IN_ARG3_READY
		%	LoadSameInR9 in_arg3,in_arg4,IN_ARG4_READY,r8,r8d
		%	LoadSameInMemR rspArg5,in_arg3,in_arg5,IN_ARG5_READY,r8,r8d
		%	LoadSameInMemR rspArg6,in_arg3,in_arg6,IN_ARG6_READY,r8,r8d
		%	LoadSameInMemR rspArg7,in_arg3,in_arg7,IN_ARG7_READY,r8,r8d
		%	LoadSameInMemR rspArg8,in_arg3,in_arg8,IN_ARG8_READY,r8,r8d
		%	LoadSameInMemR rspArg9,in_arg3,in_arg9,IN_ARG9_READY,r8,r8d
		%	LoadSameInMemR rspArg10,in_arg3,in_arg10,IN_ARG10_READY,r8,r8d
		%	LoadSameInMemR rspArg11,in_arg3,in_arg11,IN_ARG11_READY,r8,r8d
		%	LoadSameInMemR rspArg12,in_arg3,in_arg12,IN_ARG12_READY,r8,r8d
		%	LoadSameInMemR rspArg13,in_arg3,in_arg13,IN_ARG13_READY,r8,r8d
		%	LoadSameInMemR rspArg14,in_arg3,in_arg14,IN_ARG14_READY,r8,r8d
		ENDIF
		IF (ReadyInArgs and IN_ARG4_READY) EQ 0
		%	movReg64Arg r9,in_arg4
			ReadyInArgs=ReadyInArgs or IN_ARG4_READY
		%	LoadSameInMemR rspArg5,in_arg4,in_arg5,IN_ARG5_READY,r9,r9d
		%	LoadSameInMemR rspArg6,in_arg4,in_arg6,IN_ARG6_READY,r9,r9d
		%	LoadSameInMemR rspArg7,in_arg4,in_arg7,IN_ARG7_READY,r9,r9d
		%	LoadSameInMemR rspArg8,in_arg4,in_arg8,IN_ARG8_READY,r9,r9d
		%	LoadSameInMemR rspArg9,in_arg4,in_arg9,IN_ARG9_READY,r9,r9d
		%	LoadSameInMemR rspArg10,in_arg4,in_arg10,IN_ARG10_READY,r9,r9d
		%	LoadSameInMemR rspArg11,in_arg4,in_arg11,IN_ARG11_READY,r9,r9d
		%	LoadSameInMemR rspArg12,in_arg4,in_arg12,IN_ARG12_READY,r9,r9d
		%	LoadSameInMemR rspArg13,in_arg4,in_arg13,IN_ARG13_READY,r9,r9d
		%	LoadSameInMemR rspArg14,in_arg4,in_arg14,IN_ARG14_READY,r9,r9d
		ENDIF
		IF (ReadyInArgs and IN_ARG5_READY) EQ 0
		%	SetType rspArg5,in_arg5
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg5,in_arg5
			ELSE
			%	AppearsCount in_arg5,in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg5
				%	LoadSameInMemR rspArg5,in_arg5,in_arg5,IN_ARG5_READY,rax,eax
				%	LoadSameInMemR rspArg6,in_arg5,in_arg6,IN_ARG6_READY,rax,eax
				%	LoadSameInMemR rspArg7,in_arg5,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rspArg8,in_arg5,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rspArg9,in_arg5,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg5,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg5,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg5,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg5,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg5,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg5,in_arg5
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG5_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG6_READY) EQ 0
		%	SetType rspArg6,in_arg6
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg6,in_arg6
			ELSE
			%	AppearsCount in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg6
				%	LoadSameInMemR rspArg6,in_arg6,in_arg6,IN_ARG6_READY,rax,eax
				%	LoadSameInMemR rspArg7,in_arg6,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rspArg8,in_arg6,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rspArg9,in_arg6,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg6,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg6,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg6,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg6,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg6,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg6,in_arg6
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG6_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG7_READY) EQ 0
		%	SetType rspArg7,in_arg7
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg7,in_arg7
			ELSE
			%	AppearsCount in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg7
				%	LoadSameInMemR rspArg7,in_arg7,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rspArg8,in_arg7,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rspArg9,in_arg7,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg7,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg7,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg7,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg7,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg7,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg7,in_arg7
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG7_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG8_READY) EQ 0
		%	SetType rspArg8,in_arg8
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg8,in_arg8
			ELSE
			%	AppearsCount in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg8
				%	LoadSameInMemR rspArg8,in_arg8,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rspArg9,in_arg8,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg8,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg8,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg8,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg8,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg8,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg8,in_arg8
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG8_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG9_READY) EQ 0
		%	SetType rspArg9,in_arg9
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg9,in_arg9
			ELSE
			%	AppearsCount in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg9
				%	LoadSameInMemR rspArg9,in_arg9,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg9,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg9,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg9,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg9,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg9,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg9,in_arg9
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG9_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG10_READY) EQ 0
		%	SetType rspArg10,in_arg10
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg10,in_arg10
			ELSE
			%	AppearsCount in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg10
				%	LoadSameInMemR rspArg10,in_arg10,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg10,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg10,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg10,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg10,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg10,in_arg10
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG10_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG11_READY) EQ 0
		%	SetType rspArg11,in_arg11
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg11,in_arg11
			ELSE
			%	AppearsCount in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg11
				%	LoadSameInMemR rspArg11,in_arg11,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg11,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg11,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg11,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg11,in_arg11
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG11_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG12_READY) EQ 0
		%	SetType rspArg12,in_arg12
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg12,in_arg12
			ELSE
			%	AppearsCount in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg12
				%	LoadSameInMemR rspArg12,in_arg12,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg12,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg12,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg12,in_arg12
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG12_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG13_READY) EQ 0
		%	SetType rspArg13,in_arg13
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg13,in_arg13
			ELSE
			%	AppearsCount in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg13
				%	LoadSameInMemR rspArg13,in_arg13,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg13,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg13,in_arg13
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG13_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG14_READY) EQ 0
		%	movMem64Arg rspArg13,in_arg14
		%	ReadyInArgs=ReadyInArgs or IN_ARG14_READY
		ENDIF
	ENDIF
	IF (OPATTR (procname)) EQ (VALID_REF OR IMM_EXPR)
		mov rax,[rcx]
		call procname[rax]
	ELSE
		call procname
	ENDIF
endm
I macro procname,in_arg1,in_arg2,in_arg3,in_arg4,in_arg5,in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
	ReadyInArgs=0
	IFB <in_arg14>
		ReadyInArgs=ReadyInArgs or IN_ARG14_READY
	ENDIF
	IFB <in_arg13>
		ReadyInArgs=ReadyInArgs or IN_ARG13_READY
	ENDIF
	IFB <in_arg12>
		ReadyInArgs=ReadyInArgs or IN_ARG12_READY
	ENDIF
	IFB <in_arg11>
		ReadyInArgs=ReadyInArgs or IN_ARG11_READY
	ENDIF
	IFB <in_arg10>
		ReadyInArgs=ReadyInArgs or IN_ARG10_READY
	ENDIF
	IFB <in_arg9>
		ReadyInArgs=ReadyInArgs or IN_ARG9_READY
	ENDIF
	IFB <in_arg8>
		ReadyInArgs=ReadyInArgs or IN_ARG8_READY
	ENDIF
	IFB <in_arg7>
		ReadyInArgs=ReadyInArgs or IN_ARG7_READY
	ENDIF
	IFB <in_arg6>
		ReadyInArgs=ReadyInArgs or IN_ARG6_READY
	ENDIF
	IFB <in_arg5>
		ReadyInArgs=ReadyInArgs or IN_ARG5_READY
	ENDIF
	IFB <in_arg4>
		ReadyInArgs=ReadyInArgs or IN_ARG4_READY
	ENDIF
	IFB <in_arg3>
		ReadyInArgs=ReadyInArgs or IN_ARG3_READY
	ENDIF
	IFB <in_arg2>
		ReadyInArgs=ReadyInArgs or IN_ARG2_READY
	ENDIF
	IFB <in_arg1>
		ReadyInArgs=ReadyInArgs or IN_ARG1_READY
	ENDIF
	IF rbpFirstArgBias LT rspBorder
	%	LoadEAX rbpArg5,in_arg5,IN_ARG5_READY
	%	LoadEAX rbpArg6,in_arg6,IN_ARG6_READY
	%	LoadEAX rbpArg7,in_arg7,IN_ARG7_READY
	%	LoadEAX rbpArg8,in_arg8,IN_ARG8_READY
	%	LoadEAX rbpArg9,in_arg9,IN_ARG9_READY
	%	LoadEAX rbpArg10,in_arg10,IN_ARG10_READY
	%	LoadEAX rbpArg11,in_arg11,IN_ARG11_READY
	%	LoadEAX rbpArg12,in_arg12,IN_ARG12_READY
	%	LoadEAX rbpArg13,in_arg13,IN_ARG13_READY
	%	LoadEAX rbpArg14,in_arg14,IN_ARG14_READY
		IF (ReadyInArgs and IN_ARG1_READY) EQ 0
		%	movReg64Arg rcx,in_arg1
			ReadyInArgs=ReadyInArgs or IN_ARG1_READY
		%	LoadSameInEDX in_arg1,in_arg2,IN_ARG2_READY,rcx,ecx
		%	LoadSameInR8 in_arg1,in_arg3,IN_ARG3_READY,rcx,ecx
		%	LoadSameInR9 in_arg1,in_arg4,IN_ARG4_READY,rcx,ecx
		%	LoadSameInMemR rbpArg5,in_arg1,in_arg5,IN_ARG5_READY,rcx,ecx
		%	LoadSameInMemR rbpArg6,in_arg1,in_arg6,IN_ARG6_READY,rcx,ecx
		%	LoadSameInMemR rbpArg7,in_arg1,in_arg7,IN_ARG7_READY,rcx,ecx
		%	LoadSameInMemR rbpArg8,in_arg1,in_arg8,IN_ARG8_READY,rcx,ecx
		%	LoadSameInMemR rbpArg9,in_arg1,in_arg9,IN_ARG9_READY,rcx,ecx
		%	LoadSameInMemR rbpArg10,in_arg1,in_arg10,IN_ARG10_READY,rcx,ecx
		%	LoadSameInMemR rbpArg11,in_arg1,in_arg11,IN_ARG11_READY,rcx,ecx
		%	LoadSameInMemR rbpArg12,in_arg1,in_arg12,IN_ARG12_READY,rcx,ecx
		%	LoadSameInMemR rbpArg13,in_arg1,in_arg13,IN_ARG13_READY,rcx,ecx
		%	LoadSameInMemR rbpArg14,in_arg1,in_arg14,IN_ARG14_READY,rcx,ecx
		ENDIF
		IF (ReadyInArgs and IN_ARG2_READY) EQ 0
		%	movReg64Arg rdx,in_arg2
			ReadyInArgs=ReadyInArgs or IN_ARG2_READY
		%	LoadSameInR8 in_arg2,in_arg3,IN_ARG3_READY,rdx,edx
		%	LoadSameInR9 in_arg2,in_arg4,IN_ARG4_READY,rdx,edx
		%	LoadSameInMemR rbpArg5,in_arg2,in_arg5,IN_ARG5_READY,rdx,edx
		%	LoadSameInMemR rbpArg6,in_arg2,in_arg6,IN_ARG6_READY,rdx,edx
		%	LoadSameInMemR rbpArg7,in_arg2,in_arg7,IN_ARG7_READY,rdx,edx
		%	LoadSameInMemR rbpArg8,in_arg2,in_arg8,IN_ARG8_READY,rdx,edx
		%	LoadSameInMemR rbpArg9,in_arg2,in_arg9,IN_ARG9_READY,rdx,edx
		%	LoadSameInMemR rbpArg10,in_arg2,in_arg10,IN_ARG10_READY,rdx,edx
		%	LoadSameInMemR rbpArg11,in_arg2,in_arg11,IN_ARG11_READY,rdx,edx
		%	LoadSameInMemR rbpArg12,in_arg2,in_arg12,IN_ARG12_READY,rdx,edx
		%	LoadSameInMemR rbpArg13,in_arg2,in_arg13,IN_ARG13_READY,rdx,edx
		%	LoadSameInMemR rbpArg14,in_arg2,in_arg14,IN_ARG14_READY,rdx,edx
		ENDIF
		IF (ReadyInArgs and IN_ARG3_READY) EQ 0
		%	movReg64Arg r8,in_arg3
			ReadyInArgs=ReadyInArgs or IN_ARG3_READY
		%	LoadSameInR9 in_arg3,in_arg4,IN_ARG4_READY,r8,r8d
		%	LoadSameInMemR rbpArg5,in_arg3,in_arg5,IN_ARG5_READY,r8,r8d
		%	LoadSameInMemR rbpArg6,in_arg3,in_arg6,IN_ARG6_READY,r8,r8d
		%	LoadSameInMemR rbpArg7,in_arg3,in_arg7,IN_ARG7_READY,r8,r8d
		%	LoadSameInMemR rbpArg8,in_arg3,in_arg8,IN_ARG8_READY,r8,r8d
		%	LoadSameInMemR rbpArg9,in_arg3,in_arg9,IN_ARG9_READY,r8,r8d
		%	LoadSameInMemR rbpArg10,in_arg3,in_arg10,IN_ARG10_READY,r8,r8d
		%	LoadSameInMemR rbpArg11,in_arg3,in_arg11,IN_ARG11_READY,r8,r8d
		%	LoadSameInMemR rbpArg12,in_arg3,in_arg12,IN_ARG12_READY,r8,r8d
		%	LoadSameInMemR rbpArg13,in_arg3,in_arg13,IN_ARG13_READY,r8,r8d
		%	LoadSameInMemR rbpArg14,in_arg3,in_arg14,IN_ARG14_READY,r8,r8d
		ENDIF
		IF (ReadyInArgs and IN_ARG4_READY) EQ 0
		%	movReg64Arg r9,in_arg4
			ReadyInArgs=ReadyInArgs or IN_ARG4_READY
		%	LoadSameInMemR rbpArg5,in_arg4,in_arg5,IN_ARG5_READY,r9,r9d
		%	LoadSameInMemR rbpArg6,in_arg4,in_arg6,IN_ARG6_READY,r9,r9d
		%	LoadSameInMemR rbpArg7,in_arg4,in_arg7,IN_ARG7_READY,r9,r9d
		%	LoadSameInMemR rbpArg8,in_arg4,in_arg8,IN_ARG8_READY,r9,r9d
		%	LoadSameInMemR rbpArg9,in_arg4,in_arg9,IN_ARG9_READY,r9,r9d
		%	LoadSameInMemR rbpArg10,in_arg4,in_arg10,IN_ARG10_READY,r9,r9d
		%	LoadSameInMemR rbpArg11,in_arg4,in_arg11,IN_ARG11_READY,r9,r9d
		%	LoadSameInMemR rbpArg12,in_arg4,in_arg12,IN_ARG12_READY,r9,r9d
		%	LoadSameInMemR rbpArg13,in_arg4,in_arg13,IN_ARG13_READY,r9,r9d
		%	LoadSameInMemR rbpArg14,in_arg4,in_arg14,IN_ARG14_READY,r9,r9d
		ENDIF
		IF (ReadyInArgs and IN_ARG5_READY) EQ 0
		%	SetType rbpArg5,in_arg5
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg5,in_arg5
			ELSE
			%	AppearsCount in_arg5,in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg5
				%	LoadSameInMemR rbpArg5,in_arg5,in_arg5,IN_ARG5_READY,rax,eax
				%	LoadSameInMemR rbpArg6,in_arg5,in_arg6,IN_ARG6_READY,rax,eax
				%	LoadSameInMemR rbpArg7,in_arg5,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rbpArg8,in_arg5,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rbpArg9,in_arg5,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg5,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg5,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg5,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg5,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg5,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg5,in_arg5
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG5_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG6_READY) EQ 0
		%	SetType rbpArg6,in_arg6
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg6,in_arg6
			ELSE
			%	AppearsCount in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg6
				%	LoadSameInMemR rbpArg6,in_arg6,in_arg6,IN_ARG6_READY,rax,eax
				%	LoadSameInMemR rbpArg7,in_arg6,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rbpArg8,in_arg6,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rbpArg9,in_arg6,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg6,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg6,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg6,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg6,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg6,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg6,in_arg6
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG6_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG7_READY) EQ 0
		%	SetType rbpArg7,in_arg7
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg7,in_arg7
			ELSE
			%	AppearsCount in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg7
				%	LoadSameInMemR rbpArg7,in_arg7,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rbpArg8,in_arg7,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rbpArg9,in_arg7,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg7,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg7,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg7,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg7,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg7,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg7,in_arg7
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG7_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG8_READY) EQ 0
		%	SetType rbpArg8,in_arg8
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg8,in_arg8
			ELSE
			%	AppearsCount in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg8
				%	LoadSameInMemR rbpArg8,in_arg8,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rbpArg9,in_arg8,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg8,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg8,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg8,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg8,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg8,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg8,in_arg8
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG8_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG9_READY) EQ 0
		%	SetType rbpArg9,in_arg9
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg9,in_arg9
			ELSE
			%	AppearsCount in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg9
				%	LoadSameInMemR rbpArg9,in_arg9,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rbpArg10,in_arg9,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg9,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg9,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg9,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg9,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg9,in_arg9
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG9_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG10_READY) EQ 0
		%	SetType rbpArg10,in_arg10
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg10,in_arg10
			ELSE
			%	AppearsCount in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg10
				%	LoadSameInMemR rbpArg10,in_arg10,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rbpArg11,in_arg10,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg10,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg10,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg10,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg10,in_arg10
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG10_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG11_READY) EQ 0
			SetType rbpArg11,in_arg11
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg11,in_arg11
			ELSE
			%	AppearsCount in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg11
				%	LoadSameInMemR rbpArg11,in_arg11,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rbpArg12,in_arg11,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg11,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg11,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg11,in_arg11
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG11_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG12_READY) EQ 0
		%	SetType rbpArg12,in_arg12
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg12,in_arg12
			ELSE
			%	AppearsCount in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg12
				%	LoadSameInMemR rbpArg12,in_arg12,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rbpArg13,in_arg12,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg12,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg12,in_arg12
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG12_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG13_READY) EQ 0
		%	SetType rbpArg13,in_arg13
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rbpArg13,in_arg13
			ELSE
			%	AppearsCount in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg13
				%	LoadSameInMemR rbpArg13,in_arg13,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rbpArg14,in_arg13,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rbpArg13,in_arg13
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG13_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG14_READY) EQ 0
		%	movMem64Arg rbpArg13,in_arg14
		%	ReadyInArgs=ReadyInArgs or IN_ARG14_READY
		ENDIF
	ELSE
	%	LoadEAX rspArg5,in_arg5,IN_ARG5_READY
	%	LoadEAX rspArg6,in_arg6,IN_ARG6_READY
	%	LoadEAX rspArg7,in_arg7,IN_ARG7_READY
	%	LoadEAX rspArg8,in_arg8,IN_ARG8_READY
	%	LoadEAX rspArg9,in_arg9,IN_ARG9_READY
	%	LoadEAX rspArg10,in_arg10,IN_ARG10_READY
	%	LoadEAX rspArg11,in_arg11,IN_ARG11_READY
	%	LoadEAX rspArg12,in_arg12,IN_ARG12_READY
	%	LoadEAX rspArg13,in_arg13,IN_ARG13_READY
	%	LoadEAX rspArg14,in_arg14,IN_ARG14_READY
		IF (ReadyInArgs and IN_ARG1_READY) EQ 0
		%	movReg64Arg rcx,in_arg1
			ReadyInArgs=ReadyInArgs or IN_ARG1_READY
		%	LoadSameInEDX in_arg1,in_arg2,IN_ARG2_READY,rcx,ecx
		%	LoadSameInR8 in_arg1,in_arg3,IN_ARG3_READY,rcx,ecx
		%	LoadSameInR9 in_arg1,in_arg4,IN_ARG4_READY,rcx,ecx
		%	LoadSameInMemR rspArg5,in_arg1,in_arg5,IN_ARG5_READY,rcx,ecx
		%	LoadSameInMemR rspArg6,in_arg1,in_arg6,IN_ARG6_READY,rcx,ecx
		%	LoadSameInMemR rspArg7,in_arg1,in_arg7,IN_ARG7_READY,rcx,ecx
		%	LoadSameInMemR rspArg8,in_arg1,in_arg8,IN_ARG8_READY,rcx,ecx
		%	LoadSameInMemR rspArg9,in_arg1,in_arg9,IN_ARG9_READY,rcx,ecx
		%	LoadSameInMemR rspArg10,in_arg1,in_arg10,IN_ARG10_READY,rcx,ecx
		%	LoadSameInMemR rspArg11,in_arg1,in_arg11,IN_ARG11_READY,rcx,ecx
		%	LoadSameInMemR rspArg12,in_arg1,in_arg12,IN_ARG12_READY,rcx,ecx
		%	LoadSameInMemR rspArg13,in_arg1,in_arg13,IN_ARG13_READY,rcx,ecx
		%	LoadSameInMemR rspArg14,in_arg1,in_arg14,IN_ARG14_READY,rcx,ecx
		ENDIF
		IF (ReadyInArgs and IN_ARG2_READY) EQ 0
		%	movReg64Arg rdx,in_arg2
			ReadyInArgs=ReadyInArgs or IN_ARG2_READY
		%	LoadSameInR8 in_arg2,in_arg3,IN_ARG3_READY,rdx,edx
		%	LoadSameInR9 in_arg2,in_arg4,IN_ARG4_READY,rdx,edx
		%	LoadSameInMemR rspArg5,in_arg2,in_arg5,IN_ARG5_READY,rdx,edx
		%	LoadSameInMemR rspArg6,in_arg2,in_arg6,IN_ARG6_READY,rdx,edx
		%	LoadSameInMemR rspArg7,in_arg2,in_arg7,IN_ARG7_READY,rdx,edx
		%	LoadSameInMemR rspArg8,in_arg2,in_arg8,IN_ARG8_READY,rdx,edx
		%	LoadSameInMemR rspArg9,in_arg2,in_arg9,IN_ARG9_READY,rdx,edx
		%	LoadSameInMemR rspArg10,in_arg2,in_arg10,IN_ARG10_READY,rdx,edx
		%	LoadSameInMemR rspArg11,in_arg2,in_arg11,IN_ARG11_READY,rdx,edx
		%	LoadSameInMemR rspArg12,in_arg2,in_arg12,IN_ARG12_READY,rdx,edx
		%	LoadSameInMemR rspArg13,in_arg2,in_arg13,IN_ARG13_READY,rdx,edx
		%	LoadSameInMemR rspArg14,in_arg2,in_arg14,IN_ARG14_READY,rdx,edx
		ENDIF
		IF (ReadyInArgs and IN_ARG3_READY) EQ 0
		%	movReg64Arg r8,in_arg3
			ReadyInArgs=ReadyInArgs or IN_ARG3_READY
		%	LoadSameInR9 in_arg3,in_arg4,IN_ARG4_READY,r8,r8d
		%	LoadSameInMemR rspArg5,in_arg3,in_arg5,IN_ARG5_READY,r8,r8d
		%	LoadSameInMemR rspArg6,in_arg3,in_arg6,IN_ARG6_READY,r8,r8d
		%	LoadSameInMemR rspArg7,in_arg3,in_arg7,IN_ARG7_READY,r8,r8d
		%	LoadSameInMemR rspArg8,in_arg3,in_arg8,IN_ARG8_READY,r8,r8d
		%	LoadSameInMemR rspArg9,in_arg3,in_arg9,IN_ARG9_READY,r8,r8d
		%	LoadSameInMemR rspArg10,in_arg3,in_arg10,IN_ARG10_READY,r8,r8d
		%	LoadSameInMemR rspArg11,in_arg3,in_arg11,IN_ARG11_READY,r8,r8d
		%	LoadSameInMemR rspArg12,in_arg3,in_arg12,IN_ARG12_READY,r8,r8d
		%	LoadSameInMemR rspArg13,in_arg3,in_arg13,IN_ARG13_READY,r8,r8d
		%	LoadSameInMemR rspArg14,in_arg3,in_arg14,IN_ARG14_READY,r8,r8d
		ENDIF
		IF (ReadyInArgs and IN_ARG4_READY) EQ 0
		%	movReg64Arg r9,in_arg4
			ReadyInArgs=ReadyInArgs or IN_ARG4_READY
		%	LoadSameInMemR rspArg5,in_arg4,in_arg5,IN_ARG5_READY,r9,r9d
		%	LoadSameInMemR rspArg6,in_arg4,in_arg6,IN_ARG6_READY,r9,r9d
		%	LoadSameInMemR rspArg7,in_arg4,in_arg7,IN_ARG7_READY,r9,r9d
		%	LoadSameInMemR rspArg8,in_arg4,in_arg8,IN_ARG8_READY,r9,r9d
		%	LoadSameInMemR rspArg9,in_arg4,in_arg9,IN_ARG9_READY,r9,r9d
		%	LoadSameInMemR rspArg10,in_arg4,in_arg10,IN_ARG10_READY,r9,r9d
		%	LoadSameInMemR rspArg11,in_arg4,in_arg11,IN_ARG11_READY,r9,r9d
		%	LoadSameInMemR rspArg12,in_arg4,in_arg12,IN_ARG12_READY,r9,r9d
		%	LoadSameInMemR rspArg13,in_arg4,in_arg13,IN_ARG13_READY,r9,r9d
		%	LoadSameInMemR rspArg14,in_arg4,in_arg14,IN_ARG14_READY,r9,r9d
		ENDIF
		IF (ReadyInArgs and IN_ARG5_READY) EQ 0
		%	SetType rspArg5,in_arg5
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg5,in_arg5
			ELSE
			%	AppearsCount in_arg5,in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg5
				%	LoadSameInMemR rspArg5,in_arg5,in_arg5,IN_ARG5_READY,rax,eax
				%	LoadSameInMemR rspArg6,in_arg5,in_arg6,IN_ARG6_READY,rax,eax
				%	LoadSameInMemR rspArg7,in_arg5,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rspArg8,in_arg5,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rspArg9,in_arg5,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg5,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg5,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg5,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg5,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg5,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg5,in_arg5
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG5_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG6_READY) EQ 0
		%	SetType rspArg6,in_arg6
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg6,in_arg6
			ELSE
			%	AppearsCount in_arg6,in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg6
				%	LoadSameInMemR rspArg6,in_arg6,in_arg6,IN_ARG6_READY,rax,eax
				%	LoadSameInMemR rspArg7,in_arg6,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rspArg8,in_arg6,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rspArg9,in_arg6,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg6,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg6,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg6,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg6,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg6,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg6,in_arg6
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG6_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG7_READY) EQ 0
		%	SetType rspArg7,in_arg7
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg7,in_arg7
			ELSE
			%	AppearsCount in_arg7,in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg7
				%	LoadSameInMemR rspArg7,in_arg7,in_arg7,IN_ARG7_READY,rax,eax
				%	LoadSameInMemR rspArg8,in_arg7,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rspArg9,in_arg7,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg7,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg7,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg7,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg7,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg7,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg7,in_arg7
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG7_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG8_READY) EQ 0
		%	SetType rspArg8,in_arg8
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg8,in_arg8
			ELSE
			%	AppearsCount in_arg8,in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg8
				%	LoadSameInMemR rspArg8,in_arg8,in_arg8,IN_ARG8_READY,rax,eax
				%	LoadSameInMemR rspArg9,in_arg8,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg8,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg8,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg8,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg8,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg8,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg8,in_arg8
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG8_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG9_READY) EQ 0
		%	SetType rspArg9,in_arg9
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg9,in_arg9
			ELSE
			%	AppearsCount in_arg9,in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg9
				%	LoadSameInMemR rspArg9,in_arg9,in_arg9,IN_ARG9_READY,rax,eax
				%	LoadSameInMemR rspArg10,in_arg9,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg9,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg9,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg9,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg9,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg9,in_arg9
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG9_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG10_READY) EQ 0
		%	SetType rspArg10,in_arg10
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg10,in_arg10
			ELSE
			%	AppearsCount in_arg10,in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg10
				%	LoadSameInMemR rspArg10,in_arg10,in_arg10,IN_ARG10_READY,rax,eax
				%	LoadSameInMemR rspArg11,in_arg10,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg10,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg10,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg10,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg10,in_arg10
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG10_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG11_READY) EQ 0
		%	SetType rspArg11,in_arg11
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg11,in_arg11
			ELSE
			%	AppearsCount in_arg11,in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg11
				%	LoadSameInMemR rspArg11,in_arg11,in_arg11,IN_ARG11_READY,rax,eax
				%	LoadSameInMemR rspArg12,in_arg11,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg11,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg11,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg11,in_arg11
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG11_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG12_READY) EQ 0
		%	SetType rspArg12,in_arg12
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg12,in_arg12
			ELSE
			%	AppearsCount in_arg12,in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg12
				%	LoadSameInMemR rspArg12,in_arg12,in_arg12,IN_ARG12_READY,rax,eax
				%	LoadSameInMemR rspArg13,in_arg12,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg12,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg12,in_arg12
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG12_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG13_READY) EQ 0
		%	SetType rspArg13,in_arg13
			IF (itemOpattr and REG_EXPR)
			%	movMem64Arg rspArg13,in_arg13
			ELSE
			%	AppearsCount in_arg13,in_arg14
				IF __AppearsCount GT 1
				%	movReg64Arg rax,in_arg13
				%	LoadSameInMemR rspArg13,in_arg13,in_arg13,IN_ARG13_READY,rax,eax
				%	LoadSameInMemR rspArg14,in_arg13,in_arg14,IN_ARG14_READY,rax,eax
				ELSE
				%	movMem64Arg rspArg13,in_arg13
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or IN_ARG13_READY
		ENDIF
		IF (ReadyInArgs and IN_ARG14_READY) EQ 0
		%	movMem64Arg rspArg13,in_arg14
		%	ReadyInArgs=ReadyInArgs or IN_ARG14_READY
		ENDIF
	ENDIF
	IF (OPATTR (procname)) EQ (VALID_REF OR IMM_EXPR)
		mov rax,[rcx]
		call procname[rax]
	ELSE
		call procname
	ENDIF
endm
AppearsCount macro appear_string,__in___args:VARARG
__AppearsCount=1
%	FOR parm,<__in___args>
	%	IFIDN <parm>,<appear_string>
			__AppearsCount=__AppearsCount+1
		ENDIF
	ENDM
	IF __AppearsCount LE must_be_gt
		__AppearsCount=1
	ENDIF
endm
LoadEAX macro mem_in_arg,in_argx,in_arg_flag
	IF (ReadyInArgs and in_arg_flag) EQ 0
		RegPosition=@InStr(1,<rax eax ax  al  ah>,<in_argx>)
		IF RegPosition
			movMem64Arg mem_in_arg,in_argx
			ReadyInArgs=ReadyInArgs or in_arg_flag
		ENDIF
	ENDIF
endm
LoadSameInEDX macro in_argx,in_argx2,in_arg_flag,reg64w,reg32w
	IF (ReadyInArgs and in_arg_flag) EQ 0
		IFIDN <in_argx>,<in_argx2>
			IFDIF <in_argx2>,<rdx>
				IF (itemOpattr and REG_EXPR)
					IF (itemSize EQ 8)
						mov rdx,in_arg2
					ELSEIF (itemSize EQ 4)
						regIndex=Reg32Index(in_arg2)
						IF regIndex LT 8
							mov edx,in_arg2
						ELSE
							mov edx,reg32w
						ENDIF
					ELSE
						mov edx,reg32w
					ENDIF
				ELSEIF (itemSize EQ 8) or (itemSize EQ 0)
					mov rdx,reg64w
				ELSEIF (imm_nullification EQ 1) or (imm_nullification EQ 2)
					xor edx,edx
				ELSE
					mov edx,reg32w
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or in_arg_flag
		ENDIF
	ENDIF
endm
LoadSameInR8 macro in_argx,in_argx2,in_arg_flag,reg64w,reg32w
	IF (ReadyInArgs and in_arg_flag) EQ 0
		IFIDN <in_argx>,<in_argx2>
			IFDIF <in_argx2>,<r8>
				IF (itemOpattr and REG_EXPR)
					IF (itemSize EQ 8)
						mov r8,in_argx2
					ELSEIF (itemSize EQ 4)
						mov r8d,in_argx2
					ELSE
						mov r8d,reg32w
					ENDIF
				ELSEIF (itemSize EQ 8) or (itemSize EQ 0)
					mov r8,reg64w
				ELSEIF (imm_nullification EQ 1) or (imm_nullification EQ 2)
					xor r8d,r8d
				ELSE
					mov r8d,reg32w
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or in_arg_flag
		ENDIF
	ENDIF
endm
LoadSameInMemR macro mem_in_arg,in_argx,in_argx2,in_arg_flag,reg64w,reg32w
	IF (ReadyInArgs and in_arg_flag) EQ 0
		IFIDN <in_argx>,<in_argx2>
			IF (itemOpattr and REG_EXPR)
				IF (itemSize EQ 8)
					mov mem_in_arg,in_argx2
				ELSEIF (itemSize EQ 4)
					mov mem_in_arg,in_argx2
				ELSE
					mov mem_in_arg,reg32w
				ENDIF
			ELSE
				IF (imm_nullification EQ 2) or (imm_nullification EQ 3)
					mov mem_in_arg,reg64w
				ELSE
					IF (itemSize EQ 8) or (itemSize EQ 0)
						mov mem_in_arg,reg64w
					ELSE
						mov mem_in_arg,reg32w
					ENDIF
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or in_arg_flag
		ENDIF
	ENDIF
endm
LoadSameInR9 macro in_argx,in_argx2,in_arg_flag,reg64w,reg32w
	IF (ReadyInArgs and in_arg_flag) EQ 0
		IFIDN <in_argx>,<in_argx2>
			IFDIF <in_argx2>,<r9>
				IF (itemOpattr and REG_EXPR)
					IF (itemSize EQ 8)
						mov r9,in_argx2
					ELSEIF (itemSize EQ 4)
						mov r9d,in_argx2
					ELSE
						mov r9d,reg32w
					ENDIF
				ELSEIF (itemSize EQ 8) or (itemSize EQ 0)
					mov r9,reg64w
				ELSEIF (imm_nullification EQ 1) or (imm_nullification EQ 2)
					xor r9d,r9d
				ELSE
					mov r9d,reg32w
				ENDIF
			ENDIF
			ReadyInArgs=ReadyInArgs or in_arg_flag
		ENDIF
	ENDIF
endm
GetVal MACRO NumStr:REQ
%	EXITM <NumStr>
ENDM

comment $Ã‡ÍÓÒ ‰Îˇ Û‰Ó·ÌÓ„Ó ÓÔÂ‰ÂÎÂÌËˇ ‰‡ÌÌ˚ı ‚ ÒÚ‡Ì‰‡ÚÌÓÈ ÒÂÍˆËË ÍÓÌÒÚ‡ÌÚ .const.
œÂÂ‰ ÌÂÍÓÚÓ˚ÏË ÒËÏ‚ÓÎ‡ÏË ÌÂÓ·ıÓ‰ËÏÓ ÒÚ‡‚ËÚ¸ ‚ÓÒÍÎËˆ‡ÚÂÎ¸Ì˚È ÁÌ‡Í.
Õ‡ÔËÏÂ ‚ÏÂÒÚÓ < ‚ÂÁ‰Â ‰ÓÎÊÌÓ ·˚Ú¸ !<, ‡ ‚ÏÂÒÚÓ > ÒÓÓÚ‚ÂÚÒÚ‚ÂÌÌÓ !>$
CONSTANT MACRO string:VARARG
.const
	string
.code
ENDM
comment $Ã‡ÍÓÒ ‰Îˇ Û‰Ó·ÌÓ„Ó ÓÔÂ‰ÂÎÂÌËˇ ‰‡ÌÌ˚ı ‚ ÒÚ‡Ì‰‡ÚÌÓÈ ÒÂÍˆËË ‰‡ÌÌ˚ı .data.
œÂÂ‰ ÌÂÍÓÚÓ˚ÏË ÒËÏ‚ÓÎ‡ÏË ÌÂÓ·ıÓ‰ËÏÓ ÒÚ‡‚ËÚ¸ ‚ÓÒÍÎËˆ‡ÚÂÎ¸Ì˚È ÁÌ‡Í.
Õ‡ÔËÏÂ ‚ÏÂÒÚÓ < ‚ÂÁ‰Â ‰ÓÎÊÌÓ ·˚Ú¸ !<, ‡ ‚ÏÂÒÚÓ > ÒÓÓÚ‚ÂÚÒÚ‚ÂÌÌÓ !>$
STATIC MACRO string:VARARG
.data
	string
.code
ENDM
comment $Ã‡ÍÓÒ ‰Îˇ Û‰Ó·ÌÓ„Ó ÓÔÂ‰ÂÎÂÌËˇ ‰‡ÌÌ˚ı ‚ ÒÚ‡Ì‰‡ÚÌÓÈ ÒÂÍˆËË
ÌÂ ËÌËˆËÎËÁËÓ‚‡ÌÌ˚ı ‰‡ÌÌ˚ı .data?.
œÂÂ‰ ÌÂÍÓÚÓ˚ÏË ÒËÏ‚ÓÎ‡ÏË ÌÂÓ·ıÓ‰ËÏÓ ÒÚ‡‚ËÚ¸ ‚ÓÒÍÎËˆ‡ÚÂÎ¸Ì˚È ÁÌ‡Í.
Õ‡ÔËÏÂ ‚ÏÂÒÚÓ < ‚ÂÁ‰Â ‰ÓÎÊÌÓ ·˚Ú¸ !<, ‡ ‚ÏÂÒÚÓ > ÒÓÓÚ‚ÂÚÒÚ‚ÂÌÌÓ !>$
RESERV MACRO string:VARARG
.data?
align 8
	string
.code
ENDM
unicode MACRO page,string,zero
LOCAL Zstr
	%	FORC char,<string>
			Zstr CATSTR <db '>,<char>,<',>,<page>
		%	Zstr
		ENDM
	%	IFDIF <zero>,<>
			Zstr CATSTR <dw >,<zero>
		%	Zstr
		ENDIF
ENDM
RegIndex macro reg:REQ
LOCAL Index
	Index=Reg64Index(reg)
	IF Index NE NOT_A_REG64
		exitm <@CatStr(%Index)>
	ENDIF
	Index=Reg32Index(reg)
	IF Index NE NOT_A_REG32
		exitm <@CatStr(%Index)>
	ENDIF
	Index=Reg16Index(reg)
	IF Index NE NOT_A_REG16
		exitm <@CatStr(%Index)>
	ENDIF
	Index=Reg8Index(reg)
	exitm <@CatStr(%Index)>
endm
Reg64Index macro reg:REQ
LOCAL Reg64,Reg64Pos
	IF @SizeStr(<reg>) GT 3
		exitm <@CatStr(%NOT_A_REG64)>
	ENDIF
	Reg64 CATSTR < >,ToLower(<reg>),< >
	Reg64Pos INSTR 1,< rax rcx rdx rbx rsp rbp rsi rdi r8  r9  r10 r11 r12 r13 r14 r15 >,Reg64
	IF Reg64Pos NE 0
		Reg64Pos=(Reg64Pos-1) shr 2
	ELSE
		Reg64Pos=NOT_A_REG64
	ENDIF
	exitm <@CatStr(%Reg64Pos)>
endm
Reg32Index macro reg:REQ
LOCAL Reg32,Reg32Pos
	IF @SizeStr(<reg>) GT 4
		exitm <@CatStr(%NOT_A_REG32)>
	ENDIF
	Reg32 CATSTR < >,ToLower(<reg>),< >
	Reg32Pos INSTR 1,<     eax     ecx     edx     ebx     esp     ebp     esi     edi     r8d     r9d    r10d    r11d    r12d    r13d    r14d    r15d >,Reg32
	IF Reg32Pos NE 0
		Reg32Pos=(Reg32Pos-1) shr 3
	ELSE
		Reg32Pos=NOT_A_REG32
	ENDIF
	exitm <@CatStr(%Reg32Pos)>
endm
Reg16Index macro reg:REQ
LOCAL Reg16,Reg16Pos
	IF @SizeStr(<reg>) GT 4
		exitm <@CatStr(%NOT_A_REG16)>
	ENDIF
	Reg16 CATSTR < >,ToLower(<reg>),< >
	Reg16Pos INSTR 1,<      ax      cx      dx      bx      sp      bp      si      di     r8w     r9w    r10w    r11w    r12w    r13w    r14w    r15w >,Reg16
	IF Reg16Pos NE 0
		Reg16Pos=(Reg16Pos-1) shr 3
	ELSE
		Reg16Pos=NOT_A_REG16
	ENDIF
	exitm <@CatStr(%Reg16Pos)>
endm
Reg8Index macro reg:REQ
LOCAL Reg8,Reg8Pos
	IF @SizeStr(<reg>) GT 4
		exitm <@CatStr(%NOT_A_REG8)>
	ENDIF
	Reg8 CATSTR < >,ToLower(<reg>),< >
	Reg8Pos INSTR 1,<      al      cl      dl      bl     spl     bpl     sil     dil     r8b     r9b    r10b    r11b    r12b    r13b    r14b    r15b >,Reg8
	IF Reg8Pos NE 0
		Reg8Pos=(Reg8Pos-1) shr 3
	ELSE
		Reg8Pos=NOT_A_REG8
	ENDIF
	exitm <@CatStr(%Reg8Pos)>
endm
RegHigh8Index macro reg:REQ
LOCAL Reg8,Reg8Pos
	IF @SizeStr(<reg>) GT 4
		exitm <@CatStr(%NOT_A_REG8)>
	ENDIF
	Reg8 CATSTR < >,ToLower(<reg>),< >
	Reg8Pos INSTR 1,<      ah      ch      dh      bh >,Reg8
	IF Reg8Pos NE 0
		Reg8Pos=(Reg8Pos-1) shr 3
	ELSE
		Reg8Pos=NOT_A_REG8
	ENDIF
	exitm <@CatStr(%Reg8Pos)>
endm
GetReg64 macro Index:REQ
	exitm <@SubStr(< rax rcx rdx rbx rsp rbp rsi rdi r8  r9  r10 r11 r12 r13 r14 r15>,4*Index+1,4)>
endm
GetReg32 macro Index:REQ
	exitm <@SubStr(< eax ecx edx ebx esp ebp esi edi r8d r9dr10dr11dr12dr13dr14dr15d>,4*Index+1,4)>
endm
GetReg16 macro Index:REQ
	exitm <@SubStr(<  ax  cx  dx  bx  sp  bp  si  di r8w r9wr10wr11wr12wr13wr14wr15w>,4*Index+1,4)>
endm
GetReg8 macro Index:REQ
	exitm <@SubStr(<  al  cl  dl  bl spl bpl sil dil r8b r9br10br11br12br13br14br15b>,4*Index+1,4)>
endm
GetRegHigh8 macro Index:REQ
	exitm <@SubStr(<ahchdhbh>,2*Index+1,2)>
endm
;—»Ã¬ŒÀ€ ƒÀﬂ »Ã®Õ
IsCharForNames MACRO char
CharPosition INSTR 1,<0123456789abcdefghijklmnopqrstvuwxyzABCDEFGHIJKLMNOPQRSTVUWXYZ_.?$@>,<char>
	EXITM<@CatStr(%CharPosition)>
ENDM
SelectValidSymbols MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char
	SkipState=0
	curr_letter=0
	ph_count=0
	cnt_letter SIZESTR <CondString>
	WHILE cnt_letter
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IF IsCharForNames(%c_char) EQ 0
				IFIDN c_char,<[>
					SkipState=1
				ELSEIFIDN c_char,<(>
					SkipState=2
					ph_count=1
				ELSEIFIDN c_char,<">
					SkipState=5
				ELSEIFIDN c_char,<'>
					SkipState=6
				ELSEIFDIF c_char,< >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ELSEIFIDN c_char,<">
				SkipState=7
			ELSEIFIDN c_char,<'>
				SkipState=8
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=3
			ELSEIFIDN c_char,<'>
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<">
				SkipState=2
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<'>
				SkipState=2
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 7
			IFIDN c_char,<">
				SkipState=1
			ENDIF
		ELSEIF SkipState EQ 8
			IFIDN c_char,<'>
				SkipState=1
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter EQ 0
		curr_letter=0
	ENDIF
	EXITM<@CatStr(%curr_letter)>
ENDM
;;LOCAL 
;fletter TEXTEQU <>
;lletter TEXTEQU <>
;fchar=0
;schar=0
;blchar=0
;lchar=0
;cond_len=0
;reg_ind=NOT_A_REG
;reg_high_ind=NOT_A_REG8
;is_jxcxz=0
sxb equ <sbyte ptr>
sxw equ <sword ptr>
sxd equ <sdword ptr>
sxq equ <sqword ptr>
j_one_bt_pow=0
j_one_bt_pow2=0
j_one_bt_pow3=0
j_one_bt_pow4=0
j_one_bt_uses=1
J_ONE_COND MACRO LabelName,IsTrueCondition,ConditionOne:VARARG
	cond_len SIZESTR <ConditionOne>
	fletter SUBSTR <ConditionOne>,1,1
	lletter SUBSTR <ConditionOne>,cond_len,1
	fchar=0
	schar=0
	lchar=0
	blchar=0
	IF cond_len GE 2
		IFIDN fletter,<(>
			fchar=1
		ELSEIFIDN fletter,<~>
			fchar=2
		ENDIF
		IFIDN @SubStr(<ConditionOne>,2,1),<(>
			schar=1
		ENDIF
		IFIDN lletter,<)>
			lchar=1
		ENDIF
		IFIDN lletter,<?>
			lchar=2
		ENDIF
		IFIDN @SubStr(<ConditionOne>,cond_len-1,1),<?>
			blchar=2
		ENDIF
	ENDIF
	IF fchar EQ 2
		IF (schar EQ 1) AND (lchar EQ 1)
			J_ONE_COND LabelName,(IsTrueCondition xor 1),@SubStr(<ConditionOne>,3,cond_len-3)
		ELSE
			J_ONE_COND LabelName,(IsTrueCondition xor 1),@SubStr(<ConditionOne>,2,cond_len-1)
		ENDIF
	ELSEIF (fchar EQ 1) AND (lchar EQ 1)	
		J_ONE_COND LabelName,IsTrueCondition,@SubStr(<ConditionOne>,2,cond_len-2)
	ELSE
		IF IsTrueCondition EQ FALSE
			NegateChar TEXTEQU <n>
			TrueChar TEXTEQU <>
		ELSE
			NegateChar TEXTEQU <>
			TrueChar TEXTEQU <n>
		ENDIF
		OperatorPos=SelectValidSymbols(ConditionOne)
		IF OperatorPos NE 0
			SingleRunTimeOperator SUBSTR <ConditionOne>,OperatorPos,1
		ELSE
			SingleRunTimeOperator TEXTEQU <>
		ENDIF
		CmpCmd TEXTEQU <>
		JCOND TEXTEQU <>
		IF OperatorPos EQ 0
			IF (OPATTR ConditionOne) EQ (IMM_EXPR OR VALID_REF)
				IF (ConditionOne NE 0)
					IF (IsTrueCondition NE 0)
						JCOND CATSTR <jmp >,<LabelName>
					ENDIF
				ELSEIF IsTrueCondition EQ 0
					JCOND CATSTR <jmp >,<LabelName>
				ENDIF
			ELSE
				IF lchar EQ 2
					IFIDN <ConditionOne>,<SIGN?>
						JCOND CATSTR <j>,NegateChar,<s >,<LabelName>
					ELSEIFIDN <ConditionOne>,<ZERO?>
						JCOND CATSTR <j>,NegateChar,<z >,<LabelName>
					ELSEIFIDN <ConditionOne>,<OVERFLOW?>
						JCOND CATSTR <j>,NegateChar,<o >,<LabelName>
					ELSEIFIDN <ConditionOne>,<PARITY?>
						JCOND CATSTR <j>,NegateChar,<p >,<LabelName>
					ELSEIFIDN <ConditionOne>,<CARRY?>
						JCOND CATSTR <j>,NegateChar,<c >,<LabelName>
					ENDIF
				ENDIF
				IFIDN JCOND,<>
					FirstArg TEXTEQU <ConditionOne>
					reg_ind=RegIndex(%FirstArg)
					reg_high_ind=RegHigh8Index(%FirstArg)
					is_jxcxz=0
					IF (reg_ind EQ 1) AND (IsTrueCondition EQ FALSE)
						IFDIF fletter,<c>
							is_jxcxz=1
						ENDIF
					ENDIF
					IF (is_jxcxz EQ 1)
						JCOND CATSTR <j>,FirstArg,<z >,<LabelName>
					ELSEIF (reg_ind EQ NOT_A_REG) AND (reg_high_ind EQ NOT_A_REG8)
						CmpCmd CATSTR <cmp >,FirstArg,<,0>
						JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
					ELSE
						CmpCmd CATSTR <test >,FirstArg,<,>,FirstArg
						JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
					ENDIF
				ENDIF
			ENDIF
		ELSE
			IF lchar EQ 2
				IFIDN <ConditionOne>,<SIGN?{}OVERFLOW?>
					JCOND CATSTR <j>,NegateChar,<l >,<LabelName>
				ELSEIFIDN <ConditionOne>,<SIGN?~=OVERFLOW?>
					JCOND CATSTR <j>,NegateChar,<l >,<LabelName>
				ELSEIFIDN <ConditionOne>,<SIGN?==OVERFLOW?>
					JCOND CATSTR <j>,NegateChar,<ge >,<LabelName>
				ELSEIFIDN <ConditionOne>,<CARRY?|ZERO?>
					JCOND CATSTR <j>,NegateChar,<be >,<LabelName>
				ENDIF
			ELSEIF (lchar EQ 1) AND (blchar EQ 2)
				IFIDN <ConditionOne>,<ZERO?|(SIGN?{}OVERFLOW?)>
					JCOND CATSTR <j>,NegateChar,<le >,<LabelName>
				ELSEIFIDN <ConditionOne>,<ZERO?|(SIGN?~=OVERFLOW?)>
					JCOND CATSTR <j>,NegateChar,<le >,<LabelName>
				ELSEIFIDN <ConditionOne>,<ZERO?&(SIGN?==OVERFLOW?)>
					JCOND CATSTR <j>,TrueChar,<g >,<LabelName>
				ENDIF
			ENDIF
			IFIDN JCOND,<>
				RunTimeOperator SUBSTR <ConditionOne>,OperatorPos,2
				FirstArg SUBSTR <ConditionOne>,1,OperatorPos-1
				is_signed_expr=0
				first_arg_length SIZESTR FirstArg
				IF first_arg_length GT 10
					IF first_arg_length GT 11
						first_arg_type_spec SUBSTR FirstArg,1,11
						first_arg_type_spec_len=11
					ELSE
						first_arg_type_spec SUBSTR FirstArg,1,10
						first_arg_type_spec_len=10
					ENDIF
					IFIDNI first_arg_type_spec,<sdword ptr >
						is_signed_expr=4
					ELSEIFIDNI first_arg_type_spec,<sqword ptr >
						is_signed_expr=8
					ELSE
						IF first_arg_type_spec_len EQ 11
							first_arg_type_spec SUBSTR first_arg_type_spec,1,10
						ENDIF
						IFIDNI first_arg_type_spec,<sbyte ptr >
							is_signed_expr=1
						ELSEIFIDNI first_arg_type_spec,<sword ptr >
							is_signed_expr=2
						ENDIF
					ENDIF
				ENDIF				
				IF cond_len GE (OperatorPos+2)
					SecondArg SUBSTR <ConditionOne>,OperatorPos+2,cond_len-OperatorPos-1
				ENDIF
				IFIDN RunTimeOperator,<==>		
					JCOND CATSTR <j>,NegateChar,<z >,<LabelName>
				ELSEIFIDN RunTimeOperator,<~=>		
					JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
				ELSEIFIDN RunTimeOperator,<{}>
					JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
				ELSEIFIDN RunTimeOperator,<}=>
					IF is_signed_expr
						JCOND CATSTR <j>,NegateChar,<ge >,<LabelName>
					ELSE
						JCOND CATSTR <j>,NegateChar,<ae >,<LabelName>
					ENDIF
				ELSEIFIDN RunTimeOperator,<{=>
					IF is_signed_expr
						JCOND CATSTR <j>,NegateChar,<le >,<LabelName>
					ELSE
						JCOND CATSTR <j>,NegateChar,<be >,<LabelName>
					ENDIF
				ELSEIFIDN RunTimeOperator,<={>
					IF is_signed_expr
						JCOND CATSTR <j>,NegateChar,<le >,<LabelName>
					ELSE
						JCOND CATSTR <j>,NegateChar,<be >,<LabelName>
					ENDIF
				ELSEIFIDN RunTimeOperator,<&&>
					IFIDN SecondArg,<SIGN?>
						reg_ind=RegIndex(%FirstArg)
						reg_high_ind=RegHigh8Index(%FirstArg)
						IF (reg_ind EQ NOT_A_REG) AND (reg_high_ind EQ NOT_A_REG8)
							CmpCmd TEXTEQU <cmp >,FirstArg,<,0>
						ELSE
							CmpCmd TEXTEQU <test >,FirstArg,<,>,FirstArg
						ENDIF
						JCOND CATSTR <j>,NegateChar,<s >,<LabelName>
					ELSE
						CmpCmd CATSTR <test >,FirstArg,<,>,SecondArg
						JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
					ENDIF
				ENDIF
				IFIDN JCOND,<>
					SecondArg SUBSTR <ConditionOne>,OperatorPos+1,cond_len-OperatorPos
					IFIDN SingleRunTimeOperator,<}>
						IF is_signed_expr
							JCOND CATSTR <j>,NegateChar,<g >,<LabelName>
						ELSE
							JCOND CATSTR <j>,NegateChar,<a >,<LabelName>
						ENDIF
					ELSEIFIDN SingleRunTimeOperator,<{>
						IF is_signed_expr
							JCOND CATSTR <j>,NegateChar,<l >,<LabelName>
						ELSE
							JCOND CATSTR <j>,NegateChar,<b >,<LabelName>
						ENDIF
					ELSEIFIDN SingleRunTimeOperator,<|>
						CmpCmd CATSTR <or >,FirstArg,<,>,SecondArg
						JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
					ELSEIFIDN SingleRunTimeOperator,<&>
						IFIDN SecondArg,<SIGN?>
							reg_ind=RegIndex(%FirstArg)
							reg_high_ind=RegHigh8Index(%FirstArg)
							IF (reg_ind EQ NOT_A_REG) AND (reg_high_ind EQ NOT_A_REG8)
								CmpCmd TEXTEQU <cmp >,FirstArg,<,0>
							ELSE
								CmpCmd TEXTEQU <test >,FirstArg,<,>,FirstArg
							ENDIF
							JCOND CATSTR <j>,NegateChar,<s >,<LabelName>
						ELSEIF ((OPATTR (SecondArg)) EQ VIMM_EXPR) AND (TYPE FirstArg GT 1) AND (j_one_bt_uses EQ 1)
							j_one_bt_pow=0
							j_one_bt_pow4=0
							IF (SecondArg) EQ 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow2=(SecondArg) AND 0FFFFFFFFh
							j_one_bt_pow3=(SecondArg) SHR 32
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=32
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 16
							j_one_bt_pow2=j_one_bt_pow2 AND 0FFFFh
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+16
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 8
							j_one_bt_pow2=j_one_bt_pow2 AND 0FFh
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+8
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 4
							j_one_bt_pow2=j_one_bt_pow2 AND 0Fh
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+4
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 2
							j_one_bt_pow2=j_one_bt_pow2 AND 11y
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+2
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							j_one_bt_pow3=j_one_bt_pow2 SHR 1
							j_one_bt_pow2=j_one_bt_pow2 AND 1y
							IF j_one_bt_pow2 EQ 0
								j_one_bt_pow=j_one_bt_pow+1
								j_one_bt_pow2=j_one_bt_pow3
							ELSEIF j_one_bt_pow3 NE 0
								j_one_bt_pow4=-1
							ENDIF
							IF j_one_bt_pow4 EQ 0
								j_one_bt_pow4=((TYPE FirstArg) EQ 2) AND (j_one_bt_pow EQ 15)
								j_one_bt_pow4=j_one_bt_pow4 OR (((TYPE FirstArg) EQ 4) AND (j_one_bt_pow EQ 31))
								j_one_bt_pow4=j_one_bt_pow4 OR (((TYPE FirstArg) EQ 8) AND (j_one_bt_pow EQ 63))
								IF j_one_bt_pow4 EQ 0
									CmpCmd CATSTR <bt >,FirstArg,<,>,@CatStr(%j_one_bt_pow)
									JCOND CATSTR <j>,NegateChar,<c >,<LabelName>
								ELSE
									reg_ind=RegIndex(%FirstArg)
									IF reg_ind EQ NOT_A_REG
										CmpCmd TEXTEQU <cmp >,FirstArg,<,0>
									ELSE
										CmpCmd TEXTEQU <test >,FirstArg,<,>,FirstArg
									ENDIF
									JCOND CATSTR <j>,NegateChar,<s >,<LabelName>
								ENDIF
							ELSE
								CmpCmd CATSTR <test >,FirstArg,<,>,SecondArg
								JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
							ENDIF
						ELSE
							CmpCmd CATSTR <test >,FirstArg,<,>,SecondArg
							JCOND CATSTR <j>,TrueChar,<z >,<LabelName>
						ENDIF
					ELSE
						.err <Bad conditional operator.>
					ENDIF
				ENDIF
				IFDIF SecondArg,<>
					IFIDN CmpCmd,<>
						CmpCmd CATSTR <cmp >,FirstArg,<,>,SecondArg
					ENDIF
				ENDIF
			ENDIF
		ENDIF
		CmpCmd
		JCOND	
	ENDIF
ENDM
GetIfsPosition MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator,total_conds,ph_count
	SkipState=0
	curr_letter=0
	cnt_letter SIZESTR <CondString>
	IF cnt_letter LT 6
		EXITM<0>
	ENDIF
	ph_count=0
	WHILE cnt_letter GT 5
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,<(>
				SkipState=4
				ph_count=1
			ELSEIFIDN c_char,< >
				c_log_operator SUBSTR <CondString>,curr_letter,5
				IFIDN c_log_operator,< .if >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ELSEIFIDN c_char,<">
				SkipState=7
			ELSEIFIDN c_char,<'>
				SkipState=8
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=5
			ELSEIFIDN c_char,<'>
				SkipState=6
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 7
			IFIDN c_char,<">
				SkipState=1
			ENDIF
		ELSEIF SkipState EQ 8
			IFIDN c_char,<'>
				SkipState=1
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter LE 5
		EXITM<0>
	ENDIF
	EXITM<@CatStr(%curr_letter)>
ENDM
SelectOrValidConds MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator,total_conds,ph_count
	SkipState=0
	curr_letter=0
	cnt_letter SIZESTR <CondString>
	IF cnt_letter LT 6
		EXITM<0>
	ENDIF
	ph_count=0
	WHILE cnt_letter GT 4
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,<(>
				SkipState=4
				ph_count=1
			ELSEIFIDN c_char,< >
				c_log_operator SUBSTR <CondString>,curr_letter,4
				IFIDN c_log_operator,< || >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=5
			ELSEIFIDN c_char,<'>
				SkipState=6
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=4
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter LE 4
		EXITM<0>
	ENDIF
	EXITM<@CatStr(%curr_letter)>
ENDM
SelectValidCond MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator,total_conds,ph_count
	SkipState=0
	curr_letter=0
	cnt_letter SIZESTR <CondString>
	IF cnt_letter LT 6
		EXITM<0>
	ENDIF
	ph_count=0
	WHILE cnt_letter GT 4
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,<(>
				SkipState=4
				ph_count=1
			ELSEIFIDN c_char,< >
				c_log_operator SUBSTR <CondString>,curr_letter,4
				IFIDN c_log_operator,< || >
					EXITM
				ELSEIFIDN c_log_operator,< && >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=5
			ELSEIFIDN c_char,<'>
				SkipState=6
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=4
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter LE 4
		EXITM<0>
	ENDIF
	EXITM<@CatStr(%curr_letter)>
ENDM
IsSingleCond MACRO CondString:VARARG
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator
	SkipState=0
	curr_letter=0
	cnt_letter SIZESTR <CondString>
	IF cnt_letter LT 6
		EXITM<1>
	ENDIF
	WHILE cnt_letter GT 4
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,< >
				c_log_operator SUBSTR <CondString>,curr_letter,4
				IFIDN c_log_operator,< || >
					EXITM
				ELSEIFIDN c_log_operator,< && >
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter GT 4
		EXITM<0>
	ENDIF
	EXITM<1>
ENDM
IntermedLabel=0
J_POLY_COND MACRO LabelName,TrueConditions,ConditionsString:VARARG
LOCAL BeginCond,EndCond,LogOperator,locLabel,SetLabel,IsTrueConditions,NegCond,EndLabel,LastConds
	BeginCond=1
	EndCond=1
	SetLabel=0
	NegCond=0
	LastConds=0
	IsTrueConditions=TrueConditions
	IF IsSingleCond(<ConditionsString>) NE 0
		J_ONE_COND LabelName,IsTrueConditions,ConditionsString
	ELSE
		EndLabel CATSTR <intermedloc_>,@CatStr(%IntermedLabel)
		IntermedLabel=IntermedLabel+1
		SetLabel=0
		LogOperator=0
	:NextCond
		IFIDN @SubStr(<ConditionsString>,BeginCond,2),<~(>
			IsTrueConditions=IsTrueConditions xor 1
			BeginCond=BeginCond+1
			NegCond=1
		ENDIF
		EndCond=SelectValidCond(@SubStr(<ConditionsString>,BeginCond,@SizeStr(<ConditionsString>)-BeginCond+1))
		IF EndCond EQ 0
			EndCond=@SizeStr(<ConditionsString>)+1
			LogOperator=0
		ELSE
			EndCond=EndCond+BeginCond-1
			LogOperator=EndCond
		ENDIF
		IFIDN @SubStr(<ConditionsString>,BeginCond,1),<(>
			BeginCond=BeginCond+1
			EndCond=EndCond-1
			IF NegCond EQ 1
				IF IsSingleCond(@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)) EQ 1
					IsTrueConditions=IsTrueConditions xor 1
					BeginCond=BeginCond-2
					EndCond=EndCond+1
					NegCond=0
				ENDIF
			ENDIF
		ENDIF
		IF LogOperator EQ 0
			J_POLY_COND LabelName,IsTrueConditions,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
			IF SetLabel NE 0
				locLabel:
			ENDIF
			EndLabel:
			GOTO EndConditions
		ENDIF
		IF SetLabel EQ 0
			IFIDN @SubStr(<ConditionsString>,LogOperator,4),< || >
				IF IsTrueConditions NE 0
					J_POLY_COND LabelName,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
					GOTO forward
				ELSE
					J_POLY_COND EndLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
					GOTO forward
				ENDIF
			ELSE
				SetLabel=1
				locLabel CATSTR <intermedloc_>,@CatStr(%IntermedLabel)
				IntermedLabel=IntermedLabel+1
				RemnConds SUBSTR <ConditionsString>,LogOperator+4,@SizeStr(<ConditionsString>)-LogOperator-3
				LastConds=1
				IF (@SizeStr(RemnConds) NE 0) AND (SelectOrValidConds(RemnConds) NE 0)
					LastConds=0
				ENDIF
				IF IsTrueConditions EQ 0
					IF LastConds EQ 1
						IF NegCond EQ 1
							J_POLY_COND locLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
						ELSE
							J_POLY_COND LabelName,0,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
						ENDIF
						GOTO forward
					ELSE
						J_POLY_COND locLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
						GOTO forward
					ENDIF
				ELSE
					IF (LastConds EQ 1) AND (NegCond EQ 1)
						J_POLY_COND LabelName,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
						GOTO forward
					ENDIF
					J_POLY_COND locLabel,0,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
				ENDIF
			ENDIF
			GOTO forward
		ELSE
			IFIDN @SubStr(<ConditionsString>,LogOperator,4),< || >
				IF IsTrueConditions NE 0
					J_POLY_COND LabelName,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
				ELSE
					J_POLY_COND EndLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
				ENDIF
				locLabel:
				SetLabel=0
			ELSEIF IsTrueConditions EQ 0
				IF LastConds EQ 1
					J_POLY_COND LabelName,0,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
					GOTO forward
				ELSE
					J_POLY_COND locLabel,1,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
					GOTO forward
				ENDIF
			ELSE
				J_POLY_COND locLabel,0,@SubStr(<ConditionsString>,BeginCond,EndCond-BeginCond)
			ENDIF
		ENDIF
		:forward
		IF NegCond EQ 1
			IsTrueConditions=IsTrueConditions xor 1
			NegCond=0
		ENDIF		
		BeginCond=LogOperator+4
		IF IsSingleCond(@SubStr(<ConditionsString>,BeginCond,@SizeStr(<ConditionsString>)-BeginCond+1)) EQ 1
		%	J_POLY_COND LabelName,IsTrueConditions,@SubStr(<ConditionsString>,BeginCond,@SizeStr(<ConditionsString>)-BeginCond+1)
			IF SetLabel NE 0
				locLabel:
			ENDIF
			EndLabel:
			GOTO EndConditions
		ENDIF
		GOTO NextCond
	ENDIF
:EndConditions
ENDM
.goto MACRO IfCondString:VARARG
	IfsPos=GetIfsPosition(IfCondString)
	IF IfsPos NE 0
		gtLabel SUBSTR <IfCondString>,1,(IfsPos-1)
		gtConds SUBSTR <IfCondString>,IfsPos+5,@SizeStr(IfCondString)+1-(IfsPos+5)
		gtLabelAttr=(OPATTR gtLabel)
		IF (gtLabelAttr AND MEM_EXPR)
		%	.if gtConds
				jmp gtLabel
			.endif
		ELSE
		%	J_POLY_COND gtLabel,1,gtConds
		ENDIF	
	ELSE
		jmp IfCondString
	ENDIF
ENDM
.esc MACRO IfCondString:VARARG
	GetOutLabel
	IFIDN <IfCondString>,<>
		jmp LastOutLabel
	ELSE
		gtConds SUBSTR <IfCondString>,5
	%	J_POLY_COND LastOutLabel,1,gtConds
	ENDIF
ENDM
c2asmhex MACRO c_num:REQ
LOCAL lenc,asm_hex
	lenc=@SizeStr(<c_num>)
	IF (lenc GT 2)
		IF (@InStr(1,<c_num>,<0X>) EQ 1) OR (@InStr(1,<c_num>,<0x>) EQ 1)
			asm_hex CATSTR <0>,@SubStr(<c_num>,3,(lenc-2)),<h>
		ELSE
			asm_hex	TEXTEQU <c_num>
		ENDIF
	ELSE
		asm_hex	TEXTEQU <c_num>
	ENDIF
	EXITM <asm_hex>	
ENDM
DEFINE_GUID MACRO iid_name,Data1,Data2,Data3,Data4_0,Data4_1,Data4_2,Data4_3,Data4_4:REQ,Data4_5,Data4_6,Data4_7
iid_name LABEL GUID
	dd c2asmhex(Data1)
	dw c2asmhex(Data2)
	dw c2asmhex(Data3)
	db c2asmhex(Data4_0)
	db c2asmhex(Data4_1)
	db c2asmhex(Data4_2)
	db c2asmhex(Data4_3)
	db c2asmhex(Data4_4)
	db c2asmhex(Data4_5)
	db c2asmhex(Data4_6)
	db c2asmhex(Data4_7)
	EXITM<>
ENDM
pushm MACRO args:VARARG
TEX TEXTEQU <>
address TEXTEQU <>
FOR item,<args>
	IF @SizeStr(<item>) GE 6
		TEX SUBSTR <item>,1,4
		address SUBSTR <item>, 6, @SizeStr(<item>) - 5
		IFIDN TEX,<addr>
			lea rax,address
			push rax
		ELSEIFIDN TEX,<ADDR>
			lea rax,address
			push rax
		ELSEIFIDN TEX,<Addr>
			lea rax,address
			push rax
		ELSE
			push item
		ENDIF
	ELSE
		push item
	ENDIF
ENDM
ENDM
altm MACRO Consts:VARARG
    EXITM <>
ENDM
pword TYPEDEF PTR FAR16
vstrstr MACRO CondString,__SubStr__,InitialPos:=<0>
;;LOCAL SkipState,cnt_letter,curr_letter,c_char,c_log_operator,total_conds,ph_count
	SkipState=0
	curr_letter=InitialPos
	cnt_letter SIZESTR <CondString>
	cnt_letter=cnt_letter-curr_letter
	__SubStr__len SIZESTR <__SubStr__>
	IF cnt_letter LT __SubStr__len
		EXITM<0>
	ENDIF
	ph_count=0
	WHILE cnt_letter GE __SubStr__len
		curr_letter=curr_letter+1
		c_char SUBSTR <CondString>,curr_letter,1
		IF SkipState EQ 0
			IFIDN c_char,<[>
				SkipState=1
			ELSEIFIDN c_char,<">
				SkipState=2
			ELSEIFIDN c_char,<'>
				SkipState=3
			ELSEIFIDN c_char,<(>
				SkipState=4
				ph_count=1
			ELSE
				c_log_operator SUBSTR <CondString>,curr_letter,__SubStr__len
				IFIDN c_log_operator,<__SubStr__>
					cnt_letter=1000
					EXITM
				ENDIF
			ENDIF
		ELSEIF SkipState EQ 1
			IFIDN c_char,<]>
				SkipState=0
			ELSEIFIDN c_char,<">
				SkipState=7
			ELSEIFIDN c_char,<'>
				SkipState=8
			ENDIF
		ELSEIF SkipState EQ 2
			IFIDN c_char,<">
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 3
			IFIDN c_char,<'>
				SkipState=0
			ENDIF
		ELSEIF SkipState EQ 4
			IFIDN c_char,<)>
				ph_count=ph_count-1
				IF ph_count EQ 0
					SkipState=0
				ENDIF
			ELSEIFIDN c_char,<(>
				ph_count=ph_count+1
			ELSEIFIDN c_char,<">
				SkipState=5
			ELSEIFIDN c_char,<'>
				SkipState=6
			ENDIF
		ELSEIF SkipState EQ 5
			IFIDN c_char,<">
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 6
			IFIDN c_char,<'>
				SkipState=4
			ENDIF
		ELSEIF SkipState EQ 7
			IFIDN c_char,<">
				SkipState=1
			ENDIF
		ELSEIF SkipState EQ 8
			IFIDN c_char,<'>
				SkipState=1
			ENDIF
		ENDIF
		cnt_letter=cnt_letter-1
	ENDM
	IF cnt_letter GE __SubStr__len
		EXITM<@CatStr(%curr_letter)>
	ENDIF
	EXITM<0>
ENDM
defined MACRO Arg1:REQ
	IFDEF Arg1
		EXITM<1>
	ENDIF
	EXITM<0>
ENDM
;œ–Œ“Œ“»œ€ Ã¿ –Œ—Œ¬
v MACRO vl_expr:VARARG
	
ENDM
v1 MACRO vl_expr:VARARG
	
ENDM
v2 MACRO vl_expr:VARARG
	
ENDM
v3 MACRO vl_expr:VARARG
	
ENDM
v4 MACRO vl_expr:VARARG
	
ENDM
v1 MACRO vl_expr:VARARG
LOCAL vl_def_add,vl_cpos,vl_expr_len,vl_dest,vl_plus
	vl_def_add=0
	vl_expr_len SIZESTR <vl_expr>
	vl_cpos=vstrstr(<vl_expr>,<=>)+1
	vl_dest SUBSTR <vl_expr>,1,(vl_cpos-2)
	vl_char SUBSTR <vl_expr>,(vl_cpos-3),2
	IFIDN vl_char,<}}>
		vl_dest SUBSTR <vl_expr>,1,(vl_cpos-4)
		vl_def_add=1
		GOTO vl_loop
	ENDIF
	IFIDN vl_char,<{{>
		vl_dest SUBSTR <vl_expr>,1,(vl_cpos-4)
		vl_def_add=2
		GOTO vl_loop
	ENDIF
	;;;;;; ”ÃÕŒ∆≈Õ»≈ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	vl_char SUBSTR <vl_expr>,(vl_cpos-2),1
	IFIDN vl_char,<*>
		vl_dest SUBSTR <vl_expr>,1,(vl_cpos-3)
		vl_def_add=3
		GOTO vl_loop
	ENDIF
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	vl_ph=0								;;»Õ»÷»¿À»«¿÷»ﬂ Ã≈—“¿ Õ¿«Õ¿◊≈Õ»ﬂ œ≈–¬€Ã ¿–√”Ã≈Õ“ŒÃ
	vl_char SUBSTR <vl_expr>,vl_cpos,1	;;œŒ»—  ¿–√”Ã≈Õ“¿
	IFIDN vl_char,<(>					;;¬€–¿∆≈Õ»≈ ¬ — Œ¡ ¿’
		vl_ph=1
	ENDIF
	IFIDN vl_char,<&>
		vl_ph=2
	ENDIF
	IF vl_cpos GT vl_expr_len
		GOTO vl_exit
	ENDIF
	vl_def_add=1
	vl_plus=vstrstr(<vl_expr>,<}}>,vl_cpos)
	vl_plus2=vstrstr(<vl_expr>,<{{>,vl_cpos)
	IF vl_plus
		IF vl_plus2 AND (vl_plus2 LT vl_plus)
			vl_def_add=2
			vl_plus=vl_plus2
		ENDIF
	ELSE
		vl_def_add=2
		vl_plus=vl_plus2
	ENDIF
	;;;;;; ”ÃÕŒ∆≈Õ»≈ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	vl_plus2=vstrstr(<vl_expr>,<*>,vl_cpos)
	IF vl_plus
		IF vl_plus2 AND (vl_plus2 LT vl_plus)
			vl_def_add=3
			vl_plus=vl_plus2
		ENDIF
	ELSE
		vl_def_add=3
		vl_plus=vl_plus2
	ENDIF
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	IF vl_plus NE 0			;Õ¿ —À”◊¿… ¡ŒÀ≈≈ ◊≈Ã ŒƒÕŒ√Œ ¿–√”Ã≈Õ“¿
		GOTO v1_many_args
	ENDIF
	vl_char2 SUBSTR <vl_expr>,vl_expr_len,1
	IF vl_ph EQ 1	;;≈—À» ¬€–¿∆≈Õ»≈ Õ≈ ÷≈À» ŒÃ ¬ — Œ¡ ¿’
		IFDIF vl_char2,<)>
			vl_ph=0
		ENDIF
	ENDIF
	IF vl_ph EQ 1	;;–¿— –€“»≈ — Œ¡Œ 
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_expr_len-vl_cpos-1)
		vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
		IF vl_add EQ 1
		%	movst vl_dest,____v_last_arg
		ELSE
		%	v vl_dest=____v_last_arg
		ENDIF
		GOTO vl_exit
	ENDIF
	IF vl_ph EQ 2
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1
		lea vl_dest,____v_last_arg
		GOTO vl_exit
	ENDIF
	____v_last_arg SUBSTR <vl_expr>,vl_cpos
	vl_plus=vstrstr(<%____v_last_arg>,<~>)+vstrstr(<%____v_last_arg>,<|>)+vstrstr(<%____v_last_arg>,<^>)
	IF vl_plus EQ 0 AND ((OPATTR (____v_last_arg)) AND (VALID_REF))
	%	movst vl_dest,____v_last_arg
		GOTO vl_exit
	ENDIF
%	v vl_dest=____v_last_arg
	GOTO vl_exit
:v1_many_args
	vl_char2 SUBSTR <vl_expr>,vl_plus-1,1
	IF vl_ph EQ 1
		IFDIF vl_char2,<)>
			vl_ph=0
		ENDIF
	ENDIF
	IF vl_ph EQ 1
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-1-vl_cpos-1)
		vl_ph=vstrstr(<%____v_last_arg>,<|>)+vstrstr(<%____v_last_arg>,<^>)
		vl_ph=vl_ph+vstrstr(<%____v_last_arg>,< and >)+vstrstr(<%____v_last_arg>,<~>)
		vl_ph=vl_ph+vstrstr(<%____v_last_arg>,<}}>)+vstrstr(<%____v_last_arg>,<{{>)
		IF vl_ph
		%	v vl_dest=____v_last_arg
			GOTO pre_vl_loop
		ENDIF
		vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
		IF vl_add EQ 1
		%	movst vl_dest,____v_last_arg
			GOTO pre_vl_loop
		ENDIF
	%	v vl_dest=____v_last_arg
	ELSEIF vl_ph EQ 2
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-vl_cpos-1)
		lea vl_dest,____v_last_arg
	ELSE
		____v_last_arg SUBSTR <vl_expr>,vl_cpos,(vl_plus-vl_cpos)
		vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
		IF vl_add EQ 1
		%	movst vl_dest,____v_last_arg
		ELSE
			vl_add=((OPATTR (____v_last_arg)) AND (VALID_REF))
			vl_ph=vstrstr(<%____v_last_arg>,<+>)+vstrstr(<%____v_last_arg>,<->)
			vl_ph=vl_ph+vstrstr(<%____v_last_arg>,< and >)+vstrstr(<%____v_last_arg>,<~>)
			vl_ph=vl_ph+vstrstr(<%____v_last_arg>,<|>)+vstrstr(<%____v_last_arg>,<^>)
			IF vl_ph OR (vl_add EQ 0)
			%	v vl_dest=____v_last_arg
			ELSE
			%	movst vl_dest,____v_last_arg
			ENDIF
		ENDIF
	ENDIF
:pre_vl_loop
	vl_cpos=vl_plus+2	;;Ã≈—“Œ Õ¿«Õ¿◊≈Õ»ﬂ «¿√–”∆≈ÕŒ œ≈–¬€Ã —À¿√¿≈Ã€Ã
	IF vl_def_add EQ 3
		vl_cpos=vl_cpos-1
	ENDIF
:vl_loop
	WHILE vl_cpos LE vl_expr_len	;;Õ¿  ¿∆ƒŒ… »““≈–¿÷»» Œ¡–¿¡¿“€¬¿≈“—ﬂ 1 ¿–√”Ã≈Õ“
		vl_add=vl_def_add
		vl_ph=0
		vl_char SUBSTR <vl_expr>,vl_cpos,1
		IFIDN vl_char,<(>
			vl_ph=1
		ENDIF
		IFIDN vl_char,<&>
			vl_ph=2
		ENDIF
		IF vl_cpos GT vl_expr_len
			EXITM
		ENDIF
		vl_def_add=1
		vl_plus=vstrstr(<vl_expr>,<}}>,vl_cpos)
		vl_plus2=vstrstr(<vl_expr>,<{{>,vl_cpos)
		IF vl_plus
			IF vl_plus2 AND (vl_plus2 LT vl_plus)
				vl_def_add=2
				vl_plus=vl_plus2
			ENDIF
		ELSE
			vl_def_add=2
			vl_plus=vl_plus2
		ENDIF
		;;;;;; ”ÃÕŒ∆≈Õ»≈ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		vl_plus2=vstrstr(<vl_expr>,<*>,vl_cpos)
		IF vl_plus
			IF vl_plus2 AND (vl_plus2 LT vl_plus)
				vl_def_add=3
				vl_plus=vl_plus2
			ENDIF
		ELSE
			vl_def_add=3
			vl_plus=vl_plus2
		ENDIF
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		IF vl_plus EQ 0		;;Œ¡–¿¡Œ“ ¿ œŒ—À≈ƒÕ≈√Œ ¿–√”Ã≈Õ“¿
			vl_char2 SUBSTR <vl_expr>,vl_expr_len,1
			IF vl_ph EQ 1
				IFDIF vl_char2,<)>
					vl_ph=0
				ENDIF
			ENDIF
			IF vl_ph EQ 1	;–¿— –€“»≈ — Œ¡Œ 
				____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_expr_len-vl_cpos-1)
				vl_ph=vstrstr(<%____v_last_arg>,<+>)+vstrstr(<%____v_last_arg>,<->)
				vl_ph=vl_ph+vstrstr(<%____v_last_arg>,< and >)+vstrstr(<%____v_last_arg>,<~>)
				vl_ph=vl_ph+vstrstr(<%____v_last_arg>,<|>)+vstrstr(<%____v_last_arg>,<^>)
				IF vl_ph EQ 0
					IF vl_add EQ 1
						vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
						vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
						IF vl_add
							vl_ph=@CatStr(%(____v_last_arg))
							IF vl_ph
								shr vl_dest,____v_last_arg
							ENDIF
						ELSEIF vl_ph
							shr vl_dest,____v_last_arg
						ELSE
						%	v cl=____v_last_arg
							shr vl_dest,cl
						ENDIF
					ELSEIF vl_add EQ 2
						vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
						vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
						IF vl_add
							vl_ph=@CatStr(%(____v_last_arg))
							IF vl_ph
								shl vl_dest,____v_last_arg
							ENDIF
						ELSEIF vl_ph
							shl vl_dest,____v_last_arg
						ELSE
						%	v cl=____v_last_arg
							shl vl_dest,cl
						ENDIF
					ELSEIF vl_add EQ 3
						imul vl_dest,____v_last_arg
					ENDIF
				ELSE
					vl_ph=vstrstr(<%____v_last_arg>,<|>)+vstrstr(<%____v_last_arg>,<^>)
					IF vl_ph
						IF vl_add EQ 1
						%	v cl=____v_last_arg
							shr vl_dest,cl
						ELSEIF vl_add EQ 2
						%	v cl=____v_last_arg
							shl vl_dest,cl
						ELSEIF vl_add EQ 3
							imul vl_dest,____v_last_arg
						ENDIF
					ELSE
						vl_ph=vstrstr(<%____v_last_arg>,< and >)
						IF vl_ph
							IF vl_add EQ 1
							%	v4 cl=____v_last_arg
								shr vl_dest,cl
							ELSEIF vl_add EQ 2
							%	v4 cl=____v_last_arg
								shl vl_dest,cl
							ELSEIF vl_add EQ 3
								imul vl_dest,____v_last_arg
							ENDIF
						ELSE
							vl_ph=vstrstr(<%____v_last_arg>,<~>)
							IF vl_ph
								IF vl_add EQ 1
								%	v4 cl=____v_last_arg
									shr vl_dest,cl
								ELSEIF vl_add EQ 2
								%	v4 cl=____v_last_arg
									shl vl_dest,cl
								ELSEIF vl_add EQ 3
									imul vl_dest,____v_last_arg
								ENDIF
								GOTO mac_label1
							ENDIF
							IF vl_add EQ 1
							%	v2 cl=____v_last_arg
								shr vl_dest,cl
								GOTO mac_label1
							ENDIF
							IF vl_add EQ 2
							%	v2 cl=____v_last_arg
								shl vl_dest,cl
								GOTO mac_label1
							ENDIF
							IF vl_add EQ 3
								imul vl_dest,____v_last_arg
							ENDIF
						ENDIF
					ENDIF
				ENDIF
			:mac_label1
				vl_cpos=vl_expr_len+1
				GOTO v1_terminal	
			ENDIF
			IF vl_ph EQ 2
				____v_last_arg SUBSTR <vl_expr>,(vl_cpos+1)
				lea rcx,____v_last_arg
				IF vl_add EQ 1
					shr vl_dest,cl
				ELSEIF vl_add EQ 2
					shl vl_dest,cl
				ELSEIF vl_add EQ 3
					imul vl_dest,rcx
				ENDIF
				EXITM
			ENDIF
			____v_last_arg SUBSTR <vl_expr>,vl_cpos
			IF vl_add EQ 1
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
				IF (vl_add OR vl_ph)
					shr vl_dest,____v_last_arg
				ELSE
				%	v cl=____v_last_arg
					shr vl_dest,cl
				ENDIF
			ELSEIF vl_add EQ 2
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
				IF (vl_add OR vl_ph)
					shl vl_dest,____v_last_arg
				ELSE
				%	v cl=____v_last_arg
					shl vl_dest,cl
				ENDIF
			ELSEIF vl_add EQ 3
				imul vl_dest,____v_last_arg
			ENDIF
			EXITM
		ENDIF
		vl_char2 SUBSTR <vl_expr>,vl_plus-1,1
		IF vl_ph EQ 1
			IFDIF vl_char2,<)>
				vl_ph=0
			ENDIF
		ENDIF
		IF vl_ph EQ 1		;;Œ¡–¿¡Œ“ ¿ Œ◊≈–≈ƒÕŒ√Œ ¿–√”Ã≈Õ“¿
			____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-1-vl_cpos-1)
			IF vl_add EQ 1
				vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add OR vl_ph
					shr vl_dest,____v_last_arg
				ELSE
				%	v cl=____v_last_arg
					shr vl_dest,cl
				ENDIF
			ELSEIF vl_add EQ 2
				vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add OR vl_ph
					shl vl_dest,____v_last_arg
				ELSE
				%	v cl=____v_last_arg
					shl vl_dest,cl
				ENDIF
			ELSEIF vl_add EQ 3
				imul vl_dest,____v_last_arg
			ENDIF
		ELSEIF vl_ph EQ 2
			____v_last_arg SUBSTR <vl_expr>,(vl_cpos+1),(vl_plus-vl_cpos)
			lea rcx,____v_last_arg
			IF vl_def_add EQ 1
				shr vl_dest,cl
			ELSEIF vl_def_add EQ 2
				shl vl_dest,cl
			ELSEIF vl_add EQ 3
				imul vl_dest,rcx
			ENDIF
		ELSE
			____v_last_arg SUBSTR <vl_expr>,vl_cpos,(vl_plus-vl_cpos)
			IF vl_add EQ 1
				vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF (vl_add OR vl_ph)
					shr vl_dest,____v_last_arg
				ELSE
				%	v cl=____v_last_arg
					shr vl_dest,cl
				ENDIF
			ELSEIF vl_add EQ 2
				vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF (vl_add OR vl_ph)
					shl vl_dest,____v_last_arg
				ELSE
				%	v cl=____v_last_arg
					shl vl_dest,cl
				ENDIF
			ELSEIF vl_add EQ 3
				imul vl_dest,____v_last_arg
			ENDIF
		ENDIF
	
		vl_cpos=vl_plus+2
		IF vl_def_add EQ 3
			vl_cpos=vl_cpos-1
		ENDIF
	:v1_terminal
	ENDM
:vl_exit
ENDM
;;—ÀŒ∆≈Õ»≈ » ¬€◊»“¿Õ»≈
v2 MACRO vl_expr:VARARG
LOCAL vl_def_add,vl_cpos,vl_expr_len,vl_dest,vl_plus
	vl_def_add=1
	vl_expr_len SIZESTR <vl_expr>
	vl_cpos=vstrstr(<vl_expr>,<=>)+1
	vl_dest SUBSTR <vl_expr>,1,(vl_cpos-2)
	vl_char SUBSTR <vl_expr>,(vl_cpos-2),1
	IFIDN vl_char,<+>
		vl_dest SUBSTR <vl_expr>,1,(vl_cpos-3)
		GOTO vl_loop
	ENDIF
	IFIDN vl_char,<->
		vl_dest SUBSTR <vl_expr>,1,(vl_cpos-3)
		vl_def_add=0
		GOTO vl_loop
	ENDIF
	vl_add=vl_def_add						;;»Õ»÷»¿À»«¿÷»ﬂ Ã≈—“¿ Õ¿«Õ¿◊≈Õ»ﬂ œ≈–¬€Ã —À¿√¿≈Ã€Ã »À» ¬€◊»“¿≈Ã€Ã
	vl_ph=0
	WHILE vl_cpos LT vl_expr_len			;;œŒ»—  —À¿√¿≈ÃŒ√Œ »À» ¬€◊»“¿≈ÃŒ√Œ
		vl_char SUBSTR <vl_expr>,vl_cpos,1
		IFIDN vl_char,<+>
			vl_cpos=vl_cpos+1
		ELSEIFIDN vl_char,< >
			vl_cpos=vl_cpos+1
		ELSEIFIDN vl_char,<->
			vl_cpos=vl_cpos+1
			vl_add=vl_add XOR 1
		ELSE
			EXITM
		ENDIF
	ENDM
	IFIDN vl_char,<(>	;;¬€–¿∆≈Õ»≈ ¬ — Œ¡ ¿’
		vl_ph=1
	ENDIF
	IFIDN vl_char,<&>
		vl_ph=2
	ENDIF
	IF vl_cpos GT vl_expr_len
		GOTO vl_exit
	ENDIF
	vl_plus=vstrstr(<vl_expr>,<+>,vl_cpos-1)
	vl_minus=vstrstr(<vl_expr>,<->,vl_cpos-1)
	IF vl_plus EQ 0
		vl_plus=vl_minus
	ELSEIF vl_minus NE 0
		IF vl_plus GT vl_minus
			vl_plus=vl_minus
		ENDIF
	ENDIF
	IF vl_plus NE 0			;Õ¿ —À”◊¿… ŒƒÕŒ√Œ ¿–√”Ã≈Õ“¿
		GOTO v2_many_args
	ENDIF
	vl_char2 SUBSTR <vl_expr>,vl_expr_len,1
	IF vl_ph EQ 1
		IFDIF vl_char2,<)>
			vl_ph=0
		ENDIF
		IF vl_ph EQ 1
			vl_ph=vstrstr(<vl_expr>,<}}>,vl_cpos-1)+vstrstr(<vl_expr>,<{{>,vl_cpos-1)
			IF vl_ph EQ 0
				vl_ph=1
			ENDIF
		ENDIF
	ENDIF
	IF vl_ph EQ 1
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_expr_len-vl_cpos-1)		
		IF vl_add EQ 1
		%	v vl_dest=____v_last_arg
			GOTO vl_exit
		ENDIF
	%	v vl_dest=____v_last_arg
		neg vl_dest
		GOTO vl_exit
	ENDIF
	IF vl_ph EQ 2
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1
		lea vl_dest,____v_last_arg
		IF vl_add EQ 0
			neg vl_dest
		ENDIF
		GOTO vl_exit
	ENDIF
	____v_last_arg SUBSTR <vl_expr>,vl_cpos
	IF vl_add EQ 1
	%	v1 vl_dest=____v_last_arg
		GOTO vl_exit
	ENDIF
	vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
	IF vl_add EQ 1
	%	movst vl_dest,-____v_last_arg
	ELSE
	%	v1 vl_dest=____v_last_arg
		neg vl_dest
	ENDIF
	GOTO vl_exit
:v2_many_args
	vl_char2 SUBSTR <vl_expr>,vl_plus-1,1
	IF vl_ph EQ 1
		IFDIF vl_char2,<)>
			vl_ph=0
		ENDIF
	ENDIF
	IF vl_ph EQ 1
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-1-vl_cpos-1)
		IF vl_add EQ 1
		%	v vl_dest=____v_last_arg
			vl_cpos=vl_plus
			GOTO vl_loop
		ENDIF
	%	v vl_dest=____v_last_arg
		neg vl_dest
	ELSEIF vl_ph EQ 2
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-vl_cpos-1)
		lea vl_dest,____v_last_arg
		IF vl_add EQ 0
			neg vl_dest
		ENDIF
	ELSE
		____v_last_arg SUBSTR <vl_expr>,vl_cpos,(vl_plus-vl_cpos)
		IF vl_add EQ 1
			vl_ph=vstrstr(<%____v_last_arg>,<}}>)+vstrstr(<%____v_last_arg>,<{{>)
			IF vl_ph
			%	v1 vl_dest=____v_last_arg
			ELSE
			%	movst vl_dest,____v_last_arg
			ENDIF
		ELSE
			vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
			IF vl_add EQ 1
			%	movst vl_dest,-____v_last_arg
			ELSE
			%	v1 vl_dest=____v_last_arg
				neg vl_dest
			ENDIF
		ENDIF
	ENDIF
	vl_cpos=vl_plus	;;Ã≈—“Œ Õ¿«Õ¿◊≈Õ»ﬂ «¿√–”∆≈ÕŒ œ≈–¬€Ã —À¿√¿≈Ã€Ã
:vl_loop
	WHILE vl_cpos LE vl_expr_len	;;Õ¿  ¿∆ƒŒ… »““≈–¿÷»» œ–»¡¿¬Àﬂ≈“—ﬂ 1 ¿–√”Ã≈Õ“
		vl_add=vl_def_add
		vl_ph=0
		WHILE vl_cpos LT vl_expr_len
			vl_char SUBSTR <vl_expr>,vl_cpos,1
			IFIDN vl_char,<+>
				vl_cpos=vl_cpos+1
			ELSEIFIDN vl_char,< >
				vl_cpos=vl_cpos+1
			ELSEIFIDN vl_char,<->
				vl_cpos=vl_cpos+1
				vl_add=vl_add XOR 1
			ELSE
				EXITM
			ENDIF
		ENDM
		IFIDN vl_char,<(>
			vl_ph=1
		ENDIF
		IFIDN vl_char,<&>
			vl_ph=2
		ENDIF
		IF vl_cpos GT vl_expr_len
			EXITM
		ENDIF
		vl_plus=vstrstr(<vl_expr>,<+>,vl_cpos-1)
		vl_minus=vstrstr(<vl_expr>,<->,vl_cpos-1)
		IF vl_plus EQ 0
			vl_plus=vl_minus
		ELSEIF vl_minus NE 0
			IF vl_plus GT vl_minus
				vl_plus=vl_minus
			ENDIF
		ENDIF
		IF vl_plus EQ 0		;;Œ¡–¿¡Œ“ ¿ œŒ—À≈ƒÕ≈√Œ ¿–√”Ã≈Õ“¿
			vl_char2 SUBSTR <vl_expr>,vl_expr_len,1
			IF vl_ph EQ 1
				IFDIF vl_char2,<)>
					vl_ph=0
				ENDIF
			ENDIF
			IF vl_ph EQ 1
				____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_expr_len-vl_cpos-1)
				IF vl_add EQ 1
					vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
					IF vl_add
						vl_ph=@CatStr(%(____v_last_arg))
						IF vl_ph EQ 1
							inc vl_dest
						ELSEIF vl_ph
							add vl_dest,____v_last_arg
						ENDIF
					ELSE
					%	v2 vl_dest+=____v_last_arg
					ENDIF
					EXITM
				ENDIF
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph EQ 1
						dec vl_dest
					ELSEIF vl_ph
						sub vl_dest,____v_last_arg
					ENDIF
				ELSE
				%	v2 vl_dest-=____v_last_arg
				ENDIF
				EXITM
			ENDIF
			IF vl_ph EQ 2
				____v_last_arg SUBSTR <vl_expr>,(vl_cpos+1)
				IF ((OPATTR (____v_last_arg)) AND LABEL_EXPR)
				%	movst [rsp-8],vl_dest
					lea vl_dest,____v_last_arg
					IF vl_add EQ 1
						add vl_dest,[rsp-8]
					ELSE
						sub vl_dest,[rsp-8]
						neg vl_dest
					ENDIF
				ELSE
					IF vl_add EQ 1
						lea vl_dest,____v_last_arg[vl_dest]
					ELSE
					%	movst [rsp-8],vl_dest
						lea vl_dest,____v_last_arg
						sub vl_dest,[rsp-8]
						neg vl_dest
					ENDIF
				ENDIF
				EXITM
			ENDIF
			____v_last_arg SUBSTR <vl_expr>,vl_cpos
			IF vl_add EQ 1
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph EQ 1
						inc vl_dest
					ELSEIF vl_ph
						add vl_dest,____v_last_arg
					ENDIF
				ELSE
					vl_add=((OPATTR (____v_last_arg)) AND (VALID_REF))
					vl_ph=vstrstr(<%____v_last_arg>,<}}>)+vstrstr(<%____v_last_arg>,<{{>)
					IF vl_add AND (vl_ph EQ 0)
						add vl_dest,____v_last_arg
					ELSE
					%	v1 [rsp-8]=____v_last_arg
						add vl_dest,[rsp-8]
					ENDIF
				ENDIF
			ELSE
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph EQ 1
						dec vl_dest
					ELSEIF vl_ph
						sub vl_dest,____v_last_arg
					ENDIF
				ELSE
					vl_add=((OPATTR (____v_last_arg)) AND (VALID_REF))
					vl_ph=vstrstr(<%____v_last_arg>,<}}>)+vstrstr(<%____v_last_arg>,<{{>)
					IF vl_add AND (vl_ph EQ 0)
						sub vl_dest,____v_last_arg
					ELSE
					%	v1 [rsp-8]=____v_last_arg
						sub vl_dest,[rsp-8]
					ENDIF
				ENDIF
			ENDIF
			EXITM
		ENDIF
		vl_char2 SUBSTR <vl_expr>,vl_plus-1,1
		IF vl_ph EQ 1
			IFDIF vl_char2,<)>
				vl_ph=0
			ENDIF
		ENDIF
		IF vl_ph EQ 1		;;Œ¡–¿¡Œ“ ¿ Œ◊≈–≈ƒÕŒ√Œ ¿–√”Ã≈Õ“¿
			____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-1-vl_cpos-1)
			IF vl_add EQ 1
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph EQ 1
						inc vl_dest
					ELSEIF vl_ph
						add vl_dest,____v_last_arg
					ENDIF
				ELSE
				%	v2 vl_dest+=____v_last_arg
				ENDIF
			ELSE
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph EQ 1
						dec vl_dest
					ELSEIF vl_ph
						sub vl_dest,____v_last_arg
					ENDIF
				ELSE
				%	v2 vl_dest-=____v_last_arg
				ENDIF
			ENDIF
		ELSEIF vl_ph EQ 2
			____v_last_arg SUBSTR <vl_expr>,(vl_cpos+1),(vl_plus-vl_cpos-1)
			IF ((OPATTR (____v_last_arg)) AND LABEL_EXPR)
			%	movst [rsp-8],vl_dest
				lea vl_dest,____v_last_arg
				IF vl_add EQ 1
					add vl_dest,[rsp-8]
				ELSE
					sub vl_dest,[rsp-8]
					neg vl_dest
				ENDIF
			ELSE
				IF vl_add EQ 1
					lea vl_dest,____v_last_arg[vl_dest]
				ELSE
				%	movst [rsp-8],vl_dest
					lea vl_dest,____v_last_arg
					sub vl_dest,[rsp-8]
					neg vl_dest
				ENDIF
			ENDIF
		ELSE
			____v_last_arg SUBSTR <vl_expr>,vl_cpos,(vl_plus-vl_cpos)
			IF vl_add EQ 1
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph EQ 1
						inc vl_dest
					ELSEIF vl_ph
						add vl_dest,____v_last_arg
					ENDIF
				ELSE
					vl_add=((OPATTR (____v_last_arg)) AND (VALID_REF))
					vl_ph=vstrstr(<%____v_last_arg>,<}}>)+vstrstr(<%____v_last_arg>,<{{>)
					IF vl_add AND (vl_ph EQ 0)
						add vl_dest,____v_last_arg
					ELSE
					%	v1 [rsp-8]=____v_last_arg
						add vl_dest,[rsp-8]
					ENDIF
				ENDIF
			ELSE
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph EQ 1
						dec vl_dest
					ELSEIF vl_ph
						sub vl_dest,____v_last_arg
					ENDIF
				ELSE
					vl_add=((OPATTR (____v_last_arg)) AND (VALID_REF))
					IF vl_add
						sub vl_dest,____v_last_arg
					ELSE
					%	v1 [rsp-8]=____v_last_arg
						sub vl_dest,[rsp-8]
					ENDIF
				ENDIF
			ENDIF
		ENDIF
		vl_cpos=vl_plus
	ENDM
:vl_exit
ENDM
;«ƒ≈—‹ »Õ¬≈–—»ﬂ ~
NotCount MACRO vl_expr:VARARG
	____vl_expr_len SIZESTR <vl_expr>
	____not_count=0
	____vl_expr_pos=1
	WHILE ____vl_expr_pos LE ____vl_expr_len
		____not_count_char SUBSTR <vl_expr>,____vl_expr_pos,1
		IFIDN ____not_count_char,<~>
			____not_count=____not_count+1
		ELSEIFDIF ____not_count_char,< >
			EXITM
		ENDIF
		____vl_expr_pos=____vl_expr_pos+1
	ENDM
ENDM
;«ƒ≈—‹ ÀŒ√»◊≈— Œ≈ » and
v4 MACRO vl_expr:VARARG
LOCAL vl_def_add,vl_cpos,vl_expr_len,vl_dest,vl_plus
	vl_def_add=1
	vl_expr_len SIZESTR <vl_expr>
	vl_cpos=vstrstr(<vl_expr>,<=>)+1
	vl_dest SUBSTR <vl_expr>,1,(vl_cpos-2)
	vl_char SUBSTR <vl_expr>,(vl_cpos-2),1
	IFIDN vl_char,<&>
		vl_dest SUBSTR <vl_expr>,1,(vl_cpos-3)
		GOTO vl_loop
	ENDIF
	vl_add=vl_def_add						;;»Õ»÷»¿À»«¿÷»ﬂ Ã≈—“¿ Õ¿«Õ¿◊≈Õ»ﬂ œ≈–¬€Ã ¿–√”Ã≈Õ“ŒÃ
	vl_ph=0
	vl_char SUBSTR <vl_expr>,vl_cpos,1		;;œŒ»—  ¿–√”Ã≈Õ“¿
	IFIDN vl_char,<(>	;;¬€–¿∆≈Õ»≈ ¬ — Œ¡ ¿’
		vl_ph=1
	ENDIF
	IFIDN vl_char,<&>
		vl_ph=2
	ENDIF
	IF vl_cpos GT vl_expr_len
		GOTO vl_exit
	ENDIF
	vl_plus=vstrstr(<vl_expr>,< and >,vl_cpos-1)
	IF vl_plus NE 0			;Õ¿ —À”◊¿… ŒƒÕŒ√Œ ¿–√”Ã≈Õ“¿
		GOTO v4_many_args
	ENDIF
	vl_char2 SUBSTR <vl_expr>,vl_expr_len,1
	IF vl_ph EQ 1	;;≈—À» ¬€–¿∆≈Õ»≈ Õ≈ ÷≈À» ŒÃ ¬ — Œ¡ ¿’
		IFDIF vl_char2,<)>
			vl_ph=0
		ENDIF
		IF vl_ph EQ 1
			vl_ph=vstrstr(<vl_expr>,<}}>,vl_cpos-1)+vstrstr(<vl_expr>,<{{>,vl_cpos-1)
			IF vl_ph EQ 0
				vl_ph=1
			ENDIF
		ENDIF
	ENDIF
	IF vl_ph EQ 1	;;–¿— –€“»≈ — Œ¡Œ 
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_expr_len-vl_cpos-1)
		vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
		IF vl_add EQ 1
		%	movst vl_dest,____v_last_arg
		ELSE
		%	v vl_dest=____v_last_arg
		ENDIF
		GOTO vl_exit
	ENDIF
;;	IF vl_ph EQ 2
;;		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1
;;		lea vl_dest,____v_last_arg
;;		GOTO vl_exit
;;	ENDIF
	____v_last_arg SUBSTR <vl_expr>,vl_cpos
	vl_plus=vstrstr(<%____v_last_arg>,<~>)+vstrstr(<%____v_last_arg>,<|>)+vstrstr(<%____v_last_arg>,<^>)
	vl_plus=vl_plus+vstrstr(<%____v_last_arg>,<{>)+vstrstr(<%____v_last_arg>,<}>)
	vl_plus=vl_plus+vstrstr(<%____v_last_arg>,<+>)+vstrstr(<%____v_last_arg>,<->)
	IF vl_plus NE 0
		GOTO v4_call_v2
	ENDIF
	IF vl_ph EQ 2
		GOTO v4_call_v2
	ENDIF
	vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
	IF vl_add
	%	movst vl_dest,____v_last_arg
		GOTO vl_exit
	ENDIF
:v4_call_v2
	NotCount %____v_last_arg
	IF ____vl_expr_pos GT 1
		____v_last_arg SUBSTR ____v_last_arg,____vl_expr_pos
	ENDIF
	IF ____not_count AND 1
	%	v2 vl_dest=____v_last_arg
		not vl_dest
		GOTO vl_exit
	ENDIF
%	v2 vl_dest=____v_last_arg
	GOTO vl_exit
:v4_many_args
	vl_char2 SUBSTR <vl_expr>,vl_plus-1,1
	IF vl_ph EQ 1
		IFDIF vl_char2,<)>
			vl_ph=0
		ENDIF
	ENDIF
	IF vl_ph EQ 1
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-1-vl_cpos-1)
		vl_ph=vstrstr(<%____v_last_arg>,<|>)+vstrstr(<%____v_last_arg>,<^>)+vstrstr(<%____v_last_arg>,<~>)
		vl_ph=vl_ph+vstrstr(<%____v_last_arg>,<{{>)+vstrstr(<%____v_last_arg>,<}}>)
		IF vl_ph
		%	v vl_dest=____v_last_arg
			GOTO pre_vl_loop
		ENDIF
		vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
		IF vl_add EQ 1
		%	movst vl_dest,____v_last_arg
		ELSE
		%	v vl_dest=____v_last_arg
		ENDIF
	ELSEIF vl_ph EQ 2
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-vl_cpos-1)
		lea vl_dest,____v_last_arg
		GOTO pre_vl_loop
	ENDIF
	____v_last_arg SUBSTR <vl_expr>,vl_cpos,(vl_plus-vl_cpos)
	vl_ph=vstrstr(<%____v_last_arg>,<}}>)+vstrstr(<%____v_last_arg>,<~>)
	IF vl_ph NE 0
		GOTO v4_call_v
	ENDIF
	vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
	IF vl_add EQ 1
	%	movst vl_dest=____v_last_arg
		GOTO pre_vl_loop
	ENDIF
:v4_call_v
%	v vl_dest=____v_last_arg
:pre_vl_loop
	vl_cpos=vl_plus+5	;;Ã≈—“Œ Õ¿«Õ¿◊≈Õ»ﬂ «¿√–”∆≈ÕŒ œ≈–¬€Ã —À¿√¿≈Ã€Ã
:vl_loop
	WHILE vl_cpos LE vl_expr_len	;;Õ¿  ¿∆ƒŒ… »““≈–¿÷»» œ–»¡¿¬Àﬂ≈“—ﬂ 1 ¿–√”Ã≈Õ“
		vl_add=vl_def_add
		vl_ph=0
		vl_char SUBSTR <vl_expr>,vl_cpos,1
		IFIDN vl_char,<(>
			vl_ph=1
		ENDIF
		IFIDN vl_char,<&>
			vl_ph=2
		ENDIF
		IF vl_cpos GT vl_expr_len
			EXITM
		ENDIF
		vl_plus=vstrstr(<vl_expr>,< and >,vl_cpos-1)
		IF vl_plus EQ 0		;;Œ¡–¿¡Œ“ ¿ œŒ—À≈ƒÕ≈√Œ ¿–√”Ã≈Õ“¿
			vl_char2 SUBSTR <vl_expr>,vl_expr_len,1
			IF vl_ph EQ 1
				IFDIF vl_char2,<)>
					vl_ph=0
				ENDIF
			ENDIF
			IF vl_ph EQ 1	;–¿— –€“»≈ — Œ¡Œ 
				____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_expr_len-vl_cpos-1)
				vl_ph=vstrstr(<%____v_last_arg>,<|>)+vstrstr(<%____v_last_arg>,<^>)
				IF vl_ph EQ 0
					vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
					vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
					IF vl_add
						vl_ph=@CatStr(%(____v_last_arg))
						IF vl_ph
							and vl_dest,____v_last_arg
						ENDIF
					ELSEIF vl_ph
						and vl_dest,____v_last_arg
					ELSE
					%	v [rsp-8]=____v_last_arg
						and vl_dest,[rsp-8]
					ENDIF
				ELSE
				%	v [rsp-8]=____v_last_arg
					and vl_dest,[rsp-8]
				ENDIF
				EXITM
			ENDIF
			IF vl_ph EQ 2
				____v_last_arg SUBSTR <vl_expr>,(vl_cpos+1)
			%	movst [rsp-8],vl_dest
				lea vl_dest,____v_last_arg
				and vl_dest,[rsp-8]
				EXITM
			ENDIF
			____v_last_arg SUBSTR <vl_expr>,vl_cpos
			vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
			vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
			IF (vl_add OR vl_ph)
				and vl_dest,____v_last_arg
			ELSE
				NotCount %____v_last_arg
				IF ____vl_expr_pos GT 1
					____v_last_arg SUBSTR <%____v_last_arg>,____vl_expr_pos
				ENDIF
				IF ____not_count AND 1
				%	v2 [rsp-8]=____v_last_arg
					not qptr [rsp-8]
				ELSE
				%	v2 [rsp-8]=____v_last_arg
				ENDIF
				and vl_dest,[rsp-8]
			ENDIF
			EXITM
		ENDIF
		vl_char2 SUBSTR <vl_expr>,vl_plus-1,1
		IF vl_ph EQ 1
			IFDIF vl_char2,<)>
				vl_ph=0
			ENDIF
		ENDIF
		IF vl_ph EQ 1		;;Œ¡–¿¡Œ“ ¿ Œ◊≈–≈ƒÕŒ√Œ ¿–√”Ã≈Õ“¿
			____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-1-vl_cpos-1)
			vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
			vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
			IF vl_add OR vl_ph
				and vl_dest,____v_last_arg
			ELSE
			%	v vl_dest|=____v_last_arg
			ENDIF
		ELSEIF vl_ph EQ 2
			____v_last_arg SUBSTR <vl_expr>,(vl_cpos+1),(vl_plus-vl_cpos)
		%	movst [rsp-8],vl_dest
			lea vl_dest,____v_last_arg
			and vl_dest,[rsp-8]
		ELSE
			____v_last_arg SUBSTR <vl_expr>,vl_cpos,(vl_plus-vl_cpos)
			vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
			vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
			IF (vl_add OR vl_ph)
				and vl_dest,____v_last_arg
			ELSE
				NotCount %____v_last_arg
				IF ____vl_expr_pos GT 1
					____v_last_arg SUBSTR <%____v_last_arg>,____vl_expr_pos
				ENDIF
				IF ____not_count AND 1
				%	v2 [rsp-8]=____v_last_arg
					not qptr [rsp-8]
				ELSE
				%	v2 [rsp-8]=____v_last_arg
				ENDIF
				and vl_dest,[rsp-8]
			ENDIF
		ENDIF
		vl_cpos=vl_plus+5
	ENDM
:vl_exit
ENDM
v MACRO vl_expr:VARARG
LOCAL vl_def_add,vl_cpos,vl_expr_len,vl_dest,vl_plus
	vl_def_add=1
	vl_expr_len SIZESTR <vl_expr>
	vl_cpos=vstrstr(<vl_expr>,<=>)+1
	vl_dest SUBSTR <vl_expr>,1,(vl_cpos-2)
	vl_char SUBSTR <vl_expr>,(vl_cpos-2),1
	IFIDN vl_char,<|>
		vl_dest SUBSTR <vl_expr>,1,(vl_cpos-3)
		GOTO vl_loop
	ENDIF
	IFIDN vl_char,<^>
		vl_dest SUBSTR <vl_expr>,1,(vl_cpos-3)
		vl_def_add=0
		GOTO vl_loop
	ENDIF
	vl_add=vl_def_add						;;»Õ»÷»¿À»«¿÷»ﬂ Ã≈—“¿ Õ¿«Õ¿◊≈Õ»ﬂ œ≈–¬€Ã —À¿√¿≈Ã€Ã »À» ¬€◊»“¿≈Ã€Ã
	vl_ph=0
	vl_char SUBSTR <vl_expr>,vl_cpos,1
	IFIDN vl_char,<(>	;;¬€–¿∆≈Õ»≈ ¬ — Œ¡ ¿’
		vl_ph=1
	ENDIF
	IFIDN vl_char,<&>
		vl_ph=2
	ENDIF
	IF vl_cpos GT vl_expr_len
		GOTO vl_exit
	ENDIF
	vl_plus=vstrstr(<vl_expr>,<|>,vl_cpos-1)
	vl_minus=vstrstr(<vl_expr>,<^>,vl_cpos-1)
	IF vl_plus EQ 0
		vl_plus=vl_minus
	ELSEIF vl_minus NE 0
		IF vl_plus GT vl_minus
			vl_plus=vl_minus
		ENDIF
	ENDIF
	IF vl_plus NE 0			;Õ¿ —À”◊¿… ŒƒÕŒ√Œ ¿–√”Ã≈Õ“¿
		GOTO v_many_args
	ENDIF
	vl_char2 SUBSTR <vl_expr>,vl_expr_len,1
	IF vl_ph EQ 1	;;≈—À» ¬€–¿∆≈Õ»≈ Õ≈ ÷≈À» ŒÃ ¬ — Œ¡ ¿’
		IFDIF vl_char2,<)>
			vl_ph=0
		ENDIF
		IF vl_ph EQ 1
			vl_ph=vstrstr(<vl_expr>,<}}>,vl_cpos-1)+vstrstr(<vl_expr>,<{{>,vl_cpos-1)
			IF vl_ph EQ 0
				vl_ph=1
			ENDIF
		ENDIF
	ENDIF
	IF vl_ph EQ 1
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_expr_len-vl_cpos-1)
	%	v vl_dest=____v_last_arg
		GOTO vl_exit
	ENDIF
;;		IF vl_ph EQ 2
;;			____v_last_arg SUBSTR <vl_expr>,vl_cpos+1
;;			lea vl_dest,____v_last_arg
;;			GOTO vl_exit
;;		ENDIF
	____v_last_arg SUBSTR <vl_expr>,vl_cpos
	%	v4 vl_dest=____v_last_arg
	GOTO vl_exit
:v_many_args
	vl_char2 SUBSTR <vl_expr>,vl_plus-1,1
	IF vl_ph EQ 1
		IFDIF vl_char2,<)>
			vl_ph=0
		ENDIF
	ENDIF
	IF vl_ph NE 1
		GOTO v_is_vl_ph_2
	ENDIF
	____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-1-vl_cpos-1)
%	v vl_dest=____v_last_arg
	GOTO v_pre_vl_loop
:v_is_vl_ph_2
	IF vl_ph EQ 2
		____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-vl_cpos-1)
		lea vl_dest,____v_last_arg
		GOTO v_pre_vl_loop
	ENDIF
	____v_last_arg SUBSTR <vl_expr>,vl_cpos,(vl_plus-vl_cpos)
%	v4 vl_dest=____v_last_arg
:v_pre_vl_loop
	vl_cpos=vl_plus	;;Ã≈—“Œ Õ¿«Õ¿◊≈Õ»ﬂ «¿√–”∆≈ÕŒ œ≈–¬€Ã —À¿√¿≈Ã€Ã
:vl_loop
	WHILE vl_cpos LE vl_expr_len	;;Õ¿  ¿∆ƒŒ… »““≈–¿÷»» œ–»¡¿¬Àﬂ≈“—ﬂ 1 ¿–√”Ã≈Õ“
		vl_add=vl_def_add
		vl_ph=0
		WHILE vl_cpos LT vl_expr_len
			vl_char SUBSTR <vl_expr>,vl_cpos,1
			IFIDN vl_char,<|>
				vl_cpos=vl_cpos+1
			ELSEIFIDN vl_char,< >
				vl_cpos=vl_cpos+1
			ELSEIFIDN vl_char,<^>
				vl_cpos=vl_cpos+1
				vl_add=vl_add XOR 1
			ELSE
				EXITM
			ENDIF
		ENDM
		IFIDN vl_char,<(>
			vl_ph=1
		ENDIF
		IFIDN vl_char,<&>
			vl_ph=2
		ENDIF
		IF vl_cpos GT vl_expr_len
			EXITM
		ENDIF
		vl_plus=vstrstr(<vl_expr>,<|>,vl_cpos-1)
		vl_minus=vstrstr(<vl_expr>,<^>,vl_cpos-1)
		IF vl_plus EQ 0
			vl_plus=vl_minus
		ELSEIF vl_minus NE 0
			IF vl_plus GT vl_minus
				vl_plus=vl_minus
			ENDIF
		ENDIF
		IF vl_plus EQ 0		;;Œ¡–¿¡Œ“ ¿ œŒ—À≈ƒÕ≈√Œ ¿–√”Ã≈Õ“¿
			vl_char2 SUBSTR <vl_expr>,vl_expr_len,1
			IF vl_ph EQ 1
				IFDIF vl_char2,<)>
					vl_ph=0
				ENDIF
			ENDIF
			IF vl_ph EQ 1	;–¿— –€“»≈ — Œ¡Œ 
				____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_expr_len-vl_cpos-1)
				vl_ph=vstrstr(%____v_last_arg,<|>)+vstrstr(%____v_last_arg,<^>)
				IF vl_add EQ 1
					IF vl_ph EQ 0
						vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
						vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
						IF vl_add
							vl_ph=@CatStr(%(____v_last_arg))
							IF vl_ph
								or vl_dest,____v_last_arg
							ENDIF
						ELSEIF vl_ph
							or vl_dest,____v_last_arg
						ELSE
						%	v vl_dest|=____v_last_arg
						ENDIF
					ELSE
					%	v vl_dest|=____v_last_arg
					ENDIF
					EXITM
				ENDIF
				IF vl_ph EQ 0
					vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
					vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
					IF vl_add
						vl_ph=@CatStr(%(____v_last_arg))
						IF vl_ph
							xor vl_dest,____v_last_arg
						ENDIF
					ELSEIF vl_ph
						xor vl_dest,____v_last_arg
					ELSE
					%	v vl_dest^=____v_last_arg
					ENDIF
				ELSE
				%	v vl_dest^=____v_last_arg
				ENDIF
				EXITM
			ENDIF
			IF vl_ph EQ 2
				____v_last_arg SUBSTR <vl_expr>,(vl_cpos+1)
			%	movst [rsp-8],vl_dest
				lea vl_dest,____v_last_arg
				IF vl_add EQ 1
					or vl_dest,[rsp-8]
				ELSE
					xor [rsp-8],vl_dest
				%	movst vl_dest,[rsp-8]
				ENDIF
				EXITM
			ENDIF
			____v_last_arg SUBSTR <vl_expr>,vl_cpos
			IF vl_add EQ 1
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph
						or vl_dest,____v_last_arg
					ENDIF
				ELSEIF vl_ph
					or vl_dest,____v_last_arg
				ELSE
				%	v4 [rsp-8]=____v_last_arg
					or vl_dest,[rsp-8]
				ENDIF
			ELSE
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph
						xor vl_dest,____v_last_arg
					ENDIF
				ELSEIF vl_ph
					xor vl_dest,____v_last_arg
				ELSE
				%	v4 [rsp-8]=____v_last_arg
					xor vl_dest,[rsp-8]
				ENDIF
			ENDIF
			EXITM
		ENDIF
		vl_char2 SUBSTR <vl_expr>,vl_plus-1,1
		IF vl_ph EQ 1
			IFDIF vl_char2,<)>
				vl_ph=0
			ENDIF
		ENDIF
		IF vl_ph EQ 1		;;Œ¡–¿¡Œ“ ¿ Œ◊≈–≈ƒÕŒ√Œ ¿–√”Ã≈Õ“¿
			____v_last_arg SUBSTR <vl_expr>,vl_cpos+1,(vl_plus-1-vl_cpos-1)
			vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
			IF vl_add EQ 1
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph
						or vl_dest,____v_last_arg
					ENDIF
				ELSEIF vl_ph
					or vl_dest,____v_last_arg
				ELSE
				%	v vl_dest|=____v_last_arg
				ENDIF
			ELSE
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph
						xor vl_dest,____v_last_arg
					ENDIF
				ELSEIF vl_ph
					xor vl_dest,____v_last_arg
				ELSE
				%	v vl_dest^=____v_last_arg
				ENDIF
			ENDIF
		ELSEIF vl_ph EQ 2
			____v_last_arg SUBSTR <vl_expr>,(vl_cpos+1),(vl_plus-vl_cpos)
		%	movst [rsp-8],vl_dest
			lea vl_dest,____v_last_arg
			IF vl_add EQ 1
				or vl_dest,[rsp-8]
			ELSE
				xor [rsp-8],vl_dest
			%	movst vl_dest,[rsp-8]
			ENDIF
		ELSE
			____v_last_arg SUBSTR <vl_expr>,vl_cpos,(vl_plus-vl_cpos)
			vl_ph=((OPATTR (____v_last_arg)) AND (VALID_REF))
			IF vl_add EQ 1
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph
						or vl_dest,____v_last_arg
					ENDIF
				ELSEIF vl_ph
					or vl_dest,____v_last_arg
				ELSE
				%	v4 [rsp-8]=____v_last_arg
					or vl_dest,[rsp-8]
				ENDIF
			ELSE
				vl_add=((OPATTR (____v_last_arg)) EQ (VALID_REF OR IMM_EXPR))
				IF vl_add
					vl_ph=@CatStr(%(____v_last_arg))
					IF vl_ph
						xor vl_dest,____v_last_arg
					ENDIF
				ELSEIF vl_ph
					xor vl_dest,____v_last_arg
				ELSE
					%	v4 [rsp-8]=____v_last_arg
					xor vl_dest,[rsp-8]
				ENDIF
			ENDIF
		ENDIF
		vl_cpos=vl_plus
	ENDM
:vl_exit
ENDM
PreTestCond0 TEXTEQU <>
PreTestCond1 TEXTEQU <>
PreTestCond2 TEXTEQU <>
PreTestCond3 TEXTEQU <>
PreTestCond4 TEXTEQU <>
PreTestCond5 TEXTEQU <>
PreTestCond6 TEXTEQU <>
PreTestCond7 TEXTEQU <>
PreTestCond8 TEXTEQU <>
PreTestCond9 TEXTEQU <>
PreTestCond10 TEXTEQU <>
PreTestCond11 TEXTEQU <>
PreTestCond12 TEXTEQU <>
PreTestCond13 TEXTEQU <>
PreTestCond14 TEXTEQU <>
PreTestCond15 TEXTEQU <>
PreTestCond16 TEXTEQU <>
PreTestCond17 TEXTEQU <>
PreTestCond18 TEXTEQU <>
PreTestCond19 TEXTEQU <>
.for MACRO PreLoopAction,args,PreTestCondAction:VARARG
	v PreLoopAction
	SaveUntilCondsLabel
	IFDIF <args>,<TRUE>
		jmp LastUntilConds
	ENDIF
	SaveUntilOutLabel
	SaveUntilLabel	
LastUntilLabel:
	while_cnt=while_cnt+1
	IF while_cnt EQ 1
		WhileLevel0 TEXTEQU <args>
		PreTestCond0 TEXTEQU <PreTestCondAction>
		wcond0l SIZESTR <args>
	ELSEIF while_cnt EQ 2
		WhileLevel1 TEXTEQU <args>
		PreTestCond1 TEXTEQU <PreTestCondAction>
		wcond1l SIZESTR <args>
	ELSEIF while_cnt EQ 3
		WhileLevel2 TEXTEQU <args>
		PreTestCond2 TEXTEQU <PreTestCondAction>
		wcond2l SIZESTR <args>
	ELSEIF while_cnt EQ 4
		WhileLevel3 TEXTEQU <args>
		PreTestCond3 TEXTEQU <PreTestCondAction>
		wcond3l SIZESTR <args>
	ELSEIF while_cnt EQ 5
		WhileLevel4 TEXTEQU <args>
		PreTestCond4 TEXTEQU <PreTestCondAction>
		wcond4l SIZESTR <args>
	ELSEIF while_cnt EQ 6
		WhileLevel5 TEXTEQU <args>
		PreTestCond5 TEXTEQU <PreTestCondAction>
		wcond5l SIZESTR <args>
	ELSEIF while_cnt EQ 7
		WhileLevel6 TEXTEQU <args>
		PreTestCond6 TEXTEQU <PreTestCondAction>
		wcond6l SIZESTR <args>
	ELSEIF while_cnt EQ 8
		WhileLevel7 TEXTEQU <args>
		PreTestCond7 TEXTEQU <PreTestCondAction>
		wcond7l SIZESTR <args>
	ELSEIF while_cnt EQ 9
		WhileLevel8 TEXTEQU <args>
		PreTestCond8 TEXTEQU <PreTestCondAction>
		wcond8l SIZESTR <args>
	ELSEIF while_cnt EQ 10
		WhileLevel9 TEXTEQU <args>
		PreTestCond9 TEXTEQU <PreTestCondAction>
		wcond9l SIZESTR <args>
	ELSEIF while_cnt EQ 11
		WhileLevel10 TEXTEQU <args>
		PreTestCond10 TEXTEQU <PreTestCondAction>
		wcond10l SIZESTR <args>
	ELSEIF while_cnt EQ 12
		WhileLevel11 TEXTEQU <args>
		PreTestCond11 TEXTEQU <PreTestCondAction>
		wcond11l SIZESTR <args>
	ELSEIF while_cnt EQ 13
		WhileLevel12 TEXTEQU <args>
		PreTestCond12 TEXTEQU <PreTestCondAction>
		wcond12l SIZESTR <args>
	ELSEIF while_cnt EQ 14
		WhileLevel13 TEXTEQU <args>
		PreTestCond13 TEXTEQU <PreTestCondAction>
		wcond13l SIZESTR <args>
	ELSEIF while_cnt EQ 15
		WhileLevel14 TEXTEQU <args>
		PreTestCond14 TEXTEQU <PreTestCondAction>
		wcond14l SIZESTR <args>
	ELSEIF while_cnt EQ 16
		WhileLevel15 TEXTEQU <args>
		PreTestCond15 TEXTEQU <PreTestCondAction>
		wcond15l SIZESTR <args>
	ELSEIF while_cnt EQ 17
		WhileLevel16 TEXTEQU <args>
		PreTestCond16 TEXTEQU <PreTestCondAction>
		wcond16l SIZESTR <args>
	ELSEIF while_cnt EQ 18
		WhileLevel17 TEXTEQU <args>
		PreTestCond17 TEXTEQU <PreTestCondAction>
		wcond17l SIZESTR <args>
	ELSEIF while_cnt EQ 19
		WhileLevel18 TEXTEQU <args>
		PreTestCond18 TEXTEQU <PreTestCondAction>
		wcond18l SIZESTR <args>
	ELSEIF while_cnt EQ 20
		WhileLevel19 TEXTEQU <args>
		PreTestCond19 TEXTEQU <PreTestCondAction>
		wcond19l SIZESTR <args>
	ELSE
		.err <Too much nesting level.>
	ENDIF
	EXITM<>
ENDM
.endf MACRO
	IF while_cnt EQ 1
	%	FOR parm,<PreTestCond0>
			v parm
		ENDM
	ELSEIF while_cnt EQ 2
	%	FOR parm,<PreTestCond1>
			v parm
		ENDM
	ELSEIF while_cnt EQ 3
	%	FOR parm,<PreTestCond2>
			v parm
		ENDM
	ELSEIF while_cnt EQ 4
	%	FOR parm,<PreTestCond3>
			v parm
		ENDM
	ELSEIF while_cnt EQ 5
	%	FOR parm,<PreTestCond4>
			v parm
		ENDM
	ELSEIF while_cnt EQ 6
	%	FOR parm,<PreTestCond5>
			v parm
		ENDM
	ELSEIF while_cnt EQ 7
	%	FOR parm,<PreTestCond6>
			v parm
		ENDM
	ELSEIF while_cnt EQ 8
	%	FOR parm,<PreTestCond7>
			v parm
		ENDM
	ELSEIF while_cnt EQ 9
	%	FOR parm,<PreTestCond8>
			v parm
		ENDM
	ELSEIF while_cnt EQ 10
	%	FOR parm,<PreTestCond9>
			v parm
		ENDM
	ELSEIF while_cnt EQ 11
	%	FOR parm,<PreTestCond10>
			v parm
		ENDM
	ELSEIF while_cnt EQ 12
	%	FOR parm,<PreTestCond11>
			v parm
		ENDM
	ELSEIF while_cnt EQ 13
	%	FOR parm,<PreTestCond12>
			v parm
		ENDM
	ELSEIF while_cnt EQ 14
	%	FOR parm,<PreTestCond13>
			v parm
		ENDM
	ELSEIF while_cnt EQ 15
	%	FOR parm,<PreTestCond14>
			v parm
		ENDM
	ELSEIF while_cnt EQ 16
	%	FOR parm,<PreTestCond15>
			v parm
		ENDM
	ELSEIF while_cnt EQ 17
	%	FOR parm,<PreTestCond16>
			v parm
		ENDM
	ELSEIF while_cnt EQ 18
	%	FOR parm,<PreTestCond17>
			v parm
		ENDM
	ELSEIF while_cnt EQ 19
	%	FOR parm,<PreTestCond18>
			v parm
		ENDM
	ELSEIF while_cnt EQ 20
	%	FOR parm,<PreTestCond19>
			v parm
		ENDM
	ENDIF	
	GetUntilCondsLabel
LastUntilConds:
	DelUntilCondsLabel
	GetUntilLabel
	IF (while_cnt EQ 1) AND (wcond0l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel0
	ELSEIF (while_cnt EQ 2) AND (wcond1l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel1
	ELSEIF (while_cnt EQ 3) AND (wcond2l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel2
	ELSEIF (while_cnt EQ 4) AND (wcond3l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel3
	ELSEIF (while_cnt EQ 5) AND (wcond4l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel4
	ELSEIF (while_cnt EQ 6) AND (wcond5l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel5
	ELSEIF (while_cnt EQ 7) AND (wcond6l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel6
	ELSEIF (while_cnt EQ 8) AND (wcond7l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel7
	ELSEIF (while_cnt EQ 9) AND (wcond8l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel8
	ELSEIF (while_cnt EQ 10) AND (wcond9l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel9
	ELSEIF (while_cnt EQ 11) AND (wcond10l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel10
	ELSEIF (while_cnt EQ 12) AND (wcond11l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel11
	ELSEIF (while_cnt EQ 13) AND (wcond12l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel12
	ELSEIF (while_cnt EQ 14) AND (wcond13l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel13
	ELSEIF (while_cnt EQ 15) AND (wcond14l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel14
	ELSEIF (while_cnt EQ 16) AND (wcond15l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel15
	ELSEIF (while_cnt EQ 17) AND (wcond16l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel16
	ELSEIF (while_cnt EQ 18) AND (wcond17l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel17
	ELSEIF (while_cnt EQ 19) AND (wcond18l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel18
	ELSEIF (while_cnt EQ 20) AND (wcond19l GT 0)
	%	J_POLY_COND LastUntilLabel,TRUE,WhileLevel19
	ENDIF
	DelUntilLabel
	GetUntilOutLabel
LastUntilOutLabel:
	DelUntilOutLabel
	while_cnt=while_cnt-1
ENDM