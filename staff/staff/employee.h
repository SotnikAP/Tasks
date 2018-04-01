/// @file
/// @brief Описание интерфейса класса employee.
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

/// @brief Класс, содержащий всю информацию о работнике.
/// 
/// Содержит имя, должность и дату рождения работника.
/// Является составной частью вспомогательной структуры EmployeeWithKey.
class Employee
{
public:
     Employee( std::string name = "NoName", std::string post = "employee", std::string birth = "20.12.2000" );

     /// @brief Проверка корректности должности и преобразование в элемент перечисления Position.
     ///
     /// Проверяет должность на корректность, если должность не найдена - работник в дерево добавлен не будет.
     /// 
     /// @return Возвращает соответствующий должности элемент перечисления.
     /// @return Возвоащает элемент undefind, если должность не определена.
     Position GetPosition() const;

     friend std::ostream& operator<<( std::ostream& os, const Employee& target );
private:
     std::string name_;
     std::string post_;
     std::string dateOfBirth_;
}; // !class Employee
} // !namespace employee

#endif // !EMPLOYEE_H