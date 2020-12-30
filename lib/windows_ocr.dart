import 'dart:async';

import 'package:flutter/services.dart';

class WindowsOcr {
  static const MethodChannel _channel = const MethodChannel('windows_ocr');

  static Future<String> getOcr(String filePath,
      {language = "English"}) async {
    final String res = await _channel.invokeMethod('getOcr', <String, dynamic>{
      'path': filePath,
      'language': 'Languages/$language',
    });
    return res;
  }

  static Future<String> getMrz(String filePath) async {
    final String res = await _channel.invokeMethod('getMrz', <String, dynamic>{
      'path': filePath,
    });
    return res;
  }

  static Future<String> getBarcode(String filePath) async {
    final String res =
        await _channel.invokeMethod('getBarcode', <String, dynamic>{
      'path': filePath,
    });
    return res;
  }
}
