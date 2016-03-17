#include "qdialogsettings.h"

QDialogSettings::QDialogSettings()
{
    this->setWindowTitle("Settings");
    QGridLayout* temp = new QGridLayout;

    temp->addWidget(new QtempLabel("Trend buffer size[mm:ss]:"),0,0);
    temp->addWidget(new QtempLabel("Trend sample time[ms]:"),0,2);
    temp->addWidget(new QtempLabel("Default arena folder location:"),1,0);
    temp->addWidget(new QtempLabel("Camera save folder location:"),2,0);
    temp->addWidget(new QtempLabel("Log save folder location:"),3,0);

    trendTimeSpan = new QDateTimeEdit(settings->value("trendTimeSpan").toTime());
    trendTimeSpan->setMaximumTime(QTime(0,59,59));
    trendSampleTime_ms = new QLineEdit(settings->value("trendSampleTime_ms").toString());
    trendSampleTime_ms->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    trendSampleTime_ms->setMaximumWidth(50);
    trendSampleTime_ms->setValidator(new QIntValidator(0,9999));
    logFolder = new QLineEdit(settings->value("logFolder").toString());
    camFolder = new QLineEdit(settings->value("camFolder").toString());
    arenaFolder = new QLineEdit(settings->value("arenaFolder").toString());
    forceLog = new QCheckBox("Force logging ON on start");

    forceLog->setChecked(settings->value("forceLog").toBool());

    temp->addWidget(trendTimeSpan,0,1);
    temp->addWidget(trendSampleTime_ms,0,3);
    temp->addWidget(arenaFolder,1,1,1,5);
    temp->addWidget(camFolder,2,1,1,5);
    temp->addWidget(logFolder,3,1,1,5);
    temp->addWidget(forceLog,0,4);

    QIcon icon(":/images/icons/open_folder_yellow.png");

    QPushButton* searchArena = new QPushButton();
    QPushButton* searchLog = new QPushButton();
    QPushButton* searchCam = new QPushButton();

    searchArena->setIcon(icon);
    searchLog->setIcon(icon);
    searchCam->setIcon(icon);

    searchArena->setFixedSize(25,25);
    searchLog->setFixedSize(25,25);
    searchCam->setFixedSize(25,25);

    temp->addWidget(searchArena,1,5);
    temp->addWidget(searchCam,2,5);
    temp->addWidget(searchLog,3,5);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    temp->addWidget(buttons,4,3);
    this->setLayout(temp);

    link[searchArena] = arenaFolder;
    link[searchLog] = logFolder;
    link[searchCam] = camFolder;

    connect(searchArena,SIGNAL(clicked()),this,SLOT(findFolder()));
    connect(searchLog,SIGNAL(clicked()),this,SLOT(findFolder()));
    connect(searchCam,SIGNAL(clicked()),this,SLOT(findFolder()));

    QObject::connect(buttons, SIGNAL(accepted()), this, SLOT(saveConfig()));
    QObject::connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));
}

void QDialogSettings::findFolder()
{
    QString temp = QFileDialog::getExistingDirectory(this,tr("Select folder"), link[(QPushButton*)QObject::sender()]->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(temp.size())link[(QPushButton*)QObject::sender()]->setText(temp);
}

void QDialogSettings::saveConfig()
{
    settings->setValue("logFolder", logFolder->text());
    settings->setValue("camFolder", camFolder->text());
    settings->setValue("arenaFolder", arenaFolder->text());
    settings->setValue("trendTimeSpan", trendTimeSpan->text());
    settings->setValue("trendSampleTime_ms", trendSampleTime_ms->text());
    settings->setValue("forceLog", forceLog->isChecked());

    settings->setValue("logSubFolder", settings->value("logFolder").toString() + QDate::currentDate().toString("yy-MM-dd") + "/");
    settings->setValue("camSubFolder", settings->value("camFolder").toString() + QDate::currentDate().toString("yy-MM-dd") + "/");

    if(!QDir(settings->value("logSubFolder").toString()).exists())QDir().mkdir(settings->value("logSubFolder").toString());
    if(!QDir(settings->value("camSubFolder").toString()).exists())QDir().mkdir(settings->value("camSubFolder").toString());


    emit accept();
}

QtempLabel::QtempLabel(QString label) : QLabel(label)
{
    this->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
}