#include "include/windows_ocr/windows_ocr_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>
#include "NSOCR.h"
// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <sstream>
using namespace std;
namespace {

	class WindowsOcrPlugin : public flutter::Plugin {
	public:
		static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar);

		WindowsOcrPlugin();

		virtual ~WindowsOcrPlugin();

	private:
		// Called when a method is called on this plugin's channel from Dart.
		void HandleMethodCall(
			const flutter::MethodCall<flutter::EncodableValue>& method_call,
			std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
	};

	// static
	void WindowsOcrPlugin::RegisterWithRegistrar(
		flutter::PluginRegistrarWindows* registrar) {
		auto channel =
			std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
				registrar->messenger(), "windows_ocr",
				&flutter::StandardMethodCodec::GetInstance());

		auto plugin = std::make_unique<WindowsOcrPlugin>();

		channel->SetMethodCallHandler(
			[plugin_pointer = plugin.get()](const auto& call, auto result) {
			plugin_pointer->HandleMethodCall(call, std::move(result));
		});

		registrar->AddPlugin(std::move(plugin));
	}

	WindowsOcrPlugin::WindowsOcrPlugin() {}

	WindowsOcrPlugin::~WindowsOcrPlugin() {}

	std::string wchar2string(wchar_t* str)
	{
		std::string mystring;
		while (*str)
			mystring += (char)*str++;

		return  mystring;
	}

	std::string getOcr(std::string file, std::string language) {
		TNSOCR* NsOCR;
		NsOCR = new TNSOCR(L"Bin_64/NSOCR.dll");
		if (!NsOCR->IsDllLoaded()) {
			wcout << "DLL not LOADED" << endl;
			return "";
		}
		NsOCR->Engine_SetLicenseKey(L"AB2A4DD5FF2A"); //required for licensed version only
		int CfgObj, OcrObj, ImgObj, res, n;
		wchar_t* txt;
		NsOCR->Engine_InitializeAdvanced(&CfgObj, &OcrObj, &ImgObj); //initialize OCR engine, create objects and load configuration
		wchar_t* lang = new wchar_t[language.length() + 1];
		std::copy(language.begin(), language.end(), lang);
		lang[language.length()] = 0;
		wcout << lang << endl;
		NsOCR->Cfg_SetOption(CfgObj, BT_DEFAULT, lang, L"1");
		wchar_t* wide_string = new wchar_t[file.length() + 1];
		std::copy(file.begin(), file.end(), wide_string);
		wide_string[file.length()] = 0;

		res = NsOCR->Img_LoadFile(ImgObj, wide_string); //load some image for OCR

		delete[] wide_string;

		if (res > ERROR_FIRST) {
			wcout << "File not LOADED" << endl;
			return "";
		};
		res = NsOCR->Img_OCR(ImgObj, OCRSTEP_FIRST, OCRSTEP_LAST, OCRFLAG_NONE); //perform OCR
		if (res > ERROR_FIRST) {
			wcout << "OCR Error" << endl;
			return "";
		};
		n = NsOCR->Img_GetImgText(ImgObj, NULL, 0, FMT_EXACTCOPY) + 1; //get length in unicode characters plus terminating NULL character
		txt = (wchar_t*)malloc(2 * n); //allocate memory for text
		NsOCR->Img_GetImgText(ImgObj, txt, n, FMT_EXACTCOPY); //get text
		NsOCR->Engine_Uninitialize(); //release all created objects and uninitialize OCR engine
		
		std::string s = wchar2string(txt);
		free(txt); //free memory
		wcout << s.c_str() << endl;
		return s;
	}

	std::string getMrz(std::string file) {
		int CfgObj, OcrObj, ImgObj, SvrObj, res, n;
		wchar_t* txt;
		TNSOCR* NsOCR;
		NsOCR = new TNSOCR(L"Bin_64/NSOCR.dll");
		if (!NsOCR->IsDllLoaded()) {
			wcout << "DLL not LOADED" << endl;
			return "";
		}
		NsOCR->Engine_SetLicenseKey(L"AB2A4DD5FF2A"); //required for licensed version only
		NsOCR->Engine_InitializeAdvanced(&CfgObj, &OcrObj, &ImgObj); //initialize OCR engine, create objects and load configuration
		NsOCR->Cfg_SetOption(CfgObj, BT_DEFAULT, L"Zoning/OneZone", L"9"); //NSOCR must create BT_MRZ zone that covers entire page
		wchar_t* path = new wchar_t[file.length() + 1];
		std::copy(file.begin(), file.end(), path);
		path[file.length()] = 0;
		wcout << path << endl;
		res = NsOCR->Img_LoadFile(ImgObj, path); //load some image for OCR
		if (res > ERROR_FIRST) {
			wcout << "Img_LoadFile Erro" << endl;
			return "";
		};
		NsOCR->Svr_Create(CfgObj, SVR_FORMAT_XML, &SvrObj); //create Saver object, output format is XML
		NsOCR->Svr_NewDocument(SvrObj); //start new document
		res = NsOCR->Img_OCR(ImgObj, OCRSTEP_FIRST, OCRSTEP_LAST, OCRFLAG_NONE); //perform OCR
		if (res > ERROR_FIRST) {
			wcout << "Img_OCR Erro" << endl;
			return "";
		};
		res = NsOCR->Svr_AddPage(SvrObj, ImgObj, FMT_EXACTCOPY); //add OCR'ed image to output document
		if (res > ERROR_FIRST) {
			wcout << "Svr_AddPage Erro" << endl;
			return "";
		};
		//res = NsOCR->Svr_SaveToFile(SvrObj, L"D:\\out.xml"); //save OCRed image to XML file
		char* buffer = NULL;
		int bSize = NsOCR->Svr_SaveToMemory(SvrObj, buffer, 0);
		buffer = (char*)malloc(bSize);
		res = NsOCR->Svr_SaveToMemory(SvrObj, buffer, bSize); //save OCRed image to memory
		
		if (res > ERROR_FIRST) {
			wcout << "Svr_SaveToMemory Erro" << endl;
			return "";
		};
		n = NsOCR->Svr_GetText(SvrObj, -1, NULL, 0) + 1;
		txt = (wchar_t*)malloc(2 * n);
		res = NsOCR->Svr_GetText(SvrObj, -1, txt, n);
		
		std::string s = wchar2string(txt);
		wcout << s.c_str() << endl;
		free(txt); //free memory
		free(buffer);
		NsOCR->Engine_Uninitialize(); //release all created objects and uninitialize OCR engine
		return s;
	}

	std::string getBarcode(std::string file) {
		TNSOCR* NsOCR;
		std::string s = "";
		NsOCR = new TNSOCR(L"Bin_64/NSOCR.dll");
		if (!NsOCR->IsDllLoaded()) {
			wcout << "DLL not LOADED" << endl;
			return "";
		}
		NsOCR->Engine_SetLicenseKey(L"AB2A4DD5FF2A"); //required for licensed version only
		int CfgObj, OcrObj, ImgObj, res, cnt, i, n, Xpos, Ypos, Width, Height;
		wchar_t* txt;
		NsOCR->Engine_InitializeAdvanced(&CfgObj, &OcrObj, &ImgObj); //initialize OCR engine, create objects and load configuration
		NsOCR->Cfg_SetOption(CfgObj, BT_DEFAULT, L"Zoning/FindBarcodes", L"2"); //recognize barcodes only
		wchar_t* wide_string = new wchar_t[file.length() + 1];
		std::copy(file.begin(), file.end(), wide_string);
		wide_string[file.length()] = 0;
		//note: it is also possible to disable rescaling, deskew etc. to achieve best performance, check "Performace Tips" section
		res = NsOCR->Img_LoadFile(ImgObj, wide_string); //load some image for OCR
		if (res > ERROR_FIRST) {
			wcout << "Img_LoadFile Error" << endl;
			return "";
		};
		res = NsOCR->Img_OCR(ImgObj, OCRSTEP_FIRST, OCRSTEP_LAST, OCRFLAG_NONE); //perform OCR 
		if (res > ERROR_FIRST) {
			wcout << "Img_OCR Error" << endl;
			return "";
		};
		cnt = NsOCR->Blk_GetBarcodeCnt(ImgObj); //get number of barcodes of entire image
		wcout << cnt << endl;
		for (i = 0; i < cnt; i++)
		{
			NsOCR->Blk_GetBarcodeRect(ImgObj, i, &Xpos, &Ypos, &Width, &Height); //get barcode position and size
			res = NsOCR->Blk_GetBarcodeType(ImgObj, i); //get barcode type
			
			n = NsOCR->Blk_GetBarcodeText(ImgObj, i, NULL, 0) + 1; //get buffer size plus terminating NULL character
			txt = (wchar_t*)malloc(sizeof(wchar_t) * n); //allocate memory for text
			NsOCR->Blk_GetBarcodeText(ImgObj, i, txt, n); //get barcode text
			wcout << res << endl;
			if (s == "") {
				s.append(wchar2string(txt));
			}
			else {
				s.append(",").append(wchar2string(txt));
			}
			free(txt); //free memory			
		}
		NsOCR->Engine_Uninitialize(); //release all created objects and uninitialize OCR engine
		return s;
	}

	void WindowsOcrPlugin::HandleMethodCall(
		const flutter::MethodCall<flutter::EncodableValue>& method_call,
		std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {

		if (method_call.method_name().compare("getOcr") == 0) {
			std::string file;
			std::string language;
			const auto* arguments = std::get_if<flutter::EncodableMap>(method_call.arguments());
			auto vl = arguments->find(flutter::EncodableValue("path"));
			if (vl != arguments->end()) {
				file = std::get<std::string>(vl->second);
			}
			auto va = arguments->find(flutter::EncodableValue("language"));
			if (va != arguments->end()) {
				language = std::get<std::string>(va->second);
			}

			result->Success(flutter::EncodableValue(getOcr(file, language).c_str()));
		}
		else if (method_call.method_name().compare("getMrz") == 0) {
			std::string file;
			const auto* arguments = std::get_if<flutter::EncodableMap>(method_call.arguments());
			auto vl = arguments->find(flutter::EncodableValue("path"));
			if (vl != arguments->end()) {
				file = std::get<std::string>(vl->second);
			}

			result->Success(flutter::EncodableValue(getMrz(file).c_str()));
		}
		else if (method_call.method_name().compare("getBarcode") == 0) {
			std::string file;
			const auto* arguments = std::get_if<flutter::EncodableMap>(method_call.arguments());
			auto vl = arguments->find(flutter::EncodableValue("path"));
			if (vl != arguments->end()) {
				file = std::get<std::string>(vl->second);
			}

			result->Success(flutter::EncodableValue(getBarcode(file).c_str()));
		}
		else {
			result->NotImplemented();
		}
	}

}  // namespace

void WindowsOcrPluginRegisterWithRegistrar(
	FlutterDesktopPluginRegistrarRef registrar) {
	WindowsOcrPlugin::RegisterWithRegistrar(
		flutter::PluginRegistrarManager::GetInstance()
		->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
