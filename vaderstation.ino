#include <Adafruit_SCD30.h>

// Basic demo for readings from Adafruit SCD30
Adafruit_SCD30  scd30;

// Connect the MEMS AUD output to the Arduino A0 pin
int mic = A0;

// Variable to hold analog values from mic
int micOut;


void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit SCD30 test!");

  // Try to initialize!
  if (!scd30.begin()) {
    Serial.println("Failed to find SCD30 chip");
    while (1) { delay(10); }
  }
  Serial.println("SCD30 Found!");


  if (!scd30.setMeasurementInterval(20)){
     Serial.println("Failed to set measurement interval");
     while(1){ delay(10);}
   }
//  Serial.print("Measurement Interval: "); 
//  Serial.print(scd30.getMeasurementInterval()); 
//  Serial.println(" seconds");
}

void loop() {
  // 1.6V ungefär 600 i värde, : 5 volts / 1024 
  // read the input on analog pin 0:
  micOut = analogRead(mic);

  // print out the value you read:
  
  if (scd30.dataReady()){
    Serial.println("Data available!");
    Serial.print("Sound: ");
    //omvandla till V, genom formel
    Serial.print(micOut/(1024.0/3.3));
    Serial.println(" V ");
//    Serial.print(", ");
//    Serial.println(micOut);
    if (!scd30.read()){ Serial.println("Error reading sensor data"); return; }

    Serial.print("Temperature: ");
    Serial.print(scd30.temperature);
    Serial.println(" degrees C");
    
 //   Serial.print("Relative Humidity: ");
 //   Serial.print(scd30.relative_humidity);
 //   Serial.println(" %");
      
    Serial.print("CO2: ");
    Serial.print(scd30.CO2, 3);
    Serial.println(" ppm");
    Serial.println("");
  } else {
    //Serial.println("No data");
  }

  delay(100);
}
