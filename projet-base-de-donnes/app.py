import streamlit as st
import sqlite3
import pandas as pd
from datetime import datetime

# Configuration de la page
st.set_page_config(page_title="Gestion Hôtelière", layout="wide")

# Connexion à la base de données
conn = sqlite3.connect('hotel.db')

# Fonctions utilitaires
def execute_query(query, params=None):
    cursor = conn.cursor()
    if params:
        cursor.execute(query, params)
    else:
        cursor.execute(query)
    result = cursor.fetchall()
    columns = [description[0] for description in cursor.description]
    cursor.close()
    return pd.DataFrame(result, columns=columns)

# Interface utilisateur
st.title("Système de Gestion Hôtelière")

menu = st.sidebar.selectbox("Menu", [
    "Consulter les réservations",
    "Consulter les clients",
    "Chambres disponibles",
    "Ajouter un client",
    "Ajouter une réservation"
])

if menu == "Consulter les réservations":
    st.header("Liste des réservations")
    query = '''
    SELECT r.Id_Reservation, c.Nom_complet, h.Ville AS Ville_hotel, 
           r.Date_arrivee, r.Date_depart, ch.Numero AS Numero_chambre
    FROM Reservation r
    JOIN Client c ON r.Id_Client = c.Id_Client
    JOIN Reservation_Chambre rc ON r.Id_Reservation = rc.Id_Reservation
    JOIN Chambre ch ON rc.Id_Chambre = ch.Id_Chambre
    JOIN Hotel h ON ch.Id_Hotel = h.Id_Hotel
    ORDER BY r.Date_arrivee
    '''
    reservations = execute_query(query)
    st.dataframe(reservations)

elif menu == "Consulter les clients":
    st.header("Liste des clients")
    query = "SELECT * FROM Client ORDER BY Nom_complet"
    clients = execute_query(query)
    st.dataframe(clients)

elif menu == "Chambres disponibles":
    st.header("Recherche de chambres disponibles")
    col1, col2 = st.columns(2)
    with col1:
        date_arrivee = st.date_input("Date d'arrivée", datetime.now())
    with col2:
        date_depart = st.date_input("Date de départ", datetime.now())
    
    if st.button("Rechercher"):
        query = '''
        SELECT ch.Id_Chambre, ch.Numero, ch.Etage, tc.Type, tc.Tarif, h.Ville
        FROM Chambre ch
        JOIN Type_Chambre tc ON ch.Id_Type = tc.Id_Type
        JOIN Hotel h ON ch.Id_Hotel = h.Id_Hotel
        WHERE ch.Id_Chambre NOT IN (
            SELECT rc.Id_Chambre
            FROM Reservation_Chambre rc
            JOIN Reservation r ON rc.Id_Reservation = r.Id_Reservation
            WHERE (r.Date_arrivee <= ? AND r.Date_depart >= ?)
        )
        '''
        chambres = execute_query(query, (date_depart.strftime('%Y-%m-%d'), date_arrivee.strftime('%Y-%m-%d')))
        
        if not chambres.empty:
            st.success(f"{len(chambres)} chambre(s) disponible(s) pour cette période")
            st.dataframe(chambres)
        else:
            st.warning("Aucune chambre disponible pour cette période")

elif menu == "Ajouter un client":
    st.header("Ajouter un nouveau client")
    
    with st.form("nouveau_client"):
        nom = st.text_input("Nom complet")
        adresse = st.text_input("Adresse")
        ville = st.text_input("Ville")
        code_postal = st.number_input("Code postal", min_value=0, step=1)
        email = st.text_input("Email")
        telephone = st.text_input("Téléphone")
        
        submitted = st.form_submit_button("Enregistrer")
        if submitted:
            try:
                cursor = conn.cursor()
                cursor.execute('''
                INSERT INTO Client (Nom_complet, Adresse, Ville, Code_postal, Email, Telephone)
                VALUES (?, ?, ?, ?, ?, ?)
                ''', (nom, adresse, ville, code_postal, email, telephone))
                conn.commit()
                st.success("Client ajouté avec succès!")
            except Exception as e:
                st.error(f"Erreur: {e}")

elif menu == "Ajouter une réservation":
    st.header("Ajouter une nouvelle réservation")
    
    # Récupérer la liste des clients
    clients = execute_query("SELECT Id_Client, Nom_complet FROM Client ORDER BY Nom_complet")
    client_options = {row['Nom_complet']: row['Id_Client'] for _, row in clients.iterrows()}
    
    # Récupérer la liste des chambres
    chambres = execute_query('''
    SELECT ch.Id_Chambre, ch.Numero, tc.Type, h.Ville 
    FROM Chambre ch
    JOIN Type_Chambre tc ON ch.Id_Type = tc.Id_Type
    JOIN Hotel h ON ch.Id_Hotel = h.Id_Hotel
    ''')
    chambre_options = {
        f"Chambre {row['Numero']} ({row['Type']}) - {row['Ville']}": row['Id_Chambre'] 
        for _, row in chambres.iterrows()
    }
    
    with st.form("nouvelle_reservation"):
        client = st.selectbox("Client", options=list(client_options.keys()))
        date_arrivee = st.date_input("Date d'arrivée", datetime.now())
        date_depart = st.date_input("Date de départ", datetime.now())
        chambre = st.selectbox("Chambre", options=list(chambre_options.keys()))
        
        # Sélection des prestations
        prestations = execute_query("SELECT Id_Prestation, Description FROM Prestation")
        selected_prestations = st.multiselect(
            "Prestations supplémentaires",
            options=[f"{row['Description']} (ID: {row['Id_Prestation']})" for _, row in prestations.iterrows()]
        )
        
        submitted = st.form_submit_button("Enregistrer")
        if submitted:
            try:
                cursor = conn.cursor()
                
                # Ajouter la réservation
                cursor.execute('''
                INSERT INTO Reservation (Date_arrivee, Date_depart, Id_Client)
                VALUES (?, ?, ?)
                ''', (date_arrivee, date_depart, client_options[client]))
                reservation_id = cursor.lastrowid
                
                # Lier la chambre
                cursor.execute('''
                INSERT INTO Reservation_Chambre (Id_Reservation, Id_Chambre)
                VALUES (?, ?)
                ''', (reservation_id, chambre_options[chambre]))
                
                # Lier les prestations
                for presta in selected_prestations:
                    presta_id = int(presta.split("ID: ")[1].rstrip(")"))
                    cursor.execute('''
                    INSERT INTO Reservation_Prestation (Id_Reservation, Id_Prestation)
                    VALUES (?, ?)
                    ''', (reservation_id, presta_id))
                
                conn.commit()
                st.success("Réservation ajoutée avec succès!")
            except Exception as e:
                st.error(f"Erreur: {e}")

# Fermer la connexion à la fin
conn.close()