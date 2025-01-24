//#include "gpio.h"
#define PORTA *((volatile uint8_t *) 0x22)  //LCD
#define DDRA *((volatile uint8_t *) 0x21)
#define PINA *((volatile uint8_t *) 0x20)
#define PORTB *((volatile uint8_t *) 0x25) //E RW RS
#define DDRB *((volatile uint8_t *) 0x24)
#define PINB *((volatile uint8_t *) 0x23)

#define Bit(n) (1 << (n))

void setup() {
  DDRA = 0xFF;
  DDRB |= (Bit(2)|Bit(1)|Bit(0));
  LCD_Config();
  Serial.begin(9600);
}

#define RS_I 0
#define RS_D 1
#define Lines 4 // 4 or 8 bits 

#define LCD_Init 0x30
#define ClearDisplay 1
#define ReturnHome 2
#define EntryModeSet_Inc 7  
#define EntryModeSet_Dec 5
#define EntryModeSet_Static 4
#define DisplayCtr_OFF 8
#define DisplayCtr_ON 0x0C
#define DisplayCtr_CursorON 0x0E
#define DisplayCtr_CursorPisca 0x0F
#define FunctionSet_8 0x3C // 2lines;Char5x10
#define FunctionSet_4 0x2C // 2lines;Char5x10

void LCD_Config(){
  if (Lines == 8)
    LCD_Config8();
  else
    LCD_Config4();
}

void LCD_Config8(){
  LCD_Write(LCD_Init,RS_I);
  delay(5);
  LCD_Write(LCD_Init,RS_I);
  delayMicroseconds(110);
  LCD_Write(LCD_Init,RS_I);
  delay(1);
  LCD_Write(FunctionSet_8,RS_I);
  LCD_Write(ClearDisplay,RS_I);
  LCD_Write(DisplayCtr_ON,RS_I);
}

void LCD_Config4(){
  PORTB &= ~bit(2); //Instruction  
  for(int i=0;i<=2;i++){
    PORTA = LCD_Init & 0xF0;
  	PORTB |= bit(0);  
  	delay(5);
    PORTB &= ~bit(0);
  }
    PORTA = 0x20;
  	PORTB |= bit(0);  
  	delay(1);
    PORTB &= ~bit(0);
  LCD_Write(FunctionSet_4,RS_I);
  LCD_Write(ClearDisplay,RS_I);
  LCD_Write(DisplayCtr_ON,RS_I);
}

void LCD_Write(int Data, int D_I){

  if (D_I)
    PORTB |= bit(2);  //Data
  else
    PORTB &= ~bit(2); //Instruction
  
  if (Lines == 8){ 
    PORTA = Data;
  	PORTB |= bit(0);  
  	delay(1);
    PORTB &= ~bit(0);
  }else {
    PORTA = Data & 0xF0;
  	PORTB |= bit(0);  
  	delay(1);
    PORTB &= ~bit(0);
    PORTA = (Data<<4) & 0xF0;
  	PORTB |= bit(0);  
  	delay(1);
    PORTB &= ~bit(0);
  } 
}  

int msgLine01[] = {'e','l','d','e','r'};
int msgLine02[] = {'e','n','g','e','n','h','a','r','i','a',' ','d','e',' ','c','o','m','p','u','t','a','c','a','o'};

void loop()
{
  static int counter = 0;
  static int counter2 = 0;
      
  LCD_Write(0x80+counter,0);        //Define a posição da memória (10000000b - 10001111b)
  LCD_Write(msgLine01[counter],1);  //escreve

  LCD_Write(0xc0+counter2,0);       //Define a posição da memória (11000000b - 11001111b)
  LCD_Write(msgLine02[counter2],1); //escreve
    

  counter++;
  counter2++;  
  if(counter == 5)   counter =0;    //número de letras mensagem linha 01
  if(counter2 == 21) counter2 =0;   //numero de letras mensagem linha 02
  
  LCD_Write(0x1b,0);                //Faz shift da mensagem (00011000b)


  delay(100);

}
