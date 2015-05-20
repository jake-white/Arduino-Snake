int lastTime, rightButton = 11, downButton = 9, leftButton = 10, upButton = 12, LSB = 8, MSB = 7, HSB = 6;
void setup() {
  // put your setup code here, to run once:
  generatePoint();
  lastTime = millis();
  pinMode(LSB, OUTPUT);
  pinMode(MSB, OUTPUT);
  pinMode(HSB, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
}
int snakeLength = 3, foodSince;
int flash, tickTime = 500;
int snakeX[] = {1, 2, 3};
int snakeY[] = {3, 3, 3};
int sizeX = 6, sizeY = 6, foodX, foodY, xDirection = 1, yDirection = 0;
int direction;
bool killTail = true;

void loop() {
  // put your main code here, to run repeatedly:
  if(flash < 7)
    ++flash;
  else
    flash = 0;
  if(millis() - lastTime > tickTime)
  {
    tick();
  }
  output();
}

void output()
{
  bool gridArray[6][6];
  for(int x = 0; x < snakeLength; ++x)
  {
    for(int y = 0; y < snakeLength; ++y)
    {
      for(int c = 0; c < snakeLength; ++c)
      {
        if(snakeX[c] == x && snakeY[c] == y)
        {
          gridArray[x][y] = HIGH;
          break;
        }
        else
          gridArray[x][y] = LOW;
      }
    }
  }
  switch(flash)
  {
  case 0:
    flashClock(false, false, false);
    outputPart(gridArray[1][4], gridArray[1][2], gridArray[1][0], gridArray[4][4], gridArray[4][0]);
    break;
  case 1:
    flashClock(true, false, false); 
    break;
  case 2:
    flashClock(false, true, false); 
    break;
  case 3:
    flashClock(true, true, false); 
    break;
  case 4:
    flashClock(false, false, true); 
    break;
  case 5:
    flashClock(true, false, true); 
    break;
  case 6:
    flashClock(false, true, true); 
    break;
  case 7:
    flashClock(true, true, true); 
    break;
  }
}

void flashClock(bool L, bool M, bool H)
{  
  if(L)
    digitalWrite(LSB, HIGH);
  else
    digitalWrite(LSB, LOW);  
  if(M)
    digitalWrite(MSB, HIGH);
  else
    digitalWrite(MSB, LOW);
  if(H)
    digitalWrite(HSB, HIGH);
  else
    digitalWrite(HSB, LOW);
}
void tick()
{  
  int snakeLength = sizeof(snakeX)/sizeof(int);
  getInputs();
  advanceSnake();
  checkFood();
  checkDeath();
  lastTime = millis();
}

void getInputs()
{  
  switch(direction)
  {
    case 0: //right
    xDirection = 1;
    yDirection = 0;
    break;
    case 1: //down
    xDirection = 0;
    yDirection = 1;
    break;
    case 2: //left
    xDirection = -1;
    yDirection = 0;
    break;
    case 3: //up
    xDirection = 0;
    yDirection = -1;
    break;
  }
}

void advanceSnake()
{
  for(int i = snakeLength - 1; i > 0; --i)
  {
   snakeX[i] = snakeX[i - 1];
   snakeY[i] = snakeY[i - 1];
  }
  snakeX[0] = snakeX[1] + xDirection;
  snakeY[0] = snakeY[1] = yDirection;
}

void generatePoint()
{
  int randomX, randomY;
  bool continueGenerating = false;
  while(continueGenerating)
  {
    continueGenerating = false;
    randomX = random(0, sizeX), randomY = random(0, sizeY);
    for(int i = 0; i < snakeLength; ++i)
    {
     if(randomX == snakeX[i] && randomY == snakeY[i])
      {
       continueGenerating = true;
      } 
    }
  }
  foodX = randomX;
  foodY = randomY;  
}
void checkFood()
{
  for(int x = 0; x < snakeLength; ++x)
  {
    for(int y = 0; y < snakeLength; ++y)
    {  
      if(snakeX[x] == foodX && snakeY[y] == foodY)
      {
        ++foodSince;
        if(foodSince >= 3)
       { 
        killTail = false;
        generatePoint();
       }
      }
  }
  }
}
void checkDeath()
{
  
}
