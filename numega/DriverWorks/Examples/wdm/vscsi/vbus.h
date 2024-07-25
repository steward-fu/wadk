// vbus.h
//
// Generated by DriverWizard version DriverStudio 2.7.0 (Build 554)
// Requires Compuware's DriverWorks classes
//

#ifndef __VBUS_H__
#define __VBUS_H__

//////////////////////////////////////////////////////////////////////////////
// VBus class 
//		manages a collection of VDisk devices
//
class VBus : public KBus
{
	// Constructors
public:
	SAFE_DESTRUCTORS;
	VBus() {}
	~VBus() {}

	// check if address is already used
	bool AddressUsed(ULONG address);

	// remove child with id
	bool RemoveChild(ULONG address);
};


#endif // __VBUS_H__
