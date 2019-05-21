// STAR Prep Academy Electronics and Physics project for Walter Guevara and Luis Infante
// Created By Kirk Perkins
//MPU sample code provided by MIT
//Averaging done by Arduino
//We are number one created by LazyTown, notes provided by Dominik Zeman
//Megolovania produced by Toby Fox, notes provided by AnonymousAlly
/*
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
// Pins used: 
// Pin 3 = Buzzer    
// Pin 8 = Button
//Averaging is done
//data is saving
//time is running
#include<Wire.h> 
#include "SD.h" 
#include "SPI.h"
#include <MPU6050.h>
int ACCX,ACCY,ACCZ,GYRX,GYRY,GYRZ;
const int fn = 400;
const int hn = 200;
const int qn = 100;
const int f5 = 698;
const int c6 = 1047;
const int b5 = 988;
const int gh5 = 831;
const int ch6 = 1109;
const int dh6 = 1245;
int song[] = {
  f5,fn + hn,
  c6,hn,
  b5,qn,
  c6,qn,
  b5,qn,
  c6,qn,
  b5,hn,
  c6,hn,
  gh5,fn,
  f5,fn + hn,
  f5,hn,
  gh5,hn,
  c6,hn,
  ch6,fn,
  gh5,fn,
  ch6,fn,
  dh6,fn,
  c6,hn,
  ch6,hn,
  c6,hn,
  ch6,hn,
  c6,fn
  };
unsigned long int milli_time; 
MPU6050 MPU;
unsigned long lastSensorRead = 0; //what the last sensor reading was
unsigned long sensorReadInterval = 500; //interval between readings
float Gforce; //gforce 
byte speakerPin = 3; //define speaker pin
byte ledPin = 10; //define LEDpin
float refrenceTime; //timer reference to subtract
  //bool recording= false;
const int MPU_address=0x68; // I2C address of the MPU-6050
int32_t  AcX, AcY; //create gyro and accellerometer variables
byte ButtonPin = 8; //set button pin
//extern volatile unsigned long timer0_micros; //extract arduino clock and overide it to a variable
float timer;
const int CSpin = 12; //SD card pin
String dataString = ""; // holds the data to be written to the SD card
String labels = "";// labels for sensordata

bool timerisStarted= false;
bool buttonState; //boolean for state of the button
//float sensorReading3 = 0.00; // value read from your third sensor
File sensorData; //create SD file of sensor data
int flagger= 0; // flagging variable
float endingTime;
float referenceTime;

void setup() {
 // refrenceTime=timer;
  sensorData = SD.open("data.csv", FILE_WRITE); //open csv file
   pinMode(speakerPin, OUTPUT); //set spearker to output
   pinMode(ButtonPin, INPUT); //set button to input
   pinMode(ledPin, OUTPUT);
Wire.begin();
  Wire.setClock(400000L);
  MPU.initialize();
Serial.begin(115200);
Wire.beginTransmission(MPU_address);
Wire.write(0x1A);
Wire.write(0b00000000);
Wire.endTransmission(true);
Wire.beginTransmission(MPU_address);
Wire.write(0x24);
Wire.write(0b00001100);
Wire.endTransmission(true);
  
 // Serial.print("Initializing SD card...");
  pinMode(CSpin, OUTPUT);

  
  if (!SD.begin(CSpin)) {
   // Serial.println("Card failed, or not present");
    
  digitalWrite(ledPin, LOW);
     tone(speakerPin, 3000); //will make a tone  sd fail
     delay(50);
     tone(speakerPin,6000);
  noTone(speakerPin);
    return;
  }
  Serial.println("card initialized.");

 Serial.println("Creating CSV");
 

  if (SD.exists("data.csv")) { //check if the CSV file has been successfuly created, will make low high if success and high low if fail, it will also turn LED off if fail
tone(speakerPin,2000);
  delay(200);
  tone(speakerPin, 5000);
 noTone(speakerPin);
  } else {
  tone(speakerPin,5000);
  delay(200);
  tone(speakerPin, 2000);
  digitalWrite(ledPin, LOW);
 // noTone(speakerPin);
  }

  
    
  saveData(); // save to SD card



}

void CalculateAccel(){

  //Starts by creating a small averageing system
  if(micros() - lastSensorRead > sensorReadInterval){
  Wire.beginTransmission(MPU_address); //begin transmition
  Wire.write(0x3B); //Write a new address
  Wire.endTransmission(false); //true will send a stop message, releasing the bus after transmission. false will send a restart, keeping the connection active. 
  Wire.requestFrom(MPU_address,6,true); //create 6 addresses instead if 14 saving space
  ACCX=Wire.read()<<8|Wire.read(); //read on X
  ACCY=Wire.read()<<8|Wire.read(); //read on Y
  ACCZ=Wire.read()<<8|Wire.read(); //read on Z
  lastSensorRead += sensorReadInterval; //continue to the next reading

Gforce = ACCY/16384.0; //Convert accell to Gforce


Serial.println(Gforce); //print to Serial


}

}



 void justdoit() {
  //This is a forced overide to create a reference so that the timer starts over on button press.
  buttonState = digitalRead(ButtonPin);
  if(buttonState == LOW){

referenceTime=micros();

  }
   }
   
void loop() {







if (timerisStarted){
//Start timer if button is pressed
endingTime=micros()-referenceTime;
saveData(); //save data if timer has started

}
else{

  endingTime = 0;
}

//Gather readings from Accellerometer
CalculateAccel();


buttonState = digitalRead(ButtonPin);  //read buttonstate and change bool if changed

if (buttonState == LOW) { //if button is pressed, reset and begin reading
//Set reference time and start timer
refrenceTime=micros();
timerisStarted = !timerisStarted;
justdoit();
if(timerisStarted){
 tone(3,294,125);//D4
delay(125);
tone(3,294,125);//D4
delay(125);
tone(3,587,250);//D5
delay(250);
tone(3,440,250);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4

}
else{
  PlayMusic();
}
tone(speakerPin, 1000); // Send 1KHz sound signal...
 File sensorData = SD.open("data.csv", FILE_WRITE); //open CSV file

labels = String("RawData") +  "," + String("Gforce") + "," + String("time(micros)"); //print labels
 sensorData.println(labels); //save labels
 sensorData.close(); //close the file
 

  delay(250);        // ...for 1 sec
  noTone(speakerPin);
  



}




 
  delay(50); //short delay for stability
 





if(timerisStarted) {
dataString = String(ACCY) + "," + String(Gforce) + "," + String(endingTime); // convert to CSV


  

}
}
    
  



 void saveData() {
 
  if (SD.exists("data.csv")) { // check the card is still there
    // now append new data file
  File sensorData = SD.open("data.csv", FILE_WRITE);
    if (sensorData) { //if the sensorData exists

     digitalWrite(ledPin, HIGH);
      sensorData.println(dataString); //print data
      sensorData.close(); // close the file
    }
  }
  else {
 tone(speakerPin, 5000); //if SD file fail make a tone
 delay(20);
 noTone(speakerPin);
  }
 }


void PlayMusic(){
  for (int i = 0; i < (sizeof(song)/sizeof(int)); i = i + 2){
  tone(speakerPin, song[i]);
  delay(song[i + 1]);
  noTone(speakerPin);
}
}
  

 
