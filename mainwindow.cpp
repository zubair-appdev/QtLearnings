#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stop = false;


    //OR
    // QMap<QString, QMap<QString, QMap<QString, QMap<QString, QMap<QString, int>>>>> myPlace1;


    myPlace["Asia"]["India"]["Telangana"]["Hyderabad"]["Adibatla"] = 501510;
    myPlace["Asia"]["India"]["Telangana"]["Hyderabad"]["Santhosh Nagar"] = 500069;

    myPlace["North America"]["Canada"]["San Diago"]["California"]["James Street"] = 345234;

    QString myContinent = "Asia";
    QString myCountry = "India";
    QString myState = "Telangana";
    QString myDistrict = "Hyderabad";
    QString myLocality = "Santhosh Nagar";

    qDebug()<<myPlace[myContinent][myCountry][myState][myDistrict][myLocality];

    qDebug()<<myPlace;

    int targetPincode = 345234;
    QString state = findStateForPincode(myPlace, targetPincode);

    if (!state.isEmpty())
        qDebug() << "State for pincode" << targetPincode << "is:" << state;
    else
        qDebug() << "Pincode not found!";


    // Learning try-catch and throw

    try
    {
        throw 43;

        std::vector<int> v;
        v.at(2);  // Out of range


    }
    catch (const std::exception &ex)
    {
        qDebug()<<ex.what();
    }
    catch(...)
    {
        qDebug()<<"Fatal Error";
    }



    auto lambda = [](int x,int y)->int{
        return x+y;
    };

    int result = lambda(2,4);
    qDebug()<<result;

    auto sum = [](int u,int v)->int{ return u + v;}(5,5);
    qDebug()<<sum<<" :sum";


    //mutable thing
    int counter = 0;
    auto lam = [counter]() mutable{
        counter++;
        qDebug()<<counter<<" :inside counter";
    };

    lam();
    qDebug()<<counter<<" :outside counter";

    qDebug()<<QThread::currentThread()<<" :currentThread and Id: "
            <<QThread::currentThreadId();

    QFuture<int> future = QtConcurrent::run([](){
        qDebug()<<QThread::currentThread()<<" :currentThread and Id: "
                <<QThread::currentThreadId();
        int i = 0;
        while(1)
        {
            qDebug()<<"HEy";
            i++;
            if(i == 100000)
            {

                return 100;
            }
        }
    });

    // THIS RESULT WILL BLOCK UI
//    int resultOfThread = future.result();
//    qDebug()<<resultOfThread<<" :resultOfThread";

    // THIS BELOW CODE NEVER BLOCKS UI PARALLEL TASKS HAPPEN NOW
    QFutureWatcher<void> *watcher = new QFutureWatcher<void>();
    connect(watcher,&QFutureWatcher<void>::finished,this,[](){
        qDebug()<<"Background task is done";
    });

    watcher->setFuture(future);

    qDebug() << "Cores available:" << QThread::idealThreadCount();

    //same as above line
    qDebug()<<QThreadPool::globalInstance()->maxThreadCount(); // Usually = number of logical cores

    qDebug()<<sizeof(void *);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::findStateForPincode(const continent &data, int pincodeToFind)
{
    qDebug() << "=== BEGIN PINCODE SEARCH ===";

    for (const QString &continentName : data.keys())
    {
        qDebug() << "\n[Continent Level] Keys:" << data.keys();
        qDebug() << "Checking Continent:" << continentName;

        const countryData &countries = data[continentName];
        qDebug() << "  [Country Level] Keys for" << continentName << ":" << countries.keys();

        for (const QString &countryName : countries.keys())
        {
            qDebug() << "  In Country:" << countryName;

            const stateData &states = countries[countryName];
            qDebug() << "    [State Level] Keys for" << countryName << ":" << states.keys();

            for (const QString &stateName : states.keys())
            {
                qDebug() << "    In State:" << stateName;

                const districtData &districts = states[stateName];
                qDebug() << "      [District Level] Keys for" << stateName << ":" << districts.keys();

                for (const QString &districtName : districts.keys())
                {
                    qDebug() << "      In District:" << districtName;

                    const pinCodeData &localities = districts[districtName];
                    qDebug() << "        [Locality Level] Keys for" << districtName << ":" << localities.keys();

                    for (const QString &localityName : localities.keys())
                    {
                        int currentPincode = localities[localityName];
                        qDebug() << "        Checking Locality:" << localityName
                                 << "→ Pincode:" << currentPincode;

                        if (currentPincode == pincodeToFind)
                        {
                            qDebug() << "\n🎯 Match found! Pincode" << pincodeToFind
                                     << "belongs to State:" << stateName;
                            return stateName;
                        }
                    }
                }
            }
        }
    }

    qDebug() << "\n❌ Pincode" << pincodeToFind << "not found in data.";
    qDebug() << "=== END PINCODE SEARCH ===";
    return "";
}




void MainWindow::on_pushButton_infiniteLopp_clicked()
{
    while(stop == false)
    {
        qDebug()<<"Hello";
        QCoreApplication::processEvents();
        QThread::msleep(1);
    }

    qDebug()<<"Loop is stopped !!!";
    stop = false;


}

void MainWindow::on_pushButton_stop_clicked()
{
    stop = true;
}
