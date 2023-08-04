import 'package:file_picker/file_picker.dart';
import 'package:flutter/material.dart';
import 'package:windows_ocr/Barcode.dart';
import 'package:windows_ocr/Languages.dart';
import 'package:windows_ocr/Mrz.dart';
import 'package:windows_ocr/windows_ocr.dart';

void main() {
  runApp(MaterialApp(
    title: 'Windows OCR',
    home: Home(),
  ));
}

class Home extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Windows OCR Example'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            ElevatedButton(
              child: Text('OCR'),
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => MyOcr()),
                );
              },
            ),
            SizedBox(
              height: 16,
            ),
            ElevatedButton(
              child: Text('Barcode'),
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => MyBarcode()),
                );
              },
            ),
            SizedBox(
              height: 16,
            ),
            ElevatedButton(
              child: Text('MRZ'),
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => MyMrz()),
                );
              },
            )
          ],
        ),
      ),
    );
  }
}

class MyBarcode extends StatefulWidget {
  @override
  _MyBarcodeState createState() => _MyBarcodeState();
}

class _MyBarcodeState extends State<MyBarcode> {
  List<Barcode> _listBarcode = [];
  bool isLoading = false;

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    setState(() {
      isLoading = true;
      _listBarcode = [];
    });

    List<Barcode> listBarcode = [];
    // Platform messages may fail, so we use a try/catch.
    try {
      final result = await FilePicker.platform.pickFiles(allowMultiple: false);
      if (result != null) {
        if (result.paths[0] != null) {
          listBarcode = await WindowsOcr.getBarcode(result.paths[0]!);
        }
      }
    } catch (error) {
      debugPrint('Error: $error');
    }

    setState(() {
      isLoading = false;
      _listBarcode = listBarcode;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          initPlatformState();
        },
        child: Icon(Icons.image),
      ),
      appBar: AppBar(
        title: const Text('Barcode'),
      ),
      body: Center(
          child: isLoading
              ? CircularProgressIndicator()
              : _listBarcode.length > 0
                  ? ListView.builder(
                      padding: EdgeInsets.all(8),
                      itemCount: _listBarcode.length,
                      itemBuilder: (context, index) {
                        return ListTile(
                          title: Text('${_listBarcode[index].value}'),
                          subtitle: Text('${_listBarcode[index].type}'),
                        );
                      },
                    )
                  : Text("Select Image")),
    );
  }
}

class MyOcr extends StatefulWidget {
  @override
  _MyOcr createState() => _MyOcr();
}

class _MyOcr extends State<MyOcr> {
  String _ocr = '';
  bool isLoading = false;

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    setState(() {
      isLoading = true;
      _ocr = '';
    });

    String ocr = '';
    // Platform messages may fail, so we use a try/catch.
    try {
      final result = await FilePicker.platform.pickFiles(allowMultiple: false);
      if (result != null) {
        if (result.paths[0] != null) {
          ocr = await WindowsOcr.getOcr(result.paths[0]!,
              language: Languages.English);
        }
      }
    } catch (error) {
      debugPrint('Error: $error');
    }

    setState(() {
      isLoading = false;
      _ocr = ocr;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          initPlatformState();
        },
        child: Icon(Icons.image),
      ),
      appBar: AppBar(
        title: const Text('OCR'),
      ),
      body: Center(
        child: isLoading ? CircularProgressIndicator() : Text('$_ocr'),
      ),
    );
  }
}

class MyMrz extends StatefulWidget {
  @override
  _MyMrz createState() => _MyMrz();
}

class _MyMrz extends State<MyMrz> {
  Mrz? _mrz;
  bool isLoading = false;

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    setState(() {
      isLoading = true;
    });

    Mrz? mrz;
    // Platform messages may fail, so we use a try/catch.
    try {
      final result = await FilePicker.platform.pickFiles(allowMultiple: false);
      if (result != null) {
        if (result.paths[0] != null) {
          mrz = await WindowsOcr.getMrz(result.paths[0]!);
        }
      }
    } catch (error) {
      debugPrint('Error: $error');
    }

    setState(() {
      isLoading = false;
      _mrz = mrz;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          initPlatformState();
        },
        child: Icon(Icons.image),
      ),
      appBar: AppBar(
        title: const Text('MRZ'),
      ),
      body: Center(
        child: isLoading
            ? CircularProgressIndicator()
            : _mrz != null
                ? Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: [
                      Text(_mrz!.lastName),
                      Text(_mrz!.name),
                      Text(_mrz!.docNumber)
                    ],
                  )
                : SizedBox(),
      ),
    );
  }
}
