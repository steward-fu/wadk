// Kbfilter.h
//
// Generated by DriverWizard version DriverStudio 2.0.0 (Build 473)
// Requires Compuware's DriverWorks classes
//

#ifndef __Kbfilter_h__
#define __Kbfilter_h__

#define EOL "\n"

// Global driver trace object
extern	KTrace	t;

class Kbfilter : public KDriver
{
	SAFE_DESTRUCTORS
public:
	virtual NTSTATUS DriverEntry(PUNICODE_STRING RegistryPath);
	virtual NTSTATUS AddDevice(PDEVICE_OBJECT Pdo);

			void	 LoadRegistryParameters(KRegistryKey &Params);

	int	m_Unit;

	// The following data members are loaded from the registry during DriverEntry
	ULONG m_bBreakOnEntry;
	
};

#endif			// __Kbfilter_h__
