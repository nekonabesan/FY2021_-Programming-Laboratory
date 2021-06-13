// テストケース記述ファイル
#include "gtest/gtest.h" // googleTestを使用するおまじないはこれだけでOK
// テスト対象関数を呼び出せるようにするのだが
// extern "C"がないとCと解釈されない、意外とハマりがち。
extern "C" {
  #include "../pl01_01_target.h"
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
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
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
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, c_sort01)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  t = init_data(path);
  t = m_sort(t, CODE_LENGTH);
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
  EXPECT_NEAR(t->weight, 56.0, 0.0);
  // Case05
  t = t->next;
  EXPECT_NEAR(t->length, 168.0, 0.0);
  EXPECT_NEAR(t->weight, 60.0, 0.0);
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
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, c_sort02)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  t = init_data(path);
  t = m_sort(t, CODE_WEIGHT);
  // Case01
  EXPECT_NEAR(t->length, 162.0, 0.0);
  EXPECT_NEAR(t->weight, 55.0, 0.0);
  // Case02
  t = t->next;
  EXPECT_NEAR(t->length, 168.0, 0.0);
  EXPECT_NEAR(t->weight, 56.0, 0.0);
  // Case03
  t = t->next;
  EXPECT_NEAR(t->length, 166.0, 0.0);
  EXPECT_NEAR(t->weight, 57.0, 0.0);
  // Case04
  t = t->next;
  EXPECT_NEAR(t->length, 159.0, 0.0);
  EXPECT_NEAR(t->weight, 60.0, 0.0);
  // Case05
  t = t->next;
  EXPECT_NEAR(t->length, 168.0, 0.0);
  EXPECT_NEAR(t->weight, 60.0, 0.0);
  // Case06
  t = t->next;
  EXPECT_NEAR(t->length, 175.0, 0.0);
  EXPECT_NEAR(t->weight, 61.0, 0.0);
  // Case07
  t = t->next;
  EXPECT_NEAR(t->length, 179.0, 0.0);
  EXPECT_NEAR(t->weight, 62.0, 0.0);
  // Case08
  t = t->next;
  EXPECT_NEAR(t->length, 171.0, 0.0);
  EXPECT_NEAR(t->weight, 65.0, 0.0);
  // Case09
  t = t->next;
  EXPECT_NEAR(t->length, 176.0, 0.0);
  EXPECT_NEAR(t->weight, 66.0, 0.0);
  // Case10
  t = t->next;
  EXPECT_NEAR(t->length, 182.0, 0.0);
  EXPECT_NEAR(t->weight, 69.0, 0.0);
  // Case11
  t = t->next;
  EXPECT_NEAR(t->length, 174.0, 0.0);
  EXPECT_NEAR(t->weight, 72.0, 0.0);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, max_min_parson_01)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  t = init_data(path);
  // case 01 身長の最大値をテスト
  t = head_person(t);
  t = max_min_parson(t, CODE_MAX, CODE_LENGTH);
  EXPECT_NEAR(t->length, 182.0, 0.0);
  // case 02 身長の最小値をテスト
  t = head_person(t);
  t = max_min_parson(t, CODE_MIN, CODE_LENGTH);
  EXPECT_NEAR(t->length, 159.0, 0.0);
  // case 03 体重の最大値をテスト
  t = head_person(t);
  t = max_min_parson(t, CODE_MAX, CODE_WEIGHT);
  EXPECT_NEAR(t->weight, 72.0, 0.0);
  // case 04 体重の最小値をテスト
  t = head_person(t);
  t = max_min_parson(t, CODE_MIN, CODE_WEIGHT);
  EXPECT_NEAR(t->weight, 55.0, 0.0);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, avg_parson_01)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  double avg = 0.0;
  t = init_data(path);
  // case 01 身長の平均値をテスト
  t = head_person(t);
  avg = avg_parson(t, CODE_LENGTH);
  EXPECT_NEAR(avg, 170.090, 0.01);
  // case 02 体重の平均値をテスト
  t = head_person(t);
  avg = avg_parson(t, CODE_WEIGHT);
  EXPECT_NEAR(avg, 62.090, 0.01);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, med_parson_01)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  double med = 0.0;
  t = init_data(path);
  // case 01 身長の中央値をテスト
  t = head_person(t);
  med = med_parson(t, CODE_LENGTH);
  EXPECT_NEAR(med, 171.0, 0.0);
  // case 02 体重の中央値をテスト
  t = head_person(t);
  med = med_parson(t, CODE_WEIGHT);
  EXPECT_NEAR(med, 61.0, 0.0);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, std_dev_parson_01)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  double std_dev = 0.0;
  t = init_data(path);
  // case 01 身長の標準偏差をテスト
  t = head_person(t);
  std_dev = std_dev_parson(t, CODE_LENGTH);
  EXPECT_NEAR(std_dev, 6.761583266, 0.1);
  // case 02 体重の標準偏差をテスト
  t = head_person(t);
  std_dev = std_dev_parson(t, CODE_WEIGHT);
  EXPECT_NEAR(std_dev, 5.160242162, 0.1);
  // メモリ解放
  EXPECT_TRUE(del_person_array(head_person(t)));
}

TEST_F(fixtureName, correlation_coefficient_parson_01)
{
  struct person *t = NULL;
  const char *path = "../../data/data01_01.csv";
  double correlation_coefficient = 0.0;
  t = init_data(path);
  // case 01 相関係数をテスト
  correlation_coefficient = correlation_coefficient_parson(t);
  EXPECT_NEAR(correlation_coefficient, 0.675057872, 0.1);
}