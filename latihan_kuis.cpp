#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct buku // struktur data menyimpan data buku
{
    char ID[6];
    char judul[25];
    char penulis[30];
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
const char *nama_file = "data.dat";

void simpan_bukuFile(buku simpan_buku)
{
    FILE *fptr = fopen(nama_file, "a");

    if (fptr == NULL)
    {
        cout << "Tidak, dapat membuka file.\n";
        exit(1);
    }

    fprintf(fptr, "%s | %s | %s | %d\n", simpan_buku.ID, simpan_buku.judul, simpan_buku.penulis, simpan_buku.stok);
    fclose(fptr);
}

void baca_bukuFile()
{
    FILE *fptr = fopen(nama_file, "r");

    if (fptr == NULL)
    {
        cout << "Tidak, dapat membuka file.\n";
        exit(1);
    }

    // ID | judul | nama penulis | stok
    while (fscanf(fptr, "%s %*s %[^|] %*s %[^|] %*s %d\n\n", &daftar_buku[jumlah_buku].ID, &daftar_buku[jumlah_buku].judul, &daftar_buku[jumlah_buku].penulis, &daftar_buku[jumlah_buku].stok) != EOF)
    {
        jumlah_buku++;
    }
}

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
    cin.getline(buku_baru.judul, 25);

    cout << "Penulis Buku \t: "; // memasukkan penulis buku
    cin.getline(buku_baru.penulis, 30);

    cout << "Stok Buku \t: "; // memasukkan stok buku
    cin >> buku_baru.stok;

    // menambahkan data buku baru ke dalam array daftar_buku
    daftar_buku[jumlah_buku] = buku_baru;
    simpan_bukuFile(daftar_buku[jumlah_buku]);
    jumlah_buku++; // menambah jumlah buku yang sudah diinput
    cout << "Buku berhasil ditambahkan!\n";
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
    string kata_kunci; // untuk menyimpan kata kunci pencarian
    cout << "Masukkan Kata Kunci dari judul buku yang dicari : ";
    cin.ignore();
    getline(cin, kata_kunci); // input kata kunci yang dicari

    buku buku_ditemukan[jumlah_buku];
    int jumlahBuku_ditemukan = 0; // menyimpan jumlah buku yang ditetapkan

    // looping mencari buku berdasarkan kata kunci di dalam daftar_buku
    for (int i = 0; i < jumlah_buku; i++)
    {
        if (strstr(daftar_buku[i].judul, kata_kunci.c_str()) != nullptr)
        {
            buku_ditemukan[jumlahBuku_ditemukan] = daftar_buku[i];
            jumlahBuku_ditemukan++;
        }
    }

    if (jumlahBuku_ditemukan == 0) // jika tidak ada buku yang di temukan
    {
        cout << "\nBuku dengan kata kunci " << kata_kunci << " tidak ditemukan.\n";
    }

    else
    {
        cout << "\nBuku dengan kata kunci " << kata_kunci << " ditemukan.\n"; // jika buku di temukan

        cout << "======================================================================\n";
        cout << setw(10) << left << "ID"
             << setw(30) << "Judul"
             << setw(25) << "Penulis"
             << setw(25) << "Stok" << endl;
        cout << "======================================================================\n";

        for (int i = 0; i < jumlah_buku; i++)
        {
            if (strstr(daftar_buku[i].judul, kata_kunci.c_str()) != nullptr)
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
    // menampilkan daftar buku sebelum dihapus agar user dapat melihat ID buku
    tampilkan_buku();

    string id_buku;
    cout << "Masukkan ID Buku yang ingin dihapus : ";
    cin >> id_buku;

    int index_hapus = -1; // index data buku yang akan dihapus

    // mencari buku berdasarkan ID
    for (int i = 0; i < jumlah_buku; i++)
    {
        if (strcmp(daftar_buku[i].ID, id_buku.c_str()) == 0)
        {
            index_hapus = i; // menyimpan index buku yang ditemukan
            break;
        }
    }

    if (index_hapus == -1) // jika buku tidak ditemukan, akan muncul pesan
    {
        cout << "Buku dengan ID " << id_buku << " tidak ditemukan.\n";
        return;
    }
    else
    {
        for (int i = index_hapus; i < jumlah_buku - 1; i++)
        {
            daftar_buku[i] = daftar_buku[i + 1]; // menimpa data ke i dengan data selanjutnya
        }
        jumlah_buku--; // mengurangi jumlah buku karena salah satu buku telah dihapus
        cout << "Buku dengan ID " << id_buku << " berhasil dihapus.\n";

        // save to file mode w
        remove(nama_file);

        for (auto b : daftar_buku)
        {
            simpan_bukuFile(b);
        }
    }
}

int main()
{
    int pilih;
    char kembali;

    User user = login();

    baca_bukuFile();
    do
    {
        cout << "\nHallo, " << user.username << "! SELAMAT DATANG DI DATABASE PERPUSTAKAAN INFORMATIKA!" << endl;
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