#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct Slidininkas {
    char identInfo[21];
    int startoNr;
    int sVal, sMin, sSek;
    int fVal, fMin, fSek;
    int lMin, lSek;
    int skirtSek;
    bool diskv;
};

void skaityti(int &n, int &m, Slidininkas slidininkai[]);
void suskaiciuotiLaika(int n, Slidininkas slidininkai[]);
void isrinktiNugaletojus(int n, int &r, Slidininkas slidininkai[], Slidininkas nugaletojai[]);
void rusiuotiDidejanciai(int r, Slidininkas nugaletojai[]);
void rasyti(int r, Slidininkas nugaletojai[]);

int main()
{
    int n, m, r = 0;
    Slidininkas slidininkai[30];
    Slidininkas nugaletojai[30];

    skaityti(n, m, slidininkai);
    suskaiciuotiLaika(n, slidininkai);

    isrinktiNugaletojus(n, r, slidininkai, nugaletojai);
    rusiuotiDidejanciai(r, nugaletojai);
    rasyti(r, nugaletojai);

    return 0;
}

void skaityti(int &n, int &m, Slidininkas slidininkai[]) {
    ifstream fin("U2.txt");
    int laikStartoNr;

    fin >> n;
    for(int i = 0; i < n; i++) {
        fin.ignore();
        fin.get(slidininkai[i].identInfo, 21);
        fin >> slidininkai[i].startoNr;
        fin >> slidininkai[i].sVal;
        fin >> slidininkai[i].sMin;
        fin >> slidininkai[i].sSek;
        slidininkai[i].diskv = true;
    }
    fin >> m;
    for(int i = 0; i < n; i++) {
        fin >> laikStartoNr;
        for(int j = 0; j < n; j++) {
            if(slidininkai[j].startoNr == laikStartoNr) {
                fin >> slidininkai[j].fVal;
                fin >> slidininkai[j].fMin;
                fin >> slidininkai[j].fSek;
                slidininkai[j].diskv = false;
                continue;
            }
        }
    }
    fin.close();
}

void suskaiciuotiLaika(int n, Slidininkas mas[]) {
    int sLaikSek, fLaikSek;
    double skirtSek;

    for(int i = 0; i < n; i++) {
        if(!mas[i].diskv) {
            sLaikSek = (mas[i].sVal*60*60)+(mas[i].sMin*60)+mas[i].sSek;
            fLaikSek = (mas[i].fVal*60*60)+(mas[i].fMin*60)+mas[i].fSek;
            skirtSek = fLaikSek-sLaikSek;
            if(skirtSek<0) {
               skirtSek = 86400+skirtSek;
            }

            mas[i].lMin = (int)(skirtSek/60);
            mas[i].lSek = skirtSek-mas[i].lMin*60;
            mas[i].skirtSek = skirtSek;
        }
    }
}

void isrinktiNugaletojus(int n, int &r, Slidininkas mas1[], Slidininkas mas2[]) {
    for(int i = 0; i < n; i++) {
        if(!mas1[i].diskv && mas1[i].lMin >= 30 && mas1[i].lSek > 0) {
            mas1[i].diskv = true;
        } else if(!mas1[i].diskv) {
            swap(mas1[i], mas2[r]);
            r++;
        }
    }
}

void rusiuotiDidejanciai(int r, Slidininkas mas[]) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < r; j++) {
            if(mas[i].skirtSek < mas[j].skirtSek
               || ((mas[i].skirtSek == mas[j].skirtSek)
               && strcmp(mas[j].identInfo, mas[i].identInfo) > 0)) {
                swap(mas[i], mas[j]);
            }
        }
    }
}

void rasyti(int r, Slidininkas nugaletojai[]) {
    ofstream fout("U2rez.txt");

    for(int i = 0; i < r; i++) {
        fout << nugaletojai[i].identInfo << " " << nugaletojai[i].lMin << " " << nugaletojai[i].lSek << endl;
    }
    fout.close();
}
