#include <stdio.h>
#include <conio.h>

#include "Gut.h"
#include "GutInput.h"
#include "GutTimer.h"

#include "render_dx9.h"
#include "render_dx10.h"
#include "render_opengl.h"
#include "render_data.h"

GutTimer g_Timer;
float g_fFrame_Time = 0.0f;

void KeyDown_UP(void)
{
	const int alpha = 3;

	if ( g_Quad[0].m_Color[alpha] < 254 )
	{
		g_Quad[0].m_Color[alpha]+=1;
		g_Quad[1].m_Color[alpha]+=1;
		g_Quad[2].m_Color[alpha]+=1;
		g_Quad[3].m_Color[alpha]+=1;

		float fAlpha = (float)g_Quad[0].m_Color[alpha]/255.0f;
		printf("Alpha = %5.2f\r", fAlpha);
	}
}

void KeyDown_DOWN(void)
{
	const int alpha = 3;

	if ( g_Quad[0].m_Color[alpha] > 0 )
	{
		g_Quad[0].m_Color[alpha]-=1;
		g_Quad[1].m_Color[alpha]-=1;
		g_Quad[2].m_Color[alpha]-=1;
		g_Quad[3].m_Color[alpha]-=1;

		float fAlpha = (float)g_Quad[0].m_Color[alpha]/255.0f;
		printf("Alpha = %5.2f\r", fAlpha);
	}
}

void GetUserInput(void)
{
	g_fFrame_Time = g_Timer.Stop();
	g_Timer.Restart();
	GutReadKeyboard();
	g_Control.Update(g_fFrame_Time, CGutUserControl::CONTROLLER_ROTATEOBJECT);
}

void main(void)
{
	// 默认使用DirectX 9来绘图
	char *device = "dx9";
	void (*render)(void) = RenderFrameDX9;
	bool (*init_resource)(void) = InitResourceDX9;
	bool (*release_resource)(void) = ReleaseResourceDX9;
	void (*resize_func)(int width, int height) = ResizeWindowDX9;

#ifdef _ENABLE_DX10_
	printf("Press\n(1) for Direct3D9\n(2) for OpenGL\n(3) for Direct3D10\n");
#else
	printf("Press\n(1) for Direct3D9\n(2) for OpenGL\n");
#endif

	int c = getche();
	switch(c)
	{
	default:
	case '1':
		render = RenderFrameDX9;
		init_resource = InitResourceDX9;
		release_resource = ReleaseResourceDX9;
		resize_func = ResizeWindowDX9;
		break;
	case '2':
		device = "opengl";
		init_resource = InitResourceOpenGL;
		release_resource = ReleaseResourceOpenGL;
		render = RenderFrameOpenGL;
		resize_func = ResizeWindowOpenGL;
		break;
#ifdef _ENABLE_DX10_
	case '3':
		device = "dx10";
		init_resource = InitResourceDX10;
		release_resource = ReleaseResourceDX10;
		render = RenderFrameDX10;
		resize_func = ResizeWindowDX10;
		break;
#endif // _ENABLE_DX10_
	}

	printf("\nSelected %s device for rendering.\n", device);

	GutResizeFunc( resize_func );

	// 在(100,100)的位置打开一个大小为(512x512)的窗口
	GutCreateWindow(100, 100, 512, 512, device);

	// 做OpenGL或DirectX初始化
	if ( !GutInitGraphicsDevice(device) )
	{
		printf("Failed to initialize %s device\n", device);
		exit(0);
	}

	GutInputInit();

	GutRegisterKeyPressed(GUTKEY_DOWN, KeyDown_DOWN);
	GutRegisterKeyPressed(GUTKEY_UP, KeyDown_UP);

	g_Control.SetCamera(Vector4(0.0f, 0.0f, 5.0f), Vector4(0.0f, 0.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f) );

	// 载入shader
	if ( !init_resource() )
	{
		release_resource();
		printf("Failed to load resources\n");
		exit(0);
	}

	// 主循环
	while( GutProcessMessage() )
	{
		GetUserInput();
		// 画出矩形
		render();
	}
	// 释放shader
	release_resource();
	// 关闭OpenGL/DirectX绘图设备
	GutReleaseGraphicsDevice();
}
