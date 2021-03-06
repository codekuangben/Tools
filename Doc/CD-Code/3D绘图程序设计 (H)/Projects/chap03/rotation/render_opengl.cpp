#include <windows.h>
// Standard OpenGL header
#include <GL/gl.h>

#include "Gut.h"
#include "render_data.h"

static Matrix4x4 g_view_matrix;

bool InitResourceOpenGL(void)
{
	// 计算出一个可以转换到镜头坐标系的矩阵
	g_view_matrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	// 投影矩阵
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_OpenGL(60.0f, 1.0f, 1.0f, 100.0f);
	// 设置视角转换矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( (float *) &projection_matrix);

	return true;
}

bool ReleaseResourceOpenGL(void)
{
	// 没做任何事
	return true;
}

// 使用OpenGL来绘图
void RenderFrameOpenGL(void)
{
	// 清除画面
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 设置好GPU要去哪读取顶点数据
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(4, GL_FLOAT, sizeof(Vector4), g_vertices);
	// 设置要改变GL_MODELVIEW矩阵
	glMatrixMode(GL_MODELVIEW);	

	// `旋转角度`
	static float angle = 0.0f;
	angle += 0.01f;
	// `设置旋转矩阵`
	Matrix4x4 world_view_matrix = g_view_matrix;
	world_view_matrix.RotateZ(angle);
	glLoadMatrixf( (float *) &world_view_matrix);
	// `画出金字塔的8条边线`
	glDrawElements(
		GL_LINES,	// `指定所要画的基本图形种类`
		16,			// `有几个索引值`
		GL_UNSIGNED_SHORT,	// `索引值的类型`
		g_indices	// `索引值数组`
	);

	// 把背景backbuffer的画面显示出来
	GutSwapBuffersOpenGL();
}
