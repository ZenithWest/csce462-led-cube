#include "Pong.h"

Pong::Pong(Cube* c, int s, int paddleSize)
{
	size = s;
	cube = c;
	p1 = new Paddle(paddleSize);
	p2 = new Paddle(paddleSize);
	ball = new PongBall();
    gameover = false;
	
	Reset(); 
}
void Pong::Reset()
{
        gameover = false;
	ball->Position->x = size/2;
	ball->Position->y = size/2;
	ball->Position->z = size/2;
	ball->Direction->x = random(3)-1;
	ball->Direction->y = random(3)-1;
        while(ball->Direction->y == 0)
          ball->Direction->y = random(3)-1;
        ball->Direction->z = random(3)-1;
        
       // Serial.println(ball->Direction->x);
	p1->Position->x = 0;
	p1->Position->y = 0;
	p1->Position->z = 0;
	p2->Position->x = 0;
	p2->Position->y = size-1;
	p2->Position->z = 0;
}
void Pong::MovePaddle1(int x, int y)
{
  if(gameover)
          return;
	int x1 = 0;
	int z1 = 0;
	if(x >800)
		x1 = 1;
	if(x < 200)
		x1 = -1;
	if(y >800)
		z1 = 1;
	if(y < 200)
		z1 = -1;
      //  Serial.println(x1);
       
	MovePaddle(p1,x1,z1);
	MovePaddle2();
}
void Pong::MovePaddle(Paddle* p, int x1, int z1)
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
	if((z == 0 && z1 != -1) || (z+p->size==size && z1 != 1))
	{
		pos->z = z1+z;
	}	
}
void Pong::MovePaddle2()
{
        if(gameover)
          return;
	int miss = random(5);
	if(miss <= 1)
	{
		return;
	}
	int x = 0;
	int z = 0;
	//int z = 0;
	if(ball->Position->x - p2->Position->x < 1)
		x = -1;
	if(p2->Position->x + p2->size-1 - ball->Position->x  < 1)
		x = 1;
	if(ball->Position->z - p2->Position->z < 1)
		z = -1;
	if(p2->Position->z + p2->size-1 - ball->Position->z < 1)
		z = 1;
	MovePaddle(p2, x, z);
}

void Pong::Draw()
{
	cube->clear();

	cube->setHIGH(ball->Position->x,ball->Position->y,ball->Position->z);
	
	for(int i = p1->Position->x; i < p1->Position->x + p1->size; i++)
	{
		for(int j = p1->Position->z; j < p1->Position->z + p1->size; j++)
		{
			cube->setHIGH(i,p1->Position->y,j);
		}	
        }
	
	for(int i = p2->Position->x; i < p2->Position->x + p2->size; i++)
	{
		for(int j = p2->Position->z; j < p2->Position->z + p2->size; j++)
		{
			cube->setHIGH(i,p2->Position->y,j);
		}
	}
	//cube->BW_WritePins();
}
void Pong::MoveBall()
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
	if(nz < 0)
	{
		ball->Direction->z = ball->Direction->z * -1;
		nz = ball->Direction->z + ball->Position->z;
	}
	if(nz >= size)
	{
		ball->Direction->z = ball->Direction->z * -1;
		nz = ball->Direction->z + ball->Position->z;
	}
	if(ny < 0 || ny >= size)
	{
		GameOver();
		return;
	}
        Serial.println("OVER");
        Serial.println(nx);
         Serial.println(ny);
        Serial.println(nz);
	PointList* p = p1->Position;
	int s = p1->size;
        boolean flag = true;
	if(p->y == ny)
	{
            Serial.println("PLAYER 1");
            int dx = p1->Position->x - nx;
          //  if(dx < 0) {dx *= -1;}
            int dz = p1->Position->z - nz;
            //if (dz <0) {dz *=-1;}
		if((dx <= 0 && dx*-1<p1->size)&& (dz <= 0 && dz*-1<p1->size) )
		{
                     Serial.println("HIT");
                     Serial.println(dx);
                     Serial.println(dz);
			ball->Direction->y = 1;
                        flag = false;
			//ny = ball->Direction->y + ball->Position->y;
                        
			/*int q = -1 * random(1);
			int w = -1 * random(1);
			if(q && w == 0)
			{
				q = -1;
			}
			ball->Direction->z = q;
			nz = ball->Direction->z + ball->Position->z;
			ball->Direction->x = w;
		nx = ball->Direction->x + ball->Position->x;*/
		}
	}
	p = p2->Position;
	s = p2->size;
	if(p->y == ny && flag)
	{
            Serial.println("PLAYER 2");
		int dx = p2->Position->x - nx;
          //  if(dx < 0) {dx *= -1;}
            int dz = p2->Position->z - nz;
            //if (dz <0) {dz *=-1;}
		if((dx <= 0 && dx*-1<p2->size)&& (dz <= 0 && dz*-1<p2->size) )
{
                         Serial.println("HIT");
			ball->Direction->y = -1;
			//ny = ball->Direction->y + ball->Position->y;
		}
	}
        ball->Position->x = nx;
           ball->Position->y = ny;
         
         ball->Position->z = nz;
        Serial.println("NEW");
        
        Serial.println(nx);
          
        Serial.println(nz);
        Serial.println(ny);
}
void Pong::GameOver()
{
  gameover = true;
  Serial.println("GAMEOVER");
}
