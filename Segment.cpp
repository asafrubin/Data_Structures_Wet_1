#include "Segment.h"

bool Segment::operator==(Segment const &segment) {
    return segment.segmentID == segmentID;
}

int Segment::getLabelID() {
    return labelID;
}

int Segment::getSegmentID() {
    return segmentID;
}

void Segment::setLabelID(int label) {
    labelID = label;
}

void Segment::setSegmentID(int segmentID) {
    this->segmentID = segmentID;
}

int Segment::getImageID() {
    return imageID;
}

void Segment::setImageID(int imageID) {
    this->imageID = imageID;
}
