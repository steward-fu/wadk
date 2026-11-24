#include <wdm.h>
  
NTSTATUS DriverEntry(PDRIVER_OBJECT pMyDriver, PUNICODE_STRING pMyRegistry)
{
    DbgPrint("Hello, world!\n");

    return -1;
}
