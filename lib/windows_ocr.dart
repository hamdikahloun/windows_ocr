import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter/cupertino.dart';
import 'package:flutter/services.dart';
import 'package:path_provider/path_provider.dart';

import 'Barcode.dart';

class WindowsOcr {
  static const MethodChannel _channel = const MethodChannel('windows_ocr');

  static Future<String> getOcr(String filePath, {language = "English"}) async {
    final String res = await _channel.invokeMethod('getOcr', <String, dynamic>{
      'path': filePath,
      'language': 'Languages/$language',
    });
    return res;
  }

  static Future<dynamic> getMrz(String filePath) async {
    Directory tempDir = await getTemporaryDirectory();
    String tempPath = tempDir.path + '\\' + 'out.xml';
    debugPrint(tempPath);
    final res = await _channel.invokeMethod('getMrz', <String, dynamic>{
      'path': filePath,
      'pathXml': tempPath,
    });

    File file = File(tempPath);
    if (await file.exists()) {
      Uint8List uint8list = await file.readAsBytes();
      String encode = base64.encode(uint8list);
      debugPrint('$encode');
    }
    return res;
  }

  static Future<List<Barcode>> getBarcode(String filePath) async {
    final res = await _channel
        .invokeMethod<List<dynamic>>('getBarcode', <String, dynamic>{
      'path': filePath,
    });
    debugPrint(res.toString());
    final barcodes = <Barcode>[];
    for (final barcode in res) {
      barcodes.add(Barcode.fromData(barcode));
    }
    return barcodes;
  }
}
