#ifndef QGSTREAMERVIEW_H
#define QGSTREAMERVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSizePolicy>
#include <QMenu>
#include <QSplitter>

#include <Qt5GStreamer/QGst//Init>
#include <Qt5GStreamer/QGst/Ui/GraphicsVideoSurface>
#include <Qt5GStreamer/QGst/Ui/GraphicsVideoWidget>
#include <Qt5GStreamer/QGst/Pipeline>
#include <Qt5GStreamer/QGst/Element>
#include <Qt5GStreamer/QGst/ElementFactory>

class QGstreamerView : public QGraphicsView
{
    Q_OBJECT
private:
    QGst::ElementPtr source;
    QGst::ElementPtr sink;
    QGst::PipelinePtr pipeline;

    QWidget *old_parent;
    QList<int> old_sizes;
    bool docked;
    QGst::Ui::GraphicsVideoWidget *widget;

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    explicit QGstreamerView(QWidget *parent = 0);
    ~QGstreamerView();

signals:

public slots:

private slots:
    void dock_undock();
    void showContextMenu(QPoint pos);
};

#endif // QGSTREAMERVIEW_H
