/*
	Autor : Elder R. Storck
	Projeto feito para a disciplina de 
	Projeto Integrado de Computação I
   	Aula 3 - Lab Arduino básico
    Projeto - Semáforo
*/

volatile int buttonON = 0;
int semMainGreen = 10;	//Declarando semáforo Carros
int semMainYellow = 11;
int semMainRed = 12;
int semSecGreen = 8;	//Declarando semáforo pedestre
int semSecRed = 9;
int control = 0;
int time = 3000; //3 segundos



void setup(){
  //Define os pinos 8 a 12 como saída
  pinMode(semMainGreen, OUTPUT);				
  pinMode(semMainRed, OUTPUT);
  pinMode(semMainYellow, OUTPUT);
  pinMode(semSecGreen, OUTPUT);
  pinMode(semSecRed, OUTPUT);
  
  //Função que chama CheckButton() se o botao for acionado
  attachInterrupt(0,CheckButton, RISING);	
}


void loop(){  
  //Variável para o botao não ser acionado mais de uma vez por rodada
  control = 1;									
  
  LightUpGreen();								//Acende o semáforo principal verde								
  if(buttonON == 1 && control == 1){		//verifica se o botao foi apertado		
    LightUpYellow();								
    LightUpRed();
    buttonON = 0;
    control = 0;								//alterando valor variável de control
  }
  
  LightUpYellow();								//Acende o semáforo principal amarelo
  if(buttonON == 1 && control == 1){		//verifica se o botao foi apertado
    LightUpYellow();
    LightUpRed();
    buttonON = 0;
    control = 0;
  }
  
  LightUpRed();									//Acende o semáforo principal amarelo
  if(buttonON == 1 && control == 1){		//verifica se o botao foi apertado
    LightUpYellow();
    LightUpRed();
    buttonON = 0;
    control = 0;
  }
}

/**************************Função Verifica Botão************************************/
void CheckButton(){
    buttonON = 1;	//quando o botao for apertado a variável assume o valor 1
}


/******************Acende o semáforo principal (VERDE)******************************/
void LightUpGreen(){		
  digitalWrite(semMainGreen, HIGH);
  digitalWrite(semSecRed, HIGH);
  delay(time);
  digitalWrite(semMainGreen, LOW);
  digitalWrite(semSecRed, LOW);
}


/******************Acende o semáforo principal (Amarelo)******************************/
void LightUpYellow(){	
  digitalWrite(semMainYellow, HIGH);
  digitalWrite(semSecRed, HIGH);
  delay(time);
  digitalWrite(semMainYellow, LOW);
  digitalWrite(semSecRed, LOW);  
}


/******************Acende o semáforo principal (Vermelho)******************************/
void LightUpRed(){
  digitalWrite(semMainRed, HIGH);
  digitalWrite(semSecGreen, HIGH);
  delay(time);
  digitalWrite(semMainRed, LOW);
  digitalWrite(semSecGreen, LOW);
  
}
    

  
  