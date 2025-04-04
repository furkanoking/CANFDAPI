echo "removing the old build folder"
rm -rf ../build

echo "Creating new build folder"
mkdir ../build 
cd ../build

echo "Cmake is in progress"
cmake ../

echo "In compiling"
make -j${nproc}

echo "It is finished"