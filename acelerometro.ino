#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define MPU 0x68
#define MPU2 0x69
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define OLED_address  0x3c 

float A_R = 16384;
float G_R = 131.0;
float RAD_A_DEG = 57.29577951;

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
//Angulos
float Acc[3];
float Gy[3];
float Angle[3];

float AngulosX;
float AngulosY;
float AngulosZ;

void setup(){
  Wire.begin();
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  
  display.clearDisplay();
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
}

void loop() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);
  AcX = Wire.read()<<8|Wire.read();
  AcY = Wire.read()<<8|Wire.read();
  AcZ = Wire.read()<<8|Wire.read();

//Acelerometro
  Acc[0] = acos((AcX/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcY/A_R),2)+ pow((AcZ/A_R),2)))*RAD_A_DEG;
  Acc[1] = acos((AcY/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcY/A_R),2)+ pow((AcZ/A_R),2)))*RAD_A_DEG;
  Acc[2] = acos((AcZ/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcY/A_R),2)+ pow((AcZ/A_R),2)))*RAD_A_DEG;

//Giroscopio
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);
  GyX = Wire.read()<<8|Wire.read();
  GyY = Wire.read()<<8|Wire.read();
  GyZ = Wire.read()<<8|Wire.read();
  //Calculo
  Gy[0] = GyX/G_R;
  Gy[1] = GyY/G_R;
  Gy[2] = GyZ/G_R;
  //Filtro Complementario
  Angle[0] = 0.98 * (Angle[0]+Gy[0]*0.010) + 0.02*Acc[0];
  Angle[1] = 0.98 * (Angle[1]+Gy[1]*0.010)+ 0.02*Acc[1];
  Angle[2] = 0.98 * (Angle[2]+Gy[2]*0.010) + 0.02*Acc[2];

  AngulosX = Angle[0];
  AngulosY = Angle[1];
  AngulosZ = Angle[2];

  display.display();
  display.clearDisplay();   // clears the screen and buffer 

  Serial.println(String(AngulosX)+ String ("  ") + String(AngulosY)+ String("  ")+ String(AngulosZ));

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  //Display ACC
  display.print("X: ");
  display.println(AngulosX);
  display.print("Y: ");
  display.println(AngulosY);
  display.print("Z: ");
  display.println(AngulosZ);
  delay(33);
}
