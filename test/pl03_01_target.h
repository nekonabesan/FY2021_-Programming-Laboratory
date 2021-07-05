// テスト対象関数のプロトタイプ宣言
#ifndef _TARGET_H_
#define _TARGET_H_

#define CODE_ZERO_EXCEPTION 0x
#define CODE_LENGTH 1
#define CODE_WEIGHT 2
#define CODE_MAX 1
#define CODE_MIN 2

struct answer {
    unsigned int seq;
    double x;
    double y;
    struct answer *prev;
    struct answer *next;
};

struct answer * head_answer(struct answer *pos);
struct answer * eol_answer(struct answer *pos);
bool del_answer_array(struct answer *p);

#endif /* _TARGET_H_ */