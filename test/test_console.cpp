#include <gtest/gtest.h>
#include "console.h"
#include <locale.h>

TEST(Console, NormalString)
{
   setlocale(LC_ALL, "");
   EXPECT_EQ("string", fixed_width_string("string", 6, left_side));
   EXPECT_EQ("string   ", fixed_width_string("string", 9, left_side));
   EXPECT_EQ("   string", fixed_width_string("string", 9, right_side));
   EXPECT_EQ("stri", fixed_width_string("string", 4, left_side));
   EXPECT_EQ("ring", fixed_width_string("string", 4, right_side));
}

TEST(Console, StringWithMultibyte)
{
   setlocale(LC_ALL, "");
   EXPECT_EQ("10♥", fixed_width_string("10♥", 3, left_side));
   EXPECT_EQ("10♥  ", fixed_width_string("10♥", 5, left_side));
   EXPECT_EQ("  10♥", fixed_width_string("10♥", 5, right_side));
   EXPECT_EQ("10", fixed_width_string("10♥", 2, left_side));
   EXPECT_EQ("0♥", fixed_width_string("10♥", 2, right_side));
}
