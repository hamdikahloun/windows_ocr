import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:windows_ocr/windows_ocr.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  test('getOcr', () async {
    expect(await WindowsOcr.getOcr('ocr.png'), '');
  });
}
