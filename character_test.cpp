#include <gtest/gtest.h>

#define protected public
#define private public
#include "Character.h"
#undef private
#undef protected

TEST(DISABLED_Placeholder, Character) {
    EXPECT_TRUE(false);
}
