//A C++ wrapper class for NSOCR.dll functions

//******************************************************************************
//                        Nicomsoft OCR DLL interface
//                    Copyright (c) 2010-2016 Nicomsoft
//                 Copyright (c) 2010-2016 Michael Kapustin
//                           www.nsocr.com
//******************************************************************************

#ifdef _WIN32


//#include "Forcelib.h" //to avoid linker problem with LIBCMTD.lib

#include <Windows.h>

#else

#include <dlfcn.h>
#include "wchar.h"
#define   GetProcAddress dlsym 
#define   FreeLibrary    dlclose

#endif

#include "NSOCR.h"

#pragma warning(disable : 4996) //remove "deprecated" warning

TNSOCR::TNSOCR(wchar_t* DllFileName)
{
	loaded = false;
	TryLoadDLL(DllFileName);
}

TNSOCR::~TNSOCR()
{
  if (loaded) FreeLibrary(hlib);
}

bool TNSOCR::IsDllLoaded()
{
	return loaded;
}

bool TNSOCR::TryLoadDLL(wchar_t* DllFileName)
{
	if (loaded) return true;
	wchar_t fn[300];

	if (!DllFileName || !DllFileName[0]) wcscpy(fn, L"NSOCR.dll"); //old style: wcscpy(fn, L"NSOCR.dll");
	else wcscpy(fn, DllFileName); //old style: wcscpy(fn, DllFileName);
	
#ifndef _WIN32	
	// In Linux UTF-8 is used
	char        dll_name[768];
	wchar_t*    cpos = fn;
	
    wcsrtombs(dll_name, (const wchar_t **)&cpos, sizeof(dll_name), NULL);		
	hlib = dlopen(dll_name,  RTLD_NOW | RTLD_GLOBAL);
#else
	hlib = LoadLibraryW(fn);	
#endif	
		
	loaded = hlib != 0;
	if (!loaded) 
	{
		//int err = GetLastError();
		//_itow(err, fn, 10);
		//MessageBox(0, fn, NULL, 0);
		return false;
	}
////
	p_Engine_Initialize = (t_Engine_Initialize) GetProcAddress(hlib, "Engine_Initialize");
	p_Engine_InitializeAdvanced = (t_Engine_InitializeAdvanced) GetProcAddress(hlib, "Engine_InitializeAdvanced");
	p_Engine_Uninitialize = (t_Engine_Uninitialize) GetProcAddress(hlib, "Engine_Uninitialize");
	p_Engine_SetDataDirectory = (t_Engine_SetDataDirectory) GetProcAddress(hlib, "Engine_SetDataDirectory");
	p_Engine_GetVersion = (t_Engine_GetVersion) GetProcAddress(hlib, "Engine_GetVersion");
	p_Engine_SetLicenseKey = (t_Engine_SetLicenseKey) GetProcAddress(hlib, "Engine_SetLicenseKey");

	p_Cfg_Create = (t_Cfg_Create) GetProcAddress(hlib, "Cfg_Create");
	p_Cfg_Destroy = (t_Cfg_Destroy) GetProcAddress(hlib, "Cfg_Destroy");
	p_Cfg_LoadOptions = (t_Cfg_LoadOptions) GetProcAddress(hlib, "Cfg_LoadOptions");
	p_Cfg_SaveOptions = (t_Cfg_SaveOptions) GetProcAddress(hlib, "Cfg_SaveOptions");
	p_Cfg_LoadOptionsFromString = (t_Cfg_LoadOptionsFromString) GetProcAddress(hlib, "Cfg_LoadOptionsFromString");
	p_Cfg_SaveOptionsToString = (t_Cfg_SaveOptionsToString) GetProcAddress(hlib, "Cfg_SaveOptionsToString");
	p_Cfg_GetOption = (t_Cfg_GetOption) GetProcAddress(hlib, "Cfg_GetOption");
	p_Cfg_SetOption = (t_Cfg_SetOption) GetProcAddress(hlib, "Cfg_SetOption");
	p_Cfg_DeleteOption = (t_Cfg_DeleteOption) GetProcAddress(hlib, "Cfg_DeleteOption");

	p_Ocr_Create = (t_Ocr_Create) GetProcAddress(hlib, "Ocr_Create");
	p_Ocr_Destroy = (t_Ocr_Destroy) GetProcAddress(hlib, "Ocr_Destroy");
	p_Ocr_ProcessPages = (t_Ocr_ProcessPages) GetProcAddress(hlib, "Ocr_ProcessPages");

	p_Img_Create = (t_Img_Create) GetProcAddress(hlib, "Img_Create");
	p_Img_Destroy = (t_Img_Destroy) GetProcAddress(hlib, "Img_Destroy");
	p_Img_LoadFile = (t_Img_LoadFile) GetProcAddress(hlib, "Img_LoadFile");
	p_Img_LoadFromMemory = (t_Img_LoadFromMemory) GetProcAddress(hlib, "Img_LoadFromMemory");
	p_Img_LoadBmpData = (t_Img_LoadBmpData) GetProcAddress(hlib, "Img_LoadBmpData");
	p_Img_Unload = (t_Img_Unload) GetProcAddress(hlib, "Img_Unload");
	p_Img_GetPageCount = (t_Img_GetPageCount) GetProcAddress(hlib, "Img_GetPageCount");
	p_Img_SetPage = (t_Img_SetPage) GetProcAddress(hlib, "Img_SetPage");
	p_Img_GetSize = (t_Img_GetSize) GetProcAddress(hlib, "Img_GetSize");
	p_Img_DrawToDC = (t_Img_DrawToDC) GetProcAddress(hlib, "Img_DrawToDC");
	p_Img_GetBmpData = (t_Img_GetBmpData) GetProcAddress(hlib, "Img_GetBmpData");
	p_Img_DeleteAllBlocks = (t_Img_DeleteAllBlocks) GetProcAddress(hlib, "Img_DeleteAllBlocks");
	p_Img_AddBlock = (t_Img_AddBlock) GetProcAddress(hlib, "Img_AddBlock");
	p_Img_DeleteBlock = (t_Img_DeleteBlock) GetProcAddress(hlib, "Img_DeleteBlock");
	p_Img_GetBlockCnt = (t_Img_GetBlockCnt) GetProcAddress(hlib, "Img_GetBlockCnt");
	p_Img_GetBlock = (t_Img_GetBlock) GetProcAddress(hlib, "Img_GetBlock");
	p_Img_GetImgText = (t_Img_GetImgText) GetProcAddress(hlib, "Img_GetImgText");
	p_Img_OCR = (t_Img_OCR) GetProcAddress(hlib, "Img_OCR");
	p_Img_LoadBlocks = (t_Img_LoadFile) GetProcAddress(hlib, "Img_LoadBlocks");
	p_Img_SaveBlocks = (t_Img_LoadFile) GetProcAddress(hlib, "Img_SaveBlocks");
	p_Img_GetSkewAngle = (t_Img_GetSkewAngle) GetProcAddress(hlib, "Img_GetSkewAngle");
	p_Img_GetPixLineCnt = (t_Img_GetPixLineCnt) GetProcAddress(hlib, "Img_GetPixLineCnt");
	p_Img_GetPixLine = (t_Img_GetPixLine) GetProcAddress(hlib, "Img_GetPixLine");
	p_Img_GetScaleFactor = (t_Img_GetScaleFactor) GetProcAddress(hlib, "Img_GetScaleFactor");
	p_Img_CalcPointPosition = (t_Img_CalcPointPosition) GetProcAddress(hlib, "Img_CalcPointPosition");
	p_Img_CopyCurrentPage = (t_Img_CopyCurrentPage) GetProcAddress(hlib, "Img_CopyCurrentPage");
	p_Img_GetProperty = (t_Img_GetProperty) GetProcAddress(hlib, "Img_GetProperty");
	p_Img_SaveToFile = (t_Img_SaveToFile) GetProcAddress(hlib, "Img_SaveToFile");
	p_Img_SaveToMemory = (t_Img_SaveToMemory) GetProcAddress(hlib, "Img_SaveToMemory");

	p_Blk_GetType = (t_Blk_GetType) GetProcAddress(hlib, "Blk_GetType");
	p_Blk_SetType = (t_Blk_SetType) GetProcAddress(hlib, "Blk_SetType");
	p_Blk_GetRect = (t_Blk_GetRect) GetProcAddress(hlib, "Blk_GetRect");
	p_Blk_GetText = (t_Blk_GetText) GetProcAddress(hlib, "Blk_GetText");
	p_Blk_GetLineCnt = (t_Blk_GetLineCnt) GetProcAddress(hlib, "Blk_GetLineCnt");
	p_Blk_GetLineText = (t_Blk_GetLineText) GetProcAddress(hlib, "Blk_GetLineText");
	p_Blk_GetWordCnt = (t_Blk_GetWordCnt) GetProcAddress(hlib, "Blk_GetWordCnt");
	p_Blk_GetWordText = (t_Blk_GetWordText) GetProcAddress(hlib, "Blk_GetWordText");
	p_Blk_SetWordText = (t_Blk_SetWordText) GetProcAddress(hlib, "Blk_SetWordText");
	p_Blk_GetCharCnt = (t_Blk_GetCharCnt) GetProcAddress(hlib, "Blk_GetCharCnt");
	p_Blk_GetCharRect = (t_Blk_GetCharRect) GetProcAddress(hlib, "Blk_GetCharRect");
	p_Blk_GetCharText = (t_Blk_GetCharText) GetProcAddress(hlib, "Blk_GetCharText");
	p_Blk_GetCharQual = (t_Blk_GetCharQual) GetProcAddress(hlib, "Blk_GetCharQual");
	p_Blk_GetTextRect = (t_Blk_GetTextRect) GetProcAddress(hlib, "Blk_GetTextRect");
	p_Blk_Inversion = (t_Blk_Inversion) GetProcAddress(hlib, "Blk_Inversion");
	p_Blk_Rotation = (t_Blk_Rotation) GetProcAddress(hlib, "Blk_Rotation");
	p_Blk_Mirror = (t_Blk_Mirror) GetProcAddress(hlib, "Blk_Mirror");
	p_Blk_IsWordInDictionary = (t_Blk_IsWordInDictionary) GetProcAddress(hlib, "Blk_IsWordInDictionary");
	p_Blk_SetRect = (t_Blk_SetRect) GetProcAddress(hlib, "Blk_SetRect");
	p_Blk_GetWordQual = (t_Blk_GetWordQual) GetProcAddress(hlib, "Blk_GetWordQual");
	p_Blk_GetWordFontColor = (t_Blk_GetWordFontColor) GetProcAddress(hlib, "Blk_GetWordFontColor");
	p_Blk_GetWordFontSize = (t_Blk_GetWordFontSize) GetProcAddress(hlib, "Blk_GetWordFontSize");
	p_Blk_GetWordFontStyle = (t_Blk_GetWordFontStyle) GetProcAddress(hlib, "Blk_GetWordFontStyle");
	p_Blk_GetBackgroundColor = (t_Blk_GetBackgroundColor) GetProcAddress(hlib, "Blk_GetBackgroundColor");
	p_Blk_SetWordRegEx = (t_Blk_SetWordRegEx) GetProcAddress(hlib, "Blk_SetWordRegEx");
	p_Blk_GetBarcodeCnt = (t_Blk_GetBarcodeCnt) GetProcAddress(hlib, "Blk_GetBarcodeCnt");
	p_Blk_GetBarcodeText = (t_Blk_GetBarcodeText) GetProcAddress(hlib, "Blk_GetBarcodeText");
	p_Blk_GetBarcodeRect = (t_Blk_GetBarcodeRect) GetProcAddress(hlib, "Blk_GetBarcodeRect");
	p_Blk_GetBarcodeType = (t_Blk_GetBarcodeType) GetProcAddress(hlib, "Blk_GetBarcodeType");

	p_Svr_Create = (t_Svr_Create) GetProcAddress(hlib, "Svr_Create");
	p_Svr_Destroy = (t_Svr_Destroy) GetProcAddress(hlib, "Svr_Destroy");
	p_Svr_NewDocument = (t_Svr_NewDocument) GetProcAddress(hlib, "Svr_NewDocument");
	p_Svr_AddPage = (t_Svr_AddPage) GetProcAddress(hlib, "Svr_AddPage");
	p_Svr_SaveToFile = (t_Svr_SaveToFile) GetProcAddress(hlib, "Svr_SaveToFile");
	p_Svr_SaveToMemory = (t_Svr_SaveToMemory) GetProcAddress(hlib, "Svr_SaveToMemory");
	p_Svr_GetText = (t_Svr_GetText) GetProcAddress(hlib, "Svr_GetText");
	p_Svr_SetDocumentInfo = (t_Svr_SetDocumentInfo) GetProcAddress(hlib, "Svr_SetDocumentInfo");

	p_Scan_Create = (t_Scan_Create) GetProcAddress(hlib, "Scan_Create");
	p_Scan_Enumerate = (t_Scan_Enumerate) GetProcAddress(hlib, "Scan_Enumerate"); 
	p_Scan_ScanToImg = (t_Scan_ScanToImg) GetProcAddress(hlib, "Scan_ScanToImg"); 
	p_Scan_ScanToFile = (t_Scan_ScanToFile) GetProcAddress(hlib, "Scan_ScanToFile");
	p_Scan_Destroy = (t_Scan_Destroy) GetProcAddress(hlib, "Scan_Destroy");

	return true;
}

//////////////////////////////////////////////////////////////////////////

int TNSOCR::Engine_Initialize()
{
	if (!loaded || !p_Engine_Initialize) return ERROR_DLLNOTLOADED;
	return p_Engine_Initialize();
}

int TNSOCR::Engine_InitializeAdvanced(HCFG* CfgObj, HOCR* OcrObj, HIMG* ImgObj)
{
	if (!loaded || !p_Engine_InitializeAdvanced) return ERROR_DLLNOTLOADED;
	return p_Engine_InitializeAdvanced(CfgObj, OcrObj, ImgObj);
}

int TNSOCR::Engine_Uninitialize()
{
	if (!loaded || !p_Engine_Uninitialize) return ERROR_DLLNOTLOADED;
	return p_Engine_Uninitialize();
}

int TNSOCR::Engine_SetDataDirectory(UNICODECHAR* DirectoryPath)
{
	if (!loaded || !p_Engine_SetDataDirectory) return ERROR_DLLNOTLOADED;
	return p_Engine_SetDataDirectory(DirectoryPath);
}

int TNSOCR::Engine_GetVersion(UNICODECHAR* VerStr)
{
	if (!loaded || !p_Engine_GetVersion) return ERROR_DLLNOTLOADED;
	return p_Engine_GetVersion(VerStr);
}

int TNSOCR::Engine_SetLicenseKey(UNICODECHAR* LicenseKey)
{
	if (!loaded || !p_Engine_SetLicenseKey) return ERROR_DLLNOTLOADED;
	return p_Engine_SetLicenseKey(LicenseKey);
}

//////////////////

int TNSOCR::Cfg_Create(HCFG* CfgObj)
{
	if (!loaded || !p_Cfg_Create) return ERROR_DLLNOTLOADED;
	return p_Cfg_Create(CfgObj);
}

int TNSOCR::Cfg_Destroy(HCFG CfgObj)
{
	if (!loaded || !p_Cfg_Destroy) return ERROR_DLLNOTLOADED;
	return p_Cfg_Destroy(CfgObj);
}

int TNSOCR::Cfg_LoadOptions(HCFG CfgObj, UNICODECHAR* FileName)
{
	if (!loaded || !p_Cfg_LoadOptions) return ERROR_DLLNOTLOADED;
	return p_Cfg_LoadOptions(CfgObj, FileName);
}

int TNSOCR::Cfg_SaveOptions(HCFG CfgObj, UNICODECHAR* FileName)
{
	if (!loaded || !p_Cfg_SaveOptions) return ERROR_DLLNOTLOADED;
	return p_Cfg_SaveOptions(CfgObj, FileName);
}

int TNSOCR::Cfg_LoadOptionsFromString(HCFG CfgObj, UNICODECHAR* XMLString)
{
	if (!loaded || !p_Cfg_LoadOptionsFromString) return ERROR_DLLNOTLOADED;
	return p_Cfg_LoadOptionsFromString(CfgObj, XMLString);
}

int TNSOCR::Cfg_SaveOptionsToString(HCFG CfgObj, UNICODECHAR* XMLString, int MaxLen)
{
	if (!loaded || !p_Cfg_SaveOptionsToString) return ERROR_DLLNOTLOADED;
	return p_Cfg_SaveOptionsToString(CfgObj, XMLString, MaxLen);
}

int TNSOCR::Cfg_GetOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath, UNICODECHAR* OptionValue, int MaxLen)
{
	if (!loaded || !p_Cfg_GetOption) return ERROR_DLLNOTLOADED;
	return p_Cfg_GetOption(CfgObj, BlockType, OptionPath, OptionValue, MaxLen);
}

int TNSOCR::Cfg_SetOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath, UNICODECHAR* OptionValue)
{
	if (!loaded || !p_Cfg_SetOption) return ERROR_DLLNOTLOADED;
	return p_Cfg_SetOption(CfgObj, BlockType, OptionPath, OptionValue);
}

int TNSOCR::Cfg_DeleteOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath)
{
	if (!loaded || !p_Cfg_DeleteOption) return ERROR_DLLNOTLOADED;
	return p_Cfg_DeleteOption(CfgObj, BlockType, OptionPath);
}

/////////////////////

int TNSOCR::Ocr_Create(HCFG CfgObj, HOCR* OcrObj)
{
	if (!loaded || !p_Ocr_Create) return ERROR_DLLNOTLOADED;
	return p_Ocr_Create(CfgObj, OcrObj);
}

int TNSOCR::Ocr_Destroy(HOCR OcrObj)
{
	if (!loaded || !p_Ocr_Destroy) return ERROR_DLLNOTLOADED;
	return p_Ocr_Destroy(OcrObj);
}

int TNSOCR::Ocr_ProcessPages(HIMG ImgObj, HSVR SvrObj, int PageIndexStart, int PageIndexEnd, int OcrObjCnt, int Flags)
{
	if (!loaded || !p_Ocr_ProcessPages) return ERROR_DLLNOTLOADED;
	return p_Ocr_ProcessPages(ImgObj, SvrObj, PageIndexStart, PageIndexEnd, OcrObjCnt, Flags);
}

/////////////////////

int TNSOCR::Img_Create(HOCR OcrObj, HIMG* ImgObj)
{
	if (!loaded || !p_Img_Create) return ERROR_DLLNOTLOADED;
	return p_Img_Create(OcrObj, ImgObj);
}

int TNSOCR::Img_Destroy(HIMG ImgObj)
{
	if (!loaded || !p_Img_Destroy) return ERROR_DLLNOTLOADED;
	return p_Img_Destroy(ImgObj);
}

int TNSOCR::Img_LoadFile(HIMG ImgObj, UNICODECHAR* FileName)
{
	if (!loaded || !p_Img_LoadFile) return ERROR_DLLNOTLOADED;
	return p_Img_LoadFile(ImgObj, FileName);
}

int TNSOCR::Img_LoadFromMemory(HIMG ImgObj, unsigned char* Bytes, int DataSize)
{
	if (!loaded || !p_Img_LoadFromMemory) return ERROR_DLLNOTLOADED;
	return p_Img_LoadFromMemory(ImgObj, Bytes, DataSize);
}

int TNSOCR::Img_LoadBmpData(HIMG ImgObj, unsigned char* Bits, int Width, int Height, int Flags, int Stride)
{
	if (!loaded || !p_Img_LoadBmpData) return ERROR_DLLNOTLOADED;
	return p_Img_LoadBmpData(ImgObj, Bits, Width, Height, Flags, Stride);
}

int TNSOCR::Img_Unload(HIMG ImgObj)
{
	if (!loaded || !p_Img_Unload) return ERROR_DLLNOTLOADED;
	return p_Img_Unload(ImgObj);
}

int TNSOCR::Img_GetPageCount(HIMG ImgObj)
{
	if (!loaded || !p_Img_GetPageCount) return ERROR_DLLNOTLOADED;
	return p_Img_GetPageCount(ImgObj);
}

int TNSOCR::Img_SetPage(HIMG ImgObj, int PageIndex)
{
	if (!loaded || !p_Img_SetPage) return ERROR_DLLNOTLOADED;
	return p_Img_SetPage(ImgObj, PageIndex);
}

int TNSOCR::Img_GetSize(HIMG ImgObj, int* Width, int* Height)
{
	if (!loaded || !p_Img_GetSize) return ERROR_DLLNOTLOADED;
	return p_Img_GetSize(ImgObj, Width, Height);
}

int TNSOCR::Img_DrawToDC(HIMG ImgObj, int HandleDC, int X, int Y, int* Width, int* Height, int Flags)
{
	if (!loaded || !p_Img_DrawToDC) return ERROR_DLLNOTLOADED;
	return p_Img_DrawToDC(ImgObj, HandleDC, X, Y, Width, Height, Flags);
}

int TNSOCR::Img_GetBmpData(HIMG ImgObj, unsigned char* Bits, int* Width, int* Height, int Flags)
{
	if (!loaded || !p_Img_GetBmpData) return ERROR_DLLNOTLOADED;
	return p_Img_GetBmpData(ImgObj, Bits, Width, Height, Flags);
}

int TNSOCR::Img_DeleteAllBlocks(HIMG ImgObj)
{
	if (!loaded || !p_Img_DeleteAllBlocks) return ERROR_DLLNOTLOADED;
	return p_Img_DeleteAllBlocks(ImgObj);
}

int TNSOCR::Img_AddBlock(HIMG ImgObj, int Xpos, int Ypos, int Width, int Height, HBLK* BlkObj)
{
	if (!loaded || !p_Img_AddBlock) return ERROR_DLLNOTLOADED;
	return p_Img_AddBlock(ImgObj, Xpos, Ypos, Width, Height, BlkObj);
}

int TNSOCR::Img_DeleteBlock(HIMG ImgObj, HBLK BlkObj)
{
	if (!loaded || !p_Img_DeleteBlock) return ERROR_DLLNOTLOADED;
	return p_Img_DeleteBlock(ImgObj, BlkObj);
}

int TNSOCR::Img_GetBlockCnt(HIMG ImgObj)
{
	if (!loaded || !p_Img_GetBlockCnt) return ERROR_DLLNOTLOADED;
	return p_Img_GetBlockCnt(ImgObj);
}

int TNSOCR::Img_GetBlock(HIMG ImgObj, int BlockIndex, HBLK* BlkObj)
{
	if (!loaded || !p_Img_GetBlock) return ERROR_DLLNOTLOADED;
	return p_Img_GetBlock(ImgObj, BlockIndex, BlkObj);
}

int TNSOCR::Img_GetImgText(HIMG ImgObj, UNICODECHAR* TextStr, int MaxLen, int Flags)
{
	if (!loaded || !p_Img_GetImgText) return ERROR_DLLNOTLOADED;
	return p_Img_GetImgText(ImgObj, TextStr, MaxLen, Flags);
}

int TNSOCR::Img_OCR(HIMG ImgObj, int FirstStep, int LastStep, int Flags)
{
	if (!loaded || !p_Img_OCR) return ERROR_DLLNOTLOADED;
	return p_Img_OCR(ImgObj, FirstStep, LastStep, Flags);
}

int TNSOCR::Img_LoadBlocks(HIMG ImgObj, UNICODECHAR* FileName)
{
	if (!loaded || !p_Img_LoadBlocks) return ERROR_DLLNOTLOADED;
	return p_Img_LoadBlocks(ImgObj, FileName);
}

int TNSOCR::Img_SaveBlocks(HIMG ImgObj, UNICODECHAR* FileName)
{
	if (!loaded || !p_Img_SaveBlocks) return ERROR_DLLNOTLOADED;
	return p_Img_SaveBlocks(ImgObj, FileName);
}

int TNSOCR::Img_GetSkewAngle(HIMG ImgObj)
{
	if (!loaded || !p_Img_GetSkewAngle) return ERROR_DLLNOTLOADED;
	return p_Img_GetSkewAngle(ImgObj);
}

int TNSOCR::Img_GetPixLineCnt(HIMG ImgObj)
{
	if (!loaded || !p_Img_GetPixLineCnt) return ERROR_DLLNOTLOADED;
	return p_Img_GetPixLineCnt(ImgObj);
}

int TNSOCR::Img_GetPixLine(HIMG ImgObj, int LineInd, int* X1pos, int* Y1pos, int* X2pos, int* Y2pos, int* Width)
{
	if (!loaded || !p_Img_GetPixLine) return ERROR_DLLNOTLOADED;
	return p_Img_GetPixLine(ImgObj, LineInd, X1pos, Y1pos, X2pos, Y2pos, Width);
}

int TNSOCR::Img_GetScaleFactor(HIMG ImgObj)
{
	if (!loaded || !p_Img_GetScaleFactor) return ERROR_DLLNOTLOADED;
	return p_Img_GetScaleFactor(ImgObj);
}

int TNSOCR::Img_CalcPointPosition(HIMG ImgObj, int* Xpos, int* Ypos, int Mode)
{
	if (!loaded || !p_Img_CalcPointPosition) return ERROR_DLLNOTLOADED;
	return p_Img_CalcPointPosition(ImgObj, Xpos, Ypos, Mode);
}

int TNSOCR::Img_CopyCurrentPage(HIMG ImgObjSrc, HIMG ImgObjDst, int Flags)
{
	if (!loaded || !p_Img_CopyCurrentPage) return ERROR_DLLNOTLOADED;
	return p_Img_CopyCurrentPage(ImgObjSrc, ImgObjDst, Flags);
}

int TNSOCR::Img_GetProperty(HIMG ImgObj, int PropertyID)
{
	if (!loaded || !p_Img_GetProperty) return ERROR_DLLNOTLOADED;
	return p_Img_GetProperty(ImgObj, PropertyID);
}

int TNSOCR::Img_SaveToFile(HIMG ImgObj, UNICODECHAR* FileName, int Format, int Flags)
{
	if (!loaded || !p_Img_SaveToFile) return ERROR_DLLNOTLOADED;
	return p_Img_SaveToFile(ImgObj, FileName, Format, Flags);
}

int TNSOCR::Img_SaveToMemory(HIMG ImgObj, char* Buffer, int BufferSize, int Format, int Flags)
{
	if (!loaded || !p_Img_SaveToMemory) return ERROR_DLLNOTLOADED;
	return p_Img_SaveToMemory(ImgObj, Buffer, BufferSize, Format, Flags);
}

////////////////////////

int TNSOCR::Blk_GetType(HBLK BlkObj)
{
	if (!loaded || !p_Blk_GetType) return ERROR_DLLNOTLOADED;
	return p_Blk_GetType(BlkObj);
}

int TNSOCR::Blk_SetType(HBLK BlkObj, int BlockType)
{
	if (!loaded || !p_Blk_SetType) return ERROR_DLLNOTLOADED;
	return p_Blk_SetType(BlkObj, BlockType);
}

int TNSOCR::Blk_GetRect(HBLK BlkObj, int* Xpos, int* Ypos, int* Width, int* Height)
{
	if (!loaded || !p_Blk_GetRect) return ERROR_DLLNOTLOADED;
	return p_Blk_GetRect(BlkObj, Xpos, Ypos, Width, Height);
}

int TNSOCR::Blk_GetText(HBLK BlkObj, UNICODECHAR* TextStr, int MaxLen, int Flags)
{
	if (!loaded || !p_Blk_GetText) return ERROR_DLLNOTLOADED;
	return p_Blk_GetText(BlkObj, TextStr, MaxLen, Flags);
}

int TNSOCR::Blk_GetLineCnt(HBLK BlkObj)
{
	if (!loaded || !p_Blk_GetLineCnt) return ERROR_DLLNOTLOADED;
	return p_Blk_GetLineCnt(BlkObj);
}

int TNSOCR::Blk_GetLineText(HBLK BlkObj, int LineIndex, UNICODECHAR* TextStr, int MaxLen)
{
	if (!loaded || !p_Blk_GetLineText) return ERROR_DLLNOTLOADED;
	return p_Blk_GetLineText(BlkObj, LineIndex, TextStr, MaxLen);
}

int TNSOCR::Blk_GetWordCnt(HBLK BlkObj, int LineIndex)
{
	if (!loaded || !p_Blk_GetWordCnt) return ERROR_DLLNOTLOADED;
	return p_Blk_GetWordCnt(BlkObj, LineIndex);
}

int TNSOCR::Blk_GetWordText(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* TextStr, int MaxLen)
{
	if (!loaded || !p_Blk_GetWordText) return ERROR_DLLNOTLOADED;
	return p_Blk_GetWordText(BlkObj, LineIndex, WordIndex, TextStr, MaxLen);
}

int TNSOCR::Blk_SetWordText(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* TextStr)
{
	if (!loaded || !p_Blk_SetWordText) return ERROR_DLLNOTLOADED;
	return p_Blk_SetWordText(BlkObj, LineIndex, WordIndex, TextStr);
}

int TNSOCR::Blk_GetCharCnt(HBLK BlkObj, int LineIndex, int WordIndex)
{
	if (!loaded || !p_Blk_GetCharCnt) return ERROR_DLLNOTLOADED;
	return p_Blk_GetCharCnt(BlkObj, LineIndex, WordIndex);
}

int TNSOCR::Blk_GetCharRect(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int* Xpos, int* Ypos, int* Width, int* Height)
{
	if (!loaded || !p_Blk_GetCharRect) return ERROR_DLLNOTLOADED;
	return p_Blk_GetCharRect(BlkObj, LineIndex, WordIndex, CharIndex, Xpos, Ypos, Width, Height);
}

int TNSOCR::Blk_GetCharText(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int ResultIndex, UNICODECHAR* TextStr, int MaxLen)
{
	if (!loaded || !p_Blk_GetCharText) return ERROR_DLLNOTLOADED;
	return p_Blk_GetCharText(BlkObj, LineIndex, WordIndex, CharIndex, ResultIndex, TextStr, MaxLen);
}

int TNSOCR::Blk_GetCharQual(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int ResultIndex)
{
	if (!loaded || !p_Blk_GetCharQual) return ERROR_DLLNOTLOADED;
	return p_Blk_GetCharQual(BlkObj, LineIndex, WordIndex, CharIndex, ResultIndex);
}

int TNSOCR::Blk_GetTextRect(HBLK BlkObj, int LineIndex, int WordIndex, int* Xpos, int* Ypos, int* Width, int* Height)
{
	if (!loaded || !p_Blk_GetTextRect) return ERROR_DLLNOTLOADED;
	return p_Blk_GetTextRect(BlkObj, LineIndex, WordIndex, Xpos, Ypos, Width, Height);
}

int TNSOCR::Blk_Inversion(HBLK BlkObj, int Inversion)
{
	if (!loaded || !p_Blk_Inversion) return ERROR_DLLNOTLOADED;
	return p_Blk_Inversion(BlkObj, Inversion);
}

int TNSOCR::Blk_Rotation(HBLK BlkObj, int Rotation)
{
	if (!loaded || !p_Blk_Rotation) return ERROR_DLLNOTLOADED;
	return p_Blk_Rotation(BlkObj, Rotation);
}

int TNSOCR::Blk_Mirror(HBLK BlkObj, int Mirror)
{
	if (!loaded || !p_Blk_Mirror) return ERROR_DLLNOTLOADED;
	return p_Blk_Mirror(BlkObj, Mirror);
}

int TNSOCR::Blk_IsWordInDictionary(HBLK BlkObj, int LineIndex, int WordIndex)
{
	if (!loaded || !p_Blk_IsWordInDictionary) return ERROR_DLLNOTLOADED;
	return p_Blk_IsWordInDictionary(BlkObj, LineIndex, WordIndex);
}

int TNSOCR::Blk_SetRect(HBLK BlkObj, int Xpos, int Ypos, int Width, int Height)
{
	if (!loaded || !p_Blk_SetRect) return ERROR_DLLNOTLOADED;
	return p_Blk_SetRect(BlkObj, Xpos, Ypos, Width, Height);
}

int TNSOCR::Blk_GetWordQual(HBLK BlkObj, int LineIndex, int WordIndex)
{
	if (!loaded || !p_Blk_GetWordQual) return ERROR_DLLNOTLOADED;
	return p_Blk_GetWordQual(BlkObj, LineIndex, WordIndex);
}

int TNSOCR::Blk_GetWordFontColor(HBLK BlkObj, int LineIndex, int WordIndex)
{
	if (!loaded || !p_Blk_GetWordFontColor) return ERROR_DLLNOTLOADED;
	return p_Blk_GetWordFontColor(BlkObj, LineIndex, WordIndex);
}

int TNSOCR::Blk_GetWordFontSize(HBLK BlkObj, int LineIndex, int WordIndex)
{
	if (!loaded || !p_Blk_GetWordFontSize) return ERROR_DLLNOTLOADED;
	return p_Blk_GetWordFontSize(BlkObj, LineIndex, WordIndex);
}

int TNSOCR::Blk_GetWordFontStyle(HBLK BlkObj, int LineIndex, int WordIndex)
{
	if (!loaded || !p_Blk_GetWordFontStyle) return ERROR_DLLNOTLOADED;
	return p_Blk_GetWordFontStyle(BlkObj, LineIndex, WordIndex);
}

int TNSOCR::Blk_GetBackgroundColor(HBLK BlkObj)
{
	if (!loaded || !p_Blk_GetBackgroundColor) return ERROR_DLLNOTLOADED;
	return p_Blk_GetBackgroundColor(BlkObj);
}

int TNSOCR::Blk_SetWordRegEx(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* RegEx, int Flags)
{
	if (!loaded || !p_Blk_SetWordRegEx) return ERROR_DLLNOTLOADED;
	return p_Blk_SetWordRegEx(BlkObj, LineIndex, WordIndex, RegEx, Flags);
}

int TNSOCR::Blk_GetBarcodeCnt(HBLK BlkObj)
{
	if (!loaded || !p_Blk_GetBarcodeCnt) return ERROR_DLLNOTLOADED;
	return p_Blk_GetBarcodeCnt(BlkObj);
}

int TNSOCR::Blk_GetBarcodeText(HBLK BlkObj, int BarcodeInd, UNICODECHAR* TextStr, int MaxLen)
{
	if (!loaded || !p_Blk_GetBarcodeText) return ERROR_DLLNOTLOADED;
	return p_Blk_GetBarcodeText(BlkObj, BarcodeInd, TextStr, MaxLen);
}

int TNSOCR::Blk_GetBarcodeRect(HBLK BlkObj, int BarcodeInd, int* Xpos, int* Ypos, int* Width, int* Height)
{
	if (!loaded || !p_Blk_GetBarcodeRect) return ERROR_DLLNOTLOADED;
	return p_Blk_GetBarcodeRect(BlkObj, BarcodeInd, Xpos, Ypos, Width, Height);
}

int TNSOCR::Blk_GetBarcodeType(HBLK BlkObj, int BarcodeInd)
{
	if (!loaded || !p_Blk_GetBarcodeType) return ERROR_DLLNOTLOADED;
	return p_Blk_GetBarcodeType(BlkObj, BarcodeInd);
}

////////////////////////

int TNSOCR::Svr_Create(HCFG CfgObj, int Format, HSVR* SvrObj)
{
	if (!loaded || !p_Svr_Create) return ERROR_DLLNOTLOADED;
	return p_Svr_Create(CfgObj, Format, SvrObj);
}

int TNSOCR::Svr_Destroy(HSVR SvrObj)
{
	if (!loaded || !p_Svr_Destroy) return ERROR_DLLNOTLOADED;
	return p_Svr_Destroy(SvrObj);
}

int TNSOCR::Svr_NewDocument(HSVR SvrObj)
{
	if (!loaded || !p_Svr_NewDocument) return ERROR_DLLNOTLOADED;
	return p_Svr_NewDocument(SvrObj);
}

int TNSOCR::Svr_AddPage(HSVR SvrObj, HIMG ImgObj, int Flags)
{
	if (!loaded || !p_Svr_AddPage) return ERROR_DLLNOTLOADED;
	return p_Svr_AddPage(SvrObj, ImgObj, Flags);
}

int TNSOCR::Svr_SaveToFile(HSVR SvrObj, UNICODECHAR* FileName)
{
	if (!loaded || !p_Svr_SaveToFile) return ERROR_DLLNOTLOADED;
	return p_Svr_SaveToFile(SvrObj, FileName);
}

int TNSOCR::Svr_SaveToMemory(HSVR SvrObj, char* Buffer, int BufferSize)
{
	if (!loaded || !p_Svr_SaveToMemory) return ERROR_DLLNOTLOADED;
	return p_Svr_SaveToMemory(SvrObj, Buffer, BufferSize);
}

int TNSOCR::Svr_GetText(HSVR SvrObj, int PageIndex, UNICODECHAR* TextStr, int MaxLen)
{
	if (!loaded || !p_Svr_GetText) return ERROR_DLLNOTLOADED;
	return p_Svr_GetText(SvrObj, PageIndex, TextStr, MaxLen);
}

int TNSOCR::Svr_SetDocumentInfo(HSVR SvrObj, int InfoID, UNICODECHAR* InfoStr)
{
	if (!loaded || !p_Svr_SetDocumentInfo) return ERROR_DLLNOTLOADED;
	return p_Svr_SetDocumentInfo(SvrObj, InfoID, InfoStr);
}

////////////////////////

int TNSOCR::Scan_Create(HCFG CfgObj, HSCAN* ScanObj)
{
	if (!loaded || !p_Scan_Create) 
		return ERROR_DLLNOTLOADED;
	return p_Scan_Create(CfgObj, ScanObj);
}

int TNSOCR::Scan_Enumerate(HSCAN ScanObj, UNICODECHAR* ScannerNames, int MaxLen, int Flags)
{
	if (!loaded || !p_Scan_Enumerate) 
		return ERROR_DLLNOTLOADED;
	return p_Scan_Enumerate(ScanObj, ScannerNames, MaxLen, Flags);
}

int TNSOCR::Scan_ScanToImg(HSCAN ScanObj, HIMG ImgObj, int ScannerIndex, int Flags)
{
	if (!loaded || !p_Scan_ScanToImg) 
		return ERROR_DLLNOTLOADED;
	return p_Scan_ScanToImg(ScanObj, ImgObj, ScannerIndex, Flags);
}

int TNSOCR::Scan_ScanToFile(HSCAN ScanObj, UNICODECHAR* FileName, int ScannerIndex, int Flags)
{
	if (!loaded || !p_Scan_ScanToFile) 
		return ERROR_DLLNOTLOADED;
	return p_Scan_ScanToFile(ScanObj, FileName, ScannerIndex, Flags);
}

int TNSOCR::Scan_Destroy(HSCAN ScanObj)
{
	if (!loaded || !p_Scan_Destroy) 
		return ERROR_DLLNOTLOADED;
	return p_Scan_Destroy(ScanObj);
}
