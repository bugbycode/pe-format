#include "pefile.h"

BYTE* PEFile::GetSignature() {
	static BYTE signature[4];
	DWORD numberOfBytesRead = 0;//�Ѷ�ȡ�ĳ���
	BOOL readStatus = ReadFile(this->fileHandle, &signature, sizeof(signature), &numberOfBytesRead, NULL);
	if (readStatus == FALSE) {
		return signature;
	}
	return signature;
}

IMAGE_DOS_HEADER PEFile::GetDosHeader() {
	IMAGE_DOS_HEADER dosHeader = {};
	BYTE dos_byte[64];//��ȡ64�ֽ�
	DWORD numberOfBytesRead = 0;//�Ѷ�ȡ�ĳ���
	BOOL readStatus = ReadFile(this->fileHandle, &dos_byte,sizeof(dos_byte),&numberOfBytesRead,NULL);
	if (readStatus == FALSE) {
		return dosHeader;
	}

	UINT32 index = 0;

	for (index = 0; index < 64;index++) {
		if (index != 0 && index % 0x10 == 0) {
			printf("\n");
		}
		else if(index != 0){
			printf(" ");
		}
		printf("%02x", dos_byte[index]);
	}

	BYTE* pdos = dos_byte;
	//��ִ���ļ�Ϊ4d 5a��ͷ ��֮Ϊ��ִ���ļ����
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
	return dosHeader;
}

HANDLE PEFile::OpenFile() {
	DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;//����Ȩ�� ����д
	DWORD dwShareMode = 0;//�ļ����豸��������ģʽ�����Զ�ȡ��д�룬���ߣ�ɾ����ȫ����ȫ��������
	//ָ��SECURITY_ATTRIBUTES �ṹ��ָ�룬�ýṹ����������������ص����ݳ�Ա��
	//һ����ѡ�İ�ȫ���������Լ�һ������ֵ����ֵȷ���ӽ����Ƿ���Լ̳з��صľ����
	//�˲�������ΪNULL��
	LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL;

	DWORD dwCreationDisposition = OPEN_ALWAYS; //�ļ�������ֱ�Ӵ� ���򴴽����ļ�
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	HANDLE hTemplateFile = NULL;

	//��������ļ� �����ļ����
	return CreateFile(this->filePath, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}