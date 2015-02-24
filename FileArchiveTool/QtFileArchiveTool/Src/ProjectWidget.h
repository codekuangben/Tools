#ifndef __PROJECTWIDGET_H
#define __PROJECTWIDGET_H

#include <QtWidgets>

namespace Ui
{
	class ProjectWidget;
}

class ProjectWidget : public QDockWidget
{
	Q_OBJECT

public:
	explicit ProjectWidget(QWidget *parent = 0);
	~ProjectWidget();

public Q_SLOTS:
	void on_treeView_customContextMenuRequested(const QPoint& pos);
	void setValue(int);

Q_SIGNALS:
	void onTreeItemSelChangeaa(bool isDir, std::string path);
	void valueChanged(int);

private:
	Ui::ProjectWidget *m_ui;
	QDirModel *m_pModel;
};

#endif // PROJECTWIDGET_H