/*
 * Copyright (c) 2005-2016, BearWare.dk
 *
 * Contact Information:
 *
 * Bjoern D. Rasmussen
 * Kirketoften 5
 * DK-8260 Viby J
 * Denmark
 * Email: contact@bearware.dk
 * Phone: +45 20 20 54 59
 * Web: http://www.bearware.dk
 *
 * This source code is part of the TeamTalk 5 SDK owned by
 * BearWare.dk. All copyright statements may not be removed
 * or altered from any source distribution. If you use this
 * software in a product, an acknowledgment in the product
 * documentation is required.
 *
 */

#include "soundeventsmodel.h"
#include "appinfo.h"
#include "settings.h"
#include <QFileDialog>
#include <QPushButton>

extern QSettings* ttSettings;

SoundEventsModel::SoundEventsModel(QWidget* parent/* = 0*/)
: QDialog(parent, QT_DEFAULT_DIALOG_HINTS)
{
    ui.setupUi(this);
    setWindowIcon(QIcon(APPICON));
    ui.buttonBox->button(QDialogButtonBox::Ok)->setText(tr("&Ok"));
    ui.buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("&Cancel"));

    connect(ui.spackBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SoundEventsModel::slotSPackChange);
    connect(ui.newuserButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventNewUser);
    connect(ui.rmuserButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventRemoveUser);
    connect(ui.srvlostButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventServerLost);
    connect(ui.usermsgButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventUserTextMsg);
    connect(ui.sentmsgButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventSentTextMsg);
    connect(ui.chanmsgButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventChannelTextMsg);
    connect(ui.sentchannelmsgButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventSentChannelMsg);
    connect(ui.bcastmsgButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventBroadcastTextMsg);
    connect(ui.hotkeyButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventHotKey);
    connect(ui.chansilentButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventSilence);
    connect(ui.videosessionButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventNewVideo);
    connect(ui.desktopsessionButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventNewDesktop);
    connect(ui.fileupdButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventFilesUpdated);
    connect(ui.transferdoneButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventFileTxDone);
    connect(ui.questionmodeBtn, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventQuestionMode);
    connect(ui.desktopaccessBtn, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventDesktopAccess);
    connect(ui.userloggedinButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventUserLoggedIn);
    connect(ui.userloggedoutButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventUserLoggedOut);
    connect(ui.voiceactonButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventVoiceActOn);
    connect(ui.voiceactoffButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventVoiceActOff);
    connect(ui.muteallonButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventMuteAllOn);
    connect(ui.mutealloffButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventMuteAllOff);
    connect(ui.transmitqueueheadButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventTransmitQueueHead);
    connect(ui.transmitqueuestopButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventTransmitQueueStop);
    connect(ui.voiceacttrigButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventVoiceActTrig);
    connect(ui.voiceactstopButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventVoiceActStop);
    connect(ui.voiceactmeonButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventVoiceActMeOn);
    connect(ui.voiceactmeoffButton, &QAbstractButton::clicked,
            this, &SoundEventsModel::slotEventVoiceActMeOff);

    ui.spackBox->clear();
    ui.spackBox->addItem(tr("Default"));
    QDir dir( SOUNDSPATH, "", QDir::Name, QDir::AllDirs|QDir::NoSymLinks|QDir::NoDotAndDotDot);
    QStringList aspack = dir.entryList();
    for(int i=0;i<aspack.size();i++)
    {
        QString packname = aspack[i].left(aspack[i].size());
        ui.spackBox->addItem(packname, packname);
    }
    QString pack = ttSettings->value(SETTINGS_SOUNDS_PACK, QCoreApplication::translate("MainWindow", SETTINGS_SOUNDS_PACK_DEFAULT)).toString();
    int index = ui.spackBox->findData(pack);
    if(index>=0)
        ui.spackBox->setCurrentIndex(index);
    ui.newuserEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_NEWUSER, SETTINGS_SOUNDEVENT_NEWUSER_DEFAULT).toString());
    ui.rmuserEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_REMOVEUSER, SETTINGS_SOUNDEVENT_REMOVEUSER_DEFAULT).toString());
    ui.srvlostEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_SERVERLOST, SETTINGS_SOUNDEVENT_SERVERLOST_DEFAULT).toString());
    ui.usermsgEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_USERMSG, SETTINGS_SOUNDEVENT_USERMSG_DEFAULT).toString());
    ui.sentmsgEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_SENTSOUND).toString());
    ui.chanmsgEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_CHANNELMSG, SETTINGS_SOUNDEVENT_CHANNELMSG_DEFAULT).toString());
    ui.sentchannelmsgEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_SENTCHANNELSOUND).toString());
    ui.bcastmsgEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_BROADCASTMSG, SETTINGS_SOUNDEVENT_BROADCASTMSG_DEFAULT).toString());
    ui.hotkeyEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_HOTKEY, SETTINGS_SOUNDEVENT_HOTKEY_DEFAULT).toString());
    ui.chansilentEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_SILENCE).toString());
    ui.videosessionEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_NEWVIDEO, SETTINGS_SOUNDEVENT_NEWVIDEO_DEFAULT).toString());
    ui.desktopsessionEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_NEWDESKTOP, SETTINGS_SOUNDEVENT_NEWDESKTOP_DEFAULT).toString());
    ui.fileupdEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_FILESUPD, SETTINGS_SOUNDEVENT_FILESUPD_DEFAULT).toString());
    ui.transferdoneEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_FILETXDONE, SETTINGS_SOUNDEVENT_FILETXDONE_DEFAULT).toString());
    ui.questionmodeEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_QUESTIONMODE, SETTINGS_SOUNDEVENT_QUESTIONMODE_DEFAULT).toString());
    ui.desktopaccessEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_DESKTOPACCESS, SETTINGS_SOUNDEVENT_DESKTOPACCESS_DEFAULT).toString());
    ui.userloggedinEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_USERLOGGEDIN, SETTINGS_SOUNDEVENT_USERLOGGEDIN_DEFAULT).toString());
    ui.userloggedoutEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_USERLOGGEDOUT, SETTINGS_SOUNDEVENT_USERLOGGEDOUT_DEFAULT).toString());
    ui.voiceactonEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTON, SETTINGS_SOUNDEVENT_VOICEACTON_DEFAULT).toString());
    ui.voiceactoffEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTOFF, SETTINGS_SOUNDEVENT_VOICEACTOFF_DEFAULT).toString());
    ui.muteallonEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_MUTEALLON, SETTINGS_SOUNDEVENT_MUTEALLON_DEFAULT).toString());
    ui.mutealloffEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_MUTEALLOFF, SETTINGS_SOUNDEVENT_MUTEALLOFF_DEFAULT).toString());
    ui.transmitqueueheadEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_TRANSMITQUEUE_HEAD, SETTINGS_SOUNDEVENT_TRANSMITQUEUE_HEAD_DEFAULT).toString());
    ui.transmitqueuestopEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_TRANSMITQUEUE_STOP, SETTINGS_SOUNDEVENT_TRANSMITQUEUE_STOP_DEFAULT).toString());
    ui.voiceacttrigEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTTRIG, SETTINGS_SOUNDEVENT_VOICEACTTRIG_DEFAULT).toString());
    ui.voiceactstopEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTSTOP, SETTINGS_SOUNDEVENT_VOICEACTSTOP_DEFAULT).toString());
    ui.voiceactmeonEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTMEON, SETTINGS_SOUNDEVENT_VOICEACTMEON_DEFAULT).toString());
    ui.voiceactmeoffEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTMEOFF, SETTINGS_SOUNDEVENT_VOICEACTMEOFF_DEFAULT).toString());
}

bool SoundEventsModel::getSoundFile(QString& filename)
{
    QString tmp = QFileDialog::getOpenFileName(this, tr("Open Wave File"),
                                               "",
                                               tr("Wave files (*.wav)"));
    tmp = QDir::toNativeSeparators(tmp);
    if(tmp.size())
        filename = tmp;
    return tmp.size();
}

void SoundEventsModel::slotEventNewUser()
{
    QString filename;
    if(getSoundFile(filename))
        ui.newuserEdit->setText(filename);
}

void SoundEventsModel::slotEventRemoveUser()
{
    QString filename;
    if(getSoundFile(filename))
        ui.rmuserEdit->setText(filename);
}

void SoundEventsModel::slotEventServerLost()
{
    QString filename;
    if(getSoundFile(filename))
        ui.srvlostEdit->setText(filename);
}

void SoundEventsModel::slotEventUserTextMsg()
{
    QString filename;
    if(getSoundFile(filename))
        ui.usermsgEdit->setText(filename);
}

void SoundEventsModel::slotEventSentTextMsg()
{
    QString filename;
    if (getSoundFile(filename))
        ui.sentmsgEdit->setText(filename);
}

void SoundEventsModel::slotEventChannelTextMsg()
{
    QString filename;
    if(getSoundFile(filename))
        ui.chanmsgEdit->setText(filename);
}

void SoundEventsModel::slotEventSentChannelMsg()
{
    QString filename;
    if (getSoundFile(filename))
        ui.sentchannelmsgEdit->setText(filename);
}

void SoundEventsModel::slotEventBroadcastTextMsg()
{
    QString filename;
    if(getSoundFile(filename))
        ui.bcastmsgEdit->setText(filename);
}

void SoundEventsModel::slotEventHotKey()
{
    QString filename;
    if(getSoundFile(filename))
        ui.hotkeyEdit->setText(filename);
}

void SoundEventsModel::slotEventSilence()
{
    QString filename;
    if(getSoundFile(filename))
        ui.chansilentEdit->setText(filename);
}

void SoundEventsModel::slotEventNewVideo()
{
    QString filename;
    if(getSoundFile(filename))
        ui.videosessionEdit->setText(filename);
}

void SoundEventsModel::slotEventNewDesktop()
{
    QString filename;
    if(getSoundFile(filename))
        ui.desktopsessionEdit->setText(filename);
}

void SoundEventsModel::slotEventFilesUpdated()
{
    QString filename;
    if(getSoundFile(filename))
        ui.fileupdEdit->setText(filename);
}

void SoundEventsModel::slotEventFileTxDone()
{
    QString filename;
    if(getSoundFile(filename))
        ui.transferdoneEdit->setText(filename);
}

void SoundEventsModel::slotEventQuestionMode()
{
    QString filename;
    if(getSoundFile(filename))
        ui.questionmodeEdit->setText(filename);
}

void SoundEventsModel::slotEventDesktopAccess()
{
    QString filename;
    if(getSoundFile(filename))
        ui.desktopaccessEdit->setText(filename);
}

void SoundEventsModel::slotEventUserLoggedIn()
{
    QString filename;
    if(getSoundFile(filename))
        ui.userloggedinEdit->setText(filename);
}

void SoundEventsModel::slotEventUserLoggedOut()
{
    QString filename;
    if(getSoundFile(filename))
        ui.userloggedoutEdit->setText(filename);
}

void SoundEventsModel::slotEventVoiceActOn()
{
    QString filename;
    if(getSoundFile(filename))
        ui.voiceactonEdit->setText(filename);
}

void SoundEventsModel::slotEventVoiceActOff()
{
    QString filename;
    if(getSoundFile(filename))
        ui.voiceactoffEdit->setText(filename);
}

void SoundEventsModel::slotEventMuteAllOn()
{
    QString filename;
    if(getSoundFile(filename))
        ui.muteallonEdit->setText(filename);
}

void SoundEventsModel::slotEventMuteAllOff()
{
    QString filename;
    if(getSoundFile(filename))
        ui.mutealloffEdit->setText(filename);
}

void SoundEventsModel::slotEventTransmitQueueHead()
{
    QString filename;
    if(getSoundFile(filename))
        ui.transmitqueueheadEdit->setText(filename);
}

void SoundEventsModel::slotEventTransmitQueueStop()
{
    QString filename;
    if(getSoundFile(filename))
        ui.transmitqueuestopEdit->setText(filename);
}

void SoundEventsModel::slotEventVoiceActTrig()
{
    QString filename;
    if(getSoundFile(filename))
        ui.voiceacttrigEdit->setText(filename);
}

void SoundEventsModel::slotEventVoiceActStop()
{
    QString filename;
    if(getSoundFile(filename))
        ui.voiceactstopEdit->setText(filename);
}

void SoundEventsModel::slotEventVoiceActMeOn()
{
    QString filename;
    if(getSoundFile(filename))
        ui.voiceactmeonEdit->setText(filename);
}

void SoundEventsModel::slotEventVoiceActMeOff()
{
    QString filename;
    if(getSoundFile(filename))
        ui.voiceactmeoffEdit->setText(filename);
}

void SoundEventsModel::slotAccept()
{
    ttSettings->setValue(SETTINGS_SOUNDS_PACK, ui.spackBox->currentText());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_NEWUSER, ui.newuserEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_REMOVEUSER, ui.rmuserEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_SERVERLOST, ui.srvlostEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_USERMSG, ui.usermsgEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_SENTSOUND, ui.sentmsgEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_CHANNELMSG, ui.chanmsgEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_SENTCHANNELSOUND, ui.sentchannelmsgEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_BROADCASTMSG, ui.bcastmsgEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_HOTKEY, ui.hotkeyEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_SILENCE, ui.chansilentEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_NEWVIDEO, ui.videosessionEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_NEWDESKTOP, ui.desktopsessionEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_FILESUPD, ui.fileupdEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_FILETXDONE, ui.transferdoneEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_QUESTIONMODE, ui.questionmodeEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_DESKTOPACCESS, ui.desktopaccessEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_USERLOGGEDIN, ui.userloggedinEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_USERLOGGEDOUT, ui.userloggedoutEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_VOICEACTON, ui.voiceactonEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_VOICEACTOFF, ui.voiceactoffEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_MUTEALLON, ui.muteallonEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_MUTEALLOFF, ui.mutealloffEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_TRANSMITQUEUE_HEAD, ui.transmitqueueheadEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_TRANSMITQUEUE_STOP, ui.transmitqueuestopEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_VOICEACTTRIG, ui.voiceacttrigEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_VOICEACTSTOP, ui.voiceactstopEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_VOICEACTMEON, ui.voiceactmeonEdit->text());
    ttSettings->setValue(SETTINGS_SOUNDEVENT_VOICEACTMEOFF, ui.voiceactmeoffEdit->text());
}

void SoundEventsModel::slotSPackChange()
{
    ui.newuserEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_NEWUSER_DEFAULT, SETTINGS_SOUNDEVENT_NEWUSER_DEFAULT).toString());
    ui.rmuserEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_REMOVEUSER_DEFAULT, SETTINGS_SOUNDEVENT_REMOVEUSER_DEFAULT).toString());
    ui.srvlostEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_SERVERLOST_DEFAULT, SETTINGS_SOUNDEVENT_SERVERLOST_DEFAULT).toString());
    ui.usermsgEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_USERMSG_DEFAULT, SETTINGS_SOUNDEVENT_USERMSG_DEFAULT).toString());
    ui.chanmsgEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_CHANNELMSG_DEFAULT, SETTINGS_SOUNDEVENT_CHANNELMSG_DEFAULT).toString());
    ui.bcastmsgEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_BROADCASTMSG_DEFAULT, SETTINGS_SOUNDEVENT_BROADCASTMSG_DEFAULT).toString());
    ui.hotkeyEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_HOTKEY_DEFAULT, SETTINGS_SOUNDEVENT_HOTKEY_DEFAULT).toString());
    ui.videosessionEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_NEWVIDEO_DEFAULT, SETTINGS_SOUNDEVENT_NEWVIDEO_DEFAULT).toString());
    ui.desktopsessionEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_NEWDESKTOP_DEFAULT, SETTINGS_SOUNDEVENT_NEWDESKTOP_DEFAULT).toString());
    ui.fileupdEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_FILESUPD_DEFAULT, SETTINGS_SOUNDEVENT_FILESUPD_DEFAULT).toString());
    ui.transferdoneEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_FILETXDONE_DEFAULT, SETTINGS_SOUNDEVENT_FILETXDONE_DEFAULT).toString());
    ui.questionmodeEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_QUESTIONMODE_DEFAULT, SETTINGS_SOUNDEVENT_QUESTIONMODE_DEFAULT).toString());
    ui.desktopaccessEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_DESKTOPACCESS_DEFAULT, SETTINGS_SOUNDEVENT_DESKTOPACCESS_DEFAULT).toString());
    ui.userloggedinEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_USERLOGGEDIN_DEFAULT, SETTINGS_SOUNDEVENT_USERLOGGEDIN_DEFAULT).toString());
    ui.userloggedoutEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_USERLOGGEDOUT_DEFAULT, SETTINGS_SOUNDEVENT_USERLOGGEDOUT_DEFAULT).toString());
    ui.voiceactonEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTON_DEFAULT, SETTINGS_SOUNDEVENT_VOICEACTON_DEFAULT).toString());
    ui.voiceactoffEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTOFF_DEFAULT, SETTINGS_SOUNDEVENT_VOICEACTOFF_DEFAULT).toString());
    ui.muteallonEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_MUTEALLON_DEFAULT, SETTINGS_SOUNDEVENT_MUTEALLON_DEFAULT).toString());
    ui.mutealloffEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_MUTEALLOFF_DEFAULT, SETTINGS_SOUNDEVENT_MUTEALLOFF_DEFAULT).toString());
    ui.transmitqueueheadEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_TRANSMITQUEUE_HEAD_DEFAULT, SETTINGS_SOUNDEVENT_TRANSMITQUEUE_HEAD_DEFAULT).toString());
    ui.transmitqueuestopEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_TRANSMITQUEUE_STOP_DEFAULT, SETTINGS_SOUNDEVENT_TRANSMITQUEUE_STOP_DEFAULT).toString());
    ui.voiceacttrigEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTTRIG_DEFAULT, SETTINGS_SOUNDEVENT_VOICEACTTRIG_DEFAULT).toString());
    ui.voiceactstopEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTSTOP_DEFAULT, SETTINGS_SOUNDEVENT_VOICEACTSTOP_DEFAULT).toString());
    ui.voiceactmeonEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTMEON_DEFAULT, SETTINGS_SOUNDEVENT_VOICEACTMEON_DEFAULT).toString());
    ui.voiceactmeoffEdit->setText(ttSettings->value(SETTINGS_SOUNDEVENT_VOICEACTMEOFF_DEFAULT, SETTINGS_SOUNDEVENT_VOICEACTMEOFF_DEFAULT).toString());
    QString dirtoscan = QString("%1/%2").arg(SOUNDSPATH).arg(ui.spackBox->currentText());
    QDir soundsdir( dirtoscan, "*.wav", QDir::Name, QDir::Files|QDir::NoSymLinks);
    QStringList packfile = soundsdir.entryList();
    for(int i=0;i<packfile.size();i++)
    {
        QString filename = packfile[i].left(packfile[i].size()-4);
        if(filename == "newuser")
           ui.newuserEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "removeuser")
           ui.rmuserEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "serverlost")
           ui.srvlostEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "user_msg")
           ui.usermsgEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "channel_msg")
           ui.chanmsgEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "broadcast_msg")
           ui.bcastmsgEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "hotkey")
           ui.hotkeyEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "videosession")
           ui.videosessionEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "desktopsession")
           ui.desktopsessionEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "fileupdate")
           ui.fileupdEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "filetx_complete")
           ui.transferdoneEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "questionmode")
           ui.questionmodeEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "desktopaccessreq")
           ui.desktopaccessEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "logged_on")
           ui.userloggedinEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "logged_off")
           ui.userloggedoutEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "vox_enable")
           ui.voiceactonEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "vox_disable")
           ui.voiceactoffEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "mute_all")
           ui.muteallonEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "unmute_all")
           ui.mutealloffEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "txqueue_start")
           ui.transmitqueueheadEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "txqueue_stop")
           ui.transmitqueuestopEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "voiceact_on")
           ui.voiceacttrigEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "voiceact_off")
           ui.voiceactstopEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "vox_me_enable")
           ui.voiceactmeonEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
        if(filename == "vox_me_disable")
           ui.voiceactmeoffEdit->setText(QString("%1/%2/%3.wav").arg(SOUNDSPATH).arg(ui.spackBox->currentText()).arg(filename));
    }
}
