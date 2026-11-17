WINDOWS_AF_IRDA         equ 26
WINDOWS_PF_IRDA         equ WINDOWS_AF_IRDA
WCE_AF_IRDA             equ 22
WCE_PF_IRDA             equ WCE_AF_IRDA
AF_IRDA	                equ WINDOWS_AF_IRDA
IRDA_PROTO_SOCK_STREAM  equ 1
PF_IRDA                 equ AF_IRDA
SOL_IRLMP		        equ 0FFh
IRLMP_ENUMDEVICES       equ 10h
IRLMP_IAS_SET           equ 11h
IRLMP_IAS_QUERY         equ 12h
IRLMP_SEND_PDU_LEN      equ 13h
IRLMP_EXCLUSIVE_MODE    equ 14h
IRLMP_IRLPT_MODE        equ 15h
IRLMP_9WIRE_MODE        equ 16h
IRLMP_TINYTP_MODE       equ 17h
IRLMP_PARAMETERS		equ 18h
IRLMP_DISCOVERY_MODE	equ 19h
IRLMP_SHARP_MODE        equ 20h
IAS_ATTRIB_NO_CLASS     equ 10h
IAS_ATTRIB_NO_ATTRIB    equ 0
IAS_ATTRIB_INT          equ 1
IAS_ATTRIB_OCTETSEQ     equ 2
IAS_ATTRIB_STR          equ 3
IAS_MAX_USER_STRING		equ 256
IAS_MAX_OCTET_STRING	equ 1024
IAS_MAX_CLASSNAME		equ 64
IAS_MAX_ATTRIBNAME		equ 256
LM_HB_Extension         equ 128     ; Any hint byte
LM_HB1_PnP              equ 1       ; First hint byte
LM_HB1_PDA_Palmtop      equ 2
LM_HB1_Computer         equ 4
LM_HB1_Printer          equ 8
LM_HB1_Modem            equ 16
LM_HB1_Fax              equ 32
LM_HB1_LANAccess        equ 64
LM_HB2_Telephony        equ 1       ; Second hint byte
LM_HB2_FileServer       equ 2
LmCharSetASCII          equ 0
LmCharSetISO_8859_1     equ 1
LmCharSetISO_8859_2     equ 2
LmCharSetISO_8859_3     equ 3
LmCharSetISO_8859_4     equ 4
LmCharSetISO_8859_5     equ 5
LmCharSetISO_8859_6     equ 6
LmCharSetISO_8859_7     equ 7
LmCharSetISO_8859_8     equ 8
LmCharSetISO_8859_9     equ 9
LmCharSetUNICODE        equ 0FFh
LM_BAUD_RATE	TYPEDEF u_long
LM_BAUD_1200           equ 1200
LM_BAUD_2400           equ 2400
LM_BAUD_9600           equ 9600
LM_BAUD_19200          equ 19200
LM_BAUD_38400          equ 38400
LM_BAUD_57600          equ 57600
LM_BAUD_115200         equ 115200
LM_BAUD_576K           equ 576000
LM_BAUD_1152K          equ 1152000
LM_BAUD_4M             equ 4000000
LM_IRPARMS STRUC
	nTXDataBytes	u_long ?	; Max tx data bytes per packet
	nRXDataBytes	u_long ?	; Max rx data bytes per packet
	nBaudRate		LM_BAUD_RATE ?	;Negotiated baud rate
	thresholdTime	u_long ?	; Threshold (ms)
	discTime		u_long ?	; Disconnect (ms)
	nMSLinkTurn		u_short ?	; Link turn around (ms)
	nTXPackets		u_char ?	; Number packets in transmit window
	nRXPackets		u_char ?	; Number packets in receive window
LM_IRPARMS ENDS
PLM_IRPARMS TYPEDEF PTR LM_IRPARMS
SOCKADDR_IRDA STRUC
	irdaAddressFamily	u_short ?
	irdaDeviceID		u_char 4 dup(?)
	irdaServiceName		u_char 25 dup(?)
SOCKADDR_IRDA ENDS
PSOCKADDR_IRDA TYPEDEF PTR SOCKADDR_IRDA
WINDOWS_IRDA_DEVICE_INFO STRUC
	irdaDeviceID		u_char 4 dup(?)
	irdaDeviceName		char 22 dup(?)
	irdaDeviceHints1	u_char ?
	irdaDeviceHints2	u_char ?
	irdaCharSet			u_char ?
WINDOWS_IRDA_DEVICE_INFO ENDS
PWINDOWS_IRDA_DEVICE_INFO TYPEDEF PTR WINDOWS_IRDA_DEVICE_INFO
WCE_IRDA_DEVICE_INFO STRUC
	irdaDeviceID	u_char 4 dup(?)
	irdaDeviceName	char 22 dup(?)
	Reserved		u_char 2 dup(?)
WCE_IRDA_DEVICE_INFO ENDS
PWCE_IRDA_DEVICE_INFO	TYPEDEF WCE_IRDA_DEVICE_INFO
IRDA_DEVICE_INFO		TYPEDEF WINDOWS_IRDA_DEVICE_INFO
PIRDA_DEVICE_INFO		TYPEDEF IRDA_DEVICE_INFO
WINDOWS_DEVICELIST STRUC
	numDevice	ULONG ?
	Device		WINDOWS_IRDA_DEVICE_INFO<>
WINDOWS_DEVICELIST ENDS
PWINDOWS_DEVICELIST		TYPEDEF PTR WINDOWS_DEVICELIST
LPWINDOWS_DEVICELIST	TYPEDEF PTR WINDOWS_DEVICELIST
DEVICELIST TYPEDEF WINDOWS_DEVICELIST
PDEVICELIST TYPEDEF PTR DEVICELIST
LPDEVICELIST TYPEDEF PTR PDEVICELIST
WINDOWS_IAS_SET STRUC
	irdaClassName		char IAS_MAX_CLASSNAME dup(?)
	irdaAttribName		char IAS_MAX_ATTRIBNAME dup(?)
	irdaAttribType		u_long ?
	UNION irdaAttribute
		irdaAttribInt	LONG ?
		STRUC irdaAttribOctetSeq
			Len			u_short ?
			OctetSeq	u_char IAS_MAX_OCTET_STRING dup(?)
		ENDS
		STRUC irdaAttribUsrStr
			Len		u_char ?
			CharSet	u_char ?
			UsrStr	u_char IAS_MAX_USER_STRING dup(?)
		ENDS
	ENDS
WINDOWS_IAS_SET ENDS
PWINDOWS_IAS_SET TYPEDEF PTR WINDOWS_IAS_SET
LPWINDOWS_IAS_SET TYPEDEF PTR WINDOWS_IAS_SET
WINDOWS_IAS_QUERY STRUC
	irdaDeviceID	u_char 4 dup(?)
	irdaClassName	char IAS_MAX_CLASSNAME dup(?)
	irdaAttribName	char IAS_MAX_ATTRIBNAME dup(?)
	irdaAttribType	u_long ?
    UNION irdaAttribute
		irdaAttribInt	LONG ?
		STRUC irdaAttribOctetSeq
			Len			u_long ?
			OctetSeq	u_char IAS_MAX_OCTET_STRING dup(?)
		ENDS
		STRUC irdaAttribUsrStr
			Len		u_long ?
			CharSet	u_long ?
			UsrStr	u_char IAS_MAX_USER_STRING dup(?)
		ENDS
	ENDS
WINDOWS_IAS_QUERY ENDS
PWINDOWS_IAS_QUERY TYPEDEF PTR WINDOWS_IAS_QUERY
LPWINDOWS_IAS_QUERY TYPEDEF PTR WINDOWS_IAS_QUERY
IAS_SET TYPEDEF WINDOWS_IAS_SET
PIAS_SET TYPEDEF PTR IAS_SET
LPIAS_SET TYPEDEF PTR IAS_SET
PIAS_QUERY TYPEDEF PTR IAS_QUERY
LPIAS_QUERY TYPEDEF PTR IAS_QUERY