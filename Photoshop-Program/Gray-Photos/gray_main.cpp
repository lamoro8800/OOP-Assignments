#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char result[SIZE][SIZE];

void loadImage () {//this function to load the image
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage () {//this function to save the result image
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, result);
}


/*
1# Black and White Filter
The main idea is that if the pixel value is from 127 to 255, make it white. otherwise, make it white. 
*/
void B_and_W() {//
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++){
      if (image[i][j] > 127) 
        result[i][j] = 255;
      else
        result[i][j] = 0;
    }

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j];
}




/*
2# Invert Filter
The main idea is that we invert the pixel value and just make it equal (255 - pixel value).
*/
void Inv(){
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      result[i][j] = 255 - image[i][j];

  
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j]; 
}




/*
3# Merge Filter
The main idea is that we get the average of each of the two pixels value in image1 and image2
*/
void Mer(){
  char imageFileName[100];
  cout << "Please enter name of image file to merge with: ";
  cin >> imageFileName;
  strcat (imageFileName, ".bmp");
  readGSBMP(imageFileName, image2);

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      result[i][j] = (image[i][j] + image2[i][j]) / 2;//get avr of two pixels


  
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j];
}




// 4# Flip Image Filter
void Flip(){
  cout << "Flip (h)orizontally or (v)ertically ? ";
  char op;
  cin >> op;

    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        result[i][j] = (op == 'h' || op == 'H' ? image[i][SIZE-j-1] : image[SIZE-i-1][j] );


  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j];
}



/*
5# Rotate Image Filter
The main idea is that we get the number of rotations by dividing the degree by 90.
So for example, if the degree value is 90 now, we should rotate it just one time, and if it is 180, we should rotate it two times (2*90) and three times for 270 degrees (3*90).
*/
void Rotate(){
  cout << "Rotate (90), (180) or (270) degrees? ";
  int op;
  cin >> op;
  op = op / 90;//number of rotations

  while (op--)
  {
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        result[j][SIZE-i-1] = image[i][j];
    
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        image[i][j] = result[i][j];
  
  }

  
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j];
}



/*
6# Darken and Lighten Filter
The main idea is that to check if the user wants the image is lighted, we merge it with a white color according to this formula: (pixel value + 255)/2.
and if he wants it darkened, we merge it black according to this formula: (pixel value + 0)/2 --> pixel value / 2. 
*/
void D_and_L(){
  cout << "Do you want to (d)arken or (l)ighten? ";
  char op;
  cin >> op;//if user chose darken marge image with balck color
  for (int i = 0; i < SIZE; i++)//and if he chose lighten image marge with white color
    for (int j = 0; j < SIZE; j++)
      result[i][j] = (op == 'd') ? image[i][j] / 2 :  (image[i][j] + 255) / 2;

  
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j];
}




/*
7# Detect Image Edges Filter
The main idea is that we calculate the avrage (avr) of all pixels in the image by summating all pixel values and dividing it by the number of pixels (265*265).
and the itarate over all pixels If it is greater than (AVR) and one of the two her side pixels from right or down is less than (AVR), then I consider it a node, or if one of the two her side pixels from right or down is greater and our pixel is less than (AVR). else it is not a node.
*/
void detect(){
  long long AVR = 0;
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++){
      AVR += image[i][j];
    }
  AVR /= (256*256);
  
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++){
      if(((image[i][j] - AVR) * (image[i+1][j] - AVR) < 0) || ((image[i][j] - AVR) * (image[i][j+1] - AVR) < 0))
        result[i][j] = 0;
      else 
        result[i][j] = 255;
    }

  

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j];
}



/*
8# Enlarge Image filter
The main idea is that  we take the part that the user chose,double the size of one pixel,and put it into four pixels.
*/
void Enlarge(){
  int op;
  cout<<"Which quarter to enlarge 1, 2, 3 or 4 ? ";
  cin >> op;
  int x, y;
  if(op == 1)
      x = 0, y = 0;
  else if(op == 2)
      x = 0, y = 128;
  else if(op == 3)
      x = 128, y = 128;
  else if(op == 4)
      x = 128, y = 0;

  for (int i = 0; i < 256; i++)
      for (int j = 0; j < 256; j++)
          result[i][j] = image[x+i/2][y+j/2];


  for (int i = 0; i < SIZE; i++)
      for (int j = 0; j< SIZE; j++)
          image[i][j] = result[i][j];
}


/*
9# Shrink Image Filter
The main idea is that first we make the result image white and then get (avr) for each two pixels and put it in just one pixel, that's it
*/
void shrink(){
    string op;
    cout<<"shrink to (1/2), (1/3) or (1/4) ";
    cin >> op;
    int x = op[2]-'0';

    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 265; j++)
            result[i][j] = 255;

    int sum = 0;
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 265; j++){
            if(j%x == 0)sum = 0;
            sum += image[i][j];
            result[i/x][j/x] = sum/x;
        }

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            image[i][j] = result[i][j];
}

/*
10# Mirror Image Filter
The main idea is that we determine which half will be changed and make it equal to the reverse of another half. It is easy.
*/
void Mirror(){
  cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
  char op;
  int s1, s2, e1, e2;
  cin >> op;

  if(op == 'l')
    s1 = 0, e1 = 256, s2 = 128, e2 = 256;
  else if(op == 'r')
    s1 = 0, e1 = 256, s2 = 0, e2 = 128;
  else if(op == 'u')
    s1 = 128, e1 = 256, s2 = 0, e2 = 256;
  else if(op == 'd')
    s1 = 0, e1 = 128, s2 = 0, e2 = 256;
  
  for (int i = 0; i < 256; i++)
    for (int j = 0; j < 256; j++){
      if(i >= s1 && i < e1 && j >= s2 && j < e2){
        if(op == 'r' || op == 'l')
          result[i][j] = image[i][SIZE-j-1];
        else 
          result[i][j] = image[SIZE-i-1][j];
      }else{
        result[i][j] = image[i][j];
      }
      
      //This line can do the same thing instead of if and else.
      // result[i][j] = ((i >= s1 && i < e1 && j >= s2 && j < e2 ? op == 'r' || op == 'l' ? image[i][SIZE-j-1] : image[SIZE-i-1][j] : image[i][j]);
    }


  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j];
}




/*
11# shuffle image filter 
In this filter we assume the image into 4 parts .The user enters the order he wants to the parts in the new image.
*/
void shuffle() {
  cout << "New order of quarters ? ";
    int a, b, c, d;
    for (int l = 0; l < 4; l++) {
        cin >> a;
        if (l == 0) {
            b = 0, c = d = 0;
        }
        else if (l == 1) {
            b = 0, c = d = 128;
        }
        else if (l == 2) {
            b = 128, c = d = 0;
        }
        else {
            b = 128, c = d = 128;
        }
        if (a == 1) {
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    result[b][c] = image[i][j];
                    c++;
                }
                b++;
                c = d;
            }
        }
        else if (a == 2) {
            for (int i = 0; i < 128; i++) {
                for (int j = 128; j < SIZE; j++) {
                    result[b][c] = image[i][j];
                    c++;
                }
                b++;
                c = d;
            }
        }
        else if (a == 3) {
            for (int i = 128; i < SIZE; i++) {
                for (int j = 0; j < 128; j++) {
                    result[b][c] = image[i][j];
                    c++;
                }
                b++;
                c = d;
            }
        }
        else {
            for (int i = 128; i < SIZE; i++) {
                for (int j = 128; j < SIZE; j++) {
                    result[b][c] = image[i][j];
                    c++;
                }
                b++;
                c = d;
            }
        }
    }


    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j< SIZE; j++)
        image[i][j] = result[i][j];
}



/*
12# blur image
The main idea is that we collect each pixel and the pixels around it from every direction and divide the by their number, and the whole image is equal to the result.
*/
bool valid(int n,int y){
  return n>=0 && n<256 && y>=0 && y<256;
}
void blur(){

    int dx[]={1, 0, 0, -1, -1, 1, -1, 1};
    int dy[]={0, 1, -1, 0, 1, 1, -1, -1};

    for(int x=0;x<256;x++){
        for(int y=0;y<256;y++){
            int cnt=0;
            int sum=0,avr;
            for (int i = 0; i < 8; i++)
            {
                int nx = x+dx[i], ny = y+dy[i];
                if(valid(nx, ny)){
                    sum += image[nx][ny];
                    cnt++;
                }
            }
            sum += image[x][y]; cnt++;
            avr = sum/cnt;
            result[x][y] = avr;
        }
    }


    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j< SIZE; j++)
            image[i][j] = result[i][j];
}



/*
13# Crop Image Filter
The main idea is that we make the result image white and then scan (x, y) from the user and iterate from this point to make a rectangle with width = w and length = l.
*/
void crop(){
  cout << "Please enter x y l w: ";
  int x, y, l, w;
  cin >> x >> y >> l >> w;
  for (int i = 0; i < 256; i++)//make the image white
    for (int j = 0; j < 256; j++)
      result[i][j] = 255;

  //min(256, x+w) to check bounders
  for (int i = x; i < min(256, x+w); i++)
    for (int j = y; j < min(256, y+l); j++)
      result[i][j] = image[i][j];


  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j< SIZE; j++)
      image[i][j] = result[i][j];
}



/*
#14 Skew Horizontally
the main idea that we take the angle from user and 
*/
void skew_ho(){
  for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
          image2[i][j]=255;
          result[i][j]=255;
      }
  }
  double ang;
  cout<<"enter the angle : ";
  cin>>ang;
  ang = (ang * 22)/(180 * 7);
  int x = (int)SIZE / (1 + (1/tan(ang)));
  for(int i=0;i<SIZE;++i){
      for(int j=0;j<SIZE;++j){
          image2[i][ j * x / SIZE]=image[i][j];
      }
  }
  double step = SIZE - x;
  double move = step / SIZE;
  for(int i=0;i<SIZE;++i){
      for(int j=0;j<SIZE ;++j){
          result[i][(int)step+j]=image2[i][j];
      }
      step-=move;
  }
  for (int i = 0; i < SIZE; ++i)
      for (int j = 0; j< SIZE; ++j)
          image[i][j] = result[i][j];
}


/*
#15 Skew vertically

*/
void skew_ve(){
  for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
          image2[i][j]=255;
          result[i][j]=255;
      }
  }
  double ang;
  cout<<"enter the angle : ";
  cin>>ang;
  ang = (ang * 22)/(180 * 7);
  int x = (int)SIZE / (1 + (1/tan(ang)));
  for(int i=0;i<SIZE;++i){
      for(int j=0;j<SIZE;++j){
          image2[ i * x / SIZE][j]=image[i][j];
      }
  }
  double step = SIZE - x;
  double move = step / SIZE;
  for(int i=0;i<SIZE;++i){
      for(int j=0;j<SIZE ;++j){
          result[(int)step+i][j]=image2[i][j];
      }
      step-=move;
  }
  for (int i = 0; i < SIZE; ++i)
      for (int j = 0; j< SIZE; ++j)
          image[i][j] = result[i][j];

}

int main()
{
  cout << "Ahlan ya user ya habibi\n";
  loadImage();
  int op;
  do// the menu, from which the user can choose one of these options.
  {
    cout << "Please select a filter to apply or 0 to exit:\n";
    cout << "1- Black & White Filter\n";
    cout << "2- Invert Filter\n";
    cout << "3- Merge Filter\n";
    cout << "4- Flip Image\n";
    cout << "5- Rotate Image\n";
    cout << "6- Darken and Lighten Image\n";
    cout << "7- Detect Image Edges\n";
    cout << "8- Enlarge Image\n";
    cout << "9- Shrink Image\n";
    cout << "10- Mirror 1/2 Image\n";
    cout << "11- Shuffle Image\n";
    cout << "12- Blur Image\n";
    cout << "13- Crop Image\n";
    cout << "14- Skew the Image Horizontally\n";
    cout << "15- Skew the Image vertically\n";
    cout << "16- Save the image to a file\n";
    cout << "0- Exit\n";


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
      detect();
    else if(op == 8)
      Enlarge();
    else if(op == 9)
      shrink();
    else if(op == 10)
      Mirror();
    else if(op == 11)
      shuffle();
    else if(op == 12)
      blur(), blur(), blur();
    else if(op == 13)
      crop();
    else if(op == 14)
      skew_ho();
    else if(op == 15)
      skew_ve();
    else if(op == 16)
      saveImage(); /*Save the image after applying a filter.*/


    cout << "\n\n";
  } while (op);
  
}
