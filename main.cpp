//Rodolfo Lamug

#include<iostream>
#include<vector>
#include<string>
#include"bitmap.h"

using namespace std;

//Keep asking the user for a file name until they type in "Done". Note: 10 files is the maximum number allowed.
//Prints out error if not valid bitmap file or the file is non-existent. Also prints out error if the width and height of the image doesn't have the same dimensions (width and height) as the first image loaded. Do not include files that have an error as described above. After evaluating all the file names, if at least 2 images don't have the same dimensions print out error message that a composite image cannot be created and do not do anything else in the program.
//The program should work with any valid BMP images that are 24bit color depth and uncompressed, regardless of its size.
//Combine the valid images together to make a composite image.


//Prototypes:
Bitmap userFile(string, int &userFiles); //Receives the user file and checks to see of it's valid
vector <vector <Pixel> > pixelizeImage(Bitmap); //Converts user's image from bitmap to matrix of pixel
vector <vector <Pixel> > addToFin(vector< vector <Pixel> >, vector <vector <Pixel> >); //Combine bmp matrix to final picture
void averageFinal(vector< vector <Pixel> > &, int); //Takes final image and divides by amount of pictures there was
void savePicture(vector <vector <Pixel> >); //Saves matrix ineuts as final composite image

int tenImages = 10;

int main(){
    vector <vector <Pixel> > fin;
    bool equalSize = true;
    bool end = false;
    int imageAmount = 0;

    do{
        vector <vector <Pixel> > bmp;
        string pic;
        if (imageAmount != tenImages)
        {
            cout<<" Enter file name: ";
            cin >> pic;
        }
        if (pic == "DONE" || pic == "done" || imageAmount == 10)
        {
            end = true;
        }
        else {
            bmp = pixelizeImage(userFile(pic, imageAmount));
            if (imageAmount == 0)
            {
            fin = bmp;
            }
            else if (imageAmount != 0)
            {
                fin = addToFin(fin, bmp);
            }
            if (equalSize == false)
            {
                cout << "Error. Please try again.";
                return 0;
            }
            cout << "Picture " << imageAmount + 1 << " added to final picture.";
            imageAmount++;
        }
    }
    while (end == false);
    if (imageAmount == 0)
    {
        cout << "No pictures recieved, please try again.";
    }
    else
    {
        averageFinal (fin, imageAmount);
        savePicture(fin);
    }
    return 0;
   }
void averageFinal (vector <vector <Pixel> > &fin, int imageAmount)
{
    Pixel rgb;
    for (int h = 0; h < fin.size(); h++)
    {
        for (int i = 0; i < fin[h].size(); i++)
        {
        rgb = fin[h][i];
        rgb.red = rgb.red /imageAmount;
        rgb.blue = rgb.blue /imageAmount;
        rgb.green = rgb.green /imageAmount;
        fin[h][i] = rgb;
        }
    }
}
vector <vector <Pixel> >addToFin(vector <vector <Pixel> > fin, vector <vector <Pixel> > bmp)
{
    Pixel rgb;
    Pixel rgb2;
    if (fin.size() != bmp.size() && fin[0].size() != bmp[0].size())
    {
        cout << "One or more bmp files have invalid dimensions";
    }
    else
    {
        for(int h = 0; h < fin.size(); h++)
        {
            for (int i = 0; i < fin[h].size(); i++)
            {
                rgb = bmp[h][i];
                rgb2 = fin[h][i];
                rgb2.red = rgb.red + rgb2.red;
                rgb2.blue = rgb.blue + rgb2.blue;
                rgb2.green = rgb.green + rgb2.green;
                fin[h][i] = rgb2;
             }
         }
         return fin;
    }
}
Bitmap userFile(string pic, int &imageAmount)
{
    Bitmap image;
    image.open(pic);
    bool validBmp = image.isImage();
    if (validBmp == true)
    {
        cout << " File " <<imageAmount + 1 << " selected. ";
        return image;
    }
    else if (validBmp == false)
    {
        imageAmount--;
    }
}
vector <vector <Pixel> > pixelizeImage(Bitmap image)
{
    vector <vector <Pixel> > bmp;
    bmp = image.toPixelMatrix();
    return bmp;
}
void savePicture (vector <vector <Pixel> > bmp)
{
    Bitmap image;
    image.fromPixelMatrix(bmp);
    image.save("composite-rlamug.bmp");
    cout<<"Saving composite image complete."<<endl;
}
