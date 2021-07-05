#include "modules/pl01_02_module.c"

/**
 * 課題(2)
 * */
bool main(void) {
    struct person *t = NULL;
    const char *path = "./data/data01_02_02.csv";
    unsigned int max = 0;

    t = init_data(path);
    t = head_person(t);

    t= eol_person(t);
    max = t->seq;

    t = head_person(t);
    for(unsigned int i = 0; i <= max; i++) {
        printf("length : %f, weight : %f ,BMI rate : %f ", t->length, t->weight, derivation_bmi(t->length, t->weight));
        switch (calc_bmi(t->length, t->weight))
        {
        case UNDER_WEIGHT:
            printf(" -> Underweight\n");
            break;
        case STD_WEIGHT:
            printf(" -> standard\n");
            break;
        case OBESITY_WEIGHT:
            printf(" -> obesity\n");
            break;
        case HEGH_OBESITY_WEIGHT:
            printf(" -> Severe obesity\n");
            break;
        default:
            break;
        }

        if(t->next != NULL) {
            t = t->next;
        }
    }
 
    // メモリ解放
    del_person_array(head_person(t));

    return true;
}