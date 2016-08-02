#include <stdio.h>

//Pin to to turn dice on & off
int button = 2;
//LED for DICE
int bottomLeft = 3;
int middleLeft = 4;
int upperLeft = 5;
int middle = 6;
int bottomRight = 7;
int middleRight = 8;
int upperRight = 9;
boolean buttonState = LOW;
boolean blue = LOW;
boolean white = LOW;

int playerNumber = 1;
int score1 = 0;
int score2 = 0;

int state = 0;
long randNumber; 

long p1StartTime;
long p1TotalTime;
long p1Final;
int p1Counter =0;
int p1Turns = 1;


long p2StartTime;
long p2TotalTime;
long p2Final;
int p2Counter =0;
int p2Turns = 1;

boolean extraTurn = LOW;
boolean compare = LOW;
boolean flag = LOW;


//Initial setup
void setup(){
  pinMode(bottomLeft, OUTPUT);
  pinMode(middleLeft, OUTPUT);
  pinMode(upperLeft, OUTPUT);
  pinMode(middle, OUTPUT);
  pinMode(bottomRight, OUTPUT);
  pinMode(middleRight, OUTPUT);
  pinMode(upperRight, OUTPUT);
  
  pinMode(button, INPUT_PULLUP);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  attachInterrupt(digitalPinToInterrupt(2),buttonHandler, RISING);
 // attachInterrupt(digitalPinToInterrupt(10), blueButton , RISING);
 // attachInterrupt(digitalPinToInterrupt(11), whiteButton ,RISING);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  Serial.print("\nWelcome to 192L Blackjack!");
  Serial.println("\nPlayer 1, please make your call (hit/stay).");
}

void loop(){
  //Read our button if high then run dice
 if (blue == HIGH)
 {
  Serial.println("Blue was pressed");
 }


 
  if (buttonState==HIGH) 
  {
    debounce();
  }

  /*
  if (blue == HIGH) 
  {
    Serial.println("Blue INTERRUPT");
  }
  if (white==HIGH){
    Serial.println("White INTERRUPT");
  }
  */
 
  if (state == 0 && digitalRead(button) == HIGH)
  {
    state = 1;
    randNumber = random(1, 7);
    delay(300);
    //Serial.println(randNumber);
   
    clearAll();
    state = 0;
   buttonState = LOW;
    
  }
}

void led()
{
    if (randNumber == 6){
      six();
    }
    if (randNumber == 5){
      five();
    }
    if (randNumber == 4){
      four();
    }
    if (randNumber == 3){
      three();
    }
    if (randNumber == 2){
      two();
    }
    if (randNumber == 1){
      one();
    }

    delay(250);
    
}

//Create a function for each of our "sides" of the die
 void six()
{
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(middleLeft, HIGH);
  digitalWrite(upperLeft, HIGH);
  digitalWrite(bottomRight, HIGH);
  digitalWrite(middleRight, HIGH);
  digitalWrite(upperRight, HIGH);
}

void five()
{
  digitalWrite(upperLeft, HIGH);
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(upperRight, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void four()
{
  digitalWrite(upperLeft, HIGH);
  digitalWrite(bottomLeft, HIGH);
  digitalWrite(upperRight, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void three()
{
  digitalWrite(upperLeft, HIGH);
  digitalWrite(middle, HIGH);
  digitalWrite(bottomRight, HIGH);
}

void two()
{
  digitalWrite(bottomRight, HIGH);
  digitalWrite(upperLeft, HIGH);
}

void one(){
  digitalWrite(middle, HIGH);
}

void clearAll(){
  digitalWrite(bottomLeft, LOW);
  digitalWrite(middleLeft, LOW);
  digitalWrite(upperLeft, LOW);
  digitalWrite(middle,LOW);
  digitalWrite(bottomRight, LOW);
  digitalWrite(middleRight, LOW);
  digitalWrite(upperRight, LOW);
}

void debounce ()
{

static unsigned long lastInterruptTime = 0;
unsigned long interruptTime = millis();
//Serial.println(playerNumber);
if (interruptTime - lastInterruptTime > 100)
  {
    

    if (extraTurn == HIGH)
    {
      if (playerNumber == 1)
      {
        Serial.println("Player 1 extra turn");
        led();
        hit();
        //extraTurn = LOW;
      }
      else if (playerNumber == 2)
      {
        Serial.println("Player 2 extra turn");
        led();
        hit(); 
       // extraTurn = LOW;

      }
    }

    
    if (digitalRead(11) == HIGH) 
    {

      if (p1Turns >= 8)
      {
        Serial.println("\nPlayer 1 has reached maximum turns");
        stay();
      }
      
      if (p2Turns >= 8)
      {
        Serial.println("\nPlayer 2 has reached maximum turns");
        stay();
      }

      
      if (playerNumber == 1)
      {
        p1TotalTime = millis() - p1StartTime;
        p1Final += p1TotalTime;
        p1Counter = 0;
        p1Turns++;
      }

      else if (playerNumber == 2)
      {
        p2TotalTime = millis() - p2StartTime;
        p2Final += p2TotalTime;
        p2Counter = 0;
        p2Turns ++;
        
      }
     
      Serial.println("\nStay");
      stay();
    }
    
    else if (digitalRead(10) == HIGH)
    {

      if (p1Turns == 8)
      {
          Serial.println("\nPlayer 1 has reached maximum number of turns");
          stay();
      }
      
      if (p2Turns == 8)
      {
        Serial.println("\nPlayer  2 maximum turns");
        stay();

      }
      
      if (playerNumber == 1)
      {
        if (p1Counter == 0)
        {
              p1StartTime = millis();
        }
      p1Counter ++;
      p1Turns++;
      }

      if (playerNumber == 2)
      {
        if (p2Counter == 0)
      {
              p2StartTime = millis();
      }
      
      p2Counter ++;
      p2Turns++;
      
      }

     if (p1Turns < 9 && p2Turns < 9)
     { 
     Serial.println("\nHit");
     led();
     hit();
     }
    }
   
  }
  
  lastInterruptTime = interruptTime;

  
}


// 

void stay()
{
  if (playerNumber==1 && p2Turns <= 8) 
  {
    Serial.println ("Player 2's Turn");
    playerNumber = 2;
  }
  else if (p1Turns <= 8) 
  {
    Serial.println ("Player 1's Turn");
    playerNumber = 1;
  }
  
  if (p1Turns == 9 && p2Turns == 9)
  {
    endOfGame();
    p1Turns++;
    p2Turns++;
    // both people are done, check if bust, check time for each player and see whos closer to 21
  }
 
  
}

void hit()
{

 // Serial.println("Entered hit function player number is: " );

  
  if (playerNumber == 1) 
  {
   // Serial.println("Entered if statement");
    Serial.println(randNumber);
    score1 += randNumber;
    Serial.println("Player 1 score: ");
    Serial.println(score1);
    compareScores();

  }
  else if (playerNumber == 2) 
  {
   //  Serial.println("\nRand number printed");
    Serial.println(randNumber);
    score2 += randNumber;
    Serial.println("Player 2 score: ");
    Serial.println(score2);
    compareScores();
  }



  

}

void compareScores()
{
  
    if (score1 > 21) {
    Serial.println("\nPlayer 1 is bust. Player 2 wins!"); // end game, reset game
    //reset();
  }
  
  else if (score1 == 21) {
    Serial.println("\nPlayer 1 wins!"); // end game, reset game
    //reset();
  }

  if (score2 > 21) {
    Serial.println("\nPlayer 2 is bust. Player 1 wins!");
    //reset();
  }

  else if (score2 == 21) {
    Serial.println("\nPlayer 2 wins!"); // end game, reset game
    //reset();
  }


  if (score1 < 21 && score1 > score2 && extraTurn ==HIGH )
  {
    Serial.println("Player 1 wins! GAME OVER");
    extraTurn = LOW;
   
    // player 1 wins, end game reset
  }

  if (score2 < 21 && score2 > score1 && extraTurn ==HIGH)
  {
    Serial.println("Player 2 wins! GAME OVER");
    extraTurn = LOW;
   // player 1 wins, end game reset
  }
}



void buttonHandler()
{
  buttonState = HIGH;

}

void endOfGame()
{
  if (p1Final > p2Final)
  {
    playerNumber = 1;
    Serial.println("Player 1 seems to have taken a longer time, please take another turn.");
    extraTurn = HIGH;

        
    if (digitalRead(10) == HIGH) 
    {
           compare = HIGH;
           debounce();
           compare = 1;
    }
  }
   
  else if (p2Final > p1Final)
  {
    playerNumber = 2;
    Serial.println("Player 2 seems to have taken a longer time, please take an extra hit.");
    
    
    extraTurn = HIGH;

    
    if (digitalRead(10) == HIGH) 
    {
          Serial.println("Entered if statement");
          compare = HIGH;
          debounce();
          Serial.println( "compare is 1");

          
         // extraTurn = LOW;
    }    
    
    }

 
  

}

void reset()
{
  Serial.println("Do you wish to play again? Press the 'hit' button if yes, and 'stay' if not.");
  if (digitalRead(10) == HIGH) {
     softwareReset();
  }  
   else if (digitalRead(11) == HIGH); 
   {
      Serial.println("Thanks for playing, goodbye!");
   }
}

  // should be called if some one gets == 21. that player wins end game. done in hit method
  // compare if no one is bust
  // check the time, assign extra turns
  // now compare scores and if someone is bust

  // RESET


/*
void blueButton()
{
  blue= HIGH;
}

void whiteButton()
{
  white = HIGH;
}
*/


void softwareReset() 
// Restarts program from beginning but does not reset the peripherals and registers
{
  boolean reset = true;
  asm volatile ("  jmp 0");  
}

