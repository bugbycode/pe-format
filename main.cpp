#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include<tchar.h>
#include<stdio.h>
#include<Windows.h>
#include "PEFile.h"

void PrintDosHeader(PIMAGE_DOS_HEADER pDosHeader);
void PrintSignature(PEFile* pPE);
void PrintFileHeader(PIMAGE_FILE_HEADER pFileHeader);

int main(int argv, char* argc[]) {

	LPCWSTR lpFileName = L"E:/capstone_first.exe";//文件名称或路径 

	PEFile peFile(lpFileName);

	PEFile* pPE = &peFile;
	PIMAGE_DOS_HEADER pDosHeader = &pPE->dosHeader;
	PIMAGE_FILE_HEADER pFileHeader = &pPE->fileHeader;

	PrintDosHeader(pDosHeader);
	PrintSignature(pPE);
	PrintFileHeader(pFileHeader);
	return 0;
}

void PrintFileHeader(PIMAGE_FILE_HEADER pFileHeader) {
	printf("==================FILE HEADER BEGIN==========================\n");
	printf("Machine               = %04x\n", pFileHeader->Machine);
	printf("NumberOfSections      = %02x\n", pFileHeader->NumberOfSections);
	printf("TimeDateStamp         = %04x\n", pFileHeader->TimeDateStamp);
	printf("PointerToSymbolTable  = %04x\n", pFileHeader->PointerToSymbolTable);
	printf("NumberOfSymbols       = %04x\n", pFileHeader->NumberOfSymbols);
	printf("SizeOfOptionalHeader  = %02x\n", pFileHeader->SizeOfOptionalHeader);
	printf("Characteristics       = %02x\n", pFileHeader->Characteristics);
}

void PrintSignature(PEFile* pPE) {
	printf("==================Signature BEGIN==========================\n");
	printf("signature    = %s\n", pPE->signature);
}

void PrintDosHeader(PIMAGE_DOS_HEADER pDosHeader) {
	printf("==================DOS HEADER BEGIN==========================\n");
	printf("e_magic      = %04x\n", pDosHeader->e_magic);
	printf("e_cblp       = %04x\n", pDosHeader->e_cblp);
	printf("e_cp         = %04x\n", pDosHeader->e_cp);
	printf("e_crlc       = %04x\n", pDosHeader->e_crlc);
	printf("e_cparhdr    = %04x\n", pDosHeader->e_cparhdr);
	printf("e_minalloc   = %04x\n", pDosHeader->e_minalloc);
	printf("e_maxalloc   = %04x\n", pDosHeader->e_maxalloc);
	printf("e_ss         = %04x\n", pDosHeader->e_ss);
	printf("e_sp         = %04x\n", pDosHeader->e_sp);
	printf("e_csum       = %04x\n", pDosHeader->e_csum);
	printf("e_ip         = %04x\n", pDosHeader->e_ip);
	printf("e_cs         = %04x\n", pDosHeader->e_cs);
	printf("e_lfarlc     = %04x\n", pDosHeader->e_lfarlc);
	printf("e_ovno       = %04x\n", pDosHeader->e_ovno);
	printf("e_res        = ");
	UINT16 e_res_len = sizeof(pDosHeader->e_res) / sizeof(WORD);
	WORD* p_e_res = pDosHeader->e_res;
	for (int index = 0; index < e_res_len; index++) {
		printf("%04x ", *p_e_res++);
	}
	printf("\n");
	printf("e_oemid      = %04x\n", pDosHeader->e_oemid);
	printf("e_oeminfo    = %04x\n", pDosHeader->e_oeminfo);
	printf("e_res        = ");
	UINT16 e_res2_len = sizeof(pDosHeader->e_res2) / sizeof(WORD);
	WORD* p_e_res2 = pDosHeader->e_res2;
	for (int index = 0; index < e_res2_len; index++) {
		printf("%04x ", *p_e_res2++);
	}
	printf("\n");
	printf("e_lfanew     = %08x\n", pDosHeader->e_lfanew);
}