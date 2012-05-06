#include "Snake.h"
Snake::Snake(Cube* c, int s)
{
	sizee = s;
	cube = c;
        grow = false;
        gameover = false;
        snake = 0;
	Reset(); 
}
void Snake::Reset()
{
    if(snake != 0)
    {
	//snake->Clear();
	//snake->AddToBack(new PointList(1,0,0));
    }
    else{}
    snake = new PointList(1,0,0);
    PointList* p3 = new PointList(2,0,0);
    snake->AddToBack(p3);
    
    PointList* p4 = new PointList(2,1,0);
    snake->AddToBack(p4);
    PointList* p5 = new PointList(2,2,0);
    snake->AddToBack(p5);
    apple = SpawnApple();
}
int aaa = 0;
PointList* Snake::SpawnApple()
{
         aaa = aaa+1;
	 PointList* p;
         if(aaa == 1)
             p = new PointList(0,2,0);//new PointList(random(sizee),random(sizee),random(sizee));
         else
             p = new PointList(0,2,0);
	 if(CheckIfInsidePlayer(p))
	 {
		// delete p;
		// return SpawnApple();
	}
         //Serial.println("SPAWNAPPLE");
          apple = p;
         return p;
}
bool Snake::CheckIfInsidePlayer(PointList* p)
{
	PointList* p2 = snake;
        if(p2->x == p->x && p2->y == p->y && p2->z == p->z)
	{
             return true;
	}
        p2 = snake;
        while(p2->next != 0)
        {
            if(p2->x == p->x && p2->y == p->y && p2->z == p->z)
    	    {  
                 return true;
    	    }
            p2 = p2->next;
        }
        return false;
}
void Snake::EatApple()
{
	grow = true;
	delete apple;
	apple = SpawnApple();
}
void Snake::Draw()
{
	cube->clear();
	
	PointList* p = snake;
	cube->setHIGH(p->x,p->y,p->z);
       // cube->setHIGH(2,2,2);
         while(p->next != 0)
	{
		p = p->next;
		cube->setHIGH(p->x,p->y,p->z);
	}
	
	cube->setHIGH(apple->x,apple->y,apple->z);
	
	cube->BW_WritePins();
}
void Snake::Move(int x, int y, int z)
{
        if(gameover)
          return;
        Serial.println("MOVE");
        
       	if(x == apple->x && y == apple->y && z == apple->z)
         {
                Serial.println("EAT APPLE");
		EatApple();
         }
	PointList* p = new PointList(x,y,z);
        
	if(grow)
	{
                Serial.println(99);
		snake = snake->AddToFront(p);
                grow = false;
		return;
	}
       if(CheckIfInsidePlayer(p))
	{
              // Serial.println("ITSELF");
	       delete p;
	       GameOver();
                
	}

	if(x < 0 || y < 0 || z < 0 || x >= sizee || y >= sizee || z >= sizee)
	{
                Serial.println(88);
	        delete p;
		GameOver();
	}
        if(!gameover)
        {
            int ssss = 0;
            
            PointList* p34 = snake;
            while(p34->next != 0)
            {
              p34 = p34->next;
              ssss = ssss + 1;
            }
            Serial.println(ssss);
            //Serial.println(ssss);
            Serial.println("ADDING");
            
            snake = snake->AddToFront(p);
            snake->DeleteEnd();
            /*Serial.println(p->z);
          //  delete p;
           // snake->Print();
            Serial.println(snake->next->x);
            Serial.println(snake->next->y);
            Serial.println(snake->next->z);
    	snake = snake->AddToFront(p);
    
            Serial.println(snake->next->x);
            Serial.println(snake->next->y);
            Serial.println(snake->next->z);
    	snake->DeleteEnd();
     Serial.println(snake->next->x);
            Serial.println(snake->next->y);
            Serial.println(snake->next->z);*/
        }
}
void Snake::GameOver()
{
  Serial.println("GAMEOVER");
  gameover = true;
	//Reset();
}
void Snake::Move()
{
      if(!gameover)
      { 
        int x = snake->x;
        Serial.println(x);
        int y = snake->y;
        Serial.println(y);
        int z = snake->z + 1;
        Serial.println(z);
        Serial.println(apple->x);
        Move(x,y,z);
      }
	
}
void Snake::Move(int x, int y)
{
    int x1 = snake->x;
   
    int y1 = snake->y;

    int z1 = snake->z;
    
    Serial.println("HEAD VALUES");  
    Serial.println(x1);
    Serial.println(y1);
    Serial.println(z1);
    
    if(x > 700)
    {
      if(y >700)
      {
          z1 = z1 +1; 
      }
      else
      {
          x1 = x1 + 1;
      }
    }
    else if(x < 300)
    {
      if(y < 300)
      {
          z1 = z1 -1; 
      }
      else
      {
          x1 = x1 - 1;
      }
    }
    else if(y > 700)
    {
      y1 = y1 + 1;
    }
    else if( y < 300)
    {
      y1 = y1-1;
    }
    else
      z1 = z1 + 1;
    Serial.println("MOVE HERE");  
    Serial.println(x1);
    Serial.println(y1);
    Serial.println(z1);
    Draw();
    Move(x1,y1,z1);
}
