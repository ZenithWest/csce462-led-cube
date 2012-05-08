#include "PointList.h"
void PointList::Delete(PointList* p)
		{
			if(next == p)
			{
				next = p->next;
				delete p;
				return;
			}
			if(p->next != 0)
			{
			  Delete(p->next);
			}
		}
		void PointList::Clear(){
			if(next != 0)
			{
				next->Clear();
			}
			delete this;
		}
		void PointList::AddToBack(PointList* p)
		{
                        PointList* p2 = this;
			while (p2->next != 0)
			{
				p2 = p2->next;
			}
			//p2->
                        p2->next = p;
		}
		PointList* PointList::AddToFront(PointList* p)
		{
			p->next = this;
			return p;
		}
               /* void PointList::Print()
                {
                   Serial.println("PRINTING POINTS");
                  int i = 0;
                  Serial.print("POINT ");
                   Serial.print(i);
                   Serial.print("  X  ");
                   Serial.print(x);
                   Serial.print("  Y  ");
                   Serial.print(y);
                   Serial.print("  Z  ");
                   Serial.print(z);
                   if(next != 0)
                       next->Print();
                }*/
		void PointList::DeleteEnd()
		{
                        PointList* p = this;
                        PointList* p2 = this;;
			if(next == 0)
			{
				delete this;
				return;
			}
                        while(p->next != 0)
                        {
                          p2 = p;
                          p = p->next;
                 
                        }
			delete p;
                        p2->next = 0;
		}
