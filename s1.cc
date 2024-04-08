//
// Anthony Poon
// Computational Vision Homework 4
// Program 1
// Program to calculate center and radius of object based on horizontal and vertical diameters

#include "image.h"
#include "DisjSets.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <climits>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;


 // @brief Implementation of Task Program 1 to compute sphere params
 //  
 // @param input_sphere_filename the name of the input sphere image
 // @param threshold threshold for binarization
 // @param output_params_filename the name of file to store X0 Y0 radius
void ComputeAndSaveSphereParametrs(const string &input_sphere_filename, int threshold, const string &output_params_filename) {
  cout << "Computing Sphere Parameters" << endl;
  cout << "Input filename: " << input_sphere_filename << endl;
  cout << "Threshold: " << threshold << endl;
  cout << "Output filename: " << output_params_filename << endl;

  Image image;
  if (!ReadImage(input_sphere_filename, &image)) {
    cout <<"Can't open file " << input_sphere_filename << endl;
    return;
  }

  // Number of rows and columns in the image
  size_t max_rows = image.num_rows();
  size_t max_cols = image.num_columns();

  int sum_rows = 0;
  int sum_cols = 0;
  int area = 0;
  int leftmost_x = max_rows;
  int rightmost_x = 0;
  int uppermost_y = max_cols;
  int lowermost_y = 0;

  // Sets pixel to black or white depending on its relation to the threshold
  for (int i = 0; i < max_rows; i++){
    for (int j = 0; j < max_cols; j++){
      if (image.GetPixel(i, j) >= threshold) {
        // Find sums to find centroid
        sum_rows += i;
        sum_cols += j;
        area++;

        // Find minimums and maximums to calculate radius
        leftmost_x = i < leftmost_x ? i : leftmost_x;
        rightmost_x = i > rightmost_x ? i : rightmost_x;
        lowermost_y = j > lowermost_y ? j : lowermost_y;
        uppermost_y = j < uppermost_y ? j : uppermost_y;
      }
    }
  }

  // Find average of each point's coordinates
  double center_x = double(sum_rows)/area;
  double center_y = double(sum_cols)/area;

  // Find half of the average of horizontal and vertical diameter to find radius
  int horizontal_diameter = rightmost_x - leftmost_x;
  int vertical_diameter = lowermost_y - uppermost_y;
  double diameter = double(horizontal_diameter + vertical_diameter)/2;
  double radius = diameter/2;

  string output = to_string(center_x) + " ";
  output += to_string(center_y) + " " + to_string(radius);

  ofstream file(output_params_filename);
  file << output;
  file.close();
}

int main(int argc, char **argv){  
  if (argc != 4) {
    printf("Usage: %s {input original image} {input threshold value} {output parameters file}\n", argv[0]);
    return 0;
  }
  
  const string input_filename(argv[1]);
  const int threshold = atoi(argv[2]);
  const string output_params_filename(argv[3]);

  ComputeAndSaveSphereParametrs(input_filename, threshold, output_params_filename);

  return 0;
}
