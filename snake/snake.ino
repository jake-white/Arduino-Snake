int lastTime, rightButton = 1, downButton = 2, leftButton = 3, upButton = 4;
void setup() {
  // put your setup code here, to run once:
  generatePoint();
  lastTime = millis();
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
}
void tick()
{  
  Serial.print(sizeof(snakeX)/sizeof(int));
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
