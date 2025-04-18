'' FreeBASIC binding for mingw-w64-v4.0.4
''
'' based on the C header files:
''   This Software is provided under the Zope Public License (ZPL) Version 2.1.
''
''   Copyright (c) 2009, 2010 by the mingw-w64 project
''
''   See the AUTHORS file for the list of contributors to the mingw-w64 project.
''
''   This license has been certified as open source. It has also been designated
''   as GPL compatible by the Free Software Foundation (FSF).
''
''   Redistribution and use in source and binary forms, with or without
''   modification, are permitted provided that the following conditions are met:
''
''     1. Redistributions in source code must retain the accompanying copyright
''        notice, this list of conditions, and the following disclaimer.
''     2. Redistributions in binary form must reproduce the accompanying
''        copyright notice, this list of conditions, and the following disclaimer
''        in the documentation and/or other materials provided with the
''        distribution.
''     3. Names of the copyright holders must not be used to endorse or promote
''        products derived from this software without prior written permission
''        from the copyright holders.
''     4. The right to distribute this software or to use it for any purpose does
''        not give you the right to use Servicemarks (sm) or Trademarks (tm) of
''        the copyright holders.  Use of them is covered by separate agreement
''        with the copyright holders.
''     5. If any files are modified, you must cause the modified files to carry
''        prominent notices stating that you changed the files and the date of
''        any change.
''
''   Disclaimer
''
''   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY EXPRESSED
''   OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
''   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
''   EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DIRECT, INDIRECT,
''   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
''   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
''   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
''   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
''   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
''   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
''
'' translated to FreeBASIC by:
''   FreeBASIC development team

#pragma once

#include once "winapifamily.bi"

#define _RASERROR_H_
const RASBASE = 600
const SUCCESS = 0
const PENDING = RASBASE + 0
const ERROR_INVALID_PORT_HANDLE = RASBASE + 1
const ERROR_PORT_ALREADY_OPEN = RASBASE + 2
const ERROR_BUFFER_TOO_SMALL = RASBASE + 3
const ERROR_WRONG_INFO_SPECIFIED = RASBASE + 4
const ERROR_PORT_NOT_CONNECTED = RASBASE + 6
const ERROR_DEVICE_DOES_NOT_EXIST = RASBASE + 8
const ERROR_DEVICETYPE_DOES_NOT_EXIST = RASBASE + 9
const ERROR_BUFFER_INVALID = RASBASE + 10
const ERROR_ROUTE_NOT_ALLOCATED = RASBASE + 12
const ERROR_PORT_NOT_FOUND = RASBASE + 15
const ERROR_ASYNC_REQUEST_PENDING = RASBASE + 16
const ERROR_ALREADY_DISCONNECTING = RASBASE + 17
const ERROR_PORT_NOT_OPEN = RASBASE + 18
const ERROR_PORT_DISCONNECTED = RASBASE + 19
const ERROR_CANNOT_OPEN_PHONEBOOK = RASBASE + 21
const ERROR_CANNOT_LOAD_PHONEBOOK = RASBASE + 22
const ERROR_CANNOT_FIND_PHONEBOOK_ENTRY = RASBASE + 23
const ERROR_CANNOT_WRITE_PHONEBOOK = RASBASE + 24
const ERROR_CORRUPT_PHONEBOOK = RASBASE + 25
const ERROR_KEY_NOT_FOUND = RASBASE + 27
const ERROR_DISCONNECTION = RASBASE + 28
const ERROR_REMOTE_DISCONNECTION = RASBASE + 29
const ERROR_HARDWARE_FAILURE = RASBASE + 30
const ERROR_USER_DISCONNECTION = RASBASE + 31
const ERROR_INVALID_SIZE = RASBASE + 32
const ERROR_PORT_NOT_AVAILABLE = RASBASE + 33
const ERROR_UNKNOWN = RASBASE + 35
const ERROR_WRONG_DEVICE_ATTACHED = RASBASE + 36
const ERROR_REQUEST_TIMEOUT = RASBASE + 38
const ERROR_AUTH_INTERNAL = RASBASE + 45
const ERROR_RESTRICTED_LOGON_HOURS = RASBASE + 46
const ERROR_ACCT_DISABLED = RASBASE + 47
const ERROR_PASSWD_EXPIRED = RASBASE + 48
const ERROR_NO_DIALIN_PERMISSION = RASBASE + 49
const ERROR_FROM_DEVICE = RASBASE + 51
const ERROR_UNRECOGNIZED_RESPONSE = RASBASE + 52
const ERROR_MACRO_NOT_FOUND = RASBASE + 53
const ERROR_MACRO_NOT_DEFINED = RASBASE + 54
const ERROR_MESSAGE_MACRO_NOT_FOUND = RASBASE + 55
const ERROR_DEFAULTOFF_MACRO_NOT_FOUND = RASBASE + 56
const ERROR_FILE_COULD_NOT_BE_OPENED = RASBASE + 57
const ERROR_DEVICENAME_TOO_LONG = RASBASE + 58
const ERROR_DEVICENAME_NOT_FOUND = RASBASE + 59
const ERROR_NO_RESPONSES = RASBASE + 60
const ERROR_NO_COMMAND_FOUND = RASBASE + 61
const ERROR_WRONG_KEY_SPECIFIED = RASBASE + 62
const ERROR_UNKNOWN_DEVICE_TYPE = RASBASE + 63
const ERROR_ALLOCATING_MEMORY = RASBASE + 64
const ERROR_PORT_NOT_CONFIGURED = RASBASE + 65
const ERROR_DEVICE_NOT_READY = RASBASE + 66
const ERROR_READING_INI_FILE = RASBASE + 67
const ERROR_NO_CONNECTION = RASBASE + 68
const ERROR_BAD_USAGE_IN_INI_FILE = RASBASE + 69
const ERROR_READING_SECTIONNAME = RASBASE + 70
const ERROR_READING_DEVICETYPE = RASBASE + 71
const ERROR_READING_DEVICENAME = RASBASE + 72
const ERROR_READING_USAGE = RASBASE + 73
const ERROR_LINE_BUSY = RASBASE + 76
const ERROR_VOICE_ANSWER = RASBASE + 77
const ERROR_NO_ANSWER = RASBASE + 78
const ERROR_NO_CARRIER = RASBASE + 79
const ERROR_NO_DIALTONE = RASBASE + 80
const ERROR_AUTHENTICATION_FAILURE = RASBASE + 91
const ERROR_PORT_OR_DEVICE = RASBASE + 92
const ERROR_NOT_BINARY_MACRO = RASBASE + 93
const ERROR_DCB_NOT_FOUND = RASBASE + 94
const ERROR_STATE_MACHINES_NOT_STARTED = RASBASE + 95
const ERROR_STATE_MACHINES_ALREADY_STARTED = RASBASE + 96
const ERROR_PARTIAL_RESPONSE_LOOPING = RASBASE + 97
const ERROR_UNKNOWN_RESPONSE_KEY = RASBASE + 98
const ERROR_RECV_BUF_FULL = RASBASE + 99
const ERROR_CMD_TOO_LONG = RASBASE + 100
const ERROR_UNSUPPORTED_BPS = RASBASE + 101
const ERROR_UNEXPECTED_RESPONSE = RASBASE + 102
const ERROR_INTERACTIVE_MODE = RASBASE + 103
const ERROR_BAD_CALLBACK_NUMBER = RASBASE + 104
const ERROR_INVALID_AUTH_STATE = RASBASE + 105
const ERROR_X25_DIAGNOSTIC = RASBASE + 107
const ERROR_ACCT_EXPIRED = RASBASE + 108
const ERROR_CHANGING_PASSWORD = RASBASE + 109
const ERROR_OVERRUN = RASBASE + 110
const ERROR_RASMAN_CANNOT_INITIALIZE = RASBASE + 111
const ERROR_NO_ACTIVE_ISDN_LINES = RASBASE + 113
const ERROR_IP_CONFIGURATION = RASBASE + 116
const ERROR_NO_IP_ADDRESSES = RASBASE + 117
const ERROR_PPP_TIMEOUT = RASBASE + 118
const ERROR_PPP_NO_PROTOCOLS_CONFIGURED = RASBASE + 120
const ERROR_PPP_NO_RESPONSE = RASBASE + 121
const ERROR_PPP_INVALID_PACKET = RASBASE + 122
const ERROR_PHONE_NUMBER_TOO_LONG = RASBASE + 123
const ERROR_IPXCP_DIALOUT_ALREADY_ACTIVE = RASBASE + 126
const ERROR_NO_IP_RAS_ADAPTER = RASBASE + 128
const ERROR_SLIP_REQUIRES_IP = RASBASE + 129
const ERROR_PROTOCOL_NOT_CONFIGURED = RASBASE + 131
const ERROR_PPP_NOT_CONVERGING = RASBASE + 132
const ERROR_PPP_CP_REJECTED = RASBASE + 133
const ERROR_PPP_LCP_TERMINATED = RASBASE + 134
const ERROR_PPP_REQUIRED_ADDRESS_REJECTED = RASBASE + 135
const ERROR_PPP_NCP_TERMINATED = RASBASE + 136
const ERROR_PPP_LOOPBACK_DETECTED = RASBASE + 137
const ERROR_PPP_NO_ADDRESS_ASSIGNED = RASBASE + 138
const ERROR_CANNOT_USE_LOGON_CREDENTIALS = RASBASE + 139
const ERROR_TAPI_CONFIGURATION = RASBASE + 140
const ERROR_NO_LOCAL_ENCRYPTION = RASBASE + 141
const ERROR_NO_REMOTE_ENCRYPTION = RASBASE + 142
const ERROR_BAD_PHONE_NUMBER = RASBASE + 149
const ERROR_SCRIPT_SYNTAX = RASBASE + 152
const ERROR_HANGUP_FAILED = RASBASE + 153
const ERROR_BUNDLE_NOT_FOUND = RASBASE + 154
const ERROR_CANNOT_DO_CUSTOMDIAL = RASBASE + 155
const ERROR_DIAL_ALREADY_IN_PROGRESS = RASBASE + 156
const ERROR_RASAUTO_CANNOT_INITIALIZE = RASBASE + 157
const ERROR_NO_SMART_CARD_READER = RASBASE + 164
const ERROR_SHARING_ADDRESS_EXISTS = RASBASE + 165
const ERROR_NO_CERTIFICATE = RASBASE + 166
const ERROR_SHARING_MULTIPLE_ADDRESSES = RASBASE + 167
const ERROR_FAILED_TO_ENCRYPT = RASBASE + 168
const ERROR_BAD_ADDRESS_SPECIFIED = RASBASE + 169
const ERROR_CONNECTION_REJECT = RASBASE + 170
const ERROR_CONGESTION = RASBASE + 171
const ERROR_INCOMPATIBLE = RASBASE + 172
const ERROR_NUMBERCHANGED = RASBASE + 173
const ERROR_TEMPFAILURE = RASBASE + 174
const ERROR_BLOCKED = RASBASE + 175
const ERROR_DONOTDISTURB = RASBASE + 176
const ERROR_OUTOFORDER = RASBASE + 177
const ERROR_UNABLE_TO_AUTHENTICATE_SERVER = RASBASE + 178
const ERROR_INVALID_FUNCTION_FOR_ENTRY = RASBASE + 180
const ERROR_SHARING_RRAS_CONFLICT = RASBASE + 182
const ERROR_SHARING_NO_PRIVATE_LAN = RASBASE + 183
const ERROR_NO_DIFF_USER_AT_LOGON = RASBASE + 184
const ERROR_NO_REG_CERT_AT_LOGON = RASBASE + 185
const ERROR_OAKLEY_NO_CERT = RASBASE + 186
const ERROR_OAKLEY_AUTH_FAIL = RASBASE + 187
const ERROR_OAKLEY_ATTRIB_FAIL = RASBASE + 188
const ERROR_OAKLEY_GENERAL_PROCESSING = RASBASE + 189
const ERROR_OAKLEY_NO_PEER_CERT = RASBASE + 190
const ERROR_OAKLEY_NO_POLICY = RASBASE + 191
const ERROR_OAKLEY_TIMED_OUT = RASBASE + 192
const ERROR_OAKLEY_ERROR = RASBASE + 193
const ERROR_UNKNOWN_FRAMED_PROTOCOL = RASBASE + 194
const ERROR_WRONG_TUNNEL_TYPE = RASBASE + 195
const ERROR_UNKNOWN_SERVICE_TYPE = RASBASE + 196
const ERROR_CONNECTING_DEVICE_NOT_FOUND = RASBASE + 197
const ERROR_NO_EAPTLS_CERTIFICATE = RASBASE + 198
const ERROR_SHARING_HOST_ADDRESS_CONFLICT = RASBASE + 199
const ERROR_AUTOMATIC_VPN_FAILED = RASBASE + 200
const ERROR_VALIDATING_SERVER_CERT = RASBASE + 201
const ERROR_READING_SCARD = RASBASE + 202
const ERROR_INVALID_PEAP_COOKIE_CONFIG = RASBASE + 203
const ERROR_INVALID_PEAP_COOKIE_USER = RASBASE + 204
const ERROR_INVALID_MSCHAPV2_CONFIG = RASBASE + 205
const ERROR_VPN_GRE_BLOCKED = RASBASE + 206
const ERROR_VPN_DISCONNECT = RASBASE + 207
const ERROR_VPN_REFUSED = RASBASE + 208
const ERROR_VPN_TIMEOUT = RASBASE + 209
const ERROR_VPN_BAD_CERT = RASBASE + 210
const ERROR_VPN_BAD_PSK = RASBASE + 211
const ERROR_SERVER_POLICY = RASBASE + 212
const ERROR_BROADBAND_ACTIVE = RASBASE + 213
const ERROR_BROADBAND_NO_NIC = RASBASE + 214
const ERROR_BROADBAND_TIMEOUT = RASBASE + 215
const ERROR_FEATURE_DEPRECATED = RASBASE + 216
const ERROR_CANNOT_DELETE = RASBASE + 217
const ERROR_PEAP_CRYPTOBINDING_INVALID = RASBASE + 223
const ERROR_PEAP_CRYPTOBINDING_NOTRECEIVED = RASBASE + 224
const ERROR_EAPTLS_CACHE_CREDENTIALS_INVALID = RASBASE + 226
const ERROR_IPSEC_SERVICE_STOPPED = RASBASE + 227

#if _WIN32_WINNT <= &h0502
	const ERROR_CANNOT_SET_PORT_INFO = RASBASE + 5
	const ERROR_EVENT_INVALID = RASBASE + 7
	const ERROR_ROUTE_NOT_AVAILABLE = RASBASE + 11
	const ERROR_INVALID_COMPRESSION_SPECIFIED = RASBASE + 13
	const ERROR_OUT_OF_BUFFERS = RASBASE + 14
	const ERROR_NO_ENDPOINTS = RASBASE + 20
	const ERROR_CANNOT_LOAD_STRING = RASBASE + 26
	const ERROR_CANNOT_PROJECT_CLIENT = RASBASE + 34
	const ERROR_BAD_STRING = RASBASE + 37
	const ERROR_CANNOT_GET_LANA = RASBASE + 39
	const ERROR_NETBIOS_ERROR = RASBASE + 40
	const ERROR_SERVER_OUT_OF_RESOURCES = RASBASE + 41
	const ERROR_NAME_EXISTS_ON_NET = RASBASE + 42
	const ERROR_SERVER_GENERAL_NET_FAILURE = RASBASE + 43
	const WARNING_MSG_ALIAS_NOT_ADDED = RASBASE + 44
	const ERROR_SERVER_NOT_RESPONDING = RASBASE + 50
	const ERROR_READING_MAXCONNECTBPS = RASBASE + 74
	const ERROR_READING_MAXCARRIERBPS = RASBASE + 75
	const ERROR_IN_COMMAND = RASBASE + 81
	const ERROR_WRITING_SECTIONNAME = RASBASE + 82
	const ERROR_WRITING_DEVICETYPE = RASBASE + 83
	const ERROR_WRITING_DEVICENAME = RASBASE + 84
	const ERROR_WRITING_MAXCONNECTBPS = RASBASE + 85
	const ERROR_WRITING_MAXCARRIERBPS = RASBASE + 86
	const ERROR_WRITING_USAGE = RASBASE + 87
	const ERROR_WRITING_DEFAULTOFF = RASBASE + 88
	const ERROR_READING_DEFAULTOFF = RASBASE + 89
	const ERROR_EMPTY_INI_FILE = RASBASE + 90
	const ERROR_WRITING_INITBPS = RASBASE + 106
	const ERROR_BIPLEX_PORT_NOT_AVAILABLE = RASBASE + 112
	const ERROR_NO_ISDN_CHANNELS_AVAILABLE = RASBASE + 114
	const ERROR_TOO_MANY_LINE_ERRORS = RASBASE + 115
	const ERROR_PPP_REMOTE_TERMINATED = RASBASE + 119
	const ERROR_IPXCP_NO_DIALOUT_CONFIGURED = RASBASE + 124
	const ERROR_IPXCP_NO_DIALIN_CONFIGURED = RASBASE + 125
	const ERROR_ACCESSING_TCPCFGDLL = RASBASE + 127
	const ERROR_PROJECTION_NOT_COMPLETE = RASBASE + 130
	const ERROR_REMOTE_REQUIRES_ENCRYPTION = RASBASE + 143
	const ERROR_IPXCP_NET_NUMBER_CONFLICT = RASBASE + 144
	const ERROR_INVALID_SMM = RASBASE + 145
	const ERROR_SMM_UNINITIALIZED = RASBASE + 146
	const ERROR_NO_MAC_FOR_PORT = RASBASE + 147
	const ERROR_SMM_TIMEOUT = RASBASE + 148
	const ERROR_WRONG_MODULE = RASBASE + 150
	const ERROR_INVALID_CALLBACK_NUMBER = RASBASE + 151
	const ERROR_CONNECTION_ALREADY_SHARED = RASBASE + 158
	const ERROR_SHARING_CHANGE_FAILED = RASBASE + 159
	const ERROR_SHARING_ROUTER_INSTALL = RASBASE + 160
	const ERROR_SHARE_CONNECTION_FAILED = RASBASE + 161
	const ERROR_SHARING_PRIVATE_INSTALL = RASBASE + 162
	const ERROR_CANNOT_SHARE_CONNECTION = RASBASE + 163
	const ERROR_SMART_CARD_REQUIRED = RASBASE + 179
	const ERROR_CERT_FOR_ENCRYPTION_NOT_FOUND = RASBASE + 181
#endif

#if _WIN32_WINNT <= &h0600
	const ERROR_RASQEC_RESOURCE_CREATION_FAILED = RASBASE + 218
	const ERROR_RASQEC_NAPAGENT_NOT_ENABLED = RASBASE + 219
	const ERROR_RASQEC_NAPAGENT_NOT_CONNECTED = RASBASE + 220
	const ERROR_RASQEC_CONN_DOESNOTEXIST = RASBASE + 221
	const ERROR_RASQEC_TIMEOUT = RASBASE + 222
#endif

#if _WIN32_WINNT >= &h0600
	const ERROR_INVALID_VPNSTRATEGY = RASBASE + 225
	const ERROR_IDLE_TIMEOUT = RASBASE + 228
	const ERROR_LINK_FAILURE = RASBASE + 229
	const ERROR_USER_LOGOFF = RASBASE + 230
	const ERROR_FAST_USER_SWITCH = RASBASE + 231
	const ERROR_HIBERNATION = RASBASE + 232
	const ERROR_SYSTEM_SUSPENDED = RASBASE + 233
	const ERROR_RASMAN_SERVICE_STOPPED = RASBASE + 234
	const ERROR_INVALID_SERVER_CERT = RASBASE + 235
	const ERROR_NOT_NAP_CAPABLE = RASBASE + 236
#endif

#if _WIN32_WINNT >= &h0601
	const ERROR_INVALID_TUNNELID = RASBASE + 237
	const ERROR_UPDATECONNECTION_REQUEST_IN_PROCESS = RASBASE + 238
	const ERROR_PROTOCOL_ENGINE_DISABLED = RASBASE + 239
	const ERROR_INTERNAL_ADDRESS_FAILURE = RASBASE + 240
	const ERROR_FAILED_CP_REQUIRED = RASBASE + 241
	const ERROR_TS_UNACCEPTABLE = RASBASE + 242
	const ERROR_MOBIKE_DISABLED = RASBASE + 243
	const ERROR_CANNOT_INITIATE_MOBIKE_UPDATE = RASBASE + 244
	const ERROR_PEAP_SERVER_REJECTED_CLIENT_TLV = RASBASE + 245
	const ERROR_INVALID_PREFERENCES = RASBASE + 246
	const ERROR_EAPTLS_SCARD_CACHE_CREDENTIALS_INVALID = RASBASE + 247
	const ERROR_SSTP_COOKIE_SET_FAILURE = RASBASE + 248
	const ERROR_INVALID_PEAP_COOKIE_ATTRIBUTES = RASBASE + 249
	const ERROR_EAP_METHOD_NOT_INSTALLED = RASBASE + 250
	const ERROR_EAP_METHOD_DOES_NOT_SUPPORT_SSO = RASBASE + 251
	const ERROR_EAP_METHOD_OPERATION_NOT_SUPPORTED = RASBASE + 252
	const ERROR_EAP_USER_CERT_INVALID = RASBASE + 253
	const ERROR_EAP_USER_CERT_EXPIRED = RASBASE + 254
	const ERROR_EAP_USER_CERT_REVOKED = RASBASE + 255
	const ERROR_EAP_USER_CERT_OTHER_ERROR = RASBASE + 256
	const ERROR_EAP_SERVER_CERT_INVALID = RASBASE + 257
	const ERROR_EAP_SERVER_CERT_EXPIRED = RASBASE + 258
	const ERROR_EAP_SERVER_CERT_REVOKED = RASBASE + 259
	const ERROR_EAP_SERVER_CERT_OTHER_ERROR = RASBASE + 260
	const ERROR_EAP_USER_ROOT_CERT_NOT_FOUND = RASBASE + 261
	const ERROR_EAP_USER_ROOT_CERT_INVALID = RASBASE + 262
	const ERROR_EAP_USER_ROOT_CERT_EXPIRED = RASBASE + 263
	const ERROR_EAP_SERVER_ROOT_CERT_NOT_FOUND = RASBASE + 264
	const ERROR_EAP_SERVER_ROOT_CERT_INVALID = RASBASE + 265
	const ERROR_EAP_SERVER_ROOT_CERT_NAME_REQUIRED = RASBASE + 266
	const ERROR_PEAP_IDENTITY_MISMATCH = RASBASE + 267
	const ERROR_DNSNAME_NOT_RESOLVABLE = RASBASE + 268
	const ERROR_EAPTLS_PASSWD_INVALID = RASBASE + 269
	const ERROR_IKEV2_PSK_INTERFACE_ALREADY_EXISTS = RASBASE + 270
#endif

const RASBASEEND = RASBASE + 270
