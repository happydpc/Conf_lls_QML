#include "./interfaces/interfaceSerial.h"
#include "QDebug"

InterfaceSerial::InterfaceSerial() {
    this->portHandler = new QSerialPort();
}

InterfaceSerial::InterfaceSerial(const InterfaceSerial & interface) {
    this->portHandler = interface.portHandler;
}

InterfaceSerial::~InterfaceSerial() {}
void InterfaceSerial::initInterface()  {}

bool InterfaceSerial::openInterface(QString name, QStringList arg) {
    if(arg.size() > 0) {
        portHandler->setPortName(name);
        portHandler->setBaudRate(QString(arg.at(0)).toInt());
        portHandler->setDataBits(QSerialPort::Data8);
        portHandler->setParity(QSerialPort::NoParity);
        portHandler->setStopBits(QSerialPort::OneStop);
        portHandler->setFlowControl(QSerialPort::NoFlowControl);
        return portHandler->open(QIODevice::ReadWrite);
    }
    return false;
}

bool InterfaceSerial::isOpen() {
    return portHandler->isOpen();
}

void InterfaceSerial::closeInterface() {
    if(portHandler != nullptr) {
        if(portHandler->isOpen()) {
            portHandler->close();
        }
    }
}

bool InterfaceSerial::sendData(QByteArray &pData)  {
    if(!portHandler->isOpen()) {
        return false;
    }
    return (bool)portHandler->write(pData);
}

bool InterfaceSerial::readData(QByteArray &pData)  {
    if(!portHandler->isOpen()) {
        return false;
    }
    pData = portHandler->readAll();
    return (bool)pData.length();
}

QString InterfaceSerial::getInterfaceName() {
    return portHandler->portName();
}

QStringList InterfaceSerial::getInfoInterface(QString name) {
    QString description;
    QString manufacturer;
    QString serialNumber;
    QString baudrate;
    QStringList list;
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos) {
        if(info.portName().contains(name)) {
            description = info.description();
            manufacturer = info.manufacturer();
            serialNumber = info.serialNumber();
            if(portHandler->isOpen()) {
                baudrate = QString::number(portHandler->baudRate());
            }
            list << description;
            list << manufacturer;
            list << serialNumber;
            list << info.portName();
            list << baudrate;
            break;
        }
    }
    return list;
}

QStringList InterfaceSerial::getAvailableList() {
    QStringList list;
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos) {
        if(portHandler != nullptr) {
            if(!portHandler->isOpen()) {
                list << info.portName();
            }
        }
    }
    return list;
}


void InterfaceSerial::aboutClose() {
    emit closeIsNormal();
}

//#include <QSerialPortInfo>
//#include <QMessageBox>
//#include "serialport.h"
//#include "ui_serialport.h"
//#include "searchlls.h"

//SerialPort::SerialPort(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::SerialPort)
//{
//    ui->setupUi(this);

//    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

//    port = new QSerialPort();
//    lls = new Lls(port);
//    lls_is_active = false;
//    lls_disconnected = false;
//    pause_mode_state = false;
//    last_port_is_available = false;
//    getPortsInfo();
//    fillPortsParameters();
//    //--- открываем файла .conf
//    tty_settings = new QSettings("./conf/tty.conf", QSettings::IniFormat);
//    openLastSession();
//}

//void SerialPort::openLastSession() {
//    //--- если настройки ок - используем
//    if(tty_settings->value("valid") == true) {
//        const auto infos = QSerialPortInfo::availablePorts();
//        //--- если порт из настроек есть в текущем списке
//        int port_counter = 0;
//        for(const QSerialPortInfo &info : infos) {
//            if(info.portName() == tty_settings->value("last_tty").toString()) {
//                last_port_is_available = true;
//                if(tty_settings->value("last_lls_id").toInt() != 0) {
//                    ui->lls_addr->setValue(tty_settings->value("last_lls_id").toInt());
//                }
//                ui->serial_port->setCurrentIndex(port_counter);
//                ui->baudRateBox->setCurrentIndex(tty_settings->value("last_baudrate").toInt());
//                ui->lls_paswd->setText(tty_settings->value("last_pass").toString());
//                //--- попытка открытия
//                on_open_button_clicked();
//                return;
//            }
//            port_counter ++;
//        }
//    } else {
//        //--- default settings
//        tty_settings->setValue("last_tty", "");
//        tty_settings->setValue("last_lls_id", "1");
//        tty_settings->setValue("valid", true);
//    }
//}
///**************************************************************************************************/
//void SerialPort::saveSession() {
//    tty_settings->setValue("last_tty", ui->serial_port->currentText());
//    tty_settings->setValue("last_lls_id", ui->lls_addr->text());
//    tty_settings->setValue("last_baudrate", ui->baudRateBox->currentIndex());
//    tty_settings->setValue("last_pass", ui->lls_paswd->text());
//    tty_settings->setValue("valid", true);
//}
///**************************************************************************************************/
//void SerialPort::portError(QSerialPort::SerialPortError)
//{
//    QMessageBox::critical(this, "Ошибка", "Ошибка COM порта");
//    disconnect(lls);
//    port->close();
//}
///**************************************************************************************************/
//void SerialPort::fillPortsParameters() {
//    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
//    ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
//    ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
//    ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
//    ui->baudRateBox->setCurrentIndex(1); // default 19200
//}
///**************************************************************************************************/
//void SerialPort::getPortsInfo() {
//    ui->serial_port->clear();
//    QString description;
//    QString manufacturer;
//    QString serialNumber;
//    const auto infos = QSerialPortInfo::availablePorts();
//    for(const QSerialPortInfo &info : infos) {
//        QStringList list;
//        description = info.description();
//        manufacturer = info.manufacturer();
//        serialNumber = info.serialNumber();
//        list << info.portName();
//        ui->serial_port->addItem(list.first(), list);
//        ui->open_button->setVisible(true);
//    }
//}
///**************************************************************************************************/
//void SerialPort::setSettings(QString tty_name, int id) {

//}
///**************************************************************************************************/
//bool SerialPort::lastOpenPortIsAvailable() {
//    return last_port_is_available;
//}
///**************************************************************************************************/
//bool SerialPort::isButtonAck() {
//    return open_button_ack;
//}
///**************************************************************************************************/
//void SerialPort::on_updateListPort_clicked() {
//    getPortsInfo();
//}
///**************************************************************************************************/
//void SerialPort::on_seachLls_clicked() {
//    if (ui->serial_port->currentIndex() == -1) {
//        return;
//    }
//    QString port_name = ui->serial_port->currentText();
//    int baudrate = ui->baudRateBox->currentText().toInt();
//    port->setPortName(port_name);
//    port->setBaudRate(baudrate);
//    port->setDataBits(QSerialPort::Data8);
//    port->setParity(QSerialPort::NoParity);
//    port->setStopBits(QSerialPort::OneStop);
//    port->setFlowControl(QSerialPort::NoFlowControl);
//    if(port->open(QIODevice::ReadWrite)) {
//        connect(port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(portError(QSerialPort::SerialPortError)));
//        SearchLls *search_lls = new SearchLls();
//        search_lls->setPort(port);
//        search_lls->startSearch();
//        search_lls->exec();
//        ui->lls_addr->setValue(search_lls->selected_id);
//        disconnect(port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(portError(QSerialPort::SerialPortError)));
//        port->close();
//        search_lls->deleteLater();
//    } else {
//        QMessageBox::critical(this, tr("Ошибка"), QString("Не удалось открыть порт (%1)").arg(port->errorString()));
//    }
//}
///**************************************************************************************************/
//void SerialPort::exectCommandLls(S_command command, Lls::S_lls_data data)
//{
//    if(command.type == lls_check_address_and_pass) {
//        //--- тут один раз при коннекте если ок
//        //--- сохраняем настройки
//        saveSession();
//        //---
//        if(data.pass.auth_is_normal) {
//            QMessageBox::critical(this, "Ошибка", "Настроечный пароль не совпадает\nПроверьте правильность ввода");
//            portClose();
//            return;
//        }
//    }

//    if(lls_disconnected) {
//        lls_disconnected = false;
//        S_command command_struct;
//        command_struct.type = lls_check_address_and_pass;
//        command_list.push_back(command_struct);
//        command_struct.type = lls_read_settings;
//        command_list.push_back(command_struct);
//        command_struct.type = lls_read_serial_number;
//        command_list.push_back(command_struct);
//        command_struct.type = lls_read_errors;
//        command_list.push_back(command_struct);
//        command_struct.type = lls_read_cal_table;
//        command_list.push_back(command_struct);
//    }
//    emit llsActive();
//    lls_is_active = true;

//    switch(command_list.first().type) {
//    case lls_read_lvl_once:
//        emit updateGetLvlOnce(lls->lls_data);
//        break;
//    case lls_send_data_enable: break;
//    case lls_set_send_time: break;
//    case lls_send_data_default: break;
//    case lls_read_cnt:
//        emit updateGetCnt(lls->lls_data);
//        break;
//    case lls_read_lvl_all:
//        emit updateReadLevelAll(lls->lls_data);
//        break;
//    case lls_read_settings:
//        emit updateGetSettings(lls->lls_data);
//        break;
//    case lls_write_settings:
//        emit updateWriteSettings(lls->lls_data);
//        ui->lls_addr->setValue(command_list.first().data.settings_new.netAddress);
//        break;
//    case lls_read_cal_table:
//        emit updateReadCalTable(lls->lls_data);
//        break;
//    case lls_write_cal_table:
//        emit updateWriteCalTable(lls->lls_data);
//        break;
//    case lls_calibrate_min:
//    case lls_calibrate_max:
//        emit updateCalibrateMinMax(lls->lls_data);
//        break;
//    case lls_read_errors:
//        emit updateReadError(lls->lls_data);
//        break;
//    case lls_set_serial_number: break;
//    case lls_read_serial_number:
//        emit updateGetSerialNum(lls->lls_data);
//        break;
//    case lls_set_personal: break;
//    case lls_read_personal: break;
//    case lls_set_new_password:
//        emit passwdIsUpdated();
//        break;
//    case lls_check_address_and_pass:
//        break;
//    case lls_run_bootloader: break;
//    default : break;
//    }
//    if(command_list.size() > 0) {
//        command_list.removeFirst();
//    }
//    QTimer::singleShot(100, Qt::CoarseTimer, this, SLOT(commandHandlerLls()));
//}
///**************************************************************************************************/
//void SerialPort::commandError(S_command command)
//{
//    emit noReply();
//    if((command.type == lls_check_address_and_pass) //-- если первая попытка сконнектить
//            && (last_port_is_available)) {          //-- по настройкам не удалась
//        last_port_is_available = false;             //-- тогда все сбросить и закрыть порт (иначе форма будет открытой)
//        portClose();
//    }
//    lls_is_active = false;
//    lls_disconnected = true;
//    QTimer::singleShot(200, Qt::CoarseTimer, this, SLOT(commandHandlerLls()));
//}
///**************************************************************************************************/
//void SerialPort::on_open_button_clicked() {
//    QString port_name = ui->serial_port->currentText();
//    int baudrate = ui->baudRateBox->currentText().toInt();
//    port->setPortName(port_name);
//    port->setBaudRate(baudrate);
//    port->setDataBits(QSerialPort::Data8);
//    port->setParity(QSerialPort::NoParity);
//    port->setStopBits(QSerialPort::OneStop);
//    port->setFlowControl(QSerialPort::NoFlowControl);
//    if(port->open(QIODevice::ReadWrite)) {
//        port->flush();
//        connect(lls, SIGNAL(readyCommand(S_command,Lls::S_lls_data)), this, SLOT(exectCommandLls(S_command, Lls::S_lls_data)));
//        connect(lls, SIGNAL(errorCommand(S_command)), this, SLOT(commandError(S_command)));
//        uint8_t tpass[8] = {0};
//        for(uint8_t i=0; i<ui->lls_paswd->text().length(); i++) {
//            tpass[i] = ui->lls_paswd->text().toUtf8().at(i);
//        }
//        passws_form = ui->lls_paswd->text();
//        lls->setPassworSession((uint8_t*)tpass);
//        S_command command_struct;
//        command_struct.type = lls_check_address_and_pass;
//        command_list.push_back(command_struct);
//        command_struct.type = lls_read_settings;
//        command_list.push_back(command_struct);
//        command_struct.type = lls_read_serial_number;
//        command_list.push_back(command_struct);
//        command_struct.type = lls_read_errors;
//        command_list.push_back(command_struct);
//        command_struct.type = lls_read_cal_table;
//        command_list.push_back(command_struct);
//        commandHandlerLls();
//        open_button_ack = true;
//    } else {
//        QMessageBox::warning(this, "COM порт", "Ошибка открытия порта");
//    }
//    close();
//}
///**************************************************************************************************/
//void SerialPort::portClose() {
//    if(port != NULL) {
//        port->close();
//        disconnect(lls, SIGNAL(readyCommand(S_command,Lls::S_lls_data)), this, SLOT(exectCommandLls(S_command, Lls::S_lls_data)));
//        disconnect(lls, SIGNAL(errorCommand(S_command)), this, SLOT(commandError(S_command)));
//        disconnect(port);
//        command_list.clear();
//        lls_is_active = false;
//        emit noReply();
//    }
//}
///**************************************************************************************************/
//bool SerialPort::isActive() {
//    return lls_is_active;
//}

///**************************************************************************************************/
//bool SerialPort::portIsOpen() {
//    return port->isOpen();
//}
///**************************************************************************************************/
//SerialPort::~SerialPort() {
//    delete ui;
//}

///**************************************************************************************************/
//void SerialPort::commandHandlerLls()
//{
//    if(port->isOpen()) {
//        if(!pause_mode_state) {
//            if(command_list.size() == 0) { // если нет текущих задач - тогда добавляем чтение cnt и уровня
//                S_command command_struct;
//                command_struct.type = lls_read_cnt;
//                command_list.push_back(command_struct);
//                command_struct.type = lls_read_lvl_once;
//                command_list.push_back(command_struct);
//                command_struct.type = lls_read_lvl_all;
//                command_list.push_back(command_struct);
//            }
//            lls->writeCommand(command_list.first(), ui->lls_addr->text().toInt());
//        }
//    }
//}
///**************************************************************************************************/
//void SerialPort::readLlsErrors() {
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_read_errors;
//        command_list.push_back(tcommand);
//    }
//}
///**************************************************************************************************/
//void SerialPort::readCalTable() {
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_read_cal_table;
//        command_list.push_back(tcommand);
//    }
//}
///**************************************************************************************************/
//void SerialPort::writeCalTable(T_calibrationTable table) {
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_write_cal_table;
//        tcommand.data.table = table;
//        command_list.push_back(tcommand);
//    }
//}
///**************************************************************************************************/
//bool SerialPort::setNewPasswd(QString passw) {
//    bool res = false;
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_set_new_password;
//        memset((char*)tcommand.data.new_passw, 0, sizeof(tcommand.data.new_passw));
//        uint16_t len = passw.length();
//        if(len > sizeof(tcommand.data.new_passw)) {
//            memcpy((char*)tcommand.data.new_passw, passw.toLocal8Bit(), sizeof(tcommand.data.new_passw));
//        } else {
//            memcpy((char*)tcommand.data.new_passw, passw.toLocal8Bit(), len);
//        }
//        command_list.push_back(tcommand); // отправляем команду в очередь на выполенеsние
//        res = true;
//    }
//    return res;
//}

///**************************************************************************************************/
//bool SerialPort::setCalibrateNewValues(uint32_t min, uint32_t max) {
//    bool res = false;
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_read_settings;
//        command_list.push_back(tcommand); // сперва считать настройки
//        // меняем настройки
//        tcommand.type = lls_write_settings;
//        tcommand.data.settings_new = lls->lls_data.settings;
//        tcommand.data.settings_new.cntEmpty = min;
//        tcommand.data.settings_new.cntFull = max;
//        command_list.push_back(tcommand); // отправляем команду в очередь на выполенение
//        res = true;
//    }
//    return res;
//}

///**************************************************************************************************/
//bool SerialPort::setLlsFuelEmptyLimit(void) {
//    bool res = false;
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_calibrate_min;
//        command_list.push_back(tcommand);
//        res = true;
//    }
//    return res;
//}
///**************************************************************************************************/
//bool SerialPort::getSettings() {
//    bool res = false;
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_read_settings;
//        command_list.push_back(tcommand);
//        res = true;
//    }
//    return res;
//}
///**************************************************************************************************/
//void SerialPort::writeSettings(T_settings settings) {
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_write_settings;
//        tcommand.data.settings_new = settings;
//        command_list.push_back(tcommand);
//        tcommand.type = lls_read_settings;
//        command_list.push_back(tcommand);
//    }
//}
///**************************************************************************************************/
//bool SerialPort::setLlsFuelFullLimit(void) {
//    bool res = false;
//    if(port->isOpen()) {
//        S_command tcommand;
//        tcommand.type = lls_calibrate_max;
//        command_list.push_back(tcommand);
//        res = true;
//    }
//    return res;
//}
///**************************************************************************************************/
//void SerialPort::setPauseMode() {
//    pause_mode_state = true;
//}
///**************************************************************************************************/
//void SerialPort::stopPauseMode() {
//    S_command command_struct;
//    pause_mode_state = false;
//    command_struct.type = lls_check_address_and_pass;
//    command_list.push_back(command_struct);
//    command_struct.type = lls_read_settings;
//    command_list.push_back(command_struct);
//    command_struct.type = lls_read_serial_number;
//    command_list.push_back(command_struct);
//    command_struct.type = lls_read_errors;
//    command_list.push_back(command_struct);
//    command_struct.type = lls_read_cal_table;
//    command_list.push_back(command_struct);
//    commandHandlerLls();
//}
