#include <bits/stdc++.h>

using namespace std;

class Person {
protected:
    string Nama;
    int Umur;
    string Asal;
    int Nilai;

public:
    Person(string nama = "", int umur = 0, string asal = "", int nilai = 0) {
        Nama = nama;
        Umur = umur;
        Asal = asal;
        Nilai = nilai;
    }

    string getNama() {
        return Nama;
    }

    void setNama(string nama) {
        Nama = nama;
    }

    int getUmur() {
        return Umur;
    }

    void setUmur(int umur) {
        Umur = umur;
    }

    string getAsal() {
        return Asal;
    }

    void setAsal(string asal) {
        Asal = asal;
    }

    int getNilai() {
        return Nilai;
    }

    void setNilai(int nilai) {
        Nilai = nilai;
    }

    virtual void display() {
        cout << "Name     : " << Nama << endl;
        cout << "Age      : " << Umur << endl;
        cout << "Residence: " << Asal << endl;
        cout << "Grade    : " << Nilai << endl;
    }
};

class Mahasiswa : public Person {
private:
    static int nrpCounter;
    int NRP;
    string Departemen;

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


    int getNRP() {
        return NRP;
    }

    void setNRP(int nrp) {
        NRP = nrp;
    }

    string getDepartemen() {
        return Departemen;
    }

    void setDepartemen(string departemen) {
        Departemen = departemen;
    }

    void display() override {
        Person::display();
        cout << "NRP       : " << NRP << endl;
        cout << "Department: " << Departemen << endl;
    }

    bool isMahasiswaDataAvailable(vector<Mahasiswa>& m) {
        if (m.empty()) {
            cout << "No Student Data Available" << endl;
            return false;
        }
        return true;
    }
};

int Mahasiswa::nrpCounter = 0;

class PersonManager {
public:
    void insert(vector<Person>& p) {
        string nama, asal;
        int umur, nilai;
        cout << "Enter Name     : ";
        cin.ignore();
        getline(cin, nama);
        cout << "Enter Age      : ";
        cin >> umur;
        cout << "Enter Residence: ";
        cin.ignore();
        getline(cin, asal);
        cout << "Enter Grade    : ";
        cin >> nilai;
        p.push_back(Person(nama, umur, asal, nilai));
    }

    void display(vector<Person>& p) {
        for (int i = 0; i < p.size(); i++) {
            cout << "Person " << i + 1 << endl;
            p[i].display();
            cout << endl;
        }
    }

    void display(vector<Mahasiswa>& m) {
        for (int i = 0; i < m.size(); i++) {
            cout << "Student " << i + 1 << endl;
            m[i].display();
            cout << endl;
        }
    }

    void convertToMahasiswa(vector<Person>& p, vector<Mahasiswa>& m, int minimum) {
        for (int i = 0; i < p.size(); i++) {
            if (p[i].getNilai() >= minimum) {
                m.push_back(Mahasiswa(p[i].getNama(), p[i].getUmur(), p[i].getAsal(), p[i].getNilai(), "Unknown"));
                p.erase(p.begin() + i);
                i--;
            }
        }
    }

    void inputDepartemen(vector<Mahasiswa>& m) {
        int nrp;

        string departemen;
        cout << "Enter the NRP of the student to update the department: ";
        cin >> nrp;
        cin.ignore();

        bool found = false;
        for (int i = 0; i < m.size(); i++) {
            if (m[i].getNRP() == nrp) {
                cout << "Enter new Department: ";
                getline(cin, departemen);
                m[i].setDepartemen(departemen);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Student with NRP " << nrp << " not found." << endl;
        }
    }

    void updatePerson(vector<Person>& p) {
        string nama;
        cout << "Enter the name of the person to update : ";
        cin.ignore();
        getline(cin, nama);

        bool found = false;
        for (int i = 0; i < p.size(); i++) {
            if (p[i].getNama() == nama) {
                string newNama, asal;
                int umur, nilai;
                cout << "Enter new Name     : ";
                getline(cin, newNama);
                cout << "Enter new Age      : ";
                cin >> umur;
                cout << "Enter new Residence: ";
                cin.ignore();
                getline(cin, asal);
                cout << "Enter new Grade    : ";
                cin >> nilai;

                p[i].setNama(newNama);
                p[i].setUmur(umur);
                p[i].setAsal(asal);
                p[i].setNilai(nilai);

                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Person with name " << nama << " not found." << endl;
        }
    }

    void updateMahasiswa(vector<Mahasiswa>& m) {
        int option;
        cout << "Select update option: " << endl;
        cout << "1. By Name" << endl;
        cout << "2. By NRP" << endl;
        cout << "Choice: ";
        cin >> option;

        switch (option) {
        case 1:
            updateMhsbyName(m);
            break;
        case 2:
            updateMhsbyNRP(m);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    }

    void updateMhsbyName(vector<Mahasiswa>& m) {
        string nama;
        cout << "Enter the name of the student to update : ";
        cin.ignore();
        getline(cin, nama);
        updateMahasiswaData(m, nama, "name");
    }

    void updateMhsbyNRP(vector<Mahasiswa>& m) {
        int nrp;
        cout << "Enter the NRP of the student to update : ";
        cin >> nrp;
        updateMahasiswaData(m, to_string(nrp), "nrp");
    }

    void updateMahasiswaData(vector<Mahasiswa>& m, const string& dicari, const string& data) {
        bool found = false;
        for (int i = 0; i < m.size(); i++) {
            if ((data == "name" && m[i].getNama() == dicari) || (data == "nrp" && m[i].getNRP() == stoi(dicari))) {
                string newNama, asal, departemen;
                int umur, nilai;
                cout << "Enter new Name     : ";
                cin.ignore();
                getline(cin, newNama);
                cout << "Enter new Age      : ";
                cin >> umur;
                cout << "Enter new Residence: ";
                cin.ignore();
                getline(cin, asal);
                cout << "Enter new Grade    : ";
                cin >> nilai;
                cin.ignore();
                cout << "Enter new Department: ";
                getline(cin, departemen);

                m[i].setNama(newNama);
                m[i].setUmur(umur);
                m[i].setAsal(asal);
                m[i].setNilai(nilai);
                m[i].setDepartemen(departemen);

                found = true;
                if (data == "name")
                    cout << "Student with name " << dicari << " successfully updated." << endl;
                else if (data == "nrp")
                    cout << "Student with NRP " << dicari << " successfully updated." << endl;
                break;
            }
        }

        if (!found) {
            if (data == "name")
                cout << "Student with name " << dicari << " not found." << endl;
            else if (data == "nrp")
                cout << "Student with NRP " << dicari << " not found." << endl;
        }
    }

    void removePerson(vector<Person> &p)
    {
        string nama;
        cout << "Masukkan nama person yang ingin dihapus : ";
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
        cout << "Pilih opsi penghapusan : " << endl;
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
        cout << "Masukkan nama mahasiswa yang ingin dihapus : ";
        cin.ignore();
        getline(cin, nama);
        removeMahasiswaBydata(m, nama, "nama");
    }

    void removeMhsbyNRP(vector<Mahasiswa> &m)
    {
        int nrp;
        cout << "Masukkan NRP mahasiswa yang ingin dihapus : ";
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

void clearScreen() {
        system("cls");
        system("clear");
}

int main() {
    vector<Person> persons;
    vector<Mahasiswa> mahasiswa;
    PersonManager pm;
    int subchoice;

    int choice;
    do {
        clearScreen();

        cout << endl << "=============>>>>>>> Student Data Management System <<<<<<<=============" << endl;
        cout << endl << "Main Menu :" << endl;
        cout << "1. Add Person" << endl;
        cout << "2. Display" << endl;
        cout << "3. Convert Person to Student" << endl;
        cout << "4. Input Student Department" << endl;
        cout << "5. Update" << endl;
        cout << "6. Remove" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            cout << "### Add Person ###" << endl;
            pm.insert(persons);
            break;
        case 2:
            cout << "### Display Menu ###" << endl;
            cout << "1. Display Persons" << endl;
            cout << "2. Display Students" << endl;
            cout << "0. Exit" << endl;
            cout << "Choice: ";
            cin >> subchoice;
            cout << endl;
            switch (subchoice){
            case 1:
                pm.display(persons);
                break;
            case 2:
            if( mahasiswa.size() == 0){
                cout << endl << "No student data available." << endl << endl;
                break;
            }
            else{
                pm.display(mahasiswa);
                break;
            }
            case 0:
                cout << "Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice." << endl;
                break;
            }
            break;
        case 3:
            cout << "### Convert Person to Student ###" << endl;

            int minimum;
            cout << "Enter minimum grade for conversion: ";
            cin >> minimum;
            pm.convertToMahasiswa(persons, mahasiswa, minimum);
            break;
        case 4:
            cout << "### Input Student Department ###" << endl;
            if( mahasiswa.size() == 0){
                cout << endl << "No student data available." << endl << endl;
                break;
            }
            else{
            pm.display(mahasiswa);
            pm.inputDepartemen(mahasiswa);
            break;
            }
        case 5:
            cout << "### Update Menu ###" << endl;

            cout << "1. Update Person" << endl;
            cout << "2. Update Student" << endl;
            cout << "0. Exit" << endl;
            cout << "Choice: ";
            cin >> subchoice;
            cout << endl;
            switch (subchoice)
                {
                case 1:
                    if( persons.size() == 0){
                        cout << "No person data available." << endl << endl;
                        break;
                    }
                    else{
                    pm.updatePerson(persons);
                    break;
                    }
                case 2:
                    if( mahasiswa.size() == 0){
                        cout << endl << "No student data available." << endl << endl;
                        break;
                    }
                    else{
                    pm.updateMahasiswa(mahasiswa);
                    break;
                    }
                case 0:
                    cout << "Thank you!" << endl;
                    return 0;
                default:
                    cout << "Invalid choice." << endl;
                    break;
                }
            break;
        case 6:
            cout << "### Remove Menu ###" << endl;

            cout << "1. Remove Person" << endl;
            cout << "2. Remove Student" << endl;
            cout << "0. Exit" << endl;
            cout << "Choice: ";
            cin >> subchoice;

            switch (subchoice)
                {
                case 1:
                    if( persons.size() == 0){
                        cout << "No person data available." << endl << endl;
                        break;
                    }
                    else{
                        pm.removePerson(persons);
                    break;
                    }
                case 2:
                    int subsubchoice;
                    cout << "1. Remove Student by Name" << endl;
                    cout << "2. Remove Student by NRP" << endl;
                    cout << "0. Exit" << endl;
                    cout << "Choice: ";
                    cin >> subsubchoice;
                    cout << endl;

                    switch (subsubchoice){
                        case 1:
                        if( mahasiswa.size() == 0){
                            cout << endl << "No student data available." << endl << endl;
                            break;
                        }
                        else{ 
                            pm.display(mahasiswa);
                            pm.removeMhsbyName(mahasiswa);
                            break;
                        }
                        case 2:
                        if( mahasiswa.size() == 0){
                            cout << endl << "No student data available." << endl << endl;
                            break;
                        }
                        else{
                            pm.display(mahasiswa);
                            pm.removeMhsbyNRP(mahasiswa);
                            break;
                        }
                        case 0:
                            cout << "Thank you!" << endl;
                            return 0;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                    }
                break;
                case 0:
                    cout << "Thank you!" << endl;
                    return 0; 
                default:
                    cout << "Invalid choice." << endl;
                    break;
                }
        case 0:
            cout << "Thank you!" << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
        cout << endl << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 0);

    return 0;
}
