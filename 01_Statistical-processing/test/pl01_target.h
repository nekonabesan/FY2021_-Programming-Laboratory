// テスト対象関数のプロトタイプ宣言
#ifndef _TARGET_H_
#define _TARGET_H_

#define MAX 10000
#define CODE_ZERO_EXCEPTION 0x


struct person * writeperson(struct person* t, unsigned int seq, double length, double weight);
struct person * initialize(struct person *t);
struct person * person_clear(int length);
struct person * head_person(struct person *pos);
struct person * eol_person(struct person *pos);
bool del_person_array(struct person *p);
struct person* init_data(const char* path);
struct person* b_sort(struct person *p, unsigned int prefix);

#endif /* _TARGET_H_ */
