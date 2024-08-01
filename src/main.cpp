#define DEBUG 0

#define BAUDRATE 9600

#define SENSOR_1_SCORE 10
#define SENSOR_2_SCORE 20
#define SENSOR_3_SCORE 30
#define SENSOR_4_SCORE 40
#define SENSOR_5_SCORE 50
#define SENSOR_6_SCORE 60


#define SENSOR_1 34
#define SENSOR_2 35
#define SENSOR_3 32
#define SENSOR_4 33
#define SENSOR_5 25
#define SENSOR_6 26

#define SWITCH_PIN 27

#include <Arduino.h>

bool sensor1Triggered = false;
bool sensor2Triggered = false;
bool sensor3Triggered = false;
bool sensor4Triggered = false;
bool sensor5Triggered = false;
bool sensor6Triggered = false;


bool gameStarted = false;
uint16_t score = 0;


void gameRunning (){

    if (digitalRead(SENSOR_1) == LOW && !sensor1Triggered) {
        score = score + SENSOR_1_SCORE;
        Serial.println(score);
        if (DEBUG) { Serial.println("Sensor 1");}
        sensor1Triggered = true;
    } else if (digitalRead(SENSOR_1) == HIGH && sensor1Triggered) {
        sensor1Triggered = false;
    }

    if (digitalRead(SENSOR_2) == LOW && !sensor2Triggered) {
        score = score + SENSOR_2_SCORE;
        Serial.println(score);
        if (DEBUG) { Serial.println("Sensor 2");}
        sensor2Triggered = true;
    } else if (digitalRead(SENSOR_2) == HIGH && sensor2Triggered) {
        sensor2Triggered = false;
    }

    if (digitalRead(SENSOR_3) == LOW && !sensor3Triggered) {
        score = score + SENSOR_3_SCORE;
        Serial.println(score);
        if (DEBUG) { Serial.println("Sensor 3");}
        sensor3Triggered = true;
    } else if (digitalRead(SENSOR_3) == HIGH && sensor3Triggered) {
        sensor3Triggered = false;
    }

    if (digitalRead(SENSOR_4) == LOW && !sensor4Triggered) {
        score = score + SENSOR_4_SCORE;
        Serial.println(score);
        if (DEBUG) { Serial.println("Sensor 4");}
        sensor4Triggered = true;
    } else if (digitalRead(SENSOR_4) == HIGH && sensor4Triggered) {
        sensor4Triggered = false;
    }

    if (digitalRead(SENSOR_5) == LOW && !sensor5Triggered) {
        score = score + SENSOR_5_SCORE;
        Serial.println(score);
        if (DEBUG) { Serial.println("Sensor 5");}
        sensor5Triggered = true;
    } else if (digitalRead(SENSOR_5) == HIGH && sensor5Triggered) {
        sensor5Triggered = false;
    }

    if (digitalRead(SENSOR_6) == LOW && !sensor6Triggered) {
        score = score + SENSOR_6_SCORE;
        Serial.println(score);
        if (DEBUG) { Serial.println("Sensor 6");}
        sensor6Triggered = true;
    } else if (digitalRead(SENSOR_6) == HIGH && sensor6Triggered) {
        sensor6Triggered = false;
    }

}

void gameReset() {
    gameStarted = false;
    Serial.println(score);
    score = 0;
    if (DEBUG) { Serial.println("GAME RESET");}
}

unsigned long debounceDelay = 1000; // debounce delay in milliseconds
unsigned long lastSwitchTime = 0; // variable to store the last switch time

void gameHandler() {
    if (gameStarted) {
        gameRunning();
    }

    if (digitalRead(SWITCH_PIN) == LOW && (millis() - lastSwitchTime) > debounceDelay) {
        gameReset();
        lastSwitchTime = millis(); // update the last switch time
    }
}

void readSerial() {
    if (Serial.available() > 0) {
        String data = Serial.readString();
        data.trim();
        if (DEBUG) { Serial.println(data); }
        if (data == "S") { gameStarted = true; if (DEBUG) { Serial.println("GAME STARTED");} }
        if (data == "Z") { gameReset();} 
    }
}

void setup() {
    Serial.begin(BAUDRATE);
    pinMode(SENSOR_1, INPUT_PULLUP);
    pinMode(SENSOR_2, INPUT_PULLUP);
    pinMode(SENSOR_3, INPUT_PULLUP);
    pinMode(SENSOR_4, INPUT_PULLUP);
    pinMode(SENSOR_5, INPUT_PULLUP);
    pinMode(SENSOR_6, INPUT_PULLUP);

    pinMode(SWITCH_PIN, INPUT_PULLUP);

    if (DEBUG) { Serial.println("ENTER 'S' TO START!!");}
    
}

void loop() {
    readSerial();
    gameHandler();
}

