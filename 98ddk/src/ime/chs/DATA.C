#include <windows.h>
#include "imm.h"
#include "imedefs.h"

#pragma data_seg(".ShareDate")
IMEG      sImeG = {0};

CHAR SKLayout[NumsSK][48*2] = {
    "����������������������������������������������������������������������ۣܣݣ�",
	"��                    �ʦ֦Ԧ̦æͦΦϦȦЦ�  �ئצ�  ���Ħ˦ŦǦզ¦ӦƦ�                      ",
	"��                    �ݧ��ߧӧ���ا������٧ڧѧԧާէק�ҧ�֧��  ��  ���  ��  �ܧ�",
	"�����    ��    �ڨި�Ǩ֨ϨΨͨѨըبۨ�ܨ��٨ߨ�ƨШ˨Ԩ�Ҩ�  �רȨ�  ��  ����        ",
	"��                    ��  ��������  ����������������  ������  ������������    ��  ����  ��      ",
	"��  �������������������ʤ��̤��ͤΤϤĤҤդؤ��äƤ����ˤ����ᤷ�ߤ��ޤ�  ����򤡤�  ���",
	"�����������������������ʥ��̥��ͥΥϥĥҥեإ��åƥ����˥����᥷�ߥ��ޥۥ������򥡥ȥ���",
	"���������������������������������������á������ۣ������������������������������ݡ��������ࡨ����",
	"����������������������ɢǢ碳���ꢸ�����ˢʢ��������梵���Ȣ��Ƣ��Ţ�  �̢��͢΢�        ",
	"��  �ԡ٣��ܡݣ����ڡۡġѡϡƣ��ǡȡɡҡ�  �ߡסաӡء����š�  �У��Σ��͡�    �ˡ�  �֡�      ",
	"��������꣤�룥���  ��������׼���̫�İ�    �˾š���ǧ����΢һ�����      ��      ʮ      ",
	"������������������  ���Щ��ҩ©өԩթǩ֩�  ���  �����éѩĩƩ����ũ�    �穬    ����  ��  ",
	"��                    ���ޣ��������������������ߡ����������ܡ�����                      ",
    };
CHAR SKLayoutS[NumsSK][48*2] = {
	"�����������磥�ޣ��������£ãģţƣǣȣɣʣˣ̣ͣΣϣУѣңӣԣգ֣ףأ٣ڣ������ߣ�������������",
	"                      ����������������������  ������  ��������������������                      ",
	"                      ������������������������������������������������������  ��  ����  ��  ����",
	"                                                                                                ",
	"                                                                                                ",
	"    �������������������Ѥ���פ��ڤݤܤŤӤ֤٤��  �Ǥ����Ԥ��¤줸������  ��  ��  ����      ",
	"  ������  ������  �����ѥ���ץ��ڥݥХťӥ֥٥��  �ǥ����ԥ��¥쥸�����ܥ���  ��  ����      ",
	"                                                                                                ",
	"                      �٢ӢѢۢ��ܢݢޢ¢ߢ��բԢâĢ����ڢ����Ң��Т��Ϣ�  ��  �ע�          ",
	"                                                                                                ",
	"                      ��      ��      ��          �ƾ�����Ǫ��½  Ҽ  ��                ʰ      ",
	"  ����������������  ���ة��کʩ۩ܩݩϩީ�  ���  ���ȩ˩٩̩Ω�ɩ�ͩ�    �舘    ����  ��  ",
	"                                                                                                ",
	};
#pragma data_seg()

HDC   ST_UI_hDC;
UINT  uStartComp = 0;
UINT  uOpenCand = 0;
UINT  uCaps = 0;
DWORD SaTC_Trace;

HINSTANCE hInst;
IMEL      sImeL;
LPIMEL    lpImeL;
BYTE      szUIClassName[CLASS_LEN];
BYTE      szCompClassName[CLASS_LEN];
BYTE      szCandClassName[CLASS_LEN];
BYTE      szStatusClassName[CLASS_LEN];
BYTE      szCMenuClassName[CLASS_LEN];			
BYTE      szSoftkeyMenuClassName[CLASS_LEN];	
BYTE      szHandCursor[] = "Hand";
BYTE      szChinese[] = "Chinese";
BYTE      szEnglish[] = "English";
TCHAR		pszImeName[IMEINDEXNUM][MAX_PATH]={
			"��λ",
			"GBK����",
			"UNICODE"};
TCHAR		*szImeName;
TCHAR		szImeRegName[]="����";
BYTE      szCode[] = "Code";
BYTE      szEudc[] = "Eudc";
BYTE      szFullShape[] = "FullShape";
BYTE      szHalfShape[] = "HalfShape";
BYTE      szSymbol[] = "Symbol";
BYTE      szNoSymbol[] = "NoSymbol";
BYTE      szNone[] = "None";
BYTE      szSoftKBD[] = "SoftKBD";
BYTE      szNoSoftKBD[] = "NoSoftKBD";
BYTE      szDigit[] = "01234567890";
BYTE      szCandInf[] = "   ���ּ�";
BYTE	  szTrace[]= "������";
BYTE szRegRevKL[] = "�����ѯ";
BYTE szRegRevMaxKey[] = "�����ѯ�볤";
BYTE	  szWarnTitle[]="����";	
BYTE	  szErrorTitle[]="����";

// convert char to upper case
BYTE bUpper[] = {
// 0x20 - 0x27
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
// 0x28 - 0x2F
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
// 0x30 - 0x37
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
// 0x38 - 0x3F
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
// 0x40 - 0x47
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
// 0x48 - 0x4F
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
// 0x50 - 0x57
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
// 0x58 - 0x5F
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
//   '    a    b    c    d    e    f    g 
    '`', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
//   h    i    j    k    l    m    n    o
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
//   p    q    r    s    t    u    v    w
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
//   x    y    z    {    |    }    ~
    'X', 'Y', 'Z'
};

WORD fMask[] = {         // offset of bitfield
    0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
    0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000
};

BYTE szRegIMESetting[] = "Control Panel\\Input Method";
BYTE szPara[] = "Parallel Distance";
BYTE szPerp[] = "Perpendicular Distance";
BYTE szParaTol[] = "Parallel Tolerance";
BYTE szPerpTol[] = "Perpendicular Tolerance";
BYTE szRegImeIndex[] = "IME Index";

const NEARCARET ncUIEsc[] = {
   // LogFontX  LogFontY  ParaX   PerpX   ParaY   PerpY
    { 0,        1,        1,      0,      0,      1},       // 0
    { 1,        0,        0,      1,      1,      0},       // 900
    { 0,        0,       -1,      0,      0,      1},       // 1800
    {-1,        0,        0,     -1,     -1,      0}        // 2700
};
// decide another UI offset base on escapement
const NEARCARET ncAltUIEsc[] = {
   // LogFontX  LogFontY  ParaX   PerpX   ParaY   PerpY
    { 0,        0,        1,      0,      0,     -1},       // 0
    { 0,        0,        0,     -1,      1,      0},       // 900
    { 0,        0,       -1,      0,      0,     -1},       // 1800
    { 0,        0,        0,      1,     -1,      0}        // 2700
};
// decide input rectangle base on escapement
const POINT ptInputEsc[] = {
    // LogFontWi   LogFontHi
    {1,            1},                                  // 0
    {1,           -1},                                  // 900
    {1,            1},                                  // 1800
    {-1,           1}                                   // 2700
};

// decide another input rectangle base on escapement
const POINT ptAltInputEsc[] = {
    // LogFontWi   LogFontHi
    {1,           -1},                                  // 0
    {-1,          -1},                                  // 900
    {1,           -1},                                  // 1800
    {1,            1}                                   // 2700
};


BYTE VirtKey48Map[48] = {
	0x20, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53,
	0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0xba, 0xbb, 0xbc,
	0xbd, 0xbe, 0xbf, 0xc0, 0xdb, 0xdc, 0xdd, 0xde
};
