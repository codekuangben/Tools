#ifndef __MYGRAPHICSSCENE_H
#define __MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "QtIncAll.h"

class RecvDropRectItem;

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

protected:
	QPointF m_lastPos;
	RecvDropRectItem* m_pRecvDropRectItem;	// 接收拖放事件

public:
	explicit MyGraphicsScene(QObject *parent = 0);

//signals:

//public slots :

public:
	void addGraphicsObject(QGraphicsObject* pQGraphicsObject);
	void adjustSceneRect(QPointF& sceneLeftTopPos, QPointF& sceneRightBtmPos);

protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *evt);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * m);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *evt);
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // GRAPHICSSCENE_H