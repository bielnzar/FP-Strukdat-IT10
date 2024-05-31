#include <iostream>
#include <string>

using namespace std;

class Mahasiswa {
    public:
        int NRP;
        char Nama [50];
        char Departemen [50];
        char Asal [50];

    int insert(Mahasiswa *m, int d) {
        cout << "Masukkan NRP  : ";
        cin >> m[d].NRP;
        cin.ignore();
        cout << "Masukkan Nama : ";
        cin.getline(m[d].Nama, 50);
        cout << "Masukkan Dept : ";
        cin.getline(m[d].Departemen, 50);
        cout << "Masukkan Asal : ";
        cin.getline(m[d].Asal, 50);
        d++;
        return d;
    }

    void search(Mahasiswa *m, int d) {
        int nrp;
        bool found = false;
        cout << "Masukkan NRP yang dicari : ";
        cin >> nrp;

        for (int i = 0; i < d; i++) {
            if (m[i].NRP == nrp) {
                cout << "NRP   : " << m[i].NRP << endl;
                cout << "Nama  : " << m[i].Nama << endl;
                cout << "Dept. : " << m[i].Departemen << endl;
                cout << "Asal  : " << m[i].Asal << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Mahasiswa dengan NRP : " << nrp << "tidak ditemukan" << endl;
        }
    }

    void display(Mahasiswa *m, int d) {
        for (int i = 0; i < d; i++) {
            cout << "NRP   : " << m[i].NRP << endl;
            cout << "Nama  : " << m[i].Nama << endl;
            cout << "Dept. : " << m[i].Departemen << endl;
            cout << "Asal  : " << m[i].Asal << endl << endl;
        }
    }

    void update(Mahasiswa *m, int d) {
        int nrp;
        bool found = false;
        cout << "Masukkan NRP yang ingin diupdate : ";
        cin >> nrp;
        cin.ignore();

        for (int i = 0; i < d; i++) {
            if (m[i].NRP == nrp) {
                cout << "Masukkan Nama : ";
                cin.getline(m[i].Nama, 50);
                cout << "Masukkan Dept : ";
                cin.getline(m[i].Departemen, 50);
                cout << "Masukkan Asal : ";
                cin.getline(m[i].Asal, 50);

                cout << "Mahasiswa dengan NRP : " << nrp << " berhasil diupdate" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Mahasiswa dengan NRP : " << nrp << "tidak ditemukan" << endl;
        }
    }

    void remove (Mahasiswa *m, int &d) {
        int nrp;
        bool found = false;
        cout << "Masukkan NRP yang ingin dihapus : ";
        cin >> nrp;

        for (int i = 0; i < d; i++) {
            if (m[i].NRP == nrp) {
                for (int j = i; j < d - 1; j++) {
                    m[j] = m[j+1];
                }
                cout << "Mahasiswa dengan NRP : " << nrp << " berhasil dihapus" << endl;
                d--;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Mahasiswa dengan NRP : " << nrp << " tidak ditemukan" << endl;
        }
    }
};

int main() {
    Mahasiswa mhs[100];
    int d = 0;
    int pilih;
    Mahasiswa mhsInstance;

    do {
        cout << endl << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Display" << endl;
        cout << "4. Update" << endl;
        cout << "5. Delete" << endl;
        cout << "4. Exit" << endl;

        cout << "Pilihan : ";
        cin >> pilih;
        switch (pilih) {
            case 1:
                d = mhsInstance.insert(mhs, d);
                break;
            case 2:
                mhsInstance.search(mhs, d); 
                break;
            case 3:
                mhsInstance.display(mhs, d); 
                break;
            case 4:
                mhsInstance.update(mhs, d); 
                break;
            case 5:
                mhsInstance.remove(mhs, d); 
                break;
        }
    } while (pilih != 6);
    return 0;
}
