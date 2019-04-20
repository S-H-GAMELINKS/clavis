#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>
#include <httplib.h>
#include <string>
#include <unordered_map>

using namespace Rice;

class Clavis {
        std::unordered_map<std::string, std::string> routes;
        std::string port;
        const std::string default_response = "Hello Clavis!\n Enjoy Your Ruby Web dev!";
    public:
        Clavis();
        void clavis_set_port(const std::string& port);
        const std::string clavis_return_port();
        bool clavis_set_route(const std::string& route, const std::string& response);
        const std::string clavis_get_route_bracket(const std::string& key);
        void clavis_run();
};

Clavis::Clavis() {
    this->routes.emplace("/", this->default_response);
}

void Clavis::clavis_set_port(const std::string& port) {
    this->port = port;
}

const std::string Clavis::clavis_return_port() {
    return this->port;
}

bool Clavis::clavis_set_route(const std::string& route, const std::string& response) {

    this->routes[route] = response;

    if (this->routes[route] == response)
        return true;
    else
        return false;
}

const std::string Clavis::clavis_get_route_bracket(const std::string& key) {
    return this->routes[key];
}

void Clavis::clavis_run() {
    using namespace httplib;

    Server svr;

    for (auto&& r : this->routes)
        svr.Get(r.first.c_str(), [&](const Request& req, Response& res) {
            res.set_content(r.second.c_str(), "text/plain");
        });

    svr.listen("localhost", std::stoi(this->port));
}

extern "C" {
    void Init_clavis() {
        Data_Type<Clavis> rb_cClavis = define_class<Clavis>("Clavis")
            .define_constructor(Constructor<Clavis>())
            .define_method("set_port", &Clavis::clavis_set_port, Rice::Arg("port"))
            .define_method("port", &Clavis::clavis_return_port)
            .define_method("set_route", &Clavis::clavis_set_route, (Rice::Arg("route"), Rice::Arg("response")))
            .define_method("[]", &Clavis::clavis_get_route_bracket)
            .define_method("run", &Clavis::clavis_run);
    }
}