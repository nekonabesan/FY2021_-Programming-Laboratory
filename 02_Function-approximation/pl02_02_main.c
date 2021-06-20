#include "../modules/pl02_01_module.c"
#define MAX_COUNT 100
#define randDouble ((double)rand()+1.0)/((double)RAND_MAX+2.0) // 0以上1未満の実数値の乱数を生成

//============================================================================//
// genertate-data.cより移植
// @param double mu
// @param double sigma
// @return double mu + sigma * e;
//============================================================================//
double rand_normal(double mu, double sigma) {
    double e = sqrt(-2.0*log(randDouble)) * sin(2.0*M_PI*randDouble);
    return mu + sigma*e;
}

//============================================================================//
// genertate-data.cより移植
// @paramunsigned int cnt
// @param char *path
// @return struct person *t
//============================================================================//
bool generete_data(unsigned int max, const char* path) {
    double a = 0.8; 
    double b = 1.5; 
    double e = 0.0;
    double x = 0.0; 
    double y = 0.0;
    FILE *tmp_file;

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    // データを生成する
    for(unsigned int i = 0; i < max; i++){
        x = randDouble * 10.0;
        e = rand_normal(0, 1);
        y = a * x + b + e;
        fprintf(tmp_file, "%d,%lf,%lf\n", i, x, y);
    }

    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}

//============================================================================//
// 課題(2)
// @paramu int argc
// @param char *argv[]
// @return bool 
//============================================================================//
bool main(int argc, char *argv[]) {
    struct person *t = NULL;
    unsigned int max = 0;
    const char *tmp_file_path = "data/tmp.csv";
    const char *data_file_path = "data/data_02_02.csv";
    double a = 0.0;
    double b = 0.0;
    double rand_double = 0.0;
    FILE *file;

    // 引数が未定義の場合、データ数の上限値を100で初期化する
    if(argv[1] == NULL || strlen(argv[1]) == 0) {
        max = 100;
    } else {
        max = atoi(argv[1]);
    }

    // データファイルを開く
    file = fopen(data_file_path, "w");
    if (file == NULL) {
        printf("cannot open data file\n");
        return false;
    }
    
    // ヒストグラム用データを生成する
    for (unsigned int i = 0; i < MAX_COUNT; i++) {
        // 乱数を生成する
        srand((unsigned int)time(NULL) + i);
        rand();

        // genertate-dataでデータを生成する
        generete_data(max, tmp_file_path);

        // 構造体を初期化
        t = init_data(tmp_file_path);

        // 傾きと切片を導出する
        t = head_person(t);
        a = calc_a(t, CODE_LENGTH);
        t = head_person(t);
        b = calc_b(t, CODE_LENGTH);

        // ファイルへ書き込む
        fprintf(file, "%d,%lf,%lf\n", i, a, b);

        // 一時ファイルを削減する
        remove(tmp_file_path);

        // メモリ解放
        del_person_array(head_person(t));
    }

    // データファイルを閉じる
    fclose(file);

    return true;  
}