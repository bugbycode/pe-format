#include "pefile.h"

IMAGE_FILE_HEADER PEFile::GetFileHeader() {
	IMAGE_FILE_HEADER fileHeader = {};
	BYTE fileHeaderData[20];
	DWORD numberOfBytesRead = 0;//已读取的长度
	BOOL readStatus = ReadFile(this->fileHandle, &fileHeaderData, sizeof(fileHeaderData), &numberOfBytesRead, NULL);
	if (readStatus == NULL) {
		return fileHeader;
	}
	/*
	for (UINT32 index = 0; index < 20; index++) {
		printf("%02x ", fileHeaderData[index]);
		if ((index + 1) % 0x10 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	*/

	BYTE* pHeader = fileHeaderData;
	fileHeader.Machine = *pHeader++;
	fileHeader.Machine = fileHeader.Machine | *pHeader++ << 0x08;

	fileHeader.NumberOfSections = *pHeader++;
	fileHeader.NumberOfSections = fileHeader.NumberOfSections | *pHeader++ << 0x08;

	fileHeader.TimeDateStamp = *pHeader++;
	fileHeader.TimeDateStamp = fileHeader.TimeDateStamp | *pHeader++ << 0x08;
	fileHeader.TimeDateStamp = fileHeader.TimeDateStamp | *pHeader++ << 0x10;
	fileHeader.TimeDateStamp = fileHeader.TimeDateStamp | *pHeader++ << 0x18;

	fileHeader.PointerToSymbolTable = *pHeader++;
	fileHeader.PointerToSymbolTable = fileHeader.PointerToSymbolTable | *pHeader++ << 0x08;
	fileHeader.PointerToSymbolTable = fileHeader.PointerToSymbolTable | *pHeader++ << 0x10;
	fileHeader.PointerToSymbolTable = fileHeader.PointerToSymbolTable | *pHeader++ << 0x18;

	fileHeader.NumberOfSymbols = *pHeader++;
	fileHeader.NumberOfSymbols = fileHeader.NumberOfSymbols | *pHeader++ << 0x08;
	fileHeader.NumberOfSymbols = fileHeader.NumberOfSymbols | *pHeader++ << 0x10;
	fileHeader.NumberOfSymbols = fileHeader.NumberOfSymbols | *pHeader++ << 0x18;
	
	//可选PE头大小
	fileHeader.SizeOfOptionalHeader = *pHeader++;
	fileHeader.SizeOfOptionalHeader = fileHeader.SizeOfOptionalHeader | *pHeader++ << 0x08;
	
	fileHeader.Characteristics = *pHeader++;
	fileHeader.Characteristics = fileHeader.Characteristics | *pHeader++ << 0x08;

	return fileHeader;
}

BYTE* PEFile::GetSignature() {
	static BYTE signature[4];
	DWORD numberOfBytesRead = 0;//已读取的长度
	BOOL readStatus = ReadFile(this->fileHandle, &signature, sizeof(signature), &numberOfBytesRead, NULL);
	if (readStatus == FALSE) {
		return signature;
	}
	/*
	for (UINT32 index = 0; index < 4; index++) {
		if (index != 0 && index % 0x10 == 0) {
			printf("\n");
		}
		printf("%02x ", signature[index]);
	}*/
	return signature;
}

IMAGE_DOS_HEADER PEFile::GetDosHeader() {
	IMAGE_DOS_HEADER dosHeader = {};
	BYTE dos_byte[64];//读取64字节
	DWORD numberOfBytesRead = 0;//已读取的长度
	BOOL readStatus = ReadFile(this->fileHandle, &dos_byte,sizeof(dos_byte),&numberOfBytesRead,NULL);
	if (readStatus == FALSE) {
		return dosHeader;
	}
	UINT32 index = 0;
	/*

	for (index = 0; index < 64;index++) {
		printf("%02x ", dos_byte[index]);
		if ((index + 1) % 0x10 == 0) {
			printf("\n");
		}
		
	}*/

	BYTE* pdos = dos_byte;
	//可执行文件为4d 5a开头 称之为可执行文件标记
	dosHeader.e_magic = *pdos++;
	dosHeader.e_magic = dosHeader.e_magic | *pdos++ << 0x08;
	
	dosHeader.e_cblp = *pdos++;
	dosHeader.e_cblp = dosHeader.e_cblp | *pdos++ << 0x08;

	dosHeader.e_cp = *pdos++;
	dosHeader.e_cp = dosHeader.e_cp | *pdos++ << 0x08;

	dosHeader.e_crlc = *pdos++;
	dosHeader.e_crlc = dosHeader.e_crlc | *pdos++ << 0x08;

	dosHeader.e_cparhdr = *pdos++;
	dosHeader.e_cparhdr = dosHeader.e_cparhdr | *pdos++ << 0x08;

	dosHeader.e_minalloc = *pdos++;
	dosHeader.e_minalloc = dosHeader.e_minalloc | *pdos++ << 0x08;

	dosHeader.e_maxalloc = *pdos++;
	dosHeader.e_maxalloc = dosHeader.e_maxalloc | *pdos++ << 0x08;

	dosHeader.e_ss = *pdos++;
	dosHeader.e_ss = dosHeader.e_ss | *pdos++ << 0x08;

	dosHeader.e_sp = *pdos++;
	dosHeader.e_sp = dosHeader.e_sp | *pdos++ << 0x08;

	dosHeader.e_csum = *pdos++;
	dosHeader.e_csum = dosHeader.e_csum | *pdos++ << 0x08;

	dosHeader.e_ip = *pdos++;
	dosHeader.e_ip = dosHeader.e_ip | *pdos++ << 0x08;

	dosHeader.e_cs = *pdos++;
	dosHeader.e_cs = dosHeader.e_cs | *pdos++ << 0x08;

	dosHeader.e_lfarlc = *pdos++;
	dosHeader.e_lfarlc = dosHeader.e_lfarlc | *pdos++ << 0x08;

	dosHeader.e_ovno = *pdos++;
	dosHeader.e_ovno = dosHeader.e_ovno | *pdos++ << 0x08;

	UINT16 e_res_len = sizeof(dosHeader.e_res) / sizeof(WORD);

	WORD* p_e_res = dosHeader.e_res;

	for (index = 0; index < e_res_len;index++) {
		*p_e_res = *pdos++;
		*p_e_res++ = *p_e_res | *pdos++ << 0x08;
	}

	dosHeader.e_oemid = *pdos++;
	dosHeader.e_oemid = dosHeader.e_oemid | *pdos++ << 0x08;

	dosHeader.e_oeminfo = *pdos++;
	dosHeader.e_oeminfo = dosHeader.e_oeminfo | *pdos++ << 0x08;

	UINT16 e_res2_len = sizeof(dosHeader.e_res2)/sizeof(WORD);
	WORD* p_e_res2 = dosHeader.e_res2;
	for (index = 0; index < e_res2_len; index++) {
		*p_e_res2 = *pdos++;
		*p_e_res2++ = *p_e_res2 | *pdos++ << 0x08;
	}

	dosHeader.e_lfanew = *pdos++;
	dosHeader.e_lfanew = dosHeader.e_lfanew | *pdos++ << 0x08;
	dosHeader.e_lfanew = dosHeader.e_lfanew | *pdos++ << 0x10;
	dosHeader.e_lfanew = dosHeader.e_lfanew | *pdos++ << 0x18;

	//开始读取DOS头与PE标记之前的空闲数据
	numberOfBytesRead = 0;
	long data_len = dosHeader.e_lfanew - 64;
	//申请内存空间
	this->signatureData = new BYTE[data_len];

	readStatus = ReadFile(this->fileHandle, this->signatureData, data_len, &numberOfBytesRead, NULL);
	/*
	if (readStatus == TRUE) {
		for (long i = 0; i < data_len;i++) {
			printf("%02x ", *this->signatureData++);
			if ((i + 1) % 0x10 == 0) {
				printf("\n");
			}
		}
	}
	//重制指针指向开始地址
	this->signatureData -= data_len;
	*/
	return dosHeader;
}

HANDLE PEFile::OpenFile() {
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;//访问权限 读、写
	DWORD dwShareMode = 0;//文件或设备的请求共享模式，可以读取，写入，两者，删除，全部或全部不共享
	//指向SECURITY_ATTRIBUTES 结构的指针，该结构包含两个单独但相关的数据成员：
	//一个可选的安全描述符，以及一个布尔值，该值确定子进程是否可以继承返回的句柄。
	//此参数可以为NULL。
	LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL;

	DWORD dwCreationDisposition = OPEN_ALWAYS; //文件存在则直接打开 否则创建新文件
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	HANDLE hTemplateFile = NULL;

	//创建或打开文件 返回文件句柄
	return CreateFile(this->filePath, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}