#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>
#include <httplib.h>
#include <string>

using namespace Rice;

class Clavis {
        std::string port;
    public:
        Clavis();
        void clavis_set_port(const std::string& port);
        void clavis_run();
};

Clavis::Clavis() {}

void Clavis::clavis_set_port(const std::string& port) {
    this->port = port;
}

void Clavis::clavis_run() {
    using namespace httplib;

    Server svr;

    svr.Get("/", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
        auto numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
    });

    svr.listen("localhost", std::stoi(this->port));
}

extern "C" {
    void Init_clavis() {
        Data_Type<Clavis> rb_cClavis = define_class<Clavis>("Clavis")
            .define_constructor(Constructor<Clavis>())
            .define_method("set_port", &Clavis::clavis_set_port, Rice::Arg("port"))
            .define_method("run", &Clavis::clavis_run);
    }
}