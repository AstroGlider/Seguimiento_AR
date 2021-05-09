
// -*- mode: C++ -*-

// $Id: seguimiento_AR_buzzer.pde,v 1.1 31/10/2012 23:51:01 
// 2012 Ricky
//
// dada una velocidad constante para el motor
// aumenta o disminuye progresivamente la velocidad (e invierte el sentido de giro si baja de 0)
// en función de cuan lejos se mueve del centro un potenciometro
// cuando entra en la velocidad prefijada hace un beep

// se utiliza la libreria "AccelStepper" https://www.airspayce.com/mikem/arduino/AccelStepper/index.html


#include <AccelStepper.h>

//AccelStepper stepper;// Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5 (pasos enteros --> 8.021902393 pulsos por segundo para mi telescopio)
AccelStepper stepper(AccelStepper::HALF4WIRE, 2,3,4,5); // se define como medios pasos--> 16.043804786 pulsos por segundo para mi telescopio
int pin = 0;
int vel = 0;
int speakerPin = 6;
boolean buzzed = false;
const float velsid = 16.043804786; //velocidad sideral es 8.021902393 pulsos por segundo para mi telescopio en modo paso normal


void setup()
{  
//  Serial.begin(115200);
   stepper.setMaxSpeed(1000);
   stepper.setSpeed(velsid);
   pinMode(speakerPin, OUTPUT);
   
}

void loop()
{  
    if (analogRead(pin)<480)          // rango inferior del potenciometro
  {
    vel=velsid-(479-analogRead(pin)); //rango velocidad de +8 a -471
    digitalWrite(13, LOW);            // led placa arduino
    digitalWrite(07, LOW);            // led de la caja
    stepper.setSpeed(vel);
    stepper.runSpeed();
    buzzed=false;
  }
  
  else if (analogRead(pin)>540)  //rango superior del potenciometro
  {
    vel=(analogRead(pin)-541)+velsid;  //rango velocida de 8 a 483
    digitalWrite(13, LOW);
    digitalWrite(07, LOW);
    stepper.setSpeed(vel);
    stepper.runSpeed();
    buzzed=false;
   }
   else //zona neutra del potenciometro
   {
     vel=velsid;	// Se puede prescindir, vel es int y velsid es float
     digitalWrite(13, HIGH);
     digitalWrite(07, HIGH);
     stepper.setSpeed(velsid);	//Se pasar directamente la constante velsid reconoce float
     stepper.runSpeed();
     if (buzzed==false && analogRead(pin)>=485 && analogRead(pin)<=5350) //para evitar doble beep
       {
         beep(speakerPin,25);             // se pasa (pin del buzzer y duranción del beep
         buzzed=true;
       }
   }
}

// funcion beep
void beep(int speakerPin, unsigned char delayms)
{
  analogWrite(speakerPin, 20);            // Almost any value can be used except 0 and 255
  delay(delayms);                         // wait for a delayms ms
  analogWrite(speakerPin, 0);             // 0 turns it off
  delay(delayms);                         // wait for a delayms ms   
} 
