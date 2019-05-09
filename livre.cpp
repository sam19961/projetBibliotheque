#include "livre.h"

int Livre::compteur_Livre = 0;
int Objet::compteur_Objet = 0;


Objet::Objet()
{
  ++compteur_Objet;
}

Objet::Objet(QString auteur, int id, QString emprunt)
{
  ++compteur_Objet;
  m_auteur = auteur;
  m_id = id;
  m_emprunt = emprunt;
}

Objet::~Objet()
{
  --compteur_Objet;
}

void Objet::affichage()
{
  qDebug() << "[auteur]: " << m_auteur;
  qDebug() << "[emprunt]: " << m_emprunt;
}

int Objet::iswhat()
{
  return 0;
}

int Objet::CD_DVD()
{
    return -1;
}

QString Objet::informations()
{
    QString buffer;
    buffer += "; [id]:";
    buffer += QString::number(m_id);
    buffer += "; [emprunt]:";
    buffer += m_emprunt;
    return buffer;
}

int Objet::get_id()
{
    return m_id;
}

QString Objet::get_auteur()
{
    return m_auteur;
}


void Objet::prendre(int pris)
{
    (pris == 1)?m_emprunt = "pas dispo":m_emprunt = "dispo";
}


int Livre::nb_Livre()
{
  return compteur_Livre;
}

Livre::Livre() : Objet()
{
  ++compteur_Livre;
  m_annee = 0;
  m_nbPage = 0;
  m_collection = "inconnu";
  m_titre = "inconnu";
  m_resume = "rien";
  m_auteur = "inconnu";

}

Livre::Livre(QString auteur, int annee, int page, QString collection, QString titre, QString resume, int id, QString emprunt): Objet(auteur, id, emprunt),
m_nbPage(page), m_collection(collection), m_titre(titre), m_resume(resume)
{
  ++compteur_Livre;
    m_annee = annee;
}

Livre::~Livre()
{
  --compteur_Livre;
}

void Livre::affichage()
{
  qDebug() << "Livre:";
  Objet::affichage();
  qDebug() << m_annee << "  " << m_nbPage << "  " << m_titre << m_id << "exemple d'utilisation de l'affichage objet "<< "\n";  

}

int Livre::iswhat()
{
  return 1;
}

QString Livre::informations()
{
    QString buffer;
    buffer += "LIVRE: ";
    buffer += "[titre]:";
    buffer += m_titre;
    buffer += "; [auteur]:";
    buffer += m_auteur;
    buffer += "; [annee]:";
    buffer += QString::number(m_annee);
    buffer += "; [nombre de pages]:";
    buffer += QString::number(m_nbPage);
    buffer += "; [collection]:";
    buffer += m_collection;
    buffer += "; [resume]:";
    buffer += m_resume;        
    buffer += Objet::informations();
    return buffer;
}

void Livre::ajouterlivre(QString auteur, int annee, int page, QString collection, QString titre, QString resume, int id, QString emprunt)
{
    m_auteur = auteur;
    m_annee = annee;
    m_nbPage = page;
    m_collection = collection;
    m_titre = titre;
    m_resume = resume;
    m_id = id;
    m_emprunt = emprunt;
}
