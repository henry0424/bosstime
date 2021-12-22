//
// Created by henry on 2021-12-21.
//

#include "bosstime.h"
#include <memory>

using namespace BOSS;

int main() {
    auto server = std::make_shared<BOSS::BossTime>();
    server->run(4096);
}
