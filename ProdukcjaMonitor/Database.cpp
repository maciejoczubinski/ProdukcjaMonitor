#include "pch.h"
#include "Database.h"


// Konstruktor który jest pusty bo obiekt CDatabase m_db który jest polem klasy tworzy siê automatycznie
Database::Database()
{
}
// Destruktor wywo³ywany automatycznie gdy obiekt Database przestaje istnieæ. Wywo³uje Disconnect() ¿eby zamkn¹æ po³¹czenie z baz¹.
Database::~Database()
{
    Disconnect();
}

bool Database::Connect()
{
    try
    {
        CString connectionString =
            _T("DRIVER={SQL Server};"
                "SERVER=localhost\\SQLEXPRESS01;"
                "DATABASE=system_monitorowania;"
                "Trusted_Connection=yes;");

        m_db.OpenEx(connectionString, CDatabase::noOdbcDialog);
        return true;
    } // £apiemy wyj¹tki,(CDBException) to specjalny typ wyj¹tku MFC dla b³êdów bazy danych.
    catch (CDBException* e)
    {
        e->Delete();
        return false;
    }
}

void Database::Disconnect()
{
    if (m_db.IsOpen())
        m_db.Close();
}

bool Database::IsConnected()
{
    return m_db.IsOpen();
}

std::vector<Operator> Database::GetOperatorzy()
{
    std::vector<Operator> lista;
    if (!m_db.IsOpen()) return lista;

    try
    {
        CRecordset rs(&m_db);
        rs.Open(CRecordset::forwardOnly,
            _T("SELECT ID_Operatora, Imie, Nazwisko, Stanowisko, NrTelefonu, Haslo FROM Operatorzy"));

        while (!rs.IsEOF())
        {
            Operator op;
            CString val;

            rs.GetFieldValue((short)0, val); op.ID_Operatora = _ttoi(val);
            rs.GetFieldValue((short)1, op.Imie);
            rs.GetFieldValue((short)2, op.Nazwisko);
            rs.GetFieldValue((short)3, op.Stanowisko);
            rs.GetFieldValue((short)4, op.NrTelefonu);
            rs.GetFieldValue((short)5, op.Haslo);

            lista.push_back(op);
            rs.MoveNext();
        }
        rs.Close();
    }
    catch (CDBException* e)
    {
        e->Delete();
    }
    return lista;
}

std::vector<Maszyna> Database::GetMaszyny()
{
    std::vector<Maszyna> lista;
    if (!m_db.IsOpen()) return lista;

    try
    {
        CRecordset rs(&m_db);
        rs.Open(CRecordset::forwardOnly,
            _T("SELECT ID_Maszyny, Nazwa, Typ, NrSeryjny, Lokalizacja FROM Maszyny"));

        while (!rs.IsEOF())
        {
            Maszyna m;
            CString val;

            rs.GetFieldValue((short)0, val); m.ID_Maszyny = _ttoi(val);
            rs.GetFieldValue((short)1, m.Nazwa);
            rs.GetFieldValue((short)2, m.Typ);
            rs.GetFieldValue((short)3, m.NrSeryjny);
            rs.GetFieldValue((short)4, m.Lokalizacja);

            lista.push_back(m);
            rs.MoveNext();
        }
        rs.Close();
    }
    catch (CDBException* e)
    {
        e->Delete();
    }
    return lista;
}

std::vector<Zlecenie> Database::GetZlecenia()
{
    std::vector<Zlecenie> lista;
    if (!m_db.IsOpen()) return lista;

    try
    {
        CRecordset rs(&m_db);
        rs.Open(CRecordset::forwardOnly,
            _T("SELECT ID_Zlecenia, Nazwa, Ilosc, Termin FROM Zlecenia"));

        while (!rs.IsEOF())
        {
            Zlecenie z;
            CString val;

            rs.GetFieldValue((short)0, val); z.ID_Zlecenia = _ttoi(val);
            rs.GetFieldValue((short)1, z.Nazwa);
            rs.GetFieldValue((short)2, val); z.Ilosc = _ttoi(val);
            rs.GetFieldValue((short)3, z.Termin);

            lista.push_back(z);
            rs.MoveNext();
        }
        rs.Close();
    }
    catch (CDBException* e)
    {
        e->Delete();
    }
    return lista;
}

std::vector<Zadanie> Database::GetZadania() //dynamiczna tablica
{
    std::vector<Zadanie> lista;  //tworzymy pusty wektor lista
    if (!m_db.IsOpen()) return lista;  // Jeœli baza nie jest po³¹czona - zwracamy od razu pust¹ listê zamiast crashowaæ

    try
    {   // CRecordset to klasa MFC reprezentuj¹ca zapytania SQL
        CRecordset rs(&m_db);
        rs.Open(CRecordset::forwardOnly, //wykonujemy zapytanie i kursor automatycznie ustawia na pierwszym wyniku wierszu. Czytamy wiersz po wierszu tylko do przodu
            _T("SELECT z.ID_Zadania, z.ID_Operatora, z.ID_Maszyny, z.ID_Zlecenia, ")
            _T("z.DataRozpoczecia, z.DataZakonczenia, z.Status, ")
            _T("o.Imie + ' ' + o.Nazwisko AS NazwaOperatora, ")
            _T("m.Nazwa AS NazwaMaszyny, ")
            _T("zl.Nazwa AS NazwaZlecenia ")
            _T("FROM Zadania z ")
            _T("JOIN Operatorzy o ON z.ID_Operatora = o.ID_Operatora ")
            _T("JOIN Maszyny m    ON z.ID_Maszyny   = m.ID_Maszyny ")
            _T("JOIN Zlecenia zl  ON z.ID_Zlecenia  = zl.ID_Zlecenia"));

        while (!rs.IsEOF()) //EOD END OF FILE 
        {
            Zadanie z; // tworzymy pusty obiekt Zadanie który zaraz wype³nimy danymi z bie¿¹cego wiersza.
            CString val; // pomoc do odczytu wartoœci liczbowych
//wartoœæ kolumny z bie¿¹cego wiersza. Short 0 to numer kolumny  //= CString na int
            rs.GetFieldValue((short)0, val); z.ID_Zadania = _ttoi(val);
            rs.GetFieldValue((short)1, val); z.ID_Operatora = _ttoi(val);
            rs.GetFieldValue((short)2, val); z.ID_Maszyny = _ttoi(val);
            rs.GetFieldValue((short)3, val); z.ID_Zlecenia = _ttoi(val);
            rs.GetFieldValue((short)4, z.DataRozpoczecia);
            rs.GetFieldValue((short)5, z.DataZakonczenia);
            rs.GetFieldValue((short)6, z.Status);
            rs.GetFieldValue((short)7, z.NazwaOperatora);
            rs.GetFieldValue((short)8, z.NazwaMaszyny);
            rs.GetFieldValue((short)9, z.NazwaZlecenia);

            lista.push_back(z);  //dodajemy wype³niony obiekt Zadanie na koniec wektora
            rs.MoveNext(); // Przesuwa kursor na nastêpny wiersz
        }
        rs.Close();  // po wyjœciu zwalniamy zasoby
    }
    catch (CDBException* e)
    {
        e->Delete();
    }
    return lista;
}

bool Database::AddZadanie(const Zadanie& z)
{
    if (!m_db.IsOpen()) return false;

    try
    {
        CString sql;
        sql.Format(
            _T("INSERT INTO Zadania (ID_Operatora, ID_Maszyny, ID_Zlecenia, DataRozpoczecia, Status) ")
            _T("VALUES (%d, %d, %d, '%s', '%s')"),
            z.ID_Operatora, z.ID_Maszyny, z.ID_Zlecenia,
            (LPCTSTR)z.DataRozpoczecia, (LPCTSTR)z.Status);

        m_db.ExecuteSQL(sql);
        return true;
    }
    catch (CDBException* e)
    {
        e->Delete();
        return false;
    }
}

bool Database::UpdateStatus(int idZadania, const CString& status)
{
    if (!m_db.IsOpen()) return false;

    try
    {
        CString sql;
        sql.Format(
            _T("UPDATE Zadania SET Status = '%s' WHERE ID_Zadania = %d"),
            (LPCTSTR)status, idZadania);

        m_db.ExecuteSQL(sql);
        return true;
    }
    catch (CDBException* e)
    {
        e->Delete();
        return false;
    }
}

bool Database::DeleteZadanie(int idZadania)
{
    if (!m_db.IsOpen()) return false;

    try
    {
        CString sql;
        sql.Format(_T("DELETE FROM Zadania WHERE ID_Zadania = %d"), idZadania);
        m_db.ExecuteSQL(sql);
        return true;
    }
    catch (CDBException* e)
    {
        e->Delete();
        return false;
    }
}