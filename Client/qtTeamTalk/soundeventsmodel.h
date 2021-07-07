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

#ifndef SOUNDEVENTSMODEL_H
#define SOUNDEVENTSMODEL_H

#include "common.h"
#include "ui_soundeventsmodel.h"

class SoundEventsModel : public QDialog
{
    Q_OBJECT
public:
    SoundEventsModel(QWidget * parent = 0);
private:
    Ui::SoundEventsModel ui;
    bool getSoundFile(QString& filename);
    void slotAccept();
    void slotEventNewUser();
    void slotEventRemoveUser();
    void slotEventServerLost();
    void slotEventUserTextMsg();
    void slotEventSentTextMsg();
    void slotEventChannelTextMsg();
    void slotEventSentChannelMsg();
    void slotEventBroadcastTextMsg();
    void slotEventHotKey();
    void slotEventSilence();
    void slotEventNewVideo();
    void slotEventNewDesktop();
    void slotEventFilesUpdated();
    void slotEventFileTxDone();
    void slotEventQuestionMode();
    void slotEventDesktopAccess();
    void slotEventUserLoggedIn();
    void slotEventUserLoggedOut();
    void slotEventVoiceActOn();
    void slotEventVoiceActOff();
    void slotEventMuteAllOn();
    void slotEventMuteAllOff();
    void slotEventTransmitQueueHead();
    void slotEventTransmitQueueStop();
    void slotEventVoiceActTrig();
    void slotEventVoiceActStop();
    void slotEventVoiceActMeOn();
    void slotEventVoiceActMeOff();
    void slotSPackChange();
};

#endif // SOUNDEVENTSMODEL_H
