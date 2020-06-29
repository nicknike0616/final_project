#include "mbed.h"
#include "arm_math.h"
#include "FXOS8700CQ.h"
#include "bbcar.h"
#include <math.h>
#include <stdlib.h>
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"

char recv;
char mission;
int send =0;
volatile int message_num = 0;
volatile int arrivedcount = 0;
volatile bool closed = false;
const char* topic = "Mbed";
WiFiInterface *wifi;
Ticker servo_ticker;
Thread t;
PwmOut pin8(D8), pin9(D9);
DigitalInOut pin13(D13);
BBCar car(pin8, pin9, servo_ticker);
Serial uart(D1,D0); //tx,rx
RawSerial xbee(D12, D11);
DigitalOut led1(LED1);
EventQueue queue(32 * EVENTS_EVENT_SIZE);

void xbee_rx(void);

void xbee_rx(void)
{
    if(send == 0)
        xbee.printf("%c",mission);
    else
    {
        ;
    }
}

int main() {
    mission ='1';
    led1 = 1;
    parallax_ping  ping1(pin13);
    uart.baud(9600);
    xbee.baud(9600);

    car.goStraight(100);
    wait(10);
    car.stop();
    wait(0.5);

    car.turn(-60, -0.01);
    wait(1.0);
    car.stop();
    wait(0.5);

    car.turn(-70, -0.01);
    wait(1.0);
    car.stop();
    wait(0.5);

    car.goStraight(100);
    wait(2.5);
    car.stop();
    wait(0.5);

    car.turn(-60, 0.01);
    wait(2);
    car.stop();

    car.goStraight(-100);
    wait(0.5);
    car.stop();
    char s[5];

    sprintf(s,"photo");
    uart.puts(s);
    wait(0.5);

    while(1){
        if(uart.readable()){
            recv = uart.getc();
            printf("%c\r\n",recv);
            printf("1\r\n");
            break;
        }
    }
    send = 1;
    xbee.printf("o");
    wait(0.1);
    xbee.printf("%c",recv);
    send = 0;

    car.turn(100,0.01);
    wait(1.5);
    car.stop();
    wait(0.5);

    car.goStraight(100);
    wait(5);
    car.stop();
    wait(1.0);

    car.turn(60, -0.01);
    wait(1.5);
    car.stop();
    wait(0.5);

    car.turn(60, -0.01);
    wait(0.5);
    car.stop();
    wait(0.5);

    car.goStraight(-100);
    wait(2.5);
    car.stop();
    wait(1.0);

    car.goStraight(100);
    wait(2.5);
    car.stop();
    wait(0.5);
    car.turn(-100, 0.01);
    wait(1.5);
    car.stop();
    wait(0.5);

    car.goStraight(100);
    wait(4.5);
    car.stop();
    wait(0.5);

    car.turn(-90, 0.01);
    wait(1.0);
    car.stop();
    wait(0.5);

    car.turn(-90, 0.01);
    wait(1.0);
    car.stop();
    wait(0.5);

    car.goStraight(100);
    wait(8.0);
    car.stop();
    led1 = 0;
    wait(1.0);
    led1 = 1;
}
