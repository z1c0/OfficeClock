#include "Wire.h"
#include "LedMatrixObject.h"

#define DS3231_I2C_ADDRESS 0x68
#define PIR_PIN 12

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  // set the initial time here:
  // DS3231 seconds, minutes, hours, day (1.. sunday, 7 .. saturday), date, month, year
  //setDS3231time(0, 31, 20, 6, 22, 1, 16);

  pinMode(PIR_PIN, INPUT);
  digitalWrite(PIR_PIN, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < 25; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("SENSOR ACTIVE");
}
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute < 10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second < 10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch (dayOfWeek) {
    case 1:
      Serial.println("Sunday");
      break;
    case 2:
      Serial.println("Monday");
      break;
    case 3:
      Serial.println("Tuesday");
      break;
    case 4:
      Serial.println("Wednesday");
      break;
    case 5:
      Serial.println("Thursday");
      break;
    case 6:
      Serial.println("Friday");
      break;
    case 7:
      Serial.println("Saturday");
      break;
  }
}


LedMatrixObject led(2, 3, 4, 5, 6, 7, 8, 9);

unsigned char Scene[16][16] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
const unsigned char Zero[7][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
};
const unsigned char One[7][5] = {
  {1, 1, 1, 0, 1},
  {1, 1, 0, 0, 1},
  {1, 1, 1, 0, 1},
  {1, 1, 1, 0, 1},
  {1, 1, 1, 0, 1},
  {1, 1, 1, 0, 1},
  {1, 1, 1, 0, 1},
};
const unsigned char Two[7][5] = {
  {0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1},
  {0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0},
};
const unsigned char Three[7][5] = {
  {0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
};
const unsigned char Four[7][5] = {
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0},
};
const unsigned char Five[7][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1},
  {0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
};
const unsigned char Six[7][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1},
  {0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
};
const unsigned char Seven[7][5] = {
  {0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 0, 1},
  {1, 1, 0, 1, 1},
  {1, 1, 0, 1, 1},
  {1, 1, 0, 1, 1},
};
const unsigned char Eight[7][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
};
const unsigned char Nine[7][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0},
};

void drawDigit(int digit, int offsetX, int offsetY)
{
  const unsigned char (*pDigit)[5];
  switch (digit)
  {
    case 0:
      pDigit = Zero;
      break;
    case 1:
      pDigit = One;
      break;
    case 2:
      pDigit = Two;
      break;
    case 3:
      pDigit = Three;
      break;
    case 4:
      pDigit = Four;
      break;
    case 5:
      pDigit = Five;
      break;
    case 6:
      pDigit = Six;
      break;
    case 7:
      pDigit = Seven;
      break;
    case 8:
      pDigit = Eight;
      break;
    case 9:
      pDigit = Nine;
      break;
  }

  for (int x = 0; x < 5; x++)
  {
    for (int y = 0; y <  7; y++)
    {
      Scene[offsetY + y][offsetX + x] = pDigit[y][x];
    }
  }
}

unsigned long lastMillis = 0;
unsigned long lastMotion = 0;
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

void loop()
{
  unsigned long millisNow = millis();
  bool show = false;

  if (digitalRead(PIR_PIN) == HIGH)
  {
    //Serial.println("motion");
    lastMotion = millisNow;
    show = true;
  }

  #define MOTION_TIMEOUT (1000 * 20)
  if (millisNow - lastMotion <= MOTION_TIMEOUT)
  {
    if (show || millisNow - lastMillis >= 60 * 1000) // only check once a minute
    {
      //displayTime(); // display the real-time clock data on the Serial Monitor,
      readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
      lastMillis = millisNow;
      show = false;
    }

    drawDigit(hour / 10, 2, 0);
    drawDigit(hour % 10, 9, 0);

    drawDigit(minute / 10,  2, 9);
    drawDigit(minute % 10,  9, 9);

    led.setScene(Scene);
    led.draw();
  }
  else
  {
    //Serial.println("timeout");
  }
}
