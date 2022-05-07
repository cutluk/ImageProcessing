//
// Created by Luke Cutting on 3/21/22.
//

#include "Image.h"
#include <fstream>
#include <cmath>

Image::Image(){}
Image::Image(char &idLength, char &colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength,
             char colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel,
             char imageDescriptor) {
    this->idLength=idLength;
    this->colorMapType=colorMapType;
    this->dataTypeCode=dataTypeCode;
    this->colorMapOrigin=colorMapOrigin;
    this->colorMapLength=colorMapLength;
    this->colorMapDepth=colorMapDepth;
    this->xOrigin=xOrigin;
    this->yOrigin=yOrigin;
    this->width=width;
    this->height=height;
    this->bitsPerPixel=bitsPerPixel;
    this->imageDescriptor=imageDescriptor;
}

Image::Pixels::Pixels(){}
Image::Pixels::Pixels(unsigned char red, unsigned char blue, unsigned char green) {
    this->blue=blue;
    this->green=green;
    this->red=red;
}

void Image::GetDataFromFile(const string &filePath, Image &imgData){
    ifstream inFile(filePath, ios_base::binary);
    if (inFile.is_open()){
        inFile.read((char*) &idLength, 1);
        inFile.read((char*) &colorMapType, 1);
        inFile.read((char*) &dataTypeCode, 1);
        inFile.read((char*) &colorMapOrigin, 2);
        inFile.read((char*) &colorMapLength, 2);
        inFile.read((char*) &colorMapDepth, 1);
        inFile.read((char*) &xOrigin, 2);
        inFile.read((char*) &yOrigin, 2);
        inFile.read((char*) &width, 2);
        inFile.read((char*) &height, 2);
        inFile.read((char*) &bitsPerPixel, 1);
        inFile.read((char*) &imageDescriptor, 1);

        int imgSize = width * height;
        Pixels pixelColorObj;

        for(int i=0; i<imgSize; i++){
            inFile.read((char*) &pixelColorObj.blue, 1);
            inFile.read((char*) &pixelColorObj.green, 1);
            inFile.read((char*) &pixelColorObj.red, 1);

            pixelVect.push_back(pixelColorObj);
        }
    }
}
void Image::WriteDataFromFile(const string &filePath, Image &imgFinal) {
    ofstream outFile(filePath, ios_base::binary);
    if (outFile.is_open()){
        outFile.write((char*) &imgFinal.idLength, 1);
        outFile.write((char*) &imgFinal.colorMapType, 1);
        outFile.write((char*) &imgFinal.dataTypeCode, 1);
        outFile.write((char*) &imgFinal.colorMapOrigin, 2);
        outFile.write((char*) &imgFinal.colorMapLength, 2);
        outFile.write((char*) &imgFinal.colorMapDepth, 1);
        outFile.write((char*) &imgFinal.xOrigin, 2);
        outFile.write((char*) &imgFinal.yOrigin, 2);
        outFile.write((char*) &imgFinal.width, 2);
        outFile.write((char*) &imgFinal.height, 2);
        outFile.write((char*) &imgFinal.bitsPerPixel, 1);
        outFile.write((char*) &imgFinal.imageDescriptor, 1);

        int imgSize = imgFinal.height * imgFinal.width;

        for(int i=0; i<imgSize; i++){
            outFile.write((char*) &pixelVect[i].blue, 1);
            outFile.write((char*) &pixelVect[i].green, 1);
            outFile.write((char*) &pixelVect[i].red,1);
        }
    }
}
bool Image::Test(Image image, Image example){
    int imgSize = image.width * image.height;
    bool test = true;

    if (image.idLength != example.idLength){test = false;}
    if (image.colorMapType != example.colorMapType){test = false;}
    if (image.dataTypeCode != example.dataTypeCode){test = false;}
    if (image.colorMapOrigin != example.colorMapOrigin){test = false;}
    if (image.colorMapLength != example.colorMapLength){test = false;}
    if (image.colorMapDepth != example.colorMapDepth){test = false;}
    if (image.xOrigin != example.xOrigin){test = false;}
    if (image.yOrigin != example.yOrigin){test = false;}
    if (image.width != example.width){test = false;}
    if (image.height != example.height){test = false;}
    if (image.bitsPerPixel != example.bitsPerPixel){test = false;}
    if (image.imageDescriptor != example.imageDescriptor){test = false;}

    for (int i = 0; i < imgSize; i++) {
        if (image.pixelVect[i].red != example.pixelVect[i].red){test = false;}
        if (image.pixelVect[i].blue != example.pixelVect[i].blue){test = false;}
        if (image.pixelVect[i].green != example.pixelVect[i].green){test = false;}
    }
    return test;
}
void Image::Multiply(Image &layer1, Image &pattern1, Image &part1Final){
    part1Final=layer1;
    part1Final.pixelVect.clear();

    int imgSize = layer1.width * layer1.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for (int i = 0; i < imgSize; i++) {
        float redFloat = ((float) layer1.pixelVect[i].red) * ((float) pattern1.pixelVect[i].red);
        float greenFloat = ((float) layer1.pixelVect[i].green) * ((float) pattern1.pixelVect[i].green);
        float blueFloat = ((float) layer1.pixelVect[i].blue) * ((float) pattern1.pixelVect[i].blue);

        red = (unsigned char) lround(redFloat / 255);
        green = (unsigned char) lround(greenFloat / 255);
        blue = (unsigned char) lround(blueFloat / 255);

        Image::Pixels pixel(red, blue, green);
        part1Final.pixelVect.push_back(pixel);
    }
}
void Image::Subtract(Image &layer2, Image &car, Image &part2Final){
    part2Final=layer2;
    part2Final.pixelVect.clear();

    int imgSize = layer2.width * layer2.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    part2Final.pixelVect.clear();
    for (int i = 0; i < imgSize; i++) {
        // Subtracts the values
        float redFloat = ((float) car.pixelVect[i].red) - ((float) layer2.pixelVect[i].red);
        float greenFloat = ((float) car.pixelVect[i].green) - ((float) layer2.pixelVect[i].green);
        float blueFloat = ((float) car.pixelVect[i].blue) - ((float) layer2.pixelVect[i].blue);

        //Sets the values to 0 if the went under 0
        if(redFloat<0){redFloat=0;}
        if(greenFloat<0){greenFloat=0;}
        if(blueFloat<0){blueFloat=0;}

        //Rounds the functions and sets them to unsigned char
        red = (unsigned char)lround(redFloat);
        blue = (unsigned char)lround(blueFloat);
        green = (unsigned char)lround(greenFloat);

        //Stores in pixel object and stored into the pixelVector
        Image::Pixels pixel(red, blue, green);
        part2Final.pixelVect.push_back(pixel);
    }
}
void Image::Blend(Image &text, Image &part3Temp, Image &part3Final){
    part3Final=part3Temp;
    part3Final.pixelVect.clear();

    int imgSize = part3Temp.width * part3Temp.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for (int i = 0; i < imgSize; i++) {
        float redFloat = 1-(1-(float)text.pixelVect[i].red/255) * (1-(float)part3Temp.pixelVect[i].red/255);
        float greenFloat = 1-(1-(float)text.pixelVect[i].green/255) * (1-(float)part3Temp.pixelVect[i].green/255);
        float blueFloat = 1-(1-(float)text.pixelVect[i].blue/255) * (1-(float)part3Temp.pixelVect[i].blue/255);

        red = (unsigned char) lround(redFloat * 255);
        green = (unsigned char) lround(greenFloat * 255);
        blue = (unsigned char) lround(blueFloat * 255);

        Image::Pixels pixel(red, blue, green);
        part3Final.pixelVect.push_back(pixel);
    }
}
void Image::AddGreen(Image &car, Image &part6Final) {
    part6Final = car;
    part6Final.pixelVect.clear();

    int imgSize = car.width * car.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for (int i = 0; i < imgSize; i++) {
        float greenFloat = ((float) car.pixelVect[i].green+200);
        if(greenFloat>255){
            greenFloat=255;
        }
        green = (unsigned char)(greenFloat);
        red = car.pixelVect[i].red;
        blue = car.pixelVect[i].blue;

        Image::Pixels pixel(red, blue, green);
        part6Final.pixelVect.push_back(pixel);
    }
}
void Image::ScaleRedBlue(Image &car, Image &part7Final) {
    part7Final = car;
    part7Final.pixelVect.clear();

    int imgSize = car.width * car.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for (int i = 0; i < imgSize; i++) {
        float blueFloat = ((float) car.pixelVect[i].blue*0);
        float redFloat = ((float)car.pixelVect[i].red*4);
        if(redFloat>255){
            redFloat=255;
        }
        red = (unsigned char) lround(redFloat);
        blue = (unsigned char)(blueFloat);
        green = car.pixelVect[i].green;

        Image::Pixels pixel(red, blue, green);
        part7Final.pixelVect.push_back(pixel);
    }
}
void Image::Overlay(Image &layer1, Image &pattern1, Image &part5Final) {
    part5Final = layer1;
    part5Final.pixelVect.clear();

    int imgSize = layer1.width * layer1.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    float redFloat;
    float blueFloat;
    float greenFloat;

    for (int i = 0; i < imgSize; i++) {
        float redA = (float)layer1.pixelVect[i].red/255;
        float redB = (float)pattern1.pixelVect[i].red/255;
        float blueA = (float)layer1.pixelVect[i].blue/255;
        float blueB = (float)pattern1.pixelVect[i].blue/255;
        float greenA = (float)layer1.pixelVect[i].green/255;
        float greenB = (float)pattern1.pixelVect[i].green/255;

        // Red Function
        if(redB <= 0.5){
            redFloat = 2*redA*redB;
        }else{
            redFloat = 1-(2*(1-redA)*(1-redB));
        }

        //Blue Function
        if(blueB <= 0.5){
            blueFloat = 2*blueA*blueB;
        }else{
            blueFloat = 1-(2*(1-blueA)*(1-blueB));
        }

        //Green Function
        if(greenB <= 0.5){
            greenFloat = 2*greenA*greenB;
        }else{
            greenFloat = 1-(2*(1-greenA)*(1-greenB));
        }

        red = (unsigned char) lround(redFloat * 255);
        blue = (unsigned char) lround(blueFloat * 255);
        green = (unsigned char) lround(greenFloat * 255);

        Image::Pixels pixel(red, blue, green);
        part5Final.pixelVect.push_back(pixel);
    }
}
void Image::Red(Image &car, Image &part8_RFinal){
    part8_RFinal = car;
    part8_RFinal.pixelVect.clear();

    int imgSize = car.width * car.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for(int i=0; i<imgSize; i++){
        red = car.pixelVect[i].red;
        green = car.pixelVect[i].red;
        blue = car.pixelVect[i].red;

        Image::Pixels pixel(red, blue, green);
        part8_RFinal.pixelVect.push_back(pixel);
    }
}
void Image::Blue(Image &car, Image &part8_BFinal){
    part8_BFinal = car;
    part8_BFinal.pixelVect.clear();

    int imgSize = car.width * car.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for(int i=0; i<imgSize; i++){
        red = car.pixelVect[i].blue;
        green = car.pixelVect[i].blue;
        blue = car.pixelVect[i].blue;

        Image::Pixels pixel(red, blue, green);
        part8_BFinal.pixelVect.push_back(pixel);
    }
}
void Image::Green(Image &car, Image &part8_GFinal){
    part8_GFinal = car;
    part8_GFinal.pixelVect.clear();

    int imgSize = car.width * car.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for(int i=0; i<imgSize; i++){
        red = car.pixelVect[i].green;
        green = car.pixelVect[i].green;
        blue = car.pixelVect[i].green;

        Image::Pixels pixel(red, blue, green);
        part8_GFinal.pixelVect.push_back(pixel);
    }
}
void Image::Combine(Image &layer_red, Image &layer_blue, Image &layer_green, Image &part9Final){
    part9Final = layer_blue;
    part9Final.pixelVect.clear();

    int imgSize = layer_blue.width * layer_blue.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for(int i=0; i<imgSize; i++) {
        red = layer_red.pixelVect[i].red;
        green = layer_green.pixelVect[i].green;
        blue = layer_blue.pixelVect[i].blue;

        Image::Pixels pixel(red, blue, green);
        part9Final.pixelVect.push_back(pixel);
    }
}
void Image::Rotate(Image &text2, Image &part10Final){
    part10Final = text2;
    part10Final.pixelVect.clear();

    int imgSize = text2.width * text2.height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    for(int i=imgSize-1; i>=0; i--) {
        red = text2.pixelVect[i].red;
        green = text2.pixelVect[i].green;
        blue = text2.pixelVect[i].blue;

        Image::Pixels pixel(red, blue, green);
        part10Final.pixelVect.push_back(pixel);
    }
}