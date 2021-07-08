#include <Arduino.h>
#include <AccelStepper.h>

#define STEP_MOT_LEVAGE 4
#define DIR_MOT_LEVAGE 3
#define SLEEP_MOT_LEVAGE 5
#define RESET_MOT_LEVAGE 6

#define NB_PAS -501000

#define CAPTEUR A5

#define BtnOff 11 //Bouton 1
#define BtnOn 12
#define BT3 A7


#define MOTPHARE A3
#define LAMPE A4

AccelStepper motor_levage(1,STEP_MOT_LEVAGE,DIR_MOT_LEVAGE);//declaration du moteur gauche

int etat_btnoff=0, etat_btnon=0;
bool passe_up=1, passe_down=1;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(11,INPUT_PULLUP);
  // //initialisation du moteur PàP
  pinMode(RESET_MOT_LEVAGE, OUTPUT);    //le reset se fait a l'état bas
  digitalWrite(RESET_MOT_LEVAGE, HIGH);
  pinMode(SLEEP_MOT_LEVAGE, OUTPUT);    //le sleep se met a l'état bas pour une carte fonctionelle
  digitalWrite(SLEEP_MOT_LEVAGE, HIGH);

  motor_levage.setSpeed(200000);
  motor_levage.setAcceleration(150000);
  //
  //initialisation CAPTEUR IFM
  pinMode(CAPTEUR,INPUT_PULLUP);
  // delay(10000);
  pinMode(etat_btnoff,INPUT_PULLUP);
  pinMode(etat_btnon,INPUT_PULLUP);

  pinMode(MOTPHARE,OUTPUT);
  pinMode(LAMPE,OUTPUT);
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

void loop() {
   etat_btnoff=digitalRead(BtnOff);
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
  motor_levage.run();
 //  delay(1000);
 //  Serial.print(digitalRead(11));
//  Serial.println(digitalRead(BT2));

}
