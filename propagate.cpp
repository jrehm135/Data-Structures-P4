// implement the propagate application here
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "heap_priority_queue.h"
#include "image.h"

struct speedval
{
	int red;
	int green;
	int blue;
	int total;
	//initializes the values of each speed color, and creates a total value to compare
	int locx;
	int locy;
	//stores the x and y values of its pixels
	friend bool operator<(speedval& left, speedval& right)
	{
		return left.total < right.total;
	}
	friend bool operator>(speedval& left, speedval& right)
	{
		return left.total > right.total;
	}
	friend bool operator<=(speedval& left, speedval& right)
	{
		return left.total <= right.total;
	}
	friend bool operator>=(speedval& left, speedval& right)
	{
		return left.total >= right.total;
	}
	friend bool operator==(speedval& left, speedval& right)
	{
		return left.total == right.total;
	}
	//creates overloaded comparison operators for the struct
};

int main(int argc, char *argv[])
{
	if (argc != 5) {
		std::cout << "Usage: propagate.exe"
			<< "<initial interface> <speed> <output interface> <number of time steps>\n"
			<< std::endl;
		return EXIT_FAILURE;
		//If there are not the right number of arguments, the program exits
	}
	else
	{
		try
		{
			Image<Pixel> initial = readFromFile(argv[1]);
			Image<Pixel> speed = readFromFile(argv[2]);
			//reads the names of the initial and speed file in

			if ((initial.width() != speed.width()) || (initial.height() != speed.height()))
			{
				std::cerr << "Width and Height do not match";
				return EXIT_FAILURE;
				//if the files are not the same size, exits program
			}
			std::ifstream f(argv[3]);
			if (!f.good())
			{
				std::cerr << "No output file";
				return EXIT_FAILURE;
				//if the output file doesn't exist, exits the program
			}

			Image<Pixel> output = initial;
			//sets the value of output to the same as input to start
			speedval vel;
			int steps = atoi(argv[4]);
			//creates a struct vel and converts the number of steps to an integer

			if (steps <= 0)
			{
				std::cerr << "Invalid time step value";
				return EXIT_FAILURE;
				//if atoi returns false(0), or the number returned is negative, exits program
			}
			HeapPriorityQueue<speedval> location;
			//creates a queue to store the location

			for (unsigned int i = 0; i < initial.width(); ++i)
				for (unsigned int j = 0; j < initial.height(); ++j) {
					//Goes through each value in the initial picture and checks to see if it is black
					if (initial(i, j).red == 0 && initial(i, j).green == 0 && initial(i, j).blue == 0)
					{
						vel.red = speed(i, j).red;
						vel.green = speed(i, j).green;
						vel.blue = speed(i, j).blue;
						vel.total = vel.red + vel.green + vel.blue;
						//stores the speed color values
						vel.locx = i;
						vel.locy = j;
						//stores the location of the pixel

						i++;
						if (initial(i, j).red == 255 && initial(i, j).green == 255 && initial(i, j).blue == 255)
						{
							vel.red = speed(i, j).red;
							vel.green = speed(i, j).green;
							vel.blue = speed(i, j).blue;
							vel.total = vel.red + vel.green + vel.blue;
							location.add(vel);
							//If the pixel to the right is white, adds it to the heap
						}
						i -= 2;
						if (initial(i, j).red == 255 && initial(i, j).green == 255 && initial(i, j).blue == 255)
						{
							vel.red = speed(i, j).red;
							vel.green = speed(i, j).green;
							vel.blue = speed(i, j).blue;
							vel.total = vel.red + vel.green + vel.blue;
							location.add(vel);
							//If the pixel to the left is white, adds it to the heap
						}
						i++;
						j++;
						if (initial(i, j).red == 255 && initial(i, j).green == 255 && initial(i, j).blue == 255)
						{
							vel.red = speed(i, j).red;
							vel.green = speed(i, j).green;
							vel.blue = speed(i, j).blue;
							vel.total = vel.red + vel.green + vel.blue;
							location.add(vel);
							//If the pixel below is white, adds it to the heap
						}
						j -= 2;
						if (initial(i, j).red == 255 && initial(i, j).green == 255 && initial(i, j).blue == 255)
						{
							vel.red = speed(i, j).red;
							vel.green = speed(i, j).green;
							vel.blue = speed(i, j).blue;
							vel.total = vel.red + vel.green + vel.blue;
							location.add(vel);
							//If the pixel above is white, adds it to the heap
						}
						j++;
					}
					else if (initial(i, j).red == 255 && initial(i, j).green == 255 && initial(i, j).blue == 255)
					{
					}
					else 
					{
						std::cerr << "Non B/W pixel found";
						return EXIT_FAILURE;
						//if there are pixels that are not black or white, exits program
					}
				}
			for (int i = 0; i < steps && !location.isEmpty(); i++)
			{
				//iterates until there are no more steps left or the heap is empty
				speedval pixel = location.peek();

				output(pixel.locx, pixel.locy).red = 0;
				output(pixel.locx, pixel.locy).green = 0;
				output(pixel.locx, pixel.locy).blue = 0;
				//turns the selected pixel black

				pixel.locx++;
				if (output(pixel.locx, pixel.locy).red != 0 && output(pixel.locx, pixel.locy).green != 0 && output(pixel.locx, pixel.locy).blue != 0)
				{
					pixel.red = speed(pixel.locx, pixel.locy).red;
					pixel.green = speed(pixel.locx, pixel.locy).green;
					pixel.blue = speed(pixel.locx, pixel.locy).blue;
					pixel.total = pixel.red + pixel.green + pixel.blue;
					location.add(pixel);
					//If the pixel to the right is white, adds it to the heap
				}

				pixel.locx -= 2;
				if (output(pixel.locx, pixel.locy).red != 0 && output(pixel.locx, pixel.locy).green != 0 && output(pixel.locx, pixel.locy).blue != 0)
				{
					pixel.red = speed(pixel.locx, pixel.locy).red;
					pixel.green = speed(pixel.locx, pixel.locy).green;
					pixel.blue = speed(pixel.locx, pixel.locy).blue;
					pixel.total = pixel.red + pixel.green + pixel.blue;
					location.add(pixel);
					//If the pixel to the left is white, adds it to the heap
				}

				pixel.locx++;
				pixel.locy++;
				if (output(pixel.locx, pixel.locy).red != 0 && output(pixel.locx, pixel.locy).green != 0 && output(pixel.locx, pixel.locy).blue != 0)
				{
					pixel.red = speed(pixel.locx, pixel.locy).red;
					pixel.green = speed(pixel.locx, pixel.locy).green;
					pixel.blue = speed(pixel.locx, pixel.locy).blue;
					pixel.total = pixel.red + pixel.green + pixel.blue;
					location.add(pixel);
					//If the pixel below is white, adds it to the heap
				}

				pixel.locy -= 2;
				if (output(pixel.locx, pixel.locy).red != 0 && output(pixel.locx, pixel.locy).green != 0 && output(pixel.locx, pixel.locy).blue != 0)
				{
					pixel.red = speed(pixel.locx, pixel.locy).red;
					pixel.green = speed(pixel.locx, pixel.locy).green;
					pixel.blue = speed(pixel.locx, pixel.locy).blue;
					pixel.total = pixel.red + pixel.green + pixel.blue;
					location.add(pixel);
					//If the pixel above is white, adds it to the heap
				}

				pixel.locy++;
				location.remove();
				//removes the original pixel

			}
			writeToFile(output, argv[3]);
			return EXIT_SUCCESS;
			//if the program writes to the file, exits program successfully
		}
		catch (std::runtime_error)
		{
			std::cerr << "Invalid file parameters";
			return EXIT_FAILURE;
			//If one of the input files cannot be found, exits program
		}
		catch (std::out_of_range)
		{
			std::cerr << "Pixel outside image boundaries";
			return EXIT_FAILURE;
			//If one of the pixels outside the image is accessed, exits program
		}
	}
}