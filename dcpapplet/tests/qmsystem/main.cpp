#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <qmtime.h>

void testTimezone()
{
    MeeGo::QmTime qm;
    QString ret;                                                               
    if(!qm.getTimezone(ret)){                                              
        qCritical("Error during asking QmTime for timezone");                  
     }                                                                          
    if(!qm.setTimezone(ret)){                                              
        qCritical("Error setting timezone");                  
     }                                                                          

}

void testDateTime()
{
    MeeGo::QmTime qmtime;
    QDateTime time = QDateTime::currentDateTime();
    
    qDebug() << "current date/time is" << time.toString();
    time.setTime(QTime(0,0,0));
    qDebug() << "Trying to set time to" << time.toString();
    if (!qmtime.setTime(time))
        qCritical("Error setting time");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    testTimezone();	
    testDateTime();
    return 0; 
}

