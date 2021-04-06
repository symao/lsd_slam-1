/*
 * RawLogReader.h
 *
 *  Created on: 19 Nov 2012
 *      Author: thomas
 */

#ifndef RAWLOGREADER_H_
#define RAWLOGREADER_H_

#include <stdio.h>
#include <zlib.h>

#include <boost/filesystem.hpp>
#include <cassert>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

#include "Resolution.h"
#include "Stopwatch.h"

class RawLogReader {
public:
    RawLogReader(Bytef*& decompressionBuffer, IplImage*& deCompImage, std::string file);

    virtual ~RawLogReader();

    void getNext();

    int getNumFrames();

    bool hasMore();

    const std::string getFile();

    unsigned short minVal, maxVal;
    int64_t timestamp;

    unsigned short* depth;
    unsigned char* rgb;

private:
    Bytef*& decompressionBuffer;
    IplImage*& deCompImage;
    unsigned char* depthReadBuffer;
    unsigned char* imageReadBuffer;
    int32_t depthSize;
    int32_t imageSize;

    const std::string file;
    FILE* fp;
    int32_t numFrames;
    int currentFrame;
    int width;
    int height;
    int numPixels;
};

#endif /* RAWLOGREADER_H_ */
