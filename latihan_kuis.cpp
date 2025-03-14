#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct buku // struktur data menyimpan data buku
{
    char ID[5];
    string judul;
    string penulis;
    int stok;
};

struct User // struktur data menyimpan data user atau pemakai program
{
    string username;
    string password;
};

const int max_buku = 100;   // kapasitas maksimal data buku
buku daftar_buku[max_buku]; // array untuk menyimpan data buku
int jumlah_buku = 0;        // jumlah data buku yang sudah diinput

User login() // fungsi login untuk memasukkan username dan password
{

    User user;
    cout << "\nLOGIN KE DATABASE PERPUSTARAKAAN!\n";

    while (true) // looping sampai login berhasil
    {
        cout << "Username : ";
        cin >> user.username; // memasukkan username
        cout << "Password : ";
        cin >> user.password; // memasukkan password

        if (user.username == "eva" && user.password == "156") // mengecek username dan password sesuai atau tidak
        {
            cout << "==== BERHASIL LOGIN ====\n";
            break; // keluar dari looping jika login berhasil
        }
        else
        {
            cout << "\nUsername atau password salah.\n"; // pesan eror jika login gagal
        }
    }
    return user;
}

void tambah_buku()
{

    if (jumlah_buku >= max_buku) // cek apakah jumlah buku penuh atau tidak
    {
        cout << "Database penuh, tidak bisa menambah data buku.\n";
        return; // keluar dari fungsi jika penuh
    }

    buku buku_baru; // variabel untuk menyimpan data buku baru

    cout << "==== Tambah Data Buku ====\n";
    cout << "ID Buku \t: "; // memasukkan ID buku
    cin >> buku_baru.ID;
    cin.ignore();

    cout << "Judul Buku \t: "; // memasukkan judul buku
    getline(cin, buku_baru.judul);

    cout << "Penulis Buku \t: "; // memasukkan penulis buku
    getline(cin, buku_baru.penulis);

    cout << "Stok Buku \t: "; // memasukkan stok buku
    cin >> buku_baru.stok;

    // menambahkan data buku baru ke dalam array daftar_buku
    daftar_buku[jumlah_buku] = buku_baru;
    jumlah_buku++; // menambah jumlah buku yang sudah diinput
    cout << "Buku berhasil ditambahkan!\n";

    FILE *fptr = fopen("data.dat", "ab"); // membuka file data.dat

    if (fptr == NULL) // cek apakah file berhasil dibuka atau tidak
    {
        cout << "Error! Tidak bisa membuka file.\n";
        exit(1);
    }
    fwrite(&buku_baru, sizeof(buku), 1, fptr); // menyimpan data buku ke dalam file
    fclose(fptr);                              // menutup file data.dat
}

void tampilkan_buku()
{
    if (jumlah_buku == 0) // mengecek apakah data buku kosong atau tidak
    {
        cout << "Database kosong, tidak ada data buku.\n";
        return;
    }

    // sorting bubble sort secara ascending berdasarkan id buku
    for (int i = 0; i < jumlah_buku - 1; i++) // looping untuk melakukan sorting
    {
        for (int j = 0; j < jumlah_buku - i - 1; j++) // membandingkan elemen yang berdekatan
        {
            if ((daftar_buku[j].ID, daftar_buku[j + 1].ID) > 0) // jika id buku lebih besar maka tukar posisi
            {
                // tukar posisi buku (swap)
                buku temp = daftar_buku[j];
                daftar_buku[j] = daftar_buku[j + 1];
                daftar_buku[j + 1] = temp;
            }
        }
    }

    // menampilkan data buku dalam format tabel
    cout << "======================================================================\n";
    cout << setw(10) << left << "ID"
         << setw(30) << "Judul"
         << setw(25) << "Penulis"
         << setw(25) << "Stok" << endl;
    cout << "======================================================================\n";

    // looping untuk menampilkan data buku yang sudah diurutkan
    for (int i = 0; i < jumlah_buku; i++)
    {
        cout << setw(10) << left << daftar_buku[i].ID    // menampilkan ID buku
             << setw(30) << daftar_buku[i].judul         // menampilkan judul buku
             << setw(25) << daftar_buku[i].penulis       // menampilkan penulis buku
             << setw(25) << daftar_buku[i].stok << endl; // menampilkan stok buku
    }
    cout << "======================================================================\n";
}

void cari_buku()
{
    string kata_kunci;
    cout << "Masukkan Kata Kunci dari judul buku yang dicari : ";
    cin.ignore();
    getline(cin, kata_kunci);

    buku buku_ditemukan[jumlah_buku];
    int jumlahBuku_ditemukan = 0;

    for (int i = 0; i < jumlah_buku; i++)
    {
        if (daftar_buku[i].judul.find(kata_kunci) != string::npos)
        {
            buku_ditemukan[jumlahBuku_ditemukan] = daftar_buku[i];
            jumlahBuku_ditemukan++;
        }
    }

    if (jumlahBuku_ditemukan == 0)
    {
        cout << "\nBuku dengan kata kunci " << kata_kunci << " tidak ditemukan.\n";
    }

    else
    {
        cout << "\nBuku dengan kata kunci " << kata_kunci << " ditemukan.\n";

        cout << "======================================================================\n";
        cout << setw(10) << left << "ID"
             << setw(30) << "Judul"
             << setw(25) << "Penulis"
             << setw(25) << "Stok" << endl;
        cout << "======================================================================\n";

        for (int i = 0; i < jumlah_buku; i++)
        {
            if (daftar_buku[i].judul.find(kata_kunci) != string::npos)
            {
                cout << setw(10) << left << daftar_buku[i].ID
                     << setw(30) << daftar_buku[i].judul
                     << setw(25) << daftar_buku[i].penulis
                     << setw(25) << daftar_buku[i].stok << endl;
            }
        }
        cout << "======================================================================\n";
    }
}

void hapus_buku()
{
    tampilkan_buku();

    string id_buku;
    cout << "Masukkan ID Buku yang ingin dihapus : ";
    cin >> id_buku;

    int index_hapus = -1; // index data buku yang akan dihapus

    for (int i = 0; i < jumlah_buku; i++)
    {
        if (strcmp(daftar_buku[i].ID, id_buku.c_str()) == 0)
        {
            index_hapus = i;
            break;
        }
    }

    if (index_hapus == -1)
    {
        cout << "Buku dengan ID " << id_buku << " tidak ditemukan.\n";
        return;
    }
    else
    {
        for (int i = index_hapus; i < jumlah_buku - 1; i++)
        {
            daftar_buku[i] = daftar_buku[i + 1];
        }
        jumlah_buku--;
        cout << "Buku dengan ID " << id_buku << " berhasil dihapus.\n";
    }

    // tampilkan data buku
    // minta user input ID yang mau dihapus
    // cari apakah ada datanya?
    // jika ada, maka hapus dari array lalu tampilkan data buku
    // save file lagi sama kayak kamu input, tapi sekarang semua data di daftar buku
}

int main()
{
    int pilih;
    char kembali;

    // User user = login();

    // Baca data data yang ada di file fread
    do
    {
        // cout << "\nHallo, " << user.username << "! SELAMAT DATANG DI DATABASE PERPUSTAKAAN INFORMATIKA!" << endl;
        cout << "1. Tambah Data Buku" << endl;
        cout << "2. Tampilkan Daftar Buku" << endl;
        cout << "3. Cari Buku" << endl;
        cout << "4. Hapus Buku" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih Menu : ";

        cin >> pilih;

        system("cls");

        switch (pilih)
        {
        case 1:
            tambah_buku();
            break;
        case 2:
            tampilkan_buku();
            break;
        case 3:
            cari_buku();
            break;
        case 4:
            hapus_buku();
            break;
        case 5:
            cout << "Terima kasih, program akan ditutup.\n";
            return 0;
        }

        cout << "Apakah Ingin Kembali Ke Menu? (y/n) ";
        cin >> kembali;

    } while (kembali == 'y');

    return 0;
}