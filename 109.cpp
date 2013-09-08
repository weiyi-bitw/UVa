/*
 * =====================================================================================
 *
 *       Filename:  list2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/05/2013 11:31:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

class Coord
{
  public:
	int x;
	int y;
	Coord(){}
	Coord(const Coord & c)
	{
		x = c.x;
		y = c.y;
	}
	Coord(int a, int b)
	{
		x = a;
		y = b;
	}
	Coord& operator=(const Coord & cb)
	{
		x = cb.x;
		y = cb.y;
		return (*this);
	}
	friend ostream& operator<<(ostream& , const Coord &);
};

ostream& operator<<(ostream& out, const Coord & c)
{
	out << c.x << " " << c.y;
	return out;
}

bool coordCompare(const Coord & c1, const Coord & c2)
{
	if(c1.y == c2.y)
		return (c1.x < c2.x);
	return (c1.y < c2.y);
}

struct AngleComparer
{
	Coord p;
	AngleComparer(const Coord & c)
	{
		p = c;
		//cout << "P: " << c << endl;
	}
	bool operator()(const Coord & c1, const Coord & c2)
	{
		double x1 = (c1.x - p.x);
		double x2 = (c2.x - p.x);
		double l1 = x1*x1 + (c1.y - p.y) * (c1.y - p.y);
		double l2 = x2*x2 + (c2.y - p.y) * (c2.y - p.y);
		double cp1 = x1/sqrt(l1);
		double cp2 = x2/sqrt(l2);
		return cp1 > cp2;
	}
};

class Kingdom
{
	int N;
	vector<Coord> buildings;
	vector<Coord> walls;
  public:
	double area;
	bool hit;
	Kingdom()
	{
		area = 0;
		N = 0;
		hit = false;
	}
	Kingdom(int N)
	{
		this->N = N;
		area = 0;
		hit = false;
	}
	void addCoord(const Coord & c)
	{
		buildings.push_back(c);
	}

	void buildWalls()
	{
		sort(buildings.begin(), buildings.end(), &coordCompare);
		//cout << "Sorted coords." << endl;
		//for(int i = 0; i < (int)buildings.size(); i++) cout << buildings[i] << endl;
		AngleComparer ac(buildings[0]);
		sort(buildings.begin()+1, buildings.end(), ac);
		//cout << "Sorted coords." << endl;
		//for(int i = 0; i < (int)buildings.size(); i++) cout << buildings[i] << endl;
		buildings.push_back(buildings[0]);
		walls.push_back(buildings[0]);
		Coord point0(buildings[0]);
		Coord point1(buildings[1]);

		double x1, x2, y1, y2;
		int i = 2;
		while(i < N+1){
			//cout << buildings[i] << "\t" << point1 << "\t" << point0 << endl;
			x1 = point1.x - point0.x;
			y1 = point1.y - point0.y;
			x2 = buildings[i].x - point1.x;
			y2 = buildings[i].y - point1.y;
			if(x1*y2 - x2*y1 > 0){
				//cout << "push!" << point1 <<  endl;
				walls.push_back(point1);
				point0 = point1;
				point1 = buildings[i];
				i++;
			}else if(x1*y2 - x2*y1 == 0){
				point1 = buildings[i];
				i++;
			}else{
				if( i == N ) break;
				if( (int) walls.size() == 1){
					i++;
				}else{
					point1 = point0;
					//cout << "pop!" << point0 << endl;
					walls.pop_back();
					point0 = walls.back();
				}
			}
		}
		walls.push_back(walls[0]);
		// calculate area
		for(int i = 0; i < (int) walls.size()-1; i++)
			area += ( walls[i].x * walls[i+1].y - walls[i+1].x * walls[i].y );
		area /= 2;
	}

	bool enclose(const Coord & c)
	{
		double x1, x2, y1, y2, ref = 0, preref = 0;
		x1 = walls[0].x - c.x;
		y1 = walls[0].y - c.y;
		for(int i = 1; i < (int)walls.size(); i++){
			preref = ref;
			x2 = walls[i].x - c.x;
			y2 = walls[i].y - c.y;
			ref = x1*y2 - x2*y1;
			if(ref == 0) return false;
			if( preref * ref < 0) return false;
			else{
				x1 = x2;
				y1 = y2;
			}

		}
		return true;
	}

	friend ostream& operator<<(ostream&, Kingdom &);
};

ostream& operator<<(ostream& out, Kingdom & k){
	out << "N: " << k.N << endl;
	out << "Coords: " << endl;
	for(int i = 0; i < k.N; i++)
		out << k.buildings[i] << endl;
	out << "Walls: " << endl;
	for(int i = 0; i < (int) k.walls.size(); i++)
		out << k.walls[i] << endl;
	out << "Area: " << k.area << endl;
	return out;
}


int main()
{
	int N;
	vector<Kingdom> kingdoms;
	int x,y;
	double area = 0;
	while(cin >> N){
		if(N == -1){
			break;
		}
		
		Kingdom k(N);
		for(int i = 0; i < N; i++){
			cin >> x >> y;
			Coord c(x, y);
			k.addCoord(c);
		}
		k.buildWalls();
		//cout << "Add kingdom: " << endl;
		//cout << k << endl;
		kingdoms.push_back(k);
	}
	//cout << "Kingdoms: " << endl;
	//for(int i = 0; i < (int) kingdoms.size(); i++)
	//	cout << kingdoms[i] << endl;
	
	while(cin >> x >> y){
		if(x == -999 || kingdoms.empty()) break;
		Coord c(x, y);
		for(int i = 0; i < (int) kingdoms.size(); i++){
			if(kingdoms[i].enclose(c)){
				//cout << "hit " << i << endl;
				kingdoms[i].hit = true;
				break;
			}
		}
	}
	for(int i = 0; i < (int) kingdoms.size(); i++){
		if(kingdoms[i].hit){
			//cout << "hit " << i << endl;
			area += kingdoms[i].area;
		}
	}
	
	cout << fixed << setprecision(2) << area << endl;

	return 0;
}





