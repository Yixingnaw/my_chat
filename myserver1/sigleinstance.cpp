#include "sigleinstance.h"

sigleInstance::sigleInstance()
{

}
sigleInstance* getInstance(){
    return  new sigleInstance();
}
void      sigleInstance:: send(const QByteArray x){
         emit sendmesssage(x);
}
 //QMutex sigleInstance::mute;
