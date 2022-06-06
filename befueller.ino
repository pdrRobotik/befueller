#include <FtduinoSimple.h>
#include <AccessNode.h>

RobotikInterConnect* ric;
int counter = 0;
bool isClicked = false;

int i3Wert = 0;

void setup() {
  ric = new RobotikInterConnect("befueller");
}

void loop() {
  // put your main code here, to run repeatedly:
  run();
}

//m1 = Förderband (merge)
//m2 = Ablage von Werkstück
//m3 = Schranke
//m4 = Förderband (Lager Container)
//I1 = Schranke eingefahren
//I2 = Optokopler
//I3 = Phototransistor
//I4 = Schranke ausgefahren
//I5 = Optokopler
//I6 = Optokopler

void run() {
  //if ( ftduino.input_get(Ftduino::I2) || ftduino.input_get(Ftduino::I5)|| ftduino.input_get(Ftduino::I6)) {
  //  delay(1000);
  


  

  //Schranke zu
  while ( !ftduino.input_get(Ftduino::I4) ) {
    ftduino.motor_set(Ftduino::M3, Ftduino::LEFT);
  }
  ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

  //Förderband (Lager Conatiner) bis Lichtschranke
  //wenn mdsn command "an" ################################################# waiting for message -> if(message) 
  ric->send("mfc","websocket","OK");
  ric->read_wait();

  //Förderband merge an
  ftduino.motor_set(Ftduino::M1, Ftduino::LEFT);
   
  ftduino.motor_set(Ftduino::M4, Ftduino::LEFT);
  delay(100);
  while (ftduino.input_get(Ftduino::I3) ) {
    delay(1)
  }
  delay(500);
  ftduino.motor_set(Ftduino::M4, Ftduino::OFF);


  delay(2000); //muss angepasst werden

  //Förderband(merge) stopp
  ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

  //Werkstückband an
  ftduino.motor_set(Ftduino::M2, Ftduino::LEFT);
  delay(2500); //muss angepasst werden

  //Wekstückband aus
  ftduino.motor_set(Ftduino::M2, Ftduino::OFF);


  //Schranke auf
  while ( !ftduino.input_get(Ftduino::I1) ) {
    ftduino.motor_set(Ftduino::M3, Ftduino::RIGHT);
  }
  ftduino.motor_set(Ftduino::M3, Ftduino::OFF);

  ric->send("mfc","websocket","NEXT");
  ric->read_wait();

  //Förderband (merge)
  ftduino.motor_set(Ftduino::M1, Ftduino::LEFT);
  delay(5000); //muss angepasst werden
  ftduino.motor_set(Ftduino::M1, Ftduino::OFF);

  //}
}
