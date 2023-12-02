#include <gtest/gtest.h>
#include <gmock/gmock.h>

// 一个简单的示例类
class Example {
public:
    virtual int getValue() const {
        return 42;
    }
};

// 使用 Google Mock 创建一个模拟类
class MockExample : public Example {
public:
    MOCK_CONST_METHOD0(getValue, int());
};

// 编写一个基本测试用例
TEST(ExampleTest, Returns42) {
    MockExample mock;
    EXPECT_CALL(mock, getValue()).WillOnce(testing::Return(42));

    ASSERT_EQ(mock.getValue(), 42);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
