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
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2),buttonHandler, FALLING);
  attachInterrupt(digitalPinToInterrupt(10), blueButton , CHANGE);
  attachInterrupt(digitalPinToInterrupt(11), whiteButton ,CHANGE);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  Serial.print("Welcome to 192L Blackjack!");
  Serial.println("\nPlayer 1, please make your call (hit/stay).");
}

void loop(){
	//Read our button if high then run dice
  if (buttonState==HIGH) 
  {
    debounce();
  }
  if (blue == HIGH) 
  {
    Serial.println("Blue INTERRUPT");
  }
  if (white==HIGH){
    Serial.println("White INTERRUPT");
  }
 
	if ( state == 0 && digitalRead(button) == HIGH)
	{
		state = 1;
		randNumber = random(1, 7);
		delay(150);
		//Serial.println(randNumber);

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
   
		delay(500);
		clearAll();
		state = 0;
	}
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
    if (digitalRead(11) == HIGH) 
    {
      Serial.println("\nStay");
      stay();
    }
    
    else if (digitalRead(10) == HIGH)
    {
     Serial.println("\nHit");
     hit();
    }
   
  }
  lastInterruptTime = interruptTime;

  
}

void stay()
{
  if (playerNumber==1) 
  {
    Serial.println ("Player 2's Turn");
    playerNumber=2;
  }
  else 
  {
    Serial.println ("Player 1's Turn");
    playerNumber = 1;
  }
}

void hit()
{
  if (playerNumber == 1) 
  {
    Serial.println(randNumber);
    score1 += randNumber;
    Serial.println("Player 1 score: ");
    Serial.print(score1);
  }
  else if (playerNumber == 2) 
  {
    Serial.println(randNumber);
    score2 += randNumber;
    Serial.println("Player 2 score: ");
    Serial.print(score2);
  }


  if (score1 > 21) 
  {
    Serial.println("\nPlayer 1 is bust!");
  }

  if (score2 > 21) 
  {
    Serial.println("\nPlayer 2 is bust!");
  }

}

void buttonHandler()
{
  
  buttonState = HIGH;

}

void blueButton()
{
  blue= HIGH;
}

void whiteButton()
{
  white = HIGH;
}
