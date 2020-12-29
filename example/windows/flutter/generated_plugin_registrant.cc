//
//  Generated file. Do not edit.
//

#include "generated_plugin_registrant.h"

#include <file_chooser/file_chooser_plugin.h>
#include <windows_ocr/windows_ocr_plugin.h>

void RegisterPlugins(flutter::PluginRegistry* registry) {
  FileChooserPluginRegisterWithRegistrar(
      registry->GetRegistrarForPlugin("FileChooserPlugin"));
  WindowsOcrPluginRegisterWithRegistrar(
      registry->GetRegistrarForPlugin("WindowsOcrPlugin"));
}
