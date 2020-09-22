#include <gtest/gtest.h>
#include <iostream>

int Factorial (int x, int result = 1)
{
  if(x == 1)
  {
    return result;
  }
  else
  {
    return Factorial(x - 1, x * result);
  }
}

TEST(FactorialTest, Negative)
{
    //ASSERT_EQ(1+1, 2);
    EXPECT_EQ(1, Factorial(-5));
    EXPECT_EQ(1, Factorial(-1));
    EXPECT_EQ(Factorial(-10), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
