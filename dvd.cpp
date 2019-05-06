#include "dvd.h"

int DVD::compteur_DVD = 0;

int DVD::nb_DVD()
{
  return compteur_DVD;
}

DVD::DVD(): Video()
{
  ++compteur_DVD;
  m_nbPiste = 0;
}

DVD::DVD(int duree, QString auteur, QString maison, QString nom, int piste, int flag, int id): Video(duree, auteur, maison, nom, id)
, m_nbPiste(piste)
{
  ++compteur_DVD;
    m_flag = flag;
}

DVD::~DVD()
{
  --compteur_DVD;
}

int DVD::CD_DVD()
{
    if(!m_flag)
        return 0;
    else
        return 1;
}

void DVD::affichage()
{
  if(m_flag == 1)
    qDebug() <<"DVD: " << m_duree << "[auteur]:  " << m_auteur << "[maison de prod]:  "
            << m_maisonProduction << "[nom] " << m_nom_video << "[nombre piste]" << m_nbPiste << "[id]:" << m_id << "\n";
  else if(m_flag == 0)
    qDebug() <<"CD: "  << m_duree << "[auteur]:  " << m_auteur << "[maison de prod]:  "
            << m_maisonProduction << "[nom] " << m_nom_video << "[nombre piste]" << m_nbPiste << "[id]:" << m_id << "\n";
  else
    qCritical() << "erreur de la fonction affichage DVD" << endl;
}

int DVD::iswhat()
{    
    return 4; //enum pour cd/dvd
}

QString DVD::informations()
{
    QString buffer;
    if(m_flag == 1){
        buffer += "DVD: ";
    }
    else{
        buffer += "CD: ";
    }
    buffer += "[nom]:";
    buffer += m_nom_video;
    buffer += "; [duree]:";
    buffer += QString::number(m_duree);
    buffer += "; [auteur]:";
    buffer += m_auteur;
    buffer += "; [maison de prod]:";
    buffer += m_maisonProduction;
    buffer += "; [nombre de pistes]:";
    buffer += QString::number(m_nbPiste);
    buffer += Objet::informations();
    return buffer;
}

void DVD::ajouterdvd(int duree, QString auteur, QString maison, QString nom, int piste, int flag, int id)
{
    m_duree = duree;
    m_auteur = auteur;
    m_maisonProduction = maison;
    m_nom_video = nom;
    m_nbPiste = piste;
    m_flag = flag;
    m_id = id;
}
