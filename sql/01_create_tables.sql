CREATE DATABASE system_monitorowania;
GO
USE system_monitorowania;
GO

CREATE TABLE Operatorzy (
    ID_Operatora INT IDENTITY(1,1) PRIMARY KEY,
    Imie         VARCHAR(255) NOT NULL,
    Nazwisko     VARCHAR(255) NOT NULL,
    Stanowisko   VARCHAR(255),
    NrTelefonu   VARCHAR(20)
);

CREATE TABLE Maszyny (
    ID_Maszyny  INT IDENTITY(1,1) PRIMARY KEY,
    Nazwa       VARCHAR(255) NOT NULL,
    Typ         VARCHAR(255) NOT NULL,
    NrSeryjny   VARCHAR(50),
    Lokalizacja VARCHAR(255)
);

CREATE TABLE Zlecenia (
    ID_Zlecenia INT IDENTITY(1,1) PRIMARY KEY,
    Nazwa       VARCHAR(255) NOT NULL,
    Ilosc       INT NOT NULL,
    Termin      DATE
);

CREATE TABLE Zadania (
    ID_Zadania      INT IDENTITY(1,1) PRIMARY KEY,
    ID_Operatora    INT NOT NULL,
    ID_Maszyny      INT NOT NULL,
    ID_Zlecenia     INT NOT NULL,
    DataRozpoczecia DATETIME,
    DataZakonczenia DATETIME,
    Status          VARCHAR(20) NOT NULL DEFAULT 'Nowe',

    CONSTRAINT FK_Zadania_Operator
        FOREIGN KEY (ID_Operatora) REFERENCES Operatorzy(ID_Operatora),
    CONSTRAINT FK_Zadania_Maszyna
        FOREIGN KEY (ID_Maszyny)   REFERENCES Maszyny(ID_Maszyny),
    CONSTRAINT FK_Zadania_Zlecenie
        FOREIGN KEY (ID_Zlecenia)  REFERENCES Zlecenia(ID_Zlecenia),
    CONSTRAINT CHK_Status
        CHECK (Status IN ('Nowe', 'W trakcie', 'Zakończone'))
);

CREATE TABLE Kwalifikacje (
    ID_Operatora INT NOT NULL,
    ID_Maszyny   INT NOT NULL,

    CONSTRAINT PK_Kwalifikacje
        PRIMARY KEY (ID_Operatora, ID_Maszyny),
    CONSTRAINT FK_Kwalifikacje_Operator
        FOREIGN KEY (ID_Operatora) REFERENCES Operatorzy(ID_Operatora),
    CONSTRAINT FK_Kwalifikacje_Maszyna
        FOREIGN KEY (ID_Maszyny)   REFERENCES Maszyny(ID_Maszyny)
);