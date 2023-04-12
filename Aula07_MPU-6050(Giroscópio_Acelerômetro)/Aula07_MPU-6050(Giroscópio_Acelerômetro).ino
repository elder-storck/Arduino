/*
  MPU-6050
  data: 31/10/2022
  Autores Elder Storck, Alan Medina, Victor Soares, Eduardo Marchese. 
*/

#include<Wire.h>
#include <math.h>
const int MPU=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int l1,l2,l3,l4,l5;
double pitch,roll;
//===============================================================================
//  Initialization
//===============================================================================
void setup(){
Wire.begin();                 //Iniciando Comunicação com sensor
Wire.beginTransmission(MPU);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
}
//===============================================================================
//  Main
//===============================================================================
void loop(){

delay(10000);                                 //Delay entre uma letra e outra
  l1 = 0; l2 = 0; l3 = 0; l4 = 0; l5 = 0;     

  if(ehRight(getDirection(720,-100,-17000)))  //se o sensor estiver virado para direta, o valor de l1 será 1
    l1 = 1;
  if(ehRight(getDirection(720,-100,-17000)))
    l2 = 1;
  if(ehRight(getDirection(720,-100,-17000)))
    l3 = 1;
  if(ehRight(getDirection(720,-100,-17000)))
    l4 = 1;
  if(ehRight(getDirection(720,-100,-17000)))
    l5 = 1;

  letter(l1,l2,l3,l4,l5);                     //Imprime letra compatível com a tabela
  
  Serial.print("l1 :"); Serial.println(l1);   //Imprime sequência de bit
  Serial.print("l2 :"); Serial.println(l2);
  Serial.print("l3 :"); Serial.println(l3);
  Serial.print("l4 :"); Serial.println(l4);
  Serial.print("l5 :"); Serial.println(l5);
}
//===============================================================================
//  Ler a Direção
//===============================================================================

int16_t getDirection(int AcXoff,int AcYoff,int AcZoff){
  Serial.println("Vire para Esquerda ou direita Conforme a Tabela");
  delay(10000);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);
  
  AcX=((Wire.read()<<8|Wire.read()) + AcXoff);
  AcY=((Wire.read()<<8|Wire.read()) + AcYoff);    //lê a coordenada do acelerômetro
  AcZ=((Wire.read()<<8|Wire.read()) + AcZoff);
  
  return AcY;
}

//===============================================================================
//  ehRight - Função verifica se está virado para direita o sensor
//===============================================================================

int ehRight(int16_t direction){
  if(direction<-10000)          //se o sensor estiver virado para direita, retorna 1
    return 1;
  return 0;
}

//===============================================================================
//  letter - Imprimir letra
//===============================================================================
void letter(int l1, int l2, int l3, int l4, int l5){
  Serial.print("Letra : ");
  if(l1==0 && l2==0 && l3==0 && l4==0 && l5==0) Serial.println("A");
  if(l1==0 && l2==0 && l3==0 && l4==0 && l5==1) Serial.println("B");
  if(l1==0 && l2==0 && l3==0 && l4==1 && l5==0) Serial.println("C");
  if(l1==0 && l2==0 && l3==0 && l4==1 && l5==1) Serial.println("D");
  if(l1==0 && l2==0 && l3==1 && l4==0 && l5==0) Serial.println("E");
  if(l1==0 && l2==0 && l3==1 && l4==0 && l5==1) Serial.println("F");
  if(l1==0 && l2==0 && l3==1 && l4==1 && l5==0) Serial.println("G");
  if(l1==0 && l2==0 && l3==1 && l4==1 && l5==1) Serial.println("H");
  if(l1==0 && l2==1 && l3==0 && l4==0 && l5==0) Serial.println("I");
  if(l1==0 && l2==1 && l3==0 && l4==0 && l5==1) Serial.println("J");
  if(l1==0 && l2==1 && l3==0 && l4==1 && l5==0) Serial.println("K");
  if(l1==0 && l2==1 && l3==0 && l4==1 && l5==1) Serial.println("L");
  if(l1==0 && l2==1 && l3==1 && l4==0 && l5==0) Serial.println("M");
  if(l1==0 && l2==1 && l3==1 && l4==0 && l5==1) Serial.println("N");
  if(l1==0 && l2==1 && l3==1 && l4==1 && l5==0) Serial.println("O");
  if(l1==0 && l2==1 && l3==1 && l4==1 && l5==1) Serial.println("P");
  if(l1==1 && l2==0 && l3==0 && l4==0 && l5==0) Serial.println("Q");
  if(l1==1 && l2==0 && l3==0 && l4==0 && l5==1) Serial.println("R");
  if(l1==1 && l2==0 && l3==0 && l4==1 && l5==0) Serial.println("S");
  if(l1==1 && l2==0 && l3==0 && l4==1 && l5==1) Serial.println("T");
  if(l1==1 && l2==0 && l3==1 && l4==0 && l5==0) Serial.println("U");
  if(l1==1 && l2==0 && l3==1 && l4==0 && l5==1) Serial.println("V");
  if(l1==1 && l2==0 && l3==1 && l4==1 && l5==0) Serial.println("W");
  if(l1==1 && l2==0 && l3==1 && l4==1 && l5==1) Serial.println("X");
  if(l1==1 && l2==1 && l3==0 && l4==0 && l5==0) Serial.println("Y");
  if(l1==1 && l2==1 && l3==0 && l4==0 && l5==1) Serial.println("Z");
  if(l1==1 && l2==1 && l3==0 && l4==1 && l5==0) Serial.println("0");
  if(l1==1 && l2==1 && l3==0 && l4==1 && l5==1) Serial.println("1");
  if(l1==1 && l2==1 && l3==1 && l4==0 && l5==0) Serial.println("2");
  if(l1==1 && l2==1 && l3==1 && l4==0 && l5==1) Serial.println("3");
  if(l1==1 && l2==1 && l3==1 && l4==1 && l5==0) Serial.println("4");
  if(l1==1 && l2==1 && l3==1 && l4==1 && l5==1) Serial.println("5");
  
  return;
}