//
// Anthony Poon
// Computational Vision Homework 4
// Program 2
//

#include "image.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;


// @brief Implementation of Program 2 to compute light source directions
// @param input_params filename the name of the input file containing X0 Y0 radius
// @param input_sphere_filenames the names of the the three sphere files
// @param output_directions_filename the name of the output directions filename
void ComputeAndSaveDirections(const string &input_params_filename, const array<string,3> &input_sphere_filenames,
                              const string &output_directions_filename) {
  cout << "Compute And Save Directions" << endl;
  cout << "Input params filename: " << input_params_filename << endl;
  cout << "Sphere image filename 1: " << input_sphere_filenames[0] << endl;
  cout << "Sphere image filename 2: " << input_sphere_filenames[1] << endl;
  cout << "Sphere image filename 3: " << input_sphere_filenames[2] << endl;
  cout << "Output directions filename: " << output_directions_filename << endl;

  ifstream file(input_params_filename);
  double center_x;
  double center_y;
  double radius;
  file >> center_x >> center_y >> radius;
  file.close();

  string output_string = "";

  for (string filename: input_sphere_filenames) {
    Image image;
    if (!ReadImage(filename, &image)) {
      cout <<"Can't open file " << filename << endl;
      return;
    }

    // Number of rows and columns in the image
    size_t max_rows = image.num_rows();
    size_t max_cols = image.num_columns();

    int max_brightness = 0;
    int bright_x = 0;
    int bright_y = 0;

    // Find brightest point in each image
    for (int i = 0; i < max_rows; i++) {
      for (int j = 0; j < max_cols; j++) {
        int brightness = image.GetPixel(i, j);
        if (brightness > max_brightness) {
          max_brightness = brightness;
          bright_x = i;
          bright_y = j;
        }
      }
    }

    // Calculate for normal vector
    double normal_x = bright_x - center_x;
    double normal_y = bright_y - center_y;
    double squared_z = radius*radius - normal_x*normal_x - normal_y*normal_y;
    double normal_z = sqrt(squared_z);
    cout << center_x << " " << center_y << " " << radius << endl;
    double distance = sqrt(normal_x*normal_x + normal_y*normal_y + squared_z);

    // Use brightness as length
    output_string += to_string(normal_x/distance*max_brightness) + " ";
    output_string += to_string(normal_y/distance*max_brightness) + " ";
    output_string += to_string(normal_z/distance*max_brightness) + "\n";
  }

  ofstream output_file(output_directions_filename);
  output_file << output_string;
  output_file.close();
}

int main(int argc, char **argv){  
  if (argc != 6) {
    printf("Usage: %s  {input parameters file} {image 1} {image 2} {image 3} {output directions file}\n", argv[0]);
    return 0;
  }

  const string input_params_filename(argv[1]);
  const array<string, 3> input_sphere_filenames{string{argv[2]}, string{argv[3]}, string{argv[4]}};
  const string output_directions_filename(argv[5]);

  ComputeAndSaveDirections(input_params_filename, input_sphere_filenames, output_directions_filename);

  return 0;
}
