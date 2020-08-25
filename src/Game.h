#pragma once
#include <string>
#include<stack>
#include"Texture.h"
#include"Map.h"
#include"GameBase.h"

#include"Renderer.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
#include"Map.h"
#include"GLFW/glfw3.h"

#include"vendor/glm/glm.hpp"
#include"vendor/glm/gtc/matrix_transform.hpp"



struct Man{

	int x, y;
};
typedef void (*KeyCallBack)(GLFWwindow*, int, int, int, int);
class Game: public GameBase
{

public:
	

	static const int DirX[4];
	static const int DirY[4];
	enum {UP,DOWN,LEFT,RIGHT};
	enum {MinLevel=1,MaxLevel=2};
	enum
	{
		BackGround, Land, Wall,FlowerWithBox,Box,ManUp,ManDown,ManLeft,ManRight,Flower
	};

	Game(const std::string &mappath, const std::string &texpath, const std::string& shaderpath, int level);
	~Game();
	void Init();
	inline void GetLevel(Map &map,int i) { map.SetLevel(i); };
	float* GetVB();//读取map，生成坐标
	int* GetIB();
	
	void DrawMap();
	bool IsPass();
	virtual void keycallback(GLFWwindow *window,int key,int scancode,int action, int mods);
	void SpecialKeys(int key,int action);
	void Move(int dir);
	void GetManXY();
	

private: 
	//Map* m_Map;   
	std::string m_MapPath;
	std::string m_TexPath;
	std::string m_ShaderPath;
	int m_Level;
	Map* m_Map;
	Texture* m_Texture[10];
	VertexBuffer* m_VB;
	VertexArray* m_VA;
	IndexBuffer* m_IB;
	Shader* m_Shader;
	Renderer *m_Renderer;
	
	int* m_MiniMap;//int型的map数组
	int* m_OriginMiniMap;

	std::stack<int> Step;
    int m_MapSize;
	Man m_Man;
};

