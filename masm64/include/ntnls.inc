MAXIMUM_LEADBYTES   equ 12
CPTABLEINFO STRUC
	CodePage				USHORT ?	; code page number
	MaximumCharacterSize	USHORT ?	; max length (bytes) of a char
	DefaultChar				USHORT ?	; default character (MB)
	UniDefaultChar			USHORT ?	; default character (Unicode)
	TransDefaultChar		USHORT ?	; translation of default char (Unicode)
	TransUniDefaultChar		USHORT ?	; translation of Unic default char (MB)
	DBCSCodePage			USHORT ?	; Non 0 for DBCS code pages
	LeadByte				UCHAR MAXIMUM_LEADBYTES dup(?)	; lead byte ranges
	Reserved				BYTE 6 dup(?)
	MultiByteTable			PUSHORT ?	; pointer to MB translation table
	WideCharTable			PVOID	?	; pointer to WC translation table
	DBCSRanges				PUSHORT ?	; pointer to DBCS ranges
	DBCSOffsets				PUSHORT ?	; pointer to DBCS offsets
CPTABLEINFO ENDS
PCPTABLEINFO TYPEDEF PTR CPTABLEINFO
NLSTABLEINFO STRUC
	OemTableInfo	CPTABLEINFO<>
	AnsiTableInfo	CPTABLEINFO<>
	UpperCaseTable	PUSHORT ?			;844 format upcase table
	LowerCaseTable	PUSHORT ?			;844 format lower case table
NLSTABLEINFO ENDS
PNLSTABLEINFO TYPEDEF PTR NLSTABLEINFO