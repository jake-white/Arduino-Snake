
  bool gridArray[6][6];
  int gridNextX[6][6];
  int gridNextY[6][6];
  int lastTime, rightButton = 11, downButton = 9, leftButton = 10, upButton = 12, LSB = 8, MSB = 7, HSB = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lastTime = millis();
  pinMode(LSB, OUTPUT);
  pinMode(MSB, OUTPUT);
  pinMode(HSB, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      gridArray[i][j] = false;
      gridNextX[i][j]=0;
      gridNextY[i][j]=0;
    }
  }
  for(int i =1; i <=3; i++){
     gridArray[i][3]=true;
    gridNextX[i][3]=1;
    
  }
}
int snakeHeadX=3,snakeHeadY=3;
int snakeTailX=1,snakeTailY=3;
int snakeLength = 3, foodSince;
int flash = 0, tickTime = 1000;
int sizeX = 6, sizeY = 6, foodX, foodY, xDirection = 1, yDirection = 0;
int direction=0;
bool alive = true;
bool killTail = true;

void loop() {
  // put your main code here, to run repeatedly:
  if (flash < 7)
    ++flash;
  else
    flash = 0;
  if (millis() - lastTime > tickTime)
  {
    tick();
  }
  listenForInputs();
  //  if(alive)
  output();
  delay(3);
}

void output()
{
  switch (flash)
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
void listenForInputs(){
 if(!digitalRead(rightButton)){
    direction=0;
 } 
 if(!digitalRead(downButton)){
    direction=1;
 } 
 if(!digitalRead(leftButton)){
    direction=2;
 } 
 if(!digitalRead(upButton)){
    direction=3;
 } 
}
void outputPart(bool a, bool b, bool c, bool d, bool e)
{
  if (a)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  if (b)
    digitalWrite(2, HIGH);
  else
    digitalWrite(2, LOW);
  if (c)
    digitalWrite(3, HIGH);
  else
    digitalWrite(3, LOW);
  if (d)
    digitalWrite(4, HIGH);
  else
    digitalWrite(4, LOW);
  if (e)
    digitalWrite(5, HIGH);
  else
    digitalWrite(5, LOW);
}

void flashClock(bool L, bool M, bool H)
{
  if (L)
    digitalWrite(LSB, HIGH);
  else
    digitalWrite(LSB, LOW);
  if (M)
    digitalWrite(MSB, HIGH);
  else
    digitalWrite(MSB, LOW);
  if (H)
    digitalWrite(HSB, HIGH);
  else
    digitalWrite(HSB, LOW);
}
void tick()
{
  getInputs();
  if (alive)
  {
    advanceSnake();
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
  switch (direction)
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
  Serial.print(snakeHeadX);
  Serial.print(snakeHeadY);
  Serial.print(snakeTailX);
  Serial.println(snakeTailY);
  if(!isValidPos(snakeHeadX+xDirection,snakeHeadY+yDirection)){
    return;//die logic here
  }
  //advance head
  gridArray[snakeHeadX+xDirection][snakeHeadY+yDirection]=true;
  gridNextX[snakeHeadX][snakeHeadY]=xDirection;
  gridNextY[snakeHeadX][snakeHeadY]=yDirection;
  
  //advance tail
  gridArray[snakeTailX][snakeTailY]=false;
  snakeTailX+=gridNextX[snakeTailX][snakeTailY];
  snakeTailY+=gridNextY[snakeTailX][snakeTailY];
  snakeHeadX+=xDirection;
  snakeHeadY+=yDirection;
  
  
}

bool getFoodLEDs(int num)
{
  return false;
}
bool isValidPos(int x,int y){
   return !(x<0||x>5||y<0||y>5); 
}
