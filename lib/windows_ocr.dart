import 'dart:async';
import 'dart:io';

import 'package:flutter/cupertino.dart';
import 'package:flutter/services.dart';
import 'package:path_provider/path_provider.dart';
import 'package:windows_ocr/Mrz.dart';
import 'package:xml/xml.dart';

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

  static Future<Mrz?> getMrz(String filePath) async {
    Directory tempDir = await getTemporaryDirectory();
    String tempPath = tempDir.path + '\\' + 'out.xml';
    final res = await _channel.invokeMethod('getMrz', <String, dynamic>{
      'path': filePath,
      'pathXml': tempPath,
    });
    final document = XmlDocument.parse(res);
    final mrzNodes = document.findAllElements('MRZ').toList();
    Mrz? mrz;
    if (mrzNodes.length > 0) {
      XmlElement element = mrzNodes[0];
      mrz = Mrz.fromData(element);
    }
    return mrz;
  }

  static Future<List<Barcode>> getBarcode(String filePath) async {
    final res = await _channel
        .invokeMethod<List<dynamic>>('getBarcode', <String, dynamic>{
      'path': filePath,
    });
    debugPrint(res.toString());
    final barcodes = <Barcode>[];
    if (res == null) {
      return [];
    }
    for (final barcode in res) {
      barcodes.add(Barcode.fromData(barcode));
    }
    return barcodes;
  }
}
