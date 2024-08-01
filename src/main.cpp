#define DEBUG 0

// Define the baudrate for the serial communication
#define BAUDRATE 9600

#define DEBUG_SERIAL Serial
#define PC_SERIAL Serial2
// Define the score for each sensor
#define SENSOR_1_SCORE 5
#define SENSOR_2_SCORE 10
#define SENSOR_3_SCORE 15
#define SENSOR_4_SCORE 20
#define SENSOR_5_SCORE 25
#define SENSOR_6_SCORE 30

// Define the pins for the sensors and the switch
#define SENSOR_1 34
#define SENSOR_2 35
#define SENSOR_3 32
#define SENSOR_4 33
#define SENSOR_5 25
#define SENSOR_6 26

#define SWITCH_PIN 27

// Include the Arduino library
#include <Arduino.h>

// Global variables to store the state of the sensors

bool sensor1Triggered = false;
bool sensor2Triggered = false;
bool sensor3Triggered = false;
bool sensor4Triggered = false;
bool sensor5Triggered = false;
bool sensor6Triggered = false;

// Global variables to store the state of the game
bool gameStarted = false;
// Global variable to store the score
uint16_t score = 0;

// Global variables for the switch debounce
unsigned long debounceDelay = 1000; // debounce delay in milliseconds
unsigned long lastSwitchTime = 0; // variable to store the last switch time

// Function to handle the game logic
void gameRunning (){
    // Check if the sensor is triggered and add the score to the total score
    if (digitalRead(SENSOR_1) == LOW && !sensor1Triggered) {
        score = score + SENSOR_1_SCORE;
        if (DEBUG) {DEBUG_SERIAL.println(score);}
        PC_SERIAL.println(score);
        if (DEBUG) { DEBUG_SERIAL.println("Sensor 1");}
        sensor1Triggered = true;
    } else if (digitalRead(SENSOR_1) == HIGH && sensor1Triggered) { // Reset the sensor state
        sensor1Triggered = false;
    }

    if (digitalRead(SENSOR_2) == LOW && !sensor2Triggered) {
        score = score + SENSOR_2_SCORE;
        if (DEBUG) {DEBUG_SERIAL.println(score);}
        PC_SERIAL.println(score);
        if (DEBUG) { DEBUG_SERIAL.println("Sensor 2");}
        sensor2Triggered = true;
    } else if (digitalRead(SENSOR_2) == HIGH && sensor2Triggered) {
        sensor2Triggered = false;
    }

    if (digitalRead(SENSOR_3) == LOW && !sensor3Triggered) {
        score = score + SENSOR_3_SCORE;
        if (DEBUG) {DEBUG_SERIAL.println(score);}
        PC_SERIAL.println(score);
        if (DEBUG) { DEBUG_SERIAL.println("Sensor 3");}
        sensor3Triggered = true;
    } else if (digitalRead(SENSOR_3) == HIGH && sensor3Triggered) {
        sensor3Triggered = false;
    }

    if (digitalRead(SENSOR_4) == LOW && !sensor4Triggered) {
        score = score + SENSOR_4_SCORE;
        if (DEBUG) {DEBUG_SERIAL.println(score);}
        PC_SERIAL.println(score);
        if (DEBUG) { DEBUG_SERIAL.println("Sensor 4");}
        sensor4Triggered = true;
    } else if (digitalRead(SENSOR_4) == HIGH && sensor4Triggered) {
        sensor4Triggered = false;
    }

    if (digitalRead(SENSOR_5) == LOW && !sensor5Triggered) {
        score = score + SENSOR_5_SCORE;
        if (DEBUG) {DEBUG_SERIAL.println(score);}
        PC_SERIAL.println(score);
        if (DEBUG) { DEBUG_SERIAL.println("Sensor 5");}
        sensor5Triggered = true;
    } else if (digitalRead(SENSOR_5) == HIGH && sensor5Triggered) {
        sensor5Triggered = false;
    }

    if (digitalRead(SENSOR_6) == LOW && !sensor6Triggered) {
        score = score + SENSOR_6_SCORE;
        if (DEBUG) {DEBUG_SERIAL.println(score);}
        PC_SERIAL.println(score);
        if (DEBUG) { DEBUG_SERIAL.println("Sensor 6");}
        sensor6Triggered = true;
    } else if (digitalRead(SENSOR_6) == HIGH && sensor6Triggered) {
        sensor6Triggered = false;
    }
}

// Function to reset the game
void gameReset() {
    gameStarted = false;
    DEBUG_SERIAL.println(score);
    PC_SERIAL.println(score);
    score = 0;
    if (DEBUG) { DEBUG_SERIAL.println("GAME RESET");}
}

// Function to start and stop the game.
void gameHandler() {
    if (gameStarted) {
        gameRunning();
    }

    if (digitalRead(SWITCH_PIN) == LOW && (millis() - lastSwitchTime) > debounceDelay) { // check if the Reset switch is pressed
        gameReset();
        lastSwitchTime = millis(); // update the last switch time
    }
}
// Function to read the serial input
void readSerial() {
    if (PC_SERIAL.available() > 0) {
        String data = PC_SERIAL.readString();
        data.trim(); 
        if (DEBUG) { DEBUG_SERIAL.println(data); }
        if (data == "S") { gameStarted = true; if (DEBUG) { DEBUG_SERIAL.println("GAME STARTED");} } // Start the game
        if (data == "Z") { gameReset();}    // Reset the game
    }
}

void setup() {
    Serial.begin(BAUDRATE); // Start the serial communication
    // Set the pins for the sensors and the switch
    pinMode(SENSOR_1, INPUT_PULLUP);
    pinMode(SENSOR_2, INPUT_PULLUP);
    pinMode(SENSOR_3, INPUT_PULLUP);
    pinMode(SENSOR_4, INPUT_PULLUP);
    pinMode(SENSOR_5, INPUT_PULLUP);
    pinMode(SENSOR_6, INPUT_PULLUP);

    pinMode(SWITCH_PIN, INPUT_PULLUP); // Set the switch pin as input

    if (DEBUG) { DEBUG_SERIAL.println("ENTER 'S' TO START!!");} // Print the message to start the game
}

void loop() {
    // Call the functions to read the serial input and handle the game logic
    readSerial();
    gameHandler();
}