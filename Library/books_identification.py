# -*- coding: utf-8 -*-
"""
Created on Tue Apr  1 11:52:20 2025

@author: loreal
"""
import random
from abc import ABC, abstractmethod
from datetime import datetime
from time import time 

class Livre(ABC):
    
    
    editeurs_francais = {
    '978-2-07': 'Gallimard',
    '978-2-01': 'Hachette Livre',
    '978-2-266': 'Pocket',
    '978-2-253': 'Le Livre de Poche',
    '978-2-081': 'Flammarion',
    '978-2-290': 'J\'ai Lu',
    '978-2-0703': 'Folio',
    '978-2-9125': 'Actes Sud',
    '978-2-0704': 'NRF Gallimard',
    '978-2-330': 'Éditions du Seuil',
    '978-2-7112': 'Dunod',
    '978-2-7056': 'L\'Harmattan',
    '978-2-1305': 'Presses Universitaires de France (PUF)',
    '978-2-7381': 'Éditions Ellipses',
    '978-2-7598': 'Vuibert',
    '978-2-35176': 'Les Éditions de Minuit',
    '978-2-914863': 'Verticales',
    '978-2-86930': 'José Corti',
    '978-2-918878': 'Éditions Zulma'
}
    
    def __init__(self):
        self.disponible = True
        self.date       = None 
        self.isbn       = None 
    
    
    
    def emprunter(self): 
        if self.disponible: 
            self.disponible = False
            self.date = datetime.now() 
            
    
    def retourner(self): 
        if not self.disponible: 
            self.disponible = True
            self.date = datetime.now()
        
    
    def calculer_chiffre_de_controle(self, isbn):
        """Calcule le chiffre de contrôle selon l'algorithme de Luhn pour un ISBN-13"""
        total = 0
        for i, digit in enumerate(isbn):
            digit = int(digit)
            if i % 2 == 0:
                total += digit
            else:
                total += digit * 3
        return (10 - (total % 10)) % 10
    
    def generer_isbn(self):
        prefixe = "978"
        
        
        identifiant_groupe = "2"  
        identifiant_éditeur = str(random.randint(100000, 999999))
        
        numero_livre = str(random.randint(10000, 99999))
        
        #Calcul du chiffre de contrôle
        isbn_partiel = prefixe + identifiant_groupe + identifiant_éditeur + numero_livre
        chiffre_de_controle = self.calculer_chiffre_de_controle(isbn_partiel)
        
        # Retourner l'ISBN complet
        isbn_complet = f"{prefixe}-{identifiant_groupe}-{identifiant_éditeur}-{numero_livre}-{chiffre_de_controle}"
        return isbn_complet



    def __str__(self): 
        return (f"Disponibilité: {'Disponible\n' if self.disponible else 'Emprunté\n'}"
                f"Date: {self.date.strftime('%Y-%m-%d %H:%M:%S') if self.date else 'Date umprunt inconnu'}\n"
                f"ISBN: {self.isbn if self.isbn else 'Livre non reconnu, ne possède pas de ISBN'}\n"
                ) 
    


class Gestionnaire(): 
    def ajouter_livre(self): 
        pass 
    def emprunt_statue(): 
        pass 
    def retour_livre(self): 
        pass
    def supprimer_livre(self): 
        pass 
    def livre_etat(self): 
        pass 
    def enregistrer_isbn(self): 
        pass 
    def supprimer_isbn(self): 
        
        
    
class Emprunter(): 
    pass

class Roman(Livre):
    def __init__(self, titre,auteur): 
        self.titre = titre
        self.auteur = auteur
        super().__init__() 
        
    
    
    def emprunter(self): 
        if self.disponible: 
            self.disponible = False
            self.date = datetime.now()
            self.isbn = self.generer_isbn()
            
    def retourner(self): 
        if not self.disponible: 
            print("livre non retourné")
            


roman = Roman("No exception", "Me")
print(roman)
roman.emprunter()
print(roman)