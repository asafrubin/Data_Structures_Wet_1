#include "ImageTagger.h"
#include "AVLnode.h"
#include "AVLtree.h"

//ImageTagger::ImageTagger(const AVLtree<Image, CompareFunction, dummy> &ImageTree) : ImageTree(ImageTree) {}

ImageTagger::~ImageTagger() {}

bool ImageTagger::imageExists(int imageID) {
    if(imageID <= 0) {
        return INVALID_INPUT;
    }
    //find returns pointer, if pointer is null bool is false.
    Image imageToFind = Image(imageID);
    return ImageTree.find( &imageToFind );
}

StatusType ImageTagger::addImage(int imageID) {
    if(imageID <= 0) {
        return INVALID_INPUT;
    }
    if(imageExists(imageID)){
        return FAILURE;
    }

    Image *imageToAdd = new(std::nothrow) Image(imageID, segments);
    if(imageToAdd == nullptr){
        return ALLOCATION_ERROR;
    }

    ImageTree.insert( imageToAdd );
    return SUCCESS;
}

StatusType ImageTagger::imageDelete(int imageID) {
    if(imageID <= 0) {
        return INVALID_INPUT;
    }
    if(!imageExists(imageID)){
        return FAILURE;
    }

    Image imageToRemove = Image(imageID);
    //Image *image_p = nullptr;
    //ImageTree.inOrder(imageToRemove);
    //std::cout << std::endl;
    ImageTree.find( &imageToRemove )->getData();
    ImageTree.remove( &imageToRemove );
    //ImageTree.inOrder(imageToRemove);
    //std::cout << std::endl;
    return SUCCESS;
}

StatusType ImageTagger::addLabelToImage(int imageID, int segmentID, int label) {
    if(imageID <= 0 || segmentID < 0 || segmentID >= segments || label <= 0) {
        return INVALID_INPUT;
    }
    if( !imageExists(imageID) || !checkIfSegmentOfLabelExists(imageID, segmentID)){
        return FAILURE;
    }
    Image imageToFind = Image(imageID);
    ImageTree.find( &imageToFind )->getData()->setLabelToSegment(segmentID, label);

    return SUCCESS;
}

StatusType ImageTagger::getLabelOfImageBySegment(int imageID, int segmentID, int *label) {
    if(imageID <= 0 || segmentID < 0 || segmentID >= segments) {
        return INVALID_INPUT;
    }
    if( !imageExists(imageID) || checkIfSegmentOfLabelExists(imageID, segmentID)){
        return FAILURE;
    }
    Image imageToFind = Image(imageID);
    *label = ImageTree.find( &imageToFind )->getData()->getSegmentLabel(segmentID);

    return SUCCESS;
}

StatusType ImageTagger::deleteLabelFromImageBySegment(int imageID, int segmentID) {
    if(imageID <= 0 || segmentID < 0 || segmentID >= segments) {
        return INVALID_INPUT;
    }
    if( !imageExists(imageID) || checkIfSegmentOfLabelExists(imageID, segmentID)){
        return FAILURE;
    }

    Image imageToFind = Image(imageID);
    ImageTree.find( &imageToFind )->getData()->deleteLabelOfSegment(segmentID);
    return SUCCESS;
}

StatusType ImageTagger::getAllUnLabeledSegmentsOfImage(int imageID, int **segments, int *numOfSegments) {
    if( imageID <= 0) {
        return INVALID_INPUT;
    }
    if( !imageExists(imageID) || imageIsFullyLabeled(imageID) ){
        segments = nullptr;
        *numOfSegments = 0;
        return FAILURE;
    }

    Image imageToFind = Image(imageID);
    if(!ImageTree.find( &imageToFind )->getData()->getUnLabledSegments(segments, numOfSegments)){
        return FAILURE;
    }

    return SUCCESS;
}

StatusType ImageTagger::getAllSegmentsByLabel(int label, int **images, int **segments, int *numOfSegments) {
    if(label <= 0){
        return INVALID_INPUT;
    }

    List<Segment> *segmentList = new List<Segment>;
    getLables getLabel(label, segmentList);
    ImageTree.inOrder(getLabel);

    *numOfSegments = segmentList->getSize();
    if(*numOfSegments == 0){
        *images = nullptr;
        *segments = nullptr;
        delete segmentList;
        return SUCCESS;
    }
    int* p_segments = (int*)malloc(sizeof(int) * (*numOfSegments));
    if(p_segments == nullptr){
        delete segmentList;
        return ALLOCATION_ERROR;
    }
    int* p_images = (int*)malloc(sizeof(int) * (*numOfSegments));
    if(p_images == nullptr){
        delete segmentList;
        free(p_segments);
        return ALLOCATION_ERROR;
    }
    Node<Segment>* segmentNode = segmentList->getTail();
    int i=0;
    while(i < *numOfSegments){
        p_images[i] = segmentNode->getData().getImageID();
        p_segments[i] = segmentNode->getData().getSegmentID();
        segmentNode = segmentNode->getPrevious();
        i++;
    }
    *images = p_images;
    *segments = p_segments;

    delete segmentList;
    //segmentList.clear();
    return SUCCESS;
}

bool ImageTagger::checkIfSegmentOfLabelExists(int imageID, int segmentID) {
    Image imageToFind = Image(imageID);
    return ImageTree.find( &imageToFind )->getData()->getSegmentLabel(segmentID) == 0;
}

bool ImageTagger::imageIsUnLabled(int imageID) {
    Image imageToFind = Image(imageID);
    return ImageTree.find( &imageToFind )->getData()->isUnLabeled();
}

bool ImageTagger::imageIsFullyLabeled(int imageID) {
    Image imageToFind = Image(imageID);
    return ImageTree.find( &imageToFind )->getData()->isFullyLabeled();
}

void ImageTagger::Quit() {}