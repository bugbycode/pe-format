#pragma once
#include <Windows.h>
#include<tchar.h>
#include<stdio.h>
#include<winnt.h>

/*
PE 文件解析类
*/
class PEFile {
public:

	IMAGE_DOS_HEADER dosHeader;//DOS头
	
	BYTE* signature;//PE标记

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
		//关闭文件
		if (!(this->fileHandle == NULL || this->fileHandle == INVALID_HANDLE_VALUE)) {
			CloseHandle(this->fileHandle);
			this->fileHandle = NULL;
		}
		//释放内存空间
		if (this->signatureData != NULL) {
			delete[] this->signatureData;
			this->signatureData = NULL;
		}
	}
private:

	LPCWSTR filePath;//PE文件路径

	HANDLE fileHandle;//已打开的文件句柄

	BYTE* signatureData;//PE标记与DOS头之间的空闲数据

	/*
	打开PE文件
	*/
	HANDLE OpenFile();

	/*
	获取DOS头信息
	*/
	IMAGE_DOS_HEADER GetDosHeader();

	BYTE* GetSignature();
};