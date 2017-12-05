#include <LedControl.h>

LedControl lc = LedControl(12, 11, 10, 1); // the number of the LED pin
const int BUTTON = 2;     // the number of the pushbutton pin

struct tailCoord{
  int iTail;
  int jTail;
} tail[100];

// i and j are Head's Coord
int i = random(8), j = random(8);
int iApple = random(8), jApple = random(8);
int tailLength = 0, score = 0, snakeSpeed = 400;
int prevI, prevJ, prevSecondI, prevSecondJ;
int changeDirection = 0, gameOver = -1;
// variable for reading the pushbutton status
int buttonState = 0;  

void setup() {

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  
  lc.shutdown(0,false); // turn off power saving, enables display
  lc.setIntensity(0,3); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);
  
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON, INPUT);
}

void updateTail(){
    prevI = tail[0].iTail;
    prevJ = tail[0].jTail;

    // connect the head and the tail
    tail[0].iTail = i;
    tail[0].jTail = j;

    // move the tail
    for(int q = 1; q < tailLength; q++)
    {
        prevSecondI = tail[q].iTail;
        prevSecondJ = tail[q].jTail;
        tail[q].iTail = prevI;
        tail[q].jTail = prevJ;
        prevI = prevSecondI;
        prevJ = prevSecondJ;
    }
}

void printTail(){
  // print the tail
  for(int q = 0; q < tailLength; q++)
      lc.setLed(0, tail[q].iTail, tail[q].jTail, true);
   
  delay(snakeSpeed);
  
  // erase head
    lc.setLed(0, i, j, false);
  // erase tail
    for(int q = 0; q < tailLength; q++)
        lc.setLed(0, tail[q].iTail, tail[q].jTail, false);
}

void eatApple(){
  lc.setLed(0, iApple, jApple, false);
    iApple = random(8); 
    jApple = random(8);
  lc.setLed(0, iApple, jApple, true);
    score = score + 10;  
    tailLength++;

  if(snakeSpeed > 100)
    snakeSpeed = snakeSpeed - 5;
}

void hitTail(){
  for(int q = 0; q < tailLength; q++)
    if(tail[q].iTail == i && tail[q].jTail == j)
      gameOver = 1;
}

void loop() {
  
  int yjoy = analogRead(A1)/146;
  int xjoy = analogRead(A0)/146;
  buttonState = digitalRead(BUTTON);

  while(gameOver == -1){
    // scrolling: SNAKE until button pressed
      letterS();
      
      delay(100);
      buttonState = digitalRead(BUTTON);
      if (buttonState == HIGH && gameOver != 4){
        gameOver = 0; 
        break;
      }
      
      letterN();
      
      delay(100);
      buttonState = digitalRead(BUTTON);
      if (buttonState == HIGH && gameOver != 4){
        gameOver = 0; 
        break;
      }
      letterA();
      
      delay(100);
      buttonState = digitalRead(BUTTON);
      if (buttonState == HIGH && gameOver != 4){
        gameOver = 0; 
        break;
      }
      
      letterK();
      
      delay(100);
      buttonState = digitalRead(BUTTON);
      if (buttonState == HIGH && gameOver != 4){
        gameOver = 0; 
        break;
      }
      
      letterE();
      
      delay(100);
      buttonState = digitalRead(BUTTON);
      if (buttonState == HIGH && gameOver != 4){
        gameOver = 0; 
        break;
      } 
  }

  if (buttonState == HIGH && gameOver != 4)
         gameOver = 0; 

  if(gameOver == 0){
    lc.setLed(0, iApple, jApple, true);
      
      if(xjoy == 3 && yjoy == 3){
        lc.setLed(0, i, j, true);
        delay(snakeSpeed);
        lc.setLed(0, i, j, false);
      }
    
      // going up
      if(xjoy == 3 && yjoy > 3){
        int k;
        changeDirection = 0;
        for(k = j; changeDirection == 0; k--){
            hitTail();
            if(gameOver == 1)
              break;
            if(k < 0){
              k = 8;
              j = 8;
            }
            updateTail();
            lc.setLed(0, i, --j, true); //print the head
            printTail();
    
            if(i == iApple && j == jApple)
              eatApple();
              
            yjoy = analogRead(A1)/146;
            xjoy = analogRead(A0)/146;
            if(xjoy < 3 || xjoy > 3)
              changeDirection = 1;
        }
      }
      
      // going left
      if(xjoy > 3 && yjoy == 3){
        int k;
        changeDirection = 0;
        for(k = i; changeDirection == 0; k++){
            hitTail();
            if(gameOver == 1)
              break;
              
            if(k >= 8){
              k = -1;
              i = -1;
            }
            
            updateTail();
            lc.setLed(0, ++i, j, true);
            printTail();
            
            if(i == iApple && j == jApple)
              eatApple();
             
            yjoy = analogRead(A1)/146;
            xjoy = analogRead(A0)/146;
            if(yjoy > 3 || yjoy < 3)
              changeDirection = 1;
        }
      }
    
      // going down
      if( xjoy == 3 && yjoy < 3){
        int k;
        changeDirection = 0;
        for(k = j; changeDirection == 0; k++){
            hitTail();
            if(gameOver == 1)
              break;
            if(k >= 8){
              k = -1;
              j = -1;
            }
            
            updateTail();
            lc.setLed(0, i, ++j, true);
            printTail();
            
            if(i == iApple && j == jApple)
              eatApple();
    
            yjoy = analogRead(A1)/146;
            xjoy = analogRead(A0)/146;
            if(xjoy < 3 || xjoy > 3)
              changeDirection = 1;
        }
      }
    
      // going right
      if(xjoy < 3 && yjoy == 3){
        int k;
        changeDirection = 0;
        for(k = i; changeDirection == 0; k--){
            hitTail();
            if(gameOver == 1)
              break;
            if(k <= 0){
              k = 8;
              i = 8;
            }
            
            updateTail();
            lc.setLed(0, --i, j, true);
            printTail();
            
            if(i == iApple && j == jApple)
              eatApple();
    
            yjoy = analogRead(A1)/146;
            xjoy = analogRead(A0)/146;
            if(yjoy > 3 || yjoy < 3)
              changeDirection = 1;
        }
      } 
  }
  else if(gameOver == 1){
    for (int row = 0; row < 8; row++){
      for (int col = 0; col < 8; col++){
            lc.setLed(0, col, row, true); // turns on LED at col, row
            delay(30);
      }
    }
       
    for (int row = 0; row < 8; row++){
      for (int col = 0; col < 8; col++){
            lc.setLed(0, col, row, false); // turns off LED at col, row
            delay(30);
      }
    }
        gameOver = 2;  
  }
  else if(gameOver == 2){
    // scrolling: SCORE: 305
      gameOver = 3;

      letterS(); letterC(); letterO(); letterR(); letterE(); colon();
      
      // X00 digit
      if(score/100 == 1)
        digit1();
      else if(score/100 == 2)
        digit2();
      else if(score/100 == 3)
        digit3();
      else if(score/100 == 4)
        digit4();
      else if(score/100 == 5)
        digit5();
      else if(score/100 == 6)
        digit6();
      else if(score/100 == 7)
        digit7();
      else if(score/100 == 8)
        digit8();
      else if(score/100 == 9)
        digit9();

    // X0X digit
      if(score%100/10 == 1)
        digit1();
      else if(score%100/10 == 2)
        digit2();
      else if(score%100/10 == 3)
        digit3();
      else if(score%100/10 == 4)
        digit4();
      else if(score%100/10 == 5)
        digit5();
      else if(score%100/10 == 6)
        digit6();
      else if(score%100/10 == 7)
        digit7();
      else if(score%100/10 == 8)
        digit8();
      else if(score%100/10 == 9)
        digit9();
      else if(score%100/10 ==0)
        digit0();

    // XX0 digit
      digit0();
  }

  if(gameOver == 3){
    while(gameOver == 3){
      for (int row = 0; row < 8; row++){
          for (int col = 0; col < 8; col++){
            lc.setLed(0, col, row, true); // turns on LED at col, row
            buttonState = digitalRead(BUTTON);
              if (buttonState == HIGH && gameOver != 4)
                gameOver = 4;
            delay(30);
            buttonState = digitalRead(BUTTON);
              if (buttonState == HIGH && gameOver != 4)
                gameOver = 4;
          }
        }

        buttonState = digitalRead(BUTTON);
              if (buttonState == HIGH && gameOver != 4){
                gameOver = 4; 
                break;
              } 
       
        for (int row = 0; row < 8; row++){
          for (int col = 0; col < 8; col++){
            lc.setLed(0, col, row, false); // turns off LED at col, row
            buttonState = digitalRead(BUTTON);
              if (buttonState == HIGH && gameOver != 4)
                gameOver = 4;
            delay(30);
            buttonState = digitalRead(BUTTON);
              if (buttonState == HIGH && gameOver != 4)
                gameOver = 4;
          }
        }   
    }
    
    letterS();
    letterE();
    letterE();
      delay(300);
    letterY();
    letterA();
      delay(300);
    letterS();
    digit0();
    digit0();
    letterN();
      exclamation(); 
  }
}

// ************ \\
// LETTERS CODE \\
// ************ \\

void letterO(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,2,4,true);

  //little right bar
  lc.setLed(0,2,5,true);
  lc.setLed(0,2,3,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,2,4,false);

  //little right bar
  lc.setLed(0,2,5,false);
  lc.setLed(0,2,3,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void letterC()
{
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
}

void letterR()
{
  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //bottom arm
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,5,true);
  lc.setLed(0,2,6,true);

  //top round
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);
  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,2,4,true);
  //little right
  lc.setLed(0,2,3,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //bottom arm
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,5,false);
  lc.setLed(0,2,6,false);

  //top round
  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);
  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,2,4,false);
  //little right
  lc.setLed(0,2,3,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void colon()
{
  lc.setLed(0,4,3,true);
  lc.setLed(0,3,3,true);

  lc.setLed(0,4,5,true);
  lc.setLed(0,3,5,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  lc.setLed(0,4,3,false);
  lc.setLed(0,3,3,false);

  lc.setLed(0,4,5,false);
  lc.setLed(0,3,5,false);

  delay(700);
}

void exclamation()
{
  lc.setLed(0,4,3,true);
  lc.setLed(0,3,3,true);

  lc.setLed(0,4,2,true);
  lc.setLed(0,3,2,true);

  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);

  lc.setLed(0,4,6,true);
  lc.setLed(0,3,6,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  lc.setLed(0,4,3,false);
  lc.setLed(0,3,3,false);

  lc.setLed(0,4,2,false);
  lc.setLed(0,3,2,false);

  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);

  lc.setLed(0,4,6,false);
  lc.setLed(0,3,6,false);

  delay(400);
}

void letterU()
{
  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,2,4,true);

  //little right bar
  lc.setLed(0,2,5,true);
  lc.setLed(0,2,3,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,2,4,false);

  //little right bar
  lc.setLed(0,2,5,false);
  lc.setLed(0,2,3,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void letterS()
{
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);

  lc.setLed(0,2,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,5,4,true);

  lc.setLed(0,2,5,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  buttonState = digitalRead(BUTTON);
  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  buttonState = digitalRead(BUTTON);
      
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);

  lc.setLed(0,2,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,5,4,false);

  lc.setLed(0,2,5,false);

  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);
      
  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void letterN(){
  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  lc.setLed(0,4,2,true);
  lc.setLed(0,4,3,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,5,true);
  lc.setLed(0,3,6,true);

  //right bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,2,3,true);
  lc.setLed(0,2,4,true);
  lc.setLed(0,2,5,true);
  lc.setLed(0,2,6,true);
  
  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  lc.setLed(0,4,2,false);
  lc.setLed(0,4,3,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,5,false);
  lc.setLed(0,3,6,false);

  lc.setLed(0,2,2,false);
  lc.setLed(0,2,3,false);
  lc.setLed(0,2,4,false);
  lc.setLed(0,2,5,false);
  lc.setLed(0,2,6,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void letterA(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //right bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,2,3,true);
  lc.setLed(0,2,4,true);
  lc.setLed(0,2,5,true);
  lc.setLed(0,2,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,2,4,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //right bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,2,3,false);
  lc.setLed(0,2,4,false);
  lc.setLed(0,2,5,false);
  lc.setLed(0,2,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,2,4,false);
  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

}

void letterY(){
  lc.setLed(0,4,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,5,true);
  lc.setLed(0,3,5,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,2,true);
  lc.setLed(0,2,3,true);
  lc.setLed(0,2,2,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  lc.setLed(0,4,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,5,false);
  lc.setLed(0,3,5,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,2,false);
  lc.setLed(0,2,3,false);
  lc.setLed(0,2,2,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void letterK(){
  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //top arm
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,3,true);
  lc.setLed(0,2,2,true);

  //bottom arm
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,5,true);
  lc.setLed(0,2,6,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //top arm
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,3,false);
  lc.setLed(0,2,2,false);

  //bottom arm
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,5,false);
  lc.setLed(0,2,6,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void letterE(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,2,4,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,2,4,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit1()
{
  lc.setLed(0,3,2,true);
  lc.setLed(0,3,3,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,3,5,true);
  lc.setLed(0,3,6,true);

  lc.setLed(0,4,3,true);
  lc.setLed(0,5,4,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  lc.setLed(0,3,2,false);
  lc.setLed(0,3,3,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,3,5,false);
  lc.setLed(0,3,6,false);

  lc.setLed(0,4,3,false);
  lc.setLed(0,5,4,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit2()
{
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  lc.setLed(0,2,3,true);

  lc.setLed(0,2,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,5,4,true);

  lc.setLed(0,5,5,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);
      
  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  lc.setLed(0,2,3,false);

  lc.setLed(0,2,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,5,4,false);

  lc.setLed(0,5,5,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);
  
  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit3()
{
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //right bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,2,3,true);
  lc.setLed(0,2,4,true);
  lc.setLed(0,2,5,true);
  lc.setLed(0,2,6,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,2,4,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //right bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,2,3,false);
  lc.setLed(0,2,4,false);
  lc.setLed(0,2,5,false);
  lc.setLed(0,2,6,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,2,4,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit4(){
  
  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,2,4,true);

  //straigth bar
  lc.setLed(0,3,2,true);
  lc.setLed(0,3,3,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,3,5,true);
  lc.setLed(0,3,6,true);

  //oblique bar
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,3,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,2,4,false);

  //straigth bar
  lc.setLed(0,3,2,false);
  lc.setLed(0,3,3,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,3,5,false);
  lc.setLed(0,3,6,false);

  //oblique bar
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,3,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

}

void digit5(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);

  lc.setLed(0,2,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,5,4,true);

  lc.setLed(0,2,5,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);
      
  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
      
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);

  lc.setLed(0,2,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,5,4,false);

  lc.setLed(0,2,5,false);

  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);
      
  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit6(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,2,4,true);

  //little right bar
  lc.setLed(0,2,5,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,2,4,false);

  //little right bar
  lc.setLed(0,2,5,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit7(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //tail bar
  lc.setLed(0,3,3,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,4,5,true);
  lc.setLed(0,4,6,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);

  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //tail bar
  lc.setLed(0,3,3,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,4,5,false);
  lc.setLed(0,4,6,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit8(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,2,4,true);

  //little right bar
  lc.setLed(0,2,5,true);
  lc.setLed(0,2,3,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,2,4,false);

  //little right bar
  lc.setLed(0,2,5,false);
  lc.setLed(0,2,3,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit9(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,6,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,3,4,true);
  lc.setLed(0,2,4,true);

  //little right bar
  lc.setLed(0,2,5,true);
  lc.setLed(0,2,3,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,6,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,4,4,false);
  lc.setLed(0,3,4,false);
  lc.setLed(0,2,4,false);

  //little right bar
  lc.setLed(0,2,5,false);
  lc.setLed(0,2,3,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

void digit0(){
  //top bar
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);

  //left bar
  lc.setLed(0,5,2,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,5,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,5,6,true);

  //bottom bar
  lc.setLed(0,2,6,true);
  lc.setLed(0,3,6,true);
  lc.setLed(0,4,6,true);
  lc.setLed(0,5,6,true);

  //middle bar
  lc.setLed(0,5,4,true);
  lc.setLed(0,2,4,true);

  //little right bar
  lc.setLed(0,2,5,true);
  lc.setLed(0,2,3,true);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
  
  //top bar
  lc.setLed(0,2,2,false);
  lc.setLed(0,3,2,false);
  lc.setLed(0,4,2,false);
  lc.setLed(0,5,2,false);

  //left bar
  lc.setLed(0,5,2,false);
  lc.setLed(0,5,3,false);
  lc.setLed(0,5,4,false);
  lc.setLed(0,5,5,false);
  lc.setLed(0,5,6,false);

  //bottom bar
  lc.setLed(0,2,6,false);
  lc.setLed(0,3,6,false);
  lc.setLed(0,4,6,false);
  lc.setLed(0,5,6,false);

  //middle bar
  lc.setLed(0,5,4,false);
  lc.setLed(0,2,4,false);

  //little right bar
  lc.setLed(0,2,5,false);
  lc.setLed(0,2,3,false);

  buttonState = digitalRead(BUTTON);   delay(400);   buttonState = digitalRead(BUTTON);
}

