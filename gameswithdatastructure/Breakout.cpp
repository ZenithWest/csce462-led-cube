#include "Breakout.h"

Breakout::Breakout(Cube* c, int s, int paddleSize)
{
	size = s;
	cube = c;
	Blocks = new Cube(s,s,s);
	p1 = new Paddle(paddleSize);
	ball = new Ball();
    gameover = false;
	
	Reset(); 
}
void Breakout::Reset()
{
    gameover = false;
	
	for(int i = 0; i<size; i++)
	{
		for(int j = 0; j<size; j++)
		{
			Blocks->setHIGH(i,j,size-1);
		}
	}
	
	ball->Position->x = 0;
	ball->Position->y = 0;
	ball->Position->z = 0;
	
	ball->Direction->x = 0;
	ball->Direction->y = 1;
    ball->Direction->z = 1;
        
       // Serial.println(ball->Direction->x);
	p1->Position->x = 0;
	p1->Position->y = 0;
	p1->Position->z = 0;
}

void Breakout::MovePaddle1(int x, int y)
{
  if(gameover)
          return;
	int x1 = 0;
	int y1 = 0;
	if(x >800)
		x1 = 1;
	if(x < 200)
		x1 = -1;
	if(y >800)
		y1 = 1;
	if(y < 200)
		y1 = -1;
      //  Serial.println(x1);
       
	MovePaddle(p1,x1,y1);
}
void Breakout::MovePaddle(Paddle* p, int x1, int y1)
{  
        if(gameover)
          return;
	PointList* pos = p->Position;
	int x = pos->x;
	int y = pos->y;
	int z = pos->z;
       
	if((x == 0 && x1 != -1) || (x+p->size==size && x1 != 1))
	{
               // Serial.println("CHANGED");
		pos->x = x1+x;
	}
	if((y == 0 && y1 != -1) || (y+p->size==size && y1 != 1))
	{
		pos->y = y1+y;
	}	
}

void Breakout::Draw()
{
	cube->clear();

	cube->setHIGH(ball->Position->x,ball->Position->y,ball->Position->z);
	
	for(int i = p1->Position->x; i < p1->Position->x + p1->size; i++)
	{
		for(int j = p1->Position->y; j < p1->Position->y + p1->size; j++)
		{
			cube->setHIGH(i,j,p1->Position->z);
		}	
    }
	
	for(int i = 0; i< size; i++)
	{
		for(int j = 0; j< size; j++)
		{
			for(int k = 0; k< size; k++)
			{
				if(Blocks->get(i,j,k) == 1)
				{
					cube->setHIGH(i,j,k);
				}
			}
		}
	}
	//cube->BW_WritePins();
}
void Breakout::MoveBall()
{
        if(gameover)
          return;
	int nx = ball->Direction->x + ball->Position->x;
	int ny = ball->Direction->y + ball->Position->y;
	int nz = ball->Direction->z + ball->Position->z;
        //Serial.println(nx);
        //Serial.println(nz);
	if(nx < 0)
	{
		ball->Direction->x = ball->Direction->x * -1;
		nx = ball->Direction->x + ball->Position->x;
	}
	if(nx >= size)
	{
		ball->Direction->x = ball->Direction->x * -1;
		nx = ball->Direction->x + ball->Position->x;
      
	}
	if(ny < 0)
	{
		ball->Direction->y = ball->Direction->y * -1;
		ny = ball->Direction->y + ball->Position->y;
	}
	if(ny >= size)
	{
		ball->Direction->y = ball->Direction->y * -1;
		ny = ball->Direction->y + ball->Position->y;
	}
	if(nz < 0)
	{
		GameOver();
		return;
	}
        if(nz >= size)
	{
		ball->Direction->z = ball->Direction->z * -1;
		nz = ball->Direction->z + ball->Position->z;
	}
        Serial.println("OVER");
        Serial.println(nx);
         Serial.println(ny);
        Serial.println(nz);
	PointList* p = p1->Position;
	int s = p1->size;
        boolean flag = true;
	if(p->z == nz)
	{
        Serial.println("PLAYER 1");
        int dx = p1->Position->x - nx;
        //  if(dx < 0) {dx *= -1;}
        int dy = p1->Position->y - ny;
        //if (dz <0) {dz *=-1;}
		if((dx <= 0 && dx*-1<p1->size)&& (dy <= 0 && dy*-1<p1->size) )
		{
            Serial.println("HIT");
            Serial.println(dx);
            Serial.println(dy);
			ball->Direction->z = 1;
            flag = false;
		}
	}
	if(Blocks->get(nx,ny,nz) == 1)
	{
		ball->Direction->z = 1;
		Blocks->setLOW(nx,ny,nz);
	}
    ball->Position->x = nx;
    ball->Position->y = ny;        
    ball->Position->z = nz;
	
    Serial.println("NEW");
        
    Serial.println(nx);   
    Serial.println(nz);
    Serial.println(ny);
}
void Breakout::GameOver()
{
	gameover = true;
	Serial.println("GAMEOVER");
}
