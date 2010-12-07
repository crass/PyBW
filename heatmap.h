#pragma once

#include <string.h>
#include <assert.h>
#include <python.h>
#include "micropather.h"

class HeatMap
{
	micropather::Graph* graph; 
	micropather::MicroPather* pather;

	int* map;
	int _width;
	int _height;

	void cleanup()
	{
		if (map)
		{
			delete[] map;
			map = NULL;
		}
		if (graph)
		{
			delete graph;
			graph = NULL;
		}
		if (pather)
		{
			delete pather;
			pather = NULL;
		}
	}

	int* circle_arrays[10];

	void make_circle_array(int* arr, int r)
	{
		int len = r*2+1;

		for (int x=0; x<=r; x++)
		for (int y=0; y<=r; y++)
		{
			int v=0;
			if (x*x + y*y <= r*r)
			{
				v=1;
			}
			arr[ (r+y)*len + (r+x) ] = v;
			arr[ (r-y)*len + (r+x) ] = v;
			arr[ (r+y)*len + (r-x) ] = v;
			arr[ (r-y)*len + (r-x) ] = v;
		}
	}

public:


	HeatMap() : map(NULL), _width(0), _height(0), graph(NULL), pather(NULL)
	{
		for (int i=0; i<10; i++)
		{
			int r = i+1;
			int len = r*2 + 1;
			circle_arrays[i] = new int[len*len];
			make_circle_array( circle_arrays[i], r);
		}
	}

	~HeatMap()
	{
		for (int i=0; i<10; i++)
		{
			delete[] circle_arrays[i];
		}

		cleanup();
	}

	void init();

	int map_xy_into_z(int x, int y)
	{
		return y * _width + x;
	}
	void map_z_into_xy(int z, int* x, int* y)
	{
		*y = z / _width;
		*x = z % _width;
	}

	void reset()
	{
		if (map == NULL || pather == NULL)
		{
			printf("Heatmap not initialized yet!");
			return;
		}

		memset((void*)map, 0, _width*_height*sizeof(int));
		pather->Reset();
	}

	void addCircle( int cx, int cy, int r, int v )
	{
		// TODO: Cache
		if (r<=0)
			return;
		if (r<=10)
		{
			int len = r*2+1;
			addArray(cx-r, cy-r, len, len, circle_arrays[r-1], v);
			return;
		}

		printf("@@@ %d\n", r);
		for (int x=1; x<=r; x++)
		for (int y=1; y<=r; y++)
		{
			if (x*x + y*y <= r*r)
			{
				addPixel( cx + x, cy + y, v );
				addPixel( cx - x, cy + y, v );
				addPixel( cx + x, cy - y, v );
				addPixel( cx - x, cy - y, v );
			}
		}

		for (int x=1; x<r; x++)
		{
			addPixel( cx + x, cy, v );
			addPixel( cx - x, cy, v );
		}
		for (int y=1; y<r; y++)
		{
			addPixel( cx, cy - y, v );
			addPixel( cx, cy + y, v );
		}

		addPixel( cx, cy, v );
	}

	void addArray(int x, int y, int w, int h, int* arr, int multiplier)
	{
		int x1, y1, x2, y2;
		int arr_x1, arr_y1;

		if (x>=_width || y>=_height)	// out of bounds (right or below map)
			return;

		x1 = (x >= 0 ? x : 0 );
		y1 = (y >= 0 ? y : 0 );
		x2 = (x+w < _width ? x+w : _width-1);
		y2 = (y+h < _height ? y+h : _height-1);

		arr_x1 = (x1-x);
		arr_y1 = (y1-y);
		if (arr_x1 >= w || arr_y1 >= h)	// out of bounds (left or above map)
			return;

		for (int map_y=y1, arr_y=arr_y1; map_y<y2; map_y++, arr_y++)
		{
			int* arr_p = arr + (arr_y * w + arr_x1);
			int* map_p = map + (map_y * _width + x1);
			for (int map_x=x1; map_x<x2; map_x++)
			{
				*map_p++ += (*arr_p++) * multiplier;
			}
		}
	}

	void addPixel(int x, int y, int v)
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
			return;

		int z = map_xy_into_z(x, y);
		map[z] += v;
	}

	int getPixel(int x, int y)
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
			return 0;

		int z = map_xy_into_z(x, y);
		return map[z];
	}

	void draw( );

	PyObject* pathFind(BWAPI::TilePosition& start, BWAPI::TilePosition& end);

};

HeatMap* HeatMap_get();
