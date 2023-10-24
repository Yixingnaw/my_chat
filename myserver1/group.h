#ifndef GROUP_H
#define GROUP_H

#include<QtSql/QSqlDatabase>
#include<string>
#include<QHash>
class group
{
public:
    group(int id,QString group_name_,QString descrip_,QString photo_address_,QString gop_count_){
        group_id=id;
        group_name=group_name_;
        description=descrip_;
        photo_address=photo_address_;
        group_count=gop_count_;
    }
    group(){}
    group(const group& x){
        group_id=x.group_id;
        group_name=x.group_name;
        description=x.description;
        photo_address=x.photo_address;
        group_count=x.group_count;
    }
    group&   operator=(const group& x){
        if (this != &x) {
            group_id=x.group_id;
            group_name=x.group_name;
            description=x.description;
            photo_address=x.photo_address;
            group_count=x.group_count;
        }
        return *this;
    }
   QString getGrouprname() const {
       return group_name;
   }

   QString getdescription() const {
       return description;
   }

   QString getphoto_address() const {
       return photo_address;
   }

   QString get_group_count() const {
       return group_count;
   }
   int get_id()const{
       return  group_id;
   }
private:
   int group_id;
   QString group_name;
   QString description;
   QString photo_address;
   QString group_count;
public:
   // 比较操作符，用于哈希表中的比较

bool operator==(const group& other) const {
       return   group_name == other.group_name && group_count == other.group_count;

   }

bool operator<(const group&x)const
{
    return  group_count<x.get_group_count();
}

};

#endif // GROUP_H
