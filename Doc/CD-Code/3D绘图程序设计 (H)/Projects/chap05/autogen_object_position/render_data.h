#include "Vector4.h"
#include "Matrix4x4.h"

struct Vertex_V
{
	float m_Position[3]; // 顶点位置
};

// 常数定义
const float g_fFovW = 45.0f;
// 矩形
extern Vertex_V g_Quad[4];
// 镜头位置
extern Vector4 g_eye; 
// 镜头对准的点
extern Vector4 g_lookat; 
// 镜头正上方的方向
extern Vector4 g_up; 
// 镜头转换矩阵
extern Matrix4x4 g_view_matrix;
// 对象旋转矩阵
extern Matrix4x4 g_world_matrix;
//
extern int g_iFilterMode;
extern bool g_bAnisotropic;