// Vdev1394Device.cpp
// Implementation of VDev1394Device device class
//
// Generated by DriverWizard version DriverStudio 2.7.0 (Build 554)
// Requires Compuware's DriverWorks classes
//

#pragma warning(disable:4065) // Allow switch statement with no cases
		  
#include <vdw.h>
#include "..\VDev1394Deviceinterface.h"

#include "VDev1394.h"
#include "Vdev1394Device.h"
#include "..\vdev1394ioctl.h"

GUID VDev1394Device_Guid = VDev1394Device_CLASS_GUID;

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::VDev1394Device
//
//	Routine Description:
//		This is the constructor for the Functional Device Object, or FDO.
//		It is derived from KPnpDevice, which builds in automatic
//	    dispatching of subfunctions of IRP_MJ_POWER and IRP_MJ_PNP to
//		virtual member functions.
//
//	Parameters:
//		Pdo - Physical Device Object - this is a pointer to a system
//			device object that represents the physical device.
//
//		Unit - Unit number. This is a number to append to the device's
//			base device name to form the Logical Device Object's name
//
//	Return Value:
//		None   
//
//	Comments:
//		The object being constructed contains a data member (m_Lower) of type
//		KPnpLowerDevice. By initializing it, the driver binds the FDO to the
//		PDO and creates an interface to the upper edge of the system class driver.
//

VDev1394Device::VDev1394Device(PDEVICE_OBJECT Pdo) :
	KPnpDevice(Pdo, &VDev1394Device_Guid),
	m_hRom(NULL),
	m_nRomLength(0),
	m_RomMdl(NULL),
	m_pRom(NULL)
{
	t << "VDev1394Device::VDev1394Device\n";

	// Check constructor status
    if ( NT_SUCCESS(m_ConstructorStatus) )
	{
		// Initialize the lower device
		m_Lower.Initialize(this, Pdo);

		// Inform the base class of the lower edge device object
		SetLowerDevice(&m_Lower);

		// Initialize the PnP Policy settings to the "standard" policy
		SetPnpPolicy();

		// Initialize the Power Policy settings to the "standard" policy
		SetPowerPolicy();
	}
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::~VDev1394Device
//
//	Routine Description:
//		This is the destructor for the Functional Device Object, or FDO.
//
//	Parameters:
//		None
//
//	Return Value:
//		None
//
//	Comments:
//		None
//
VDev1394Device::~VDev1394Device()
{
	t << "VDev1394Device::~VDev1394Device\n";
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::DefaultPnp
//
//	Routine Description:
//		Default handler for IRP_MJ_PNP
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result returned from lower device
//
//	Comments:
//		This routine just passes the IRP through to the lower device. It is 
//		the default handler for IRP_MJ_PNP. IRPs that correspond to
//		any virtual members of KpnpDevice that handle minor functions of
//		IRP_MJ_PNP and that are not overridden get passed to this routine.
//
NTSTATUS VDev1394Device::DefaultPnp(KIrp I) 
{
	t << "VDev1394Device::DefaultPnp " << I;

	I.ForceReuseOfCurrentStackLocationInCalldown();
	return m_Lower.PnpCall(this, I);
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::DefaultPower
//
//	Routine Description:
//		Default handler for IRP_MJ_POWER 
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result returned from lower device
//
//	Comments:
//		This routine just passes the IRP through to the lower device. It is 
//		the default handler for IRP_MJ_POWER.
//
NTSTATUS VDev1394Device::DefaultPower(KIrp I) 
{
	t << "VDev1394Device::DefaultPower\n";

	I.IndicatePowerIrpProcessed();
	I.CopyParametersDown();
	return m_Lower.PnpPowerCall(this, I);
}

////////////////////////////////////////////////////////////////////////////////
//  VDev1394Device::SystemControl
//
//	Routine Description:
//		Default handler for IRP_MJ_SYSTEM_CONTROL
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result returned from lower device
//
//	Comments:
//		This routine just passes the IRP through to the next device since this driver
//		is not a WMI provider.
//
NTSTATUS VDev1394Device::SystemControl(KIrp I) 
{
	t << "VDev1394Device::SystemControl\n";

	I.ForceReuseOfCurrentStackLocationInCalldown();
	return m_Lower.PnpCall(this, I);
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::OnStartDevice
//
//	Routine Description:
//		Handler for IRP_MJ_PNP subfcn IRP_MN_START_DEVICE
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result code
//
//	Comments:
//		Initialize the 1394 device.
//
NTSTATUS VDev1394Device::OnStartDevice(KIrp I)
{
	// Let's add a new entry to config rom
	static ULONG ConfigRom[] =
	{
		0x00000400,			// length in quads
		0x2DA10012,
		0x01000113,
		0xFFFFFF17,
		0x01000081,			// textual leaf
		0x00000600,			// length in quads
		0x00000080,
		0x09040000,			// language id
		0x0075004E,			// uN
		0x0065006D,			// em
		0x00610067			// ag
	};

	t << "VDev1394Device::OnStartDevice\n";

	NTSTATUS status = STATUS_INSUFFICIENT_RESOURCES;

	I.Information() = 0;

	m_nRomLength = sizeof(ConfigRom);

	m_pRom = new UCHAR[sizeof(ConfigRom)];
	if ( m_pRom )
	{
		RtlCopyMemory(m_pRom, ConfigRom, sizeof(ConfigRom));

		PSET_LOCAL_HOST_PROPS3 pInfo = new SET_LOCAL_HOST_PROPS3;
		if ( pInfo )
		{
			RtlZeroMemory(pInfo, sizeof(SET_LOCAL_HOST_PROPS3));

			PMDL m_RomMdl = IoAllocateMdl(m_pRom, m_nRomLength, FALSE, FALSE, NULL);
			if ( m_RomMdl )
			{
				MmBuildMdlForNonPagedPool(m_RomMdl);

				pInfo->fulFlags = SLHP_FLAG_ADD_CROM_DATA;
				pInfo->nLength = m_nRomLength;
				pInfo->Mdl = m_RomMdl;

				KIrb<REQUEST_SET_LOCAL_HOST_PROPERTIES> Irb(SET_LOCAL_HOST_PROPERTIES_MODIFY_CROM, pInfo);

				status = m_Lower.SubmitIrb(Irb);
				if ( NT_SUCCESS(status) )
				{
					m_hRom = pInfo->hCromData;
					m_Lower.BusReset();

					delete pInfo;
					return status;
				}
				else
				{
					m_hRom = NULL;
				}

				IoFreeMdl(m_RomMdl);
				m_RomMdl = NULL;
			}

			delete pInfo;
		}

		delete[] m_pRom;
		m_pRom = NULL;
		m_nRomLength = 0;
	}

	return status;
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::OnStopDevice
//
//	Routine Description:
//		Handler for IRP_MJ_PNP subfcn IRP_MN_STOP_DEVICE
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result code
//
//	Comments:
//		The system calls this when the device is stopped.
//		The driver should release any hardware resources
//		in this routine.
//
//		The base class passes the irp to the lower device.
//
NTSTATUS VDev1394Device::OnStopDevice(KIrp I)
{
	NTSTATUS status = STATUS_SUCCESS;

	t << "VDev1394Device::OnStopDevice\n";

	if ( m_hRom )
	{
		PSET_LOCAL_HOST_PROPS3 pInfo = new SET_LOCAL_HOST_PROPS3;

		if ( pInfo )
		{
			RtlZeroMemory(pInfo, sizeof(SET_LOCAL_HOST_PROPS3));
			pInfo->fulFlags = SLHP_FLAG_REMOVE_CROM_DATA;
			pInfo->hCromData = m_hRom;
			pInfo->nLength = m_nRomLength;

			KIrb<REQUEST_SET_LOCAL_HOST_PROPERTIES> Irb(SET_LOCAL_HOST_PROPERTIES_MODIFY_CROM, pInfo);

			status = m_Lower.SubmitIrb(Irb);
			if ( NT_SUCCESS(status) )
			{
				m_hRom = NULL;
				status = m_Lower.BusReset();
			}

			delete pInfo;
		}
	}

	if ( m_pRom )
	{
		delete[] m_pRom;
		m_pRom = NULL;
		m_nRomLength = 0;
	}

	if ( m_RomMdl )
	{
		IoFreeMdl(m_RomMdl);
		m_RomMdl = NULL;
	}

	return status;
	UNREFERENCED_PARAMETER(I);
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::OnRemoveDevice
//
//	Routine Description:
//		Handler for IRP_MJ_PNP subfcn IRP_MN_REMOVE_DEVICE
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result code
//
//	Comments:
//		The system calls this when the device is removed.
//		Our PnP policy will take care of 
//			(1) giving the IRP to the lower device
//			(2) detaching the PDO
//			(3) deleting the device object
//

NTSTATUS VDev1394Device::OnRemoveDevice(KIrp I)
{
	NTSTATUS status = STATUS_SUCCESS;

	t << "VDev1394Device::OnRemoveDevice\n";

	if ( m_hRom )
	{
		PSET_LOCAL_HOST_PROPS3 pInfo = new SET_LOCAL_HOST_PROPS3;

		if ( pInfo )
		{
			RtlZeroMemory(pInfo, sizeof(SET_LOCAL_HOST_PROPS3));
			pInfo->fulFlags = SLHP_FLAG_REMOVE_CROM_DATA;
			pInfo->hCromData = m_hRom;
			pInfo->nLength = m_nRomLength;

			KIrb<REQUEST_SET_LOCAL_HOST_PROPERTIES> Irb(SET_LOCAL_HOST_PROPERTIES_MODIFY_CROM, pInfo);

			status = m_Lower.SubmitIrb(Irb);
			if ( NT_SUCCESS(status) )
			{
				m_hRom = NULL;
				status = m_Lower.BusReset();
			}

			delete pInfo;
		}
	}

	if ( m_pRom )
	{
		delete[] m_pRom;
		m_pRom = NULL;
		m_nRomLength = 0;
	}

	if ( m_RomMdl )
	{
		IoFreeMdl(m_RomMdl);
		m_RomMdl = NULL;
	}

	return status;
	UNREFERENCED_PARAMETER(I);
}
////////////////////////////////////////////////////////////////////////
//  VDev1394Device::OnDevicePowerUp
//
//	Routine Description:
//		Handler for IRP_MJ_POWER with minor function IRP_MN_SET_POWER
//		for a request to go to power on state from low power state
//
//	Parameters:
//		I - IRP containing POWER request
//
//	Return Value:
//		NTSTATUS - Status code indicating success or failure
//
//	Comments:
//		This routine implements the OnDevicePowerUp function.
//		This function was called by the framework from the completion
//		routine of the IRP_MJ_POWER dispatch handler in KPnpDevice.
//		The bus driver has completed the IRP and this driver can now
//		access the hardware device.  
//		This routine runs at dispatch level.
//	
NTSTATUS VDev1394Device::OnDevicePowerUp(KIrp I)
{
	t << "VDev1394Device::OnDevicePowerUp\n";
	return STATUS_SUCCESS;
	UNREFERENCED_PARAMETER(I);
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::OnDeviceSleep
//
//	Routine Description:
//		Handler for IRP_MJ_POWER with minor function IRP_MN_SET_POWER
//		for a request to go to a low power state from a high power state
//
//	Parameters:
//		I - IRP containing POWER request
//
//	Return Value:
//		NTSTATUS - Status code indicating success or failure
//
//	Comments:
//		This routine implements the OnDeviceSleep function.
//		This function was called by the framework from the IRP_MJ_POWER 
//		dispatch handler in KPnpDevice prior to forwarding to the PDO.
//		The hardware has yet to be powered down and this driver can now
//		access the hardware device.  
//		This routine runs at passive level.
//	
NTSTATUS VDev1394Device::OnDeviceSleep(KIrp I)
{
	t << "VDev1394Device::OnDeviceSleep\n";
	return STATUS_SUCCESS;
	UNREFERENCED_PARAMETER(I);
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::Create
//
//	Routine Description:
//		Handler for IRP_MJ_CREATE
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result code
//
//	Comments:
//
NTSTATUS VDev1394Device::Create(KIrp I)
{
	t << "VDev1394Device::Create\n";

	return I.PnpComplete(this, STATUS_SUCCESS, IO_NO_INCREMENT);
}


////////////////////////////////////////////////////////////////////////
//  VDev1394Device::Close
//
//	Routine Description:
//		Handler for IRP_MJ_CLOSE
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result code
//
//	Comments:
//
NTSTATUS VDev1394Device::Close(KIrp I)
{
	t << "VDev1394Device::Close\n";

	return I.PnpComplete(this, STATUS_SUCCESS, IO_NO_INCREMENT);
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::Cleanup
//
//	Routine Description:
//		Handler for IRP_MJ_CLEANUP	
//
//	Parameters:
//		I - Current IRP
//
//	Return Value:
//		NTSTATUS - Result code
//
//	Comments:
//

NTSTATUS VDev1394Device::CleanUp(KIrp I)
{
	t << "VDev1394Device::CleanUp\n";

	return I.PnpComplete(this, STATUS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::DeviceControl
//
//	Routine Description:
//		Handler for IRP_MJ_DEVICE_CONTROL
//
//	Parameters:
//		I - Current IRP
// 
//	Return Value:
//		None
//
//	Comments:
//		This routine is the first handler for Device Control requests.
//		The KPnpDevice class handles restricting IRP flow
//		if the device is stopping or being removed.
//

NTSTATUS VDev1394Device::DeviceControl(KIrp I) 
{
	NTSTATUS status;

	t << "Entering VDev1394Device::Device Control, " << I << EOL;
	switch (I.IoctlCode())
	{
		case VDEV1394_IOCTL_BUS_RESET:
			status = VDEV1394_IOCTL_BUS_RESET_Handler(I);
			break;

		default:
			// Unrecognized IOCTL request
			status = STATUS_INVALID_PARAMETER;
			break;
	}

	// If the IRP's IOCTL handler deferred processing using some driver
	// specific scheme, the status variable is set to STATUS_PENDING.
	// In this case we simply return that status, and the IRP will be
	// completed later.  Otherwise, complete the IRP using the status
	// returned by the IOCTL handler.
	if (status == STATUS_PENDING)
	{
		return status;
	}
	else
	{
		return I.PnpComplete(this, status);
	}
}

////////////////////////////////////////////////////////////////////////
//  VDev1394Device::VDEV1394_IOCTL_BUS_RESET_Handler
//
//	Routine Description:
//		Handler for IO Control Code VDEV1394_IOCTL_BUS_RESET
//
//	Parameters:
//		I - IRP containing IOCTL request
//
//	Return Value:
//		NTSTATUS - Status code indicating success or failure
//
//	Comments:
//		This routine implements the VDEV1394_IOCTL_BUS_RESET function.
//		This routine runs at passive level.
//

NTSTATUS VDev1394Device::VDEV1394_IOCTL_BUS_RESET_Handler(KIrp I)
{
	NTSTATUS status = STATUS_SUCCESS;

	t << "Entering VDev1394Device::VDEV1394_IOCTL_BUS_RESET_Handler, " << I << EOL;

	I.Information() = 0;

	if ( I.IoctlInputBufferSize() == sizeof(UCHAR) )
	{
		PUCHAR p = (PUCHAR)I.IoctlBuffer();
		status = m_Lower.BusReset((*p) ? true : false);
	}
	else 
	{
		status = STATUS_INVALID_PARAMETER;
	}

	return status;
}



