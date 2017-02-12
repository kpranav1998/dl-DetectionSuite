//
// Created by frivas on 5/02/17.
//

#include <Utils/Logger.h>
#include "GenericDatasetWriter.h"


GenericDatasetWriter::GenericDatasetWriter(const std::string &path,DatasetReaderPtr &reader, const std::string &writerImplementation) {
    configureAvailablesImplementations();
    if (std::find(this->availableImplementations.begin(), this->availableImplementations.end(), writerImplementation) != this->availableImplementations.end()){
        imp = getImplementation(writerImplementation);
        switch (imp) {
            case WR_YOLO:
                this->yoloDatasetWriterPtr = YoloDatasetWriterPtr( new YoloDatasetWriter(path,reader));
                break;
            case WR_OWN:
                this->ownDatasetWriterPtr = OwnDatasetWriterPtr( new OwnDatasetWriter(path,reader));
                break;
            default:
                Logger::getInstance()->error(writerImplementation + " is not a valid writer implementation");
                break;
        }
    }
    else{
        Logger::getInstance()->error(writerImplementation + " is not a valid writer implementation");
    }
}



void GenericDatasetWriter::configureAvailablesImplementations() {
    this->availableImplementations.push_back("own");
    this->availableImplementations.push_back("yolo");
}

WRITER_IMPLEMENTATIONS GenericDatasetWriter::getImplementation(const std::string &writerImplementation) {
    if (writerImplementation.compare("yolo")==0){
        return WR_YOLO;
    }
    if (writerImplementation.compare("own")==0){
        return WR_OWN;
    }
}

DatasetWriterPtr GenericDatasetWriter::getWriter() {
    switch (imp) {
        case WR_YOLO:
            return this->yoloDatasetWriterPtr;
        case WR_OWN:
            return this->ownDatasetWriterPtr;
        default:
            break;
    }
}


