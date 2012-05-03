#include "Snake.h"
Snake::Snake(int s)
{
	sizee = s;
	cube = new Cube(s,s,s);
        grow = false;
        gameover = false;
	Reset();
}
void Snake::Reset()
{
    if(snake != 0)
    {
	snake->Clear();
	snake->AddToBack(new PointList(1,0,0));
    }
    else
    snake = new PointList(1,0,0);
    PointList* p3 = new PointList(2,0,0);
    snake->AddToBack(p3);
	//snake.AddToBack(new PointList(3,0,0));
}
PointList* Snake::SpawnApple()
{
	 PointList* p = new PointList(2,2,2);//new PointList(random(sizee),random(sizee),random(sizee));
	 if(!CheckIfInsidePlayer(p))
	 {
		 //delete p;
		 return SpawnApple();
	 }
          //Serial.println("SPAWNAPPLE");
         return p;
}
bool Snake::CheckIfInsidePlayer(PointList* p)
{
	PointList* p2 = snake;
        if(p2->x == p->x && p2->y == p->y && p2->z == p->z)
	{
             return true;
	}
        while(p2->next != 0)
        {
            p2 = snake;
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
	grow = false;
	delete apple;
	apple = SpawnApple();
}
void Snake::Draw()
{
	cube->clear();
	
	PointList* p = snake;
	cube->setHIGH(p->x,p->y,p->z);
	while(snake->next != 0)
	{
		p = snake->next;
		cube->setHIGH(p->x,p->y,p->z);
	}
	
	cube->setHIGH(apple->x,apple->y,apple->z);
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
              //  Serial.println("GROW");
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
                //Serial.println("WALL");
	        delete p;
		GameOver();
	}
        if(!gameover)
        {
            Serial.println("ADDING");
            Serial.println(p->z);
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
            Serial.println(snake->next->z);
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
        int x = snake->x;
        Serial.println(x);
        int y = snake->y;
        Serial.println(y);
        int z = snake->z + 1;
        Serial.println(z);
	Move(x,y,z);
}
