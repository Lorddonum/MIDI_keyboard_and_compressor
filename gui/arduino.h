#include <stdio.h>
#include <stdlib.h>

// Define the five bytes to send ("hello")
char bytes_to_send[5] = {104, 101, 108, 108, 111};

// Declare variables and structures
HANDLE hSerial;
DCB dcbSerialParams = {0};
COMMTIMEOUTS timeouts = {0};

// Open the highest available serial port number
fprintf(stderr, "Opening serial port...");
hSerial = CreateFile("\\\\.\\COM1", GENERIC_READ | GENERIC_WRITE, 0, NULL,
                     OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
if (hSerial == INVALID_HANDLE_VALUE) {
  fprintf(stderr, "Error\n");
  return 1;
} else
  fprintf(stderr, "OK\n");

// Set device parameters (38400 baud, 1 start bit,
// 1 stop bit, no parity)
dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
if (GetCommState(hSerial, &dcbSerialParams) == 0) {
  fprintf(stderr, "Error getting device state\n");
  CloseHandle(hSerial);
  return 1;
}

dcbSerialParams.BaudRate = CBR_38400;
dcbSerialParams.ByteSize = 8;
dcbSerialParams.StopBits = ONESTOPBIT;
dcbSerialParams.Parity = NOPARITY;
if (SetCommState(hSerial, &dcbSerialParams) == 0) {
  fprintf(stderr, "Error setting device parameters\n");
  CloseHandle(hSerial);
  return 1;
}

// Set COM port timeout settings
timeouts.ReadIntervalTimeout = 50;
timeouts.ReadTotalTimeoutConstant = 50;
timeouts.ReadTotalTimeoutMultiplier = 10;
timeouts.WriteTotalTimeoutConstant = 50;
timeouts.WriteTotalTimeoutMultiplier = 10;
if (SetCommTimeouts(hSerial, &timeouts) == 0) {
  fprintf(stderr, "Error setting timeouts\n");
  CloseHandle(hSerial);
  return 1;
}

// Send specified text (remaining command line arguments)
DWORD bytes_written, total_bytes_written = 0;
fprintf(stderr, "Sending bytes...");
if (!WriteFile(hSerial, bytes_to_send, 5, &bytes_written, NULL)) {
  fprintf(stderr, "Error\n");
  CloseHandle(hSerial);
  return 1;
}
fprintf(stderr, "%d bytes written\n", bytes_written);

// Close serial port
fprintf(stderr, "Closing serial port...");
if (CloseHandle(hSerial) == 0) {
  fprintf(stderr, "Error\n");
  return 1;
}
fprintf(stderr, "OK\n");

// exit normally
return 0;
}
