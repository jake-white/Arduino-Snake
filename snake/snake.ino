void setup() {
  // put your setup code here, to run once:
  

}
int snakeLength = 3, foodSince;
int flash, tickTime = 500;
int snakeX[] = {1, 2, 3};
int snakeY[] = {3, 3, 3};
int sizeX = 6, sizeY = 6;

void loop() {
  // put your main code here, to run repeatedly:  
  if(flash < 7)
    ++flash;
  else
    flash = 0;
}

void generatePoint()
{
  bool continue = false;
  while(continue)
  {
    continue = false;
    int randomX = random(0, sizeX), randomY = random(0, sizeY);
    for(int i = 0; i < snakeX.length; ++i)
    {
     if(randomX == snakeX[i] && randomY == snakeY[i])
      {
       continue = true;
      } 
    }
  }
  
}
