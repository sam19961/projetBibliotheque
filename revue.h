#ifndef REVUE_H
#define REVUE_H
#include "livre.h"

class Revue: public Livre
{
public:
    Revue();
    Revue(QString auteur, int annee, int page, QString collection, QString titre, QString resume, QString editeur, int nb_article, int id, QString emprunt);
    ~Revue();
    void ajouterrevue(QString auteur, int annee, int page, QString collection, QString titre, QString resume, QString editeur, int nb_article, int id, QString emprunt);
    virtual void affichage();
    virtual int iswhat();
    virtual QString informations();


protected:
    QString m_editeur;
    int m_nb_article;
    QList<QString> m_article; //on n'utilise pas cet attribut pour eviter de surchager le code et l'affichage
    static int compteur_Revue;

};
#endif
