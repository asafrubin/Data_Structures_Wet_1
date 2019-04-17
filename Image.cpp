#include <cstdlib>
#include "Image.h"

Image::Image(int imageID, int numOfSegments) : imageID(imageID), numOfSegments(numOfSegments) {
    try {
        labeledSegments = new Segment[numOfSegments];
    }catch(std::bad_alloc &e){
        throw e;
    }
    try {
        unLabeledSegmentList = new List<Segment>;
    }catch(std::bad_alloc &e){
        delete labeledSegments;
        throw e;
    }
    for(int i = 0; i < numOfSegments ; i++){
        labeledSegments[i].setImageID(imageID);
        labeledSegments[i].setLabelID(0);
        labeledSegments[i].setSegmentID(i);
        unLabeledSegmentList->insert(labeledSegments[i]);
    }
}

Image::Image(int ImageID) : imageID(ImageID), numOfSegments(0), labeledSegments(nullptr), unLabeledSegmentList(nullptr){}

int Image::getImageID() {
    return imageID;
}

int Image::getSegmentLabel(int segment) const {
    return labeledSegments[segment].getLabelID();
}

bool Image::setLabelToSegment(int segmentID, int label) {
    unLabeledSegmentList->remove( Segment(imageID, segmentID, label) );
    labeledSegments[segmentID].setLabelID(label);
    return true;
}

void Image::deleteLabelOfSegment(int segmentID) {
    labeledSegments[segmentID].setLabelID(0);
    unLabeledSegmentList->insert( Segment(imageID, segmentID, 0) );
}

bool Image::getUnLabledSegments(int **segments, int *numOfSegments) {
    *numOfSegments = unLabeledSegmentList->getSize();
    int* p_segments = (int*)malloc(sizeof(int) * (*numOfSegments) );
    if(p_segments == nullptr){
        *numOfSegments = 0;
        segments = nullptr;
        return false;
    }
    Node<Segment> *it = unLabeledSegmentList->getHead();
    int i=0;
    while(it != nullptr){
        p_segments[i] = it->getData().getSegmentID();
        it = it->getNext();
        i++;
    }
    *segments = p_segments;
    return true;
}

bool Image::isUnLabeled() const {
    return unLabeledSegmentList->getSize() == numOfSegments;
}

bool Image::isFullyLabeled() const {
    return unLabeledSegmentList->getSize() == 0;
}

void Image::operator()(Image *image) {
    std::cout << std::to_string(image->getImageID()) + " " ;
}

int Image::getNumOfSegments() const {
    return numOfSegments;
}

Segment Image::getSegment(int i) const {
    return labeledSegments[i];
}

Image::Image(Image const &image) {
    imageID = image.imageID;
    numOfSegments = image.numOfSegments;

    try {
        labeledSegments = new Segment[numOfSegments];
    }catch(std::bad_alloc &e){
        throw e;
    }
    try {
        unLabeledSegmentList = new List<Segment>;
    }catch(std::bad_alloc &e){
        delete labeledSegments;
        throw e;
    }
    for(int i=0; i < numOfSegments; i++) {
        labeledSegments[i] = image.labeledSegments[i];
        if(labeledSegments[i].getLabelID() == 0){
            unLabeledSegmentList->insert(labeledSegments[i]);
        }
    }
}

Image::~Image(){
    delete[] labeledSegments;
    labeledSegments = nullptr;
    delete unLabeledSegmentList;
    unLabeledSegmentList = nullptr;
}
