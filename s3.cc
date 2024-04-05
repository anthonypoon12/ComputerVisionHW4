//
// Anthony Poon
// Computational Vision Homework 3
// Program 3
//

#include "image.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ComputerVisionProjects;

double findAdjoin(vector<vector<double>> matrix, int rowNum, int colNum);

// Make sure matrix is square
double findDeterminant(vector<vector<double>> matrix) {
  if (matrix.size() == 1) {
    return matrix[0][0];
  }
  if (matrix.size() == 2){
    double left_diagonal = matrix[0][0] * matrix[1][1];
    double right_diagonal = matrix[0][1] * matrix[1][0];
    return left_diagonal - right_diagonal;
  }
  else {
    double sum = 0;
    // Use first row
    for (int j = 0; j < matrix[0].size(); j++) {
      int subtract = j % 2 == 0 ? 1 : -1;
      sum += matrix[0][j] * subtract * findAdjoin(matrix, 0, j); 
    }
    return sum;
  }
}

double findAdjoin(vector<vector<double>> matrix, int rowNum, int colNum) {
  vector<vector<double>> shortened_matrix;
  for (int i = 0; i < matrix.size(); i++) {
    vector<double> row;
    for (int j = 0; j < matrix[i].size(); j++) {
      if (i != rowNum && j != colNum)
        row.push_back(matrix[i][j]);
    }
    if (row.size() > 0)
      shortened_matrix.push_back(row);
  }
  return findDeterminant(shortened_matrix);
}

// Make sure determinant is not 0
vector<vector<double>> findInverse(vector<vector<double>> matrix) {
  double determinant = findDeterminant(matrix);

  vector<vector<double>> transverse(3, vector<double>(3));
  vector<vector<double>> adjoint(3, vector<double>(3));
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      adjoint[i][j] = findAdjoin(matrix, i, j)/determinant;
      if ((i+j) % 2 != 0) {
        adjoint[i][j] = adjoint[i][j] * -1;
      }

    }
  }
  
  for (int i = 0; i < adjoint.size(); i++) {
    for (int j = 0; j < adjoint[i].size(); j++) {
      transverse[j][i] = adjoint[i][j];
    }
  }
  return transverse;

}


// Make sure m1xn and nxm2
vector<vector<double>> matrixMultiplication(vector<vector<double>> matrixA, vector<vector<double>> matrixB) {
  vector<vector<double>> output;
  // For every row in matrix A
  for (int matrix_A_row = 0; matrix_A_row < matrixA.size(); matrix_A_row++) {
    vector<double> row;

    // For every column in matrix B
    for (int matrix_B_col = 0; matrix_B_col < matrixB[0].size(); matrix_B_col++) {
      double sum = 0;
      for (int i = 0; i < matrixA[0].size(); i++) {
        double matrix_A_val = matrixA[matrix_A_row][i];
        double matrix_B_val = matrixB[i][matrix_B_col];
        sum += matrix_A_val * matrix_B_val;
      }
      row.push_back(sum);
    }
    output.push_back(row);
  }
  return output;
}

// @brief Computes Normals and Albedos
// @param input_directions_filename the name of the input directions filename (as computed from s2)
// @param input_object_filenames the names of the the three object files
// @param step the step parameter (for skipping in normal visualization)
// @param threshold the threshold parameter (for determining bright pixels)
// @param output_normals_filename the name of output normals image
// @param output_albedos_filename the name of output albedos image
void ComputeAndSaveNormalsAndAlbedoImages(const string &input_directions_filename, const array<string,3> &input_object_filenames, int step, int threshold,
                                          const string &output_normals_filename, const string &output_albedos_filename) {
  cout << "Compute Normals and Albedos using Photometric Stereo" << endl;
  cout << "Input directions filename: " << input_directions_filename << endl;
  cout << "Object image filename 1: " << input_object_filenames[0] << endl;
  cout << "Object image filename 2: " << input_object_filenames[1] << endl;
  cout << "Object image filename 3: " << input_object_filenames[2] << endl;
  cout << "Step parameter: " << step << endl;
  cout << "Threshold parameter: " << threshold << endl;
  cout << "Output normals filename: " << output_normals_filename << endl;
  cout << "Output albedos filename: " << output_albedos_filename << endl;

  vector<vector<double>> sources;
  ifstream file(input_directions_filename);
  string line;
  while(getline(file, line, '\n')) {
    string num;
    vector<double> row;
    stringstream ss(line);
    while (getline(ss, num, ' ')) {
      row.push_back(stod(num));
    }
    sources.push_back(row);
  }
  file.close();

  vector<Image> images;
  for (string filename: input_object_filenames) {
    Image image;
    if (!ReadImage(filename, &image)) {
      cout <<"Can't open file " << filename << endl;
      return;
    }
    images.push_back(image);
  }

  vector<vector<int>> points;
  size_t max_rows = images[0].num_rows();
  size_t max_cols = images[0].num_columns();

// Get all pixels above threshold in all three images
  for (int i = 0; i < max_rows; i++) {
  for (int j = 0; j < max_cols; j++) {
    if (images[0].GetPixel(i, j) >= threshold){
      if (images[1].GetPixel(i, j) >= threshold) {
        if (images[2].GetPixel(i, j) >= threshold) {
          vector<int> point{i, j};
          points.push_back(point);
        }
      }
    }
  }
}

}

int main(int argc, char **argv){
  if (argc != 9) {
    printf("Usage: %s  {input directions filename} {object 1 filename} {object 2 filename} {object 3 filename} {step} {threshold} {output normals filename} {output albedos filename}\n", argv[0]);
    return 0;
  }
  
  const string input_directions_filename{argv[1]};
  const array<string, 3> input_object_filenames{string{argv[2]}, string{argv[3]}, string{argv[4]}};
  const int step = atoi(argv[5]);
  const int threshold = atoi(argv[6]);
  const string output_normals_filename{argv[7]};
  const string output_albedos_filename{argv[8]};
  
  ComputeAndSaveNormalsAndAlbedoImages(input_directions_filename, input_object_filenames, step, threshold, output_normals_filename, output_albedos_filename);
  
  return 0;
}
