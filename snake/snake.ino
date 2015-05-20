int lastTime, rightButton = 11, downButton = 9, leftButton = 10, upButton = 12, LSB = 8, MSB = 7, HSB = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
int flash = 0, tickTime = 1000;
int snakeX[] = {1, 2, 3};
int snakeY[] = {3, 3, 3};
int sizeX = 6, sizeY = 6, foodX, foodY, xDirection = 1, yDirection = 0;
int direction;
bool alive = true;
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
//  if(alive)
  output();
}

void output()
{
  bool gridArray[6][6];
  int sum = 0;
  for(int x = 0; x < snakeLength; ++x)
  {
    for(int y = 0; y < snakeLength; ++y)
    {
      for(int c = 0; c < snakeLength; ++c)
      {
        if(snakeX[c] == x && snakeY[c] == y)
        {
          gridArray[x][y] = true;
          ++sum;
          break;
        }
        else
          gridArray[x][y] = false;
      }
    }
  }
  Serial.println(sum);
  switch(flash)
  {
  case 0:
    flashClock(false, false, false);
    outputPart(gridArray[1][4], gridArray[1][2], gridArray[1][0], gridArray[4][4], gridArray[4][0]);
    break;
  case 1:
    flashClock(true, false, false); 
    outputPart(gridArray[3][4], gridArray[3][2], gridArray[3][0], gridArray[5][4], gridArray[5][0]);
    break;
  case 2:
    flashClock(false, true, false); 
    outputPart(gridArray[0][4], gridArray[0][2], gridArray[0][0], gridArray[4][5], gridArray[4][1]);
    break;
  case 3:
    flashClock(true, true, false); 
    outputPart(gridArray[2][4], gridArray[2][2], gridArray[2][0], gridArray[5][5], gridArray[5][1]);
    break;
  case 4:
    flashClock(false, false, true); 
    outputPart(gridArray[1][5], gridArray[1][3], gridArray[1][1], getFoodLEDs(0), gridArray[4][2]);
    break;
  case 5:
    flashClock(true, false, true); 
    outputPart(gridArray[3][5], gridArray[3][3], gridArray[3][1], getFoodLEDs(1), gridArray[5][2]);
    break;
  case 6:
    flashClock(false, true, true); 
    outputPart(gridArray[0][5], gridArray[0][3], gridArray[0][1], getFoodLEDs(2), gridArray[4][3]);
    break;
  case 7:
    flashClock(true, true, true); 
    outputPart(gridArray[2][5], gridArray[2][3], gridArray[2][1], getFoodLEDs(3), gridArray[5][3]);
    break;
  }
}
void outputPart(bool a, bool b, bool c, bool d, bool e)
{
  if(a)
  digitalWrite(1, HIGH);
  else
  digitalWrite(1, LOW);
  if(b)
  digitalWrite(2, HIGH);
  else
  digitalWrite(2, LOW);
  if(c)
  digitalWrite(3, HIGH);
  else
  digitalWrite(3, LOW);
  if(d)
  digitalWrite(4, HIGH);
  else
  digitalWrite(4, LOW);
  if(e)
  digitalWrite(5, HIGH);
  else
  digitalWrite(5, LOW);
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
  if(alive)
  {
  advanceSnake();
  checkFood();
  checkDeath();
  }
  lastTime = millis();
 // Serial.print("[");
//  for(int i = 0; i < snakeLength; ++i)
//  {
//  Serial.print(snakeX[i]);
//  }
//  Serial.print("]");
//  Serial.println();
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

bool getFoodLEDs(int num)
{
  return false;
}

void checkDeath()
{
  if(snakeX[0] > 5 || snakeX[0] < 0 || snakeY[0] > 5 || snakeY[0] < 0 )
    alive = false;
  for(int i = 1; i < snakeLength; ++i)
  {
    if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
    alive = false;
  }
}
