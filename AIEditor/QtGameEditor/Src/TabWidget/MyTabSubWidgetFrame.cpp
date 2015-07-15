#include "MyTabSubWidgetFrame.h"
#include <QtGui>

MyTabSubWidgetFrame::MyTabSubWidgetFrame(QWidget *parent) :QWidget(parent)
{

}

MyTabSubWidgetFrame::~MyTabSubWidgetFrame()
{

}

bool MyTabSubWidgetFrame::event(QEvent *event)
{
#ifdef unix
	if (event->type() == QEvent::MouseButtonDblClick){   //标题栏单击没反应，就单击窗口边缘替代吧
		emit sig_doubleClickedTitleBar();
		return true;
	}
#endif   
	if (event->type() == QEvent::NonClientAreaMouseButtonDblClick)  //这个事件在Linux下没有触发，应该算是Qt的一个Bug吧
	{
		emit sig_doubleClickedTitleBar();
		return true;
	}
	return QWidget::event(event);
}