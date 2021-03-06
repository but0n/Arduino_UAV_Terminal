//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//
//  >>  Mac_tty_Motor_Controller.no
//  >>  Created by Jack.
//  >>  Copyright <c> Jack
//
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
#include <stdio.h>
#define NONE          Serial.print("\033[m")
#define RED           Serial.print("\033[0;32;31m")
#define LIGHT_RED     Serial.print("\033[1;31m")
#define GREEN         Serial.print("\033[0;32;32m")
#define LIGHT_GREEN   Serial.print("\033[1;32m")
#define BLUE          Serial.print("\033[0;32;34m")
#define LIGHT_BLUE    Serial.print("\033[1;34m")
#define DARY_GRAY     Serial.print("\033[1;30m")
#define CYAN          Serial.print("\033[0;36m")
#define LIGHT_CYAN    Serial.print("\033[1;36m")
#define PURPLE        Serial.print("\033[0;35m")
#define LIGHT_PURPLE  Serial.print("\033[1;35m")
#define BROWN         Serial.print("\033[0;33m")
#define YELLOW        Serial.print("\033[1;33m")
#define LIGHT_GRAY    Serial.print("\033[0;37m")
#define WHITE         Serial.print("\033[1;37m")

#define COLORRTN    Serial.print("\33[7m")
#define CLEAR       Serial.print("\33[2J")
#define UNDERLINE   Serial.print("\33[4m")
#define FLASH       Serial.print("\33[5m")
#define OPTOFF      Serial.print("\33[0m")

#define LEFT_1  3
#define LEFT_2  0
#define LEFT_3  0
#define RIGHT_1 9
#define RIGHT_2 0
#define RIGHT_3 0

uint8_t left1 = 0;
uint8_t left2 = 0;
uint8_t left3 = 0;
uint8_t right1 = 0;
uint8_t right2 = 0;
uint8_t right3 = 0;
void pregister();
void updatePWM();
void setup() {
    if (LEFT_1) pinMode(LEFT_1, OUTPUT);
    if (LEFT_2) pinMode(LEFT_2, OUTPUT);
    if (LEFT_3) pinMode(LEFT_3, OUTPUT);

    if (RIGHT_1) pinMode(RIGHT_1, OUTPUT);
    if (RIGHT_2) pinMode(RIGHT_2, OUTPUT);
    if (RIGHT_3) pinMode(RIGHT_3, OUTPUT);

    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
}
int bash = 0;

void loop() {
    // for(int coun=0; coun<255; coun++){
    //     analogWrite(LEFT_1, coun);
    //     delay(700);
    // }
    // for(int cou=255; cou>0; cou--){
    //     analogWrite(LEFT_1, cou);
    //     delay(700);
    // }
    pregister();
    while(1) {
        if (Serial.available() > 0) {
            bash = Serial.read();
            switch (bash) {
                case 'w':
                    if (left1 < 255) {left1 += 15;}
                    break;
                case 's':
                    if (left1 > 0) {left1 -= 15;}
                    break;

                case 'o':
                    if (right1 < 255) {right1 += 15;}
                    break;
                case 'k':
                    if (right1 > 0) {right1 -= 15;}
                    break;
                case ' ':
                    left1 = right1 = 120;
                    break;
                case 'q':
                    left1 = right1 = 0;
                    break;
                default:
                    break;
            }
            CLEAR;
            updatePWM();
            pregister();
        }
    }
}

void pregister() {
    Serial.println();
    GREEN;
    CLEAR;
    Serial.println("|\t>>\tUAV_Controller_1.0.ino");
    Serial.println("|\t>>\tCreated By Jack, November 7, 2015.");
    Serial.println("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=");    
    NONE;
    for (int coun = 255; coun > -1; coun-=15) {
        GREEN;
        Serial.print("|");
        NONE;
        Serial.print("--");
        Serial.print(coun);
        Serial.print("\t--\t");
        if (left1 >= coun) {
            if (left1) {
                if (left1 == 255) BROWN;
                else GREEN;
            }
            else {RED;}
            COLORRTN;
        }
        Serial.print("     ");
        NONE;
        GREEN;
        Serial.print("|\t");

        Serial.print("|");
        NONE;
        Serial.print("--");
        Serial.print(coun);
        Serial.print("\t--\t");
        if (right1 >= coun) {
            if (right1) {
                if (right1 == 255) BROWN;
                else GREEN;
            }
            else {RED;}
            COLORRTN;
        }
        Serial.println("     ");
        NONE;
    }
    GREEN;
    Serial.print("|MOTO_1\t\t");
    Serial.print(left1,DEC);

    Serial.print("\t|MOTO_2\t\t");
    Serial.println(right1,DEC);

    Serial.println("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=");    
    NONE;
        
    Serial.print("root@AVR-vmare:$ Sublime Python,finaly done!");
}
void updatePWM() {
    analogWrite(LEFT_1, left1);
    analogWrite(LEFT_2, left2);
    analogWrite(LEFT_3, left3);
    analogWrite(RIGHT_1, right1);
    analogWrite(RIGHT_2, right2);
    analogWrite(RIGHT_3, right3);
}

