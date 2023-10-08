#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char result[SIZE][SIZE];

void loadImage () {
  char imageFileName[100];
  cout << "Enter the source image file name: ";
  cin >> imageFileName;
  strcat (imageFileName, ".bmp");
  readGSBMP(imageFileName, image);
}

void saveImage () {
  char imageFileName[100];
  cout << "Enter the target image file name: ";
  cin >> imageFileName;
  strcat (imageFileName, ".bmp");
  writeGSBMP(imageFileName, result);
}

void B_and_W() {
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++){
      if (image[i][j] > 127)
        result[i][j] = 255;
      else
        result[i][j] = 0;
    }
}

void Inv(){
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      result[i][j] = 255 - image[i][j];
  
}

void Mer(){
  char imageFileName[100];
  cout << "Please enter name of image file to merge with: ";
  cin >> imageFileName;
  strcat (imageFileName, ".bmp");
  readGSBMP(imageFileName, image2);

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      result[i][j] = (image[i][j] + image2[i][j]) / 2;
}

void Flip(){
  cout << "Flip (h)orizontally or (v)ertically ? ";
  char op;
  cin >> op;
  if(op == 'h')
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        result[i][j] = image[i][SIZE-j-1];
    
  else if(op == 'v')
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        result[i][j] = image[SIZE-i-1][j];
}

void Rotate(){
  cout << "Rotate (90), (180) or (270) degrees? ";
  int op;
  cin >> op;
  op = op / 90;//number of rotations
  // unsigned char temp[SIZE][SIZE];

  while (op--)
  {
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        result[j][SIZE-i-1] = image[i][j];
    
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        image[i][j] = result[i][j];
     
  }
}

void D_and_L(){
  cout << "Do you want to (d)arken or (l)ighten? ";
  char op;
  cin >> op;//if user chose darken marge image with balck color
    for (int i = 0; i < SIZE; i++)//and if he chose lighten image marge with white color
      for (int j = 0; j < SIZE; j++)
        result[i][j] = (op == 'd') ? image[i][j] / 2 :  (image[i][j] + 255) / 2;

}

//Detected image
void det(){
  long long avr = 0;
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++){
      avr += image[i][j];
    }
  avr /= (256*256);
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++){
      if(((image[i][j] - avr) * (image[i+1][j] - avr) < 0) || ((image[i][j] - avr) * (image[i][j+1] - avr) < 0))
        result[i][j] = 0;
      else 
        result[i][j] = 255;
    }
}
int main()
{
  cout << "Ahlan ya user ya habibi\n";
  loadImage();
  cout << "Please select a filter to apply or 0 to exit:\n";
  cout << "1- Black & White Filter\n";
  cout << "2- Invert Filter\n";
  cout << "3- Merge Filter\n";
  cout << "4- Flip Image\n";
  cout << "5- Rotate Image\n";
  cout << "6- Darken and Lighten Image\n";
  cout << "7- Detect Image Edges\n";
  cout << "0- To exit\n";
  int op;
  cin >> op;
  if(op == 1)
    B_and_W();
  else if(op == 2)
    Inv();
  else if(op == 3)
    Mer();
  else if(op == 4)
    Flip();
  else if(op == 5)
    Rotate();
  else if(op == 6)
    D_and_L();
  else if(op == 7)
    det();
  else if(op == 0)
    return 0;



  saveImage();
}