/// @file
/// @brief �������� ���������� ������ employee.
///
/// @copyright Copyright 2018 InfoTeCS

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

namespace employee
{
enum Position
{
     undefind, employee, manager, director
};

/// @brief �����, ���������� ��� ���������� � ���������.
/// 
/// �������� ���, ��������� � ���� �������� ���������.
/// �������� ��������� ������ ��������������� ��������� EmployeeWithKey.
class Employee
{
public:
     Employee( std::string name = "NoName", std::string post = "employee", std::string birth = "20.12.2000" );

     /// @brief �������� ������������ ��������� � �������������� � ������� ������������ Position.
     ///
     /// ��������� ��������� �� ������������, ���� ��������� �� ������� - �������� � ������ �������� �� �����.
     /// 
     /// @return ���������� ��������������� ��������� ������� ������������.
     /// @return ���������� ������� undefind, ���� ��������� �� ����������.
     Position GetPosition() const;

     friend std::ostream& operator<<( std::ostream& os, const Employee& target );
private:
     std::string name_;
     std::string post_;
     std::string dateOfBirth_;
}; // !class Employee
} // !namespace employee

#endif // !EMPLOYEE_H