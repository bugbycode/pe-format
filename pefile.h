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
		}
	}
private:

	LPCWSTR filePath;//PE文件路径

	HANDLE fileHandle;//已打开的文件句柄

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