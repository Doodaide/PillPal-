//Libraries 
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>


//defining stuff

//screen
#define TFT_DC 4 //correct 
#define TFT_CS 5 //do not change
#define TFT_CLK 18 //do not change
#define TFT_MOSI 23 //do not change
#define TFT_MISO 19 // do not change
#define TFT_RST 2 

//servo pulses
#define SERVOMIN  150 
#define SERVOMAX  600




//RFID
#define SS_PIN 15
#define RST_PIN 34

//initiating all of the components
MFRC522 mfrc522(SS_PIN, RST_PIN); 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//compartments and their associated servos
uint8_t comp1 = 0;
uint8_t comp2 = 1;
uint8_t comp3 = 2;
uint8_t comp4 = 3;
uint8_t comp5 = 4;
uint8_t comp6 = 5;

//FOR THE BUZZER
int freq = 2000;
int channel = 0;
int resolution = 8;

//counters
int alanac = 0;
int alicec = 0;
int anishc = 0;
//setup
void setup() {
 
  Serial.begin(115200);   // Initiate a serial communication
  
  //SPI
  SPI.begin();      // Initiate  SPI bus

  //RFID
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  //screen
  tft.begin();
  tft.setRotation(3);

  //PWM module
  pwm.begin();
  pwm.setPWMFreq(60); 

  //clears screen
  tft.fillScreen(ILI9341_BLACK);
  //begins with the home screen function
  homeScreen();
  // buzzer
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(26, channel);
 
}

//this function sets up the I2C component and the pulses the servos will rotate at
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;

  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength);
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); 
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}



//function to call upon when a new function begins (like a clear screen)
void reload(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
}




void boop(){
  reload();
  tft.setCursor(110, 100);
  tft.println("Scanning...");
  ledcWriteTone(channel, freq);
  delay(500);
  ledcWriteTone(channel, 0);
  delay(500);
  reload();
}

//the main screen with (Hi I'm pillpal)
void homeScreen(){
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5);
  tft.setCursor(0,3);
  tft.println(" HI I'M    PILL-PAL");
  tft.setTextSize(3);
  tft.setCursor(0,90);
  tft.println("Please tap your  card");
}




//function for Alex(individual)
void Alex(){
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5);
  tft.setCursor(0,3);
  tft.println(" Hi Alex");
  tft.setTextSize(3);
  tft.setCursor(0,90);
  tft.println("Today, your pills are from        compartments:");
  tft.setCursor(0,170);
  tft.println("1 2 3 4 5 6");
  anishc = 0;
  alicec = 0;
  alanac = 0;

    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(comp1, 0, pulselen);
      pwm.setPWM(comp2, 0, pulselen);
      pwm.setPWM(comp3, 0, pulselen);
      pwm.setPWM(comp4, 0, pulselen);
      pwm.setPWM(comp5, 0, pulselen);
      pwm.setPWM(comp6, 0, pulselen);
    }
    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(comp1, 0, pulselen);
      pwm.setPWM(comp2, 0, pulselen);
      pwm.setPWM(comp3, 0, pulselen);
      pwm.setPWM(comp4, 0, pulselen);
      pwm.setPWM(comp5, 0, pulselen);
      pwm.setPWM(comp6, 0, pulselen);
    }
    delay(1000);
}

//function for Anish
void Anish(){
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(5);
  tft.setCursor(0,3);
  tft.println(" Hi Anish");
  tft.setTextSize(3);
  tft.setCursor(0,90);
  tft.println("Today, your pills are from        compartments:");
  tft.setCursor(0,160);
  tft.println("3 and 6");
   for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(comp3, 0, pulselen);
      pwm.setPWM(comp6, 0, pulselen);
    }
    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(comp3, 0, pulselen);
      pwm.setPWM(comp6, 0, pulselen);
    }
    delay(700);
}

//function for Alana
void Alana(){
  tft.setTextColor(ILI9341_PURPLE);
  tft.setTextSize(5);
  tft.setCursor(0,3);
  tft.println(" Hi Alana");
  tft.setTextSize(3);
  tft.setCursor(0,90);
  tft.println("Today, you get   pills    from tubes");
  tft.setCursor(0,140);
  tft.println(" 2, 5, and one  from tube 4 ");
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(comp2, 0, pulselen);
      pwm.setPWM(comp5, 0, pulselen);
      pwm.setPWM(comp4, 0, pulselen);
    }
    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(comp2, 0, pulselen);
      pwm.setPWM(comp5, 0, pulselen);
      pwm.setPWM(comp4, 0, pulselen); 
    }
    delay(500);

    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(comp2, 0, pulselen);
      pwm.setPWM(comp5, 0, pulselen);

    }
    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(comp2, 0, pulselen);
      pwm.setPWM(comp5, 0, pulselen);

    }
    delay(700);
}

//function for Alice(WIP)
void Alice(){
  tft.setTextColor(ILI9341_PINK);
  tft.setTextSize(5);
  tft.setCursor(0,3);
  tft.println(" Hi Alice");
  tft.setTextSize(3);
  tft.setCursor(0,90);
  tft.println("Today, your pills are from        compartments:");
  tft.setCursor(0,160);
  tft.println("4, 5 and 6");
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(comp4, 0, pulselen);
      pwm.setPWM(comp5, 0, pulselen);
      pwm.setPWM(comp6, 0, pulselen);
    }
    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
      pwm.setPWM(comp4, 0, pulselen);
      pwm.setPWM(comp5, 0, pulselen);
      pwm.setPWM(comp6, 0, pulselen);
    }
    delay(1000);
  }



//the loop and RFID 
void loop() {
// Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();


  // ^ everything above was to scan the RFID

  //Alex's debugging and mastercard
  if (content.substring(1) == "B7 1A F0 2B"){
  reload();
  boop();
  Alex();
  tft.setCursor(0,200);
  tft.println(content.substring(1));
  delay(1000);
  reload();
  homeScreen();
  }
  //End of master card function



  //Anish's function
  if (content.substring(1) == "2C 43 F0 2B"){
    reload();
    boop();
     anishc = anishc+1;
  if(anishc == 1){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Anish has taken his first  round of Pills");
  Anish();
  tft.setCursor(0,200);
  delay(2000); 
  reload();
  }
  if(anishc == 2){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Anish has taken his second  round of Pills");
  Anish();
  delay(2000); 
  reload();
  }
  if(anishc == 3){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Anish has taken his third  round of Pills");
  Anish();
  delay(2000); 
  reload();
  }
  if(anishc > 3){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Anish has had enough Pills");    
  }
  homeScreen();
  delay(2000);

  }
  //end of Anish Function

  //beginning of Alana function
  if (content.substring(1) == "15 3A B4 79"){
    reload();
    boop();
    alanac = alanac+1;
  if(alanac == 1){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Alana has taken her first  round of Pills");
  Alana();
  tft.setCursor(0,200);
  delay(2000); 
  reload();
  }
  if(alanac > 1){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Alana has had enough Pills");    
  }
  homeScreen();
  
  
    delay(2000);
    reload();
    homeScreen();

  }
  //end of Alana function

  //Beginning of Alice function
  if (content.substring(1) == "A1 DA B5 79"){
    reload();
    boop();
    alicec = alicec+1;
  if(alicec == 1){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Alice has taken her first  round of Pills");
  Alice();
  tft.setCursor(0,200);
  delay(2000); 
  reload();
  }
  if(alicec == 2){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Alice has taken her second  round of Pills");
  Alice();
  delay(2000); 
  reload();
  }
  if(alicec > 2){
  tft.setTextSize(2);
  tft.setCursor(0, 190);
  tft.println("Alice has had enough Pills");    
  }
  homeScreen();
  
  
    delay(2000);


  }
  //end of Alice function
else {

  homeScreen();
}


}
