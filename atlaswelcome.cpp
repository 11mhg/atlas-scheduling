#include "atlaswelcome.h"
#include "ui_atlaswelcome.h"
#include <QScrollBar>
#include <sstream>

AtlasWelcome::AtlasWelcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AtlasWelcome)
{
    ui->setupUi(this);
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

    // Shirt Combo Box
    ui->outfitCombo->addItem("-None-");
    ui->outfitCombo->addItem("Pink");
    //ui->outfitCombo->addItem("Blue Suit");
    ui->outfitCombo->addItem("Star rek");


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
        User.LoadTasks();
        vector<Task*> weekTasks;
        for (int i = 0 ; i < User.wtasks.size();i++){
            weekTasks.push_back(&User.wtasks.at(i));
        }
        ui->calendar->loadTasks(weekTasks);

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

        User.SaveUserInfo();
        User.LoadTasks();
        std::string def = "Default";
        Category *newCat = new Category(def,13408767,1);
        User.categories.push_back(newCat);
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
    User.SaveUserInfo();
    ui->stacked->setCurrentIndex(0);
    User = Profile();
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
    //open up the settings page

    ui->stacked->setCurrentIndex(9);
}

void AtlasWelcome::on_logoutButton_clicked()
{
    //logout, clear memory and return to welcome page.
    User.SaveUserInfo();
    ui->pswdIn->clear();
    ui->stacked->setCurrentIndex(0);
}

void AtlasWelcome::on_saveCatButton_clicked()
{

    // this case will have to create and save a new category and task.
    if (ui->newCatNameIn->text().toStdString() == ""){
        QDateTime enddate = ui->newTaskEndSelect->dateTime();
        enddate.addDays(7);
        std::string endd = enddate.toString().toStdString();
        Category *defCat;
        for (uint i = 0 ; i < User.categories.size(); i++){
            if (User.categories.at(i)->getName() == "Default")
            {
                defCat = User.categories.at(i);
            }
        }
        Task newTask(ui->newTaskNameIn->text().toStdString(), ui->newTaskStartSelect->dateTime(), ui->newTaskEndSelect->dateTime(),enddate,defCat->getName(),&User);
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
    vector<Task*> weekTasks;
    for (int i = 0 ; i < User.wtasks.size();i++){
        weekTasks.push_back(&User.wtasks.at(i));
    }
    ui->calendar->loadTasks(weekTasks);
    setCategorySelect();
    ui->pswdIn->clear();
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
    vector<Task*> weekTasks;
    for (int i = 0 ; i < User.wtasks.size();i++){
        weekTasks.push_back(&User.wtasks.at(i));
    }
    ui->calendar->loadTasks(weekTasks);
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
