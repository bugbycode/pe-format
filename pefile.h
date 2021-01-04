#pragma once
#include <Windows.h>
#include<tchar.h>
#include<stdio.h>
#include<winnt.h>

/*
PE �ļ�������
*/
class PEFile {
public:

	IMAGE_DOS_HEADER dosHeader;//DOSͷ
	
	BYTE* signature;//PE���

	PEFile() {
		this->dosHeader = {};
		this->signature = NULL;
		this->filePath = NULL;
		this->fileHandle = NULL;
		this->signatureData = NULL;
	}

	PEFile(LPCWSTR filePath) {
		this->filePath = filePath;
		this->fileHandle = OpenFile();
		this->dosHeader = GetDosHeader();
		this->signature = GetSignature();
	}

	~PEFile() {
		//�ر��ļ�
		if (!(this->fileHandle == NULL || this->fileHandle == INVALID_HANDLE_VALUE)) {
			CloseHandle(this->fileHandle);
			this->fileHandle = NULL;
		}
		//�ͷ��ڴ�ռ�
		if (this->signatureData != NULL) {
			delete[] this->signatureData;
			this->signatureData = NULL;
		}
	}
private:

	LPCWSTR filePath;//PE�ļ�·��

	HANDLE fileHandle;//�Ѵ򿪵��ļ����

	BYTE* signatureData;//PE�����DOSͷ֮��Ŀ�������

	/*
	��PE�ļ�
	*/
	HANDLE OpenFile();

	/*
	��ȡDOSͷ��Ϣ
	*/
	IMAGE_DOS_HEADER GetDosHeader();

	BYTE* GetSignature();
};