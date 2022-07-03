#include <gtest/gtest.h>
#include <windows.h>
#include <xorstr/xorstr.hpp>
#define XORSTR(x) xorstr_(x)
#include <wow64pp.hpp>

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

TEST(WOW64PP, NtReadVirtualMemory)
{
    auto ntdll = wow64pp::module_handle ("ntdll.dll");
    std::error_code ec;
    auto            fn = wow64pp::import (ntdll, "NtReadVirtualMemory", ec);
    EXPECT_TRUE(!ec);
    auto h = wow64pp::detail::self_handle ();

    volatile int  i = 6;
    volatile int  b = 20;
    std::uint64_t read;

    for (int idx = 0; idx < 20; ++idx) {
        read = 0;
        i    = rand ();
        b    = rand ();

        for (int j = 0; j < 200; ++j) {
            auto ret = wow64pp::call_function (fn, h, &i, &b, 4, &read);
            EXPECT_TRUE (ret >= 0);
            EXPECT_TRUE (i == b);
            EXPECT_TRUE (read == 4);
        }
    }

}
int main(int argc, char** argv)
{
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}