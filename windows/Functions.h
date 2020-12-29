//******************************************************************************
//                           Nicomsoft OCR Engine
//                    Copyright (c) 2010-2016 Nicomsoft
//                 Copyright (c) 2010-2016 Michael Kapustin
//                                www.nsocr.com
//******************************************************************************

#ifndef _FunctionsH_
#define _FunctionsH_

#include "../Engine/Types.h" 


typedef int HCFG;
typedef int HOCR;
typedef int HIMG;
typedef int HBLK;
typedef int HSVR;
typedef int HSCAN;

#define NSOCRAPI	extern "C" int __stdcall

/////////////////////////////////////

NSOCRAPI Engine_GetVersion(UNICODECHAR* VerStr);
NSOCRAPI Engine_Initialize();
NSOCRAPI Engine_InitializeAdvanced(HCFG* CfgObj, HOCR* OcrObj, HIMG* ImgObj);
NSOCRAPI Engine_Uninitialize();
NSOCRAPI Engine_SetDataDirectory(UNICODECHAR* DirectoryPath);

NSOCRAPI Cfg_Create(HCFG* CfgObj);
NSOCRAPI Cfg_Destroy(HCFG CfgObj);
NSOCRAPI Cfg_LoadOptions(HCFG CfgObj, const UNICODECHAR* FileName);
NSOCRAPI Cfg_SaveOptions(HCFG CfgObj, const UNICODECHAR* FileName);
NSOCRAPI Cfg_LoadOptionsFromString(HCFG CfgObj, const UNICODECHAR* XMLString);
NSOCRAPI Cfg_SaveOptionsToString(HCFG CfgObj, UNICODECHAR* XMLString, int MaxLen);
NSOCRAPI Cfg_GetOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath, UNICODECHAR* OptionValue, int MaxLen);
NSOCRAPI Cfg_SetOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath, UNICODECHAR* OptionValue);
NSOCRAPI Cfg_DeleteOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath);

NSOCRAPI Ocr_Create(HCFG CfgObj, HOCR* OcrObj);
NSOCRAPI Ocr_Destroy(HOCR OcrObj);
NSOCRAPI Ocr_ProcessPages(HIMG ImgObj, HSVR SvrObj, int PageIndexStart, int PageIndexEnd, int OcrObjCnt, int Flags);

NSOCRAPI Img_Create(HOCR OcrObj, HIMG* ImgObj);
NSOCRAPI Img_Destroy(HIMG ImgObj);
NSOCRAPI Img_LoadFile(HIMG ImgObj, UNICODECHAR* FileName);
NSOCRAPI Img_LoadFromMemory(HIMG ImgObj, unsigned char* Bytes, int DataSize);
NSOCRAPI Img_LoadBmpData(HIMG ImgObj, unsigned char* Bits, int Width, int Height, int Flags, int Stride);
NSOCRAPI Img_GetPageCount(HIMG ImgObj);
NSOCRAPI Img_SetPage(HIMG ImgObj, int PageIndex);
NSOCRAPI Img_GetSize(HIMG ImgObj, int* Width, int* Height);
#ifdef _WIN32
NSOCRAPI Img_DrawToDC(HIMG ImgObj, int HandleDC, int X, int Y, int* Width, int* Height, int Flags);
#endif
NSOCRAPI Img_DeleteAllBlocks(HIMG ImgObj);
NSOCRAPI Img_AddBlock(HIMG ImgObj, int Xpos, int Ypos, int Width, int Height, HBLK* BlkObj);
NSOCRAPI Img_DeleteBlock(HIMG ImgObj, HBLK BlkObj);
NSOCRAPI Img_GetBlockCnt(HIMG ImgObj);
NSOCRAPI Img_GetBlock(HIMG ImgObj, int BlockIndex, HBLK* BlkObj);
NSOCRAPI Img_GetImgText(HIMG ImgObj, UNICODECHAR* TextStr, int MaxLen, int Flags);
NSOCRAPI Img_GetBmpData(HIMG ImgObj, unsigned char* Bits, int* Width, int* Height, int Flags);
NSOCRAPI Img_OCR(HIMG ImgObj, int FirstStep, int LastStep, int Flags);
NSOCRAPI Img_SaveBlocks(HIMG ImgObj, UNICODECHAR* FileName);
NSOCRAPI Img_LoadBlocks(HIMG ImgObj, UNICODECHAR* FileName);
NSOCRAPI Img_GetSkewAngle(HIMG ImgObj);
NSOCRAPI Img_GetPixLineCnt(HIMG ImgObj);
NSOCRAPI Img_GetPixLine(HIMG ImgObj, int LineInd, int* X1pos, int* Y1pos, int* X2pos, int* Y2pos, int* Width);
NSOCRAPI Img_GetScaleFactor(HIMG ImgObj);
NSOCRAPI Img_CalcPointPosition(HIMG ImgObj, int* Xpos, int* Ypos, int Mode);
NSOCRAPI Img_CopyCurrentPage(HIMG ImgObjSrc, HIMG ImgObjDst, int Flags);
NSOCRAPI Img_GetProperty(HIMG ImgObj, int PropertyID);
NSOCRAPI Img_Unload(HIMG ImgObj);
NSOCRAPI Img_SaveToFile(HIMG ImgObj, UNICODECHAR* FileName, int Format, int Flags);
NSOCRAPI Img_SaveToMemory(HIMG ImgObj, char* Buffer, int BufferSize, int Format, int Flags);

NSOCRAPI Blk_GetType(HBLK BlkObj);
NSOCRAPI Blk_SetType(HBLK BlkObj, int BlockType);
NSOCRAPI Blk_GetRect(HBLK BlkObj, int* Xpos, int* Ypos, int* Width, int* Height);
NSOCRAPI Blk_GetText(HBLK BlkObj, UNICODECHAR* TextStr, int MaxLen, int Flags);
NSOCRAPI Blk_GetLineCnt(HBLK BlkObj);
NSOCRAPI Blk_GetLineText(HBLK BlkObj, int LineIndex, UNICODECHAR* TextStr, int MaxLen);
NSOCRAPI Blk_GetWordCnt(HBLK BlkObj, int LineIndex);
NSOCRAPI Blk_GetWordText(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* TextStr, int MaxLen);
NSOCRAPI Blk_SetWordText(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* TextStr);
NSOCRAPI Blk_GetCharCnt(HBLK BlkObj, int LineIndex, int WordIndex);
NSOCRAPI Blk_GetCharRect(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int* Xpos, int* Ypos, int* Width, int* Height);
NSOCRAPI Blk_GetCharText(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int ResultIndex, UNICODECHAR* TextStr, int MaxLen);
NSOCRAPI Blk_GetCharQual(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int ResultIndex);
NSOCRAPI Blk_GetTextRect(HBLK BlkObj, int LineIndex, int WordIndex, int* Xpos, int* Ypos, int* Width, int* Height);
NSOCRAPI Blk_Inversion(HBLK BlkObj, int Inversion);
NSOCRAPI Blk_Rotation(HBLK BlkObj, int Rotation);
NSOCRAPI Blk_Mirror(HBLK BlkObj, int Mirror);
NSOCRAPI Blk_IsWordInDictionary(HBLK BlkObj, int LineIndex, int WordIndex);
NSOCRAPI Blk_SetRect(HBLK BlkObj, int Xpos, int Ypos, int Width, int Height);
NSOCRAPI Blk_GetWordQual(HBLK BlkObj, int LineIndex, int WordIndex);
NSOCRAPI Blk_GetWordFontColor(HBLK BlkObj, int LineIndex, int WordIndex);
NSOCRAPI Blk_GetWordFontSize(HBLK BlkObj, int LineIndex, int WordIndex);
NSOCRAPI Blk_GetWordFontStyle(HBLK BlkObj, int LineIndex, int WordIndex);
NSOCRAPI Blk_GetBackgroundColor(HBLK BlkObj);
NSOCRAPI Blk_SetWordRegEx(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* RegEx, int Flags);
NSOCRAPI Blk_GetBarcodeCnt(HBLK BlkObj);
NSOCRAPI Blk_GetBarcodeText(HBLK BlkObj, int BarcodeInd, UNICODECHAR* TextStr, int MaxLen);
NSOCRAPI Blk_GetBarcodeRect(HBLK BlkObj, int BarcodeInd, int* Xpos, int* Ypos, int* Width, int* Height);
NSOCRAPI Blk_GetBarcodeType(HBLK BlkObj, int BarcodeInd);

NSOCRAPI Svr_Create(HCFG CfgObj, int Format, HSVR* SvrObj);
NSOCRAPI Svr_Destroy(HSVR SvrObj);
NSOCRAPI Svr_NewDocument(HSVR SvrObj);
NSOCRAPI Svr_AddPage(HSVR SvrObj, HIMG ImgObj, int Flags);
NSOCRAPI Svr_SaveToFile(HSVR SvrObj, UNICODECHAR* FileName);
NSOCRAPI Svr_SaveToMemory(HSVR SvrObj, char* Buffer, int BufferSize);
NSOCRAPI Svr_GetText(HSVR SvrObj, int PageIndex, UNICODECHAR* TextStr, int MaxLen);
NSOCRAPI Svr_SetDocumentInfo(HSVR SvrObj, int InfoID, UNICODECHAR* InfoStr);


#ifdef _WIN32
NSOCRAPI Scan_Create(HCFG CfgObj, HSCAN* ScanObj);
NSOCRAPI Scan_Enumerate(HSCAN ScanObj, UNICODECHAR* ScannerNames, int MaxLen, int Flags);
NSOCRAPI Scan_ScanToImg(HSCAN ScanObj, HIMG ImgObj, int ScannerIndex, int Flags);
NSOCRAPI Scan_ScanToFile(HSCAN ScanObj, UNICODECHAR* FileName, int ScannerIndex, int Flags);
NSOCRAPI Scan_Destroy(HSCAN ScanObj);
#endif

/////////////////////////////////////

#endif //_FunctionsH_
