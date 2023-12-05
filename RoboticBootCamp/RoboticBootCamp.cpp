#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <unordered_map>
using namespace std;

struct Otomobil {
    string Plaka;
    int otoParkKati;
    int otoParkYeri;
};

struct ParkYeri {
    bool isFull=false;
    string parkPlaka;
    ParkYeri() {}
};

struct OtoPark {
    vector<vector<ParkYeri>> katlar;
};

void OtoParkBaslat(OtoPark& otoPark) {
    otoPark.katlar.resize(5);
    for (int i = 0; i < 5; ++i) {
        otoPark.katlar[i].resize(10);
        for (int j = 0; j < 10; ++j) {
            otoPark.katlar[i][j].isFull = false;
        }
    }
}

bool parkAlaniDoluMu(const OtoPark& otoPark, int kat, int yeri) {
    return otoPark.katlar[kat][yeri].isFull;
}

bool enterVehicle(OtoPark& otoPark, const Otomobil& arac) {
    for (int i = arac.otoParkKati; i < 5; ++i) {
        for (int j = arac.otoParkYeri; j < 10; ++j) {
            if (!parkAlaniDoluMu(otoPark, arac.otoParkKati, arac.otoParkYeri)) {
                otoPark.katlar[arac.otoParkKati][arac.otoParkYeri].isFull = true;
                otoPark.katlar[arac.otoParkKati][arac.otoParkYeri].parkPlaka = arac.Plaka;
                return true;
            }
        }
    }
    return false;
}

bool exitVehicle(OtoPark& otoPark, const string& plaka) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (otoPark.katlar[i][j].isFull && otoPark.katlar[i][j].parkPlaka == plaka) {
                otoPark.katlar[i][j].isFull = false;
                otoPark.katlar[i][j].parkPlaka = "";
                return true;
            }
        }
    }
    return false;
}

void listVehicles(const OtoPark& otoPark) {
    unordered_map<string, pair<int, int>> vehicleMap;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (otoPark.katlar[i][j].isFull) {
                vehicleMap[otoPark.katlar[i][j].parkPlaka] = { i, j };
            }
        }
    }
    for (const auto& arac : vehicleMap) {
        cout << "\033[96mPlaka: " << arac.first << ", Kat: " << arac.second.first << ", Yeri: " << arac.second.second << endl;
    }

   
}

void listMenu() {
    OtoPark otoPark;
    OtoParkBaslat(otoPark);

    vector<Otomobil> araclar = { { "67-ABC-1920", 0, 0 }, { "67-ABC-1923", 1, 2 }, { "67-DEF-2023", 2, 3 } };
    for (const auto& arac : araclar) {
        enterVehicle(otoPark, arac);
    }
    int seçim;
    int exitControl = 0;
    while (exitControl != 4) {
        cout << "\033[92m1. Otopark Arac Listesi\n";
        cout << "\033[32m2. Otopark Arac Girisi\n";
        cout << "\033[91m3. Otopark Arac Cikisi\n";
        cout << "\033[31m4. Cikis\n";
        cout << "\033[96mSeciminizi Yapiniz: \n";
        cin >> seçim;

        switch (seçim)
        {
        case 1:
        {
            system("cls");
            listVehicles(otoPark);
            cout << "Ana menuye donmek icin entera basiniz." << endl;
            _getch();
            system("cls");

        }
            break;
        case 2:
        {
            string plaka;
            int otoParkKati, otoParkYeri;
            system("CLS");
            cout << "Dolu olan park alanlarimiz bunlardir." << endl;
            Sleep(1000);
            listVehicles(otoPark);
            Sleep(1000);
            cout << "\nBos katlardaki bos yerleri secebilirsiniz.Tusa basiniz." << endl;
            _getch();
            cout << "Park Alaninin Katina(0-4) Girin: ";
            cin >> otoParkKati;
            cout << "Park Alaninin Yerini(0-9) Girin: ";
            cin >> otoParkYeri;
            cout << "Aracin Plakasini Giriniz: ";
            cin >> plaka;
            if (enterVehicle(otoPark, { plaka, otoParkKati, otoParkYeri })) {
                system("CLS");
                cout << "Arac " << otoParkKati << ".Kat " << otoParkYeri << ".nolu yere park edildi." << endl;
                cout << "Ana Menuye Yonlendiriliyorsunuz.."<< endl;
                Sleep(2500);
                system("CLS");
            }
            else {
                system("CLS");
                cout << "Park Yeri Dolu veya Bulunmamaktadir.\nAna menuye Yonlendiriliyorsunuz!" << endl;
                Sleep(2500);
                system("CLS");

            }
        }
            break;
        case 3:
        {
            string plaka;
            listVehicles(otoPark);
            Sleep(1500);
            cout << "\nCikis yapmasini istediginiz Arac plakasini giriniz: ";
            cin >> plaka;
            if (exitVehicle(otoPark, plaka)) {
                cout << "Arac park cikisi yapildi." << endl;
                cout << "Ana Menuye Yonlendiriliyorsunuz.." << endl;
                Sleep(2500);
                system("CLS");
            }
            else {
                system("CLS");
                cout << "Arac bulunamadý!" << endl;
                Sleep(1500);
                system("CLS");

            }
        }
            break;
        case 4:
            system("CLS");
            cout << "\033[31mCikis Yapiliyor!" << endl;
            Sleep(500);
            cout << "\033[31mCikis Yapiliyor!" << endl;
            Sleep(500);
            exitControl = 4;
            break;
        default:
            system("CLS");
            cout << "\033[31m Hatali Secim yaptiniz. 2 saniye sonra Tekrar Deneyiniz!" << endl;
            Sleep(2000);
            system("CLS");
            break;
        }
        
    }
}


    
int main() {
    
    string username = "";
    int password = -1;
    cout << "\033[93mRobotik Otoparka Hosgeldiniz." << endl;
    Sleep(1000);
    system("cls");
    cout << "\033[96mUsername Giriniz." << endl;
    cin >> username;
    cout << "\033[91mPassword Giriniz." << endl;
    cin >> password;
    if (username == "admin" && password == 12) {
        system("CLS");
        cout << "\033[92mGiris Gerceklesti.";
        Sleep(1000);
        system("CLS");
        listMenu();
    }
    else {
        system("CLS");
        cout << "\033[91mGirdiginiz bilgilerde hata var..";
        Sleep(1000);
        system("CLS");
        cout << "\033[91mProgram kapaniyor !! ..";
        Sleep(1000);

    }

    system("CLS");
    system("PAUSE");
    return 0;
}   

    
    
    


void LoopExample()
{
    int Sayi1 = 6;
    int Sayi2 = 6;

    if (Sayi1 > Sayi2) {
        cout << "1. Sayi, 2. Sayidan Buyuk";
    }
    else if (Sayi1 == Sayi2) {
        cout << "Sayilar bir birine esit";
    }
    else {
        cout << "2. Sayi, 1. Sayidan Buyuk";
    }

    int GirilenSayi, RastgeleSayi;
    GirilenSayi = -1;
    RastgeleSayi = -2;
    srand(time(NULL));

    while (GirilenSayi != RastgeleSayi) {
        cout << "1 ile 10 arasinda bir sayi giriniz: ";
        cin >> GirilenSayi;
        RastgeleSayi = rand() % 10 + 1;
        cout << "Girdiginiz Sayi: " << GirilenSayi << endl;
        cout << "Sistemin Belirledigi Sayi: " << RastgeleSayi << endl;
        if (GirilenSayi != RastgeleSayi) {
            cout << "Kaybettiniz Yeniden Deneyiniz!" << endl;
        }
        Sleep(2500);
        system("CLS");
    }
    cout << "Tebrikler Kazandiniz!" << endl;

    do
    {
        cout << "Kosul Saglandi Dongu Calisiyor" << endl;
    } while (5 > 6);


    int Sayilar[5] = { 10, 20, 30, 40, 50 };
    for (int i = 0; i < 5; i++)
    {
        cout << "Sayilar Dizisinin " << i << ". Elemanin Degeri: " << Sayilar[i] << endl;
    }

    for (int Sayi : Sayilar)
    {
        cout << "Sayilar Dizisinin Elemanlari: " << Sayi << endl;
    }
}

void variableExample()
{
    int Sayi = 100;
    float OndalikliSayi = 100.5f;
    char Karakter = 'A';
    string Metin = "Hello World!";

    cout << "Tamsayi Degiskenin Degeri: " << Sayi << endl;
    cout << "Ondalikli Sayi Degiskenin Degeri: " << OndalikliSayi << endl;
    cout << "Karakter Degiskenin Degeri: " << Karakter << endl;
    cout << "Metin Degiskenin Degeri: " << Metin << endl;
    cout << "Tamsayi Degiskeninin Bellek Boyutu: " << sizeof(Sayi) << endl;
    cout << "Metin Degiskeninin Bellek Boyutu: " << sizeof(Metin) << endl;
    cout << "Karakter Degiskeninin Bellek Boyutu: " << sizeof(Karakter) << endl;

    const char* KarakterMetni = "Hello World!";
    cout << "Pointer Karakter Metni Degiskeninin Degeri: " << KarakterMetni << endl;
    cout << "Pointer Karakter Metni Degiskeninin Bellek Boyutunu: " << sizeof(KarakterMetni) << endl;


    int Sayilar[5] = { 10, 20, 30, 40, 50 };
    cout << "Dizinin 1. Elemanin Degeri: " << Sayilar[0] << endl;
    cout << "Dizinin 2. Elemanin Degeri: " << Sayilar[1] << endl;
    cout << "Dizinin 3. Elemanin Degeri: " << Sayilar[2] << endl;
    cout << "Dizinin 4. Elemanin Degeri: " << Sayilar[3] << endl;
    cout << "Dizinin 5. Elemanin Degeri: " << Sayilar[4] << endl;

    int BosDizi[5];
    cout << "Dizinin 1. Elemanin Degeri Giriniz: ";
    cin >> BosDizi[0];
    cout << "Dizinin 2. Elemanin Degeri Giriniz: ";
    cin >> BosDizi[1];
    cout << "Dizinin 3. Elemanin Degeri Giriniz: ";
    cin >> BosDizi[2];
    cout << "Dizinin 4. Elemanin Degeri Giriniz: ";
    cin >> BosDizi[3];
    cout << "Dizinin 5. Elemanin Degeri Giriniz: ";
    cin >> BosDizi[4];

    cout << "Dizinin 1. Elemanin Degeri: " << BosDizi[0] << endl;
    cout << "Dizinin 2. Elemanin Degeri: " << BosDizi[1] << endl;
    cout << "Dizinin 3. Elemanin Degeri: " << BosDizi[2] << endl;
    cout << "Dizinin 4. Elemanin Degeri: " << BosDizi[3] << endl;
    cout << "Dizinin 5. Elemanin Degeri: " << BosDizi[4] << endl;

    int Matrix[2][2] = {
        { 40, 10 },
        { 50, 20 }
    };

    cout << "Matrix'in 1.Elemanin 1.Degeri: " << Matrix[0][0] << endl;
    cout << "Matrix'in 1.Elemanin 2.Degeri: " << Matrix[0][1] << endl;
    cout << "Matrix'in 2.Elemanin 1.Degeri: " << Matrix[1][0] << endl;
    cout << "Matrix'in 2.Elemanin 2.Degeri: " << Matrix[1][1] << endl;

    int Sayi1 = 100;
    int Sayi2 = 50;

    cout << "Toplama: " << Sayi1 + Sayi2 << endl;
    cout << "Cikarma: " << Sayi1 - Sayi2 << endl;
    cout << "Bolme: " << Sayi1 / Sayi2 << endl;
    cout << "Carpma: " << Sayi1 * Sayi2 << endl;
    cout << "Mod Alma: " << Sayi1 % Sayi2 << endl;

    Sayi1++;
    cout << "Arttirma: " << Sayi1 << endl;
    Sayi2--;
    cout << "Azaltma: " << Sayi2 << endl;

    cout << "Kosulun Sonucu(5 > 4): " << (5 > 4) << endl;
    cout << "Kosulun Sonucu(5 < 4): " << (5 < 4) << endl;
    cout << "Kosulun Sonucu(5 == 5): " << (5 == 5) << endl;
    cout << "Kosulun Sonucu(5 != 4): " << (5 != 4) << endl;
    cout << "Kosulun Sonucu(5 <= 4): " << (5 <= 4) << endl;
    cout << "Kosulun Sonucu(5 >= 5): " << (5 >= 5) << endl;
    cout << "Kosulun Sonucu!(5 >= 5): " << !(5 >= 5) << endl;
    cout << "Kosulun Sonucu(5 >= 5) && (5 < 4): " << ((5 >= 5) && (5 < 4)) << endl;
    cout << "Kosulun Sonucu(5 >= 5) || (5 < 4): " << ((5 >= 5) || (5 < 4)) << endl;
}
