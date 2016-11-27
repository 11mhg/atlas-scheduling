#include "atlaswelcome.h"
#include "ui_atlaswelcome.h"
#include <QScrollBar>
#include <sstream>

AtlasWelcome::AtlasWelcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AtlasWelcome)
{
    ui->setupUi(this);
    ui->NewCatColourSelect->addItem("Red");
    ui->NewCatColourSelect->addItem("Green");
    ui->NewCatColourSelect->addItem("Purple");

   /*
    // Skin Combo Box
    ui->skinColourSelect->addItem("Black");
    ui->skinColourSelect->addItem("White");
    ui->skinColourSelect->addItem("Tan");

    // Eye Combo Box
    ui->eyeColourSelect->addItem("Side-eye");
    ui->eyeColourSelect->addItem("Classic");

    // Hair Combo Box
    ui->hairColourSelect->addItem("Brunette");
    ui->hairColourSelect->addItem("Blonde");
    ui->hairColourSelect->addItem("Rouge");

    // Shirt Combo Box
    ui->shirtsSelect->addItem("Pink");
    ui->shirtsSelect->addItem("Blue Suit");
    ui->shirtsSelect->addItem("Star Trek");

    // Bottoms Combo Box
    ui->bottomsSelect->addItem("Black Pants");
    ui->bottomsSelect->addItem("Jeans");
    ui->bottomsSelect->addItem("Red Shorts");
*/
    // Settings Combo Boxes ----------------------------
//    ui->changeEyeSelect->addItem("Side-Eye");
//    ui->changeEyeSelect->addItem("Classic");

//    ui->changeSkinSelect->addItem("Black");
//    ui->changeSkinSelect->addItem("White");
//    ui->changeSkinSelect->addItem("Tan");

//    ui->changeHColourSelect->addItem("Brunette");
//    ui->changeHColourSelect->addItem("Blonde");
//    ui->changeHColourSelect->addItem("Rouge");


}


AtlasWelcome::~AtlasWelcome()
{
    delete ui;
}

void AtlasWelcome::on_SignIn_clicked()
{
    ui->stacked->setCurrentIndex(1);
}

void AtlasWelcome::on_loginCheckButton_clicked()
{
    //If statements to check for viable login information.
    QString tempuser = ui->userIn->text();
    QString temppass = ui->pswdIn->text();
    std::string user = tempuser.toUtf8().constData();
    std::string pass = temppass.toUtf8().constData();
    if (user == ""){
        QMessageBox messageBox;
        messageBox.critical(0,"Acess Denied","Your user name cannot be blank");
        messageBox.setFixedSize(500,200);
    }else if (SuccessfulLogin(user,pass)){
        ui->stacked->setCurrentIndex(4);
        ui->usernameDisplay->setText(tempuser);
        ui->UsernameLabel->setText(tempuser);
        //load profile
        User = Profile(user,pass);
        User.LoadInfo();
        User.LoadTasks();
        vector<Task*> weekTasks;
        for (int i = 0 ; i < User.wtasks.size();i++){
            weekTasks.push_back(&User.wtasks.at(i));
        }
        ui->calendar->loadTasks(weekTasks);

    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Access Denied","Your username or password is wrong.");
        messageBox.setFixedSize(500,200);
    }
    ui->catList->setProfile(&User);
}


void AtlasWelcome::on_nextProfile_clicked()
{
    //continue creating the profile.
    //Creates New Profile
    QString tempNewUser = ui->userProfileIn->text();
    QString tempPass = ui->PswdProfileIn->text();
    std::string NewUserString = tempNewUser.toUtf8().constData();
    std::string NewPassString = tempPass.toUtf8().constData();
    if (NewUserString == ""){
        QMessageBox messageBox;
        messageBox.critical(0,"Wrong User Name","Your username cannot be blank");
        messageBox.setFixedSize(500,200);
    }else if (UserNameExists(NewUserString)){
        QMessageBox messageBox;
        messageBox.critical(0,"Access Denied","Your username has already been used");
        messageBox.setFixedSize(500,200);
    }else{
        User = Profile(NewUserString,NewPassString);
        User.name = ui->nameProfileIn->text().toUtf8().constData();
        if (ui->femaleSelect->isEnabled()){
            User.gender = "female";
        }else if(ui->maleSelect->isEnabled()){
            User.gender = "male";
        }else{
            User.gender = "other";
        }
        User.name = ui->DoBSelect->dateTime().toString().toUtf8().constData();
        User.SaveUserInfo();
        ui->stacked->setCurrentIndex(3);
        ui->usernameDisplay->setText(tempNewUser);
    }
}

void AtlasWelcome::on_finishCharacter_clicked()
{
    // finalize creation of the character.
    ui->stacked->setCurrentIndex(4);


}

void AtlasWelcome::on_LogoutButton_clicked()
{
    //logout, clear memory and return to welcome page.

    ui->stacked->setCurrentIndex(0);
}

void AtlasWelcome::on_SettingsButton_clicked()
{
    //open the settings page

    ui->stacked->setCurrentIndex(9);
}

void AtlasWelcome::on_addTaskButton_clicked()
{
    ui->newTaskNameIn->setText("New Task");
    ui->newCatNameIn->setText("");
    ui->newTaskStartSelect->setDateTime(QDateTime::currentDateTime());
    ui->newTaskEndSelect->setDateTime((QDateTime::currentDateTime()).addSecs(60*60*2));
    //open up add task button

    ui->stacked->setCurrentIndex(7);
}

void AtlasWelcome::on_removeTaskButton_clicked()
{
    //open up the remove task view

    ui->stacked->setCurrentIndex(8);
}

void AtlasWelcome::on_settingsButton_clicked()
{
    //open up the settings page

    ui->stacked->setCurrentIndex(9);
}

void AtlasWelcome::on_logoutButton_clicked()
{
    //logout, clear memory and return to welcome page.

    ui->stacked->setCurrentIndex(0);
}

void AtlasWelcome::on_saveCatButton_clicked()
{

    // this case will have to create and save a new category and task.
    if (ui->newCatNameIn->text().toUtf8().constData() == ""){
        QDateTime enddate = ui->newTaskEndSelect->dateTime();
        enddate.addDays(7);
        std::string endd = enddate.toString().toUtf8().constData();
        Task newTask(ui->newTaskNameIn->text().toStdString(), ui->newTaskStartSelect->dateTime(), ui->newTaskEndSelect->dateTime(),enddate,(User.categories.at(2))->getName());
        User.addTask(newTask);
    }else{
        int col;
        if (ui->NewCatColourSelect->currentText().toUtf8().constData() == "Red")
        {
            col = 16711680;
        }else if(ui->NewCatColourSelect->currentText().toUtf8().constData() == "Green")
        {
            col = 65280;
        }else{
            col = 13408767;
        }
        Category *newCat = new Category(string(ui->newCatNameIn->text().toUtf8().constData()),col,1);
        QDateTime enddate = ui->newTaskEndSelect->dateTime();
        enddate.addDays(7);
        std::string endd = enddate.toString().toUtf8().constData();
        User.categories.push_back(newCat);
        Task newTask(ui->newTaskNameIn->text().toStdString(), ui->newTaskStartSelect->dateTime(), ui->newTaskEndSelect->dateTime(), enddate,newCat->getName());
        User.addTask(newTask);
    }
    User.UpdateSave();
    //User.LoadInfo();
    User.LoadTasks();
    ui->stacked->setCurrentIndex(4);
    vector<Task*> weekTasks;
    for (int i = 0 ; i < User.wtasks.size();i++){
        weekTasks.push_back(&User.wtasks.at(i));
    }
    ui->calendar->loadTasks(weekTasks);

}

void AtlasWelcome::on_cancelAddTask_clicked()
{
    //cancel add task
    ui->stacked->setCurrentIndex(4);
}

void AtlasWelcome::on_deleteTaskButton_clicked()
{
    // delete a task

    ui->stacked->setCurrentIndex(4);

}

void AtlasWelcome::on_cancelDeleteButton_clicked()
{
    //do not delete a task, cancel the request.

    ui->stacked->setCurrentIndex(4);

}

void AtlasWelcome::on_cancelSettingsButton_clicked()
{
    //cancel apply settings

    ui->stacked->setCurrentIndex(4);

}

void AtlasWelcome::on_applySettingsButton_clicked()
{
    // apply settings

    ui->stacked->setCurrentIndex(4);

}

void AtlasWelcome::on_myProfileButton_clicked()
{

    ui->stacked->setCurrentIndex(5);
}

void AtlasWelcome::on_registrationButton_clicked()
{
    ui->stacked->setCurrentIndex(2);
}

void AtlasWelcome::on_settingsButton_2_clicked()
{

    ui->stacked->setCurrentIndex(9);
}

void AtlasWelcome::on_logoutButton_2_clicked()
{

    ui->stacked->setCurrentIndex(0);
}

void AtlasWelcome::on_registrationButton_2_clicked()
{

    ui->stacked->setCurrentIndex(2);
}

void AtlasWelcome::on_backProfileButton_clicked()
{
    ui->stat1Progress->valueChanged(50);
}


void AtlasWelcome::on_nameProfileIn_textChanged(const QString &arg1)
{
    ui->ProfileProgress->setValue(14);
}

void AtlasWelcome::on_maleSelect_clicked(bool checked)
{
    ui->ProfileProgress->setValue(28);
}

void AtlasWelcome::on_femaleSelect_clicked()
{
    ui->ProfileProgress->setValue(28);
}

void AtlasWelcome::on_otherSelect_clicked()
{
    ui->ProfileProgress->setValue(28);
}

void AtlasWelcome::on_DoBSelect_editingFinished()
{
    ui->ProfileProgress->setValue(42);
}

void AtlasWelcome::on_FavSubjectProfileIn_textChanged(const QString &arg1)
{
    ui->ProfileProgress->setValue(56);
}

void AtlasWelcome::on_userProfileIn_textChanged(const QString &arg1)
{
    ui->ProfileProgress->setValue(70);
}

void AtlasWelcome::on_emailProfileIn_textChanged(const QString &arg1)
{
    ui->ProfileProgress->setValue(84);
}

void AtlasWelcome::on_PswdProfileIn_textChanged(const QString &arg1)
{
    ui->ProfileProgress->setValue(100);
}


void AtlasWelcome::on_characterSelect1_clicked()
{
    ui->avatarPreviewStack->setCurrentIndex(0);
}

void AtlasWelcome::on_characterSelect2_clicked()
{
    ui->avatarPreviewStack->setCurrentIndex(1);
}

void AtlasWelcome::on_characterSelect3_clicked()
{
    ui->avatarPreviewStack->setCurrentIndex(2);
}

void AtlasWelcome::on_characterSelect4_clicked()
{
    ui->avatarPreviewStack->setCurrentIndex(3);
}

void AtlasWelcome::on_characterSelect5_clicked()
{
    ui->avatarPreviewStack->setCurrentIndex(4);
}

void AtlasWelcome::on_characterSelect1_2_clicked()
{
    ui->avatarPreviewStack_3->setCurrentIndex(0);
}

void AtlasWelcome::on_characterSelect2_2_clicked()
{
    ui->avatarPreviewStack_3->setCurrentIndex(1);
}

void AtlasWelcome::on_characterSelect3_2_clicked()
{
    ui->avatarPreviewStack_3->setCurrentIndex(2);
}

void AtlasWelcome::on_characterSelect4_2_clicked()
{
    ui->avatarPreviewStack_3->setCurrentIndex(3);
}

void AtlasWelcome::on_characterSelect5_2_clicked()
{
    ui->avatarPreviewStack_3->setCurrentIndex(4);
}
