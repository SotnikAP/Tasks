#include <algorithm>
#include <fstream>
#include <deque>
#include <iterator>
#include <iostream>

using namespace std;

int main()
{
     deque<double> first, second;
     ifstream one( "file1.txt" ), two( "file2.txt" );

     std::copy( istream_iterator<int>( one ), std::istream_iterator<int>(), back_inserter( first ) );
     std::copy( istream_iterator<int>( two ), std::istream_iterator<int>(), back_inserter( second ) );

     // Приравниваем размеры очередей.
     // Отрезаем начало от бОльшей очереди.
     if( first.size() > second.size() )
          first.erase( first.begin(), first.begin() + ( first.size() - second.size() ) );
     else if( second.size() > first.size() )
          second.erase( second.begin(), second.begin() + ( second.size() - first.size() ) );
     
     // Вывод в консоль.
     cout << "After initializing: \n";
     for_each( first.begin(), first.end(), []( double x )
     {
          cout << x << " ";
     } );
     cout << endl;
     for_each( second.begin(), second.end(), []( double x )
     {
          cout << x << " ";
     } );

     deque<double> common = first;

     // Суммируем квадраты и берём корень.
     for_each( common.begin(), common.end(), [ &second ]( double& x ) 
     {
          auto it= second.begin();
          x = sqrt( x*x + (*it)*(*it) );
          ++it;
     } );
     
     cout << "\nAfter sqrt and summ: \n";
     ostream_iterator<double> outIt( cout, " " );
     std::copy( common.begin(), common.end(), outIt );

     sort( common.rbegin(), common.rend() );

     cout << "\nAfter sorting: \n";
     std::copy( common.begin(), common.end(), outIt );

     std::system( "pause" );
     return 0;
}