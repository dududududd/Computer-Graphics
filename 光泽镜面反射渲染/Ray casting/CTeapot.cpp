#include "pch.h"
#include "CTeapot.h"

CTeapot::CTeapot(void)
{
	this->Renumber = 3;
}

CTeapot::~CTeapot(void)
{
}

void CTeapot::SetRecursiveNumber(int Renumber)
{
	this->Renumber = Renumber;
}

void CTeapot::ReadVertex(void)//读入控制点坐标
{
	CStdioFile file;
	if (!file.Open(L"Vertices.txt", CFile::modeRead))
	{
		MessageBox(NULL, L"can not open file!", L"Warning", MB_ICONEXCLAMATION);
		return;
	}
	CString  strLine;//定义行字符串
	int index = 0;//用于区分数字
	CString data1, data2, data3;//存放坐标
	for (int i = 0; i < 306; i++)
	{
		file.ReadString(strLine);//按行读入
		for (int j = 0; j < strLine.GetLength(); j++)
		{
			if (' ' == strLine[j])
				index++;
			switch (index)
			{
			case 0:
				data1 += strLine[j];
				break;
			case 1:
				data2 += strLine[j];
				break;
			case 2:
				data3 += strLine[j];
				break;
			}
		}
		Ver[i].x = _wtof(data1.GetBuffer());//浮点数表示的x值
		Ver[i].y = _wtof(data3.GetBuffer());//浮点数表示的z值
		Ver[i].z = _wtof(data2.GetBuffer());//浮点数表示的y值
		strLine = "", data1 = "", data2 = "", data3 = "", index = 0;
	}
	file.Close();
}


void CTeapot::ReadPatch(void)//读入茶壶曲面片
{
	CStdioFile file;
	if (!file.Open(L"Patches.txt", CFile::modeRead))
	{
		MessageBox(NULL, L"can not open file!", L"Warning", MB_ICONEXCLAMATION);
		return;
	}
	CString strLine;
	int index = 0;
	CString str[16];//存放控制点索引号
	for (int nPatch = 0; nPatch < 32; nPatch++)
	{
		file.ReadString(strLine);
		for (int i = 0; i < strLine.GetLength(); i++)
		{
			if (' ' == strLine[i])
				index++;
			switch (index)
			{
			case 0:
				str[0] += strLine[i];
				break;
			case 1:
				str[1] += strLine[i];
				break;
			case 2:
				str[2] += strLine[i];
				break;
			case 3:
				str[3] += strLine[i];
				break;
			case 4:
				str[4] += strLine[i];
				break;
			case 5:
				str[5] += strLine[i];
				break;
			case 6:
				str[6] += strLine[i];
				break;
			case 7:
				str[7] += strLine[i];
				break;
			case 8:
				str[8] += strLine[i];
				break;
			case 9:
				str[9] += strLine[i];
				break;
			case 10:
				str[10] += strLine[i];
				break;
			case 11:
				str[11] += strLine[i];
				break;
			case 12:
				str[12] += strLine[i];
				break;
			case 13:
				str[13] += strLine[i];
				break;
			case 14:
				str[14] += strLine[i];
				break;
			case 15:
				str[15] += strLine[i];
				break;
			}
		}
		for (int nVertex = 0; nVertex < 16; nVertex++)
			Pat[nPatch].indices.push_back(_wtoi(str[nVertex].GetBuffer()));//整数表示的控制点索引号
		strLine = "";
		for (int nVertex = 0; nVertex < 16; nVertex++)
		{
			str[nVertex] = "";
		}
		index = 0;
	}
	file.Close();
}

void CTeapot::set_point()//绘制整壶
{
	ReadVertex();
	ReadPatch();
	bezier.set_material(material);
	//案照面片编号顺序划分部件
	DrawRim();//壶边
	DrawBody();//壶体
	DrawHandle();//壶柄
	DrawSpout();//壶嘴
	DrawLid();//壶盖	
	DrawBottom();//壶底
	bezier.setup_cells();
	this->bbox  = bezier.get_bounding_box();
}

bool CTeapot::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	return (bezier.hit(ray, tmin, sr));
}

bool CTeapot::shadow_hit(const Ray & ray, float & tmin) const
{
	return(bezier.shadow_hit(ray, tmin));
}

BBox CTeapot::get_bounding_box(void)
{
	return this->bbox;
}

void CTeapot::DrawRim()//绘制壶边
{
	for (int nPatch = 0; nPatch < 4; nPatch++)
	{
		for (int nVertex = 0; nVertex < 16; nVertex++)
		{
			Ver3[nVertex] = Ver[Pat[nPatch].indices[nVertex] - 1];
		}
		SigleCurvedPatch();//双三次Bezier曲面
	}
}


void CTeapot::DrawBody()//绘制壶体
{
	for (int nPatch = 4; nPatch < 12; nPatch++)
	{
		for (int nVertex = 0; nVertex < 16; nVertex++)
		{
			Ver3[nVertex] = Ver[Pat[nPatch].indices[nVertex] - 1];
		}
		SigleCurvedPatch();//双三次Bezier曲面
	}
}


void CTeapot::DrawBottom()//绘制壶底
{
	for (int nPatch = 28; nPatch < 32; nPatch++)
	{
		for (int nVertex = 0; nVertex < 16; nVertex++)
		{
			Ver3[nVertex] = Ver[Pat[nPatch].indices[nVertex] - 1];
		}
		SigleCurvedPatch();//双三次Bezier曲面
	}
}

void CTeapot::DrawHandle()//绘制壶柄
{
	for (int nPatch = 12; nPatch < 16; nPatch++)
	{
		for (int nVertex = 0; nVertex < 16; nVertex++)
		{
			Ver3[nVertex] = Ver[Pat[nPatch].indices[nVertex] - 1];
		}
		SigleCurvedPatch();//双三次Bezier曲面
	}
}

void CTeapot::DrawSpout()//绘制壶嘴
{
	for (int nPatch = 16; nPatch < 20; nPatch++)
	{
		for (int nVertex = 0; nVertex < 16; nVertex++)
		{
			Ver3[nVertex] = Ver[Pat[nPatch].indices[nVertex] - 1];
		}
		SigleCurvedPatch();//双三次Bezier曲面
	}
}

void CTeapot::DrawLid()//绘制壶盖
{
	for (int nPatch = 20; nPatch < 28; nPatch++)
	{
		for (int nVertex = 0; nVertex < 16; nVertex++)
		{
			Ver3[nVertex] = Ver[Pat[nPatch].indices[nVertex] - 1];
		}
		SigleCurvedPatch();//双三次Bezier曲面
	}
}

void CTeapot::SigleCurvedPatch()//绘制每个曲面片
{
	bezier.ReadControlPoint(Ver3, Renumber);//16个控制点
}