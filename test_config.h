#ifndef MARIADBCLIENTPP_TEST_CONFIG_H
#define MARIADBCLIENTPP_TEST_CONFIG_H

namespace mariadb {
    namespace testing {
        class TestConfig {
        public:
            static constexpr const char *Hostname = "@TEST_HOSTNAME@";
            static const uint32_t Port = 1;
            static constexpr const char *User = "@TEST_USERNAME@";
            static constexpr const char *Password = "@TEST_PASSWORD@";
            static constexpr const char *UnixSocket = "@TEST_UNIXSOCKET@";
            static constexpr const char *Database = "@TEST_DATABASE@";
        };
    }
}

#endif //MARIADBCLIENTPP_TEST_CONFIG_H
