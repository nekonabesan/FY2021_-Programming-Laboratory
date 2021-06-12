// テストケース記述ファイル
#include "gtest/gtest.h" // googleTestを使用するおまじないはこれだけでOK
// テスト対象関数を呼び出せるようにするのだが
// extern "C"がないとCと解釈されない、意外とハマりがち。
extern "C" {
    #include "../pl01_02_target.h"
}

// fixtureNameはテストケース群をまとめるグループ名と考えればよい、任意の文字列
// それ以外のclass～testing::Testまではおまじないと考える
class fixtureName : public ::testing::Test {
protected:
    // fixtureNameでグループ化されたテストケースはそれぞれのテストケース実行前に
    // この関数を呼ぶ。共通の初期化処理を入れておくとテストコードがすっきりする
    virtual void SetUp(){
    }
    // SetUpと同様にテストケース実行後に呼ばれる関数。共通後始末を記述する。
    virtual void TearDown(){
    }
};

// 成功するテストケース。細かい説明はGoogleTestのマニュアルを見てね。
// char mystrlen(char s[]);
TEST_F(fixtureName, calc_bmi_01)
{
    struct person *t = NULL;
    unsigned int bmi = 0;
    const char *path = "../../data/data01_01.csv";
    t = init_data(path);
    t = head_person(t);
    // Case01    
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case02
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case03
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case04
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case05
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case06
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case07
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case08
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case09
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case10
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case11
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    // メモリ解放
    EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, calc_bmi_02)
{
    struct person *t = NULL;
    unsigned int bmi = 0;
    const char *path = "../../data/data01_02.csv";
    t = init_data(path);
    t = head_person(t);
    // Case01    
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, UNDER_WEIGHT);
    t = t->next;
    // Case02
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, UNDER_WEIGHT);
    t = t->next;
    // Case03
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case04
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, STD_WEIGHT);
    t = t->next;
    // Case05
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, OBESITY_WEIGHT);
    t = t->next;
    // Case06
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, OBESITY_WEIGHT);
    t = t->next;
    // Case07
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, HEGH_OBESITY_WEIGHT);
    t = t->next;
    // Case08
    bmi = calc_bmi(t->length, t->weight);
    EXPECT_EQ(bmi, HEGH_OBESITY_WEIGHT);
    // メモリ解放
    EXPECT_TRUE(del_person_array(head_person(t)));
}