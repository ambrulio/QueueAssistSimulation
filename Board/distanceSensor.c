	#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define TRUE 1
#define TRIG 4
#define ECHO 5
//#define TRIG 5
//#define ECHO 6

void setupRaspberry() {
        //wiringPiSetup();
        pinMode(TRIG, OUTPUT);
        pinMode(ECHO, INPUT);

        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}

int getCM() {
        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);

        //Wait for echo start
	//printf("waiting for echo start..\n");
        long startTime0 = micros();
        while(digitalRead(ECHO) == LOW){
		if(micros()-startTime0 > 1000000){
			return 99999;
		}
	}
	//printf("waiting for echo end..\n");
        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH){
		if(micros()-startTime > 1000000){
			return 99999;
		}
	}
        long travelTime = micros() - startTime;

        //Get distance in cm
        int distance = travelTime / 58;

        return distance;
}

		