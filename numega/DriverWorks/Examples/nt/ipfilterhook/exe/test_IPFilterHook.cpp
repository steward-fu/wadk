// Test_IPFilterHook.cpp
//
// Generated by DriverWizard version DriverStudio 2.0.1 (Build 36)
//
// This console application demonstrates how to open a handle
// to a device in your driver, and communicate with the driver
// using Read, Write, and DeviceIoControl calls, as appropriate.
//
// This test program attempts to open the device with link name
// IPFilterHookDevice, which corresponds to Unit 0 of the 
// IPFilterHookDevice device class in the driver.

//
// You can build this application using the command line compiler with
// the following command:
//
//		cl Test_IPFilterHook.cpp
//


#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include <winioctl.h>
#include "..\IPFilterHookioctl.h"


typedef void VOIDFUNC();

// Prototypes
void Usage(void);
void ShowIoctlValues(void);

//	TODO:
//		You can redefine the IOCTL handler prototypes as needed, adding
//		appropriate parameters that can be collected from the command line.
//		To do this you must modify the command line parsing logic.  An
//		example of this is shown in comments throughout the test application.
//
//=== Parameterized IOCTL Example ===
// void Test_IOCTL_PARAMETERIZED(int nVal, ULONG dwVal);
void Test_IPFILTERHOOK_IOCTL_SetHook(void);
void Test_IPFILTERHOOK_IOCTL_ClearHook(void);

void CloseIfOpen(void);
void doRead(int i);
void doWrite(int i);

// Global data


#define N_IOCODES	2

// Names of IOCTL codes
//
char *IOnames[N_IOCODES+1] =
{

//=== Parameterized IOCTL Example ===
//	"IOCTL_PARAMETERIZED",
	"IPFILTERHOOK_IOCTL_SetHook",
	"IPFILTERHOOK_IOCTL_ClearHook",
	""
};

// IOCTL codes
//
int IOcodes[N_IOCODES+1] =
{

//=== Parameterized IOCTL Example ===
//	IOCTL_PARAMETERIZED,
	IPFILTERHOOK_IOCTL_SetHook,
	IPFILTERHOOK_IOCTL_ClearHook,
	0
};


// Handle to device opened in driver.
//
HANDLE	hDevice = INVALID_HANDLE_VALUE;

// Name used to open device
//
char *sLinkName = "\\\\.\\IPFilterHookDevice0";

////////////////////////////////////////////////////////////////////////
// OpenByName
//
//		Open a handle to the requested device
//
HANDLE OpenByName(void)
{
	// Create a handle to the driver
	return CreateFile(sLinkName,
					  GENERIC_READ | GENERIC_WRITE,
					  FILE_SHARE_READ,
					  NULL,
					  OPEN_EXISTING,
					  0,
					  NULL);
}



////////////////////////////////////////////////////////////////////////
// Exit
//
//		Print a message and exit   
//
   void Exit(int res)
{
	printf("Exiting...\n\n");
	CloseIfOpen();
	exit(res);
}


////////////////////////////////////////////////////////////////////////
// Main entry point
//
//
int __cdecl main(int argc, char *argv[])
{
	int		nArgIndex;				// Walk through command line arguments
	int		nArgIncrement = 0;
	int		val;

//=== Parameterized IOCTL Example ===
//	int		nVal;
//	ULONG	dwVal;

	printf("Test application Test_IPFilterHook starting...\n");

	hDevice = OpenByName();
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("ERROR opening device: (%0x) returned from CreateFile\n", GetLastError());
		Exit(1);
	}
	else
	{
		printf("Device found, handle open.\n");
	}

	// Parse the command line

	if (argc < 2) Usage();

	nArgIndex = 1;
	while (nArgIndex < argc)
	{
		// Parse ahead to determine numeric value of argument

		if (nArgIndex+1 >= argc) Usage();
		if (!isdigit(argv[nArgIndex+1][0])) Usage();
		val = atoi(argv[nArgIndex+1]);

		switch (argv[nArgIndex][0])
		{

			case 'r':
			case 'R':
			    printf("Driver does not have a read handler\n");
				nArgIncrement = 2;
				break;

			case 'w':
			case 'W':
			    printf("Driver does not have a write handler\n");
				nArgIncrement = 2;
				break;

			case 'i':
			case 'I':
				if (val >= N_IOCODES)
				{
					printf("IO control code index must be less than %d\n", N_IOCODES);
					ShowIoctlValues();
					Exit(1);
				}
				switch (IOcodes[val])
				{

//=== Parameterized IOCTL Example ===
//					case IOCTL_PARAMETERIZED:
//						if (nArgIndex+3 >= argc) Usage();
//						nVal = atoi(argv[nArgIndex+2]);
//						dwVal = strtoul(argv[nArgIndex+3], NULL, 0);
//						Test_IOCTL_PARAMETERIZED(nVal, dwVal);
//						nArgIncrement = 4;
//						break;

					case IPFILTERHOOK_IOCTL_SetHook:
						Test_IPFILTERHOOK_IOCTL_SetHook();
						nArgIncrement = 2;
						break;

					case IPFILTERHOOK_IOCTL_ClearHook:
						Test_IPFILTERHOOK_IOCTL_ClearHook();
						nArgIncrement = 2;
						break;

					default:
						printf("IO control code not valid\n");
						Exit(1);

				}
				break;

			case '?':
			case 'h':
			default:
				Usage();
		}
		nArgIndex += nArgIncrement;
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////
// CloseIfOpen
//
//		Close the device if we previously opened a handle to it.
//
void CloseIfOpen(void)
{
	if (hDevice != INVALID_HANDLE_VALUE)
	{
		// Close the handle to the driver
		if (!CloseHandle(hDevice))
		{
			printf("ERROR: CloseHandle returns %0x.\n", GetLastError());
		}
		hDevice = INVALID_HANDLE_VALUE;
	}
}


////////////////////////////////////////////////////////////////////////
// doRead
//
//		Read 'n' bytes of data from the device
//
// Note: This simple test app reads data from the device and displays the
//			data as characters.  This behavior can be modified as appropriate
//			for your device.
//
void doRead(int n)
{
	char	*buf;
	ULONG	nRead;
	int		i;
	int		j;

	buf = (char *) malloc(n);
	if (buf == NULL)
	{
		printf("Failed to allocate buffer for read");
		Exit(1);
	}

	// Read data from driver
	printf("Reading from device - ");
	ReadFile(hDevice, buf, n, &nRead, NULL);
	printf("%d bytes read from device (%d requested).\n", nRead, n);

	// Print what was read
	i = 0;
	while(i < n)
	{
		j = min((i+26),n);
		for(; i < j; i++)
		{
			printf("%c, ", buf[i]);
		}
		printf("\n");
	}
	
	free(buf);
}


////////////////////////////////////////////////////////////////////////
// doWrite
//
//		Write 'n' bytes of data to the device
//
// Note: This simple test app writes sequential characters to the
// 			device.  This behavior can be modified as appropriate
//			for your device.
//
void doWrite(int n)
{
	char	*buf;
	ULONG	nWritten;
	int		i;
	int		j;

	buf = (char *) malloc(n);
	if (buf == NULL)
	{
		printf("Failed to allocate buffer for write");
		Exit(1);
	}

	// start with the mod26 letter of the number of bytes to write
	j = (n % 26);
	// load buffer with dummy data (abcdefg...)
	for (i=0; i<n; i++, j=(j + 1)%26)
	{
		buf[i] = 'a' + j;
	}
	
	// Write data to driver
	printf("Writing to device - ");
	WriteFile(hDevice, buf, n, &nWritten, NULL);
	printf("%d bytes written to device (%d attempted).\n", nWritten, n);

	// Print what was written
	i = 0;
	while(i < n)
	{
		j = min((i+26),n);
		for(; i < j; i++)
		{
			printf("%c, ", buf[i]);
		}
		printf("\n");
	}

	free(buf);
}


////////////////////////////////////////////////////////////////////////
// Usage
//
//		Print a usage message describing arguments to this program
//
void Usage(void)
{
	printf("Usage: Test_IPFilterHook [r n] [w n] [i n]\n");
	printf("       r initiates a read of specified number of bytes\n");
	printf("       w initiates a write of specified number of bytes\n");
	printf("       i initiates an IO Control Code message with specified index value\n");
	ShowIoctlValues();
	printf("Example:\n");
	printf("    Test_IPFilterHook r 32 w 32\n");
	printf("        read 32 bytes, then write 32 bytes\n");

	Exit(1);
}



#define	IOCTL_INBUF_SIZE	512
#define	IOCTL_OUTBUF_SIZE	512

//=== Parameterized IOCTL Example ===
//void Test_IOCTL_PARAMETERIZED(int nVal, ULONG dwVal)
//{
//  Function body same as other IOCTL handlers, with command line
//	parameters 'nVal' and 'dwVal' available as input.
//}

////////////////////////////////////////////////////////////////////////
// Test_IPFILTERHOOK_IOCTL_SetHook
//
//		Test one Io Control Code
//
// TODO:
//		Pass appropriate arguments to your device and check
//		the return value
//
void Test_IPFILTERHOOK_IOCTL_SetHook(void)
{
// Note that Input and Output are named from the point of view
// of the DEVICE:
//		bufInput  supplies data to the device
//		bufOutput is written by the device to return data to this application

	CHAR	bufInput[IOCTL_INBUF_SIZE];		// Input to device
	CHAR	bufOutput[IOCTL_OUTBUF_SIZE];	// Output from device
	ULONG	nOutput;						// Count written to bufOutput

	// Call device IO Control interface (IPFILTERHOOK_IOCTL_SetHook) in driver
	printf("Issuing Ioctl to device - ");
	if (!DeviceIoControl(hDevice,
						 IPFILTERHOOK_IOCTL_SetHook,
						 bufInput,
						 IOCTL_INBUF_SIZE,
						 bufOutput,
						 IOCTL_OUTBUF_SIZE,
						 &nOutput,
						 NULL)
	   )
	{
		printf("ERROR: DeviceIoControl returns %0x.", GetLastError());
		Exit(1);
	}
}

////////////////////////////////////////////////////////////////////////
// Test_IPFILTERHOOK_IOCTL_ClearHook
//
//		Test one Io Control Code
//
// TODO:
//		Pass appropriate arguments to your device and check
//		the return value
//
void Test_IPFILTERHOOK_IOCTL_ClearHook(void)
{
// Note that Input and Output are named from the point of view
// of the DEVICE:
//		bufInput  supplies data to the device
//		bufOutput is written by the device to return data to this application

	CHAR	bufInput[IOCTL_INBUF_SIZE];		// Input to device
	CHAR	bufOutput[IOCTL_OUTBUF_SIZE];	// Output from device
	ULONG	nOutput;						// Count written to bufOutput

	// Call device IO Control interface (IPFILTERHOOK_IOCTL_ClearHook) in driver
	printf("Issuing Ioctl to device - ");
	if (!DeviceIoControl(hDevice,
						 IPFILTERHOOK_IOCTL_ClearHook,
						 bufInput,
						 IOCTL_INBUF_SIZE,
						 bufOutput,
						 IOCTL_OUTBUF_SIZE,
						 &nOutput,
						 NULL)
	   )
	{
		printf("ERROR: DeviceIoControl returns %0x.", GetLastError());
		Exit(1);
	}
}


////////////////////////////////////////////////////////////////////////
// ShowIoctlValues
//
//		Print list of IO Control Code values for usage display
//
void ShowIoctlValues(void)
{
	int i;

	for (i=0; i<N_IOCODES; i++)
	{
		if (i==0)
			printf( "         IO control code index\n");
		printf( "           %d is code %s [%x]\n", i, IOnames[i], IOcodes[i]);

//=== Parameterized IOCTL Example ===
//		if (IOcodes[i] == IOCTL_PARAMETERIZED)
//		{
//			printf( "               and has two arguments: <arg1 desc.> <arg1 desc.>\n");
//			printf( "               Example: i %d <IOCTL index> <ex. arg1> <ex. arg2>\n", i);
//		}
	}
}
