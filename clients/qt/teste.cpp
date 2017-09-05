#include "teste.h"
#include <QDateTime>
#include <QtGlobal>

Teste::Teste(){
	QDateTime cd = QDateTime::currentDateTime();
	qsrand(cd.toTime_t());
}

Teste::~Teste(){

}


int Teste::runToBall(){
	return (int) qrand()%10;
}
