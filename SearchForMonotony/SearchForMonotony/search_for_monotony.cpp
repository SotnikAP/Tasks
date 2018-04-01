/// @file
/// @brief Поиск монотонных строк квадратного массива
///
/// @copyright Copyright 2018 InfoTeCS.

#include <iostream>
#include <vector>
#include <streambuf>
#include <algorithm>
#include <iterator>
#include <assert.h>

#include <boost/algorithm/cxx11/is_sorted.hpp>

typedef std::vector<int> vecOfInt;

namespace monotonic
{
bool IsMonotonicIncreasing( const vecOfInt& arr )
{
     assert( arr.empty() == 0 );

     return boost::algorithm::is_sorted( arr.begin(), arr.end() );
}

bool IsMonotonicDecreasing( const vecOfInt& arr )
{
     assert( arr.empty() == 0 );

     return boost::algorithm::is_sorted( arr.rbegin(), arr.rend() );
}

void PrintArrInConsole( const std::vector< vecOfInt >& arr )
{
     assert( arr.empty() == 0 );

     for ( std::vector< vecOfInt >::const_iterator it = arr.begin(); it != arr.end(); ++it )
     {
          std::copy( it->begin(), it->end(), std::ostream_iterator<int>( std::cout, " " ) );
          std::cout << "\n";
     }
}
} //!namespace monotonic

void main()
{
     int repeatOrQuit = 0;
     std::cout << "Enter number of strings (equal to number of numbers in each string) or any other symbol for quit: ";
     while ( std::cin >> repeatOrQuit )
     {
          int numOfStrings = repeatOrQuit;
          while ( numOfStrings <= 1 )
          {
               // Проверка корректности ввода размера массива.
               std::cout << "Enter an integer number more than 1 (any other symbol for quit): ";
               if ( !( std::cin >> numOfStrings ) )
                    return;
          }

          std::vector<std::vector<int>> arr;
          arr.resize( numOfStrings );
          for ( int currentVector = 0; currentVector < numOfStrings; ++currentVector )
               arr[currentVector].resize( numOfStrings );

          for ( int currentString = 0; currentString < numOfStrings; ++currentString )
          {
               for ( int currentElem = 0; currentElem < numOfStrings; ++currentElem )
               {
                    std::cout << "Enter " << currentElem + 1 << " element of " << currentString + 1 << " string: ";
                    while ( !( std::cin >> arr[currentString][currentElem] ) || std::cin.peek() != '\n' )
                    {
                         // Проверка корректности ввода.
                         std::cout << "Please, enter number: ";
                         std::cin.clear();
                         while ( std::cin.get() == '\n' );
                    }
               } // !for
          } // !for

          std::cout << "Here is entered array: " << std::endl;
          monotonic::PrintArrInConsole( arr );

          std::vector<std::vector<int>> monotonicStrings;
          int numOfMonotonicStr = 0;

          for ( int currentString = 0; currentString < numOfStrings; ++currentString )
          {
               if ( monotonic::IsMonotonicIncreasing( arr[currentString] ) || monotonic::IsMonotonicDecreasing( arr[currentString] ) )
               {
                    monotonicStrings.push_back( arr[currentString] );
                    numOfMonotonicStr++;
               }
          } // !for

          if ( monotonicStrings.size() == 0 )
          {
               std::cout << "There are no monotonic strings.\n";
          }
          else
          {
               std::cout << "Here are monotonic strings: \n";
               monotonic::PrintArrInConsole( monotonicStrings );
          }

          std::cout << "Enter number of strings (equal to number of numbers in each string) or any other symbol for quit: ";
     } // !while
}