#include "qmltranslator.h"
#include <QApplication>

QmlTranslator::QmlTranslator(QObject *parent) : QObject(parent)
{

}

void QmlTranslator::setTranslation(std::string translation)
{
    m_translator.load(":/QmlLanguage_" + QString(translation.c_str()), "."); // Загружаем перевод
    qApp->installTranslator(&m_translator);                 // Устанавливаем его в приложение
    emit languageChanged();                                 // Сигнализируем об изменении текущего перевода
}
