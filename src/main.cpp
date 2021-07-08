#include <Arduino.h>
#include <AccelStepper.h>

#define STEP_MOT_LEVAGE 4
#define DIR_MOT_LEVAGE 3
#define SLEEP_MOT_LEVAGE 5
#define RESET_MOT_LEVAGE 6

#define NB_PAS -501000

#define CAPTEUR 19

#define BtnOff 11 //Bouton 1
#define BtnOn 12
#define BT3 20

#define LED_1 16
#define LED_2 15
#define LED_3 14
#define LED_4 13
#define LED_5 12

AccelStepper motor_levage(1, STEP_MOT_LEVAGE, DIR_MOT_LEVAGE); //declaration du moteur gauche

void chenillard();

bool  autor_chenil = 0, passe_up=1;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  // //initialisation du moteur PàP
  pinMode(RESET_MOT_LEVAGE, OUTPUT); //le reset se fait a l'état bas
  digitalWrite(RESET_MOT_LEVAGE, HIGH);
  pinMode(SLEEP_MOT_LEVAGE, OUTPUT); //le sleep se met a l'état bas pour une carte fonctionelle
  digitalWrite(SLEEP_MOT_LEVAGE, HIGH);

  for (int i = 12; i <= 16; i++)
  { //init des leds
    pinMode(i, OUTPUT);
  }

  motor_levage.setSpeed(200000);
  motor_levage.setAcceleration(150000);
  //
  //initialisation CAPTEUR IFM
  pinMode(CAPTEUR, INPUT_PULLUP);
  // delay(10000);

  //chenillard();
  // Serial.println();
  // Serial.println(analogRead(BT1));
  // Serial.println(analogRead(BT1));
  // // while(analogRead(BT1)<800){
  // //   delay(1);
  // // }
  // // motor_levage.move(NB_PAS);
  // // do{
  // //   motor_levage.run();
  // // }while(motor_levage.isRunning());
  motor_levage.move(0);
}

void loop()
{
  /*    etat_btnoff=digitalRead(BtnOff);
   etat_btnon=digitalRead(BtnOn);
   if(etat_btnon==0){ // si bouton post-PREPARATION activé
     if(digitalRead(CAPTEUR)==1){ // si ifm détecte robot le toucher
        if(passe_up==1){//donne nb de pas à faire pour monter
          digitalWrite(LAMPE,1);
          digitalWrite(MOTPHARE,1);
          motor_levage.move(NB_PAS);
          passe_up=0;
        }
    }
    if(etat_btnoff==0){ // si bouton de descente activée
      if(passe_down==1){
        digitalWrite(LAMPE,0);
        digitalWrite(MOTPHARE,0);
        motor_levage.setSpeed(200000);
        motor_levage.setAcceleration(10000);
        motor_levage.move(-NB_PAS-100);
        passe_down=0;
      }
    }
  }
  motor_levage.run(); */

  if (digitalRead(CAPTEUR) == 1)
  { // si ifm détecte robot le toucher
    if (passe_up == 1)
    { //donne nb de pas à faire pour monter
      motor_levage.setSpeed(200000);
      motor_levage.setAcceleration(10000);
      motor_levage.move(NB_PAS);
      passe_up = 0;
      autor_chenil = 1;
    }
  }
  motor_levage.run();
  while (autor_chenil)
      chenillard();
}

void chenillard()
{
  for (int j = 12; j <= 16; j++)
  {
    digitalWrite(j, HIGH);
    delay(100);
    digitalWrite(j, LOW);
  }
}