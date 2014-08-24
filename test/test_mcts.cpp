#include <gtest/gtest.h>
#include "mcts.h"

TEST(MonteCarloTreeSearch, Check)
{
   EXPECT_NO_THROW(MCTS::check(true, "True should not throw an exception."));
   EXPECT_ANY_THROW(MCTS::check(false, "False should throw an exception."));
}

TEST(MonteCarloTreeSearch, AssertionFailed)
{
   EXPECT_THROW(MCTS::assertion_failed("AssertionFailedTest", "test_mcts.cpp", 12), std::runtime_error);
}
