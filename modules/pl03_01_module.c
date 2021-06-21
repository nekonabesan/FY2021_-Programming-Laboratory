#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define EPSILON 0.000000000001
#define NMAX 1000000000000

struct answer {
    unsigned int seq;
    double x;
    double y;
    struct answer *prev;
    struct answer *next;
};

//--------------------------------------------------------------//
// 先頭のアドレスを返す処理
// @param struct ent2 *pos
// @return struct ent2 *start
//--------------------------------------------------------------//
struct answer * head_answer(struct answer *pos) {
    if(pos->prev == NULL || pos == NULL){
        return pos;
    }
    struct answer *head = pos->prev;
    while(1){
        if(head->prev){
        head = head->prev;
        } else {
        break;
        }
    }
    return head;
}

//--------------------------------------------------------------//
// 最後尾のアドレスを返す処理
// @param struct ent2 *pos
// @return struct ent2 *next
//--------------------------------------------------------------//
struct answer * eol_answer(struct answer *pos) {
    if(pos->next == NULL){
        return pos;
    }
    struct answer *next = pos->next;
    while(1){
        if(next->next != NULL){
            next = next->next;
        } else {
            break;
        }
    }
    return next;
}

//============================================================================//
// リストを全て削除する処理
// @param struct answer *p
// @return bool
//============================================================================//
bool del_answer_array(struct answer *p) {
    if(p == NULL){
        return false;
    }
    struct answer *pos = p;
    while(pos->next){
        pos = pos->next;
        free(pos->prev);
    }
    return true;
}