#include "Gut.h"
#include "render_data.h"

static LPDIRECT3DVERTEXDECLARATION9 g_pVertexDecl = NULL;

bool InitResourceDX9(void)
{
	// 获得Direct3D 9设备
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// 设置视角转换矩阵
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, 1.0f, 0.1f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// 计算出一个可以转换到镜头坐标系的矩阵
	Matrix4x4 viewmatrix = GutMatrixLookAtRH(g_eye, g_lookat, g_up);
	device->SetTransform(D3DTS_VIEW, (D3DMATRIX *) &viewmatrix);
	g_Simulation.SetViewMatrix(viewmatrix);
	// 关闭光照
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 画出正向和反向的三角形
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return true;
}

bool ReleaseResourceDX9(void)
{
	return true;
}

void ResizeWindowDX9(int width, int height)
{
	GutResetGraphicsDeviceDX9();
	// 投影矩阵, 重设水平和垂直方向的视角.
	float aspect = (float) height / (float) width;
	Matrix4x4 projection_matrix = GutMatrixPerspectiveRH_DirectX(g_fFovW, aspect, 0.1f, 100.0f);
	// 获得Direct3D 9设备
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX *) &projection_matrix);
	// 关闭光照
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 画出正向和反向的三角形
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

// 使用DirectX 9来绘图
void RenderFrameDX9(void)
{
	LPDIRECT3DDEVICE9 device = GutGetGraphicsDeviceDX9();
	// 清除画面
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	// 开始下绘图指令
	device->BeginScene(); 
	device->SetTransform(D3DTS_WORLD, (D3DMATRIX *) &g_Simulation.m_WorldMatrix);
	// 设置数据格式
	//device->SetVertexDeclaration(g_pVertexDecl); 
	device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
	ConvertToDX9(g_pGridVertices, g_pGridVerticesDX9, g_iNumGridVertices);
	// 画出格子
	device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, g_iNumGridVertices, g_iNumGridTriangles, 
		g_pGridIndices, D3DFMT_INDEX16, g_pGridVerticesDX9, sizeof(Vertex_DX9) );
	// 声明所有的绘图指令都下完了
	device->EndScene(); 
	// 把背景backbuffer的画面显示出来
    device->Present( NULL, NULL, NULL, NULL );
}
