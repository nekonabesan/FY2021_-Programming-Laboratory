#include "pl01_01_module.c"

#define UNDER_WEIGHT 0
#define STD_WEIGHT 1
#define OBESITY_WEIGHT 2
#define HEGH_OBESITY_WEIGHT 3

//============================================================================//
// BMIを計算する
// @param double length
// @param double weight
// @return double bmi
//============================================================================//
double derivation_bmi(double length, double weight) {
    double bmi = 0.0;

    // BMIを導出する
    bmi = (weight/pow((length/100.0), 2));

    return bmi;
}

//============================================================================//
// 課題2 肥満度を判定するプログラム
// @param double length
// @param double weight
// @return double bmi
//============================================================================//
unsigned int calc_bmi(double length, double weight) {
    unsigned int bmi = 0;
    double tmp = 0.0;

    // BMIを導出する
    tmp = derivation_bmi(length, weight);

    // 判定基準をパラメータへセットする
    if (tmp < 18.5) {
        bmi = UNDER_WEIGHT;
    } else if (18.5 <= tmp && tmp < 25.0) {
        bmi = STD_WEIGHT;
    } else if (25.0 <= tmp && tmp < 30.0) {
        bmi = OBESITY_WEIGHT;
    } else if (30 <= tmp) {
        bmi = HEGH_OBESITY_WEIGHT;
    }

    return bmi;
}