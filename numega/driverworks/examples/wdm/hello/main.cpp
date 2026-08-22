#define VDW_MAIN

#define DRIVER_FUNCTION_PNP
#define DRIVER_FUNCTION_POWER
#define DRIVER_FUNCTION_UNLOAD
#define DRIVER_FUNCTION_ADD_DEVICE
 
#include <vdw.h>

KDebugOnlyTrace T("MyDriver");

class MyDevice : public KPnpDevice
{
    SAFE_DESTRUCTORS

public:
    MyDevice(PDEVICE_OBJECT pPhyDev) :
        KPnpDevice(pPhyDev, L"MyDriver", FILE_DEVICE_UNKNOWN)
    {
        m_pMyDev.Initialize(this, pPhyDev);
        SetLowerDevice(&m_pMyDev);
        SetPnpPolicy();
    }

    NTSTATUS DefaultPnp(KIrp I) {
        I.ForceReuseOfCurrentStackLocationInCalldown();

        return m_pMyDev.PnpCall(this, I);
    }

    NTSTATUS DefaultPower(KIrp I) {
        I.IndicatePowerIrpProcessed();
        I.CopyParametersDown();

        return m_pMyDev.PnpPowerCall(this, I);
    }

private:
    KPnpLowerDevice m_pMyDev;
};
 
class MyDriver : public KDriver
{
    SAFE_DESTRUCTORS

public:
    NTSTATUS DriverEntry(PUNICODE_STRING pMyRegistry);

    NTSTATUS AddDevice(PDEVICE_OBJECT pPhyDev) {
        new (NonPagedPool)MyDevice(pPhyDev);

        return STATUS_SUCCESS;
    }

    void Unload(void) {
        KDriver::Unload();
    }
};
 
DECLARE_DRIVER_CLASS(MyDriver, NULL)
 
NTSTATUS MyDriver::DriverEntry(PUNICODE_STRING pMyRegistry) {
    T << "Hello, world!";

    return STATUS_SUCCESS;
}
 
