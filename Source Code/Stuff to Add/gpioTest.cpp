#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "jetsonGPIO.h"
using namespace std;

int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

int main(int argc, char *argv[]){

    cout << "Testing the GPIO Pins" << endl;


//Set the pin numbers to variables
		jetsonTX2GPIONumber BotHal = gpio394 ;    // Input Hall Effect Sensor (Bottom)(Pin 38)
		jetsonTX2GPIONumber TopHal = gpio393; 	  // Input Hall Effect Sensor (Top)(Pin 40)
		jetsonTX2GPIONumber Power = gpio388; 	  // Output Power (3.3V)(Pin 37)
		//Use Pin 39 as ground

	//export these pins to the user space
		gpioUnexport(BotHal);
		gpioUnexport(TopHal); // free the gpio pins
		gpioUnexport(Power);
		gpioExport(BotHal);
		gpioExport(TopHal);
		gpioExport(Power);

	//Tell the pins whether they are sending or recieving
		gpioSetDirection(BotHal,inputPin);
		gpioSetDirection(TopHal,inputPin);
		gpioSetDirection(Power,outputPin);
	
	//instantiate the value variables for the pins
		unsigned int bValue = low; //(low == 0, high == 1, *defined in jetsonGPIO.h)
		unsigned int tValue = low;

//**Run in main loop
	gpioSetValue(Power, on);
	while(getkey() != 27){
		gpioGetValue(BotHal, &bValue); //Get the values from the pins
		gpioGetValue(TopHal, &tValue);
		cout<<"\r"<<tValue;
	}
cout<<endl;
gpioUnexport(BotHal);
gpioUnexport(TopHal); // free the gpio pins
gpioUnexport(Power);
}
