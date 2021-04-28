
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#define SPLASHTIME 3000
#define INIT_SNAKE 2

BOOL drawSnake();
BOOL moveSnake();
BOOL inBounds();
BOOL getTouchEvent();
BOOL checkSnakeCollision();
void growSnake();
void spawnFood();

void _INIT ProgramInit(void)
{
	startTime = clock_ms();	
	gHTML_Link;
	
}


void _CYCLIC ProgramCyclic(void)
{
	
	

	if (!gVisHandle) {
		gVisHandle = VA_Setup(1, "Visu");
	}
	
	switch(gCurrentPage)
	{
		case 0:
			elapsedTime = clock_ms() - startTime;
			gChangeToPage = (elapsedTime > SPLASHTIME);
			break;
		case 1:
			if (startButton)
				gChangeToPage = 2;
			break;
		case 2:
			
			if (!gameStarted){

				initSnake();
				currDirection = Right;
				gameStarted = 1;
				lockDown, lockLeft, lockRight, lockUp = 1;
				spawnFood();
				lastDrawTime = 0;
			} 
			
			
			
			if (quitButton){
			gameStarted = 0;
			gChangeToPage = 1;
			}
			
			
			timeToDraw = ((clock_ms() - lastDrawTime) >= REFRESH_MS);
			if (!gameOver){
				if (timeToDraw && drawSnake(gVisHandle, Green)){
					lastDrawTime = clock_ms();
					gameOver = (!moveSnake(currDirection));
				}
			
			}
			else{
				drawSnake(gVisHandle, Red);
				int time = clock_ms();
				while ((clock_ms() - time <= 1000))
					if (getTouchEvent(gVisHandle))
						break;	
					gameStarted = 0;
					gameOver = 0;
				}
				
			
			
			break;
			
	}
		
}


void _EXIT ProgramExit(void)
{

}

			
BOOL getTouchEvent(UDINT handle){
	if (!VA_Saccess(1, handle)){
		TouchAction touch;
		VA_GetTouchAction(1, gVisHandle, 1, (UDINT) &touch);
		VA_Srelease(1, handle);
		return (touch.status == 1);
	}
}
			

BOOL drawSnake(UDINT handle, Color c) {
	while(VA_Saccess(1, handle)){;}
	while(VA_Attach(1, handle, 0, (UDINT) &"Main/Buttons/PlayArea")){;}
	VA_Rect(1, handle, 0, 0, 780, 340, 248, 0);
	int i;
	for (i = 0; i <= snakeSize; i++)
		VA_Rect(1, handle, snakeArray[i].xLoc, snakeArray[i].yLoc, BLOCK_SIZE, BLOCK_SIZE, c, 0);
	VA_Rect(1, handle, foodSquare.xLoc, foodSquare.yLoc, BLOCK_SIZE, BLOCK_SIZE, 67, 0);
	VA_Detach(1, handle);
	VA_Srelease(1, handle);
	return 1;
}


BOOL moveSnake(Direction dir){
	int xL = snakeArray[0].xLoc;
	int yL = snakeArray[0].yLoc;
	switch(dir)
	{
		case Left:
			lockRight = 0;
			lockLeft = 1;
			lockUp = 1;
			lockDown = 1;
			xL -= BLOCK_SIZE;
			break;
		case Right:
			lockRight = 1;
			lockLeft = 0;
			lockUp = 1;
			lockDown = 1;
			xL += BLOCK_SIZE;
			break; 
		case Up:
			lockRight = 1;
			lockLeft = 1;
			lockUp = 1;
			lockDown = 0;
			yL -= BLOCK_SIZE;
			break;
		case Down:
			lockRight = 1;
			lockLeft = 1;
			lockUp = 0;
			lockDown = 1;
			yL += BLOCK_SIZE;
			break;
	}
	if(checkSnakeCollision(xL,yL)){
		int i;

		for (i = snakeSize; i != 0; i--){
			snakeArray[i].xLoc = snakeArray[i-1].xLoc;
			snakeArray[i].yLoc = snakeArray[i-1].yLoc;
		}
		snakeArray[0].xLoc = xL;
		snakeArray[0].yLoc = yL;
		
		if (snakeArray[0].xLoc == foodSquare.xLoc && snakeArray[0].yLoc == foodSquare.yLoc){
			growSnake();
			spawnFood();
		}
		return 1;
	}
	return 0;
}


void spawnFood(){
	srand(clock_ms());
	
	int xLoc = rand() % (X_LIM);
	
	xLoc += (BLOCK_SIZE-(xLoc % BLOCK_SIZE ?: BLOCK_SIZE));
	if (xLoc >= X_LIM)
		xLoc = X_LIM - BLOCK_SIZE;
	
	
	srand(clock_ms() + gVisHandle);
	
	int yLoc = rand() % (Y_LIM);
	yLoc += (BLOCK_SIZE-(yLoc % BLOCK_SIZE ?: BLOCK_SIZE));
	
	if (yLoc >= Y_LIM)
		yLoc = Y_LIM - BLOCK_SIZE;
		
	foodSquare.xLoc = xLoc;
	foodSquare.yLoc = yLoc;
}

	
void initSnake(){
	snakeSize = 2;
	snakeArray[2].xLoc = 160;
	snakeArray[2].yLoc = 200;
	snakeArray[1].xLoc = 180;
	snakeArray[1].yLoc = 200;
	snakeArray[0].xLoc = 200;
	snakeArray[0].yLoc = 200;
}	
	
void growSnake(){
	int i;
	for (i = snakeSize+1; i <= (snakeSize + 2) ; i++){
		snakeArray[i].xLoc = snakeArray[i-1].xLoc;
		snakeArray[i].yLoc = snakeArray[i-1].yLoc;
	}
	snakeSize += 2;
}

BOOL checkSnakeCollision(int x, int y){
	int i;
	for (i = 1; i <= snakeSize; i++)
		if (x == snakeArray[i].xLoc && y == snakeArray[i].yLoc)
			return 0;
	return (x <= X_LIM && x >= 0 && y <= Y_LIM && y >= 0);
}


	