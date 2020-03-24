#pragma once

#include "pch.h"
#include "ui_schedule_widget.h"

class ScheduleWidget : public QWidget {
  Q_OBJECT

public:
  /*
    StreamWidget(QProcess *rclone, QProcess *player, const QString &remote,
                 const QString &stream, const QStringList &args,
                 QWidget *parent = nullptr);
    ~StreamWidget();
  */

  ScheduleWidget(const QString &taskId, const QString &taskName, QWidget *parent = nullptr);
  ~ScheduleWidget();

  bool isRunning = true;

public slots:
  //  void cancel();

signals:
  //  void finished();
  // void closed();

private:
  Ui::ScheduleWidget ui;
  QStringList mArgs;


  void applySettingsToScreen();

  // list of scheduler parameters to be persistent in file
  QString mTaskId;
  QString mTaskName; //b64
  QString mSchedulerName; //b64
  QString mSchedulerId = QUuid::createUuid().toString();

  QString mLastRun = "Last run: never"; //b64
  QString mRequestId = "";
  QString mLastRunFinished = ""; //b64
  QString mLastRunStatus = ""; //b64

  bool mDailyState = true;
  bool mDailyMon = true;
  bool mDailyTue = true;
  bool mDailyWed = true;
  bool mDailyThu = true;
  bool mDailyFri = true;
  bool mDailySat = true;
  bool mDailySun = true;

  bool mCronState = false;
  QString mCron = "30 6,18 */2 * MON-FRI";

  QString executionMode = "1"; //1,2,3

};
