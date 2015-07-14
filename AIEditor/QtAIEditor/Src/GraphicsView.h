#ifndef __GRAPHICSVIEW_H
#define __GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QtGui/QtGui>
#include <QtCore/QtCore>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

//protected:
//	QPointF m_lastPos;

public:
	explicit GraphicsView(QWidget *parent = 0);
	void adjustSceneRect();	// 调整 VIEW 始终正好能放下整个场景就行了

protected:
	virtual void paintEvent(QPaintEvent *e);
	// 添加了事件一定要调用 Parent 函数，否则就不能自动移动了
	virtual void mouseMoveEvent(QMouseEvent * e);//鼠标移动事件响应
	virtual void mousePressEvent(QMouseEvent * e);//鼠标单击事件响应
	virtual void mouseReleaseEvent(QMouseEvent * e);//鼠标松开事件响应
	virtual void GraphicsView::dragEnterEvent(QDragEnterEvent *event);
	virtual void GraphicsView::dropEvent(QDropEvent *event);
};

#endif // GRAPHICSVIEW_H