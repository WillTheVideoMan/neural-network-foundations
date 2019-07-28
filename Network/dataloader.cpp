#include "dataloader.hpp"

//loads the MNIST training data
DataSet<NumberData> loadMNISTTraining(bool showProgress, int start, int size) {
  return loadMNIST(showProgress, "train", start, size);
}

//load in all the MNIST training data
DataSet<NumberData> loadMNISTTraining(bool showProgress) {
  return loadMNISTTraining(showProgress, 0, 60000);
}

//loads the MNIST test data
DataSet<NumberData> loadMNISTTest(bool showProgress, int start, int size) {
  return loadMNIST(showProgress, "t10k", start, size);
}

//load in all the MNIST test data
DataSet<NumberData> loadMNISTTest(bool showProgress) {
  return loadMNISTTest(showProgress, 0, 10000);
}

//this method loads in the data from the MNIST database
DataSet<NumberData> loadMNIST(bool showProgress, std::string path, int start, int size) {

  const int res = 28; //all MNIST images have a resolution of 28x28

  const std::string imagePath = "../data/MNIST/" + path + "-images.idx3-ubyte";
  const std::string labelPath = "../data/MNIST/" + path + "-labels.idx1-ubyte";

  std::ifstream images(imagePath, std::ifstream::binary);
  std::ifstream labels(labelPath, std::ifstream::binary);

  if (!images.is_open() || !labels.is_open()) {
    std::cout << "\nError: failed to load MNIST data\n";
    return DataSet<NumberData>();
  }

  //skip magic number
  images.ignore(4);

  //get image count, stored as 32 bit integer so requires next 4 bytes
  int imageCount;
  images.read(reinterpret_cast<char*>(&imageCount), sizeof(int));
  imageCount = std::min(imageCount - start, size);

  //skip rest to labels and pixels
  images.ignore(8);
  labels.ignore(8);

  //skip images to start index
  images.ignore(res * res * start);
  labels.ignore(start);

  //the set of data
  DataSet<NumberData> data(imageCount);

  //get the length of the buffer as a const
  const int pixelCount = res * res;

  //create buffer to load data
  char buffer[pixelCount];

  //create vector to store pixels in form used by network
  Vector pixels(pixelCount);

  //main loop where all the images are loaded
  for (int j = 0; j < imageCount; j++) {
    if (showProgress && j % 101 == 0) std::cout << "\r" << j << "/" << imageCount << " images loaded";

    images.read(buffer, pixelCount);

    for (int i = 0; i < pixelCount; i++) {
      pixels[i] = ((double)buffer[i]);
      if (pixels[i] < 0) pixels[i] += 255;
      pixels[i] /= 255.0;
    }
    data[j] = NumberData(pixels, (int)labels.get());
  }

  images.close();
  labels.close();

  if (showProgress) std::cout << "\r" << imageCount << "/" << imageCount << " images loaded\n";
  return data;
}