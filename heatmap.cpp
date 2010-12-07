#include <BWAPI.h>
#include "heatmap.h"


class MapPather : public micropather::Graph
{
	HeatMap& _heatmap;
	public:

	MapPather(HeatMap& heatmap)
		: _heatmap(heatmap)
	{
	}

	virtual float LeastCostEstimate( void* stateStart, void* stateEnd );
	virtual void AdjacentCost( void* state, std::vector< micropather::StateCost > *adjacent );
	virtual void PrintStateInfo( void* node );
};


float MapPather::LeastCostEstimate( void* stateStart, void* stateEnd )
{
	int x1,y1,x2,y2;
	_heatmap.map_z_into_xy((int)stateStart, &x1, &y1 );
	_heatmap.map_z_into_xy((int)stateEnd, &x2, &y2 );
	BWAPI::Position p1(x1, y1);
	BWAPI::Position p2(x2, y2);
	return (float)(p1.getApproxDistance(p2) * 40);
}
void MapPather::AdjacentCost( void* state, std::vector< micropather::StateCost > *adjacent )
{
	int adj_x[4] = {1, -1, 0 ,0};
	int adj_y[4] = {0, 0, 1, -1};
	int x,y;
	_heatmap.map_z_into_xy((int)state, &x, &y );
	BWAPI::Broodwar->drawTextMap(x*32+16, y*32+16, ".");
	micropather::StateCost cost = {0,1};
	for (int i=0; i<4; i++)
	{
		int new_x = x + adj_x[i];
		int new_y = y + adj_y[i];
		if (BWAPI::Broodwar->isWalkable(new_x*4, new_y*4) )
		{
			int value = _heatmap.getPixel( new_x, new_y );
			cost.cost = (float)(( value>=0 ? value : 0 ) + 10);
			cost.state = (void*)_heatmap.map_xy_into_z( new_x, new_y );
			adjacent->push_back( cost );
		}
	}
}

void MapPather::PrintStateInfo( void* node ) 
{
	int x, y;
	_heatmap.map_z_into_xy( (int)node, &x, &y );
	printf( "(%d,%d)", x, y );
}


HeatMap heat_map;

void HeatMap::init()
{
	if (BWAPI::Broodwar == NULL)
	{
		printf("HeatMap couldn't initialize: Game hasn't started yet!\n");
		return;
	}
	cleanup();
	_width = BWAPI::Broodwar->mapWidth();
	_height = BWAPI::Broodwar->mapHeight();
	map = new int[_width * _height];
	graph = new MapPather(*this);
	pather = new micropather::MicroPather( graph, 250, 4 );

	reset();
}

PyObject* HeatMap::pathFind(BWAPI::TilePosition& start, BWAPI::TilePosition& end)
{
	std::vector< void* > path;
	float totalCost;

	//pather.Reset();

	void* startState = (void*)map_xy_into_z(start.x(), start.y());
	void* endState = (void*)map_xy_into_z(end.x(), end.y());

	int result = pather->Solve( startState, endState, &path, &totalCost );

	PyObject* path_list = PyList_New(path.size());
	if (path_list == NULL)
	{
		PyErr_SetString(PyExc_MemoryError, "Error allocating list!");
		return NULL;
	}

	int i=0;
    for(std::vector< void* >::iterator p=path.begin();p!=path.end();p++)
	{
		int x,y;
		map_z_into_xy((int)*p, &x, &y);
		//BWAPI::Broodwar->drawTextMap(x*32+16, y*32+16, "P");
		PyObject* pos_tuple = Py_BuildValue("ii", x, y);
		if (pos_tuple == NULL)
		{
			Py_DECREF(path_list);
			PyErr_SetString(PyExc_MemoryError, "Error allocating tuple!");
			return NULL;
		}

		PyList_SET_ITEM(path_list, i++, pos_tuple);
	}

	return path_list;
}

void HeatMap::draw()
{
	for (int x=0; x<_width; x++)
	for (int y=0; y<_height; y++)
	{
		int z = map_xy_into_z(x,y);
		if (map[z])
		{
			BWAPI::Broodwar->drawTextMap(x*32+16, y*32+16, "%d", map[z]);
			//BWAPI::Broodwar->drawDotMap(x*32+16, y*32+16, BWAPI::Color(map[z], 0, 0));
		}
	}
}


HeatMap* HeatMap_get()
{
	return &heat_map;
}

