//
// Created by henry on 2021-12-21.
//

#include "bosstime.h"

BOSS::BossTime::BossTime() {

    crow::mustache::set_base(".");

    CROW_ROUTE(app, "/")([&](const crow::request &req) {
        crow::response res;
        this->send_html(res, "index");
        return res;
    });

    CROW_ROUTE(app, "/<string>")([&](const crow::request &req, std::string _1) {
        crow::response res;
        this->send_html(res, _1);
        return res;
    });

    CROW_ROUTE(app, "/css/<string>")([&](const crow::request &req, std::string _1) {
        crow::response res;
        this->send_style(res, _1);
        return res;
    });

    CROW_ROUTE(app, "/js/<string>")([&](const crow::request &req, std::string _1) {
        crow::response res;
        this->send_script(res, _1);
        return res;
    });

    CROW_ROUTE(app, "/img/<string>")([&](const crow::request &req, std::string _1) {
        crow::response res;
        this->send_image(res, _1);
        return res;
    });

    CROW_ROUTE(app, "/img/<string>/<string>")([&](const crow::request &req, std::string _1, std::string _2) {
        crow::response res;
        this->send_image(res, _1 + "/" + _2);
        return res;
    });

    CROW_ROUTE(app, "/about")
            ([]() {
                return "About ITRI MCS.";
            });
}

BOSS::BossTime::~BossTime() {

}

void BOSS::BossTime::run(const int port) {
    this->app.port(port).multithreaded().run();
}

std::string BOSS::BossTime::version() {
    return "1.0.0";
}

void BOSS::BossTime::send_file(crow::response &res, std::string filename, std::string content_type) {
    std::string ROOT_DIR = "../../html/";
    std::string filename_path = ROOT_DIR.append(filename);

    try {
        std::ifstream ifs;
        ifs.open(filename_path, std::ifstream::in);
        ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        std::ostringstream oss;
        oss << ifs.rdbuf();
        ifs.close();

        res.set_header("Content-Type", content_type);
        res.write(oss.str());
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        res.code = 404;
        res.write("content not found...");
    }
}

void BOSS::BossTime::send_html(crow::response &res, std::string _1) {
    if (_1.find("html") == std::string::npos)
        return send_file(res, _1.append(".html"), "text/html");
    else
        return send_file(res, _1, "text/html");
}

void BOSS::BossTime::send_script(crow::response &res, std::string _1) {
    std::string path = "js/" + _1;
    return send_file(res, path, "text/script");
}

void BOSS::BossTime::send_image(crow::response &res, std::string _1) {
    std::string path = "img/" + _1;
    return send_file(res, path, "text/jpeg");
}

void BOSS::BossTime::send_style(crow::response &res, std::string _1) {
    std::string path = "css/" + _1;
    return send_file(res, path, "text/css");
}