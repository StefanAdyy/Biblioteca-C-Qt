#include "PasswordChange.h"
#include "User.h"
#include "QtMessageBox.h"

PasswordChange::PasswordChange(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

PasswordChange::~PasswordChange()
{

}

void PasswordChange::on_passwordChangeBtn_clicked() 
{
	QString confirmPasswordInput = ui.confirmPasswordInput->text();
	QString newPasswordInput = ui.newPasswordInput->text();
	QString oldPasswordInput = ui.oldPasswordInput->text();

	if (!confirmPasswordInput.isEmpty() && !newPasswordInput.isEmpty() && !oldPasswordInput.isEmpty())
	{
		if (oldPasswordInput!= QString::fromStdString(user.GetPassword()))
		{
			QtMessageBox* errorMessage = new QtMessageBox;
			errorMessage->SetMessage("Old password is wrong!");
			errorMessage->show();
		}
		else
		{
			if (newPasswordInput == confirmPasswordInput)
			{
				if (user.PasswordRequirements(newPasswordInput.toStdString()))
				{
					user.SetKeyword(newPasswordInput.toStdString());
					user.SetOption(changePassword);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					close();
					QtMessageBox* errorMessage = new QtMessageBox;
					errorMessage->SetMessage("Password successfully changed!");
					errorMessage->show();
				}
			}
			else
			{
				QtMessageBox* errorMessage = new QtMessageBox;
				errorMessage->SetMessage("New password and confirm passwords don't match!");
				errorMessage->show();
			}
		}
	}
	else
	{
		QtMessageBox* errorMessage = new QtMessageBox;
		errorMessage->SetMessage("You must fill up the blank fields!");
		errorMessage->show();
	}
}
