#include "profile.h"

/**
 * @brief Profile::Profile
 * Construct empty profile
 */
Profile::Profile()
{
    username="";
    password="";
}

/**
 * @brief Profile::Profile
 * Construct profile with Username and password
 */
Profile::Profile(std::string User, std::string Pass)
{
    username=User;
    password=Pass;
    SaveUserInfo();
}



/**
 * @brief EncryptLogin
 * Encrypts username and password as login hash.
 * @return
 * Returns a login hash using username and password.
 */
std::string EncryptLogin(std::string user,std::string pass)
{
    std::string out = user+pass;
    Botan::AutoSeeded_RNG rng;
    std::string toret = Botan::generate_bcrypt(out,rng,10);
    return toret;
}

/**
 * @brief HashUserName
 * Hashes user name using sha256
 * @return
 * returns username hash.
 */
std::string HashUserName(std::string user)
{
    Botan::Pipe pipe(new Botan::Chain(new Botan::Hash_Filter(new Botan::SHA_256),new Botan::Hex_Encoder));
    pipe.process_msg(user);
    std::string buffer = pipe.read_all_as_string(0);
    return buffer;
}

/**
 * @brief Profile::SaveUserInfo
 * Saves Users user name and password in profiles
 * file. This acts as a quick way to check if user
 * exists.
 */
void Profile::SaveUserInfo()
{
    std::string output = EncryptLogin(username,password);
    std::ofstream pFile (HashUserName(username));
    if (pFile.is_open())
    {
        pFile << output << '\n';
        std::string info = Encrypt(name+","+gender+","+DoB+","+characterSelect);
        pFile << info << '\n';
        pFile << "Category" << '\n';
        std::string cat;
        for (unsigned int i=0; i < categories.size(); i++){
            cat = (*categories.at(i)).fileWrite();
            cat = Encrypt(cat);
            pFile << cat << '\n';
        }
        pFile << "Tasks" << '\n';
        std::string allTasks;
        for (unsigned int i=0; i < ptasks.size();i++){
            allTasks = ptasks.at(i).fileWrite();
            allTasks = Encrypt(allTasks);
            pFile << allTasks << '\n';
        }
    }
    pFile.close();
}

bool UserNameExists(std::string username)
{
    std::string toCheck = HashUserName(username);
    std::ifstream iFile(toCheck);
    return (bool)iFile;
}

bool SuccessfulLogin(std::string username, std::string password){
    std::string FileName = HashUserName(username);
    std::ifstream iFile(FileName);
    std::string toFind = username+password;
    if (iFile.is_open()){
        std::string lines;
        while(std::getline(iFile,lines)){
            if (Botan::check_bcrypt(toFind,lines)){
                iFile.close();
                return true;
            }
        }
    }
    iFile.close();
    return false;
}

/**
 * @brief LoadUser
 * Loads User password and username as well as calendar ideally.
 * Is a wrapper for Login
 * @return
 * returns the user profile with the calendar and tasks.
 */
Profile LoadUser(std::string Username, std::string Password)
{
    std::string ToLoad = HashUserName(Username);
    //make new profile with calendar loaded in

    return Profile(Username,Password);
}

void Profile::LogOut(){
    UpdateSave();
}

void Profile::UpdateSave(){
    std::string FileName = HashUserName(username);
    remove (FileName.c_str());
    SaveUserInfo();
    //Get all strings to save here
    std::string toEncrypt;
    //save all tasks and encrypt here
    std::string EncryptedToSave = Encrypt(toEncrypt);

    std::ofstream iFile;
    iFile.open(FileName,std::ios_base::app);
    if (iFile.is_open())
    {
        iFile << EncryptedToSave << std::endl;
    }
    iFile.close();
}

std::string Profile::Encrypt(std::string toEncrypt)
{
    Botan::secure_vector<Botan::byte> mSalt;
    mSalt.resize(48);
    for (int i = 0 ; i < mSalt.size();i++)
    {
        mSalt[i] = i;
    }
    try{
       Botan::PKCS5_PBKDF2 pbkdf2(new Botan::HMAC(new Botan::SHA_160));
       const Botan::u32bit PBKDF2_ITERATIONS = 100;
       Botan::KDF* kdf= Botan::get_kdf("KDF2(SHA-1)");

       Botan::secure_vector<Botan::byte> mMaster = pbkdf2.derive_key(48, password,
                                                                     &mSalt[0],mSalt.size(),PBKDF2_ITERATIONS).bits_of();
       Botan::SymmetricKey mkey = kdf->derive_key(32, mMaster, "salt1");

       Botan::InitializationVector mIV = kdf->derive_key(16, mMaster, "salt2");

       Botan::Pipe pipe (Botan::get_cipher("AES-256/CBC/PKCS7",mkey,mIV,Botan::ENCRYPTION),new
                         Botan::Base64_Encoder);
       pipe.process_msg(toEncrypt);
       return pipe.read_all_as_string(0);


    }
    catch(...){
        return "";
    }
}

std::string Profile::Decrypt(std::string toDecrypt)
{
    Botan::secure_vector<Botan::byte> mSalt;
    mSalt.resize(48);
    for (int i = 0 ; i < mSalt.size();i++)
    {
        mSalt[i] = i;
    }
    try{
        Botan::PKCS5_PBKDF2 pbkdf2(new Botan::HMAC(new Botan::SHA_160));
        const Botan::u32bit PBKDF2_ITERATIONS = 100;

        Botan::KDF* kdf = Botan::get_kdf("KDF2(SHA-1)");

        Botan::secure_vector<Botan::byte> mMaster = pbkdf2.derive_key(48,password,&mSalt[0],mSalt.size(),PBKDF2_ITERATIONS).bits_of();
        Botan::SymmetricKey mkey = kdf->derive_key(32, mMaster,"salt1");
        Botan::InitializationVector mIV = kdf->derive_key(16,mMaster,"salt2");

        Botan::Pipe pipe(new Botan::Base64_Decoder, Botan::get_cipher("AES-256/CBC/PKCS7",mkey,mIV,Botan::DECRYPTION));
        pipe.process_msg(toDecrypt);
        return pipe.read_all_as_string(0);
    }
    catch(...){
        return "";
    }

}

std::string Profile::LoadInfo()
{
    std::string FileName = HashUserName(username);
    std::string toDecrypt;
    std::string lines;
    int i = 0;
    std::ifstream iFile(FileName);
    if (iFile.is_open()){
        while(std::getline(iFile,lines))
        {
            if (i==1)
            {
                toDecrypt = lines;
                break;
            }
            i+=1;
        }
    }
    return Decrypt(toDecrypt);

}

void Profile::LoadTasks()
{
    std::string FileName = HashUserName(username);
    std::string Decrypted;
    std::string lines;
    int i = 0;
    int c = 0;
    std::ifstream iFile(FileName);
    ptasks.clear();
    wtasks.clear();
    if (iFile.is_open()){
        while(std::getline(iFile,lines))
        {
            if (i>1)
            {
                if (c==1 && lines.find("Tasks")==std::string::npos){
                    Category *temp = new Category(Decrypt(lines));
                    categories.push_back(temp);
                }
                if (c==2){
                    Task temp(Decrypt(lines));
                    ptasks.push_back(temp);
                }
                if (lines.find("Category")!=std::string::npos){
                    c = 1;
                }
                if (lines.find("Tasks")!=std::string::npos){
                    c = 2;
                }

            }
            i+=1;
        }
    }
    std::sort(ptasks.begin(),ptasks.end());

    time_t rawtime;
    time_t starTime;
    time_t endTime;
    std::tm *timeinfo;
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    starTime = std::mktime(timeinfo);
    int wday = timeinfo->tm_wday;
    starTime = starTime -(60*60*24*wday);
    endTime = starTime + (60*60*24*7);

    for (unsigned int i=0; i < ptasks.size(); i++){
        if (starTime < ptasks.at(i).task_time.start)
        {
            if(ptasks.at(i).task_time.start < endTime)
            {
                wtasks.push_back(ptasks.at(i));
            }
        }
    }
}



