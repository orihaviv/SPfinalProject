//
// Created by אורי חביב on 31/05/2017.
//


#include "SPArrayList.h"


action generateAction(position a, position b, char c, char d, SP_CHESS_CASTLING_STATE e,
                      int LWCDeactivated, int RWCDeactivated, int LBCDeactivated, int RBCDeactivated){
    action res;
    res.prev.row = a.row;
    res.prev.column = a.column;
    res.current.row = b.row;
    res.current.column = b.column;
    res.captured = c;
    res.piece = d;
    res.castling = e;
    res.isLWCastlingDeactivated = LWCDeactivated;
    res.isRWCastlingDeactivated = RWCDeactivated;
    res.isLBCastlingDeactivated = LBCDeactivated;
    res.isRBCastlingDeactivated = RBCDeactivated;
    return res;
}


action* actionCopy (action* move) {

    action *res = (action *) malloc(sizeof(action));
    res->prev.row = (*move).prev.row;
    res->prev.column = (*move).prev.column;
    res->current.row = (*move).current.row;
    res->current.column = (*move).current.column;
    res->captured = (*move).captured;
    res->piece = (*move).piece;
    res->castling = (*move).castling;
    res->isLWCastlingDeactivated = (*move).isLWCastlingDeactivated;
    res->isRWCastlingDeactivated = (*move).isRWCastlingDeactivated;
    res->isLBCastlingDeactivated = (*move).isLBCastlingDeactivated;
    res->isRBCastlingDeactivated = (*move).isRBCastlingDeactivated;
    return res;
}


void gameSpArrayListAdd(SPArrayList* src, action elem){
    SP_ARRAY_LIST_MESSAGE message1 = spArrayListAddFirst(src, elem);
    if (message1 == SP_ARRAY_LIST_FULL){
        spArrayListRemoveLast(src);
        spArrayListAddFirst(src, elem);
        return;
    }
    return;
}


SPArrayList* spArrayListCreate(int maxSize){
    if (maxSize <= 0){
        return NULL;
    }
    SPArrayList *recentMoves = (SPArrayList *) malloc(sizeof(SPArrayList));
    if(recentMoves != NULL) {
        recentMoves->elements = (action*)calloc(maxSize, sizeof(action));
        if (recentMoves->elements != NULL) {
            recentMoves->actualSize = 0;
            recentMoves->maxSize = maxSize;
            return recentMoves;
        }
        spArrayListDestroy(&recentMoves);
        printf("Error: calloc has failed");
        return NULL;
    }
    printf("Error: malloc has failed");
    return NULL;
}


SPArrayList* spArrayListCopy(SPArrayList* src){
    if (src != NULL) {
        SPArrayList* newCopy = (SPArrayList*)malloc(sizeof(SPArrayList));
        if (newCopy!=NULL) {
            newCopy->actualSize = src->actualSize;
            newCopy->maxSize = src->maxSize;
            newCopy->elements = (action*)calloc((src->maxSize), sizeof(action));
            if (newCopy->elements != NULL) {
                for (int i = 0; i < src->actualSize; i++) {
                    newCopy->elements[i] = src->elements[i];
                }
                return newCopy;
            }
            spArrayListDestroy(&newCopy);
        }
    }
    printf("Error: calloc has failed");
    return NULL;
}

void spArrayListDestroy(SPArrayList** src){
    if (*src == NULL){
        return;
    }
    free((*src)->elements);
    free(*src);
    *src = NULL;
    return;
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src){
    if (src == NULL){
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    src->actualSize = 0;
    return  SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, action elem, int index){
    if ((src == NULL) || (index > src->actualSize) || (index < 0)){
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    if (src->maxSize == src->actualSize){
        return SP_ARRAY_LIST_FULL;
    }
    for (int i = src->actualSize; i > index; i--){
        src->elements[i] = src->elements[i-1];
    }
    src->elements[index] = elem;
    src->actualSize++;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, action elem){
    SP_ARRAY_LIST_MESSAGE res = spArrayListAddAt(src, elem, 0);
    if (res == SP_ARRAY_LIST_FULL){
        spArrayListRemoveLast(src);
        res = spArrayListAddAt(src, elem, 0);
    }
    return res;
}


SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, action elem){
    return spArrayListAddAt(src, elem, src->actualSize);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index){
    if ((src == NULL) || (index < 0)){
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    if (src->actualSize == 0){
        return SP_ARRAY_LIST_EMPTY;
    }
    if (index >= src->actualSize){
        return SP_ARRAY_LIST_SUCCESS;
    }
    for (int i = index; i < src->actualSize-1; i++){
        src->elements[i] = src->elements[i+1];
    }
    src->actualSize--;
    return  SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src){
    return spArrayListRemoveAt(src, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src){
    return  spArrayListRemoveAt(src, src->actualSize-1);
}

action* spArrayListGetAt(SPArrayList* src, int index){
    if ((src == NULL) || (index >= src->actualSize)){
        return NULL;
    }
    return &(src->elements[index]);
}


action* spArrayListGetFirst(SPArrayList* src){
    return spArrayListGetAt(src, 0);
}

action* spArrayListGetLast(SPArrayList* src){
    return spArrayListGetAt(src, src->actualSize-1);
}

int spArrayListMaxCapacity(SPArrayList* src){
    if (src == NULL){
        return -1;
    }
    return (src->maxSize);
}

int spArrayListSize(SPArrayList* src){
    if (src == NULL){
        return -1;
    }
    return (src->actualSize);
}

bool spArrayListIsFull(SPArrayList* src){
    if (src == NULL){
        return false;
    }
    return ((src->actualSize) == (src->maxSize));
}

bool spArrayListIsEmpty(SPArrayList* src){
    if (src == NULL){
        return false;
    }
    return ((src->actualSize) == 0);
}


int actionCompare(const void *action1, const void *action2) {
    action* a1 = (action*) action1;
    action* a2 = (action*) action2;
    if (a1->current.row == a2->current.row)
        return (a1->current.column  - a2->current.column);
    else
        return a1->current.row - a2->current.row;
}
