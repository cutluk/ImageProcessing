#include <iostream>
#include "Image.h"

using namespace std;

int main() {
    // Part 1
    // Use the Multiply blending mode to combine “layer1.tga” (top layer) with “pattern1.tga” (bottom layer).
    Image layer1;
    Image pattern1;
    Image part1Final;

    layer1.GetDataFromFile("input/layer1.tga", layer1);
    pattern1.GetDataFromFile("input/pattern1.tga", pattern1);

    Image::Multiply(layer1, pattern1, part1Final);
    part1Final.WriteDataFromFile("output/part1.tga", part1Final);

    Image test1;
    test1.GetDataFromFile("examples/EXAMPLE_part1.tga", test1);
    bool part1 = Image::Test(part1Final, test1);
    if(part1){
        cout << "Test #1...... Passed!" << endl;
    }else{
        cout << "Test #1...... Failed!" << endl;
     }

    // Part 2
    // Use the Subtract blending mode to combine “layer2.tga” (top layer) with “car.tga” (bottom layer). This mode subtracts the top layer from the bottom layer.
    Image layer2;
    Image car;
    Image part2Final;

    layer2.GetDataFromFile("input/layer2.tga", layer1);
    car.GetDataFromFile("input/car.tga", car);

    Image::Subtract(layer2, car, part2Final);
    part2Final.WriteDataFromFile("output/part2.tga", part2Final);

    Image test2;
    test2.GetDataFromFile("examples/EXAMPLE_part2.tga", test2);
    bool part2 = Image::Test(part2Final,test2);
    if(part2){
        cout << "Test #2...... Passed!" << endl;
    }else{
        cout << "Test #2...... Failed!" << endl;
    }

    // Part 3
    // Use the Multiply blending mode to combine “layer1.tga” with “pattern2.tga”, and store the results temporarily.
    // Load the image “text.tga” and, using that as the top layer, combine it with the previous results of layer1/pattern2 using the Screen blending mode.

    Image pattern2;
    Image part3Temp;
    Image part3Final;
    Image text;

    layer1.GetDataFromFile("input/layer1.tga", layer1);
    pattern2.GetDataFromFile("input/pattern2.tga", pattern2);
    Image::Multiply(layer1, pattern2, part3Temp);

    text.GetDataFromFile("input/text.tga", text);
    Image::Blend(text, part3Temp, part3Final);

    part3Final.WriteDataFromFile("output/part3.tga", part3Final);

    Image test3;
    test3.GetDataFromFile("examples/EXAMPLE_part3.tga", test3);
    bool part3 = Image::Test(part3Final,test3);
    if(part3){
        cout << "Test #3...... Passed!" << endl;
    }else{
        cout << "Test #3...... Failed!" << endl;
    }

    // Part 4
    // Multiply “layer2.tga” with “circles.tga”, and store it.
    // Load “pattern2.tga” and, using that as the top layer, combine it with the previous result using the Subtract blending mode.

    Image circles;
    Image part4Temp;
    Image part4Final;

    layer1.GetDataFromFile("input/layer1.tga", layer1);
    circles.GetDataFromFile("input/circles.tga", circles);
    Image::Multiply(layer2, circles, part4Temp);

    pattern2.GetDataFromFile("input/pattern2.tga", pattern2);
    Image::Subtract(pattern2, part4Temp, part4Final);
    part4Final.WriteDataFromFile("output/part4.tga", part4Final);

    Image test4;
    test4.GetDataFromFile("examples/EXAMPLE_part4.tga", test4);
    bool part4 = Image::Test(part4Final,test4);
    if(part4){
        cout << "Test #4...... Passed!" << endl;
    }else{
        cout << "Test #4...... Failed!" << endl;
    }

    // Part 5
    // Combine “layer1.tga” (as the top layer) with “pattern1.tga” using the Overlay blending mode.

    Image part5Final;
    layer1.GetDataFromFile("input/layer1.tga", layer1);
    pattern1.GetDataFromFile("input/pattern1.tga", pattern1);

    Image::Overlay(layer1, pattern1, part5Final);
    part5Final.WriteDataFromFile("output/part5.tga", part5Final);

    Image test5;
    test5.GetDataFromFile("examples/EXAMPLE_part5.tga", test5);
    bool part5 = Image::Test(part5Final,test5);
    if(part5){
        cout << "Test #5...... Passed!" << endl;
    }else{
        cout << "Test #5...... Failed!" << endl;
    }

    // Part 6
    // Load “car.tga” and add 200 to the green channel.

    Image part6Final;

    car.GetDataFromFile("input/car.tga", car);
    Image::AddGreen(car, part6Final);
    part6Final.WriteDataFromFile("output/part6.tga", part6Final);

    Image test6;
    test6.GetDataFromFile("examples/EXAMPLE_part6.tga", test6);
    bool part6 = Image::Test(part6Final,test6);
    if(part6){
        cout << "Test #6...... Passed!" << endl;
    }else{
        cout << "Test #6...... Failed!" << endl;
    }

    // Part 7
    // Load “car.tga” and scale (multiply) the red channel by 4, and the blue channel by 0.
    // This will increase the intensity of any red in the image, while negating any blue it may have.

    Image part7Final;

    Image::ScaleRedBlue(car, part7Final);
    part7Final.WriteDataFromFile("output/part7.tga", part7Final);

    Image test7;
    test7.GetDataFromFile("examples/EXAMPLE_part7.tga", test7);
    bool part7 = Image::Test(part7Final,test7);
    if(part7){
        cout << "Test #7...... Passed!" << endl;
    }else{
        cout << "Test #7...... Failed!" << endl;
    }

    // Part 8
    // Load “car.tga” and write each channel to a separate file: the red channel should be “part8_r.tga”,
    // the green channel should be “part8_g.tga”, and the blue channel should be “part8_b.tga”
    // (Hint: If your red channel image appears all red, try writing [Red, Red, Red] instead of [Red, 0, 0] to the file—ditto for green and blue!)

    Image part8_RFinal;
    Image part8_BFinal;
    Image part8_GFinal;

    car.GetDataFromFile("input/car.tga", car);
    Image::Red(car, part8_RFinal);
    Image::Blue(car, part8_BFinal);
    Image::Green(car, part8_GFinal);
    part8_RFinal.WriteDataFromFile("output/part8_r.tga", car);
    part8_BFinal.WriteDataFromFile("output/part8_b.tga", car);
    part8_GFinal.WriteDataFromFile("output/part8_g.tga", car);

    Image test8_r;
    Image test8_b;
    Image test8_g;
    test8_r.GetDataFromFile("examples/EXAMPLE_part8_r.tga", test8_r);
    test8_b.GetDataFromFile("examples/EXAMPLE_part8_b.tga", test8_b);
    test8_g.GetDataFromFile("examples/EXAMPLE_part8_g.tga", test8_g);
    bool part8_r = Image::Test(part8_RFinal,test8_r);
    bool part8_b = Image::Test(part8_BFinal,test8_b);
    bool part8_g= Image::Test(part8_GFinal,test8_g);
    if(part8_r && part8_b && part8_g){
        cout << "Test #8...... Passed!" << endl;
    }else{
        cout << "Test #8...... Failed!" << endl;
    }

    // Part 9
    // Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga”, and combine the three files into one file.
    // The data from “layer_red.tga” is the red channel of the new image, layer_green is green, and layer_blue is blue.

    Image layer_red;
    Image layer_green;
    Image layer_blue;
    Image part9Final;

    layer_red.GetDataFromFile("input/layer_red.tga", layer_red);
    layer_blue.GetDataFromFile("input/layer_blue.tga", layer_blue);
    layer_green.GetDataFromFile("input/layer_green.tga", layer_green);

    Image::Combine(layer_red, layer_blue, layer_green, part9Final);
    part9Final.WriteDataFromFile("output/part9.tga", part9Final);

    Image test9;
    test9.GetDataFromFile("examples/EXAMPLE_part9.tga", test9);
    bool part9 = Image::Test(part9Final,test9);
    if(part9){
        cout << "Test #9...... Passed!" << endl;
    }else{
        cout << "Test #9...... Failed!" << endl;
    }

    // Part 10
    // Load “text2.tga”, and rotate it 180 degrees, flipping it upside down. This is easier than you think!
    // Try diagramming the data of an image (such as earlier in this document). What would the data look like if you flipped it?

    Image part10Final;
    Image text2;

    text2.GetDataFromFile("input/text2.tga", text2);
    Image::Rotate(text2, part10Final);
    part10Final.WriteDataFromFile("output/part10.tga", part10Final);

    Image test10;
    test10.GetDataFromFile("examples/EXAMPLE_part10.tga", test10);
    bool part10 = Image::Test(part10Final,test10);
    if(part10){
        cout << "Test #10...... Passed!" << endl;
    }else{
        cout << "Test #10...... Failed!" << endl;
    }
}