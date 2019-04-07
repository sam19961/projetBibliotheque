#include "livre.h"

int Livre::compteur_Livre = 0;
int Objet::compteur_Objet = 0;


Objet::Objet()
{
  ++compteur_Objet;
}

Objet::~Objet()
{
  --compteur_Objet;
}

void Objet::affichage()
{
  qDebug() << "Un objet non définit\n";
}

int Objet::iswhat()
{
  return 0;
}

int Objet::CD_DVD()
{
    return -1;
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

Livre::Livre(QString auteur, int annee, int page, QString collection, QString titre, QString resume): Objet(),
m_auteur(auteur), m_nbPage(page), m_collection(collection), m_titre(titre), m_resume(resume)
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
  qDebug() << "Livre:" << m_annee << "  " << m_nbPage << "  " << m_auteur << "  " << m_titre << "\n";

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
    return buffer;
}

void Livre::ajouterlivre(QString auteur, int annee, int page, QString collection, QString titre, QString resume)
{
    m_auteur = auteur;
    m_annee = annee;
    m_nbPage = page;
    m_collection = collection;
    m_titre = titre;
    m_resume = resume;
}
