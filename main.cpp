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
vector <vector <Pixel> > addToFin(vector< vector <Pixel> >, vector <vector <Pixel> >); //Combine bmp matricies to final picture
void avgFinal(vector< vector <Pixel> > &, int); //Takes final image and divides by amount of pictures there was
void savePic(vector <vector <Pixel> >); //Saves matrix inputs as final composite image

int tenPics =10;

int main(){
    vector <vector <Pixel> > fin;
    bool eqlSize = true;
    bool end = false;
    int imgAmt = 0;

    do{
        vector <vector <Pixel> > bmp;
        string pic;
        if (imgAmt != tenPics)
        {
            cout<<" Enter file name: ";
            cin >> pic;
        }
        if (pic == "DONE" )
        {
            end = true;
        }
        else if (pic == "done" )
        {
            end = true;
        }
        else if (imgAmt == 10)
        {
            end = true;
        }
        else {
            bmp = pixelizeImage(userFile(pic, imgAmt));
            if (imgAmt == 0)
            {
            fin = bmp;
            }
            else if (imgAmt != 0)
            {
                fin = addToFin(fin, bmp);
            }
            if(eqlSize == false)
            {
                cout << "Error. Please try again.";
                return 0;
            }
            cout << " Picture " << imgAmt + 1 << " added to final picture. ";
            imgAmt++;
        }
    }
    while (end == false);
    if (imgAmt == 0)
    {
        cout << "No pictures recieved, please try again.";
    }
    else
    {
        avgFinal (fin, imgAmt);
        savePic(fin);
    }
    return 0;
   }
void avgFinal (vector <vector <Pixel> > &fin, int imgAmt)
{
    Pixel rgb;
    for (int k = 0; k < fin.size(); k++)
    {
        for (int b =0; b < fin[k].size(); b++)
        {
        rgb = fin[k][b];
        rgb.red = rgb.red /imgAmt;
        rgb.blue = rgb.blue /imgAmt;
        rgb.green = rgb.green /imgAmt;
        fin[k][b] = rgb;
        }
    }
}
vector <vector <Pixel> >addToFin(vector <vector <Pixel> > fin, vector <vector <Pixel> > bmp)
{
    Pixel rgb;
    Pixel rgb2;
    if (fin.size() != bmp.size() && fin[0].size() != bmp[0].size())
    {
        cerr << "One or more bmp files have invalid dimensions";
    }
    else
    {
        for(int k = 0; k < fin.size(); k++)
        {
            for (int b = 0; b < fin[k].size(); b++)
            {
                rgb = bmp[k][b];
                rgb2 = fin[k][b];
                rgb2.red = rgb.red + rgb2.red;
                rgb2.blue = rgb.blue + rgb2.blue;
                rgb2.green = rgb.green + rgb2.green;
                fin[k][b] = rgb2;
             }
         }
         return fin;
    }
}
Bitmap userFile(string pic, int &imgAmt)
{
    Bitmap image;
    image.open(pic);
    bool validBmp = image.isImage();
    if (validBmp == true)
    {
        cout << " File " <<imgAmt + 1 << " selected. ";
        return image;
    }
    else if (validBmp == false)
    {
        imgAmt--;
    }
}
vector <vector <Pixel> > pixelizeImage(Bitmap image)
{
    vector <vector <Pixel> > bmp;
    bmp = image.toPixelMatrix();
    return bmp;
}
void savePic(vector <vector <Pixel> > bmp)
{
    Bitmap image;
    image.fromPixelMatrix(bmp);
    image.save("composite-rlamug.bmp");
    cout<<"Saving composite image complete."<<endl;
}
