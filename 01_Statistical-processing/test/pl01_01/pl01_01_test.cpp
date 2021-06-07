#define RMAX 1000
#define TRUE 1
#define FALSE 0
#define CODE_LENGTH 1
#define CODE_WEIGHT 2

struct person {
  unsigned int seq;
  double length;
  double weight;
  struct person *prev;
  struct person *next;
};

// テストケース記述ファイル
#include "gtest/gtest.h" // googleTestを使用するおまじないはこれだけでOK
// テスト対象関数を呼び出せるようにするのだが
// extern "C"がないとCと解釈されない、意外とハマりがち。
extern "C" {
  #include "../pl01_target.h"
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
TEST_F(fixtureName, init_data)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  t = init_data(path);
  // Case01
  EXPECT_NEAR(t->length, 168.0, 0.0);
  EXPECT_NEAR(t->weight, 60.0, 0.0);
  // Case02
  t = t->next;
  EXPECT_NEAR(t->length, 162.0, 0.0);
  EXPECT_NEAR(t->weight, 55.0, 0.0);
  // Case03
  t = t->next;
  EXPECT_NEAR(t->length, 171.0, 0.0);
  EXPECT_NEAR(t->weight, 65.0, 0.0);
  // Case04
  t = t->next;
  EXPECT_NEAR(t->length, 159.0, 0.0);
  EXPECT_NEAR(t->weight, 60.0, 0.0);
  // Case05
  t = t->next;
  EXPECT_NEAR(t->length, 174.0, 0.0);
  EXPECT_NEAR(t->weight, 72.0, 0.0);
  // Case06
  t = t->next;
  EXPECT_NEAR(t->length, 166.0, 0.0);
  EXPECT_NEAR(t->weight, 57.0, 0.0);
  // Case07
  t = t->next;
  EXPECT_NEAR(t->length, 175.0, 0.0);
  EXPECT_NEAR(t->weight, 61.0, 0.0);
  // Case08
  t = t->next;
  EXPECT_NEAR(t->length, 176.0, 0.0);
  EXPECT_NEAR(t->weight, 66.0, 0.0);
  // Case09
  t = t->next;
  EXPECT_NEAR(t->length, 168.0, 0.0);
  EXPECT_NEAR(t->weight, 56.0, 0.0);
  // Case10
  t = t->next;
  EXPECT_NEAR(t->length, 182.0, 0.0);
  EXPECT_NEAR(t->weight, 69.0, 0.0);
  // Case11
  t = t->next;
  EXPECT_NEAR(t->length, 179.0, 0.0);
  EXPECT_NEAR(t->weight, 62.0, 0.0);


  EXPECT_TRUE(del_person_array(t));
}

TEST_F(fixtureName, b_sort01)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  t = init_data(path);
  t = b_sort(t, CODE_LENGTH);
  // Case01
  EXPECT_NEAR(t->length, 159.0, 0.0);
  EXPECT_NEAR(t->weight, 60.0, 0.0);
  // Case02
  t = t->next;
  EXPECT_NEAR(t->length, 162.0, 0.0);
  EXPECT_NEAR(t->weight, 55.0, 0.0);
  // Case03
  t = t->next;
  EXPECT_NEAR(t->length, 166.0, 0.0);
  EXPECT_NEAR(t->weight, 57.0, 0.0);
  // Case04
  t = t->next;
  EXPECT_NEAR(t->length, 168.0, 0.0);
  EXPECT_NEAR(t->weight, 60.0, 0.0);
  // Case05
  t = t->next;
  EXPECT_NEAR(t->length, 168.0, 0.0);
  EXPECT_NEAR(t->weight, 56.0, 0.0);
  // Case06
  t = t->next;
  EXPECT_NEAR(t->length, 171.0, 0.0);
  EXPECT_NEAR(t->weight, 65.0, 0.0);
  // Case07
  t = t->next;
  EXPECT_NEAR(t->length, 174.0, 0.0);
  EXPECT_NEAR(t->weight, 72.0, 0.0);
  // Case08
  t = t->next;
  EXPECT_NEAR(t->length, 175.0, 0.0);
  EXPECT_NEAR(t->weight, 61.0, 0.0);
  // Case09
  t = t->next;
  EXPECT_NEAR(t->length, 176.0, 0.0);
  EXPECT_NEAR(t->weight, 66.0, 0.0);
  // Case10
  t = t->next;
  EXPECT_NEAR(t->length, 179.0, 0.0);
  EXPECT_NEAR(t->weight, 62.0, 0.0);
  // Case11
  t = t->next;
  EXPECT_NEAR(t->length, 182.0, 0.0);
  EXPECT_NEAR(t->weight, 69.0, 0.0);
}
