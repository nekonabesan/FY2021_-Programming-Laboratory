#include "modules/pl01_01_module.c"

bool main(void) {
    struct person *t = NULL;
    const char *path = "./data/data01_01.csv";
    t = init_data(path);
    /**
     * 01 最大値と最小値
     * */
    // case 01 身長の最大値
    t = head_person(t);
    t = max_min_parson(t, CODE_MAX, CODE_LENGTH);
    printf("max length : %f\n", t->length);
    // case 02 身長の最小値
    t = head_person(t);
    t = max_min_parson(t, CODE_MIN, CODE_LENGTH);
    printf("min length : %f\n", t->length);
    // case 03 体重の最大値
    t = head_person(t);
    t = max_min_parson(t, CODE_MAX, CODE_WEIGHT);
    printf("max weight :%f\n", t->weight);
    // case 04 体重の最小値
    t = head_person(t);
    t = max_min_parson(t, CODE_MIN, CODE_WEIGHT);
    printf("min weight : %f\n", t->weight);
    
    /**
     * 02 平均値
     * */
      // case 01
    t = head_person(t);
    printf("avg length : %f\n", avg_parson(t, CODE_LENGTH));
    // case 02
    t = head_person(t);
    printf("avg weight : %f\n", avg_parson(t, CODE_WEIGHT));

    /**
     * 03 中央値
     * */
    // case 01
    t = head_person(t);
    printf("med length : %f\n", med_parson(t, CODE_LENGTH));
    // case 02
    t = head_person(t);
    printf("med weight : %f\n", med_parson(t, CODE_WEIGHT));

    /**
     * 04 標準偏差
     * */
    // case 01
    t = head_person(t);
    printf("std dev length : %f\n", std_dev_parson(t, CODE_LENGTH));
    // case 02
    t = head_person(t);
    printf("std dev weight : %f\n", std_dev_parson(t, CODE_WEIGHT));

    /**
     * 05 （身長と体重の）相関係数
     * */
    printf("correlation_coefficient : %f\n", correlation_coefficient_parson(t));

    // メモリ解放
    del_person_array(head_person(t));

    return true; 
}