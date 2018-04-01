/// @file
/// @brief 
///
/// @copyright Copyright 2018 InfoTeCS

#include <iostream>
#include <fstream>
#include <queue>
#include <string>

//#include <platform_pack/pkdef.h>
#include <boost/thread.hpp>
#include <boost/ref.hpp>
//#include <platform_pack/pkend.h>

#include "employee.h"
#include "heap.h"

employee::Employee ReadFileLine( std::ifstream& input )
{
     std::string name, post, birth;
     std::getline( input, name, ',' );
     std::getline( input, post, ',' );
     std::getline( input, birth );
     // Делаем поле должности не чувствительным к регистру.
     std::transform( post.begin(), post.end(), post.begin(), ::tolower );
     return employee::Employee( name, post, birth );
}

employee::Employee ReadFromConsole()
{
     std::string name, post, birth;
     std::cout << "Enter the name: ";
     std::getline( std::cin, name, '\n' );
     std::cout << "Enter the post (director|manager|employee): ";
     std::getline( std::cin, post, '\n' );
     // Делаем поле должности не чувствительным к регистру.
     std::transform( post.begin(), post.end(), post.begin(), ::tolower );
     std::cout << "Enter the date of birth: ";
     std::getline( std::cin, birth, '\n' );
     return employee::Employee( name, post, birth );
}

void MakeHeapFromQueue( std::queue< employee::Employee >& employees, heap::Heap& treeOfEmployees )
// Стартовая функция первого рабочего потока.
// Строит дерево через очередь FIFO.
{
     while( !employees.empty() )
     {
          treeOfEmployees.AddEmployee( employees.front() );
          employees.pop();
     }
}

void PrintHeapInFile(  heap::Heap& treeOfEmployees )
// Стартовая функция (вывод в файл) второго рабочего потока.
{
     std::ofstream fout( "result.txt" );
     fout << treeOfEmployees;
     fout.close();
}

void PrintHeapInConsole( heap::Heap& treeOfEmployees )
// Стартовая функция (вывод в консоль) второго рабочего потока.
{
     std::cout << treeOfEmployees;
}

int main( int argc, char* argv[] )
{
     std::queue< employee::Employee > employees;

     if( argc == 2 ) // Подан файл.
     {
          std::ifstream input( argv[1] );
          if( !input.is_open() )
          {
               std::cerr << "Can't open the file." << std::endl;
               exit( EXIT_FAILURE );
          }
          while( !input.eof() )
          {
               employees.push( ReadFileLine( input ) );
          }
     }
     else
     {
          // Файл не подан, считывание с клавиатуры.
          std::cout << "The file was not submitted. Keyboard entry: " << std::endl;
          char keepOrStop = 'k';
          while( keepOrStop != 'q' )
          {
               employees.push( ReadFromConsole() );
               std::cout << "Enter any symbol to add new employee (q for stop): ";
               std::cin >> keepOrStop;
               while( std::cin.get() != '\n' );
          }
     }

     char fileOrConsole;
     std::cout << "Enter 'f' for output to file" << std::endl
          << "or 'c' for output to console" << std::endl
          << "Your choice: ";
     std::cin >> fileOrConsole;

     heap::Heap treeOfEmployees;
     boost::thread heapMaker( MakeHeapFromQueue, boost::ref( employees ), boost::ref( treeOfEmployees ) );

     if( fileOrConsole == 'f' )
     {
          boost::thread writingInFile( PrintHeapInFile, boost::ref( treeOfEmployees ) );
          writingInFile.join();
     }
     else
     {
          boost::thread writingInConsole( PrintHeapInConsole, boost::ref( treeOfEmployees ) );
          writingInConsole.join();
     }

     heapMaker.join();
     system( "pause" );
}