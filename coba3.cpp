#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // untuk numeric_limits
#include <cstdlib> // untuk system("pause")

using namespace std;

class Person {
protected:
    string Nama;
    int Umur;
    string Asal;
    int Nilai;

public:
    Person(string nama = "", int umur = 0, string asal = "", int nilai = 0)
        : Nama(nama), Umur(umur), Asal(asal), Nilai(nilai) {}

    string getNama() const { return Nama; }
    void setNama(string nama) { Nama = nama; }

    int getUmur() const { return Umur; }
    void setUmur(int umur) { Umur = umur; }

    string getAsal() const { return Asal; }
    void setAsal(string asal) { Asal = asal; }

    int getNilai() const { return Nilai; }
    void setNilai(int nilai) { Nilai = nilai; }

    virtual void display() const {
        cout << "Nama  : " << Nama << endl;
        cout << "Umur  : " << Umur << endl;
        cout << "Asal  : " << Asal << endl;
        cout << "Nilai : " << Nilai << endl;
    }
};

class Mahasiswa : public Person {
private:
    int NRP;
    string Departemen;
    static int nrpCounter;

public:
    Mahasiswa(string nama = "", int umur = 0, string asal = "", int nilai = 0, string departemen = "Unknown")
        : Person(nama, umur, asal, nilai), Departemen(departemen) {
        NRP = ++nrpCounter;
    }

    int getNRP() const { return NRP; }
    void setNRP(int nrp) { NRP = nrp; }

    string getDepartemen() const { return Departemen; }
    void setDepartemen(string departemen) { Departemen = departemen; }

    void display() const {
        Person::display();
        cout << "NRP        : " << NRP << endl;
        cout << "Departemen : " << Departemen << endl;
    }
};

int Mahasiswa::nrpCounter = 0;

class PersonManager {
public:
    void insert(vector<Person> &p) {
        string nama, asal;
        int umur, nilai;

        cout << "=== Student Data Management ===\n";
        cout << "Masukkan Nama  : ";
        cin.ignore();
        getline(cin, nama);

        cout << "Masukkan Umur  : ";
        while (!(cin >> umur)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan umur dalam bentuk angka. Coba lagi: ";
        }

        cout << "Masukkan Asal  : ";
        cin.ignore();
        getline(cin, asal);

        cout << "Masukkan Nilai : ";
        while (!(cin >> nilai)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan nilai dalam bentuk angka. Coba lagi: ";
        }

        cout << "Data berhasil dimasukkan." << endl;
        p.push_back(Person(nama, umur, asal, nilai));
    }

    void display(const vector<Person> &p) const {
        if (p.empty()) {
            cout << "Tidak ada data." << endl;
            return;
        }

        for (int i = 0; i < p.size(); i++) {
            cout << "Person " << i + 1 << endl;
            p[i].display();
            cout << endl;
        }
    }

    void convertToMahasiswa(vector<Person> &p, vector<Mahasiswa> &m, int minimum) {
        for (auto it = p.begin(); it != p.end(); ) {
            if (it->getNilai() >= minimum) {
                m.push_back(Mahasiswa(it->getNama(), it->getUmur(), it->getAsal(), it->getNilai(), "Unknown"));
                it = p.erase(it);
            } else {
                ++it;
            }
        }
    }

    void inputDepartemen(vector<Mahasiswa> &m) {
        int nrp;
        string departemen;
        cout << "Masukkan NRP mahasiswa yang ingin di-update departemennya: ";
        cin >> nrp;
        cin.ignore();

        auto it = find_if(m.begin(), m.end(), [nrp](const Mahasiswa &mhs) {
            return mhs.getNRP() == nrp;
        });

        if (it != m.end()) {
            cout << "Masukkan Departemen baru: ";
            getline(cin, departemen);
            it->setDepartemen(departemen);
            cout << "Departemen berhasil diupdate." << endl;
        } else {
            cout << "Mahasiswa dengan NRP " << nrp << " tidak ditemukan." << endl;
        }
    }

    void updatePerson(vector<Person> &p) {
        string nama;
        cout << "Masukkan nama person yang ingin di-update: ";
        cin.ignore();
        getline(cin, nama);

        auto it = find_if(p.begin(), p.end(), [nama](const Person &person) {
            return person.getNama() == nama;
        });

        if (it != p.end()) {
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

            it->setNama(newNama);
            it->setUmur(umur);
            it->setAsal(asal);
            it->setNilai(nilai);

            cout << "Person berhasil diupdate." << endl;
        } else {
            cout << "Person dengan nama " << nama << " tidak ditemukan." << endl;
        }
    }

    void updateMahasiswa(vector<Mahasiswa> &m) {
        int nrp;
        cout << "Masukkan NRP mahasiswa yang ingin di-update: ";
        cin >> nrp;

        auto it = find_if(m.begin(), m.end(), [nrp](const Mahasiswa &mhs) {
            return mhs.getNRP() == nrp;
        });

        if (it != m.end()) {
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
            cout << "Masukkan Departemen baru: ";
            cin.ignore();
            getline(cin, departemen);

            it->setNama(newNama);
            it->setUmur(umur);
            it->setAsal(asal);
            it->setNilai(nilai);
            it->setDepartemen(departemen);

            cout << "Mahasiswa berhasil diupdate." << endl;
        } else {
            cout << "Mahasiswa dengan NRP " << nrp << " tidak ditemukan." << endl;
        }
    }

    void displayMahasiswa(const vector<Mahasiswa> &m) const {
        if (m.empty()) {
            cout << "Tidak ada data." << endl;
            return;
        }

        for (int i = 0; i < m.size(); i++) {
            cout << "Mahasiswa " << i + 1 << endl;
            m[i].display();
            cout << endl;
        }
    }

    void displayNonMahasiswa(const vector<Person> &p) const {
        if (p.empty()) {
            cout << "Tidak ada data." << endl;
            return;
        }

        for (int i = 0; i < p.size(); i++) {
            p[i].display();
            cout << endl;
        }
    }

    void removePerson(vector<Person> &p) {
        string nama;
        cout << "Masukkan nama person yang ingin dihapus: ";
        cin.ignore();
        getline(cin, nama);

        auto it = find_if(p.begin(), p.end(), [nama](const Person &person) {
            return person.getNama() == nama;
        });

        if (it != p.end()) {
            p.erase(it);
            cout << "Person berhasil dihapus." << endl;
        } else {
            cout << "Person dengan nama " << nama << " tidak ditemukan." << endl;
        }
    }

    void removeMahasiswa(vector<Mahasiswa> &m) {
        int nrp;
        cout << "Masukkan NRP mahasiswa yang ingin dihapus: ";
        cin >> nrp;

        auto it = find_if(m.begin(), m.end(), [nrp](const Mahasiswa &mhs) {
            return mhs.getNRP() == nrp;
        });
            if (it != m.end()) {
            m.erase(it);
            cout << "Mahasiswa berhasil dihapus." << endl;
        } else {
            cout << "Mahasiswa dengan NRP " << nrp << " tidak ditemukan." << endl;
        }
    }

    void findPersonByName(const vector<Person> &p) const {
        string nama;
        cout << "Masukkan nama person yang ingin dicari: ";
        cin.ignore();
        getline(cin, nama);

        auto it = find_if(p.begin(), p.end(), [nama](const Person &person) {
            return person.getNama() == nama;
        });
        if (it != p.end()) {
            cout << "Person ditemukan:" << endl;
            it->display();
        } else {
            cout << "Person dengan nama " << nama << " tidak ditemukan." << endl;
        }
    }

    void findMahasiswaByNRP(const vector<Mahasiswa> &m) const {
        int nrp;
        cout << "Masukkan NRP mahasiswa yang ingin dicari: ";
        cin >> nrp;

        auto it = find_if(m.begin(), m.end(), [nrp](const Mahasiswa &mhs) {
            return mhs.getNRP() == nrp;
        });

        if (it != m.end()) {
            cout << "Mahasiswa ditemukan:" << endl;
            it->display();
        } else {
            cout << "Mahasiswa dengan NRP " << nrp << " tidak ditemukan." << endl;
        }
    }

    void sortPeopleByName(vector<Person> &p) const {
        sort(p.begin(), p.end(), [](const Person &a, const Person &b) {
            return a.getNama() < b.getNama();
        });

        cout << "Data berhasil diurutkan berdasarkan nama secara ascending." << endl;
    }

    void sortMahasiswaByNRP(vector<Mahasiswa> &m) const {
        sort(m.begin(), m.end(), [](const Mahasiswa &a, const Mahasiswa &b) {
            return a.getNRP() < b.getNRP();
        });

        cout << "Data Mahasiswa berhasil diurutkan berdasarkan NRP secara ascending." << endl;
    }

    bool authenticate() const {
        const string correctPassword = "FPASIK";
        string inputPassword;
        int attempts = 0;
        const int maxAttempts = 3;

        while (attempts < maxAttempts) {
            cout << "Masukkan password untuk mengakses aplikasi: ";
            cin >> inputPassword;

            if (inputPassword == correctPassword) {
                cout << "Login berhasil!" << endl;
                return true;
            } else {
                attempts++;
                cout << "Password salah. Sisa percobaan: " << maxAttempts - attempts << endl;
            }
        }

        cout << "Terlalu banyak percobaan gagal. Nice Try:v" << endl;
        return false;
    }
};

int main() {
    PersonManager manager;
    vector<Person> p;
    vector<Mahasiswa> m;
    int pilih = 0;
    int subpilih = 0;

    if (!manager.authenticate()) {
        return 1;
    }

    do {
        cout << "1. Insert Person" << endl;
        cout << "2. Display" << endl;
        cout << "3. Convert Person to Mahasiswa" << endl;
        cout << "4. Input Departemen Mahasiswa" << endl;
        cout << "5. Update" << endl;
        cout << "6. Find data" << endl;
        cout << "7. Sort data" << endl;
        cout << "8. Remove" << endl;
        cout << "9. Exit" << endl << endl;

        cout << "Pilih : ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                manager.insert(p);
                break;
            case 2:
                cout << "1. Display Person" << endl;
                cout << "2. Display Mahasiswa" << endl;
                cout << "3. Display Non Mahasiswa" << endl;
                cout << "Pilih : ";
                cin >> subpilih;

                switch (subpilih) {
                    case 1:
                        manager.display(p);
                        break;
                    case 2:
                        if (m.empty()) {
                            cout << "Belum ada data Mahasiswa" << endl;
                            cout << "Mohon untuk menjalankan Convert to Mahasiswa terlebih dahulu." << endl;
                        } else {
                            manager.displayMahasiswa(m);
                        }
                        break;
                    case 3:
                        if (p.empty()) {
                            cout << "Tidak ada data." << endl;
                        } else {
                            manager.displayNonMahasiswa(p);
                        }
                        break;
                    default:
                        cout << "Pilihan tidak valid" << endl;
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
                if (m.empty()) {
                    cout << "Belum ada data Mahasiswa" << endl;
                    cout << "Mohon untuk menjalankan Convert to Mahasiswa terlebih dahulu." << endl;
                } else {
                    manager.inputDepartemen(m);
                }
                break;
            case 5:
                cout << "1. Update Person" << endl;
                cout << "2. Update Mahasiswa" << endl;
                cout << "Pilih : ";
                cin >> subpilih;
                cout << endl;

                switch (subpilih) {
                    case 1:
                        manager.updatePerson(p);
                        break;
                    case 2:
                        if (m.empty()) {
                            cout << "Belum ada data Mahasiswa" << endl;
                            cout << "Mohon untuk menjalankan Convert to Mahasiswa terlebih dahulu." << endl;
                        } else {
                            manager.updateMahasiswa(m);
                        }
                        break;
                    default:
                        cout << "Pilihan tidak valid" << endl;
                        break;
                }
                break;
            case 6:
                cout << "1. Find Person by Name" << endl;
                cout << "2. Find Mahasiswa by NRP" << endl;
                cout << "Pilih : ";
                cin >> subpilih;
                cout << endl;

                switch (subpilih) {
                    case 1:
                        manager.findPersonByName(p);
                        break;
                    case 2:
                        manager.findMahasiswaByNRP(m);
                        break;
                    default:
                        cout << "Pilihan tidak valid" << endl;
                        break;
                }
                break;
            case 7:
                cout << "1. Sort Person by Name" << endl;
                cout << "2. Sort Mahasiswa by NRP" << endl;
                cout << "Pilih : ";
                cin >> subpilih;
                cout << endl;

                switch (subpilih) {
                    case 1:
                        manager.sortPeopleByName(p);
                        break;
                    case 2:
                        manager.sortMahasiswaByNRP(m);
                        break;
                    default:
                        cout << "Pilihan tidak valid" << endl;
                        break;
                }
                break;
            case 8:
                cout << "1. Remove Person" << endl;
                cout << "2. Remove Mahasiswa" << endl;
                cout << "Pilih : ";
                cin >> subpilih;
                cout << endl;

                switch (subpilih) {
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
            case 9:
                cout << "Terima kasih" << endl;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
        }
    } while (pilih != 9);

    return 0;
}
