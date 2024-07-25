// plxdrv.h
//
// Generated by DriverWizard version DriverStudio 2.7.0 (Build 554)
// Requires Compuware's DriverWorks classes
//

#ifndef __PLXDRV_H__
#define __PLXDRV_H__

#define EOL "\n"

// Global driver trace object
extern	KDebugOnlyTrace	t;

// The Driver Class
class PlxDriver : public KDriver
{
	SAFE_DESTRUCTORS
public:
	virtual NTSTATUS DriverEntry(PUNICODE_STRING RegistryPath);
	virtual NTSTATUS AddDevice(PDEVICE_OBJECT Pdo);

protected:
	ULONG	m_Unit;
};

#endif // __PLXDRV_H__
