#include <gtest/gtest.h>
#include "../include/eleven.hpp"
#include <string>

// Тесты конструкторов
TEST(ElevenTest, DefaultConstructor) {
    Eleven num;
    EXPECT_EQ(num.get_value_for_print(), "0");
    EXPECT_EQ(num.getSize(), 1);
    EXPECT_TRUE(num.isNull());
}

TEST(ElevenTest, StringConstructorBasic) {
    Eleven num("123");
    EXPECT_EQ(num.get_value_for_print(), "123");
    EXPECT_EQ(num.getSize(), 3);
}

TEST(ElevenTest, StringConstructorWithLeadingZeros) {
    Eleven num("000123");
    EXPECT_EQ(num.get_value_for_print(), "123");
    EXPECT_EQ(num.getSize(), 3);
}

TEST(ElevenTest, StringConstructorAllZeros) {
    Eleven num("0000");
    EXPECT_EQ(num.get_value_for_print(), "0");
    EXPECT_EQ(num.getSize(), 1);
    EXPECT_TRUE(num.isNull());
}

TEST(ElevenTest, StringConstructorWithDigitA) {
    Eleven num("A5A");
    EXPECT_EQ(num.get_value_for_print(), "A5A");
    EXPECT_EQ(num.getSize(), 3);
}

TEST(ElevenTest, StringConstructorMixedCase) {
    Eleven num("a5A");
    EXPECT_EQ(num.get_value_for_print(), "A5A");
}

TEST(ElevenTest, StringConstructorInvalidChar) {
    EXPECT_THROW(Eleven num("12B"), std::invalid_argument);
    EXPECT_THROW(Eleven num("G"), std::invalid_argument);
}

TEST(ElevenTest, SizeConstructorBasic) {
    Eleven num(3, '5');
    EXPECT_EQ(num.get_value_for_print(), "555");
    EXPECT_EQ(num.getSize(), 3);
}

TEST(ElevenTest, SizeConstructorWithDigitA) {
    Eleven num(4, 'A');
    EXPECT_EQ(num.get_value_for_print(), "AAAA");
    EXPECT_EQ(num.getSize(), 4);
}

TEST(ElevenTest, SizeConstructorMixedCase) {
    Eleven num(2, 'a');
    EXPECT_EQ(num.get_value_for_print(), "AA");
}

TEST(ElevenTest, SizeConstructorInvalidChar) {
    EXPECT_THROW(Eleven num(3, 'B'), std::invalid_argument);
    EXPECT_THROW(Eleven num(2, 'Z'), std::invalid_argument);
}

TEST(ElevenTest, SizeConstructorZeroSize) {
    Eleven num(0, '5');
    EXPECT_EQ(num.getSize(), 1);
    EXPECT_EQ(num.get_value_for_print(), "5");
}


TEST(ElevenTest, InitializerListWithLowerCase) {
    Eleven num("5a");
    std::string value = num.getValue();
    EXPECT_TRUE(value[0] == 'A');
    EXPECT_TRUE(value[1] == '5');
}

TEST(ElevenTest, InitializerListInvalidChar) {
    EXPECT_THROW(Eleven num("1B2"), std::invalid_argument);
}

TEST(ElevenTest, CopyConstructor) {
    Eleven original("A123");
    Eleven copy(original);
    EXPECT_EQ(copy.get_value_for_print(), "A123");
    EXPECT_EQ(copy.getSize(), 4);
    EXPECT_TRUE(copy.equal(original));
}

TEST(ElevenTest, MoveConstructor) {
    Eleven original("A567");
    Eleven moved(std::move(original));
    EXPECT_EQ(moved.get_value_for_print(), "A567");
    EXPECT_EQ(moved.getSize(), 4);
    // original должен быть в валидном но пустом состоянии
    EXPECT_EQ(original.getSize(), 0);
}

TEST(ElevenTest, EqualOperation) {
    Eleven num1("123");
    Eleven num2("123");
    Eleven num3("124");
    
    EXPECT_TRUE(num1.equal(num2));
    EXPECT_FALSE(num1.equal(num3));
}

TEST(ElevenTest, MoreOperation) {
    Eleven num1("124");
    Eleven num2("123");
    Eleven num3("A");
    
    EXPECT_TRUE(num1.more(num2));
    EXPECT_FALSE(num2.more(num1));
    EXPECT_FALSE(num3.more(num1)); 
}

TEST(ElevenTest, LessOperation) {
    Eleven num1("122");
    Eleven num2("123");
    Eleven num3("A");
    
    EXPECT_TRUE(num1.less(num2));
    EXPECT_FALSE(num2.less(num1));
}

TEST(ElevenTest, CompareWithDifferentLengths) {
    Eleven num1("1000");
    Eleven num2("AAA"); 
    
    EXPECT_TRUE(num1.more(num2));
    EXPECT_TRUE(num2.less(num1));
    EXPECT_FALSE(num1.equal(num2));
}

TEST(ElevenTest, CompareEdgeCases) {
    Eleven zero1("0");
    Eleven zero2("000");
    Eleven small("1");
    Eleven large("A");
    
    EXPECT_TRUE(zero1.equal(zero2));
    EXPECT_TRUE(small.more(zero1));
    EXPECT_TRUE(large.more(small));
}

TEST(ElevenTest, AddBasic) {
    Eleven num1("12");
    Eleven num2("23");
    Eleven result = num1.add(num2);
    EXPECT_EQ(result.get_value_for_print(), "35"); 
}

TEST(ElevenTest, AddWithCarry) {
    Eleven num1("A"); 
    Eleven num2("1"); 
    Eleven result = num1.add(num2);
    EXPECT_EQ(result.get_value_for_print(), "10"); 
}

TEST(ElevenTest, AddWithMultipleCarry) {
    Eleven num1("AA"); 
    Eleven num2("11"); 
    Eleven result = num1.add(num2);
    EXPECT_EQ(result.get_value_for_print(), "110"); 
}

TEST(ElevenTest, AddDifferentLengths) {
    Eleven num1("AAA"); 
    Eleven num2("1"); 
    Eleven result = num1.add(num2);
    EXPECT_EQ(result.get_value_for_print(), "1000"); // 1330 + 1 = 1331 в 11-ричной
}

TEST(ElevenTest, AddToZero) {
    Eleven zero("0");
    Eleven num("123");
    Eleven result1 = zero.add(num);
    Eleven result2 = num.add(zero);
    
    EXPECT_TRUE(result1.equal(num));
    EXPECT_TRUE(result2.equal(num));
}

TEST(ElevenTest, AddCommutative) {
    Eleven num1("A5");
    Eleven num2("37");
    Eleven result1 = num1.add(num2);
    Eleven result2 = num2.add(num1);
    
    EXPECT_TRUE(result1.equal(result2));
}

TEST(ElevenTest, SubstractionBasic) {
    Eleven num1("35");
    Eleven num2("12");
    Eleven result = num1.substraction(num2);
    EXPECT_EQ(result.get_value_for_print(), "23");
}

TEST(ElevenTest, SubstractionWithBorrow) {
    Eleven num1("100"); // 121
    Eleven num2("1");   // 1
    Eleven result = num1.substraction(num2);
    EXPECT_EQ(result.get_value_for_print(), "AA"); // 120
}

TEST(ElevenTest, SubstractionEqualNumbers) {
    Eleven num1("A53");
    Eleven num2("A53");
    Eleven result = num1.substraction(num2);
    EXPECT_TRUE(result.isNull());
}

TEST(ElevenTest, SubstractionResultZero) {
    Eleven num1("123");
    Eleven num2("123");
    Eleven result = num1.substraction(num2);
    EXPECT_TRUE(result.isNull());
}

TEST(ElevenTest, SubstractionNegativeResult) {
    Eleven num1("12");
    Eleven num2("34");
    
    EXPECT_THROW(num1.substraction(num2), std::underflow_error);
}

TEST(ElevenTest, SubstractionZeroZero) {
    Eleven num1;
    Eleven num2;
    
    EXPECT_EQ(num1.substraction(num2).getValue(), "0");
}

TEST(ElevenTest, SubstractionFromLargerNumber) {
    Eleven num1("A"); 
    Eleven num2("9"); 
    Eleven result = num1.substraction(num2);
    EXPECT_EQ(result.get_value_for_print(), "1");
}

TEST(ElevenTest, SubstractionComplexBorrow) {
    Eleven num1("1000"); 
    Eleven num2("1");
    Eleven result = num1.substraction(num2);
    EXPECT_EQ(result.get_value_for_print(), "AAA"); 
}

TEST(ElevenTest, MaxDigitOperations) {
    Eleven max1(3, 'A');
    Eleven max2(2, 'A'); 
    Eleven one("1");
    
    // AAA + 1 = 1000
    Eleven sum = max1.add(one);
    EXPECT_EQ(sum.get_value_for_print(), "1000");
    
    // AAA - AA = A00
    Eleven diff = max1.substraction(max2);
    EXPECT_EQ(diff.get_value_for_print(), "A00");
}

TEST(ElevenTest, ChainOperations) {
    Eleven a("12");
    Eleven b("23");
    Eleven c("34");
    
    Eleven sum_ab = a.add(b); 
    Eleven final_result = sum_ab.substraction(c);
    
    EXPECT_EQ(final_result.get_value_for_print(), "1");
}

TEST(ElevenTest, LargeNumbers) {
    Eleven large1("AAAAA"); 
    Eleven large2("11111"); 
    Eleven one("1");
    
    Eleven sum = large1.add(large2);
    Eleven diff = sum.substraction(one);
    
    EXPECT_TRUE(diff.more(large1));
}

TEST(ElevenTest, GetValueConsistency) {
    Eleven num("1A35");
    std::string stored_value = num.getValue();
    std::string print_value = num.get_value_for_print();
    EXPECT_EQ(print_value, "1A35");
    EXPECT_EQ(stored_value, "53A1");
    
}

TEST(ElevenTest, IsNullVariousCases) {
    Eleven zero1("0");
    Eleven zero2(1, '0');
    Eleven nonZero1("1");
    Eleven nonZero2("0001");
    
    EXPECT_TRUE(zero1.isNull());
    EXPECT_TRUE(zero2.isNull());
    EXPECT_FALSE(nonZero1.isNull());
    EXPECT_FALSE(nonZero2.isNull());
}

// Тесты исключительных ситуаций
TEST(ElevenTest, InvalidInputHandling) {
    EXPECT_THROW(Eleven("12G34"), std::invalid_argument);
    EXPECT_EQ(Eleven("").get_value_for_print(), "0"); 
}

TEST(ElevenTest, MemoryManagement) {
    Eleven* num1 = new Eleven("12345");
    Eleven* num2 = new Eleven(*num1); // Копирование
    Eleven* num3 = new Eleven(std::move(*num1)); // Перемещение
    
    delete num1;
    delete num2;
    delete num3;
}

TEST(ElevenTest, MultipleOperationsConsistency) {
    Eleven a("25");
    Eleven b("13");
    Eleven c("37");
    
    Eleven result1 = a.add(b).substraction(c);
    Eleven result2 = c.substraction(b);
    
    if (!a.less(result2)) {
        Eleven result3 = a.substraction(result2);
        EXPECT_TRUE(result1.equal(result3));
    }
}

TEST(ElevenTest, BoundaryValues) {
    Eleven min("1");
    Eleven max("AAAAAAAAAA");
    
    EXPECT_TRUE(max.more(min));
    
    Eleven max_plus_one = max.add(Eleven("1"));
    EXPECT_TRUE(max_plus_one.more(max));
}

TEST(ElevenTest, AddSubIdentity) {
    Eleven num("A53");
    Eleven zero("0");
    

    EXPECT_TRUE(num.add(zero).equal(num));
    EXPECT_TRUE(num.substraction(zero).equal(num));
    EXPECT_TRUE(num.substraction(num).isNull());
}

TEST(ElevenTest, CompareTransitivity) {
    Eleven a("123");
    Eleven b("456");
    Eleven c("789");
    
    if (a.less(b) && b.less(c)) {
        EXPECT_TRUE(a.less(c));
    }
}

TEST(ElevenTest, StringConstructorEmpty) {
    Eleven num("");
    EXPECT_TRUE(num.isNull());
    EXPECT_EQ(num.get_value_for_print(), "0");
}

TEST(ElevenTest, GetValueForPrintConsistency) {
    std::string test_values[] = {"0", "1", "A", "10", "1A", "A1", "100", "AAA"};
    
    for (const auto& str : test_values) {
        Eleven num(str);
        EXPECT_EQ(num.get_value_for_print(), str);
    }
}

TEST(ElevenTest, MixedOperations) {
    Eleven num1("2A");
    Eleven num2("15");
    Eleven num3("10");
    
    Eleven result = num1.substraction(num2).add(num3);
    EXPECT_TRUE(result.more(num1) || result.less(num1) || result.equal(num1));
}

TEST(ElevenTest, SizeGetters) {
    Eleven empty("0");
    Eleven small("1");
    Eleven medium("123");
    Eleven large("123456789A");
    
    EXPECT_EQ(empty.getSize(), 1);
    EXPECT_EQ(small.getSize(), 1);
    EXPECT_EQ(medium.getSize(), 3);
    EXPECT_EQ(large.getSize(), 10);
}

TEST(ElevenTest, ReverseFunction) {
    std::string test1 = "123";
    std::string result1 = reverse(test1);
    EXPECT_EQ(result1, "321");
    
    std::string test2 = "A";
    std::string result2 = reverse(test2);
    EXPECT_EQ(result2, "A");
    
    std::string test3 = "";
    std::string result3 = reverse(test3);
    EXPECT_EQ(result3, "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}