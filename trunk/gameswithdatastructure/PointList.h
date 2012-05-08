#ifndef POINTLIST_H
#define POINTLIST_H



/*
	Cube makes the assumption that the size doesn't change (copy and assignment would crash otherwise)

*/


class PointList {
	public:
		int x;
		int y;
		int z;
		PointList* next;
		PointList(int X, int Y, int Z){x = X; y = Y; z = Z; next = 0;}
		PointList(){}
		~PointList(){}
		void Delete(PointList* p);
		void Clear();
		void AddToBack(PointList* p);
		PointList* AddToFront(PointList* p);
		void DeleteEnd();
               
};

#endif
