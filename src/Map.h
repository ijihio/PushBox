#pragma once
#include<iostream>
#include<string>

class Map 
{
private:
	int m_Level;//game level
	std::string m_FilePath;
	std::string m_Map;
public:
	
	Map(const std::string filepath,int level=0);
	~Map();
	inline void SetLevel(int level) { m_Level = level; };
	void ReadMap();
	inline size_t GetSize() { return m_Map.size(); };
	int* GetMap();
	int* GetMiniMap();
};