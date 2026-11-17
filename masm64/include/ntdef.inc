SINGLE_LIST_ENTRY STRUC
	Next PVOID ?
SINGLE_LIST_ENTRY ENDS
APPLICATION_ERROR_MASK       equ 20000000h
ERROR_SEVERITY_SUCCESS       equ 00000000h
ERROR_SEVERITY_INFORMATIONAL equ 40000000h
ERROR_SEVERITY_WARNING       equ 80000000h
ERROR_SEVERITY_ERROR         equ 0C0000000h
FLOAT128 STRUC
	LowPart		__int64 ?
	HighPart	__int64 ?
FLOAT128 ENDS
PFLOAT128	TYPEDEF PTR FLOAT128
IFNDEF LARGE_INTEGER
	LARGE_INTEGER UNION
		QuadPart	LONGLONG ?
		STRUC
			LowPart		ULONG ?
			HighPart	LONG ?
		ENDS
	LARGE_INTEGER ENDS
ENDIF
PLARGE_INTEGER	TYPEDEF PTR LARGE_INTEGER
ULARGE_INTEGER UNION
	QuadPart	ULONGLONG ?
	STRUC
		LowPart		ULONG ?
		HighPart	ULONG ?
	ENDS
ULARGE_INTEGER ENDS
LUID STRUC
	LowPart		ULONG ?
	HighPart	LONG ?
LUID ENDS
PLUID	TYPEDEF PTR LUID
PHYSICAL_ADDRESS	TYPEDEF LARGE_INTEGER
PPHYSICAL_ADDRESS	TYPEDEF PTR PHYSICAL_ADDRESS
EVENT_TYPE	TYPEDEF HANDLE
NotificationEvent		equ 0
SynchronizationEvent	equ 1
TIMER_TYPE	TYPEDEF HANDLE
NotificationTimer		equ 0
SynchronizationTimer	equ 1
WAIT_TYPE	TYPEDEF HANDLE
WaitAll		equ 0
WaitAny		equ 1
PSZ		TYPEDEF PTR BYTE
PCSZ	TYPEDEF PTR BYTE
STRING STRUC
	woLength		USHORT ?
	MaximumLength	USHORT ?
	reserve			DWORD ?
	Buffer			PCHAR ?
STRING ENDS
PSTRING TYPEDEF PTR STRING
ANSI_STRING TYPEDEF STRING
PANSI_STRING TYPEDEF PTR ANSI_STRING
OEM_STRING TYPEDEF STRING
POEM_STRING TYPEDEF PTR OEM_STRING
CSTRING TYPEDEF STRING
PCSTRING TYPEDEF PTR STRING
CANSI_STRING	TYPEDEF STRING
PCANSI_STRING	TYPEDEF PTR CANSI_STRING
UNICODE_STRING STRUC
	woLength		USHORT ?
	MaximumLength	USHORT ?
	reserve			DWORD ?
	Buffer			PWSTR ?
UNICODE_STRING ENDS
PUNICODE_STRING TYPEDEF PTR UNICODE_STRING
PCUNICODE_STRING TYPEDEF PTR UNICODE_STRING
LIST_ENTRY STRUC
	Flink	PVOID ?
	Blink	PVOID ?
LIST_ENTRY ENDS
PLIST_ENTRY	TYPEDEF PTR LIST_ENTRY
LIST_ENTRY32 STRUC
	Flink	ULONG ?
	Blink	ULONG ?
LIST_ENTRY32 ENDS
PLIST_ENTRY32	TYPEDEF PTR LIST_ENTRY32
LIST_ENTRY64 STRUC
	Flink	ULONGLONG ?
	Blink	ULONGLONG ?
LIST_ENTRY64 ENDS
PLIST_ENTRY64	TYPEDEF PTR LIST_ENTRY64
STRING32 STRUC
	woLength		USHORT ?
	MaximumLength	USHORT ?
	Buffer			ULONG ?
STRING32 ENDS
PSTRING32	TYPEDEF PTR STRING32
UNICODE_STRING32	TYPEDEF STRING32
PUNICODE_STRING32	TYPEDEF PTR UNICODE_STRING32
ANSI_STRING32		TYPEDEF PTR STRING32
PANSI_STRING32		TYPEDEF PTR ANSI_STRING32
STRING64	TYPEDEF STRING
PSTRING64	TYPEDEF PTR STRING64
UNICODE_STRING64	TYPEDEF STRING64
PUNICODE_STRING64	TYPEDEF PTR UNICODE_STRING64
ANSI_STRING64		TYPEDEF STRING64
PANSI_STRING64		TYPEDEF PTR ANSI_STRING64
OBJ_INHERIT         equ 00000002h
OBJ_PERMANENT       equ 00000010h
OBJ_EXCLUSIVE       equ 00000020h
OBJ_CASE_INSENSITIVE    equ 00000040h
OBJ_OPENIF              equ 00000080h
OBJ_OPENLINK            equ 00000100h
OBJ_KERNEL_HANDLE       equ 00000200h
OBJ_VALID_ATTRIBUTES    equ 000003F2h
OBJECT_ATTRIBUTES STRUC
	oLength						ULONG ?
	Reserved1					DWORD ?
	RootDirectory				HANDLE ?
	ObjectName					PUNICODE_STRING ?
	Attributes					ULONG ?
	Reserved2					DWORD ?
	SecurityDescriptor			PVOID ?		; Points to type SECURITY_DESCRIPTOR
	SecurityQualityOfService	PVOID ?		; Points to type SECURITY_QUALITY_OF_SERVICE
OBJECT_ATTRIBUTES ENDS
POBJECT_ATTRIBUTES TYPEDEF PTR OBJECT_ATTRIBUTES
OBJECTID STRUC
	Lineage	GUID<>
	Uniquifier	ULONG ?
OBJECTID ENDS
POBJECTID TYPEDEF PTR OBJECTID
MINCHAR     equ 80h
MAXCHAR     equ 7Fh
MINSHORT    equ 8000h
MAXSHORT    equ 7FFFh
MINLONG     equ 80000000h
MAXLONG     equ 7FFFFFFFh
MAXUCHAR    equ 0FFh
MAXUSHORT   equ 0FFFFh
MAXULONG    equ 0FFFFFFFFh
NT_PRODUCT_TYPE TYPEDEF HANDLE
NtProductWinNt		equ 1
NtProductLanManNt	equ 2
NtProductServer		equ 3
PNT_PRODUCT_TYPE	TYPEDEF PTR NT_PRODUCT_TYPE
SUITE_TYPE TYPEDEF HANDLE
SmallBusiness			equ 0
Enterprise				equ 1
BackOffice				equ 2
CommunicationServer		equ 3
TerminalServer			equ 4
SmallBusinessRestricted	equ 5
EmbeddedNT				equ 6
DataCenter				equ 7
SingleUserTS			equ 8
Personal				equ 9
ServerAppliance			equ 10
MaxSuiteType			equ 11
VER_SERVER_NT                       equ 80000000h
VER_WORKSTATION_NT                  equ 40000000h
VER_SUITE_SMALLBUSINESS             equ 00000001h
VER_SUITE_ENTERPRISE                equ 00000002h
VER_SUITE_BACKOFFICE                equ 00000004h
VER_SUITE_COMMUNICATIONS            equ 00000008h
VER_SUITE_TERMINAL                  equ 00000010h
VER_SUITE_SMALLBUSINESS_RESTRICTED  equ 00000020h
VER_SUITE_EMBEDDEDNT                equ 00000040h
VER_SUITE_DATACENTER                equ 00000080h
VER_SUITE_SINGLEUSERTS              equ 00000100h
VER_SUITE_PERSONAL                  equ 00000200h
VER_SUITE_SERVERAPPLIANCE           equ 00000400h
LANG_NEUTRAL                     equ 0
LANG_AFRIKAANS                   equ 36h
LANG_ALBANIAN                    equ 1Ch
LANG_ARABIC                      equ 1
LANG_ARMENIAN                    equ 2Bh
LANG_ASSAMESE                    equ 4Dh
LANG_AZERI                       equ 2Ch
LANG_BASQUE                      equ 2Dh
LANG_BELARUSIAN                  equ 23h
LANG_BENGALI                     equ 45h
LANG_BULGARIAN                   equ 2
LANG_CATALAN                     equ 3
LANG_CHINESE                     equ 4
LANG_CROATIAN                    equ 1Ah
LANG_CZECH                       equ 5
LANG_DANISH                      equ 6
LANG_DUTCH                       equ 13h
LANG_ENGLISH                     equ 9
LANG_ESTONIAN                    equ 25h
LANG_FAEROESE                    equ 38h
LANG_FARSI                       equ 29h
LANG_FINNISH                     equ 0Bh
LANG_FRENCH                      equ 0Ch
LANG_GEORGIAN                    equ 37h
LANG_GERMAN                      equ 7
LANG_GREEK                       equ 8
LANG_GUJARATI                    equ 47h
LANG_HEBREW                      equ 0Dh
LANG_HINDI                       equ 39h
LANG_HUNGARIAN                   equ 0Eh
LANG_ICELANDIC                   equ 0Fh
LANG_INDONESIAN                  equ 21h
LANG_ITALIAN                     equ 10h
LANG_JAPANESE                    equ 11h
LANG_KANNADA                     equ 4Bh
LANG_KASHMIRI                    equ 60h
LANG_KAZAK                       equ 3Fh
LANG_KONKANI                     equ 57h
LANG_KOREAN                      equ 12h
LANG_LATVIAN                     equ 26h
LANG_LITHUANIAN                  equ 27h
LANG_MACEDONIAN                  equ 2Fh   ; the Former Yugoslav Republic of Macedonia
LANG_MALAY                       equ 3Eh
LANG_MALAYALAM                   equ 4Ch
LANG_MANIPURI					 equ 58h
LANG_MARATHI                     equ 4Eh
LANG_NORWEGIAN                   equ 14h
LANG_ORIYA                       equ 48h
LANG_POLISH                      equ 15h
LANG_PORTUGUESE                  equ 16h
LANG_PUNJABI                     equ 46h
LANG_ROMANIAN                    equ 18h
LANG_RUSSIAN                     equ 19h
LANG_SANSKRIT                    equ 4Fh
LANG_SERBIAN                     equ 1Ah
LANG_SINDHI                      equ 59h
LANG_SLOVAK                      equ 1Bh
LANG_SLOVENIAN                   equ 24h
LANG_SPANISH                     equ 0Ah
LANG_SWAHILI                     equ 41h
LANG_SWEDISH                     equ 1Dh
LANG_TAMIL                       equ 49h
LANG_TATAR                       equ 44h
LANG_TELUGU                      equ 4Ah
LANG_THAI                        equ 1Eh
LANG_TURKISH                     equ 1Fh
LANG_UKRAINIAN                   equ 22h
LANG_URDU                        equ 20h
LANG_UZBEK                       equ 43h
LANG_VIETNAMESE                  equ 2Ah
;  Sublanguage IDs.
;  The name immediately following SUBLANG_ dictates which primary
;  language ID that sublanguage ID can be combined with to form a
;  valid language ID.
SUBLANG_NEUTRAL                  equ 0    ; language neutral
SUBLANG_DEFAULT                  equ 1    ; user default
SUBLANG_SYS_DEFAULT              equ 2    ; system default
SUBLANG_ARABIC_SAUDI_ARABIA      equ 1    ; Arabic (Saudi Arabia)
SUBLANG_ARABIC_IRAQ              equ 2    ; Arabic (Iraq)
SUBLANG_ARABIC_EGYPT             equ 3    ; Arabic (Egypt)
SUBLANG_ARABIC_LIBYA             equ 4    ; Arabic (Libya)
SUBLANG_ARABIC_ALGERIA           equ 5    ; Arabic (Algeria)
SUBLANG_ARABIC_MOROCCO           equ 6    ; Arabic (Morocco)
SUBLANG_ARABIC_TUNISIA           equ 7    ; Arabic (Tunisia)
SUBLANG_ARABIC_OMAN              equ 8    ; Arabic (Oman)
SUBLANG_ARABIC_YEMEN             equ 9    ; Arabic (Yemen)
SUBLANG_ARABIC_SYRIA             equ 0Ah  ; Arabic (Syria)
SUBLANG_ARABIC_JORDAN            equ 0Bh  ; Arabic (Jordan)
SUBLANG_ARABIC_LEBANON           equ 0Ch  ; Arabic (Lebanon)
SUBLANG_ARABIC_KUWAIT            equ 0Dh  ; Arabic (Kuwait)
SUBLANG_ARABIC_UAE               equ 0Eh  ; Arabic (U.A.E)
SUBLANG_ARABIC_BAHRAIN           equ 0Fh  ; Arabic (Bahrain)
SUBLANG_ARABIC_QATAR             equ 10h  ; Arabic (Qatar)
SUBLANG_AZERI_LATIN              equ 1    ; Azeri (Latin)
SUBLANG_AZERI_CYRILLIC           equ 2    ; Azeri (Cyrillic)
SUBLANG_CHINESE_TRADITIONAL      equ 1    ; Chinese (Taiwan)
SUBLANG_CHINESE_SIMPLIFIED       equ 2    ; Chinese (PR China)
SUBLANG_CHINESE_HONGKONG         equ 3    ; Chinese (Hong Kong S.A.R., P.R.C.)
SUBLANG_CHINESE_SINGAPORE        equ 4    ; Chinese (Singapore)
SUBLANG_CHINESE_MACAU            equ 5    ; Chinese (Macau)
SUBLANG_DUTCH                    equ 1    ; Dutch
SUBLANG_DUTCH_BELGIAN            equ 2    ; Dutch (Belgian)
SUBLANG_ENGLISH_US               equ 1    ; English (USA)
SUBLANG_ENGLISH_UK               equ 2    ; English (UK)
SUBLANG_ENGLISH_AUS              equ 3    ; English (Australian)
SUBLANG_ENGLISH_CAN              equ 4    ; English (Canadian)
SUBLANG_ENGLISH_NZ               equ 5    ; English (New Zealand)
SUBLANG_ENGLISH_EIRE             equ 6    ; English (Irish)
SUBLANG_ENGLISH_SOUTH_AFRICA     equ 7    ; English (South Africa)
SUBLANG_ENGLISH_JAMAICA          equ 8    ; English (Jamaica)
SUBLANG_ENGLISH_CARIBBEAN        equ 9    ; English (Caribbean)
SUBLANG_ENGLISH_BELIZE           equ 0Ah  ; English (Belize)
SUBLANG_ENGLISH_TRINIDAD         equ 0Bh  ; English (Trinidad)
SUBLANG_ENGLISH_ZIMBABWE         equ 0Ch  ; English (Zimbabwe)
SUBLANG_ENGLISH_PHILIPPINES      equ 0Dh  ; English (Philippines)
SUBLANG_FRENCH                   equ 1    ; French
SUBLANG_FRENCH_BELGIAN           equ 2    ; French (Belgian)
SUBLANG_FRENCH_CANADIAN          equ 3    ; French (Canadian)
SUBLANG_FRENCH_SWISS             equ 4    ; French (Swiss)
SUBLANG_FRENCH_LUXEMBOURG        equ 5    ; French (Luxembourg)
SUBLANG_FRENCH_MONACO            equ 6    ; French (Monaco)
SUBLANG_GERMAN                   equ 1    ; German
SUBLANG_GERMAN_SWISS             equ 2    ; German (Swiss)
SUBLANG_GERMAN_AUSTRIAN          equ 3    ; German (Austrian)
SUBLANG_GERMAN_LUXEMBOURG        equ 4    ; German (Luxembourg)
SUBLANG_GERMAN_LIECHTENSTEIN     equ 5    ; German (Liechtenstein)
SUBLANG_ITALIAN                  equ 1    ; Italian
SUBLANG_ITALIAN_SWISS            equ 2    ; Italian (Swiss)
SUBLANG_KASHMIRI_INDIA           equ 2    ; Kashmiri (India)
SUBLANG_KOREAN                   equ 1    ; Korean (Extended Wansung)
SUBLANG_LITHUANIAN               equ 1    ; Lithuanian
SUBLANG_MALAY_MALAYSIA           equ 1    ; Malay (Malaysia)
SUBLANG_MALAY_BRUNEI_DARUSSALAM  equ 2    ; Malay (Brunei Darussalam)
SUBLANG_NEPALI_INDIA             equ 2    ; Nepali (India)
SUBLANG_NORWEGIAN_BOKMAL         equ 1    ; Norwegian (Bokmal)
SUBLANG_NORWEGIAN_NYNORSK        equ 2    ; Norwegian (Nynorsk)
SUBLANG_PORTUGUESE               equ 2    ; Portuguese
SUBLANG_PORTUGUESE_BRAZILIAN     equ 1    ; Portuguese (Brazilian)
SUBLANG_SERBIAN_LATIN            equ 2    ; Serbian (Latin)
SUBLANG_SERBIAN_CYRILLIC         equ 3    ; Serbian (Cyrillic)
SUBLANG_SPANISH                  equ 1    ; Spanish (Castilian)
SUBLANG_SPANISH_MEXICAN          equ 2    ; Spanish (Mexican)
SUBLANG_SPANISH_MODERN           equ 3    ; Spanish (Modern)
SUBLANG_SPANISH_GUATEMALA        equ 4    ; Spanish (Guatemala)
SUBLANG_SPANISH_COSTA_RICA       equ 5    ; Spanish (Costa Rica)
SUBLANG_SPANISH_PANAMA           equ 6    ; Spanish (Panama)
SUBLANG_SPANISH_DOMINICAN_REPUBLIC equ 7  ; Spanish (Dominican Republic)
SUBLANG_SPANISH_VENEZUELA        equ 8    ; Spanish (Venezuela)
SUBLANG_SPANISH_COLOMBIA         equ 9    ; Spanish (Colombia)
SUBLANG_SPANISH_PERU             equ 0Ah  ; Spanish (Peru)
SUBLANG_SPANISH_ARGENTINA        equ 0Bh  ; Spanish (Argentina)
SUBLANG_SPANISH_ECUADOR          equ 0Ch  ; Spanish (Ecuador)
SUBLANG_SPANISH_CHILE            equ 0Dh  ; Spanish (Chile)
SUBLANG_SPANISH_URUGUAY          equ 0Eh  ; Spanish (Uruguay)
SUBLANG_SPANISH_PARAGUAY         equ 0Fh  ; Spanish (Paraguay)
SUBLANG_SPANISH_BOLIVIA          equ 10h  ; Spanish (Bolivia)
SUBLANG_SPANISH_EL_SALVADOR      equ 11h  ; Spanish (El Salvador)
SUBLANG_SPANISH_HONDURAS         equ 12h  ; Spanish (Honduras)
SUBLANG_SPANISH_NICARAGUA        equ 13h  ; Spanish (Nicaragua)
SUBLANG_SPANISH_PUERTO_RICO      equ 14h  ; Spanish (Puerto Rico)
SUBLANG_SWEDISH                  equ 1    ; Swedish
SUBLANG_SWEDISH_FINLAND          equ 2    ; Swedish (Finland)
SUBLANG_URDU_PAKISTAN            equ 1    ; Urdu (Pakistan)
SUBLANG_URDU_INDIA               equ 2    ; Urdu (India)
SUBLANG_UZBEK_LATIN              equ 1    ; Uzbek (Latin)
SUBLANG_UZBEK_CYRILLIC           equ 2    ; Uzbek (Cyrillic)
;Sorting IDs.
SORT_DEFAULT                     equ 0     ; sorting default
SORT_JAPANESE_XJIS               equ 0     ; Japanese XJIS order
SORT_JAPANESE_UNICODE            equ 1     ; Japanese Unicode order
SORT_CHINESE_BIG5                equ 0     ; Chinese BIG5 order
SORT_CHINESE_PRCP                equ 0     ; PRC Chinese Phonetic order
SORT_CHINESE_UNICODE             equ 1     ; Chinese Unicode order
SORT_CHINESE_PRC                 equ 2     ; PRC Chinese Stroke Count order
SORT_CHINESE_BOPOMOFO            equ 3     ; Traditional Chinese Bopomofo order
SORT_KOREAN_KSC                  equ 0     ; Korean KSC order
SORT_KOREAN_UNICODE              equ 1     ; Korean Unicode order
SORT_GERMAN_PHONE_BOOK           equ 1     ; German Phone Book order
SORT_HUNGARIAN_DEFAULT           equ 0     ; Hungarian Default order
SORT_HUNGARIAN_TECHNICAL         equ 1     ; Hungarian Technical order
SORT_GEORGIAN_TRADITIONAL        equ 0     ; Georgian Traditional order
SORT_GEORGIAN_MODERN             equ 1     ; Georgian Modern order
