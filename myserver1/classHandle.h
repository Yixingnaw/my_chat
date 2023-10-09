#ifndef CLASSHANDLE_H
#define CLASSHANDLE_H
#include <QThreadPool>
#include <QObject>
#include<QTcpSocket>
class classHandle : public QRunnable
{

public:
      classHandle(qintptr socketDescriptor);
void run() override;

public slots:

private:
   qintptr socket_Descriptor;
   std::mutex mutex;
   std::mutex mutex_rb;
};

#endif // CLASSHANDLE_H
