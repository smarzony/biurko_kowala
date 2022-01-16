#include <HCSR04.h>

#include <AccelStepper.h>
#include <MultiStepper.h>

// #include <ESP8266WiFi.h>
// #include <ESP8266mDNS.h>
// #include <WiFiUdp.h>
// #include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "smarzony"
#define STAPSK "metalisallwhatineed"
#endif

// #define BTN_UP D1
// #define BTN_DN D2
// #define LIMIT_DOWN D3
// #define LED D4

#define BTN_UP 4
#define BTN_DN 5
#define LIMIT_UP 6
#define LIMIT_DOWN 7
#define LED 13
#define PULSE_PIN 10
#define DIR_PIN 9
#define ENABLE_PIN 8
// #define TRIGGER_PIN 5
// #define ECHO_PIN 6
// #define DIST_MEASURE_PERIOD 500

#define MOTOR_ENABLED true

#define MOTOR_SPEED 400

#define CIRC_BUFFER_SIZE 5

const char *ssid = STASSID;
const char *password = STAPSK;


// UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN, 400.0, 2000);
// UltraSonicDistanceSensor distanceSensor(TRIGGER_PIN, ECHO_PIN);
AccelStepper stepper(AccelStepper::DRIVER, PULSE_PIN, DIR_PIN);

// unsigned long long now, last_dist_measure;
// float distance[CIRC_BUFFER_SIZE];
// float distance_current;
// float distance_avg;

// void circDist(float measure)
// {
//     float sum = 0.0;
//     for (uint8_t x = CIRC_BUFFER_SIZE - 1; x>0; x--)
//     {
//         distance[x] = distance[x-1];
//         sum = sum + distance[x];
//     }
//     distance[0] = measure;
//     distance_avg = sum / (CIRC_BUFFER_SIZE-1);
// }

void setup()
{
    Serial.begin(115200);
    delay(100);
    Serial.println("Booting");
    // ota();

    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DN, INPUT_PULLUP);
    pinMode(LIMIT_UP, INPUT_PULLUP);
    pinMode(LIMIT_DOWN, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);

    stepper.setMaxSpeed(4000);
    stepper.setAcceleration(100);

}

void loop()
{
    // now = millis();
    // ArduinoOTA.handle();
    // if (now - last_dist_measure > DIST_MEASURE_PERIOD)
    // {
    //     last_dist_measure = now;
    //     distance_current = distanceSensor.measureDistanceCm(22.0);
    //     circDist(distance_current);
    //     Serial.print(distance_current);
    //     Serial.print(" cm, avg ");
    //     Serial.print(distance_avg);
    //     Serial.println(" cm");
    // }
    // if (!digitalRead(BTN_UP) && distance_avg < 50.0)
    if (!digitalRead(BTN_UP) &&  digitalRead(LIMIT_UP))
    {
        digitalWrite(ENABLE_PIN, MOTOR_ENABLED);
        stepper.setSpeed(MOTOR_SPEED);
        stepper.runSpeed();
        // stepper.run();
        digitalWrite(LED, HIGH);
        Serial.println("FWD");
    }

    else if (!digitalRead(BTN_DN) && digitalRead(LIMIT_DOWN))
    {
        digitalWrite(ENABLE_PIN, MOTOR_ENABLED);
        stepper.setSpeed(-MOTOR_SPEED);
        stepper.runSpeed();
        digitalWrite(LED, HIGH);
        Serial.println("BWD");
    }

    else
    {
        stepper.stop();
        digitalWrite(ENABLE_PIN, !MOTOR_ENABLED);
        digitalWrite(LED, LOW);
        // Serial.println("STP");
    }
    // if (stepped == false)
    //     Serial.println(stepped);
    // else
    // {
    //     Serial.println();
    // }
    
}
