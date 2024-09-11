#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Panasonic.h>

const uint16_t kIrLed = 4; 
IRPanasonicAc ac(kIrLed); 

void printState() {
  // Display the settings.
  Serial.println("Panasonic A/C remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
  // Display the encoded IR sequence.
  unsigned char* ir_code = ac.getRaw();
  Serial.print("IR Code: 0x");
  for (uint8_t i = 0; i < kPanasonicAcStateLength; i++)
    Serial.printf("%02X", ir_code[i]);
  Serial.println();
}

void setup() {
  ac.begin();
  Serial.begin(115200);
  delay(200);

  // Turn on the AC and set temperature to 20°C
  Serial.println("Turning on AC and setting temperature to 20°C.");
  ac.setModel(kPanasonicRkr);
  ac.on();
  ac.setFan(kPanasonicAcFanAuto);
  ac.setMode(kPanasonicAcCool);
  ac.setTemp(20);
  ac.setSwingVertical(kPanasonicAcSwingVAuto);
  ac.setSwingHorizontal(kPanasonicAcSwingHAuto);
  ac.send();  // Send the command to turn on the AC and set it to 20°C
  printState();
  delay(5000);  // Wait for 5 seconds

  // Set temperature to 24°C
  Serial.println("Setting temperature to 24°C.");
  ac.setTemp(24);
  ac.send();  // Send the command to change the temperature to 24°C
  printState();
  delay(5000);  // Wait for another 5 seconds

  //Set temperature to 22
  Serial.println("Setting temperature to 22°C.");
  ac.setTemp(22);
  ac.send();  // Send the command to change the temperature to 24°C
  printState();
  delay(5000);  // Wait for another 5 seconds

  // Turn off the AC
  Serial.println("Turning off the AC.");
  ac.off();
  ac.send();  // Send the command to turn off the AC
  printState();
}

void loop() {
  // Nothing to do in the loop
}
