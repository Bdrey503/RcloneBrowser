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

  ScheduleWidget(const QString &taskName,
               QWidget *parent = nullptr);
  ~ScheduleWidget();


  bool isRunning = true;

public slots:
  void cancel();

signals:
  void finished();
  void closed();

private:
  Ui::StreamWidget ui;

  QProcess *mRclone;
  QProcess *mPlayer;

  QStringList mArgs;
};
