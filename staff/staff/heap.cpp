#include <iostream>
#include <fstream>
#include <algorithm>

//#include <platform_pack/pkdef.h>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
//#include <platform_pack/pkend.h>

#include "heap.h"

using namespace heap;

Heap::Heap()
{

}

void Heap::AddEmployee( const employee::Employee& empl )
{
     boost::unique_lock< boost::shared_mutex > w_lock( writeOrRead_ );
     if( empl.GetPosition() != employee::undefind )
     {
          treeOfEmployees_.push_back( empl );
     }
     else
     {
          // Должность не установлена.
          return;
     }

     // Проверка сбалансированности дерева.
     HeapBalancing();
}

void Heap::HeapBalancing()
{
     int currPosition, parent;
     currPosition = treeOfEmployees_.size() - 1;
     parent = ( currPosition - 1 ) / 2;
     while( parent >= 0 && currPosition > 0 )
     {
          if( treeOfEmployees_[currPosition].GetPosition() > treeOfEmployees_[parent].GetPosition() )
          {
               std::swap( treeOfEmployees_[currPosition], treeOfEmployees_[parent] );
          }
          currPosition = parent;
          parent = ( currPosition - 1 ) / 2;
     }
}

std::ostream& heap::operator<<( std::ostream& os, Heap& employees )
{
     for( size_t i = 0; i < employees.treeOfEmployees_.size(); ++i )
     {
          boost::shared_lock<boost::shared_mutex> r_lock( employees.writeOrRead_ );
          os << employees.treeOfEmployees_[i];
     }
     return os;
}

