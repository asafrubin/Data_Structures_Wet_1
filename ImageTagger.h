#ifndef WET1_PART2_IMAGETAGGER_H
#define WET1_PART2_IMAGETAGGER_H

#include "AVLtree.h"
#include "AVLnode.h"
#include "Image.h"
#include "library2.h"

class dummy{
public:
    int operator()(Image *a){
        return 1;
    }
};
class CompareFunction{
public:
    int operator()(Image *a, Image *b){
        if(a->getImageID() == b->getImageID()){
            return 0;
        }
        else if(a->getImageID() < b->getImageID()){
            return 1;
        }
        else
            return -1;
    }
};
class getLables{
    List<Segment>* segmentList;
    int labelID;
public:
    getLables(int labelID, List<Segment> *segmentList) : segmentList(segmentList), labelID(labelID) {};
    ~getLables() = default;
    getLables(const getLables &var1) : segmentList(var1.segmentList), labelID(var1.labelID) {
        //std::cout << "getLabel copyConstructor" << endl;
    };

    void operator()(Image const *image){
        if(image->isUnLabeled()){
            return;
        }
        for(int i=0; i < image->getNumOfSegments(); i++){
            if(image->getSegmentLabel(i) == labelID){
                segmentList->insert( image->getSegment(i) );
            }
        }
    }
};


class ImageTagger {
    AVLtree<Image*,CompareFunction,dummy> ImageTree;
    int segments;

    bool imageExists(int imageID);
    bool checkIfSegmentOfLabelExists(int imageID, int segmentID);
    bool imageIsUnLabled(int imageID);
    bool imageIsFullyLabeled(int imageID);
public:
    explicit ImageTagger(int segments) : ImageTree(), segments(segments)  {};
    //ImageTagger(const AVLtree<Image, CompareFunction, dummy> &ImageTree);
    virtual ~ImageTagger();
    StatusType addImage(int imageID);
    StatusType imageDelete(int imageID);
    StatusType addLabelToImage(int imageID, int segmentID, int Label);
    StatusType getLabelOfImageBySegment(int imageID, int segmentID, int* label);
    StatusType deleteLabelFromImageBySegment(int imageID, int segmentID);
    StatusType getAllUnLabeledSegmentsOfImage(int imageID,int** segments, int* numOfSegments);
    StatusType getAllSegmentsByLabel(int label, int **images, int **segments, int *numOfSegments);
    void operator()(Image *image){
        delete image;
    }
    void Quit();
};
class destroyImage{
public:
    void operator()(Image *node){
        node->getImageID();
    }
};
#endif //WET1_PART2_IMAGETAGGER_H