
#define ERROR_BLE_BEGIN 1
#define ERROR_BLE_RESET 2
#define ERROR_BLE_NAME 3

void errorState(int errorNum)
{
  static bool flashDigits = true;
  while (1)
  {
    if(flashDigits)
    {
      clearAllSegments(&T1_1,true);
      clearAllSegments(&T1_1,false);
      clearAllSegments(&T1_2,true);
      clearAllSegments(&T1_2,false);
      clearAllSegments(&T2_1,true);
      clearAllSegments(&T2_1,false);
      clearAllSegments(&T2_2,true);
      clearAllSegments(&T2_2,false);
    }
    else
    {
      writeDigitValue(errorNum, &T1_1);
      writeDigitValue(errorNum, &T1_2);
      writeDigitValue(errorNum, &T2_1);
      writeDigitValue(errorNum, &T2_2);
    }
    digitalWrite(13, !digitalRead(13));
    delay(100);
  }
}
