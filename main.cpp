#include "mariadb++/account.hpp"
//#include "mariadb++/bind.hpp"
//#include "mariadb++/concurrency.hpp"
//#include "mariadb++/connection.hpp"
//#include "mariadb++/conversion_helper.hpp"
//#include "mariadb++/data.hpp"
//#include "mariadb++/date_time.hpp"
//#include "mariadb++/decimal.hpp"
//#include "mariadb++/exceptions.hpp"
//#include "mariadb++/last_error.hpp"
//#include "mariadb++/result_set.hpp"
//#include "mariadb++/save_point.hpp"
//#include "mariadb++/statement.hpp"
//#include "mariadb++/time.hpp"
//#include "mariadb++/time_span.hpp"
//#include "mariadb++/transaction.hpp"
//#include "mariadb++/types.hpp"

using namespace std;
using namespace mariadb;

#include <mariadb++/account.hpp>
#include <mariadb++/conversion_helper.hpp>

using namespace mariadb;

account::account(const std::string &host_name, const std::string &user_name,
                 const std::string &password, const std::string &schema, u32 port,
                 const std::string &unix_socket)
    : m_auto_commit(true),
      m_port(port),
      m_host_name(host_name),
      m_user_name(user_name),
      m_password(password),
      m_schema(schema),
      m_unix_socket(unix_socket) {}

const std::string &account::host_name() const { return m_host_name; }

const std::string &account::user_name() const { return m_user_name; }

const std::string &account::password() const { return m_password; }

const std::string &account::unix_socket() const { return m_unix_socket; }

u32 account::port() const { return m_port; }

const std::string &account::ssl_key() const { return m_ssl_key; }

const std::string &account::ssl_certificate() const { return m_ssl_certificate; }

const std::string &account::ssl_ca() const { return m_ssl_ca; }

const std::string &account::ssl_ca_path() const { return m_ssl_ca_path; }

const std::string &account::ssl_cipher() const { return m_ssl_cipher; }

const std::string &account::schema() const { return m_schema; }

void account::set_schema(const std::string &schema) { m_schema = schema; }

void account::set_ssl(const std::string &key, const std::string &certificate, const std::string &ca,
                      const std::string &ca_path, const std::string &cipher) {
    m_ssl_key = key;
    m_ssl_certificate = certificate;
    m_ssl_ca = ca;
    m_ssl_ca_path = ca_path;
    m_ssl_cipher = cipher;
}

bool account::auto_commit() const { return m_auto_commit; }

void account::set_auto_commit(bool auto_commit) { m_auto_commit = auto_commit; }

bool account::store_result() const { return m_store_result; }

void account::set_store_result(bool store_result) { m_store_result = store_result; }

const account::map_options_t &account::options() const { return m_options; }

const std::string account::option(const std::string &name) const {
    const map_options_t::const_iterator value = m_options.find(name);

    // return option value if found
    return value == m_options.end() ? "" : value->second;
}

void account::set_option(const std::string &name, const std::string &value) {
    m_options[name] = value;
}

void account::clear_options() { m_options.clear(); }

const account::map_connect_options_t &account::connect_options() const { return m_connect_options; }

void account::clear_connect_options() { m_connect_options.clear(); }

void account::set_connect_option(mysql_option option, bool arg) {
    m_connect_options[option] = std::unique_ptr<option_arg>(new option_arg_bool(arg));
}

void account::set_connect_option(mysql_option option, int arg) {
    m_connect_options[option] = std::unique_ptr<option_arg>(new option_arg_int(arg));
}

void account::set_connect_option(mysql_option option, const std::string &arg) {
    m_connect_options[option] = std::unique_ptr<option_arg>(new option_arg_string(arg));
}


account_ref account::create(const std::string &host_name, const std::string &user_name,
                            const std::string &password, const std::string &schema, u32 port,
                            const std::string &unix_socket) {
    return account_ref(new account(host_name, user_name, password, schema, port, unix_socket));
}

int main()
{
    /**
     * Create an account
     *
     * @param host_name Hostname to connect to
     * @param user_name Username to log in with
     * @param password  Password for the user to log in with (may be empty)
     * @param schema    Database name to select on connect. Can also be set after connecting
     * @param port      Port of host to connect to (defaults to 3306)
     * @param unix_sock Path of unix socket to connect to. If specified, host and port will be
     * ignored
     */
    account_ref acc = account::create("localhost", "root", "3215237", "Restaurant_Claude_Monet", 3306, "hz");

//    // create connection
//    connection_ref con = connection::create(acc);

//    // insert, update, select on the connection
//    u64 id = con->insert("INSERT INTO table VALUES (1, 2, 3)");
//    u64 affected = con->execute("UPDATE table SET a=1");
//    result_set_ref result = con->query("SELECT * FROM table");

//    // create statement
//    statement_ref stmt = con->create_statement(f);

//    // insert, update, select on the statement
//    u64 id = stmt->insert();
//    u64 affected = stmt->execute();
//    result_set_ref result = stmt->query();

//    // reading from a result set
//    while (result->next()) {
//        int a = result->get_unsigned32(0);
//        int b = result->get_unsigned32("b");
//    }

//    // insert using prepared statement
//    statement_ref stmt = con->create_statement("INSERT INTO table (?, ?, ?)");
//    stmt->set_unsigned32(0, 13);
//    stmt->set_unsigned32(1, 37);
//    stmt->set_unsigned32(2, 42);
//    stmt->insert();

    return 0;
}
