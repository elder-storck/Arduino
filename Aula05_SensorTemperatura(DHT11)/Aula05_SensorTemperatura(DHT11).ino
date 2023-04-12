/*
  Projeto usando o sensor de temperatura DHT 11
  usando a biblioteca DHT Sensor Library da Adafruit
  Aula 5 : Projeto Integrado da computação   
*/
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define redLed  4   //Pinos do led
#define greenLed 5
#define blueLed 6

#define DHTPin 10                 //pino que está ligado o Data do sensor
#define DHTType DHT11             //Tipo do Sensor => DHT 11 / DHT 22 (AM2302) / DHT 21 (AM2301)

DHT_Unified dht(DHTPin, DHTType); //Inicializando a classe DHT_Unifield com nome dht

void setup() {

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  /*Serial.begin(9600);   //Iniciando comunicação serial
  */
  dht.begin();          //Iniciando DHT

}

void loop() {

  sensors_event_t event;              //Iniciando struct event  
  dht.temperature().getEvent(&event); //Colhendo a Temperatura e preenchendo na struct event
  /*
  Serial.print(F("Temperature: "));
  Serial.println(event.temperature);  //Exibindo a temperatura no serial monitor
  */
  temperatureTest(event.temperature);

  delay(1000);
}


/***************************** Função testa em qual faixa a temperatura está e chama colorOn *****************************/

void temperatureTest(float temp){
  if(temp < 10){         //Se a temperatura for (t<10) acende azul
    colorOn(0,0,1);
  }else
    if(temp < 20){       //Se a temperatura for (10<t<20) acende verde
     colorOn(0,1,0);
    }else
      if(temp < 30){     //Se a temperatura for (20<t<30) acende amarelo
        colorOn(1,1,0);
      }else{                          //Se a temperatura for (t>30) acende Vermelho
        colorOn(0,0,1);
      }
}


/***************************** Função que acende a cor do led correspondente *****************************/
/**
**  INPUT: (0 ou 1) para cada parametro
**  OUTPUT: Led ligado na cor correspondente
**/
void colorOn(int v, int g, int b){
  digitalWrite(redLed, v);
  digitalWrite(greenLed, g);
  digitalWrite(blueLed, b);

}