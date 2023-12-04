#ifndef CONTENEUR_H
#define CONTENEUR_H
#include<QString>
#include <QSqlQueryModel>
#include<QToolTip>
class conteneur
{
    int id,niveau,capacite;


public:
    conteneur(){};
    conteneur(int,int,int);
    void setid(int);
    void setniveau(int);
    void setcapacite(int);

    int get_id();
    int get_niveau();
    int get_capacite();
    QSqlQueryModel* afficher();
    bool ajouter();
    bool supprimer(int);
    bool modifier(int,int,int);
    void pdfprinter();
    QSqlQueryModel * trie_id();
    QSqlQueryModel* chercherid(int id);


private:


};

#endif // CONTENEUR_H
