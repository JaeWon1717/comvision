#include "softServo.h"
#define RCSERVO 23 //GPIO 23
#define servopwron 27 //27
int main(void)
{
	softServoSetup(RCSERVO, -1, -1, -1, -1, -1, -1, -1);
	pinMode(servopwron, OUTPUT);
	digitalWrite(servopwron, 1);
	for (i = 0; i < 10; i++) {
		printf("rc servo on \n");
		delay(1000);
		softServoWrite(RCSERVO, -250);
		delay(3000);
		printf("rc servo off \n");
		softServoWrite(RCSERVO, 1250);
		delay(3000);