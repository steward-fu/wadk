// Simple1394.h
//
// Generated by DriverWizard version DriverStudio 2.5.0 (Build 44)
// Requires Compuware's DriverWorks classes
//

#ifndef __Simple1394_h__
#define __Simple1394_h__

#define EOL "\n"

// Global driver trace object
extern KDebugOnlyTrace t;

class Simple1394 : public KDriver
{
	SAFE_DESTRUCTORS
public:
	virtual NTSTATUS DriverEntry(PUNICODE_STRING RegistryPath);
	virtual NTSTATUS AddDevice(PDEVICE_OBJECT Pdo);


	int	m_Unit;

};

#endif			// __Simple1394_h__
