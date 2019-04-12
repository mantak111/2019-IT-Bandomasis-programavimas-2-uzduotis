#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Slidininkas {
    char identInfo[22];
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
        fin.get(slidininkai[i].identInfo, 22);
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

void suskaiciuotiLaika(int n, Slidininkas slidininkai[]) {
    int sLaikSek, fLaikSek;
    double skirtSek;

    for(int i = 0; i < n; i++) {
        if(!slidininkai[i].diskv) {
            sLaikSek = (slidininkai[i].sVal*60*60)+(slidininkai[i].sMin*60)+slidininkai[i].sSek;
            fLaikSek = (slidininkai[i].fVal*60*60)+(slidininkai[i].fMin*60)+slidininkai[i].fSek;
            skirtSek = fLaikSek-sLaikSek;
            slidininkai[i].lMin = (int)(skirtSek/60);
            slidininkai[i].lSek = skirtSek-slidininkai[i].lMin*60;
            slidininkai[i].skirtSek = skirtSek;
        }
    }
}

void isrinktiNugaletojus(int n, int &r, Slidininkas slidininkai[], Slidininkas nugaletojai[]) {
    for(int i = 0; i < n; i++) {
        if(!slidininkai[i].diskv && slidininkai[i].lMin >= 30 && slidininkai[i].lSek > 0) {
            slidininkai[i].diskv = true;
        } else if(!slidininkai[i].diskv) {
            push(slidininkai[i], nugaletojai[r]);
            r++;
        }
    }
}

void rusiuotiDidejanciai(int r, Slidininkas nugaletojai[]) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j > r; j++) {
            if(nugaletojai[i].skirtSek < nugaletojai[j].skirtSek) {
                push(nugaletojai[i], nugaletojai[j]);
            }
        }
    }
}

void rasyti(int r, Slidininkas nugaletojai[]) {
    ofstream fout("U2rez.txt");

    for(int i = 0; i < r; i++) {
        fout >> nugaletojai[i].identInfo << " " << nugaletojai[i].lMin << " " << nugaletojai[i].lSek << endl;
    }
    fout.close();
}
