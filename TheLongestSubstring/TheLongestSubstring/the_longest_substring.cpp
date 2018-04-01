/// @file
/// @brief Поиск самой длиной подстроки без цифр.
///
/// @copyright Copyright 2018 InfoTeCS

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost\algorithm\is_palindrome.hpp>
#include <assert.h>

namespace longeststring
{
std::string FindLongestNoNumbers( const std::string& initialStr, int prevMax )
{
     int currLen = 0; //< Длина текущей подстроки.
     std::string::const_iterator currentStringBegin;
     std::string longestSubstring;	//< Самая длинная подстрока на данный момент.
     for ( std::string::const_iterator cit = initialStr.begin(); cit != initialStr.end(); ++cit )
     {
          if ( isdigit( *cit ) )
          {
               if ( currLen > prevMax )
               {
                    longestSubstring.clear();
                    longestSubstring.insert( longestSubstring.begin(), currentStringBegin, currentStringBegin + currLen );
                    prevMax = currLen; //< Обновляем длину предыдущей максимальной строки.
                    currLen = 0;
               }
               else
               {
                    currLen = 0;
               }
          }
          else
          {
               if ( currLen == 0 )
               {
                    // Длина текущей проверяемой подстроки нулевая (только начали её проверять).
                    currLen++;
                    currentStringBegin = cit;
               }
               else
               {
                    currLen++;
               }
          }
     } // !for

     // Цифра не встретилась, а закончилась строка.
     if ( currLen < longestSubstring.length() )
     {
          // Эта подстрока меньше предыдущей максимальной.
          return longestSubstring;
     }
     else
     {
          // И эта подстрока больше предыдущей максимальной.
          longestSubstring.clear();
          longestSubstring.insert( longestSubstring.begin(), currentStringBegin, currentStringBegin + currLen );
          return longestSubstring;
     }
}


std::string FindTheLongestString( const std::vector< std::string >& vecOfStrings )
{
     assert( vecOfStrings.empty() == 0 );

     std::string maxString = "";
     for ( std::vector< std::string >::const_iterator cit = vecOfStrings.begin(); cit != vecOfStrings.end(); ++cit )
     {
          std::string currString;
          currString = longeststring::FindLongestNoNumbers( *cit, maxString.length() );
          if ( currString.length() > maxString.length() )
          {
               maxString = currString;
          }
     }
     return maxString;
}
} //!namespace longeststring

int main()
{
     int repeatOrQuit = 0;
     std::cout << "Enter number of strings (positive integer) or any other symbol for quit: ";
     while ( std::cin >> repeatOrQuit )
     {
          int numOfStrings = repeatOrQuit;
          while ( numOfStrings <= 0 )
          {
               std::cerr << "Number of strings can't be negative. Try again (or enter not a number for quit): ";
               std::cin.clear();
               if ( !( std::cin >> numOfStrings ) )
               {
                    return 0;
               }
          }

          std::cin.get(); // Забираем из потока "\n".

          std::vector< std::string > arrStrings; //< Массив самых длинных подстрок без цифр.
          for ( int stringNumber = 0; stringNumber < numOfStrings; ++stringNumber )
          {
               std::string readFromFile;
               std::cout << "Enter string #" << stringNumber << ": ";
               std::getline( std::cin, readFromFile );
               arrStrings.push_back( readFromFile );
          }

          std::string maxString = longeststring::FindTheLongestString( arrStrings );
          std::cout << "Max substring is: " << maxString << std::endl;

          if ( tolower( maxString[0] ) == tolower( maxString[maxString.length() - 1] ) )
          {
               if ( !boost::algorithm::is_palindrome( maxString ) )
               {
                    std::reverse( maxString.begin(), maxString.end() );
                    std::cout << "Reverse of max substring: " << maxString;
               }
               else
               {
                    std::cout << "Substring is palindrome: " << maxString;
               }
          }
          else
          {
               std::reverse( maxString.begin(), maxString.end() );
               std::cout << "Reverse of max substring: " << maxString;
          }

          std::cout << std::endl << "Enter number of strings (positive integer) or NOT-number for quit: ";
     } // !while
     return 0;
}