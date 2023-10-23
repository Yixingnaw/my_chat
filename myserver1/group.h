#ifndef GROUP_H
#define GROUP_H

#include<QtSql/QSqlDatabase>
#include<string>

class group
{
public:
    group();

   QString group_name;
   QString description;
   QString photo_address;
   QString group_count;

};

#endif // GROUP_H
