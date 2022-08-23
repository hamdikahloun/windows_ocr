import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:windows_ocr_example/main.dart' as app;

void main() {
  //run(_testMain);
}

void _testMain() {
  testWidgets('Counter increments smoke test', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    app.main();

    // Trigger a frame.
    await tester.pumpAndSettle();

    // Verify that platform version is retrieved.
    expect(
      find.byWidgetPredicate(
        (Widget widget) =>
            widget is Text && (widget.data?.startsWith('Running on:') ?? false),
      ),
      findsOneWidget,
    );
  });
}
