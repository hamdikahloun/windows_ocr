import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:windows_ocr_example/main.dart';

void main() {
  testWidgets('Verify OCR result', (WidgetTester tester) async {
    await tester.pumpWidget(Home());
    expect(
      find.byWidgetPredicate(
        (Widget widget) =>
            widget is Text && (widget.data?.startsWith('Result :') ?? false),
      ),
      findsOneWidget,
    );
  });
}
