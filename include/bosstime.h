//
// Created by henry on 2021-12-21.
//

#ifndef MCSWEBUI_BOSSTIME_H
#define MCSWEBUI_BOSSTIME_H

#include "crow.h"
#include <string>
#include <vector>
#include <chrono>
#include <boost/filesystem.hpp>

namespace BOSS {

    class BossTime {

    private:
        crow::SimpleApp app;

    public:
        BossTime();

        ~BossTime();

        void run(const int port=80);

    private:
        std::string version();

        void send_file(crow::response &res, std::string filename, std::string content_type);

        void send_html(crow::response &res, std::string filename);

        void send_script(crow::response &res, std::string filename);

        void send_image(crow::response &res, std::string filename);

        void send_style(crow::response &res, std::string filename);

    };
}


#endif //MCSWEBUI_BOSSTIME_H
