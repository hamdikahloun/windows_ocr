class Barcode {
  String value;
  String type;

  Barcode({this.value, this.type});

  Barcode.fromData(dynamic data) {
    this.value = data['value'];
    this.type = data['type'];
  }
}
