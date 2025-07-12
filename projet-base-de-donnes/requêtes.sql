-- a. Afficher la liste des réservations avec le nom du client et la ville de l’hôtel réservé.

SELECT r.Id_Reservation, c.Nom_complet, h.Ville AS Ville_hotel, 
       r.Date_arrivee, r.Date_depart
FROM Reservation r
JOIN Client c ON r.Id_Client = c.Id_Client
JOIN Reservation_Chambre rc ON r.Id_Reservation = rc.Id_Reservation
JOIN Chambre ch ON rc.Id_Chambre = ch.Id_Chambre
JOIN Hotel h ON ch.Id_Hotel = h.Id_Hotel;

-- b. Afficher les clients qui habitent à Paris.

SELECT * FROM Client WHERE Ville = 'Paris';

-- c. Calculer le nombre de réservations faites par chaque client.

SELECT c.Id_Client, c.Nom_complet, COUNT(r.Id_Reservation) AS Nombre_reservations
FROM Client c
LEFT JOIN Reservation r ON c.Id_Client = r.Id_Client
GROUP BY c.Id_Client, c.Nom_complet;

-- d. Donner le nombre de chambres pour chaque type de chambre.

SELECT tc.Type, COUNT(c.Id_Chambre) AS Nombre_chambres
FROM Type_Chambre tc
LEFT JOIN Chambre c ON tc.Id_Type = c.Id_Type
GROUP BY tc.Type;

-- e. Afficher la liste des chambres qui ne sont pas réservées pour une période donnée (entre deux dates saisies par l’utilisateur). 
-- Pour une période donnée (par exemple du 2025-06-10 au 2025-06-20)
SELECT ch.* 
FROM Chambre ch
WHERE ch.Id_Chambre NOT IN (
    SELECT rc.Id_Chambre
    FROM Reservation_Chambre rc
    JOIN Reservation r ON rc.Id_Reservation = r.Id_Reservation
    WHERE (r.Date_arrivee <= '2025-06-20' AND r.Date_depart >= '2025-06-10')
);


