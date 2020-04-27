// gainCmd.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "gainCmd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "d:\gt-gain-control\siusbxp.h"

// Единственный объект приложения

CWinApp theApp;

using namespace std;

static unsigned char auchCRCHi[] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40
};

// Low - Order Byte Table
/* Table of CRC values for low–order byte */

static char auchCRCLo[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
	0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
	0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
	0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
	0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
	0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
	0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
	0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
	0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
	0x40
};


unsigned short CRC16(unsigned char * puchMsg, unsigned short usDataLen) /* The function returns the CRC as a unsigned short type */
{
	unsigned char uchCRCHi = 0xFF; /* high byte of CRC initialized */
	unsigned char uchCRCLo = 0xFF; /* low byte of CRC initialized */
	unsigned uIndex; /* will index into CRC lookup table */
	while (usDataLen--) /* pass through message buffer */
	{
		uIndex = uchCRCLo ^ *puchMsg++; /* calculate the CRC */
		uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
		uchCRCHi = auchCRCLo[uIndex];
	}
	return (uchCRCHi << 8 | uchCRCLo);
}

//1000: Перегрузка(номер бита - номер канала)
//0 - Нет
//1 - Перегрузка
//4001 : Вход
//0 - зарядовый,
//1 - IEPE
//4002 : Коэфф.усиления
//0 - 0.1; 1
//1 - 0.2; 2
//2 - 0.5; 5
//3 - 1; 10
//4 - 2; 20
//5 - 5; 50
//6 - 10; 100
//4003: ФНЧ
//0 - 10 кГц
//1 - 20 кГц
//2 - 50 кГц
//3 - 100 кГц

//Установка параметров процедура в файле InfPanel.pas:

//procedure TFInfPnl.SetPar;

//const
//iin = 1;
//iku = 3;
//ifn = 5;

//att = 10;


static unsigned char rdRegs = 0x03; //Чтение регистров
static unsigned char wrRegs = 0x10; //Запись в регистры


static unsigned short regAl = 1000;	//16-бит
static unsigned short regCh = 2000;	//16-бит
static unsigned short regIn = 4001; //16-бит
static unsigned short regKu = 4002; //16-бит
static unsigned short regFn = 4003; //16-бит

static unsigned short regUf = 2001; //16-бит * 16
static unsigned short regUl = 2002; //16-бит * 8
static unsigned short regSN = 2003; //16-бит * 4
static unsigned short regIP = 4001; //16-бит x 2

byte high(unsigned short number) {	return number / 256; }
byte low(unsigned short number) {	return number % 256; }


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	if (argc < 5) return 1; // недостаточно параметров

	bool silence   = _wtoi(argv[1]) ? true : false;
	byte channelID = _wtoi(argv[2]);
	byte gainMode  = _wtoi(argv[3]);
	byte gainKu    = _wtoi(argv[4]);
	byte gainF     = _wtoi(argv[5]);

	int nRetCode = 0;
	
	unsigned char Buffer[1024];

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// инициализировать MFC, а также печать и сообщения об ошибках про сбое
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: измените код ошибки соответственно своим потребностям
			_tprintf(_T("Критическая ошибка: сбой при инициализации MFC\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: Вставьте сюда код для приложения.
			byte __devID = 0;
			HANDLE __handle;

			DWORD dwNumDevices = 0;
			SI_DEVICE_STRING devStr;

			SI_STATUS status = SI_GetNumDevices(&dwNumDevices);
			if (!silence) cout << "Devices: " << dwNumDevices << endl;

			if (dwNumDevices != 1) {
				return 2; // неверное количество устройтсв
			}

			status = SI_GetProductString(__devID, &devStr, SI_RETURN_SERIAL_NUMBER);
			if (SI_SUCCESS == status) { if (!silence) cout << "Serial Number: " << devStr << endl; }
			else { if (!silence) cout << "Error code: " << status << endl; }

			status = SI_GetProductString(__devID, &devStr, SI_RETURN_DESCRIPTION);

			if (SI_SUCCESS == status) { if (!silence)cout << "Description: " << devStr << endl; }
			else { if (!silence) cout << "Error code: " << status << endl; }

			status = SI_GetProductString(__devID, &devStr, SI_RETURN_LINK_NAME);
			if (SI_SUCCESS == status) { if (!silence) cout << "Link name: " << devStr << endl; }
			else { if (!silence) cout << "Error code: " << status << endl; }

			status = SI_GetProductString(__devID, &devStr, SI_RETURN_VID);
			if (SI_SUCCESS == status) { if (!silence) cout << "VID: " << devStr << endl; }
			else { if (!silence) cout << "Error code: " << status << endl; }

			status = SI_GetProductString(__devID, &devStr, SI_RETURN_PID);
			if (SI_SUCCESS == status) { if (!silence) cout << "PID: " << devStr << endl; }
			else { if (!silence) cout << "Error code: " << status << endl; }

			status = SI_Open(__devID, &__handle);
			if (SI_SUCCESS == status) { if (!silence) cout << "Port open. Ok" << endl; }
			else { if (!silence) cout << "Error code (port open): " << status << endl; }

			status = SI_SetBaudRate(__handle, 115200);
			if (SI_SUCCESS == status) { if (!silence) cout << "Set BaundRate. Ok" << endl; }
			else { if (!silence) cout << "Error code (Set BaundRate): " << status << endl; }

			status = SI_SetLineControl(__handle, 0x800);  //1 стопбит, паритет нет, 8 бит
			if (SI_SUCCESS == status) { if (!silence) cout << "Set line control. Ok" << endl; }
			else { if (!silence) cout << "Error code (Set line control): " << status << endl; }
		
			status = SI_SetTimeouts(2500, 2500);
			if (SI_SUCCESS == status) { if (!silence) cout << "Set timeouts. Ok" << endl; }
			else { if (!silence) cout << "Error code (Set timeouts): " << status << endl; }

			unsigned short __crc;
			unsigned short __count = 0;

			DWORD dwBytesSucceed = 0;


			if (!silence) cout << "Looking for hardware...." << endl;
			
			// проверяем доступность канала
			__count = 0;
			Buffer[__count++] = channelID;
			Buffer[__count++] = rdRegs;
			Buffer[__count++] = high(regAl);
			Buffer[__count++] = low(regAl);
			Buffer[__count++] = 0x00;
			Buffer[__count++] = 0x01;

			__crc = CRC16(Buffer, __count);
			Buffer[__count++] = low(__crc);
			Buffer[__count++] = high(__crc);

			status = SI_FlushBuffers(__handle, 1, 1);
			status = SI_Write(__handle, &Buffer, __count, &dwBytesSucceed);
			status = SI_Read(__handle, &Buffer, 20, &dwBytesSucceed);
			if (status != SI_SUCCESS) {
				if (!silence) wcout << "Error channel: " << channelID << endl;
				return 3; // ошибка канала
			}
			
			
			if (!silence) cout << "Setup mode...." << endl;

			// настраиваем режим работы
			__count = 0;
			Buffer[__count++] = channelID;
			Buffer[__count++] = wrRegs;
			Buffer[__count++] = high(regIn);
			Buffer[__count++] = low(regIn);
			Buffer[__count++] = 0x00;
			Buffer[__count++] = 0x01;
			Buffer[__count++] = 0x02;
			Buffer[__count++] = 0x00;
			Buffer[__count++] = gainMode;

			__crc = CRC16(Buffer, __count);
			Buffer[__count++] = low(__crc);
			Buffer[__count++] = high(__crc);

			status = SI_FlushBuffers(__handle, 1, 1);
			status = SI_Write(__handle, &Buffer, __count, &dwBytesSucceed);
			status = SI_Read(__handle, &Buffer, 20, &dwBytesSucceed);
			if (status != SI_SUCCESS) {
				if (!silence) wcout << "Error channel: " << channelID << endl;
				return 4; // нет ответа после записи в регистр
			}
			
			if (!silence) cout << "Setup Ku...." << endl;

			// настраиваем режим работы
			__count = 0;
			Buffer[__count++] = channelID;
			Buffer[__count++] = wrRegs;
			Buffer[__count++] = high(regKu);
			Buffer[__count++] = low(regKu);
			Buffer[__count++] = 0x00;
			Buffer[__count++] = 0x01;
			Buffer[__count++] = 0x02;
			Buffer[__count++] = 0x00;
			Buffer[__count++] = gainKu;

			__crc = CRC16(Buffer, __count);
			Buffer[__count++] = low(__crc);
			Buffer[__count++] = high(__crc);

			status = SI_FlushBuffers(__handle, 1, 1);
			status = SI_Write(__handle, &Buffer, __count, &dwBytesSucceed);
			status = SI_Read(__handle, &Buffer, 20, &dwBytesSucceed);
			if (status != SI_SUCCESS) {
				if (!silence) wcout << "Error channel (Ku register): " << channelID << endl;
				return 5; // нет ответа после записи в регистр
			}

			if (!silence) cout << "Setup Fn...." << endl;


			// настраиваем режим работы
			__count = 0;
			Buffer[__count++] = channelID;
			Buffer[__count++] = wrRegs;
			Buffer[__count++] = high(regFn);
			Buffer[__count++] = low(regFn);
			Buffer[__count++] = 0x00;
			Buffer[__count++] = 0x01;
			Buffer[__count++] = 0x02;
			Buffer[__count++] = 0x00;
			Buffer[__count++] = gainF;

			__crc = CRC16(Buffer, __count);
			Buffer[__count++] = low(__crc);
			Buffer[__count++] = high(__crc);

			status = SI_FlushBuffers(__handle, 1, 1);
			status = SI_Write(__handle, &Buffer, __count, &dwBytesSucceed);
			status = SI_Read(__handle, &Buffer, 20, &dwBytesSucceed);
			if (status != SI_SUCCESS) {
				if (!silence) wcout << "Error channel (Filter register): " << channelID << endl;
				return 6; // нет ответа после записи в регистр
			}

		}
	}
	else
	{
		// TODO: Измените код ошибки соответственно своим потребностям
		_tprintf(_T("Критическая ошибка: неудачное завершение GetModuleHandle\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
