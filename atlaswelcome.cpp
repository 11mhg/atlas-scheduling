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
    ui->NewCatColourSelect->addItem("Blue");
    // Skin Combo Box
    ui->skinColourCombo->addItem("-None-");
    ui->skinColourCombo->addItem("White");
    ui->skinColourCombo->addItem("Black");
    ui->skinColourCombo->addItem("Tan");

    // Hair Combo Box
    ui->hairstyleCombo->addItem("-None-");
    ui->hairstyleCombo->addItem("Black");
    ui->hairstyleCombo->addItem("Blonde");
    ui->hairstyleCombo->addItem("Brunette");
    ui->hairstyleCombo->addItem("Rouge");

    ui->W111->hide();
    ui->W112->hide();
    ui->W121->hide();
    ui->W122->hide();
    ui->W131->hide();
    ui->W132->hide();
    ui->W141->hide();
    ui->W142->hide();

    ui->B211->hide();
    ui->B212->hide();
    ui->B221->hide();
    ui->B222->hide();
    ui->B231->hide();
    ui->B232->hide();
    ui->B241->hide();
    ui->B242->hide();

    ui->T311->hide();
    ui->T312->hide();
    ui->T321->hide();
    ui->T322->hide();
    ui->T331->hide();
    ui->T332->hide();
    ui->T341->hide();
    ui->T342->hide();

    ui->W111_2->hide();
    ui->W112_2->hide();
    ui->W121_2->hide();
    ui->W122_2->hide();
    ui->W131_2->hide();
    ui->W132_2->hide();
    ui->W141_2->hide();
    ui->W142_2->hide();

    ui->B211_2->hide();
    ui->B212_2->hide();
    ui->B221_2->hide();
    ui->B222_2->hide();
    ui->B231_2->hide();
    ui->B232_2->hide();
    ui->B241_2->hide();
    ui->B242_2->hide();

    ui->T311_2->hide();
    ui->T312_2->hide();
    ui->T321_2->hide();
    ui->T322_2->hide();
    ui->T331_2->hide();
    ui->T332_2->hide();
    ui->T341_2->hide();
    ui->T342_2->hide();

    // Shirt Combo Box
    ui->outfitCombo->addItem("-None-");
    ui->outfitCombo->addItem("Pink");
    //ui->outfitCombo->addItem("Blue Suit");
    ui->outfitCombo->addItem("Star Trek");

    QPixmap pixToTreasure(":/assets/assets/treasure.png");
            QIcon ButtonIcon(pixToTreasure);
            ui->toTreasureChest->setIcon(ButtonIcon);
            ui->toTreasureChest->setIconSize(pixToTreasure.rect().size());
            ui->toTreasureChest->setFixedSize(pixToTreasure.rect().size());
            ui->toTreasureChest->setIconSize(QSize(100,100));

            //draws the back arrow onto corresponding pushbuttons.
            QPixmap pixBackArrow(":/assets/assets/backArrow.png");
            QIcon ButtonIcon2(pixBackArrow);
            ui->backCharacterButton->setIcon(ButtonIcon2);
            ui->backCharacterButton->setIconSize(pixBackArrow.rect().size());
            ui->backCharacterButton->setFixedSize(pixBackArrow.rect().size());
            ui->backCharacterButton->setIconSize(QSize(100,100));
            ui->backProfileButton->setIcon(ButtonIcon2);
            ui->backProfileButton->setIconSize(pixBackArrow.rect().size());
            ui->backProfileButton->setFixedSize(pixBackArrow.rect().size());
            ui->backProfileButton->setIconSize(QSize(100,100));

            //draws a lock icon onto "locked item" pushbuttons.
            QPixmap pixLock(":/assets/assets/lock.png");
            QIcon ButtonIcon3(pixLock);
            ui->locked1->setIcon(ButtonIcon3);
            ui->locked1->setIconSize(pixLock.rect().size());
            ui->locked1->setFixedSize(pixLock.rect().size());
            ui->locked1->setIconSize(QSize(100,100));
            ui->locked2->setIcon(ButtonIcon3);
            ui->locked2->setIconSize(pixLock.rect().size());
            ui->locked2->setFixedSize(pixLock.rect().size());
            ui->locked2->setIconSize(QSize(100,100));
            ui->locked3->setIcon(ButtonIcon3);
            ui->locked3->setIconSize(pixLock.rect().size());
            ui->locked3->setFixedSize(pixLock.rect().size());
            ui->locked3->setIconSize(QSize(100,100));
            ui->locked4->setIcon(ButtonIcon3);
            ui->locked4->setIconSize(pixLock.rect().size());
            ui->locked4->setFixedSize(pixLock.rect().size());
            ui->locked4->setIconSize(QSize(100,100));

            //draws the equippable items.
            QPixmap pixCalc(":/assets/assets/calculator1.png");
            QIcon ButtonIcon4(pixCalc);
            ui->calculator->setIcon(ButtonIcon4);
            ui->calculator->setIconSize(pixCalc.rect().size());
            ui->calculator->setFixedSize(pixCalc.rect().size());
            ui->calculator->setIconSize(QSize(100,100));
            ui->calculator->setIcon(ButtonIcon4);
            QPixmap pixMath(":/assets/assets/math.png");
            QIcon ButtonIcon5(pixMath);
            ui->owl->setIcon(ButtonIcon5);
            ui->owl->setIconSize(pixMath.rect().size());
            ui->owl->setFixedSize(pixMath.rect().size());
            ui->owl->setIconSize(QSize(100,100));
            ui->owl->setIcon(ButtonIcon5);
            QPixmap pixStar(":/assets/assets/star.png");
            QIcon ButtonIcon6(pixStar);
            ui->star->setIcon(ButtonIcon6);
            ui->star->setIconSize(pixStar.rect().size());
            ui->star->setFixedSize(pixStar.rect().size());
            ui->star->setIconSize(QSize(100,100));
            ui->star->setIcon(ButtonIcon6);
            QPixmap pixTrophy(":/assets/assets/trophy.png");
            QIcon ButtonIcon7(pixTrophy);
            ui->trophy->setIcon(ButtonIcon7);
            ui->trophy->setIconSize(pixTrophy.rect().size());
            ui->trophy->setFixedSize(pixTrophy.rect().size());
            ui->trophy->setIconSize(QSize(100,100));
            ui->trophy->setIcon(ButtonIcon7);
            QPixmap pixPencil(":/assets/assets/pencil.png");
            QIcon ButtonIcon8(pixPencil);
            ui->pencil->setIcon(ButtonIcon8);
            ui->pencil->setIconSize(pixPencil.rect().size());
            ui->pencil->setFixedSize(pixPencil.rect().size());
            ui->pencil->setIconSize(QSize(100,100));
            ui->pencil->setIcon(ButtonIcon8);
            QPixmap pixNotebook(":/assets/assets/notebook.png");
            QIcon ButtonIcon9(pixNotebook);
            ui->notebook->setIcon(ButtonIcon9);
            ui->notebook->setIconSize(pixNotebook.rect().size());
            ui->notebook->setFixedSize(pixNotebook.rect().size());
            ui->notebook->setIconSize(QSize(100,100));
            ui->notebook->setIcon(ButtonIcon9);

            ui->calculator->setCheckable(true);
            ui->owl->setCheckable(true);
            ui->star->setCheckable(true);
            ui->trophy->setCheckable(true);
            ui->pencil->setCheckable(true);
            ui->notebook->setCheckable(true);
            //hides the pencil and notebook - these will be unlocked.
            ui->pencil->setCheckable(true);
            ui->notebook->setCheckable(true);
            ui->notebook->hide();
            ui->pencil->hide();

            if(User.lockedItem == true){
                 ui->notebook->show();
                 int i = 0;
                 if (i == 1)
                     ui->pencil->show();
                 i =1;
                 User.lockedItem = false;
            }

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
    std::string user = tempuser.toStdString();
    std::string pass = temppass.toStdString();
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
        ui->calendar->loadTasks(User.wtasks);

        int comb = atoi(User.combo.c_str());

        switch(comb){
        case(111):
            ui->W111->show();
            ui->W111_2->show();
            break;
        case(121):
                    ui->W121->show();
                    ui->W121_2->show();

            break;
        case(131):
                    ui->W131->show();
                    ui->W131_2->show();
            break;
        case(112):
                    ui->W112->show();
                    ui->W112_2->show();
            break;
        case(122):
                    ui->W122->show();
                    ui->W122_2->show();
            break;
        case(132):
                    ui->W132->show();
                    ui->W132_2->show();
            break;
        case(141):
                    ui->W141->show();
                    ui->W141_2->show();
            break;
        case(211):
                    ui->B211->show();
                    ui->B211_2->show();
            break;
        case(221):
                    ui->B221->show();
                    ui->B221_2->show();
            break;
        case(231):
                    ui->B231->show();
                    ui->B231_2->show();
            break;
        case(241):
                    ui->B241->show();
                    ui->B241_2->show();
            break;
        case(212):
                    ui->B212->show();
                    ui->B212_2->show();
            break;
        case(222):
                    ui->B222->show();
                    ui->B222_2->show();
            break;
        case(232):
                    ui->B232->show();
                    ui->B232_2->show();
            break;
        case(242):
                    ui->B242->show();
                    ui->B242_2->show();
            break;
        case(311):
                    ui->T311->show();
                    ui->T311_2->show();
            break;
        case(321):
                    ui->T321->show();
                    ui->T321_2->show();
            break;
        case(331):
                    ui->T331->show();
                    ui->T331_2->show();
            break;
        case(341):
                    ui->T341->show();
                    ui->T341_2->show();
            break;
        case(312):
                    ui->T312->show();
                    ui->T312_2->show();
            break;
        case(322):
                    ui->T322->show();
                    ui->T322_2->show();
            break;
        case(332):
                    ui->T332->show();
                    ui->T332_2->show();
            break;
        case(342):
                    ui->T342->show();
                    ui->T342_2->show();
            break;

        }

    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Access Denied","Username or Password is invalid.");
        messageBox.setFixedSize(500,200);
    }
    ui->catList->setProfile(&User);
    ui->weekHeader->setProfile(&User, ui->calendar);
}


void AtlasWelcome::on_nextProfile_clicked()
{
    //continue creating the profile.
    //Creates New Profile
    QString tempNewUser = ui->userProfileIn->text();
    QString tempPass = ui->PswdProfileIn->text();
    std::string NewUserString = tempNewUser.toStdString();
    std::string NewPassString = tempPass.toStdString();
    if (NewUserString == ""){
        QMessageBox messageBox;
        messageBox.critical(0,"Wrong User Name","Your username cannot be blank");
        messageBox.setFixedSize(500,200);
    }else if (UserNameExists(NewUserString)){
        QMessageBox messageBox;
        messageBox.critical(0,"Access Denied","Username or Password is invalid");
        messageBox.setFixedSize(500,200);
    }else{
        User = Profile(NewUserString,NewPassString);
        User.name = ui->nameProfileIn->text().toStdString();

        User.name = ui->DoBSelect->dateTime().toString().toStdString();
        ui->userProfileIn->clear();
        ui->PswdProfileIn->clear();
        User.Stats.timeManagement = 0;
        User.Stats.productivity = 0 ;
        User.SaveUserInfo();
        User.LoadInfo();
        User.LoadTasks();
        std::string def = "Default";
        Category *newCat = new Category(def,13408767,1);
        User.categories.push_back(newCat);
        ui->calendar->loadTasks(User.wtasks);
        ui->stacked->setCurrentIndex(3);
        ui->usernameDisplay->setText(tempNewUser);
        ui->catList->setProfile(&User);
        ui->weekHeader->setProfile(&User, ui->calendar);
    }
}

void AtlasWelcome::on_finishCharacter_clicked()
{
    // finalize creation of the character.
    std::string skin = std::to_string(ui->skinColourCombo->currentIndex());
    std::string hair = std::to_string(ui->hairstyleCombo->currentIndex());
    std::string shirt = std::to_string(ui->outfitCombo->currentIndex());

    std::string combo = skin+hair+shirt;
    User.combo = combo;
    int comb = atoi(User.combo.c_str());

    switch(comb){
    case(111):
        ui->W111->show();
        ui->W111_2->show();
        break;
    case(121):
                ui->W121->show();
                ui->W121_2->show();

        break;
    case(131):
                ui->W131->show();
                ui->W131_2->show();
        break;
    case(112):
                ui->W112->show();
                ui->W112_2->show();
        break;
    case(122):
                ui->W122->show();
                ui->W122_2->show();
        break;
    case(132):
                ui->W132->show();
                ui->W132_2->show();
        break;
    case(141):
                ui->W141->show();
                ui->W141_2->show();
        break;
    case(211):
                ui->B211->show();
                ui->B211_2->show();
        break;
    case(221):
                ui->B221->show();
                ui->B221_2->show();
        break;
    case(231):
                ui->B231->show();
                ui->B231_2->show();
        break;
    case(241):
                ui->B241->show();
                ui->B241_2->show();
        break;
    case(212):
                ui->B212->show();
                ui->B212_2->show();
        break;
    case(222):
                ui->B222->show();
                ui->B222_2->show();
        break;
    case(232):
                ui->B232->show();
                ui->B232_2->show();
        break;
    case(242):
                ui->B242->show();
                ui->B242_2->show();
        break;
    case(311):
                ui->T311->show();
                ui->T311_2->show();
        break;
    case(321):
                ui->T321->show();
                ui->T321_2->show();
        break;
    case(331):
                ui->T331->show();
                ui->T331_2->show();
        break;
    case(341):
                ui->T341->show();
                ui->T341_2->show();
        break;
    case(312):
                ui->T312->show();
                ui->T312_2->show();
        break;
    case(322):
                ui->T322->show();
                ui->T322_2->show();
        break;
    case(332):
                ui->T332->show();
                ui->T332_2->show();
        break;
    case(342):
                ui->T342->show();
                ui->T342_2->show();
        break;

    }
    ui->stacked->setCurrentIndex(4);

}

void AtlasWelcome::on_LogoutButton_clicked()
{
    //logout, clear memory and return to welcome page.
    User.SaveUserInfo();
    ui->stacked->setCurrentIndex(0);
    vector<Task*> n;
    ui->calendar->loadTasks(n);
    for (uint i = 0 ; i < User.categories.size(); i++)
    {
        delete(User.categories.at(i));
    }
    User.categories.clear();
    ui->userIn->clear();
    ui->pswdIn->clear();
    User = Profile();
    ui->W111->hide();
    ui->W112->hide();
    ui->W121->hide();
    ui->W122->hide();
    ui->W131->hide();
    ui->W132->hide();
    ui->W141->hide();
    ui->W142->hide();

    ui->B211->hide();
    ui->B212->hide();
    ui->B221->hide();
    ui->B222->hide();
    ui->B231->hide();
    ui->B232->hide();
    ui->B241->hide();
    ui->B242->hide();

    ui->T311->hide();
    ui->T312->hide();
    ui->T321->hide();
    ui->T322->hide();
    ui->T331->hide();
    ui->T332->hide();
    ui->T341->hide();
    ui->T342->hide();

    ui->W111_2->hide();
    ui->W112_2->hide();
    ui->W121_2->hide();
    ui->W122_2->hide();
    ui->W131_2->hide();
    ui->W132_2->hide();
    ui->W141_2->hide();
    ui->W142_2->hide();

    ui->B211_2->hide();
    ui->B212_2->hide();
    ui->B221_2->hide();
    ui->B222_2->hide();
    ui->B231_2->hide();
    ui->B232_2->hide();
    ui->B241_2->hide();
    ui->B242_2->hide();

    ui->T311_2->hide();
    ui->T312_2->hide();
    ui->T321_2->hide();
    ui->T322_2->hide();
    ui->T331_2->hide();
    ui->T332_2->hide();
    ui->T341_2->hide();
    ui->T342_2->hide();
}

void AtlasWelcome::on_SettingsButton_clicked()
{
    //open the settings page
}

void AtlasWelcome::on_addTaskButton_clicked()
{
    ui->newTaskNameIn->setText("New Task");
    bool defExists = false;
    for (uint i = 0 ; i < User.categories.size(); i++)
    {
        if ((User.categories.at(i))->getName() == "Default"){
            defExists = true;
        }
    }
    if (!defExists)
    {
        ui->categorySelect->addItem("Default");
        std::string def = "Default";
        Category *newCat = new Category(def,0,1);
        User.categories.push_back(newCat);
        ui->categorySelect->addItem("Default");
    }

    ui->newTaskStartSelect->setDateTime(QDateTime::currentDateTime());
    ui->newTaskEndSelect->setDateTime((QDateTime::currentDateTime()).addSecs(60*60*2));
    setCategorySelect();
    //open up add task button

    ui->stacked->setCurrentIndex(7);
}

void AtlasWelcome::on_removeTaskButton_clicked()
{
    //open up the remove task view
    ui->RemoveListView->model()->removeRows(0,ui->RemoveListView->model()->rowCount());
    for (uint i = 0 ; i < User.ptasks.size(); i ++)
    {
        ui->RemoveListView->addItem(QString::fromStdString(User.ptasks.at(i).getName()));
    }
    ui->stacked->setCurrentIndex(8);
}

void AtlasWelcome::on_settingsButton_clicked()
{
}

void AtlasWelcome::on_logoutButton_clicked()
{
    //logout, clear memory and return to welcome page.
    User.UpdateSave();
    ui->pswdIn->clear();
    ui->stacked->setCurrentIndex(0);
}

void AtlasWelcome::on_saveCatButton_clicked()
{


    // this case will have to create and save a new category and task.
    if (ui->newCatNameIn->text().toStdString() == ""){
        std::string s = ui->categorySelect->currentText().toStdString();
        cout << s << endl;
        QDateTime enddate = ui->newTaskEndSelect->dateTime();
        enddate.addDays(7);
        std::string endd = enddate.toString().toStdString();
        Task newTask(ui->newTaskNameIn->text().toStdString(), ui->newTaskStartSelect->dateTime(), ui->newTaskEndSelect->dateTime(),enddate,s,&User);
        newTask.setComplete(false);
        User.addTask(newTask);
    }else{
        int col;
        if (ui->NewCatColourSelect->currentText().toStdString() == "Red")
        {
            col = 16711680;
        }else if(ui->NewCatColourSelect->currentText().toStdString() == "Green")
        {
            col = 65280;
        }else{
            col = 0;
        }
        Category *newCat = new Category(string(ui->newCatNameIn->text().toUtf8().constData()),col,1);
        QDateTime enddate = ui->newTaskEndSelect->dateTime();
        enddate.addDays(7);
        std::string endd = enddate.toString().toStdString();
        User.categories.push_back(newCat);
        Task newTask(ui->newTaskNameIn->text().toStdString(), ui->newTaskStartSelect->dateTime(), ui->newTaskEndSelect->dateTime(), enddate,newCat->getName(),&User);
        newTask.setComplete(false);
        User.addTask(newTask);
    }
    User.UpdateSave();
    User.LoadTasks();
    ui->stacked->setCurrentIndex(4);
    ui->calendar->loadTasks(User.wtasks);
    ui->catList->update();
    setCategorySelect();
    ui->pswdIn->clear();
    ui->newCatNameIn->clear();
}

void AtlasWelcome::setCategorySelect(){
    ui->categorySelect->clear();
    for (int i = 0 ; i < User.categories.size(); i++)
    {
        ui->categorySelect->addItem(QString::fromStdString(User.categories.at(i)->getName()));
    }
    cout << User.categories.size() << endl;
}

void AtlasWelcome::on_cancelAddTask_clicked()
{
    //cancel add task
    ui->stacked->setCurrentIndex(4);
}

void AtlasWelcome::on_deleteTaskButton_clicked()
{
    // delete a task
    vector<std::string> toRemoveName;
    vector<Task> willReplace;
    QList<QListWidgetItem *> list = ui->RemoveListView->selectedItems();
    for (uint i = 0 ; i < list.size(); i++){
        toRemoveName.push_back(list.at(i)->text().toStdString());
    }
    for (uint i = 0 ; i < toRemoveName.size() ; i++){
        for (uint j = 0 ; j < User.ptasks.size(); j++)
        {
            if (User.ptasks.at(j).getName() == toRemoveName.at(i))
            {
                continue;
            }else{
                willReplace.push_back(User.ptasks.at(j));
            }
        }
    }
    User.SetTasks(willReplace);
    User.SaveUserInfo();
    User.LoadTasks();
    ui->calendar->loadTasks(User.wtasks);
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
    if(ui->maleGenderSetting->isEnabled()){
        User.gender = "male";
    }else if (ui->femaleGenderSetting->isEnabled()){
        User.gender = "female";
    }else if (ui->otherGenderSetting->isEnabled()){
        User.gender = "other";
    }
    if (ui->changeUserSelect->text().toStdString() != ""){
        User.setUserName(ui->changeUserSelect->text().toStdString());
    }
    User.SaveUserInfo();
    User.LoadInfo();
    User.LoadTasks();
    ui->usernameDisplay->setText(ui->changeUserSelect->text());
    ui->changeUserSelect->clear();
    ui->stacked->setCurrentIndex(4);

}

void AtlasWelcome::on_myProfileButton_clicked()
{
    ui->ProductProgress->setValue(User.Stats.productivity);
    ui->TimeProgress->setValue(User.Stats.timeManagement);
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
    User.~Profile();
    ui->pswdIn->clear();
    ui->stacked->setCurrentIndex(0);
}

void AtlasWelcome::on_registrationButton_2_clicked()
{

    ui->stacked->setCurrentIndex(2);
}

void AtlasWelcome::on_backProfileButton_clicked()
{

    ui->stacked->setCurrentIndex(5);
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

void AtlasWelcome::on_toTreasureChest_clicked()
{
    ui->stacked->setCurrentIndex(6);
}

void AtlasWelcome::on_backCharacterButton_clicked()
{
    ui->stacked->setCurrentIndex(4);
}

void AtlasWelcome::on_calculator_clicked(bool checked)
{
    if (checked == true){
        QPixmap calcEquip(":/assets/assets/calculator1.png");
        ui->handsEquip->setPixmap(calcEquip.scaled(75,75,Qt::KeepAspectRatio));
        ui->handsEquip->setAlignment(Qt::AlignCenter);
        ui->equip1->setPixmap(calcEquip.scaled(60,60,Qt::KeepAspectRatio));
        ui->equip1->setAlignment(Qt::AlignCenter);
        ui->treasureStatus->setText("Calculator was equipped!");
    }
    else{
        ui->handsEquip->clear();
        ui->equip1->clear();
        ui->treasureStatus->setText("");
    }

}

void AtlasWelcome::on_owl_clicked(bool checked)
{
    if (checked == true){
        QPixmap owlEquip(":/assets/assets/math.png");
        ui->shoulderEquip->setPixmap(owlEquip.scaled(20,20,Qt::KeepAspectRatio));
        ui->shoulderEquip->setAlignment(Qt::AlignCenter);
        ui->shoulder->setPixmap(owlEquip.scaled(60,60,Qt::KeepAspectRatio));
        ui->shoulder->setAlignment(Qt::AlignCenter);
        ui->equip2->setPixmap(owlEquip.scaled(50,50,Qt::KeepAspectRatio));
        ui->equip2->setAlignment(Qt::AlignCenter);
        ui->treasureStatus->setText("The Wise Owl of Math was equipped!");
    }
    else{
        ui->shoulderEquip->clear();
        ui->equip2->clear();
        ui->shoulder->clear();
        ui->treasureStatus->setText("");
    }
}

void AtlasWelcome::on_star_clicked(bool checked)
{
    if (checked == true){
        QPixmap starEquip(":/assets/assets/star.png");
        ui->chestEquip->setPixmap(starEquip.scaled(60,60,Qt::KeepAspectRatio));
        ui->chestEquip->setAlignment(Qt::AlignCenter);
        ui->equip3->setPixmap(starEquip.scaled(50,50,Qt::KeepAspectRatio));
        ui->equip3->setAlignment(Qt::AlignCenter);
        ui->treasureStatus->setText("Well, at least you tried!");
    }
    else{
        ui->chestEquip->clear();
        ui->equip3->clear();
        ui->treasureStatus->setText("");
    }
}

void AtlasWelcome::on_trophy_clicked(bool checked)
{
    if (checked == true){
        QPixmap trophyEquip(":/assets/assets/trophy.png");
        ui->handsEquip->setPixmap(trophyEquip.scaled(75,75,Qt::KeepAspectRatio));
        ui->handsEquip->setAlignment(Qt::AlignCenter);
        ui->equip1->setPixmap(trophyEquip.scaled(50,50,Qt::KeepAspectRatio));
        ui->equip1->setAlignment(Qt::AlignCenter);
        ui->treasureStatus->setText("Trophy was equipped!");
    }
    else{
        ui->handsEquip->clear();
        ui->equip1->clear();
        ui->treasureStatus->setText("");
    }
}

void AtlasWelcome::on_locked1_clicked()
{
    ui->treasureStatus->setText("This item is locked - Get your life together.");
}

void AtlasWelcome::on_locked2_clicked()
{
    ui->treasureStatus->setText("This item is locked - Get your life together.");
}

void AtlasWelcome::on_locked3_clicked()
{
    ui->treasureStatus->setText("This item is locked - Get your life together.");
}

void AtlasWelcome::on_locked4_clicked()
{
    ui->treasureStatus->setText("This item is locked - Get your life together.");
}

void AtlasWelcome::on_pencil_clicked(bool checked)
{
    if (checked == true){
        QPixmap pencilEquip(":/assets/assets/pencil.png");
        ui->handsEquip->setPixmap(pencilEquip.scaled(75,75,Qt::KeepAspectRatio));
        ui->handsEquip->setAlignment(Qt::AlignCenter);
        ui->equip1->setPixmap(pencilEquip.scaled(50,50,Qt::KeepAspectRatio));
        ui->equip1->setAlignment(Qt::AlignCenter);
        ui->treasureStatus->setText("Pencil was equipped!");
    }
    else{
        ui->handsEquip->clear();
        ui->equip1->clear();
        ui->treasureStatus->setText("");
    }

}

void AtlasWelcome::on_notebook_clicked(bool checked)
{
    if (checked == true){
        QPixmap notebookEquip(":/assets/assets/notebook.png");
        ui->handsEquip->setPixmap(notebookEquip.scaled(75,75,Qt::KeepAspectRatio));
        ui->handsEquip->setAlignment(Qt::AlignCenter);
        ui->equip1->setPixmap(notebookEquip.scaled(50,50,Qt::KeepAspectRatio));
        ui->equip1->setAlignment(Qt::AlignCenter);
        ui->treasureStatus->setText("Notebook was equipped!");
    }
    else{
        ui->handsEquip->clear();
        ui->equip1->clear();
        ui->treasureStatus->setText("");
    }
}


void AtlasWelcome::on_skinColourCombo_currentIndexChanged(int index)
{
    if(ui->skinColourCombo->currentIndex() == 1){
        ui->WHairStacked->setCurrentIndex(0);
        ui->avatarPreviewStack->setCurrentIndex(0);
        ui->hairstyleCombo->setCurrentIndex(0);
       }
    else if(ui->skinColourCombo->currentIndex() == 2)
    {
        ui->BHairStack->setCurrentIndex(0);
        ui->avatarPreviewStack->setCurrentIndex(1);
        ui->hairstyleCombo->setCurrentIndex(0);
    }
    else if(ui->skinColourCombo->currentIndex() == 3)
    {
        ui->THairStacked->setCurrentIndex(0);
        ui->avatarPreviewStack->setCurrentIndex(2);
        ui->hairstyleCombo->setCurrentIndex(0);
    }
    else{}
}

// Hairstyle Character Creation Selection.
void AtlasWelcome::on_hairstyleCombo_currentIndexChanged(int index)
{
    if(ui->hairstyleCombo->currentIndex() == 1) //Black hairstyle selected.
    {
        if(ui->avatarPreviewStack->currentIndex() == 0) //White avatar w Black hair.
        {
            ui->WHairStacked->setCurrentIndex(1);
            ui->WBStacked->setCurrentIndex(1);
            ui->outfitCombo->setCurrentIndex(0);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1)    // Black avatar w Black Hair.
        {
            ui->BHairStack->setCurrentIndex(1);
            ui->BBStackedShirts->setCurrentIndex(0);
            ui->outfitCombo->setCurrentIndex(0);
        }
        else {                                               // Tanned avatar w Black Hair.
            ui->THairStacked->setCurrentIndex(1);
            ui->TBStackedShirts->setCurrentIndex(0);
            ui->outfitCombo->setCurrentIndex(0);
        }
    }
    else if(ui->hairstyleCombo->currentIndex() == 2) //Blonde hairstyle selected.
    {
        if(ui->avatarPreviewStack->currentIndex() == 0) // White avatar w Blonde hair.
        {
            ui->WHairStacked->setCurrentIndex(2);
            ui->WBlStacked->setCurrentIndex(1);
            ui->outfitCombo->setCurrentIndex(0);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1) //Black avatar w Blonde hair.
        {
            ui->BHairStack->setCurrentIndex(2);
            ui->BBlStackedShirts->setCurrentIndex(0);
            ui->outfitCombo->setCurrentIndex(0);
        }
        else  {                                               // Tanned avatar w Blonde hair.
            ui->THairStacked->setCurrentIndex(2);
            ui->TBlStackedShirts->setCurrentIndex(0);
            ui->outfitCombo->setCurrentIndex(0);
        }
    }

    else if(ui->hairstyleCombo->currentIndex() == 3) //Brunnette hairstyle selected.
    {
        if(ui->avatarPreviewStack->currentIndex() == 0) // White avatar w Brown hair.
        {
            ui->WHairStacked->setCurrentIndex(3);
            ui->WBrStackedShirts->setCurrentIndex(1);
            ui->outfitCombo->setCurrentIndex(0);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1) //Black avatar w Brown hair.
        {
            ui->BHairStack->setCurrentIndex(3);
            ui->BBrStackedShirts->setCurrentIndex(0);
            ui->outfitCombo->setCurrentIndex(0);
        }
        else                                                 // Tanned avatar w Brown hair.
           {
            ui->THairStacked->setCurrentIndex(3);
            ui->TBrStackedShirts->setCurrentIndex(0);
            ui->outfitCombo->setCurrentIndex(0);
        }
    }

    else                                            //Red hairstyle selected.
    {
        if(ui->avatarPreviewStack->currentIndex() == 0) // White avatar w Red hair.
        {
            ui->WHairStacked->setCurrentIndex(4);
            ui->WRStackedShirts->setCurrentIndex(1);
            ui->outfitCombo->setCurrentIndex(0);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1) //Black avatar w Red hair.
        {
            ui->BHairStack->setCurrentIndex(4);
            ui->BRStackedShirts->setCurrentIndex(0);
            ui->outfitCombo->setCurrentIndex(0);
        }
        else                                                 // Tanned avatar w Red hair.
           {
            ui->THairStacked->setCurrentIndex(4);
            ui->TRStackedShirts->setCurrentIndex(0);
            ui->outfitCombo->setCurrentIndex(0);
        }
    }
}


// Outfit Selection
void AtlasWelcome::on_outfitCombo_currentIndexChanged(int index)
{

    // PINK SHIRT
    if(ui->outfitCombo->currentIndex() == 1) //Pink shirt selected.
    {
        // BLACK HAIR OPTIONS - Pink
        if((ui->avatarPreviewStack->currentIndex() == 0) && (ui->hairstyleCombo->currentIndex() == (1))) //White avatar w Black hair.
        {
            ui->WBStacked->setCurrentIndex(2);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (1))    // Black avatar w Black Hair.
        {
            ui->BBStackedShirts->setCurrentIndex(1);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (1))   // Tanned avatar w Black Hair.
        {
            ui->TBStackedShirts->setCurrentIndex(1);
        }

        // BLONDE HAIR OPTIONS - Pink
        else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (2)) // White avatar w Blonde hair.
        {
            ui->WBlStacked->setCurrentIndex(2);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (2)) //Black avatar w Blonde hair.
        {
            ui->BBlStackedShirts->setCurrentIndex(1);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (2)) // Tanned avatar w Blonde hair.
        {
            ui->TBlStackedShirts->setCurrentIndex(1);
        }
        // BROWN HAIR OPTIONS - Pink
        else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (3)) // White avatar w Brown hair.
        {
            ui->WBrStackedShirts->setCurrentIndex(2);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (3)) //Black avatar w Brown hair.
        {
            ui->BBrStackedShirts->setCurrentIndex(1);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (3)) // Tanned avatar w Brown hair.
        {
            ui->TBrStackedShirts->setCurrentIndex(1);
        }
        // RED HAIR OPTIONS - Pink
        else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (4)) // White avatar w Red hair.
        {
            ui->WRStackedShirts->setCurrentIndex(2);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (4)) //Black avatar w Red hair.
        {
            ui->BRStackedShirts->setCurrentIndex(1);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (4)) // Tanned avatar w Red hair.
        {
          ui->TRStackedShirts->setCurrentIndex(1);
        }
        else{}
    }


    // BLUE SHIRT
    else if(ui->outfitCombo->currentIndex() == 2) //Blue shirt selected.
    {
        // BLACK HAIR OPTIONS - Blue
        if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (1)) //White avatar w Black hair.
        {
            ui->WBStacked->setCurrentIndex(4);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (1))    // Black avatar w Black Hair.
        {
            ui->BBStackedShirts->setCurrentIndex(3);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (1))   // Tanned avatar w Black Hair.
            ui->TBStackedShirts->setCurrentIndex(3);

        // BLONDE HAIR OPTIONS - Blue
        else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (2)) // White avatar w Blonde hair.
        {
            ui->WBlStacked->setCurrentIndex(4);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (2)) //Black avatar w Blonde hair.
        {
            ui->BBlStackedShirts->setCurrentIndex(3);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (2)) // Tanned avatar w Blonde hair.
            ui->TBlStackedShirts->setCurrentIndex(3);

        // BROWN HAIR OPTIONS - Blue
        else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (3)) // White avatar w Brown hair.
        {
            ui->WBrStackedShirts->setCurrentIndex(4);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (3)) //Black avatar w Brown hair.
        {
            ui->BBrStackedShirts->setCurrentIndex(3);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (3)) // Tanned avatar w Brown hair.
            ui->TBrStackedShirts->setCurrentIndex(3);

        // RED HAIR OPTIONS - Blue
        else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (4)) // White avatar w Red hair.
        {
            ui->WRStackedShirts->setCurrentIndex(4);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (4)) //Black avatar w Red hair.
        {
            ui->BRStackedShirts->setCurrentIndex(3);
        }
        else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (4)) // Tanned avatar w Red hair.
            ui->TRStackedShirts->setCurrentIndex(3);


        /*// STAR TREK SHIRT
        else if(ui->outfitCombo->currentIndex() == 3) //Star Trek shirt selected.
        {
            // BLACK HAIR OPTIONS - Star Trek
            if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (1)) //White avatar w Black hair.
            {
                ui->WBStacked->setCurrentIndex(4);
            }
            else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (1))    // Black avatar w Black Hair.
            {
                ui->BBStackedShirts->setCurrentIndex(3);
            }
            else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (1))   // Tanned avatar w Black Hair.
                ui->TBStackedShirts->setCurrentIndex(3);

            // BLONDE HAIR OPTIONS - Star Trek
            else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (2)) // White avatar w Blonde hair.
            {
                ui->WBlStacked->setCurrentIndex(4);
            }
            else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (2)) //Black avatar w Blonde hair.
            {
                ui->BBlStackedShirts->setCurrentIndex(3);
            }
            else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (2)) // Tanned avatar w Blonde hair.
                ui->TBlStackedShirts->setCurrentIndex(3);

            // BROWN HAIR OPTIONS - Star Trek
            else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (3)) // White avatar w Brown hair.
            {
                ui->WBrStackedShirts->setCurrentIndex(4);
            }
            else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (3)) //Black avatar w Brown hair.
            {
                ui->BBrStackedShirts->setCurrentIndex(3);
            }
            else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (3)) // Tanned avatar w Brown hair.
                ui->TBrStackedShirts->setCurrentIndex(3);

            // RED HAIR OPTIONS - Star Trek
            else if(ui->avatarPreviewStack->currentIndex() == 0 && ui->hairstyleCombo->currentIndex() == (4)) // White avatar w Red hair.
            {
                ui->WRStackedShirts->setCurrentIndex(4);
            }
            else if(ui->avatarPreviewStack->currentIndex() == 1 && ui->hairstyleCombo->currentIndex() == (4)) //Black avatar w Red hair.
            {
                ui->BRStackedShirts->setCurrentIndex(3);
            }
            else if(ui->avatarPreviewStack->currentIndex() == 2 && ui->hairstyleCombo->currentIndex() == (4)) // Tanned avatar w Red hair.
                ui->TRStackedShirts->setCurrentIndex(3);
    }*/
        else{}

}
}
