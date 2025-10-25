#include <iostream>
#include "include/eleven.hpp"

int main() {
    std::cout << "ДЕМОНСТРАЦИЯ КЛАССА ELEVEN (11-ричная система)\n";
    std::cout << "=============================================\n\n";

    std::cout << "1. КОНСТРУКТОРЫ:\n";
    std::cout << "----------------\n";
    
    Eleven default_num;
    std::cout << "По умолчанию: " << default_num.get_value_for_print() << std::endl;
    
    Eleven str_num1("123A5");
    std::cout << "Из строки '123A5': " << str_num1.get_value_for_print() << std::endl;
    
    Eleven str_num2("000A5");
    std::cout << "Из строки '000A5': " << str_num2.get_value_for_print() << std::endl;
    
    Eleven str_num3("00000");
    std::cout << "Из строки '00000': " << str_num3.get_value_for_print() << std::endl;
    
    Eleven size_num1(5, '3');
    std::cout << "5 цифр '3': " << size_num1.get_value_for_print() << std::endl;
    
    Eleven size_num2(4, 'A');
    std::cout << "4 цифры 'A': " << size_num2.get_value_for_print() << std::endl;
    
    Eleven original("A57");
    Eleven copy(original);
    std::cout << "Копия из 'A57': " << copy.get_value_for_print() << std::endl;
    
    Eleven moved(std::move(Eleven("789")));
    std::cout << "Перемещенный из '789': " << moved.get_value_for_print() << std::endl;

    std::cout << "\n2. АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ:\n";
    std::cout << "---------------------------\n";
    
    Eleven a1("123");
    Eleven b1("456");
    std::cout << "123 + 456 = " << a1.add(b1).get_value_for_print() << std::endl;
    
    Eleven a2("A");
    Eleven b2("1");
    std::cout << "A + 1 = " << a2.add(b2).get_value_for_print() << std::endl;
    
    Eleven a3("AA");
    Eleven b3("11");
    std::cout << "AA + 11 = " << a3.add(b3).get_value_for_print() << std::endl;
    
    Eleven c1("579");
    Eleven d1("123");
    std::cout << "579 - 123 = " << c1.substraction(d1).get_value_for_print() << std::endl;
    
    Eleven c2("100");
    Eleven d2("1");
    std::cout << "100 - 1 = " << c2.substraction(d2).get_value_for_print() << std::endl;
    
    std::cout << "987 - A23 = ";
    try {
        Eleven e("987");
        Eleven f("A23");
        std::cout << e.substraction(f).get_value_for_print() << std::endl;
    } catch (const std::underflow_error& e) {
        std::cout << "Ошибка! " << e.what();
    }
    
    Eleven zero("0");
    Eleven num("A57");
    std::cout << "A57 + 0 = " << num.add(zero).get_value_for_print() << std::endl;
    std::cout << "A57 - 0 = " << num.substraction(zero).get_value_for_print() << std::endl;

    std::cout << "\n3. ОПЕРАЦИИ СРАВНЕНИЯ:\n";
    std::cout << "---------------------\n";
    
    Eleven x1("123");
    Eleven y1("123");
    std::cout << "123 == 123: " << (x1.equal(y1) ? "true" : "false") << std::endl;
    std::cout << "123 > 123: " << (x1.more(y1) ? "true" : "false") << std::endl;
    std::cout << "123 < 123: " << (x1.less(y1) ? "true" : "false") << std::endl;
    
    Eleven x2("123");
    Eleven y2("124");
    std::cout << "123 == 124: " << (x2.equal(y2) ? "true" : "false") << std::endl;
    std::cout << "123 > 124: " << (x2.more(y2) ? "true" : "false") << std::endl;
    std::cout << "123 < 124: " << (x2.less(y2) ? "true" : "false") << std::endl;
    
    Eleven x3("1000");
    Eleven y3("AAA");
    std::cout << "1000 == AAA: " << (x3.equal(y3) ? "true" : "false") << std::endl;
    std::cout << "1000 > AAA: " << (x3.more(y3) ? "true" : "false") << std::endl;
    std::cout << "1000 < AAA: " << (x3.less(y3) ? "true" : "false") << std::endl;
    
    Eleven x4("1");
    Eleven y4("0");
    std::cout << "1 == 0: " << (x4.equal(y4) ? "true" : "false") << std::endl;
    std::cout << "1 > 0: " << (x4.more(y4) ? "true" : "false") << std::endl;
    std::cout << "1 < 0: " << (x4.less(y4) ? "true" : "false") << std::endl;

    std::cout << "\n4. ДОПОЛНИТЕЛЬНЫЕ ВОЗМОЖНОСТИ:\n";
    std::cout << "----------------------------\n";
    
    std::cout << "'0' является нулем: " << (zero.isNull() ? "true" : "false") << std::endl;
    std::cout << "'A57' является нулем: " << (num.isNull() ? "true" : "false") << std::endl;
    
    Eleven p("12");
    Eleven q("34");
    Eleven r("11");
    std::cout << "(12 + 34) - 11 = " << p.add(q).substraction(r).get_value_for_print() << std::endl;
    
    Eleven m("A5");
    Eleven n("37");
    std::cout << "A5 + 37 = " << m.add(n).get_value_for_print() << std::endl;
    std::cout << "37 + A5 = " << n.add(m).get_value_for_print() << std::endl;
    std::cout << "Сложение коммутативно: " << (m.add(n).equal(n.add(m)) ? "true" : "false") << std::endl;

    std::cout << "\nДемонстрация завершена!\n";
    
    return 0;
}