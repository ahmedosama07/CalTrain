#!/bin/bash                                                                     
                                                                                
# Directory containing test folders                                             
testing_folder="test"                                                           
build_folder="build"
mkdir $testing_folder
for i in {1..1000}
do
  echo "Test(" $i ") ................................................. :-" >> $testing_folder/final_result.out
  ./$build_folder/caltrain >> $testing_folder/final_result.out
done