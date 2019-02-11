#ifndef QTAUTOUPDATER_PROGRESSDIALOG_P_H
#define QTAUTOUPDATER_PROGRESSDIALOG_P_H

#include "qtautoupdatergui_global.h"

#include <QtCore/QScopedPointer>

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>

#include <functional>

#include <qtaskbarcontrol.h>

namespace Ui {
class ProgressDialog;
}

namespace QtAutoUpdater
{

class Q_AUTOUPDATERGUI_EXPORT ProgressDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ProgressDialog(QWidget *parent = nullptr);
	~ProgressDialog() override;

	template <class Class>
	void open(Class *object, void(Class::* member)(int,bool)) {
		connect(this, &ProgressDialog::canceled, object, [=](){
			(object->*member)(3000, true);
		});
		show();
	}

	void setCanceled();

public Q_SLOTS:
	void accept() override {}
	void reject() override {}

	void hide(QMessageBox::Icon hideType);

Q_SIGNALS:
	void canceled();

protected:
	void closeEvent(QCloseEvent *event) override;

private:
	QScopedPointer<Ui::ProgressDialog> ui;
	QTaskbarControl *taskbar;
};

}

#endif // QTAUTOUPDATER_PROGRESSDIALOG_P_H
