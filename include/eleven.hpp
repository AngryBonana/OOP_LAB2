#ifndef ELEVEN_H

#define ELEVEN_H
#include <cstdlib>
#include <string>

class Eleven
{
public:
    // === КОНСТРУКТОРЫ ===
    
    // Конструктор по умолчанию
    Eleven();
    
    // Конструктор с числовым значением (размер + значение)
    Eleven(const size_t& n, unsigned char t = '0');
    
    // Конструктор из списка инициализации (C++11)
    Eleven(const std::initializer_list<unsigned char>& t);
    
    // Конструктор из строки
    Eleven(const std::string& t);
    
    // === КОПИРУЮЩИЕ И ПЕРЕМЕЩАЮЩИЕ ОПЕРАЦИИ ===
    
    // Копирующий конструктор (Правило пяти)
    Eleven(const Eleven& other);
    
    // Перемещающий конструктор (C++11) - Правило пяти
    Eleven(Eleven&& other) noexcept;

    // === АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ ===

    // Сложение
    Eleven add(const Eleven& other) const;

    // Вычитание
    Eleven substraction(const Eleven& other) const;

    // === ОПЕРАЦИИ СРАВНЕНИЯ ===

    // Больше
    bool more(const Eleven& other) const;

    // Меньше
    bool less(const Eleven& other) const;

    // Равно
    bool equal(const Eleven& other) const;

    // Проверка на 0
    bool isNull() const;

    // === ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ
    // Получение результата в корректном отображении
    std::string get_value_for_print() const;

    // ===ГЕТТЕРЫ===
    // Строка из символов
    std::string getValue() const;
    
    // Размер
    size_t getSize() const;


    // === ДЕСТРУКТОР ===
    
    // Виртуальный деструктор (Правило пяти)
    virtual ~Eleven() noexcept;


private:
    size_t array_size ;
    unsigned char * data;
};


std::string reverse(std::string& str);

#endif