#include "schedule_widget.h"
#include "utils.h"

ScheduleWidget::ScheduleWidget(const QString &taskId, const QString &taskName, QWidget *parent)
    : QWidget(parent) {

  if (taskName == "") {
  }

mTaskId = taskId;
mTaskName = taskName;

  ui.setupUi(this);
  auto settings = GetSettings();

  QString newInfo ="Scheduled task: " + taskName;

  if (newInfo.length() > 140) {
    mSchedulerName = newInfo.left(57) + "..." + newInfo.right(80);
  } else {
    mSchedulerName = newInfo;
  }

  applySettingsToScreen();

  ui.info->setEnabled(false);
  ui.nextRun->setEnabled(false);

  /*
    QString remoteTrimmed;

    auto settings = GetSettings();
    mArgs.append(QDir::toNativeSeparators(GetRclone()));
    mArgs.append(args);
    mArgs.append(" | ");
    mArgs.append(stream);

    ui.showOutput->setToolTip(mArgs.join(" "));

    if (remote.length() > 140) {
      remoteTrimmed = remote.left(57) + "..." + remote.right(80);
    } else {
      remoteTrimmed = remote;
    }

    ui.info->setText(remoteTrimmed);
    ui.info->setCursorPosition(0);

    ui.stream->setText(stream);
    ui.stream->setCursorPosition(0);
    ui.stream->setToolTip(stream);

    ui.remote->setText(remote);
    ui.remote->setCursorPosition(0);
    ui.remote->setToolTip(remote);

    ui.details->setVisible(false);

    ui.output->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    ui.output->setVisible(false);
  */

  QString iconsColour = settings->value("Settings/iconsColour").toString();

  QString img_add = "";

  if (iconsColour == "white") {
    img_add = "_inv";
  }

  ui.showDetails->setIcon(
      QIcon(":media/images/qbutton_icons/vrightarrow" + img_add + ".png"));
  ui.showDetails->setIconSize(QSize(24, 24));

  ui.details->setVisible(false);

  /*
    ui.showOutput->setIcon(
        QIcon(":media/images/qbutton_icons/vrightarrow" + img_add + ".png"));
    ui.showOutput->setIconSize(QSize(24, 24));
  */

  /*
    ui.cancel->setToolTip("Stop streaming");
    ui.cancel->setStatusTip("Stop streaming");
  */

  ui.runTask->setIcon(
      QIcon(":media/images/qbutton_icons/run" + img_add + ".png"));
  ui.runTask->setIconSize(QSize(24, 24));

  ui.cancel->setIcon(
      QIcon(":media/images/qbutton_icons/cancel" + img_add + ".png"));
  ui.cancel->setIconSize(QSize(24, 24));

  ui.pause->setIcon(
      QIcon(":media/images/qbutton_icons/pause" + img_add + ".png"));
  ui.pause->setIconSize(QSize(24, 24));

  ui.start->setIcon(
      QIcon(":media/images/qbutton_icons/run" + img_add + ".png"));
  ui.start->setIconSize(QSize(24, 24));

  ui.pause->setEnabled(false);

  QObject::connect(ui.cancel, &QToolButton::clicked, this, [=]() {});

  QObject::connect(
      ui.showDetails, &QToolButton::toggled, this, [=](bool checked) {
        ui.details->setVisible(checked);
        if (checked) {
          ui.showDetails->setIcon(QIcon(
              ":media/images/qbutton_icons/vdownarrow" + img_add + ".png"));
          ui.showDetails->setIconSize(QSize(24, 24));
        } else {
          ui.showDetails->setIcon(QIcon(
              ":media/images/qbutton_icons/vrightarrow" + img_add + ".png"));
          ui.showDetails->setIconSize(QSize(24, 24));
        }
      });

  /*
    QObject::connect(
        ui.showOutput, &QToolButton::toggled, this, [=](bool checked) {
          ui.output->setVisible(checked);
          if (checked) {
            ui.showOutput->setIcon(QIcon(
                ":media/images/qbutton_icons/vdownarrow" + img_add + ".png"));
            ui.showOutput->setIconSize(QSize(24, 24));
          } else {
            ui.showOutput->setIcon(QIcon(
                ":media/images/qbutton_icons/vrightarrow" + img_add + ".png"));
            ui.showOutput->setIconSize(QSize(24, 24));
          }
        });
  */

  /*
    ui.cancel->setIcon(
        QIcon(":media/images/qbutton_icons/cancel" + img_add + ".png"));
    ui.cancel->setIconSize(QSize(24, 24));

    QObject::connect(ui.cancel, &QToolButton::clicked, this, [=]() {
      if (isRunning) {
        int button = QMessageBox::question(
            this, "Stop", QString("Do you want to stop %1 stream?").arg(remote),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (button == QMessageBox::Yes) {
          cancel();
        }
      } else {
        emit closed();
      }
    });
  */

  ui.showDetails->setStyleSheet(
      "QToolButton { border: 0; color: black; font-weight: bold;}");
  ui.showDetails->setText("  Paused");
}

ScheduleWidget::~ScheduleWidget() {}

/*
void ScheduleWidget::cancel() {
  if (!isRunning) {
    return;
  }
}
*/


void ScheduleWidget::applySettingsToScreen() {

//  QString mTaskId;
//  QString mTaskName; //b64
  ui.taskName->setText(mTaskName);

//  QString mSchedulerName; //b64
  ui.schedulerName->setText(mSchedulerName);
  ui.schedulerName->setCursorPosition(0);
  ui.info->setText(mSchedulerName);

//  QString mSchedulerId = QUuid::createUuid().toString();

//  QString mLastRun; //b64
  ui.lastRun->setText(mLastRun);

//  QString mRequestId;
//  QString mLastRunFinished; //b64
  ui.lastRunFinished->setText(mLastRunFinished);
//  QString mLastRunStatus; //b64
  ui.lastRunStatus->setText(mLastRunStatus);

//  bool mDailyState = true;
//  bool mDailyMon = true;
//  bool mDailyTue = true;
//  bool mDailyWed = true;
//  bool mDailyThu = true;
//  bool mDailyFri = true;
//  bool mDailySat = true;
//  bool mDailySun = true;
  ui.dailyState->setChecked(mDailyState);
  ui.cb_mon->setChecked(mDailyMon);
  ui.cb_tue->setChecked(mDailyTue);
  ui.cb_wed->setChecked(mDailyThu);
  ui.cb_thu->setChecked(mDailyThu);
  ui.cb_fri->setChecked(mDailyFri);
  ui.cb_sat->setChecked(mDailySat);
  ui.cb_sun->setChecked(mDailySun);

//  bool mCronState = false;
  ui.cronState->setChecked(mCronState);

//  QString mCron = "30 6,18 */2 * MON-FRI";
  ui.cron->setText(mCron);

//  QString executionMode = "1"; //1,2,3
  ui.cb_executionMode->setCurrentIndex(executionMode.toInt());

}


