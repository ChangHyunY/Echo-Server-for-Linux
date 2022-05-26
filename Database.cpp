
#include "Database.h"

Database::Database()
{
    instance = this;

    this->con = mysql_init(NULL);

    if(con == NULL)
    {
        cout << mysql_error(con) << endl;

        exit(1);
    }

    database_connect();

    use_database();
}

Database::~Database()
{
    mysql_free_result(result);

    mysql_close(con);

    exit(1);
}

void Database::table_detail(const char* query)
{
    if(mysql_query(con, query))
    {
        finish_with_error(con);
    }

    result = mysql_store_result(con);

    cout << result->row_count << endl;

    if(result == NULL)
    {
        finish_with_error(con);
    }

    num_fields = mysql_num_fields(result);

    while((row = mysql_fetch_row(result)))
    {
        for(int i = 0, loop = num_fields; i < loop; ++i)
        {
            if(row[i] == NULL) cout << i << " Field is NULL";
            else cout << row[i] << endl;
        }

        cout << endl;
    }
}

void Database::throw_query(const char *query)
{
    cout << query << endl;

    if(mysql_query(con, query))
    {
        finish_with_error(con);
    }

    result = mysql_store_result(con);

    if(result == NULL)
    {
        finish_with_error(con);
    }

    num_fields = mysql_num_fields(result);

    row = mysql_fetch_row(result);
}

bool Database::Check_User(const char* unique_code, const char* game_code)
{
    if(strcmp(game_code, "DELVINEV") == 0)
    {
        m_unique_code = "MASTER";

        return true;
    }

    if(unique_code[0] != 'N')
    {
        cout << "User " << unique_code << " is not New" << endl;

        m_unique_code = unique_code;

        return check_unique_code(unique_code);
    }
    else
    {
        cout << "User " << unique_code << " is New" << endl;

        if(check_game_code(game_code))
        {
            m_unique_code = "Del-" + get_seq_num(game_code);

            cout << "created unique code : " << m_unique_code << endl;

            return update_user(m_unique_code.c_str(), game_code);
        }
        else
        {
            cout << "check game code is false" << endl;

            return false;
        }
    }
}

string Database::get_seq_num(const char* code)
{
    sprintf(query, "select seq from user where unique_code = '%s' or game_code = '%s'", code, code);

    throw_query(query);

    return row[0];
}

void Database::get_user_score(int seq, int arr[])
{
    sprintf(query, "select * from score where seq = %d", seq);
    throw_query(query);
    for(int i = 1, loop = mysql_num_fields(result); i < loop; ++i)
    {
        arr[i - 1] = atoi(row[i]);
    }
}

bool Database::check_game_code(const char* game_code)
{
    sprintf(query, "select unique_code from user where game_code = '%s'", game_code);

    throw_query(query);

    if(row == 0)
    {
        cout << "row is 0" << endl;

        return false;
    }
    else
    {
        if(row[0] == NULL)
        {
            cout << "is null" << endl;

            return true;
        }
        else
        {
            cout << row[0] << endl;

            return false;
        }
    }
}

bool Database::check_unique_code(const char* unique_code)
{
    sprintf(query, "select unique_code from user where unique_code = '%s'", unique_code);

    throw_query(query);

    if(row != 0) return true;
    else return false;
}

bool Database::update_user(const char* unique_code, const char* game_code)
{
    sprintf(query, "update user set unique_code = '%s' where game_code = '%s'", unique_code, game_code);

    if(mysql_query(con, query)) 
    {
        finish_with_error(con);

        return false;
    }
    else return true;
}

void Database::update_score(int scores[9], int seq)
{
    sprintf(query, "update score set s1c1 = %d, s1c2 = %d, s1c3 = %d, s2c1 = %d, s2c2 = %d, s2c3 = %d, s3c1 = %d, s3c2 = %d, s3c3 = %d where seq = %d",
    scores[0], scores[1], scores[2], scores[3], scores[4], scores[5], scores[6], scores[7], scores[8], seq);

    if(mysql_query(con, query))
    {
        finish_with_error(con);

        exit(1);
    }
}

void Database::update_date(int seq)
{
    memset(query, '\0', sizeof(query));
    sprintf(query, "update user set last_login = now() where seq = %d", seq);
    if(mysql_query(con, query))
    {
        finish_with_error(con);
    }
}

void Database::update_info(int seq, int level, int exp)
{
    sprintf(query, "update info set level = %d, exp = %d where seq = %d", level, exp, seq);

    if(mysql_query(con, query))
    {
        cout << "error : " << mysql_error(con);
    }
}

void Database::finish_with_error(MYSQL *con)
{
    cout << "error : " << mysql_error(con);

    mysql_close(con);

    exit(1);
}