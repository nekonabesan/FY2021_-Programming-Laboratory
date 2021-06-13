// テスト対象関数のプロトタイプ宣言
#ifndef _TARGET_H_
#define _TARGET_H_

#define MAX 10000
#define CODE_ZERO_EXCEPTION 0x
#define CODE_LENGTH 1
#define CODE_WEIGHT 2
#define CODE_MAX 1
#define CODE_MIN 2

#define UNDER_WEIGHT 0
#define STD_WEIGHT 1
#define OBESITY_WEIGHT 2
#define HEGH_OBESITY_WEIGHT 3

struct person {
  unsigned int seq;
  double length;
  double weight;
  struct person *prev;
  struct person *next;
};

// 01_01
struct person * writeperson(struct person* t, unsigned int seq, double length, double weight);
struct person * initialize(struct person *t);
struct person * person_clear(int length);
struct person * head_person(struct person *pos);
struct person * eol_person(struct person *pos);
bool del_person_array(struct person *p);
struct person* init_data(const char* path);
struct person* b_sort(struct person *p, unsigned int control_code);
struct person* m_sort(struct person *p, unsigned int control_code);
struct person* max_min_parson(struct person* p, unsigned int max_min_code, unsigned int control_code);
double avg_parson(struct person* p, unsigned int control_code);
double med_parson(struct person* p, unsigned int control_code);
double std_dev_parson(struct person* p, unsigned int control_code);
double correlation_coefficient_parson(struct person* p);

// 01_02
double derivation_bmi(double length, double weight);
unsigned int calc_bmi(double length, double weight);

#endif /* _TARGET_H_ */