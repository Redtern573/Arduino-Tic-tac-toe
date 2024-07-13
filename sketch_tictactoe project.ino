// C++ code
//
#include <LiquidCrystal.h>
int pos = 0;

int button1_state = LOW;
int button2_state = LOW;
int player2_count = 9;
 
int player = 1;


int LED_up = 0;

boolean game_over = false;
boolean player1win = false;
boolean player2win = false;
 
boolean blink = true;
 
int leds[] = { 13, 12, 11, 10, 9, 8, 7, 6, 5 };
int state[] = {  0, 0, 0,  0, 0, 0,  0, 0, 0 };
LiquidCrystal lcd_1(43, 45, 53, 51, 49, 47);  
 
void setup()
{
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  for (int n=0; n < 9; n++) pinMode(leds[n], OUTPUT);
  
  pinMode(4, OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(0,OUTPUT);
}
 
void check_button1()
{
  // BUTTON 1
  int button = digitalRead(3);
  
  if (button == HIGH && button1_state == LOW)
  {
    button1_state = HIGH;
    
    boolean ok = false;
      
    while(!ok)
    {
      pos++;
      if (pos > 8) pos = 0;
      if (state[pos] == 0) ok = true;
    }
  }
   
  if (button == LOW && button1_state == HIGH) button1_state = LOW;
}
 
void check_button2()
{
  // BUTTON 2
  int button = digitalRead(2);
  
  if (button == HIGH && button2_state == LOW)
  {
    // set led state
    state[pos] = player;
    
    
   
    button2_state = HIGH;

    // next player
    LED_up++;
    player++;
    boolean ok = false;
      
    while(!ok)
    {
      pos++;
      if (pos > 8) pos = 0;
      if (state[pos] == 0) ok = true;
    }
    if (player > 2) player = 1;
    
   
  }
  
  if (button == LOW && button2_state == HIGH) button2_state = LOW;
}
 
void setLed(int id, int player)
{
  if (player == 0)
  {
    digitalWrite(id, LOW);
    
  }
  
  if (player == 1)
  {
    digitalWrite(id, HIGH);

  }
  
  if (player == 2)
  {
    if (player2_count > 5)
    {
      digitalWrite(id, HIGH);
    }
    else
    {
      digitalWrite(id, LOW);
    }
  }
}
 
void loop()
{
  
  if (!game_over)
  {
    check_button1();
    check_button2();
  }
  
  for (int n=0; n < 9; n++)
  {
    if (n != pos) setLed(leds[n], state[n]);
  }
  
  if (!game_over)
  {
    if (blink) 
      digitalWrite(leds[pos], HIGH);
    else
      digitalWrite(leds[pos], LOW);
    
    blink = !blink;
  }
  
  player2_count--;
  if (player2_count == 0) player2_count = 9;
  

  if (player1win) digitalWrite(leds[pos],LOW);
  
  if (player2win) digitalWrite(leds[pos],LOW);

  if (LED_up == 8)
  {boolean ok = false;
      
    while(!ok)
    {
      pos++;
      if (pos > 8) pos = 0;
      if (state[pos] == 0) ok = true;
      digitalWrite(leds[pos],HIGH);
    }
    }
  
    player1();
    player2();
    player1special();
    draw();
    delay(100);
}

void player1(){
   if((state[0] == 1) && (state[1] == 1) && (state[2] == 1))
    player1win = true;
      
   if((state[3] == 1) && (state[4] == 1) && (state[5] == 1))
    player1win = true;
          
   if((state[6] == 1) && (state[7] == 1) && (state[8] == 1))
    player1win = true;
      
   if((state[0] == 1) && (state[4] == 1) && (state[8] == 1))
    player1win = true;
      
   if((state[6] == 1) && (state[4] == 1) && (state[2] == 1))
    player1win = true;
      
   if((state[0] == 1) && (state[3] == 1) && (state[6] == 1))
    player1win = true;
      
   if((state[1] == 1) && (state[4] == 1) && (state[7] == 1))
    player1win = true;
      
   if((state[2] == 1) && (state[5] == 1) && (state[8] == 1))
    player1win = true;   
   
   win();
}

void player2(){
   if((state[0] == 2) && (state[1] == 2) && (state[2] == 2))
    player2win = true;
      
   if((state[3] == 2) && (state[4] == 2) && (state[5] == 2))
    player2win = true;
          
   if((state[6] == 2) && (state[7] == 2) && (state[8] == 2))
    player2win = true;
      
   if((state[0] == 2) && (state[4] == 2) && (state[8] == 2))
    player2win = true;
      
   if((state[6] == 2) && (state[4] == 2) && (state[2] == 2))
    player2win = true;
      
   if((state[0] == 2) && (state[3] == 2) && (state[6] == 2))
    player2win = true;
      
   if((state[1] == 2) && (state[4] == 2) && (state[7] == 2))
    player2win = true;
      
   if((state[2] == 2) && (state[5] == 2) && (state[8] == 2))
    player2win = true; 

   win();
}
void player1special()
{
  if (LED_up == 8) 
  {
    if((state[0] == 1) && (state[1] == 1) && (state[2] == 0))
    player1win = true;
    if((state[0] == 1) && (state[1] == 0) && (state[2] == 1))
    player1win = true;
    if((state[0] == 0) && (state[1] == 1) && (state[2] == 1))
    player1win = true;
      if((state[3] == 1) && (state[4] == 1) && (state[5] == 0))
      player1win = true;
      if((state[3] == 1) && (state[4] == 0) && (state[5] == 1))
      player1win = true;
      if((state[3] == 0) && (state[4] == 1) && (state[5] == 1))
      player1win = true;
          if((state[6] == 1) && (state[7] == 1) && (state[8] == 0))
          player1win = true;
          if((state[6] == 1) && (state[7] == 0) && (state[8] == 1))
          player1win = true;
          if((state[6] == 0) && (state[7] == 1) && (state[8] == 1))
          player1win = true;
            if((state[0] == 1) && (state[4] == 1) && (state[8] == 0))
            player1win = true;
            if((state[0] == 1) && (state[4] == 0) && (state[8] == 1))
            player1win = true;
            if((state[0] == 0) && (state[4] == 1) && (state[8] == 1))
            player1win = true;
              if((state[6] == 1) && (state[4] == 1) && (state[2] == 0))
              player1win = true;
              if((state[6] == 1) && (state[4] == 0) && (state[2] == 1))
              player1win = true;
              if((state[6] == 0) && (state[4] == 1) && (state[2] == 1))
              player1win = true;
                if((state[0] == 1) && (state[3] == 1) && (state[6] == 0))
                player1win = true;
                if((state[0] == 1) && (state[3] == 0) && (state[6] == 1))
                player1win = true;
                if((state[0] == 0) && (state[3] == 1) && (state[6] == 1))
                player1win = true;
                  if((state[1] == 1) && (state[4] == 1) && (state[7] == 0))
                  player1win = true;
                  if((state[1] == 1) && (state[4] == 0) && (state[7] == 1))
                  player1win = true;
                  if((state[1] == 0) && (state[4] == 1) && (state[7] == 1))
                  player1win = true;
                    if((state[2] == 1) && (state[5] == 1) && (state[8] == 0))
                    player1win = true;
                    if((state[2] == 1) && (state[5] == 0) && (state[8] == 1))
                    player1win = true;
                    if((state[2] == 0) && (state[5] == 1) && (state[8] == 1))
                    player1win = true;

  }
  win();
}
void win(){
  if(player1win == true){
      lcd_1.setCursor(2, 0);
    lcd_1.print("PLAYER 1 WIN");
  }

  if(player2win == true){
      lcd_1.setCursor(2, 0);
    lcd_1.print("PLAYER 2 WIN");
  }
}
 void draw()
{
   if ((LED_up == 8) && (player1win == false) && (player2win == false))
  {
    lcd_1.setCursor(6, 0);
    lcd_1.print("DRAW");
  }
}

// 15 12 11 = Line / 10 9 8 = Line / 7 6 5 = Line
// 13 9 5 = Angle / 11 9 7 = Angle 
// 13 10 7 = Line / 12 9 6 = Line / 11 8 5 = Line
