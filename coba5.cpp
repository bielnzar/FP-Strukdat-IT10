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
        cout << "Name  : " << Nama << endl;
        cout << "Age   : " << Umur << endl;
        cout << "Origin: " << Asal << endl;
        cout << "Grade : " << Nilai << endl;
    }
};

class Mahasiswa : public Person {
private:
    static int nrpCounter;
    int NRP;
    string Departemen;

public:
    Mahasiswa(string nama = "", int umur = 0, string asal = "", int nilai = 0, string departemen = "Unknown")
        : Person(nama, umur, asal, nilai) {
        NRP = ++nrpCounter;
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
};

int Mahasiswa::nrpCounter = 0;

class PersonManager {
public:
    void insert(vector<Person>& p) {
        string nama, asal;
        int umur, nilai;
        cout << "Enter Name  : ";
        cin.ignore();
        getline(cin, nama);
        cout << "Enter Age   : ";
        cin >> umur;
        cout << "Enter Origin: ";
        cin.ignore();
        getline(cin, asal);
        cout << "Enter Grade : ";
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
        cout << "Enter the name of the person to update: ";
        cin.ignore();
        getline(cin, nama);

        bool found = false;
        for (int i = 0; i < p.size(); i++) {
            if (p[i].getNama() == nama) {
                string newNama, asal;
                int umur, nilai;
                cout << "Enter new Name: ";
                getline(cin, newNama);
                cout << "Enter new Age: ";
                cin >> umur;
                cout << "Enter new Origin: ";
                cin.ignore();
                getline(cin, asal);
                cout << "Enter new Grade: ";
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
        cout << "Enter the name of the student to update: ";
        cin.ignore();
        getline(cin, nama);
        updateMahasiswaData(m, nama, "name");
    }

    void updateMhsbyNRP(vector<Mahasiswa>& m) {
        int nrp;
        cout << "Enter the NRP of the student to update: ";
        cin >> nrp;
        updateMahasiswaData(m, to_string(nrp), "nrp");
    }

    void updateMahasiswaData(vector<Mahasiswa>& m, const string& dicari, const string& data) {
        bool found = false;
        for (int i = 0; i < m.size(); i++) {
            if ((data == "name" && m[i].getNama() == dicari) || (data == "nrp" && m[i].getNRP() == stoi(dicari))) {
                string newNama, asal, departemen;
                int umur, nilai;
                cout << "Enter new Name: ";
                cin.ignore();
                getline(cin, newNama);
                cout << "Enter new Age: ";
                cin >> umur;
                cout << "Enter new Origin: ";
                cin.ignore();
                getline(cin, asal);
                cout << "Enter new Grade: ";
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
};

int main() {
    vector<Person> persons;
    vector<Mahasiswa> mahasiswa;
    PersonManager pm;

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Add Person" << endl;
        cout << "2. Display Persons" << endl;
        cout << "3. Convert Person to Student" << endl;
        cout << "4. Display Students" << endl;
        cout << "5. Input Student Department" << endl;
        cout << "6. Update Person Data" << endl;
        cout << "7. Update Student Data" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            pm.insert(persons);
            break;
        case 2:
            pm.display(persons);
            break;
        case 3:
            int minimum;
            cout << "Enter minimum grade for conversion: ";
            cin >> minimum;
            pm.convertToMahasiswa(persons, mahasiswa, minimum);
            break;
        case 4:
            pm.display(mahasiswa);
            break;
        case 5:
            pm.inputDepartemen(mahasiswa);
            break;
        case 6:
            pm.updatePerson(persons);
            break;
        case 7:
            pm.updateMahasiswa(mahasiswa);
            break;
        case 0:
            cout << "Thank you!" << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
