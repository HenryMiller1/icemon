/*
    This file is part of Icecream.

    Copyright (c) 2003 Frerich Raabe <raabe@kde.org>
    Copyright (c) 2003,2004 Stephan Kulow <coolo@kde.org>
    Copyright (c) 2003,2004 Cornelius Schumacher <schumacher@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#ifndef ICEMON_MONITOR_H
#define ICEMON_MONITOR_H

#include "statusview.h"

#include <kmainwindow.h>
#include <time.h>
#include <qdict.h>

class MsgChannel;
class QSocketNotifier;
class Msg;
class HostInfoManager;

class Monitor : public QObject
{
    Q_OBJECT
  public:
    Monitor( HostInfoManager *, QObject *parent, const char *name = 0 );
    ~Monitor();

    void setCurrentNet( const QString & );
    void setCurrentView( StatusView *, bool rememberJobs );

  protected:
    void setSchedulerState( bool );

  private slots:
    void slotCheckScheduler();
    void msgReceived();

  private:
    void checkScheduler(bool deleteit = false);
    void handle_getcs( Msg *m );
    void handle_job_begin( Msg *m );
    void handle_job_done( Msg *m );
    void handle_stats( Msg *m );
    void handle_local_begin( Msg *m );
    void handle_local_done( Msg *m );

    HostInfoManager *m_hostInfoManager;
    StatusView *m_view;
    JobList m_rememberedJobs;
    MsgChannel *m_scheduler;
    QSocketNotifier *m_scheduler_read;
    QString m_current_netname;

    bool mSchedulerOnline;
};

#endif // MON_KDE_H
// vim:ts=4:sw=4:noet