#include "video.h"

int Video::compteur_Video = 0;

int Video::nb_Video()
{
  return compteur_Video;
}

Video::Video(): Objet()
{
  ++compteur_Video;
  m_auteur = "inconnu";
  m_duree = 0;
  m_maisonProduction = "inconnu";
  m_nom_video = "inconnu";
}

Video::Video(int duree, QString auteur, QString maison, QString nom): Objet(), m_duree(duree),
m_auteur(auteur), m_maisonProduction(maison), m_nom_video(nom)
{
  ++compteur_Video;
}

Video::~Video()
{
  --compteur_Video;
}

void Video::affichage()
{
  qDebug() << "Video" << m_duree << "  " << m_auteur << "  " << m_maisonProduction << "  " << m_nom_video << "\n";
}


int Video::iswhat()
{
  return 3;
}

QString Video::informations()
{
    QString buffer;
    buffer += "Video: ";
    buffer += "[nom]:";
    buffer += m_nom_video;
    buffer += "; [duree]:";
    buffer += QString::number(m_duree);
    buffer += "; [auteur]:";
    buffer += m_auteur;
    buffer += "; [maison de prod]:";
    buffer += m_maisonProduction;
    return buffer;
}

void Video::ajoutervideo(int duree, QString auteur, QString maison, QString nom)
{
    m_duree = duree;
    m_auteur = auteur;
    m_maisonProduction = maison;
    m_nom_video = nom;
}
