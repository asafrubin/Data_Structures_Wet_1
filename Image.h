#ifndef WET1_PART2_IMAGE_H
#define WET1_PART2_IMAGE_H

#include "List.h"
#include "listNode.h"
#include "Segment.h"

class Image {
    int imageID;
    int numOfSegments;
    Segment *labeledSegments;
    List<Segment> *unLabeledSegmentList;

public:
    Image(int imageID, int numOfSegments);
    explicit Image(int ImageID);
    Image(Image const &image);
    ~Image();

    int getImageID();
    int getSegmentLabel(int segment) const;
    int getNumOfSegments() const;
    Segment getSegment(int i) const;
    bool setLabelToSegment(int segmentID, int label);
    void deleteLabelOfSegment(int segmentID);
    bool getUnLabledSegments(int** segments, int* numOfSegments);
    bool isUnLabeled() const;
    bool isFullyLabeled() const;
    void operator()(Image *image);
};


#endif //WET1_PART2_IMAGE_H
