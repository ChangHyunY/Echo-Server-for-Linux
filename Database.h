
#ifndef DATABASE
#define DATABASE

#include <iostream>
#include <string.h>
#include "/usr/include/mysql/mysql.h"

using namespace std;

class Database
{
private:
    Database();

public:
    ~Database();

    static Database* GetInstance()
    {
        if(Database::instance == nullptr)
        {
            Database::instance = new Database();
        }

        return Database::instance;
    }

    void table_detail(const char* query);                               // print detail of table datas

    void throw_query(const char *query);                                // throw query to MySQL server

    bool Check_User(const char* unique_code, const char* game_code);    // return true if user information is vaild

    string get_last_unique_code() 
    { 
        cout << hex << m_unique_code << endl;

        return m_unique_code; 
    }

    string get_seq_num(const char* code);

    void get_user_score(int seq, int arr[]);
   
    bool check_game_code(const char* game_code);                        // return true if gamecode into db

    bool check_unique_code(const char* unique_code);                    // return true if unique code is matched.

    bool update_user(const char* unique_code, const char* game_code);   // return true if update is successed

    void update_score(int scores[9], int seq);

    void update_date(int seq);

    void update_info(int seq, int level, int exp);

    void finish_with_error(MYSQL *con);

private:
    void database_connect()
    {
        if(mysql_real_connect(con, NULL, user, pw, db, 0, NULL, 0) == NULL)
        {
            finish_with_error(con);
        }
    }

    void use_database()
    {
        if(mysql_query(con, "use delvine"))
        {
            finish_with_error(con);
        }

        printf("use delvine\n");
    }

    static Database *instance;

    MYSQL *con;

    MYSQL_RES *result;

    MYSQL_ROW row;

    MYSQL_FIELD* field;

    const char *user = "yoo";

    const char *pw = "yoo1628*";

    const char *db = "delvine";

    int num_fields;

    char query[126];

    string m_unique_code;
};

#endif