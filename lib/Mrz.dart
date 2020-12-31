class Mrz {
  String linesCnt;
  String docType;
  String docSubType;
  String country;
  String lastName;
  String name;
  String docNumber;
  String nationality;
  String birthDate;
  String expDate;
  String sex;
  String personalNumber;
  String optionalData1;
  String optionalData2;
  String docNumCheck;
  String docNumberVerified;
  String birthDateCheck;
  String birthDateVerified;
  String expDateCheck;
  String expDateVerified;
  String personalNumberCheck;
  String personalNumberVerified;
  String compositeCheck;
  String compositeVerified;

  Mrz(
      {this.linesCnt,
        this.docType,
        this.docSubType,
        this.country,
        this.lastName,
        this.name,
        this.docNumber,
        this.nationality,
        this.birthDate,
        this.expDate,
        this.sex,
        this.personalNumber,
        this.optionalData1,
        this.optionalData2,
        this.docNumCheck,
        this.docNumberVerified,
        this.birthDateCheck,
        this.birthDateVerified,
        this.expDateCheck,
        this.expDateVerified,
        this.personalNumberCheck,
        this.personalNumberVerified,
        this.compositeCheck,
        this.compositeVerified});

  Mrz.fromData(dynamic data) {
    linesCnt = data['LinesCnt'];
    docType = data['DocType'];
    docSubType = data['DocSubType'];
    country = data['Country'];
    lastName = data['LastName'];
    name = data['Name'];
    docNumber = data['DocNumber'];
    nationality = data['Nationality'];
    birthDate = data['BirthDate'];
    expDate = data['ExpDate'];
    sex = data['Sex'];
    personalNumber = data['PersonalNumber'];
    optionalData1 = data['OptionalData1'];
    optionalData2 = data['OptionalData2'];
    docNumCheck = data['DocNumCheck'];
    docNumberVerified = data['DocNumberVerified'];
    birthDateCheck = data['BirthDateCheck'];
    birthDateVerified = data['BirthDateVerified'];
    expDateCheck = data['ExpDateCheck'];
    expDateVerified = data['ExpDateVerified'];
    personalNumberCheck = data['PersonalNumberCheck'];
    personalNumberVerified = data['PersonalNumberVerified'];
    compositeCheck = data['CompositeCheck'];
    compositeVerified = data['CompositeVerified'];
  }
}