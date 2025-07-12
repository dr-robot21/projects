-- Création de la base de données
CREATE DATABASE IF NOT EXISTS gestion_hotel;
USE gestion_hotel;

-- Table Hotel
CREATE TABLE Hotel (
    Id_Hotel INT AUTO_INCREMENT PRIMARY KEY,
    Ville VARCHAR(100) NOT NULL,
    Pays VARCHAR(100) NOT NULL,
    Code_postal INT NOT NULL
);

-- Table Type_Chambre
CREATE TABLE Type_Chambre (
    Id_Type INT AUTO_INCREMENT PRIMARY KEY,
    Type VARCHAR(50) NOT NULL,
    Tarif DECIMAL(10,2) NOT NULL
);

-- Table Chambre
CREATE TABLE Chambre (
    Id_Chambre INT AUTO_INCREMENT PRIMARY KEY,
    Numero INT NOT NULL,
    Etage INT NOT NULL,
    Fumeur BOOLEAN NOT NULL,
    Id_Hotel INT NOT NULL,
    Id_Type INT NOT NULL,
    FOREIGN KEY (Id_Hotel) REFERENCES Hotel(Id_Hotel),
    FOREIGN KEY (Id_Type) REFERENCES Type_Chambre(Id_Type)
);

-- Table Client
CREATE TABLE Client (
    Id_Client INT AUTO_INCREMENT PRIMARY KEY,
    Adresse VARCHAR(255) NOT NULL,
    Ville VARCHAR(100) NOT NULL,
    Code_postal INT NOT NULL,
    Email VARCHAR(100) NOT NULL,
    Telephone VARCHAR(20) NOT NULL,
    Nom_complet VARCHAR(100) NOT NULL
);

-- Table Prestation
CREATE TABLE Prestation (
    Id_Prestation INT AUTO_INCREMENT PRIMARY KEY,
    Prix DECIMAL(10,2) NOT NULL,
    Description TEXT NOT NULL
);

-- Table Reservation
CREATE TABLE Reservation (
    Id_Reservation INT AUTO_INCREMENT PRIMARY KEY,
    Date_arrivee DATE NOT NULL,
    Date_depart DATE NOT NULL,
    Id_Client INT NOT NULL,
    FOREIGN KEY (Id_Client) REFERENCES Client(Id_Client)
);

-- Table Evaluation
CREATE TABLE Evaluation (
    Id_Evaluation INT AUTO_INCREMENT PRIMARY KEY,
    Date_evaluation DATE NOT NULL,
    Note INT NOT NULL,
    Commentaire TEXT NOT NULL,
    Id_Client INT NOT NULL,
    FOREIGN KEY (Id_Client) REFERENCES Client(Id_Client)
);

-- Table de liaison Reservation_Chambre
CREATE TABLE Reservation_Chambre (
    Id_Reservation INT NOT NULL,
    Id_Chambre INT NOT NULL,
    PRIMARY KEY (Id_Reservation, Id_Chambre),
    FOREIGN KEY (Id_Reservation) REFERENCES Reservation(Id_Reservation),
    FOREIGN KEY (Id_Chambre) REFERENCES Chambre(Id_Chambre)
);

-- Table de liaison Reservation_Prestation
CREATE TABLE Reservation_Prestation (
    Id_Reservation INT NOT NULL,
    Id_Prestation INT NOT NULL,
    PRIMARY KEY (Id_Reservation, Id_Prestation),
    FOREIGN KEY (Id_Reservation) REFERENCES Reservation(Id_Reservation),
    FOREIGN KEY (Id_Prestation) REFERENCES Prestation(Id_Prestation)
);