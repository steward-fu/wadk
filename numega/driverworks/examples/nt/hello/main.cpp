#define VDW_MAIN	

#define DRIVER_FUNCTION_UNLOAD

#include <vdw.h>

KDebugOnlyTrace T("MyDriver");

class MyDriver : public KDriver
{
	SAFE_DESTRUCTORS

public:
	NTSTATUS DriverEntry(PUNICODE_STRING pMyReg);

	void Unload(void) {
        T << "Unloading MyDriver";
    }
};

DECLARE_DRIVER_CLASS(MyDriver, NULL)

NTSTATUS MyDriver::DriverEntry(PUNICODE_STRING pMyReg)
{
    T << "Hello, world!";

    return STATUS_SUCCESS;
}

