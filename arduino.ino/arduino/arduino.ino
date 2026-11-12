#include <Arduino.h>
#include <time.h>

#define MAX_ELAPSED_TIME (1000) //ms
unsigned long last_check;
unsigned long StartTime;
//socket 
void setup() {


Serial.begin(9600);
unsigned long StartTime = millis();
Serial.println("Starttime: %ul\nprogram has format: <data>: at <elapsed time>");
Serial.println(StartTime);
}


void loop() {

unsigned long elapsed = millis() - StartTime;

signed long vibration_sensor_data = 0;

signed long Delta_time = millis() - last_check;

if (Delta_time >= MAX_ELAPSED_TIME) {

Serial.print(vibration_sensor_data);
Serial.println(": at");
Serial.print(elapsed);

Serial.print(" DT:");
Serial.println(Delta_time);

last_check = millis();

} 


}
