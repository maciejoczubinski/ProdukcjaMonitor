#pragma once
#include <afxdb.h>
#include <vector>
#include <string>

// Struktury danych odpowiadaj¹ce tabelom w bazie
struct Operator
{
    int     ID_Operatora;
    CString Imie;
    CString Nazwisko;
    CString Stanowisko;
    CString NrTelefonu;
    CString Haslo;
};

struct Maszyna
{
    int    ID_Maszyny;
    CString Nazwa;
    CString Typ;
    CString NrSeryjny;
    CString Lokalizacja;
};

struct Zlecenie
{
    int    ID_Zlecenia;
    CString Nazwa;
    int    Ilosc;
    CString Termin;
};

struct Zadanie
{
    int    ID_Zadania;
    int    ID_Operatora;
    int    ID_Maszyny;
    int    ID_Zlecenia;
    CString DataRozpoczecia;
    CString DataZakonczenia;
    CString Status;
    // Pola pomocnicze do wyœwietlania w liœcie. W bazie danych tabela Zadania przechowuje tylko liczby a w aplikacji uzytkownik chce widziec nazwy
    CString NazwaOperatora;
    CString NazwaMaszyny;
    CString NazwaZlecenia;
};

class Database
{
public:
    Database();
    ~Database();

    bool        Connect();
    void        Disconnect();
    bool        IsConnected();

    // Operatorzy
    std::vector<Operator>  GetOperatorzy();

    // Maszyny
    std::vector<Maszyna>   GetMaszyny();

    // Zlecenia
    std::vector<Zlecenie>  GetZlecenia();

    // Zadania
    std::vector<Zadanie>   GetZadania();

    //czy sie udalo
    bool                   AddZadanie(const Zadanie& z);
    bool                   UpdateStatus(int idZadania, const CString& status);
    bool                   DeleteZadanie(int idZadania);

private:
    CDatabase m_db;
};