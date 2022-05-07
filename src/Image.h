//
// Created by Luke Cutting on 3/21/22.
//

#ifndef PROJECT2_IMAGE_H
#define PROJECT2_IMAGE_H
#include <iostream>
#include <vector>
using namespace std;


struct Image {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    struct Pixels{
        unsigned char red;
        unsigned char blue;
        unsigned char green;
        Pixels();
        Pixels(unsigned char red, unsigned char blue, unsigned char green);
    };

    vector<Pixels> pixelVect;
    Image();
    Image(char &idLength, char &colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength,
          char colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel, char imageDescriptor);

    void GetDataFromFile(const string& filePath, Image &header);
    void WriteDataFromFile(const string& filePath, Image &header);
    static bool Test(Image image, Image example);
    static void Multiply(Image &layer1, Image &pattern1, Image &part1Final);
    static void Subtract(Image &layer2, Image &car, Image &part2Final);
    static void Blend(Image &text, Image &part3Temp, Image &part3Final);
    static void AddGreen(Image &car, Image &part6Final);
    static void ScaleRedBlue(Image &car, Image &part7Final);
    static void Overlay(Image &layer1, Image &pattern1, Image &part5Final);
    static void Red(Image &car, Image &part8_RFinal);
    static void Blue(Image &car, Image &part8_BFinal);
    static void Green(Image &car, Image &part8_GFinal);
    static void Combine(Image &layer_red, Image &layer_blue, Image &layer_green, Image &part9Final);
    static void Rotate(Image &text2, Image &part10Final);
};


#endif //PROJECT2_IMAGE_H
