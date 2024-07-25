
//******************************************************************************************
// Application to test the HELLO driver. 
//******************************************************************************************

#include "windows.h"
#include "stdio.h"

HANDLE hTest;

//******************************************************************************************
// Here's our main program.
//******************************************************************************************

int __cdecl main(int argc, char **argv)
{
  //****************************************************************************************
  // Open the access to our device driver. 
  //****************************************************************************************

  HANDLE hTest = CreateFile("\\\\.\\HELLO", GENERIC_READ | GENERIC_WRITE, 0, NULL, 
												OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  //****************************************************************************************
  // Error out if we couldn't open. That may mean that the Driver is not started, 
  // or not properly installed.
  //****************************************************************************************

  if (hTest != INVALID_HANDLE_VALUE)
  {
    printf("CreateFile worked!!!\n");

    //**************************************************************************************
    // Close the Driver Handle.
    //**************************************************************************************

    CloseHandle(hTest);
  }

  //******************************************************************************************
  // Error out if we can't open.
  //******************************************************************************************

  else
  {
    printf("Can't get a handle to the CDriver device\n");
  }

  return 0;
} 

