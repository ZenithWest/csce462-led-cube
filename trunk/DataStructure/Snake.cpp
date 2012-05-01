#include "Snake.h"
Snake::Snake(int s)
{
	size = s;
	cube = new Cube(s,s,s);
	Reset();
}
void Snake::Reset()
{
	while(snake.size() > 0)
	{
		Point* p = snake.front();
		delete p;
		snake.erase(snake.begin(), p);
	}
	snake.push_back(new Point(1,0,0));
	snake.push_back(new Point(2,0,0));
	snake.push_back(new Point(3,0,0));
}
Point* Snake::SpawnApple()
{
	 Point* p = new Point(random(size),random(size),random(size));
	 if(!CheckIfInsidePlayer(p))
	 {
		 delete p;
		 return SpawnApple();
	 }
	 return p;
}
bool Snake::CheckIfInsidePlayer(Point* p)
{
	for(int i = 0; i <= snake.size(); i++) {
		if(snake[i]->x == p->x && snake[i]->y == p->y && snake[i]->y == p->y)
			return false;
	}
	return true;
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
	for(int i = 0; i <= snake.size(); i++) {
		cube->setHIGH(*(snake[i]));
	}
	cube->setHIGH(*(apple));
}
void Snake::Move(int x, int y, int z)
{
	if(x == apple->x && y == apple->y && z == apple->z)
		EatApple();
	Point* p = new Point(x,y,z);
	if(grow)
	{
		snake.insert(snake.begin(),p);
		return;
	}
	if(CheckIfInsidePlayer(p))
	{
		delete p;
		GameOver();
	}
	if(x < 0 || y < 0 || z < 0 ||
		x >= size || y >= size || z >= size)
	{
		delete p;
		GameOver();
	}
	snake.insert(snake.begin(),p);
	snake.erase(snake.begin() + snake.size()-1);
}
void Snake::GameOver()
{
	Reset();
}
void Snake::Move()
{
	//This Function needs to be called every XXXXX seconds? Not sure where we want to do it
	//Get From joystick TODO
	Move(0,0,1);
}