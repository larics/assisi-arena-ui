#ifndef CASUTREEITEM_H
#define CASUTREEITEM_H

#include <fstream>
#include <QTreeWidgetItem>

#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>

#include <nzmqt/nzmqt.hpp>
#include "dev_msgs.pb.h"
#include "global.h"

using namespace nzmqt;
using namespace AssisiMsg;
using namespace boost;
using namespace std;

class CasuTreeItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

private:
    nzmqt::ZMQContext* context_;
    nzmqt::ZMQSocket* pub_sock_;
    nzmqt::ZMQSocket* sub_sock_;

    QTimer* connection_timer;

    // Connect the publisher and subscriber
    void connect_();

    QString log_name;
    bool log_open;
    ofstream log_file;
    void openLogFile();
    void closeLogFile();

    QString casu_name;

public:
    bool connected;
    bool led_on;

    QColor led_color;

    QString sub_addr;
    QString pub_addr;
    QString msg_addr;

    QTreeWidgetItem *widget_IR;
    QTreeWidgetItem *widget_LED;
    QTreeWidgetItem *widget_temp;
    QTreeWidgetItem *widget_vibr;
    QTreeWidgetItem *widget_light;

    CasuTreeItem(QObject *parent, QString name);

    void setAddr(QString sub, QString pub, QString msg);

    void setSelected(bool select);

signals:
    void updateScene();

private slots:
    void widgetClicked();

    void messageReceived(const QList<QByteArray>& message);

    void connectionTimeout();
};

#endif // CASUTREEITEM_H