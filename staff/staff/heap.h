/// @file
/// @brief �������� ���������� ����������� ���������.
///
/// @copyright Copyright 2018 InfoTeCS

#ifndef HEAP_H
#define HEAP_H

#include <vector>

//#include <platform_pack/pkdef.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
//#include <platform_pack/pkend.h>

#include "employee.h"

namespace heap
{
/// @brief �������� ���� (������), ���������� ������ ����������.
///
/// ����������� ��������� - �������� ����.
/// �������� ������ ���� ����������, ��������� ������� ����������.
/// ��������� ��������:
/// ���������� ����� ��������� ������ ��������.
/// ���������� ����� ��������� �������� ��� ��������.
/// ������� ���������� ����� ��������� ��������, �������� ��� ������� ��������.
class Heap
{
public:
     Heap();

     /// @brief ��������� ��������� � ������.
     ///
     /// ��������� ��������� � ������, ���� ��� ��������� ����������.
     /// ��������������� ������ ����� ���������� ���������.
     ///
     /// @param ��������, ���������� � ������� ���������� �������� � ������.
     void AddEmployee( const employee::Employee& empl );

     friend std::ostream& operator<<( std::ostream& os, Heap& employees );
private:
     std::vector< employee::Employee > treeOfEmployees_;
     boost::shared_mutex writeOrRead_;

     /// @brief ����������� �������� ����.
     ///
     /// ����������� �������� ���� ��� �������������.
     /// ������������ ��� ���������� ������ ���������.
     void HeapBalancing();
}; // !class Heap
} // !namespace heap

#endif // !HEAP_H