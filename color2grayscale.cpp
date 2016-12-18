/*
This code shows you an example of how to use the image library.

It is not part of the assignment.
*/
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "image.h"

int main(int argc, char *argv[]) {

  if (argc != 3) {
    std::cout << "Usage: color2grayscale"
              << "<input_filename> <output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  try {
    Image<Pixel> input = readFromFile(argv[1]);

    Image<Pixel> output = input;

    // convert each pixel to grayscale using RGB->YUV
    for (unsigned int i = 0; i < input.width(); ++i)
      for (unsigned int j = 0; j < input.height(); ++j) {
        uint8_t temp =
            (uint8_t)floor(0.299 * input(i, j).red + 0.587 * input(i, j).green +
                           0.114 * input(i, j).blue);
        output(i, j).red = temp;
        output(i, j).green = temp;
        output(i, j).blue = temp;
      }

    writeToFile(output, argv[2]);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
