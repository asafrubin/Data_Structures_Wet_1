#ifndef WET1_PART2_SEGMENT_H
#define WET1_PART2_SEGMENT_H


class Segment {
    int imageID;
    int segmentID;
    int labelID;

public:
    Segment() : imageID(0), segmentID(0), labelID(0) {};
    Segment(int imageID, int segmentID, int labelID) : imageID(imageID), segmentID(segmentID), labelID(labelID) {};
    bool operator==(Segment const& segment);
    int getImageID();
    int getLabelID();
    int getSegmentID();
    void setLabelID(int label);
    void setSegmentID(int segmentID);
    void setImageID(int imageID);
};


#endif //WET1_PART2_SEGMENT_H


