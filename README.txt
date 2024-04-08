Anthony Poon
Computational Vision Homework 4

1. All four parts of the assignment have been completed.
2. Have some problems when ...
3. All programs runs as directed in assignment details.
4. Input files same as the ones provided.

Program_1 s1
    - Threshold used is: 89
    Using the user inputted threshold, this program finds the center of the object
    and radius based on the average of the vertical and horizontal diameter
    How to Use: ./s1 (input_image_file) (threshold) (output_text_file)

Program_2 s2
    - The formula used for computation of sphere normals was: 1/(N1^2+ N2^2+ N3^2) * {N1, N2, N3} = Unit normals
    The program uses the X and Y values of the brightest points of the three objects for its calculations
    The normal vector can be calculated with X -X0, Y - Y0, sqrt(radius^2 - (X-X0)^2 - (Y-Y0)^2) where X0 and Y0 represent the center of the circle
    We use the unit vector and scale it based on the value of the brightness
    Finally, we output to a text file
    How to Use: ./s2 (program_1_output_file) (input_object_file_1) (input_object_file_2) (input_object_file_3) (output_file)

Program_3 s3
    - the threshold used is: 87
    Using the output from Program 2, we find all albedo values for each pixel that's brightness is above the threshold in all three images
    We output these values in an image, scaled to the brightnesses of 0 to 255
    We find the values of the normal vector of the pixels in the object images, taking regular intervals based on the user inputted step parameter
    We find the unit normal vector and multiply the values by 10, drawing a line using these values
    Finally, we output an image displaying these needles.
    How to Use: ./s3 (program_2_output_file) (input_object_file_1) (input_object_file_2) (input_object_file_3) (step_value) (threshold) (output_normal_file) (output_albedo_file)
