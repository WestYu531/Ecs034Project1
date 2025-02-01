#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    // basic
    EXPECT_EQ(StringUtils::Slice("lukecombs", 0, 4), "luke");  // "lukecombs" -> "luke"
    EXPECT_EQ(StringUtils::Slice("lukecombs", 0, 10), "lukecombs");  // whole str

    // Negative
    EXPECT_EQ(StringUtils::Slice("lukecombs", -5, 9), "comb");  // -5 >> 5， "comb"
    EXPECT_EQ(StringUtils::Slice("lukecombs", -6, -4), "ke");  // -6 >> 4，-4 >> 6， "ke"

    // end == 0
    EXPECT_EQ(StringUtils::Slice("lukecombs", 6, 0), "ombs");  // 6 >> end "ombs"

    // over length
    EXPECT_EQ(StringUtils::Slice("lukecombs", -17, 20), "lukecombs");  // -17 >> 0，20>> 10，return whole str
    EXPECT_EQ(StringUtils::Slice("lukecombs", 20, 25), "");  // `start >= length`，return empty

    EXPECT_EQ(StringUtils::Slice("lukecombs", 7, 7), "");  // start == end，
    EXPECT_EQ(StringUtils::Slice("", 0, 5), "");
}

TEST(StringUtilsTest, Capitalize){
    // basic
    EXPECT_EQ(StringUtils::Capitalize("luke"), "Luke");
    EXPECT_EQ(StringUtils::Capitalize("LUKE"), "Luke");
    EXPECT_EQ(StringUtils::Capitalize("lUKE"), "Luke");
    EXPECT_EQ(StringUtils::Capitalize("Luke"), "Luke");

    // numbers
    EXPECT_EQ(StringUtils::Capitalize("123luke"), "123luke"); // beginning with numbers
    EXPECT_EQ(StringUtils::Capitalize("!luke"), "!luke"); // beginning with symbols
}

TEST(StringUtilsTest, Upper){
    EXPECT_EQ(StringUtils::Upper("luke"), "LUKE");
    EXPECT_EQ(StringUtils::Upper("Luke"), "LUKE");
    EXPECT_EQ(StringUtils::Upper("LUKE"), "LUKE");
    EXPECT_EQ(StringUtils::Upper("37743@&@*#"), "37743@&@*#");
}

TEST(StringUtilsTest, Lower){
    EXPECT_EQ(StringUtils::Lower("luke"), "luke");
    EXPECT_EQ(StringUtils::Lower("Luke"), "luke");
    EXPECT_EQ(StringUtils::Lower("LUKE"), "luke");
    EXPECT_EQ(StringUtils::Lower("37743@&@*#"), "37743@&@*#");
}

TEST(StringUtilsTest, LStrip){
    EXPECT_EQ(StringUtils::LStrip("   luke"), "luke");
    EXPECT_EQ(StringUtils::LStrip("luke"), "luke");  // no space
    EXPECT_EQ(StringUtils::LStrip("   "), "");  // all space
    EXPECT_EQ(StringUtils::LStrip(""), "");  // empty string
}

TEST(StringUtilsTest, RStrip){
    EXPECT_EQ(StringUtils::RStrip("luke   "), "luke");
    EXPECT_EQ(StringUtils::RStrip("luke"), "luke");  // no space
    EXPECT_EQ(StringUtils::RStrip("   "), "");  // all space
    EXPECT_EQ(StringUtils::RStrip(""), "");  // empty string
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip("   hello   "), "hello");
    EXPECT_EQ(StringUtils::Strip("hello"), "hello");  // no space
    EXPECT_EQ(StringUtils::Strip("   "), "");  // all space
    EXPECT_EQ(StringUtils::Strip(""), "");  // empty string
}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(StringUtils::Center("luke", 10, '*'), "***luke***");
    EXPECT_EQ(StringUtils::Center("h", 6, '-'), "--h---");
    EXPECT_EQ(StringUtils::Center("lukecombs", 4, '.'), "lukecombs");  // no change
    EXPECT_EQ(StringUtils::Center("", 6, '#'), "######");  // empty string
}

TEST(StringUtilsTest, LJust){
    EXPECT_EQ(StringUtils::LJust("luke", 10, '*'), "luke******");
    EXPECT_EQ(StringUtils::LJust("h", 6, '-'), "h-----");
    EXPECT_EQ(StringUtils::LJust("lukecombs", 4, '.'), "lukecombs");  // no change
    EXPECT_EQ(StringUtils::LJust("", 6, '#'), "######");  // empty string
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(StringUtils::RJust("luke", 10, '*'), "******luke");
    EXPECT_EQ(StringUtils::RJust("h", 6, '-'), "-----h");
    EXPECT_EQ(StringUtils::RJust("lukecombs", 4, '.'), "lukecombs");  // no change
    EXPECT_EQ(StringUtils::RJust("", 6, '#'), "######");  // empty string
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(StringUtils::Replace("lukecombs is a singer", "singer", "legend"), "lukecombs is a legend");
    EXPECT_EQ(StringUtils::Replace("better call saulgoodman", "better call", "trust"), "trust saulgoodman");
    EXPECT_EQ(StringUtils::Replace("lukecombs", "saul", "goodman"), "lukecombs");  // no fit
    EXPECT_EQ(StringUtils::Replace("aaa", "aa", "b"), "ba");
    EXPECT_EQ(StringUtils::Replace("", "a", "b"), "");  // empty
    EXPECT_EQ(StringUtils::Replace("saulgoodman", "", "lukecombs"), "saulgoodman");  // old is empty
}

TEST(StringUtilsTest, Split){
    EXPECT_EQ(StringUtils::Split("lukecombs is a singer", " "), 
              std::vector<std::string>({"lukecombs", "is", "a", "singer"}));

    EXPECT_EQ(StringUtils::Split("saulgoodman-better-call", "-"), 
              std::vector<std::string>({"saulgoodman", "better", "call"}));

    EXPECT_EQ(StringUtils::Split("no_separator_here", ","), 
              std::vector<std::string>({"no_separator_here"}));  // no sperators
}

TEST(StringUtilsTest, Join){
    EXPECT_EQ(StringUtils::Join(" ", {"lukecombs", "is", "a", "legend"}), "lukecombs is a legend");
    EXPECT_EQ(StringUtils::Join("-", {"saulgoodman", "better", "call"}), "saulgoodman-better-call");
    EXPECT_EQ(StringUtils::Join(",", {"saulgoodman"}), "saulgoodman");  // only one element
    EXPECT_EQ(StringUtils::Join(",", {}), "");  // empty vector
}

TEST(StringUtilsTest, ExpandTabs){
    TEST(StringUtilsTest, ExpandTabsTest) {
    EXPECT_EQ(StringUtils::ExpandTabs("lukecombs\tis\tawesome", 4), "lukecombs   is  awesome");
    EXPECT_EQ(StringUtils::ExpandTabs("saulgoodman\tbetter\tcall", 8), "saulgoodman        better  call");
    EXPECT_EQ(StringUtils::ExpandTabs("\tleadingtab", 4), "    leadingtab");
    EXPECT_EQ(StringUtils::ExpandTabs("no tabs here", 4), "no tabs here");
}
}

TEST(StringUtilsTest, EditDistance){
    TEST(StringUtilsTest, EditDistanceTest) {
    EXPECT_EQ(StringUtils::EditDistance("lukecombs", "luke", false), 5);
    EXPECT_EQ(StringUtils::EditDistance("saulgoodman", "SaulGoodMan", true), 0);
    EXPECT_EQ(StringUtils::EditDistance("kitten", "sitting", false), 3);
    EXPECT_EQ(StringUtils::EditDistance("", "", false), 0);
}
}
