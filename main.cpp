#include <iostream>
#include <string>
#include <cstring>
#include <ctype.h>
using namespace std;



int main()
{
   int t = 3, i = 0, j;     //0         1       2       3       4           5       6          7          8        9       10       11        12     13       14      15        16        17        18       19         20       21       22       23        24       25       26
   int PolyTable[27][2]={{0, 0},{10, 3},{100, 9},{12, 5},{120, 15},{212, 23},{111, 13},{122, 17},{202, 20},{11, 4},{110, 12},{112,14},{102, 11},{2, 2},{20, 6},{200, 18},{21, 7},{210, 21},{121, 16},{222, 26},{211, 22},{101, 10},{22, 8},{220, 24},{221, 25},{201, 19},{1, 1},};
        int Expo1, Expo2;

    int PolyHundred, PolyTen, PolyOne;
    string Word;
    cout<<"Enter the word you wish to encrypt: "; cin>>Word;
cout<<"The word will be converted into uppercase characters: ";

    while(Word[i])
    {
        int uppercaser = Word[i];
        Word[i] = putchar(toupper(uppercaser));
        i++;

    }

cout<<endl;

 char arr[Word.size()];

strcpy(arr, Word.c_str());

    int Galois[7][Word.size()];
    for(i = 0; i<7; i++)
        for(j = 0; j<Word.size(); j++) //finding the character's place in the alphabet and putting its value in the next row, same column
        {
            if(i == 0)
                Galois[i][j] = (int)arr[j] - 64;

            if(i == 1)
                for(int k = 0; k<27; k++)
                if(Galois[i-1][j] == PolyTable[k][1])
                {
                    Galois[i][j] = PolyTable[k][0];
                    Galois[i+1][j] = k;
                }


            if(i == 3)     //We must enter the first two polynoms by hand, you have to simply add 3-digit number, whose digits are <= 3
            {
             if(j < 2 || Word.size() < 2)
                {
                   cout<<"Enter the polynoms for the field "<<i<<" and "<<j<<": ";
            cin>>Galois[i][j];
            cout<<endl;
                }
                else {    //on this row, we will add polynoms. The i-2 and i-1 polynoms will form polynom i.
                          //Even though I use 3-digit numbers, they will be printed as a polynom.
                        Galois[i][j] = Galois[i][j-1] + Galois [i][j-2];
                        PolyHundred = (Galois[i][j] / 100) % 3;
                        PolyTen = ((Galois[i][j] / 10) % 10) % 3;
                        PolyOne = Galois[i][j] % 10 % 3;
                        Galois[i][j] = PolyHundred * 100 + PolyTen * 10 + PolyOne;
                     }

                for(int k = 0; k<27; k++)
                            if(Galois[i][j] == PolyTable[k][0])
                            Galois[i+1][j] = k;
            }


            if(i == 5)
                if(j < 2)
                { //We must enter the first two polynoms by hand, you have to simply add 3-digit number, whose digits are <= 3
                     cout<<"Enter the polynoms for the field "<<i<<" and "<<j<<": ";
                cin>>Galois[i][j];
                cout<<endl;
                }

                else {
                    for(int k = 0; k < 27; k++)

                       if(Galois[i][j-2] == PolyTable[k][0]) Expo1 = k;


                    for(int k = 0; k < 27; k++)

                    if(Galois[i][j-1] == PolyTable[k][0]) Expo2 = k;
                       Galois[i][j] = PolyTable[(Expo1+Expo2)%26][0];

                     }

            if(i == 6)
                {
                  for(int k = 0; k < 27; k++)
                      {
                          if(Galois[1][j] == PolyTable[k][0]) Expo1 = k;
                      }

                    //here, we will have to add the exponents of i-2 and i-1 polynoms, in order to create the i polynom.
                    //in the case there an exponent is bigger than 26, we just use modulo and then we create the polynom.
                   for(int k = 0; k < 27; k++)
                      {
                          if(Galois[3][j] == PolyTable[k][0]) Expo2 = k;
                      }

                       Galois[i][j] = PolyTable[(Expo1+Expo2)%26][0] + Galois[i-1][j];
                        PolyHundred = (Galois[i][j] / 100) % 3;
                        PolyTen = ((Galois[i][j] / 10) % 10) % 3;
                        PolyOne = Galois[i][j] % 10 % 3;
                        Galois[i][j] = PolyHundred * 100 + PolyTen * 10 + PolyOne;

                    for(int k = 0; k < 27; k++)
                        if(Galois[i][j] == PolyTable[k][0]) {Galois[i][j] = PolyTable[k][1]; break;}

                }


        }
        //printing the table
        for(i = 0; i<Word.size(); i++)
            cout<<arr[i]<<"\t ";
        cout<<endl<<"-----------------------------------------------"<<endl;

        for(i = 0; i<Word.size(); i++)
        {
            if(j == 0) cout<<"\t ";
           for(j = 0; j<Word.size(); j++)


            if(i % 2 == 1)
           {
                if(Galois[i][j] < 10)  cout<<"(0,0,"<<Galois[i][j]<<")"<<"\t";
               else if(Galois[i][j] < 100 && Galois[i][j] > 9) cout<<"(0,"<<Galois[i][j]/10<<","<<Galois[i][j]%10<<")"<<"\t";
               else cout<<"("<<Galois[i][j]/100<<","<<(Galois[i][j]/10)%10<<","<<Galois[i][j]%10<<")"<<"\t";
           }
            else cout<<Galois[i][j]<<"\t ";
            cout<<endl<<"-----------------------------------------------"<<endl;



        }

        for(j = 0; j<Word.size(); j++)
            cout<<Galois[6][j]<<"\t";
            cout<<endl<<"-----------------------------------------------"<<endl;
            for(j = 0; j<Word.size(); j++)
            cout<<(char)(Galois[6][j]+64)<<"\t";


}
