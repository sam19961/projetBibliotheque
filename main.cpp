#include "bibliotheque.cpp"

#define TAB_MAX 2
// includes: livre->revue->video->dvd->ressource->biblio->main
// ajouter auteur sur fenetrelivre
// fonction de recherche/clear/show id/list
// delete tous les elements car pointeurs ???
// faire la liste d'article dans la revue
// rajouter revue dans les fenetres Qt

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Bibliotheque b1, b2;
    Livre l1("Albert Einstein",1916,220,"SBP","Relativity","un livre de science", 1);
    Video v1(194, "James Cameron", "20th Century Fox", "Titanic", 10);
    DVD d1(162, "James Cameron", "Dune Entertainment", "Avatar", 2, 1, 2);
    RessourceNum r1(123, "jean michel", PDF, "du lesa.txt", "C://ici/maybela/avoila", 7);
    Livre l2("Stephen Hawking",1988,236,"Flammarion","Une brève histoire","un autre livre de science", 5);
    Revue rev1("myke",2005,200,"hsbc","science et vie","une revue de science","le S",3, 6);
    DVD c1(50,"PLK","Fifou","Polak",12,0,12);
    Livre essai("test1",777,777,"test1","test1","test1", 2);
    ///devoir faire une bibliotheque avec 20 elements -> realisme   

    b1.ajouter(l1);
    b1.ajouter(v1);
    b1.ajouter(d1);
    b1.ajouter(r1);
    b1.ajouter(l2);
    b1.ajouter(rev1);    
    b1.ajouter(c1);
    b1.ajouter(essai);
    b1.affichage();
    int lel = b1.doublon();
    qDebug() << "un peu apres \n \n" << endl;
    b1.affichage();


    /// Sauvegarde dans base
    /*QFile labase("../../../../BiblioTest/sauvegardeArmoire.txt");
    QFile *baseDeDonneeBuffer;
    baseDeDonneeBuffer = b1.sauvegarde(&labase);*/

    ///recherche dans base
    /*b1.afficher_BaseDeDonnee();
    qDebug() << "un peu de temps apres \n" << endl;
    QFile labaseRecherche("../../../../BiblioTest/baseRecherche.txt");
    b1.recherche("Albert", &labaseRecherche);
    b1.afficher_BaseDeDonnee();
    b1.affichage();*/

    ///test fct clear
    /*b1.Clear(&labaseRecherche);
    b1.afficher_BaseDeDonnee();*/

    ///load from base
    /*QFile exemple_fichier("../../../../BiblioTest/loadFichier.txt");
    b1.load(&exemple_fichier);
    b1.affichage();*/

    ///tri a finir
    /*b1.tri_donnee();
    qDebug() << "la suite au prochain episode \n" << endl;
    b1.affichage();*/

    //return a.exec();
}
