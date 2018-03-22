#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>

using namespace std;


void spausdinimas ( ifstream& fin, ofstream& fout) //Tekstas surenkamas po eilute, sudaromos bigramos, jos irasomos i faila. Kadangi c++ nepalaiko UTF-8 formato, tai naudajami unsigned long long kintamieji (juose telpa 8 byte'ai). Imami stringai, jie unifikuojami ir pakraunami i unsigned long kintamaji (4 byte'u). Veliau sudaroma bigrama is unsigned long long kintamojo (8 byte'u).
{
    map <unsigned long long, double> mBigramos;
    map <unsigned long long, double>::iterator it;

    unsigned long long ullBigram;
    string eilute;
    unsigned int uiCharacter[2];
    int i;
    int i1=0;
    int i2=0;

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
            fout<<"Klaida duomenyse"<<endl;
            fout<<i<<"-tasis"<<endl;
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

fout<<mBigramos.size()<<endl;
for (it=mBigramos.begin(); it!=mBigramos.end(); it++){
        fout << it->first <<endl;
        fout << it->second <<endl;
    }
}
int main()

{

    ifstream f1("cs.txt");
    ofstream f2("csAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("da.txt");
    f2.open("daAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("de.txt");
    f2.open("deAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("el.txt");
    f2.open("elAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("en.txt");
    f2.open("enAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("es.txt");
    f2.open("esAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("et.txt");
    f2.open("etAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("fi.txt");
    f2.open("fiAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("fr.txt");
    f2.open("frAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("hu.txt");
    f2.open("huAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("it.txt");
    f2.open("itAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("lt.txt");
    f2.open("ltAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("lv.txt");
    f2.open("lvAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("mt.txt");
    f2.open("mtAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("nl.txt");
    f2.open("nlAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("pl.txt");
    f2.open("plAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("pt.txt");
    f2.open("ptAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("ro.txt");
    f2.open("roAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("sk.txt");
    f2.open("skAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("sl.txt");
    f2.open("slAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();

    f1.open("sv.txt");
    f2.open("svAts.txt");
    spausdinimas(f1,f2);
    f1.close();
    f2.close();



    return 0;
}
