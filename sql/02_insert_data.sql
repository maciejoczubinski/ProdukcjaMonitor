USE system_monitorowania;

-- Operatorzy
INSERT INTO Operatorzy (Imie, Nazwisko, Stanowisko, NrTelefonu) VALUES ('Jan', 'Kowalski', 'Operator CNC', '600100200');
INSERT INTO Operatorzy (Imie, Nazwisko, Stanowisko, NrTelefonu) VALUES ('Anna', 'Nowak', 'Spawacz', '600100201');
INSERT INTO Operatorzy (Imie, Nazwisko, Stanowisko, NrTelefonu) VALUES ('Piotr', 'Wiśniewski', 'Tokarz', '600100202');

-- Maszyny
INSERT INTO Maszyny (Nazwa, Typ, NrSeryjny, Lokalizacja) VALUES ('Tokarka TUR-50', 'Tokarka', 'SN-001', 'Hala A');
INSERT INTO Maszyny (Nazwa, Typ, NrSeryjny, Lokalizacja) VALUES ('Spawarka MIG-200', 'Spawarka', 'SN-002', 'Hala B');
INSERT INTO Maszyny (Nazwa, Typ, NrSeryjny, Lokalizacja) VALUES ('Frezarka FU-32', 'Frezarka', 'SN-003', 'Hala A');

-- Zlecenia
INSERT INTO Zlecenia (Nazwa, Ilosc, Termin) VALUES ('Produkcja wałków', 100, '2026-06-30');
INSERT INTO Zlecenia (Nazwa, Ilosc, Termin) VALUES ('Spawanie ram', 50, '2026-07-15');
INSERT INTO Zlecenia (Nazwa, Ilosc, Termin) VALUES ('Frezowanie paneli', 200, '2026-07-31');

-- Zadania
INSERT INTO Zadania (ID_Operatora, ID_Maszyny, ID_Zlecenia, DataRozpoczecia, Status) VALUES (1, 1, 1, '2026-06-02 08:00', 'W trakcie');
INSERT INTO Zadania (ID_Operatora, ID_Maszyny, ID_Zlecenia, DataRozpoczecia, Status) VALUES (2, 2, 2, '2026-06-02 09:00', 'Nowe');
INSERT INTO Zadania (ID_Operatora, ID_Maszyny, ID_Zlecenia, DataRozpoczecia, Status) VALUES (3, 3, 3, '2026-06-02 10:00', 'Nowe');

-- Kwalifikacje
INSERT INTO Kwalifikacje (ID_Operatora, ID_Maszyny) VALUES (1, 1);
INSERT INTO Kwalifikacje (ID_Operatora, ID_Maszyny) VALUES (1, 3);
INSERT INTO Kwalifikacje (ID_Operatora, ID_Maszyny) VALUES (2, 2);
INSERT INTO Kwalifikacje (ID_Operatora, ID_Maszyny) VALUES (3, 1);
INSERT INTO Kwalifikacje (ID_Operatora, ID_Maszyny) VALUES (3, 3);