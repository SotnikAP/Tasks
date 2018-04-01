#include "employee.h"

using namespace employee;

Employee::Employee( std::string name, std::string post, std::string birth )
     : name_( name )
     , post_( post )
     , dateOfBirth_( birth )
{

}

Position Employee::GetPosition() const
{
     if( post_ == "director" || post_ == " director" )
     {
          return director;
     }
     else if( post_ == "manager" || post_ == " manager" )
     {
          return manager;
     }
     else if( post_ == "employee" || post_ == " employee" )
     {
          return employee;
     }
     else
     {
          // ƒолжность не найдена и в дерево добавлена не будет.
          return undefind;
     }
}

std::ostream& employee::operator<<( std::ostream& os, const Employee& target )
{
     os << target.name_ << ", ";
     if( target.GetPosition() == director || target.GetPosition() == manager
          || target.GetPosition() == employee )
     {
          os << target.post_ << ", ";
     }
     else
     {
          os << "undefined post, ";
     }
     os << target.dateOfBirth_ << std::endl;
     return os;
}
