#include <bits/stdc++.h>

using namespace std;

class Person
{
protected:
    string Nama;
    int Umur;
    string Asal;
    int Nilai;

public:
    Person(string nama = "", int umur = 0, string asal = "", int nilai = 0)
    {
        Nama = nama;
        Umur = umur;
        Asal = asal;
        Nilai = nilai;
    };

    string getNama() {
        return Nama; 
    }
    
    void setNama(string nama){ 
        Nama = nama; 
    }

    int getUmur() { 
        return Umur; 
    }
    
    void setUmur(int umur) { 
        Umur = umur; 
    }

    string getAsal(){ 
        return Asal; 
    }
    
    void setAsal(string asal){
        Asal = asal; 
    }

    int getNilai(){ 
        return Nilai; 
    }
    
    void setNilai(int nilai){ 
        Nilai = nilai; 
    }

    virtual void display()
    {
        cout << "Nama  : " << Nama << endl;
        cout << "Umur  : " << Umur << endl;
        cout << "Asal  : " << Asal << endl;
        cout << "Nilai : " << Nilai << endl;
    }
};

class Mahasiswa : public Person
{
private:
    int NRP;
    string Departemen;
    int nrpCounter;

public:
    Mahasiswa(string nama = "", int umur = 0, string asal = "", int nilai = 0, string departemen = "Unknown")
    {
        nrpCounter++;
        NRP = nrpCounter;
        Nama = nama;
        Umur = umur;
        Asal = asal;
        Nilai = nilai;
        Departemen = departemen;
    }

    int getNRP(){ 
        return NRP; 
    }

    void setNRP(int nrp){
        NRP = nrp; 
    }

    string getDepartemen(){ 
        return Departemen; 
    }
    
    void setDepartemen(string departemen){ 
        Departemen = departemen; 
    }

    void display()
    {
        Person::display();
        cout << "NRP        : " << NRP << endl;
        cout << "Departemen : " << Departemen << endl;
    }
};

class PersonManager
{
public:
    void insert(vector<Person> &p)
    {
        string nama, asal;
        int umur, nilai;
        cout << "Masukkan Nama  : ";
        cin.ignore();
        getline(cin, nama);
        cout << "Masukkan Umur  : ";
        cin >> umur;
        cout << "Masukkan Asal  : ";
        cin.ignore();
        getline(cin, asal);
        cout << "Masukkan Nilai : ";
        cin >> nilai;
        p.push_back(Person(nama, umur, asal, nilai));
    }

    void display(vector<Person> &p)
    {
        for (int i = 0; i < p.size(); i++)
        {
            cout << "Person " << i + 1 << endl;
            p[i].display();
            cout << endl;
        }
    }

    void convertToMahasiswa(vector<Person> &p, vector<Mahasiswa> &m, int minimum)
    {
        for (int i = 0; i < p.size(); i++)
        {
            if (p[i].getNilai() >= minimum)
            {
                m.push_back(Mahasiswa(p[i].getNama(), p[i].getUmur(), p[i].getAsal(), p[i].getNilai(), "Unknown"));
                p.erase(p.begin() + i);
                i--;
            }
        }
    }

    void inputDepartemen(vector<Mahasiswa> &m)
    {
        int nrp;
        string departemen;
        cout << "Masukkan NRP mahasiswa yang ingin di-update departemennya: ";
        cin >> nrp;
        cin.ignore();

        bool found = false;
        for (int i = 0; i < m.size(); i++)
        {
            if (m[i].getNRP() == nrp)
            {
                cout << "Masukkan Departemen baru: ";
                getline(cin, departemen);
                m[i].setDepartemen(departemen);
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Mahasiswa dengan NRP " << nrp << " tidak ditemukan." << endl;
        }
    }

    void updatePerson(vector<Person> &p)
    {
        string nama;
        cout << "Masukkan nama person yang ingin di-update: ";
        cin.ignore();
        getline(cin, nama);

        bool found = false;
        for (int i = 0; i < p.size(); i++)
        {
            if (p[i].getNama() == nama)
            {
                string newNama, asal;
                int umur, nilai;
                cout << "Masukkan Nama baru: ";
                getline(cin, newNama);
                cout << "Masukkan Umur baru: ";
                cin >> umur;
                cout << "Masukkan Asal baru: ";
                cin.ignore();
                getline(cin, asal);
                cout << "Masukkan Nilai baru: ";
                cin >> nilai;

                p[i].setNama(newNama);
                p[i].setUmur(umur);
                p[i].setAsal(asal);
                p[i].setNilai(nilai);

                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Person dengan nama " << nama << " tidak ditemukan." << endl;
        }
    }

    void updateMahasiswa(vector<Mahasiswa> &m)
    {
        int option;
        cout << "Pilih opsi pembaruan: " << endl;
        cout << "1. Berdasarkan Nama" << endl;
        cout << "2. Berdasarkan NRP" << endl;
        cout << "Pilihan: ";
        cin >> option;

        switch (option)
        {
        case 1:
            updateMhsbyName(m);
            break;
        case 2:
            updateMhsbyNRP(m);
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
    }

    void updateMhsbyName(vector<Mahasiswa> &m)
    {
        string nama;
        cout << "Masukkan nama mahasiswa yang ingin diperbarui: ";
        cin.ignore();
        getline(cin, nama);
        updateMahasiswaData(m, nama, "nama");
    }

    void updateMhsbyNRP(vector<Mahasiswa> &m)
    {
        int nrp;
        cout << "Masukkan NRP mahasiswa yang ingin diperbarui: ";
        cin >> nrp;
        updateMahasiswaData(m, to_string(nrp), "nrp");
    }

    void updateMahasiswaData(vector<Mahasiswa> &m, const string &dicari, const string &data)
    {
        bool found = false;
        for (int i = 0; i < m.size(); i++)
        {
            if ((data == "nama" && m[i].getNama() == dicari) || (data == "nrp" && m[i].getNRP() == stoi(dicari)))
            {
                string newNama, asal, departemen;
                int umur, nilai;
                cout << "Masukkan Nama baru: ";
                cin.ignore();
                getline(cin, newNama);
                cout << "Masukkan Umur baru: ";
                cin >> umur;
                cout << "Masukkan Asal baru: ";
                cin.ignore();
                getline(cin, asal);
                cout << "Masukkan Nilai baru: ";
                cin >> nilai;
                cin.ignore();
                cout << "Masukkan Departemen baru: ";
                getline(cin, departemen);

                m[i].setNama(newNama);
                m[i].setUmur(umur);
                m[i].setAsal(asal);
                m[i].setNilai(nilai);
                m[i].setDepartemen(departemen);

                found = true;
                if (data == "nama")
                    cout << "Mahasiswa dengan nama " << dicari << " berhasil diperbarui." << endl;
                else if (data == "nrp")
                    cout << "Mahasiswa dengan NRP " << dicari << " berhasil diperbarui." << endl;
                break;
            }
        }

        if (!found)
        {
            if (data == "nama")
                cout << "Mahasiswa dengan nama " << dicari << " tidak ditemukan." << endl;
            else if (data == "nrp")
                cout << "Mahasiswa dengan NRP " << dicari << " tidak ditemukan." << endl;
        }
    }

    void displayMahasiswa(vector<Mahasiswa> &m)
    {
        for (int i = 0; i < m.size(); i++)
        {
            cout << "Mahasiswa " << i + 1 << endl;
            m[i].display();
            cout << endl;
        }
    }

    void displayNonMahasiswa(vector<Person> &p)
    {
        for (int i = 0; i < p.size(); i++)
        {
            p[i].display();
            cout << endl;
        }
    }

    void removePerson(vector<Person> &p)
    {
        string nama;
        cout << "Masukkan nama person yang ingin dihapus: ";
        cin.ignore();
        getline(cin, nama);

        bool found = false;
        for (int i = 0; i < p.size(); ++i)
        {
            if (p[i].getNama() == nama)
            {
                p.erase(p.begin() + i);
                found = true;
                cout << "Person dengan nama " << nama << " berhasil dihapus." << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Person dengan nama " << nama << " tidak ditemukan." << endl;
        }
    }

    void removeMahasiswa(vector<Mahasiswa> &m)
    {
        int option;
        cout << "Pilih opsi penghapusan: " << endl;
        cout << "1. Berdasarkan Nama" << endl;
        cout << "2. Berdasarkan NRP" << endl;
        cout << "Pilihan: ";
        cin >> option;

        switch (option)
        {
        case 1:
            removeMhsbyName(m);
            break;
        case 2:
            removeMhsbyNRP(m);
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
    }

    void removeMhsbyName(vector<Mahasiswa> &m)
    {
        string nama;
        cout << "Masukkan nama mahasiswa yang ingin dihapus: ";
        cin.ignore();
        getline(cin, nama);
        removeMahasiswaBydata(m, nama, "nama");
    }

    void removeMhsbyNRP(vector<Mahasiswa> &m)
    {
        int nrp;
        cout << "Masukkan NRP mahasiswa yang ingin dihapus: ";
        cin >> nrp;
        removeMahasiswaBydata(m, to_string(nrp), "nrp");
    }

    void removeMahasiswaBydata(vector<Mahasiswa> &m, const string &dicari, const string &data)
    {
        bool found = false;
        for (int i = 0; i < m.size(); ++i)
        {
            if ((data == "nama" && m[i].getNama() == dicari) || (data == "nrp" && m[i].getNRP() == stoi(dicari)))
            {
                m.erase(m.begin() + i);
                found = true;
                if (data == "nama")
                    cout << "Mahasiswa dengan nama " << dicari << " berhasil dihapus." << endl;
                else if (data == "nrp")
                    cout << "Mahasiswa dengan NRP " << dicari << " berhasil dihapus." << endl;
                break;
            }
        }

        if (!found)
        {
            if (data == "nama")
                cout << "Mahasiswa dengan nama " << dicari << " tidak ditemukan." << endl;
            else if (data == "nrp")
                cout << "Mahasiswa dengan NRP " << dicari << " tidak ditemukan." << endl;
        }
    }
};

bool authenticate()
{
    const string correctPassword = "FPASIK";
    string inputPassword;
    int attempts = 0;
    const int maxAttempts = 3;

    while (attempts < maxAttempts)
    {
        cout << "Masukkan password untuk mengakses aplikasi: ";
        cin >> inputPassword;

        if (inputPassword == correctPassword)
        {
            cout << "Login berhasil!" << endl;
            return true;
        }
        else
        {
            attempts++;
            cout << "Password salah. Sisa percobaan: " << maxAttempts - attempts << endl;
        }
    }

    cout << "Terlalu banyak percobaan gagal. Nice Try:v" << endl;
    return false;
}

int main()
{
    if (authenticate() == false)
    {
        return 1;
    }

    PersonManager manager;
    vector<Person> p;
    vector<Mahasiswa> m;
    int pilih = 0;
    int subpilih = 0;

    do
    {
        cout << "1. Insert Person" << endl;
        cout << "2. Display" << endl;
        cout << "3. Convert Person to Mahasiswa" << endl;
        cout << "4. Input Departemen Mahasiswa" << endl;
        cout << "5. Update" << endl;
        cout << "6. Remove" << endl;
        // cout << "6. Update Mahasiswa" << endl;
        // cout << "7. Display Mahasiswa" << endl;
        // cout << "8. Display Non Mahasiswa" << endl;
        cout << "7. Exit" << endl
             << endl;

        cout << "Pilih : ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            manager.insert(p);
            break;
        case 2:
            cout << "1. Display Person" << endl;
            cout << "2. Display Mahasiswa" << endl;
            cout << "3. Display Non Mahasiswa" << endl;
            cout << "Pilih : ";
            cin >> subpilih;

            switch (subpilih)
            {
            case 1:
                manager.display(p);
                break;
            case 2:
                if (m.empty())
                {
                    cout << "Belum ada data Mahasiswa" << endl;
                    cout << "Mohon untuk menjalankan Convert to Mahasiswa terlebih dahulu." << endl;
                }
                else
                {
                    manager.displayMahasiswa(m);
                }
                break;
            case 3:
                if (m.empty())
                {
                    cout << "Belum ada data Mahasiswa" << endl;
                    cout << "Mohon untuk menjalankan Convert to Mahasiswa terlebih dahulu." << endl;
                }
                else
                {
                    manager.displayNonMahasiswa(p);
                }
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
                cout << "Mohon untuk menjalankan Convert to Mahasiswa terlebih dahulu." << endl;
                break;
            }
            break;
        case 3:
            int minimum;
            cout << "Masukkan nilai minimum : ";
            cin >> minimum;
            manager.convertToMahasiswa(p, m, minimum);
            break;
        case 4:
            if (m.empty())
            {
                cout << "Belum ada data Mahasiswa" << endl;
                cout << "Mohon untuk menjalankan Convert to Mahasiswa terlebih dahulu." << endl;
            }
            else
            {
                manager.inputDepartemen(m);
            }
            break;
        case 5:
            cout << "1. Update Person" << endl;
            cout << "2. Update Mahasiswa" << endl;
            cout << "Pilih : ";
            cin >> subpilih;
            cout << endl;

            switch (subpilih)
            {
            case 1:
                manager.updatePerson(p);
                break;
            case 2:
                if (m.empty())
                {
                    cout << "Belum ada data Mahasiswa" << endl;
                    cout << "Mohon untuk menjalankan Convert to Mahasiswa terlebih dahulu." << endl;
                }
                else
                {
                    manager.updateMahasiswa(m);
                }
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
            }
            break;
        case 6:
            cout << "1. Remove Person" << endl;
            cout << "2. Remove Mahasiswa" << endl;
            cout << "Pilih : ";
            cin >> subpilih;
            cout << endl;

            switch (subpilih)
            {
            case 1:
                manager.removePerson(p);
                break;
            case 2:
                manager.removeMahasiswa(m);
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
            }
            break;
        case 7:
            cout << "Terima kasih" << endl;
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            break;
        }
    } while (pilih != 7);

    return 0;
}
