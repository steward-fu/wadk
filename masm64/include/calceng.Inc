init_calc proto int_length:DWORD,decseparator:DWORD,fract_length:DWORD
off_calc proto hMath:HANDLE
atoiX proto hMath:HANDLE,X:PVOID,Radix:DWORD
atorX proto hMath:HANDLE,X:PVOID,Radix:DWORD
int_add proto hCalc:HANDLE,x1:PVOID,x2:PVOID
int_sub proto hMath:HANDLE,x1:PVOID,x2:PVOID
int_mul proto hCalc:HANDLE,x1:PVOID,x2:PVOID
int_div proto hCalc:HANDLE,x1:PVOID,x2:PVOID,Remn:PVOID
itoaX proto hMath:HANDLE,X:PVOID,Radix:DWORD
fmtitoax proto hMath:HANDLE,X:PVOID,Radix:DWORD,MaxNum:DWORD
fmtrtoa proto hCalc:HANDLE,x1:PVOID,Radix:DWORD,MaxNum:DWORD
rtoaX proto hMath:HANDLE,X:PVOID,Radix:DWORD
uint_add proto hCalc:HANDLE,x1:PVOID,x2:PVOID
uint_sub proto hMath:HANDLE,x1:PVOID,x2:PVOID
uint_mul proto hCalc:HANDLE,x1:PVOID,x2:PVOID
uint_div proto hCalc:HANDLE,x1:PVOID,x2:PVOID,Remn:PVOID
ureal_add proto hCalc:HANDLE,x1:PVOID,x2:PVOID
ureal_sub proto hCalc:HANDLE,x1:PVOID,x2:PVOID
ureal_cmp proto hCalc:HANDLE,x1:PVOID,x2:PVOID
ild proto hCalc:HANDLE,X:PVOID
uild proto hCalc:HANDLE,X:PVOID
ShortDivUx proto hCalc:HANDLE,W:PVOID,V:DWORD
ShortMulUx proto hMath:HANDLE,W:PVOID,V:DWORD
ShortRDiv proto hCalc:HANDLE,W:PVOID,V:DWORD
ShortRMul proto hCalc:HANDLE,W:PVOID,V:DWORD
recalcpi proto hCalc:HANDLE,ppi:PVOID,prec_pi:DWORD
uint_cmp proto hCalc:HANDLE,x1:PVOID,x2:PVOID
Factorial proto hCalc:HANDLE,x1:PVOID,n:DWORD
Unfactorial proto hCalc:HANDLE,x1:PVOID,Remn:PVOID,maxN:DWORD
ShortUintPow proto hCalc:HANDLE,x1:PVOID,n:DWORD
_ultoa2 PROTO Val:DWORD,pBuff:PVOID,Radix:DWORD
buffuild proto hCalc:HANDLE,x1:PVOID,pBuff:PVOID,szBuff:DWORD
rmul proto hCalc:HANDLE,x1:PVOID,x2:PVOID
rdiv proto hCalc:HANDLE,x1:PVOID,x2:PVOID
radd proto hCalc:HANDLE,x1:PVOID,x2:PVOID
rsub proto hCalc:HANDLE,x1:PVOID,x2:PVOID
fmtator proto hCalc:HANDLE,x1:PVOID,Radix:DWORD
rmove proto hCalc:HANDLE,x1:PVOID,x2:PVOID
rsin proto hCalc:HANDLE,sine:PVOID,angle:PVOID,prec_sine:DWORD
rcos proto hCalc:HANDLE,cosine:PVOID,angle:PVOID,prec_cosine:DWORD
ralloc proto hCalc:HANDLE
rfree proto hCalc:HANDLE,xfree:PVOID
rsqrt proto hCalc:HANDLE,x1:PVOID,prec_sqrt:DWORD
st2r proto hCalc:HANDLE,X:PVOID
r2st proto hCalc:HANDLE,x1:PVOID
rshl1 proto hCalc:HANDLE,x1:PVOID
rshr1 proto hCalc:HANDLE,x1:PVOID
rtest proto hCalc:HANDLE,x1:PVOID
rsuidiv_bypow proto hCalc:HANDLE,x1:PVOID,dwx2:DWORD,_pow:DWORD
GetEngineVersion proto

;САМАЯ ОСНОВНАЯ И ЕДИНСТВЕННАЯ СТРУКТУРА СОДЕРЖАЩАЯ ОСНОВНЫЕ ХАРАКТЕРИСТИКИ ЧИСЕЛ
;УКАЗАТЕЛЬ НА ТАКУЮ СТРУКТУРУ НЕОБХОДИМ ПОЧТИ ДЛЯ ВСЕХ ФУНКЦИЙ
calc STRUC
	calc_size dd ?	;размер всей выделеной памяти при инициализации
			  dd ?
	reg0 PVOID ?	; reg_x это комплект готовых для работы предопределённых переменных
	reg1 PVOID ?	; выделены они для облегчения программирования
	reg2 PVOID ?	; при решении не сложных задач этого достаточно, что в большинстве случаев 
	reg3 PVOID ?	; позволяет избежать мароки с дополнительным выделением/освобождением памяти
	reg4 PVOID ?
	reg5 PVOID ?
	reg6 PVOID ?
	reg7 PVOID ?
	msr0 PVOID ?	; msr_x это комплект переменных для хранения промежуточных результатов вычисления
	msr1 PVOID ?
	msr2 PVOID ?
	msr3 PVOID ?
	msr4 PVOID ?
	msr5 PVOID ?
	msr6 PVOID ?
	msr7 PVOID ?
	Reserved1 db ?
	Reserved2 db ?
	ErrFlags db ?
	DecimalSeparator db ?	;код десятичного разделителя, обычно это точка или запятая
	int_length dd ?			;размер целой части числа в машинных словах для x86 это 4 байтовые DWORD`ы
	fract_length dd ?		;размер дробной части
	ascii_buff PVOID ?			;буфер ввода/вывода чисел в виде строк
	size_abuff dd ?			;размер буфера ввода/вывода числовых строк 
calc ENDS
CALC_DESCRIPTOR TYPEDEF calc

DIV_BY_ZERO equ 10b
OVERFLOW_FLAG equ 100b