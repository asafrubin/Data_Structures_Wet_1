#include <new>
#include "library2.h"
#include "ImageTagger.h"

using namespace std;

void *Init(int segments) {
    if(segments <= 0){
        return nullptr;
    }
    void* DS = new(std::nothrow) ImageTagger(segments);
    return DS;
}

StatusType AddImage(void *DS, int imageID) {
    if(DS == nullptr) {
        return INVALID_INPUT;
    }

    return ((ImageTagger*)DS)->addImage(imageID);
}

StatusType DeleteImage(void *DS, int imageID) {
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((ImageTagger*)DS)->imageDelete(imageID);
}

StatusType AddLabel(void *DS, int imageID, int segmentID, int label) {
    if(DS == nullptr) {
        return INVALID_INPUT;
    }

    return ((ImageTagger*)DS)->addLabelToImage(imageID, segmentID, label);
}

StatusType GetLabel(void *DS, int imageID, int segmentID, int *label) {
    if (DS == nullptr || label == nullptr) {
        return INVALID_INPUT;
    }
    return ((ImageTagger*)DS)->getLabelOfImageBySegment(imageID, segmentID, label);
}

StatusType DeleteLabel(void *DS, int imageID, int segmentID) {
    if(DS == nullptr) {
        return INVALID_INPUT;
    }

    return ((ImageTagger*)DS)->deleteLabelFromImageBySegment(imageID, segmentID);
}

StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments, int *numOfSegments) {
    if(DS == nullptr || segments == nullptr || numOfSegments == nullptr) {
        return INVALID_INPUT;
    }

    return ((ImageTagger*)DS)->getAllUnLabeledSegmentsOfImage(imageID, segments, numOfSegments);
}

StatusType GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments, int *numOfSegments) {
    if(DS == nullptr || images == nullptr || segments == nullptr || numOfSegments == nullptr) {
        return INVALID_INPUT;
    }

    return ((ImageTagger*)DS)->getAllSegmentsByLabel(label, images, segments, numOfSegments);
}

void Quit(void **DS) {
    if(DS == nullptr) {
        return;
    }
     //((ImageTagger*)DS)->Quit();
     delete (*((ImageTagger**)DS));
    *DS = nullptr;
}
