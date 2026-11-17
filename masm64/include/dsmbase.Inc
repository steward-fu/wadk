;Основные понятия базы данных.
;1. База данных - хранилище директорий и файлов с произвольным содержанием.
;Теоретически размер базы данных может изменяться от 104 байт (пустая база) до 2^64 байт.
;2. Индекс - номер файлового смещения в базе данных. Используется в качестве относительного указателя на 
;директории, файлы и строки внутри базы данных. Исчисление индексов начинается с еденицы, а нулевой индекс 
;отмечает отсутствие директории, файла или строки с именем.
;3. Директория - папка базы данных. Содержит массив номеров индексов других директорий, а также файлов
;базы данных.
;4. Файл базы данных - бинарные данные произвольного содержания.

;Основные структуры базы данных
;1. Структура хранящая файловое смещение для определенного объекта.
OBJ_INDEX struc
	Index		ULONG64 ?	;Номер индекса
	BaseOffset	ULONG64 ?	;Файловый оффсет на определенный объект (директорию, файл)
	NameInd		ULONG64 ?	;Индекс строки содержащей имя объекта
	HostInd		ULONG64 ?	;Номер индекса "директории владельца",
							;при удалении "директории владельца", её собственные
							;дочернии директории и файлы тоже удаляются
	FileSize	ULONG64 ?	;размер директории или файла
OBJ_INDEX ends
LPOBJ_INDEX TYPEDEF PTR OBJ_INDEX
;2. Структура хранящая файловое смещение на строку оканчивающуюся нулём.
STR_INDEX struc
	Index		ULONG64 ?	;Номер индекса
	BaseOffset	ULONG64 ?	;Файловый оффсет для базы данных на строку
	UseCount	ULONG64 ?	;Количество объектов использующих эту строку как имя
STR_INDEX ends
LPSTR_INDEX TYPEDEF PTR STR_INDEX
;3. Заголовок файла базы данных с индексом корневой директории.
DSM_VER_BASE equ -1
BHEAD struc
	Signature		CHAR "DSMBASE",0	;Сигнатура файла базы
	RootIndex		ULONG64 ?			;Индекс корневой директории
	IndStrCnt		ULONG64 ?			;Количество индексов строк с именами директорий и файлов
	IndDirCnt		ULONG64 ?			;Количество индексов директорий
	IndFileCnt		ULONG64 ?			;Количество индексов файлов
	ErasedCnt		ULONG64 ?			;Ранее удаленные индексы
										;т.е. это индексы которые снова могут быть использованны
	MaxIndex		ULONG64 ?			;Номер самого большого использованного индекса
	;Начиная с 0.4 версии библиотеки dsmbase
	VersionID		SQWORD DSM_VER_BASE	;ID версии формата базы данных
	IndStrRes		ULONG64 ?			;Количество зарезервированных индексов строк
	IndDirRes		ULONG64 ?			;Количество зарезервированных индексов директорий
	IndFileRes		ULONG64 ?			;Количество зарезервированных индексов файлов
	ErasedRes		ULONG64 ?			;Количество QWORD`ов зарезервированное для номеров удаляемых индексов
	BDirRes			ULONG64 ?			;Количество QWORD`ов зарезервированное для новых директорий
BHEAD ends
PBHEAD TYPEDEF PTR BHEAD
BASE_HEADER struc
    Signature  CHAR "DSMBASE",0
    RootIndex  ULONG64 ?
    IndStrCnt  ULONG64 ?
    IndDirCnt  ULONG64 ?
    IndFileCnt ULONG64 ?
    ErasedCnt  ULONG64 ?
    MaxIndex   ULONG64 ?
BASE_HEADER ends
LPBASE_HEADER TYPEDEF PTR BASE_HEADER
;Сразу после заголовка распологается массив из IndStrCnt структур STR_INDEX,
;далее идет массив индексов директорий OBJ_INDEX, 
;после массив индексов файлов OBJ_INDEX,
;и в конце массив 64-битных чисел ранее использованных номеров индексов
;Всё остальное будет приходиться на бинарные данные
;Обобщенная структура индекса на случай директории, файла или строки
INDEX struc
	Index		ULONG64 ?
	BaseOffset	ULONG64 ?
	union
		UseCount	ULONG64 ?
		struc
			NameInd		ULONG64 ?
			HostInd		ULONG64 ?
			FileSize	ULONG64 ?
		ends
	ends
INDEX ends
LPINDEX TYPEDEF PTR INDEX
;Хэндл базы данных
dsmbase struc
	hFile			HANDLE ?	;хэндл файла
	hMap			HANDLE ?	;хэндл мапирования 
	lpBase			LPBASE_HEADER ?	;указатель на мапированную базу данных
	BaseSize		ULONG64 ?		;текущий размер базы данных
	FileSize		ULONG64 ?		;текущий размер маппированного файла
	flProtect		DWORD ?			;зарезервированно для перемапирования
	dwDesiredAccess	DWORD ?			;зарезервированно для перемапирования
dsmbase ends
HDBASE TYPEDEF PTR dsmbase
;Функции выполняют следующие операции
;hBase - везде хэндл базы данных
; 1. Создание новой или открытие существующей базы данных, обёртка вокруг CreateFileA
;в rax возвращает хэндл базы данных
CreateDataBase PROTO lpBaseName:LPSTR,dwDesiredAccess:DWORD,dwShareMode:DWORD,\
	lpSecurityAttributes:LPSECURITY_ATTRIBUTES,dwCreationDisposition:DWORD,\
	dwFlagsAndAttributes:DWORD,hTemplateFile:HANDLE
; 2. Создание именной строки
;AsciiStr - указатель на строку
;UseCount - это обычно должно равняться нулю, записывается в поле STR_INDEX.UseCount
;AsciiStrLen - длина строки AsciiStr
;в rax возвращает номер индекса именной строки
AddString PROTO hBase:HDBASE,AsciiStr:LPSTR,UseCount:ULONG64
AddStringEx PROTO hBase:HDBASE,AsciiStr:LPSTR,UseCount:ULONG64,AsciiStrLen:ULONG64
; 3. Удаление именной строки
;sIndex - номер индекса строки
DeleteStringEx PROTO hBase:HDBASE,sIndex:ULONG64,UseCount:ULONG64
DeleteString PROTO hBase:HDBASE,sIndex:ULONG64
; 4. Добавление файла
;BinData - указатель на бинарные данные
;SizeOfData - размер в байтах бинарных данных
;HostInd - индекс "директории владельца"
;FileName - указатель на имя файла
;NameInd - номер индекса именной строки
;в rax возвращает номер индекса файла или 0 если не получилось создать
NewFile PROTO hBase:HDBASE,BinData:LPVOID,SizeOfData:ULONG64,HostInd:ULONG64,FileName:LPSTR
AddFile PROTO hBase:HDBASE,BinData:LPVOID,SizeOfData:ULONG64,HostInd:ULONG64,NameInd:ULONG64
; 5. Удаление файла
;fIndex - номер индекса файла, который нужно удалить
;HostIndex - номер индекса "директории владельца", если равно нулю то файл обязательно удаляется
;в противном случае этот номер должен быть равен полю OBJ_INDEX.HostInd
DelFile PROTO hBase:HDBASE,fIndex:ULONG64,HostIndex:ULONG64
; 6. Создание директории
;всё также как и для NewFile/AddFile
;BinData здесь это указатель на список номеров индексов, обычно равняется нулю
;SizeOfData должно быть кратно 8 и обычно равно нулю, т.е. в начале создается пустая директория
;если HostInd равно нулю, то номер индекса создаваемой директории заносится в поле BASE_HEADER.RootIndex
;в rax возвращает номер индекса созданной диретории или 0 если не получилось создать
NewDirectory PROTO hBase:HDBASE,BinData:PULONG64,SizeOfData:ULONG64,HostInd:ULONG64,DirName:LPSTR
AddDirectory PROTO hBase:HDBASE,BinData:PULONG64,SizeOfData:ULONG64,HostInd:ULONG64,NameInd:ULONG64
; 7. Удаление директории
;drIndex - номер индекса директории, которую нужно удалить
;HostIndex - номер индекса "директории владельца", если равно нулю то директория обязательно удаляется
;в противном случае этот номер должен быть равен полю OBJ_INDEX.HostInd
DelDirectory PROTO hBase:HDBASE,drIndex:ULONG64,HostIndex:ULONG64
; 8. Получение типа индекса
curr_id=0
enf    NULL_TYPE,    STR_TYPE, DIR_TYPE,FILE_TYPE
enf OBJ_INCREASE,OBJ_DECREASE, IMM_SIZE
;lpIndex - указатель на структуру INDEX
;перед вызовом в структуре INDEX нужно указать номер индекса INDEX.Index остальное функция сама всё заполнит
;в rax возвращает тип индекса STR_TYPE для строки, DIR_TYPE для директории, 
;FILE_TYPE для файла и 0 если если нету запрошенного индекса
GetIndexType PROTO hBase:HDBASE,lpIndex:LPINDEX
PPINDEX	TYPEDEF PTR LPINDEX
GetIndexTypeEx PROTO hBase:HDBASE,lpIndex:LPINDEX,ImmIndex:PPINDEX
; 9. Получение индекса строки
;lpIndex - указатель на структуру STR_INDEX
;__buffer - если поле STR_INDEX.Index не равно нулю то это указатель на буфер для приёма строки иначе это
; указатель на строку по которой будет искаться индекс
;buf_size - размер буффера для приёма строки, если поле STR_INDEX.Index равно нулю то никак не используется
;в rax возвращает размер строки
GetString PROTO hBase:HDBASE,lpIndex:LPSTR_INDEX,__buffer:LPSTR,buf_size:ULONG64
;10. Установка строки
;__Index - номер индекса строки
;__string - указатель на строку
;в eax возвращает 1 если всё прошло успешно и 0 в противном случае
SetString PROTO hBase:HDBASE,__Index:ULONG64,__string:LPSTR
;11. Установка нового размера объекта, директории или файла
;__Index - индекс директории или файла
;__Type - указавает тип объекта DIR_TYPE или FILE_TYPE плюс способ изменения размера 
;OBJ_INCREASE увеличение на __Size байт
;OBJ_DECREASE уменьшение на __Size байт
;IMM_SIZE непосредственно новый размер __Size байт
;NewSize - указатель на переменную для сохранения нового размера
;в rax файловый указатель на объект, если к нему прибавить dsmbase.lpBase то это будет просто указатель на
;тело объекта
SetObjectSize PROTO hBase:HDBASE,__Index:ULONG64,__Type:DWORD,__Size:ULONG64,NewSize:PULONG64
;11. Получение индекса из имени/пути объекта
;RootDir - номер индекса базовой директории, может равняться нулю, тогда строка пути должна 
;будет начинаться с имени корневой директории
;lpPath - указатель на строку пути, символы / и \ разделяют имена директорий и файлов
;каких-то ограничений на использование определённых символов пока не предусмотренно, но это может измениться
PathToIndex PROTO hBase:HDBASE,RootDir:ULONG64,lpPath:LPSTR
PathToIndexEx PROTO hBase:HDBASE,RootDir:ULONG64,lpPath:LPSTR,PathSize:ULONG64
;12. Получение имени/пути из индекса объекта
;__Index - номер индекса директории или файла
;lpPath - указатель на буфер для сохранения пути
;PathSize - размер буфера
;в eax 1 если все получилось, 0 если индекса не существует и -1 (0FFFFFFFFh) если буфер слишком мал
IndexToPath PROTO hBase:HDBASE,__Index:ULONG64,lpPath:LPSTR,PathSize:ULONG64
;13. Закрытие базы данных
CloseDataBase PROTO hBase:HDBASE
;14. Увеличение базы данных
;Для оптимизации лучше увеличивать размер базы данных за ранее перед добавлением
;большого количества файлов и директорий, особенно если есть возможность примерной оценки их общего размера
IncreaseDataBase PROTO hBase:HDBASE,NumOfBytes:ULONG64
;15. Увеличение базы данных
DecreaseDataBase PROTO hBase:HDBASE,NumOfBytes:ULONG64
;16. Получение/установка порядка объекта в своей "директории владельце"
GetOrder PROTO hBase:HDBASE,objIndex:ULONG64,objOrder:PULONG64
SetOrder PROTO hBase:HDBASE,objIndex:ULONG64,NewOrder:ULONG64
;17. Переименование объекта.
RenameObject PROTO hBase:HDBASE,objIndex:ULONG64,NewHost:ULONG64,NameInd:ULONG64
;18. Добавление индекса в директорию
AddRef PROTO hBase:HDBASE,drIndex:ULONG64,objIndex:ULONG64,objOrder:ULONG64
;19. Удаление индекса из директории
DeleteRef PROTO hBase:HDBASE,drIndex:ULONG64,objIndex:ULONG64,objOrder:ULONG64
;20. Сортировка индексов строк для соблюдения алфавитного порядка
SortStringIndices PROTO hBase:HDBASE
;16. Получение/установка порядка ссылки на объект в определённой директории
GetRefOrder PROTO hBase:HDBASE,drIndex:ULONG64,objIndex:ULONG64,objOrder:PULONG64
SetRefOrder PROTO hBase:HDBASE,drIndex:ULONG64,objOrder:ULONG64,NewOrder:ULONG64
;получение номера индекса по его порядку
GetRefByOrder PROTO hBase:HDBASE,drIndex:ULONG64,objOrder:ULONG64
GetFileIndexByNameInd PROTO hBase:HDBASE,lpIndex:LPINDEX,ImmIndex:PPINDEX
GetDirIndex PROTO hBase:HDBASE,lpIndex:LPINDEX,ImmIndex:PPINDEX
GetDirIndexAndUp PROTO hBase:HDBASE,lpIndex:LPINDEX,ImmIndex:PPINDEX
SetStringEx PROTO hBase:HDBASE,__Index:ULONG64,__string:LPSTR,AsciiStrLen:ULONG64
IncreaseStrRes PROTO hBase:HDBASE,StrRes:ULONG64
IncreaseDirRes PROTO hBase:HDBASE,DirRes:ULONG64
IncreaseFileRes PROTO hBase:HDBASE,FileRes:ULONG64
IncreaseErasedRes PROTO hBase:HDBASE,ErdRes:ULONG64
IncreaseBDirRes PROTO hBase:HDBASE,BDirRes:ULONG64
GetFilePtr PROTO hBase:HDBASE,FileName:LPSTR,Host:ULONG64,FileSize:PULONG64
;Закрытие базы данных, с определением формата
curr_id=0
enf B_COMPACT,B_LEGACY
CloseDataBaseEx PROTO hdBase:HDBASE,dwFlags:DWORD