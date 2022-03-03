#include <Windows.h>
#include <iostream>

int main()
{
	HANDLE device;
	char device_path_process[MAX_PATH + 1] = "COM1";

	COMMTIMEOUTS timeouts, cto;
	timeouts.ReadIntervalTimeout = 1;
	timeouts.ReadTotalTimeoutMultiplier = 2;
	timeouts.ReadTotalTimeoutConstant = 3;
	timeouts.WriteTotalTimeoutMultiplier = 4;
	timeouts.WriteTotalTimeoutConstant = 5;

	device = CreateFileA(device_path_process, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (device == INVALID_HANDLE_VALUE) {
		std::cout << "device INVALID_HANDLE_VALUE, Lasterror" << GetLastError() << std::endl;
		return -1;
	}
	if (!SetCommTimeouts(device, &timeouts)) {
		std::cout <<"SetCommTimeouts failure, Lasterror"<< GetLastError() << std::endl;
		return -1;
	}
	//ZeroMemory(&cto, sizeof(COMMTIMEOUTS));
	if (!GetCommTimeouts(device, &cto)) {
		std::cout << "GetCommTimeouts failure, Lasterror" << GetLastError() << std::endl;
		
		return -1;
	}
	std::cout << "success" << std::endl;
}
