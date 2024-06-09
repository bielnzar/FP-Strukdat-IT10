#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // untuk numeric_limits

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

public:
    Mahasiswa(string nama = "", int umur = 0, string asal = "", int nilai = 0, int nrp = 0, string departemen = "Unknown")
        : Person(nama, umur, asal, nilai), NRP(nrp), Departemen(departemen) {}

    int getNRP() const { return NRP; }
    void setNRP(int nrp) { NRP = nrp; }

    string getDepartemen() const { return Departemen; }
    void setDepartemen(string departemen) { Departemen = departemen; }

    void display() const override {
        Person::display();
        cout << "NRP        : " << NRP << endl;
        cout << "Departemen : " << Departemen << endl;
    }
};

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
                int nrp;
                cout << "Masukkan NRP untuk " << it->getNama() << ": ";
                while (!(cin >> nrp)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Masukkan NRP dalam bentuk angka. Coba lagi: ";
                }

                bool nrpExists = any_of(m.begin(), m.end(), [nrp](const Mahasiswa &mhs) {
                    return mhs.getNRP() == nrp;
                });

                if (nrpExists) {
                    cout << "NRP " << nrp << " sudah ada. Coba lagi." << endl;
                } else {
                    m.push_back(Mahasiswa(it->getNama(), it->getUmur(), it->getAsal(), it->getNilai(), nrp, "Unknown"));
                    it = p.erase(it);
                }
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
            while (!(cin >> umur)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan umur dalam bentuk angka. Coba lagi: ";
            }
            cout << "Masukkan Asal baru: ";
            cin.ignore();
            getline(cin, asal);
            cout << "Masukkan Nilai baru: ";
            while (!(cin >> nilai)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan nilai dalam bentuk angka. Coba lagi: ";
            }

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
        cin.ignore();

        auto it = find_if(m.begin(), m.end(), [nrp](const Mahasiswa &mhs) {
            return mhs.getNRP() == nrp;
        });

        if (it != m.end()) {
            string newNama, asal, departemen;
            int umur, nilai;
            cout << "Masukkan Nama baru: ";
            getline(cin, newNama);
            cout << "Masukkan Umur baru: ";
            while (!(cin >> umur)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan umur dalam bentuk angka. Coba lagi: ";
            }
            cout << "Masukkan Asal baru: ";
            cin.ignore();
            getline(cin, asal);
            cout << "Masukkan Nilai baru: ";
            while (!(cin >> nilai)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan nilai dalam bentuk angka. Coba lagi: ";
            }
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
            cout << "Non-Mahasiswa " << i + 1 << endl;
            p[i].display();
            cout << endl;
        }
    }

    void filterByMinNilai(const vector<Person> &p, int minNilai) const {
        if (p.empty()) {
            cout << "Tidak ada data." << endl;
            return;
        }

        vector<Person> filtered;
        for (const auto &person : p) {
            if (person.getNilai() >= minNilai) {
                filtered.push_back(person);
            }
        }

        if (filtered.empty()) {
            cout << "Tidak ada Person dengan nilai di atas " << minNilai << "." << endl;
            return;
        }

        cout << "Person dengan nilai di atas " << minNilai << ":" << endl;
        for (const auto &person : filtered) {
            person.display();
            cout << endl;
        }
    }
};

int main() {
    PersonManager manager;
    vector<Person> persons;
    vector<Mahasiswa> mahasiswas;
    int choice;

    do {
        cout << "=== Menu ===" << endl;
        cout << "1. Insert Person" << endl;
        cout << "2. Display Persons" << endl;
        cout << "3. Convert Person to Mahasiswa" << endl;
        cout << "4. Input Departemen Mahasiswa" << endl;
        cout << "5. Update Person" << endl;
        cout << "6. Update Mahasiswa" << endl;
        cout << "7. Display Mahasiswa" << endl;
        cout << "8. Display Non-Mahasiswa" << endl;
        cout << "9. Filter Person by Min Nilai" << endl;
        cout << "0. Exit" << endl;
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.insert(persons);
                break;
            case 2:
                manager.display(persons);
                break;
            case 3: {
                int minNilai;
                cout << "Masukkan nilai minimum untuk konversi: ";
                cin >> minNilai;
                manager.convertToMahasiswa(persons, mahasiswas, minNilai);
                break;
            }
            case 4:
                manager.inputDepartemen(mahasiswas);
                break;
            case 5:
                manager.updatePerson(persons);
                break;
            case 6:
                manager.updateMahasiswa(mahasiswas);
                break;
            case 7:
                manager.displayMahasiswa(mahasiswas);
                break;
            case 8:
                manager.displayNonMahasiswa(persons);
                break;
            case 9: {
                int minNilai;
                cout << "Masukkan nilai minimum untuk filter: ";
                cin >> minNilai;
                manager.filterByMinNilai(persons, minNilai);
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
