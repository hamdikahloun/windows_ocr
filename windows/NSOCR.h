//A C++ wrapper class for NSOCR.dll functions

//******************************************************************************
//                        Nicomsoft OCR DLL interface
//                    Copyright (c) 2010-2016 Nicomsoft
//                 Copyright (c) 2010-2016 Michael Kapustin
//                           www.nsocr.com
//******************************************************************************
#ifndef __NSOCRH__
#define __NSOCRH__

#include "ErrorCodes.h" //see for error codes


#ifndef _WIN32
#define __stdcall
#define HMODULE void*
#endif

typedef int HOCR;
typedef int HCFG;
typedef int HIMG;
typedef int HBLK;
typedef int HSVR;
typedef int HSCAN;

typedef wchar_t UNICODECHAR;

//block types
#define BT_DEFAULT		0
#define BT_OCRTEXT		1
#define BT_ICRDIGIT		2
#define BT_CLEAR		3
#define BT_PICTURE		4
#define BT_ZONING		5
#define BT_OCRDIGIT		6
#define BT_BARCODE		7
#define BT_TABLE		8
#define BT_MRZ			9

//for Img_LoadBmpData
#define BMP_24BIT		0x00
#define BMP_8BIT		0x01
#define BMP_1BIT		0x02
#define BMP_32BIT		0x03
#define BMP_BOTTOMTOP	0x100

//for Img_GetImgText, Blk_GetText and Svr_AddPage functions
#define FMT_EDITCOPY	0x00
#define FMT_EXACTCOPY	0x01

//for Img_OCR
#define OCRSTEP_FIRST			0x00 //first step
#define OCRSTEP_PREFILTERS		0x10 //filters before binarizing: scaling, invert, rotate etc
#define OCRSTEP_BINARIZE		0x20 //binarize
#define OCRSTEP_POSTFILTERS		0x50 //bin garbage filter etc
#define OCRSTEP_REMOVELINES		0x60 //find and remove lines
#define OCRSTEP_ZONING			0x70 //analyze page layout
#define OCRSTEP_OCR				0x80 //ocr itself
#define OCRSTEP_LAST			0xFF //last step

//for Img_OCR, "Flags" parameter
#define OCRFLAG_NONE			0x00 //default mode (blocking)
#define OCRFLAG_THREAD			0x01 //non-blocking mode
#define OCRFLAG_GETRESULT		0x02 //get result for non-blocking mode
#define OCRFLAG_GETPROGRESS		0x03 //get progress
#define OCRFLAG_CANCEL			0x04 //cancel ocr

//for Img_DrawToDC and Img_GetBmpData
#define DRAW_NORMAL				0x00
#define DRAW_BINARY				0x01
#define DRAW_GETBPP				0x100

//values for Blk_Inversion function
#define BLK_INVERSE_GET			-1
#define BLK_INVERSE_SET0		0
#define BLK_INVERSE_SET1		1
#define BLK_INVERSE_DETECT		0x100

//for Blk_Rotation function
#define BLK_ROTATE_GET			-1
#define BLK_ROTATE_NONE			0x00
#define BLK_ROTATE_90			0x01
#define BLK_ROTATE_180			0x02
#define BLK_ROTATE_270			0x03
#define BLK_ROTATE_ANGLE        0x100000
#define BLK_ROTATE_DETECT 		0x100

//for Blk_Mirror function
#define BLK_MIRROR_GET			-1
#define BLK_MIRROR_NONE			0x00
#define BLK_MIRROR_H			0x01
#define BLK_MIRROR_V			0x02

//for Svr_Create function
#define SVR_FORMAT_PDF			0x01
#define SVR_FORMAT_RTF			0x02
#define SVR_FORMAT_TXT_ASCII            0x03
#define SVR_FORMAT_TXT_UNICODE          0x04
#define SVR_FORMAT_XML			0x05
#define SVR_FORMAT_PDFA			0x06

//for Scan_Enumerate function
#define SCAN_GETDEFAULTDEVICE           0x01
#define SCAN_SETDEFAULTDEVICE           0x100

//for Scan_ScanToImg and Scan_ScanToFile functions
#define SCAN_NOUI                       0x01
#define SCAN_SOURCEADF                  0x02
#define SCAN_SOURCEAUTO                 0x04
#define SCAN_DONTCLOSEDS				0x08
#define SCAN_FILE_SEPARATE				0x10

//for Blk_GetWordFontStyle function
#define FONT_STYLE_UNDERLINED           0x01
#define FONT_STYLE_STRIKED		0x02
#define FONT_STYLE_BOLD			0x04
#define FONT_STYLE_ITALIC		0x08

//for Img_GetProperty function, PropertyID parameter
#define IMG_PROP_DPIX			0x01	//original DPI
#define IMG_PROP_DPIY			0x02
#define IMG_PROP_BPP			0x03	//color depth
#define IMG_PROP_WIDTH			0x04	//original width
#define IMG_PROP_HEIGHT			0x05	//original height
#define IMG_PROP_INVERTED		0x06	//image inversion flag after OCR_STEP_PREFILTERS step
#define IMG_PROP_SKEW			0x07	//image skew angle after OCR_STEP_PREFILTERS step, multiplied by 1000
#define IMG_PROP_SCALE			0x08	//image scale factor after OCR_STEP_PREFILTERS step, multiplied by 1000
#define IMG_PROP_PAGEINDEX		0x09	//page index for multipage document

//for "Blk_SetWordRegEx" function
#define REGEX_SET				0x00
#define REGEX_CLEAR				0x01
#define REGEX_CLEAR_ALL			0x02
#define REGEX_DISABLE_DICT		0x04
#define REGEX_CHECK				0x08

//for Svr_SetDocumentInfo function
#define INFO_PDF_AUTHOR			0x01
#define INFO_PDF_CREATOR		0x02
#define INFO_PDF_PRODUCER		0x03
#define INFO_PDF_TITLE			0x04
#define INFO_PDF_SUBJECT		0x05
#define INFO_PDF_KEYWORDS		0x06

//for Blk_GetBarcodeType function
#define BARCODE_TYPE_EAN8		0x01
#define BARCODE_TYPE_UPCE		0x02
#define BARCODE_TYPE_ISBN10		0x03
#define BARCODE_TYPE_UPCA		0x04
#define BARCODE_TYPE_EAN13		0x05
#define BARCODE_TYPE_ISBN13		0x06
#define BARCODE_TYPE_ZBAR_I25	0x07
#define BARCODE_TYPE_CODE39		0x08
#define BARCODE_TYPE_QRCODE		0x09
#define BARCODE_TYPE_CODE128	0x0A

//for "BarCode/TypesMask" configuration option
#define BARCODE_TYPE_MASK_EAN8		0x01
#define BARCODE_TYPE_MASK_UPCE		0x02
#define BARCODE_TYPE_MASK_ISBN10	0x04
#define BARCODE_TYPE_MASK_UPCA		0x08
#define BARCODE_TYPE_MASK_EAN13		0x10
#define BARCODE_TYPE_MASK_ISBN13	0x20
#define BARCODE_TYPE_MASK_ZBAR_I25	0x40
#define BARCODE_TYPE_MASK_CODE39	0x80
#define BARCODE_TYPE_MASK_QRCODE	0x100
#define BARCODE_TYPE_MASK_CODE128	0x200

//for Img_SaveToFile function
#define IMG_FORMAT_BMP			0
#define IMG_FORMAT_JPEG			2
#define IMG_FORMAT_PNG			13
#define IMG_FORMAT_TIFF			18
#define IMG_FORMAT_FLAG_BINARIZED	0x100
////////////////////////////////////////////////////////////

typedef int (__stdcall *t_Engine_Initialize)();
typedef int (__stdcall *t_Engine_InitializeAdvanced)(HCFG* CfgObj, HOCR* OcrObj, HIMG* ImgObj);
typedef int (__stdcall *t_Engine_Uninitialize)();
typedef int (__stdcall *t_Engine_SetDataDirectory)(UNICODECHAR* DirectoryPath);
typedef int (__stdcall *t_Engine_GetVersion)(UNICODECHAR* VerStr);
typedef int (__stdcall *t_Engine_SetLicenseKey)(UNICODECHAR* LicenseKey);

typedef int (__stdcall *t_Cfg_Create)(HCFG* CfgObj);
typedef int (__stdcall *t_Cfg_Destroy)(HCFG CfgObj);
typedef int (__stdcall *t_Cfg_LoadOptions)(HCFG CfgObj, UNICODECHAR* FileName);
typedef int (__stdcall *t_Cfg_SaveOptions)(HCFG CfgObj, UNICODECHAR* FileName);
typedef int (__stdcall *t_Cfg_LoadOptionsFromString)(HCFG CfgObj, UNICODECHAR* XMLString);
typedef int (__stdcall *t_Cfg_SaveOptionsToString)(HCFG CfgObj, UNICODECHAR* XMLString, int MaxLen);
typedef int (__stdcall *t_Cfg_GetOption)(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath, UNICODECHAR* OptionValue, int MaxLen);
typedef int (__stdcall *t_Cfg_SetOption)(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath, UNICODECHAR* OptionValue);
typedef int (__stdcall *t_Cfg_DeleteOption)(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath);

typedef int (__stdcall *t_Ocr_Create)(HCFG CfgObj, HOCR* OcrObj);
typedef int (__stdcall *t_Ocr_Destroy)(HOCR OcrObj);
typedef int (__stdcall *t_Ocr_ProcessPages)(HIMG ImgObj, HSVR SvrObj, int PageIndexStart, int PageIndexEnd, int OcrObjCnt, int Flags);

typedef int (__stdcall *t_Img_Create)(HOCR OcrObj, HIMG* ImgObj);
typedef int (__stdcall *t_Img_Destroy)(HIMG ImgObj);
typedef int (__stdcall *t_Img_LoadFile)(HIMG ImgObj, UNICODECHAR* FileName);
typedef int (__stdcall *t_Img_LoadFromMemory)(HIMG ImgObj, unsigned char* Bytes, int DataSize);
typedef int (__stdcall *t_Img_LoadBmpData)(HIMG ImgObj, unsigned char* Bits, int Width, int Height, int Flags, int Stride);
typedef int (__stdcall *t_Img_Unload)(HIMG ImgObj);
typedef int (__stdcall *t_Img_GetPageCount)(HIMG ImgObj);
typedef int (__stdcall *t_Img_SetPage)(HIMG ImgObj, int PageIndex);
typedef int (__stdcall *t_Img_GetSize)(HIMG ImgObj, int* Width, int* Height);
typedef int (__stdcall *t_Img_DrawToDC)(HIMG ImgObj, int HandleDC, int X, int Y, int* Width, int* Height, int Flags);
typedef int (__stdcall *t_Img_GetBmpData)(HIMG ImgObj, unsigned char* Bits, int* Width, int* Height, int Flags);
typedef int (__stdcall *t_Img_DeleteAllBlocks)(HIMG ImgObj);
typedef int (__stdcall *t_Img_AddBlock)(HIMG ImgObj, int Xpos, int Ypos, int Width, int Height, HBLK* BlkObj);
typedef int (__stdcall *t_Img_DeleteBlock)(HIMG ImgObj, HBLK BlkObj);
typedef int (__stdcall *t_Img_GetBlockCnt)(HIMG ImgObj);
typedef int (__stdcall *t_Img_GetBlock)(HIMG ImgObj, int BlockIndex, HBLK* BlkObj);
typedef int (__stdcall *t_Img_GetImgText)(HIMG ImgObj, UNICODECHAR* TextStr, int MaxLen, int Flags);
typedef int (__stdcall *t_Img_OCR)(HIMG ImgObj, int FirstStep, int LastStep, int Flags);
typedef int (__stdcall *t_Img_LoadBlocks)(HIMG ImgObj, UNICODECHAR* FileName);
typedef int (__stdcall *t_Img_SaveBlocks)(HIMG ImgObj, UNICODECHAR* FileName);
typedef int (__stdcall *t_Img_GetSkewAngle)(HIMG ImgObj);
typedef int (__stdcall *t_Img_GetPixLineCnt)(HIMG ImgObj);
typedef int (__stdcall *t_Img_GetPixLine)(HIMG ImgObj, int LineInd, int* X1pos, int* Y1pos, int* X2pos, int* Y2pos, int* Width);
typedef int (__stdcall *t_Img_GetScaleFactor)(HIMG ImgObj);
typedef int (__stdcall *t_Img_CalcPointPosition)(HIMG ImgObj, int* Xpos, int* Ypos, int Mode);
typedef int (__stdcall *t_Img_CopyCurrentPage)(HIMG ImgObjSrc, HIMG ImgObjDst, int Flags);
typedef int (__stdcall *t_Img_GetProperty)(HIMG ImgObj, int PropertyID);
typedef int (__stdcall *t_Img_SaveToFile)(HIMG ImgObj, UNICODECHAR* FileName, int Format, int Flags);
typedef int (__stdcall *t_Img_SaveToMemory)(HIMG ImgObj, char* Buffer, int BufferSize, int Format, int Flags);

typedef int (__stdcall *t_Blk_GetType)(HBLK BlkObj);
typedef int (__stdcall *t_Blk_SetType)(HBLK BlkObj, int BlockType);
typedef int (__stdcall *t_Blk_GetRect)(HBLK BlkObj, int* Xpos, int* Ypos, int* Width, int* Height);
typedef int (__stdcall *t_Blk_GetText)(HBLK BlkObj, UNICODECHAR* TextStr, int MaxLen, int Flags);
typedef int (__stdcall *t_Blk_GetLineCnt)(HBLK BlkObj);
typedef int (__stdcall *t_Blk_GetLineText)(HBLK BlkObj, int LineIndex, UNICODECHAR* TextStr, int MaxLen);
typedef int (__stdcall *t_Blk_GetWordCnt)(HBLK BlkObj, int LineIndex);
typedef int (__stdcall *t_Blk_GetWordText)(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* TextStr, int MaxLen);
typedef int (__stdcall *t_Blk_SetWordText)(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* TextStr);
typedef int (__stdcall *t_Blk_GetCharCnt)(HBLK BlkObj, int LineIndex, int WordIndex);
typedef int (__stdcall *t_Blk_GetCharRect)(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int* Xpos, int* Ypos, int* Width, int* Height);
typedef int (__stdcall *t_Blk_GetCharText)(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int ResultIndex, UNICODECHAR* TextStr, int MaxLen);
typedef int (__stdcall *t_Blk_GetCharQual)(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int ResultIndex);
typedef int (__stdcall *t_Blk_GetTextRect)(HBLK BlkObj, int LineIndex, int WordIndex, int* Xpos, int* Ypos, int* Width, int* Height);
typedef int (__stdcall *t_Blk_Inversion)(HBLK BlkObj, int Inversion);
typedef int (__stdcall *t_Blk_Rotation)(HBLK BlkObj, int Rotation);
typedef int (__stdcall *t_Blk_Mirror)(HBLK BlkObj, int Mirror);
typedef int (__stdcall *t_Blk_IsWordInDictionary)(HBLK BlkObj, int LineIndex, int WordIndex);
typedef int (__stdcall *t_Blk_SetRect)(HBLK BlkObj, int Xpos, int Ypos, int Width, int Height);
typedef int (__stdcall *t_Blk_GetWordQual)(HBLK BlkObj, int LineIndex, int WordIndex);
typedef int (__stdcall *t_Blk_GetWordFontColor)(HBLK BlkObj, int LineIndex, int WordIndex);
typedef int (__stdcall *t_Blk_GetWordFontSize)(HBLK BlkObj, int LineIndex, int WordIndex);
typedef int (__stdcall *t_Blk_GetWordFontStyle)(HBLK BlkObj, int LineIndex, int WordIndex);
typedef int (__stdcall *t_Blk_GetBackgroundColor)(HBLK BlkObj);
typedef int (__stdcall *t_Blk_SetWordRegEx)(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* RegEx, int Flags);
typedef int (__stdcall *t_Blk_GetBarcodeCnt)(HBLK BlkObj);
typedef int (__stdcall *t_Blk_GetBarcodeText)(HBLK BlkObj, int BarcodeInd, UNICODECHAR* TextStr, int MaxLen);
typedef int (__stdcall *t_Blk_GetBarcodeRect)(HBLK BlkObj, int BarcodeInd, int* Xpos, int* Ypos, int* Width, int* Height);
typedef int (__stdcall *t_Blk_GetBarcodeType)(HBLK BlkObj, int BarcodeInd);

typedef int (__stdcall *t_Svr_Create)(HCFG CfgObj, int Format, HSVR* SvrObj);
typedef int (__stdcall *t_Svr_Destroy)(HSVR SvrObj);
typedef int (__stdcall *t_Svr_NewDocument)(HSVR SvrObj);
typedef int (__stdcall *t_Svr_AddPage)(HSVR SvrObj, HIMG ImgObj, int Flags);
typedef int (__stdcall *t_Svr_SaveToFile)(HSVR SvrObj, UNICODECHAR* FileName);
typedef int (__stdcall *t_Svr_SaveToMemory)(HSVR SvrObj, char* Buffer, int BufferSize);
typedef int (__stdcall *t_Svr_GetText)(HSVR SvrObj, int PageIndex, UNICODECHAR* TextStr, int MaxLen);
typedef int (__stdcall *t_Svr_SetDocumentInfo)(HSVR SvrObj, int InfoID, UNICODECHAR* InfoStr);


typedef int (__stdcall *t_Scan_Create)(HCFG CfgObj, HSCAN* ScanObj);
typedef int (__stdcall *t_Scan_Enumerate)(HSCAN ScanObj, UNICODECHAR* ScannerNames, int MaxLen, int Flags);
typedef int (__stdcall *t_Scan_ScanToImg)(HSCAN ScanObj, HIMG ImgObj, int ScannerIndex, int Flags);
typedef int (__stdcall *t_Scan_ScanToFile)(HSCAN ScanObj, UNICODECHAR* FileName, int ScannerIndex, int Flags);
typedef int (__stdcall *t_Scan_Destroy)(HSCAN ScanObj);

////////////////////////////////////////////////////////////

class TNSOCR
{
private:
	HMODULE hlib;
	bool loaded;
	////
	t_Engine_Initialize p_Engine_Initialize;
	t_Engine_InitializeAdvanced p_Engine_InitializeAdvanced;
	t_Engine_Uninitialize p_Engine_Uninitialize;
	t_Engine_SetDataDirectory p_Engine_SetDataDirectory;
	t_Engine_GetVersion p_Engine_GetVersion;
	t_Engine_SetLicenseKey p_Engine_SetLicenseKey;

	t_Cfg_Create p_Cfg_Create;
	t_Cfg_Destroy p_Cfg_Destroy;
	t_Cfg_LoadOptions p_Cfg_LoadOptions;
	t_Cfg_SaveOptions p_Cfg_SaveOptions;
	t_Cfg_LoadOptionsFromString p_Cfg_LoadOptionsFromString;
	t_Cfg_SaveOptionsToString p_Cfg_SaveOptionsToString;
	t_Cfg_GetOption p_Cfg_GetOption;
	t_Cfg_SetOption p_Cfg_SetOption;
	t_Cfg_DeleteOption p_Cfg_DeleteOption;

	t_Ocr_Create p_Ocr_Create;
	t_Ocr_Destroy p_Ocr_Destroy;
	t_Ocr_ProcessPages p_Ocr_ProcessPages;

	t_Img_Create p_Img_Create;
	t_Img_Destroy p_Img_Destroy;
	t_Img_LoadFile p_Img_LoadFile;
	t_Img_LoadFromMemory p_Img_LoadFromMemory;
	t_Img_LoadBmpData p_Img_LoadBmpData;
	t_Img_Unload p_Img_Unload;
	t_Img_GetPageCount p_Img_GetPageCount;
	t_Img_SetPage p_Img_SetPage;
	t_Img_GetSize p_Img_GetSize;
	t_Img_DrawToDC p_Img_DrawToDC;
	t_Img_GetBmpData p_Img_GetBmpData;
	t_Img_DeleteAllBlocks p_Img_DeleteAllBlocks;
	t_Img_AddBlock p_Img_AddBlock;
	t_Img_DeleteBlock p_Img_DeleteBlock;
	t_Img_GetBlockCnt p_Img_GetBlockCnt;
	t_Img_GetBlock p_Img_GetBlock;
	t_Img_GetImgText p_Img_GetImgText;
	t_Img_OCR p_Img_OCR;
	t_Img_LoadBlocks p_Img_LoadBlocks;
	t_Img_SaveBlocks p_Img_SaveBlocks;
	t_Img_GetSkewAngle p_Img_GetSkewAngle;
	t_Img_GetPixLineCnt p_Img_GetPixLineCnt;
	t_Img_GetPixLine p_Img_GetPixLine;
	t_Img_GetScaleFactor p_Img_GetScaleFactor;
	t_Img_CalcPointPosition p_Img_CalcPointPosition;
	t_Img_CopyCurrentPage p_Img_CopyCurrentPage;
	t_Img_GetProperty p_Img_GetProperty;
	t_Img_SaveToFile p_Img_SaveToFile;
	t_Img_SaveToMemory p_Img_SaveToMemory;

	t_Blk_GetType p_Blk_GetType;
	t_Blk_SetType p_Blk_SetType;
	t_Blk_GetRect p_Blk_GetRect;
	t_Blk_GetText p_Blk_GetText;
	t_Blk_GetLineCnt p_Blk_GetLineCnt;
	t_Blk_GetLineText p_Blk_GetLineText;
	t_Blk_GetWordCnt p_Blk_GetWordCnt;
	t_Blk_GetWordText p_Blk_GetWordText;
	t_Blk_SetWordText p_Blk_SetWordText;
	t_Blk_GetCharCnt p_Blk_GetCharCnt;
	t_Blk_GetCharRect p_Blk_GetCharRect;
	t_Blk_GetCharText p_Blk_GetCharText;
	t_Blk_GetCharQual p_Blk_GetCharQual;
	t_Blk_GetTextRect p_Blk_GetTextRect;
	t_Blk_Inversion p_Blk_Inversion;
	t_Blk_Rotation p_Blk_Rotation;
	t_Blk_Mirror p_Blk_Mirror;
	t_Blk_IsWordInDictionary p_Blk_IsWordInDictionary;
	t_Blk_SetRect p_Blk_SetRect;
	t_Blk_GetWordQual p_Blk_GetWordQual;
	t_Blk_GetWordFontColor p_Blk_GetWordFontColor;
	t_Blk_GetWordFontSize p_Blk_GetWordFontSize;
	t_Blk_GetWordFontStyle p_Blk_GetWordFontStyle;
	t_Blk_GetBackgroundColor p_Blk_GetBackgroundColor;
	t_Blk_SetWordRegEx p_Blk_SetWordRegEx;
	t_Blk_GetBarcodeCnt p_Blk_GetBarcodeCnt;
	t_Blk_GetBarcodeText p_Blk_GetBarcodeText;
	t_Blk_GetBarcodeRect p_Blk_GetBarcodeRect;
	t_Blk_GetBarcodeType p_Blk_GetBarcodeType;

	t_Svr_Create p_Svr_Create;
	t_Svr_Destroy p_Svr_Destroy;
	t_Svr_NewDocument p_Svr_NewDocument;
	t_Svr_AddPage p_Svr_AddPage;
	t_Svr_SaveToFile p_Svr_SaveToFile;
	t_Svr_SaveToMemory p_Svr_SaveToMemory;
	t_Svr_GetText p_Svr_GetText;
	t_Svr_SetDocumentInfo p_Svr_SetDocumentInfo;

	t_Scan_Create p_Scan_Create;
	t_Scan_Enumerate p_Scan_Enumerate;
	t_Scan_ScanToImg p_Scan_ScanToImg;
	t_Scan_ScanToFile p_Scan_ScanToFile;
	t_Scan_Destroy p_Scan_Destroy;
public:
	TNSOCR(wchar_t* DllFileName);
	virtual ~TNSOCR();
	bool IsDllLoaded();
	bool TryLoadDLL(wchar_t* DllFileName);

	//////////////////// DLL functions

	int Engine_Initialize();
	int Engine_InitializeAdvanced(HCFG* CfgObj, HOCR* OcrObj, HIMG* ImgObj);
	int Engine_Uninitialize();
	int Engine_SetDataDirectory(UNICODECHAR* DirectoryPath);
	int Engine_GetVersion(UNICODECHAR* VerStr);
	int Engine_SetLicenseKey(UNICODECHAR* LicenseKey);

	int Cfg_Create(HCFG* CfgObj);
	int Cfg_Destroy(HCFG CfgObj);
	int Cfg_LoadOptions(HCFG CfgObj, UNICODECHAR* FileName);
	int Cfg_SaveOptions(HCFG CfgObj, UNICODECHAR* FileName);
	int Cfg_LoadOptionsFromString(HCFG CfgObj, UNICODECHAR* XMLString);
	int Cfg_SaveOptionsToString(HCFG CfgObj, UNICODECHAR* XMLString, int MaxLen);
	int Cfg_GetOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath, UNICODECHAR* OptionValue, int MaxLen);
	int Cfg_SetOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath, UNICODECHAR* OptionValue);
	int Cfg_DeleteOption(HCFG CfgObj, int BlockType, UNICODECHAR* OptionPath);

	int Ocr_Create(HCFG CfgObj, HOCR* OcrObj);
	int Ocr_Destroy(HOCR OcrObj);
	int Ocr_ProcessPages(HIMG ImgObj, HSVR SvrObj, int PageIndexStart, int PageIndexEnd, int OcrObjCnt, int Flags);

	int Img_Create(HOCR OcrObj, HIMG* ImgObj);
	int Img_Destroy(HIMG ImgObj);
	int Img_LoadFile(HIMG ImgObj, UNICODECHAR* FileName);
	int Img_LoadFromMemory(HIMG ImgObj, unsigned char* Bytes, int DataSize);
	int Img_LoadBmpData(HIMG ImgObj, unsigned char* Bits, int Width, int Height, int Flags, int Stride);
	int Img_Unload(HIMG ImgObj);
	int Img_GetPageCount(HIMG ImgObj);
	int Img_SetPage(HIMG ImgObj, int PageIndex);
	int Img_GetSize(HIMG ImgObj, int* Width, int* Height);
	int Img_DrawToDC(HIMG ImgObj, int HandleDC, int X, int Y, int* Width, int* Height, int Flags);
	int Img_GetBmpData(HIMG ImgObj, unsigned char* Bits, int* Width, int* Height, int Flags);
	int Img_DeleteAllBlocks(HIMG ImgObj);
	int Img_AddBlock(HIMG ImgObj, int Xpos, int Ypos, int Width, int Height, HBLK* BlkObj);
	int Img_DeleteBlock(HIMG ImgObj, HBLK BlkObj);
	int Img_GetBlockCnt(HIMG ImgObj);
	int Img_GetBlock(HIMG ImgObj, int BlockIndex, HBLK* BlkObj);
	int Img_GetImgText(HIMG ImgObj, UNICODECHAR* TextStr, int MaxLen, int Flags);
	int Img_OCR(HIMG ImgObj, int FirstStep, int LastStep, int Flags);
	int Img_LoadBlocks(HIMG ImgObj, UNICODECHAR* FileName);
	int Img_SaveBlocks(HIMG ImgObj, UNICODECHAR* FileName);
	int Img_GetSkewAngle(HIMG ImgObj);
	int Img_GetPixLineCnt(HIMG ImgObj);
	int Img_GetPixLine(HIMG ImgObj, int LineInd, int* X1, int* Y1, int* X2, int* Y2, int* Width);
	int Img_GetScaleFactor(HIMG ImgObj);
	int Img_CalcPointPosition(HIMG ImgObj, int* Xpos, int* Ypos, int Mode);
	int Img_CopyCurrentPage(HIMG ImgObjSrc, HIMG ImgObjDst, int Flags);
	int Img_GetProperty(HIMG ImgObj, int PropertyID);
	int Img_SaveToFile(HIMG ImgObj, UNICODECHAR* FileName, int Format, int Flags);
	int Img_SaveToMemory(HIMG ImgObj, char* Buffer, int BufferSize, int Format, int Flags);

	int Blk_GetType(HBLK BlkObj);
	int Blk_SetType(HBLK BlkObj, int BlockType);
	int Blk_GetRect(HBLK BlkObj, int* Xpos, int* Ypos, int* Width, int* Height);
	int Blk_GetText(HBLK BlkObj, UNICODECHAR* TextStr, int MaxLen, int Flags);
	int Blk_GetLineCnt(HBLK BlkObj);
	int Blk_GetLineText(HBLK BlkObj, int LineIndex, UNICODECHAR* TextStr, int MaxLen);
	int Blk_GetWordCnt(HBLK BlkObj, int LineIndex);
	int Blk_GetWordText(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* TextStr, int MaxLen);
	int Blk_SetWordText(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* TextStr);
	int Blk_GetCharCnt(HBLK BlkObj, int LineIndex, int WordIndex);
	int Blk_GetCharRect(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int* Xpos, int* Ypos, int* Width, int* Height);
	int Blk_GetCharText(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int ResultIndex, UNICODECHAR* TextStr, int MaxLen);
	int Blk_GetCharQual(HBLK BlkObj, int LineIndex, int WordIndex, int CharIndex, int ResultIndex);
	int Blk_GetTextRect(HBLK BlkObj, int LineIndex, int WordIndex, int* Xpos, int* Ypos, int* Width, int* Height);
	int Blk_Inversion(HBLK BlkObj, int Inversion);
	int Blk_Rotation(HBLK BlkObj, int Rotation);
	int Blk_Mirror(HBLK BlkObj, int Mirror);
	int Blk_IsWordInDictionary(HBLK BlkObj, int LineIndex, int WordIndex);
	int Blk_SetRect(HBLK BlkObj, int Xpos, int Ypos, int Width, int Height);
	int Blk_GetWordQual(HBLK BlkObj, int LineIndex, int WordIndex);
	int Blk_GetWordFontColor(HBLK BlkObj, int LineIndex, int WordIndex);
	int Blk_GetWordFontSize(HBLK BlkObj, int LineIndex, int WordIndex);
	int Blk_GetWordFontStyle(HBLK BlkObj, int LineIndex, int WordIndex);
	int Blk_GetBackgroundColor(HBLK BlkObj);
	int Blk_SetWordRegEx(HBLK BlkObj, int LineIndex, int WordIndex, UNICODECHAR* RegEx, int Flags);
	int Blk_GetBarcodeCnt(HBLK BlkObj);
	int Blk_GetBarcodeText(HBLK BlkObj, int BarcodeInd, UNICODECHAR* TextStr, int MaxLen);
	int Blk_GetBarcodeRect(HBLK BlkObj, int BarcodeInd, int* Xpos, int* Ypos, int* Width, int* Height);
	int Blk_GetBarcodeType(HBLK BlkObj, int BarcodeInd);

	int Svr_Create(HCFG CfgObj, int Format, HSVR* SvrObj);
	int Svr_Destroy(HSVR SvrObj);
	int Svr_NewDocument(HSVR SvrObj);
	int Svr_AddPage(HSVR SvrObj, HIMG ImgObj, int Flags);
	int Svr_SaveToFile(HSVR SvrObj, UNICODECHAR* FileName);
	int Svr_SaveToMemory(HSVR SvrObj, char* Buffer, int BufferSize);
	int Svr_GetText(HSVR SvrObj, int PageIndex, UNICODECHAR* TextStr, int MaxLen);
	int Svr_SetDocumentInfo(HSVR SvrObj, int InfoID, UNICODECHAR* InfoStr);

	int Scan_Create(HCFG CfgObj, HSCAN* ScanObj);
	int Scan_Enumerate(HSCAN ScanObj, UNICODECHAR* ScannerNames, int MaxLen, int Flags);
	int Scan_ScanToImg(HSCAN ScanObj, HIMG ImgObj, int ScannerIndex, int Flags);
	int Scan_ScanToFile(HSCAN ScanObj, UNICODECHAR* FileName, int ScannerIndex, int Flags);
	int Scan_Destroy(HSCAN ScanObj);
};

#endif
