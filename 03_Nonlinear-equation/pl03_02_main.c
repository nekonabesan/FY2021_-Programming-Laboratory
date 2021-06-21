#include  "../modules/pl03_01_module.c"

//============================================================================//
// @param double x
// @return double powl(x, 3) + (-1 * (3 * powl(x, 2))) + (-1 * x) + 3
//============================================================================//
double g(double x) {
    return powl(x, 3) + (-1 * (3 * powl(x, 2))) + (-1 * x) + 3; 
}

//============================================================================//
// @param double x
// @return (3 * powl(x, 2)) + (-1 * (6 * x)) - 1; 
//============================================================================//
double g_2(double x) {
    return (3 * powl(x, 2)) + (-1 * (6 * x)) - 1; 
}

//============================================================================//
// ニュートン法で解を導出する処理
// @param struct answer *p
// @return bool
//============================================================================//
struct answer * newton(struct answer *q) {
    struct answer *t = NULL;
    struct answer *prev = NULL;
    struct answer *start = NULL;
    unsigned int seq = 0;
    unsigned int n = 0;
    double d = 0.0;
    double x = 0.0;
    
    q = head_answer(q);

    while (1) {
        // xを初期化する
        x = q->x;

        // 構造体を初期化する
        t = (struct answer*)malloc(sizeof(struct answer) * 1);

        // リストの先頭要素を取得
        if(seq == 0){
            start = t;
            t->prev = NULL;
        }

        // 解の導出を試行する
        do {
            d = ((-1 * g(x))/g_2(x));
            x = x + d;
            n++;
        } while (fabs(d) > EPSILON && n < NMAX);
        // 失敗の場合xへ未定義値を設定する
        if (n == NMAX) {
            x = NMAX;
        }
        t->x = x;
        // 線形リスト
        if (prev != NULL) {
            t->prev = prev;
            prev->next = t;
        }
        // 線形リスト
        prev = t;
        t->next = NULL;
        t->seq = seq;
        seq++;

        if(q->next != NULL) {
            q = q->next;
        } else {
            break;
        }
    }

    del_answer_array(head_answer(q));
    if (t != NULL) {
        t = head_answer(t);
    }

    return t;
}

struct answer * print_answer(struct answer *a) {
    a = head_answer(a);

    while (1) {
        printf("Answer %lf\n", a->x);
        if(a->next == NULL) {
            break;
        } else {
            a = a->next;
        }
    }

    return head_answer(a);
}

//============================================================================//
// 演習課題ニュートン法
// @param void
// @return bool
//============================================================================//
bool main(void) {
    struct answer *q = NULL;
    struct answer *a = NULL;
    struct answer *prev = NULL;
    double arr1[3] = {-2.0, 1.5, 5.0};
    
    for (unsigned int i = 0; i < 3; i++) {
        q = (struct answer*)malloc(sizeof(struct answer) * 1);
        if (prev != NULL) {
            q->prev = prev;
            prev->next = q;
        }
        // 線形リスト
        prev = q;
        q->next = NULL;
        q->seq = i;
        q->x = arr1[i];
    }

    a = newton(head_answer(q));
    a = print_answer(a);

    return del_answer_array(head_answer(a));
}

