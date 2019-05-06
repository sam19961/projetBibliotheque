#ifndef REVUE_H
#define REVUE_H
#include "livre.h"

class Revue: public Livre
{
public:
    Revue();
    Revue(QString auteur, int annee, int page, QString collection, QString titre, QString resume, QString editeur, int nb_article, int id);
    ~Revue();
    void ajouterrevue(QString auteur, int annee, int page, QString collection, QString titre, QString resume, QString editeur, int nb_article, int id);
    virtual void affichage();
    virtual int iswhat();
    virtual QString informations();


protected:
    QString m_editeur;
    int m_nb_article;
    QList<QString> m_article;
    static int compteur_Revue;

};
#endif
