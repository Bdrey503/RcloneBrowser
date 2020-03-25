#include "scheduler_widget.h"
#include "utils.h"

SchedulerWidget::SchedulerWidget(const QString &taskId, const QString &taskName,
                                 const QStringList &args, QWidget *parent)
    : QWidget(parent) {

  mTaskId = taskId;
  mTaskName = taskName;

  ui.setupUi(this);
  auto settings = GetSettings();

  QString newInfo = "Scheduled task: " + taskName;

  if (newInfo.length() > 140) {
    mSchedulerName = newInfo.left(57) + "..." + newInfo.right(80);
  } else {
    mSchedulerName = newInfo;
  }

  if (args.at(0) == "NewScheduler") {
    // new scheduler - apply defaults
    applySettingsToScreen();

    ui.info->setEnabled(false);
    ui.nextRun->setEnabled(false);
  } else {

    applyArgsToScheduler(args);
    applySettingsToScreen();
  }

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

  QObject::connect(ui.cancel, &QToolButton::clicked, this, [=]() {
    int button = QMessageBox::question(
        this, "Stop",
        QString("Do you want to delete\n\n %1 \n\nscheduler?")
            .arg(mSchedulerName),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (button == QMessageBox::Yes) {
      emit closed();
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

SchedulerWidget::~SchedulerWidget() {}

/*
void SchedulerWidget::cancel() {
  if (!isRunning) {
    return;
  }
}
*/

void SchedulerWidget::applySettingsToScreen() {

  // mSchedulerStatus

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
  ui.cb_executionMode->setCurrentIndex(mExecutionMode.toInt());
}

QStringList SchedulerWidget::getSchedulerParameters() {

  QStringList schedulerArgs;

  schedulerArgs << "mSchedulerId" << mSchedulerId;
  schedulerArgs << "mSchedulerName" << mSchedulerName.toUtf8().toBase64();
  schedulerArgs << "mTaskId" << mTaskId;
  schedulerArgs << "mTaskName" << mTaskName.toUtf8().toBase64();
  schedulerArgs << "mLastRun" << mLastRun.toUtf8().toBase64();
  schedulerArgs << "mRequestId" << mRequestId;
  schedulerArgs << "mLastRunFinished" << mLastRunFinished.toUtf8().toBase64();
  schedulerArgs << "mLastRunStatus" << mLastRunStatus.toUtf8().toBase64();

  schedulerArgs << "mDailyState" << QVariant(mDailyState).toString();
  schedulerArgs << "mDailyMon" << QVariant(mDailyMon).toString();
  schedulerArgs << "mDailyTue" << QVariant(mDailyTue).toString();
  schedulerArgs << "mDailyWed" << QVariant(mDailyWed).toString();
  schedulerArgs << "mDailyThu" << QVariant(mDailyThu).toString();
  schedulerArgs << "mDailyFri" << QVariant(mDailyFri).toString();
  schedulerArgs << "mDailySat" << QVariant(mDailySat).toString();
  schedulerArgs << "mDailySun" << QVariant(mDailySun).toString();

  schedulerArgs << "mCronState" << QVariant(mCronState).toString();
  schedulerArgs << "mCron" << mCron.toUtf8().toBase64();
  schedulerArgs << "mExecutionMode" << mExecutionMode;

  schedulerArgs << "mSchedulerStatus" << mSchedulerStatus;

  return schedulerArgs;
}

void SchedulerWidget::applyArgsToScheduler(QStringList args) {

  int argsLength = args.count();

  QString arg;
  QString argValue;

  for (int i = 0; i < argsLength; i = i + 2) {

    arg = args.at(i);
    argValue = args.at(i + 1);

    if (arg == "mSchedulerId") {
      mSchedulerId = argValue;
    }
    if (arg == "mSchedulerName") {
      mSchedulerName = (QString)QByteArray::fromBase64(argValue.toUtf8());
    }
    if (arg == "mTaskId") {
      mTaskId = argValue;
    }
    if (arg == "mTaskName") {
      mTaskName = (QString)QByteArray::fromBase64(argValue.toUtf8());
    }
    if (arg == "mLastRun") {
      mLastRun = (QString)QByteArray::fromBase64(argValue.toUtf8());
    }
    if (arg == "mRequestId") {
      mRequestId = argValue;
    }
    if (arg == "mLastRunFinished") {
      mLastRunFinished = (QString)QByteArray::fromBase64(argValue.toUtf8());
    }
    if (arg == "mLastRunStatus") {
      mLastRunStatus = (QString)QByteArray::fromBase64(argValue.toUtf8());
    }

    if (arg == "mDailyState") {
      mDailyState = QVariant(argValue).toBool();
    }

    if (arg == "mDailyMon") {
      mDailyMon = QVariant(argValue).toBool();
    }
    if (arg == "mDailyTue") {
      mDailyTue = QVariant(argValue).toBool();
    }
    if (arg == "mDailyWed") {
      mDailyWed = QVariant(argValue).toBool();
    }
    if (arg == "mDailyThu") {
      mDailyThu = QVariant(argValue).toBool();
    }
    if (arg == "mDailyFri") {
      mDailyFri = QVariant(argValue).toBool();
    }
    if (arg == "mDailySat") {
      mDailySat = QVariant(argValue).toBool();
    }
    if (arg == "mDailySun") {
      mDailySun = QVariant(argValue).toBool();
    }

    if (arg == "mCronState") {
      mCronState = QVariant(argValue).toBool();
    }
    if (arg == "mCron") {
      mCron = (QString)QByteArray::fromBase64(argValue.toUtf8());
    }
    if (arg == "mExecutionMode") {
      mExecutionMode = argValue;
    }

    if (arg == "mSchedulerStatus") {
      mSchedulerStatus = argValue;
    }
  }

  return;
}

void SchedulerWidget::updateTaskName(const QString newTaskName) {

  mTaskName = newTaskName;
  ui.taskName->setText(mTaskName);
}

QString SchedulerWidget::getSchedulerTaskId() { return mTaskId; }
