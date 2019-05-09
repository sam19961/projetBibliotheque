#include "revue.h"

int Revue::compteur_Revue = 0;

Revue::Revue()
{
    ++compteur_Revue;
}

Revue::Revue(QString auteur, int annee, int page, QString collection, QString titre, QString resume, QString editeur, int nb_article, int id, QString emprunt)
    :Livre(auteur,annee,page,collection,titre,resume,id,emprunt), m_editeur(editeur), m_nb_article(nb_article)
{
    ++compteur_Revue;
}

Revue::~Revue()
{
    --compteur_Revue;
}

void Revue::affichage()
{
  Objet::affichage();
  qDebug() << "Revue: " << m_annee << "  " << m_nbPage << "  " << m_auteur << "  " << m_titre << "  " << m_editeur << "  "
           << m_nb_article << m_id << "\n";

}

int Revue::iswhat()
{
  return 2;
}

QString Revue::informations()
{
    QString buffer;
    buffer += "REVUE: ";
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
    buffer += "; [editeur]:";
    buffer += m_editeur;
    buffer += "; [nombre d'articles]:";
    buffer += QString::number(m_nb_article);
    buffer += Objet::informations(); //pour avoir id a la fin
    return buffer;
}

void Revue::ajouterrevue(QString auteur, int annee, int page, QString collection, QString titre, QString resume, QString editeur, int nb_article, int id, QString emprunt)
{
    m_auteur = auteur;
    m_annee = annee;
    m_nbPage = page;
    m_collection = collection;
    m_titre = titre;
    m_resume = resume;
    m_editeur = editeur;
    m_nb_article = nb_article;
    m_id = id;
    m_emprunt = emprunt;
}
