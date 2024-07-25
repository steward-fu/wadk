// Vbus.h
//
// Generated by DriverWizard version DriverStudio 2.7.0 (Build 554)
// Requires Compuware's DriverWorks classes
//

#ifndef __Vbus_h__
#define __Vbus_h__

#define EOL "\n"

// Global driver trace object
extern	KDebugOnlyTrace	t;

class VBusDriver : public KDriver
{
	SAFE_DESTRUCTORS
public:
	virtual NTSTATUS DriverEntry(PUNICODE_STRING RegistryPath);
	virtual NTSTATUS AddDevice(PDEVICE_OBJECT Pdo);

	virtual NTSTATUS DispatchFilter(
		KDevice* pDevice, 
		KIrp I, 
		NTSTATUS (KDevice::*func)(KIrp)
		)
	{
		if ( pDevice->IsValid() )
		{
			return pDevice->DeviceIrpDispatch(I);
		}
		else
		{
			t << "IRP request for removed device " << I;

			return I.Complete(STATUS_NO_SUCH_DEVICE);
		}
	}

	ULONG	m_Unit;
};

#endif			// __Vbus_h__
