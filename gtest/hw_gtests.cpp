// ------------------------- Tests File - test.cpp -------------------------- //
// This file is for writing your own user tests. Be sure to include your *.h
// files to be able to access the functions that you wrote for unit testing.
// An example has been provided, but more documentation is available here:
// https://github.com/google/googletest/blob/main/docs/primer.md
// -------------------------------------------------------------------------- //

// future plan : templates -> empty, insert, find, remove same bodies

// make test
#include "gtest/gtest.h"
#include "../src/unordered_list.h"

class UAL : 
    public::testing::Test {

protected:
    UnorderedArrayList list;
    void SetUp() override{}
    void TearDown() override{}
};

class ULL : 
    public::testing::Test {

protected:
    UnorderedLinkedList list;
    void SetUp() override{}
    void TearDown() override{}
};


// empty

TEST_F(UAL, empty_list) {
    EXPECT_TRUE(list.is_empty());
    EXPECT_FALSE(list.is_full());
}
TEST_F(ULL, empty_list) {
    EXPECT_TRUE(list.is_empty());
    EXPECT_FALSE(list.is_full());
}

// insert
TEST_F(UAL, insert) {
    list.insert("cane");
    EXPECT_FALSE(list.is_empty());
    EXPECT_TRUE(list.find("cane"));
}
TEST_F(ULL, insert) {
    list.insert("perfume");
    EXPECT_FALSE(list.is_empty());
    EXPECT_TRUE(list.find("perfume"));
}

// find
TEST_F(UAL, find) {
    list.insert("ohio");
    list.insert("sigma");

    EXPECT_TRUE(list.find("ohio"));
    EXPECT_TRUE(list.find("sigma"));
    
    EXPECT_FALSE(list.find("rizz"));
}
TEST_F(ULL, find) {
    list.insert("ohio");
    list.insert("sigma");

    EXPECT_TRUE(list.find("ohio"));
    EXPECT_TRUE(list.find("sigma"));
    
    EXPECT_FALSE(list.find("rizz"));
}

// remove
TEST_F(UAL, remove) {
    list.insert("coke");
    list.insert("banana");

    list.remove("banana");
    EXPECT_FALSE(list.find("banana"));
    EXPECT_TRUE(list.find("coke"));

    EXPECT_FALSE(list.is_empty());
    list.remove("coke");
    EXPECT_TRUE(list.is_empty());
}
TEST_F(ULL, remove) {
    list.insert("coke");
    list.insert("banana");

    list.remove("banana");
    EXPECT_FALSE(list.find("banana"));
    EXPECT_TRUE(list.find("coke"));

    EXPECT_FALSE(list.is_empty());
    list.remove("coke");
    EXPECT_TRUE(list.is_empty());
}

TEST_F(UAL, remove_non_elem) {
    list.insert("apple");
    list.remove("banana"); // attempting to remove an element not in the list
    
    EXPECT_TRUE(list.find("apple"));
    EXPECT_FALSE(list.find("banana"));
    EXPECT_FALSE(list.is_empty()); 
}

TEST_F(ULL, remove_non_elem) {
    list.insert("apple");
    list.remove("banana");

    EXPECT_TRUE(list.find("apple"));
    EXPECT_FALSE(list.find("banana"));
    EXPECT_FALSE(list.is_empty());
}

TEST_F(UAL, double_cap) {
    int cap = NWORDS;

    // fill array with // word0...word[NWORDS-1]
    for(int i = 0; i < cap; ++i) { list.insert("word" + std::to_string(i)); } 
    EXPECT_TRUE(list.is_full());

    // double_cap triggers
    list.insert("new_unique_word");
    EXPECT_FALSE(list.is_full());
    EXPECT_TRUE(list.find("new_unique_word"));
}

TEST_F(ULL, MultipleInsertionsAndRemovals) {
    list.insert("asian");
    list.insert("bob");
    list.insert("clock");
    list.insert("dairy");

    // a b c d e 
    EXPECT_TRUE(list.find("clock"));
    list.remove("clock");
    // a b d e
    EXPECT_FALSE(list.find("clock"));
    EXPECT_TRUE(list.find("dairy"));
    list.remove("dairy");
    // a b e
    EXPECT_FALSE(list.find("dairy"));
    EXPECT_TRUE(list.find("asian"));
    EXPECT_TRUE(list.find("bob"));
}

// print
// capturestdout() example : 
// https://matrix.senecapolytechnic.ca/~smlee36/oop244/gtest.md


TEST_F(UAL, print){

    UnorderedArrayList ual;

    ual.insert("phone");
    ual.insert("mouse");

    testing::internal::CaptureStdout();
    std::cout << ual;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "phone\nmouse\n");
}
TEST_F(ULL, print){
    
    UnorderedLinkedList ull;
    ull.insert("milk");
    ull.insert("eggs");

    testing::internal::CaptureStdout();
    std::cout << ull;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "eggs\nmilk\n"); // opposite order 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
