//
// Created by אורי חביב on 31/05/2017.
//


#include "SPArrayList.h"





void gameSpArrayListAdd(SPArrayList* src, position elem){
    SP_ARRAY_LIST_MESSAGE message1 = spArrayListAddLast(src, elem);
    if (message1 == SP_ARRAY_LIST_FULL){
        spArrayListRemoveFirst(src);
        spArrayListAddLast(src, elem);
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
        recentMoves->elements = (position*)calloc(maxSize, sizeof(position));
        if (recentMoves->elements != NULL) {
            recentMoves->actualSize = 0;
            recentMoves->maxSize = maxSize;
            return recentMoves;
        }
        spArrayListDestroy(recentMoves);
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
            newCopy->elements = (position*)calloc((src->maxSize), sizeof(position));
            if (newCopy->elements != NULL) {
                for (int i = 0; i < src->actualSize; i++) {
                    newCopy->elements[i] = src->elements[i];
                }
                return newCopy;
            }
            spArrayListDestroy(newCopy);
        }
    }
    printf("Error: calloc has failed");
    return NULL;
}

void spArrayListDestroy(SPArrayList* src){
    if (src == NULL){
        return;
    }
    free(src->elements);
    free(src);
    return;
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src){
    if (src == NULL){
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    src->actualSize = 0;
    return  SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, position elem, int index){
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

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, position elem){
    return spArrayListAddAt(src, elem, 0);
}


SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, position elem){
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

int spArrayListGetAt(SPArrayList* src, int index){
    if ((src == NULL) || (index >= src->actualSize)){
        return -1;
    }
    return (src->elements[index]);
}


int spArrayListGetFirst(SPArrayList* src){
    return spArrayListGetAt(src, 0);
}

int spArrayListGetLast(SPArrayList* src){
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
