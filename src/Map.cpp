#include "Map.h"
#include<fstream>
#include<sstream>

Map::Map(const std::string filepath, int level)
	:m_FilePath(filepath),m_Level(level)
{
	ReadMap();
}

Map::~Map()
{
}

void Map::ReadMap()
{
    std::string filepath;
    int i = 1;
    filepath = m_FilePath + (char)(m_Level +'0') + ".map";
    std::ifstream stream(filepath);
    if (!stream)
        std::cout << "can't open file!!!" << std::endl;
    //else
     //   std::cout << "success open!!" << std::endl;
    std::string line;
    std::stringstream ss;

    while (getline(stream, line))
    {
        ss << line;
    }
    stream.close();
    m_Map = ss.str();
}


int* Map::GetMap()
{
	int size = m_Map.size();
	int* map = new int[size * 4];
	const char* str = m_Map.c_str();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i * 4 + j] = (str[i] - 48);

		}
		
	}
	return map;
}

int* Map::GetMiniMap()
{
	int size = m_Map.size();
	int* map = new int[size ];
	const char* str = m_Map.c_str();

	for (int i = 0; i < size; i++)
	{			
		map[i ] = (str[i] - 48);
	}
	return map;
}

