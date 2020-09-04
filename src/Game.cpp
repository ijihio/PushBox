#include "Game.h"
#include<Windows.h>

const int Game::DirX[4]{ 0,0,-1,1 };
const int Game::DirY[4]{  1,-1,0,0};

Game::Game(const std::string& mappath, const std::string& texpath, const std::string& shaderpath,int level)
	:m_MapPath(mappath), m_TexPath(texpath), m_ShaderPath(shaderpath),m_Level(level)
{
	m_Renderer = new Renderer();
	m_Map = new Map(m_MapPath, m_Level);
	m_Shader = new Shader(m_ShaderPath);

	for (unsigned int i = 0; i < 10; i++)
	{
		std::string tem_MiniMap = m_TexPath + (char)(i + '0') + ".bmp";
		m_Texture[i] = new Texture(tem_MiniMap, i);
	}

	m_MiniMap = m_Map->GetMiniMap();
	m_OriginMiniMap = m_Map->GetMiniMap();
	m_MapSize = m_Map->GetSize();

	

	float* vb = Game::GetVB();
	int* ib = Game::GetIB();
	m_IB = new IndexBuffer(ib, m_MapSize * 6);
	m_VB = new VertexBuffer(vb, m_MapSize * 4 * 5 * sizeof(float));
	VertexBufferLayout layout;
	m_VA = new VertexArray();
	layout.Push<float>(2);
	layout.Push<float>(2);
	layout.Push<float>(1);
	m_VA->Bind();
	m_VA->AddBuffer(*m_VB, layout);
}

Game::~Game()
{
	delete m_Map;
	delete m_VB;
	delete m_VA;
	delete m_IB;
	delete m_Shader;
	delete m_Renderer;
	for (int i = 0; i < 10; i++)
		delete m_Texture[i];	

	delete m_MiniMap;
	delete m_OriginMiniMap;

}

void Game::Init()
{
	
	glm::mat4 proj = glm::ortho(0.0f, 544.0f, -100.0f, 544.0f, -1.0f, 1.0f);
	int TexIndex[] = { 0,1,2,3,4,5,6,7,8,9 };

	m_Shader->Bind();
	m_Shader->SetUniform1iv("u_Textures", TexIndex, 10);
	m_Shader->SetUniformMat4f("u_MVP", proj);
	
	Step.push(UP);
}

float* Game::GetVB()
{
	float* vb = new float[m_MapSize * 20];
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++) {
			int ij20 = (i * 15 + j) * 20;

			vb[ij20 + 0] = 32.0f + j * 32.0f;
			vb[ij20 + 1] = 32.0f + i * 32.0f;
			vb[ij20 + 2] = 0.0f;
			vb[ij20 + 3] = 0.0f;
			vb[ij20 + 4] = 4 * (i * 15 + j) + 0.0f;

			vb[ij20 + 5] = 32.0f + (j + 1) * 32.0f;
			vb[ij20 + 6] = 32.0f +  i* 32.0f;
			vb[ij20 + 7] = 1.0f;
			vb[ij20 + 8] = 0.0f;
			vb[ij20 + 9] = 4 * (i * 15 + j) + 1.0f;

			vb[ij20 + 10] = 32.0f + (j + 1) * 32.0f;
			vb[ij20 + 11] = 32.0f + (i + 1) * 32.0f;
			vb[ij20 + 12] = 1.0f;
			vb[ij20 + 13] = 1.0f;
			vb[ij20 + 14] = 4 * (i * 15 + j) + 2.0f;

			vb[ij20 + 15] = 32.0f + j * 32.0f;
			vb[ij20 + 16] = 32.0f + (i + 1) * 32.0f;
			vb[ij20 + 17] = 0.0f;
			vb[ij20 + 18] = 1.0f;
			vb[ij20 + 19] = 4 * (i * 15 + j) + 3.0f;
		}
	}

	

	return vb;
}

int* Game::GetIB()
{
	
	int* ib = new int[m_MapSize *6];
	
	for (int i = 0; i < m_MapSize; i++)
	{
		int i6 = i * 6, i4 = i * 4;

		ib[i6 + 0] = i4 + 0;
		ib[i6 + 1] = i4 + 1;
		ib[i6 + 2] = i4 + 2;
		ib[i6 + 3] = i4 + 2;
		ib[i6 + 4] = i4 + 3;
		ib[i6 + 5] = i4 + 0;
		
	}
	
	return ib;
}

void Game::DrawMap()
{

	int maxMap[900];
	for (int i = 0; i < m_MapSize; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			maxMap[i * 4 + j] = m_MiniMap[i];

		}
	}

	
	m_Shader->SetUniform1iv("u_Index", maxMap, m_MapSize * 4);
	m_Renderer->Clear(0.1f, 0.4f, 0.5f, 1.0f);
	m_Renderer->Draw(*m_VA, *m_IB, *m_Shader);

	

	
	
//	IsPass();

}

bool Game::IsPass()
{
	int p = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (m_MiniMap[i * 15 + j] == Box)
			{
				return false;
			}
		}
	}
	if (p == 0)
	{
		MessageBox(NULL, TEXT("passed,next level?"), TEXT("info"), 1);

		if (m_Level < MaxLevel)
		{

			m_Level += 1;

			delete m_Map;
			delete m_MiniMap;//int型的map数组
			delete m_OriginMiniMap;

			m_Map = new Map(m_MapPath, m_Level);
			m_MiniMap = m_Map->GetMiniMap();
			m_OriginMiniMap = m_Map->GetMiniMap();
			
		}
		
		return true;
	}


}

void Game::keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	SpecialKeys(key,action);
}

void Game::SpecialKeys(int key,int action)
{
	//判断，如果按键状态为release，检查是否通过游戏
	if (action == GLFW_RELEASE)
	{
		IsPass();
		return;
	}
	else if (action != GLFW_PRESS)
		return;
	switch (key) {


	case GLFW_KEY_R:

		delete m_MiniMap;
		m_MiniMap=m_Map->GetMiniMap();
		break;

	case GLFW_KEY_ESCAPE:
		exit(0);
		break;
	case GLFW_KEY_BACKSPACE:
		if(Step.size()>3)
		{ 
			int cur_dir = Step.top(); Step.pop();  //当前坐标的方向
										 //当前坐标
			int mx = m_Man.x;
			int my = m_Man.y;

			int cur_pic = Step.top(); Step.pop();   //当前坐标cur_dir方向的图片
			int next_pic = Step.top(); Step.pop();   //前一个坐标以前图片
			int pre_dir = Step.top();
			int dx = DirX[cur_dir];
			int dy = DirY[cur_dir];
			m_MiniMap[mx + my * 15] = cur_pic;
			m_MiniMap[mx + dx+(my + dy)*15] = next_pic;
			m_MiniMap[mx - dx+(my - dy)*15] = pre_dir + 5;
			m_Man.x = mx - dx;
			m_Man.y = my - dy;
				
		}
		break;

	case GLFW_KEY_UP: //向上移动
	{
		std::cout << "Key:" << "up" << std::endl;
		Move(UP);
		break;
	}
	case GLFW_KEY_DOWN:  //向下移动
	{
		std::cout << "Key:" << "down" << std::endl;
		Move( DOWN);
		break;
	}
	case GLFW_KEY_LEFT:  //向左移动
	{
		std::cout << "Key:" << "left" << std::endl;
		Move(LEFT);
		break;
	}
	case GLFW_KEY_RIGHT:   //向右移动
	{		
		std::cout << "Key:" << "right" << std::endl;
		Move(RIGHT);
		break;
	}
	case GLFW_KEY_PAGE_UP:    //下一关
	{
		std::cout << "Key:" << "下一关" << std::endl;
		
		if (m_Level < MaxLevel)
		{
			m_Level++;

			delete m_Map;
			delete m_MiniMap;//int型的map数组
			delete m_OriginMiniMap;

			m_Map = new Map(m_MapPath, m_Level);
			m_MiniMap = m_Map->GetMiniMap();
			m_OriginMiniMap = m_Map->GetMiniMap();
		}
			break;
	
	}
	case GLFW_KEY_PAGE_DOWN:    //上一关
	{
		std::cout << "Key:" << "上一关" << std::endl;
		
		if (m_Level > MinLevel) {
			m_Level--;

			delete m_Map;
			delete m_MiniMap;
			delete m_OriginMiniMap;
			m_Map = new Map(m_MapPath, m_Level);
			m_MiniMap = m_Map->GetMiniMap();
			m_OriginMiniMap = m_Map->GetMiniMap();
			m_MapSize = m_Map->GetSize();

			break;
		}		
		break;
	}
	default:
		std::cout << "Key:" << "other" << std::endl;
		break;
	}
}

	void Game::Move(int dir)
	{

		GetManXY();		
		bool PushStack = false;
		int dx = DirX[dir];
		int dy = DirY[dir];

		int manNextX = m_Man.x + dx;
		int manNextY = m_Man.y + dy;

		int Next = m_MiniMap[manNextX + 15 * manNextY];
		int Next2 = m_MiniMap[(manNextX + dx) + 15 * (manNextY + dy)];

		switch (Next) 
		{
		case Wall:	//Next is Wall
			//m_MiniMap[m_Man.x + m_Man.y * 15] = dir + 5;
			break;
		case Land:	//Next is Land
			//todo:
			m_MiniMap[manNextX + 15 * manNextY] = dir + 5;
			if (m_OriginMiniMap[m_Man.x + m_Man.y * 15] == Flower || m_OriginMiniMap[m_Man.x + m_Man.y * 15] == FlowerWithBox)
				m_MiniMap[m_Man.x + m_Man.y * 15] = Flower;
			else 
				m_MiniMap[m_Man.x + m_Man.y * 15] = Land;
			m_Man.x = manNextX;
			m_Man.y = manNextY;

			PushStack = true;

			break;
		case Flower:	//Next is Land
			//todo:
			m_MiniMap[manNextX + 15 * manNextY] = dir + 5;
			if (m_OriginMiniMap[m_Man.x + m_Man.y * 15] == Flower|| m_OriginMiniMap[m_Man.x + m_Man.y * 15] == FlowerWithBox )
				m_MiniMap[m_Man.x + m_Man.y * 15] = Flower;
			else
				m_MiniMap[m_Man.x + m_Man.y * 15] = Land;
			m_Man.x = manNextX;
			m_Man.y = manNextY;

			PushStack = true;

			break;
		case Box:	//Next is box
		{
			switch(Next2)
			{
			case Wall: //Next2 is Wall
				break;
			case Box:// Next2 is Box
				break;				
			case Land:// Next2 is Land
				//原来为人的位置恢复原状，且对人的位置进行更新
				if (m_OriginMiniMap[m_Man.x + m_Man.y * 15] == Flower || m_OriginMiniMap[m_Man.x + m_Man.y * 15] == FlowerWithBox)
					m_MiniMap[m_Man.x + m_Man.y * 15] = Flower;
				else
					m_MiniMap[m_Man.x + m_Man.y * 15] = Land;
				
			
				//将地图中box 的位置置为人
				m_MiniMap[manNextX + 15 * manNextY] = dir + 5;

				//将地图中land的位置置为box
				m_MiniMap[manNextX + DirX[dir] + 15 * (manNextY + DirY[dir])] = Box;		

				m_Man.x = manNextX;
				m_Man.y = manNextY;

				PushStack = true;
				
				break;
			case Flower://Next2 is Flower
						//原来为人的位置恢复原状，且对人的位置进行更新
				if (m_OriginMiniMap[m_Man.x + m_Man.y * 15] == Flower || m_OriginMiniMap[m_Man.x + m_Man.y * 15] == FlowerWithBox)
					m_MiniMap[m_Man.x + m_Man.y * 15] = Flower;
				else
					m_MiniMap[m_Man.x + m_Man.y * 15] = Land;
				

				//将地图中box 的位置置为人

				m_MiniMap[manNextX + 15 * manNextY] = dir + 5;
				//将地图中land的位置置为box
				m_MiniMap[manNextX + DirX[dir] + 15 * (manNextY + DirY[dir])] = FlowerWithBox;

				m_Man.x = manNextX;
				m_Man.y = manNextY;

				PushStack = true;

				break;
			default:
				break;
			}		
		}

		case FlowerWithBox:
			if (Next2 == Land)
			{
				//还原人
				if (m_OriginMiniMap[m_Man.x + m_Man.y * 15] == Flower || m_OriginMiniMap[m_Man.x + m_Man.y * 15] == FlowerWithBox)
				{
					m_MiniMap[m_Man.x + m_Man.y * 15] = Flower;
				}
				else
				{
					m_MiniMap[m_Man.x + m_Man.y * 15] = Land;
				}
				//还原flower				
				m_MiniMap[manNextX + manNextY * 15] = dir+5;

				m_MiniMap[manNextX + DirX[dir] + (manNextY + DirY[dir]) * 15] = Box;

				m_Man.x = manNextX;
				m_Man.y = manNextY;

				PushStack = true;
			}
			else if (Next2 == Flower)
			{
				if (m_OriginMiniMap[m_Man.x + m_Man.y * 15] == Flower || m_OriginMiniMap[m_Man.x + m_Man.y * 15] == FlowerWithBox)
				{
					m_MiniMap[m_Man.x + m_Man.y * 15] = Flower;
				}
				else
				{
					m_MiniMap[m_Man.x + m_Man.y * 15] = Land;
				}
				m_MiniMap[manNextX + manNextY * 15] = dir+5;
				m_MiniMap[manNextX+DirX[dir] + (manNextY+DirY[dir]) * 15] = FlowerWithBox;

				m_Man.x = manNextX;
				m_Man.y = manNextY;

				PushStack = true;
			}

			break;

		default: 

			break;			
		}		

		//每走一步保存当前位置的坐标、以前的图片
		if (PushStack)
		{				
			Step.push(Next2);
			Step.push(Next);			
			Step.push(dir);

		}
		
		
	
	}

	void Game::GetManXY()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (m_MiniMap[i + j * 15] == ManUp ||
					m_MiniMap[i + j * 15] == ManDown ||
					m_MiniMap[i + j * 15] == ManLeft ||
					m_MiniMap[i + j * 15] == ManRight)
				{
					m_Man.x = i;
					m_Man.y = j;
					return;
				}				
			}
		}
	}
