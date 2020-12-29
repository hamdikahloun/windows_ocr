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

	std::string getOcr(std::string file) {
		TNSOCR* NsOCR;
		NsOCR = new TNSOCR(L"Bin_64/NSOCR.dll");
		if (!NsOCR->IsDllLoaded()) {
			wcout << "DLL not LOADED" << endl;
			return "";
		}
		NsOCR->Engine_SetLicenseKey(L"AB2A4DD5FF2A"); //required for licensed version only
		int CfgObj, OcrObj, ImgObj, res, n;
		wchar_t* txt;
		NsOCR->Engine_Initialize(); //initialize OCR engine
		NsOCR->Cfg_Create(&CfgObj); //create CFG object
		//NsOCR->Cfg_LoadOptions(CfgObj, L"Bin_common/Config.dat"); //load configuration
		NsOCR->Cfg_SetOption(CfgObj, BT_DEFAULT, L"Languages/English", L"1"); //unselect English language
		NsOCR->Ocr_Create(CfgObj, &OcrObj); //create OCR object
		NsOCR->Img_Create(OcrObj, &ImgObj); //create IMG object
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
		wcout << txt << endl;
		std::string s = wchar2string(txt);
		free(txt); //free memory
		return s;
	}

	std::string getMrz(std::string file) {
		TNSOCR* NsOCR;
		NsOCR = new TNSOCR(L"Bin_64/NSOCR.dll");
		if (!NsOCR->IsDllLoaded()) {
			wcout << "DLL not LOADED" << endl;
			return "";
		}
		NsOCR->Engine_SetLicenseKey(L"AB2A4DD5FF2A"); //required for licensed version only
		int SvrObj, CfgObj, OcrObj, ImgObj, res, n;
		wchar_t* txt;
		NsOCR->Engine_Initialize(); //initialize OCR engine
		NsOCR->Cfg_Create(&CfgObj); //create CFG object
		NsOCR->Cfg_LoadOptions(CfgObj, L"Bin_common/Config.dat"); //load configuration
		NsOCR->Ocr_Create(CfgObj, &OcrObj); //create OCR object
		NsOCR->Img_Create(OcrObj, &ImgObj); //create IMG object
		NsOCR->Cfg_SetOption(CfgObj, BT_DEFAULT, L"Zoning/OneZone", L"9"); //NSOCR must create BT_MRZ zone that covers entire page
		wchar_t* wide_string = new wchar_t[file.length() + 1];
		std::copy(file.begin(), file.end(), wide_string);
		wide_string[file.length()] = 0;

		res = NsOCR->Img_LoadFile(ImgObj, wide_string); //load some image for OCR

		delete[] wide_string;
		if (res > ERROR_FIRST) {
			wcout << "File not LOADED" << endl;
			return "";
		};
		NsOCR->Svr_Create(CfgObj, SVR_FORMAT_XML, &SvrObj); //create Saver object, output format is XML
		NsOCR->Svr_NewDocument(SvrObj); //start new document
		res = NsOCR->Img_OCR(ImgObj, OCRSTEP_FIRST, OCRSTEP_LAST, OCRFLAG_NONE); //perform OCR
		if (res > ERROR_FIRST) {
			wcout << "OCR error" << endl;
			return "";
		};
		res = NsOCR->Svr_AddPage(SvrObj, ImgObj, FMT_EXACTCOPY); //add OCR'ed image to output document
		if (res > ERROR_FIRST) {
			wcout << "Output Doc not LOADED" << endl;
			return "";
		};
		res = NsOCR->Svr_SaveToFile(SvrObj, L"d:\\out.xml"); //save OCRed image to XML file
		n = NsOCR->Svr_GetText(SvrObj, -1, NULL, 0) + 1;
		txt = (wchar_t*)malloc(2 * n);
		res = NsOCR->Svr_GetText(SvrObj, -1, txt, n); //save OCRed image to buffer
		
		if (res > ERROR_FIRST) {
			wcout << "Svr_GetText Error" << endl;
			return "";
		};
		wcout << txt << endl;
		NsOCR->Engine_Uninitialize(); //release all created objects and uninitialize OCR engine
		std::string s = wchar2string(txt);
		free(txt); //free memory
		return s;
	}

	std::string getBarcode(std::string file) {
		TNSOCR* NsOCR;
		NsOCR = new TNSOCR(L"Bin_64/NSOCR.dll");
		if (!NsOCR->IsDllLoaded()) {
			wcout << "DLL not LOADED" << endl;
			return "";
		}
		NsOCR->Engine_SetLicenseKey(L"AB2A4DD5FF2A"); //required for licensed version only
		int CfgObj, OcrObj, ImgObj, res, n;
		wchar_t* txt;
		NsOCR->Engine_Initialize(); //initialize OCR engine
		NsOCR->Cfg_Create(&CfgObj); //create CFG object
		//NsOCR->Cfg_LoadOptions(CfgObj, L"Bin_common/Config.dat"); //load configuration
		NsOCR->Ocr_Create(CfgObj, &OcrObj); //create OCR object
		NsOCR->Img_Create(OcrObj, &ImgObj); //create IMG object
		NsOCR->Cfg_SetOption(CfgObj, BT_DEFAULT, L"Zoning/OneZone", L"7");
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
		wcout << txt << endl;
		std::string s = wchar2string(txt);
		free(txt); //free memory
		return s;
	}

	void WindowsOcrPlugin::HandleMethodCall(
		const flutter::MethodCall<flutter::EncodableValue>& method_call,
		std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {

		if (method_call.method_name().compare("getOcr") == 0) {
			std::string file;
			const auto* arguments = std::get_if<flutter::EncodableMap>(method_call.arguments());
			auto vl = arguments->find(flutter::EncodableValue("path"));
			if (vl != arguments->end()) {
				file = std::get<std::string>(vl->second);
			}

			result->Success(flutter::EncodableValue(getOcr(file).c_str()));
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
