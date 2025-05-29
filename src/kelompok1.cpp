// Kelompok 1
#include <iostream>
#include <iomanip>
using namespace std;

struct node {
    string penjaga;
    string nim;
    int shift = 0;
    node*next;
};

//menambah penjaga di bagian belakang
void tambahPenjaga(node *&head, string penjaga_b, string nim_b){
    node *nodeBaru = new node;
    nodeBaru->penjaga = penjaga_b;
    nodeBaru->nim = nim_b;

    if (head == nullptr){
        nodeBaru->shift = 1;
        nodeBaru->next = nodeBaru;
        head = nodeBaru;

    } else {
        node *tail = head;
        while(tail->next != head){
            tail = tail->next;
        }
        tail->next = nodeBaru;
        nodeBaru->shift = tail->shift + 1;
        nodeBaru->next = head;
    }
    cout << setw(10) << "Penjaga dengan nama " << penjaga_b << " dan NIM " << nim_b
         << " berhasil ditambahkan.. , shift " << nodeBaru->shift << endl;
}

// Fungsi untuk memundurkan shift setelah dihapus
void mundurkanShift (node *&head, node *&mulai){
    if(mulai->next == head || head == nullptr) return;

    node *temp = mulai->next;
    do{
        temp->shift -= 1;
        temp = temp->next;
    } while (temp != head);
}

//menghapus penjaga berdasarkan NIM
void hapusPenjaga (node *&head, string nim_hapus){
    if(head == nullptr){
        cout << "Shift Kosong\n";
        return;
    }

    node *dihapus = head;
    node *prev = nullptr;

    do{
        if(dihapus->nim == nim_hapus){
            char opsi;
            do{ // Konfirmasi penghapusan
                cout << "Apakah anda ingin menghapus " << dihapus->penjaga << " (" << dihapus->nim << ") ? [Y/n] : "; cin >> opsi;
                if(opsi != 'Y' && opsi != 'y' && opsi != 'N' && opsi != 'n') cout << "Opsi tidak valid.." << endl;
            }while(opsi != 'Y' && opsi != 'y' && opsi != 'N' && opsi != 'n');
            
            // Menghapus jika opsi 'Y'
            if (opsi == 'Y' || opsi == 'y'){
                cout << "Menghapus " << dihapus->penjaga << " (" << dihapus->nim
                     << "), shift " << dihapus->shift << endl;
                mundurkanShift(head, dihapus);
                if (dihapus == head && dihapus->next == head){
                    delete head;
                    head = nullptr;
                } else if (dihapus == head){
                    node *tail = head;
                    while (tail->next != head){
                        tail = tail->next;
                    }
                    head = head->next;
                    tail->next = head;
                    delete dihapus;
                }else{
                    prev->next = dihapus->next;
                    delete dihapus;
                }
                return;
            }else{
                return;
            }
        }
        prev = dihapus;
        dihapus = dihapus->next;
    } while (dihapus != head);
    cout << "Penjaga dengan NIM " << nim_hapus << " tidak ditemukan..\n";
}

// Fungsi untuk menampilkan semua data penjaga
void tampilDaftarPenjaga (node *head){
    // Cek apakah data kosong
    if (head == nullptr){
        cout << "List Kosong\n";
        return;
    }

    // Tampikan
    cout << "\n---------------------------------------------------------\n"
         << left << setw(20) << "| Nama Penjaga" << setw(20) << "| NIM"
         << setw(10) << "| Shift" << "|\n"
         << "---------------------------------------------------------\n";

    node *temp = head;
    do{
        cout << "| " << left << setw(18) << temp->penjaga << "| " << setw(18) << temp->nim
             << "| " << setw(8) << temp->shift << "|\n";
        temp = temp->next;
    }while (temp != head);
    cout << "---------------------------------------------------------\n\n";
}

// Fungsi untuk simulasi rotasi
void shiftSetelah (node *head,string nama, int x){

    // Cek apakah data kosong
    if (head == nullptr) {
        cout << "Data Kosong\n";
        return;
    }

    // Cari nama penjaga di dalam list
    node *cari = head;
    do{
        if(cari->penjaga == nama){
            for (int i = 0; i < x; i++){
                cari = cari->next;
            }
            cout << x << " shift setelah " << nama << " adalah " << cari->penjaga << endl;
            return;
        }
        cari = cari->next;
    }while (cari != head);
    
    cout << setw(10) << "Data tidak ditemukan..." << endl;
}

// Fungsi utama
int main(){

    node *data = nullptr;

    string nama, nim;
    int opsi;

    do{
        cout << "\n ========================================" << endl;
        cout << "| Sistem Rotasi Penjaga Stand Pameran TI |" << endl;
        cout << " ========================================" << endl;
        cout << "\t[1] Tambah penjaga\n\t[2] Hapus penjaga\n\t[3] Tampilkan penjaga\n\t[4] Simulasi rotasi\n\t[5] Keluar\nPilihan >> "; cin >> opsi;
        cin.ignore();
    
        switch(opsi){
            case 1: // Menu tambah data
                cout << setw(5) << "\n===== Input Data Penjaga =====\n";
                cout << setw(10) << "Nama\t: "; getline(cin, nama);
                cout << setw(9) << "Nim\t: "; cin >> nim;
                tambahPenjaga(data, nama, nim);
                break;
            case 2: // Menu Hapus data
                cout << setw(5) << "\n===== Hapus Data Penjaga =====\n";
                cout << setw(10) << "Masukkan Nim : "; cin >> nim;
                hapusPenjaga(data, nim);
                break;
            case 3: // Menu menampilkan data
                tampilDaftarPenjaga(data);
                break;
            case 4: // Menu simulasi rotasi
                int x;
                cout << left << setw(5) << "\n========== Simulasi Rotasi ==========\n";
                cout << setw(10) << "Masukkan nama penjaga\t\t: ";getline(cin, nama);
                cout << setw(10) << "Masukkan shift setelahnya\t: "; cin >> x;
                shiftSetelah(data, nama, x);
                break;
            case 5:
                cout << "Keluar program..." << endl;
                return 0;
            default:
                cout << "Opsi tidak ditemukan..." << endl;
                continue;
        }
    }while(true);

    return 0;
}