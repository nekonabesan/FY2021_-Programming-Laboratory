// テストケース記述ファイル
#include "gtest/gtest.h" // googleTestを使用するおまじないはこれだけでOK
// テスト対象関数を呼び出せるようにするのだが
// extern "C"がないとCと解釈されない、意外とハマりがち。
extern "C" {
  #include "../pl02_01_target.h"
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
TEST_F(fixtureName, calc_S1)
{
  struct person *t = NULL;
  const char *path = "../../02_Function-approximation/data/data02_01.csv";
  t = init_data(path);
  t = from_cm_to_m_for_length(t);
  // case 01
  EXPECT_NEAR(calc_S1(t), 106.3545455, 0.1);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, calc_S2)
{
  struct person *t = NULL;
  const char *path = "../../02_Function-approximation/data/data02_01.csv";
  t = init_data(path);
  t = from_cm_to_m_for_length(t);
  // case 01
  EXPECT_NEAR(calc_S2(t, CODE_LENGTH), 2.925563636, 0.1);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, calc_a)
{
  struct person *t = NULL;
  const char *path = "../../02_Function-approximation/data/data02_01.csv";
  t = init_data(path);
  t = from_cm_to_m_for_length(t);
  // case01
  EXPECT_NEAR(calc_a(t, CODE_LENGTH), 36.329586321776894, 0.5);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, calc_b)
{
  struct person *t = NULL;
  const char *path = "../../02_Function-approximation/data/data02_01.csv";
  t = init_data(path);
  t = from_cm_to_m_for_length(t);
  // case01
  EXPECT_NEAR(calc_b(t, CODE_LENGTH), 0.040174511151791575, 0.5);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}