#include "ressource.h"

int RessourceNum::compteur_RessourceNum = 0;

int RessourceNum::nb_RessourceNum()
{
  return compteur_RessourceNum;
}

RessourceNum::RessourceNum()
{
  ++compteur_RessourceNum;
  m_auteur = "inconnu";
  m_type = inconnu;
  m_taille = 0;
  m_nom = "inconnu";
  m_cheminAcces = "inconnu";
}

RessourceNum::RessourceNum(int taille, QString auteur, format type, QString nom, QString chemin, int id): Objet(auteur, id),
m_type(type), m_nom(nom), m_cheminAcces(chemin)
 {
   ++compteur_RessourceNum;
   m_taille = taille; //un warning si taille est en haut
 }

RessourceNum::~RessourceNum()
{
  --compteur_RessourceNum;
}

void RessourceNum::affiche_type()
{
  switch(m_type){
    case PDF : qDebug() << "PDF\n"; break;
    case DOC : qDebug() << "DOC\n"; break;
    case PPT : qDebug() << "PPT\n"; break;
    case inconnu : qDebug() << "inconnu\n"; break;
  }
}

void RessourceNum::affichage()
{
  qDebug() << "Ressource Numerique: " << m_auteur << "  " << m_taille << "  " << m_nom << "  " << m_cheminAcces << "  " << m_id << " ";
  affiche_type();
}

int RessourceNum::iswhat()
{
  return 5;
}

QString RessourceNum::informations()
{
    QString buffer;
    buffer += "Ressource Numerique: ";
    buffer += "[nom]:";
    buffer += m_nom;
    buffer += "; [auteur]:";
    buffer += m_auteur;
    buffer += "; [taille]:";
    buffer += QString::number(m_taille);
    buffer += "; [chemin d'acces]:";    
    buffer += m_cheminAcces;


    buffer += "; [format]:";

    switch(m_type){
      case PDF : buffer += "PDF"; break;
      case DOC : buffer += "DOC"; break;
      case PPT : buffer += "PPT"; break;
      case inconnu : buffer += "inconnu"; break;
    }

    buffer += Objet::informations();

    return buffer;
}

void RessourceNum::ajouterressource(int taille, QString auteur, QString type, QString nom, QString chemin, int id)
{    
    if(type == "PDF"){
        m_type = PDF;
    }
    else if(type == "DOC"){
        m_type = DOC;
    }
    else if(type == PPT){
        m_type = PPT;
    }
    else {
        m_type = inconnu;
    }
    m_taille = taille;
    m_auteur = auteur;    
    m_nom = nom;
    m_cheminAcces = chemin;
    m_id = id;
}

void RessourceNum::set_format(QString mot)
{    
    if(mot == "PDF")
        m_type = PDF;
    else if(mot == "DOC")
        m_type =DOC;
    else if(mot == "PPT")
        m_type = PPT;
    else
        m_type = inconnu;
}
