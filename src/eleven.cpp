#include "../include/eleven.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <string>

// По умолчанию 0
Eleven::Eleven() : array_size(1), data(nullptr)
{
    data = new unsigned char[array_size];
    data[0] = '0';
}

// Из строки
Eleven::Eleven(const std::string& t) : array_size(0), data(nullptr)
{
    size_t start_pos = t.find_first_not_of("0");
    if (start_pos == std::string::npos) 
    {
        array_size = 1;
        data = new unsigned char[array_size];
        data[0] = '0';
        return;
    }

    std::string tmp;
    for (size_t i = start_pos; i < t.length(); i++)
    {
        if (t[i] - '0' > 9 && t[i] != 'a' && t[i] != 'A')
        {
            throw std::invalid_argument("Got invalid character!\n");
        }
        tmp.push_back(std::toupper(t[i]));
    }

    array_size = tmp.length();
    if (array_size == 0)
    {
        array_size = 1;
        data = new unsigned char[array_size];
        data[0] = '0';
    }
    else 
    {
        data = new unsigned char[array_size];
        for (size_t i = 0; i < array_size; i++)
        {
            data[array_size - 1 - i] = tmp[i];
        }
    }
}

// Конструктор с числовым значением (размер + значение) (Число из одинаковых символов)
Eleven::Eleven(const size_t& n, unsigned char t) : array_size(n), data(nullptr)
{
    unsigned char tmp;
    if ((t - '0' >= 0 && t - '0' <= 9))
    {
        tmp = t;
    }
    else if (t == 'A' || t == 'a')
    {
        tmp = 'A';
    }
    else  
    {
        throw std::invalid_argument("Got invalid character!\n");
    }
    if (n == 0)
    {
        array_size = 1;
    }
    data = new unsigned char[array_size];
    for (size_t i = 0; i < array_size; i++)
    {
        data[i] = tmp;
    }

}

// Конструктор из списка инициализации
Eleven::Eleven(const std::initializer_list<unsigned char>& t)
{
    array_size = t.size();
    data = new unsigned char[array_size];
    size_t index = 0;
    for (const auto& value : t) {
        if (value - '0' > 9 && value != 'A' && value != 'a')
        {
            throw std::invalid_argument("Got invalid character!\n");
        }
        if (value == 'a')
        {
            data[index++] = 'A';
            continue;
        }
        data[index++] = value;
    }
}


// === КОПИРУЮЩИЕ И ПЕРЕМЕЩАЮЩИЕ ОПЕРАЦИИ ===
    
// Копирующий конструктор (Правило пяти)
Eleven::Eleven(const Eleven& other)
{
    array_size = other.array_size;
    data = new unsigned char[array_size];

    for (size_t i = 0; i < array_size; i++)
    {
        data[i] = other.data[i];
    }
}
    
// Перемещающий конструктор (C++11) - Правило пяти
Eleven::Eleven(Eleven&& other) noexcept
{
    array_size = other.array_size;
    data = other.data;
    other.array_size = 0;
    other.data = nullptr;
}

// === ГЕТТЕРЫ ===
// Строка из символов
std::string Eleven::getValue() const
{
    std::string res;
    for (size_t i = 0; i < array_size; i++)
    {
        res.push_back(data[i]);
    }
    return res;
}
    
// Размер
size_t Eleven::getSize() const
{
    return array_size;
}

// === ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ
// Получение результата в корректном отображении
std::string Eleven::get_value_for_print() const
{
    std::string res;
    for (size_t i = 0; i < array_size; i ++)
    {
        res.push_back(data[array_size - 1 - i]);
    }
    return res;

}


// === АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ ===

// Сложение
Eleven Eleven::add(const Eleven& other) const
{
    std::string left = this->getValue();
    std::string right = other.getValue();
    std::string res;
    bool dop = false;
    unsigned char l;
    unsigned char r;
    unsigned char tmp;
    for (size_t i = 0; i < std::max(left.size(), right.size()); i++)
    {
        if (i < left.size())
        {
            if (left[i] == 'A' || left[i] == 'a')
            {
                l = 10;
            }
            else
            {
                l = left[i] - '0';
            }
        }
        else 
        {
        l = 0;
        }

        if (i < right.size())
        {
            if (right[i] == 'A' || right[i] == 'a')
            {
                r = 10;
            }
            else
            {
                r = right[i] - '0';
            }
        }
        else 
        {
        r = 0;
        }

        tmp = l + r;
        if (dop)
        {
            tmp++;
            dop = false;
        }
        if (tmp / 11 >= 1)
        {
            dop = true;
            tmp -= 11;
        }
        if (tmp == 10)
        {
            res.push_back('A');
            continue;
        }
        res.push_back(tmp + '0');
    }
    if (dop)
    {
        res.push_back('1');
    }

    return Eleven(reverse(res));
}

// Вычитание
Eleven Eleven::substraction(const Eleven& other) const
{
    size_t lsize = this->getSize();
    size_t rsize = other.getSize();
    if (lsize < rsize)
    {
        throw std::underflow_error("Result is negative!\n");
    }
    std::string left = this->getValue();
    std::string right = other.getValue();
    std::string res;

    int l;
    int r;
    int tmp;
    bool dop = false;
    for (size_t i = 0; i < lsize; i++)
    {
        if (left[i] == 'A' || left[i] == 'a')
        {
            l = 10;
        }
        else
        {
            l = left[i] - '0';
        }

        if (i < rsize)
        {
            if (right[i] == 'A' || right[i] == 'a')
            {
                r = 10;
            }
            else
            {
                r = right[i] - '0';
            }
        }
        else 
        {
        r = 0;
        }
        
        tmp = l - r;
        if (dop)
        {
            tmp--;
            dop = false;
        }
        if (tmp < 0)
        {
            tmp += 11;
            dop = true;
        }

        if (tmp == 10)
        {
            res.push_back('A');
        }
        else  
        {
            res.push_back(tmp + '0');
        }

        if (i == lsize - 1 && dop)
        {
            throw std::underflow_error("Result is negative!\n");
        }

        
    }
    return Eleven(reverse(res));
}

// === ОПЕРАЦИИ СРАВНЕНИЯ ===

// Проверка на ноль
bool Eleven::isNull() const
{
    if (array_size == 1 && data[0] == '0')
    {
        return true;
    }
    return false;
}
// Больше
bool Eleven::more(const Eleven& other) const
{
    try
    {
        Eleven res = this->substraction(other);
        return !res.isNull();
    }
    catch (std::underflow_error)
    {
        return false;
    }
    
}

// Меньше
bool Eleven::less(const Eleven& other) const
{
    return other.more(*this);
}

// Равно
bool Eleven::equal(const Eleven& other) const
{
    if (this->getSize() != other.getSize())
    {
        return false;
    }
    size_t s = this->getSize();
    std::string l = this->getValue();
    std::string r = other.getValue();
    for (size_t i = 0; i < s; i++)
    {
        if (l[i] != r[i])
        {
            return false;
        }
    }
    return true;
}

// === ДЕСТРУКТОРЫ ===
Eleven::~Eleven() noexcept
{
    if (data != nullptr)
    {
        delete [] data;
        data = nullptr;
    }

    array_size = 0;
}


std::string reverse(std::string& str)
{
    std::string res;
    for (size_t i = str.size(); i > 0; i--)
    {
        res.push_back(str[i - 1]);
    }
    return res;
}