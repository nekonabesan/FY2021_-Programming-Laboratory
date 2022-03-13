#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

/** 
 * (課題1)
 * 例題２で作成したプログラム（タイムステップ：dt = 0.1, およびdt = 0.025）において， 
 * 計算終了時間をt=2,4,6,8,10と変更した際の相対誤差 （次ページ参照）の変化を確認せよ．
 * なお，値は指数関数表記とし，仮数部は⼩数点以下第６位までとする．
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double dx = 0.0;
    double t = 0.0;
    double dt = 0.1;
    double max = 2.0;
    double end_time = 0.0;
    unsigned int values = 10;
    const char *path = "data/pl06_01.csv";

    // データを配列として定義する
    double data[10][3] = {
         {0.1,    2.0,  20}
        ,{0.1,    4.0,  40}
        ,{0.1,    6.0,  60}
        ,{0.1,    8.0,  80}
        ,{0.1,   10.0, 100}
        ,{0.025,  2.0,  80}
        ,{0.025,  4.0, 160}
        ,{0.025,  6.0, 240}
        ,{0.025,  8.0, 320}
        ,{0.025, 10.0, 400}
    };


    // 計算結果を出力するCSVファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    for (unsigned int i = 0; i < values; i++) {
        x = 1.0;
        t = 0.0;
        dt  =       data[i][0];
        end_time =  data[i][1];
        max =       data[i][2];
        
        // オイラー法による数値解の導出
        for (unsigned int j = 0; j < max; j++) {
            t += dt;
            x += (x * dt);
        }

        // 相対誤差の導出
        dx = fabs((x - exp(t))/exp(t));

        // 計算結果をファイルへ出力する
        fprintf(tmp_file, "%.6f,%.6f,%.20f,%.20f,%.20f,%.20f\n", dt, max, t, x, exp(t), dx);
    }

    // 計算結果を出力するCSVファイルを閉じる
    fclose(tmp_file);

    return true;
}