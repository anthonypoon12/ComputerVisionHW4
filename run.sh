rm output.txt output2.txt
make all
# ./s1 ImagesForHW4/sphere0.pgm 89 output.txt
# ./s2 output.txt ImagesForHW4/sphere1.pgm ImagesForHW4/sphere2.pgm ImagesForHW4/sphere3.pgm output2.txt
./s3 output2.txt ImagesForHW4/sphere1.pgm ImagesForHW4/sphere2.pgm ImagesForHW4/sphere3.pgm 10 87 output_normals.pgm output_albedo.pgm
make clean