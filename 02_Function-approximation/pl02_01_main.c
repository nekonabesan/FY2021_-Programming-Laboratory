#include "../modules/pl02_01_module.c"

//============================================================================//
// 課題(1)のmain関数
// @return bool 
//============================================================================//
bool main(void) {
    struct person *t = NULL;
    unsigned int max = 0;
    const char *path = "data/data02_01.csv";

    // CSVを読み込み線形リストへ格納
    t = init_data(path);
    // 身長の単位を(m)へ変換
    t = from_cm_to_m_for_length(t);

    // 傾きを表示する
    t = head_person(t);
    printf("Tilt      : %lf\n", calc_a(t, CODE_LENGTH));

    // 切片を表示する
    t = head_person(t);
    printf("Intercept : %lf\n", calc_b(t, CODE_LENGTH));

    return true;
}