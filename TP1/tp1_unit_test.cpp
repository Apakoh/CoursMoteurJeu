#include <gtest/gtest.h>
#include <iostream>


TEST(module_name, test_name) a
{
    std::cout << "Test" << std::endl;
    // Google Test will also provide macros for assertions.
    ASSERT_EQ(1+1, 2);
}

int main()
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
