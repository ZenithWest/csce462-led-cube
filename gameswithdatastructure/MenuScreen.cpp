#include "MenuScreen.h"

MenuScreen::MenuScreen(Cube* c, int s)
{
	size = s;
	cube = c;
	
	Reset(); 
}
void MenuScreen::Reset()
{
    inMenu = true;
    minSelection = 0;
    maxSelection = 2;
	currentSelection = 0;
 counter = 0;
 timetoScroll = 50;
 countdown = 100;
}

void MenuScreen::Joystick(int x, int y)
{
    
	if(inMenu)
	{
		counter++;
		if(counter%timetoScroll == 0)
		{
                        Serial.println(currentSelection);
			if(x > 800)
			{
				CreateGame();
				return;
			}
                        
			if(y>800)
			{
				if(currentSelection > minSelection)
{
  
					currentSelection--;
}
			}
			if(y<200)
			{
				if(currentSelection < maxSelection)
{
  	//Serial.println(maxSelection);				
  currentSelection++;
}
			}	
		}
		Draw();
	}
	else
	{
                if(countdown > 100)
                {
                  countdown--;
                 
                  return;
                }
		if(currentSelection == 0)
		{
			counter++;
			if(counter%30 == 0)
			{
				pong->MovePaddle1(x,y);
			}
			if(counter%200 == 0)
			{
				pong->MoveBall();
			}
			pong->Draw();
		}
		else if(currentSelection == 1)
		{
			counter++;
			if(counter%30 == 0)
			{
                            
				breakout->MovePaddle1(x,y);
			}
			if(counter%200 == 0)
			{
				breakout->MoveBall();
			}
			breakout->Draw();
		}
		else if(currentSelection == 2)
		{
			counter++;
			if(counter%30 == 0)
			{
				snake->Move(x,y);
			}
			pong->Draw();
		}
	}
}
void MenuScreen::CreateGame()
{
	if(currentSelection == 0)
		pong = new Pong(cube,size,2);
	else if(currentSelection == 1)
		breakout = new Breakout(cube,size,2);
	else if(currentSelection == 2)
		snake = new Snake(cube,size);
	inMenu = false;
	counter = 0;
        countdown = 100;
}

void MenuScreen::Draw()
{
	cube->clear();
	
	for(int i = minSelection; i <= maxSelection; i++)
	{		
		cube->setHIGH(0,0,size-1-i);	
        }
        for(int i = 0; i < size; i++)
	{		
          for(int j = 0; j < size; j++)
	    {		
		cube->setHIGH(i,j,currentSelection);	
             }
	}
}

void MenuScreen::GameOver()
{
	//gameover = true;
	Serial.println("GAMEOVER");
}
