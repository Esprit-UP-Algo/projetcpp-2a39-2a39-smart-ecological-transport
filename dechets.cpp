#include "dechets.h"

Dechets::Dechets()
{
    nom = "";
    type= "";
    matiere="";
    destinataire="";
    etat="";
    poids=0;
    volume =0;

}
Dechets::Dechets(QString a,QString b ,float c,float d,QString e,QString f,QString g,QDate h)
{
    this->nom=a;
    this->type=b;
    this->poids=c;
    this->volume=d;
    this->etat=e;
    this->destinataire=f;
    this->matiere=g;
    this->Date=h;
}

bool Dechets::ajouter ()
{
    QSqlQuery q ; //me permet dajouter
    QString poids_string=QString::number (poids); // convertir poids en string
    QString volume_string=QString::number (volume);
    q.prepare("insert into Dechets (ID,NOM,TYPE,POIDS,VOLUME,MATIERE,DATEARRIVE,ETAT,DESTINATAIRE,ID_C,ID_COL)""values(:nom,:type,:matiere,:destinataire,:etat,:poids,:volume,:date)");
    q.bindValue(":NOM",nom); // bindValue : relier les variables (attributs ) ajoutés a les attributs principales dans tableau déchets elli houwa f BD
    q.bindValue(":TYPE",type);
    q.bindValue(":MATIERE",matiere);
    q.bindValue(":DESTINATAIRE",destinataire);
    q.bindValue(":ETAT",etat);
    q.bindValue(":POIDS",poids);
    q.bindValue(":VOLUME",volume);
    q.bindValue(":DATEARRIVE",Date);
    return q.exec (); // verifer execution

}

bool Dechets::supprimer (int id )
{
    QSqlQuery q ;
    q.prepare("delete from dechets where ID =:id (paramétre)");  //ID = clé primaire elli fel tableau dechets f BD
    q.bindValue(":ID",id);
    return q.exec ();
}

QSqlQueryModel * Dechets:: afficher () //QSqlQueryModel : afficher tableau dechets f BD
{
    QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM Dechet"); // SELECT * FROM Dechet : afficher des attribus selon tabelau dechets // setQuery --> definir une nouvelle requette
        return model;
}

bool Dechets::modifier(int id)
{
QSqlQuery q ;
QString poids_string=QString::number (poids); // convertir poids en string
QString volume_string=QString::number (volume);
q.prepare("update dechets set nom=:nom,type=:type,matiere=:matiere,destinataire=:destinataire,etat=:etat,volume:=volume,date=:date where id (dechets)=:id (paramétre)"); //dechets :nom tableua BD
q.bindValue(":ID",id);
q.bindValue(":NOM",nom); // bindValue : relier les variables (attributs ) ajoutés a les attributs principales dans tableau déchets
q.bindValue(":TYPE",type);
q.bindValue(":MATIERE",matiere);
q.bindValue(":DESTINATAIRE",destinataire);
q.bindValue(":ETAT",etat);
q.bindValue(":POIDS",poids);
q.bindValue(":VOLUME",volume);
q.bindValue(":DATEARRIVE",Date);
return q.exec (); // verifer execution
}
