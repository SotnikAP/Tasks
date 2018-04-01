/// @file
/// @brief Описание интерфейса древовидной структуры.
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
/// @brief Двоичная куча (дерево), содержащая данные работников.
///
/// Древовидная структура - двоичная куча.
/// Содержит данные всех работников, должности которых определены.
/// Соблюдает иерархию:
/// Директором может управлять только директор.
/// Менеджером может управлять директор или менеджер.
/// Рядовым работником может управлять директор, менеджер или рядовой работник.
class Heap
{
public:
     Heap();

     /// @brief Добавляет работника в дерево.
     ///
     /// Добавляет работника в дерево, если его должность определена.
     /// Перебалансирует дерево после добавления работника.
     ///
     /// @param Работник, информацию о котором необходимо добавить в дерево.
     void AddEmployee( const employee::Employee& empl );

     friend std::ostream& operator<<( std::ostream& os, Heap& employees );
private:
     std::vector< employee::Employee > treeOfEmployees_;
     boost::shared_mutex writeOrRead_;

     /// @brief Балансирует двоичную кучу.
     ///
     /// Балансирует двоичную кучу при необходимости.
     /// Используется при добавлении нового работника.
     void HeapBalancing();
}; // !class Heap
} // !namespace heap

#endif // !HEAP_H