import 'dart:async';

import 'package:file_chooser/file_chooser.dart';
import 'package:flutter/material.dart';
import 'package:windows_ocr/windows_ocr.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _ocr = '';
  bool isLoading = false;

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    setState(() {
      isLoading = true;
      _ocr = '';
    });
    String ocr;
    // Platform messages may fail, so we use a try/catch PlatformException.
    try {
      FileChooserResult result =
          await showOpenPanel(allowsMultipleSelection: false);
      if (!result.canceled) {
        ocr = await WindowsOcr.getOcr(result.paths[0]);
      } else {
        ocr = 'File selector canceled';
      }
    } catch (error) {
      debugPrint('Error: $error');
      ocr = 'Failed to get ocr: $error';
    }

    setState(() {
      isLoading = false;
      _ocr = ocr;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        floatingActionButton: FloatingActionButton(
          onPressed: () {
            initPlatformState();
          },
          child: Icon(Icons.image),
        ),
        appBar: AppBar(
          title: const Text('OCR example app'),
        ),
        body: Center(
          child: isLoading ? CircularProgressIndicator() : Text('$_ocr'),
        ),
      ),
    );
  }
}
