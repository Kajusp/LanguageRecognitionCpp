#include <iostream>
#include <cmath>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

    map <unsigned long long, double> mBigramos;
    map <unsigned long long, double>::iterator it;

    pair <double, string> koficientai[21];

double koficientas (int iBigramuKiekis, double *iKalba1, double *iKalba2)
{
    double dSkaitiklis=0;

    for (int i=0; i<iBigramuKiekis; i++){
        dSkaitiklis+=iKalba1[i]*iKalba2[i];
    }

    double dKalbos1Modulis=0;
    double dKalbos2Modulis=0;

    dKalbos1Modulis=0;

    for (int i=0; i<iBigramuKiekis; i++){
        dKalbos1Modulis+=iKalba1[i]*iKalba1[i];
        dKalbos2Modulis+=iKalba2[i]*iKalba2[i];
    }

    dKalbos1Modulis=sqrt(dKalbos1Modulis);
    dKalbos2Modulis=sqrt(dKalbos2Modulis);

    return dSkaitiklis/(dKalbos1Modulis*dKalbos2Modulis);

}

double KalbuLyginimas (ifstream& f1){

    unsigned long long bigrama;
    double verte;

    map <unsigned long long, double> kalba;
    map <unsigned long long, double> mBigramos2; //mBigramos mapo kopija, tam, kad originalaus mapo neuzpildyti nereikalingom vertem.

    mBigramos2.insert(mBigramos.begin(), mBigramos.end());

    int kiekis;
    f1>>kiekis;
    for (int i=0; i<kiekis; i++){
        f1>>bigrama;
        f1>>verte;
        kalba[bigrama]=verte;
    }

    for (it=mBigramos2.begin(); it!=mBigramos2.end(); ++it){
        if (kalba.find(it->first)==kalba.end())
            kalba[it->first]=0.001;
    }

    for (it=kalba.begin(); it!=kalba.end(); ++it){
        if (mBigramos2.find(it->first)==mBigramos2.end())
            mBigramos2[it->first]=0.001;
    }

    double maskalba[kalba.size()];
    double masmBigramos[mBigramos2.size()];

    int i=0;

    for (it=mBigramos2.begin(); it!=mBigramos2.end(); ++it){
        masmBigramos[i]=it->second;
        i++;
    }

    i=0;

    for (it=kalba.begin(); it!=kalba.end(); ++it){
        maskalba[i]=it->second;
        i++;
    }
    return koficientas(kalba.size(), masmBigramos, maskalba);
}


int main()

{

    ifstream fin("failas.txt");

    unsigned long long ullBigram;
    string eilute;
    unsigned int uiCharacter[2];
    int i;

    while (getline(fin, eilute)){

    i=0;

    if (eilute.size()==0)
        continue;

    if ((eilute[i]&0xF0)==0xF0 && eilute.size()>=i+4){
            uiCharacter[0]=eilute[i]*0x01000000+eilute[i+1]*0x010000+eilute[i+2]*0x0100+eilute[i+3]; //raide is 4 byte ir toliau reikia perskaityti tuos byteus ir suformuoti simboli.
            if (eilute.size()>=i+5)
                i=i+4;
            else{
                continue;
            }
    }

    else
        if ((eilute[i]&0xE0)==0xE0 && eilute.size()>=i+3){
            uiCharacter[0]=eilute[i]*0x010000+eilute[i+1]*0x0100+eilute[i+2];
            if (eilute.size()>=i+4)
                i=i+3;
            else{
                continue;
            }
        }

    else
        if ((eilute[i]&0xC0)==0xC0 && eilute.size()>=i+2){
            uiCharacter[0]=eilute[i]*0x0100+eilute[i+1];  //raide is 2 byteu
            if (eilute.size()>=i+3)
                i=i+2;
            else{
                continue;
            }
        }

    else{

        if ((eilute[i]&(0x80))==0 && eilute.size()>=i+1){
            uiCharacter[0]=eilute[i]; //raide is 1 byte
            if (eilute.size()>=i+2)
                i=i+1;
            else{
                continue;
            }
        }
        else
        cout<<"Klaida duomenyse"<<endl;
    }
    while (1){

    if ((eilute[i]&0xF0)==0xF0 && eilute.size()>=i+4){
            uiCharacter[1]=eilute[i]*0x01000000+eilute[i+1]*0x010000+eilute[i+2]*0x0100+eilute[i+3]; //raide is 4 byte ir toliau reikia perskaityti tuos byteus ir suformuoti simboli.
            if (eilute.size()>=i+5)
                i=i+4;
            else{
                break;
            }
    }

    else
        if ((eilute[i]&0xE0)==0xE0 && eilute.size()>=i+3){
            uiCharacter[1]=eilute[i]*0x010000+eilute[i+1]*0x0100+eilute[i+2];
            if (eilute.size()>=i+4)
                i=i+3;
            else{
                break;
            }//raide is 3 byte
        }

    else
        if ((eilute[i]&0xC0)==0xC0 && eilute.size()>=i+2){
            uiCharacter[1]=eilute[i]*0x0100+eilute[i+1];  //raide is 2 byteu
            if (eilute.size()>=i+3)
                i=i+2;
            else{
                break;
            }
        }

    else
        if ((eilute[i]&0x80)==0 && eilute.size()>=i+1){
            uiCharacter[1]=eilute[i]; //raide is 1 byte
            if (eilute.size()>=i+2)
                i=i+1;
            else{
                break;
            }
        }
        else{
            cout<<"Klaida duomenyse"<<endl;
            cout<<i<<"-tasis"<<endl;
        }
        //klaida duomenys

    ullBigram=uiCharacter[0]*0x0100000000+uiCharacter[1];
    uiCharacter[0]=uiCharacter[1];
    if (mBigramos.find(ullBigram)==mBigramos.end())
        mBigramos[ullBigram]=1;
    else
        mBigramos[ullBigram]++;
    }

}

    ifstream f1("csAts.txt");
    koficientai[0].second="cs";
    koficientai[0].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("daAts.txt");
    koficientai[1].second="da";
    koficientai[1].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("elAts.txt");
    koficientai[2].second="el";
    koficientai[2].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("enAts.txt");
    koficientai[3].second="en";
    koficientai[3].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("esAts.txt");
    koficientai[4].second="es";
    koficientai[4].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("etAts.txt");
    koficientai[5].second="et";
    koficientai[5].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("fiAts.txt");
    koficientai[6].second="fi";
    koficientai[6].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("frAts.txt");
    koficientai[7].second="fr";
    koficientai[7].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("huAts.txt");
    koficientai[8].second="hu";
    koficientai[8].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("itAts.txt");
    koficientai[9].second="it";
    koficientai[9].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("ltAts.txt");
    koficientai[10].second="lt";
    koficientai[10].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("lvAts.txt");
    koficientai[11].second="lv";
    koficientai[11].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("mtAts.txt");
    koficientai[12].second="mt";
    koficientai[12].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("nlAts.txt");
    koficientai[13].second="nl";
    koficientai[13].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("plAts.txt");
    koficientai[14].second="pl";
    koficientai[14].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("ptAts.txt");
    koficientai[15].second="pt";
    koficientai[15].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("roAts.txt");
    koficientai[16].second="ro";
    koficientai[16].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("skAts.txt");
    koficientai[17].second="sk";
    koficientai[17].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("slAts.txt");
    koficientai[18].second="sl";
    koficientai[18].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("svAts.txt");
    koficientai[19].second="sv";
    koficientai[19].first=KalbuLyginimas(f1);
    f1.close();

    f1.open("deAts.txt");
    koficientai[20].second="de";
    koficientai[20].first=KalbuLyginimas(f1);
    f1.close();


    sort(koficientai, koficientai+21);

    for (int i=20; i>15; i--)
        cout<<koficientai[i].second<<" -> "<<koficientai[i].first<<endl;

    return 0;
}
