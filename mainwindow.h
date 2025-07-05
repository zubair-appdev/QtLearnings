#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    inline void pauseFor(int milliseconds) {
        QEventLoop loop;
        QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);  // After delay, quit the event loop
        loop.exec();  // Start the event loop and wait for it to quit
    }

    QDialog *createPleaseWaitDialog(const QString &text);



private slots:
    void on_pushButton_infiniteLopp_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_createDialog_clicked();

    void on_pushButton_closeDialog_clicked();

private:
    Ui::MainWindow *ui;

    typedef QMap<QString,int> pinCodeData;
    typedef QMap<QString,pinCodeData> districtData;
    typedef QMap<QString,districtData> stateData;
    typedef QMap<QString,stateData> countryData;
    typedef QMap<QString,countryData> continent;

    continent myPlace;

    QString findStateForPincode(const continent &data, int pincodeToFind);

    bool stop;

    QDialog *dlg;

};
#endif // MAINWINDOW_H
